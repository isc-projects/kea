AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_builddir)/src/lib/dns/cpp -I$(top_srcdir)/src/lib/dns/cpp -I$(top_srcdir)/src/lib -I$(top_srcdir)/ext

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_PROGRAMS = b10-parkinglot

b10_parkinglot_SOURCES = b10-parkinglot.cc b10-parkinglot.h
b10_parkinglot_SOURCES += common.cc common.h zoneset.h zoneset.cc main.cc
b10_parkinglot_SOURCES += data_source_plot.h data_source_plot.cc
b10_parkinglot_SOURCES += data_source.h data_source.cc
b10_parkinglot_SOURCES += builtin.h builtin.cc
b10_parkinglot_LDADD =  $(top_builddir)/src/lib/dns/cpp/.libs/libdns.a
b10_parkinglot_LDADD += $(top_builddir)/src/lib/config/cpp/libclient.a
b10_parkinglot_LDADD += $(top_builddir)/src/lib/cc/cpp/libcc.a

b10_parkinglotdir = $(DESTDIR)$(pkgdatadir)
b10_parkinglot_DATA = parkinglot.spec

# TODO: don't install this here
bin_PROGRAMS = builtin_bench
builtin_bench_SOURCES = builtin_bench.cc builtin.h builtin.cc
builtin_bench_LDADD = $(top_builddir)/src/lib/dns/cpp/.libs/libdns.a
