# Copyright (C) 2013  Internet Systems Consortium.
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

import unittest
import os
import signal

import isc.log
import isc.config
from isc.server_common.bind10_server import *
from isc.testutils.ccsession_mock import MockModuleCCSession

class TestException(Exception):
    """A generic exception class specific in this test module."""
    pass

class MyCCSession(MockModuleCCSession, isc.config.ConfigData):
    def __init__(self, specfile, config_handler, command_handler):
        pass

class MockServer(BIND10Server):
    def _setup_ccsession(self):
        orig_cls = isc.config.ModuleCCSession
        isc.config.ModuleCCSession = MyCCSession
        try:
            super()._setup_ccsession()
        except Exception:
            raise
        finally:
            isc.config.ModuleCCSession = orig_cls

class TestBIND10Server(unittest.TestCase):
    def setUp(self):
        self.__server = MockServer()

    def test_init(self):
        """Check initial conditions"""
        self.assertFalse(self.__server.shutdown)

    def test_trigger_shutdown(self):
        self.__server._trigger_shutdown()
        self.assertTrue(self.__server.shutdown)

    def test_sigterm_handler(self):
        """Check the signal handler behavior.

        SIGTERM and SIGINT should be caught and should call memmgr's
        _trigger_shutdown().  This test also indirectly confirms main() calls
        run_internal().

        """
        def checker():
            self.__shutdown_called = True

        self.__server._run_internal = lambda: os.kill(os.getpid(),
                                                      signal.SIGTERM)
        self.__server._trigger_shutdown = lambda: checker()
        self.assertEqual(0, self.__server.run('test'))
        self.assertTrue(self.__shutdown_called)

        self.__shutdown_called = False
        self.__server._run_internal = lambda: os.kill(os.getpid(),
                                                      signal.SIGINT)
        self.assertEqual(0, self.__server.run('test'))
        self.assertTrue(self.__shutdown_called)

    def test_exception(self):
        """Check exceptions are handled, not leaked."""
        def exception_raiser(ex_cls):
            raise ex_cls('test')

        # Test all possible exceptions that are explicitly caught
        for ex in [TestException]:
            self.__server._run_internal = lambda: exception_raiser(ex)
            self.assertEqual(1, self.__server.run('test'))

if __name__== "__main__":
    isc.log.init("bind10_server_test")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
