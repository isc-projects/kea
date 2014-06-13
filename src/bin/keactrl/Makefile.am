SUBDIRS = . tests

# Install keactrl in sbin and the keactrl.conf required by the keactrl
# in etc. keactrl will look for its configuration file in the etc folder.
# If the default location needs to be changed the it may be achieved by
# setting KEACTRL_CONF environment variable.
sbin_SCRIPTS  = keactrl
CONFIGFILES = keactrl.conf kea.conf

DISTCLEANFILES = keactrl $(CONFIGFILES)
EXTRA_DIST = keactrl.in keactrl.conf.in

install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@sysconfdir@/@PACKAGE@
	for f in $(CONFIGFILES) ; do	\
	  if test ! -f $(DESTDIR)$(sysconfdir)/@PACKAGE@/$$f; then	\
	    ${INSTALL_DATA} $$f $(DESTDIR)$(sysconfdir)/@PACKAGE@/ ;	\
	  fi ;	\
	done

