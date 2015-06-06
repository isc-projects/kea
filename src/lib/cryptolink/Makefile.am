SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-cryptolink.la

libkea_cryptolink_la_SOURCES = cryptolink.h cryptolink.cc
libkea_cryptolink_la_SOURCES += crypto_hash.h crypto_hash.cc
libkea_cryptolink_la_SOURCES += crypto_hmac.h crypto_hmac.cc
libkea_cryptolink_la_SOURCES += crypto_asym.h crypto_asym.cc
if HAVE_BOTAN
libkea_cryptolink_la_SOURCES += botan_link.cc
libkea_cryptolink_la_SOURCES += botan_common.h
libkea_cryptolink_la_SOURCES += botan_hash.cc
libkea_cryptolink_la_SOURCES += botan_hmac.cc
libkea_cryptolink_la_SOURCES += botan_asym.cc
libkea_cryptolink_la_SOURCES += botan_rsa.h botan_rsa.cc
endif
if HAVE_OPENSSL
libkea_cryptolink_la_SOURCES += openssl_link.cc
libkea_cryptolink_la_SOURCES += openssl_common.h
libkea_cryptolink_la_SOURCES += openssl_hash.cc
libkea_cryptolink_la_SOURCES += openssl_hmac.cc
libkea_cryptolink_la_SOURCES += openssl_asym.cc
libkea_cryptolink_la_SOURCES += openssl_rsa.h openssl_rsa.cc
endif

libkea_cryptolink_la_LDFLAGS = ${CRYPTO_LDFLAGS}
libkea_cryptolink_la_LIBADD = ${CRYPTO_LIBS} ${CRYPTO_RPATH}
