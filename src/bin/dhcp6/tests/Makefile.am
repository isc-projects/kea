PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = dhcp6_test.py
EXTRA_DIST = $(PYTESTS)

# Explicitly specify paths to dynamic libraries required by loadable python
# modules. That is required on Mac OS systems. Otherwise we will get exception
# about python not being able to load liblog library.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/threads/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
endif

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	$(LIBRARY_PATH_PLACEHOLDER) \
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_srcdir)/src/bin:$(abs_top_builddir)/src/bin/bind10:$(abs_top_builddir)/src/lib/util/io/.libs \
		$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done


AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -DTOP_BUILDDIR="\"$(top_builddir)\""
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

CLEANFILES  = $(builddir)/interfaces.txt $(builddir)/logger_lockfile
CLEANFILES += $(builddir)/load_marker.txt $(builddir)/unload_marker.txt

AM_CXXFLAGS = $(B10_CXXFLAGS)
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

TESTS += dhcp6_unittests
dhcp6_unittests_SOURCES  = dhcp6_unittests.cc
dhcp6_unittests_SOURCES += dhcp6_srv_unittest.cc
dhcp6_unittests_SOURCES += fqdn_unittest.cc
dhcp6_unittests_SOURCES += hooks_unittest.cc
dhcp6_unittests_SOURCES += dhcp6_test_utils.cc dhcp6_test_utils.h
dhcp6_unittests_SOURCES += d2_unittest.cc d2_unittest.h
dhcp6_unittests_SOURCES += marker_file.cc
dhcp6_unittests_SOURCES += ../dhcp6_srv.h ../dhcp6_srv.cc
dhcp6_unittests_SOURCES += ../dhcp6_log.h ../dhcp6_log.cc
dhcp6_unittests_SOURCES += ../ctrl_dhcp6_srv.h ../ctrl_dhcp6_srv.cc
dhcp6_unittests_SOURCES += ctrl_dhcp6_srv_unittest.cc
dhcp6_unittests_SOURCES += wireshark.cc
dhcp6_unittests_SOURCES += dhcp6_client.cc dhcp6_client.h
dhcp6_unittests_SOURCES += rebind_unittest.cc
dhcp6_unittests_SOURCES += ../json_config_parser.cc ../json_config_parser.h
dhcp6_unittests_SOURCES += config_parser_unittest.cc

if CONFIG_BACKEND_BUNDY
# For Bundy backend, we only need to run the usual tests. There are no
# Bundy-specific tests yet.
dhcp6_unittests_SOURCES += ../bundy_controller.cc
dhcp6_unittests_SOURCES += bundy_backend_unittest.cc
endif

if CONFIG_BACKEND_JSON
dhcp6_unittests_SOURCES += ../jsonfile_controller.cc
dhcp6_unittests_SOURCES += jsonfile_backend_unittest.cc
endif

nodist_dhcp6_unittests_SOURCES  = ../dhcp6_messages.h ../dhcp6_messages.cc
nodist_dhcp6_unittests_SOURCES += marker_file.h test_libraries.h

dhcp6_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
dhcp6_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
dhcp6_unittests_LDADD = $(GTEST_LDADD)
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcp/tests/libdhcptest.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcp/tests/libdhcptest.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
endif

noinst_PROGRAMS = $(TESTS)
