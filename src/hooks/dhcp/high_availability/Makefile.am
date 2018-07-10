SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Define rule to build logging source files from message file
ha_messages.h ha_messages.cc: s-messages
s-messages: ha_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/high_availability/ha_messages.mes
	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = ha_messages.h ha_messages.cc

# Ensure that the message file is included in the distribution
EXTRA_DIST = ha_messages.mes
EXTRA_DIST += ha.dox

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda ha_messages.h ha_messages.cc s-messages

# convenience archive

noinst_LTLIBRARIES = libha.la

libha_la_SOURCES  = command_creator.cc command_creator.h
libha_la_SOURCES += communication_state.cc communication_state.h
libha_la_SOURCES += ha_callouts.cc
libha_la_SOURCES += ha_config.cc ha_config.h
libha_la_SOURCES += ha_config_parser.cc ha_config_parser.h
libha_la_SOURCES += ha_impl.cc ha_impl.h
libha_la_SOURCES += ha_log.cc ha_log.h
libha_la_SOURCES += ha_server_type.h
libha_la_SOURCES += ha_service.cc ha_service.h
libha_la_SOURCES += ha_service_states.cc ha_service_states.h
libha_la_SOURCES += query_filter.cc query_filter.h
libha_la_SOURCES += version.cc

nodist_libha_la_SOURCES = ha_messages.cc ha_messages.h

libha_la_CXXFLAGS = $(AM_CXXFLAGS)
libha_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/hooks
lib_hooksdir = $(libdir)/hooks
lib_hooks_LTLIBRARIES = libdhcp_ha.la

libdhcp_ha_la_SOURCES  =
libdhcp_ha_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_ha_la_LDFLAGS  += -avoid-version -export-dynamic -module

libdhcp_ha_la_LIBADD  = libha.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_ha_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
