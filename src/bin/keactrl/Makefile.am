SUBDIRS = . tests

# Install keactrl in sbin and the keactrl.conf required by the keactrl
# in etc. keactrl will look for its configuration file in the etc folder.
sbin_SCRIPTS  = keactrl
KEA_CONFIGFILES = kea-dhcp4.conf
KEA_CONFIGFILES += kea-dhcp6.conf
KEA_CONFIGFILES += kea-dhcp-ddns.conf
KEA_CONFIGFILES += kea-ctrl-agent.conf

if HAVE_NETCONF
KEA_CONFIGFILES += kea-netconf.conf
endif

CONFIGFILES = keactrl.conf $(KEA_CONFIGFILES)

DISTCLEANFILES = keactrl keactrl.conf
CLEANFILES = $(KEA_CONFIGFILES)
EXTRA_DIST = keactrl.in
EXTRA_DIST += keactrl.conf.in
EXTRA_DIST += kea-dhcp4.conf.pre
EXTRA_DIST += kea-dhcp6.conf.pre
EXTRA_DIST += kea-dhcp-ddns.conf.pre
EXTRA_DIST += kea-ctrl-agent.conf.pre
EXTRA_DIST += kea-netconf.conf.pre

# *.conf files are not really sources used for building other targets, but we need
# these files to be generated before make install is called.
BUILT_SOURCES = $(KEA_CONFIGFILES)


kea-dhcp4.conf: kea-dhcp4.conf.pre
	$(top_builddir)/tools/path_replacer.sh \
	$(top_srcdir)/src/bin/keactrl/kea-dhcp4.conf.pre $@

kea-dhcp6.conf: kea-dhcp6.conf.pre
	$(top_builddir)/tools/path_replacer.sh \
	$(top_srcdir)/src/bin/keactrl/kea-dhcp6.conf.pre $@

kea-dhcp-ddns.conf: kea-dhcp-ddns.conf.pre
	$(top_builddir)/tools/path_replacer.sh \
	$(top_srcdir)/src/bin/keactrl/kea-dhcp-ddns.conf.pre $@

kea-ctrl-agent.conf: kea-ctrl-agent.conf.pre
	$(top_builddir)/tools/path_replacer.sh \
	$(top_srcdir)/src/bin/keactrl/kea-ctrl-agent.conf.pre $@

kea-netconf.conf: kea-netconf.conf.pre
	$(top_builddir)/tools/path_replacer.sh \
	$(top_srcdir)/src/bin/keactrl/kea-netconf.conf.pre $@

if INSTALL_CONFIGURATIONS

# Since Kea 1.3.0 release we have 4 different Kea configuration files
# instead of one, i.e. kea-dhcp4.conf, kea-dhcp6.conf, kea-dhcp-ddns.conf
# and kea-ctrl-agent.conf. To facilitate the use of these new files
# the keactrl.conf has been updated in Kea 1.3.0 release. Therefore,
# we install new version of thea keactrl.conf file unconditionally.
# To preserve any user modifications to the old version of the file,
# this old file is backed up as keactrl.conf.bak.
install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@sysconfdir@/@PACKAGE@
	for f in $(CONFIGFILES) ; do	\
		if test -f $(DESTDIR)$(sysconfdir)/@PACKAGE@/$$f && \
		   test $$f = "keactrl.conf"; then \
			mv $(DESTDIR)$(sysconfdir)/@PACKAGE@/$$f \
			   $(DESTDIR)$(sysconfdir)/@PACKAGE@/$$f.bak; \
		fi; \
		if test ! -f $(DESTDIR)$(sysconfdir)/@PACKAGE@/$$f; then \
			${INSTALL_DATA} $$f $(DESTDIR)$(sysconfdir)/@PACKAGE@/; \
		fi; \
	done

endif
