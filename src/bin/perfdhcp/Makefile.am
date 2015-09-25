SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

AM_LDFLAGS = -lm
if USE_STATIC_LINK
AM_LDFLAGS += -static
endif

# convenience archive

noinst_LTLIBRARIES = libperfdhcp.la

libperfdhcp_la_SOURCES  =
libperfdhcp_la_SOURCES += command_options.cc command_options.h
libperfdhcp_la_SOURCES += localized_option.h
libperfdhcp_la_SOURCES += perf_pkt6.cc perf_pkt6.h
libperfdhcp_la_SOURCES += perf_pkt4.cc perf_pkt4.h
libperfdhcp_la_SOURCES += packet_storage.h
libperfdhcp_la_SOURCES += pkt_transform.cc pkt_transform.h
libperfdhcp_la_SOURCES += rate_control.cc rate_control.h
libperfdhcp_la_SOURCES += stats_mgr.h
libperfdhcp_la_SOURCES += test_control.cc test_control.h

libperfdhcp_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libperfdhcp_la_CXXFLAGS += -Wno-unused-parameter
endif

sbin_PROGRAMS = perfdhcp
perfdhcp_SOURCES = main.cc
libkea_perfdhcp___la_CXXFLAGS = $(AM_CXXFLAGS)

perfdhcp_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

perfdhcp_LDADD = libperfdhcp.la
perfdhcp_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
perfdhcp_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
perfdhcp_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
perfdhcp_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
perfdhcp_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
perfdhcp_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
perfdhcp_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
perfdhcp_LDADD += $(CRYPTO_LIBS)
perfdhcp_LDADD += $(BOOST_LIBS)
perfdhcp_LDADD += $(PTHREAD_LDFLAGS)

# ... and the documentation
EXTRA_DIST = perfdhcp_internals.dox

man_MANS = perfdhcp.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST += $(man_MANS) perfdhcp.xml

if GENERATE_DOCS

perfdhcp.8: perfdhcp.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/perfdhcp.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif
