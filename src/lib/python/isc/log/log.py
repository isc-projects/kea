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

"""
This module is to convert python logging module over
to log4python.
Copyright (C) 2010  Internet Systems Consortium.
To use, simply 'import isc.log.log' and log away!
"""
import os
import syslog
import logging
import logging.handlers

"""
LEVELS: logging levels mapping
"""
LEVELS = {'debug' : logging.DEBUG,
       	  'info' : logging.INFO,
          'warning' : logging.WARNING,
          'error' : logging.ERROR,
          'critical' : logging.CRITICAL}

formatter = logging.Formatter("%(name)s: %(levelname)s: %(message)s")
time_formatter = logging.Formatter("%(asctime)s: %(name)s: %(levelname)s: %(message)s")

class RotatingFileHandler(logging.handlers.RotatingFileHandler):
    """
    RotatingFileHandler: replace RotatingFileHandler with a custom handler 
    """
    def shouldRollover(self, record):
        """
        Rewrite RotatingFileHandler.shouldRollover. 
       
        If the log file is deleted at run-time, a new file will be created. 
        """
        dfn = self.baseFilename                 
        if (self.stream) and (not os.path.exists(dfn)): #Is log file exist?
            self.stream.close()
            self.stream = self._open()
        super(RotatingFileHandler, self).shouldRollover(record)

    def update_config(self, file_name, backup_count, max_bytes):
        """
        Update RotatingFileHandler configuration.

        input:
            log file name
            max backup count
            predetermined log file size
        """
        try:
            self._open(file_name)
        except IOError:
            print("The file path is not exist!")
            return 
        self.baseFilename = file_name
        self.maxBytes = max_bytes
        self.backupCount = backup_count

class SLHandler(logging.Handler):    
    """
    Replace SysLogHandler with a custom handler 

    A handler class which sends formatted logging records to a syslog
    server. 
    """
    def __init__(self, ident, logopt=0, facility=syslog.LOG_USER):        
        """
        Initialize a handler.
    
        If facility is not specified, LOG_USER is used.
        """
        super(SLHandler, self).__init__(self)
        self.ident = ident        
        self.logopt = logopt        
        self.facility = facility        
        self.mappings = {            
                logging.DEBUG: syslog.LOG_DEBUG,            
                logging.INFO: syslog.LOG_INFO,            
                logging.WARNING: syslog.LOG_WARNING,            
                logging.ERROR: syslog.LOG_ERR,            
                logging.CRITICAL: syslog.LOG_CRIT,            
                }   
        
    def encodeLevel(self, level):        
        """
        Encoding the priority.
        """
        return self.mappings.get(level, syslog.LOG_INFO)    
   
    def emit(self, record):   
        """
        Emit a record.
     
        The record is formatted, and then sent to the syslog server. If
        exception information is present, it is NOT sent to the server.
        """
        syslog.openlog(self.ident, self.logopt, self.facility)        
        msg = self.format(record)        
        prio = self.encodeLevel(record.levelno)        
        syslog.syslog(prio, msg)        
        syslog.closelog()


class ModuleLogger(logging.getLoggerClass()):
    """
    Override logging.logger behaviour
    """
    def __init__(self, log_name, log_file, 
                 severity = 'debug', backup_count = 0, max_bytes = 0,
                 log_to_console = True):
        """
        Initializes the logger with some specific parameters
        """
        logging.Logger.__init__(self, log_name)

        # Set up a specific logger with our desired output level
        logLevel = LEVELS.get(severity, logging.NOTSET)
        self.setLevel(logLevel)
        
        self.null_handler = None 
        self.rotating_handler = None
        self.stream_handler = None
        self.syslog_handler = None

        self.add_null_handler()
        self.add_rotate_handler(log_file, max_bytes, backup_count)
        if log_to_console:
            self.add_stream_handler()
        else:
            self.add_syslog_handler()

    def add_null_handler(self):
        """
        Add a null handler.
        """
        self.null_handler = logging.NullHandler()
        self.addHandler(self.null_handler)

    def add_rotate_handler(self, log_file, max_bytes, backup_count):
        """
        Add a rotate file handler.
   
        input:
            log_file : the location of log file.Handler would't be created is log_file is empty
            max_bytes : limit log growth
            backup_count : max backup count
        """
        if(log_file != 0  and log_file != ''):
            try:
                self.rotating_handler = RotatingFileHandler(filename = log_file, maxBytes = max_bytes, 
                                                            backupCount = backup_count)
            except IOError:
                self.rotating_handler = None
                return
            self.rotating_handler.setFormatter(time_formatter)
            self.addHandler(self.rotating_handler)

    def add_stream_handler(self):
        """
        Add a stream handler.
    
        sys.stderr will be used for logging output.
        """
        self.stream_handler = logging.StreamHandler()
        self.stream_handler.setFormatter(time_formatter)
        self.addHandler(self.stream_handler)

    def add_syslog_handler(self):
        """
        Add a syslog handler.
   
        If facility is not specified, LOG_USER is used.
        The default severity level is INFO.
        """
        self.syslog_handler = SLHandler('BIND10', facility=syslog.LOG_USER)
        self.syslog_handler.setFormatter(formatter)
        #set syslog handler level info
        self.syslog_handler.setLevel(logging.INFO)
        self.addHandler(self.syslog_handler)

    def update_rotate_handler(self, log_file, max_bytes, backup_count):
        """
        If rotate handler has been added to the logger, update its configuration,
        else add it to logger.
    
        If log file is empty, the handler will be removed.
        """
        if (self.rotating_handler in self.handlers):
            if(log_file != 0 and log_file != ''):
                self.rotating_handler.update_config(log_file, max_bytes, backup_count)
            else:
                self.rotating_handler.flush()
                self.rotating_handler.close()
                self.removeHandler(self.rotating_handler)
        else:
            self.add_rotate_handler(log_file, max_bytes, backup_count)


    def update_config(self, file_name, level, max_bytes, backup_count):
        """
        Update logger's configuration.

        We can update logger's log level and its rotate file handler's configuration.
        """
        logLevel = LEVELS.get(level, logging.NOTSET)
        if(logLevel != self.getEffectiveLevel()):
            self.setLevel(logLevel)
        self.update_rotate_handler(file_name, backup_count, max_bytes)

    def log_message(self, level, msg, *args, **kwargs):
        """
        Log 'msg % args' with the integer severity 'level'.
     
        To pass exception information, use the keyword argument exc_info with
        a true value, e.g.
  
        logger.log_message('info', "We have a %s", "mysterious problem", exc_info=1)
        """
        logLevel = LEVELS.get(level, logging.NOTSET)
        self.log(logLevel, msg, *args, **kwargs)


