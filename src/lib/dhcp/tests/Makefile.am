SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/dhcp/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

# Creates a library which is shared by various unit tests which require
# configuration of fake interfaces.
# The libdhcp++ does not link with this library because this would cause
# build failures being a result of concurrency between build of this
# library and the unit tests when make -j option was used, as they
# are built out of the same makefile. Instead, the libdhcp++ tests link to
# files belonging to this library, directly.
noinst_LTLIBRARIES = libdhcptest.la

libdhcptest_la_SOURCES  = iface_mgr_test_config.cc iface_mgr_test_config.h
libdhcptest_la_SOURCES  += pkt_filter_test_stub.cc pkt_filter_test_stub.h
libdhcptest_la_SOURCES  += pkt_filter6_test_stub.cc pkt_filter6_test_stub.h
libdhcptest_la_SOURCES  += pkt_captures4.cc pkt_captures6.cc pkt_captures.h
libdhcptest_la_CXXFLAGS  = $(AM_CXXFLAGS)
libdhcptest_la_CPPFLAGS  = $(AM_CPPFLAGS)
libdhcptest_la_LDFLAGS   = $(AM_LDFLAGS)
libdhcptest_la_LIBADD    = $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la

TESTS += libdhcp++_unittests

libdhcp___unittests_SOURCES  = run_unittests.cc
libdhcp___unittests_SOURCES += classify_unittest.cc
libdhcp___unittests_SOURCES += duid_factory_unittest.cc
libdhcp___unittests_SOURCES += hwaddr_unittest.cc
libdhcp___unittests_SOURCES += iface_mgr_unittest.cc
libdhcp___unittests_SOURCES += iface_mgr_test_config.cc iface_mgr_test_config.h
libdhcp___unittests_SOURCES += libdhcp++_unittest.cc
libdhcp___unittests_SOURCES += opaque_data_tuple_unittest.cc
libdhcp___unittests_SOURCES += option4_addrlst_unittest.cc
libdhcp___unittests_SOURCES += option4_client_fqdn_unittest.cc
libdhcp___unittests_SOURCES += option6_addrlst_unittest.cc
libdhcp___unittests_SOURCES += option6_client_fqdn_unittest.cc
libdhcp___unittests_SOURCES += option6_ia_unittest.cc
libdhcp___unittests_SOURCES += option6_iaaddr_unittest.cc
libdhcp___unittests_SOURCES += option6_iaprefix_unittest.cc
libdhcp___unittests_SOURCES += option6_status_code_unittest.cc
libdhcp___unittests_SOURCES += option_int_unittest.cc
libdhcp___unittests_SOURCES += option_int_array_unittest.cc
libdhcp___unittests_SOURCES += option_data_types_unittest.cc
libdhcp___unittests_SOURCES += option_definition_unittest.cc
libdhcp___unittests_SOURCES += option_custom_unittest.cc
libdhcp___unittests_SOURCES += option_opaque_data_tuples_unittest.cc
libdhcp___unittests_SOURCES += option_unittest.cc
libdhcp___unittests_SOURCES += option_space_unittest.cc
libdhcp___unittests_SOURCES += option_string_unittest.cc
libdhcp___unittests_SOURCES += option_vendor_unittest.cc
libdhcp___unittests_SOURCES += option_vendor_class_unittest.cc
libdhcp___unittests_SOURCES  += pkt_captures4.cc pkt_captures6.cc pkt_captures.h
libdhcp___unittests_SOURCES += pkt4_unittest.cc
libdhcp___unittests_SOURCES += pkt6_unittest.cc
libdhcp___unittests_SOURCES += pkt4o6_unittest.cc
libdhcp___unittests_SOURCES += pkt_filter_unittest.cc
libdhcp___unittests_SOURCES += pkt_filter_inet_unittest.cc
libdhcp___unittests_SOURCES += pkt_filter_inet6_unittest.cc
libdhcp___unittests_SOURCES += pkt_filter_test_stub.cc pkt_filter_test_stub.h
libdhcp___unittests_SOURCES += pkt_filter6_test_stub.cc pkt_filter_test_stub.h
libdhcp___unittests_SOURCES += pkt_filter_test_utils.h pkt_filter_test_utils.cc
libdhcp___unittests_SOURCES += pkt_filter6_test_utils.h pkt_filter6_test_utils.cc

# Utilize Linux Packet Filtering on Linux.
if OS_LINUX
libdhcp___unittests_SOURCES += pkt_filter_lpf_unittest.cc
endif

# Utilize Berkeley Packet Filtering on BSD.
if OS_BSD
libdhcp___unittests_SOURCES += pkt_filter_bpf_unittest.cc
endif

libdhcp___unittests_SOURCES += protocol_util_unittest.cc
libdhcp___unittests_SOURCES += duid_unittest.cc

libdhcp___unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

libdhcp___unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

libdhcp___unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# This is to workaround unused variables tcout and tcerr in
# log4cplus's streams.h and unused parameters from some of the
# Boost headers.
libdhcp___unittests_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter
endif

libdhcp___unittests_LDADD  = $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp___unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp___unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
libdhcp___unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
