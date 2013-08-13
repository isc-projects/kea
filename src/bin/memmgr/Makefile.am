if USE_SHARED_MEMORY

# If we don't have shared memory, the memory manager is useless.
# Skip building, testing and installing it completely.

SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-memmgr

b10_memmgrdir = $(pkgdatadir)
b10_memmgr_DATA = memmgr.spec

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = b10-memmgr memmgr.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.pyc
CLEANFILES += memmgr.spec

EXTRA_DIST =  memmgr_messages.mes

man_MANS = b10-memmgr.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST += $(man_MANS) b10-memmgr.xml

if GENERATE_DOCS

b10-memmgr.8: b10-memmgr.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-memmgr.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.py : memmgr_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/memmgr_messages.mes

memmgr.spec: memmgr.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" memmgr.spec.pre > $@

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-memmgr: memmgr.py $(PYTHON_LOGMSGPKG_DIR)/work/memmgr_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" memmgr.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

# install the default directory for memory-mapped files.  Note that the
# path must be identical to the default value in memmgr.spec.  We'll make
# it readable only for the owner to minimize the risk of accidents.
install-data-local:
	$(mkinstalldirs) $(DESTDIR)@localstatedir@/@PACKAGE@/mapped_files

install-data-hook:
	-chmod 700 $(DESTDIR)@localstatedir@/@PACKAGE@/mapped_files

clean-local:
	rm -rf $(CLEANDIRS)

endif
