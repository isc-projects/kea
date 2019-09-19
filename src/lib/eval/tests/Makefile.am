SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DLOGGING_SPEC_FILE=\"$(abs_top_srcdir)/src/lib/dhcpsrv/logging.spec\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += libeval_unittests

libeval_unittests_SOURCES  = boolean_unittest.cc
libeval_unittests_SOURCES += context_unittest.cc
libeval_unittests_SOURCES += dependency_unittest.cc
libeval_unittests_SOURCES += evaluate_unittest.cc
libeval_unittests_SOURCES += token_unittest.cc
libeval_unittests_SOURCES += run_unittests.cc
libeval_unittests_CXXFLAGS = $(AM_CXXFLAGS)
libeval_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libeval_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
libeval_unittests_LDADD    = $(top_builddir)/src/lib/eval/libkea-eval.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/cc/libkea-cc.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/dns/libkea-dns++.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/log/libkea-log.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/util/libkea-util.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/testutils/libkea-testutils.la
libeval_unittests_LDADD   += $(CRYPTO_LIBS) $(LOG4CPLUS_LIBS)
libeval_unittests_LDADD   += $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
