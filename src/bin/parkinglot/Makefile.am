AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_srcdir)/ext

bin_PROGRAMS = parkinglot
parkinglot_SOURCES = common.cc common.h zoneset.h zoneset.cc parkinglot.cc
parkinglot_SOURCES += parkinglot.h main.cc
parkinglot_SOURCES += data_source_plot.h data_source_plot.cc
parkinglot_SOURCES += data_source.h data_source.cc
parkinglot_LDADD =  $(top_srcdir)/src/lib/dns/cpp/.libs/libdns.a
parkinglot_LDADD += $(top_srcdir)/src/lib/config/cpp/libclient.a
parkinglot_LDADD += $(top_srcdir)/src/lib/cc/cpp/libcc.a
