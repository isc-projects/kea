#!/bin/sh
#
# Copyright (C) 2004, 2005, 2007, 2011  Internet Systems Consortium, Inc. ("ISC")
# Copyright (C) 2000, 2001  Internet Software Consortium.
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

# On entry, the IXFR server is at version N-6.  The common tests assume that
# it is an N-4, so update it.
echo "I:updating IXFR-server $SERVER_NAME to suitable start version"
update_server_zone $SERVER_NAME $SERVER_IP $IXFR_TOP/largezone_n-4.db
status=$?

# The pre-requisites for this test are the same as for the common tests, so
# we can execute that directly.

. ../common_tests.sh
status=`expr $status + $?`

# TODO: Check the BIND 10 log, looking for the IXFR messages that indicate that
# it has initiated an IXFR and that it received the update via TCP.

echo "I:exit status: $status"
exit $status
