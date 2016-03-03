SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libdhcpsrvtest.la

libdhcpsrvtest_la_SOURCES  = config_result_check.cc config_result_check.h
if HAVE_MYSQL
libdhcpsrvtest_la_SOURCES += mysql_schema.cc mysql_schema.h
libdhcpsrvtest_la_SOURCES += schema_mysql_copy.h
endif

libdhcpsrvtest_la_CXXFLAGS = $(AM_CXXFLAGS)
libdhcpsrvtest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
if HAVE_MYSQL
libdhcpsrvtest_la_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif
libdhcpsrvtest_la_LDFLAGS  = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
if HAVE_MYSQL
libdhcpsrvtest_la_LDFLAGS  += $(MYSQL_LIBS)
endif
libdhcpsrvtest_la_LIBADD   = $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcpsrvtest_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la

endif
