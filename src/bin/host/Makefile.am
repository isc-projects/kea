AM_CPPFLAGS =  -I$(top_builddir)/src/lib -I$(top_srcdir)/ext

CLEANFILES = *.gcno *.gcda

bin_PROGRAMS = host
host_SOURCES = host.cc
host_LDADD = $(top_builddir)/src/lib/dns/.libs/libdns.a
host_LDADD += $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
