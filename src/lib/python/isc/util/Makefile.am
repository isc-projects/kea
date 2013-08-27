SUBDIRS = . cio tests

python_PYTHON =  __init__.py process.py socketserver_mixin.py file.py \
	traceback_handler.py
BUILT_SOURCES = $(PYTHON_LOGMSGPKG_DIR)/work/util_messages.py
python_PYTHON += address_formatter.py

EXTRA_DIST = util_messages.mes

CLEANFILES = $(PYTHON_LOGMSGPKG_DIR)/work/util_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/util_messages.pyc

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/util_messages.py: util_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
		-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/util_messages.mes

pythondir = $(pyexecdir)/isc/util

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
