SUBDIRS = . compiler tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(LOG4CPLUS_INCLUDES)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = liblog.la
liblog_la_SOURCES  =
liblog_la_SOURCES += dummylog.h dummylog.cc
liblog_la_SOURCES += log_formatter.h log_formatter.cc
liblog_la_SOURCES += logger.cc logger.h
liblog_la_SOURCES += logger_impl.cc logger_impl.h
liblog_la_SOURCES += logger_level.h
liblog_la_SOURCES += logger_level.h
liblog_la_SOURCES += logger_level_impl.cc logger_level_impl.h
liblog_la_SOURCES += logger_manager.cc logger_manager.h
liblog_la_SOURCES += logger_specification.h
liblog_la_SOURCES += logger_support.cc logger_support.h
liblog_la_SOURCES += macros.h
liblog_la_SOURCES += messagedef.cc messagedef.h
liblog_la_SOURCES += message_dictionary.cc message_dictionary.h
liblog_la_SOURCES += message_exception.h
liblog_la_SOURCES += message_initializer.cc message_initializer.h
liblog_la_SOURCES += message_reader.cc message_reader.h
liblog_la_SOURCES += message_types.h
liblog_la_SOURCES += output_option.h
liblog_la_SOURCES += root_logger_name.cc root_logger_name.h

EXTRA_DIST  = README
EXTRA_DIST += messagedef.mes

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
liblog_la_LIBADD = $(top_builddir)/src/lib/util/libutil.la
