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

    def test_update_config(self):
        self.handler.update_config(self.FILE_LOG2.name, 3, 512)
        self.assertEqual(self.handler.baseFilename, self.FILE_LOG2.name)
        self.assertEqual(self.handler.maxBytes, 512)
        self.assertEqual(self.handler.backupCount, 3)

        dir = os.path.split(self.FILE_LOG3.name)                                        
        path = dir[0] + "path_not_exists"
        update_file = os.path.join(path, dir[1])

        if not os.path.exists(path):
            self.handler.update_config(update_file, 4, 1024)
            self.assertEqual(self.handler.baseFilename, self.FILE_LOG2.name)
            self.assertEqual(self.handler.maxBytes, 1024)
            self.assertEqual(self.handler.backupCount, 4)

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
        record = logging.LogRecord(None, None, "", 0, "syslog handler", (), None, None)
        self.handler.emit(record)


class TestLogging(unittest.TestCase):
    
    def setUp(self):
        self.FILE_STREAM_LOG1= tempfile.NamedTemporaryFile(mode='w',
                                                      prefix="b10",
                                                      delete=True)
        self.FILE_STREAM_LOG2= tempfile.NamedTemporaryFile(mode='w',
                                                      prefix="b10",
                                                      delete=True)
        self.FILE_STREAM_LOG3= tempfile.NamedTemporaryFile(mode='w',
                                                      prefix="b10",
                                                      delete=True)
        self.file_stream_logger = NSLogger('File_Stream_Logger',
                                           self.FILE_STREAM_LOG1.name,
                                           'debug', 5, 1024, True)
        self.syslog_logger = NSLogger('SysLogger', '', 'info', 5, 1024, False)
    
    def test_logging_init(self):
        self.assertNotEqual(self.file_stream_logger._file_handler, None)
        self.assertNotEqual(self.file_stream_logger._stream_handler, None)
        self.assertEqual(self.file_stream_logger._syslog_handler, None)

        ret = self.file_stream_logger._file_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)
        ret = self.file_stream_logger._stream_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)
        ret = self.file_stream_logger._syslog_handler in self.file_stream_logger.handlers
        self.assertFalse(ret)
        logLevel = LEVELS.get('debug', logging.NOTSET)
        self.assertEqual(self.file_stream_logger.getEffectiveLevel(), logLevel)

        self.assertEqual(self.syslog_logger._file_handler, None)
        self.assertEqual(self.syslog_logger._stream_handler, None)
        self.assertNotEqual(self.syslog_logger._syslog_handler, None)
        ret = self.syslog_logger._file_handler in self.syslog_logger.handlers
        self.assertFalse(ret)
        ret = self.syslog_logger._stream_handler in self.syslog_logger.handlers
        self.assertFalse(ret)
        ret = self.syslog_logger._syslog_handler in self.syslog_logger.handlers
        self.assertTrue(ret)

        logLevel = LEVELS.get('info', logging.NOTSET)
        self.assertEqual(self.syslog_logger.getEffectiveLevel(), logLevel)

    def test_add_rotate_handler(self):
        if(self.syslog_logger._file_handler in self.syslog_logger.handlers):
            self.syslog_logger.removeHandler(self.syslog_logger._file_handler)
        
        self.syslog_logger._add_rotate_handler('', 5, 1024)
        ret = self.syslog_logger._file_handler in self.syslog_logger.handlers
        self.assertFalse(ret)

        self.syslog_logger._add_rotate_handler(self.FILE_STREAM_LOG1.name, 5, 1024)
        ret = self.syslog_logger._file_handler in self.syslog_logger.handlers
        self.assertTrue(ret)

    def test_add_stream_handler(self):
        if(self.file_stream_logger._stream_handler in self.file_stream_logger.handlers):
            self.file_stream_logger.removeHandler(self.file_stream_logger._stream_handler)

        self.file_stream_logger._add_stream_handler()
        ret = self.file_stream_logger._stream_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)

    def test_add_syslog_handler(self):
        if(self.syslog_logger._syslog_handler in self.syslog_logger.handlers):
            self.syslog_logger.removeHandler(self.syslog_logger._syslog_handler)

        self.syslog_logger._add_syslog_handler()
        ret = self.syslog_logger._syslog_handler in self.syslog_logger.handlers
        self.assertTrue(ret)

    def test_update_rotate_handler(self):
        self.file_stream_logger._update_rotate_handler(self.FILE_STREAM_LOG2.name, 4, 1024)
        ret = self.file_stream_logger._file_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)

        self.file_stream_logger._update_rotate_handler('', 5, 1024)
        ret = self.file_stream_logger._file_handler in self.file_stream_logger.handlers
        self.assertFalse(ret)

        self.file_stream_logger._update_rotate_handler(self.FILE_STREAM_LOG1.name, 4, 1024)
        ret = self.file_stream_logger._file_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)

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
        self.file_stream_logger.log_message('info', 'info message')
        self.file_stream_logger.log_message('warning', 'warning message')
        self.file_stream_logger.log_message('error', 'error message')
        self.assertTrue(os.path.exists(self.FILE_STREAM_LOG3.name))
    
    def tearDown(self):
        self.FILE_STREAM_LOG1.close()
        self.FILE_STREAM_LOG2.close()
        self.FILE_STREAM_LOG3.close()

if __name__ == '__main__':
    unittest.main()
