# Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

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
    if [ $# -gt 1 ]; then
        QUERY="$1"
        shift
        mysql -N -B  $* -e "${QUERY}"
        retcode=$?
    else
        mysql -N -B --user=$db_user --password=$db_password -e "${1}" $db_name
        retcode="$?"
    fi

    return $retcode
}

mysql_version() {
    mysql_execute "SELECT CONCAT(version,\".\",minor) FROM schema_version" "$@"
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
        echo $QUERY | psql --set ON_ERROR_STOP=1 -A -t -q $*
        retcode=$?
    else
        export PGPASSWORD=$db_password
        echo $QUERY | psql --set ON_ERROR_STOP=1 -A -t -q -U $db_user -d $db_name
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
        psql --set ON_ERROR_STOP=1 -A -t -q -f $file $*
        retcode=$?
    else
        export PGPASSWORD=$db_password
        psql --set ON_ERROR_STOP=1 -A -t -q -U $db_user -d $db_name -f $file
        retcode=$?
    fi
    return $retcode
}


pgsql_version() {
    pgsql_execute "SELECT version || '.' || minor FROM schema_version" "$@"
    return $?
}
