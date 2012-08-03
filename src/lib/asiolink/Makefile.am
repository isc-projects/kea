SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

# This is a wrapper library.

# The ASIO header files have some code fragments that would hit
# gcc's unused-parameter warning, which would make the build fail
# with -Werror (our default setting).

lib_LTLIBRARIES = libb10-asiolink.la

libb10_asiolink_la_LDFLAGS = -no-undefined -version-info 1:0:1

libb10_asiolink_la_SOURCES  = asiolink.h
libb10_asiolink_la_SOURCES += dummy_io_cb.h
libb10_asiolink_la_SOURCES += interval_timer.cc interval_timer.h
libb10_asiolink_la_SOURCES += io_address.cc io_address.h
libb10_asiolink_la_SOURCES += io_asio_socket.h
libb10_asiolink_la_SOURCES += io_endpoint.cc io_endpoint.h
libb10_asiolink_la_SOURCES += io_error.h
libb10_asiolink_la_SOURCES += io_message.h
libb10_asiolink_la_SOURCES += io_service.h io_service.cc
libb10_asiolink_la_SOURCES += io_socket.h io_socket.cc
libb10_asiolink_la_SOURCES += simple_callback.h
libb10_asiolink_la_SOURCES += tcp_endpoint.h
libb10_asiolink_la_SOURCES += tcp_socket.h
libb10_asiolink_la_SOURCES += udp_endpoint.h
libb10_asiolink_la_SOURCES += udp_socket.h

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
libb10_asiolink_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# Same for clang++, but we need to turn off -Werror completely.
libb10_asiolink_la_CXXFLAGS += -Wno-error
endif
libb10_asiolink_la_CPPFLAGS = $(AM_CPPFLAGS)
libb10_asiolink_la_LIBADD = $(top_builddir)/src/lib/log/libb10-log.la
