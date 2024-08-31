SUBDIRS = sphinx devel

EXTRA_DIST = images/kea-logo-100x70.png

nobase_dist_doc_DATA  = examples/agent/comments.json
nobase_dist_doc_DATA += examples/agent/https.json
nobase_dist_doc_DATA += examples/agent/rbac.json
nobase_dist_doc_DATA += examples/agent/simple.json
nobase_dist_doc_DATA += examples/ddns/all-keys.json
nobase_dist_doc_DATA += examples/ddns/all-keys-netconf.json
nobase_dist_doc_DATA += examples/ddns/comments.json
nobase_dist_doc_DATA += examples/ddns/gss-tsig.json
nobase_dist_doc_DATA += examples/ddns/sample1.json
nobase_dist_doc_DATA += examples/ddns/template.json
nobase_dist_doc_DATA += examples/https/httpd2/kea-httpd2.conf
nobase_dist_doc_DATA += examples/https/nginx/kea-nginx.conf
nobase_dist_doc_DATA += examples/https/shell/kea-stunnel.conf
nobase_dist_doc_DATA += examples/kea4/advanced.json
nobase_dist_doc_DATA += examples/kea4/all-keys.json
nobase_dist_doc_DATA += examples/kea4/all-keys-netconf.json
nobase_dist_doc_DATA += examples/kea4/all-options.json
nobase_dist_doc_DATA += examples/kea4/backends.json
nobase_dist_doc_DATA += examples/kea4/classify.json
nobase_dist_doc_DATA += examples/kea4/classify2.json
nobase_dist_doc_DATA += examples/kea4/comments.json
nobase_dist_doc_DATA += examples/kea4/config-backend.json
nobase_dist_doc_DATA += examples/kea4/dhcpv4-over-dhcpv6.json
nobase_dist_doc_DATA += examples/kea4/global-reservations.json
nobase_dist_doc_DATA += examples/kea4/ha-load-balancing-server1-mt-with-tls.json
nobase_dist_doc_DATA += examples/kea4/ha-load-balancing-server2-mt.json
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
nobase_dist_doc_DATA += examples/kea4/vivso.json
nobase_dist_doc_DATA += examples/kea4/vendor-specific.json
nobase_dist_doc_DATA += examples/kea6/advanced.json
nobase_dist_doc_DATA += examples/kea6/all-keys.json
nobase_dist_doc_DATA += examples/kea6/all-keys-netconf.json
nobase_dist_doc_DATA += examples/kea6/all-options.json
nobase_dist_doc_DATA += examples/kea6/backends.json
nobase_dist_doc_DATA += examples/kea6/classify.json
nobase_dist_doc_DATA += examples/kea6/classify2.json
nobase_dist_doc_DATA += examples/kea6/comments.json
nobase_dist_doc_DATA += examples/kea6/config-backend.json
nobase_dist_doc_DATA += examples/kea6/dhcpv4-over-dhcpv6.json
nobase_dist_doc_DATA += examples/kea6/duid.json
nobase_dist_doc_DATA += examples/kea6/global-reservations.json
nobase_dist_doc_DATA += examples/kea6/ha-hot-standby-server1-with-tls.json
nobase_dist_doc_DATA += examples/kea6/ha-hot-standby-server2.json
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
nobase_dist_doc_DATA += examples/kea6/tee-times.json
nobase_dist_doc_DATA += examples/kea6/with-ddns.json
nobase_dist_doc_DATA += examples/netconf/kea-dhcp6-operations/boot.json
nobase_dist_doc_DATA += examples/netconf/kea-dhcp6-operations/logging.xml
nobase_dist_doc_DATA += examples/netconf/kea-dhcp6-operations/netconf.json
nobase_dist_doc_DATA += examples/netconf/kea-dhcp6-operations/startup.xml
nobase_dist_doc_DATA += examples/netconf/kea-dhcp6-operations/twopools.xml
nobase_dist_doc_DATA += examples/netconf/kea-dhcp6-operations/twosubnets.xml
nobase_dist_doc_DATA += examples/netconf/comments.json
nobase_dist_doc_DATA += examples/netconf/simple-dhcp4.json
nobase_dist_doc_DATA += examples/netconf/simple-dhcp6.json

nobase_dist_doc_DATA += examples/template-power-user-home/info.md
nobase_dist_doc_DATA += examples/template-power-user-home/kea-ca-1.conf
nobase_dist_doc_DATA += examples/template-power-user-home/kea-ca-2.conf
nobase_dist_doc_DATA += examples/template-power-user-home/kea-dhcp4-1.conf
nobase_dist_doc_DATA += examples/template-power-user-home/kea-dhcp4-2.conf

nobase_dist_doc_DATA += examples/template-ha-mt-tls/info.md
nobase_dist_doc_DATA += examples/template-ha-mt-tls/kea-ca-1.conf
nobase_dist_doc_DATA += examples/template-ha-mt-tls/kea-ca-2.conf
nobase_dist_doc_DATA += examples/template-ha-mt-tls/kea-dhcp4-1.conf
nobase_dist_doc_DATA += examples/template-ha-mt-tls/kea-dhcp4-2.conf

# If there's any new parameter added for any grammar in one of the daemons, someone should go through
# this procedure:
#
# 1. autoreconf -i && ./configure --enable-generate-docs --enable-generate-parser
# 2. cd doc
# 3. make grammar
# 4. make -C sphinx html
# 5. Inspect the html output and make sure it's ok.
# 6. Review changes in doc/sphinx/grammar/*
# 7. Check in changed files in doc/sphinx/grammar/*
#
# Make sure you commit only relevant changes, skip the timestamp only updates.
grammar:
if GENERATE_DOCS
if GENERATE_PARSER
	mkdir -p $(abs_top_srcdir)/doc/sphinx/grammar
	$(abs_top_srcdir)/tools/extract_bnf.sh $(abs_top_srcdir)/src/bin/dhcp4/dhcp4_parser \
	    --markdown ':ref:`dhcp4`' > $(abs_top_srcdir)/doc/sphinx/grammar/grammar-dhcp4-parser.rst
	$(abs_top_srcdir)/tools/extract_bnf.sh $(abs_top_srcdir)/src/bin/dhcp6/dhcp6_parser \
	    --markdown ':ref:`dhcp6`' > $(abs_top_srcdir)/doc/sphinx/grammar/grammar-dhcp6-parser.rst
	$(abs_top_srcdir)/tools/extract_bnf.sh $(abs_top_srcdir)/src/bin/d2/d2_parser \
	    --markdown ':ref:`dhcp-ddns-server`' > $(abs_top_srcdir)/doc/sphinx/grammar/grammar-d2-parser.rst
	$(abs_top_srcdir)/tools/extract_bnf.sh $(abs_top_srcdir)/src/bin/agent/agent_parser \
	    --markdown ':ref:`kea-ctrl-agent`' > $(abs_top_srcdir)/doc/sphinx/grammar/grammar-ca-parser.rst
	$(abs_top_srcdir)/tools/extract_bnf.sh $(abs_top_srcdir)/src/bin/netconf/netconf_parser \
	    --markdown ':ref:`netconf`' > $(abs_top_srcdir)/doc/sphinx/grammar/grammar-netconf-parser.rst
else
	@echo "ERROR: You need to enable both docs (--enable-generate-docs) and parser (--enable-generate-parser)"
	@echo "ERROR: to regenerate grammar documentation."
	false
endif
else
	@echo "ERROR: You need to enable both docs (--enable-generate-docs) and parser (--enable-generate-parser)"
	@echo "ERROR: to regenerate grammar documentation."
	false
endif
