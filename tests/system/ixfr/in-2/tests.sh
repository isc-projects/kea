#!/bin/sh
#
# Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

# \file
# This script performs the first IXFR-IN test.  A BIND 9 nameserver (the
# "server") contains a version of the zone (version N) and three previous
# versions, N-2, N-4 and N-6.  A BIND 10 nameserver (the "client") is loaded
# with version N-6 of the zone.  A NOTIFY is sent to it, and it is expected that
# it will send an IXFR to the server and update itself with the latest version
# of the zone.  (The changes are such that the update will have to take place
# over TCP.)

. ../ixfr_init.sh

# On entry, the IXFR server is at version N-6.  The common tests assume that
# it is an N-4, so update it.
echo "I:$SERVER_NAME updating IXFR-server to suitable start version"
update_server_zone $SERVER_NAME $SERVER_IP $IXFR_TOP/db.example.n4
if [ $? -ne 0 ];
then
    exit 1
fi

# The pre-requisites for this test are the same as for the common tests, so
# we can execute that directly.
. ../common_tests.sh
if [ $? -ne 0 ];
then
    exit 1
fi

# TEMPORARY: at the time of writing (October 2011) BIND 10 does not attempt
# a UDP transfer first.  Therefore just check for TCP transfer.

# Check that the client initiated and completed an IXFR.  Use a simple grep as
# the syntax and capabilities of egrep may vary between systems.
grep XFRIN_XFR_TRANSFER_STARTED nsx2/bind10.run | grep IXFR > /dev/null
if [ $? -ne 0 ];
then
    echo "R:$CLIENT_NAME FAIL no 'IXFR started' message in the BIND 10 log"
    exit 1
fi

grep XFRIN_IXFR_TRANSFER_SUCCESS nsx2/bind10.run | grep IXFR > /dev/null
if [ $? -ne 0 ];
then
    echo "R:$CLIENT_NAME FAIL no 'IXFR successful' message in the BIND 10 log"
    exit 1
fi

# Look in the named log file to see if a TCP IXFR was requested.  Again use a
# simple grep.
grep "transfer of" ns1/named.run | grep "sending TCP message" > /dev/null
if [ $? -ne 0 ];
then
    echo "R:$SERVER_NAME FAIL no 'sending TCP' message in the BIND 9 log"
    exit 1
fi

grep "IXFR ended" ns1/named.run > /dev/null
if [ $? -ne 0 ];
then
    echo "R:$SERVER_NAME FAIL no 'IXFR ended' message in the BIND 9 log"
    exit 1
fi

echo "I:exit status: 0"
exit 0
