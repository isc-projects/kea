# This makefile is a hack to enable tests to run with one module generated
# while the rest is just used. The generated file is created under build dir,
# not the src dir, which means it is not found when these are different.
#
# We have a forwarder module in the src dir and build the real one in different
# location. This is similar to what happens in log_messages/work. We can't
# reuse the name `work`, since it would collide, so we use less generic name.

nodist_python_PYTHON = proto_defs.py
BUILT_SOURCES = proto_defs.py __init__.py
noinst_SCRIPTS = __init__.py

proto_defs.py: $(top_srcdir)/src/lib/cc/proto_defs.cc \
	$(top_srcdir)/src/lib/util/python/pythonize_constants.py
	$(PYTHON) $(top_srcdir)/src/lib/util/python/pythonize_constants.py \
		$(top_srcdir)/src/lib/cc/proto_defs.cc $@

# We need to create an __init__.py, so it is recognized as module.
# But it may be empty.
__init__.py:
	touch $@

pythondir = $(pyexecdir)/isc/cc

CLEANDIRS = __pycache__

CLEANFILES = proto_defs.py __init__.py
CLEANFILES += proto_defs.pyc __init__.pyc
CLEANFILES += proto_defs.pyo __init__.pyo

clean-local:
	rm -rf $(CLEANDIRS)
