SUBDIRS = . cio tests

python_PYTHON = __init__.py process.py socketserver_mixin.py file.py \
		common_defs.py
BUILT_SOURCES = common_defs.py
EXTRA_DIST = pythonize_constants.py

common_defs.py: $(top_srcdir)/src/lib/util/common_defs.cc pythonize_constants.py
	$(PYTHON) $(srcdir)/pythonize_constants.py $(top_srcdir)/src/lib/util/common_defs.cc $@

pythondir = $(pyexecdir)/isc/util

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
