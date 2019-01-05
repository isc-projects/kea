AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
#AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)

CLEANFILES = *.gcno *.gcda

sbin_PROGRAMS = parser4
#sbin_PROGRAMS += to-yang from-yang

parser4_SOURCES = parser4.cc
parser4_LDADD  = $(top_builddir)/src/bin/dhcp4/libparser4.la
parser4_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
parser4_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
parser4_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
parser4_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
parser4_LDADD += $(BOOST_LIBS)
#parser4_LDADD += $(SYSREPO_LIBS)
parser4_LDFLAGS = $(AM_LDFLAGS)
