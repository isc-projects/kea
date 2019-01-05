AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
if HAVE_SYSREPO
AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

man_MANS = tools4.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) tools4.xml

if GENERATE_DOCS
tools4.8: tools4.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
	http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/tools4.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

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
import_to_yang4_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
import_to_yang4_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
import_to_yang4_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
import_to_yang4_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
import_to_yang4_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)
import_to_yang4_LDADD += $(SYSREPO_LIBS)
import_to_yang4_LDFLAGS = $(AM_LDFLAGS)

export_from_yang4_SOURCES = export_from_yang4.cc
export_from_yang4_LDADD  = $(top_builddir)/src/lib/yang/libkea-yang.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
export_from_yang4_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
export_from_yang4_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)
export_from_yang4_LDADD += $(SYSREPO_LIBS)
export_from_yang4_LDFLAGS = $(AM_LDFLAGS)
endif
