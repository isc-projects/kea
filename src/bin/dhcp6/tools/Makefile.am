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

man_MANS = tools6.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) tools6.xml

if GENERATE_DOCS
tools6.8: tools6.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
	http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/tools6.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

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
import_to_yang6_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
import_to_yang6_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
import_to_yang6_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
import_to_yang6_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
import_to_yang6_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)
import_to_yang6_LDADD += $(SYSREPO_LIBS)
import_to_yang6_LDFLAGS = $(AM_LDFLAGS)

export_from_yang6_SOURCES = export_from_yang6.cc
export_from_yang6_LDADD  = $(top_builddir)/src/lib/yang/libkea-yang.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
export_from_yang6_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
export_from_yang6_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)
export_from_yang6_LDADD += $(SYSREPO_LIBS)
export_from_yang6_LDFLAGS = $(AM_LDFLAGS)
endif
