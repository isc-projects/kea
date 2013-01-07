SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libb10-dhcp++.la
libb10_dhcp___la_SOURCES  =
libb10_dhcp___la_SOURCES += duid.cc duid.h
libb10_dhcp___la_SOURCES += iface_mgr.cc iface_mgr.h
libb10_dhcp___la_SOURCES += iface_mgr_bsd.cc
libb10_dhcp___la_SOURCES += iface_mgr_linux.cc
libb10_dhcp___la_SOURCES += iface_mgr_sun.cc
libb10_dhcp___la_SOURCES += libdhcp++.cc libdhcp++.h
libb10_dhcp___la_SOURCES += option.cc option.h
libb10_dhcp___la_SOURCES += option_data_types.cc option_data_types.h
libb10_dhcp___la_SOURCES += option_definition.cc option_definition.h
libb10_dhcp___la_SOURCES += option_custom.cc option_custom.h
libb10_dhcp___la_SOURCES += option6_ia.cc option6_ia.h
libb10_dhcp___la_SOURCES += option6_iaaddr.cc option6_iaaddr.h
libb10_dhcp___la_SOURCES += option6_addrlst.cc option6_addrlst.h
libb10_dhcp___la_SOURCES += option4_addrlst.cc option4_addrlst.h
libb10_dhcp___la_SOURCES += option_int.h
libb10_dhcp___la_SOURCES += option_int_array.h
libb10_dhcp___la_SOURCES += dhcp6.h dhcp4.h
libb10_dhcp___la_SOURCES += pkt6.cc pkt6.h
libb10_dhcp___la_SOURCES += pkt4.cc pkt4.h
libb10_dhcp___la_SOURCES += std_option_defs.h

libb10_dhcp___la_CXXFLAGS = $(AM_CXXFLAGS)
libb10_dhcp___la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libb10_dhcp___la_LIBADD   = $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
libb10_dhcp___la_LIBADD  += $(top_builddir)/src/lib/dns/libb10-dns++.la
libb10_dhcp___la_LIBADD  += $(top_builddir)/src/lib/util/libb10-util.la
libb10_dhcp___la_LDFLAGS  = -no-undefined -version-info 2:0:0

EXTRA_DIST  = README libdhcp++.dox

if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libb10_dhcp___la_CXXFLAGS += -Wno-unused-parameter
endif
