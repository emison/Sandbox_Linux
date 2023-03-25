#!/bin/bash
baseline=$(mktemp)
result=$(mktemp)

# Create baseline
echo -e "Town with the most number of packages is B
Town with the most number of packages is A
A:
    0:
        a
        b
    1:
        c
        e
        f
        h
B:
    0:
        d" > $baseline

# Execute code
posttrans <<< "2
A
2
2 1 3
a 2
b 3
1 2 4
c 2
B
1
4 1 4
d 1
e 2
f 3
h 4
5
3
2 B 0 A 1
3
1 A
1 B" | tee $result

# Diff and report result
if [ -z "$(diff -qw $baseline $result)" ]; then
    echo "PASS"
else
    echo "FAIL"
fi
