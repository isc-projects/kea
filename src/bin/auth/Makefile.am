AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_builddir)/src/lib/dns/cpp -I$(top_builddir)/include/dns/cpp -I$(top_builddir)/include -I$(top_srcdir)/ext

bin_PROGRAMS = b10-auth
b10_auth_SOURCES = auth_srv.cc auth_srv.h
b10_auth_SOURCES += common.cc common.h
b10_auth_SOURCES += main.cc
b10_auth_LDADD =  $(top_builddir)/src/lib/dns/cpp/.libs/libdns.a
b10_auth_LDADD +=  $(top_builddir)/src/lib/auth/cpp/.libs/libauth.a
b10_auth_LDADD += $(top_builddir)/src/lib/config/cpp/libclient.a
b10_auth_LDADD += $(top_builddir)/src/lib/cc/cpp/libcc.a

b10_authdir = $(DESTDIR)$(pkgdatadir)
b10_auth_DATA = auth.spec

