SUBDIRS = . tests

python_PYTHON = __init__.py builder.py datasrc_info.py logger.py

pythondir = $(pyexecdir)/isc/memmgr

BUILT_SOURCES = $(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.py

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.py

pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = $(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.pyc

EXTRA_DIST = memmgr_messages.mes

$(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.py : memmgr_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/memmgr_messages.mes

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
