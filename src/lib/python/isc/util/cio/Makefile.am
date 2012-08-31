SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

python_PYTHON = __init__.py
pythondir = $(PYTHON_SITEPKG_DIR)/isc/util/cio

pyexec_LTLIBRARIES = socketsession.la
pyexecdir = $(PYTHON_SITEPKG_DIR)/isc/util/cio

socketsession_la_SOURCES = socketsession_python.cc socketsession_python.h
socketsession_la_SOURCES += socketsessionforwarder_python.cc
socketsession_la_SOURCES += socketsessionforwarder_python.h
socketsession_la_SOURCES += socketsessionreceiver_python.cc
socketsession_la_SOURCES += socketsessionreceiver_python.h
socketsession_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
socketsession_la_LDFLAGS = $(PYTHON_LDFLAGS)
# Note: PYTHON_CXXFLAGS may have some -Wno... workaround, which must be
# placed after -Wextra defined in AM_CXXFLAGS
socketsession_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)

# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
socketsession_la_LDFLAGS += -module -avoid-version
socketsession_la_LIBADD = $(top_builddir)/src/lib/util/io/libb10-util-io.la
socketsession_la_LIBADD += $(PYTHON_LIB)

# This is not installed, it helps locate the module during tests
EXTRA_DIST = __init__.py socketsession.py

EXTRA_DIST += socketsession_inc.cc
EXTRA_DIST += socketsessionforwarder_inc.cc socketsessionreceiver_inc.cc

CLEANFILES = __init__.pyc socketsession.pyc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
