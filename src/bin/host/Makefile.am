AM_CPPFLAGS =  -I$(top_builddir)/src/lib -I$(top_builddir)/src/lib/dns/cpp -I$(top_builddir)/include/dns/cpp -I$(top_builddir)/include -I$(top_srcdir)/ext

bin_PROGRAMS = host
host_SOURCES = host.cc
host_LDADD = $(top_builddir)/src/lib/dns/cpp/.libs/libdns.a
host_LDADD += $(top_builddir)/src/lib/exceptions/cpp/.libs/libexceptions.a
