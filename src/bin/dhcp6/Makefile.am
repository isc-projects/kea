SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/cc -I$(top_builddir)/src/lib/cc
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

CLEANFILES = spec_config.h dhcp6_messages.h dhcp6_messages.cc s-messages

man_MANS = b10-dhcp6.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-dhcp6.xml dhcp6.spec

if GENERATE_DOCS

b10-dhcp6.8: b10-dhcp6.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
        $(srcdir)/b10-dhcp6.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

dhcp6_messages.h dhcp6_messages.cc: s-messages

s-messages: dhcp6_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/bin/dhcp6/dhcp6_messages.mes
	touch $@

BUILT_SOURCES = spec_config.h dhcp6_messages.h dhcp6_messages.cc

pkglibexec_PROGRAMS = b10-dhcp6

b10_dhcp6_SOURCES  = main.cc
b10_dhcp6_SOURCES += dhcp6_log.cc dhcp6_log.h
b10_dhcp6_SOURCES += dhcp6_srv.cc dhcp6_srv.h
b10_dhcp6_SOURCES += ctrl_dhcp6_srv.cc ctrl_dhcp6_srv.h
b10_dhcp6_SOURCES += json_config_parser.cc json_config_parser.h

if CONFIG_BACKEND_BIND10
b10_dhcp6_SOURCES += bundy_backend.cc
endif

if CONFIG_BACKEND_JSON
b10_dhcp6_SOURCES += jsonfile_backend.cc
endif

nodist_b10_dhcp6_SOURCES = dhcp6_messages.h dhcp6_messages.cc
EXTRA_DIST += dhcp6_messages.mes

b10_dhcp6_LDADD  = $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la

b10_dhcp6dir = $(pkgdatadir)
b10_dhcp6_DATA = dhcp6.spec
