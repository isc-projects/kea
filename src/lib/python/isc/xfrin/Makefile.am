SUBDIRS = . tests

python_PYTHON = __init__.py diff.py
BUILT_SOURCES = $(PYTHON_LOGMSGPKG_DIR)/work/libxfrin_messages.py
nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/libxfrin_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

EXTRA_DIST = libxfrin_messages.mes

CLEANFILES = $(PYTHON_LOGMSGPKG_DIR)/work/libxfrin_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/libxfrin_messages.pyc

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/libxfrin_messages.py: libxfrin_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
		-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/libxfrin_messages.mes

pythondir = $(pyexecdir)/isc/xfrin

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
