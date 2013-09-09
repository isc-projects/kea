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

CLEANFILES  = *.gcno *.gcda spec_config.h d2_messages.h d2_messages.cc

man_MANS = b10-dhcp-ddns.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-dhcp-ddns.xml dhcp-ddns.spec

if GENERATE_DOCS
b10-dhcp-ddns.8: b10-dhcp-ddns.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/b10-dhcp-ddns.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

d2_messages.h d2_messages.cc: d2_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/bin/d2/d2_messages.mes

BUILT_SOURCES = spec_config.h d2_messages.h d2_messages.cc

pkglibexec_PROGRAMS = b10-dhcp-ddns

b10_dhcp_ddns_SOURCES  = main.cc
b10_dhcp_ddns_SOURCES += d2_log.cc d2_log.h
b10_dhcp_ddns_SOURCES += d2_process.cc d2_process.h
b10_dhcp_ddns_SOURCES += d_controller.cc d_controller.h
b10_dhcp_ddns_SOURCES += d2_controller.cc d2_controller.h
b10_dhcp_ddns_SOURCES += d_cfg_mgr.cc d_cfg_mgr.h
b10_dhcp_ddns_SOURCES += d2_config.cc d2_config.h
b10_dhcp_ddns_SOURCES += d2_cfg_mgr.cc d2_cfg_mgr.h
b10_dhcp_ddns_SOURCES += d2_queue_mgr.cc d2_queue_mgr.h
b10_dhcp_ddns_SOURCES += d2_update_message.cc d2_update_message.h
b10_dhcp_ddns_SOURCES += d2_update_mgr.cc d2_update_mgr.h
b10_dhcp_ddns_SOURCES += d2_zone.cc d2_zone.h
b10_dhcp_ddns_SOURCES += dns_client.cc dns_client.h
b10_dhcp_ddns_SOURCES += nc_trans.cc nc_trans.h
b10_dhcp_ddns_SOURCES += state_model.cc state_model.h

nodist_b10_dhcp_ddns_SOURCES = d2_messages.h d2_messages.cc
EXTRA_DIST += d2_messages.mes

b10_dhcp_ddns_LDADD = $(top_builddir)/src/lib/log/libb10-log.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/asiodns/libb10-asiodns.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libb10-dhcp_ddns.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dhcpsrv/libb10-dhcpsrv.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dns/libb10-dns++.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
b10_dhcp_ddns_LDADD += $(top_builddir)/src/lib/hooks/libb10-hooks.la

b10_dhcp_ddnsdir = $(pkgdatadir)
b10_dhcp_ddns_DATA = dhcp-ddns.spec
