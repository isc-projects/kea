SUBDIRS = bootp flex_option high_availability lease_cmds perfmon

if HAVE_MYSQL
SUBDIRS += mysql_lb mysql_hb mysql_cb
endif

if HAVE_PGSQL
SUBDIRS += pgsql_lb pgsql_hb pgsql_cb
endif

SUBDIRS += run_script stat_cmds user_chk
