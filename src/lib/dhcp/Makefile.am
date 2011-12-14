SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libdhcp.la
libdhcp_la_SOURCES  =
libdhcp_la_SOURCES += libdhcp.cc libdhcp.h
libdhcp_la_SOURCES += iface_mgr.cc iface_mgr.h
libdhcp_la_SOURCES += option.cc option.h
libdhcp_la_SOURCES += option6_ia.cc option6_ia.h
libdhcp_la_SOURCES += option6_iaaddr.cc option6_iaaddr.h
libdhcp_la_SOURCES += option6_addrlst.cc option6_addrlst.h
libdhcp_la_SOURCES += option4_addrlst.cc option4_addrlst.h
libdhcp_la_SOURCES += dhcp6.h dhcp4.h
libdhcp_la_SOURCES += pkt6.cc pkt6.h
libdhcp_la_SOURCES += pkt4.cc pkt4.h

EXTRA_DIST  = README
#EXTRA_DIST += log_messages.mes

libdhcp_la_CXXFLAGS = $(AM_CXXFLAGS)
libdhcp_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libdhcp_la_LIBADD   = $(top_builddir)/src/lib/util/libutil.la
