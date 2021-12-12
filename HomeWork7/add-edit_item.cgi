#!/bin/sh
#
# add_item.cgi
# this script is called from ewp.html for the Add function
# it takes the specified items and creates a new record on the
# end of the named file in the data directory
#
        echo "Content-type: text/plain"
        echo ""
	
	eval `./qryparse`		# receive form data
	DATAFILE=$pagename.tab		# $pagename set by qryparse


	if test ! -d data		# if no data directory
	then
		mkdir data		# try to make it
		if test $? -ne 0	# and check for errors
		then
			echo "Cannot create data directory."
			exit
		fi
	fi

	cd data

        if [ ! -f $DATAFILE ] # Page doesnot exist
        then
            echo Page $DATAFILE doesnot exist. Press back button to re-enter data # Page has to exist
            exit 1
        else
	    EXISTING=$(grep -w $title $DATAFILE)
           
            if test ! -z "$EXISTING" # Update existing data if provided
            then
                test ! -z "$titlecolor" && sed -i "/title=$title|/s/tcolor=[^|]*|/tcolor=$titlecolor|/" $DATAFILE
                test ! -z "$descrip" && sed -i "/title=$title|/s/desc=[^|]*|/desc=$descrip|/" $DATAFILE
                test ! -z "$url" && sed -i "/title=$title|/s(url=[^|]*(url=$url(" $DATAFILE
            else

                if test -z "$title"  # can't be added without title
                then
                   echo Title doesnot exist. Press back button to re-enter data
                   exit 1
                fi

                if test -z "$titlecolor"
                then
                   titlecolor="white" # Default title color is white
                fi

		if test -z "$url"
                then
                   url="#" # Default url is "#" for same page
                fi

                printf "title=%s|tcolor=%s|desc=%s|url=%s\n" \
		  "$title" "$titlecolor" "$descrip" "$url" >> $DATAFILE
            fi
        fi

	if test $? -eq 0
	then
		echo "Addition of $title was successful."
		echo "Press the Back button now."
	else
		echo "Unable to update file $DATAFILE ."
		echo "Please report to page admin."
	fi

