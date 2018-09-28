SUBDIRS = guide

EXTRA_DIST  = version.ent.in Doxyfile Doxyfile-xml
EXTRA_DIST += devel/bison.dox
EXTRA_DIST += devel/config-backend.dox
EXTRA_DIST += devel/contribute.dox
EXTRA_DIST += devel/mainpage.dox
EXTRA_DIST += devel/terminology.dox
EXTRA_DIST += devel/unit-tests.dox

nobase_dist_doc_DATA  = examples/agent/comments.json
nobase_dist_doc_DATA += examples/agent/simple.json
nobase_dist_doc_DATA += examples/ddns/comments.json
nobase_dist_doc_DATA += examples/ddns/sample1.json
nobase_dist_doc_DATA += examples/ddns/template.json
nobase_dist_doc_DATA += examples/https/httpd2/kea-httpd2.conf
nobase_dist_doc_DATA += examples/https/nginx/kea-nginx.conf
nobase_dist_doc_DATA += examples/https/shell/kea-stunnel.conf
nobase_dist_doc_DATA += examples/kea4/advanced.json
nobase_dist_doc_DATA += examples/kea4/backends.json
nobase_dist_doc_DATA += examples/kea4/cassandra.json
nobase_dist_doc_DATA += examples/kea4/classify.json
nobase_dist_doc_DATA += examples/kea4/classify2.json
nobase_dist_doc_DATA += examples/kea4/comments.json
nobase_dist_doc_DATA += examples/kea4/dhcpv4-over-dhcpv6.json
nobase_dist_doc_DATA += examples/kea4/ha-load-balancing-primary.json
nobase_dist_doc_DATA += examples/kea4/hooks.json
nobase_dist_doc_DATA += examples/kea4/hooks-radius.json
nobase_dist_doc_DATA += examples/kea4/leases-expiration.json
nobase_dist_doc_DATA += examples/kea4/multiple-options.json
nobase_dist_doc_DATA += examples/kea4/mysql-reservations.json
nobase_dist_doc_DATA += examples/kea4/pgsql-reservations.json
nobase_dist_doc_DATA += examples/kea4/reservations.json
nobase_dist_doc_DATA += examples/kea4/several-subnets.json
nobase_dist_doc_DATA += examples/kea4/shared-network.json
nobase_dist_doc_DATA += examples/kea4/single-subnet.json
nobase_dist_doc_DATA += examples/kea4/with-ddns.json
nobase_dist_doc_DATA += examples/kea6/advanced.json
nobase_dist_doc_DATA += examples/kea6/backends.json
nobase_dist_doc_DATA += examples/kea6/cassandra.json
nobase_dist_doc_DATA += examples/kea6/classify.json
nobase_dist_doc_DATA += examples/kea6/classify2.json
nobase_dist_doc_DATA += examples/kea6/comments.json
nobase_dist_doc_DATA += examples/kea6/dhcpv4-over-dhcpv6.json
nobase_dist_doc_DATA += examples/kea6/duid.json
nobase_dist_doc_DATA += examples/kea6/ha-hot-standby.json
nobase_dist_doc_DATA += examples/kea6/hooks.json
nobase_dist_doc_DATA += examples/kea6/iPXE.json
nobase_dist_doc_DATA += examples/kea6/leases-expiration.json
nobase_dist_doc_DATA += examples/kea6/multiple-options.json
nobase_dist_doc_DATA += examples/kea6/mysql-reservations.json
nobase_dist_doc_DATA += examples/kea6/pgsql-reservations.json
nobase_dist_doc_DATA += examples/kea6/reservations.json
nobase_dist_doc_DATA += examples/kea6/several-subnets.json
nobase_dist_doc_DATA += examples/kea6/shared-network.json
nobase_dist_doc_DATA += examples/kea6/simple.json
nobase_dist_doc_DATA += examples/kea6/softwire46.json
nobase_dist_doc_DATA += examples/kea6/stateless.json
nobase_dist_doc_DATA += examples/kea6/with-ddns.json
nobase_dist_doc_DATA += examples/netconf/comments.json
nobase_dist_doc_DATA += examples/netconf/simple.json
nobase_dist_doc_DATA += examples/netconf/simple-dhcp4.json

devel:
	mkdir -p html
	(cat Doxyfile; echo PROJECT_NUMBER=$(PACKAGE_VERSION)) | doxygen - > html/doxygen.log 2> html/doxygen-error.log
	echo `grep -i ": warning:" html/doxygen-error.log | wc -l` warnings/errors detected.

guide:
	$(MAKE) -C guide kea-guide.html

clean:
	rm -rf html

# That's a bit of a hack, but we are making sure that devel target
# is always valid. The alternative is to make devel depend on all
# *.cc *.h files in the whole tree.
.PHONY: devel guide
