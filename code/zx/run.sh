#!/bin/sh

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 a.cpp|a.py sample-number" >&2
    exit 2
fi
case $2 in
    ''|*[!0-9]*) echo "Sample number must contain only digits." >&2; exit 2 ;;
esac
case $1 in
    /*) src=$1 ;;
    *) src=./$1 ;;
esac
input=$2.in
answer=$2.out
[ -f "$answer" ] || answer=$2.ans
for file in "$src" "$input" "$answer"; do
    [ -f "$file" ] || { echo "Missing file: $file" >&2; exit 2; }
done

tmpbase=$TMPDIR
[ -n "$tmpbase" ] || tmpbase=/tmp
work=$(mktemp -d "$tmpbase/xcpc-run.XXXXXXXX") || exit 2
trap 'rm -rf "$work"' 0
trap 'exit 130' INT
trap 'exit 143' TERM

case $src in
    *.[cC][pP][pP])
        [ -n "$CXXSTD" ] || CXXSTD=c++23
        g++ -x c++ -std="$CXXSTD" -O2 -Wall -Wextra -Wshadow -DLOCAL \
            "$src" -o "$work/sol" || exit 2
        set -- "$work/sol"
        ;;
    *.[pP][yY])
        set -- python3 "$src"
        ;;
    *) echo "Use a .cpp or .py source file." >&2; exit 2 ;;
esac

run_status=0
"$@" < "$input" > "$work/actual" || run_status=$?
printf '%s\n' '=== Expected output ==='
cat "$answer"
printf '\n%s\n' '=== Actual output ==='
cat "$work/actual"
printf '\n%s\n' '=== Differences ==='

cr=$(printf '\r')
sed "s/$cr\$//" "$answer" > "$work/expected.txt" || exit 2
sed "s/$cr\$//" "$work/actual" > "$work/actual.txt" || exit 2
result=0
diff -U 0 -L "$answer" -L 'actual output' \
    "$work/expected.txt" "$work/actual.txt" > "$work/diff" || result=$?
case $result in
    0) echo "No differences." ;;
    1)
        if [ -t 1 ] && [ "$TERM" != dumb ]; then
            awk 'NR <= 2 { print; next }
                 /^[-+]/ { printf "\033[31m%s\033[0m\n", $0; next }
                 { print }' "$work/diff"
        else
            cat "$work/diff"
        fi
        ;;
    *) echo "Comparison failed." >&2; exit 2 ;;
esac
if [ "$run_status" -ne 0 ]; then
    echo "Runtime error (exit $run_status)." >&2
    exit 2
fi
if [ "$result" -eq 0 ]; then
    echo "Accepted"
else
    echo "Wrong Answer"
fi
exit "$result"
