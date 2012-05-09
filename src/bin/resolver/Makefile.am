SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/cc -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiodns
AM_CPPFLAGS += -I$(top_builddir)/src/lib/asiodns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += -I$(top_builddir)/src/lib/asiolink
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES  = *.gcno *.gcda
CLEANFILES += resolver.spec spec_config.h
CLEANFILES += resolver_messages.cc resolver_messages.h

man_MANS = b10-resolver.8
EXTRA_DIST = $(man_MANS) b10-resolver.xml resolver_messages.mes

if ENABLE_MAN

b10-resolver.8: b10-resolver.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-resolver.xml

endif

resolver.spec: resolver.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" resolver.spec.pre >$@

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

# Define rule to build logging source files from message file
resolver_messages.h resolver_messages.cc: resolver_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/bin/resolver/resolver_messages.mes


BUILT_SOURCES = spec_config.h resolver_messages.cc resolver_messages.h

pkglibexec_PROGRAMS = b10-resolver
b10_resolver_SOURCES = resolver.cc resolver.h
b10_resolver_SOURCES += resolver_log.cc resolver_log.h
b10_resolver_SOURCES += response_scrubber.cc response_scrubber.h
b10_resolver_SOURCES += $(top_builddir)/src/bin/auth/common.h
b10_resolver_SOURCES += main.cc
b10_resolver_SOURCES += common.cc common.h

nodist_b10_resolver_SOURCES = resolver_messages.cc resolver_messages.h


b10_resolver_LDADD =  $(top_builddir)/src/lib/dns/libdns++.la
b10_resolver_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
b10_resolver_LDADD += $(top_builddir)/src/lib/cc/libcc.la
b10_resolver_LDADD += $(top_builddir)/src/lib/util/libutil.la
b10_resolver_LDADD += $(top_builddir)/src/lib/acl/libdnsacl.la
b10_resolver_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
b10_resolver_LDADD += $(top_builddir)/src/lib/asiodns/libasiodns.la
b10_resolver_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
b10_resolver_LDADD += $(top_builddir)/src/lib/xfr/libxfr.la
b10_resolver_LDADD += $(top_builddir)/src/lib/log/liblog.la
b10_resolver_LDADD += $(top_builddir)/src/lib/server_common/libserver_common.la
b10_resolver_LDADD += $(top_builddir)/src/lib/cache/libcache.la
b10_resolver_LDADD += $(top_builddir)/src/lib/nsas/libnsas.la
b10_resolver_LDADD += $(top_builddir)/src/lib/resolve/libresolve.la
b10_resolver_LDFLAGS = -pthread

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_resolverdir = $(pkgdatadir)
b10_resolver_DATA = resolver.spec

