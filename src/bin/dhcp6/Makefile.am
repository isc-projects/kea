SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/cc -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some Boost headers when compiling with clang
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = spec_config.h dhcp6_messages.h dhcp6_messages.cc s-messages

man_MANS = kea-dhcp6.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) kea-dhcp6.xml dhcp6.spec
EXTRA_DIST += dhcp6.dox dhcp6_hooks.dox

if GENERATE_DOCS

kea-dhcp6.8: kea-dhcp6.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
        $(srcdir)/kea-dhcp6.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

dhcp6_messages.h dhcp6_messages.cc: s-messages

s-messages: dhcp6_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/bin/dhcp6/dhcp6_messages.mes
	touch $@

BUILT_SOURCES = spec_config.h dhcp6_messages.h dhcp6_messages.cc

# convenience archive

noinst_LTLIBRARIES = libdhcp6.la

libdhcp6_la_SOURCES  =
libdhcp6_la_SOURCES += dhcp6_log.cc dhcp6_log.h
libdhcp6_la_SOURCES += dhcp6_srv.cc dhcp6_srv.h
libdhcp6_la_SOURCES += ctrl_dhcp6_srv.cc ctrl_dhcp6_srv.h
libdhcp6_la_SOURCES += json_config_parser.cc json_config_parser.h

if CONFIG_BACKEND_BUNDY
libdhcp6_la_SOURCES += bundy_controller.cc
endif

if CONFIG_BACKEND_JSON
libdhcp6_la_SOURCES += kea_controller.cc
endif

nodist_libdhcp6_la_SOURCES = dhcp6_messages.h dhcp6_messages.cc
EXTRA_DIST += dhcp6_messages.mes

sbin_PROGRAMS = kea-dhcp6

kea_dhcp6_SOURCES  = main.cc

kea_dhcp6_LDADD  = libdhcp6.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
kea_dhcp6_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
kea_dhcp6_LDADD += $(top_builddir)/src/bin/cfgrpt/libcfgrpt.la

kea_dhcp6dir = $(pkgdatadir)
kea_dhcp6_DATA = dhcp6.spec
