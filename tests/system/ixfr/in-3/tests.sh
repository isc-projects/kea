
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
# This script performs the thrid IXFR-IN test.  A BIND 9 nameserver (the
# "server") contains a version of the zone (version N) and has IXFRs disabled.
# A BIND 10 nameserver (the "client") is loaded with version N-2 of the zone.
# A NOTIFY is sent to it, and it is expected that it will send an IXFR to the
# server; the server should not respond to the request, so ther client should
# then send an AXFR request and receive the latest copy of the zone.

. ../ixfr_init.sh
status=$?

# Store the SOA serial number of the BIND 10 client for later use.
old_client_serial=`$DIG_SOA @$CLIENT_IP | $AWK '{print $3}'`
echo "I:SOA serial of IXFR client $CLIENT_NAME is $old_client_serial"

# TODO: Need to alter configuration of BIND 10 server such that it accepts
# NOTIFYs from and sends IXFR requests to the BIND 9 master.

# If required, get the IXFR server to notify the IXFR client of the new zone.
# Do this by allowing notifies and then triggering a re-notification of the
# server.
echo "I:notifying IXFR-client $CLIENT_NAME of presence of new version of zone"
do_rndc $SERVER_NAME $SERVER_IP notify example
status=`expr $status + $?`

# Wait for the client to update itself.
wait_for_update $CLIENT_NAME $CLIENT_IP $old_client_serial
status=`expr $status + $?`

# Has updated, get the latest serial of the client and server - they
# should be the same.
compare_soa $SERVER_NAME $SERVER_IP $CLIENT_NAME $CLIENT_IP
status=`expr $status + $?`

# TODO: Check the BIND 10 log, looking for the IXFR messages that indicate that
# it has initiated an IXFR and then an AXFR.

echo "I:exit status: $status"
exit $status
