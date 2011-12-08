SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

# The core library
lib_LTLIBRARIES = libacl.la
libacl_la_SOURCES  = acl.h
libacl_la_SOURCES += check.h
libacl_la_SOURCES += ip_check.h ip_check.cc
libacl_la_SOURCES += logic_check.h
libacl_la_SOURCES += loader.h loader.cc

libacl_la_LIBADD = $(top_builddir)/src/lib/exceptions/libexceptions.la
libacl_la_LIBADD += $(top_builddir)/src/lib/cc/libcc.la
libacl_la_LIBADD += $(top_builddir)/src/lib/util/libutil.la

# DNS specialized one
lib_LTLIBRARIES += libdnsacl.la

libdnsacl_la_SOURCES = dns.h dns.cc dnsname_check.h

libdnsacl_la_LIBADD = libacl.la
libdnsacl_la_LIBADD += $(top_builddir)/src/lib/dns/libdns++.la

CLEANFILES = *.gcno *.gcda
