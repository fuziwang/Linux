#!/bin/bash

comm="ps -e -o user,pid,ppid,tty,comm,args"

if [ $# -gt 0 ] ; then
    $comm | grep "$1" | grep -v "$0" | grep -v "grep"
else
    $comm | grep -v "$0"
fi

exit 0

if [ $#>0 ] ; then
	ps -e | grep "$1"
else
	ps -e -o user,pid,ppid,tty,comm,args
fi
