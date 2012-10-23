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
TESTS += libdhcp++_unittests libdhcpsrv_unittests
libdhcp___unittests_SOURCES  = run_unittests.cc
libdhcp___unittests_SOURCES += libdhcp++_unittest.cc
libdhcp___unittests_SOURCES += iface_mgr_unittest.cc
libdhcp___unittests_SOURCES += lease_mgr_unittest.cc
libdhcp___unittests_SOURCES += option6_iaaddr_unittest.cc
libdhcp___unittests_SOURCES += option6_ia_unittest.cc
libdhcp___unittests_SOURCES += option6_addrlst_unittest.cc
libdhcp___unittests_SOURCES += option4_addrlst_unittest.cc
libdhcp___unittests_SOURCES += option6_int_unittest.cc
libdhcp___unittests_SOURCES += option6_int_array_unittest.cc
libdhcp___unittests_SOURCES += option_unittest.cc
libdhcp___unittests_SOURCES += option_definition_unittest.cc
libdhcp___unittests_SOURCES += pkt6_unittest.cc
libdhcp___unittests_SOURCES += pkt4_unittest.cc
libdhcp___unittests_SOURCES += duid_unittest.cc

libdhcp___unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)
libdhcp___unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)
libdhcp___unittests_CXXFLAGS = $(AM_CXXFLAGS)

libdhcpsrv_unittests_SOURCES  = run_unittests.cc
libdhcpsrv_unittests_SOURCES += cfgmgr_unittest.cc triplet_unittest.cc
libdhcpsrv_unittests_SOURCES += pool_unittest.cc subnet_unittest.cc
libdhcpsrv_unittests_SOURCES += addr_utilities_unittest.cc

libdhcpsrv_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)
libdhcpsrv_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)
libdhcpsrv_unittests_CXXFLAGS = $(AM_CXXFLAGS)
libdhcpsrv_unittests_LDADD  = $(GTEST_LDADD)
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libb10-dhcpsrv.la
libdhcpsrv_unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la


if USE_CLANGPP
# This is to workaround unused variables tcout and tcerr in
# log4cplus's streams.h and unused parameters from some of the
# Boost headers.
libdhcp___unittests_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter
libdhcpsrv_unittests_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter
endif

libdhcp___unittests_LDADD  = $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
libdhcp___unittests_LDADD += $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
