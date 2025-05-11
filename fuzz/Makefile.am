SUBDIRS = . input tests

if FUZZING

AM_CPPFLAGS  =
AM_CPPFLAGS += -I$(top_builddir)/src/bin -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -DKEA_FUZZ_DIR_INSTALLATION=\"$(datarootdir)/$(PACKAGE_NAME)/fuzzing\"
AM_CPPFLAGS += -DKEA_FUZZ_DIR_SOURCES=\"$(abs_top_builddir)/fuzz\"
AM_CPPFLAGS += -DKEA_LFC_INSTALLATION=\"$(prefix)/sbin/kea-lfc\"
AM_CPPFLAGS += -DKEA_LFC_SOURCES=\"$(abs_top_builddir)/src/bin/lfc/kea-lfc\"
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += $(GTEST_INCLUDES)

AM_CXXFLAGS  =
AM_CXXFLAGS += $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

sbin_PROGRAMS  =
sbin_PROGRAMS += fuzz_config_kea_dhcp4
sbin_PROGRAMS += fuzz_config_kea_dhcp6
sbin_PROGRAMS += fuzz_http_endpoint_kea_dhcp4
sbin_PROGRAMS += fuzz_http_endpoint_kea_dhcp6
sbin_PROGRAMS += fuzz_packets_kea_dhcp4
sbin_PROGRAMS += fuzz_packets_kea_dhcp6
sbin_PROGRAMS += fuzz_unix_socket_kea_dhcp4
sbin_PROGRAMS += fuzz_unix_socket_kea_dhcp6

V6_LDADD = $(top_builddir)/src/bin/dhcp6/libdhcp6.la
V4_LDADD = $(top_builddir)/src/bin/dhcp4/libdhcp4.la
LDADD  =
LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
LDADD += $(top_builddir)/src/lib/process/libkea-process.la
LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
LDADD += $(top_builddir)/src/lib/http/libkea-http.la
LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
LDADD += $(top_builddir)/src/lib/database/libkea-database.la
LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
LDADD += $(top_builddir)/src/lib/log/libkea-log.la
LDADD += $(top_builddir)/src/lib/util/libkea-util.la
LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)
LDADD += $(GTEST_LDADD)

AM_LDFLAGS = $(GTEST_LDFLAGS)

common_sources = fuzz.cc fuzz.h
if FUZZING_IN_CI
AM_CXXFLAGS += -fsanitize=fuzzer -gdwarf-4
else
common_sources += main.cc
endif

fuzz_config_kea_dhcp4_SOURCES  = $(common_sources)
fuzz_config_kea_dhcp4_SOURCES += fuzz_config_kea_dhcp4.cc
fuzz_config_kea_dhcp4_LDADD = $(V4_LDADD) $(LDADD)

fuzz_config_kea_dhcp6_SOURCES  = $(common_sources)
fuzz_config_kea_dhcp6_SOURCES += fuzz_config_kea_dhcp6.cc
fuzz_config_kea_dhcp6_LDADD = $(V6_LDADD) $(LDADD)

fuzz_http_endpoint_kea_dhcp4_SOURCES  = $(common_sources)
fuzz_http_endpoint_kea_dhcp4_SOURCES += fuzz_http_endpoint_kea_dhcp4.cc
fuzz_http_endpoint_kea_dhcp4_LDADD = $(V4_LDADD) $(LDADD)

fuzz_http_endpoint_kea_dhcp6_SOURCES  = $(common_sources)
fuzz_http_endpoint_kea_dhcp6_SOURCES += fuzz_http_endpoint_kea_dhcp6.cc
fuzz_http_endpoint_kea_dhcp6_LDADD = $(V6_LDADD) $(LDADD)

fuzz_packets_kea_dhcp4_SOURCES  = $(common_sources)
fuzz_packets_kea_dhcp4_SOURCES += fuzz_packets_kea_dhcp4.cc
fuzz_packets_kea_dhcp4_LDADD = $(V4_LDADD) $(LDADD)

fuzz_packets_kea_dhcp6_SOURCES  = $(common_sources)
fuzz_packets_kea_dhcp6_SOURCES += fuzz_packets_kea_dhcp6.cc
fuzz_packets_kea_dhcp6_LDADD = $(V6_LDADD) $(LDADD)

fuzz_unix_socket_kea_dhcp4_SOURCES  = $(common_sources)
fuzz_unix_socket_kea_dhcp4_SOURCES += fuzz_unix_socket_kea_dhcp4.cc
fuzz_unix_socket_kea_dhcp4_LDADD = $(V4_LDADD) $(LDADD)

fuzz_unix_socket_kea_dhcp6_SOURCES  = $(common_sources)
fuzz_unix_socket_kea_dhcp6_SOURCES += fuzz_unix_socket_kea_dhcp6.cc
fuzz_unix_socket_kea_dhcp6_LDADD = $(V6_LDADD) $(LDADD)

endif  # FUZZING
