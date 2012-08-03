AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

noinst_LTLIBRARIES = pyunittests_util.la

pyunittests_util_la_SOURCES = pyunittests_util.cc
pyunittests_util_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
pyunittests_util_la_LDFLAGS = $(PYTHON_LDFLAGS)
# Note: PYTHON_CXXFLAGS may have some -Wno... workaround, which must be
# placed after -Wextra defined in AM_CXXFLAGS
pyunittests_util_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)

# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
pyunittests_util_la_LDFLAGS += -module -avoid-version
pyunittests_util_la_LIBADD = $(top_builddir)/src/lib/util/libb10-util.la
pyunittests_util_la_LIBADD += $(PYTHON_LIB)

# hack to trigger libtool to not create a convenience archive,
# resulting in shared modules
pyunittests_util_la_LDFLAGS += -rpath /nowhere
