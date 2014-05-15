SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

# There is a build problem with python3.4 (a new field tp_finalize) has been
# added and now compiler complains about it not being properly initialized in
# construtor. Since the whole python thing goes away, it's counter-productive
# to spend any time on making this work on both python3.3 and 3.4, so
# ingoring the warning seems the way to go.
AM_CXXFLAGS += -Wno-error

pythondir = $(pyexecdir)/isc
python_LTLIBRARIES = log.la
log_la_SOURCES = log.cc

log_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
# Note: PYTHON_CXXFLAGS may have some -Wno... workaround, which must be
# placed after -Wextra defined in AM_CXXFLAGS
log_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)
log_la_LDFLAGS = $(PYTHON_LDFLAGS)
log_la_LDFLAGS += -module -avoid-version
log_la_LIBADD = $(top_builddir)/src/lib/log/libkea-log.la
log_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
log_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
log_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
log_la_LIBADD += $(PYTHON_LIB)

# This is not installed, it helps locate the module during tests
EXTRA_DIST = __init__.py

pytest:
	$(SHELL) tests/log_test

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
