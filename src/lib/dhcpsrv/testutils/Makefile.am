SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -DDATABASE_SCRIPTS_DIR=\"$(abs_top_srcdir)/src/share/database/scripts\"
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libdhcpsrvtest.la

libdhcpsrvtest_la_SOURCES  = config_result_check.cc config_result_check.h
libdhcpsrvtest_la_SOURCES += dhcp4o6_test_ipc.cc dhcp4o6_test_ipc.h
libdhcpsrvtest_la_SOURCES += host_data_source_utils.cc host_data_source_utils.h
libdhcpsrvtest_la_SOURCES += memory_host_data_source.cc memory_host_data_source.h
libdhcpsrvtest_la_SOURCES += test_utils.cc test_utils.h
libdhcpsrvtest_la_SOURCES += generic_backend_unittest.cc generic_backend_unittest.h
libdhcpsrvtest_la_SOURCES += generic_host_data_source_unittest.cc generic_host_data_source_unittest.h
libdhcpsrvtest_la_SOURCES += generic_cb_dhcp4_unittest.h generic_cb_dhcp4_unittest.cc
libdhcpsrvtest_la_SOURCES += generic_cb_recovery_unittest.h generic_cb_recovery_unittest.cc
libdhcpsrvtest_la_SOURCES += lease_file_io.cc lease_file_io.h
libdhcpsrvtest_la_SOURCES += test_config_backend.h
libdhcpsrvtest_la_SOURCES += test_config_backend_dhcp4.cc test_config_backend_dhcp4.h
libdhcpsrvtest_la_SOURCES += test_config_backend_dhcp6.cc test_config_backend_dhcp6.h

if HAVE_MYSQL
libdhcpsrvtest_la_SOURCES += mysql_generic_backend_unittest.cc mysql_generic_backend_unittest.h
endif

if HAVE_PGSQL
libdhcpsrvtest_la_SOURCES += pgsql_generic_backend_unittest.cc pgsql_generic_backend_unittest.h
endif

libdhcpsrvtest_la_CXXFLAGS = $(AM_CXXFLAGS)
libdhcpsrvtest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

libdhcpsrvtest_la_LIBADD =

if HAVE_MYSQL
libdhcpsrvtest_la_CPPFLAGS += $(MYSQL_CPPFLAGS)
libdhcpsrvtest_la_LIBADD  += $(top_builddir)/src/lib/mysql/libkea-mysql.la
endif
if HAVE_PGSQL
libdhcpsrvtest_la_CPPFLAGS += $(PGSQL_CPPFLAGS)
libdhcpsrvtest_la_LIBADD  += $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
endif
if HAVE_CQL
libdhcpsrvtest_la_CPPFLAGS += $(CQL_CPPFLAGS)
libdhcpsrvtest_la_LIBADD  += $(top_builddir)/src/lib/cql/libkea-cql.la
endif

libdhcpsrvtest_la_LDFLAGS  = $(AM_LDFLAGS)
if HAVE_MYSQL
libdhcpsrvtest_la_LDFLAGS  += $(MYSQL_LIBS)
endif
if HAVE_PGSQL
libdhcpsrvtest_la_LDFLAGS  += $(PGSQL_LIBS)
endif
if HAVE_CQL
libdhcpsrvtest_la_LDFLAGS  += $(CQL_LIBS)
endif


libdhcpsrvtest_la_LIBADD  += $(top_builddir)/src/lib/database/libkea-database.la
libdhcpsrvtest_la_LIBADD  += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcpsrvtest_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la

endif
