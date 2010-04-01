AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
if GCC_WERROR_OK
AM_CPPFLAGS += -Werror
endif

pyexec_LTLIBRARIES = bind10_dns_noboost.la
bind10_dns_noboost_la_SOURCES = cpp_binding.cc
bind10_dns_noboost_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
bind10_dns_noboost_la_LDFLAGS = $(PYTHON_LDFLAGS)
# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
bind10_dns_noboost_la_LDFLAGS += -module
bind10_dns_noboost_la_LIBADD = $(top_builddir)/src/lib/dns/libdns.la
bind10_dns_noboost_la_LIBADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
bind10_dns_noboost_la_LIBADD += $(PYTHON_LIB)
