SUBDIRS = interprocess . compiler tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTOP_BUILDDIR=\"$(abs_top_builddir)\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-log.la
libkea_log_la_SOURCES  =
libkea_log_la_SOURCES += logimpl_messages.cc logimpl_messages.h
libkea_log_la_SOURCES += log_dbglevels.cc log_dbglevels.h
libkea_log_la_SOURCES += log_formatter.h log_formatter.cc
libkea_log_la_SOURCES += logger.cc logger.h
libkea_log_la_SOURCES += logger_impl.cc logger_impl.h
libkea_log_la_SOURCES += logger_level.h
libkea_log_la_SOURCES += logger_level.cc logger_level.h
libkea_log_la_SOURCES += logger_level_impl.cc logger_level_impl.h
libkea_log_la_SOURCES += logger_manager.cc logger_manager.h
libkea_log_la_SOURCES += logger_manager_impl.cc logger_manager_impl.h
libkea_log_la_SOURCES += logger_name.cc logger_name.h
libkea_log_la_SOURCES += logger_specification.h
libkea_log_la_SOURCES += logger_support.cc logger_support.h
libkea_log_la_SOURCES += logger_unittest_support.cc logger_unittest_support.h
libkea_log_la_SOURCES += log_messages.cc log_messages.h
libkea_log_la_SOURCES += macros.h
libkea_log_la_SOURCES += message_dictionary.cc message_dictionary.h
libkea_log_la_SOURCES += message_exception.h
libkea_log_la_SOURCES += message_initializer.cc message_initializer.h
libkea_log_la_SOURCES += message_reader.cc message_reader.h
libkea_log_la_SOURCES += message_types.h
libkea_log_la_SOURCES += output_option.cc output_option.h
libkea_log_la_SOURCES += buffer_appender_impl.cc buffer_appender_impl.h

EXTRA_DIST  = logging.dox
EXTRA_DIST += logimpl_messages.mes
EXTRA_DIST += log_messages.mes

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# KEA_CXXFLAGS)
libkea_log_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
libkea_log_la_CXXFLAGS += -Wno-unused-parameter -Wno-deprecated-declarations
endif
libkea_log_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libkea_log_la_LIBADD   = $(top_builddir)/src/lib/log/interprocess/libkea-log_interprocess.la
libkea_log_la_LIBADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_log_la_LIBADD  += $(top_builddir)/src/lib/util/libkea-util.la
libkea_log_la_LIBADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_log_la_LIBADD  += $(LOG4CPLUS_LIBS)
libkea_log_la_LDFLAGS = -no-undefined -version-info 3:1:0

# Specify the headers for copying into the installation directory tree.
libkea_log_includedir = $(pkgincludedir)/log
libkea_log_include_HEADERS = \
	buffer_appender_impl.h \
	log_dbglevels.h \
	log_formatter.h \
	log_messages.h \
	logger.h \
	logger_impl.h \
	logger_level.h \
	logger_level_impl.h \
	logger_manager.h \
	logger_manager_impl.h \
	logger_name.h \
	logger_specification.h \
	logger_support.h \
	logger_unittest_support.h \
	logimpl_messages.h \
	macros.h \
	message_dictionary.h \
	message_exception.h \
	message_initializer.h \
	message_reader.h \
	message_types.h \
	output_option.h

libkea_log_interprocess_includedir = $(pkgincludedir)/log/interprocess
libkea_log_interprocess_include_HEADERS = \
	interprocess/interprocess_sync.h \
	interprocess/interprocess_sync_file.h \
	interprocess/interprocess_sync_null.h
