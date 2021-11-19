SUBDIRS = . testutils pretests tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)
AM_CPPFLAGS += $(SYSREPO_INCLUDEDIR)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-yang.la
libkea_yang_la_SOURCES  = adaptor.cc adaptor.h
libkea_yang_la_SOURCES += adaptor_host.cc adaptor_host.h
libkea_yang_la_SOURCES += adaptor_pool.cc adaptor_pool.h
libkea_yang_la_SOURCES += adaptor_option.cc adaptor_option.h
libkea_yang_la_SOURCES += adaptor_subnet.cc adaptor_subnet.h
libkea_yang_la_SOURCES += adaptor_config.cc adaptor_config.h
libkea_yang_la_SOURCES += sysrepo_error.h
libkea_yang_la_SOURCES += translator.cc translator.h
libkea_yang_la_SOURCES += translator_control_socket.cc
libkea_yang_la_SOURCES += translator_control_socket.h
libkea_yang_la_SOURCES += translator_database.cc translator_database.h
libkea_yang_la_SOURCES += translator_logger.cc translator_logger.h
libkea_yang_la_SOURCES += translator_option_data.cc
libkea_yang_la_SOURCES += translator_option_data.h
libkea_yang_la_SOURCES += translator_option_def.cc
libkea_yang_la_SOURCES += translator_option_def.h
libkea_yang_la_SOURCES += translator_class.cc translator_class.h
libkea_yang_la_SOURCES += translator_pool.cc translator_pool.h
libkea_yang_la_SOURCES += translator_pd_pool.cc translator_pd_pool.h
libkea_yang_la_SOURCES += translator_host.cc translator_host.h
libkea_yang_la_SOURCES += translator_subnet.cc translator_subnet.h
libkea_yang_la_SOURCES += translator_shared_network.cc
libkea_yang_la_SOURCES += translator_shared_network.h
libkea_yang_la_SOURCES += translator_config.cc translator_config.h
libkea_yang_la_SOURCES += yang_models.h yang_revisions.h

libkea_yang_la_LIBADD =  $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_yang_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(SYSREPO_LIBS)

libkea_yang_la_LDFLAGS = -no-undefined -version-info 27:0:0

# Specify the headers for copying into the installation directory tree.
libkea_yang_includedir = $(pkgincludedir)/yang
libkea_yang_include_HEADERS = \
	adaptor.h \
	adaptor_config.h \
	adaptor_host.h \
	adaptor_option.h \
	adaptor_pool.h \
	adaptor_subnet.h \
	sysrepo_error.h \
	translator.h \
	translator_class.h \
	translator_config.h \
	translator_control_socket.h \
	translator_database.h \
	translator_host.h \
	translator_logger.h \
	translator_option_data.h \
	translator_option_def.h \
	translator_pd_pool.h \
	translator_pool.h \
	translator_shared_network.h \
	translator_subnet.h \
	yang_models.h \
	yang_revisions.h

EXTRA_DIST = yang.dox yang_revisions.h.skel

CLEANFILES = *.gcno *.gcda
