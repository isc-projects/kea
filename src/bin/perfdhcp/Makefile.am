SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

AM_LDFLAGS = -lm
if USE_STATIC_LINK
AM_LDFLAGS += -static
endif

# convenience archive

noinst_LTLIBRARIES = libperfdhcp.la

libperfdhcp_la_SOURCES  =
libperfdhcp_la_SOURCES += command_options.cc command_options.h
libperfdhcp_la_SOURCES += localized_option.h
libperfdhcp_la_SOURCES += perf_pkt6.cc perf_pkt6.h
libperfdhcp_la_SOURCES += perf_pkt4.cc perf_pkt4.h
libperfdhcp_la_SOURCES += packet_storage.h
libperfdhcp_la_SOURCES += pkt_transform.cc pkt_transform.h
libperfdhcp_la_SOURCES += rate_control.cc rate_control.h
libperfdhcp_la_SOURCES += stats_mgr.cc stats_mgr.h
libperfdhcp_la_SOURCES += test_control.cc test_control.h
libperfdhcp_la_SOURCES += random_number_generator.h
libperfdhcp_la_SOURCES += receiver.cc receiver.h
libperfdhcp_la_SOURCES += perf_socket.cc perf_socket.h
libperfdhcp_la_SOURCES += abstract_scen.h
libperfdhcp_la_SOURCES += avalanche_scen.cc avalanche_scen.h
libperfdhcp_la_SOURCES += basic_scen.cc basic_scen.h

sbin_PROGRAMS = perfdhcp
perfdhcp_SOURCES = main.cc

perfdhcp_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

perfdhcp_LDADD = libperfdhcp.la
perfdhcp_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
perfdhcp_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
perfdhcp_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
perfdhcp_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
perfdhcp_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
perfdhcp_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
perfdhcp_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
perfdhcp_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
perfdhcp_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
perfdhcp_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
perfdhcp_LDADD += $(CRYPTO_LIBS)
perfdhcp_LDADD += $(BOOST_LIBS)
perfdhcp_LDADD += $(PTHREAD_LDFLAGS)

# ... and the documentation
EXTRA_DIST = perfdhcp_internals.dox

