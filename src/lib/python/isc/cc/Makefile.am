SUBDIRS = . tests

python_PYTHON =	__init__.py data.py session.py message.py
nodist_python_PYTHON = proto_defs.py
BUILT_SOURCES = proto_defs.py

proto_defs.py: $(top_srcdir)/src/lib/cc/proto_defs.cc \
	$(top_srcdir)/src/lib/util/python/pythonize_constants.py
	$(PYTHON) $(top_srcdir)/src/lib/util/python/pythonize_constants.py \
		$(top_srcdir)/src/lib/cc/proto_defs.cc $@


pythondir = $(pyexecdir)/isc/cc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
