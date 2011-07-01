SUBDIRS = . tests

python_PYTHON = __init__.py ccsession.py cfgmgr.py config_data.py module_spec.py
pyexec_DATA = cfgmgr_messages.py config_messages.py

pythondir = $(pyexecdir)/isc/config

# Define rule to build logging source files from message file
cfgmgr_messages.py: cfgmgr_messages.mes
	$(top_builddir)/src/lib/log/compiler/message -p $(top_srcdir)/src/lib/python/isc/config/cfgmgr_messages.mes
config_messages.py: config_messages.mes
	$(top_builddir)/src/lib/log/compiler/message -p $(top_srcdir)/src/lib/python/isc/config/config_messages.mes

CLEANFILES = cfgmgr_messages.py cfgmgr_messages.pyc config_messages.py config_messages.pyc

CLEANDIRS = __pycache__

EXTRA_DIST = cfgmgr_messages.mes config_messages.mes

clean-local:
	rm -rf $(CLEANDIRS)
