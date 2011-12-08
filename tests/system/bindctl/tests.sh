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

SYSTEMTESTTOP=..
. $SYSTEMTESTTOP/conf.sh

#
# Do bindctl tests.
#

status=0
n=0

# TODO: consider consistency with statistics definition in auth.spec
auth_queries_tcp="\<queries\.tcp\>"
auth_queries_udp="\<queries\.udp\>"

echo "I:Checking b10-auth is working by default ($n)"
$DIG +norec @10.53.0.1 -p 53210 ns.example.com. A >dig.out.$n || status=1
# perform a simple check on the output (digcomp would be too much for this)
grep 192.0.2.1 dig.out.$n > /dev/null || status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:Checking BIND 10 statistics after a pause ($n)"
# wait for 2sec to make sure b10-stats gets the latest statistics.
# note that we set statistics-interval to 1.
sleep 2
echo 'Stats show
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR > bindctl.out.$n || status=1
# the server should have received 1 UDP and 1 TCP queries (TCP query was
# sent from the server startup script)
grep $auth_queries_tcp".*\<1\>" bindctl.out.$n > /dev/null || status=1
grep $auth_queries_udp".*\<1\>" bindctl.out.$n > /dev/null || status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:Stopping b10-auth and checking that ($n)"
echo 'config remove Boss/components b10-auth
config commit
quit
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR 2>&1 > /dev/null || status=1
# dig should exit with a failure code.
$DIG +tcp +norec @10.53.0.1 -p 53210 ns.example.com. A && status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:Restarting b10-auth and checking that ($n)"
echo 'config add Boss/components b10-auth
config set Boss/components/b10-auth { "special": "auth", "kind": "needed" }
config commit
quit
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR 2>&1 > /dev/null || status=1
$DIG +norec @10.53.0.1 -p 53210 ns.example.com. A >dig.out.$n || status=1
grep 192.0.2.1 dig.out.$n > /dev/null || status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:Rechecking BIND 10 statistics after a pause ($n)"
sleep 2
echo 'Stats show
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR > bindctl.out.$n || status=1
# The statistics counters should have been reset while stop/start.
grep $auth_queries_tcp".*\<0\>" bindctl.out.$n > /dev/null || status=1
grep $auth_queries_udp".*\<1\>" bindctl.out.$n > /dev/null || status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:Changing the data source from sqlite3 to in-memory ($n)"
DATASRC_SPEC='[{"type": "memory", "zones": [{"origin": "com","file":'
DATASRC_SPEC="${DATASRC_SPEC} \"${TEST_TOP}/bindctl/nsx1/example-normalized.db\"}]}]"
echo "config set Auth/datasources ${DATASRC_SPEC}
config commit
quit
" | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR > bindctl.out.$n || status=1
$DIG +norec @10.53.0.1 -p 53210 ns.example.com. A >dig.out.$n || status=1
grep 192.0.2.2 dig.out.$n > /dev/null || status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:Rechecking BIND 10 statistics after changing the datasource ($n)"
sleep 2
echo 'Stats show
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR > bindctl.out.$n || status=1
# The statistics counters shouldn't be reset due to hot-swapping datasource.
grep $auth_queries_tcp".*\<0\>" bindctl.out.$n > /dev/null || status=1
grep $auth_queries_udp".*\<2\>" bindctl.out.$n > /dev/null || status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:exit status: $status"
exit $status
