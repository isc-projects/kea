SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MYSQL_CPPFLAGS)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Define rule to build logging source files from message file
mysql_cb_messages.h mysql_cb_messages.cc: s-messages
s-messages: mysql_cb_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/mysql_cb/mysql_cb_messages.mes
	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = mysql_cb_messages.h mysql_cb_messages.cc

# Ensure that the message file is included in the distribution
EXTRA_DIST = mysql_cb_messages.mes
EXTRA_DIST += ha.dox

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda mysql_cb_messages.h mysql_cb_messages.cc s-messages

# convenience archive

noinst_LTLIBRARIES = libmysqlcb.la

libmysqlcb_la_SOURCES  = mysql_cb_callouts.cc
libmysqlcb_la_SOURCES += mysql_cb_dhcp4.cc mysql_cb_dhcp4.h
libmysqlcb_la_SOURCES += mysql_cb_impl.cc mysql_cb_impl.h
libmysqlcb_la_SOURCES += version.cc

nodist_libmysqlcb_la_SOURCES = mysql_cb_messages.cc mysql_cb_messages.h

libmysqlcb_la_CXXFLAGS = $(AM_CXXFLAGS)
libmysqlcb_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/hooks
lib_hooksdir = $(libdir)/hooks
lib_hooks_LTLIBRARIES = libdhcp_mysql_cb.la

libdhcp_mysql_cb_la_SOURCES  =
libdhcp_mysql_cb_la_LDFLAGS  = $(AM_LDFLAGS) $(MYSQL_LIBS)o
libdhcp_mysql_cb_la_LDFLAGS  += -avoid-version -export-dynamic -module

libdhcp_mysql_cb_la_LIBADD  = libmysqlcb.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_mysql_cb_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
