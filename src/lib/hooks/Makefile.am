SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libb10-hooks.la
libb10_hooks_la_SOURCES  =
libb10_hooks_la_SOURCES += callout_handle.cc callout_handle.h
libb10_hooks_la_SOURCES += callout_manager.cc callout_manager.h
libb10_hooks_la_SOURCES += hooks.h
libb10_hooks_la_SOURCES += library_handle.cc library_handle.h
libb10_hooks_la_SOURCES += library_manager.cc library_manager.h
libb10_hooks_la_SOURCES += server_hooks.cc server_hooks.h

libb10_hooks_la_CXXFLAGS = $(AM_CXXFLAGS)
libb10_hooks_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libb10_hooks_la_LDFLAGS  = $(AM_LDFLAGS) -ldl
libb10_hooks_la_LIBADD  =
libb10_hooks_la_LIBADD += $(top_builddir)/src/lib/log/libb10-log.la
libb10_hooks_la_LIBADD += $(top_builddir)/src/lib/util/libb10-util.la
libb10_hooks_la_LIBADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la


if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libb10_hooks_la_CXXFLAGS += -Wno-unused-parameter
endif
