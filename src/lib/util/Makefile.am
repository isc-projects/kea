AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS = . io unittests tests python threads

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/exceptions -I$(top_builddir)/src/lib/exceptions
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-util.la
libkea_util_la_SOURCES  = boost_time_utils.h boost_time_utils.cc
libkea_util_la_SOURCES += csv_file.h csv_file.cc
libkea_util_la_SOURCES += filename.h filename.cc
libkea_util_la_SOURCES += locks.h lru_list.h
libkea_util_la_SOURCES += strutil.h strutil.cc
libkea_util_la_SOURCES += buffer.h io_utilities.h
libkea_util_la_SOURCES += time_utilities.h time_utilities.cc
libkea_util_la_SOURCES += memory_segment.h
libkea_util_la_SOURCES += memory_segment_local.h memory_segment_local.cc
libkea_util_la_SOURCES += optional_value.h
libkea_util_la_SOURCES += pid_file.h pid_file.cc
libkea_util_la_SOURCES += pointer_util.h
libkea_util_la_SOURCES += process_spawn.h process_spawn.cc
libkea_util_la_SOURCES += range_utilities.h
libkea_util_la_SOURCES += signal_set.cc signal_set.h
libkea_util_la_SOURCES += stopwatch.cc stopwatch.h
libkea_util_la_SOURCES += stopwatch_impl.cc stopwatch_impl.h
libkea_util_la_SOURCES += watch_socket.cc watch_socket.h
libkea_util_la_SOURCES += encode/base16_from_binary.h
libkea_util_la_SOURCES += encode/base32hex.h encode/base64.h
libkea_util_la_SOURCES += encode/base32hex_from_binary.h
libkea_util_la_SOURCES += encode/base_n.cc encode/hex.h
libkea_util_la_SOURCES += encode/binary_from_base32hex.h
libkea_util_la_SOURCES += encode/binary_from_base16.h
libkea_util_la_SOURCES += random/qid_gen.h random/qid_gen.cc
libkea_util_la_SOURCES += random/random_number_generator.h

libkea_util_la_LIBADD = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

libkea_util_la_LDFLAGS  = -no-undefined -version-info 1:0:0

CLEANFILES = *.gcno *.gcda

libkea_util_includedir = $(includedir)/$(PACKAGE_NAME)/util
libkea_util_include_HEADERS = buffer.h io_utilities.h
