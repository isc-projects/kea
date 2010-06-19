SUBDIRS = . 

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/ext -Wno-strict-aliasing

if GCC_WERROR_OK
AM_CPPFLAGS += -Werror
endif

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libxfr.la
libxfr_la_SOURCES = xfrout_client.h xfrout_client.cc 
libxfr_la_SOURCES += fd_share.h fd_share.cc

if HAVE_BOOST_PYTHON
pyexec_LTLIBRARIES = bind10_xfr.la
bind10_xfr_la_SOURCES = python_xfr.cc fd_share.cc fd_share.h
bind10_xfr_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
if GCC_WERROR_OK
# XXX: Boost.Python triggers strict aliasing violation, so if we use -Werror
# we need to suppress the warnings.
bind10_xfr_la_CPPFLAGS += -fno-strict-aliasing
endif
bind10_xfr_la_LDFLAGS = $(BOOST_LDFLAGS) $(PYTHON_LDFLAGS)
# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
bind10_xfr_la_LDFLAGS += -module
bind10_xfr_la_LIBADD = $(BOOST_PYTHON_LIB) $(PYTHON_LIB)
endif

