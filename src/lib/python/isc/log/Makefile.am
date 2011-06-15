SUBDIRS = . tests

python_PYTHON = __init__.py log.py

pythondir = $(pyexecdir)/isc/log

pytest:
	$(SHELL) tests/log_test

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
