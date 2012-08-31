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
MAINTAINERCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-resolver.xml resolver_messages.mes

if GENERATE_DOCS

b10-resolver.8: b10-resolver.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-resolver.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

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


b10_resolver_LDADD =  $(top_builddir)/src/lib/dns/libb10-dns++.la
b10_resolver_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
b10_resolver_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la
b10_resolver_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
b10_resolver_LDADD += $(top_builddir)/src/lib/acl/libb10-dnsacl.la
b10_resolver_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
b10_resolver_LDADD += $(top_builddir)/src/lib/asiodns/libb10-asiodns.la
b10_resolver_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
b10_resolver_LDADD += $(top_builddir)/src/lib/xfr/libb10-xfr.la
b10_resolver_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
b10_resolver_LDADD += $(top_builddir)/src/lib/server_common/libb10-server-common.la
b10_resolver_LDADD += $(top_builddir)/src/lib/cache/libb10-cache.la
b10_resolver_LDADD += $(top_builddir)/src/lib/nsas/libb10-nsas.la
b10_resolver_LDADD += $(top_builddir)/src/lib/resolve/libb10-resolve.la
b10_resolver_LDFLAGS = -pthread

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_resolverdir = $(pkgdatadir)
b10_resolver_DATA = resolver.spec

