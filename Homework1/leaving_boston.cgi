#!/bin/sh

eval $(./qryparse)

echo "Content-Type: text/plain"
echo ""

echo "First train leaving Boston on line $line on day $when"

./from_boston "$line" "$when" ]
