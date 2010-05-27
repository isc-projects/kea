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

import os
import syslog
import logging
import logging.handlers

#########################################################################
# LEVELS: logging levels mapping
#########################################################################
LEVELS = {'debug' : logging.DEBUG,
       	  'info' : logging.INFO,
          'warning' : logging.WARNING,
          'error' : logging.ERROR,
          'critical' : logging.CRITICAL}

formatter = logging.Formatter("%(name)s: %(levelname)s: %(message)s")
time_formatter = logging.Formatter("%(asctime)s: %(name)s: %(levelname)s: %(message)s")
#########################################################################
# NullHandler: define a do-nothing handler 
#########################################################################
class NullHandler(logging.Handler):
    def emit(self, record):
        pass

#########################################################################
# RotatingFileHandler: replace RotatingFileHandler with a custom handler 
#########################################################################
class RotatingFileHandler(logging.handlers.RotatingFileHandler):

    def __init__(self, filename, mode='a', maxBytes=0, backupCount=0, encoding=None):
        logging.handlers.RotatingFileHandler.__init__(self, filename, mode, 
                                                      maxBytes, backupCount,
                                                      encoding)
    #####################################################################
    # shouldRollover 
    #   Rewrite RotatingFileHandler.shouldRollover. 
    #   If the log file is deleted, a new file will be created. 
    #####################################################################
    def shouldRollover(self, record):
        if self.stream is None:                 # delay was set...
            self.stream = self._open()

        dfn = self.baseFilename                 # Is log file exist?
        if not os.path.exists(dfn):
            self.stream.close()
            self.stream = self._open()

        if self.maxBytes > 0:                   # are we rolling over?
            msg = "%s\n" % self.format(record)
            self.stream.seek(0, 2)  #due to non-posix-compliant Windows feature
            if self.stream.tell() + len(msg) >= self.maxBytes:
                return 1
        return 0

    ######################################################################
    # handleError 
    #   Rewrite RotatingFileHandler.handleError.
    #   If raiseExceptions is false, exceptions get silently ignored.
    ######################################################################
    def handleError(self, record):
        pass

    ######################################################################
    # update_config
    #   update RotatingFileHandler configuration
    #   input:
    #         new log file name
    #         max backup count
    #         predetermined log file size
    ######################################################################
    def update_config(self, file_name, backup_count, max_bytes):
        self.baseFilename = file_name
        self.maxBytes = max_bytes
        self.backupCount = backup_count


#########################################################################
# SLHandler: Replace SysLogHandler with a custom handler due to python3.1
#            SysLogHandler issue : http://bugs.python.org/issue8148
#########################################################################
class SLHandler(logging.Handler):    
    def __init__(self, ident, logopt=0, facility=syslog.LOG_USER):        
        logging.Handler.__init__(self)        
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
        return self.mappings.get(level, syslog.LOG_INFO)    
   
    def handleError(self, record):
        pass

    def emit(self, record):        
        syslog.openlog(self.ident, self.logopt, self.facility)        
        msg = self.format(record)        
        prio = self.encodeLevel(record.levelno)        
        syslog.syslog(prio, msg)        
        syslog.closelog()


#########################################################################
# ModuleLogger: rewrite logging.Logger 
#########################################################################
class ModuleLogger(logging.getLoggerClass()):
    def __init__(self, log_name, log_file, 
                 severity = 'debug', backup_count = 0, max_bytes = 0,
                 log_to_console = True):
        logging.Logger.__init__(self, log_name)

        # Set up a specific logger with our desired output level
        logLevel = LEVELS.get(severity, logging.NOTSET)
        self.setLevel(logLevel)
        
        null_handler = NullHandler()
        self.addHandler(null_handler)

        self.rotating_handler = None
        self.stream_handler = None
        self.syslog_handler = None
        self.add_rotate_handler(log_file, max_bytes, backup_count)
        if log_to_console:
            self.add_stream_handler()
        else:
            self.add_syslog_handler()

    def add_rotate_handler(self, log_file, max_bytes, backup_count):
        # If logFile was specified
        if(log_file != 0  and log_file != ''):
            # Add the log message handler to the logger
            try:
                self.rotating_handler = RotatingFileHandler(filename = log_file, maxBytes = max_bytes, 
                                                            backupCount = backup_count)
                # add formatter to ch
                self.rotating_handler.setFormatter(time_formatter)
                self.addHandler(self.rotating_handler)
            except IOError:
                pass

    def add_stream_handler(self):
        self.stream_handler = logging.StreamHandler()
        self.stream_handler.setFormatter(time_formatter)
        self.addHandler(self.stream_handler)

    def add_syslog_handler(self):
        self.syslog_handler = SLHandler('BIND10')
        self.syslog_handler.setFormatter(formatter)
        #set syslog handler level info
        self.syslog_handler.setLevel(logging.INFO)
        self.addHandler(self.syslog_handler)

    def update_rotate_handler(self, log_file, max_bytes, backup_count):
        # If logFile was specified
        if (self.rotating_handler not in self.handlers):
            pass
        else:
            if(log_file != 0 and log_file != ''):
                self.rotating_handler.update_config(log_file, max_bytes, backup_count)
            else:
                self.rotating_handler.flush()
                self.rotating_handler.close()
                self.removeHandler(self.rotating_handler)

    def update_config(self, file_name, level, max_bytes, backup_count):
        logLevel = LEVELS.get(level, logging.NOTSET)
        if(logLevel != self.getEffectiveLevel()):
            self.setLevel(logLevel)
        self.update_rotate_handler(file_name, backup_count, max_bytes)

    def log_message(self, level, msg, *args, **kwargs):
        logLevel = LEVELS.get(level, logging.NOTSET)
        self.log(logLevel, msg, *args, **kwargs)


