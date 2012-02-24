SUBDIRS = tests

python_PYTHON = __init__.py tsig_keyring.py

pythondir = $(pyexecdir)/isc/server_common

BUILT_SOURCES = $(PYTHON_LOGMSGPKG_DIR)/work/server_common_messages.py
nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/server_common_messages.py

pylogmessagedir = $(pyexecdir)/isc/logmessages/

CLEANFILES = $(PYTHON_LOGMSGPKG_DIR)/work/server_common_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/server_common_messages.pyc

CLEANDIRS = __pycache__

EXTRA_DIST = server_common_messages.mes

$(PYTHON_LOGMSGPKG_DIR)/work/server_common_messages.py : server_common_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/server_common_messages.mes

clean-local:
	rm -rf $(CLEANDIRS)
