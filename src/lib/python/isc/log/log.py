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

"""This module is to convert python logging module over
to log4python.
Copyright (C) 2010  Internet Systems Consortium.
To use, simply 'import isc.log.log' and log away!
"""
import os
import syslog
import logging
import logging.handlers

"""LEVELS: logging levels mapping
"""
LEVELS = {'debug' : logging.DEBUG,
       	  'info' : logging.INFO,
          'warning' : logging.WARNING,
          'error' : logging.ERROR,
          'critical' : logging.CRITICAL}


FORMATTER = logging.Formatter("%(name)s: %(levelname)s: %(message)s")
TIME_FORMATTER = logging.Formatter("%(asctime)s.%(msecs)03d %(name)s: %(levelname)s: %(message)s",
                                   "%d-%b-%Y %H:%M:%S")

class NSFileLogHandler(logging.handlers.RotatingFileHandler):
    """RotatingFileHandler: replace RotatingFileHandler with a custom handler"""

    def __init__(self, filename, mode='a', maxBytes=0, backupCount=0, encoding=None, delay=0):
        dir = os.path.split(filename)
        if not (os.path.exists(dir[0])):
            os.makedirs(dir[0])
        super(NSFileLogHandler, self).__init__(filename, mode, maxBytes,
                                                backupCount, encoding, delay)

    def shouldRollover(self, record):
        """Rewrite RotatingFileHandler.shouldRollover. 
       
        If the log file is deleted at runtime, a new file will be created.
        """
        dfn = self.baseFilename                 
        if (self.stream) and (not os.path.exists(dfn)): #Is log file exist?
            self.stream.close()
            self.stream = self._open()
        return super(NSFileLogHandler, self).shouldRollover(record)
    
    def update_config(self, file_name, backup_count, max_bytes):
        """Update RotatingFileHandler configuration.

        If the file path is not exist, we will use the old log file.
        input:
            log file name
            max backup count
            predetermined log file size
        """
        dir = os.path.split(file_name)
        if(os.path.exists(dir[0])):
            self.baseFilename = file_name
        self.maxBytes = max_bytes
        self.backupCount = backup_count

class NSSysLogHandler(logging.Handler):    
    """Replace SysLogHandler with a custom handler 

    A handler class which sends formatted logging records to a syslog
    server.
    """
    def __init__(self, ident, logopt=0, facility=syslog.LOG_USER):        
        """Initialize a handler.
    
        If facility is not specified, LOG_USER is used.
        """
        super(NSSysLogHandler, self).__init__()
        self._ident = ident        
        self._logopt = logopt        
        self._facility = facility        
        self._mappings = {            
                logging.DEBUG: syslog.LOG_DEBUG,            
                logging.INFO: syslog.LOG_INFO,            
                logging.WARNING: syslog.LOG_WARNING,            
                logging.ERROR: syslog.LOG_ERR,            
                logging.CRITICAL: syslog.LOG_CRIT,            
                }   
        
    def _encodeLevel(self, level):        
        """Encoding the priority."""
        return self._mappings.get(level, syslog.LOG_INFO)    
   
    def emit(self, record):   
        """Emit a record.
     
        The record is formatted, and then sent to the syslog server. If
        exception information is present, it is NOT sent to the server.
        """
        syslog.openlog(self._ident, self._logopt, self._facility)        
        msg = self.format(record)        
        prio = self._encodeLevel(record.levelno)        
        syslog.syslog(prio, msg)        
        syslog.closelog()


class NSLogger(logging.getLoggerClass()):
    """Override logging.logger behaviour."""
    def __init__(self, log_name, log_file, severity='debug', versions=0,
                 max_bytes=0, log_to_console=True):
        """Initializes the logger with some specific parameters

        If log_to_console is True, stream handler will be used;
        else syslog handler will be used.

        To disable file handler, set log_file = ''.
        """
        self._log_name = log_name
        self._log_file = log_file
        self._severity = severity
        self._versions = versions
        self._max_bytes = max_bytes

        super(NSLogger, self).__init__(self._log_name)

        # Set up a specific logger with our desired output level
        logLevel = LEVELS.get(self._severity, logging.NOTSET)
        self.setLevel(logLevel)

        self._file_handler = None
        self._stream_handler = None
        self._syslog_handler = None

        self._add_rotate_handler(self._log_file, self._versions, self._max_bytes)
        if log_to_console:
            self._add_stream_handler()
        else:
            self._add_syslog_handler()

    def _add_rotate_handler(self, log_file, backup_count, max_bytes):
        """Add a rotate file handler.
   
        input:
            log_file : the location of log file. Handler wouldn't be created 
                       if log_file=''
            max_bytes : limit log growth
            backup_count : max backup count
        """
        if(log_file != 0  and log_file != ''):
            try:
                self._file_handler = NSFileLogHandler(filename = log_file,
                                          maxBytes = max_bytes, backupCount = backup_count)
            except IOError:
                self._file_handler = None
                return
            self._file_handler.setFormatter(TIME_FORMATTER)
            self.addHandler(self._file_handler)

    def _add_stream_handler(self):
        """Add a stream handler.
    
        sys.stderr will be used for logging output.
        """
        self._stream_handler = logging.StreamHandler()
        self._stream_handler.setFormatter(TIME_FORMATTER)
        self.addHandler(self._stream_handler)

    def _add_syslog_handler(self, facility=syslog.LOG_USER):
        """Add a syslog handler.
   
        If facility is not specified, LOG_USER is used.
        The default severity level is INFO.
        """
        self._syslog_handler = NSSysLogHandler('BIND10', facility)
        self._syslog_handler.setFormatter(FORMATTER)
        #set syslog handler severity level INFO
        self._syslog_handler.setLevel(logging.INFO)
        self.addHandler(self._syslog_handler)

    def _update_rotate_handler(self, log_file, backup_count, max_bytes):
        """If the rotate file handler has been added to the logger, update its 
        configuration, or add it to the logger.
        """
        if (self._file_handler in self.handlers):
            if(log_file != 0 and log_file != ''):
                self._file_handler.update_config(log_file, backup_count, max_bytes)
            else:
                """If log file is empty, the handler will be removed."""
                self._file_handler.flush()
                self._file_handler.close()
                self.removeHandler(self._file_handler)
        else:
            self._add_rotate_handler(log_file, backup_count, max_bytes)

    def _get_config(self, config_data):
         """Get config data from module configration"""
         
         log_file_str = config_data.get('log_file')
         if(log_file_str):
            self._log_file = log_file_str
         
         severity_str = config_data.get('log_severity')
         if(severity_str):
             self._severity = severity_str

         versions_str = config_data.get('log_versions')
         if(versions_str):
             self._versions = int(versions_str)

         max_bytes_str = config_data.get('log_max_bytes')
         if(max_bytes_str):
             self._max_bytes = int(max_bytes_str)

    def update_config(self, config_data):
        """Update logger's configuration.

        We can update logger's log level and its rotate file handler's configuration.
        """
        self._get_config(config_data)

        logLevel = LEVELS.get(self._severity, logging.NOTSET)
        if(logLevel != self.getEffectiveLevel()):
            self.setLevel(logLevel)
        self._update_rotate_handler(self._log_file, self._versions, self._max_bytes)

    def log_message(self, level, msg, *args, **kwargs):
        """Log 'msg % args' with the integer severity 'level'.
     
        To pass exception information, use the keyword argument exc_info with
        a true value, e.g.
  
        logger.log_message('info', "We have a %s", "mysterious problem").
        """
        logLevel = LEVELS.get(level, logging.NOTSET)
        self.log(logLevel, msg, *args, **kwargs)


