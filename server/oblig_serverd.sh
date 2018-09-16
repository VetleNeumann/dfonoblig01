#!/bin/bash
#/usr/local/bin/oblig_serverd.sh
#

function d_start()
{
    echo "Oblig Server: starting service"
    oblig_server 80
    sleep 5
    echo "PID id $(cat /tmp/oblig_server.pid)"
}

function d_stop()
{
    echo "Oblig Server: stopping service Service (PID = $(cat /tmp/server.pid))"
    kill $(cat /tmp/oblig_server.pid)
    rm /tmp/oblig_server.pid
}

function d_status()
{
    ps -ef | grep oblig_server | grep -v grep
    echo "PID indicate indication file $(cat /tmp/oblig_server.pid 2> /dev/null)"
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