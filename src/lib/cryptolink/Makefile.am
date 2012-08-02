SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(BOTAN_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libb10-cryptolink.la

libb10_cryptolink_la_SOURCES = cryptolink.h cryptolink.cc
libb10_cryptolink_la_SOURCES += crypto_hmac.h crypto_hmac.cc

libb10_cryptolink_la_LDFLAGS = ${BOTAN_LDFLAGS}
libb10_cryptolink_la_LIBADD = ${BOTAN_LIBS} ${BOTAN_RPATH}
