#!/usr/bin/env python3.1

# Copyright (C) 2011  Internet Systems Consortium.
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

'''This script was used to create zone differences for IXFR tests.

The result was stored in the test SQLite3 database file, so this script
itself isn't necessary for testing.  It's provided here for reference
purposes.

'''

import isc.datasrc
import isc.log
from isc.dns import *
from isc.testutils.rrset_utils import *

isc.log.init("dummy")           # XXX

ZONE_NAME = Name('example.com')
NS_NAME_STR = 'a.dns.example.com'
NS_NAME = Name(NS_NAME_STR)

client = isc.datasrc.DataSourceClient('sqlite3',
                                      '{ "database_file": "test.sqlite3" }')

# Install the initial data
updater = client.get_updater(ZONE_NAME, True)
updater.add_rrset(create_soa(2011111802))
updater.add_rrset(create_ns(NS_NAME_STR))
updater.add_rrset(create_a(NS_NAME, '192.0.2.53'))
updater.add_rrset(create_aaaa(NS_NAME, '2001:db8::1'))
updater.commit()

# Incremental update to generate diffs
updater = client.get_updater(ZONE_NAME, False, True)
updater.delete_rrset(create_soa(2011111802))
updater.add_rrset(create_soa(2011111900))
updater.add_rrset(create_a(NS_NAME, '192.0.2.2', 7200))
updater.delete_rrset(create_soa(2011111900))
updater.delete_rrset(create_a(NS_NAME, '192.0.2.53'))
updater.delete_rrset(create_aaaa(NS_NAME, '2001:db8::1'))
updater.add_rrset(create_soa(2011112001))
updater.add_rrset(create_a(NS_NAME, '192.0.2.1'))
updater.commit()
