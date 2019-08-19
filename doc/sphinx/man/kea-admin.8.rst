..
   Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.


kea-admin - Shell script for managing Kea databases
---------------------------------------------------

Synopsis
~~~~~~~~

:program:`kea-admin` [command] [backend] [**-u** database username] [**-p** database password] [**-n** database name] [**-d** scripts directory] [**-4** | **-6**] [**-o** output file] [**-v**]

Description
~~~~~~~~~~~

``kea-admin`` is a shell script which offers database maintenance. In
particular, it features database initialization, database version
checking, and database schema upgrade.

Arguments
~~~~~~~~~

``command``
   Specifies the command to be issued to the servers. It can be one of the following:

   **lease-init**
      Initializes a new lease database, which is useful during the first Kea
      installation. The database is initialized to the latest version
      supported by the version of the software.

   **lease-version**
      Reports the lease database version. This is not necessarily the same as the
      Kea version, as each backend has its own versioning scheme.

   **lease-upgrade**
      Conducts a lease database upgrade. This is useful when migrating
      between old and new Kea versions.

   **lease-dump**
      Dumps the contents of the lease database (MySQL and PostgreSQL
      backends) to a text file. The content of the file consists of
      comma-separated values (CSV) where each line in the file contains
      all of the values for a single lease. The first line of the file is a
      header line containing the column names.

``backend``
   Specifies the backend type. Currently allowed backends are: memfile,
   mysql, and pgsql.

``-u|--user username``
   Specifies the username when connecting to a database. If not specified,
   the default value of **keatest** is used.

``-p|--password password``
   Specifies the password when connecting to a database. If not
   specified, the default value of **keatest** is used.

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
https://kb.isc.org/docs/kea-administrator-reference-manual .

Kea source code is documented in the Kea Developer's Guide. Its online
version is available at https://jenkins.isc.org/job/Kea_doc/doxygen/.

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
