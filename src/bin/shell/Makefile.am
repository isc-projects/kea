SUBDIRS = . tests

EXTRA_DIST =

if KEA_SHELL

# Kea-shell is enabled, here are proper rules for it.
kea_shell_PYTHON = kea-shell.py kea_conn.py kea_connection2.py kea_connector3.py kea_params.py
kea_shelldir = @localstatedir@/@PACKAGE@

bin_SCRIPTS = kea-shell

else

# Kea-shell is disabled, simply keep the files for make dist
EXTRA_DIST += kea-shell.py kea_conn.py kea_connection2.py kea_connector3.py kea_params.py

endif

CLEANFILES = kea-shell kea-shell.pyc


man_MANS = kea-shell.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST += $(man_MANS) kea-shell.xml

if GENERATE_DOCS
kea-shell.8: kea-shell.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/kea-shell.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
kea-shell: kea-shell.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" kea-shell.py >$@
	chmod a+x $@

install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@localstatedir@/@PACKAGE@

install-data-hook:
	-chmod 2770 $(DESTDIR)/@localstatedir@/@PACKAGE@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
