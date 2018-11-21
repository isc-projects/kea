#!/bin/sh
# Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Check hashes:

for m in *.yang
do
    hash1=`yanglint -f yin $m | openssl dgst -sha256 | sed 's/(stdin)= //'`
    h=hashes/`basename $m .yang`.hash
    if test -f $h
    then
        hash2=`cat $h`
        if test $hash1 != $hash2
        then
            echo hash mismatch on $m expected $hash1 in $h
        fi
    else
        echo missing hash file $h for $m
    fi
done
