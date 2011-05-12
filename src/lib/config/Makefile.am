SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += $(BOOST_INCLUDES)

# Define rule to build logging source files from message file
configdef.h configdef.cc: configdef.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/config/configdef.mes

BUILT_SOURCES = configdef.h configdef.cc

lib_LTLIBRARIES = libcfgclient.la
libcfgclient_la_SOURCES = config_data.h config_data.cc
libcfgclient_la_SOURCES += module_spec.h module_spec.cc
libcfgclient_la_SOURCES += ccsession.cc ccsession.h
libcfgclient_la_SOURCES += config_log.h config_log.cc

nodist_libcfgclient_la_SOURCES  = configdef.h configdef.cc

# The message file should be in the distribution.
EXTRA_DIST = configdef.mes

CLEANFILES = *.gcno *.gcda configdef.h configdef.cc
