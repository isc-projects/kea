..
   Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.


kea-admin - Shell script for managing Kea databases
---------------------------------------------------

Synopsis
~~~~~~~~

:program:`kea-admin` [command] [backend] [**-h** database_host] [**-P** database_port] [**-u** database_username] [**-p** [database_password]] [**-n** database_name] [**-d** script_directory] [**-v**] [**-4** | **-6**] [**-o** output_file]

Description
~~~~~~~~~~~

``kea-admin`` is a shell script which offers database maintenance. In
particular, it features database initialization, database version
checking, and database schema upgrade.

Arguments
~~~~~~~~~

``command``
   Specifies the command to be issued to the servers. It can be one of the following:

   **db-init**
      Initializes a new database schema. This is useful during a new Kea
      installation. The database is initialized to the latest version
      supported by the version of the software being installed.

   **db-version**
      Reports the database backend version number. This is not necessarily
      equal to the Kea version number as each backend has its own
      versioning scheme.

   **db-upgrade**
      Conducts a database schema upgrade. This is useful when upgrading Kea.

   **lease-dump**
      Dumps the contents of the lease database (for MySQL, PostgreSQL,
      or CQL backends) to a CSV (comma-separated values) text file.
      The first line of the file contains the column names. This is meant
      to be used as a diagnostic tool, so it provides a portable,
      human-readable form of the lease data.

   **stats-recount**
      Recounts lease statistics for MySQL or PostgreSQL database.

``backend``
   Specifies the backend type. Currently allowed backends are: memfile,
   mysql, pgsql, and cql.

``-h|--host hostname``
   Specifies the hostname when connecting to a database. If not specified,
   the default value of **localhost** is used.

``-P|--port port``
   Specifies the port when connecting to a database. If not specified,
   the default value chosen by the database client is used.

``-u|--user username``
   Specifies the username when connecting to a database. If not specified,
   the default value of **keatest** is used.

``-p|--password password``
   Specifies the password when connecting to a database.
   If only ``-p`` or ``--password`` is given, the user is prompted for a password.
   If not specified at all, the **KEA_ADMIN_DB_PASSWORD** environment variable
   is checked for a value and used if it exists.
   Otherwise the default value of **keatest** is used.

``-n|--name database-name``
   Specifies the name of the database to connect to. If not specified, the
   default value of **keatest** is used.

``-d|--directory script-directory``
   Specifies the override scripts directory. That script is used during
   upgrades, database initialization, and possibly other operations. If
   not specified, the default value of ``(prefix)/share/kea/scripts/`` is
   used.

``-o|--output output_file``
   Specifies the file to which the lease data will be dumped. Required for lease-dump.

``-v|--version``
   Prints the ``kea-admin`` version and quits.

``-4``
   Directs ``kea-admin`` to lease-dump the DHCPv4 leases. Incompatible with
   the -6 option.

``-6``
   Directs ``kea-admin`` to lease-dump the DHCPv6 leases. Incompatible with
   the -4 option.

Documentation
~~~~~~~~~~~~~

Kea comes with an extensive Kea Administrator Reference Manual that covers
all aspects of running the Kea software - compilation, installation,
configuration, configuration examples, and much more. Kea also features a
Kea Messages Manual, which lists all possible messages Kea can print
with a brief description for each of them. Both documents are
available in various formats (.txt, .html, .pdf) with the Kea
distribution. The Kea documentation is available at
https://kea.readthedocs.io.

Kea source code is documented in the Kea Developer's Guide. Its online
version is available at https://reports.kea.isc.org/dev_guide/.

The Kea project website is available at https://kea.isc.org.

Mailing Lists and Support
~~~~~~~~~~~~~~~~~~~~~~~~~

There are two public mailing lists available for the Kea project. **kea-users**
(kea-users at lists.isc.org) is intended for Kea users, while **kea-dev**
(kea-dev at lists.isc.org) is intended for Kea developers, prospective
contributors, and other advanced users. Both lists are available at
https://lists.isc.org. The community provides best-effort support
on both of those lists.

ISC provides professional support for Kea services. See
https://www.isc.org/kea/ for details.

See Also
~~~~~~~~

:manpage:`kea-dhcp4(8)`, :manpage:`kea-dhcp6(8)`,
:manpage:`kea-dhcp-ddns(8)`, :manpage:`kea-ctrl-agent(8)`, :manpage:`keactrl(8)`,
:manpage:`perfdhcp(8)`, :manpage:`kea-netconf(8)`, Kea Administrator Reference Manual.
