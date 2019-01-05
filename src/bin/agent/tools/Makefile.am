AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
#AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)

CLEANFILES = *.gcno *.gcda

sbin_PROGRAMS = parser-ca
#sbin_PROGRAMS += to-yang from-yang

parser_ca_SOURCES = parser-ca.cc
parser_ca_LDADD  = $(top_builddir)/src/bin/agent/libparser-ca.la
parser_ca_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
parser_ca_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
parser_ca_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
parser_ca_LDADD += $(BOOST_LIBS)
#parser_ca_LDADD += $(SYSREPO_LIBS)
parser_ca_LDFLAGS = $(AM_LDFLAGS)
