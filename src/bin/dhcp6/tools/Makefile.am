AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
if HAVE_SYSREPO
AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)
endif

CLEANFILES = *.gcno *.gcda

sbin_PROGRAMS = parser6
if HAVE_SYSREPO
sbin_PROGRAMS += import-to-yang6 export-from-yang6
endif

parser6_SOURCES = parser6.cc
parser6_LDADD  = $(top_builddir)/src/bin/dhcp6/libparser6.la
parser6_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
parser6_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
parser6_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
parser6_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
parser6_LDADD += $(BOOST_LIBS)
parser6_LDFLAGS = $(AM_LDFLAGS)

if HAVE_SYSREPO
import_to_yang6_SOURCES = import_to_yang6.cc
import_to_yang6_LDADD  = $(top_builddir)/src/bin/dhcp6/libparser6.la
import_to_yang6_LDADD += $(top_builddir)/src/lib/yang/libkea-yang.la
import_to_yang6_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
import_to_yang6_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
import_to_yang6_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
import_to_yang6_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
import_to_yang6_LDADD += $(BOOST_LIBS)
import_to_yang6_LDADD += $(SYSREPO_LIBS)
import_to_yang6_LDFLAGS = $(AM_LDFLAGS)

export_from_yang6_SOURCES = export_from_yang6.cc
export_from_yang6_LDADD  = $(top_builddir)/src/bin/dhcp6/libparser6.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/yang/libkea-yang.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
export_from_yang6_LDADD += $(BOOST_LIBS)
export_from_yang6_LDADD += $(SYSREPO_LIBS)
export_from_yang6_LDFLAGS = $(AM_LDFLAGS)
endif
