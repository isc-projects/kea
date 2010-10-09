AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns

AM_CXXFLAGS = $(B10_CXXFLAGS) -Wno-strict-aliasing
AM_CXXFLAGS += -Wno-unused-parameter # see src/lib/cc/Makefile.am
#for clang++
AM_CXXFLAGS += -Wno-unused-function
AM_CXXFLAGS += -Wno-char-subscripts

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libxfr.la
libxfr_la_SOURCES = xfrout_client.h xfrout_client.cc 
libxfr_la_SOURCES += fd_share.h fd_share.cc

pyexec_LTLIBRARIES = libxfr_python.la
# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
libxfr_python_la_LDFLAGS = -module
libxfr_python_la_SOURCES = fdshare_python.cc fd_share.cc fd_share.h
libxfr_python_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
libxfr_python_la_CXXFLAGS = $(AM_CXXFLAGS)
