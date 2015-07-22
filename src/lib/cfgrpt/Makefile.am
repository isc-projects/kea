AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda config_report.cc

# config_report.cc is generated below
BUILT_SOURCES = config_report.cc

# convenience archive
noinst_LTLIBRARIES = libcfgrpt.la

nodist_libcfgrpt_la_SOURCES = config_report.cc
libcfgrpt_la_SOURCES = config_report.h cfgrpt.cc

# Generate config_report.cc
config_report.cc: $(abs_top_builddir)/config.report
	$(abs_top_builddir)/tools/mk_cfgrpt.sh $(abs_top_builddir)/src/lib/cfgrpt/config_report.cc
