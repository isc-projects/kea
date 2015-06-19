SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some Boost headers when compiling with clang
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES  = lfc_messages.h lfc_messages.cc s-messages

man_MANS = kea-lfc.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) kea-lfc.xml lfc.dox

if GENERATE_DOCS
kea-lfc.8: kea-lfc.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/kea-lfc.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

lfc_messages.h lfc_messages.cc: s-messages

s-messages: lfc_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/bin/lfc/lfc_messages.mes
	touch $@

BUILT_SOURCES = lfc_messages.h lfc_messages.cc

# convenience archive

noinst_LTLIBRARIES = liblfc.la

liblfc_la_SOURCES  =
liblfc_la_SOURCES += lfc_controller.h lfc_controller.cc
liblfc_la_SOURCES += lfc_log.h lfc_log.cc

nodist_liblfc_la_SOURCES = lfc_messages.h lfc_messages.cc
EXTRA_DIST += lfc_messages.mes

sbin_PROGRAMS = kea-lfc

kea_lfc_SOURCES  = main.cc

kea_lfc_LDADD  = liblfc.la
kea_lfc_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
kea_lfc_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_lfc_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_lfc_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
kea_lfc_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
kea_lfc_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
kea_lfc_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
kea_lfc_LDADD += $(top_builddir)/src/bin/cfgrpt/libcfgrpt.la

kea_lfcdir = $(pkgdatadir)
