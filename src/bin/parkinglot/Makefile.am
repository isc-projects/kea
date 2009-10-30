AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_srcdir)/ext

bin_PROGRAMS = parkinglot
parkinglot_SOURCES = common.cc common.h main.cc zoneset.h parkinglot.cc parkinglot.h
parkinglot_LDADD = $(top_srcdir)/src/lib/dns/libdns.a $(top_srcdir)/src/lib/cc/cpp/libcc.a
