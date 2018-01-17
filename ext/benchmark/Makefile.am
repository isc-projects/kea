SUBDIRS = .

CLEANFILES = benchmark.cc

noinst_LIBRARIES = libbenchmark.a
libbenchmark_a_CXXFLAGS = $(BENCHMARK_INCLUDES) $(AM_CXXFLAGS)
nodist_libbenchmark_a_SOURCES = benchmark.cc

benchmark.cc: $(BENCHMARK_SOURCE)/src/benchmark.cc
	cp -p $(BENCHMARK_SOURCE)/src/benchmark.cc $@

