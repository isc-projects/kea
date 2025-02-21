SUBDIRS = . libloadtests tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST = class_cmds_messages.mes

CLEANFILES = *.gcno *.gcda

# convenience archive

noinst_LTLIBRARIES = libclass_cmds.la

libclass_cmds_la_SOURCES  = class_cmds.cc class_cmds.h
libclass_cmds_la_SOURCES += class_cmds_callouts.cc
libclass_cmds_la_SOURCES += class_cmds_log.cc class_cmds_log.h
libclass_cmds_la_SOURCES += class_cmds_messages.cc class_cmds_messages.h
libclass_cmds_la_SOURCES += version.cc

libclass_cmds_la_CXXFLAGS = $(AM_CXXFLAGS)
libclass_cmds_la_CPPFLAGS = $(AM_CPPFLAGS)

# install the shared object into $(libdir)/kea/hooks
lib_hooksdir = $(libdir)/kea/hooks
lib_hooks_LTLIBRARIES = libdhcp_class_cmds.la

libdhcp_class_cmds_la_SOURCES =
libdhcp_class_cmds_la_LDFLAGS = $(AM_LDFLAGS)
libdhcp_class_cmds_la_LDFLAGS += -avoid-version -export-dynamic -module
libdhcp_class_cmds_la_LIBADD  = libclass_cmds.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_class_cmds_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

EXTRA_DIST += class_cmds.dox Doxyfile

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
	rm -f class_cmds_messages.h class_cmds_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: class_cmds_messages.h class_cmds_messages.cc
	@echo Message files regenerated

class_cmds_messages.h class_cmds_messages.cc: class_cmds_messages.mes
	(cd $(top_srcdir); \
	$(abs_top_builddir)/src/lib/log/compiler/kea-msg-compiler src/hooks/dhcp/class_cmds/class_cmds_messages.mes)

else

messages class_cmds_messages.h class_cmds_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif
