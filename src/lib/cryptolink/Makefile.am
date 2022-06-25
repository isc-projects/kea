SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-cryptolink.la

libkea_cryptolink_la_SOURCES = cryptolink.h cryptolink.cc
libkea_cryptolink_la_SOURCES += crypto_hash.h crypto_hash.cc
libkea_cryptolink_la_SOURCES += crypto_hmac.h crypto_hmac.cc
libkea_cryptolink_la_SOURCES += crypto_rng.h crypto_rng.cc
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
libkea_cryptolink_la_SOURCES += openssl_compat.h
libkea_cryptolink_la_SOURCES += openssl_hmac.cc
endif

libkea_cryptolink_la_LDFLAGS = $(CRYPTO_LDFLAGS)
libkea_cryptolink_la_LDFLAGS += -no-undefined -version-info 28:0:0
libkea_cryptolink_la_LIBADD  = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_cryptolink_la_LIBADD += $(CRYPTO_LIBS)


# Specify the headers for copying into the installation directory tree.
libkea_cryptolink_includedir = $(pkgincludedir)/cryptolink
libkea_cryptolink_include_HEADERS = \
	crypto_hash.h \
	crypto_hmac.h \
	crypto_rng.h \
	cryptolink.h

if HAVE_BOTAN
libkea_cryptolink_include_HEADERS += \
	botan_common.h
endif

if HAVE_OPENSSL
libkea_cryptolink_include_HEADERS += \
	openssl_common.h \
	openssl_compat.h
endif
