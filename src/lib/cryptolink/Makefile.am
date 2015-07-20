SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-cryptolink.la

libkea_cryptolink_la_SOURCES = cryptolink.h cryptolink.cc
libkea_cryptolink_la_SOURCES += crypto_hash.h crypto_hash.cc
libkea_cryptolink_la_SOURCES += crypto_hmac.h crypto_hmac.cc
if HAVE_BOTAN
libkea_cryptolink_la_SOURCES += botan_link.cc
libkea_cryptolink_la_SOURCES += botan_common.h
libkea_cryptolink_la_SOURCES += botan_hash.cc
libkea_cryptolink_la_SOURCES += botan_hmac.cc
endif
if HAVE_OPENSSL
libkea_cryptolink_la_SOURCES += openssl_link.cc
libkea_cryptolink_la_SOURCES += openssl_common.h
libkea_cryptolink_la_SOURCES += openssl_hash.cc
libkea_cryptolink_la_SOURCES += openssl_hmac.cc
endif

libkea_cryptolink_la_LDFLAGS = ${CRYPTO_LDFLAGS}
libkea_cryptolink_la_LDFLAGS += -no-undefined -version-info 1:0:0
libkea_cryptolink_la_LIBADD  = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_cryptolink_la_LIBADD += ${CRYPTO_LIBS} ${CRYPTO_RPATH}
