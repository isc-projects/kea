# Nothing is installed from this directory.  This local_plugins
# directory overrides the plugins directory when lettuce is run, and the
# spec file here is used to serve the static zone from the source tree
# for testing (instead of installation prefix).

noinst_DATA = datasrc.spec

datasrc.spec: ../plugins/datasrc.spec.pre
	$(SED) -e "s|@@STATIC_ZONE_FILE@@|$(abs_top_builddir)/src/lib/datasrc/static.zone|;s|@@SQLITE3_DATABASE_FILE@@|$(abs_top_builddir)/local.zone.sqlite3|" ../plugins/datasrc.spec.pre >$@

CLEANFILES = datasrc.spec
