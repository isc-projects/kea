SUBDIRS = tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

pythondir = $(pyexecdir)/isc
python_LTLIBRARIES = log.la
log_la_SOURCES = main.cc

log_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
log_la_LDFLAGS = $(PYTHON_LDFLAGS)
log_la_LDFLAGS += -module
log_la_LIBADD = $(top_builddir)/src/lib/log/liblog.la
log_la_LIBADD += $(PYTHON_LIB)
