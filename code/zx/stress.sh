#!/bin/sh

while true; do
    python gen.py > data.in

    ./std < data.in > std.out
    ./sol < data.in > sol.out

    diff -Z std.out sol.out || break

    echo "Accepted"
done