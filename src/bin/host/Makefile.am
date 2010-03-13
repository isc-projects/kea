AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/ext

CLEANFILES = *.gcno *.gcda

bin_PROGRAMS = host
host_SOURCES = host.cc
host_LDADD = $(top_builddir)/src/lib/dns/.libs/libdns.a
host_LDADD += $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
