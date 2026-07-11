#!/bin/sh

g++ -std=c++23 -O2 -Wall -Wextra -Wshadow \
    -fsanitize=address,undefined \
    -DLOCAL \
    $1.cpp -o sol

./sol < $2.in > sol.out

diff -Z sol.out $2.out

if [ $? -eq 0 ]; then
    echo "Accepted"
else
    echo "Wrong Answer"
fi