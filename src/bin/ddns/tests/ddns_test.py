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

'''Tests for the DDNS module'''

import unittest
import isc
import ddns
import isc.config
import select
import errno
import isc.util.io.socketsession
import socket
import os.path

class FakeSocket:
    """
    A fake socket. It only provides a file number, peer name and accept method.
    """
    def __init__(self, fileno):
        self.__fileno = fileno
    def fileno(self):
        return self.__fileno
    def getpeername(self):
        return "fake_unix_socket"
    def accept(self):
        return FakeSocket(self.__fileno + 1)

class FakeSessionReceiver:
    """
    A fake socket session receiver, for our tests.
    """
    def __init__(self, socket):
        self._socket = socket
    def socket(self):
        """
        This method is not present in the real receiver, but we use it to
        inspect the socket passed to the constructor.
        """
        return self._socket

class MyCCSession(isc.config.ConfigData):
    '''Fake session with minimal interface compliance'''
    def __init__(self):
        module_spec = isc.config.module_spec_from_file(
            ddns.SPECFILE_LOCATION)
        isc.config.ConfigData.__init__(self, module_spec)
        self._started = False

    def start(self):
        '''Called by DDNSServer initialization, but not used in tests'''
        self._started = True

    def get_socket(self):
        """
        Used to get the file number for select.
        """
        return FakeSocket(1)

class MyDDNSServer():
    '''Fake DDNS server used to test the main() function'''
    def __init__(self):
        self.reset()

    def run(self):
        '''
        Fake the run() method of the DDNS server. This will set
        self._run_called to True.
        If self._exception is not None, this is raised as an exception
        '''
        self.run_called = True
        if self._exception is not None:
            self.exception_raised = True
            raise self._exception

    def set_exception(self, exception):
        '''Set an exception to be raised when run() is called'''
        self._exception = exception

    def reset(self):
        '''(Re)set to initial values'''
        self.run_called = False
        self.exception_raised = False
        self._exception = None

class TestDDNSServer(unittest.TestCase):
    def setUp(self):
        cc_session = MyCCSession()
        self.assertFalse(cc_session._started)
        self.ddns_server = ddns.DDNSServer(cc_session)
        self.__cc_session = cc_session
        self.assertTrue(cc_session._started)
        self.__select_expected = None
        self.__select_answer = None
        self.__select_exception = None
        self.__hook_called = False
        self.ddns_server._listen_socket = FakeSocket(2)
        ddns.select.select = self.__select

    def tearDown(self):
        ddns.select.select = select.select
        ddns.isc.util.io.socketsession.SocketSessionReceiver = \
            isc.util.io.socketsession.SocketSessionReceiver

    def test_listen(self):
        '''
        Test the old socket file is removed (if any) and a new socket
        is created when the ddns server is created.
        '''
        # Make sure the socket does not exist now
        ddns.clear_socket()
        # Hook the call for clearing the socket
        orig_clear = ddns.clear_socket
        ddns.clear_socket = self.__hook
        # Create the server
        ddnss = ddns.DDNSServer(MyCCSession())
        ddns.clear_socket = orig_clear
        # The socket is created
        self.assertTrue(os.path.exists(ddns.SOCKET_FILE))
        self.assertTrue(isinstance(ddnss._listen_socket, socket.socket))
        # And deletion of the socket was requested
        self.assertIsNone(self.__hook_called)
        # Now make sure the clear_socket really works
        ddns.clear_socket()
        self.assertFalse(os.path.exists(ddns.SOCKET_FILE))

    def test_config_handler(self):
        # Config handler does not do anything yet, but should at least
        # return 'ok' for now.
        new_config = {}
        answer = self.ddns_server.config_handler(new_config)
        self.assertEqual((0, None), isc.config.parse_answer(answer))

    def test_shutdown_command(self):
        '''Test whether the shutdown command works'''
        self.assertFalse(self.ddns_server._shutdown)
        answer = self.ddns_server.command_handler('shutdown', None)
        self.assertEqual((0, None), isc.config.parse_answer(answer))
        self.assertTrue(self.ddns_server._shutdown)

    def test_command_handler(self):
        '''Test some commands.'''
        # this command should not exist
        answer = self.ddns_server.command_handler('bad_command', None)
        self.assertEqual((1, 'Unknown command: bad_command'),
                         isc.config.parse_answer(answer))

    def test_signal_handler(self):
        '''Test whether signal_handler calls shutdown()'''
        signal_handler = ddns.create_signal_handler(self.ddns_server)
        self.assertFalse(self.ddns_server._shutdown)
        signal_handler(None, None)
        self.assertTrue(self.ddns_server._shutdown)

    def __select(self, reads, writes, exceptions, timeout=None):
        """
        A fake select. It checks it was called with the correct parameters and
        returns a preset answer.

        If there's an exception stored in __select_exception, it is raised
        instead and the exception is cleared.
        """
        self.assertEqual(self.__select_expected, (reads, writes, exceptions,
                                                  timeout))
        if self.__select_exception is not None:
            (self.__select_exception, exception) = (None,
                                                    self.__select_exception)
            raise exception
        answer = self.__select_answer
        self.__select_answer = None
        self.ddns_server._shutdown = True
        return answer

    def __hook(self, param=None):
        """
        A hook that can be installed to any nullary or unary function and see
        if it was really called.
        """
        self.__hook_called = param

    def test_accept_called(self):
        """
        Test we call the accept function when a new connection comes.
        """
        self.ddns_server.accept = self.__hook
        self.__select_expected = ([1, 2], [], [], None)
        self.__select_answer = ([2], [], [])
        self.__hook_called = "Not called"
        self.ddns_server.run()
        self.assertTrue(self.ddns_server._shutdown)
        # The answer got used
        self.assertIsNone(self.__select_answer)
        # Reset, when called without parameter
        self.assertIsNone(self.__hook_called)

    def test_check_command_called(self):
        """
        Test the check_command is called when there's something on the
        socket.
        """
        self.__cc_session.check_command = self.__hook
        self.__select_expected = ([1, 2], [], [], None)
        self.__select_answer = ([1], [], [])
        self.ddns_server.run()
        self.assertTrue(self.ddns_server._shutdown)
        # The answer got used
        self.assertIsNone(self.__select_answer)
        # And the check_command was called with true parameter (eg.
        # non-blocking)
        self.assertTrue(self.__hook_called)

    def test_accept(self):
        """
        Test that we can accept a new connection.
        """
        # There's nothing before the accept
        ddns.isc.util.io.socketsession.SocketSessionReceiver = \
            FakeSessionReceiver
        self.assertEqual({}, self.ddns_server._socksession_receivers)
        self.ddns_server.accept()
        # Now the new socket session receiver is stored in the dict
        # The 3 comes from _listen_socket.accept() - _listen_socket has
        # fileno 2 and accept returns socket with fileno increased by one.
        self.assertEqual([3],
                         list(self.ddns_server._socksession_receivers.keys()))
        (socket, receiver) = self.ddns_server._socksession_receivers[3]
        self.assertTrue(isinstance(socket, FakeSocket))
        self.assertEqual(3, socket.fileno())
        self.assertTrue(isinstance(receiver, FakeSessionReceiver))
        self.assertEqual(socket, receiver.socket())

    def test_incoming_called(self):
        """
        Test the run calls handle_session when there's something on the
        socket.
        """
        socket = FakeSocket(3)
        self.ddns_server._socksession_receivers = \
            {3: (socket, FakeSessionReceiver(socket))}
        self.ddns_server.handle_session = self.__hook
        self.__select_expected = ([1, 2, 3], [], [], None)
        self.__select_answer = ([3], [], [])
        self.ddns_server.run()
        self.assertTrue(self.ddns_server._shutdown)
        self.assertIsNone(self.__select_answer)
        self.assertEqual(3, self.__hook_called)

    def test_handle_session_ok(self):
        """
        Test the handle_session pops the receiver and calls handle_request
        when everything is OK.
        """
        socket = FakeSocket(3)
        receiver = FakeSessionReceiver(socket)
        # It doesn't really matter what data we use here, it is only passed
        # through the code
        param = (FakeSocket(4), ('127.0.0.1', 1234), ('127.0.0.1', 1235),
                 'Some data')
        def pop():
            return param
        # Prepare data into the receiver
        receiver.pop = pop
        self.ddns_server._socksession_receivers = {3: (socket, receiver)}
        self.ddns_server.handle_request = self.__hook
        # Call it
        self.ddns_server.handle_session(3)
        # The popped data are passed into the handle_request
        self.assertEqual(param, self.__hook_called)
        # The receivers are kept the same
        self.assertEqual({3: (socket, receiver)},
                         self.ddns_server._socksession_receivers)

    def test_handle_session_fail(self):
        """
        Test the handle_session removes (and closes) the socket and receiver
        when the receiver complains.
        """
        socket = FakeSocket(3)
        receiver = FakeSessionReceiver(socket)
        def pop():
            raise isc.util.io.socketsession.SocketSessionError('Test error')
        receiver.pop = pop
        socket.close = self.__hook
        self.__hook_called = False
        self.ddns_server._socksession_receivers = {3: (socket, receiver)}
        self.ddns_server.handle_session(3)
        # The "dead" receiver is removed
        self.assertEqual({}, self.ddns_server._socksession_receivers)
        # Close is called with no parameter, so the default None
        self.assertIsNone(self.__hook_called)

    def test_select_exception_ignored(self):
        """
        Test that the EINTR is ignored in select.
        """
        # Prepare the EINTR exception
        self.__select_exception = select.error(errno.EINTR)
        # We reuse the test here, as it should act the same. The exception
        # should just get ignored.
        self.test_check_command_called()

    def test_select_exception_fatal(self):
        """
        Test that other exceptions are fatal to the run.
        """
        # Prepare a different exception
        self.__select_exception = select.error(errno.EBADF)
        self.__select_expected = ([1, 2], [], [], None)
        self.assertRaises(select.error, self.ddns_server.run)

class TestMain(unittest.TestCase):
    def setUp(self):
        self._server = MyDDNSServer()
        self.__orig_clear = ddns.clear_socket
        ddns.clear_socket = self.__clear_socket
        self.__clear_called = False

    def tearDown(self):
        ddns.clear_socket = self.__orig_clear

    def test_main(self):
        self.assertFalse(self._server.run_called)
        ddns.main(self._server)
        self.assertTrue(self._server.run_called)
        self.assertTrue(self.__clear_called)

    def __clear_socket(self):
        self.__clear_called = True

    def check_exception(self, ex):
        '''Common test sequence to see if the given exception is caused.
        '''
        # Should technically not be necessary, but reset server to be sure
        self._server.reset()
        self.assertFalse(self._server.exception_raised)
        self._server.set_exception(ex)
        ddns.main(self._server)
        self.assertTrue(self._server.exception_raised)

    def test_exceptions(self):
        '''
        Test whether exceptions are caught in main()
        These exceptions should not bubble up.
        '''
        self._server.set_exception(KeyboardInterrupt())
        self.assertFalse(self._server.exception_raised)
        ddns.main(self._server)
        self.assertTrue(self._server.exception_raised)

        self.check_exception(isc.cc.SessionError("error"))
        self.check_exception(isc.config.ModuleCCSessionError("error"))
        self.check_exception(ddns.DDNSConfigError("error"))
        self.check_exception(isc.cc.SessionTimeout("error"))
        self.check_exception(Exception("error"))

        # Add one that is not a subclass of Exception, and hence not
        # caught. Misuse BaseException for that.
        self._server.reset()
        self.assertFalse(self._server.exception_raised)
        self._server.set_exception(BaseException("error"))
        self.assertRaises(BaseException, ddns.main, self._server)
        self.assertTrue(self._server.exception_raised)

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
