AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DTEST_CA_DIR=\"$(abs_srcdir)/../../asiolink/testutils/ca\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda test-socket

DISTCLEANFILES =

noinst_SCRIPTS =

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += tcp_test_client.h tcp_test_listener.h
run_unittests_SOURCES += tcp_listener_unittests.cc
run_unittests_SOURCES += mt_tcp_listener_mgr_unittests.cc

if HAVE_OPENSSL
run_unittests_SOURCES += tls_listener_unittests.cc
endif
if HAVE_BOTAN_BOOST
run_unittests_SOURCES += tls_listener_unittests.cc
endif

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

run_unittests_LDADD  = $(top_builddir)/src/lib/tcp/libkea-tcp.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/testutils/libasiolinktest.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(CRYPTO_LIBS)
run_unittests_LDADD += $(GTEST_LDADD)

run_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# KEA_CXXFLAGS)
run_unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
run_unittests_CXXFLAGS += -Wno-unused-parameter -Wno-unused-private-field
endif
endif

noinst_PROGRAMS = $(TESTS)
