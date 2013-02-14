#!/bin/sh

# Copyright (C) 2011  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

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
