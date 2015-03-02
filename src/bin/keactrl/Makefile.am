SUBDIRS = . tests

# Install keactrl in sbin and the keactrl.conf required by the keactrl
# in etc. keactrl will look for its configuration file in the etc folder.
# If the default location needs to be changed it may be achieved by
# setting KEACTRL_CONF environment variable.
sbin_SCRIPTS  = keactrl
CONFIGFILES = keactrl.conf kea.conf

man_MANS = keactrl.8
DISTCLEANFILES = keactrl keactrl.conf $(man_MANS)
CLEANFILES = kea.conf
EXTRA_DIST = keactrl.in keactrl.conf.in kea.conf.pre $(man_MANS) keactrl.xml

# kea.conf is not really a source used for building other targets, but we need
# this file to be generated before make install is called.
BUILT_SOURCES = kea.conf

if GENERATE_DOCS

keactrl.8: keactrl.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/keactrl.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

kea.conf: kea.conf.pre
	$(top_builddir)/tools/path_replacer.sh $(top_srcdir)/src/bin/keactrl/kea.conf.pre $@

if INSTALL_CONFIGURATIONS

install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@sysconfdir@/@PACKAGE@
	for f in $(CONFIGFILES) ; do	\
	  if test ! -f $(DESTDIR)$(sysconfdir)/@PACKAGE@/$$f; then	\
	    ${INSTALL_DATA} $$f $(DESTDIR)$(sysconfdir)/@PACKAGE@/ ;	\
	  fi ;	\
	done

endif
