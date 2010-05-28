from isc.log.log import *
import unittest
import os

class TestRotateFileHandler(unittest.TestCase):

    def setUp(self):
        self.handler = RotatingFileHandler('/var/log/rotate_file_handler.log', 1024, 5)

    def test_shouldRollover(self):
        if(os.path.exists('/var/log/rotate_file_handler.log')):
            os.remove('/var/log/rotate_file_handler.log')
        record = logging.LogRecord(None, None, "", 0, "rotate file handler", (), None, None)
        self.handler.shouldRollover(record)
        self.assertTrue(os.path.exists('/var/log/rotate_file_handler.log'))

    def test_update_config(self):
        self.handler.update_config('/var/log/rotate_file_handler2.log', 512, 3)
        self.assertEqual(self.handler.baseFilename, '/var/log/rotate_file_handler2.log')
        self.assertEqual(self.handler.maxBytes, 3)
        self.assertEqual(self.handler.backupCount, 512)


class TestLogging(unittest.TestCase):

    def setUp(self):
        self.file_stream_logger = ModuleLogger('File_Stream_Logger', '/var/log/FileStreamLogger.log',
                                               'debug', 5, 1024, True)
        self.syslog_logger = ModuleLogger('SysLogger', '', 'info', 5, 1024, False)

    def test_logging_init(self):
        self.assertNotEqual(self.file_stream_logger.null_handler, None)
        self.assertNotEqual(self.file_stream_logger.rotating_handler, None)
        self.assertNotEqual(self.file_stream_logger.stream_handler, None)
        self.assertEqual(self.file_stream_logger.syslog_handler, None)

        ret = self.file_stream_logger.null_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)
        ret = self.file_stream_logger.rotating_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)
        ret = self.file_stream_logger.stream_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)
        ret = self.file_stream_logger.syslog_handler in self.file_stream_logger.handlers
        self.assertFalse(ret)
        logLevel = LEVELS.get('debug', logging.NOTSET)
        self.assertEqual(self.file_stream_logger.getEffectiveLevel(), logLevel)

        self.assertNotEqual(self.syslog_logger.null_handler, None)
        self.assertEqual(self.syslog_logger.rotating_handler, None)
        self.assertEqual(self.syslog_logger.stream_handler, None)
        self.assertNotEqual(self.syslog_logger.syslog_handler, None)
        ret = self.syslog_logger.null_handler in self.syslog_logger.handlers
        self.assertTrue(ret)
        ret = self.syslog_logger.rotating_handler in self.syslog_logger.handlers
        self.assertFalse(ret)
        ret = self.syslog_logger.stream_handler in self.syslog_logger.handlers
        self.assertFalse(ret)
        ret = self.syslog_logger.syslog_handler in self.syslog_logger.handlers
        self.assertTrue(ret)

        logLevel = LEVELS.get('info', logging.NOTSET)
        self.assertEqual(self.syslog_logger.getEffectiveLevel(), logLevel)

    def test_add_null_handler(self):
        if(self.syslog_logger.null_handler in self.syslog_logger.handlers):
            self.syslog_logger.removeHandler(self.syslog_logger.null_handler)

        self.syslog_logger.add_null_handler()
        ret = self.syslog_logger.null_handler in self.syslog_logger.handlers
        self.assertTrue(ret)
    

    def test_add_rotate_handler(self):
        if(self.syslog_logger.rotating_handler in self.syslog_logger.handlers):
            self.syslog_logger.removeHandler(self.syslog_logger.rotating_handler)
        
        self.syslog_logger.add_rotate_handler('', 1024, 5)
        ret = self.syslog_logger.rotating_handler in self.syslog_logger.handlers
        self.assertFalse(ret)

        self.syslog_logger.add_rotate_handler('/var/log/RotateFile.log', 1024, 5)
        ret = self.syslog_logger.rotating_handler in self.syslog_logger.handlers
        self.assertTrue(ret)

    def test_add_stream_handler(self):
        if(self.file_stream_logger.stream_handler in self.file_stream_logger.handlers):
            self.file_stream_logger.removeHandler(self.file_stream_logger.stream_handler)

        self.file_stream_logger.add_stream_handler()
        ret = self.file_stream_logger.stream_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)

    def test_add_syslog_handler(self):
        if(self.syslog_logger.syslog_handler in self.syslog_logger.handlers):
            self.syslog_logger.removeHandler(self.syslog_logger.syslog_handler)

        self.syslog_logger.add_syslog_handler()
        ret = self.syslog_logger.syslog_handler in self.syslog_logger.handlers
        self.assertTrue(ret)

    def test_update_rotate_handler(self):
        self.file_stream_logger.update_rotate_handler('/var/log/RotateFile', 4, 1024)
        ret = self.file_stream_logger.rotating_handler in self.file_stream_logger.handlers
        self.assertTrue(ret)

        self.file_stream_logger.update_rotate_handler('', 5, 1024)
        ret = self.file_stream_logger.rotating_handler in self.file_stream_logger.handlers
        self.assertFalse(ret)

        self.file_stream_logger.update_rotate_handler('/var/log/RotateFile', 4, 1024)
        ret = self.file_stream_logger.rotating_handler in self.file_stream_logger.handlers
        self.assertFalse(ret)

    def test_update_config(self):
        self.file_stream_logger.update_config('/var/log/RotateFile','error', 4, 1024)
        logLevel = LEVELS.get('error', logging.NOTSET)
        self.assertEqual(self.file_stream_logger.getEffectiveLevel(), logLevel)

    def test_log_message(self):
        print ('\r')
        #output log message to stderr and file
        self.file_stream_logger.log_message('debug', 'Debug message')
        self.file_stream_logger.log_message('info', 'Info message')
        self.file_stream_logger.log_message('warning', 'Warning message')
        self.file_stream_logger.log_message('error', 'Error message')
        self.file_stream_logger.log_message('critical', 'Critical message')

        #output log message to syslog 
        self.syslog_logger.log_message('debug', 'Debug message')
        self.syslog_logger.log_message('info', 'Info message')
        self.syslog_logger.log_message('warning', 'Warning message')
        self.syslog_logger.log_message('error', 'Error message')
        self.syslog_logger.log_message('critical', 'Critical message')

if __name__ == '__main__':
    unittest.main()
