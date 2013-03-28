SUBDIRS = . cc_generated tests

python_PYTHON =	__init__.py data.py session.py message.py logger.py
BUILT_SOURCES = $(PYTHON_LOGMSGPKG_DIR)/work/pycc_messages.py
nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/pycc_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = $(PYTHON_LOGMSGPKG_DIR)/work/pycc_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/pycc_messages.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/pycc_messages.pyo

EXTRA_DIST = pycc_messages.mes proto_defs.py

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/pycc_messages.py: pycc_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
		-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/pycc_messages.mes

pythondir = $(pyexecdir)/isc/cc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
