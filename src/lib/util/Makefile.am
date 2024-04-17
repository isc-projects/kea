AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS = . io unittests tests python

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-util.la
libkea_util_la_SOURCES  =
libkea_util_la_SOURCES += bigints.h
libkea_util_la_SOURCES += boost_time_utils.h boost_time_utils.cc
libkea_util_la_SOURCES += buffer.h
libkea_util_la_SOURCES += chrono_time_utils.h chrono_time_utils.cc
libkea_util_la_SOURCES += csv_file.h csv_file.cc
libkea_util_la_SOURCES += dhcp_space.h dhcp_space.cc
libkea_util_la_SOURCES += doubles.h
libkea_util_la_SOURCES += filesystem.h filesystem.cc
libkea_util_la_SOURCES += hash.h
libkea_util_la_SOURCES += io.h
libkea_util_la_SOURCES += labeled_value.h labeled_value.cc
libkea_util_la_SOURCES += memory_segment.h
libkea_util_la_SOURCES += memory_segment_local.h memory_segment_local.cc
libkea_util_la_SOURCES += multi_threading_mgr.h multi_threading_mgr.cc
libkea_util_la_SOURCES += optional.h
libkea_util_la_SOURCES += pid_file.h pid_file.cc
libkea_util_la_SOURCES += pointer_util.h
libkea_util_la_SOURCES += range_utilities.h
libkea_util_la_SOURCES += readwrite_mutex.h
libkea_util_la_SOURCES += reconnect_ctl.h reconnect_ctl.cc
libkea_util_la_SOURCES += staged_value.h
libkea_util_la_SOURCES += state_model.cc state_model.h
libkea_util_la_SOURCES += stopwatch.cc stopwatch.h
libkea_util_la_SOURCES += stopwatch_impl.cc stopwatch_impl.h
libkea_util_la_SOURCES += str.h str.cc
libkea_util_la_SOURCES += thread_pool.h
libkea_util_la_SOURCES += triplet.h
libkea_util_la_SOURCES += unlock_guard.h
libkea_util_la_SOURCES += versioned_csv_file.h versioned_csv_file.cc
libkea_util_la_SOURCES += watch_socket.cc watch_socket.h
libkea_util_la_SOURCES += watched_thread.cc watched_thread.h
libkea_util_la_SOURCES += encode/encode.cc encode/encode.h
libkea_util_la_SOURCES += encode/utf8.cc encode/utf8.h

libkea_util_la_LIBADD = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

libkea_util_la_LDFLAGS  = -no-undefined -version-info 83:0:0

EXTRA_DIST = util.dox

CLEANFILES = *.gcno *.gcda

# Specify the headers for copying into the installation directory tree.
libkea_util_includedir = $(pkgincludedir)/util
libkea_util_include_HEADERS = \
	bigints.h \
	boost_time_utils.h \
	buffer.h \
	csv_file.h \
	chrono_time_utils.h \
	dhcp_space.h \
	doubles.h \
	filesystem.h \
	hash.h \
	io.h \
	labeled_value.h \
	memory_segment.h \
	memory_segment_local.h \
	multi_threading_mgr.h \
	optional.h \
	pid_file.h \
	pointer_util.h \
	range_utilities.h \
	readwrite_mutex.h \
	reconnect_ctl.h \
	staged_value.h \
	state_model.h \
	stopwatch.h \
	stopwatch_impl.h \
	str.h \
	thread_pool.h \
	triplet.h \
	unlock_guard.h \
	versioned_csv_file.h \
	watch_socket.h \
	watched_thread.h

libkea_util_encode_includedir = $(pkgincludedir)/util/encode
libkea_util_encode_include_HEADERS = \
	encode/encode.h \
	encode/utf8.h

libkea_util_io_includedir = $(pkgincludedir)/util/io
libkea_util_io_include_HEADERS = \
	io/fd.h \
	io/fd_share.h \
	io/pktinfo_utilities.h \
	io/sockaddr_util.h \
	io/socketsession.h
