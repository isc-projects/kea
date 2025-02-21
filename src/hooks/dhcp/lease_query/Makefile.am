SUBDIRS = . libloadtests tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST  = lease_query_messages.mes
EXTRA_DIST += lease_query.dox Doxyfile Doxyfile-xml

CLEANFILES = *.gcno *.gcda

# convenience archive
noinst_LTLIBRARIES = liblease_query.la

liblease_query_la_SOURCES  = lease_query_callouts.cc
liblease_query_la_SOURCES += lease_query_connection.cc lease_query_connection.h
liblease_query_la_SOURCES += lease_query_impl.cc lease_query_impl.h
liblease_query_la_SOURCES += lease_query_impl_factory.cc lease_query_impl_factory.h
liblease_query_la_SOURCES += lease_query_impl4.cc lease_query_impl4.h
liblease_query_la_SOURCES += lease_query_impl6.cc lease_query_impl6.h
liblease_query_la_SOURCES += lease_query_listener.h
liblease_query_la_SOURCES += lease_query_log.cc lease_query_log.h
liblease_query_la_SOURCES += lease_query_messages.cc lease_query_messages.h
liblease_query_la_SOURCES += blq_msg.h
liblease_query_la_SOURCES += bulk_lease_query.h
liblease_query_la_SOURCES += bulk_lease_query4.cc bulk_lease_query4.h
liblease_query_la_SOURCES += bulk_lease_query6.cc bulk_lease_query6.h
liblease_query_la_SOURCES += blq_service.cc blq_service.h
liblease_query_la_SOURCES += mt_lease_query_mgr.cc mt_lease_query_mgr.h
liblease_query_la_SOURCES += version.cc

liblease_query_la_CXXFLAGS = $(AM_CXXFLAGS)
liblease_query_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_lease_query.la

libdhcp_lease_query_la_SOURCES =

libdhcp_lease_query_la_LDFLAGS  = $(AM_LDFLAGS)
libdhcp_lease_query_la_LDFLAGS  += -avoid-version -export-dynamic -module

libdhcp_lease_query_la_LIBADD  = liblease_query.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/tcp/libkea-tcp.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_lease_query_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_lease_query_la_LIBADD += $(LOG4CPLUS_LIBS)
libdhcp_lease_query_la_LIBADD += $(CRYPTO_LIBS)
libdhcp_lease_query_la_LIBADD += $(BOOST_LIBS)

devel:
	mkdir -p html
	(cat Doxyfile; echo PROJECT_NUMBER=$(PACKAGE_VERSION)) | doxygen - > html/doxygen.log 2> html/doxygen-error.log
	echo `grep -i ": warning:" html/doxygen-error.log | wc -l` warnings/errors detected.

clean-local:
	rm -rf html

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required. To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f lease_query_messages.h lease_query_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: lease_query_messages.h lease_query_messages.cc
	@echo Message files regenerated

lease_query_messages.h lease_query_messages.cc: lease_query_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/dhcp/lease_query/lease_query_messages.mes)

else

messages lease_query_messages.h lease_query_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
