SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
if HAVE_MYSQL
AM_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif

AM_CXXFLAGS = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libb10-dhcpsrv.la
libb10_dhcpsrv_la_SOURCES  =
libb10_dhcpsrv_la_SOURCES += addr_utilities.cc addr_utilities.h
libb10_dhcpsrv_la_SOURCES += alloc_engine.cc alloc_engine.h
libb10_dhcpsrv_la_SOURCES += cfgmgr.cc cfgmgr.h
libb10_dhcpsrv_la_SOURCES += lease_mgr.cc lease_mgr.h
libb10_dhcpsrv_la_SOURCES += lease_mgr_factory.cc lease_mgr_factory.h
libb10_dhcpsrv_la_SOURCES += memfile_lease_mgr.cc memfile_lease_mgr.h
if HAVE_MYSQL
libb10_dhcpsrv_la_SOURCES += mysql_lease_mgr.cc mysql_lease_mgr.h
endif
libb10_dhcpsrv_la_SOURCES += pool.cc pool.h
libb10_dhcpsrv_la_SOURCES += subnet.cc subnet.h
libb10_dhcpsrv_la_SOURCES += triplet.h

libb10_dhcpsrv_la_CXXFLAGS = $(AM_CXXFLAGS)
libb10_dhcpsrv_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libb10_dhcpsrv_la_LIBADD   = $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
libb10_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
libb10_dhcpsrv_la_LIBADD  += $(top_builddir)/src/lib/util/libb10-util.la
libb10_dhcpsrv_la_LDFLAGS  = -no-undefined -version-info 2:0:0
if HAVE_MYSQL
libb10_dhcpsrv_la_LDFLAGS += $(MYSQL_LIBS)
endif

if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libb10_dhcpsrv_la_CXXFLAGS += -Wno-unused-parameter
endif

# Distribute MySQL schema creation script and backend documentation
EXTRA_DIST = dhcpdb_create.mysql database_backends.dox libdhcpsrv.dox
dist_pkgdata_DATA = dhcpdb_create.mysql
