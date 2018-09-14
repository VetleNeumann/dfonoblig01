#!/bin/bash
#/usr/local/bin/serverd.sh
#

function d_start()
{
    echo "Server: starting service"
    server 80
    sleep 5
    echo "PID id $(cat /tmp/server.pid)"
}

function d_stop()
{
    echo "Server: stopping service Service (PID = $(cat /tmp/server.pid))"
    kill $(cat /tmp/server.pid)
    rm /tmp/server.pid
}

function d_status()
{
    ps -ef | grep server | grep -v grep
    echo "PID indicate indication file $(cat /tmp/server.pid 2> /dev/null)"
}

case "$1" in
    start)
        d_start
        ;;
    stop)
        d_stop
        ;;
    reload)
        d_stop
        sleep 1
        d_start
        ;;
    status)
        d_status
        ;;
    *)
        echo "usage: $0 {start|stop|reload|status}"
        exit 1
        ;;
esac

exit 0