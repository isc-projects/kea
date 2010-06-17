from isc.log.log import *
import unittest
import os
import sys
import tempfile


class TestRotateFileHandler(unittest.TestCase):

    def setUp(self):
        self.FILE_LOG1 = tempfile.mkstemp()
        self.FILE_LOG2 = tempfile.mkstemp()
        self.FILE_LOG3 = tempfile.mkstemp()
        self.handler = NSFileLogHandler(filename = self.FILE_LOG1[1], maxBytes = 1024, backupCount = 5)

    def test_shouldRollover(self):
        if(os.path.exists(self.FILE_LOG1[1])):
            os.remove(self.FILE_LOG1[1])
        record = logging.LogRecord(None, None, "", 0, "rotate file handler", (), None, None)
        self.handler.shouldRollover(record)
        self.assertTrue(os.path.exists(self.FILE_LOG1[1]))

    def test_update_config(self):
        self.handler.update_config(self.FILE_LOG2[1], 3, 512)
        self.assertEqual(self.handler.baseFilename, self.FILE_LOG2[1])
        self.assertEqual(self.handler.maxBytes, 512)
        self.assertEqual(self.handler.backupCount, 3)

        dir = os.path.split(self.FILE_LOG3[1])                                        
        path = dir[0] + "path_not_exists"
        update_file = os.path.join(path, dir[1])

        if not os.path.exists(path):
            self.handler.update_config(update_file, 4, 1024)
            self.assertEqual(self.handler.baseFilename, self.FILE_LOG2[1])
            self.assertEqual(self.handler.maxBytes, 1024)
            self.assertEqual(self.handler.backupCount, 4)

    def tearDown(self):
        os.close(self.FILE_LOG1[0])
        os.close(self.FILE_LOG2[0])
        os.unlink(self.FILE_LOG1[1])
        os.unlink(self.FILE_LOG2[1])
        self.handler.flush()
        self.handler.close()


class TestLogging(unittest.TestCase):
    
    def setUp(self):
        self.FILE_STREAM_LOG1 = tempfile.mkstemp()
        self.FILE_STREAM_LOG2 = tempfile.mkstemp()
        self.FILE_STREAM_LOG3 = tempfile.mkstemp()
        self.file_stream_logger = NSLogger('File_Stream_Logger', self.FILE_STREAM_LOG1[1],
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

        self.syslog_logger._add_rotate_handler(self.FILE_STREAM_LOG1[1], 5, 1024)
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
        self.file_stream_logger._update_rotate_handler(self.FILE_STREAM_LOG2[1], 4, 1024)
        ret = self.file_stream_logger._file_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)

        self.file_stream_logger._update_rotate_handler('', 5, 1024)
        ret = self.file_stream_logger._file_handler in self.file_stream_logger.handlers
        self.assertFalse(ret)

        self.file_stream_logger._update_rotate_handler(self.FILE_STREAM_LOG1[1], 4, 1024)
        ret = self.file_stream_logger._file_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)

    def test_update_config(self):
        update_config = {'log_file' : self.FILE_STREAM_LOG1[1],
                         'log_severity' : 'error',
                         'log_versions' : 4,
                         'log_max_bytes' : 1024}
        self.file_stream_logger.update_config(update_config)
        logLevel = LEVELS.get('error', logging.NOTSET)
        self.assertEqual(self.file_stream_logger.getEffectiveLevel(), logLevel)

    def test_log_message(self):
        update_config = {'log_file' : self.FILE_STREAM_LOG3[1],
                         'log_severity' : 'critical',
                         'log_versions' : 4,
                         'log_max_bytes' : 1024}
        self.file_stream_logger.update_config(update_config)
        self.file_stream_logger.log_message('debug', 'debug message')
        self.file_stream_logger.log_message('info', 'info message')
        self.file_stream_logger.log_message('warning', 'warning message')
        self.file_stream_logger.log_message('error', 'error message')
        self.assertTrue(os.path.exists(self.FILE_STREAM_LOG3[1]))
    
    def tearDown(self):
        os.close(self.FILE_STREAM_LOG1[0])
        os.unlink(self.FILE_STREAM_LOG1[1])
        os.close(self.FILE_STREAM_LOG2[0])
        os.unlink(self.FILE_STREAM_LOG2[1])
        os.close(self.FILE_STREAM_LOG3[0])
        os.unlink(self.FILE_STREAM_LOG3[1])

if __name__ == '__main__':
    unittest.main()
