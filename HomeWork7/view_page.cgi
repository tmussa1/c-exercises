#!/bin/sh
#
# view_page.cgi
# cgi program to display current state of page
# simply takes the page name from form and passes it to mwp.cgi
# as QUERY_STRING and as $1
#

	eval `./qryparse`
	
	QUERY_STRING=$pagename
	export QUERY_STRING

        if [ -z $pagename ] || [ ! -f data/$pagename.tab ]
        then
           echo "Content-type: text/html"
           echo ""
           echo Page with $pagename doesnot exist. Press back button to re-enter page name
        else
           ./mwp.cgi $pagename
        fi
