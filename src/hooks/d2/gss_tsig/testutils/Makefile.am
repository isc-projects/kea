SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/d2/gss_tsig -I$(top_srcdir)/src/hooks/d2/gss_tsig
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_srcdir)\"
AM_CPPFLAGS += $(GSSAPI_CFLAGS) $(BOOST_INCLUDES)
AM_CPPFLAGS += $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libgsstsigtest.la

libgsstsigtest_la_SOURCES = gss_tsig_dns_server.cc gss_tsig_dns_server.h

libgsstsigtest_la_CXXFLAGS = $(AM_CXXFLAGS)
libgsstsigtest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

libgsstsigtest_la_LIBADD  = $(top_builddir)/src/lib/d2srv/libkea-d2srv.la

libgsstsigtest_la_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

endif
