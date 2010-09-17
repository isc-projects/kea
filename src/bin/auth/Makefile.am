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

CLEANFILES = *.gcno *.gcda auth.spec spec_config.h

if ENABLE_MAN
man_MANS = b10-auth.8
EXTRA_DIST = $(man_MANS) b10-auth.xml

b10-auth.8: b10-auth.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-auth.xml
endif

auth.spec: auth.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" auth.spec.pre >$@

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

BUILT_SOURCES = spec_config.h 
pkglibexec_PROGRAMS = b10-auth
b10_auth_SOURCES = auth_srv.cc auth_srv.h
b10_auth_SOURCES += change_user.cc change_user.h
b10_auth_SOURCES += common.h
b10_auth_SOURCES += main.cc
b10_auth_LDADD =  $(top_builddir)/src/lib/datasrc/libdatasrc.la
b10_auth_LDADD += $(top_builddir)/src/lib/dns/libdns++.la
b10_auth_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
b10_auth_LDADD += $(top_builddir)/src/lib/cc/libcc.la
b10_auth_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
b10_auth_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.a
b10_auth_LDADD += $(top_builddir)/src/lib/xfr/libxfr.la
b10_auth_LDADD += $(SQLITE_LIBS)

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_authdir = $(DESTDIR)$(pkgdatadir)
b10_auth_DATA = auth.spec

