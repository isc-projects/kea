SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/cc -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES = spec_config.h

man_MANS = b10-dhcp6.8
EXTRA_DIST = $(man_MANS) b10-dhcp6.xml dhcp6.spec

if ENABLE_MAN

b10-dhcp6.8: b10-dhcp6.xml
	xsltproc --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
        $(srcdir)/b10-dhcp6.xml
endif

spec_config.h: spec_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" spec_config.h.pre >$@

BUILT_SOURCES = spec_config.h
pkglibexec_PROGRAMS = b10-dhcp6

b10_dhcp6_SOURCES = main.cc dhcp6_srv.cc dhcp6_srv.h
b10_dhcp6_SOURCES += ctrl_dhcp6_srv.cc ctrl_dhcp6_srv.h

if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
b10_dhcp6_CXXFLAGS = -Wno-unused-parameter
endif

b10_dhcp6_LDADD = $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
b10_dhcp6_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la

b10_dhcp6dir = $(pkgdatadir)
b10_dhcp6_DATA = dhcp6.spec
