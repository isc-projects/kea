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
import isc.util.io.socketsession

class FakeSocket:
    """
    A fake socket. It only provides a file number.
    """
    def __init__(self, fileno):
        self.__fileno = fileno
    def fileno(self):
        return self.__fileno
    def accept(self):
        return FakeSocket(self.__fileno + 1)

class FakeSession:
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
        self.cc_session = cc_session
        self.assertTrue(cc_session._started)
        self.__select_expected = None
        self.__select_answer = None
        self.__hook_called = False
        self.ddns_server._listen_socket = FakeSocket(2)
        ddns.select.select = self.__select

    def tearDown(self):
        ddns.select.select = select.select
        ddns.isc.util.io.socketsession.SocketSessionReceiver = \
            isc.util.io.socketsession.SocketSessionReceiver

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
        """
        self.assertEqual(self.__select_expected, (reads, writes, exceptions,
                                                  timeout))
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
        self.cc_session.check_command = self.__hook
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
        ddns.isc.util.io.socketsession.SocketSessionReceiver = FakeSession
        self.assertEqual({}, self.ddns_server._socket_sessions)
        self.ddns_server.accept()
        # Now the new session socket receiver is stored in the dict
        self.assertEqual([3], list(self.ddns_server._socket_sessions.keys()))
        (socket, session) = self.ddns_server._socket_sessions[3]
        self.assertTrue(isinstance(socket, FakeSocket))
        self.assertEqual(3, socket.fileno())
        self.assertTrue(isinstance(session, FakeSession))
        self.assertEqual(socket, session.socket())

    def test_incoming_called(self):
        """
        Test the run calls handle_incoming when there's something on the
        socket.
        """
        socket = FakeSocket(3)
        self.ddns_server._socket_sessions = {3: (socket, FakeSession(socket))}
        self.ddns_server.handle_incoming = self.__hook
        self.__select_expected = ([1, 2, 3], [], [], None)
        self.__select_answer = ([3], [], [])
        self.ddns_server.run()
        self.assertTrue(self.ddns_server._shutdown)
        self.assertIsNone(self.__select_answer)
        self.assertEqual(3, self.__hook_called)

    def test_handle_incoming_ok(self):
        """
        Test the handle_incoming pops the session and calls handle_request
        when everything is OK.
        """
        socket = FakeSocket(3)
        session = FakeSession(socket)
        # It doesn't really matter what data we use here, it is only passed
        # through the code
        param = (FakeSocket(4), ('127.0.0.1', 1234), ('127.0.0.1', 1235),
                 'Some data')
        def pop():
            return param
        # Prepare data into the session
        session.pop = pop
        self.ddns_server._socket_sessions = {3: (socket, session)}
        self.ddns_server.handle_request = self.__hook
        # Call it
        self.ddns_server.handle_incoming(3)
        # The popped data are passed into the handle_request
        self.assertEqual(param, self.__hook_called)
        # The sessions are kept the same
        self.assertEqual({3: (socket, session)},
                         self.ddns_server._socket_sessions)

    def test_handle_incoming_fail(self):
        """
        Test the handle_incoming removes (and closes) the socket and session
        when the session complains.
        """
        socket = FakeSocket(3)
        session = FakeSession(socket)
        def pop():
            raise isc.util.io.socketsession.SocketSessionError('Test error')
        session.pop = pop
        socket.close = self.__hook
        self.__hook_called = False
        self.ddns_server._socket_sessions = {3: (socket, session)}
        self.ddns_server.handle_incoming(3)
        # The "dead" session is removed
        self.assertEqual({}, self.ddns_server._socket_sessions)
        # Close is called with no parameter, so the default None
        self.assertIsNone(self.__hook_called)

class TestMain(unittest.TestCase):
    def setUp(self):
        self._server = MyDDNSServer()

    def test_main(self):
        self.assertFalse(self._server.run_called)
        ddns.main(self._server)
        self.assertTrue(self._server.run_called)

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
