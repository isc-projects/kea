AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DTEST_SCRIPT_SH=\"$(abs_top_builddir)/src/lib/asiolink/tests/process_spawn_app.sh\"
AM_CPPFLAGS += -DINVALID_TEST_SCRIPT_SH=\"$(abs_top_srcdir)/README\"
TEST_CA_DIR = $(abs_srcdir)/../testutils/ca
AM_CPPFLAGS += -DTEST_CA_DIR=\"$(TEST_CA_DIR)\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda test-socket

DISTCLEANFILES = process_spawn_app.sh

noinst_SCRIPTS = process_spawn_app.sh

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += addr_utilities_unittest.cc
run_unittests_SOURCES += io_address_unittest.cc
run_unittests_SOURCES += hash_address_unittest.cc
run_unittests_SOURCES += io_endpoint_unittest.cc
run_unittests_SOURCES += io_socket_unittest.cc
run_unittests_SOURCES += interval_timer_unittest.cc
run_unittests_SOURCES += tcp_endpoint_unittest.cc
run_unittests_SOURCES += tcp_socket_unittest.cc
run_unittests_SOURCES += udp_endpoint_unittest.cc
run_unittests_SOURCES += udp_socket_unittest.cc
run_unittests_SOURCES += io_service_unittest.cc
run_unittests_SOURCES += io_service_signal_unittests.cc
run_unittests_SOURCES += dummy_io_callback_unittest.cc
run_unittests_SOURCES += tcp_acceptor_unittest.cc
run_unittests_SOURCES += unix_domain_socket_unittest.cc
run_unittests_SOURCES += process_spawn_unittest.cc
if HAVE_OPENSSL
run_unittests_SOURCES += tls_unittest.cc
run_unittests_SOURCES += tls_acceptor_unittest.cc
run_unittests_SOURCES += tls_socket_unittest.cc
endif
if HAVE_BOTAN_BOOST
run_unittests_SOURCES += tls_unittest.cc
run_unittests_SOURCES += tls_acceptor_unittest.cc
run_unittests_SOURCES += tls_socket_unittest.cc
endif

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

run_unittests_LDADD  = $(top_builddir)/src/lib/asiolink/testutils/libasiolinktest.la
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
