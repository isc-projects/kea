.. _config-backend:

Kea Configuration Backend
=========================

.. _cb-applicability:

Applicability
-------------

Kea Configuration Backend (CB or config backend) gives Kea servers the ability
to manage and fetch their configuration from one or more databases. In
this documentation, the term "Configuration Backend" may also refer to
the particular Kea module providing support to manage and fetch the
configuration information from the particular database type.  For
example, the MySQL Configuration Backend is the logic implemented within the
``mysql_cb`` hook library, which provides a complete set of functions to
manage and fetch the configuration information from the MySQL database.
The PostgreSQL Configuration Backend is the logic implemented within the
``pgsql_cb`` hook library, which provides a complete set of functions to
manage and fetch the configuration information from the PostgreSQL database.
From herein, the term "database" is used to refer to either a MySQL or
PostgreSQL database.

In small deployments, e.g. those comprising a single DHCP server
instance with limited and infrequently changing number of subnets, it
may be impractical to use the CB as a configuration repository because
it requires additional third-party software to be installed and
configured - in particular the database server, client and libraries.
Once the number of DHCP servers and/or the number of managed subnets in the
network grows, the usefulness of the CB becomes obvious.

One use case for the CB is a pair of Kea DHCP servers that are configured
to support High Availability as described in
:ref:`hooks-high-availability`. The configurations of both servers
(including the value of the ``server-tag`` parameter)
are almost exactly the same: they may differ by the server identifier
and designation of the server as a primary or standby (or secondary), and/or
by their interfaces' configuration. Typically, the
subnets, shared networks, option definitions, and global parameters are the
same for both servers and can be sourced from a single database instance
to both Kea servers.

Using the database as a single source of configuration for subnets
and/or other configuration information supported by the CB has the
advantage that any modifications to the configuration in the database are
automatically applied to both servers.

Another case when the centralized configuration repository is useful is
in deployments including a large number of DHCP servers, possibly
using a common lease database to provide redundancy. New servers can
be added to the pool frequently to fulfill growing scalability
requirements. Adding a new server does not require replicating the
entire configuration to the new server when a common database is used.

Using the database as a configuration repository for Kea servers also
brings other benefits, such as:

-  the ability to use database specific tools to access the configuration
   information;

-  the ability to create customized statistics based on the information
   stored in the database; and

-  the ability to backup the configuration information using the database's
   built-in replication mechanisms.

.. _cb-limitations:

CB Capabilities and Limitations
-------------------------------

Currently, the Kea CB has the following limitations:

- It is only supported for MySQL and PostgreSQL databases.

- It is only supported for the DHCPv4 and DHCPv6 daemons; the Control Agent,
  D2 daemon, and the NETCONF daemon cannot be configured from the database,

- Only certain DHCP configuration parameters can be set in the
  database: global parameters, option definitions, global options, client
  classes, shared networks, and subnets. Other configuration parameters
  must be sourced from a JSON configuration file.

Kea CB stores data in a schema that is public. It is possible to
insert configuration data into the tables manually or automatically
using SQL scripts, but this requires SQL and schema knowledge.
The supported method for managing the data is through the ``cb-cmds`` hook library,
which provides management commands for config backends. It simplifies many
typical operations, such as listing, adding, retrieving, and deleting global
parameters, shared networks, subnets, pools, options, option definitions, and
client classes. In addition, it provides essential business logic that ensures
the logical integrity of the data. See commands starting with ``remote-`` in
Appendix A of this manual for a complete list.

.. note::

   The ``cb_cmds`` hook library is available only to ISC support subscribers.
   For more information on subscription options, please complete the form
   at https://www.isc.org/contact.


The schema creation scripts can be found at `dhcpdb_create.mysql <https://gitlab.isc.org/isc-projects/kea/blob/master/src/share/database/scripts/mysql/dhcpdb_create.mysql>`__ and
;
`dhcpdb_create.pgsql <https://gitlab.isc.org/isc-projects/kea/blob/master/src/share/database/scripts/pgsql/dhcpdb_create.pgsql>`__ and
;
other related design documents are stored in our GitLab: `CB Design <https://gitlab.isc.org/isc-projects/kea/wikis/designs/configuration-in-db-design>`__ and
`Client Classes in CB Design <https://gitlab.isc.org/isc-projects/kea/wikis/designs/client-classes-in-cb>`__.

We strongly recommend against duplication of configuration information
in both the file and the database. For example, when specifying subnets
for the DHCP server, please store them in either the configuration backend
or in the configuration file, not both. Storing some subnets in the database
and others in the file may put users at risk of potential configuration
conflicts. Note that the configuration instructions from the database take
precedence over instructions from the file, so parts of the configuration
specified in the file may be overridden if contradicted by information in
the database.

Although it is not recommended, it is possible to specify certain parameter
types both in a configuration file and the database. For example, a subnet
can be specified in the configuration file and another subnet in the database;
in this case, the server will use both subnets. DHCP client classes, however,
must not be specified in both the configuration file and the database, even if
they do not overlap. If any client classes are specified in the database
for a particular DHCP server, this server will use these classes and ignore
all classes present in its configuration file. This behavior was introduced
to ensure that the server receives a consistent set of client classes
specified in an expected order with all inter-class dependencies fulfilled.
It is impossible to guarantee consistency when client classes are specified
in two independent configuration sources.

.. note::

   It is recommended that the ``subnet_cmds`` hook library not be used to
   manage subnets when the configuration backend is used as a source
   of information about the subnets. The ``subnet_cmds`` hook library
   modifies the local subnets configuration in the server's memory,
   not in the database. Use the ``cb_cmds`` hook library to manage the
   subnets information in the database instead.

.. note::

   Using custom option formats requires creating definitions for these options.
   Suppose a user wishes to set option data in the configuration backend. In
   that case, we recommend specifying the definition for that option in the
   configuration backend as well. It is essential when multiple servers are
   managed via the configuration backend, and may differ in their
   configurations. The option data parser can search for an option definition
   appropriate for the server for which the option data is specified.

   In a single-server deployment, or when all servers share the same
   configuration file information, it is possible to specify option
   definitions in the configuration files and option data in the configuration
   backend. The server receiving a command to set option data must have a
   valid definition in its configuration file, even when it sets option data
   for another server.

   It is not supported to specify option definitions in the configuration
   backend and the corresponding option data in the server configuration files.

CB Components
-------------

To use a MySQL configuration backend you must compile the ``mysql_cb`` open
source hook library and configure the DHCP servers to load it.  It is compiled when
the ``--with-mysql`` configuration switch is used during the Kea build. The MySQL
C client libraries must be installed, as explained in :ref:`dhcp-install-configure`.

To use a PostgreSQL configuration backend you must compile the ``pgsql_cb`` open
source hook library and configure the DHCP servers to load it.  It is compiled when
the ``--with-pgsql`` configuration switch is used during the Kea build. The PostgreSQL
C client libraries must be installed, as explained in :ref:`dhcp-install-configure`.

.. note::

   An existing database schema must be upgraded to the latest schema
   required by the particular Kea version using the ``kea-admin`` tool,
   as described in :ref:`kea-admin`.

The ``cb_cmds`` premium hook library, which is available to ISC's paid support
customers, provides a complete set of commands to manage the
servers' configuration information within the database. This library can
be attached to both DHCPv4 and DHCPv6 server instances. While it is
possible to manage the configuration information without the ``cb_cmds``
hook library with commonly available tools, such as MySQL Workbench or
the command-line MySQL client, or by directly working with the database;
these avenues are neither recommended nor supported.

Refer to :ref:`hooks-cb-cmds` for the details regarding the
``cb_cmds`` hook library.

The DHCPv4 and DHCPv6 server-specific configurations of the CB, as well as
the list of supported configuration parameters, can be found in
:ref:`dhcp4-cb` and :ref:`dhcp6-cb`, respectively.

.. _cb-sharing:

Configuration Sharing and Server Tags
-------------------------------------

The configuration database is designed to store configuration information
for multiple Kea servers. Depending on the use case, the entire configuration
may be shared by all servers; parts of the configuration may be shared by
multiple servers and the rest of the configuration may be different for these
servers; or each server may have its own non-shared configuration.

The configuration elements in the database are associated with the servers
by "server tags." The server tag is an arbitrary string holding the name
of the Kea server instance. The tags of the DHCPv4 and DHCPv6 servers are
independent in the database, i.e. the same server tag can be created for
both the DHCPv4 and the DHCPv6 server. The value is configured
using the ``server-tag`` parameter in the Dhcp4 or Dhcp6 scope. The current
server tag can be checked with the ``server-tag-get`` command.

The server definition, which consists of the server tag and the server
description, must be stored in the configuration database prior to creating
the dedicated configuration for that server. In cases when all servers use
the same configuration, e.g. a pair of servers running as High Availability
peers, there is no need to configure the server tags for these
servers in the database.

Commands which contain the logical server `all` are applied to all servers
connecting to the database. The `all` server cannot be
deleted or modified, and it is not returned among other servers
as a result of the ``remote-server[46]-get-all`` command.

In most cases, there are no server tags defined in the configuration
database; all connecting servers get the same configuration
regardless of the server tag they use. The server tag that a
particular Kea instance presents to the database to fetch its configuration
is specified in the Kea configuration file, using the
`config-control` map (please refer to the :ref:`dhcp4-cb-json` and
:ref:`dhcp6-cb-json` for details). All Kea instances presenting the same
server tag to the configuration database
are given the same configuration.

It is the administrator's choice whether
multiple Kea instances use the same server tag or each Kea instance uses
a different server tag. There is no requirement that the instances
running on the same physical or virtual machine use the same server tag. It is
even possible to configure the Kea server without assigning it a server tag.
In such a case the server will be given the configuration specified for `all`
servers.

To differentiate between different Kea server configurations, a
list of the server tags used by the servers must be stored in the
database. For the DHCPv4 and DHCPv6 servers, it can be done using the
commands described in :ref:`command-remote-server4-set` and
:ref:`command-remote-server6-set`. The
server tags can then be used to associate the configuration information with
the servers. However, it is important to note that some DHCP
configuration elements may be associated with multiple server tags (known
as "shareable" elements), while
other configuration elements may be associated with only one
server tag ("non-shareable" elements). The :ref:`dhcp4-cb`
and :ref:`dhcp6-cb` sections list the DHCP-specific shareable and
non-shareable configuration elements; however, in this section we
briefly explain the differences between them.

A shareable configuration element is one which has some unique
property identifying it, and which may appear only once in
the database. An example of a shareable DHCP element is a subnet
instance: the subnet is a part of the network topology and we assume
that any particular subnet may have only one definition within this
network. Each subnet has two unique identifiers: the subnet identifier and the
subnet prefix. The subnet identifier is used in Kea to uniquely
identify the subnet within the network and to connect it with other configuration elements,
e.g. in host reservations. Some commands provided by the
``cb_cmds`` hook library allow the subnet
information to be accessed by either subnet identifier or prefix, and explicitly prohibit
using the server tag to access the subnet. This is because, in
general, the subnet definition is associated with multiple servers
rather than a single server. In fact, it may even be associated
with no servers (unassigned). Still, the unassigned subnet has an
identifier and prefix which can be used to access the subnet.

A shareable configuration element may be associated with multiple
servers, one server, or no servers. Deletion of the server which is
associated with the shareable element does not cause the deletion of
the shareable element. It merely deletes the association of the
deleted server with the element.

Unlike a shareable element, a non-shareable element must not be
explicitly associated with more than one server and must not exist
after the server is deleted (must not remain unassigned). A
non-shareable element only exists within the context of the server.
An example of a non-shareable element in DHCP is a global
parameter, e.g. `renew-timer`. The renew timer
is the value to be used by a particular server and only this
server. Other servers may have their respective renew timers
set to the same or different values. The renew timer
parameter has no unique identifier by which it could be
accessed, modified, or otherwise used. Global parameters like
the renew timer can be accessed by the parameter name and the
tag of the server for which they are configured. For example:
the commands described in :ref:`command-remote-global-parameter4-get` allow
the value of the global parameter to be fetched by the parameter name and
the server name. Getting the global parameter only by its name (without
specifying the server tag) is not possible, because there may be many
global parameters with a given name in the database.

When the server associated with a non-shareable configuration element
is deleted, the configuration element is automatically deleted from
the database along with the server because the non-shareable element
must be always assigned to a server (or the logical server `all`).

The terms "shareable" and "non-shareable" only apply to associations
with user-defined servers; all configuration elements associated with
the logical server `all` are by definition shareable. For example: the
`renew-timer` associated with `all` servers is used
by all servers connecting to the database which do not have their specific
renew timers defined. In a special case, when none of the configuration
elements are associated with user-defined servers, the entire
configuration in the database is shareable because all its pieces
belong to `all` servers.

.. note::

   Be very careful when associating configuration elements with
   different server tags. The configuration backend does not protect
   against some possible misconfigurations that may arise from the
   wrong server tags' assignments. For example: if a shared
   network is assigned to one server and the subnets belonging to this shared network
   to another server, the servers will fail upon trying to fetch and
   use this configuration. The server fetching the subnets will be
   aware that the subnets are associated with the shared network, but
   the shared network will not be found by this server since it doesn't
   belong to it. In such a case, both the shared network and the subnets
   should be assigned to the same set of servers.
