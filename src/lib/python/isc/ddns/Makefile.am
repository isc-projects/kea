SUBDIRS = . tests

python_PYTHON = __init__.py session.py logger.py zone_config.py
BUILT_SOURCES = $(PYTHON_LOGMSGPKG_DIR)/work/libddns_messages.py
nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/libddns_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

EXTRA_DIST = libddns_messages.mes

CLEANFILES = $(PYTHON_LOGMSGPKG_DIR)/work/libddns_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/libddns_messages.pyc

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/libddns_messages.py: libddns_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
		-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/libddns_messages.mes

pythondir = $(pyexecdir)/isc/ddns

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
