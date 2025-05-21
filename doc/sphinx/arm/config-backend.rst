 .. _config-backend:

Kea Configuration Backend
=========================

.. _cb-applicability:

Applicability
-------------

The Kea Configuration Backend (CB or config backend) gives Kea servers the
ability to store almost all of their configuration in one or more databases.

Potential features and benefits include:

-  Re-use of identical configuration sections across multiple Kea servers

-  A "single source of truth" for all Kea servers

-  All configuration done through an API with real-time logic checks

-  Easier integration with third-party tools or in-house automation

-  Database architecture provides concurrency, consistency, and atomicity

-  The ability to mine the database for statistics and reporting

-  Use of database replication for real-time fault-tolerance

Potential drawbacks include:

-  Significant up-front effort to prepare integration and/or automation

-  Supported scenarios require use of API for most configuration

-  The API is only available to ISC customers with a paid support contract

-  Incompatible with some uses, software, and scenarios

.. note::

   Use of a database for storage of leases and/or reservations is still possible without the CB.  See the ``host-databases`` and ``lease-database`` config directives.

Example Scenario
^^^^^^^^^^^^^^^^

Consider a large organization with many sites, each with a pair of Kea servers deployed in a high availability (HA) configuration.  Typically such deployments use standardized configurations, leading to similar config parameters for every site.  The members of each HA pair are often almost exactly the same, differing only by name.  Often installations of this size will feature a high level of automation, including provisioning and management systems.

The CB is ideal for such deployments.  While some effort is required to integrate with the provisioning automation, once accomplished, deployment of new Kea servers can be nearly automatic.  A small "stub" JSON config, identical for every server, can be used, and all remaining configuration (interfaces, subnets, pools, etc.) loaded from the central CB database.  Any updates to the central CB database are automatically propagated to all Kea instances.  The CB becomes the "single source of truth" for DHCP throughout the organization.

.. _cb-limitations:

Limitations and Warnings
------------------------

Availability
^^^^^^^^^^^^

:ischooklib:`libdhcp_cb_cmds.so` is available only to ISC customers with a
paid support contract. For more information on subscription options, please
complete the form at https://www.isc.org/contact.  While it is theoretically
possible to use the CB without this hook, this is neither supported nor
recommended.

Preparation is Required
^^^^^^^^^^^^^^^^^^^^^^^

The Configuration Backend is not a "plug-and-play" solution.  Supported
scenarios require use of the CB API commands.  Configuration information must
be loaded into the CB database using the API for the CB to have any effect.
The general intent is for the CB to be integrated with external software.
Please do not define ``config-databases`` unless you have done the necessary
preparation work.

Incompatibilities
^^^^^^^^^^^^^^^^^

Use of the :ischooklib:`libdhcp_subnet_cmds.so` hook with the CB is
contraindicated.  The API commands starting with ``subnet`` all modify the
in-memory configuration of Kea.  The only way to save that config would be to
write out a JSON config file.  That would conflict with any subnets defined by
the CB.  Use :ischooklib:`libdhcp_cb_cmds.so` to manage the
subnets information in the database instead.

The Stork management suite does not currently support the CB.  Stork operates
by direct configuration modification, with accompanying ``config-write`` of
the JSON config file.  That would create duplicate definitions vs the CB.
Support for the CB is planned for a future release of Stork.

In certain carefully-controlled scenarios, it may be possible to use these tools with the CB.  Namely, if they are used in strictly "read-only" fashion, to retrieve Kea information, but never to modify it.  However, no protection against accidental modification is provided, so this is not recommended.

Implementation
^^^^^^^^^^^^^^

Currently, the Kea CB has the following limitations:

- It is only supported for MySQL and PostgreSQL databases.

- It is only supported for the DHCPv4 and DHCPv6 daemons; the Control Agent,
  D2 daemon, and the NETCONF daemon cannot be configured from the database,

- Only certain DHCP configuration parameters can be set in the
  database: global parameters, option definitions, global options, client
  classes, shared networks, and subnets. Other configuration parameters
  must be sourced from a JSON configuration file.

Database Management
^^^^^^^^^^^^^^^^^^^

While it is possible to manage the configuration information in the database
without :ischooklib:`libdhcp_cb_cmds.so` (using commonly available tools, such
as MySQL Workbench or the command-line MySQL client), these avenues are
neither recommended nor supported.  The supported method for managing the
database contents is through :ischooklib:`libdhcp_cb_cmds.so`, which provides
management commands for config backends.

Duplicate Definitions
^^^^^^^^^^^^^^^^^^^^^

We strongly recommend against storing configuration information in both the
config file and the CB database.  In other words, do not use both JSON config
files (like ``kea-dhcp4.conf``) and CB to configure the same items.  Ideally,
when using the CB, the Kea config files should contain the absolute bare
minimum necessary, with everything else coming from the CB.

Using both CB and JSON as a source of configuration risks conflicting
definitions, which is confusing at best, and usually leads to undesired
behavior.

In the event of a conflict, configuration instructions from the CB database
generally take precedence over instructions from a JSON file.

In certain carefully-controlled scenarios, it may be technically possible to
use both.  For example, defining one subnet in a JSON file and a second
(different) subnet in the CB database would not conflict.  However, other
structures are replaced entirely.  For example, if client classes are defined
in the CB database, the DHCP server disregards any client classes defined in
the JSON file.

   Note that use of a database for storage of leases and/or reservations is still possible without the CB (with the ``host-databases`` and ``lease-database`` config directives).  Such databases also load their config independently from the CB, and will conflict the same way JSON would.

Custom Options
^^^^^^^^^^^^^^

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

Components
----------

The Kea Configuration Backend solution consists of the CB modules (hook libraries), the CB commands API (its own hook library), the external database software (MySQL or PostgreSQL), the database schema, and the Kea configuration information stored in the database.

In this documentation, the term "Configuration Backend" may also refer to the
particular Kea module providing support for that database type.  For example,
the MySQL Configuration Backend, :ischooklib:`libdhcp_mysql.so`, provides a
complete set of functions to manage and fetch the configuration information
from a MySQL database.  The PostgreSQL Configuration Backend,
:ischooklib:`libdhcp_pgsql.so`, is the corresponding module for PostgreSQL.
Similarly, the term "database" is used to refer to either a MySQL or
PostgreSQL database.

The CB commands API provides a complete set of commands to manage Kea
configuration information, as stored within the database.  This API is
implemented in its own hook library, :ischooklib:`libdhcp_cb_cmds.so`.  This
library can be attached to both DHCPv4 and DHCPv6 server instances.  It
simplifies many typical operations, such as listing, adding, retrieving, and
deleting global parameters, shared networks, subnets, pools, options, option
definitions, and client classes. In addition, it provides essential business
logic that ensures the logical integrity of the data.  All CB API commands
start with ``remote-``.  See :ref:`commands-cb-cmds` for a complete
list.

Installation and maintenance of external database software is beyond the scope of this manual.

The database schema is typically installed via the  tool.  See :ref:`cb-install` for more information.  The raw schema creation scripts are
`dhcpdb_create.mysql <https://gitlab.isc.org/isc-projects/kea/blob/master/src/share/database/scripts/mysql/dhcpdb_create.mysql>`__
and
`dhcpdb_create.pgsql <https://gitlab.isc.org/isc-projects/kea/blob/master/src/share/database/scripts/pgsql/dhcpdb_create.pgsql>`__.

Use the CB commands API to populate the database with Kea configuration information.

Related design documents are available in our GitLab:

-  `CB Design <https://gitlab.isc.org/isc-projects/kea/wikis/designs/configuration-in-db-design>`__
-  `Client Classes in CB Design <https://gitlab.isc.org/isc-projects/kea/wikis/designs/client-classes-in-cb>`__

.. _cb-install:

Installation
------------

To use either Configuration Backend, the appropriate module library
(:ischooklib:`libdhcp_mysql.so` or :ischooklib:`libdhcp_pgsql.so`) must be
compiled during the Kea build.  The ``-D`` switch specifies which database
module to build, if any: ``-D mysql`` or ``-D pgsql``.  The appropriate
database client libraries and header files must be installed prior to build.
See :ref:`dhcp-install-configure` for more information on building Kea with
database support.  ISC's Kea packaging, as well as some distributions, provide
separate packages for each database type.

The database server hosting the CB tables must be prepared with the Kea
schema.  When upgrading an existing Kea installation, the database schema may
also need to be upgraded.  The :iscman:`kea-admin` tool can be used to more
easily apply the schema, as described in :ref:`kea-admin`.

At runtime, the DHCP servers must be configured to load the module, in the
``hooks-libraries`` section.  A ``config-databases`` directive must then be
used to instruct Kea to load configuration using the database backend.  The
DHCPv4 and DHCPv6 server-specific configurations of the CB, as well as the
list of supported configuration parameters, can be found in :ref:`dhcp4-cb`
and :ref:`dhcp6-cb`, respectively.

Once installation is completed, the CB commands API can be used to populate
the database with Kea configuration information.

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
using the ``server-tag`` parameter in the ``Dhcp4`` or ``Dhcp6`` scope. The current
server tag can be checked with the :isccmd:`server-tag-get` command.

The server definition, which consists of the server tag and the server
description, must be stored in the configuration database prior to creating
the dedicated configuration for that server. In cases when all servers use
the same configuration, e.g. a pair of servers running as High Availability
peers, there is no need to configure the server tags for these
servers in the database.

Commands which contain the logical server `all` are applied to all servers
connecting to the database. The `all` server cannot be
deleted or modified, and it is not returned among other servers
as a result of the :isccmd:`remote-server4-get-all` and :isccmd:`remote-server6-get-all` commands.

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
database. For the DHCPv4 and DHCPv6 servers, this can be done using the
:isccmd:`remote-server4-set` and :isccmd:`remote-server6-set` commands. The
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
e.g. in host reservations. Some commands provided by
:ischooklib:`libdhcp_cb_cmds.so` allow the subnet
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
tag of the server for which they are configured. For example, the
:isccmd:`remote-global-parameter4-get` and
:isccmd:`remote-global-parameter6-get` commands allow
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
