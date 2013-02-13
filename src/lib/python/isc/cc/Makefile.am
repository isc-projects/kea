SUBDIRS = . cc_generated tests

python_PYTHON =	__init__.py data.py session.py message.py
EXTRA_DIST = proto_defs.py

pythondir = $(pyexecdir)/isc/cc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
