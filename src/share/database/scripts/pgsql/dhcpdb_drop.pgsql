-- Copyright (C) 2016-2018 Internet Systems Consortium.

-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at http://mozilla.org/MPL/2.0/.

DROP TABLE IF EXISTS lease4 CASCADE;
DROP TABLE IF EXISTS lease6 CASCADE;
DROP TABLE IF EXISTS lease6_types CASCADE;
DROP TABLE IF EXISTS schema_version CASCADE;
DROP TABLE IF EXISTS lease_state CASCADE;
DROP TABLE IF EXISTS dhcp4_options CASCADE;
DROP TABLE IF EXISTS dhcp6_options CASCADE;
DROP TABLE IF EXISTS ipv6_reservations CASCADE;
DROP TABLE IF EXISTS lease_hwaddr_source CASCADE;
DROP TABLE IF EXISTS host_identifier_type CASCADE;
DROP TABLE IF EXISTS dhcp_option_scope CASCADE;
DROP TABLE IF EXISTS hosts CASCADE;
DROP FUNCTION IF EXISTS lease4DumpHeader();
DROP FUNCTION IF EXISTS lease4DumpData();
DROP FUNCTION IF EXISTS lease6DumpHeader();
DROP FUNCTION IF EXISTS lease6DumpData();
DROP TABLE IF EXISTS lease4_stat CASCADE;
DROP FUNCTION IF EXISTS proc_stat_lease4_insert ();
DROP FUNCTION IF EXISTS proc_stat_lease4_update ();
DROP FUNCTION IF EXISTS proc_stat_lease4_delete ();
DROP TABLE IF EXISTS lease6_stat CASCADE;
DROP FUNCTION IF EXISTS proc_stat_lease6_insert ();
DROP FUNCTION IF EXISTS proc_stat_lease6_update ();
DROP FUNCTION IF EXISTS proc_stat_lease6_delete ();
DROP TABLE IF EXISTS logs CASCADE;

--
DROP TABLE IF EXISTS dhcp6_audit;
DROP TABLE IF EXISTS dhcp6_option_def_server;
DROP TABLE IF EXISTS dhcp6_option_def;
DROP TABLE IF EXISTS dhcp6_options_server;
DROP TABLE IF EXISTS dhcp6_pool;
DROP TABLE IF EXISTS dhcp6_pd_pool;
DROP TABLE IF EXISTS dhcp6_subnet;
DROP TABLE IF EXISTS dhcp6_shared_network_server;
DROP TABLE IF EXISTS dhcp6_shared_network;
DROP TABLE IF EXISTS dhcp6_global_parameter_server;
DROP TABLE IF EXISTS dhcp6_global_parameter;
DROP TABLE IF EXISTS dhcp6_server;
DROP TABLE IF EXISTS dhcp6_audit_revision;

DROP TABLE IF EXISTS dhcp4_audit;
DROP TABLE IF EXISTS dhcp4_option_def_server;
DROP TABLE IF EXISTS dhcp4_option_def;
DROP TABLE IF EXISTS dhcp4_options_server;
DROP TABLE IF EXISTS dhcp4_pool;
DROP TABLE IF EXISTS dhcp4_pd_pool;
DROP TABLE IF EXISTS dhcp4_subnet;
DROP TABLE IF EXISTS dhcp4_shared_network_server;
DROP TABLE IF EXISTS dhcp4_shared_network;
DROP TABLE IF EXISTS dhcp4_global_parameter_server;
DROP TABLE IF EXISTS dhcp4_global_parameter;
DROP TABLE IF EXISTS dhcp4_server;
DROP TABLE IF EXISTS dhcp4_audit_revision;

DROP TABLE IF EXISTS modification;
DROP TABLE IF EXISTS parameter_data_type;
DROP TABLE IF EXISTS ddns_replace_client_name_types;
DROP FUNCTION IF EXISTS modification_ts_update;