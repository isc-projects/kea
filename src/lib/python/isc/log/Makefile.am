SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

pythondir = $(pyexecdir)/isc
python_LTLIBRARIES = log.la
log_la_SOURCES = log.cc

log_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
# Note: PYTHON_CXXFLAGS may have some -Wno... workaround, which must be
# placed after -Wextra defined in AM_CXXFLAGS
log_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)
log_la_LDFLAGS = $(PYTHON_LDFLAGS)
log_la_LDFLAGS += -module -avoid-version
log_la_LIBADD = $(top_builddir)/src/lib/log/libb10-log.la
log_la_LIBADD += $(top_builddir)/src/lib/cc/libb10-cc.la
log_la_LIBADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
log_la_LIBADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
log_la_LIBADD += $(PYTHON_LIB)

# This is not installed, it helps locate the module during tests
EXTRA_DIST = __init__.py

pytest:
	$(SHELL) tests/log_test

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
