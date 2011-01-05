SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = liblog.la
liblog_la_SOURCES  = root_logger_name.cc root_logger_name.h
liblog_la_SOURCES += xdebuglevel.cc xdebuglevel.h
liblog_la_SOURCES += logger.cc logger.h
liblog_la_SOURCES += message_reader.cc message_reader.h
liblog_la_SOURCES += filename.h filename.cc
liblog_la_SOURCES += stringutil.h stringutil.cc

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
liblog_la_CPPFLAGS = $(AM_CPPFLAGS)
