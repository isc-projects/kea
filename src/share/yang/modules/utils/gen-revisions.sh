#!/bin/sh
# Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Build module / revision table:

test=keatest-module*.yang
last=kea-dhcp-ddns*.yang

for m in keatest-module*.yang \
         ietf-dhcpv6-types*.yang \
         ietf-dhcpv6-options*.yang \
         ietf-dhcpv6-server*.yang \
         kea-types*.yang \
         kea-logging*.yang \
         kea-dhcp-types*.yang \
         kea-dhcp4-server*.yang \
         kea-dhcp6-server*.yang \
         kea-ctrl-agent*.yang \
         kea-dhcp-ddns*.yang
do
    if test $m = $test
    then
        echo '#ifdef KEATEST_MODULE'
    fi
    b=`echo $m | sed 's/\(.*\)@.*/\1/'`
    r=`echo $m | sed 's/.*@\(.*\)\.yang/\1/'`
    c=','
    if test $m = $last
    then
        c=''
    fi
    echo '    { "'$b'", "'$r'" }'$c
    if test $m = $test
    then
        echo '#endif // KEATEST_MODULE'
    fi
done


