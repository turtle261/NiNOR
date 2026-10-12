#!/bin/sh
f1=$(mktemp); f2=$(mktemp); for f in graphs/*; do 
./dcg $f | rg node | sort | sha512sum > $f1 && cat $f | rg node | sort | sha512sum > $f2 && cmp $f1 $f2 && echo "TEST1_PASSED on $f";
done
