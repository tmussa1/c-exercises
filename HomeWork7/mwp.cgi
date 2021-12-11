#!/bin/sh
#
# CGI Program that merges format files with data to preface HTML

    echo "Content-type: text/html"
    echo ""

    PAGE_NAME=$QUERY_STRING

    if [ ! -z $PAGE_NAME ] # Render only if page name is provided
    then
        echo "<h2>A Web Page for $PAGE_NAME</h2>"
        echo "<hr>"
        echo "</br>"
        echo "<h4>Customized Links for $PAGE_NAME</h4>"
        echo "<table>"
        ./fl -d"|" $PAGE_NAME.fmt data/$PAGE_NAME.tab # Reuse fl program to merge fmt with data
        echo "</table>"
    fi
