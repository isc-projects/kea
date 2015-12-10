SHTESTS =
# The test of dynamic reconfiguration based on signals will work only
# if we are using file based configuration approach.
SHTESTS += dhcp6_process_tests.sh

noinst_SCRIPTS = dhcp6_process_tests.sh

EXTRA_DIST = $(SHTESTS) dhcp6_process_tests.sh.in

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -DTOP_BUILDDIR="\"$(top_builddir)\""
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/dhcp6/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

CLEANFILES  = $(builddir)/logger_lockfile
CLEANFILES += $(builddir)/load_marker.txt $(builddir)/unload_marker.txt
CLEANFILES += *.json *.log

DISTCLEANFILES = dhcp6_process_tests.sh

AM_CXXFLAGS = $(KEA_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some Boost headers when compiling with clang
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
# Build shared libraries for testing. The libtool way to create a shared library
# is to specify "-avoid-version -export-dynamic -module" in the library LDFLAGS
# (see http://www.gnu.org/software/libtool/manual/html_node/Link-mode.html).
# Use of these switches will guarantee that the .so files are created in the
# .libs folder and they can be dlopened.
# Note that the shared libraries with callouts should not be used together with
# the --enable-static-link option. With this option, the bind10 libraries are
# statically linked with the program and if the callout invokes the methods
# which belong to these libraries, the library with the callout will get its
# own copy of the static objects (e.g. logger, ServerHooks) and that will lead
# to unexpected errors. For this reason, the --enable-static-link option is
# ignored for unit tests built here.

noinst_LTLIBRARIES = libco1.la libco2.la

# -rpath /nowhere is a hack to trigger libtool to not create a
# convenience archive, resulting in shared modules

libco1_la_SOURCES  = callout_library_1.cc callout_library_common.h
libco1_la_CXXFLAGS = $(AM_CXXFLAGS)
libco1_la_CPPFLAGS = $(AM_CPPFLAGS)
libco1_la_LDFLAGS = -avoid-version -export-dynamic -module -rpath /nowhere

libco2_la_SOURCES  = callout_library_2.cc callout_library_common.h
libco2_la_CXXFLAGS = $(AM_CXXFLAGS)
libco2_la_CPPFLAGS = $(AM_CPPFLAGS)
libco2_la_LDFLAGS = -avoid-version -export-dynamic -module -rpath /nowhere

TESTS += dhcp6_unittests
dhcp6_unittests_SOURCES  = dhcp6_unittests.cc
dhcp6_unittests_SOURCES += dhcp6_srv_unittest.cc
dhcp6_unittests_SOURCES += fqdn_unittest.cc
dhcp6_unittests_SOURCES += hooks_unittest.cc
dhcp6_unittests_SOURCES += host_unittest.cc
dhcp6_unittests_SOURCES += dhcp6_test_utils.cc dhcp6_test_utils.h
dhcp6_unittests_SOURCES += d2_unittest.cc d2_unittest.h
dhcp6_unittests_SOURCES += marker_file.cc
dhcp6_unittests_SOURCES += ctrl_dhcp6_srv_unittest.cc
dhcp6_unittests_SOURCES += dhcp6_client.cc dhcp6_client.h
dhcp6_unittests_SOURCES += rebind_unittest.cc
dhcp6_unittests_SOURCES += renew_unittest.cc
dhcp6_unittests_SOURCES += sarr_unittest.cc
dhcp6_unittests_SOURCES += config_parser_unittest.cc
dhcp6_unittests_SOURCES += confirm_unittest.cc
dhcp6_unittests_SOURCES += infrequest_unittest.cc
dhcp6_unittests_SOURCES += decline_unittest.cc
dhcp6_unittests_SOURCES += dhcp6_message_test.cc dhcp6_message_test.h

dhcp6_unittests_SOURCES += kea_controller_unittest.cc

nodist_dhcp6_unittests_SOURCES  = marker_file.h test_libraries.h

dhcp6_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
dhcp6_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
if HAVE_MYSQL
dhcp6_unittests_LDFLAGS += $(MYSQL_LIBS)
endif
if HAVE_PGSQL
dhcp6_unittests_LDFLAGS += $(PGSQL_LIBS)
endif
dhcp6_unittests_LDFLAGS += $(GTEST_LDFLAGS)

dhcp6_unittests_LDADD = $(top_builddir)/src/bin/dhcp6/libdhcp6.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcp/tests/libdhcptest.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
dhcp6_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
dhcp6_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
