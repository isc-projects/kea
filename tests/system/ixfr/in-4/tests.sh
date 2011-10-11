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
# This script performs the fourth IXFR-IN test.  A BIND 9 nameserver (the
# "server") contains a version of the zone (version N) and has IXFRs enabled.
# A BIND 10 nameserver (the "client") is loaded with version N-2 of the zone
# and a small refresh time.  After this expires, the IXFR client should send
# an IXFR request to the IXFR server.

. ../ixfr_init.sh
status=$?

# Ensure the server has the latest copy of the zone.  The implicit assumption
# here is that starting the two systems and reloading the IXFR server takes
# less time than the SOA refresh time set in the "db.example.n2.refresh" zone
# file.
cp $IXFR_TOP/db.example.n0 ns1/db.example
do_rndc $SERVER_NAME $SERVER_IP reload

# Store the SOA serial number of the BIND 10 client for later use.
old_client_serial=`$DIG_SOA @$CLIENT_IP | $AWK '{print $3}'`
echo "I:SOA serial of IXFR client $CLIENT_NAME is $old_client_serial"

# Wait for the client to update itself. 30 seconds has been given as the
# refresh interface and 2 seconds as the retry interval.  The wait_for_update
# function will check for up to a minute looking for the new serial.
wait_for_update $CLIENT_NAME $CLIENT_IP $old_client_serial
status=`expr $status + $?`

# Has updated, get the latest serial of the client and server - they
# should be the same.
compare_soa $SERVER_NAME $SERVER_IP $CLIENT_NAME $CLIENT_IP
status=`expr $status + $?`

# TODO: Check the BIND 10 log, looking for the IXFR messages that indicate that
# the client has initiated the IXFR.

echo "I:exit status: $status"
exit $status
