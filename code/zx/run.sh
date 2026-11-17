#!/bin/sh
usage() { echo "Usage: $0 a.cpp sample-number" >&2; exit 2; }
[ "$#" -eq 2 ] || usage
case $1 in *.[cC][pP][pP]) ;; *) usage ;; esac
case $1 in /*) src=$1 ;; *) src=./$1 ;; esac

work=$(mktemp -d "${TMPDIR:-/tmp}/xcpc-run.XXXXXXXX") || exit 2
trap 'rm -rf "$work"' 0
trap 'exit 2' HUP INT TERM
g++ -x c++ -std=c++23 -O2 -DLOCAL "$src" -o "$work/sol" || exit 2
"$work/sol" < "$2.in" > "$work/actual" || exit 2

echo '=== Expected output ==='
cat -- "$2.ans" || exit 2
printf '\n%s\n' '=== Actual output ==='
cat "$work/actual" || exit 2
printf '\n'

cr=$(printf '\r')
sed "s/$cr\$//" < "$2.ans" > "$work/want" || exit 2
sed "s/$cr\$//" "$work/actual" > "$work/got" || exit 2
cmp -s "$work/want" "$work/got"
case $? in
    0) echo Accepted ;;
    1) echo 'Wrong Answer'; exit 1 ;;
    *) exit 2 ;;
esac
