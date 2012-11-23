from msgq import SubscriptionManager, MsgQ

import unittest
import os
import socket
import signal
import sys
import time
import errno
import threading
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

class DummySocket:
    """
    Dummy socket class.
    This one does nothing at all, but some calls are used.
    It is mainly intended to override the listen socket for msgq, which
    we do not need in these tests.
    """
    def fileno():
        return -1

    def close():
        pass

class BadSocket:
    """
    Special socket wrapper class. Once given a socket in its constructor,
    it completely behaves like that socket, except that its send() call
    will only actually send one byte per call, and optionally raise a given
    exception at a given time.
    """
    def __init__(self, real_socket, raise_on_send=0, send_exception=None):
        """
        Parameters:
        real_socket: The actual socket to wrap
        raise_on_send: integer. If send_exception is not None, it will be
                                raised on this byte (i.e. 1 = on the first
                                call to send(), 1 = on the 4th call to send)
                                Note: if 0, send_exception will not be raised.
        send_exception: if not None, this exception will be raised
                        (if raise_on_send is not 0)
        """
        self.socket = real_socket
        self.send_count = 0
        self.raise_on_send = raise_on_send
        self.send_exception = send_exception

    # completely wrap all calls and member access
    # (except explicitely overridden ones)
    def __getattr__(self, name, *args):
        attr = getattr(self.socket, name)
        if callable(attr):
            def callable_attr(*args):
                return attr.__call__(*args)
            return callable_attr
        else:
            return attr

    def send(self, data):
        self.send_count += 1
        if self.send_exception is not None and\
           self.send_count == self.raise_on_send:
            raise self.send_exception

        if len(data) > 0:
            return self.socket.send(data[:1])
        else:
            return 0

class MsgQThread(threading.Thread):
    """
    Very simple thread class that runs msgq.run() when started,
    and stores the exception that msgq.run() raises, if any.
    """
    def __init__(self, msgq):
        threading.Thread.__init__(self)
        self.msgq_ = msgq
        self.caught_exception = None
        self.lock = threading.Lock()

    def run(self):
        try:
            self.msgq_.run()
        except Exception as exc:
            # Store the exception to make the test fail if necessary
            self.caught_exception = exc

    def stop(self):
        self.msgq_.stop()


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

        # Explicitly close temporary socket pair as the Python
        # interpreter expects it.  It may not be 100% exception safe,
        # but since this is only for tests we prefer brevity.
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

        # Explicitly close temporary socket pair as the Python
        # interpreter expects it.  It may not be 100% exception safe,
        # but since this is only for tests we prefer brevity.
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

    def do_send(self, write, read, expect_arrive=True,
                expect_send_exception=None):
        """
        Makes a msgq object that is talking to itself,
        run it in a separate thread so we can use and
        test run().
        Parameters:
        write: a socket that is used to send the data to
        read: a socket that is used to read the data from
        expect_arrive: if True, the read socket is read from, and the data
                       that is read is expected to be the same as the data
                       that has been sent to the write socket.
        expect_send_exception: if not None, this is the exception that is
                               expected to be raised by msgq
        """

        # Some message and envelope data to send and check
        env = b'{"env": "foo"}'
        msg = b'{"msg": "bar"}'

        msgq = MsgQ()
        # Don't need a listen_socket
        msgq.listen_socket = DummySocket
        msgq.setup_poller()
        msgq.register_socket(write)
        # Queue the message for sending
        msgq.sendmsg(write, env, msg)

        # Run it in a thread
        msgq_thread = MsgQThread(msgq)
        # If we're done, just kill it
        msgq_thread.start()

        if expect_arrive:
            (recv_env, recv_msg) = msgq.read_packet(read.fileno(),
                read)
            self.assertEqual(env, recv_env)
            self.assertEqual(msg, recv_msg)

            # expect_arrive also suggests everything should
            # still be working, so a stop command should also
            # be processed correctly
            msg = msgq.preparemsg({"type" : "stop"})
            read.sendall(msg)
        else:
            # OK, then bluntly call stop itself
            # First give it a chance to handle any remaining events.
            # 1 second arbitrarily chosen to hopefully be long enough
            # yet not bog down the tests too much.
            msgq_thread.join(1.0)
            msgq.stop()

        # Wait for thread to stop if it hasn't already
        # Put in a (long) timeout; the thread *should* stop, but if it
        # does not, we don't want the test to hang forever
        msgq_thread.join(60)
        # Fail the test if it didn't stop
        self.assertFalse(msgq_thread.isAlive(), "Thread did not stop")

        # Check the exception from the thread, if any
        # First, if we didn't expect it; reraise it (to make test fail and
        # show the stacktrace for debugging)
        if expect_send_exception is None:
            if msgq_thread.caught_exception is not None:
                raise msgq_thread.caught_exception
        else:
            # If we *did* expect it, fail it there was none
            self.assertIsNotNone(msgq_thread.caught_exception)

    def do_send_with_send_error(self, raise_on_send, send_exception,
                                expect_answer=True,
                                expect_send_exception=None):
        """
        Sets up two connected sockets, wraps the sender socket into a BadSocket
        class, then performs a do_send() test.
        Parameters:
        raise_on_send: the byte at which send_exception should be raised
                       (see BadSocket)
        send_exception: the exception to raise (see BadSocket)
        expect_answer: whether the send is expected to complete (and hence
                       the read socket should get the message)
        expect_send_exception: the exception msgq is expected to raise when
                               send_exception is raised by BadSocket.
        """
        (write, read) = socket.socketpair(socket.AF_UNIX, socket.SOCK_STREAM)
        badwrite = BadSocket(write, raise_on_send, send_exception)
        self.do_send(badwrite, read, expect_answer, expect_send_exception)
        write.close()
        read.close()

    def test_send_raise_recoverable(self):
        """
        Test whether msgq survices a recoverable socket errors when sending.
        Two tests are done: one where the error is raised on the 3rd octet,
                            and one on the 23rd.
        """
        sockerr = socket.error
        for err in [ errno.EAGAIN, errno.EWOULDBLOCK, errno.EINTR ]:
            sockerr.errno = err
            self.do_send_with_send_error(3, sockerr)
            self.do_send_with_send_error(23, sockerr)

    def test_send_raise_nonrecoverable(self):
        """
        Test whether msgq survives socket errors that are nonrecoverable
        (for said socket that is, i.e. EPIPE etc).
        Two tests are done: one where the error is raised on the 3rd octet,
                            and one on the 23rd.
        """
        sockerr = socket.error
        for err in [ errno.EPIPE, errno.ENOBUFS, errno.ECONNRESET ]:
            sockerr.errno = err
            self.do_send_with_send_error(3, sockerr, False)
            self.do_send_with_send_error(23, sockerr, False)

    def otest_send_raise_crash(self):
        """
        Test whether msgq does NOT survive on a general exception.
        Note, perhaps it should; but we'd have to first discuss and decide
        how it should recover (i.e. drop the socket and consider the client
        dead?
        It may be a coding problem in msgq itself, and we certainly don't
        want to ignore those.
        """
        sockerr = Exception("just some general exception")
        self.do_send_with_send_error(3, sockerr, False, sockerr)
        self.do_send_with_send_error(23, sockerr, False, sockerr)


if __name__ == '__main__':
    unittest.main()
