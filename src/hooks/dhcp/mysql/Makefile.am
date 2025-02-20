SUBDIRS = . tests libloadtests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MYSQL_CPPFLAGS) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST  = mysql_cb_messages.mes
EXTRA_DIST += mysql_hb_messages.mes
EXTRA_DIST += mysql_lb_messages.mes

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libmysql.la

libmysql_la_SOURCES  = mysql_callouts.cc
libmysql_la_SOURCES += mysql_cb_dhcp4.cc mysql_cb_dhcp4.h
libmysql_la_SOURCES += mysql_cb_dhcp6.cc mysql_cb_dhcp6.h
libmysql_la_SOURCES += mysql_cb_impl.cc mysql_cb_impl.h
libmysql_la_SOURCES += mysql_cb_messages.cc mysql_cb_messages.h
libmysql_la_SOURCES += mysql_cb_log.cc mysql_cb_log.h
libmysql_la_SOURCES += mysql_query_macros_dhcp.h
libmysql_la_SOURCES += mysql_hb_log.cc mysql_hb_log.h
libmysql_la_SOURCES += mysql_hb_messages.cc mysql_hb_messages.h
libmysql_la_SOURCES += mysql_host_data_source.cc mysql_host_data_source.h
libmysql_la_SOURCES += mysql_lb_log.cc mysql_lb_log.h
libmysql_la_SOURCES += mysql_lb_messages.cc mysql_lb_messages.h
libmysql_la_SOURCES += mysql_lease_mgr.cc mysql_lease_mgr.h
libmysql_la_SOURCES += version.cc

libmysql_la_CXXFLAGS = $(AM_CXXFLAGS)
libmysql_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_mysql.la

libdhcp_mysql_la_SOURCES  =
libdhcp_mysql_la_LDFLAGS  = $(AM_LDFLAGS) $(MYSQL_LIBS)
libdhcp_mysql_la_LDFLAGS  += -avoid-version -export-dynamic -module

libdhcp_mysql_la_LIBADD  = libmysql.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_mysql_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_mysql_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_mysql_la_LIBADD += $(CRYPTO_LIBS)
libdhcp_mysql_la_LIBADD += $(BOOST_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f mysql_cb_messages.h mysql_cb_messages.cc
	rm -f mysql_hb_messages.h mysql_hb_messages.cc
	rm -f mysql_lb_messages.h mysql_lb_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: mysql_cb_messages.h mysql_cb_messages.cc \
	  mysql_hb_messages.h mysql_hb_messages.cc \
	  mysql_lb_messages.h mysql_lb_messages.cc
	@echo Message files regenerated

mysql_cb_messages.h mysql_cb_messages.cc: mysql_cb_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/dhcp/mysql/mysql_cb_messages.mes)

mysql_hb_messages.h mysql_hb_messages.cc: mysql_hb_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/dhcp/mysql/mysql_hb_messages.mes)

mysql_lb_messages.h mysql_lb_messages.cc: mysql_lb_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/dhcp/mysql/mysql_lb_messages.mes)

else

messages: mysql_cb_messages.h mysql_cb_messages.cc \
	  mysql_hb_messages.h mysql_hb_messages.cc \
	  mysql_lb_messages.h mysql_lb_messages.cc
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

