# The following build order must be maintained.
SUBDIRS = util cc config dns log net testutils bind10 log_messages \
          sysinfo

python_PYTHON = __init__.py

pythondir = $(pyexecdir)/isc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
