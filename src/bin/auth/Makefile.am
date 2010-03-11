SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/ext $(SQLITE_CFLAGS)

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES = *.gcno *.gcda

pkglibexec_PROGRAMS = b10-auth
b10_auth_SOURCES = auth_srv.cc auth_srv.h
b10_auth_SOURCES += common.h
b10_auth_SOURCES += main.cc
b10_auth_LDADD =  $(top_builddir)/src/lib/auth/.libs/libauth.a
b10_auth_LDADD +=  $(top_builddir)/src/lib/dns/.libs/libdns.a
b10_auth_LDADD += $(top_builddir)/src/lib/config/libcfgclient.a
b10_auth_LDADD += $(top_builddir)/src/lib/cc/libcc.a
b10_auth_LDADD += $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
b10_auth_LDADD += $(SQLITE_LIBS)
if HAVE_BOOSTLIB
b10_auth_LDFLAGS = $(AM_LDFLAGS) $(BOOST_LDFLAGS)
b10_auth_LDADD += $(BOOST_SYSTEM_LIB)
endif

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_authdir = $(DESTDIR)$(pkgdatadir)
b10_auth_DATA = auth.spec

