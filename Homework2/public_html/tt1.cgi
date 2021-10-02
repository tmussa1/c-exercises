#!/bin/sh
# 
# cgi program to generate text tables from local Unix commands
#
   echo "Content-Type: text/plain"
   echo ""

   echo "Here are the current internet connnections:"
   netstat -A inet
   echo "Here are the current files:"
   ls -l
   echo "Here are the system CPUs:"
   cat /proc/cpuinfo

