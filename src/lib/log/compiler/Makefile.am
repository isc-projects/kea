SUBDIRS = .

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

noinst_PROGRAMS = message

message_SOURCES = message.cc
message_LDADD   = $(top_builddir)/src/lib/log/libb10-log.la
message_LDADD  += $(top_builddir)/src/lib/util/libb10-util.la
message_LDADD  += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
