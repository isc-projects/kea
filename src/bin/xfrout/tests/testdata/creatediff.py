#!/usr/bin/env python3.1

import isc.datasrc
import isc.log
from isc.dns import *

isc.log.init("dummy")           # XXX

ZONE_NAME = Name('example.com')
NS_NAME = Name('a.dns.example.com')

def create_a(address, ttl=3600):
    rrset = RRset(NS_NAME, RRClass.IN(), RRType.A(), RRTTL(ttl))
    rrset.add_rdata(Rdata(RRType.A(), RRClass.IN(), address))
    return rrset

def create_aaaa(address):
    rrset = RRset(NS_NAME, RRClass.IN(), RRType.AAAA(), RRTTL(3600))
    rrset.add_rdata(Rdata(RRType.AAAA(), RRClass.IN(), address))
    return rrset

def create_ns(name):
    rrset = RRset(ZONE_NAME, RRClass.IN(), RRType.NS(), RRTTL(3600))
    rrset.add_rdata(Rdata(RRType.NS(), RRClass.IN(), name))
    return rrset

def create_soa(serial):
    rrset = RRset(ZONE_NAME, RRClass.IN(), RRType.SOA(), RRTTL(3600))
    rdata_str = 'master.example.com. admin.example.com. ' + \
        str(serial) + ' 3600 1800 2419200 7200'
    rrset.add_rdata(Rdata(RRType.SOA(), RRClass.IN(), rdata_str))
    return rrset

client = isc.datasrc.DataSourceClient('sqlite3',
                                      '{ "database_file": "test.sqlite3" }')

# Install the initial data
updater = client.get_updater(ZONE_NAME, True)
updater.add_rrset(create_soa(2011111802))
updater.add_rrset(create_ns('a.dns.example.com.'))
updater.add_rrset(create_a('192.0.2.53'))
updater.add_rrset(create_aaaa('2001:db8::1'))
updater.commit()

# Incremental update to generate diffs
updater = client.get_updater(ZONE_NAME, False, True)
updater.delete_rrset(create_soa(2011111802))
updater.add_rrset(create_soa(2011111900))
updater.add_rrset(create_a('192.0.2.2', 7200))
updater.delete_rrset(create_soa(2011111900))
updater.delete_rrset(create_a('192.0.2.53'))
updater.delete_rrset(create_aaaa('2001:db8::1'))
updater.add_rrset(create_soa(2011112001))
updater.add_rrset(create_a('192.0.2.1'))
updater.commit()
