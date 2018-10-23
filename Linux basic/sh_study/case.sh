#!/bin/bash

case "$1" in
    time)
        date
        ;;
    cpu)
        cat /proc/cpuinfo
        ;;
    sysinfo)
        uname -a
        ;;
    *)
        echo 'enter a args: time|cpu|sysinfo'
        ;;
esac

