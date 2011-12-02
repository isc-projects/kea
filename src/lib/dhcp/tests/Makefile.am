SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += libdhcp_unittests
libdhcp_unittests_SOURCES  = run_unittests.cc
libdhcp_unittests_SOURCES += ../libdhcp++.h ../libdhcp++.cc
libdhcp_unittests_SOURCES += libdhcp++_unittest.cc
libdhcp_unittests_SOURCES += ../option6_iaaddr.h ../option6_iaaddr.cc option6_iaaddr_unittest.cc
libdhcp_unittests_SOURCES += ../option6_ia.h ../option6_ia.cc option6_ia_unittest.cc
libdhcp_unittests_SOURCES += ../option6_addrlst.h ../option6_addrlst.cc option6_addrlst_unittest.cc
libdhcp_unittests_SOURCES += ../option.h ../option.cc option_unittest.cc
libdhcp_unittests_SOURCES += ../pkt6.h ../pkt6.cc pkt6_unittest.cc
libdhcp_unittests_SOURCES += ../pkt4.h ../pkt4.cc pkt4_unittest.cc

libdhcp_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)
libdhcp_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

libdhcp_unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# This is to workaround unused variables tcout and tcerr in
# log4cplus's streams.h.
libdhcp_unittests_CXXFLAGS += -Wno-unused-variable
endif
libdhcp_unittests_LDADD  = $(GTEST_LDADD)
libdhcp_unittests_LDADD += $(top_builddir)/src/lib/log/liblog.la
libdhcp_unittests_LDADD += $(top_builddir)/src/lib/util/libutil.la
libdhcp_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
libdhcp_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
endif

noinst_PROGRAMS = $(TESTS)
