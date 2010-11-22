# Copyright (C) 2010  Internet Systems Consortium.
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

# $Id$

import unittest
import os
from pydnspp import *
from testutil import *

class EDNSTest(unittest.TestCase):

    def setUp(self):
        self.rrtype = RRType("OPT")
        self.rrclass = RRClass(4096)
        self.rrttl_do_on = RRTTL(0x00008000)
        self.rrttl_do_off = RRTTL(0)
        self.rrttl_badver = RRTTL(0x00018000)
        self.opt_rdata = Rdata(self.rrtype, self.rrclass, bytes())
        self.edns_base = EDNS(Name.ROOT_NAME, self.rrclass, self.rrtype,
                              self.rrttl_do_off, self.opt_rdata)

    def test_badver_construct(self):
        self.assertRaises(InvalidParameter, EDNS, 1)
        self.assertRaises(TypeError, EDNS, 1, 2) # signature mismatch
        self.assertRaises(TypeError, EDNS, 256) # invalid arguments

    def test_dnssec_dobit(self):
        edns = EDNS(Name.ROOT_NAME, self.rrclass, self.rrtype,
                    self.rrttl_do_on, self.opt_rdata)
        self.assertTrue(edns.get_dnssec_awareness())

        edns = EDNS(Name.ROOT_NAME, self.rrclass, self.rrtype,
                    self.rrttl_do_off, self.opt_rdata)
        self.assertFalse(edns.get_dnssec_awareness())

        edns = EDNS()
        self.assertFalse(edns.get_dnssec_awareness())
        edns.set_dnssec_awareness(True)
        self.assertTrue(edns.get_dnssec_awareness())
        edns.set_dnssec_awareness(False);
        self.assertFalse(edns.get_dnssec_awareness())

        self.assertRaises(TypeError, edns.set_dnssec_awareness, "wrong")
        self.assertRaises(TypeError, edns.set_dnssec_awareness, 1)

    def test_udpsize(self):
        edns = EDNS(Name.ROOT_NAME, self.rrclass, self.rrtype,
                    self.rrttl_do_on, self.opt_rdata)
        self.assertEqual(4096, edns.get_udp_size())

        edns = EDNS()
        edns.set_udp_size(511)
        self.assertEqual(511, edns.get_udp_size())
        edns.set_udp_size(0)
        self.assertEqual(0, edns.get_udp_size())
        edns.set_udp_size(65535)
        self.assertEqual(65535, edns.get_udp_size())

        self.assertRaises(TypeError, edns.set_udp_size, "wrong")

        # Range check.  We need to do this at the binding level, so we need
        # explicit tests for it.
        self.assertRaises(OverflowError, edns.set_udp_size, 65536)
        self.assertRaises(OverflowError, edns.set_udp_size, -1)

    def test_get_version(self):
        self.assertEqual(EDNS.SUPPORTED_VERSION, EDNS().get_version())

    def test_bad_wiredata(self):
        self.assertRaises(InvalidParameter, EDNS, Name.ROOT_NAME,
                          self.rrclass, RRType("A"),
                          self.rrttl_do_on, self.opt_rdata)
        self.assertRaises(DNSMessageFORMERR, EDNS, Name("example.com"),
                          self.rrclass, self.rrtype, self.rrttl_do_on,
                          self.opt_rdata)
        self.assertRaises(DNSMessageBADVERS, EDNS, Name.ROOT_NAME,
                          self.rrclass, self.rrtype, self.rrttl_badver,
                          self.opt_rdata)

    def test_to_text(self):
        edns = EDNS()
        edns.set_udp_size(4096)
        expected_str = "; EDNS: version: 0, flags:; udp: 4096\n"
        self.assertEqual(expected_str, edns.to_text())
        self.assertEqual(expected_str, str(edns))

        edns.set_dnssec_awareness(True)
        self.assertEqual("; EDNS: version: 0, flags: do; udp: 4096\n",
                         edns.to_text())

        self.assertEqual("; EDNS: version: 0, flags: do; udp: 4096\n",
                         EDNS(Name.ROOT_NAME, self.rrclass, self.rrtype,
                              RRTTL(0x01008000), self.opt_rdata).to_text())

        self.assertEqual("; EDNS: version: 0, flags: do; udp: 4096\n",
                         EDNS(Name.ROOT_NAME, self.rrclass, self.rrtype,
                              RRTTL(0x00008001), self.opt_rdata).to_text())

    def test_towire_renderer(self):
        renderer = MessageRenderer()
        extrcode_noerror = Rcode.NOERROR().get_extended_code()
        extrcode_badvers = Rcode.BADVERS().get_extended_code()

        self.assertEqual(1, self.edns_base.to_wire(renderer, extrcode_noerror))
        wiredata = read_wire_data("edns_toWire1.wire")
        self.assertEqual(wiredata, renderer.get_data())

        renderer.clear()
        self.edns_base.set_dnssec_awareness(True)
        self.assertEqual(1, self.edns_base.to_wire(renderer, extrcode_noerror))
        wiredata = read_wire_data("edns_toWire2.wire")
        self.assertEqual(wiredata, renderer.get_data())

        renderer.clear()
        self.edns_base.set_dnssec_awareness(True)
        self.assertEqual(1, self.edns_base.to_wire(renderer, extrcode_badvers))
        wiredata = read_wire_data("edns_toWire3.wire")
        self.assertEqual(wiredata, renderer.get_data())

        renderer.clear()
        self.edns_base.set_dnssec_awareness(True)
        self.edns_base.set_udp_size(511)
        self.assertEqual(1, self.edns_base.to_wire(renderer, extrcode_noerror))
        wiredata = read_wire_data("edns_toWire4.wire")
        self.assertEqual(wiredata, renderer.get_data())

        renderer.clear()
        edns = EDNS(Name.ROOT_NAME, self.rrclass, self.rrtype,
                    RRTTL(0x00008001), self.opt_rdata)
        self.assertEqual(1, edns.to_wire(renderer, extrcode_noerror))
        wiredata = read_wire_data("edns_toWire2.wire")
        self.assertEqual(wiredata, renderer.get_data())

        renderer.clear()
        renderer.set_length_limit(10)
        self.edns_base.set_dnssec_awareness(True)
        self.assertEqual(0, self.edns_base.to_wire(renderer, extrcode_noerror))
        self.assertEqual(0, renderer.get_length())

    def test_towire_buffer(self):
        extrcode_noerror = Rcode.NOERROR().get_extended_code()

        obuffer = bytes()
        obuffer = self.edns_base.to_wire(obuffer, extrcode_noerror)
        wiredata = read_wire_data("edns_toWire1.wire")
        self.assertEqual(wiredata, obuffer)

    def test_create_from_rr(self):
        (edns, extrcode) = EDNS.create_from_rr(Name.ROOT_NAME, self.rrclass,
                                               self.rrtype, self.rrttl_do_on,
                                               self.opt_rdata)
        self.assertEqual(EDNS.SUPPORTED_VERSION, edns.get_version())
        self.assertTrue(edns.get_dnssec_awareness())
        self.assertEqual(4096, edns.get_udp_size())
        self.assertEqual(0, extrcode)

        (edns, extrcode) = EDNS.create_from_rr(Name.ROOT_NAME, self.rrclass,
                                               self.rrtype, RRTTL(0x01008000),
                                               self.opt_rdata)
        self.assertEqual(1, extrcode)

        self.assertRaises(DNSMessageBADVERS, EDNS.create_from_rr,
                          Name.ROOT_NAME, self.rrclass, self.rrtype,
                          self.rrttl_badver, self.opt_rdata)

if __name__ == '__main__':
    unittest.main()
