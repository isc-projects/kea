#!/bin/sh
# Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Check hashes
#
# This developer script verifies recorded hashes still match the
# result of SHA-256 checksums of the YIN format.
# Requires yanglint to translate YANG to YIN formats and openssl
# for a system independent SHA-256.

error=0
for m in *.yang
do
    hash1=`yanglint -f yin $m | openssl dgst -sha256 | sed 's/(stdin)= //'`
    h=hashes/`basename $m .yang`.hash
    if test -f $h
    then
        hash2=`cat $h`
        if test $hash1 != $hash2
        then
            error=1
            echo hash mismatch on $m expected $hash1 in $h
        fi
    else
        error=1
        echo missing hash file $h for $m
    fi
done
exit $error
