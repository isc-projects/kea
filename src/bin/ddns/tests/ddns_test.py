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

class FakeSocket:
    """
    A fake socket. It only provides a file number.
    """
    def __init__(self, fileno):
        self.__fileno = fileno
    def fileno(self):
        return self.__fileno

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
        self.assertTrue(cc_session._started)
        self.__select_expected = None
        self.__select_answer = None
        self.__hook_called = False

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

    def __hook(self):
        """
        A hook that can be installed to any unary function and see if it was
        really called.
        """
        self.__hook_called = True

    def test_accept_called(self):
        """
        Test we call the accept function when a new connection comes.
        """
        self.ddns_server._listen_socket = FakeSocket(2)
        ddns.select.select = self.__select
        self.ddns_server.accept = self.__hook
        self.__select_expected = ([1, 2], [], [], None)
        self.__select_answer = ([2], [], [])
        self.ddns_server.run()
        self.assertTrue(self.ddns_server._shutdown)
        # The answer got used
        self.assertIsNone(self.__select_answer)
        self.assertTrue(self.__hook_called)
        ddns.select.select = select.select

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
