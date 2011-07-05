SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
#Do we need boost?
#AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

pyexec_LTLIBRARIES = dns.la
dns_la_SOURCES = dns.cc
dns_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
dns_la_LDFLAGS = $(PYTHON_LDFLAGS)
# Note: PYTHON_CXXFLAGS may have some -Wno... workaround, which must be
# placed after -Wextra defined in AM_CXXFLAGS
acl_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)

# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
dns_la_LDFLAGS += -module
dns_la_LIBADD = $(top_builddir)/src/lib/acl/libacl.la
dns_la_LIBADD += $(PYTHON_LIB)
