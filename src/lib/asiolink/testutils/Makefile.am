SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
TEST_CA_DIR = $(abs_srcdir)/ca
AM_CPPFLAGS += -DTEST_CA_DIR=\"$(TEST_CA_DIR)\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

EXTRA_DIST  =
EXTRA_DIST += ca/00af7a28.0
EXTRA_DIST += ca/0c7eedb9.0
EXTRA_DIST += ca/28f5a777.0
EXTRA_DIST += ca/2eefa08b.0
EXTRA_DIST += ca/71336a4d.0
EXTRA_DIST += ca/7a5b785e.0
EXTRA_DIST += ca/ad950210.0
EXTRA_DIST += ca/doc.txt
EXTRA_DIST += ca/ext-addr-conf.cnf
EXTRA_DIST += ca/ext-conf.cnf
EXTRA_DIST += ca/kea-ca.crt
EXTRA_DIST += ca/kea-ca.key
EXTRA_DIST += ca/kea-client.crt
EXTRA_DIST += ca/kea-client.csr
EXTRA_DIST += ca/kea-client.key
EXTRA_DIST += ca/kea-client.p12
EXTRA_DIST += ca/kea-other.crt
EXTRA_DIST += ca/kea-other.key
EXTRA_DIST += ca/kea-self.crt
EXTRA_DIST += ca/kea-self.key
EXTRA_DIST += ca/kea-server-addr.crt
EXTRA_DIST += ca/kea-server-addr.csr
EXTRA_DIST += ca/kea-server-raw.crt
EXTRA_DIST += ca/kea-server-raw.csr
EXTRA_DIST += ca/kea-server.crt
EXTRA_DIST += ca/kea-server.csr
EXTRA_DIST += ca/kea-server.key
EXTRA_DIST += ca/server-addr-conf.cnf
EXTRA_DIST += ca/server-conf.cnf

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libasiolinktest.la

libasiolinktest_la_SOURCES  = test_server_unix_socket.cc test_server_unix_socket.h
libasiolinktest_la_SOURCES += timed_signal.cc timed_signal.h
libasiolinktest_la_SOURCES += test_tls.cc test_tls.h

libasiolinktest_la_CXXFLAGS = $(AM_CXXFLAGS)
libasiolinktest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libasiolinktest_la_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

libasiolinktest_la_LIBADD  = $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libasiolinktest_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libasiolinktest_la_LIBADD += $(BOOST_LIBS) $(CRYPTO_LIBS)

if HAVE_OPENSSL
# Boost ASIO SSL sample server and client for C++11.
# https://www.boost.org/doc/libs/1_75_0/doc/html/boost_asio/example/cpp11/ssl/
# openssl_sample_server <port>
# openssl_sample_server <address> <port>

noinst_PROGRAMS = openssl_sample_client openssl_sample_server

openssl_sample_client_SOURCES = openssl_sample_client.cc
openssl_sample_client_CPPFLAGS = $(AM_CPPFLAGS)
openssl_sample_client_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
openssl_sample_client_LDADD = $(BOOST_LIBS) $(CRYPTO_LIBS)

openssl_sample_server_SOURCES = openssl_sample_server.cc
openssl_sample_server_CPPFLAGS = $(AM_CPPFLAGS)
openssl_sample_server_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
openssl_sample_server_LDADD = $(BOOST_LIBS) $(CRYPTO_LIBS)
endif

if HAVE_BOTAN_BOOST
# Same samples ported to Botan boost ASIO.

noinst_PROGRAMS = botan_boost_sample_client botan_boost_sample_server

botan_boost_sample_client_SOURCES = botan_boost_sample_client.cc
botan_boost_sample_client_CPPFLAGS = $(AM_CPPFLAGS)
botan_boost_sample_client_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
botan_boost_sample_client_LDADD = $(BOOST_LIBS) $(CRYPTO_LIBS)

botan_boost_sample_server_SOURCES = botan_boost_sample_server.cc
botan_boost_sample_server_CPPFLAGS = $(AM_CPPFLAGS)
botan_boost_sample_server_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
botan_boost_sample_server_LDADD = $(BOOST_LIBS) $(CRYPTO_LIBS)
endif
endif
