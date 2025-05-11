SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/class_cmds -I$(top_srcdir)/src/hooks/dhcp/class_cmds
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DLIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/class_cmds/.libs/libdhcp_class_cmds.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += class_cmds_unittests

class_cmds_unittests_SOURCES = run_unittests.cc
class_cmds_unittests_SOURCES += class_cmds_unittest.cc

class_cmds_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

class_cmds_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

class_cmds_unittests_CXXFLAGS = $(AM_CXXFLAGS)

class_cmds_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/class_cmds/libclass_cmds.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
class_cmds_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

class_cmds_unittests_LDADD += $(LOG4CPLUS_LIBS)
class_cmds_unittests_LDADD += $(CRYPTO_LIBS)
class_cmds_unittests_LDADD += $(BOOST_LIBS)
class_cmds_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
