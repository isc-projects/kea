bin_SCRIPTS = bindctl
man_MANS = bindctl.1

EXTRA_DIST = $(man_MANS) bindctl.xml

python_PYTHON = __init__.py bindcmd.py cmdparse.py exception.py moduleinfo.py mycollections.py
pythondir = $(pyexecdir)/bindctl

bindctldir = $(DESTDIR)$(pkgdatadir)
bindctl_DATA = bindctl.pem
EXTRA_DIST += bindctl.pem

CLEANFILES = bindctl

bindctl.1: bindctl.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/bindctl.xml

bindctl: bindctl-source.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@SYSCONFDIR@@|@sysconfdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bindctl-source.py >$@
	chmod a+x $@
