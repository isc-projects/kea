SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(BOTAN_INCLUDES)
AM_CXXFLAGS  = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)


# Define rule to build logging source files from message file
dhcp_ddns_messages.h dhcp_ddns_messages.cc: dhcp_ddns_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/dhcp_ddns/dhcp_ddns_messages.mes

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = dhcp_ddns_messages.h dhcp_ddns_messages.cc

# Ensure that the message file is included in the distribution
EXTRA_DIST = dhcp_ddns_messages.mes libdhcp_ddns.dox

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda dhcp_ddns_messages.h dhcp_ddns_messages.cc

lib_LTLIBRARIES = libb10-dhcp_ddns.la
libb10_dhcp_ddns_la_SOURCES  =
libb10_dhcp_ddns_la_SOURCES += dhcp_ddns_log.cc dhcp_ddns_log.h
libb10_dhcp_ddns_la_SOURCES += ncr_io.cc ncr_io.h
libb10_dhcp_ddns_la_SOURCES += ncr_msg.cc ncr_msg.h
libb10_dhcp_ddns_la_SOURCES += ncr_udp.cc ncr_udp.h

nodist_libb10_dhcp_ddns_la_SOURCES = dhcp_ddns_messages.cc dhcp_ddns_messages.h

libb10_dhcp_ddns_la_CXXFLAGS = $(AM_CXXFLAGS)
libb10_dhcp_ddns_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libb10_dhcp_ddns_la_LDFLAGS  = $(AM_LDFLAGS)
libb10_dhcp_ddns_la_LDFLAGS += ${BOTAN_LDFLAGS}
libb10_dhcp_ddns_la_LIBADD  =
libb10_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
libb10_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/log/libb10-log.la
libb10_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/util/libb10-util.la
libb10_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libb10_dhcp_ddns_la_LIBADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
libb10_dhcp_ddns_la_LIBADD += ${BOTAN_LIBS} ${BOTAN_RPATH}

if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libb10_dhcp_ddns_la_CXXFLAGS += -Wno-unused-parameter
endif

