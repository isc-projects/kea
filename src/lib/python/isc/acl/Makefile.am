SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

python_PYTHON = __init__.py dns.py
pythondir = $(PYTHON_SITEPKG_DIR)/isc/acl

pyexec_LTLIBRARIES = acl.la _dns.la
pyexecdir = $(PYTHON_SITEPKG_DIR)/isc/acl

acl_la_SOURCES = acl.cc
acl_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
acl_la_LDFLAGS = $(PYTHON_LDFLAGS)
acl_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)

_dns_la_SOURCES = dns.h dns.cc dns_requestacl_python.h dns_requestacl_python.cc
_dns_la_SOURCES += dns_requestcontext_python.h dns_requestcontext_python.cc
_dns_la_SOURCES += dns_requestloader_python.h dns_requestloader_python.cc
_dns_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
_dns_la_LDFLAGS = $(PYTHON_LDFLAGS)
# Note: PYTHON_CXXFLAGS may have some -Wno... workaround, which must be
# placed after -Wextra defined in AM_CXXFLAGS
_dns_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)

# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
acl_la_LDFLAGS += -module -avoid-version
acl_la_LIBADD = $(top_builddir)/src/lib/acl/libb10-acl.la
acl_la_LIBADD += $(PYTHON_LIB)

_dns_la_LDFLAGS += -module -avoid-version
_dns_la_LIBADD = $(top_builddir)/src/lib/acl/libb10-dnsacl.la
_dns_la_LIBADD += $(PYTHON_LIB)

EXTRA_DIST = acl.py _dns.py
EXTRA_DIST += acl_inc.cc
EXTRA_DIST += dnsacl_inc.cc dns_requestacl_inc.cc dns_requestcontext_inc.cc
EXTRA_DIST += dns_requestloader_inc.cc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
