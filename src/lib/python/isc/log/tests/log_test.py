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
# Tests for the python logging module
#

from isc.log.log import *
import unittest
import os
import sys
import tempfile


class TestRotateFileHandler(unittest.TestCase):

    def setUp(self):
        self.FILE_LOG1 = tempfile.NamedTemporaryFile(mode='w',
                                                 prefix="b10",
                                                 delete=True)
        self.FILE_LOG2 = tempfile.NamedTemporaryFile(mode='w',
                                                 prefix="b10",
                                                 delete=True)
        self.FILE_LOG3 = tempfile.NamedTemporaryFile(mode='w',
                                                 prefix="b10",
                                                 delete=True)
        self.handler = NSFileLogHandler(filename = self.FILE_LOG1.name, 
                                        maxBytes = 1024, 
                                        backupCount = 5)

    def test_shouldRollover(self):
        if(os.path.exists(self.FILE_LOG1.name)):
            os.remove(self.FILE_LOG1.name)
        record = logging.LogRecord(None, None, "", 0, "rotate file handler", (), None, None)
        self.handler.shouldRollover(record)
        self.assertTrue(os.path.exists(self.FILE_LOG1.name))

    def test_get_absolute_file_path(self):
        abs_file_name = self.handler._get_abs_file_path(self.FILE_LOG1.name)
        self.assertEqual(abs_file_name, self.FILE_LOG1.name)
        # test bare filename
        file_name1 = "bind10.py"
        abs_file_name = self.handler._get_abs_file_path(file_name1)
        self.assertEqual(abs_file_name, os.path.join(os.getcwd(), file_name1))
        # test relative path 
        file_name2 = "./bind10.py"
        abs_file_name = self.handler._get_abs_file_path(file_name2)
        self.assertEqual(abs_file_name, os.path.join(os.getcwd(), os.path.basename(file_name2)))
         
    def test_update_config(self):
        self.handler.update_config(self.FILE_LOG2.name, 3, 512)
        self.assertEqual(self.handler.baseFilename, self.FILE_LOG2.name)
        self.assertEqual(self.handler.maxBytes, 512)
        self.assertEqual(self.handler.backupCount, 3)

        # check the existence of new log file.
        # emit() will call shouldRollover() to update the log file
        if(os.path.exists(self.FILE_LOG2.name)):
            os.remove(self.FILE_LOG2.name)
        record = logging.LogRecord(None, None, "", 0, "rotate file handler", (), None, None)
        self.handler.emit(record)
        self.assertTrue(os.path.exists(self.FILE_LOG2.name))

    def test_handle_Error(self):
        if(os.path.exists(self.FILE_LOG3.name)):
            os.remove(self.FILE_LOG3.name)
        # redirect error message to file
        savederr = sys.stderr
        errfd = open(self.FILE_LOG3.name, 'w+')
        sys.stderr = errfd
        record = logging.LogRecord(None, None, "", 0, "record message", (), None, None)
        try:
            raise ValueError("ValueError")
        except ValueError:
            self.handler.handleError(record)

        self.assertEqual("[b10-logging] : ValueError", errfd.read())
        sys.stderr = savederr
        errfd.close()

    def tearDown(self):
        self.handler.flush()
        self.handler.close()
        self.FILE_LOG1.close()
        self.FILE_LOG2.close()
        self.FILE_LOG3.close()

class TestSysLogHandler(unittest.TestCase):
    def setUp(self):
        self.handler = NSSysLogHandler("BIND10")

    def test_encodeLevel(self):
        sysLevel = self.handler._encodeLevel(logging.ERROR)
        self.assertEqual(sysLevel, syslog.LOG_ERR)

    def test_emit(self):
        syslog_message = "bind10 syslog testing"
        record = logging.LogRecord(None, None, "", 0, syslog_message, (), None, None)
        self.handler.emit(record)

class TestLogging(unittest.TestCase):
    
    def setUp(self):
        self.FILE_STREAM_LOG1 = tempfile.NamedTemporaryFile(mode='w',
                                                      prefix="b10",
                                                      delete=True)
        self.FILE_STREAM_LOG2 = tempfile.NamedTemporaryFile(mode='w',
                                                      prefix="b10",
                                                      delete=True)
        self.FILE_STREAM_LOG3 = tempfile.NamedTemporaryFile(mode='w',
                                                      prefix="b10",
                                                      delete=True)
        self.file_stream_logger = NSLogger('File_Stream_Logger',
                                           self.FILE_STREAM_LOG1.name,
                                           'debug', 5, 1024, True)
        self.syslog_logger = NSLogger('SysLogger', '', 'info', 5, 1024, False)
        self.stderr_bak = sys.stderr
        sys.stderr = open(os.devnull, 'w')
    
    def test_logging_init(self):
        self.assertNotEqual(self.file_stream_logger._file_handler, None)
        self.assertNotEqual(self.file_stream_logger._stream_handler, None)
        self.assertEqual(self.file_stream_logger._syslog_handler, None)

        self.assertIn(self.file_stream_logger._file_handler, self.file_stream_logger.handlers)
        self.assertIn(self.file_stream_logger._stream_handler, self.file_stream_logger.handlers)
        self.assertNotIn(self.file_stream_logger._syslog_handler, self.file_stream_logger.handlers)
        logLevel = LEVELS.get('debug', logging.NOTSET)
        self.assertEqual(self.file_stream_logger.getEffectiveLevel(), logLevel)

        self.assertEqual(self.syslog_logger._file_handler, None)
        self.assertEqual(self.syslog_logger._stream_handler, None)
        self.assertNotEqual(self.syslog_logger._syslog_handler, None)
        self.assertNotIn(self.syslog_logger._file_handler, self.syslog_logger.handlers)
        self.assertNotIn(self.syslog_logger._stream_handler, self.syslog_logger.handlers)
        self.assertIn(self.syslog_logger._syslog_handler, self.syslog_logger.handlers)

        logLevel = LEVELS.get('info', logging.NOTSET)
        self.assertEqual(self.syslog_logger.getEffectiveLevel(), logLevel)

    def test_add_rotate_handler(self):
        if(self.syslog_logger._file_handler in self.syslog_logger.handlers):
            self.syslog_logger.removeHandler(self.syslog_logger._file_handler)
        
        self.syslog_logger._add_rotate_handler('', 5, 1024)
        self.assertNotIn(self.syslog_logger._file_handler, self.syslog_logger.handlers)

        self.syslog_logger._add_rotate_handler(self.FILE_STREAM_LOG1.name, 5, 1024)
        self.assertIn(self.syslog_logger._file_handler, self.syslog_logger.handlers)

        # test IOError exception
        self.syslog_logger.removeHandler(self.syslog_logger._file_handler)
        log_file = self.FILE_STREAM_LOG1.name + '/logfile'
        self.syslog_logger._add_rotate_handler(log_file, 5, 1024)
        self.assertNotIn(self.syslog_logger._file_handler, self.syslog_logger.handlers)

    def test_add_stream_handler(self):
        if(self.file_stream_logger._stream_handler in self.file_stream_logger.handlers):
            self.file_stream_logger.removeHandler(self.file_stream_logger._stream_handler)

        self.file_stream_logger._add_stream_handler()
        self.assertIn(self.file_stream_logger._stream_handler, self.file_stream_logger.handlers)

    def test_add_syslog_handler(self):
        if(self.syslog_logger._syslog_handler in self.syslog_logger.handlers):
            self.syslog_logger.removeHandler(self.syslog_logger._syslog_handler)

        self.syslog_logger._add_syslog_handler()
        self.assertIn(self.syslog_logger._syslog_handler, self.syslog_logger.handlers)

    def test_update_rotate_handler(self):
        self.file_stream_logger._update_rotate_handler(self.FILE_STREAM_LOG2.name, 4, 1024)
        self.assertIn(self.file_stream_logger._file_handler, self.file_stream_logger.handlers)

        self.file_stream_logger._update_rotate_handler('', 5, 1024)
        self.assertNotIn(self.file_stream_logger._file_handler, self.file_stream_logger.handlers)

        self.file_stream_logger._update_rotate_handler(self.FILE_STREAM_LOG1.name, 4, 1024)
        self.assertIn(self.file_stream_logger._file_handler, self.file_stream_logger.handlers)

    def test_get_config(self):
        config_data = {'log_file' : self.FILE_STREAM_LOG1.name,
                       'log_severity' : 'critical',
                       'log_versions' : 4,
                       'log_max_bytes' : 1024}
        self.file_stream_logger._get_config(config_data)
        self.assertEqual(self.file_stream_logger._log_file, self.FILE_STREAM_LOG1.name)
        self.assertEqual(self.file_stream_logger._severity, 'critical')
        self.assertEqual(self.file_stream_logger._versions, 4)
        self.assertEqual(self.file_stream_logger._max_bytes, 1024)


    def test_update_config(self):
        update_config = {'log_file' : self.FILE_STREAM_LOG1.name,
                         'log_severity' : 'error',
                         'log_versions' : 4,
                         'log_max_bytes' : 1024}
        self.file_stream_logger.update_config(update_config)
        logLevel = LEVELS.get('error', logging.NOTSET)
        self.assertEqual(self.file_stream_logger.getEffectiveLevel(), logLevel)

    def test_log_message(self):
        update_config = {'log_file' : self.FILE_STREAM_LOG3.name,
                         'log_severity' : 'critical',
                         'log_versions' : 4,
                         'log_max_bytes' : 1024}
        self.file_stream_logger.update_config(update_config)
        self.file_stream_logger.log_message('debug', 'debug message')
        self.file_stream_logger.log_message('warning', 'warning message')
        self.file_stream_logger.log_message('error', 'error message')
        #test non-exist log level
        self.assertRaises(None, self.file_stream_logger.log_message('not-exist', 'not exist message'))
        #test log_message KeyError exception
        self.assertRaises(None, self.file_stream_logger.log_message('critical', 'critical message', extra=['message', 'asctime']))
        self.assertTrue(os.path.exists(self.FILE_STREAM_LOG3.name))
    
    def tearDown(self):
        self.FILE_STREAM_LOG1.close()
        self.FILE_STREAM_LOG2.close()
        self.FILE_STREAM_LOG3.close()
        sys.stderr.flush();
        sys.stderr = self.stderr_bak

if __name__ == '__main__':
    unittest.main()
