systest:
	sh $(srcdir)/runall.sh

distclean-local:
	sh $(srcdir)/cleanall.sh

# Most of the files under this directory (including test subdirectories)
# must be listed in EXTRA_DIST.
EXTRA_DIST = README cleanall.sh ifconfig.sh start.pl stop.pl run.sh runall.sh
EXTRA_DIST += common/default_user.csv
EXTRA_DIST += glue/auth.good glue/example.good glue/noglue.good glue/test.good
EXTRA_DIST += glue/tests.sh glue/clean.sh
EXTRA_DIST += glue/nsx1/com.db glue/nsx1/net.db glue/nsx1/root-servers.nil.db
EXTRA_DIST += glue/nsx1/root.db
EXTRA_DIST += bindctl/tests.sh bindctl/clean.sh bindctl/setup.sh
EXTRA_DIST += bindctl/nsx1/root.db bindctl/nsx1/example-normalized.db
