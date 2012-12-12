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

# This tests it can be loaded, nothing more yet
import isc.log
import unittest
import json
import sys
import bind10_config
from isc.config.ccsession import path_search

class LogDict(unittest.TestCase):
    def setUp(self):
        # We work on a test dictionary now.
        isc.log.set_test_dictionary(True)
    def tearDown(self):
        # Return to the global dictionary
        isc.log.set_test_dictionary(False)

    def test_load_msgs(self):
        # Try loading a message and see it's there, but nothing more
        self.assertEqual(isc.log.create_message("ID", "Text"), "ID")
        self.assertEqual(isc.log.get_message("ID"), "Text")
        self.assertEqual(isc.log.get_message("no-ID"), None)

class Manager(unittest.TestCase):
    def tearDown(self):
        isc.log.reset()

    def test_init_debug(self):
        # We try calling it now only, as we don't have any other functions
        # to check the outcome by it. Once we add the logger class, we may
        # check more.
        isc.log.init("root", "DEBUG", 50, None)

    def test_init_defaults(self):
        # We try calling it now only, as we don't have any other functions
        # to check the outcome by it. Once we add the logger class, we may
        # check more.
        isc.log.init("root")

    def test_init_notfound(self):
        # This should not throw, because the C++ one doesn't. Should we really
        # ignore errors like missing file?
        isc.log.init("root", "INFO", 0, "/no/such/file");

    def test_init_keywords(self):
        isc.log.init(name="root", severity="DEBUG", debuglevel=50, file=None,
                     buffer=True)
        # unknown keyword
        self.assertRaises(TypeError, isc.log.init, name="root", foo="bar")
        # Replace the values for each keyword by a wrong type, one by one
        self.assertRaises(TypeError, isc.log.init, name=1,
                          severity="DEBUG", debuglevel=50, file=None,
                          buffer=True)
        self.assertRaises(TypeError, isc.log.init, name="root",
                          severity=2, debuglevel=50, file=None,
                          buffer=True)
        self.assertRaises(TypeError, isc.log.init, name="root",
                          severity="DEBUG", debuglevel="50", file=None,
                          buffer=True)
        self.assertRaises(TypeError, isc.log.init, name="root",
                          severity="DEBUG", debuglevel=50, file=1,
                          buffer=True)
        self.assertRaises(TypeError, isc.log.init, name="root",
                          severity="DEBUG", debuglevel=50, file=None,
                          buffer=None)

    def test_log_config_update(self):
        log_spec = json.dumps(isc.config.module_spec_from_file(path_search('logging.spec', bind10_config.PLUGIN_PATHS)).get_full_spec())

        self.assertRaises(TypeError, isc.log.log_config_update)
        self.assertRaises(TypeError, isc.log.log_config_update, 1)
        self.assertRaises(TypeError, isc.log.log_config_update, 1, 1)
        self.assertRaises(TypeError, isc.log.log_config_update, 1, 1, 1)

        self.assertRaises(TypeError, isc.log.log_config_update, 1, log_spec)
        self.assertRaises(TypeError, isc.log.log_config_update, [], log_spec)
        self.assertRaises(TypeError, isc.log.log_config_update, "foo", log_spec)
        self.assertRaises(TypeError, isc.log.log_config_update, "{ '", log_spec)

        # empty should pass
        isc.log.log_config_update("{}", log_spec)

        # bad spec
        self.assertRaises(TypeError, isc.log.log_config_update, "{}", json.dumps({"foo": "bar"}))

        # Try a correct one
        log_conf = json.dumps({"loggers":
                                [{"name": "b10-xfrout", "output_options":
                                    [{"output": "/tmp/bind10.log",
                                       "destination": "file",
                                       "flush": True}]}]})
        isc.log.log_config_update(log_conf, log_spec)

class Logger(unittest.TestCase):
    def tearDown(self):
        isc.log.reset()

    def setUp(self):
        isc.log.init("root", "DEBUG", 50)
        self.sevs = ['INFO', 'WARN', 'ERROR', 'FATAL']
        self.TEST_MSG = isc.log.create_message('TEST_MESSAGE', '%1')

    # Checks defaults of the logger
    def defaults(self, logger):
        self.assertEqual(logger.get_effective_severity(), "DEBUG")
        self.assertEqual(logger.get_effective_debug_level(), 50)

    def test_default_severity(self):
        logger = isc.log.Logger("child")
        self.defaults(logger)

    # Try changing the severities little bit
    def test_severity(self):
        logger = isc.log.Logger("child")
        logger.set_severity('DEBUG', 25)
        self.assertEqual(logger.get_effective_severity(), "DEBUG")
        self.assertEqual(logger.get_effective_debug_level(), 25)
        for sev in self.sevs:
            logger.set_severity(sev)
            self.assertEqual(logger.get_effective_severity(), sev)
            self.assertEqual(logger.get_effective_debug_level(), 0)
        # Return to default
        logger.set_severity(None)
        self.defaults(logger)

    def test_enabled(self):
        logger = isc.log.Logger("child")
        self.sevs.insert(0, 'DEBUG')
        methods = {
            'DEBUG': logger.is_debug_enabled,
            'INFO': logger.is_info_enabled,
            'WARN': logger.is_warn_enabled,
            'ERROR': logger.is_error_enabled,
            'FATAL': logger.is_fatal_enabled
        }
        for sev in self.sevs:
            logger.set_severity(sev)
            enabled = False
            for tested in self.sevs:
                if tested == sev:
                    enabled = True
                self.assertEqual(methods[tested](), enabled)
        logger.set_severity('DEBUG', 50)
        self.assertTrue(logger.is_debug_enabled())
        self.assertTrue(logger.is_debug_enabled(0))
        self.assertTrue(logger.is_debug_enabled(50))
        self.assertFalse(logger.is_debug_enabled(99))

    def test_invalid_params(self):
        """
           Tests invalid arguments for logging functions. The output is tested
           in check_output.sh.
        """
        logger = isc.log.Logger("child")
        methods = [
            logger.info,
            logger.warn,
            logger.error,
            logger.fatal
        ]
        for meth in methods:
            # Not enough arguments
            self.assertRaises(TypeError, meth)
            # Bad type
            self.assertRaises(TypeError, meth, 1)
        # Too few arguments
        self.assertRaises(TypeError, logger.debug, 42)
        self.assertRaises(TypeError, logger.debug)
        # Bad type
        self.assertRaises(TypeError, logger.debug, "42", "hello")

    def test_dbglevel_constants(self):
        """
            Just check a constant to make sure it is defined and is the
            correct value.  (The constant chosen has a non-zero value to
            ensure that the code has both define the constant and set its
            value correctly.)
        """
        logger = isc.log.Logger("child")
        self.assertEqual(logger.DBGLVL_COMMAND, 10)

    def test_param_reference(self):
        """
        Check whether passing a parameter to a logger causes a reference leak.
        """
        class LogParam:
            def __str__(self):
                return 'LogParam'
        logger = isc.log.Logger("child")
        param = LogParam()
        orig_msgrefcnt = sys.getrefcount(param)
        orig_idrefcnt = sys.getrefcount(self.TEST_MSG)
        logger.info(self.TEST_MSG, param);
        self.assertEqual(sys.getrefcount(self.TEST_MSG), orig_idrefcnt)
        self.assertEqual(sys.getrefcount(param), orig_msgrefcnt)

        # intentionally pass an invalid type for debug level.  It will
        # result in TypeError.  The passed object still shouldn't leak a
        # reference.
        self.assertRaises(TypeError, logger.debug, param, self.TEST_MSG, param)
        self.assertEqual(sys.getrefcount(param), orig_msgrefcnt)

    def test_bad_parameter(self):
        # a log parameter cannot be converted to a string object.
        class LogParam:
            def __str__(self):
                raise ValueError("LogParam can't be converted to string")
        logger = isc.log.Logger("child")
        self.assertRaises(ValueError, logger.info, self.TEST_MSG, LogParam())

if __name__ == '__main__':
    unittest.main()
