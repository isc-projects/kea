SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/exceptions -I$(top_builddir)/src/lib/exceptions
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

lib_LTLIBRARIES = libutil.la
libutil_la_SOURCES  = filename.h filename.cc
libutil_la_SOURCES += locks.h lru_list.h
libutil_la_SOURCES += strutil.h strutil.cc
libutil_la_SOURCES += buffer.h io_utilities.h
libutil_la_SOURCES += coder/base16_from_binary.h
libutil_la_SOURCES += coder/base32hex.h coder/base64.h
libutil_la_SOURCES += coder/base32hex_from_binary.h
libutil_la_SOURCES += coder/base_n.cc coder/hex.h
libutil_la_SOURCES += coder/binary_from_base32hex.h
libutil_la_SOURCES += coder/binary_from_base16.h
libutil_la_SOURCES += coder/sha1.h coder/sha1.cc
libutil_la_SOURCES += coder/time_utilities.h
libutil_la_SOURCES += coder/time_utilities.cc
libutil_la_SOURCES += random/qid_gen.h random/qid_gen.cc
libutil_la_SOURCES += random/random_number_generator.h

libutil_la_LIBADD = $(top_builddir)/src/lib/exceptions/libexceptions.la
CLEANFILES = *.gcno *.gcda
