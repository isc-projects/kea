SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/dhcp/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libdhcpsrv_unittests

libdhcpsrv_unittests_SOURCES  = run_unittests.cc
libdhcpsrv_unittests_SOURCES += addr_utilities_unittest.cc
libdhcpsrv_unittests_SOURCES += alloc_engine_unittest.cc
libdhcpsrv_unittests_SOURCES += cfgmgr_unittest.cc
libdhcpsrv_unittests_SOURCES += hwaddr_unittest.cc
libdhcpsrv_unittests_SOURCES += lease_mgr_factory_unittest.cc
libdhcpsrv_unittests_SOURCES += lease_mgr_unittest.cc
libdhcpsrv_unittests_SOURCES += memfile_lease_mgr_unittest.cc
if HAVE_MYSQL
libdhcpsrv_unittests_SOURCES += mysql_lease_mgr_unittest.cc
endif
libdhcpsrv_unittests_SOURCES += pool_unittest.cc
libdhcpsrv_unittests_SOURCES += schema_copy.h
libdhcpsrv_unittests_SOURCES += subnet_unittest.cc
libdhcpsrv_unittests_SOURCES += triplet_unittest.cc

libdhcpsrv_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)
if HAVE_MYSQL
libdhcpsrv_unittests_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif

libdhcpsrv_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)
if HAVE_MYSQL
libdhcpsrv_unittests_LDFLAGS  += $(MYSQL_LIBS)
endif

libdhcpsrv_unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# This is to workaround unused variables tcout and tcerr in
# log4cplus's streams.h and unused parameters from some of the
# Boost headers.
libdhcpsrv_unittests_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter
endif

libdhcpsrv_unittests_LDADD  = $(top_builddir)/src/lib/dhcpsrv/libb10-dhcpsrv.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
libdhcpsrv_unittests_LDADD += $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
