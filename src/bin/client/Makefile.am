SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = 
man_MANS = kea-client.8

DISTCLEANFILES = $(man_MANS)

EXTRA_DIST = $(man_MANS) kea-client.xml
EXTRA_DIST += client.dox
EXTRA_DIST += clnt_lexer.ll clnt_parser.yy

if GENERATE_DOCS

kea-client.8: kea-client.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
	http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/kea-client.xml
else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

noinst_LTLIBRARIES = libclient.la

libclnt_la_SOURCES  =
libclnt_la_SOURCES += main.cc
libclnt_la_SOURCES += client_interface.h client_interface.cc

sbin_PROGRAMS = kea-client

kea_client_LDADD  = libclnt.la

kea_client_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_client_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
kea_client_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
kea_client_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_client_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
kea_client_LDADD += $(BOOST_LIBS)

kea_client_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

# too big
# kea_client_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la

# not needed:
#kea_client_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
#kea_client_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
#kea_client_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
#kea_client_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
#kea_client_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
#kea_client_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
#kea_client_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
#kea_client_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
#kea_client_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
#kea_client_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
#kea_client_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
#kea_client_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)


kea_clntdir = $(pkgdatadir)
kea_clnt_DATA = dhcp6.spec

if GENERATE_PARSER

parser: dhcp6_lexer.cc location.hh position.hh stack.hh dhcp6_parser.cc dhcp6_parser.h
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
location.hh position.hh stack.hh clnt_parser.cc clnt_parser.h: clnt_parser.yy
	$(YACC) --defines=clnt_parser.h --report=all --report-file=clnt_parser.report -o clnt_parser.cc clnt_parser.yy

clnt_lexer.cc: clnt_lexer.ll
	$(LEX) --prefix clnt_ -o clnt_lexer.cc clnt_lexer.ll

else

parser location.hh position.hh stack.hh clnt_parser.cc clnt_parser.h clnt_lexer.cc:
	@echo Parser generation disabled. Configure with --enable-generate-parser to enable it.

endif
