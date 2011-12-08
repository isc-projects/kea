SUBDIRS = tests

EXTRA_DIST = README logging.spec tsig_keys.spec

config_plugindir = @prefix@/share/@PACKAGE@/config_plugins
config_plugin_DATA = logging.spec tsig_keys.spec

python_PYTHON = b10logging.py tsig_keys.py
pythondir = $(config_plugindir)

CLEANFILES = b10logging.pyc tsig_keys.pyc
CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
