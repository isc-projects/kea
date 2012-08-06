SUBDIRS = tests

EXTRA_DIST = README logging.spec tsig_keys.spec

datasrc.spec: datasrc.spec.pre
	$(SED) -e "s|@@PKGDATADIR@@|$(pkgdatadir)|;s|@@LOCALSTATEDIR@@|$(localstatedir)|" datasrc.spec.pre >$@

config_plugindir = @prefix@/share/@PACKAGE@/config_plugins
config_plugin_DATA = logging.spec tsig_keys.spec datasrc.spec

python_PYTHON = b10logging.py tsig_keys.py datasrc_config_plugin.py
pythondir = $(config_plugindir)

CLEANFILES = b10logging.pyc tsig_keys.pyc datasrc.spec
CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
