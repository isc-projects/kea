SUBDIRS = . tests
bin_SCRIPTS = b10-loadzone
noinst_SCRIPTS = run_loadzone.sh

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/loadzone_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = b10-loadzone
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/loadzone_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/loadzone_messages.pyc

man_MANS = b10-loadzone.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-loadzone.xml loadzone_messages.mes

if GENERATE_DOCS

b10-loadzone.8: b10-loadzone.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-loadzone.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/loadzone_messages.py : loadzone_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/loadzone_messages.mes

b10-loadzone: loadzone.py $(PYTHON_LOGMSGPKG_DIR)/work/loadzone_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" loadzone.py >$@
	chmod a+x $@

EXTRA_DIST += tests/normal/README
EXTRA_DIST += tests/normal/dsset-subzone.example.com
EXTRA_DIST += tests/normal/example.com
EXTRA_DIST += tests/normal/example.com.signed
EXTRA_DIST += tests/normal/Kexample.com.+005+04456.key
EXTRA_DIST += tests/normal/Kexample.com.+005+04456.private
EXTRA_DIST += tests/normal/Kexample.com.+005+33495.key
EXTRA_DIST += tests/normal/Kexample.com.+005+33495.private
EXTRA_DIST += tests/normal/Ksql1.example.com.+005+12447.key
EXTRA_DIST += tests/normal/Ksql1.example.com.+005+12447.private
EXTRA_DIST += tests/normal/Ksql1.example.com.+005+33313.key
EXTRA_DIST += tests/normal/Ksql1.example.com.+005+33313.private
EXTRA_DIST += tests/normal/Ksql2.example.com.+005+38482.key
EXTRA_DIST += tests/normal/Ksql2.example.com.+005+38482.private
EXTRA_DIST += tests/normal/Ksql2.example.com.+005+63192.key
EXTRA_DIST += tests/normal/Ksql2.example.com.+005+63192.private
EXTRA_DIST += tests/normal/sql1.example.com
EXTRA_DIST += tests/normal/sql1.example.com.signed
EXTRA_DIST += tests/normal/sql2.example.com
EXTRA_DIST += tests/normal/sql2.example.com.signed

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
