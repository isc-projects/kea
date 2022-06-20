SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/bootp -I$(top_srcdir)/src/hooks/dhcp/bootp
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DBOOTP_LIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/bootp/.libs/libdhcp_bootp.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

LOG_COMPILER = $(LIBTOOL)
AM_LOG_FLAGS = --mode=execute

TESTS =
if HAVE_GTEST
TESTS += bootp_unittests

bootp_unittests_SOURCES = run_unittests.cc
bootp_unittests_SOURCES += bootp_unittests.cc

bootp_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

bootp_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

bootp_unittests_CXXFLAGS = $(AM_CXXFLAGS)

bootp_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/bootp/libbootp.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
bootp_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
bootp_unittests_LDADD += $(LOG4CPLUS_LIBS)
bootp_unittests_LDADD += $(CRYPTO_LIBS)
bootp_unittests_LDADD += $(BOOST_LIBS)
bootp_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
