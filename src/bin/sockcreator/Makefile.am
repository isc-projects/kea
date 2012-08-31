SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES = *.gcno *.gcda

man_MANS = b10-sockcreator.8
CLEANFILES += $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-sockcreator.xml

if GENERATE_DOCS

b10-sockcreator.8: b10-sockcreator.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-sockcreator.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

pkglibexec_PROGRAMS = b10-sockcreator

b10_sockcreator_SOURCES = sockcreator.cc sockcreator.h main.cc
b10_sockcreator_LDADD  = $(top_builddir)/src/lib/util/io/libb10-util-io.la
b10_sockcreator_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
