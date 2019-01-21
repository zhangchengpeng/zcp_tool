#!/bin/bash

source init.sh

echo "start..."

procs=`ps -ef | grep main | grep -v grep | grep -v vi | grep -v tail | grep -v kill -c`
if [ $procs -ge 1 ];then
	echo "main already runing!"
	exit 0
else
	./main ../conf/server.xml 1>../log/server.log 2>&1
	procs=`ps -ef | grep main | grep -v grep | grep -v vi | grep -v tail | grep -v kill -c`
	if [ $procs -lt 1 ];then
		echo "start main failed!"
		exit 0
	else
		echo "start main success"
	fi
fi
