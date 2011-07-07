SUBDIRS = . tests

python_PYTHON = __init__.py notify_out.py
pyexec_DATA = $(top_builddir)/src/lib/python/notify_out_messages.py

pythondir = $(pyexecdir)/isc/notify

$(top_builddir)/src/lib/python/notify_out_messages.py: notify_out_messages.mes
	$(top_builddir)/src/lib/log/compiler/message -p -d $(top_builddir)/src/lib/python $(top_srcdir)/src/lib/python/isc/notify/notify_out_messages.mes

EXTRA_DIST = notify_out_messages.mes

CLEANFILES =  $(top_builddir)/src/lib/python/notify_out_messages.pyc
CLEANFILES += $(top_builddir)/src/lib/python/notify_out_messages.py

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
