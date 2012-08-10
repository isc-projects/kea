#!/bin/sh
#
# Copyright (C) 2004, 2007  Internet Systems Consortium, Inc. ("ISC")
# Copyright (C) 2000, 2001, 2003  Internet Software Consortium.
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
# Do glue tests.
#

status=0
n=0

# This query should result in a delegation with two NS; one in the delegated
# zone and one in a so called out-of-bailiwick zone for which the auth server
# has authority, too.  For the former, the server should return glue in the
# parent zone.  For the latter, BIND 9 and BIND 10 behave differently; BIND 9
# uses "glue" in the parent zone (since this is the root zone everything can
# be considered a valid glue).  BIND 10 (using sqlite3 data source) searches
# the other zone and uses the authoritative data in that zone (which is
# intentionally different from the glue in the root zone).
echo "I:testing that a TLD referral gets a full glue set from the root zone ($n)"
$DIG +norec @10.53.0.1 -p 53210 foo.bar.example. A >dig.out.$n || status=1
$PERL $DIGCOMP example.good dig.out.$n || status=1
n=`expr $n + 1`

# Disabling this test, as it checks for looking up glue in a different zone
# finder than the answer is from. This is not supported now.
#echo "I:testing that we find glue A RRs we are authoritative for ($n)"
#$DIG +norec @10.53.0.1 -p 53210 foo.bar.example.org. a >dig.out.$n || status=1
#$PERL $DIGCOMP auth.good dig.out.$n || status=1
#n=`expr $n + 1`

# We cannot do this test for BIND 10 because b10-auth doesn't act as a
# recursive (caching) server (by design)
# echo "I:testing that we find glue A/AAAA RRs in the cache ($n)"
# $DIG +norec @10.53.0.1 -p 53210 foo.bar.yy. a >dig.out.$n || status=1
# $PERL $DIGCOMP yy.good dig.out.$n || status=1
# n=`expr $n + 1`

echo "I:testing that we don't find out-of-zone glue ($n)"
$DIG +norec @10.53.0.1 -p 53210 example.net. a > dig.out.$n || status=1
$PERL $DIGCOMP noglue.good dig.out.$n || status=1
n=`expr $n + 1`

# This test currently fails (additional section will be empty, which is
# incorrect).  See Trac ticket #646.
#echo "I:testing that we are finding partial out-of-zone glue ($n)"
#$DIG +norec @10.53.0.1 -p 53210 foo.bar.test. a >dig.out.$n || status=1
#$PERL $DIGCOMP test.good dig.out.$n || status=1
#n=`expr $n + 1`

echo "I:exit status: $status"
exit $status
