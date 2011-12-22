AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.h
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc
run_unittests_SOURCES += resolve_unittest.cc
run_unittests_SOURCES += resolver_callback_unittest.cc
run_unittests_SOURCES += response_classifier_unittest.cc
run_unittests_SOURCES += recursive_query_unittest.cc
run_unittests_SOURCES += recursive_query_unittest_2.cc
run_unittests_SOURCES += recursive_query_unittest_3.cc

run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD +=  $(top_builddir)/src/lib/nsas/libnsas.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/cache/libcache.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/asiolink/libasiolink.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/asiodns/libasiodns.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/resolve/libresolve.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/dns/libdns++.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/util/libutil.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/log/liblog.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/exceptions/libexceptions.la

endif

noinst_PROGRAMS = $(TESTS)
