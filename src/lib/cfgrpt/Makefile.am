SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda config_report.cc

# config_report.cc is generated below
BUILT_SOURCES = config_report.cc

# convenience archive
noinst_LTLIBRARIES = libcfgrpt.la

nodist_libcfgrpt_la_SOURCES = config_report.cc
libcfgrpt_la_SOURCES = config_report.h cfgrpt.cc

# set pathname to the input configuration report
report_file = $(abs_top_builddir)/config.report

# Generate config_report.cc
config_report.cc: $(report_file)
	${SHELL} $(top_srcdir)/tools/mk_cfgrpt.sh $(report_file) $(top_builddir)/src/lib/cfgrpt/config_report.cc
