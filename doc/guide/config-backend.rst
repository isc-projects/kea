.. _config-backend:

Kea Configuration Backend
=========================

.. _cb-applicability:

Applicability
-------------

Kea Configuration Backend (abbreviated as CB) is a feature first
introduced in the 1.6.0 release, which provides Kea servers with the ability
to manage and fetch their configuration from one or more databases. In
the documentation, the term "Configuration Backend" may also refer to
the particular Kea module providing support to manage and fetch the
configuration information from the particular database type. For
example: MySQL Configuration Backend is the logic implemented within the
"mysql_cb" hooks library which provides a complete set of functions to
manage and fetch the configuration information from the MySQL database.

In small deployments, e.g. those comprising a single DHCP server
instance with limited and infrequently changing number of subnets, it
may be impractical to use the CB as a configuration repository because
it requires additional third-party software to be installed and
configured - in particular the MySQL server and MySQL client. Once the
number of DHCP servers and/or the number of managed subnets in the
network grows, the usefulness of the CB becomes obvious.

A good example of a use case for the CB is a pair of Kea DHCP servers which can be configured
to support High Availability as described in
:ref:`ha: High Availability <high-availability-library>`. The configurations of both servers
are almost exactly the same. They may differ by the server identifier
and designation of the server as a primary or standby (or secondary).
They may also differ by the interfaces configuration. Typically, the
subnets, shared networks, option definitions, global parameters are the
same for both servers and can be sourced from a single database instance
to both Kea servers.

Using the database as a single source of configuration for subnets
and/or other configuration information supported by the CB has the
advantage that any modifications to the configuration in the database are
automatically applied to both servers.

Another case when the centralized configuration repository is desired is
in deployments including a large number of DHCP servers, possibly
using a common lease database to provide redundancy. New servers can
be added to the pool frequently to fulfill growing scalability
requirements. Adding a new server does not require replicating the
entire configuration to the new server when a common database is used.

Using the database as a configuration repository for Kea servers also
brings other benefits, such as:

-  the ability to use database specific tools to access the configuration
   information,

-  the ability to create customized statistics based on the information
   stored in the database, and

-  the ability to backup the configuration information using the database's
   built-in replication mechanisms.

.. _cb-limitations:

CB Capabilities and Limitations
-------------------------------

Kea CB, introduced in the 1.6.0 release,
comes with a number of limitations as a result of the overall
complexity of this feature and the development time constraints. This
feature will evolve over time and the new capabilities will be added in
subsequent releases. In this section we present the capabilities and limitations of the
CB in the current Kea 1.6.0 release:

-  Kea CB is supported for the MySQL database only.

-  Kea CB is only supported for DHCPv4 and DHCPv6 servers. Neither the
   Control Agent nor the D2 daemon can be configured via the database.

-  Potential configurations to be stored for the DHCP servers include: global
   parameters, option definitions, global options, shared networks, and
   subnets. Other configuration parameters are not stored in the
   database and must be configured via the JSON
   configuration file.

-  Different configurations of multiple DHCP
   servers cannot be stored within the same database; all servers connected to the
   particular database instance share the configuration stored in this
   database. This limitation is expected to be removed in the Kea 1.6.0 final release.

..

   **Note**

   We strongly recommend against duplication of the configuration information
   in the file and the database. For example, when specifying subnets
   for the DHCP server, please store them in either the configuration backend
   or in the configuration file, not both. Storing some
   subnets in the database and others in the file may put you at risk of
   potential configuration conflicts. Note that the configuration instructions from
   the database take precedence over instructions from the file,
   so it is possible that parts of the configuration specified in the
   file may be overridden if contradicted by information in the database.

   **Note**

   It is recommended that the ``subnet_cmds`` hooks library not be used to
   manage the subnets when the configuration backend is used as a source
   of information about the subnets. The ``subnet_cmds`` hooks library
   modifies the local subnets configuration in the server's memory,
   not in the database. Use the ``cb_cmds`` hooks library to manage the
   subnets information in the database instead.

CB Components
-------------

In order to use the Kea CB feature, the Kea 1.6.0 version or later is
required. The ``mysql_cb`` open source hooks library implementing the
Configuration Backend for MySQL must be compiled and loaded by the DHCP
servers. This hooks library is compiled when the ``--with-mysql``
configuration switch is used during the Kea build. The MySQL C client
libraries must be installed, as explained in
:ref:`DHCP Database Installation and Configuration <dhcp-install-configure>`.

   **Note**

   Any existing MySQL schema must be upgraded to the latest schema
   required by the particular Kea version using the ``kea-admin`` tool,
   as described in `The kea-admin Tool <kea-admin>`.

The ``cb_cmds`` premium hooks library, which is available to ISC's paid support
customers, provides a complete set of commands to manage the
servers' configuration information within the database. This library can
be attached to both DHCPv4 and DHCPv6 server instances. It is still
possible to manage the configuration information without the ``cb_cmds``
hooks library with commonly available tools, such as MySQL Workbench or
the command-line MySQL client, by directly working with the database.

Refer to :ref:`cb_cmds: Configuration Backend Commands <cb-cmds-library>` for the details regarding the
``cb_cmds`` hooks library.

The DHCPv4 and DHCPv6 server-specific configurations of the CB, as well as
the list of supported configuration parameters, can be found in
:ref:`Configuration Backend in DHCPv4 <dhcp4-cb>` and :ref:`Configuration Backend in DHCPv6 <dhcp6-cb>` respectively.
