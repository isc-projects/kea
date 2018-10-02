SUBDIRS = .

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

AM_LDFLAGS = -static

if GENERATE_DOCS
noinst_PROGRAMS = kea-docgen
kea_docgen_SOURCES = kea_docgen.cc

# For bare distcheck
EXTRA_DIST = cmd_docgen

kea_docgen_LDADD = $(top_builddir)/src/lib/cc/libkea-cc.la
kea_docgen_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

endif
