AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
if HAVE_SYSREPO
AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)
endif

CLEANFILES = *.gcno *.gcda

sbin_PROGRAMS = parser4
if HAVE_SYSREPO
sbin_PROGRAMS += import-to-yang4 export-from-yang4
endif

parser4_SOURCES = parser4.cc
parser4_LDADD  = $(top_builddir)/src/bin/dhcp4/libparser4.la
parser4_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
parser4_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
parser4_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
parser4_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
parser4_LDADD += $(BOOST_LIBS)
parser4_LDFLAGS = $(AM_LDFLAGS)

if HAVE_SYSREPO
import_to_yang4_SOURCES = import_to_yang4.cc
import_to_yang4_LDADD  = $(top_builddir)/src/bin/dhcp4/libparser4.la
import_to_yang4_LDADD += $(top_builddir)/src/lib/yang/libkea-yang.la
import_to_yang4_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
import_to_yang4_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
import_to_yang4_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
import_to_yang4_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
import_to_yang4_LDADD += $(BOOST_LIBS)
import_to_yang4_LDADD += $(SYSREPO_LIBS)
import_to_yang4_LDFLAGS = $(AM_LDFLAGS)

export_from_yang4_SOURCES = export_from_yang4.cc
export_from_yang4_LDADD  = $(top_builddir)/src/bin/dhcp4/libparser4.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/yang/libkea-yang.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
export_from_yang4_LDADD += $(BOOST_LIBS)
export_from_yang4_LDADD += $(SYSREPO_LIBS)
export_from_yang4_LDFLAGS = $(AM_LDFLAGS)
endif
