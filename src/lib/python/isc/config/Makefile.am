SUBDIRS = . tests

python_PYTHON = __init__.py ccsession.py cfgmgr.py config_data.py module_spec.py cfgmgr_messages.py
python_SCRIPTS = cfgmgr_messages.py

pythondir = $(pyexecdir)/isc/config

# Define rule to build logging source files from message file
cfgmgr_messages.py: cfgmgr_messages.mes
	$(top_builddir)/src/lib/log/compiler/message -p $(top_srcdir)/src/lib/python/isc/config/cfgmgr_messages.mes

CLEANFILES = cfgmgr_messages.py cfgmgr_messages.pyc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
