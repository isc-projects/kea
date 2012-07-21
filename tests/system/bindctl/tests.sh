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
cnt_name1="\<queries\.tcp\>"
cnt_name2="\<queries\.udp\>"
cnt_name3="\<opcode\.query\>"
cnt_value1=0
cnt_value2=0
cnt_value3=0

echo "I:Checking b10-auth is disabled by default ($n)"
$DIG +norec @10.53.0.1 -p 53210 ns.example.com. A > /dev/null && status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:Starting b10-auth and checking that it works ($n)"
echo 'config add Boss/components b10-auth
config set Boss/components/b10-auth { "special": "auth", "kind": "needed" }
config commit
quit
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR 2>&1 > /dev/null || status=1
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
# the server should have received 1 UDP and 0 TCP queries (the server
# startup script no longer sends any TCP queries)
cnt_value1=`expr $cnt_value1 + 0`
cnt_value2=`expr $cnt_value2 + 1`
cnt_value3=`expr $cnt_value1 + $cnt_value2`
# Further changes of Boss(#2137) and Auth(#2138) depends on this
# change(#2136). So statistics tests in this system test make no
# sense. Following statistics tests are disabled until codes of both
# #2137 and #2138 are merged.
#grep $cnt_name1".*\<"$cnt_value1"\>" bindctl.out.$n > /dev/null || status=1
#grep $cnt_name2".*\<"$cnt_value2"\>" bindctl.out.$n > /dev/null || status=1
#grep $cnt_name3".*\<"$cnt_value3"\>" bindctl.out.$n > /dev/null || status=1
#if [ $status != 0 ]; then echo "I:failed"; fi
echo "I:skipped"
n=`expr $n + 1`

echo "I:Stopping b10-auth and checking that ($n)"
echo 'config remove Boss/components b10-auth
config commit
quit
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR 2>&1 > /dev/null || status=1
# dig should exit with a failure code.
$DIG +tcp +norec @10.53.0.1 -p 53210 ns.example.com. A > /dev/null && status=1
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
# perform a simple check on the output (digcomp would be too much for this)
grep 192.0.2.1 dig.out.$n > /dev/null || status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:Rechecking BIND 10 statistics after a pause ($n)"
sleep 2
echo 'Stats show
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR > bindctl.out.$n || status=1
# The statistics counters can not be reset even after auth
# restarts. Because stats preserves the query counts which the dying
# auth sent. Then it cumulates them and new counts which the living
# auth sends. This note assumes that the issue would have been
# resolved : "#1941 stats lossage (multiple auth servers)".
cnt_value1=`expr $cnt_value1 + 0`
cnt_value2=`expr $cnt_value2 + 1`
cnt_value3=`expr $cnt_value1 + $cnt_value2`
# Further changes of Boss(#2137) and Auth(#2138) depends on this
# change(#2136). So statistics tests in this system test make no
# sense. Following statistics tests are disabled until codes of both
# #2137 and #2138 are merged.
#grep $cnt_name1".*\<"$cnt_value1"\>" bindctl.out.$n > /dev/null || status=1
#grep $cnt_name2".*\<"$cnt_value2"\>" bindctl.out.$n > /dev/null || status=1
#grep $cnt_name3".*\<"$cnt_value3"\>" bindctl.out.$n > /dev/null || status=1
#if [ $status != 0 ]; then echo "I:failed"; fi
echo "I:skipped"
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
cnt_value1=`expr $cnt_value1 + 0`
cnt_value2=`expr $cnt_value2 + 1`
cnt_value3=`expr $cnt_value1 + $cnt_value2`
# Further changes of Boss(#2137) and Auth(#2138) depends on this
# change(#2136). So statistics tests in this system test make no
# sense. Following statistics tests are disabled until codes of both
# #2137 and #2138 are merged.
#grep $cnt_name1".*\<"$cnt_value1"\>" bindctl.out.$n > /dev/null || status=1
#grep $cnt_name2".*\<"$cnt_value2"\>" bindctl.out.$n > /dev/null || status=1
#grep $cnt_name3".*\<"$cnt_value3"\>" bindctl.out.$n > /dev/null || status=1
#if [ $status != 0 ]; then echo "I:failed"; fi
echo "I:skipped"
n=`expr $n + 1`

echo "I:Starting more b10-auths and checking that ($n)"
for i in 2 3
do
    echo 'config add Boss/components b10-auth-'$i'
config set Boss/components/b10-auth-'$i' { "special": "auth", "kind": "needed" }
config commit
quit
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR 2>&1 > /dev/null || status=1
done
$DIG +norec @10.53.0.1 -p 53210 ns.example.com. A >dig.out.$n || status=1
grep 192.0.2.2 dig.out.$n > /dev/null || status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

echo "I:Rechecking BIND 10 statistics consistency after a pause ($n)"
sleep 2
cnt_value1=`expr $cnt_value1 + 0`
cnt_value2=`expr $cnt_value2 + 1`
cnt_value3=`expr $cnt_value1 + $cnt_value2`
# Rechecking some times
for i in 1 2 3 4
do
    echo 'Stats show
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR > bindctl.out.$n || status=1
    # The statistics counters should keep being consistent even while
    # multiple b10-auths are running.

    # Further changes of Boss(#2137) and Auth(#2138) depends on this
    # change(#2136). So statistics tests in this system test make no
    # sense. Following statistics tests are disabled until codes of both
    # #2137 and #2138 are merged.
    #grep $cnt_name1".*\<"$cnt_value1"\>" bindctl.out.$n > /dev/null || status=1
    #grep $cnt_name2".*\<"$cnt_value2"\>" bindctl.out.$n > /dev/null || status=1
    #grep $cnt_name3".*\<"$cnt_value3"\>" bindctl.out.$n > /dev/null || status=1
    #if [ $status != 0 ]; then echo "I:failed "; break ; fi
    echo "I:skipped"
done
n=`expr $n + 1`

echo "I:Stopping extra b10-auths and checking that ($n)"
for i in 3 2
do
    echo 'config remove Boss/components b10-auth-'$i'
config commit
quit
' | $RUN_BINDCTL \
	--csv-file-dir=$BINDCTL_CSV_DIR 2>&1 > /dev/null || status=1
done
$DIG +norec @10.53.0.1 -p 53210 ns.example.com. A >dig.out.$n || status=1
grep 192.0.2.2 dig.out.$n > /dev/null || status=1
if [ $status != 0 ]; then echo "I:failed"; fi
n=`expr $n + 1`

# The statistics counters can not be rechecked here because the auth
# instance seems to hang up after one of the multiple auth instances
# was removed via bindctl. This reason seems to be the same reason as
# #1703.

echo "I:exit status: $status"
exit $status
