# InterprocessSyncFile has a dependency on isc::util::thread::Mutex
SUBDIRS = io unittests threads . tests pyunittests python

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/exceptions -I$(top_builddir)/src/lib/exceptions
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DLOCKFILE_DIR=\"${localstatedir}/${PACKAGE_NAME}\"
AM_CXXFLAGS = $(B10_CXXFLAGS)

lib_LTLIBRARIES = libb10-util.la
libb10_util_la_SOURCES  = filename.h filename.cc
libb10_util_la_SOURCES += locks.h lru_list.h
libb10_util_la_SOURCES += strutil.h strutil.cc
libb10_util_la_SOURCES += buffer.h io_utilities.h
libb10_util_la_SOURCES += time_utilities.h time_utilities.cc
libb10_util_la_SOURCES += interprocess_sync.h
libb10_util_la_SOURCES += interprocess_sync_file.h interprocess_sync_file.cc
libb10_util_la_SOURCES += interprocess_sync_null.h interprocess_sync_null.cc
libb10_util_la_SOURCES += memory_segment.h
libb10_util_la_SOURCES += memory_segment_local.h memory_segment_local.cc
libb10_util_la_SOURCES += range_utilities.h
libb10_util_la_SOURCES += hash/sha1.h hash/sha1.cc
libb10_util_la_SOURCES += encode/base16_from_binary.h
libb10_util_la_SOURCES += encode/base32hex.h encode/base64.h
libb10_util_la_SOURCES += encode/base32hex_from_binary.h
libb10_util_la_SOURCES += encode/base_n.cc encode/hex.h
libb10_util_la_SOURCES += encode/binary_from_base32hex.h
libb10_util_la_SOURCES += encode/binary_from_base16.h
libb10_util_la_SOURCES += random/qid_gen.h random/qid_gen.cc
libb10_util_la_SOURCES += random/random_number_generator.h

EXTRA_DIST = python/pycppwrapper_util.h

libb10_util_la_LIBADD =  $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
libb10_util_la_LIBADD += $(top_builddir)/src/lib/util/threads/libb10-threads.la
CLEANFILES = *.gcno *.gcda

libb10_util_includedir = $(includedir)/$(PACKAGE_NAME)/util
libb10_util_include_HEADERS = buffer.h
