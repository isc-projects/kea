SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

AM_LDFLAGS = $(CLOCK_GETTIME_LDFLAGS)
AM_LDFLAGS += -lm
if USE_STATIC_LINK
AM_LDFLAGS += -static
endif

# We have to suppress warnings because we are compiling C code with CXX
# We have to do this to link with new C++ pieces of code
perfdhcp_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
perfdhcp_CXXFLAGS += -Wno-error
else
if USE_GXX
perfdhcp_CXXFLAGS += -Wno-write-strings
endif
endif

pkglibexec_PROGRAMS  = perfdhcp
perfdhcp_SOURCES  = perfdhcp.cc
perfdhcp_SOURCES += localized_option.h
perfdhcp_SOURCES += command_options.cc command_options.h
perfdhcp_SOURCES += perf_pkt6.cc perf_pkt6.h

perfdhcp_LDADD = $(top_builddir)/src/lib/exceptions/libexceptions.la
perfdhcp_LDADD += $(top_builddir)/src/lib/dhcp/libdhcp++.la
perfdhcp_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la