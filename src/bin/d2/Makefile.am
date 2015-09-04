SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
if HAVE_MYSQL
AM_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif
if HAVE_PGSQL
AM_CPPFLAGS += $(PGSQL_CPPFLAGS)
endif

AM_CXXFLAGS = $(KEA_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some Boost headers when compiling with clang
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES  = *.gcno *.gcda spec_config.h d2_messages.h d2_messages.cc s-messages

man_MANS = kea-dhcp-ddns.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) kea-dhcp-ddns.xml dhcp-ddns.spec d2.dox

EXTRA_DIST += images/abstract_app_classes.svg images/add_state_model.svg
EXTRA_DIST += images/config_data_classes.svg images/config_from_file_sequence.svg
EXTRA_DIST += images/config_parser_classes.svg images/cpl_signal_classes.svg
EXTRA_DIST += images/cpl_signal_sequence.svg images/d2_app_classes.svg
EXTRA_DIST += images/nc_trans_sequence.svg images/remove_state_model.svg
EXTRA_DIST += images/request_mgt_classes.svg images/state_model_classes.svg
EXTRA_DIST += images/trans_classes.svg images/update_exec_classes.svg

if GENERATE_DOCS
kea-dhcp-ddns.8: kea-dhcp-ddns.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/kea-dhcp-ddns.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

d2_messages.h d2_messages.cc: s-messages

s-messages: d2_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/bin/d2/d2_messages.mes
	touch $@

BUILT_SOURCES = spec_config.h d2_messages.h d2_messages.cc

# convenience archive

noinst_LTLIBRARIES = libd2.la

libd2_la_SOURCES  =
libd2_la_SOURCES += d_process.h
libd2_la_SOURCES += d_controller.cc d_controller.h
libd2_la_SOURCES += d_cfg_mgr.cc d_cfg_mgr.h
libd2_la_SOURCES += d2_log.cc d2_log.h
libd2_la_SOURCES += d2_process.cc d2_process.h
libd2_la_SOURCES += d2_config.cc d2_config.h
libd2_la_SOURCES += d2_cfg_mgr.cc d2_cfg_mgr.h
libd2_la_SOURCES += d2_queue_mgr.cc d2_queue_mgr.h
libd2_la_SOURCES += d2_update_message.cc d2_update_message.h
libd2_la_SOURCES += d2_update_mgr.cc d2_update_mgr.h
libd2_la_SOURCES += d2_zone.cc d2_zone.h
libd2_la_SOURCES += dns_client.cc dns_client.h
libd2_la_SOURCES += io_service_signal.cc io_service_signal.h
libd2_la_SOURCES += labeled_value.cc labeled_value.h
libd2_la_SOURCES += nc_add.cc nc_add.h
libd2_la_SOURCES += nc_remove.cc nc_remove.h
libd2_la_SOURCES += nc_trans.cc nc_trans.h
libd2_la_SOURCES += state_model.cc state_model.h

libd2_la_SOURCES += d2_controller.cc d2_controller.h

nodist_libd2_la_SOURCES = d2_messages.h d2_messages.cc
EXTRA_DIST += d2_messages.mes

sbin_PROGRAMS = kea-dhcp-ddns

kea_dhcp_ddns_SOURCES  = main.cc

kea_dhcp_ddns_LDADD  = libd2.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
kea_dhcp_ddns_LDADD += $(BOOST_LIBS)

kea_dhcp_ddnsdir = $(pkgdatadir)
kea_dhcp_ddns_DATA = dhcp-ddns.spec
