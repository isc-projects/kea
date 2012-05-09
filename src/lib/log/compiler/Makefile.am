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
message_LDADD   = $(top_builddir)/src/lib/log/liblog.la
message_LDADD  += $(top_builddir)/src/lib/util/libutil.la
message_LDADD  += $(top_builddir)/src/lib/exceptions/libexceptions.la
