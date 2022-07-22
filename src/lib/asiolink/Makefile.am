SUBDIRS = . testutils tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS) -Wno-non-virtual-dtor

EXTRA_DIST = asiolink.dox

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-asiolink.la

libkea_asiolink_la_LDFLAGS = -no-undefined -version-info 40:0:0
libkea_asiolink_la_LDFLAGS += $(CRYPTO_LDFLAGS)

libkea_asiolink_la_SOURCES  = asiolink.h
libkea_asiolink_la_SOURCES += asio_wrapper.h
libkea_asiolink_la_SOURCES += addr_utilities.cc addr_utilities.h
libkea_asiolink_la_SOURCES += botan_boost_tls.h botan_boost_wrapper.h
libkea_asiolink_la_SOURCES += botan_tls.h
libkea_asiolink_la_SOURCES += common_tls.cc common_tls.h
libkea_asiolink_la_SOURCES += crypto_tls.h
libkea_asiolink_la_SOURCES += dummy_io_cb.h
libkea_asiolink_la_SOURCES += interval_timer.cc interval_timer.h
libkea_asiolink_la_SOURCES += io_acceptor.h
libkea_asiolink_la_SOURCES += io_address.cc io_address.h
libkea_asiolink_la_SOURCES += io_asio_socket.h
libkea_asiolink_la_SOURCES += io_endpoint.cc io_endpoint.h
libkea_asiolink_la_SOURCES += io_error.h
libkea_asiolink_la_SOURCES += io_service.h io_service.cc
libkea_asiolink_la_SOURCES += io_service_signal.cc io_service_signal.h
libkea_asiolink_la_SOURCES += io_socket.h io_socket.cc
libkea_asiolink_la_SOURCES += openssl_tls.h
libkea_asiolink_la_SOURCES += process_spawn.h process_spawn.cc
libkea_asiolink_la_SOURCES += tcp_acceptor.h
libkea_asiolink_la_SOURCES += tcp_endpoint.h
libkea_asiolink_la_SOURCES += tcp_socket.h
libkea_asiolink_la_SOURCES += tls_acceptor.h
libkea_asiolink_la_SOURCES += tls_socket.h
libkea_asiolink_la_SOURCES += udp_endpoint.h
libkea_asiolink_la_SOURCES += udp_socket.h
libkea_asiolink_la_SOURCES += unix_domain_socket.cc unix_domain_socket.h
libkea_asiolink_la_SOURCES += unix_domain_socket_acceptor.h
libkea_asiolink_la_SOURCES += unix_domain_socket_endpoint.h

if HAVE_BOTAN
if HAVE_BOTAN_BOOST
libkea_asiolink_la_SOURCES += botan_boost_tls.cc
else
libkea_asiolink_la_SOURCES += botan_tls.cc
endif
endif
if HAVE_OPENSSL
libkea_asiolink_la_SOURCES += openssl_tls.cc
endif

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# KEA_CXXFLAGS)
libkea_asiolink_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_asiolink_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_asiolink_la_LIBADD = $(top_builddir)/src/lib/util/libkea-util.la
libkea_asiolink_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_asiolink_la_LIBADD += $(BOOST_LIBS) $(CRYPTO_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_asiolink_includedir = $(pkgincludedir)/asiolink
libkea_asiolink_include_HEADERS = \
	addr_utilities.h \
	asio_wrapper.h \
	asiolink.h \
	botan_boost_tls.h \
	botan_boost_wrapper.h \
	botan_tls.h \
	common_tls.h \
	crypto_tls.h \
	dummy_io_cb.h \
	interval_timer.h \
	io_acceptor.h \
	io_address.h \
	io_asio_socket.h \
	io_endpoint.h \
	io_error.h \
	io_service.h \
	io_service_signal.h \
	io_socket.h \
	openssl_tls.h \
	process_spawn.h \
	tcp_acceptor.h \
	tcp_endpoint.h \
	tcp_socket.h \
	tls_acceptor.h \
	tls_socket.h \
	udp_endpoint.h \
	udp_socket.h \
	unix_domain_socket.h \
	unix_domain_socket_acceptor.h \
	unix_domain_socket_endpoint.h
