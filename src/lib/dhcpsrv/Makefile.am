AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS = . testutils tests

dhcp_data_dir = @localstatedir@/@PACKAGE@
kea_lfc_location = @prefix@/sbin/kea-lfc

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib -DDHCP_DATA_DIR="\"$(dhcp_data_dir)\""
AM_CPPFLAGS += -DTOP_BUILDDIR="\"$(top_builddir)\""
# Set location of the kea-lfc binary.
AM_CPPFLAGS += -DKEA_LFC_EXECUTABLE="\"$(kea_lfc_location)\""
AM_CPPFLAGS += $(BOOST_INCLUDES)
if HAVE_MYSQL
AM_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif
if HAVE_PGSQL
AM_CPPFLAGS += $(PGSQL_CPPFLAGS)
endif

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# The files in the subfolder must be explicitly specified here so
# as they are copied to the distribution. The other option would
# be to specify a whole 'parsers' folder here but that would also
# copy all other files, e.g. gitignore, .git etc.
# Whenever new file is added to the parsers folder, it must be
# added here.
EXTRA_DIST =
EXTRA_DIST += parsers/dbaccess_parser.cc
EXTRA_DIST += parsers/dbaccess_parser.h
EXTRA_DIST += parsers/dhcp_parsers.cc
EXTRA_DIST += parsers/dhcp_parsers.h
EXTRA_DIST += parsers/host_reservation_parser.cc
EXTRA_DIST += parsers/host_reservation_parser.h
EXTRA_DIST += parsers/host_reservations_list_parser.h

# Define rule to build logging source files from message file
alloc_engine_messages.h alloc_engine_messages.cc dhcpsrv_messages.h \
dhcpsrv_messages.cc hosts_messages.h hosts_messages.cc: s-messages

s-messages: alloc_engine_messages.mes dhcpsrv_messages.mes hosts_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/dhcpsrv/alloc_engine_messages.mes
	touch $@
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/dhcpsrv/dhcpsrv_messages.mes
	touch $@
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/dhcpsrv/hosts_messages.mes
	touch $@

# Tell Automake that the {alloc_engine,dhcpsrv,hosts}_messages.{cc,h} source files
# are created in the build process, so it must create these before doing anything
# else. Although they are a dependency of the library (so will be created from the
# message file anyway), there is no guarantee as to exactly _when_ in the build
# they will be created.  As the .h file is included in other sources file (so
# must be present when they are compiled), the safest option is to create it
# first.
BUILT_SOURCES = alloc_engine_messages.h alloc_engine_messages.cc
BUILT_SOURCES += dhcpsrv_messages.h dhcpsrv_messages.cc
BUILT_SOURCES += hosts_messages.h hosts_messages.cc

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# Make sure the generated files are deleted in a "clean" operation
CLEANFILES = *.gcno *.gcda
CLEANFILES += alloc_engine_messages.h alloc_engine_messages.cc
CLEANFILES += dhcpsrv_messages.h dhcpsrv_messages.cc
CLEANFILES += hosts_messages.h hosts_messages.cc s-messages
# Remove CSV files created by the CSVLeaseFile6 and CSVLeaseFile4 unit tests.
CLEANFILES += *.csv

lib_LTLIBRARIES = libkea-dhcpsrv.la
libkea_dhcpsrv_la_SOURCES  =
libkea_dhcpsrv_la_SOURCES += addr_utilities.cc addr_utilities.h
libkea_dhcpsrv_la_SOURCES += alloc_engine.cc alloc_engine.h
libkea_dhcpsrv_la_SOURCES += alloc_engine_log.cc alloc_engine_log.h
libkea_dhcpsrv_la_SOURCES += base_host_data_source.h
libkea_dhcpsrv_la_SOURCES += callout_handle_store.h
libkea_dhcpsrv_la_SOURCES += cfg_hosts.cc cfg_hosts.h
libkea_dhcpsrv_la_SOURCES += cfg_iface.cc cfg_iface.h
libkea_dhcpsrv_la_SOURCES += cfg_option.cc cfg_option.h
libkea_dhcpsrv_la_SOURCES += cfg_option_def.cc cfg_option_def.h
libkea_dhcpsrv_la_SOURCES += cfg_rsoo.cc cfg_rsoo.h
libkea_dhcpsrv_la_SOURCES += cfg_subnets4.cc cfg_subnets4.h
libkea_dhcpsrv_la_SOURCES += cfg_subnets6.cc cfg_subnets6.h
libkea_dhcpsrv_la_SOURCES += cfg_mac_source.cc cfg_mac_source.h
libkea_dhcpsrv_la_SOURCES += cfgmgr.cc cfgmgr.h
libkea_dhcpsrv_la_SOURCES += csv_lease_file4.cc csv_lease_file4.h
libkea_dhcpsrv_la_SOURCES += csv_lease_file6.cc csv_lease_file6.h
libkea_dhcpsrv_la_SOURCES += d2_client_cfg.cc d2_client_cfg.h
libkea_dhcpsrv_la_SOURCES += d2_client_mgr.cc d2_client_mgr.h
libkea_dhcpsrv_la_SOURCES += daemon.cc daemon.h
libkea_dhcpsrv_la_SOURCES += dhcpsrv_log.cc dhcpsrv_log.h
libkea_dhcpsrv_la_SOURCES += host.cc host.h
libkea_dhcpsrv_la_SOURCES += host_container.h
libkea_dhcpsrv_la_SOURCES += host_mgr.cc host_mgr.h
libkea_dhcpsrv_la_SOURCES += hosts_log.cc hosts_log.h
libkea_dhcpsrv_la_SOURCES += key_from_key.h
libkea_dhcpsrv_la_SOURCES += lease.cc lease.h
libkea_dhcpsrv_la_SOURCES += lease_file_loader.h
libkea_dhcpsrv_la_SOURCES += lease_file_stats.h
libkea_dhcpsrv_la_SOURCES += lease_mgr.cc lease_mgr.h
libkea_dhcpsrv_la_SOURCES += lease_mgr_factory.cc lease_mgr_factory.h
libkea_dhcpsrv_la_SOURCES += logging.cc logging.h
libkea_dhcpsrv_la_SOURCES += logging_info.cc logging_info.h
libkea_dhcpsrv_la_SOURCES += memfile_lease_mgr.cc memfile_lease_mgr.h
libkea_dhcpsrv_la_SOURCES += memfile_lease_storage.h

if HAVE_MYSQL
libkea_dhcpsrv_la_SOURCES += mysql_lease_mgr.cc mysql_lease_mgr.h
endif
if HAVE_PGSQL
libkea_dhcpsrv_la_SOURCES += pgsql_lease_mgr.cc pgsql_lease_mgr.h
endif
libkea_dhcpsrv_la_SOURCES += option_space_container.h
libkea_dhcpsrv_la_SOURCES += pool.cc pool.h
libkea_dhcpsrv_la_SOURCES += srv_config.cc srv_config.h
libkea_dhcpsrv_la_SOURCES += subnet.cc subnet.h
libkea_dhcpsrv_la_SOURCES += subnet_id.h
libkea_dhcpsrv_la_SOURCES += subnet_selector.h
libkea_dhcpsrv_la_SOURCES += triplet.h
libkea_dhcpsrv_la_SOURCES += utils.h
libkea_dhcpsrv_la_SOURCES += writable_host_data_source.h

# Configuration parsers
libkea_dhcpsrv_la_SOURCES += parsers/dhcp_config_parser.h
libkea_dhcpsrv_la_SOURCES += parsers/dbaccess_parser.cc
libkea_dhcpsrv_la_SOURCES += parsers/dbaccess_parser.h
libkea_dhcpsrv_la_SOURCES += parsers/dhcp_parsers.cc
libkea_dhcpsrv_la_SOURCES += parsers/dhcp_parsers.h
libkea_dhcpsrv_la_SOURCES += parsers/host_reservation_parser.cc
libkea_dhcpsrv_la_SOURCES += parsers/host_reservation_parser.h
libkea_dhcpsrv_la_SOURCES += parsers/host_reservations_list_parser.h
libkea_dhcpsrv_la_SOURCES += parsers/ifaces_config_parser.cc
libkea_dhcpsrv_la_SOURCES += parsers/ifaces_config_parser.h

nodist_libkea_dhcpsrv_la_SOURCES = alloc_engine__messages.h
nodist_libkea_dhcpsrv_la_SOURCES += alloc_engine_messages.cc
nodist_libkea_dhcpsrv_la_SOURCES += dhcpsrv_messages.h dhcpsrv_messages.cc
nodist_libkea_dhcpsrv_la_SOURCES += hosts_messages.h hosts_messages.cc

libkea_dhcpsrv_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_dhcpsrv_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libkea_dhcpsrv_la_LIBADD   = $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libkea_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libkea_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libkea_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libkea_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/util/libkea-util.la
libkea_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libkea_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

libkea_dhcpsrv_la_LDFLAGS  = -no-undefined -version-info 3:0:0
if HAVE_MYSQL
libkea_dhcpsrv_la_LDFLAGS += $(MYSQL_LIBS)
endif
if HAVE_PGSQL
libkea_dhcpsrv_la_LDFLAGS += $(PGSQL_LIBS)
endif

if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libkea_dhcpsrv_la_CXXFLAGS += -Wno-unused-parameter
endif

# The message file should be in the distribution
EXTRA_DIST += alloc_engine_messages.mes
EXTRA_DIST += dhcpsrv_messages.mes
EXTRA_DIST += hosts_messages.mes

# Distribute backend documentation
# Database schema creation script moved to src/bin/admin
EXTRA_DIST += database_backends.dox libdhcpsrv.dox

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(dhcp_data_dir)


