AM_CPPFLAGS =  -I$(top_builddir)/src/lib -I$(top_builddir)/src/lib/dns/cpp -I$(top_srcdir)/src/lib/dns/cpp -I$(top_srcdir)/src/lib -I$(top_srcdir)/ext

bin_PROGRAMS = host
host_SOURCES = host.cc
host_LDADD = $(top_builddir)/src/lib/dns/cpp/.libs/libdns.a
