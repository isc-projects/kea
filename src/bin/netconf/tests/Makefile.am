SUBDIRS = . shtests

EXTRA_DIST = testdata/get_config.json

AM_CPPFLAGS  =
AM_CPPFLAGS += -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -DCFG_EXAMPLES=\"$(abs_top_srcdir)/doc/examples/netconf\"
AM_CPPFLAGS += -DKEATEST_MODULE
AM_CPPFLAGS += -DSYNTAX_FILE=\"$(abs_srcdir)/../netconf_parser.yy\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/netconf/tests\"
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += $(LIBYANG_CPPFLAGS)
AM_CPPFLAGS += $(LIBYANG_INCLUDEDIR)
AM_CPPFLAGS += $(LIBYANGCPP_CPPFLAGS)
AM_CPPFLAGS += $(LIBYANGCPP_INCLUDEDIR)
AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)
AM_CPPFLAGS += $(SYSREPO_INCLUDEDIR)
AM_CPPFLAGS += $(SYSREPOCPP_CPPFLAGS)
AM_CPPFLAGS += $(SYSREPOCPP_INCLUDEDIR)

CLEANFILES = *.json *.log

DISTCLEANFILES = test_data_files_config.h test_libraries.h

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

noinst_LTLIBRARIES = libbasic.la

TESTS += netconf_unittests

netconf_unittests_SOURCES  = control_socket_unittests.cc
netconf_unittests_SOURCES += get_config_unittest.cc
netconf_unittests_SOURCES += netconf_cfg_mgr_unittests.cc
netconf_unittests_SOURCES += netconf_controller_unittests.cc
netconf_unittests_SOURCES += netconf_process_unittests.cc
netconf_unittests_SOURCES += netconf_unittests.cc
netconf_unittests_SOURCES += parser_unittests.cc
netconf_unittests_SOURCES += run_unittests.cc

netconf_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
netconf_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)


netconf_unittests_LDADD  = $(top_builddir)/src/bin/netconf/libnetconf.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/process/testutils/libprocesstest.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/yang/testutils/libyangtest.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/yang/libkea-yang.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
netconf_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
netconf_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)
netconf_unittests_LDADD += $(LIBYANG_LIBS)
netconf_unittests_LDADD += $(LIBYANGCPP_LIBS)
netconf_unittests_LDADD += $(SYSREPO_LIBS)
netconf_unittests_LDADD += $(SYSREPOCPP_LIBS)

# The basic callout library - contains standard callouts
libbasic_la_SOURCES  = basic_library.cc
libbasic_la_CXXFLAGS = $(AM_CXXFLAGS)
libbasic_la_CPPFLAGS = $(AM_CPPFLAGS)
libbasic_la_LIBADD   = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libbasic_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libbasic_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libbasic_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere

nodist_netconf_unittests_SOURCES = test_data_files_config.h test_libraries.h
endif

noinst_EXTRA_DIST = configs-list.txt

noinst_PROGRAMS = $(TESTS)
