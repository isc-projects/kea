AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_srcdir)/ext

bin_PROGRAMS = parkinglot
parkinglot_SOURCES = common.cc common.h zoneset.h parkinglot.cc
parkinglot_SOURCES += parkinglot.h ccsession.cc ccsession.h main.cc
parkinglot_SOURCES += data_source_plot.h data_source_plot.cc
parkinglot_LDADD = $(top_srcdir)/src/lib/dns/libdns.a $(top_srcdir)/src/lib/cc/cpp/libcc.a
