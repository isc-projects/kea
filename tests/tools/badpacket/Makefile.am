SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS  = badpacket
badpacket_SOURCES  = badpacket.cc
badpacket_SOURCES += command_options.cc command_options.h
badpacket_SOURCES += header_flags.h
badpacket_SOURCES += option_info.cc option_info.h
badpacket_SOURCES += scan.cc scan.h
badpacket_SOURCES += version.h

badpacket_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
badpacket_CXXFLAGS += -Wno-error
endif

badpacket_LDADD  = $(top_builddir)/src/lib/asiodns/libasiodns.la
badpacket_LDADD += $(top_builddir)/src/lib/dns/libdns++.la
badpacket_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
badpacket_LDADD += $(top_builddir)/src/lib/log/liblog.la
badpacket_LDADD += $(top_builddir)/src/lib/util/libutil.la
badpacket_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
