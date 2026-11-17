#!/bin/sh
usage() { echo "Usage: $0 a.cpp sample-number" >&2; exit 2; }
[ "$#" -eq 2 ] || usage
case $1 in *.[cC][pP][pP]) ;; *) usage ;; esac
case $2 in ''|*[!0-9]*) usage ;; esac
case $1 in /*) src=$1 ;; *) src=./$1 ;; esac

answer=$2.out
[ -f "$answer" ] || answer=$2.ans
for file in "$src" "$2.in" "$answer"; do
    [ -f "$file" ] || { echo "Missing file: $file" >&2; exit 2; }
done
work=$(mktemp -d "${TMPDIR:-/tmp}/xcpc-run.XXXXXXXX") || exit 2
trap 'rm -rf "$work"' 0
trap 'exit 130' INT
trap 'exit 143' TERM

g++ -x c++ -std=c++23 -O2 -DLOCAL "$src" -o "$work/sol" || exit 2
"$work/sol" < "$2.in" > "$work/actual" || { echo 'Runtime error' >&2; exit 2; }
echo '=== Expected output ==='
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
    0) echo Accepted ;;
    1)
        red=0
        [ -t 1 ] && [ "$TERM" != dumb ] && red=1
        awk -v red="$red" '
            red && NR > 2 && /^[-+]/ { $0 = "\033[31m" $0 "\033[0m" }
            1
        ' "$work/diff"
        echo 'Wrong Answer' ;;
    *) echo 'Comparison failed' >&2 ;;
esac
exit "$result"
