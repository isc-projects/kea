SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

# GCC 4.4 emits warning about breaking strict aliasing rule.
# This warning is a result of a GCC bug:
# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=41874
# The warning is raised in the generated code in parser.h.
# Disabling the strict aliasing rule suppresses this warning.
AM_CXXFLAGS += $(WARNING_GCC_44_STRICT_ALIASING_CFLAG)

lib_LTLIBRARIES = libkea-eval.la
libkea_eval_la_SOURCES  =
libkea_eval_la_SOURCES += eval_log.cc eval_log.h
libkea_eval_la_SOURCES += evaluate.cc evaluate.h
libkea_eval_la_SOURCES += token.cc token.h

libkea_eval_la_SOURCES += parser.cc parser.h
libkea_eval_la_SOURCES += lexer.cc
libkea_eval_la_SOURCES += location.hh position.hh stack.hh
libkea_eval_la_SOURCES += eval_context.cc eval_context.h eval_context_decl.h

nodist_libkea_eval_la_SOURCES = eval_messages.h eval_messages.cc

libkea_eval_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_eval_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_eval_la_LIBADD   = $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/dns/libkea-dns++.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/util/libkea-util.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_eval_la_LIBADD  += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

libkea_eval_la_LDFLAGS  = -no-undefined -version-info 7:1:0
libkea_eval_la_LDFLAGS += $(CRYPTO_LDFLAGS)

EXTRA_DIST  = eval.dox
EXTRA_DIST += eval_messages.mes
EXTRA_DIST += lexer.ll parser.yy

# Define rule to build logging source files from message file
eval_messages.h eval_messages.cc: s-messages

s-messages: eval_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/eval/eval_messages.mes
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

# If we want to get rid of all flex/bison generated files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required. To make it easy to rebuild flex/bison without going through
# reconfigure, a new target parser-clean has been added.
maintainer-clean-local:
	rm -f location.hh lexer.cc parser.cc parser.h position.hh stack.hh

# To regenerate flex/bison files, one can do:
#
# make parser-clean
# make parser
#
# This is needed only when the lexer.ll or parser.yy files are modified.
# Make sure you have both flex and bison installed.
parser-clean: maintainer-clean-local

if GENERATE_PARSER

parser: lexer.cc location.hh position.hh stack.hh parser.cc parser.h
	@echo "Flex/bison files regenerated"

# --- Flex/Bison stuff below --------------------------------------------------
# When debugging grammar issues, it's useful to add -v to bison parameters.
# bison will generate parser.output file that explains the whole grammar.
# It can be used to manually follow what's going on in the parser.
# This is especially useful if yydebug_ is set to 1 as that variable
# will cause parser to print out its internal state.
location.hh position.hh stack.hh parser.cc parser.h: parser.yy
	$(YACC) --defines=parser.h -o parser.cc parser.yy

.NOTPARALLEL: location.hh position.hh stack.hh parser.cc parser.h

lexer.cc: lexer.ll
	$(LEX) --prefix eval -o lexer.cc lexer.ll

else

parser location.hh position.hh stack.hh parser.cc parser.h lexer.cc:
	@echo Parser generation disabled. Configure with --enable-generate-parser to enable it.

endif


# Specify the headers for copying into the installation directory tree.
libkea_eval_includedir = $(pkgincludedir)/eval
libkea_eval_include_HEADERS = \
	eval_context.h \
	eval_context_decl.h \
	eval_log.h \
	evaluate.h \
	parser.h \
	token.h
# does not include *.hh generated headers as they come with lexer and parser.
