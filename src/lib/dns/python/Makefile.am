SUBDIRS = tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS = $(B10_CXXFLAGS)

pyexec_LTLIBRARIES = pydnspp.la
pydnspp_la_SOURCES = pydnspp.cc pydnspp_common.cc
pydnspp_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
pydnspp_la_LDFLAGS = $(PYTHON_LDFLAGS)

# directly included from source files, so these don't have their own
# rules
EXTRA_DIST = pydnspp_common.h
EXTRA_DIST += messagerenderer_python.cc
EXTRA_DIST += message_python.cc
EXTRA_DIST += rrclass_python.cc
EXTRA_DIST += name_python.cc
EXTRA_DIST += rrset_python.cc
EXTRA_DIST += question_python.cc
EXTRA_DIST += rrttl_python.cc
EXTRA_DIST += rdata_python.cc
EXTRA_DIST += rrtype_python.cc

# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
pydnspp_la_LDFLAGS += -module
pydnspp_la_LIBADD = $(top_builddir)/src/lib/dns/libdns++.la
pydnspp_la_LIBADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
pydnspp_la_LIBADD += $(PYTHON_LIB)
