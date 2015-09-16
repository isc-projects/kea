SUBDIRS = .

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

bin_PROGRAMS = message

message_SOURCES = message.cc
message_LDADD   = $(top_builddir)/src/lib/log/libkea-log.la
message_LDADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
message_LDADD  += $(top_builddir)/src/lib/util/libkea-util.la
message_LDADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
message_LDADD  += $(LOG4CPLUS_LIBS)
