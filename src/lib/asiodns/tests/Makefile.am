AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib // @todo - please update
AM_CPPFLAGS += $(BOOST_INCLUDES) // @todo - please update
 // @todo - please update
AM_CXXFLAGS = $(KEA_CXXFLAGS)
 // @todo - please update
if USE_STATIC_LINK // @todo - please update
AM_LDFLAGS = -static // @todo - please update
endif // @todo - please update
 // @todo - please update
CLEANFILES = *.gcno *.gcda // @todo - please update
 // @todo - please update
TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS = // @todo - please update
if HAVE_GTEST // @todo - please update
TESTS += run_unittests // @todo - please update
run_unittests_SOURCES  = run_unittests.cc // @todo - please update
run_unittests_SOURCES += io_fetch_unittest.cc // @todo - please update
 // @todo - please update
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) // @todo - please update
 // @todo - please update
run_unittests_LDADD  = $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
run_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)
 // @todo - please update
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
 // @todo - please update
# Note: the ordering matters: -Wno-... must follow -Wextra (defined in KEA_CXXFLAGS)
run_unittests_CXXFLAGS = $(AM_CXXFLAGS) // @todo - please update
if USE_GXX // @todo - please update
run_unittests_CXXFLAGS += -Wno-unused-parameter // @todo - please update
endif // @todo - please update
endif // @todo - please update
 // @todo - please update
noinst_PROGRAMS = $(TESTS)
