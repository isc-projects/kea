#!/bin/sh

# Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# This is an utility script that is being included by other scripts.

# There are two ways of calling this method.
# mysql_execute SQL_QUERY - This call is simpler, but requires db_user,
#     db_password and db_name variables to be set.
# mysql_execute SQL_QUERY PARAM1 PARAM2 .. PARAMN - Additional parameters
#     may be specified. They are passed directly to mysql. This one is
#     more convenient to use if the script didn't parse db_user db_password
#     and db_name.
#
# It returns the mysql command exit status to the caller as $?
mysql_execute() {
    QUERY=$1
    shift
    if [ $# -gt 1 ]; then
        mysql -N -B "$@" -e "${QUERY}"
        retcode=$?
    else
        # Shellcheck complains about variables not being set. They're set in the script that calls this script.
        # shellcheck disable=SC2154
        mysql -N -B --host="${db_host}" --database="${db_name}" --user="${db_user}" --password="${db_password}" -e "${QUERY}"
        retcode=$?
    fi

    return $retcode
}

mysql_execute_script() {
    file=$1
    shift
    if [ $# -ge 1 ]; then
        mysql -N -B "$@" < "${file}"
        retcode=$?
    else
        mysql -N -B --host="${db_host}" --database="${db_name}" --user="${db_user}" --password="${db_password}" < "${file}"
        retcode=$?
    fi

    return $retcode
}

mysql_version() {
    mysql_execute "SELECT CONCAT_WS('.', version, minor) FROM schema_version" "$@"
    return $?
}

# Submits given SQL text to PostgreSQL
# There are two ways of calling this method.
# pgsql_execute SQL_QUERY - This call is simpler, but requires db_user,
#     db_password and db_name variables to be set.
# pgsql_execute SQL_QUERY PARAM1 PARAM2 .. PARAMN - Additional parameters
#     may be specified. They are passed directly to pgsql. This one is
#     more convenient to use if the script didn't parse db_user db_password
#     and db_name.
#
# It returns the pgsql command exit status to the caller as $?
pgsql_execute() {
    QUERY=$1
    shift
    if [ $# -gt 0 ]; then
        echo "${QUERY}" | psql --set ON_ERROR_STOP=1 -A -t -h "${db_host}" -q "$@"
        retcode=$?
    else
        export PGPASSWORD=$db_password
        echo "${QUERY}" | psql --set ON_ERROR_STOP=1 -A -t -h "${db_host}" -q -U "${db_user}" -d "${db_name}"
        retcode=$?
    fi
    return $retcode
}

# Submits SQL in a given file to PostgreSQL
# There are two ways of calling this method.
# pgsql_execute SQL_FILE - This call is simpler, but requires db_user,
#     db_password and db_name variables to be set.
# pgsql_execute SQL_FILE PARAM1 PARAM2 .. PARAMN - Additional parameters
#     may be specified. They are passed directly to pgsql. This one is
#     more convenient to use if the script didn't parse db_user db_password
#     and db_name.
#
# It returns the pgsql command exit status to the caller as $?
pgsql_execute_script() {
    file=$1
    shift
    if [ $# -gt 0 ]; then
        psql --set ON_ERROR_STOP=1 -A -t -h "${db_host}" -q -f "${file}" "$@"
        retcode=$?
    else
        export PGPASSWORD=$db_password
        psql --set ON_ERROR_STOP=1 -A -t -h "${db_host}" -q -U "${db_user}" -d "${db_name}" -f "${file}"
        retcode=$?
    fi
    return $retcode
}

pgsql_version() {
    pgsql_execute "SELECT version || '.' || minor FROM schema_version" "$@"
    return $?
}

cql_execute() {
    query=$1
    shift
    if [ $# -gt 1 ]; then
        cqlsh "$@" -e "$query"
        retcode=$?
    else
        cqlsh -u "${db_user}" -p "${db_password}" -k "${db_name}" -e "${query}"
        retcode=$?
    fi

    if [ $retcode -ne 0 ]; then
        printf "cqlsh returned with exit status %s\n" "${retcode}"
        exit $retcode
    fi

    return $retcode
}

cql_execute_script() {
    file=$1
    shift
    if [ $# -gt 1 ]; then
        cqlsh "$@" -e "$file"
        retcode=$?
    else
        cqlsh -u "${db_user}" -p "${db_password}" -k "${db_name}" -f "${file}"
        retcode=$?
    fi

    if [ $retcode -ne 0 ]; then
        printf "cqlsh returned with exit status %s\n" "${retcode}"
        exit $retcode
    fi

    return $retcode
}

cql_version() {
    version=$(cql_execute "SELECT version, minor FROM schema_version" "$@")
    error=$?
    version=$(echo "$version" | grep -A 1 "+" | grep -v "+" | tr -d ' ' | cut -d "|" -f 1-2 | tr "|" ".")
    echo "$version"
    return $error
}
