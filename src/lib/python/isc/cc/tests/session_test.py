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

#
# Tests for the ConfigData and MultiConfigData classes
#

import unittest
import os
import json
from isc.cc.session import *

# our fake socket, where we can read and insert messages
class MySocket():
    def __init__(self, family, type):
        self.family = family
        self.type = type
        self.recvqueue = bytearray()
        self.sendqueue = bytearray()
        self._blocking = True
        self.send_limit = None

    def connect(self, to):
        pass

    def close(self):
        pass

    def setblocking(self, val):
        self._blocking = val

    def send(self, data):
        # If the upper limit is specified, only "send" up to the specified
        # limit
        if self.send_limit is not None and len(data) > self.send_limit:
            self.sendqueue.extend(data[0:self.send_limit])
            return self.send_limit
        else:
            self.sendqueue.extend(data)
            return len(data)

    def readsent(self, length):
        if length > len(self.sendqueue):
            raise Exception("readsent(" + str(length) + ") called, but only " + str(len(self.sendqueue)) + " in queue")
        result = self.sendqueue[:length]
        del self.sendqueue[:length]
        return result

    def readsentmsg(self):
        """return bytearray of the full message include length specifiers"""
        result = bytearray()

        length_buf = self.readsent(4)
        result.extend(length_buf)
        length = struct.unpack('>I', length_buf)[0]

        header_length_buf = self.readsent(2)
        header_length = struct.unpack('>H', header_length_buf)[0]
        result.extend(header_length_buf)

        data_length = length - 2 - header_length

        result.extend(self.readsent(header_length))
        result.extend(self.readsent(data_length))

        return result

    def readsentmsg_parsed(self):
        length_buf = self.readsent(4)
        length = struct.unpack('>I', length_buf)[0]
        header_length_buf = self.readsent(2)
        header_length = struct.unpack('>H', header_length_buf)[0]
        data_length = length - 2 - header_length

        env = json.loads(self.readsent(header_length).decode('utf-8'), strict=False)
        if (data_length > 0):
            msg = json.loads(self.readsent(data_length).decode('utf-8'), strict=False)
        else:
            msg = {}
        return (env, msg)

    def recv(self, length):
        if len(self.recvqueue) == 0:
            if self._blocking:
                return bytes()
            else:
                raise socket.error(errno.EAGAIN, "Resource temporarily unavailable")
        if length > len(self.recvqueue):
            raise Exception("Buffer underrun in test, does the test provide the right data?")
        result = self.recvqueue[:length]
        del self.recvqueue[:length]
        #print("[XX] returning: " + str(result))
        #print("[XX] queue now: " + str(self.recvqueue))
        return result

    def addrecv(self, env, msg = None):
        if type(env) == dict:
            env = isc.cc.message.to_wire(env)
        if type(msg) == dict:
            msg = isc.cc.message.to_wire(msg)
        length = 2 + len(env);
        if msg:
            length += len(msg)
        self.recvqueue.extend(struct.pack("!I", length))
        self.recvqueue.extend(struct.pack("!H", len(env)))
        self.recvqueue.extend(env)
        if msg:
            self.recvqueue.extend(msg)

    def settimeout(self, val):
        pass

    def gettimeout(self):
        return 0

    def set_send_limit(self, limit):
        '''Specify the upper limit of the transmittable data at once.

        By default, the send() method of this class "sends" all given data.
        If this method is called and the its parameter is not None,
        subsequent calls to send() will only transmit the specified amount
        of data.  This can be used to emulate the situation where send()
        on a real socket object results in partial write.
        '''
        self.send_limit = limit

#
# We subclass the Session class we're testing here, only
# to override the __init__() method, which wants a socket,
# and we need to use our fake socket
class MySession(Session):
    def __init__(self, port=9912, s=None):
        self._socket = None
        self._socket_timeout = 1
        self._lname = None
        self._recvbuffer = bytearray()
        self._recv_len_size = 0
        self._recv_size = 0
        self._sequence = 1
        self._closed = False
        self._queue = []
        self._lock = threading.RLock()

        if s is not None:
            self._socket = s
        else:
            try:
                self._socket = MySocket(socket.AF_INET, socket.SOCK_STREAM)
                self._socket.connect(tuple(['127.0.0.1', port]))
                self._lname = "test_name"
                # testing getlname here isn't useful, code removed
            except socket.error as se:
                    raise SessionError(se)

class testSession(unittest.TestCase):

    def test_session_close(self):
        sess = MySession()
        self.assertEqual("test_name", sess.lname)
        sess.close()
        self.assertRaises(SessionError, sess.sendmsg, {}, {"hello": "a"})

    def test_env_too_large(self):
        sess = MySession()
        largeenv = { "a": "b"*65535 }
        self.assertRaises(ProtocolError, sess.sendmsg, largeenv, {"hello": "a"})

    def test_session_sendmsg(self):
        sess = MySession()
        sess.sendmsg({}, {"hello": "a"})
        sent = sess._socket.readsentmsg();
        self.assertEqual(sent, b'\x00\x00\x00\x12\x00\x02{}{"hello": "a"}')
        sess.close()
        self.assertRaises(SessionError, sess.sendmsg, {}, {"hello": "a"})

    def test_session_sendmsg2(self):
        sess = MySession()
        sess.sendmsg({'to': 'someone', 'reply': 1}, {"hello": "a"})
        sent = sess._socket.readsentmsg();
        #print(sent)
        #self.assertRaises(SessionError, sess.sendmsg, {}, {"hello": "a"})

    def test_session_sendmsg_shortwrite(self):
        sess = MySession()
        # Specify the upper limit of the size that can be transmitted at
        # a single send() call on the faked socket (10 is an arbitrary choice,
        # just reasonably small).
        sess._socket.set_send_limit(10)
        sess.sendmsg({'to': 'someone', 'reply': 1}, {"hello": "a"})
        # The complete message should still have been transmitted in the end.
        sent = sess._socket.readsentmsg();

    def recv_and_compare(self, session, bytes, env, msg):
        """Adds bytes to the recvqueue (which will be read by the
           session object, and compare the resultinv env and msg to
           the ones given."""
        session._socket.addrecv(bytes)
        s_env, s_msg = session.recvmsg(False)
        self.assertEqual(env, s_env)
        self.assertEqual(msg, s_msg)
        # clear the recv buffer in case a malformed message left garbage
        # (actually, shouldn't that case provide some error instead of
        # None?)
        session._socket.recvqueue = bytearray()

    def test_session_recvmsg(self):
        sess = MySession()
        # {'to': "someone"}, {"hello": "a"}
        #self.recv_and_compare(sess,
        #                      b'\x00\x00\x00\x1f\x00\x10Skan\x02to(\x07someoneSkan\x05hello(\x01a',
        #                      {'to': "someone"}, {"hello": "a"})

        # 'malformed' messages
        # shouldn't some of these raise exceptions?
        #self.recv_and_compare(sess,
        #                      b'\x00',
        #                      None, None)
        #self.recv_and_compare(sess,
        #                      b'\x00\x00\x00\x10',
        #                      None, None)
        #self.recv_and_compare(sess,
        #                      b'\x00\x00\x00\x02\x00\x00',
        #                      None, None)
        #self.recv_and_compare(sess,
        #                      b'\x00\x00\x00\x02\x00\x02',
        #                      None, None)
        #self.recv_and_compare(sess,
        #                      b'',
        #                      None, None)

        # need to clear
        sess._socket.recvqueue = bytearray()

        # 'queueing' system
        # sending message {'to': 'someone', 'reply': 1}, {"hello": "a"}
        #print("sending message {'to': 'someone', 'reply': 1}, {'hello': 'a'}")
        # get no message without asking for a specific sequence number reply
        self.assertFalse(sess.has_queued_msgs())
        sess._socket.addrecv({'to': 'someone', 'reply': 1}, {"hello": "a"})
        env, msg = sess.recvmsg(True)
        self.assertEqual(None, env)
        self.assertTrue(sess.has_queued_msgs())
        env, msg = sess.recvmsg(True, 1)
        self.assertEqual({'to': 'someone', 'reply': 1}, env)
        self.assertEqual({"hello": "a"}, msg)
        self.assertFalse(sess.has_queued_msgs())

        # ask for a different sequence number reply (that doesn't exist)
        # then ask for the one that is there
        self.assertFalse(sess.has_queued_msgs())
        sess._socket.addrecv({'to': 'someone', 'reply': 1}, {"hello": "a"})
        env, msg = sess.recvmsg(True, 2)
        self.assertEqual(None, env)
        self.assertEqual(None, msg)
        self.assertTrue(sess.has_queued_msgs())
        env, msg = sess.recvmsg(True, 1)
        self.assertEqual({'to': 'someone', 'reply': 1}, env)
        self.assertEqual({"hello": "a"}, msg)
        self.assertFalse(sess.has_queued_msgs())

        # ask for a different sequence number reply (that doesn't exist)
        # then ask for any message
        self.assertFalse(sess.has_queued_msgs())
        sess._socket.addrecv({'to': 'someone', 'reply': 1}, {"hello": "a"})
        env, msg = sess.recvmsg(True, 2)
        self.assertEqual(None, env)
        self.assertEqual(None, msg)
        self.assertTrue(sess.has_queued_msgs())
        env, msg = sess.recvmsg(True, 1)
        self.assertEqual({'to': 'someone', 'reply': 1}, env)
        self.assertEqual({"hello": "a"}, msg)
        self.assertFalse(sess.has_queued_msgs())

        #print("sending message {'to': 'someone', 'reply': 1}, {'hello': 'a'}")

        # ask for a different sequence number reply (that doesn't exist)
        # send a new message, ask for specific message (get the first)
        # then ask for any message (get the second)
        self.assertFalse(sess.has_queued_msgs())
        sess._socket.addrecv({'to': 'someone', 'reply': 1}, {'hello': 'a'})
        env, msg = sess.recvmsg(True, 2)
        self.assertEqual(None, env)
        self.assertEqual(None, msg)
        self.assertTrue(sess.has_queued_msgs())
        sess._socket.addrecv({'to': 'someone' }, {'hello': 'b'})
        env, msg = sess.recvmsg(True, 1)
        self.assertEqual({'to': 'someone', 'reply': 1 }, env)
        self.assertEqual({"hello": "a"}, msg)
        self.assertFalse(sess.has_queued_msgs())
        env, msg = sess.recvmsg(True)
        self.assertEqual({'to': 'someone'}, env)
        self.assertEqual({"hello": "b"}, msg)
        self.assertFalse(sess.has_queued_msgs())

        # send a message, then one with specific reply value
        # ask for that specific message (get the second)
        # then ask for any message (get the first)
        self.assertFalse(sess.has_queued_msgs())
        sess._socket.addrecv({'to': 'someone' }, {'hello': 'b'})
        sess._socket.addrecv({'to': 'someone', 'reply': 1}, {'hello': 'a'})
        env, msg = sess.recvmsg(True, 1)
        self.assertEqual({'to': 'someone', 'reply': 1}, env)
        self.assertEqual({"hello": "a"}, msg)
        self.assertTrue(sess.has_queued_msgs())
        env, msg = sess.recvmsg(True)
        self.assertEqual({'to': 'someone'}, env)
        self.assertEqual({"hello": "b"}, msg)
        self.assertFalse(sess.has_queued_msgs())

    def test_recv_bad_msg(self):
        sess = MySession()
        self.assertFalse(sess.has_queued_msgs())
        sess._socket.addrecv({'to': 'someone' }, {'hello': 'b'})
        sess._socket.addrecv({'to': 'someone', 'reply': 1}, {'hello': 'a'})
        # mangle the bytes a bit
        sess._socket.recvqueue[5] = sess._socket.recvqueue[5] - 2
        sess._socket.recvqueue = sess._socket.recvqueue[:-2]
        self.assertRaises(SessionError, sess.recvmsg, True, 1)

    def test_next_sequence(self):
        sess = MySession()
        self.assertEqual(sess._sequence, 1)
        self.assertEqual(sess._next_sequence(), 2)
        self.assertEqual(sess._sequence, 2)
        sess._sequence = 56175
        self.assertEqual(sess._sequence, 56175)
        self.assertEqual(sess._next_sequence(), 56176)
        self.assertEqual(sess._sequence, 56176)

    def test_group_subscribe(self):
        sess = MySession()
        sess.group_subscribe("mygroup")
        sent = sess._socket.readsentmsg_parsed()
        self.assertEqual(sent, ({"group": "mygroup", "type": "subscribe",
                                 "instance": "*"}, {}))

        sess.group_subscribe("mygroup")
        sent = sess._socket.readsentmsg_parsed()
        self.assertEqual(sent, ({"group": "mygroup", "type": "subscribe",
                                 "instance": "*"}, {}))

        sess.group_subscribe("mygroup", "my_instance")
        sent = sess._socket.readsentmsg_parsed()
        self.assertEqual(sent, ({"group": "mygroup", "type": "subscribe",
                                 "instance": "my_instance"}, {}))

    def test_group_unsubscribe(self):
        sess = MySession()
        sess.group_unsubscribe("mygroup")
        sent = sess._socket.readsentmsg_parsed()
        self.assertEqual(sent, ({"group": "mygroup", "type": "unsubscribe",
                                 "instance": "*"}, {}))

        sess.group_unsubscribe("mygroup")
        sent = sess._socket.readsentmsg_parsed()
        self.assertEqual(sent, ({"group": "mygroup", "type": "unsubscribe",
                                 "instance": "*"}, {}))

        sess.group_unsubscribe("mygroup", "my_instance")
        sent = sess._socket.readsentmsg_parsed()
        self.assertEqual(sent, ({"group": "mygroup", "type": "unsubscribe",
                                 "instance": "my_instance"}, {}))

    def test_group_sendmsg(self):
        sess = MySession()
        self.assertEqual(sess._sequence, 1)

        msg = { "hello": "a" }

        def check_sent(additional_headers, sequence):
            sent = sess._socket.readsentmsg_parsed()
            headers = dict({"from": "test_name",
                            "seq": sequence,
                            "to": "*",
                            "type": "send"},
                           **additional_headers)
            self.assertEqual(sent, (headers, msg))
            self.assertEqual(sess._sequence, sequence)

        sess.group_sendmsg(msg, "my_group")
        check_sent({"instance": "*", "group": "my_group",
                    "want_answer": False}, 2)

        sess.group_sendmsg(msg, "my_group", "my_instance")
        check_sent({"instance": "my_instance", "group": "my_group",
                    "want_answer": False}, 3)

        sess.group_sendmsg(msg, "your_group", "your_instance")
        check_sent({"instance": "your_instance", "group": "your_group",
                    "want_answer": False}, 4)

        # Test the optional want_answer parameter
        sess.group_sendmsg(msg, "group", want_answer=True)
        check_sent({"instance": "*", "group": "group", "want_answer": True}, 5)


        sess.group_sendmsg(msg, "group", want_answer=False)
        check_sent({"instance": "*", "group": "group", "want_answer": False},
                   6)

    def test_group_recvmsg(self):
        # must this one do anything except not return messages with
        # no header?
        pass

    def test_group_reply(self):
        sess = MySession()
        sess.group_reply({ 'from': 'me', 'group': 'our_group',
                           'instance': 'other_instance', 'seq': 4},
                         {"hello": "a"})
        sent = sess._socket.readsentmsg_parsed();
        self.assertEqual(sent, ({"from": "test_name", "seq": 2,
                                 "to": "me", "instance": "other_instance",
                                 "reply": 4, "group": "our_group",
                                 "type": "send"},
                                {"hello": "a"}))

        sess.group_reply({ 'from': 'me', 'group': 'our_group',
                           'instance': 'other_instance', 'seq': 9},
                         {"hello": "a"})
        sent = sess._socket.readsentmsg_parsed();
        self.assertEqual(sent, ({"from": "test_name", "seq": 3,
                                 "to": "me", "instance": "other_instance",
                                 "reply": 9, "group": "our_group",
                                 "type": "send"},
                                {"hello": "a"}))

    def test_timeout(self):
        if "BIND10_TEST_SOCKET_FILE" not in os.environ:
            self.assertEqual("", "This test can only run if the value BIND10_TEST_SOCKET_FILE is set in the environment")
        TEST_SOCKET_FILE = os.environ["BIND10_TEST_SOCKET_FILE"]

        # create a read domain socket to pass into the session
        s1 = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        if os.path.exists(TEST_SOCKET_FILE):
            os.remove(TEST_SOCKET_FILE)
        s1.bind(TEST_SOCKET_FILE)

        try:
            s1.listen(1)

            s2 = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
            s2.connect(TEST_SOCKET_FILE)
            sess = MySession(1, s2)
            # set timeout to 100 msec, so test does not take too long
            sess.set_timeout(100)
            self.assertRaises(SessionTimeout, sess.group_recvmsg, False)
        finally:
            os.remove(TEST_SOCKET_FILE)

if __name__ == "__main__":
    unittest.main()

