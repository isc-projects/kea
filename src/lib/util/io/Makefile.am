SUBDIRS = .
AM_CXXFLAGS = $(KEA_CXXFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

lib_LTLIBRARIES = libkea-util-io.la
libkea_util_io_la_SOURCES = fd.h fd.cc fd_share.h fd_share.cc
libkea_util_io_la_SOURCES += socketsession.h socketsession.cc sockaddr_util.h
libkea_util_io_la_SOURCES += pktinfo_utilities.h
libkea_util_io_la_LIBADD = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_util_io_la_LDFLAGS = -no-undefined -version-info 0:1:0

CLEANFILES = *.gcno *.gcda
