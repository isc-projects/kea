SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

man_MANS = b10-dhcp4.8
EXTRA_DIST = $(man_MANS) dhcp4.spec

if ENABLE_MAN

b10-dhcp4.8: b10-dhcp4.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-dhcp4.xml

endif

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

BUILT_SOURCES = spec_config.h
pkglibexec_PROGRAMS = b10-dhcp4

b10_dhcp4_SOURCES = main.cc dhcp4_srv.cc dhcp4_srv.h

b10_dhcp4_LDADD = $(top_builddir)/src/lib/dhcp/libdhcp.la
b10_dhcp4_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
b10_dhcp4_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
b10_dhcp4_LDADD += $(top_builddir)/src/lib/log/liblog.la

# TODO: config.h.in is wrong because doesn't honor pkgdatadir
# and can't use @datadir@ because doesn't expand default ${prefix}
b10_dhcp4dir = $(pkgdatadir)
b10_dhcp4_DATA = dhcp4.spec

