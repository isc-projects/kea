SUBDIRS = . testutils tests

dhcp_data_dir = @localstatedir@/@PACKAGE@

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib -DDHCP_DATA_DIR="\"$(dhcp_data_dir)\""
AM_CPPFLAGS += -DTOP_BUILDDIR="\"$(top_builddir)\""
AM_CPPFLAGS += $(BOOST_INCLUDES)
if HAVE_MYSQL
AM_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif
if HAVE_PGSQL
AM_CPPFLAGS += $(PGSQL_CPPFLAGS)
endif

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Define rule to build logging source files from message file
dhcpsrv_messages.h dhcpsrv_messages.cc: s-messages

s-messages: dhcpsrv_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/dhcpsrv/dhcpsrv_messages.mes
	touch $@

# Tell Automake that the dhcpsrv_messages.{cc,h} source files are created in the
# build process, so it must create these before doing anything else.  Although
# they are a dependency of the library (so will be created from the message file
# anyway), there is no guarantee as to exactly _when_ in the build they will be
# created.  As the .h file is included in other sources file (so must be
# present when they are compiled), the safest option is to create it first.
BUILT_SOURCES = dhcpsrv_messages.h dhcpsrv_messages.cc

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# Make sure the generated files are deleted in a "clean" operation
CLEANFILES = *.gcno *.gcda dhcpsrv_messages.h dhcpsrv_messages.cc s-messages
# Remove CSV files created by the CSVLeaseFile6 and CSVLeaseFile4 unit tests.
CLEANFILES += *.csv

lib_LTLIBRARIES = libkea-dhcpsrv.la
libkea_dhcpsrv_la_SOURCES  =
libkea_dhcpsrv_la_SOURCES += addr_utilities.cc addr_utilities.h
libkea_dhcpsrv_la_SOURCES += alloc_engine.cc alloc_engine.h
libkea_dhcpsrv_la_SOURCES += callout_handle_store.h
libkea_dhcpsrv_la_SOURCES += csv_lease_file4.cc csv_lease_file4.h
libkea_dhcpsrv_la_SOURCES += csv_lease_file6.cc csv_lease_file6.h
libkea_dhcpsrv_la_SOURCES += d2_client_cfg.cc d2_client_cfg.h
libkea_dhcpsrv_la_SOURCES += d2_client_mgr.cc d2_client_mgr.h
libkea_dhcpsrv_la_SOURCES += daemon.cc daemon.h
libkea_dhcpsrv_la_SOURCES += dbaccess_parser.cc dbaccess_parser.h
libkea_dhcpsrv_la_SOURCES += dhcpsrv_log.cc dhcpsrv_log.h
libkea_dhcpsrv_la_SOURCES += cfgmgr.cc cfgmgr.h
libkea_dhcpsrv_la_SOURCES += dhcp_config_parser.h
libkea_dhcpsrv_la_SOURCES += dhcp_parsers.cc dhcp_parsers.h
libkea_dhcpsrv_la_SOURCES += key_from_key.h
libkea_dhcpsrv_la_SOURCES += lease.cc lease.h
libkea_dhcpsrv_la_SOURCES += lease_mgr.cc lease_mgr.h
libkea_dhcpsrv_la_SOURCES += lease_mgr_factory.cc lease_mgr_factory.h
libkea_dhcpsrv_la_SOURCES += logging.cc logging.h
libkea_dhcpsrv_la_SOURCES += configuration.h configuration.cc
libkea_dhcpsrv_la_SOURCES += memfile_lease_mgr.cc memfile_lease_mgr.h

if HAVE_MYSQL
libkea_dhcpsrv_la_SOURCES += mysql_lease_mgr.cc mysql_lease_mgr.h
endif
if HAVE_PGSQL
libkea_dhcpsrv_la_SOURCES += pgsql_lease_mgr.cc pgsql_lease_mgr.h
endif
libkea_dhcpsrv_la_SOURCES += option_space_container.h
libkea_dhcpsrv_la_SOURCES += pool.cc pool.h
libkea_dhcpsrv_la_SOURCES += subnet.cc subnet.h
libkea_dhcpsrv_la_SOURCES += triplet.h
libkea_dhcpsrv_la_SOURCES += utils.h

nodist_libkea_dhcpsrv_la_SOURCES = dhcpsrv_messages.h dhcpsrv_messages.cc

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
EXTRA_DIST = dhcpsrv_messages.mes

# Distribute MySQL schema creation script and backend documentation
EXTRA_DIST += dhcpdb_create.mysql dhcpdb_create.pgsql database_backends.dox libdhcpsrv.dox
dist_pkgdata_DATA = dhcpdb_create.mysql dhcpdb_create.pgsql

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(dhcp_data_dir)


