SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS  = perfdhcp
perfdhcp_SOURCES  = perfdhcp.cc
perfdhcp_SOURCES += packetdisp.c
perfdhcp_SOURCES += perfdhcp.h
perfdhcp_SOURCES += dhcp.h dhcp6.h
perfdhcp_SOURCES += cloptions.cc
perfdhcp_SOURCES += dkdebug.cc dkdebug.h
perfdhcp_SOURCES += procconf.h procconf.cc

perfdhcp_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
perfdhcp_CXXFLAGS += -Wno-error
endif
