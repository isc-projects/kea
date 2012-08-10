AM_CXXFLAGS = $(B10_CXXFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

lib_LTLIBRARIES = libb10-util-io.la
libb10_util_io_la_SOURCES = fd.h fd.cc fd_share.h fd_share.cc
libb10_util_io_la_SOURCES += socketsession.h socketsession.cc sockaddr_util.h
libb10_util_io_la_SOURCES += pktinfo_utilities.h
libb10_util_io_la_LIBADD = $(top_builddir)/src/lib/exceptions/libb10-exceptions.la

CLEANFILES = *.gcno *.gcda

pyexec_LTLIBRARIES = libutil_io_python.la
# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
libutil_io_python_la_LDFLAGS = -module -avoid-version
libutil_io_python_la_SOURCES = fdshare_python.cc
libutil_io_python_la_LIBADD = libb10-util-io.la
libutil_io_python_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
# Note: PYTHON_CXXFLAGS may have some -Wno... workaround, which must be
# placed after -Wextra defined in AM_CXXFLAGS
libutil_io_python_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)
