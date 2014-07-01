SHTESTS =
# The test of dynamic reconfiguration based on signals will work only
# if we are using file based configuration approach.
if CONFIG_BACKEND_JSON
SHTESTS += d2_process_tests.sh
endif

noinst_SCRIPTS = d2_process_tests.sh

EXTRA_DIST  = d2_process_tests.sh.in

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	export B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/d2/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

CLEANFILES = $(builddir)/interfaces.txt $(builddir)/logger_lockfile

DISTCLEANFILES = d2_process_tests.sh

AM_CXXFLAGS = $(B10_CXXFLAGS)
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

TESTS += d2_unittests

d2_unittests_SOURCES = ../d2_asio.h
d2_unittests_SOURCES += ../d2_log.h ../d2_log.cc
d2_unittests_SOURCES += ../d_process.h
d2_unittests_SOURCES += ../d_controller.cc ../d_controller.h
d2_unittests_SOURCES += ../d_cfg_mgr.cc ../d_cfg_mgr.h
d2_unittests_SOURCES += ../d2_process.cc ../d2_process.h
d2_unittests_SOURCES += ../d2_config.cc ../d2_config.h
d2_unittests_SOURCES += ../d2_cfg_mgr.cc ../d2_cfg_mgr.h
d2_unittests_SOURCES += ../d2_queue_mgr.cc ../d2_queue_mgr.h
d2_unittests_SOURCES += ../d2_update_message.cc ../d2_update_message.h
d2_unittests_SOURCES += ../d2_update_mgr.cc ../d2_update_mgr.h
d2_unittests_SOURCES += ../d2_zone.cc ../d2_zone.h
d2_unittests_SOURCES += ../dns_client.cc ../dns_client.h
d2_unittests_SOURCES += ../io_service_signal.cc ../io_service_signal.h
d2_unittests_SOURCES += ../labeled_value.cc ../labeled_value.h
d2_unittests_SOURCES += ../nc_add.cc ../nc_add.h
d2_unittests_SOURCES += ../nc_remove.cc ../nc_remove.h
d2_unittests_SOURCES += ../nc_trans.cc ../nc_trans.h
d2_unittests_SOURCES += ../state_model.cc ../state_model.h
d2_unittests_SOURCES += d_test_stubs.cc d_test_stubs.h
d2_unittests_SOURCES += d2_unittests.cc
d2_unittests_SOURCES += d2_process_unittests.cc
d2_unittests_SOURCES += d_cfg_mgr_unittests.cc
d2_unittests_SOURCES += d2_cfg_mgr_unittests.cc
d2_unittests_SOURCES += d2_queue_mgr_unittests.cc
d2_unittests_SOURCES += d2_update_message_unittests.cc
d2_unittests_SOURCES += d2_update_mgr_unittests.cc
d2_unittests_SOURCES += d2_zone_unittests.cc
d2_unittests_SOURCES += dns_client_unittests.cc
d2_unittests_SOURCES += io_service_signal_unittests.cc
d2_unittests_SOURCES += labeled_value_unittests.cc
d2_unittests_SOURCES += nc_add_unittests.cc
d2_unittests_SOURCES += nc_remove_unittests.cc
d2_unittests_SOURCES += nc_test_utils.cc nc_test_utils.h
d2_unittests_SOURCES += nc_trans_unittests.cc
d2_unittests_SOURCES += state_model_unittests.cc
nodist_d2_unittests_SOURCES = ../d2_messages.h ../d2_messages.cc

if CONFIG_BACKEND_BUNDY
d2_unittests_SOURCES += ../bundy_d2_controller.cc ../bundy_d2_controller.h
d2_unittests_SOURCES += bundy_d2_controller_unittests.cc
else
if CONFIG_BACKEND_JSON
d2_unittests_SOURCES += ../d2_controller.cc ../d2_controller.h
d2_unittests_SOURCES += d2_controller_unittests.cc
d2_unittests_SOURCES += d_controller_unittests.cc
endif
endif

d2_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
d2_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
d2_unittests_LDADD = $(GTEST_LDADD)
d2_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
d2_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
d2_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
d2_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
d2_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
d2_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
d2_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
d2_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la

endif

noinst_PROGRAMS = $(TESTS)
