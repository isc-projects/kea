SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-cfgclient.la
libkea_cfgclient_la_SOURCES  = cmds_impl.h
libkea_cfgclient_la_SOURCES += base_command_mgr.cc base_command_mgr.h
libkea_cfgclient_la_SOURCES += client_connection.cc client_connection.h
libkea_cfgclient_la_SOURCES += command_mgr.cc command_mgr.h
libkea_cfgclient_la_SOURCES += config_log.h config_log.cc
libkea_cfgclient_la_SOURCES += config_messages.h config_messages.cc
libkea_cfgclient_la_SOURCES += hooked_command_mgr.cc hooked_command_mgr.h
libkea_cfgclient_la_SOURCES += timeouts.h

libkea_cfgclient_la_LIBADD = $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_cfgclient_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_cfgclient_la_LIBADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS)

libkea_cfgclient_la_LDFLAGS = -no-undefined -version-info 6:0:0
libkea_cfgclient_la_LDFLAGS += $(CRYPTO_LDFLAGS)

# The message file should be in the distribution.
EXTRA_DIST = config_messages.mes command-socket.dox

CLEANFILES = *.gcno *.gcda

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f config_messages.h config_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: config_messages.h config_messages.cc
	@echo Message files regenerated

config_messages.h config_messages.cc: config_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/config/config_messages.mes

else

messages config_messages.h config_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

# Specify the headers for copying into the installation directory tree.
libkea_cfgclient_includedir = $(pkgincludedir)/config
libkea_cfgclient_include_HEADERS = \
	base_command_mgr.h \
	client_connection.h \
	cmds_impl.h \
	command_mgr.h \
	config_log.h \
	config_messages.h \
	hooked_command_mgr.h \
	timeouts.h

