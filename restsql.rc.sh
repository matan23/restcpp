#!/bin/sh

name=MyRestSql
exec=./MyRestSql

start() {
    $exec
}

stop() {
    pkill $name
}

case "$1" in
    start|stop)
	$1
	;;
    restart|reload|force-reload)
	stop
	start
	;;
    *)
	echo 'Usage : $0 {start|stop|restart|reload|force-reload}'
	;;
esac

exit 0