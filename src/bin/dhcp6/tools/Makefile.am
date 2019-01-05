AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
#AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)

CLEANFILES = *.gcno *.gcda

sbin_PROGRAMS = parser6
#sbin_PROGRAMS += to-yang from-yang

parser6_SOURCES = parser6.cc
parser6_LDADD  = $(top_builddir)/src/bin/dhcp6/libparser6.la
parser6_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
parser6_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
parser6_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
parser6_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
parser6_LDADD += $(BOOST_LIBS)
#parser6_LDADD += $(SYSREPO_LIBS)
parser6_LDFLAGS = $(AM_LDFLAGS)
