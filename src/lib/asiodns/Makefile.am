SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink -I$(top_builddir)/src/lib/asiolink

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

# This is a wrapper library solely used for b10-auth.  The ASIO header files
# have some code fragments that would hit gcc's unused-parameter warning,
# which would make the build fail with -Werror (our default setting).
lib_LTLIBRARIES = libasiodns.la
libasiodns_la_SOURCES = dns_answer.h
libasiodns_la_SOURCES += dns_lookup.h
libasiodns_la_SOURCES += dns_server.h
libasiodns_la_SOURCES += dns_service.cc dns_service.h

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
libasiodns_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# Same for clang++, but we need to turn off -Werror completely.
libasiodns_la_CXXFLAGS += -Wno-error
endif
libasiodns_la_CPPFLAGS = $(AM_CPPFLAGS)
libasiodns_la_LIBADD = $(top_builddir)/src/lib/log/liblog.la
