SUBDIRS = . tests

python_PYTHON = __init__.py ccsession.py cfgmgr.py config_data.py module_spec.py
pythondir = $(pyexecdir)/isc/config

BUILT_SOURCES = $(PYTHON_LOGMSGPKG_DIR)/work/cfgmgr_messages.py
BUILT_SOURCES += $(PYTHON_LOGMSGPKG_DIR)/work/config_messages.py
nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/cfgmgr_messages.py
nodist_pylogmessage_PYTHON += $(PYTHON_LOGMSGPKG_DIR)/work/config_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = $(PYTHON_LOGMSGPKG_DIR)/work/cfgmgr_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/cfgmgr_messages.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/config_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/config_messages.pyc

CLEANDIRS = __pycache__

EXTRA_DIST = cfgmgr_messages.mes config_messages.mes

BUILT_SOURCES += $(PYTHON_LOGMSGPKG_DIR)/cfgmgr_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/cfgmgr_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/cfgmgr_messages.pyc
EXTRA_DIST += $(PYTHON_LOGMSGPKG_SRCDIR)/cfgmgr_messages.py

BUILT_SOURCES += $(PYTHON_LOGMSGPKG_DIR)/config_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/config_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/config_messages.pyc
EXTRA_DIST += $(PYTHON_LOGMSGPKG_SRCDIR)/config_messages.py

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/cfgmgr_messages.py : cfgmgr_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/cfgmgr_messages.mes

$(PYTHON_LOGMSGPKG_DIR)/cfgmgr_messages.py: Makefile
	echo "from work.cfgmgr_messages import *" > $@

$(PYTHON_LOGMSGPKG_DIR)/work/config_messages.py : config_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/config_messages.mes

$(PYTHON_LOGMSGPKG_DIR)/config_messages.py: Makefile
	echo "from work.config_messages import *" > $@

clean-local:
	rm -rf $(CLEANDIRS)
