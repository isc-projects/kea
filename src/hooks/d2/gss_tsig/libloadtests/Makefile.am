SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/d2/gss_tsig -I$(top_srcdir)/src/hooks/d2/gss_tsig
AM_CPPFLAGS += $(GSSAPI_CFLAGS) $(BOOST_INCLUDES)
AM_CPPFLAGS += $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/hooks/d2/gss_tsig/libloadtests\"
AM_CPPFLAGS += -DLIBDHCP_GSS_TSIG_SO=\"$(abs_top_builddir)/src/hooks/d2/gss_tsig/.libs/libddns_gss_tsig.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libddns_gss_tsig_unittests

libddns_gss_tsig_unittests_SOURCES = run_unittests.cc
libddns_gss_tsig_unittests_SOURCES += load_unload_unittests.cc

libddns_gss_tsig_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

libddns_gss_tsig_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

libddns_gss_tsig_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libddns_gss_tsig_unittests_LDADD  = $(top_builddir)/src/lib/d2srv/libkea-d2srv.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libddns_gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libddns_gss_tsig_unittests_LDADD += $(GSSAPI_LIBS)
libddns_gss_tsig_unittests_LDADD += $(LOG4CPLUS_LIBS)
libddns_gss_tsig_unittests_LDADD += $(CRYPTO_LIBS)
libddns_gss_tsig_unittests_LDADD += $(BOOST_LIBS)
libddns_gss_tsig_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
