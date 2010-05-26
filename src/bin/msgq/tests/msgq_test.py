from msgq import SubscriptionManager, MsgQ

import unittest
import os
import socket

#
# Currently only the subscription part is implemented...  I'd have to mock
# out a socket, which, while not impossible, is not trivial.
#

class TestSubscriptionManager(unittest.TestCase):
    def setUp(self):
        self.sm = SubscriptionManager()

    def test_subscription_add_delete_manager(self):
        self.sm.subscribe("a", "*", 'sock1')
        self.assertEqual(self.sm.find_sub("a", "*"), [ 'sock1' ])

    def test_subscription_add_delete_other(self):
        self.sm.subscribe("a", "*", 'sock1')
        self.sm.unsubscribe("a", "*", 'sock2')
        self.assertEqual(self.sm.find_sub("a", "*"), [ 'sock1' ])

    def test_subscription_add_several_sockets(self):
        socks = [ 's1', 's2', 's3', 's4', 's5' ]
        for s in socks:
            self.sm.subscribe("a", "*", s)
        self.assertEqual(self.sm.find_sub("a", "*"), socks)

    def test_unsubscribe(self):
        socks = [ 's1', 's2', 's3', 's4', 's5' ]
        for s in socks:
            self.sm.subscribe("a", "*", s)
        self.sm.unsubscribe("a", "*", 's3')
        self.assertEqual(self.sm.find_sub("a", "*"), [ 's1', 's2', 's4', 's5' ])

    def test_unsubscribe_all(self):
        self.sm.subscribe('g1', 'i1', 's1')
        self.sm.subscribe('g1', 'i1', 's2')
        self.sm.subscribe('g1', 'i2', 's1')
        self.sm.subscribe('g1', 'i2', 's2')
        self.sm.subscribe('g2', 'i1', 's1')
        self.sm.subscribe('g2', 'i1', 's2')
        self.sm.subscribe('g2', 'i2', 's1')
        self.sm.subscribe('g2', 'i2', 's2')
        self.sm.unsubscribe_all('s1')
        self.assertEqual(self.sm.find_sub("g1", "i1"), [ 's2' ])
        self.assertEqual(self.sm.find_sub("g1", "i2"), [ 's2' ])
        self.assertEqual(self.sm.find_sub("g2", "i1"), [ 's2' ])
        self.assertEqual(self.sm.find_sub("g2", "i2"), [ 's2' ])

    def test_find(self):
        self.sm.subscribe('g1', 'i1', 's1')
        self.sm.subscribe('g1', '*', 's2')
        self.assertEqual(set(self.sm.find("g1", "i1")), set([ 's1', 's2' ]))

    def test_find_sub(self):
        self.sm.subscribe('g1', 'i1', 's1')
        self.sm.subscribe('g1', '*', 's2')
        self.assertEqual(self.sm.find_sub("g1", "i1"), [ 's1' ])

    def test_open_socket_parameter(self):
        self.assertFalse(os.path.exists("./my_socket_file"))
        msgq = MsgQ("./my_socket_file");
        msgq.setup()
        self.assertTrue(os.path.exists("./my_socket_file"))
        msgq.shutdown();
        self.assertFalse(os.path.exists("./my_socket_file"))

    def test_open_socket_environment_variable(self):
        self.assertFalse(os.path.exists("my_socket_file"))
        os.environ["BIND10_MSGQ_SOCKET_FILE"] = "./my_socket_file"
        msgq = MsgQ();
        msgq.setup()
        self.assertTrue(os.path.exists("./my_socket_file"))
        msgq.shutdown();
        self.assertFalse(os.path.exists("./my_socket_file"))

    def test_open_socket_default(self):
        env_var = None
        if "BIND10_MSGQ_SOCKET_FILE" in os.environ:
            env_var = os.environ["BIND10_MSGQ_SOCKET_FILE"]
            del os.environ["BIND10_MSGQ_SOCKET_FILE"]
        socket_file = MsgQ.SOCKET_FILE
        self.assertFalse(os.path.exists(socket_file))
        msgq = MsgQ();
        try:
            msgq.setup()
            self.assertTrue(os.path.exists(socket_file))
            msgq.shutdown();
            self.assertFalse(os.path.exists(socket_file))
        except socket.error:
            # ok, the install path doesn't exist at all,
            # so we can't check any further
            pass
        if env_var is not None:
            os.environ["BIND10_MSGQ_SOCKET_FILE"] = env_var

    def test_open_socket_bad(self):
        msgq = MsgQ("/does/not/exist")
        self.assertRaises(socket.error, msgq.setup)

if __name__ == '__main__':
    unittest.main()
