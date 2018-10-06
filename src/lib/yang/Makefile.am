SUBDIRS = . pretests tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(SYSREPO_CPPFLAGS)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-yang.la
libkea_yang_la_SOURCES  = adaptor.cc adaptor.h
libkea_yang_la_SOURCES += sysrepo_error.h
libkea_yang_la_SOURCES += translator.cc translator.h
libkea_yang_la_SOURCES += translator_logger.cc translator_logger.h
libkea_yang_la_SOURCES += translator_option_data.cc
libkea_yang_la_SOURCES += translator_option_data.h
libkea_yang_la_SOURCES += translator_option_def.cc
libkea_yang_la_SOURCES += translator_option_def.h
libkea_yang_la_SOURCES += translator_pool.cc translator_pool.h
libkea_yang_la_SOURCES += yang_models.h

libkea_yang_la_LIBADD =  $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_yang_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(SYSREPO_LIBS)

libkea_yang_la_LDFLAGS = -no-undefined -version-info 0:0:0

# Specify the headers for copying into the installation directory tree.
libkea_yang_includedir = $(pkgincludedir)/yang
libkea_yang_include_HEADERS = \
	adaptor.h \
	sysrepo_error.h \
	translator.h \
	translator_logger.h \
	translator_option_data.h \
	translator_option_def.h \
	translator_pool.h \
	yang_models.h

EXTRA_DIST = yang.dox
# Distribute yang models.
EXTRA_DIST += models/ietf-dhcpv6-client.yang
EXTRA_DIST += models/ietf-dhcpv6-options.yang
EXTRA_DIST += models/ietf-dhcpv6-relay.yang
EXTRA_DIST += models/ietf-dhcpv6-server.yang
EXTRA_DIST += models/ietf-dhcpv6-types.yang
EXTRA_DIST += models/ietf-inet-types.yang
EXTRA_DIST += models/ietf-yang-types.yang
EXTRA_DIST += models/kea-ctrl-agent.yang
EXTRA_DIST += models/kea-dhcp-ddns.yang
EXTRA_DIST += models/kea-dhcp-types.yang
EXTRA_DIST += models/kea-dhcp4-server.yang
EXTRA_DIST += models/kea-dhcp6-server.yang
EXTRA_DIST += models/kea-logging.yang
EXTRA_DIST += models/kea-types.yang

CLEANFILES = *.gcno *.gcda
