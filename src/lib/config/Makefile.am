SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += $(BOOST_INCLUDES)

lib_LTLIBRARIES = libkea-cfgclient.la
libkea_cfgclient_la_SOURCES = config_data.h config_data.cc
libkea_cfgclient_la_SOURCES += module_spec.h module_spec.cc
libkea_cfgclient_la_SOURCES += config_log.h config_log.cc

libkea_cfgclient_la_LIBADD = $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la

libkea_cfgclient_la_LDFLAGS = -no-undefined -version-info 1:0:1

CLEANFILES = *.gcno *.gcda
