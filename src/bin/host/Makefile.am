AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

bin_PROGRAMS = host
host_SOURCES = host.cc
host_LDADD = $(top_builddir)/src/lib/dns/libdns++.la
host_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la

#man_MANS = host.1
#EXTRA_DIST = $(man_MANS) host.xml
#
#if ENABLE_MAN
#
#host.1: host.xml
#	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/host.xml
#
#endif
