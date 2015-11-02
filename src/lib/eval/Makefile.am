SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

lib_LTLIBRARIES = libkea-eval.la
libkea_eval_la_SOURCES  =
libkea_eval_la_SOURCES += eval_log.cc eval_log.h
libkea_eval_la_SOURCES += token.cc token.h

nodist_libkea_eval_la_SOURCES = eval_messages.h eval_messages.cc

libkea_eval_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_eval_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_eval_la_LIBADD   = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libkea_eval_la_LIBADD  += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)

libkea_eval_la_LDFLAGS  = -no-undefined -version-info 3:0:0
libkea_eval_la_LDFLAGS += $(CRYPTO_LDFLAGS)

EXTRA_DIST  = eval.dox
EXTRA_DIST += eval_messages.mes

# Define rule to build logging source files from message file
eval_messages.h eval_messages.cc: s-messages

s-messages: eval_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/eval/eval_messages.mes
	touch $@

# Tell Automake that the eval_messages.{cc,h} source files are created in the
# build process, so it must create these before doing anything else. Although
# they are a dependency of the library (so will be created from the
# message file anyway), there is no guarantee as to exactly _when_ in the build
# they will be created.  As the .h file is included in other sources file (so
# must be present when they are compiled), the safest option is to create it
# first.
BUILT_SOURCES = eval_messages.h eval_messages.cc

CLEANFILES = eval_messages.h eval_messages.cc s-messages
