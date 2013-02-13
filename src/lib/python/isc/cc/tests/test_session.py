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

import isc

import time
import pprint
import unittest

#
# This test requires the MsgQ daemon to be running.  We are doing nasty
# tricks here, and so insert sleeps to give things time to migrate from
# this process, to the MsgQ, and back to this process.
#

class TestCCWireEncoding(unittest.TestCase):
    def setUp(self):
        self.s1 = isc.cc.Session()
        self.s2 = isc.cc.Session()

    def tearDown(self):
        self.s1.close()
        self.s2.close()

    def test_lname(self):
        self.assertTrue(self.s1.lname)
        self.assertTrue(self.s2.lname)

    def test_subscribe(self):
        self.s1.group_subscribe("g1", "i1")
        self.s2.group_subscribe("g1", "i1")
        time.sleep(0.5)
        outmsg = { "data" : "foo" }
        self.s1.group_sendmsg(outmsg, "g1", "i1")
        time.sleep(0.5)
        msg, env = self.s2.group_recvmsg()
        self.assertEqual(env["from"], self.s1.lname)

    def test_unsubscribe(self):
        self.s1.group_subscribe("g1", "i1")
        self.s2.group_subscribe("g1", "i1")
        time.sleep(0.5)
        self.s2.group_unsubscribe("g1", "i1")
        outmsg = { "data" : "foo" }
        self.s1.group_sendmsg(outmsg, "g1", "i1")
        time.sleep(0.5)
        msg, env = self.s2.group_recvmsg()
        self.assertFalse(env)

    def test_directed_recipient(self):
        self.s1.group_subscribe("g1", "i1")
        time.sleep(0.5)
        outmsg = { "data" : "foo" }
        self.s1.group_sendmsg(outmsg, "g4", "i4", self.s2.lname)
        time.sleep(0.5)
        msg, env = self.s2.group_recvmsg()
        self.assertEqual(env["from"], self.s1.lname)
        self.assertEqual(env["to"], self.s2.lname)
        self.assertEqual(env["group"], "g4")
        self.assertEqual(env["instance"], "i4")

if __name__ == '__main__':
    unittest.main()
