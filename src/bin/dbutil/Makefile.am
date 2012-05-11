SUBDIRS = . tests

bin_SCRIPTS = b10-dbutil
man_MANS = b10-dbutil.8

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/dbutil_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

EXTRA_DIST = $(man_MANS) b10-dbutil.xml dbutil_messages.mes

noinst_SCRIPTS = run_dbutil.sh

CLEANFILES = b10-dbutil b10-dbutil.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/dbutil_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/dbutil_messages.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/dbutil_messages.pyo

if ENABLE_MAN

b10-dbutil.8: b10-dbutil.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-dbutil.xml

endif

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/dbutil_messages.py : dbutil_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/dbutil_messages.mes

b10-dbutil: dbutil.py $(PYTHON_LOGMSGPKG_DIR)/work/dbutil_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@SYSCONFDIR@@|@sysconfdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" dbutil.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
