SUBDIRS = .
dhcp_data_dir = @localstatedir@/@PACKAGE@
AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/process/tests\"
AM_CPPFLAGS += -DDATA_DIR="\"$(dhcp_data_dir)\""
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libprocess_unittests

libprocess_unittests_SOURCES  = d_cfg_mgr_unittests.cc
libprocess_unittests_SOURCES += cb_ctl_base_unittests.cc
libprocess_unittests_SOURCES += config_base_unittests.cc
libprocess_unittests_SOURCES += config_ctl_info_unittests.cc
libprocess_unittests_SOURCES += config_ctl_parser_unittests.cc
libprocess_unittests_SOURCES += d_controller_unittests.cc
libprocess_unittests_SOURCES += daemon_unittest.cc
libprocess_unittests_SOURCES += io_service_signal_unittests.cc
libprocess_unittests_SOURCES += log_parser_unittests.cc
libprocess_unittests_SOURCES += logging_info_unittests.cc
libprocess_unittests_SOURCES += run_unittests.cc

libprocess_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

libprocess_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libprocess_unittests_LDFLAGS  = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

libprocess_unittests_LDADD  = $(top_builddir)/src/lib/process/testutils/libprocesstest.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libprocess_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libprocess_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
libprocess_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
