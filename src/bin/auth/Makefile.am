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
MAINTAINERCLEANFILES += $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-auth.xml

if GENERATE_DOCS

b10-auth.8: b10-auth.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-auth.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

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
b10_auth_SOURCES += datasrc_configurator.h
b10_auth_SOURCES += main.cc
# This is a temporary workaround for #1206, where the InMemoryClient has been
# moved to an ldopened library. We could add that library to LDADD, but that
# is nonportable. This should've been moot after #1207, but there is still
# one dependency; the in-memory-specific zone loader call is still in
# auth.
b10_auth_SOURCES += ${top_srcdir}/src/lib/datasrc/memory_datasrc.cc

nodist_b10_auth_SOURCES = auth_messages.h auth_messages.cc
EXTRA_DIST += auth_messages.mes

b10_auth_LDADD =  $(top_builddir)/src/lib/datasrc/libb10-datasrc.la
b10_auth_LDADD += $(top_builddir)/src/lib/dns/libb10-dns++.la
b10_auth_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
b10_auth_LDADD += $(top_builddir)/src/lib/util/io/libb10-util-io.la
b10_auth_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
b10_auth_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la
b10_auth_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
b10_auth_LDADD += $(top_builddir)/src/lib/asiodns/libb10-asiodns.la
b10_auth_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
b10_auth_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
b10_auth_LDADD += $(top_builddir)/src/lib/xfr/libb10-xfr.la
b10_auth_LDADD += $(top_builddir)/src/lib/server_common/libb10-server-common.la
b10_auth_LDADD += $(top_builddir)/src/lib/statistics/libb10-statistics.la
b10_auth_LDADD += $(SQLITE_LIBS)

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_authdir = $(pkgdatadir)
b10_auth_DATA = auth.spec

