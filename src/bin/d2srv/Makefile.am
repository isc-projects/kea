SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some Boost headers when compiling with clang
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES  = *.gcno *.gcda spec_config.h d2_srv_messages.h d2_srv_messages.cc

man_MANS = b10-d2srv.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-d2srv.xml d2srv.spec

if GENERATE_DOCS
b10-d2srv.8: b10-d2srv.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/b10-d2srv.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

d2srv_messages.h d2srv_messages.cc: d2srv_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/bin/d2srv/d2srv_messages.mes

BUILT_SOURCES = spec_config.h d2srv_messages.h d2srv_messages.cc

pkglibexec_PROGRAMS = b10-d2srv

b10_d2srv_SOURCES  = main.cc
b10_d2srv_SOURCES += d2srv_log.cc d2srv_log.h

nodist_b10_d2srv_SOURCES = d2srv_messages.h d2srv_messages.cc
EXTRA_DIST += d2srv_messages.mes

b10_d2srv_LDADD  = $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
b10_d2srv_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
b10_d2srv_LDADD += $(top_builddir)/src/lib/dhcpsrv/libb10-dhcpsrv.la
b10_d2srv_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
b10_d2srv_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
b10_d2srv_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
b10_d2srv_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
b10_d2srv_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la

b10_d2srvdir = $(pkgdatadir)
b10_d2srv_DATA = d2srv.spec
