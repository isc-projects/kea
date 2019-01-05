AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
#AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)

CLEANFILES = *.gcno *.gcda

sbin_PROGRAMS = parser-nc
#sbin_PROGRAMS += to-yang from-yang

parser_nc_SOURCES = parser-nc.cc
parser_nc_LDADD  = $(top_builddir)/src/bin/netconf/libparser-nc.la
parser_nc_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
parser_nc_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
parser_nc_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
parser_nc_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
parser_nc_LDADD += $(BOOST_LIBS)
#parser_nc_LDADD += $(SYSREPO_LIBS)
parser_nc_LDFLAGS = $(AM_LDFLAGS)
