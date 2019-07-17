kea-admin
8
Kea
kea-admin
Shell script for managing Kea databases
2014-2018
Internet Systems Consortium, Inc. ("ISC")
kea-admin
command
backend
-u
database username
-p
database password
-n
database name
-d
scripts directory
-4 \| -6
-o
output file
-v
DESCRIPTION
===========

kea-admin is a shell script which offers database maintenance. In
particular, it features database initialization, database version
checking and database schema upgrade.

OPTIONS
=======

``command``
   Command to be issued to the servers. It can be one of the following:

   lease-init
      Initializes a new lease database. Useful during first Kea
      installation. The database is initialized to the latest version
      supported by the version of the software.

   lease-version
      Reports lease database version. This is not necessarily equal to
      Kea version as each backend has its own versioning scheme.

   lease-upgrade
      Conducts lease database upgrade. This is useful when migrating
      between old and new Kea versions.

   lease-dump
      Dumps the contents of the lease database (MySQL and PostgreSQL
      backends) to text file. The content of the file consists of
      comma-separated-values (CSV) where each line in the file contains
      all of the values for a single lease. The first line of file is a
      header line containing the column names.

``backend``
   Specifies backend type. Currently allowed backends are: memfile,
   mysql and pgsql.

``-u|--user username``
   Specify the username when connecting to a database. If not specified,
   the default value of keatest is used.

``-p|--password password``
   Specifies the password when connecting to a database. If not
   specified, the default value of keatest is used.

``-n|--name database-name``
   Specifies the database name to connect to. If not specified, the
   default value of keatest is used.

``-d|--directory script-directory``
   Used for override scripts directory. That script is used during
   upgrades, database initialization and possibly other operations. If
   not specified, the default value of (prefix)/share/kea/scripts/ is
   used.

``-o|--output output_file``
   Required for lease-dump, Specifies the file to which the lease data
   will be dumped.

``-v|--version``
   Prints kea-admin version and quits.

``-4``
   Directs kea-admin to lease-dump the DHCPv4 leases. Incompatible with
   the -6 option.

``-6``
   Directs kea-admin to lease-dump the DHCPv6 leases. Incompatible with
   the -4 option.

SEE ALSO
========

keactrl 8, kea-dhcp4 8, kea-dhcp6 8, kea-dhcp-ddns 8, kea-ctrl-agent 8,
kea-netconf 8, keactrl 8, perfdhcp 8, Kea Administrator Guide.
