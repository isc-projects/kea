SUBDIRS = .

EXTRA_DIST = dhcpdb_create.mysql upgrade_1.0_to_2.0.sh

install-data-hook:
	mkdir -p $(DESTDIR)${datarootdir}/${PACKAGE_NAME}/scripts/mysql
	for file in $(EXTRA_DIST); do \
		cp $$file $(DESTDIR)${datarootdir}/${PACKAGE_NAME}/scripts/mysql; \
	done
