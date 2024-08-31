SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/user_chk -I$(top_srcdir)/src/hooks/dhcp/user_chk
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_srcdir)/src/hooks/dhcp/user_chk/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

USER_CHK_LIB = $(top_builddir)/src/hooks/dhcp/user_chk/libdhcp_user_chk.la

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST = test_users_1.txt test_users_err.txt

CLEANFILES = *.gcno *.gcda
DISTCLEANFILES = test_data_files_config.h

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libdhcp_user_chk_unittests

libdhcp_user_chk_unittests_SOURCES  = 
libdhcp_user_chk_unittests_SOURCES += run_unittests.cc
libdhcp_user_chk_unittests_SOURCES += userid_unittests.cc
libdhcp_user_chk_unittests_SOURCES += user_unittests.cc
libdhcp_user_chk_unittests_SOURCES += user_registry_unittests.cc
libdhcp_user_chk_unittests_SOURCES += user_file_unittests.cc

libdhcp_user_chk_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

libdhcp_user_chk_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

libdhcp_user_chk_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libdhcp_user_chk_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/user_chk/libduc.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_user_chk_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_user_chk_unittests_LDADD += $(LOG4CPLUS_LIBS)
libdhcp_user_chk_unittests_LDADD += $(CRYPTO_LIBS)
libdhcp_user_chk_unittests_LDADD += $(BOOST_LIBS)
libdhcp_user_chk_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
