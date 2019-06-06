
rst_sources=admin.rst
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
rst_sources+=intro.rst
rst_sources+=keactrl.rst
rst_sources+=kea-guide.rst
rst_sources+=lease-expiration.rst
rst_sources+=lfc.rst
rst_sources+=logging.rst
rst_sources+=netconf.rst
rst_sources+=quickstart.rst
rst_sources+=shell.rst
rst_sources+=stats.rst


sphinxbuild = sphinx-build
sphinxopts = -E

kea-guide.pdf: $(rst_sources)
	@$(sphinxbuild) -M latexpdf $(srcdir) $(builddir)/_build $(sphinxopts)

kea-guide.html: $(rst_sources)
	@$(sphinxbuild) -M singlehtml $(srcdir) $(builddir)/_build $(sphinxopts)


EXTRA_DIST = $(rst_sources)

# TODO: here should ba added some stuff for DIST, etc to be consumed by automake/autoconf
