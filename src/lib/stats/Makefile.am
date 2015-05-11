SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS=$(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-stats.la
libkea_stats_la_SOURCES = observation.h observation.cc
libkea_stats_la_SOURCES += context.h context.cc
libkea_stats_la_SOURCES += stats_mgr.h stats_mgr.cc

libkea_stats_la_LIBADD  = $(top_builddir)/src/lib/cc/libkea-cc.la

# This library seem to be required when certain methods are called from
# boost::posix_time. In particular, to_simple_string(ptime) and
# to_simple_string(time_duration) require it on Ubuntu. It doesn't seem
# to be required on Mac OS, though.
libkea_stats_la_LIBADD += -lboost_date_time

libkea_stats_includedir = $(includedir)/$(PACKAGE_NAME)/stats
libkea_stats_include_HEADERS = stats_mgr.h
