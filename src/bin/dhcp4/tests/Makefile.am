SHTESTS =
# The test of dynamic reconfiguration based on signals will work only
# if we are using file based configuration approach.
if CONFIG_BACKEND_JSON
SHTESTS += dhcp4_process_tests.sh
endif

noinst_SCRIPTS = dhcp4_process_tests.sh

EXTRA_DIST  = dhcp4_process_tests.sh.in

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/dhcp6/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

CLEANFILES = $(builddir)/interfaces.txt $(builddir)/logger_lockfile
CLEANFILES += $(builddir)/load_marker.txt $(builddir)/unload_marker.txt
CLEANFILES += *.json *.log

DISTCLEANFILES = dhcp4_process_tests.sh

AM_CXXFLAGS = $(KEA_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some Boost headers when compiling with clang
AM_CXXFLAGS += -Wno-unused-parameter
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

TESTS += dhcp4_unittests

dhcp4_unittests_SOURCES  = d2_unittest.h d2_unittest.cc
dhcp4_unittests_SOURCES += dhcp4_test_utils.h
dhcp4_unittests_SOURCES += dhcp4_unittests.cc
dhcp4_unittests_SOURCES += dhcp4_srv_unittest.cc
dhcp4_unittests_SOURCES += dhcp4_test_utils.cc dhcp4_test_utils.h
dhcp4_unittests_SOURCES += direct_client_unittest.cc
dhcp4_unittests_SOURCES += ctrl_dhcp4_srv_unittest.cc
dhcp4_unittests_SOURCES += config_parser_unittest.cc
dhcp4_unittests_SOURCES += fqdn_unittest.cc
dhcp4_unittests_SOURCES += marker_file.cc
dhcp4_unittests_SOURCES += dhcp4_client.cc dhcp4_client.h
dhcp4_unittests_SOURCES += inform_unittest.cc
dhcp4_unittests_SOURCES += dora_unittest.cc
dhcp4_unittests_SOURCES += release_unittest.cc

if CONFIG_BACKEND_BUNDY
# For Bundy backend, we only need to run the usual tests. There are no
# Bundy-specific tests yet.
dhcp4_unittests_SOURCES += bundy_controller_unittest.cc
endif

if CONFIG_BACKEND_JSON
dhcp4_unittests_SOURCES += kea_controller_unittest.cc
endif

nodist_dhcp4_unittests_SOURCES = marker_file.h test_libraries.h

dhcp4_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
dhcp4_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
dhcp4_unittests_LDADD = $(GTEST_LDADD)
dhcp4_unittests_LDADD += $(top_builddir)/src/bin/dhcp4/libdhcp4.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/dhcp/tests/libdhcptest.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/util/io/libkea-util-io.la
endif

noinst_EXTRA_DIST = configs-list.txt

noinst_PROGRAMS = $(TESTS)
