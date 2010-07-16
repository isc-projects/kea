SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin

AM_CXXFLAGS = $(B10_CXXFLAGS)

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES = *.gcno *.gcda auth.spec spec_config.h

man_MANS = b10-auth.8
EXTRA_DIST = $(man_MANS) b10-auth.xml

if ENABLE_MAN

b10-auth.8: b10-auth.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-auth.xml

endif

auth.spec: auth.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" auth.spec.pre >$@

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

# This is a wrapper library solely used for b10-auth.  The ASIO header files
# have some code fragments that would hit gcc's unused-parameter warning,
# which would make the build fail with -Werror (our default setting).
# We don't want to lower the warning level for our own code just for ASIO,
# so as a workaround we extract the ASIO related code into a separate library,
# only for which we accept the unused-parameter warning.
lib_LIBRARIES = libasio_link.a
libasio_link_a_SOURCES = asio_link.cc asio_link.h
# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
libasio_link_a_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
libasio_link_a_CXXFLAGS += -Wno-unused-parameter
endif
libasio_link_a_CPPFLAGS = $(AM_CPPFLAGS)

BUILT_SOURCES = spec_config.h 
pkglibexec_PROGRAMS = b10-auth
b10_auth_SOURCES = auth_srv.cc auth_srv.h
b10_auth_SOURCES += common.h
b10_auth_SOURCES += main.cc
b10_auth_LDADD =  $(top_builddir)/src/lib/datasrc/.libs/libdatasrc.a
b10_auth_LDADD += $(top_builddir)/src/lib/dns/.libs/libdns++.a
b10_auth_LDADD += $(top_builddir)/src/lib/config/.libs/libcfgclient.a
b10_auth_LDADD += $(top_builddir)/src/lib/cc/.libs/libcc.a
b10_auth_LDADD += $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
b10_auth_LDADD += $(top_builddir)/src/bin/auth/libasio_link.a
b10_auth_LDADD += $(SQLITE_LIBS)
b10_auth_LDADD += $(top_builddir)/src/lib/xfr/.libs/libxfr.a

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_authdir = $(DESTDIR)$(pkgdatadir)
b10_auth_DATA = auth.spec

