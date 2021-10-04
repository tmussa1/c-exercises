#!/bin/sh
# 
# cgi program to test tt2ht2
#
    echo "Content-Type: text/html"
    echo ""

    ( cat part4b.top ; cat ~dce-lib113/hw/tt2ht/who.output ) | ./tt2ht2
    echo "</table></body></html>"
