#!/bin/bash

PID=`pidof CommonData`
[[ -n "$PID" ]] && kill -s SIGTERM $PID || exit 0