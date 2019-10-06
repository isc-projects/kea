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
:ref:`high-availability-library`. The configurations of both servers
(including the value of the ``server-tag`` parameter)
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
CB in the Kea 1.6.0 release:

-  Kea CB is supported for the MySQL database only.

-  Kea CB is only supported for DHCPv4 and DHCPv6 servers. Neither the
   Control Agent nor the D2 daemon can be configured via the database.

-  Potential configurations to be stored for the DHCP servers include: global
   parameters, option definitions, global options, shared networks, and
   subnets. Other configuration parameters are not stored in the
   database and must be configured via the JSON
   configuration file.

..

.. note::
    Kea CB stores data in a MySQL schema that is public. It's possible to
    insert configuration data into the MySQL tables manually, or automatically
    using SQL scripts, but this requires a reasonably good knowledge of SQL and the
    schema.  The supported method for managing the data is through our cb-cmds
    hook library which provides management commands for config backends.
    It simplifies many typical operations, such as listing, adding, retrieving,
    and deleting of global parameters, shared networks, subnets, pools, options,
    and option definitions.  In addition, it provides essential business logic
    that ensures logical integrity of the data.  For a complete list, see commands
    starting with "remote-" in Appendix A of the Kea Administrator Reference Manual.
    The cb_cmds hooks library is available to subscribers only. If you are not a
    subscriber and would like to subscribe, please contact info@isc.org and
    our sales team will assist you.

    The schema creation script can be found here `dhcpdb_create.mysql <https://gitlab.isc.org/isc-projects/kea/blob/master/src/share/database/scripts/mysql/dhcpdb_create.mysql>`__ and
    we have some related design documents in gitlab `CB Design <https://gitlab.isc.org/isc-projects/kea/wikis/designs/configuration-in-db-design>`__.

.. note::

   We strongly recommend against duplication of the configuration information
   in the file and the database. For example, when specifying subnets
   for the DHCP server, please store them in either the configuration backend
   or in the configuration file, not both. Storing some
   subnets in the database and others in the file may put you at risk of
   potential configuration conflicts. Note that the configuration instructions from
   the database take precedence over instructions from the file,
   so it is possible that parts of the configuration specified in the
   file may be overridden if contradicted by information in the database.

.. note::

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
:ref:`dhcp-install-configure`.

.. note::

   Any existing MySQL schema must be upgraded to the latest schema
   required by the particular Kea version using the ``kea-admin`` tool,
   as described in :ref:`kea-admin`.

The ``cb_cmds`` premium hooks library, which is available to ISC's paid support
customers, provides a complete set of commands to manage the
servers' configuration information within the database. This library can
be attached to both DHCPv4 and DHCPv6 server instances. It is still
possible to manage the configuration information without the ``cb_cmds``
hooks library with commonly available tools, such as MySQL Workbench or
the command-line MySQL client, by directly working with the database.

Refer to :ref:`cb-cmds-library` for the details regarding the
``cb_cmds`` hooks library.

The DHCPv4 and DHCPv6 server-specific configurations of the CB, as well as
the list of supported configuration parameters, can be found in
:ref:`dhcp4-cb` and :ref:`dhcp6-cb` respectively.

.. _cb-sharing:

Configuration Sharing and Server Tags
-------------------------------------


The configuration database is designed to store the configuration information
for multiple Kea servers. Depending on the use case, the entire configuration
may be shared by all servers, parts of the configuration may be shared by
multiple servers and the rest of the configuration may be different for these
servers or, finally, each server may have its own non-shared configuration.

The configuration elements in the database are associated with the servers
by "server tags". The server tag is an arbitrary string holding the name
of the Kea server instance. The tags of the DHCPv4 and DHCPv6 servers are
independent in the database, i.e. the same server tag can be created for
the DHCPv4 and the DHCPv6 server respectively. The value is configured
using ``server-tag`` parameter in the Dhcp4 or Dhcp6 scope. The current
server-tag can be checked with the ``server-tag-get`` command.

The server definition, which consists of the server tag and the server
description, must be stored in the configuration database prior to creating
the dedicated configuration for that server. In cases when all servers use
the same configuration, e.g. a pair of servers running as the High Availability
peers, there is no need to configure the server tags for these
servers in the database. The database by default includes the logical
server `all`, which is used as a keyword to indicate that
the particular piece of configuration must be shared between all servers
connecting to the database. The `all` server can't be
deleted or modified. It is not even returned among other servers
as a result of the `remote-server[46]-get-all`
commands. Also, slightly different rules may apply to "all" keyword
than to any user defined server when running the commands provided by
the `cb_cmds` hooks library :ref:`cb-cmds-library`.

In the simplest case there are no server tags defined in the configuration
database and all connecting servers will get the same configuration
regardless of the server tag they are using. The server tag that the
particular Kea instance presents to the database to fetch its configuration
is specified in the Kea configuration file, using the
`config-control` map (please refer to the :ref:`dhcp4-cb-json` and
:ref:`dhcp6-cb-json` for details).

All Kea instances presenting the same server tag to the configuration database
are given the same configuration. It is the administrator's choice whether
multiple Kea instances use the same server tag or each Kea instance is using
a different sever tag. Also, there is no requirement that the instances
running on the same physical or virtual machine use the same server tag. It is
even possible to configure the Kea server without assigning it a server tag.
In such case the server will be given the configuration specified for "all"
servers.

In order to differentiate the configurations between the Kea servers, a
collection of the server tags used by the servers must be stored in the
database. For the DHCPv4 and DHCPv6 servers, it can be done using the
commands described in :ref:`command-remote-server4-set` and
:ref:`command-remote-server6-set`. Next, the
server tags can be used to associate the configuration information with
the servers. However, it is important to note that some DHCP
configuration elements may be associated with multiple server tags and
other configuration elements may be associated with exactly one
server tag. The former configuration elements are referred to as
shareable configuration elements and the latter are referred to as
non-shareable configuration elements. The :ref:`dhcp4-cb`
and :ref:`dhcp6-cb` list the DHCP specific shareable and
non-shareable configuration elements. However, in this section we
want to briefly explain the difference between them.

The shareable configuration element is the one having some unique
property identifying it and which instance may appear only once in
the database. An example of the shareable DHCP element is a subnet
instance. The subnet is a part of the network topology and we assume
that the particular subnet may have only one definition within this
network. The subnet has two unique identifiers: subnet id and the
subnet prefix. The subnet identifier is used in Kea to uniquely
identify the subnet and to connect it with other configuration elements,
e.g. in host reservations. The subnet identifier uniquely identifies
the subnet within the network. Some commands provided by the
`cb_cmds` hooks library allow for accessing the subnet
information by subnet identifier (or prefix) and explicitly prohibit
using the server tag to access the subnet. This is because, in a
general case, the subnet definition is associated with multiple servers
rather than single server. In fact, it may even be associated
with no servers (unassigned). Still, the unassigned subnet has an
identifier and prefix which can be used to access the subnet.

A shareable configuration element may be associated with multiple
servers, one server or no servers. Deletion of the server which is
associated with the shareable element does not cause the deletion of
the shareable element. It merely deletes the association of the
deleted server with the element.

Unlike the shareable element, the non-shareable element must not be
explicitly associated with more than one server and must not exist
after the server is deleted (must not remain unassigned). The
non-shareable element only exists within the context of the server.
An example of the non-shareable element in DHCP is a global
parameter, e.g. `renew-timer`. The renew timer
is the value to be used by the particular server and only this
server. Other servers may have their respective renew timers
set to the same or different value. The renew timer is the
parameter which has no unique identifier by which it could be
accessed, modified or otherwise used. The global parameters like
the renew timer can be accessed by the parameter name and the
tag of the server for which they are configured. For example:
the commands described in :ref:`command-remote-global-parameter4-get` allow for
fetching the value of the global parameter by the parameter name and
the server name. Getting the global parameter only by its name (without
specifying the server tag) is not possible because there may be many
global parameters with the given name in the database.

When the server associated with a non-shareable configuration element
is deleted, the configuration element is automatically deleted from
the database along with the server because the non-shareable element
must be always assigned to some server (or the logical server "all").

The terms "shareable" and "non-shareable" only apply to the associations
with user defined servers. All configuration elements associated with
the logical server "all" are by definition shareable. For example: the
`renew-timer` associated with "all" servers is used
by all servers connecting to the database which don't have their specific
renew timers defined. In the special case, when none of the configuration
elements are associated with user defined servers, the entire
configuration in the database is shareable because all its pieces
belong to "all" servers.

.. note::
   Be very careful when associating the configuration elements with
   different server tags. The configuration backend doesn't protect you
   against some possible misconfigurations that may arise from the
   wrong server tags' assignments. For example: if you assign a shared
   network to one server and the subnets belonging to this shared network
   to another server, the servers will fail upon trying to fetch and
   use this configuration. The server fetching the subnets will be
   aware that the subnets are associated with the shared network but
   the shared network will not be found by this server as it doesn't
   belong to it. In such case, both the shared network and the subnets
   should be assigned to the same set of servers.
