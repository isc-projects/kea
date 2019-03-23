SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES  = *.gcno *.gcda

man_MANS = kea-slaac.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) kea-slaac.xml
EXTRA_DIST += slaac.dox

if GENERATE_DOCS
kea-slaac.8: kea-slaac.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/kea-slaac.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

# convenience archive

noinst_LTLIBRARIES = libslaac.la

libslaac_la_SOURCES  = 
libslaac_la_SOURCES += slaac_parser.cc slaac_parser.h
libslaac_la_SOURCES += slaac_lexer.cc
libslaac_la_SOURCES += slaac_controller.cc slaac_controller.h
libslaac_la_SOURCES += slaac_log.cc slaac_log.h
libslaac_la_SOURCES += slaac_process.cc slaac_process.h
libslaac_la_SOURCES += simple_parser.cc simple_parser.h
libslaac_la_SOURCES += parser_context.cc parser_context.h parser_context_decl.h
libslaac_la_SOURCES += slaac_lexer.ll slaac_parser.yy
libslaac_la_SOURCES += slaac_messages.h slaac_messages.cc

EXTRA_DIST += slaac_messages.mes
EXTRA_DIST += slaac_lexer.ll
EXTRA_DIST += slaac_parser.yy

sbin_PROGRAMS = kea-slaac

kea_slaac_SOURCES = main.cc

kea_slaac_LDADD  = libslaac.la
kea_slaac_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
kea_slaac_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
kea_slaac_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
#kea_slaac_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
kea_slaac_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
kea_slaac_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
kea_slaac_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
kea_slaac_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
kea_slaac_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_slaac_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

kea_slaac_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f netconf_messages.h netconf_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: slaac_messages.h slaac_messages.cc
	@echo Message files regenerated

slaac_messages.h slaac_messages.cc: slaac_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/bin/slaac/slaac_messages.mes

else

messages slaac_messages.h slaac_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

if GENERATE_PARSER

parser: slaac_lexer.cc location.hh position.hh stack.hh slaac_parser.cc slaac_parser.h
	@echo "Flex/bison files regenerated"

# --- Flex/Bison stuff below --------------------------------------------------
# When debugging grammar issues, it's useful to add -v to bison parameters.
# bison will generate parser.output file that explains the whole grammar.
# It can be used to manually follow what's going on in the parser.
# This is especially useful if yydebug_ is set to 1 as that variable
# will cause parser to print out its internal state.
# Call flex with -s to check that the default rule can be suppressed
# Call bison with -W to get warnings like unmarked empty rules
# Note C++11 deprecated register still used by flex < 2.6.0
location.hh position.hh stack.hh slaac_parser.cc slaac_parser.h: slaac_parser.yy
	$(YACC) --defines=slaac_parser.h --report=all --report-file=slaac_parser.report -o slaac_parser.cc slaac_parser.yy

slaac_lexer.cc: slaac_lexer.ll
	$(LEX) --prefix slaac_ -o slaac_lexer.cc slaac_lexer.ll

else

parser location.hh position.hh stack.hh slaac_parser.cc slaac_parser.h slaac_lexer.cc:
	@echo Parser generation disabled. Configure with --enable-generate-parser to enable it.

endif
