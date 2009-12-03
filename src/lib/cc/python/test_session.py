import ISC

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
        self.s1 = ISC.CC.Session()
        self.s2 = ISC.CC.Session()

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
