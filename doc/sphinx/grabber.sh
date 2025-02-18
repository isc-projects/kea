#!/bin/sh

cd "$1" || exit 1

find "$2" -type f -name "[a-z]*.$3" | sort -V

