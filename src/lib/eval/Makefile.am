SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-eval.la
libkea_eval_la_SOURCES  =
libkea_eval_la_SOURCES += token.cc token.h

libkea_eval_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_eval_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_eval_la_LIBADD   = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_eval_la_LIBADD  += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libkea_eval_la_LDFLAGS  = -no-undefined -version-info 3:0:0
libkea_eval_la_LDFLAGS += $(CRYPTO_LDFLAGS)

EXTRA_DIST  = eval.dox

# Define rule to build logging source files from message file
expr_messages.h expr_messages.cc: s-messages

s-messages: expr_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/expr/expr_messages.mes

CLEANFILES = expr_messages.h expr_messages.cc
