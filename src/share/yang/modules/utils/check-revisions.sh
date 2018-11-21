#!/bin/sh
# Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Check revisions:

for m in *.yang
do
    rev1=`yanglint -f yin $m | grep '<revision date=' | head -1 | sed \
 's/.*<revision date="\([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]\)".*/\1/'`
    rev2=`echo $m | sed \
 's/.*@\([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]\)\..*/\1/'`

    if test $rev1 != $rev2
    then
        echo revision mismatch on $m got $rev1
    fi
done
