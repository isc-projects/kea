SUBDIRS = . tests benchmarks

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda datasrc_messages.h datasrc_messages.cc

noinst_LTLIBRARIES = libdatasrc_memory.la

libdatasrc_memory_la_SOURCES = \
	rdataset.h rdataset.cc \
	rdata_serialization.h rdata_serialization.cc \
	domaintree.h
EXTRA_DIST  = rdata_serialization_priv.cc
