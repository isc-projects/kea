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
libkea_eval_la_SOURCES += dependency.cc dependency.h
libkea_eval_la_SOURCES += eval_log.cc eval_log.h
libkea_eval_la_SOURCES += evaluate.cc evaluate.h
libkea_eval_la_SOURCES += token.cc token.h

libkea_eval_la_SOURCES += parser.cc parser.h
libkea_eval_la_SOURCES += lexer.cc
libkea_eval_la_SOURCES += location.hh position.hh stack.hh
libkea_eval_la_SOURCES += eval_context.cc eval_context.h eval_context_decl.h
libkea_eval_la_SOURCES += eval_messages.h eval_messages.cc

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

libkea_eval_la_LDFLAGS  = -no-undefined -version-info 10:0:0
libkea_eval_la_LDFLAGS += $(CRYPTO_LDFLAGS)

EXTRA_DIST  = eval.dox
EXTRA_DIST += eval_messages.mes
EXTRA_DIST += lexer.ll parser.yy

CLEANFILES = *.gcno *.gcda

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean:
	rm -f eval_messages.h eval_messages.cc

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: eval_messages.h eval_messages.cc
	@echo Message files regenerated

eval_messages.h eval_messages.cc: eval_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/eval/eval_messages.mes

else

messages eval_messages.h eval_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
#
# If we want to get rid of all flex/bison generated files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required. To make it easy to rebuild flex/bison without going through
# reconfigure, a new target parser-clean has been added.
maintainer-clean-local:
	rm -f eval_messages.h eval_messages.cc
	rm -f location.hh lexer.cc parser.cc parser.h position.hh stack.hh

# To regenerate flex/bison files, one can do:
#
# make parser-clean
# make parser
#
# This is needed only when the lexer.ll or parser.yy files are modified.
# Make sure you have both flex and bison installed.
parser-clean:
	rm -f location.hh lexer.cc parser.cc parser.h position.hh stack.hh

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

lexer.cc: lexer.ll
	$(LEX) --prefix eval -o lexer.cc lexer.ll

else

parser location.hh position.hh stack.hh parser.cc parser.h lexer.cc:
	@echo Parser generation disabled. Configure with --enable-generate-parser to enable it.

endif


# Specify the headers for copying into the installation directory tree.
libkea_eval_includedir = $(pkgincludedir)/eval
libkea_eval_include_HEADERS = \
	dependency.h \
	eval_context.h \
	eval_context_decl.h \
	eval_log.h \
	eval_messages.h \
	evaluate.h \
	parser.h \
	token.h
# does not include *.hh generated headers as they come with lexer and parser.
