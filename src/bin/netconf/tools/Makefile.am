AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

man_MANS = tools-nc.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) tools-nc.xml

if GENERATE_DOCS
tools-nc.8: tools-nc.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
	http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/tools-nc.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

sbin_PROGRAMS = parser-nc

parser_nc_SOURCES = parser-nc.cc
parser_nc_LDADD  = $(top_builddir)/src/bin/netconf/libparser-nc.la
parser_nc_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
parser_nc_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
parser_nc_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
parser_nc_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
parser_nc_LDADD += $(BOOST_LIBS)
parser_nc_LDFLAGS = $(AM_LDFLAGS)
