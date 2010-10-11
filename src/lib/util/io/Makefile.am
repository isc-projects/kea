AM_CXXFLAGS = $(B10_CXXFLAGS)

lib_LTLIBRARIES = libutil_io.la
libutil_io_la_SOURCES = fd.h fd.cc fd_share.h fd_share.cc
libutil_io_la_CXXFLAGS = $(AM_CXXFLAGS) -fno-strict-aliasing

CLEANFILES = *.gcno *.gcda

pyexec_LTLIBRARIES = libutil_io_python.la
# Python prefers .so, while some OSes (specifically MacOS) use a different
# suffix for dynamic objects.  -module is necessary to work this around.
libutil_io_python_la_LDFLAGS = -module
libutil_io_python_la_SOURCES = fdshare_python.cc
libutil_io_python_la_LIBADD = libutil_io.la
libutil_io_python_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_INCLUDES)
libutil_io_python_la_CXXFLAGS = $(AM_CXXFLAGS)
