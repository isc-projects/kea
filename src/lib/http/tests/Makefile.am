SUBDIRS = .

# Add to the tarball:
EXTRA_DIST = testdata/empty
EXTRA_DIST += testdata/hiddenp
EXTRA_DIST += testdata/hiddens
EXTRA_DIST += testdata/hiddenu

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
TEST_CA_DIR = $(srcdir)/../../asiolink/testutils/ca
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(TEST_CA_DIR)\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"
AM_CPPFLAGS += -DDATA_DIR=\"$(abs_srcdir)/testdata\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libhttp_unittests

libhttp_unittests_SOURCES  = basic_auth_unittests.cc
libhttp_unittests_SOURCES += basic_auth_config_unittests.cc
libhttp_unittests_SOURCES += connection_pool_unittests.cc
libhttp_unittests_SOURCES += date_time_unittests.cc
libhttp_unittests_SOURCES += http_header_unittests.cc
libhttp_unittests_SOURCES += post_request_unittests.cc
libhttp_unittests_SOURCES += post_request_json_unittests.cc
libhttp_unittests_SOURCES += request_parser_unittests.cc
libhttp_unittests_SOURCES += request_test.h
libhttp_unittests_SOURCES += response_creator_unittests.cc
libhttp_unittests_SOURCES += response_parser_unittests.cc
libhttp_unittests_SOURCES += response_test.h
libhttp_unittests_SOURCES += request_unittests.cc
libhttp_unittests_SOURCES += response_unittests.cc
libhttp_unittests_SOURCES += response_json_unittests.cc
libhttp_unittests_SOURCES += run_unittests.cc
libhttp_unittests_SOURCES += server_client_unittests.cc
if HAVE_OPENSSL
libhttp_unittests_SOURCES += tls_server_unittests.cc
libhttp_unittests_SOURCES += tls_client_unittests.cc
endif
if HAVE_BOTAN_BOOST
libhttp_unittests_SOURCES += tls_server_unittests.cc
libhttp_unittests_SOURCES += tls_client_unittests.cc
endif
libhttp_unittests_SOURCES += url_unittests.cc
libhttp_unittests_SOURCES += test_http_client.h
libhttp_unittests_SOURCES += client_mt_unittests.cc

libhttp_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libhttp_unittests_CXXFLAGS = $(AM_CXXFLAGS)
libhttp_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

libhttp_unittests_LDADD  = $(top_builddir)/src/lib/http/libkea-http.la
libhttp_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libhttp_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
libhttp_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libhttp_unittests_LDADD += $(top_builddir)/src/lib/asiolink/testutils/libasiolinktest.la
libhttp_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libhttp_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libhttp_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libhttp_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libhttp_unittests_LDADD += $(LOG4CPLUS_LIBS)
libhttp_unittests_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
