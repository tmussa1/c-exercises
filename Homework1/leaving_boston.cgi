#!/bin/sh

eval $(./qryparse)
echo "Content-Type: text/html"

echo "Trains Leaving Boston on line $line on day $when"
./from_boston "$line" "$when"
