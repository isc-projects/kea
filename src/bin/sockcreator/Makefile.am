SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES = *.gcno *.gcda

man_MANS = b10-sockcreator.8
EXTRA_DIST = $(man_MANS) b10-sockcreator.xml

if ENABLE_MAN

b10-sockcreator.8: b10-sockcreator.xml
        xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-sockcreator.xml

endif

pkglibexec_PROGRAMS = b10-sockcreator

b10_sockcreator_SOURCES = sockcreator.cc sockcreator.h main.cc
b10_sockcreator_LDADD  = $(top_builddir)/src/lib/util/io/libutil_io.la
b10_sockcreator_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
