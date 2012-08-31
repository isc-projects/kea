AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

bin_PROGRAMS = b10-host
b10_host_SOURCES = host.cc
b10_host_LDADD = $(top_builddir)/src/lib/dns/libb10-dns++.la
b10_host_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
b10_host_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la

man_MANS = b10-host.1
MAINTAINERCLEANFILES += $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-host.xml

.PHONY: man
if GENERATE_DOCS

man: b10-host.1

b10-host.1: b10-host.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-host.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif
