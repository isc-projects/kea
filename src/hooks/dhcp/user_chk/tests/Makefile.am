SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/user_chk -I$(top_srcdir)/src/hooks/dhcp/user_chk
AM_CPPFLAGS += $(BOOST_INCLUDES) $(BOTAN_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_srcdir)/src/hooks/dhcp/user_chk/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

USER_CHK_LIB = $(top_builddir)/src/hooks/dhcp/user_chk/libdhcp_user_chk.la

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST = test_users_1.txt test_users_err.txt

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libdhcp_user_chk_unittests

libdhcp_user_chk_unittests_SOURCES  = 
libdhcp_user_chk_unittests_SOURCES += ../load_unload.cc
libdhcp_user_chk_unittests_SOURCES += ../pkt_receive_co.cc
libdhcp_user_chk_unittests_SOURCES += ../pkt_send_co.cc
libdhcp_user_chk_unittests_SOURCES += ../subnet_select_co.cc
libdhcp_user_chk_unittests_SOURCES += ../version.cc
libdhcp_user_chk_unittests_SOURCES += ../user.cc ../user.h
libdhcp_user_chk_unittests_SOURCES += ../user_chk.h
# Until logging in dynamically loaded libraries is fixed, exclude these.
#libdhcp_user_chk_unittests_SOURCES += ../user_chk_log.cc ../user_chk_log.h
#libdhcp_user_chk_unittests_SOURCES += ../user_chk_messages.cc ../user_chk_messages.h
libdhcp_user_chk_unittests_SOURCES += ../user_data_source.h
libdhcp_user_chk_unittests_SOURCES += ../user_file.cc ../user_file.h
libdhcp_user_chk_unittests_SOURCES += ../user_registry.cc ../user_registry.h
libdhcp_user_chk_unittests_SOURCES += run_unittests.cc
libdhcp_user_chk_unittests_SOURCES += userid_unittests.cc
libdhcp_user_chk_unittests_SOURCES += user_unittests.cc
libdhcp_user_chk_unittests_SOURCES += user_registry_unittests.cc
libdhcp_user_chk_unittests_SOURCES += user_file_unittests.cc

libdhcp_user_chk_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

libdhcp_user_chk_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

libdhcp_user_chk_unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# This is to workaround unused variables tcout and tcerr in
# log4cplus's streams.h and unused parameters from some of the
# Boost headers.
libdhcp_user_chk_unittests_CXXFLAGS += -Wno-unused-parameter
endif

libdhcp_user_chk_unittests_LDADD = $(top_builddir)/src/lib/log/libb10-log.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/hooks/libb10-hooks.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
libdhcp_user_chk_unittests_LDADD += ${BOTAN_LIBS} ${BOTAN_RPATH}
libdhcp_user_chk_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
