SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

AM_LDFLAGS = $(CLOCK_GETTIME_LDFLAGS)
AM_LDFLAGS += -lm
if USE_STATIC_LINK
AM_LDFLAGS += -static
endif

lib_LTLIBRARIES = libb10_perfdhcp++.la
libb10_perfdhcp___la_SOURCES = command_options.cc command_options.h
libb10_perfdhcp___la_SOURCES += localized_option.h
libb10_perfdhcp___la_SOURCES += perf_pkt6.cc perf_pkt6.h
libb10_perfdhcp___la_SOURCES += perf_pkt4.cc perf_pkt4.h
libb10_perfdhcp___la_SOURCES += pkt_transform.cc pkt_transform.h
libb10_perfdhcp___la_SOURCES += stats_mgr.h

libb10_perfdhcp___la_CXXFLAGS = $(AM_CXXFLAGS)

if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libb10_perfdhcp___la_CXXFLAGS += -Wno-unused-parameter
endif

libb10_perfdhcp___la_LIBADD = $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libb10_perfdhcp___la_LIBADD += $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
libb10_perfdhcp___la_LIBADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la

pkglibexec_PROGRAMS  = perfdhcp
perfdhcp_SOURCES  = perfdhcp.c
