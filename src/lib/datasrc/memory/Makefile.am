SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda datasrc_messages.h datasrc_messages.cc

noinst_LTLIBRARIES = libdatasrc_memory.la

libdatasrc_memory_la_SOURCES = rdata_encoder.h rdata_encoder.cc
libdatasrc_memory_la_SOURCES += domaintree.h
libdatasrc_memory_la_SOURCES += zone_data.h
libdatasrc_memory_la_SOURCES += zone_table.h zone_table.cc
