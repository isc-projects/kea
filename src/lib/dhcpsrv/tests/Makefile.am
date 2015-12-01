SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/dhcpsrv/tests\"
AM_CPPFLAGS += -DDHCP_DATA_DIR=\"$(abs_top_builddir)/src/lib/dhcpsrv/tests\"
AM_CPPFLAGS += -DKEA_LFC_BUILD_DIR=\"$(abs_top_builddir)/src/bin/lfc\"
AM_CPPFLAGS += -DLOGGING_SPEC_FILE=\"$(abs_top_srcdir)/src/lib/dhcpsrv/logging.spec\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

CLEANFILES = *.gcno *.gcda

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

libco1_la_SOURCES  = callout_library.cc
libco1_la_CXXFLAGS = $(AM_CXXFLAGS)
libco1_la_CPPFLAGS = $(AM_CPPFLAGS)
libco1_la_LDFLAGS = -avoid-version -export-dynamic -module -rpath /nowhere

libco2_la_SOURCES  = callout_library.cc
libco2_la_CXXFLAGS = $(AM_CXXFLAGS)
libco2_la_CPPFLAGS = $(AM_CPPFLAGS)
libco2_la_LDFLAGS = -avoid-version -export-dynamic -module -rpath /nowhere

TESTS += libdhcpsrv_unittests

libdhcpsrv_unittests_SOURCES  = run_unittests.cc
libdhcpsrv_unittests_SOURCES += addr_utilities_unittest.cc
libdhcpsrv_unittests_SOURCES += alloc_engine_utils.cc alloc_engine_utils.h
libdhcpsrv_unittests_SOURCES += alloc_engine_expiration_unittest.cc
libdhcpsrv_unittests_SOURCES += alloc_engine_hooks_unittest.cc
libdhcpsrv_unittests_SOURCES += alloc_engine4_unittest.cc
libdhcpsrv_unittests_SOURCES += alloc_engine6_unittest.cc
libdhcpsrv_unittests_SOURCES += callout_handle_store_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_duid_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_expiration_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_hosts_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_iface_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_mac_source_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_option_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_option_def_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_rsoo_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_subnets4_unittest.cc
libdhcpsrv_unittests_SOURCES += cfg_subnets6_unittest.cc
libdhcpsrv_unittests_SOURCES += cfgmgr_unittest.cc
libdhcpsrv_unittests_SOURCES += client_class_def_unittest.cc
libdhcpsrv_unittests_SOURCES += client_class_def_parser_unittest.cc
libdhcpsrv_unittests_SOURCES += csv_lease_file4_unittest.cc
libdhcpsrv_unittests_SOURCES += csv_lease_file6_unittest.cc
libdhcpsrv_unittests_SOURCES += d2_client_unittest.cc
libdhcpsrv_unittests_SOURCES += d2_udp_unittest.cc
libdhcpsrv_unittests_SOURCES += daemon_unittest.cc
libdhcpsrv_unittests_SOURCES += database_connection_unittest.cc
libdhcpsrv_unittests_SOURCES += dbaccess_parser_unittest.cc
libdhcpsrv_unittests_SOURCES += duid_config_parser_unittest.cc
libdhcpsrv_unittests_SOURCES += expiration_config_parser_unittest.cc
libdhcpsrv_unittests_SOURCES += host_mgr_unittest.cc
libdhcpsrv_unittests_SOURCES += host_unittest.cc
libdhcpsrv_unittests_SOURCES += host_reservation_parser_unittest.cc
libdhcpsrv_unittests_SOURCES += host_reservations_list_parser_unittest.cc
libdhcpsrv_unittests_SOURCES += ifaces_config_parser_unittest.cc
libdhcpsrv_unittests_SOURCES += lease_file_io.cc lease_file_io.h
libdhcpsrv_unittests_SOURCES += lease_file_loader_unittest.cc
libdhcpsrv_unittests_SOURCES += lease_unittest.cc
libdhcpsrv_unittests_SOURCES += lease_mgr_factory_unittest.cc
libdhcpsrv_unittests_SOURCES += lease_mgr_unittest.cc
libdhcpsrv_unittests_SOURCES += logging_unittest.cc
libdhcpsrv_unittests_SOURCES += logging_info_unittest.cc
libdhcpsrv_unittests_SOURCES += generic_lease_mgr_unittest.cc generic_lease_mgr_unittest.h
libdhcpsrv_unittests_SOURCES += generic_host_data_source_unittest.cc generic_host_data_source_unittest.h
libdhcpsrv_unittests_SOURCES += memfile_lease_mgr_unittest.cc
libdhcpsrv_unittests_SOURCES += dhcp_parsers_unittest.cc
if HAVE_MYSQL
libdhcpsrv_unittests_SOURCES += mysql_lease_mgr_unittest.cc
libdhcpsrv_unittests_SOURCES += mysql_host_data_source_unittest.cc
endif

libdhcpsrv_unittests_SOURCES += ncr_generator_unittest.cc

if HAVE_PGSQL
libdhcpsrv_unittests_SOURCES += pgsql_lease_mgr_unittest.cc
endif
libdhcpsrv_unittests_SOURCES += pool_unittest.cc
libdhcpsrv_unittests_SOURCES += schema_mysql_copy.h
libdhcpsrv_unittests_SOURCES += schema_pgsql_copy.h
libdhcpsrv_unittests_SOURCES += srv_config_unittest.cc
libdhcpsrv_unittests_SOURCES += subnet_unittest.cc
libdhcpsrv_unittests_SOURCES += test_get_callout_handle.cc test_get_callout_handle.h
libdhcpsrv_unittests_SOURCES += triplet_unittest.cc
libdhcpsrv_unittests_SOURCES += test_utils.cc test_utils.h
libdhcpsrv_unittests_SOURCES += timer_mgr_unittest.cc

libdhcpsrv_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
if HAVE_MYSQL
libdhcpsrv_unittests_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif
if HAVE_PGSQL
libdhcpsrv_unittests_CPPFLAGS += $(PGSQL_CPPFLAGS)
endif

libdhcpsrv_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
if HAVE_MYSQL
libdhcpsrv_unittests_LDFLAGS  += $(MYSQL_LIBS)
endif
if HAVE_PGSQL
libdhcpsrv_unittests_LDFLAGS  += $(PGSQL_LIBS)
endif

libdhcpsrv_unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# This is to workaround unused variables tcout and tcerr in
# log4cplus's streams.h and unused parameters from some of the
# Boost headers.
libdhcpsrv_unittests_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter
endif

libdhcpsrv_unittests_LDADD  = $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/dhcp/tests/libdhcptest.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
libdhcpsrv_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
libdhcpsrv_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
