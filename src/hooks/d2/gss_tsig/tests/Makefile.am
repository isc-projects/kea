SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/d2/gss_tsig -I$(top_srcdir)/src/hooks/d2/gss_tsig
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_srcdir)\"
AM_CPPFLAGS += $(GSSAPI_CFLAGS) $(BOOST_INCLUDES)
AM_CPPFLAGS += $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST = doc.txt administrator.ccache testdenied.ccache dns.keytab

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += gss_tsig_unittests

gss_tsig_unittests_SOURCES  = run_unittests.cc
gss_tsig_unittests_SOURCES += dns_update_unittests.cc
gss_tsig_unittests_SOURCES += gss_tsig_api_unittests.cc
gss_tsig_unittests_SOURCES += gss_tsig_api_utils.h
gss_tsig_unittests_SOURCES += gss_tsig_callouts_unittests.cc
gss_tsig_unittests_SOURCES += gss_tsig_cfg_unittests.cc
gss_tsig_unittests_SOURCES += gss_tsig_context_unittests.cc
gss_tsig_unittests_SOURCES += gss_tsig_impl_unittests.cc
gss_tsig_unittests_SOURCES += gss_tsig_key_unittests.cc
gss_tsig_unittests_SOURCES += managed_key_unittests.cc
gss_tsig_unittests_SOURCES += tkey_unittests.cc
gss_tsig_unittests_SOURCES += tkey_exchange_unittests.cc

gss_tsig_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

gss_tsig_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

gss_tsig_unittests_CXXFLAGS = $(AM_CXXFLAGS)

gss_tsig_unittests_LDADD  = $(top_builddir)/src/hooks/d2/gss_tsig/testutils/libgsstsigtest.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/hooks/d2/gss_tsig/libgss_tsig.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/d2srv/testutils/libd2srvtest.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/d2srv/libkea-d2srv.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/dhcp/testutils/libdhcptest.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
gss_tsig_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
gss_tsig_unittests_LDADD += $(GSSAPI_LIBS)
gss_tsig_unittests_LDADD += $(LOG4CPLUS_LIBS)
gss_tsig_unittests_LDADD += $(CRYPTO_LIBS)
gss_tsig_unittests_LDADD += $(BOOST_LIBS)
gss_tsig_unittests_LDADD += $(GTEST_LDADD)

nsupdate_SOURCES = nsupdate.cc

nsupdate_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)
nsupdate_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
nsupdate_CXXFLAGS = $(AM_CXXFLAGS)
nsupdate_LDADD  = $(top_builddir)/src/hooks/d2/gss_tsig/libgss_tsig.la
nsupdate_LDADD += $(top_builddir)/src/lib/d2srv/libkea-d2srv.la
nsupdate_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
nsupdate_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
nsupdate_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
nsupdate_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
nsupdate_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
nsupdate_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
nsupdate_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
nsupdate_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
nsupdate_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
nsupdate_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
nsupdate_LDADD += $(GSSAPI_LIBS) $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

noinst_PROGRAMS = $(TESTS) nsupdate
endif

# Heimdal requires restricted permissions on the credential cache files.
check-recursive: pre-check-recursive

pre-check-recursive:
	chmod go-rw $(abs_srcdir)/administrator.ccache
	chmod go-rw $(abs_srcdir)/testdenied.ccache

.PHONY=pre-check-recursive
