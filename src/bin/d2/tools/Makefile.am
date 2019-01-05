AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
#AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)

CLEANFILES = *.gcno *.gcda

sbin_PROGRAMS = parser2
#sbin_PROGRAMS += to-yang from-yang

parser2_SOURCES = parser2.cc
parser2_LDADD  = $(top_builddir)/src/bin/d2/libparser2.la
parser2_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
parser2_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
parser2_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
parser2_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
parser2_LDADD += $(BOOST_LIBS)
#parser2_LDADD += $(SYSREPO_LIBS)
parser2_LDFLAGS = $(AM_LDFLAGS)
