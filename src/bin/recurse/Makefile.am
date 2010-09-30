SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/cc -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += -I$(top_builddir)/src/lib/asiolink

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES = *.gcno *.gcda recurse.spec spec_config.h


man_MANS = b10-recurse.8
EXTRA_DIST = $(man_MANS) b10-recurse.xml

# if ENABLE_MAN

b10-recurse.8: b10-recurse.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-recurse.xml

# endif

recurse.spec: recurse.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" recurse.spec.pre >$@

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

BUILT_SOURCES = spec_config.h 
pkglibexec_PROGRAMS = b10-recurse
b10_recurse_SOURCES = recursor.cc recursor.h
b10_recurse_SOURCES += change_user.cc change_user.h
b10_recurse_SOURCES += common.h
b10_recurse_SOURCES += main.cc
b10_recurse_LDADD =  $(top_builddir)/src/lib/dns/libdns++.la
b10_recurse_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
b10_recurse_LDADD += $(top_builddir)/src/lib/cc/libcc.la
b10_recurse_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
b10_recurse_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
b10_recurse_LDADD += $(top_builddir)/src/lib/xfr/libxfr.la
b10_recurse_LDFLAGS = -pthread

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_recursedir = $(DESTDIR)$(pkgdatadir)
b10_recurse_DATA = recurse.spec

