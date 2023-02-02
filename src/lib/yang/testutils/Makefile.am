SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(LIBYANG_CPPFLAGS)
AM_CPPFLAGS += $(LIBYANG_INCLUDEDIR)
AM_CPPFLAGS += $(LIBYANGCPP_CPPFLAGS)
AM_CPPFLAGS += $(LIBYANGCPP_INCLUDEDIR)
AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)
AM_CPPFLAGS += $(SYSREPO_INCLUDEDIR)
AM_CPPFLAGS += $(SYSREPOCPP_CPPFLAGS)
AM_CPPFLAGS += $(SYSREPOCPP_INCLUDEDIR)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libyangtest.la

libyangtest_la_SOURCES  = translator_test.cc translator_test.h

libyangtest_la_CXXFLAGS = $(AM_CXXFLAGS)
libyangtest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libyangtest_la_LDFLAGS  = $(AM_LDFLAGS)

libyangtest_la_LIBADD  = $(top_builddir)/src/lib/yang/libkea-yang.la
libyangtest_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la

endif
