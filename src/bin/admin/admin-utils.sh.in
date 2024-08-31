#!/bin/sh

# Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# This is an utility script that is being included by other scripts.

# shellcheck disable=SC2086
# SC2086: Double quote to prevent globbing and word splitting.
# Reason for disable: explicitly don't quote db_port_full_parameter so it
# doesn't expand to empty string if it is not set and explicitly don't quote
# extra_arguments so it is considered multiple arguments instead of one.

# shellcheck disable=SC2154
# SC2154: ... is referenced but not assigned.
# Some variables are assigned in kea-admin.

# Exit with error if commands exit with non-zero and if undefined variables are
# used.
set -eu

# These are the default parameters. They will likely not work in any
# specific deployment. Also used in unit tests.
db_host='localhost'
db_user='keatest'
db_password='keatest'
db_name='keatest'
extra_arguments=

# Runs all the given arguments as a single command. Maintains quoting. Places
# output in ${OUTPUT} and exit code in ${EXIT_CODE}. Does not support pipes and
# redirections. Support for them could be added through eval and single
# parameter assignment, but eval is not recommended.
run_command() {
    if test -n "${DEBUG+x}"; then
        printf '%s\n' "${*}" >&2
    fi
    set +e
    OUTPUT=$("${@}")
    EXIT_CODE=${?}
    set -e
}

mysql_sanity_checks() {
    # https://bugs.mysql.com/bug.php?id=55796#c321360
    # https://dev.mysql.com/doc/refman/8.0/en/connecting.html
    # On Unix, MySQL programs treat the host name localhost specially, in a way
    # that is likely different from what you expect compared to other
    # network-based programs: the client connects using a Unix socket file.
    if test -n "${db_port+x}" && \
        { test "${db_host}" = 'localhost' || \
          test "${db_host}" = '127.0.0.1'; }; then
        printf 'Warning: the MySQL client uses the default unix socket ' >&2
        printf 'instead of TCP port %s ' "${db_port}" >&2
        printf 'when connecting to localhost. Continuing...\n' >&2
    fi
}

# Executes a given MySQL statement.
# mysql_execute SQL_QUERY PARAM1 PARAM2 .. PARAMN - Additional parameters
#     may be specified. They are passed directly to mysql.
#
# It returns the mysql command exit status to the caller as $?
mysql_execute() {
    QUERY=$1
    shift

    mysql_sanity_checks

    if [ $# -gt 0 ]; then
        mysql -N -B --host="${db_host}" ${db_port_full_parameter-} \
        --database="${db_name}" --user="${db_user}" \
        --password="${db_password}" ${extra_arguments} \
        --execute "${QUERY}" "${@}"
    else
        mysql -N -B --host="${db_host}" ${db_port_full_parameter-} \
        --database="${db_name}" --user="${db_user}" \
        --password="${db_password}" ${extra_arguments} \
        --execute "${QUERY}"
    fi
}

# Submits SQL in a given file to MySQL.
# pgsql_execute SQL_FILE PARAM1 PARAM2 .. PARAMN - Additional parameters
#     may be specified. They are passed directly to pgsql.
#
# It returns the mysql command exit status to the caller as $?
mysql_execute_script() {
    file=$1
    shift

    mysql_sanity_checks

    if [ $# -gt 0 ]; then
        mysql -N -B --host="${db_host}" ${db_port_full_parameter-} \
        --database="${db_name}" --user="${db_user}" \
        --password="${db_password}" ${extra_arguments} "${@}" < "${file}"
    else
        mysql -N -B --host="${db_host}" ${db_port_full_parameter-} \
        --database="${db_name}" --user="${db_user}" \
        --password="${db_password}" ${extra_arguments} < "${file}"
    fi
}

mysql_version() {
    mysql_execute "SELECT CONCAT_WS('.', version, minor) FROM schema_version" "$@"
}

checked_mysql_version() {
    run_command \
        mysql_execute "SELECT CONCAT_WS('.', version, minor) FROM schema_version" "$@"

    if [ "${EXIT_CODE}" -ne 0 ]
    then
        printf "Failed to get schema version, mysql status  %s\n" "${EXIT_CODE}"
    fi

    printf '%s\n' "${OUTPUT}"
    return "${EXIT_CODE}"
}

# Submits given SQL text to PostgreSQL
# pgsql_execute SQL_QUERY PARAM1 PARAM2 .. PARAMN - Additional parameters
#     may be specified. They are passed directly to pgsql.
#
# It returns the pgsql command exit status to the caller as $?
pgsql_execute() {
    QUERY=$1
    shift

    # Prioritize externally set PGPASSWORD. wipe_data.sh sets it for example.
    if test -z "${PGPASSWORD-}"; then
        PGPASSWORD="${db_password}"
    fi
    export PGPASSWORD

    if [ $# -gt 0 ]; then
        printf '%s' "${QUERY}" | psql --set ON_ERROR_STOP=1 -A -t \
        -h "${db_host}" ${db_port_full_parameter-} -q -U "${db_user}" \
        -d "${db_name}" ${extra_arguments} "${@}"
    else
        printf '%s' "${QUERY}" | psql --set ON_ERROR_STOP=1 -A -t \
        -h "${db_host}" ${db_port_full_parameter-} -q -U "${db_user}" \
        -d "${db_name}" ${extra_arguments}
    fi
}

# Submits SQL in a given file to PostgreSQL
# pgsql_execute SQL_FILE PARAM1 PARAM2 .. PARAMN - Additional parameters
#     may be specified. They are passed directly to pgsql.
#
# It returns the pgsql command exit status to the caller as $?
pgsql_execute_script() {
    file=$1
    shift

    # Prioritize externally set PGPASSWORD. wipe_data.sh sets it for example.
    if test -z "${PGPASSWORD-}"; then
        PGPASSWORD="${db_password}"
    fi
    export PGPASSWORD

    if [ $# -gt 0 ]; then
        psql --set ON_ERROR_STOP=1 -A -t -h "${db_host}" \
        ${db_port_full_parameter-} -q -U "${db_user}" -d "${db_name}" \
        ${extra_arguments} -f "${file}" "${@}"
    else
        psql --set ON_ERROR_STOP=1 -A -t -h "${db_host}" \
        ${db_port_full_parameter-} -q -U "${db_user}" -d "${db_name}" \
        ${extra_arguments} -f "${file}"
    fi
}

pgsql_version() {
    pgsql_execute "SELECT version || '.' || minor FROM schema_version" "$@"
}

checked_pgsql_version() {
    run_command \
        pgsql_execute "SELECT version || '.' || minor FROM schema_version" "$@"

    if [ "${EXIT_CODE}" -ne 0 ]
    then
        printf "Failed to get schema version, pgsql status %s\n" "${EXIT_CODE}"
    fi

    printf '%s\n' "${OUTPUT}"
    return "${EXIT_CODE}"
}

# recount IPv4 leases from scratch
_RECOUNT4_QUERY=\
"
START TRANSACTION; \
DELETE FROM lease4_stat; \
INSERT INTO lease4_stat (subnet_id, state, leases) \
    SELECT subnet_id, state, COUNT(*) \
    FROM lease4 WHERE state = 0 OR state = 1 \
    GROUP BY subnet_id, state; \
DELETE FROM lease4_pool_stat; \
INSERT INTO lease4_pool_stat (subnet_id, pool_id, state, leases) \
    SELECT subnet_id, pool_id, state, count(*) FROM lease4 \
    WHERE state = 0 OR state = 1 GROUP BY subnet_id, pool_id, state; \
COMMIT;"
export _RECOUNT4_QUERY

# recount IPv6 leases from scratch
_RECOUNT6_QUERY=\
"
START TRANSACTION; \
DELETE FROM lease6_stat; \
INSERT INTO lease6_stat (subnet_id, lease_type, state, leases) \
    SELECT subnet_id, lease_type, state, COUNT(*) \
    FROM lease6 WHERE state = 0 OR state = 1 \
    GROUP BY subnet_id, lease_type, state; \
DELETE FROM lease6_pool_stat; \
INSERT INTO lease6_pool_stat (subnet_id, pool_id, lease_type, state, leases) \
    SELECT subnet_id, pool_id, lease_type, state, count(*) FROM lease6 \
    WHERE state = 0 OR state = 1 GROUP BY subnet_id, pool_id, lease_type, state; \
COMMIT;"
export _RECOUNT6_QUERY
