SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libdhcptest.la

libdhcptest_la_SOURCES  = iface_mgr_test_config.cc iface_mgr_test_config.h
libdhcptest_la_SOURCES += pkt_filter_test_stub.cc pkt_filter_test_stub.h
libdhcptest_la_SOURCES += pkt_filter6_test_stub.cc pkt_filter6_test_stub.h
libdhcptest_la_SOURCES += pkt_captures4.cc pkt_captures6.cc pkt_captures.h

libdhcptest_la_CXXFLAGS = $(AM_CXXFLAGS)
libdhcptest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

libdhcptest_la_LIBADD  =
libdhcptest_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la

endif
