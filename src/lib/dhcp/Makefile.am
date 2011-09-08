SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += -I$(top_builddir)/src/lib/asiolink
AM_CPPFLAGS += $(BOOST_INCLUDES)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libdhcp.la
libdhcp_la_SOURCES  =
libdhcp_la_SOURCES += libdhcp.cc libdhcp.h
libdhcp_la_SOURCES += option.cc option.h
libdhcp_la_SOURCES += option6_ia.cc option6_ia.h
libdhcp_la_SOURCES += option6_iaaddr.cc option6_iaaddr.h
libdhcp_la_SOURCES += option6_addrlst.cc option6_addrlst.h
libdhcp_la_SOURCES += dhcp6.h
libdhcp_la_SOURCES += pkt6.cc pkt6.h

EXTRA_DIST  = README
#EXTRA_DIST += log_messages.mes

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
libdhcp_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
libdhcp_la_CXXFLAGS += -Wall
endif
if USE_CLANGPP
# Same for clang++, but we need to turn off -Werror completely.
libdhcp_la_CXXFLAGS += -Wall
endif
libdhcp_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libdhcp_la_LDFLAGS  = $(LOG4CPLUS_LDFLAGS)
libdhcp_la_LIBADD   = $(top_builddir)/src/lib/util/libutil.la
