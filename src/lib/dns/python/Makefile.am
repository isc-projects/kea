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

lib_LTLIBRARIES = libkea-pydnspp.la
libkea_pydnspp_la_SOURCES = pydnspp_common.cc pydnspp_common.h
libkea_pydnspp_la_SOURCES += pydnspp_config.h pydnspp_towire.h
libkea_pydnspp_la_SOURCES += name_python.cc name_python.h
libkea_pydnspp_la_SOURCES += nsec3hash_python.cc nsec3hash_python.h
libkea_pydnspp_la_SOURCES += rrset_python.cc rrset_python.h
libkea_pydnspp_la_SOURCES += rrclass_python.cc rrclass_python.h
libkea_pydnspp_la_SOURCES += rrtype_python.cc rrtype_python.h
libkea_pydnspp_la_SOURCES += rrttl_python.cc rrttl_python.h
libkea_pydnspp_la_SOURCES += rdata_python.cc rdata_python.h
libkea_pydnspp_la_SOURCES += serial_python.cc serial_python.h
libkea_pydnspp_la_SOURCES += messagerenderer_python.cc messagerenderer_python.h
libkea_pydnspp_la_SOURCES += rcode_python.cc rcode_python.h
libkea_pydnspp_la_SOURCES += opcode_python.cc opcode_python.h
libkea_pydnspp_la_SOURCES += question_python.cc question_python.h
libkea_pydnspp_la_SOURCES += tsigkey_python.cc tsigkey_python.h
libkea_pydnspp_la_SOURCES += tsigerror_python.cc tsigerror_python.h
libkea_pydnspp_la_SOURCES += tsig_rdata_python.cc tsig_rdata_python.h
libkea_pydnspp_la_SOURCES += tsigrecord_python.cc tsigrecord_python.h
libkea_pydnspp_la_SOURCES += tsig_python.cc tsig_python.h
libkea_pydnspp_la_SOURCES += edns_python.cc edns_python.h
libkea_pydnspp_la_SOURCES += message_python.cc message_python.h
libkea_pydnspp_la_SOURCES += rrset_collection_python.cc
libkea_pydnspp_la_SOURCES += rrset_collection_python.h
libkea_pydnspp_la_SOURCES += zone_checker_python.cc zone_checker_python.h

libkea_pydnspp_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
libkea_pydnspp_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)
libkea_pydnspp_la_LDFLAGS = $(PYTHON_LDFLAGS)



pyexec_LTLIBRARIES = pydnspp.la
pydnspp_la_SOURCES = pydnspp.cc
pydnspp_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
# Note: PYTHON_CXXFLAGS may have some -Wno... workaround, which must be
# placed after -Wextra defined in AM_CXXFLAGS
pydnspp_la_CXXFLAGS = $(AM_CXXFLAGS) $(PYTHON_CXXFLAGS)
pydnspp_la_LDFLAGS = $(PYTHON_LDFLAGS)

EXTRA_DIST = tsigerror_python_inc.cc
EXTRA_DIST += message_python_inc.cc
EXTRA_DIST += nsec3hash_python_inc.cc
EXTRA_DIST += rrset_collection_python_inc.cc
EXTRA_DIST += zone_checker_python_inc.cc

# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
pydnspp_la_LDFLAGS += -module -avoid-version
pydnspp_la_LIBADD = $(top_builddir)/src/lib/dns/libkea-dns++.la
pydnspp_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
pydnspp_la_LIBADD += libkea-pydnspp.la
pydnspp_la_LIBADD += $(PYTHON_LIB)
