#!/bin/sh
#
# cgi wrapper for xcal2
# Increments the year to next year if the given month is already behind 

    echo "Content-type: text/plain/n/n"
    echo ""

    MONTH=""

    if [ -z $QUERY_STRING ]
    then
       MONTH=$(date '+%m') # Read in current month if not given
    else 
       MONTH=$QUERY_STRING
    fi
 
    MONTH_NUM=$(./name2num $MONTH)
    CURRENT_MON=$(date '+%m')
    CURRENT_YEAR=$(date '+%y')
    
    # Increrment current year if the given month is behind
    if [ $CURRENT_MON -gt $MONTH_NUM ] 
    then
       CURRENT_YEAR=$(expr $CURRENT_YEAR + 1)
    fi

    ./xcal2 $MONTH_NUM $CURRENT_YEAR
