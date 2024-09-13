SUBDIRS = . tests libloadtests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(MYSQL_CPPFLAGS)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST = mysql_lb_messages.mes

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libmysqllb.la
libmysqllb_la_SOURCES = mysql_lease_mgr.cc mysql_lease_mgr.h

libmysqllb_la_CXXFLAGS = $(AM_CXXFLAGS)
libmysqllb_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_mysql_lb.la

libdhcp_mysql_lb_la_SOURCES  =
libdhcp_mysql_lb_la_LDFLAGS  = $(AM_LDFLAGS) $(MYSQL_LIBS)
libdhcp_mysql_lb_la_LDFLAGS  += -avoid-version -export-dynamic -module

libdhcp_mysql_lb_la_LIBADD = libmysqllb.la
libdhcp_mysql_lb_la_LIBADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
libdhcp_mysql_lb_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_mysql_lb_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_mysql_lb_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_mysql_lb_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_mysql_lb_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_mysql_lb_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_mysql_lb_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_mysql_lb_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_mysql_lb_la_LIBADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
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
messages: mysql_lb_messages.h mysql_lb_messages.cc
	@echo Message files regenerated

mysql_lb_messages.h mysql_lb_messages.cc: mysql_lb_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/hooks/dhcp/mysql_lb/mysql_lb_messages.mes

else

messages mysql_lb_messages.h mysql_lb_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif