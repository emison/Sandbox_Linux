#!/bin/bash
baseline=$(mktemp)
result=$(mktemp)

# Create baseline
echo -e "e ht m o zk
e ht m zk o
e ht o m zk
e ht o zk m
e ht zk m o
e ht zk o m
e m ht o zk
e m ht zk o
e m o ht zk
e m o zk ht
e m zk ht o
e m zk o ht
e o ht m zk
e o ht zk m
e o m ht zk
e o m zk ht
e o zk ht m
e o zk m ht
e zk ht m o
e zk ht o m
e zk m ht o
e zk m o ht
e zk o ht m
e zk o m ht
ht e m o zk
ht e m zk o
ht e o m zk
ht e o zk m
ht e zk m o
ht e zk o m
ht m e o zk
ht m e zk o
ht m o e zk
ht m o zk e
ht m zk e o
ht m zk o e
ht o e m zk
ht o e zk m
ht o m e zk
ht o m zk e
ht o zk e m
ht o zk m e
ht zk e m o
ht zk e o m
ht zk m e o
ht zk m o e
ht zk o e m
ht zk o m e
m e ht o zk
m e ht zk o
m e o ht zk
m e o zk ht
m e zk ht o
m e zk o ht
m ht e o zk
m ht e zk o
m ht o e zk
m ht o zk e
m ht zk e o
m ht zk o e
m o e ht zk
m o e zk ht
m o ht e zk
m o ht zk e
m o zk e ht
m o zk ht e
m zk e ht o
m zk e o ht
m zk ht e o
m zk ht o e
m zk o e ht
m zk o ht e
o e ht m zk
o e ht zk m
o e m ht zk
o e m zk ht
o e zk ht m
o e zk m ht
o ht e m zk
o ht e zk m
o ht m e zk
o ht m zk e
o ht zk e m
o ht zk m e
o m e ht zk
o m e zk ht
o m ht e zk
o m ht zk e
o m zk e ht
o m zk ht e
o zk e ht m
o zk e m ht
o zk ht e m
o zk ht m e
o zk m e ht
o zk m ht e
zk e ht m o
zk e ht o m
zk e m ht o
zk e m o ht
zk e o ht m
zk e o m ht
zk ht e m o
zk ht e o m
zk ht m e o
zk ht m o e
zk ht o e m
zk ht o m e
zk m e ht o
zk m e o ht
zk m ht e o
zk m ht o e
zk m o e ht
zk m o ht e
zk o e ht m
zk o e m ht
zk o ht e m
zk o ht m e
zk o m e ht
zk o m ht e" > $baseline

# Execute code
perm <<< "5 e ht m o zk" | tee $result

# Diff and report result
if [ -z "$(diff -qw $baseline $result)" ]; then
    echo "PASS"
else
    echo "FAIL"
fi
