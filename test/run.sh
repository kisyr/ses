#! /bin/sh
set -x
for file in *.cpp; do
    g++ -g -std=c++0x $file -I.. && ./a.out || return 1
done
rm a.out
return 0
