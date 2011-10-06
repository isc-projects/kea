#!/bin/sh

MODULE_NAME=$1
if test -z $MODULE_NAME; then
	echo 'Usage: gen-forwarder.sh module_name'
	exit 1
fi

echo "from work.${MODULE_NAME}_messages import *" > ${MODULE_NAME}_messages.py
echo "Forwarder python script is generated.  Make sure to perform:"
echo "git add ${MODULE_NAME}_messages.py"
echo "and add the following to Makefile.am:"
echo "EXTRA_DIST += ${MODULE_NAME}_messages.py"
echo "CLEANFILES += ${MODULE_NAME}_messages.pyc"
