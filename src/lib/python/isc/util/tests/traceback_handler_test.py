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
import isc.log
import isc.util.traceback_handler

class HandlerTest(unittest.TestCase):
    def setUp(self):
        """
        Save some things to be restored later, if we overwrite them
        for tests.
        """
        self.exit = isc.util.traceback_handler.sys.exit
        self.logger = isc.util.traceback_handler.logger
        # Sanity check - the functions exist.
        self.assertTrue(self.exit)
        self.assertTrue(self.logger)

    def tearDown(self):
        """
        Restore mocked things.
        """
        isc.util.traceback_handler.sys.exit = self.exit
        isc.util.traceback_handler.logger = self.logger

    def test_success(self):
        """
        Test the handler doesn't influence the result of successful
        function.
        """
        def succ():
            return 42

        self.assertEqual(42,
                         isc.util.traceback_handler.traceback_handler(succ))

    def test_exception(self):
        """
        Test the exception is caught and logged, but not propagated.
        """
        # Mock up bunch of things
        self.exited = False
        def exit(status):
            self.assertEqual(1, status)
            self.exited = True
        isc.util.traceback_handler.sys.exit = exit
        self.logged = False
        obj = self
        class Logger:
            def fatal(self, message, ename, exception, filename):
                obj.assertTrue(isinstance(exception, Exception))
                obj.assertEqual('Exception', ename)
                with open(filename) as f:
                    text = f.read()
                obj.assertTrue(text.startswith('Traceback'))
                os.remove(filename)
                obj.logged = True
        isc.util.traceback_handler.logger = Logger()
        # The failing function
        def fail():
            raise Exception('Anybody there?')
        # Does not raise, but returns nothing
        self.assertIsNone(isc.util.traceback_handler.traceback_handler(fail))
        # It logged and exited (sane values for those are checked in the mocks)
        self.assertTrue(self.exited)
        self.assertTrue(self.logged)

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
