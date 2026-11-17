#!/bin/sh
work=$(mktemp -d "${TMPDIR:-/tmp}/xcpc-stress.XXXXXXXX") || exit 2
trap 'rm -rf "$work"' 0
trap 'exit 130' INT
trap 'exit 143' TERM

while :; do
    ./gen > data.in || exit 2
    ./std < data.in > std.out || exit 2
    ./sol < data.in > sol.out || exit 2
    sed 's/[[:space:]]*$//' std.out > "$work/std.txt" || exit 2
    sed 's/[[:space:]]*$//' sol.out > "$work/sol.txt" || exit 2
    diff -u -L std.out -L sol.out "$work/std.txt" "$work/sol.txt" || exit $?
    echo Accepted
done
