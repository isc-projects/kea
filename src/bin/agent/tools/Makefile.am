AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
#AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

man_MANS = tools-ca.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) tools-ca.xml

if GENERATE_DOCS
tools-ca.8: tools-ca.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
	http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/tools-ca.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

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
