SUBDIRS = . tests benchmarks

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/cc -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += -I$(top_builddir)/src/lib/asiolink
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES  = *.gcno *.gcda auth.spec spec_config.h
CLEANFILES += auth_messages.h auth_messages.cc

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

auth_messages.h auth_messages.cc: auth_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/bin/auth/auth_messages.mes

BUILT_SOURCES = spec_config.h auth_messages.h auth_messages.cc

pkglibexec_PROGRAMS = b10-auth
b10_auth_SOURCES = query.cc query.h
b10_auth_SOURCES += auth_srv.cc auth_srv.h
b10_auth_SOURCES += auth_log.cc auth_log.h
b10_auth_SOURCES += auth_config.cc auth_config.h
b10_auth_SOURCES += command.cc command.h
b10_auth_SOURCES += common.h common.cc
b10_auth_SOURCES += statistics.cc statistics.h
b10_auth_SOURCES += main.cc
# This is a temporary workaround for #1206, where the InMemoryClient has been
# moved to an ldopened library. We could add that library to LDADD, but that
# is nonportable. When #1207 is done this becomes moot anyway, and the
# specific workaround is not needed anymore, so we can then remove this
# line again.
b10_auth_SOURCES += ${top_srcdir}/src/lib/datasrc/memory_datasrc.cc

nodist_b10_auth_SOURCES = auth_messages.h auth_messages.cc
EXTRA_DIST += auth_messages.mes

b10_auth_LDADD =  $(top_builddir)/src/lib/datasrc/libdatasrc.la
b10_auth_LDADD += $(top_builddir)/src/lib/dns/libdns++.la
b10_auth_LDADD += $(top_builddir)/src/lib/util/libutil.la
b10_auth_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
b10_auth_LDADD += $(top_builddir)/src/lib/cc/libcc.la
b10_auth_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
b10_auth_LDADD += $(top_builddir)/src/lib/asiodns/libasiodns.la
b10_auth_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
b10_auth_LDADD += $(top_builddir)/src/lib/log/liblog.la
b10_auth_LDADD += $(top_builddir)/src/lib/xfr/libxfr.la
b10_auth_LDADD += $(top_builddir)/src/lib/server_common/libserver_common.la
b10_auth_LDADD += $(top_builddir)/src/lib/statistics/libstatistics.la
b10_auth_LDADD += $(SQLITE_LIBS)

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_authdir = $(pkgdatadir)
b10_auth_DATA = auth.spec

