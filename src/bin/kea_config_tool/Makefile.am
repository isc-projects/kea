SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

AM_LDFLAGS = -lm
if USE_STATIC_LINK
AM_LDFLAGS += -static
endif

config_tool_messages.h config_tool_messages.cc: s-messages

s-messages: config_tool_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/bin/kea_config_tool/config_tool_messages.mes
	touch $@

BUILT_SOURCES = config_tool_messages.h config_tool_messages.cc

# convenience archive

noinst_LTLIBRARIES = libkeaconfigtool.la

libkeaconfigtool_la_SOURCES  =
libkeaconfigtool_la_SOURCES += command_options.cc command_options.h
libkeaconfigtool_la_SOURCES += config_tool_controller.cc config_tool_controller.h
libkeaconfigtool_la_SOURCES += server_config.cc server_config.h
libkeaconfigtool_la_SOURCES += config_tool_log.cc config_tool_log.h
libkeaconfigtool_la_SOURCES += kea_admin.cc kea_admin.h

nodist_libkeaconfigtool_la_SOURCES = config_tool_messages.cc config_tool_messages.h
EXTRA_DIST = config_tool_messages.mes

sbin_PROGRAMS = kea-config-tool
kea_config_tool_SOURCES = main.cc
libkea_keaconfigtool___la_CXXFLAGS = $(AM_CXXFLAGS)

kea_config_tool_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

kea_config_tool_LDADD  = libkeaconfigtool.la
kea_config_tool_LDADD += $(top_builddir)/src/bin/dhcp4/libdhcp4.la
kea_config_tool_LDADD += $(top_builddir)/src/bin/dhcp6/libdhcp6.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_config_tool_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
kea_config_tool_LDADD += $(CRYPTO_LIBS)
kea_config_tool_LDADD += $(BOOST_LIBS)
kea_config_tool_LDADD += $(PTHREAD_LDFLAGS)

CLEANFILES = config_tool_messages.h config_tool_messages.cc s-messages

man_MANS = kea-config-tool.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST += $(man_MANS) kea-config-tool.xml

if GENERATE_DOCS

kea-config-tool.8: kea-config-tool.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/kea-config-tool.xml

else

$(man_MANS):
	@echo Man generation disabled. Creating dummy $@. Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled. Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif
