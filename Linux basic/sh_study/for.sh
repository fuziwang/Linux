#!/bin/bash


DIR_LIST="a b c d e f"

for i in $DIR_LIST ; do
    if ! test -d ~/sh/study/$i ; then
        mkdir ~/sh/study/$i
    fi
done

