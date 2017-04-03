SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libasiolinktest.la

libasiolinktest_la_SOURCES  = test_server_unix_socket.cc test_server_unix_socket.h

libasiolinktest_la_CXXFLAGS = $(AM_CXXFLAGS)
libasiolinktest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libasiolinktest_la_LDFLAGS  = $(AM_LDFLAGS)

libasiolinktest_la_LIBADD  = $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libasiolinktest_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libasiolinktest_la_LIBADD += $(BOOST_LIBS)

endif
