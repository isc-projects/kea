from msgq import SubscriptionManager, MsgQ

import unittest
import os
import socket
import signal
import sys
import time
import isc.cc

#
# Currently only the subscription part and some sending is implemented...
# I'd have to mock out a socket, which, while not impossible, is not trivial.
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
        orig_socket_file = None
        if "BIND10_MSGQ_SOCKET_FILE" in os.environ:
            env_var = os.environ["BIND10_MSGQ_SOCKET_FILE"]
            del os.environ["BIND10_MSGQ_SOCKET_FILE"]
        # temporarily replace the class "default" not to be disrupted by
        # any running BIND 10 instance.
        if "BIND10_TEST_SOCKET_FILE" in os.environ:
            MsgQ.SOCKET_FILE = os.environ["BIND10_TEST_SOCKET_FILE"]
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
        if orig_socket_file is not None:
            MsgQ.SOCKET_FILE = orig_socket_file

    def test_open_socket_bad(self):
        msgq = MsgQ("/does/not/exist")
        self.assertRaises(socket.error, msgq.setup)

class SendNonblock(unittest.TestCase):
    """
    Tests that the whole thing will not get blocked if someone does not read.
    """

    def terminate_check(self, task, timeout=30):
        """
        Runs task in separate process (task is a function) and checks
        it terminates sooner than timeout.
        """
        task_pid = os.fork()
        if task_pid == 0:
            # Kill the forked process after timeout by SIGALRM
            signal.alarm(timeout)
            # Run the task
            # If an exception happens or we run out of time, we terminate
            # with non-zero
            task()
            # If we got here, then everything worked well and in time
            # In that case, we terminate successfully
            os._exit(0)	# needs exit code
        else:
            (pid, status) = os.waitpid(task_pid, 0)
            self.assertEqual(0, status,
                "The task did not complete successfully in time")

    def infinite_sender(self, sender):
        """
        Sends data until an exception happens. socket.error is caught,
        as it means the socket got closed. Sender is called to actually
        send the data.
        """
        msgq = MsgQ()
        # We do only partial setup, so we don't create the listening socket
        msgq.setup_poller()
        (read, write) = socket.socketpair(socket.AF_UNIX, socket.SOCK_STREAM)
        msgq.register_socket(write)
        # Keep sending while it is not closed by the msgq
        try:
            while True:
                sender(msgq, write)
        except socket.error:
            pass
        read.close()
        write.close()

    def test_infinite_sendmsg(self):
        """
        Tries sending messages (and not reading them) until it either times
        out (in blocking call, wrong) or closes it (correct).
        """
        data = "data"
        for i in range(1, 10):
            data += data
        self.terminate_check(lambda: self.infinite_sender(
            lambda msgq, socket: msgq.sendmsg(socket, {}, {"message" : data})))

    def test_infinite_sendprepared(self):
        """
        Tries sending data (and not reading them) until it either times
        out (in blocking call, wrong) or closes it (correct).
        """
        data = b"data"
        for i in range(1, 10):
            data += data
        self.terminate_check(lambda: self.infinite_sender(
            lambda msgq, socket: msgq.send_prepared_msg(socket, data)))

    def send_many(self, data):
        """
        Tries that sending a command many times and getting an answer works.
        """
        msgq = MsgQ()
        # msgq.run needs to compare with the listen_socket, so we provide
        # a replacement
        class DummySocket:
            def fileno():
                return -1
        msgq.listen_socket = DummySocket
        (queue, out) = socket.socketpair(socket.AF_UNIX, socket.SOCK_STREAM)
        def run():
            length = len(data)
            queue_pid = os.fork()
            if queue_pid == 0:
                signal.alarm(120)
                msgq.setup_poller()
                msgq.register_socket(queue)
                msgq.run()
            else:
                try:
                    def killall(signum, frame):
                        os.kill(queue_pid, signal.SIGTERM)
                        os._exit(1)
                    signal.signal(signal.SIGALRM, killall)
                    msg = msgq.preparemsg({"type" : "ping"}, data)
                    now = time.clock()
                    while time.clock() - now < 0.2:
                        out.sendall(msg)
                        # Check the answer
                        (routing, received) = msgq.read_packet(out.fileno(),
                            out)
                        self.assertEqual({"type" : "pong"},
                            isc.cc.message.from_wire(routing))
                        self.assertEqual(data, received)
                finally:
                    os.kill(queue_pid, signal.SIGTERM)
        self.terminate_check(run)
        queue.close()
        out.close()

    def test_small_sends(self):
        """
        Tests sending small data many times.
        """
        self.send_many(b"data")

    def test_large_sends(self):
        """
        Tests sending large data many times.
        """
        data = b"data"
        for i in range(1, 20):
            data = data + data
        self.send_many(data)

if __name__ == '__main__':
    unittest.main()
