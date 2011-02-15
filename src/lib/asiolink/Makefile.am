SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

# This is a wrapper library solely used for b10-auth.  The ASIO header files
# have some code fragments that would hit gcc's unused-parameter warning,
# which would make the build fail with -Werror (our default setting).
lib_LTLIBRARIES = libasiolink.la
libasiolink_la_SOURCES = asiolink.h
libasiolink_la_SOURCES += io_service.cc io_service.h
libasiolink_la_SOURCES += dns_service.cc dns_service.h
libasiolink_la_SOURCES += dns_server.h
libasiolink_la_SOURCES += dns_lookup.h
libasiolink_la_SOURCES += dns_answer.h
libasiolink_la_SOURCES += simple_callback.h
libasiolink_la_SOURCES += interval_timer.h interval_timer.cc
libasiolink_la_SOURCES += recursive_query.h recursive_query.cc
libasiolink_la_SOURCES += io_error.h
libasiolink_la_SOURCES += io_socket.cc io_socket.h
libasiolink_la_SOURCES += io_message.h
libasiolink_la_SOURCES += io_address.cc io_address.h
libasiolink_la_SOURCES += io_endpoint.cc io_endpoint.h
libasiolink_la_SOURCES += udp_endpoint.h
libasiolink_la_SOURCES += udp_server.h udp_server.cc
libasiolink_la_SOURCES += udp_socket.h udp_socket.cc
libasiolink_la_SOURCES += udp_query.h udp_query.cc
libasiolink_la_SOURCES += tcp_endpoint.h tcp_socket.h
libasiolink_la_SOURCES += tcp_server.h tcp_server.cc
# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
libasiolink_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
libasiolink_la_CXXFLAGS += -Wno-unused-parameter
endif
if USE_CLANGPP
# Same for clang++, but we need to turn off -Werror completely.
libasiolink_la_CXXFLAGS += -Wno-error
endif
libasiolink_la_CPPFLAGS = $(AM_CPPFLAGS)
libasiolink_la_LIBADD = $(top_builddir)/src/lib/log/liblog.la
libasiolink_la_LIBADD += $(top_builddir)/src/lib/resolve/libresolve.la
