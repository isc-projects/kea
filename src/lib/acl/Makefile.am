SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

# The core library
lib_LTLIBRARIES = libb10-acl.la
libb10_acl_la_SOURCES  = acl.h
libb10_acl_la_SOURCES += check.h
libb10_acl_la_SOURCES += ip_check.h ip_check.cc
libb10_acl_la_SOURCES += logic_check.h
libb10_acl_la_SOURCES += loader.h loader.cc

libb10_acl_la_LIBADD = $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libb10_acl_la_LIBADD += $(top_builddir)/src/lib/cc/libb10-cc.la
libb10_acl_la_LIBADD += $(top_builddir)/src/lib/util/libb10-util.la

# DNS specialized one
lib_LTLIBRARIES += libb10-dnsacl.la

libb10_dnsacl_la_SOURCES = dns.h dns.cc dnsname_check.h

libb10_dnsacl_la_LIBADD = libb10-acl.la
libb10_dnsacl_la_LIBADD += $(top_builddir)/src/lib/dns/libb10-dns++.la

CLEANFILES = *.gcno *.gcda
