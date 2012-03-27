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

# Make sure we can load the module, put it into path
import sys
import os
sys.path.extend(os.environ["B10_TEST_PLUGIN_DIR"].split(':'))

import b10logging
import unittest

class LoggingConfCheckTest(unittest.TestCase):
    def test_load(self):
        """
        Checks the entry point returns the correct values.
        """
        (spec, check) = b10logging.load()
        # It returns the checking function
        self.assertEqual(check, b10logging.check)
        # The plugin stores it's spec
        self.assertEqual(spec, b10logging.spec)

    def test_logger_conf(self):
        self.assertEqual(None,
                         b10logging.check({'loggers':
                                          [{'name': '*',
                                            'severity': 'DEBUG',
                                            'debuglevel': 50,
                                            'output_options':
                                            [{'destination': 'file',
                                              'output': '/some/file'
                                            }]
                                           },
                                           {'name': 'b10-resolver',
                                            'severity': 'WARN',
                                            'additive': True,
                                            'output_options':
                                            [{'destination': 'console',
                                              'output': 'stderr',
                                              'flush': True
                                            }]
                                           },
                                           {'name': 'b10-resolver.resolver',
                                            'severity': 'ERROR',
                                            'output_options': []
                                           },
                                           {'name': '*.cache',
                                            'severity': 'INFO'
                                           }
                                          ]}))
    def do_bad_name_test(self, name):
        err_str = "Bad logger name: '" + name + "': * can only be "\
                  "used instead of the full first-level name, e.g. "\
                  "'*' or '*.subsystem'"
        self.assertEqual(err_str,
                         b10logging.check({'loggers':
                                          [{'name': name,
                                            'severity': 'DEBUG'},
                                          ]}))
        
    def test_logger_bad_name(self):
        self.do_bad_name_test("*.")
        self.do_bad_name_test("*foo")
        self.do_bad_name_test("*foo.lib")
        self.do_bad_name_test("foo*")
        self.do_bad_name_test("foo*.lib")

    def test_logger_bad_severity(self):
        self.assertEqual('bad severity value for logger *: BADVAL',
                         b10logging.check({'loggers':
                                          [{'name': '*',
                                            'severity': 'BADVAL'}]}))

    def test_logger_bad_destination(self):
        self.assertEqual('bad destination for logger *: baddest',
                         b10logging.check({'loggers':
                                          [{'name': '*',
                                            'severity': 'INFO',
                                            'output_options': [
                                            { 'destination': 'baddest' }
                                            ]}]}))

    def test_logger_bad_console_output(self):
        self.assertEqual('bad output for logger *: bad_output, must be stdout or stderr',
                         b10logging.check({'loggers':
                                          [{'name': '*',
                                            'severity': 'INFO',
                                            'output_options': [
                                            { 'destination': 'console',
                                              'output': 'bad_output'
                                            }
                                            ]}]}))

    def test_logger_bad_file_output(self):
        self.assertEqual('destination set to file but output not set to any filename for logger *',
                         b10logging.check({'loggers':
                                          [{'name': '*',
                                            'severity': 'INFO',
                                            'output_options': [
                                            { 'destination': 'file' }
                                            ]}]}))

    def test_logger_bad_syslog_output(self):
        self.assertEqual('destination set to syslog but output not set to any facility for logger *',
                         b10logging.check({'loggers':
                                          [{'name': '*',
                                            'severity': 'INFO',
                                            'output_options': [
                                            { 'destination': 'syslog' }
                                            ]}]}))

    def test_logger_bad_type(self):
        self.assertEqual('123 should be a string',
                         b10logging.check({'loggers':
                                          [{'name': 123,
                                            'severity': 'INFO'}]}))
        self.assertEqual('123 should be a string',
                         b10logging.check({'loggers':
                                          [{'name': 'bind10',
                                            'severity': 123}]}))

if __name__ == '__main__':
        unittest.main(verbosity=2)
