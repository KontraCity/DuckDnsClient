#!/bin/bash

pid=$(pidof DuckDnsClient)
if [ -z $pid ]
then
    echo "Couldn't locate DuckDnsClient executable, check if it is running."
    exit
fi

sudo kill -s SIGUSR1 $pid
echo "Sent DDNS force update signal to process $pid."
