SUBDIRS = .

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# This check is for clang complaining about unused parameter
# in boost version included in FreeBSD 10.
if USE_CLANGPP
AM_CXXFLAGS +=-Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

bin_PROGRAMS = kea-msg-compiler

kea_msg_compiler_SOURCES = message.cc
kea_msg_compiler_LDADD   = $(top_builddir)/src/lib/log/libkea-log.la
kea_msg_compiler_LDADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
kea_msg_compiler_LDADD  += $(top_builddir)/src/lib/util/libkea-util.la
kea_msg_compiler_LDADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_msg_compiler_LDADD  += $(LOG4CPLUS_LIBS)
