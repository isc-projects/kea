SUBDIRS = .

CLEANFILES = gtest-all.cc

noinst_LIBRARIES = libgtest.a
libgtest_a_CXXFLAGS = $(GTEST_INCLUDES) $(AM_CXXFLAGS)
nodist_libgtest_a_SOURCES = gtest-all.cc

gtest-all.cc: $(GTEST_SOURCE)/src/gtest-all.cc
	cp -p $(GTEST_SOURCE)/src/gtest-all.cc $@
