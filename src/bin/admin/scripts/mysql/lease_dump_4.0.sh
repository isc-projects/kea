#!/bin/sh
# Copyright (C) 2015  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
# Specifies the MySQL sql for schema-version 4.0 required to produce 
# lease output that includes a header row containing column names,
# followed by the lease data. The text is used in a single call 
# to the mysql command line tool.

# SQL for DHCPv4 leases
lease4_dump_sql="\
SELECT 'address', 'hwaddr', 'client_id', 'valid_lifetime', 'expire',\
'subnet_id', 'fqdn_fwd', 'fqdn_rev', 'hostname', 'state';\
SELECT INET_NTOA(address), IFNULL(HEX(hwaddr), ''), IFNULL(HEX(client_id), ''),\
valid_lifetime, expire, subnet_id, fqdn_fwd, fqdn_rev, hostname, state from lease4"

# SQL for DHCPv6 leases
lease6_dump_sql="\
SELECT 'address', 'duid', 'valid_lifetime', 'expire',\
'subnet_id', 'pref_lifetime', 'lease_type', 'iaid', 'prefix_len', 'fqdn_fwd',\
'fqdn_rev', 'hostname', 'hwaddr', 'hwtype', 'hwaddr_source', 'state';\
SELECT a.address, IFNULL(HEX(a.duid), ''), a.valid_lifetime,\
a.expire, a.subnet_id, a.pref_lifetime, IFNULL(b.name, ''), a.iaid, a.prefix_len,\
a.fqdn_fwd, a.fqdn_rev, hostname, IFNULL(HEX(hwaddr), ''), IFNULL(hwtype, ''),\
IFNULL(hwaddr_source, ''), state \
FROM lease6 a left outer join lease6_types b on (a.lease_type = b.lease_type)"
