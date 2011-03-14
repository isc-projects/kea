SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(SQLITE_CFLAGS)

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libresolve.la
libresolve_la_SOURCES = resolve.h resolve.cc
libresolve_la_SOURCES += resolver_interface.h
libresolve_la_SOURCES += resolver_callback.h resolver_callback.cc
libresolve_la_SOURCES += response_classifier.cc response_classifier.h
libresolve_la_SOURCES += recursive_query.cc recursive_query.h
libresolve_la_LIBADD = $(top_builddir)/src/lib/dns/libdns++.la
libresolve_la_LIBADD += $(top_builddir)/src/lib/exceptions/libexceptions.la

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
libresolve_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# For clang++, we need to turn off -Werror completely.
libresolve_la_CXXFLAGS += -Wno-error
endif
libresolve_la_CPPFLAGS = $(AM_CPPFLAGS)

