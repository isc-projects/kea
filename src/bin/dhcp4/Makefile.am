SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += $(BOOST_INCLUDES)
if HAVE_MYSQL
AM_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif
if HAVE_PGSQL
AM_CPPFLAGS += $(PGSQL_CPPFLAGS)
endif
if HAVE_CQL
AM_CPPFLAGS += $(CQL_CPPFLAGS)
endif

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES  = *.gcno *.gcda

man_MANS = kea-dhcp4.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) kea-dhcp4.xml
EXTRA_DIST += dhcp4.dox dhcp4_hooks.dox dhcp4o6.dox
EXTRA_DIST += dhcp4_parser.yy

if GENERATE_DOCS
kea-dhcp4.8: kea-dhcp4.xml
	@XSLTPROC@ --novalid --xinclude @NONET@ -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/kea-dhcp4.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

# convenience archive

noinst_LTLIBRARIES = libdhcp4.la

libdhcp4_la_SOURCES  =
libdhcp4_la_SOURCES += ctrl_dhcp4_srv.cc ctrl_dhcp4_srv.h
libdhcp4_la_SOURCES += json_config_parser.cc json_config_parser.h
libdhcp4_la_SOURCES += dhcp4_log.cc dhcp4_log.h
libdhcp4_la_SOURCES += dhcp4_srv.cc dhcp4_srv.h
libdhcp4_la_SOURCES += dhcp4to6_ipc.cc dhcp4to6_ipc.h
libdhcp4_la_SOURCES += dhcp4_lexer.ll location.hh position.hh stack.hh
libdhcp4_la_SOURCES += dhcp4_parser.cc dhcp4_parser.h
libdhcp4_la_SOURCES += parser_context.cc parser_context.h parser_context_decl.h
libdhcp4_la_SOURCES += dhcp4_messages.h dhcp4_messages.cc
EXTRA_DIST += dhcp4_messages.mes

sbin_PROGRAMS = kea-dhcp4

kea_dhcp4_SOURCES  = main.cc

kea_dhcp4_LDADD  = libdhcp4.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la

if HAVE_MYSQL
kea_dhcp4_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
endif
if HAVE_PGSQL
kea_dhcp4_LDADD += $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
endif
if HAVE_CQL
kea_dhcp4_LDADD += $(top_builddir)/src/lib/cql/libkea-cql.la
endif

kea_dhcp4_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
kea_dhcp4_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_dhcp4_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

kea_dhcp4_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
if HAVE_MYSQL
kea_dhcp4_LDFLAGS += $(MYSQL_LIBS)
endif
if HAVE_PGSQL
kea_dhcp4_LDFLAGS += $(PGSQL_LIBS)
endif
if HAVE_CQL
kea_dhcp4_LDFLAGS += $(CQL_LIBS)
endif

kea_dhcp4dir = $(pkgdatadir)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f dhcp4_messages.h dhcp4_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: dhcp4_messages.h dhcp4_messages.cc
	@echo Message files regenerated

dhcp4_messages.h dhcp4_messages.cc: dhcp4_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/bin/dhcp4/dhcp4_messages.mes

else

messages dhcp4_messages.h dhcp4_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

if GENERATE_PARSER

parser: dhcp4_lexer.cc location.hh position.hh stack.hh dhcp4_parser.cc dhcp4_parser.h
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
location.hh position.hh stack.hh dhcp4_parser.cc dhcp4_parser.h: dhcp4_parser.yy
	$(YACC) --defines=dhcp4_parser.h --report=all --report-file=dhcp4_parser.report -o dhcp4_parser.cc dhcp4_parser.yy

dhcp4_lexer.cc: dhcp4_lexer.ll
	$(LEX) --prefix parser4_ -o dhcp4_lexer.cc dhcp4_lexer.ll

else

parser location.hh position.hh stack.hh dhcp4_parser.cc dhcp4_parser.h dhcp4_lexer.cc:
	@echo Parser generation disabled. Configure with --enable-generate-parser to enable it.

endif
