SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += $(BOOST_INCLUDES)

# Define rule to build logging source files from message file
config_messages.h config_messages.cc: config_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/config/config_messages.mes

BUILT_SOURCES = config_messages.h config_messages.cc

lib_LTLIBRARIES = libcfgclient.la
libcfgclient_la_SOURCES = config_data.h config_data.cc
libcfgclient_la_SOURCES += module_spec.h module_spec.cc
libcfgclient_la_SOURCES += ccsession.cc ccsession.h
libcfgclient_la_SOURCES += config_log.h config_log.cc

libcfgclient_la_LIBADD = $(top_builddir)/src/lib/cc/libcc.la
libcfgclient_la_LIBADD += $(top_builddir)/src/lib/exceptions/libexceptions.la

libcfgclient_la_LDFLAGS = -no-undefined -version-info 1:0:1

nodist_libcfgclient_la_SOURCES  = config_messages.h config_messages.cc

# The message file should be in the distribution.
EXTRA_DIST = config_messages.mes

CLEANFILES = *.gcno *.gcda config_messages.h config_messages.cc
