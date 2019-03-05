SUBDIRS = .

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

if GENERATE_MESSAGES

bin_PROGRAMS = kea-msg-compiler

kea_msg_compiler_SOURCES = message.cc
kea_msg_compiler_LDADD   = $(top_builddir)/src/lib/log/libkea-log.la
kea_msg_compiler_LDADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
kea_msg_compiler_LDADD  += $(top_builddir)/src/lib/util/libkea-util.la
kea_msg_compiler_LDADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_msg_compiler_LDADD  += $(LOG4CPLUS_LIBS)

endif
