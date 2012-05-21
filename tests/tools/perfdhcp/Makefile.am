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

# We have to suppress errors because we are compiling C code with CXX
# We have to do this to link with new C++ pieces of code
perfdhcp_CXXFLAGS = $(AM_CXXFLAGS)
perfdhcp_CXXFLAGS += -Wno-error -Wno-writestrings

pkglibexec_PROGRAMS  = perfdhcp
perfdhcp_SOURCES  = perfdhcp.cc
perfdhcp_SOURCES += command_options.cc command_options.h

perfdhcp_LDADD = $(top_builddir)/src/lib/exceptions/libexceptions.la
