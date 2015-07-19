SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

# This is a wrapper library.

# The ASIO header files have some code fragments that would hit
# gcc's unused-parameter warning, which would make the build fail
# with -Werror (our default setting).

lib_LTLIBRARIES = libkea-asiolink.la

libkea_asiolink_la_LDFLAGS = -no-undefined -version-info 2:0:0

libkea_asiolink_la_SOURCES  = asiolink.h
libkea_asiolink_la_SOURCES += dummy_io_cb.h
libkea_asiolink_la_SOURCES += interval_timer.cc interval_timer.h
libkea_asiolink_la_SOURCES += io_address.cc io_address.h
libkea_asiolink_la_SOURCES += io_asio_socket.h
libkea_asiolink_la_SOURCES += io_endpoint.cc io_endpoint.h
libkea_asiolink_la_SOURCES += io_error.h
libkea_asiolink_la_SOURCES += io_message.h
libkea_asiolink_la_SOURCES += io_service.h io_service.cc
libkea_asiolink_la_SOURCES += io_socket.h io_socket.cc
libkea_asiolink_la_SOURCES += simple_callback.h
libkea_asiolink_la_SOURCES += tcp_endpoint.h
libkea_asiolink_la_SOURCES += tcp_socket.h
libkea_asiolink_la_SOURCES += udp_endpoint.h
libkea_asiolink_la_SOURCES += udp_socket.h
libkea_asiolink_la_SOURCES += local_socket.h local_socket.cc

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# KEA_CXXFLAGS)
libkea_asiolink_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_asiolink_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_asiolink_la_LIBADD = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

# IOAddress is sometimes used in user-library code
libkea_asiolink_includedir = $(pkgincludedir)/asiolink
libkea_asiolink_include_HEADERS = io_address.h
