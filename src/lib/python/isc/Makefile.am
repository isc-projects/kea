if WANT_DNS

want_acl = acl
want_datasrc = datasrc
want_ddns = ddns
want_notify = notify
want_server_common = server_common
want_statistics = statistics
want_xfrin = xfrin

if USE_SHARED_MEMORY
# Build the memory manager only if we have shared memory.
# It is useless without it.
want_memmgr = memmgr
endif

endif # WANT_DNS

# The following build order must be maintained. So we create the
# variables above and add directories in that order to SUBDIRS.
SUBDIRS = $(want_datasrc) util cc config dns log net $(want_notify) \
	testutils $(want_acl) bind10 $(want_xfrin) log_messages \
	$(want_server_common) $(want_ddns) sysinfo $(want_statistics) \
	$(want_memmgr)

python_PYTHON = __init__.py

pythondir = $(pyexecdir)/isc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
