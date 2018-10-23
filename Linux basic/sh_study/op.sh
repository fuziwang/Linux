#!/bin/bash

#-gt:> ; -lt:< ; -eq:= ; -ne:!= -le:<= ; -ge:>=

if [ $# -gt 0 ] ; then
    
fi

if [ 5 -gt 3 ] ; then
    echo '5>3'
fi

a=abc
b=bcd

if [ $a = $b ] ; then
    echo "$a=$b"
else
    echo "$a!=$b"
fi

