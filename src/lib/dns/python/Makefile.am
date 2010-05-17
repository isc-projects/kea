AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib

#lib_LTLIBRARIES = libdns_python_name.la libdns_python_rrset.la
#libdns_python_name_la_SOURCES = name_python.cc
#libdns_python_name_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
#libdns_python_name_la_LDFLAGS = $(PYTHON_LDFLAGS)

#lib_LTLIBRARIES = libdns_python_name.la libdns_python_rrset.la
pyexec_LTLIBRARIES = libdns_python.la
libdns_python_la_SOURCES = libdns_python.cc libdns_python_common.cc
libdns_python_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
libdns_python_la_LDFLAGS = $(PYTHON_LDFLAGS)

#libdns_python_rrset_la_SOURCES = rrset_python.cc
#libdns_python_rrset_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
#libdns_python_rrset_la_LDFLAGS = $(PYTHON_LDFLAGS) libdns_python_name.la

#libdns_python_rrset_la_SOURCES = rrset_python.cc
#libdns_python_rrset_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
#libdns_python_rrset_la_LDFLAGS = $(PYTHON_LDFLAGS)

# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
libdns_python_la_LDFLAGS += -module
libdns_python_la_LIBADD = $(top_builddir)/src/lib/dns/libdns.la
libdns_python_la_LIBADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
libdns_python_la_LIBADD += $(PYTHON_LIB)
