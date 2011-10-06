SUBDIRS = . tests

python_PYTHON = __init__.py notify_out.py
pythondir = $(pyexecdir)/isc/notify

BUILT_SOURCES = $(PYTHON_LOGMSGPKG_DIR)/work/notify_out_messages.py
nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/notify_out_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

EXTRA_DIST = notify_out_messages.mes

CLEANFILES = $(PYTHON_LOGMSGPKG_DIR)/work/notify_out_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/notify_out_messages.pyc

CLEANDIRS = __pycache__

$(PYTHON_LOGMSGPKG_DIR)/work/notify_out_messages.py : notify_out_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/notify_out_messages.mes

clean-local:
	rm -rf $(CLEANDIRS)
