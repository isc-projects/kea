-- Copyright (C) 2016-2023 Internet Systems Consortium.

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
DROP TABLE IF EXISTS lease4_pool_stat CASCADE;
DROP FUNCTION IF EXISTS proc_stat_lease4_insert ();
DROP FUNCTION IF EXISTS proc_stat_lease4_update ();
DROP FUNCTION IF EXISTS proc_stat_lease4_delete ();
DROP TABLE IF EXISTS lease6_stat CASCADE;
DROP TABLE IF EXISTS lease6_pool_stat CASCADE;
DROP FUNCTION IF EXISTS proc_stat_lease6_insert ();
DROP FUNCTION IF EXISTS proc_stat_lease6_update ();
DROP FUNCTION IF EXISTS proc_stat_lease6_delete ();
DROP TABLE IF EXISTS logs CASCADE;

-- config backend procedures for DHCPv6
DROP FUNCTION IF EXISTS createAuditRevisionDHCP6(audit_ts TIMESTAMP WITH TIME ZONE, server_tag VARCHAR(64),
                                                 audit_log_message TEXT, cascade_transaction BOOLEAN);
DROP FUNCTION IF EXISTS createAuditEntryDHCP6(object_type_val VARCHAR(256), object_id_val BIGINT,
                                              modification_type_val VARCHAR(32));
DROP FUNCTION IF EXISTS createOptionAuditDHCP6(modification_type VARCHAR, scope_id SMALLINT,
                                               option_id INT, subnet_id BIGINT, host_id INT,
                                               network_name VARCHAR, pool_id BIGINT, pd_pool_id BIGINT,
                                               modification_ts TIMESTAMP WITH TIME ZONE);
DROP FUNCTION IF EXISTS createOptionAuditDHCP6(modification_type VARCHAR, scope_id SMALLINT,
                                               option_id INT, p_subnet_id BIGINT, host_id INT,
                                               network_name VARCHAR, pool_id BIGINT, pd_pool_id BIGINT,
                                               p_modification_ts TIMESTAMP WITH TIME ZONE);
DROP FUNCTION IF EXISTS setClientClass6Order(id BIGINT, follow_class_name VARCHAR(128),
                                             old_follow_class_name VARCHAR(128));
DROP FUNCTION IF EXISTS checkDHCPv6ClientClassDependency(class_id BIGINT, dependency_id BIGINT);
DROP FUNCTION IF EXISTS updateDHCPv6ClientClassKnownDependency(client_class_id BIGINT,
                                                               dependency_id BIGINT);
DROP FUNCTION IF EXISTS checkDHCPv6ClientClassKnownDependencyChange();

-- config backend tables for DHCPv6
DROP TABLE IF EXISTS dhcp6_audit CASCADE;
DROP TABLE IF EXISTS dhcp6_option_def_server CASCADE;
DROP TABLE IF EXISTS dhcp6_option_def CASCADE;
DROP TABLE IF EXISTS dhcp6_options_server CASCADE;
DROP TABLE IF EXISTS dhcp6_pool CASCADE;
DROP TABLE IF EXISTS dhcp6_pd_pool CASCADE;
DROP TABLE IF EXISTS dhcp6_subnet_server CASCADE;
DROP TABLE IF EXISTS dhcp6_subnet CASCADE;
DROP TABLE IF EXISTS dhcp6_shared_network_server CASCADE;
DROP TABLE IF EXISTS dhcp6_shared_network CASCADE;
DROP TABLE IF EXISTS dhcp6_global_parameter_server CASCADE;
DROP TABLE IF EXISTS dhcp6_global_parameter CASCADE;
DROP TABLE IF EXISTS dhcp6_server CASCADE;
DROP TABLE IF EXISTS dhcp6_audit_revision CASCADE;
DROP TABLE IF EXISTS dhcp6_client_class_server CASCADE;
DROP TABLE IF EXISTS dhcp6_client_class_dependency CASCADE;
DROP TABLE IF EXISTS dhcp6_client_class_order CASCADE;
DROP TABLE IF EXISTS dhcp6_client_class CASCADE;

-- drop trigger functions for DHCPv6
DROP FUNCTION IF EXISTS func_dhcp6_client_class_AINS();
DROP FUNCTION IF EXISTS func_dhcp6_client_class_AUPD();
DROP FUNCTION IF EXISTS func_dhcp6_client_class_ADEL();
DROP FUNCTION IF EXISTS func_dhcp6_client_class_check_dependency_BINS();
DROP FUNCTION IF EXISTS func_dhcp6_client_class_dependency_AINS();
DROP FUNCTION IF EXISTS func_dhcp6_pool_BDEL();
DROP FUNCTION IF EXISTS func_dhcp6_global_parameter_AINS();
DROP FUNCTION IF EXISTS func_dhcp6_global_parameter_AUPD();
DROP FUNCTION IF EXISTS func_dhcp6_global_parameter_ADEL();
DROP FUNCTION IF EXISTS func_dhcp6_subnet_AINS();
DROP FUNCTION IF EXISTS func_dhcp6_subnet_AUPD();
DROP FUNCTION IF EXISTS func_dhcp6_shared_network_AINS();
DROP FUNCTION IF EXISTS func_dhcp6_shared_network_AUPD();
DROP FUNCTION IF EXISTS func_dhcp6_shared_network_ADEL();
DROP FUNCTION IF EXISTS func_dhcp6_option_def_AINS();
DROP FUNCTION IF EXISTS func_dhcp6_option_def_AUPD();
DROP FUNCTION IF EXISTS func_dhcp6_option_def_ADEL();
DROP FUNCTION IF EXISTS func_dhcp6_options_AINS();
DROP FUNCTION IF EXISTS func_dhcp6_options_AUPD();
DROP FUNCTION IF EXISTS func_dhcp6_options_ADEL();
DROP FUNCTION IF EXISTS func_dhcp6_server_AINS();
DROP FUNCTION IF EXISTS func_dhcp6_server_AUPD();
DROP FUNCTION IF EXISTS func_dhcp6_server_ADEL();
DROP FUNCTION IF EXISTS func_dhcp6_shared_network_BDEL();
DROP FUNCTION IF EXISTS func_dhcp6_subnet_BDEL();
DROP FUNCTION IF EXISTS func_dhcp6_pd_pool_BDEL();

-- config backend procedures for DHCPv4
DROP FUNCTION IF EXISTS createAuditRevisionDHCP4(audit_ts TIMESTAMP WITH TIME ZONE, server_tag VARCHAR(64),
                                                 audit_log_message TEXT, cascade_transaction BOOLEAN);
DROP FUNCTION IF EXISTS createAuditEntryDHCP4(object_type_val VARCHAR(256), object_id_val BIGINT,
                                              modification_type_val VARCHAR(32));
DROP FUNCTION IF EXISTS createOptionAuditDHCP4(modification_type VARCHAR, scope_id SMALLINT,
                                               option_id INT, subnet_id BIGINT, host_id INT,
                                               network_name VARCHAR, pool_id BIGINT,
                                               modification_ts TIMESTAMP WITH TIME ZONE);
DROP FUNCTION IF EXISTS setClientClass4Order(id BIGINT, follow_class_name VARCHAR(128),
                                             old_follow_class_name VARCHAR(128));
DROP FUNCTION IF EXISTS checkDHCPv4ClientClassDependency(class_id BIGINT, dependency_id BIGINT);
DROP FUNCTION IF EXISTS updateDHCPv4ClientClassKnownDependency(client_class_id BIGINT,
                                                               dependency_id BIGINT);
DROP FUNCTION IF EXISTS checkDHCPv4ClientClassKnownDependencyChange();

-- config backend tables for DHCPv4
DROP TABLE IF EXISTS dhcp4_audit CASCADE;
DROP TABLE IF EXISTS dhcp4_option_def_server CASCADE;
DROP TABLE IF EXISTS dhcp4_option_def CASCADE;
DROP TABLE IF EXISTS dhcp4_options_server CASCADE;
DROP TABLE IF EXISTS dhcp4_pool CASCADE;
DROP TABLE IF EXISTS dhcp4_pd_pool CASCADE;
DROP TABLE IF EXISTS dhcp4_subnet_server CASCADE;
DROP TABLE IF EXISTS dhcp4_subnet CASCADE;
DROP TABLE IF EXISTS dhcp4_shared_network_server CASCADE;
DROP TABLE IF EXISTS dhcp4_shared_network CASCADE;
DROP TABLE IF EXISTS dhcp4_global_parameter_server CASCADE;
DROP TABLE IF EXISTS dhcp4_global_parameter CASCADE;
DROP TABLE IF EXISTS dhcp4_server CASCADE;
DROP TABLE IF EXISTS dhcp4_audit_revision CASCADE;
DROP TABLE IF EXISTS dhcp4_client_class_server CASCADE;
DROP TABLE IF EXISTS dhcp4_client_class_dependency CASCADE;
DROP TABLE IF EXISTS dhcp4_client_class_order CASCADE;
DROP TABLE IF EXISTS dhcp4_client_class CASCADE;

-- drop trigger functions for DHCPv4
DROP FUNCTION IF EXISTS func_dhcp4_client_class_AINS();
DROP FUNCTION IF EXISTS func_dhcp4_client_class_AUPD();
DROP FUNCTION IF EXISTS func_dhcp4_client_class_ADEL();
DROP FUNCTION IF EXISTS func_dhcp4_client_class_check_dependency_BINS();
DROP FUNCTION IF EXISTS func_dhcp4_client_class_dependency_AINS();
DROP FUNCTION IF EXISTS func_dhcp4_pool_BDEL();
DROP FUNCTION IF EXISTS func_dhcp4_global_parameter_AINS();
DROP FUNCTION IF EXISTS func_dhcp4_global_parameter_AUPD();
DROP FUNCTION IF EXISTS func_dhcp4_global_parameter_ADEL();
DROP FUNCTION IF EXISTS func_dhcp4_subnet_AINS();
DROP FUNCTION IF EXISTS func_dhcp4_subnet_AUPD();
DROP FUNCTION IF EXISTS func_dhcp4_shared_network_AINS();
DROP FUNCTION IF EXISTS func_dhcp4_shared_network_AUPD();
DROP FUNCTION IF EXISTS func_dhcp4_shared_network_ADEL();
DROP FUNCTION IF EXISTS func_dhcp4_option_def_AINS();
DROP FUNCTION IF EXISTS func_dhcp4_option_def_AUPD();
DROP FUNCTION IF EXISTS func_dhcp4_option_def_ADEL();
DROP FUNCTION IF EXISTS func_dhcp4_options_AINS();
DROP FUNCTION IF EXISTS func_dhcp4_options_AUPD();
DROP FUNCTION IF EXISTS func_dhcp4_options_ADEL();
DROP FUNCTION IF EXISTS func_dhcp4_server_AINS();
DROP FUNCTION IF EXISTS func_dhcp4_server_AUPD();
DROP FUNCTION IF EXISTS func_dhcp4_server_ADEL();
DROP FUNCTION IF EXISTS func_dhcp4_shared_network_BDEL();
DROP FUNCTION IF EXISTS func_dhcp4_subnet_BDEL();

-- common tables for config backend
DROP TABLE IF EXISTS modification CASCADE;
DROP TABLE IF EXISTS parameter_data_type CASCADE;
DROP TABLE IF EXISTS ddns_replace_client_name_types CASCADE;
DROP FUNCTION IF EXISTS modification_ts_update();
DROP FUNCTION IF EXISTS get_session_boolean(name text);
DROP FUNCTION IF EXISTS get_session_big_int(name text);
DROP FUNCTION IF EXISTS get_session_value(name text);
DROP FUNCTION IF EXISTS set_session_value(name text, value TEXT);
DROP FUNCTION IF EXISTS set_session_value(name text, value BIGINT);
DROP FUNCTION IF EXISTS set_session_value(name text, value BOOLEAN);

DROP FUNCTION IF EXISTS lease4Upload(address VARCHAR, hwaddr VARCHAR,
    client_id VARCHAR, valid_lifetime BIGINT, expire BIGINT, subnet_id BIGINT,
    fqdn_fwd INT, fqdn_rev INT, hostname VARCHAR, state INT8,
    user_context VARCHAR);
DROP FUNCTION IF EXISTS lease6Upload(address VARCHAR, duid VARCHAR,
    valid_lifetime BIGINT, expire BIGINT, subnet_id BIGINT,
    pref_lifetime BIGINT, lease_type INT, iaid INT, prefix_len INT,
    fqdn_fwd INT, fqdn_rev INT, hostname VARCHAR, hwaddr VARCHAR,
    state INT8, user_context VARCHAR, hwtype INT, hwaddr_source INT);
DROP FUNCTION IF EXISTS colonSeparatedHex(TEXT);

DROP FUNCTION IF EXISTS gmt_epoch(input_time TIMESTAMP WITH TIME ZONE);

-- lease limiting tables and functions
DROP TABLE IF EXISTS lease4_stat_by_client_class;
DROP TABLE IF EXISTS lease6_stat_by_client_class;
DROP FUNCTION IF EXISTS lease4_AINS_lease4_stat(new_state BIGINT,
                                                new_subnet_id BIGINT);
DROP FUNCTION IF EXISTS lease4_AUPD_lease4_stat(old_state BIGINT,
        old_subnet_id BIGINT, new_state BIGINT, new_subnet_id BIGINT);
DROP FUNCTION IF EXISTS lease4_ADEL_lease4_stat(old_state BIGINT,
                                                old_subnet_id BIGINT);
DROP FUNCTION IF EXISTS lease6_AINS_lease6_stat(new_state BIGINT,
        new_subnet_id BIGINT, new_lease_type SMALLINT);
DROP FUNCTION IF EXISTS lease6_AUPD_lease6_stat(old_state BIGINT,
        old_subnet_id BIGINT, old_lease_type SMALLINT, new_state BIGINT,
        new_subnet_id BIGINT, new_lease_type SMALLINT);
DROP FUNCTION IF EXISTS lease6_ADEL_lease6_stat(old_state BIGINT,
        old_subnet_id BIGINT, old_lease_type SMALLINT);
DROP FUNCTION IF EXISTS lease4_AINS_lease4_pool_stat(new_state BIGINT,
        new_subnet_id BIGINT, new_pool_id BIGINT);
DROP FUNCTION IF EXISTS lease4_AUPD_lease4_pool_stat(old_state BIGINT,
        old_subnet_id BIGINT, old_pool_id BIGINT, new_state BIGINT,
        new_subnet_id BIGINT, new_pool_id BIGINT);
DROP FUNCTION IF EXISTS lease4_ADEL_lease4_pool_stat(old_state BIGINT,
        old_subnet_id BIGINT, old_pool_id BIGINT);
DROP FUNCTION IF EXISTS lease6_AINS_lease6_pool_stat(new_state BIGINT,
        new_subnet_id BIGINT, new_pool_id BIGINT, new_lease_type SMALLINT);
DROP FUNCTION IF EXISTS lease6_AUPD_lease6_pool_stat(old_state BIGINT,
        old_subnet_id BIGINT, old_pool_id BIGINT, old_lease_type SMALLINT,
        new_state BIGINT, new_subnet_id BIGINT, new_pool_id BIGINT,
        new_lease_type SMALLINT);
DROP FUNCTION IF EXISTS lease6_ADEL_lease6_pool_stat(old_state BIGINT,
        old_subnet_id BIGINT, old_pool_id BIGINT, old_lease_type SMALLINT);
DROP FUNCTION IF EXISTS lease4_AINS_lease4_stat_by_client_class(
        new_state BIGINT, new_user_context TEXT);
DROP FUNCTION IF EXISTS lease4_AUPD_lease4_stat_by_client_class(
        old_state BIGINT, old_user_context TEXT,
        new_state BIGINT, new_user_context TEXT);
DROP FUNCTION IF EXISTS lease4_ADEL_lease4_stat_by_client_class(
        old_state BIGINT, old_user_context TEXT);
DROP FUNCTION IF EXISTS lease6_AINS_lease6_stat_by_client_class(
        new_state BIGINT, new_user_context TEXT, new_lease_type SMALLINT);
DROP FUNCTION IF EXISTS lease6_AUPD_lease6_stat_by_client_class(
        old_state BIGINT, old_user_context TEXT, old_lease_type SMALLINT,
        new_state BIGINT, new_user_context TEXT, new_lease_type SMALLINT);
DROP FUNCTION IF EXISTS lease6_ADEL_lease6_stat_by_client_class(
        old_state BIGINT, old_user_context TEXT, old_lease_type SMALLINT);
DROP FUNCTION IF EXISTS func_lease4_AINS();
DROP FUNCTION IF EXISTS func_lease4_AUPD();
DROP FUNCTION IF EXISTS func_lease4_ADEL();
DROP FUNCTION IF EXISTS func_lease6_AINS();
DROP FUNCTION IF EXISTS func_lease6_AUPD();
DROP FUNCTION IF EXISTS func_lease6_ADEL();
DROP FUNCTION IF EXISTS checkLease4Limits(user_context TEXT);
DROP FUNCTION IF EXISTS checkLease6Limits(user_context TEXT);
DROP FUNCTION IF EXISTS isJsonSupported();
DROP FUNCTION IF EXISTS json_cast(json_candidate TEXT);

-- v6 BLQ cross-tables
DROP TABLE IF EXISTS lease6_relay_id;
DROP TABLE IF EXISTS lease6_remote_id;
