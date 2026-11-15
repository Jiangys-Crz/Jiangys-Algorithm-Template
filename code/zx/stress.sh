#!/usr/bin/env bash
set -euo pipefail

if (( $# < 3 || $# > 4 )); then
    echo 'usage: stress.sh GEN BRUTE SOL [ROUNDS]' >&2
    exit 2
fi

gen=$1
brute=$2
sol=$3
rounds=${4:-1000}
if [[ ! $rounds =~ ^(0|[1-9][0-9]{0,17})$ ]]; then
    echo 'ROUNDS must be a decimal integer (0 = unlimited)' >&2
    exit 2
fi
limit=${TIME_LIMIT:-2s}

work=$(mktemp -d "${TMPDIR:-/tmp}/xcpc-stress.XXXXXXXX")
keep=1
cleanup() {
    if (( keep )); then
        printf 'Files kept in %s\n' "$work" >&2
    else
        rm -- "$work"/{data.in,brute.out,sol.out,gen.err,brute.err,sol.err}
        rmdir -- "$work"
    fi
}
trap cleanup EXIT
trap 'exit 130' INT
trap 'exit 143' TERM

fail() {
    printf 'seed=%s %s\n' "$seed" "$*" >&2
    exit 1
}

run_case() {
    local name=$1 out=$2 status
    shift 2
    if timeout -k 1s "$limit" "$@" > "$work/$out" 2> "$work/$name.err"; then
        return 0
    else
        status=$?
    fi
    fail "$name failed (exit $status)"
}

for (( i=0; rounds == 0 || i < rounds; ++i )); do
    seed=$(( (i + 1) & 4294967295 ))
    for file in brute.out sol.out brute.err sol.err; do
        : > "$work/$file"
    done
    run_case gen data.in "$gen" "$seed" < /dev/null
    run_case brute brute.out "$brute" < "$work/data.in"
    run_case sol sol.out "$sol" < "$work/data.in"
    if diff -uZ -- "$work/brute.out" "$work/sol.out"; then
        if (( (i + 1) % 100 == 0 )); then
            printf 'Passed %d cases\n' "$((i + 1))"
        fi
    else
        status=$?
        if (( status == 1 )); then fail 'outputs differ'; fi
        fail "diff failed (exit $status)"
    fi
done

keep=0
printf 'All %s cases passed\n' "$rounds"
