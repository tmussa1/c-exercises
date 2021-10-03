#!/bin/sh
#
# cgi program to generate html tables from local unix commands
#
    echo "Content-Type: text/html"
    echo ""

    echo "<html><body style='background-color: white;'>"
    echo "<p>Here are routes to other computers: </p>"
    /sbin/route | ./tt2ht1
    echo "<p>Here are the current files:</p>"
    ls -l | ./tt2ht1 
    echo "<p>Here is memory usage:</p>"
    ./tt2ht1 < /proc/meminfo
    echo "<p>Here is train 1205:</p>"
    (cd /home/users/dce-lib113/lectures/lect04/5_Code/web; ./trainsched 1205)| ./tt2ht1
    echo "</body></html>"
