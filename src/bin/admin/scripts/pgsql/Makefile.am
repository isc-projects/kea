SUBDIRS = .

EXTRA_DIST = dhcpdb_create.pgsql

dist_pkgdata_DATA = $(EXTRA_DIR)

install-data-hook:
	mkdir -p $(DESTDIR)${datarootdir}/${PACKAGE_NAME}/scripts/pgsql
	for file in $(EXTRA_DIST); do \
		cp $$file $(DESTDIR)${datarootdir}/${PACKAGE_NAME}/scripts/pgsql; \
	done
