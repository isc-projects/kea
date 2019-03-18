SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES  = *.gcno *.gcda

man_MANS = kea-ctrl-agent.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) kea-ctrl-agent.xml
EXTRA_DIST += agent.dox agent_hooks.dox

if GENERATE_DOCS
kea-ctrl-agent.8: kea-ctrl-agent.xml
	@XSLTPROC@ --novalid --xinclude @NONET@ -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/kea-ctrl-agent.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

# convenience archive

noinst_LTLIBRARIES = libagent.la

libagent_la_SOURCES  = agent_parser.cc agent_parser.h
libagent_la_SOURCES += agent_lexer.cc
libagent_la_SOURCES += ca_cfg_mgr.cc ca_cfg_mgr.h
libagent_la_SOURCES += ca_controller.cc ca_controller.h
libagent_la_SOURCES += ca_command_mgr.cc ca_command_mgr.h
libagent_la_SOURCES += ca_log.cc ca_log.h
libagent_la_SOURCES += ca_process.cc ca_process.h
libagent_la_SOURCES += ca_response_creator.cc ca_response_creator.h
libagent_la_SOURCES += ca_response_creator_factory.h
libagent_la_SOURCES += simple_parser.cc simple_parser.h
libagent_la_SOURCES += parser_context.cc parser_context.h parser_context_decl.h
libagent_la_SOURCES += agent_lexer.ll location.hh position.hh stack.hh
libagent_la_SOURCES += ca_messages.h ca_messages.cc
EXTRA_DIST += ca_messages.mes
EXTRA_DIST += agent_lexer.ll
EXTRA_DIST += agent_parser.yy

sbin_PROGRAMS = kea-ctrl-agent

kea_ctrl_agent_SOURCES = main.cc

kea_ctrl_agent_LDADD  = libagent.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_ctrl_agent_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
kea_ctrl_agent_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

kea_ctrl_agent_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f ca_messages.h ca_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: ca_messages.h ca_messages.cc
	@echo Message files regenerated

ca_messages.h ca_messages.cc: ca_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/bin/agent/ca_messages.mes

else

messages ca_messages.h ca_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

if GENERATE_PARSER

parser: agent_lexer.cc location.hh position.hh stack.hh agent_parser.cc agent_parser.h
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
location.hh position.hh stack.hh agent_parser.cc agent_parser.h: agent_parser.yy
	$(YACC) --defines=agent_parser.h --report=all --report-file=agent_parser.report -o agent_parser.cc agent_parser.yy

agent_lexer.cc: agent_lexer.ll
	$(LEX) --prefix agent_ -o agent_lexer.cc agent_lexer.ll

else

parser location.hh position.hh stack.hh agent_parser.cc agent_parser.h agent_lexer.cc:
	@echo Parser generation disabled. Configure with --enable-generate-parser to enable it.

endif
