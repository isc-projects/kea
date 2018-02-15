# Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
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
    if [ $# -gt 0 ]; then
        cmdline=$(mysql_compose_connect_cmd_line)
        cmdline="$cmdline $* -e \"$QUERY\""
        eval "mysql " $cmdline
        retcode=$?
    else
        cmdline=$(mysql_compose_connect_cmd_line)
        cmdline="$cmdline -e \"$QUERY\" $db_name"
        eval "mysql " $cmdline
        retcode="$?"
    fi

    return $retcode
}

mysql_execute_no_dbname() {
    QUERY=$1
    shift

    cmdline=$(mysql_compose_connect_cmd_line)
    cmdline="$cmdline -e \"$QUERY\""

    eval "mysql " $cmdline
    retcode="$?"

    if [ $retcode -ne 0 ]; then
        printf "mysql returned with exit status $retcode\n"
        exit $retcode
    fi

    return $retcode
}

mysql_execute_script() {
    file=$1
    shift
    if [ $# -gt 0 ]; then
        cmdline=$(mysql_compose_connect_cmd_line)
        eval "mysql " $cmdline $* < ${file}
        retcode=$?
    else
        cmdline=$(mysql_compose_connect_cmd_line)
        eval "mysql "$cmdline $db_name < ${file}
        retcode="$?"
    fi

    return $retcode
}

mysql_version() {
    mysql_execute "SELECT CONCAT_WS('.', version, minor) FROM schema_version;" "$@"
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
        export PGPASSWORD=$db_password
        cmdline=$(pgsql_compose_connect_cmd_line)
        cmdline="$cmdline $*"
        echo $QUERY | psql $cmdline
        retcode=$?
    else
        export PGPASSWORD=$db_password
        cmdline=$(pgsql_compose_connect_cmd_line)
        cmdline="$cmdline -d $db_name"
        echo $QUERY | psql $cmdline
        retcode=$?
    fi
    return $retcode
}

pgsql_execute_no_dbname() {
    QUERY=$1
    shift
    export PGPASSWORD=$db_password
    cmdline=$(pgsql_compose_connect_cmd_line)
#   Sometimes we don't need to connect to a specific database
#   (e.g. when we want to create a new one)
#   Postgresql client requires to connect all the time a database.
#   The first database is always created by the initdb command when
#   the data storage area is initialized is called postgres.
#   So we will connect to the default database "postgres")
    cmdline="$cmdline -d postgres"
    echo $QUERY | psql $cmdline
    retcode=$?
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
        export PGPASSWORD=$db_password
        cmdline=$(pgsql_compose_connect_cmd_line)
        cmdline="$cmdline -d $db_name -f $file $*"
        eval "psql "$cmdline
        retcode=$?
    else
        export PGPASSWORD=$db_password
        cmdline=$(pgsql_compose_connect_cmd_line)
        cmdline="$cmdline -d $db_name -f $file"
        eval "psql "$cmdline
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
    if [ $# -gt 0 ]; then
        cmdline=$(cql_compose_connect_cmd_line)
        cmdline="$cmdline $* -e \"$query\""
        eval "cqlsh " $cmdline
        retcode=$?
    else
        cmdline=$(cql_compose_connect_cmd_line)
        cmdline="$cmdline -k $db_name -e \"$query\""
        eval "cqlsh " $cmdline
        retcode=$?
    fi

    if [ $retcode -ne 0 ]; then
        printf "cqlsh returned with exit status %s\n" "${retcode}"
        exit $retcode
    fi

    return $retcode
}

cql_execute_no_keyspace() {
    query=$1
    shift

    cmdline=$(cql_compose_connect_cmd_line)
    cmdline="$cmdline -e \"$query\""
    eval "cqlsh " $cmdline
    retcode=$?

    if [ $retcode -ne 0 ]; then
        printf "cqlsh returned with exit status $retcode\n"
        exit $retcode
    fi

    return $retcode
}

cql_execute_script() {
    file=$1
    shift
    if [ $# -gt 0 ]; then
        cmdline=$(cql_compose_connect_cmd_line)
        cmdline="$cmdline $* -f \"$file\""
        eval "cqlsh " $cmdline
        retcode=$?
    else
        cmdline=$(cql_compose_connect_cmd_line)
        cmdline="$cmdline -k $db_name -f \"$file\""
        eval "cqlsh " $cmdline
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
    echo $version
    return $error
}

mysql_compose_connect_cmd_line() {
    local line="-N -B"

    if [ -n "$db_server_address" ]; then
        line="$line --host=$db_server_address"
    fi

    if [ -n "$db_server_port" ]; then
        line="$line --port=$db_server_port"
    fi

    if [ -n "$db_user" ]; then
        line="$line --user=$db_user"
    fi

    if [ -n "$db_password" ]; then
        line="$line --password=$db_password"
    fi

    if [ -n "$db_host" ]; then
        line="$line --host=$db_host"
    fi

    echo $line
}

pgsql_compose_connect_cmd_line() {
    local line="--set ON_ERROR_STOP=1 -A -t -q"

    if [ -n "$db_server_address" ]
    then
        line="$line -h $db_server_address"
    else
        if [ -n "$db_host" ]; then
            line="$line -h $db_host"
        else
            line="$line -h localhost"
        fi
    fi

    if [ -n "$db_server_port" ]; then
        line="$line -p $db_server_port"
    fi

    if [ -n "$db_user" ]; then
        line="$line -U $db_user"
    fi

    if [ -n "$db_host" ]; then
        line="$line -h $db_host"
    fi

    echo $line
}

cql_compose_connect_cmd_line() {
    local line=""

    if [ -n "$db_server_address" ]; then
        line=$line" "$db_server_address
    fi

    if [ -n "$db_server_port" ]; then
        line=$line" "$db_server_port
    fi

    if [ -n "$db_server_version" ]; then
        line=$line" --cqlversion="$db_server_version
    fi

    if [ -n "$db_user" ]; then
        line=$line" -u "$db_user
    fi

    if [ -n "$db_password" ]; then
        line=$line" -p "$db_password
    fi

    if [ -n "$db_use_ssl" ]; then
        line=$line" --ssl"
    fi

    echo $line
}
