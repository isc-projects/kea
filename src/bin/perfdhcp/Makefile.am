SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
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

sbin_PROGRAMS = perfdhcp
perfdhcp_SOURCES = main.cc
perfdhcp_SOURCES += command_options.cc command_options.h
perfdhcp_SOURCES += localized_option.h
perfdhcp_SOURCES += perf_pkt6.cc perf_pkt6.h
perfdhcp_SOURCES += perf_pkt4.cc perf_pkt4.h
perfdhcp_SOURCES += packet_storage.h
perfdhcp_SOURCES += pkt_transform.cc pkt_transform.h
perfdhcp_SOURCES += rate_control.cc rate_control.h
perfdhcp_SOURCES += stats_mgr.h
perfdhcp_SOURCES += test_control.cc test_control.h
libkea_perfdhcp___la_CXXFLAGS = $(AM_CXXFLAGS)

perfdhcp_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
perfdhcp_CXXFLAGS += -Wno-unused-parameter
endif

perfdhcp_LDADD = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
perfdhcp_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
perfdhcp_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la


# ... and the documentation
EXTRA_DIST = perfdhcp_internals.dox

man_MANS = perfdhcp.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST += $(man_MANS) perfdhcp.xml

if GENERATE_DOCS

perfdhcp.8: perfdhcp.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(builddir)/perfdhcp.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif
