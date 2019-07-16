if GENERATE_DOCS
# TODO
#HTMLDOCS = kea-guide.html kea-messages.html
#DOCS = kea-guide.txt

#dist_doc_DATA = $(DOCS)
#dist_html_DATA = $(HTMLDOCS) kea-guide.css kea-logo-100x70.png
#dist_html_DATA = $(HTMLDOCS) _static/kea-logo-100x70.png

#doc_DATA = _build/singlehtml/kea-guide.html _build/singlehtml/_static/kea-logo-100x70.png

rst_sources=
rst_sources+=kea-messages.rst
rst_sources+=admin.rst
rst_sources+=agent.rst
rst_sources+=api.rst
rst_sources+=classify.rst
rst_sources+=config-backend.rst
rst_sources+=config.rst
rst_sources+=congestion-handling.rst
rst_sources+=ctrl-channel.rst
rst_sources+=ddns.rst
rst_sources+=dhcp4-srv.rst
rst_sources+=dhcp6-srv.rst
rst_sources+=hammer.rst
rst_sources+=hooks-cb-cmds.rst
rst_sources+=hooks-class-cmds.rst
rst_sources+=hooks-ha.rst
rst_sources+=hooks-host-cache.rst
rst_sources+=hooks-lease-cmds.rst
rst_sources+=hooks-radius.rst
rst_sources+=hooks.rst
rst_sources+=hooks-stat-cmds.rst
rst_sources+=install.rst
rst_sources+=index.rst
rst_sources+=intro.rst
rst_sources+=keactrl.rst
rst_sources+=lease-expiration.rst
rst_sources+=lfc.rst
rst_sources+=logging.rst
rst_sources+=netconf.rst
rst_sources+=quickstart.rst
rst_sources+=shell.rst
rst_sources+=stats.rst

static_sources=
static_sources+=_static/kea-imageonly-100bw.png
static_sources+=_static/kea-logo-200.png
static_sources+=_static/kea.css

all_sources=$(rst_sources) conf.py $(static_sources)


EXTRA_DIST = $(all_sources) $(top_srcdir)/tools/system_messages.py

DISTCLEANFILES = $(HTMLDOCS) $(DOCS) kea-messages.xml

CLEANFILES = kea-guide.pdf kea-messages.pdf

mes_files=
mes_files+=$(top_srcdir)/src/hooks/dhcp/mysql_cb/mysql_cb_messages.mes
mes_files+=$(top_srcdir)/src/hooks/dhcp/lease_cmds/lease_cmds_messages.mes
mes_files+=$(top_srcdir)/src/hooks/dhcp/high_availability/ha_messages.mes
mes_files+=$(top_srcdir)/src/hooks/dhcp/stat_cmds/stat_cmds_messages.mes
mes_files+=$(top_srcdir)/src/hooks/dhcp/user_chk/user_chk_messages.mes
mes_files+=$(top_srcdir)/src/lib/config/config_messages.mes
mes_files+=$(top_srcdir)/src/lib/hooks/hooks_messages.mes
mes_files+=$(top_srcdir)/src/lib/dhcpsrv/dhcpsrv_messages.mes
mes_files+=$(top_srcdir)/src/lib/dhcpsrv/alloc_engine_messages.mes
mes_files+=$(top_srcdir)/src/lib/dhcpsrv/hosts_messages.mes
mes_files+=$(top_srcdir)/src/lib/http/http_messages.mes
mes_files+=$(top_srcdir)/src/lib/dhcp_ddns/dhcp_ddns_messages.mes
mes_files+=$(top_srcdir)/src/lib/database/db_messages.mes
mes_files+=$(top_srcdir)/src/lib/log/log_messages.mes
mes_files+=$(top_srcdir)/src/lib/log/logimpl_messages.mes
mes_files+=$(top_srcdir)/src/lib/log/tests/log_test_messages.mes
mes_files+=$(top_srcdir)/src/lib/process/process_messages.mes
mes_files+=$(top_srcdir)/src/lib/asiodns/asiodns_messages.mes
mes_files+=$(top_srcdir)/src/lib/eval/eval_messages.mes
mes_files+=$(top_srcdir)/src/bin/dhcp4/dhcp4_messages.mes
mes_files+=$(top_srcdir)/src/bin/agent/ca_messages.mes
mes_files+=$(top_srcdir)/src/bin/d2/d2_messages.mes
mes_files+=$(top_srcdir)/src/bin/dhcp6/dhcp6_messages.mes
mes_files+=$(top_srcdir)/src/bin/lfc/lfc_messages.mes
mes_files+=$(top_srcdir)/src/bin/netconf/netconf_messages.mes

kea-messages.rst: $(mes_files) $(top_srcdir)/tools/system_messages.py
	$(top_srcdir)/tools/system_messages.py -o $@ $(mes_files)


sphinxopts=
sphinxopts+=-v
sphinxopts+=-E
sphinxopts+=-a
sphinxopts+=-c "${abs_srcdir}"
sphinxopts+=-D release="@PACKAGE_VERSION@"
sphinxopts+=-D version="@PACKAGE_VERSION@"

sphinxbuilddir=$(builddir)/_build

all: pdf html

pdf: $(all_sources)
	$(SPHINXBUILD) -M latexpdf $(srcdir) $(sphinxbuilddir) $(sphinxopts)

html: $(all_sources)
	$(SPHINXBUILD) -M $@ $(srcdir) $(sphinxbuilddir) $(sphinxopts)


install-data-local:
	mkdir -p $(DESTDIR)$(docdir)
	cp -r $(sphinxbuilddir)/html $(DESTDIR)$(docdir)
	cp -r $(sphinxbuilddir)/latex/KeaAdministratorReferenceManual.pdf $(DESTDIR)$(docdir)

uninstall-local:
	rm -rf $(DESTDIR)$(docdir)

clean::
	-rm -rf $(sphinxbuilddir)


.PHONY: all pdf html


endif
