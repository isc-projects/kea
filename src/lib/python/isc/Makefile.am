SUBDIRS = datasrc util cc config dns log net notify testutils acl bind10
SUBDIRS += xfrin log_messages server_common ddns sysinfo statistics
if USE_SHARED_MEMORY
# The memory manager is useless without shared memory support
SUBDIRS += memmgr
endif

python_PYTHON = __init__.py

pythondir = $(pyexecdir)/isc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
