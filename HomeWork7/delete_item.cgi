#!/bin/sh
# 
# CGI program that deletes an item from a given page
# 
   
   echo "Content-type: text/html"
   echo ""

   eval `./qryparse` #  Evaluate query string

   FILE=$pagename.tab
   TO_DELETE=$title 
   
   cd data

   if [ ! -f $FILE ] || [ -z $TO_DELETE ] # Error checking for file and record
   then
      echo File $FILE or record $TO_DELETE does not exist
   fi

   if grep -q $TO_DELETE $FILE # Error checking for record exists in file
   then
      echo Deleted records containing $TO_DELETE from file $FILE
      sed -i "/$TO_DELETE/d" $FILE # Delete in place
   else
      echo $TO_DELETE not found in $FILE # Record not found in file
   fi
