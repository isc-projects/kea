#!/bin/sh

cd "$1" || exit 1
shift
exec "$@"
