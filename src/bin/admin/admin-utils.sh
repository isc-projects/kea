#!/bin/sh

# There are two ways of calling this method.
# mysql_execute SQL_QUERY - This call is simpler, but requires db_user,
#     db_password and db_name variables to be bet.
# mysql_execute SQL_QUERY PARAM1 PARAM2 .. PARAMN - Additional parameters
#     may be specified. They are passed directly to mysql. This one is
#     more convenient to use if the script didn't parse db_user db_password
#     and db_name.
mysql_execute() {
    if [ $# -gt 1 ]; then
        QUERY=$1
        shift
        _RESULT=`echo $QUERY | mysql -N -B $@ | sed "s/\t/./g"`
    else
        _RESULT=`mysql -N -B --user=$db_user --password=$db_password -e "${1}" $db_name | sed "s/\t/./g"`
    fi
}

mysql_version() {
    mysql_execute "SELECT version,minor FROM schema_version" "$@"
}

mysql_version_print() {
    mysql_version "$@"
    printf "%s" $_RESULT
}