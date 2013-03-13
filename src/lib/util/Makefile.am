SUBDIRS = . io unittests tests pyunittests python threads

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/exceptions -I$(top_builddir)/src/lib/exceptions
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DLOCKFILE_DIR=\"${localstatedir}/${PACKAGE_NAME}\"
AM_CXXFLAGS = $(B10_CXXFLAGS)
# If we use the shared-memory support, corresponding Boost library may
# cause build failures especially if it's strict about warnings.  We've
# detected it in ./configure and set BOOST_MAPPED_FILE_CXXFLAG to be more
# lenient as necessary (specifically, when set it'd usually supporess -Werror).
# This is a module wide setting, and has a possible bad side effect of hiding
# issues in other files, but making it per-file seems to be too costly.
# So we begin with the wider setting. If the side effect turns out to be too
# harmful, we'll consider other measure, e.g, moving the related files into
# a subdirectory.
if USE_SHARED_MEMORY
AM_CXXFLAGS += $(BOOST_MAPPED_FILE_CXXFLAG)
endif

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
if USE_SHARED_MEMORY
libb10_util_la_SOURCES += memory_segment_mapped.h memory_segment_mapped.cc
endif
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
libb10_util_la_LIBADD = $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
CLEANFILES = *.gcno *.gcda

libb10_util_includedir = $(includedir)/$(PACKAGE_NAME)/util
libb10_util_include_HEADERS = buffer.h
