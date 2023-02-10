SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES  = *.gcno *.gcda

EXTRA_DIST = d2.dox d2_hooks.dox
EXTRA_DIST += d2_parser.yy

EXTRA_DIST += images/abstract_app_classes.svg images/add_state_model.svg
EXTRA_DIST += images/config_data_classes.svg images/config_from_file_sequence.svg
EXTRA_DIST += images/config_parser_classes.svg images/cpl_signal_classes.svg
EXTRA_DIST += images/cpl_signal_sequence.svg images/d2_app_classes.svg
EXTRA_DIST += images/nc_trans_sequence.svg images/remove_state_model.svg
EXTRA_DIST += images/request_mgt_classes.svg images/state_model_classes.svg
EXTRA_DIST += images/trans_classes.svg images/update_exec_classes.svg


# convenience archive

noinst_LTLIBRARIES = libd2.la

libd2_la_SOURCES  =
libd2_la_SOURCES += d2_process.cc d2_process.h
libd2_la_SOURCES += d2_lexer.ll location.hh
libd2_la_SOURCES += d2_parser.cc d2_parser.h
libd2_la_SOURCES += d2_queue_mgr.cc d2_queue_mgr.h
libd2_la_SOURCES += d2_update_mgr.cc d2_update_mgr.h
libd2_la_SOURCES += nc_add.cc nc_add.h
libd2_la_SOURCES += nc_remove.cc nc_remove.h
libd2_la_SOURCES += d2_controller.cc d2_controller.h
libd2_la_SOURCES += parser_context.cc parser_context.h parser_context_decl.h
libd2_la_SOURCES += simple_add.cc simple_add.h
libd2_la_SOURCES += simple_remove.cc simple_remove.h

sbin_PROGRAMS = kea-dhcp-ddns

kea_dhcp_ddns_SOURCES  = main.cc

kea_dhcp_ddns_LDADD  = libd2.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/d2srv/libkea-d2srv.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
kea_dhcp_ddns_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
kea_dhcp_ddns_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

kea_dhcp_ddns_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

kea_dhcp_ddnsdir = $(pkgdatadir)

if GENERATE_PARSER

# Generate parser first.
all-recursive: d2_lexer.cc location.hh d2_parser.cc d2_parser.h

parser: d2_lexer.cc location.hh d2_parser.cc d2_parser.h
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
location.hh d2_parser.cc d2_parser.h: d2_parser.yy
	$(YACC) -Wno-yacc --defines=d2_parser.h --report=all \
	--report-file=d2_parser.report -o d2_parser.cc d2_parser.yy

d2_lexer.cc: d2_lexer.ll
	$(LEX) --prefix d2_parser_ -o d2_lexer.cc d2_lexer.ll

else

parser location.hh d2_parser.cc d2_parser.h d2_lexer.cc:
	@echo Parser generation disabled. Configure with --enable-generate-parser to enable it.

endif
