SUBDIRS = . tests templates

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

pkglibexec_PROGRAMS = perfdhcp2
perfdhcp2_SOURCES = main.cc
perfdhcp2_SOURCES += command_options.cc command_options.h
perfdhcp2_SOURCES += localized_option.h
perfdhcp2_SOURCES += perf_pkt6.cc perf_pkt6.h
perfdhcp2_SOURCES += perf_pkt4.cc perf_pkt4.h
perfdhcp2_SOURCES += pkt_transform.cc pkt_transform.h
perfdhcp2_SOURCES += stats_mgr.h
perfdhcp2_SOURCES += test_control.cc test_control.h
libb10_perfdhcp___la_CXXFLAGS = $(AM_CXXFLAGS)

perfdhcp2_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
perfdhcp2_CXXFLAGS += -Wno-unused-parameter
endif

perfdhcp2_LDADD = $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
perfdhcp2_LDADD += $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
perfdhcp2_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la

#pkglibexec_PROGRAMS  = perfdhcp
#perfdhcp_SOURCES  = perfdhcp.c
