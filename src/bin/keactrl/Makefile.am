SUBDIRS = . tests

# Install keactrl in sbin and the keactrl.conf required by the keactrl
# in etc. keactrl will look for its configuration file in the etc folder.
# If the default location needs to be changed it may be achieved by
# setting KEACTRL_CONF environment variable.
sbin_SCRIPTS  = keactrl
KEA_CONFIGFILES = kea-dhcp4.conf kea-dhcp6.conf kea-dhcp-ddns.conf \
                  kea-ctrl-agent.conf
CONFIGFILES = keactrl.conf $(KEA_CONFIGFILES)

man_MANS = keactrl.8
DISTCLEANFILES = keactrl keactrl.conf $(man_MANS)
CLEANFILES = $(KEA_CONFIGFILES)
EXTRA_DIST = keactrl.in keactrl.conf.in kea-dhcp4.conf.pre \
             kea-dhcp6.conf.pre kea-dhcp-ddns.conf.pre \
             kea-ctrl-agent.conf.pre $(man_MANS) keactrl.xml

# *.conf files are not really sources used for building other targets, but we need
# these files to be generated before make install is called.
BUILT_SOURCES = $(KEA_CONFIGFILES)

if GENERATE_DOCS

keactrl.8: keactrl.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/keactrl.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

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
