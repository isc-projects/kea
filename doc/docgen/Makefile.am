SUBDIRS = .

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

if GENERATE_DOCS
noinst_PROGRAMS = kea-docgen
kea_docgen_SOURCES = kea_docgen.cc

EXTRA_DIST  = generate-templates
EXTRA_DIST += cmds-list

kea_docgen_LDADD = $(top_builddir)/src/lib/cc/libkea-cc.la
kea_docgen_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

endif
