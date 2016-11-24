#ps w | grep -m1 tcp_slave | awk '{print $1}'
kill `pidof python`
/usr/bin/reset-mcu
