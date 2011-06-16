#!/bin/sh

"$1" 2>&1 | cut -d\  -f3- | diff - "$2" 1>&2
