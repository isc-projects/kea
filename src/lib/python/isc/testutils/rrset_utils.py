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

'''Utility functions handling DNS RRsets commonly used for tests'''

from isc.dns import *

def rrsets_equal(a, b):
    '''Compare two RRsets, return True if equal, otherwise False

    We provide this function as part of test utils as we have no direct rrset
    comparison atm.  There's no accessor for sigs either (so this only checks
    name, class, type, ttl, and rdata).
    Also, since we often use fake data in RRSIGs, RRSIG RDATA are not checked.

    '''
    return a.get_name() == b.get_name() and \
           a.get_class() == b.get_class() and \
           a.get_type() == b.get_type() and \
           a.get_ttl() == b.get_ttl() and \
           (a.get_type() == RRType.RRSIG() or
            sorted(a.get_rdata()) == sorted(b.get_rdata()))

# The following are short cut utilities to create an RRset of a specific
# RR type with one RDATA.  Many of the RR parameters are common in most
# tests, so we define default values for them for convenience.

def create_a(name, address, ttl=3600):
    rrset = RRset(name, RRClass.IN(), RRType.A(), RRTTL(ttl))
    rrset.add_rdata(Rdata(RRType.A(), RRClass.IN(), address))
    return rrset

def create_aaaa(name, address, ttl=3600):
    rrset = RRset(name, RRClass.IN(), RRType.AAAA(), RRTTL(ttl))
    rrset.add_rdata(Rdata(RRType.AAAA(), RRClass.IN(), address))
    return rrset

def create_ns(nsname, name=Name('example.com'), ttl=3600):
    '''For convenience we use a default name often used as a zone name'''
    rrset = RRset(name, RRClass.IN(), RRType.NS(), RRTTL(ttl))
    rrset.add_rdata(Rdata(RRType.NS(), RRClass.IN(), nsname))
    return rrset

def create_generic(name, rdlen, type=RRType('TYPE65300'), ttl=3600):
    '''Create an RR of a general type with an arbitrary length of RDATA

    If the RR type isn't specified, type of 65300 will be used, which is
    arbitrarily chosen from the IANA "Reserved for Private Usage" range.
    The RDATA will be filled with specified length of all-0 data.

    '''
    rrset = RRset(name, RRClass.IN(), type, RRTTL(ttl))
    rrset.add_rdata(Rdata(type, RRClass.IN(), '\\# ' +
                          str(rdlen) + ' ' + '00' * rdlen))
    return rrset

def create_soa(serial, name=Name('example.com'), ttl=3600):
    '''For convenience we use a default name often used as a zone name'''

    rrset = RRset(name, RRClass.IN(), RRType.SOA(), RRTTL(ttl))
    rdata_str = 'master.example.com. admin.example.com. ' + \
        str(serial) + ' 3600 1800 2419200 7200'
    rrset.add_rdata(Rdata(RRType.SOA(), RRClass.IN(), rdata_str))
    return rrset
