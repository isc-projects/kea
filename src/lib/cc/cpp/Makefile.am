AM_CPPFLAGS = -I$(top_srcdir)/src/lib/cc/cpp -I$(top_srcdir)/ext

bin_PROGRAMS = test
test_SOURCES = test.cc
test_LDADD = libcc.a
lib_LIBRARIES = libcc.a
libcc_a_SOURCES = data.cc data.h data_def.h data_def.cc session.cc session.h
