SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
if GCC_WERROR_OK
AM_CPPFLAGS += -Werror
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES = *.gcno *.gcda auth.pre auth.spec

man_MANS = b10-auth.8
EXTRA_DIST = $(man_MANS) b10-auth.xml

if ENABLE_MAN

b10-auth.8: b10-auth.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-auth.xml

endif

auth.spec: auth.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" auth.pre >$@

pkglibexec_PROGRAMS = b10-auth
b10_auth_SOURCES = auth_srv.cc auth_srv.h
b10_auth_SOURCES += common.h
b10_auth_SOURCES += main.cc
b10_auth_LDADD =  $(top_builddir)/src/lib/auth/.libs/libauth.a
b10_auth_LDADD +=  $(top_builddir)/src/lib/dns/.libs/libdns.a
b10_auth_LDADD += $(top_builddir)/src/lib/config/.libs/libcfgclient.a
b10_auth_LDADD += $(top_builddir)/src/lib/cc/libcc.a
b10_auth_LDADD += $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
b10_auth_LDADD += $(SQLITE_LIBS)
if HAVE_BOOST_SYSTEM
if HAVE_BOOST_PYTHON
b10_auth_LDADD += $(top_builddir)/src/lib/xfr/.libs/libxfr.a
endif
b10_auth_LDFLAGS = $(AM_LDFLAGS) $(BOOST_LDFLAGS)
b10_auth_LDADD += $(BOOST_SYSTEM_LIB)
endif

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_authdir = $(DESTDIR)$(pkgdatadir)
b10_auth_DATA = auth.spec

