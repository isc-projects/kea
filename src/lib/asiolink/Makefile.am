SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

# This is a wrapper library.

# The ASIO header files have some code fragments that would hit
# gcc's unused-parameter warning, which would make the build fail
# with -Werror (our default setting).

lib_LTLIBRARIES = libasiolink.la

libasiolink_la_LDFLAGS = -no-undefined -version-info 1:0:1

libasiolink_la_SOURCES  = asiolink.h
libasiolink_la_SOURCES += dummy_io_cb.h
libasiolink_la_SOURCES += interval_timer.cc interval_timer.h
libasiolink_la_SOURCES += io_address.cc io_address.h
libasiolink_la_SOURCES += io_asio_socket.h
libasiolink_la_SOURCES += io_endpoint.cc io_endpoint.h
libasiolink_la_SOURCES += io_error.h
libasiolink_la_SOURCES += io_message.h
libasiolink_la_SOURCES += io_service.h io_service.cc
libasiolink_la_SOURCES += io_socket.h io_socket.cc
libasiolink_la_SOURCES += simple_callback.h
libasiolink_la_SOURCES += tcp_endpoint.h
libasiolink_la_SOURCES += tcp_socket.h
libasiolink_la_SOURCES += udp_endpoint.h
libasiolink_la_SOURCES += udp_socket.h

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
libasiolink_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# Same for clang++, but we need to turn off -Werror completely.
libasiolink_la_CXXFLAGS += -Wno-error
endif
libasiolink_la_CPPFLAGS = $(AM_CPPFLAGS)
libasiolink_la_LIBADD = $(top_builddir)/src/lib/log/liblog.la
