SUBDIRS = . compiler tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = liblog.la
liblog_la_SOURCES  =
liblog_la_SOURCES += dummylog.h dummylog.cc
liblog_la_SOURCES += logimpl_messages.cc logimpl_messages.h
liblog_la_SOURCES += log_dbglevels.h
liblog_la_SOURCES += log_formatter.h log_formatter.cc
liblog_la_SOURCES += logger.cc logger.h
liblog_la_SOURCES += logger_impl.cc logger_impl.h
liblog_la_SOURCES += logger_level.h
liblog_la_SOURCES += logger_level.cc logger_level.h
liblog_la_SOURCES += logger_level_impl.cc logger_level_impl.h
liblog_la_SOURCES += logger_manager.cc logger_manager.h
liblog_la_SOURCES += logger_manager_impl.cc logger_manager_impl.h
liblog_la_SOURCES += logger_name.cc logger_name.h
liblog_la_SOURCES += logger_specification.h
liblog_la_SOURCES += logger_support.cc logger_support.h
liblog_la_SOURCES += logger_unittest_support.cc logger_unittest_support.h
liblog_la_SOURCES += log_messages.cc log_messages.h
liblog_la_SOURCES += macros.h
liblog_la_SOURCES += message_dictionary.cc message_dictionary.h
liblog_la_SOURCES += message_exception.h
liblog_la_SOURCES += message_initializer.cc message_initializer.h
liblog_la_SOURCES += message_reader.cc message_reader.h
liblog_la_SOURCES += message_types.h
liblog_la_SOURCES += output_option.cc output_option.h

EXTRA_DIST  = README
EXTRA_DIST += logimpl_messages.mes
EXTRA_DIST += log_messages.mes

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
liblog_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
liblog_la_CXXFLAGS += -Wno-unused-parameter
endif
if USE_CLANGPP
# Same for clang++, but we need to turn off -Werror completely.
liblog_la_CXXFLAGS += -Wno-error
endif
liblog_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
liblog_la_LDFLAGS  = $(LOG4CPLUS_LDFLAGS)
liblog_la_LIBADD   = $(top_builddir)/src/lib/util/libutil.la
