#!/bin/sh

# Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Get the list of generated files.

# Usage:
#
# ./tools/print-generated-files.sh

# Exit with error if commands exit with non-zero and if undefined variables are
# used.
set -eu

# If run from premium, it lacks the premium prefix.
for prefix in '' 'premium/'; do
    for path in \
        'src/hooks/dhcp/cb_cmds/cb_cmds_messages.cc' \
        'src/hooks/dhcp/cb_cmds/cb_cmds_messages.h' \
        'src/hooks/dhcp/rbac/rbac_messages.cc' \
        'src/hooks/dhcp/rbac/rbac_messages.h' \
    ; do
        file="${prefix}${path}"
        if test -f "${file}"; then
            echo "${file}"
        fi
    done
done

printf "\
src/bin/agent/agent_lexer.cc
src/bin/agent/agent_parser.cc
src/bin/agent/agent_parser.h
src/bin/agent/ca_messages.cc
src/bin/agent/ca_messages.h
src/bin/agent/location.hh
src/bin/d2/d2_lexer.cc
src/bin/d2/d2_parser.cc
src/bin/d2/d2_parser.h
src/bin/d2/location.hh
src/bin/dhcp4/dhcp4_lexer.cc
src/bin/dhcp4/dhcp4_messages.cc
src/bin/dhcp4/dhcp4_messages.h
src/bin/dhcp4/dhcp4_parser.cc
src/bin/dhcp4/dhcp4_parser.h
src/bin/dhcp4/location.hh
src/bin/dhcp6/dhcp6_lexer.cc
src/bin/dhcp6/dhcp6_messages.cc
src/bin/dhcp6/dhcp6_messages.h
src/bin/dhcp6/dhcp6_parser.cc
src/bin/dhcp6/dhcp6_parser.h
src/bin/dhcp6/location.hh
src/bin/lfc/lfc_messages.cc
src/bin/lfc/lfc_messages.h
src/bin/netconf/location.hh
src/bin/netconf/netconf_lexer.cc
src/bin/netconf/netconf_messages.cc
src/bin/netconf/netconf_messages.h
src/bin/netconf/netconf_parser.cc
src/bin/netconf/netconf_parser.h
src/hooks/d2/gss_tsig/gss_tsig_messages.cc
src/hooks/d2/gss_tsig/gss_tsig_messages.h
src/hooks/dhcp/bootp/bootp_messages.cc
src/hooks/dhcp/bootp/bootp_messages.h
src/hooks/dhcp/class_cmds/class_cmds_messages.cc
src/hooks/dhcp/class_cmds/class_cmds_messages.h
src/hooks/dhcp/ddns_tuning/ddns_tuning_messages.cc
src/hooks/dhcp/ddns_tuning/ddns_tuning_messages.h
src/hooks/dhcp/flex_id/flex_id_messages.cc
src/hooks/dhcp/flex_id/flex_id_messages.h
src/hooks/dhcp/flex_option/flex_option_messages.cc
src/hooks/dhcp/flex_option/flex_option_messages.h
src/hooks/dhcp/forensic_log/legal_log_messages.cc
src/hooks/dhcp/forensic_log/legal_log_messages.h
src/hooks/dhcp/high_availability/ha_messages.cc
src/hooks/dhcp/high_availability/ha_messages.h
src/hooks/dhcp/host_cache/host_cache_messages.cc
src/hooks/dhcp/host_cache/host_cache_messages.h
src/hooks/dhcp/host_cmds/host_cmds_messages.cc
src/hooks/dhcp/host_cmds/host_cmds_messages.h
src/hooks/dhcp/lease_cmds/lease_cmds_messages.cc
src/hooks/dhcp/lease_cmds/lease_cmds_messages.h
src/hooks/dhcp/lease_query/lease_query_messages.cc
src/hooks/dhcp/lease_query/lease_query_messages.h
src/hooks/dhcp/limits/limits_messages.cc
src/hooks/dhcp/limits/limits_messages.h
src/hooks/dhcp/mysql/mysql_cb_messages.cc
src/hooks/dhcp/mysql/mysql_cb_messages.h
src/hooks/dhcp/mysql/mysql_fb_messages.cc
src/hooks/dhcp/mysql/mysql_fb_messages.h
src/hooks/dhcp/mysql/mysql_hb_messages.cc
src/hooks/dhcp/mysql/mysql_hb_messages.h
src/hooks/dhcp/mysql/mysql_lb_messages.cc
src/hooks/dhcp/mysql/mysql_lb_messages.h
src/hooks/dhcp/perfmon/perfmon_messages.cc
src/hooks/dhcp/perfmon/perfmon_messages.h
src/hooks/dhcp/pgsql/pgsql_cb_messages.cc
src/hooks/dhcp/pgsql/pgsql_cb_messages.h
src/hooks/dhcp/pgsql/pgsql_fb_messages.cc
src/hooks/dhcp/pgsql/pgsql_fb_messages.h
src/hooks/dhcp/pgsql/pgsql_hb_messages.cc
src/hooks/dhcp/pgsql/pgsql_hb_messages.h
src/hooks/dhcp/pgsql/pgsql_lb_messages.cc
src/hooks/dhcp/pgsql/pgsql_lb_messages.h
src/hooks/dhcp/ping_check/ping_check_messages.cc
src/hooks/dhcp/ping_check/ping_check_messages.h
src/hooks/dhcp/radius/radius_messages.cc
src/hooks/dhcp/radius/radius_messages.h
src/hooks/dhcp/run_script/run_script_messages.cc
src/hooks/dhcp/run_script/run_script_messages.h
src/hooks/dhcp/stat_cmds/stat_cmds_messages.cc
src/hooks/dhcp/stat_cmds/stat_cmds_messages.h
src/hooks/dhcp/subnet_cmds/subnet_cmds_messages.cc
src/hooks/dhcp/subnet_cmds/subnet_cmds_messages.h
src/hooks/dhcp/user_chk/user_chk_messages.cc
src/hooks/dhcp/user_chk/user_chk_messages.h
src/lib/asiodns/asiodns_messages.cc
src/lib/asiodns/asiodns_messages.h
src/lib/config/config_messages.cc
src/lib/config/config_messages.h
src/lib/d2srv/d2_messages.cc
src/lib/d2srv/d2_messages.h
src/lib/database/db_messages.cc
src/lib/database/db_messages.h
src/lib/dhcp/dhcp_messages.cc
src/lib/dhcp/dhcp_messages.h
src/lib/dhcp_ddns/dhcp_ddns_messages.cc
src/lib/dhcp_ddns/dhcp_ddns_messages.h
src/lib/dhcpsrv/alloc_engine_messages.cc
src/lib/dhcpsrv/alloc_engine_messages.h
src/lib/dhcpsrv/dhcpsrv_messages.cc
src/lib/dhcpsrv/dhcpsrv_messages.h
src/lib/dhcpsrv/fuzz_messages.cc
src/lib/dhcpsrv/fuzz_messages.h
src/lib/dhcpsrv/hosts_messages.cc
src/lib/dhcpsrv/hosts_messages.h
src/lib/eval/eval_messages.cc
src/lib/eval/eval_messages.h
src/lib/eval/lexer.cc
src/lib/eval/location.hh
src/lib/eval/parser.cc
src/lib/eval/parser.h
src/lib/hooks/hooks_messages.cc
src/lib/hooks/hooks_messages.h
src/lib/http/auth_messages.cc
src/lib/http/auth_messages.h
src/lib/http/http_messages.cc
src/lib/http/http_messages.h
src/lib/log/logimpl_messages.cc
src/lib/log/logimpl_messages.h
src/lib/log/log_messages.cc
src/lib/log/log_messages.h
src/lib/log/tests/log_test_messages.cc
src/lib/log/tests/log_test_messages.h
src/lib/process/process_messages.cc
src/lib/process/process_messages.h
src/lib/tcp/tcp_messages.cc
src/lib/tcp/tcp_messages.h
"
