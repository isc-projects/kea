SUBDIRS = tests

EXTRA_DIST = README logging.spec tsig_keys.spec

datasrc.spec: datasrc.spec.pre
	$(SED) -e "s|@@STATIC_ZONE_FILE@@|$(pkgdatadir)/static.zone|;s|@@SQLITE3_DATABASE_FILE@@|$(localstatedir)/$(PACKAGE)/zone.sqlite3|" datasrc.spec.pre >$@

config_plugindir = @prefix@/share/@PACKAGE@/config_plugins
config_plugin_DATA = logging.spec tsig_keys.spec datasrc.spec

python_PYTHON = b10logging.py tsig_keys.py datasrc_config_plugin.py
pythondir = $(config_plugindir)

CLEANFILES = b10logging.pyc tsig_keys.pyc datasrc.spec
CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
