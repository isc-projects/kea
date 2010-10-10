SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns

AM_CXXFLAGS = $(B10_CXXFLAGS)
if USE_GXX
# ASIO header files used in session.cc will trigger the "unused-parameter"
# warning.  Unfortunately there doesn't seem to be an easy way to selectively
# avoid the error.  As a short term workaround we suppress this warning
# for the entire this module.  See also src/bin/auth/Makefile.am.
AM_CXXFLAGS += -Wno-unused-parameter
endif
if USE_CLANGPP
# Likewise, ASIO header files will trigger various warnings with clang++.
# Worse, there doesn't seem to be any option to disable one of the warnings
# in any way, so we need to turn off -Werror.
AM_CXXFLAGS += -Wno-error
endif

lib_LTLIBRARIES = libcc.la
libcc_la_SOURCES = data.cc data.h session.cc session.h

CLEANFILES = *.gcno *.gcda session_config.h

session_config.h: session_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" session_config.h.pre >$@

BUILT_SOURCES = session_config.h 
