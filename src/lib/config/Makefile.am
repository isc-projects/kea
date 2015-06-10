SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += $(BOOST_INCLUDES)

# Define rule to build logging source files from message file
config_messages.h config_messages.cc: s-messages

s-messages: config_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/config/config_messages.mes
	touch $@

BUILT_SOURCES = config_messages.h config_messages.cc

lib_LTLIBRARIES = libkea-cfgclient.la
libkea_cfgclient_la_SOURCES = config_data.h config_data.cc
libkea_cfgclient_la_SOURCES += module_spec.h module_spec.cc
libkea_cfgclient_la_SOURCES += command_mgr.cc command_mgr.h
libkea_cfgclient_la_SOURCES += command_socket_factory.cc command_socket_factory.h
libkea_cfgclient_la_SOURCES += config_log.h config_log.cc

libkea_cfgclient_la_LIBADD = $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la

libkea_cfgclient_la_LDFLAGS = -no-undefined -version-info 1:0:1

nodist_libkea_cfgclient_la_SOURCES  = config_messages.h config_messages.cc

# The message file should be in the distribution.
EXTRA_DIST = config_messages.mes command-socket.dox

CLEANFILES = *.gcno *.gcda config_messages.h config_messages.cc s-messages
