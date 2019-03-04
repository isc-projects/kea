SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES = *.gcno *.gcda

man_MANS = kea-sockcreator.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) kea-sockcreator.xml

if GENERATE_DOCS

kea-sockcreator.8: kea-sockcreator.xml
	@XSLTPROC@ --novalid --xinclude @NONET@ -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/kea-sockcreator.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

# convenience archive

noinst_LTLIBRARIES = libsockcreator.la

libsockcreator_la_SOURCES = sockcreator.cc sockcreator.h

pkglibexec_PROGRAMS = kea-sockcreator

kea_sockcreator_SOURCES = main.cc
kea_sockcreator_LDADD  = libsockcreator.la
kea_sockcreator_LDADD += $(top_builddir)/src/lib/util/io/libkea-util-io.la
kea_sockcreator_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
