.. _cb-cmds-library:

cb_cmds: Configuration Backend Commands
=======================================

This section describes the ``cb_cmds`` hooks library, which is used to
manage Kea servers' configurations in the Configuration Backends. This
library must be used in conjunction with the available CB hooks libraries
implementing the common APIs to create, read, update, and delete (CRUD)
the configuration information in the respective databases. For example:
the ``mysql_cb`` hooks library, released in Kea 1.6.0, implements this
API for MySQL. In order to manage the configuration information in the
MySQL database, both the ``mysql_cb`` and ``cb_cmds`` libraries must be
loaded by the server used for the configuration management.

The ``cb_cmds`` library is only available to ISC customers with a paid
support contract.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or
   ``kea-dhcp6`` process.

Commands Structure
------------------

There are 5 types of commands supported by this library:

-  ``del`` - delete the selected object from the database, e.g.
   ``remote-global-parameter4-del``.

-  ``get`` - fetch the selected object from the database, e.g.
   ``remote-subnet4-get``.

-  ``get-all`` - fetch all objects of the particular type from the
   database, e.g. ``remote-option-def4-get-all``.

-  ``list`` - list all objects of the particular type in the database,
   e.g. ``remote-network4-list``; this class of commands returns brief
   information about each object comparing to the output of ``get-all``.

-  ``set`` - creates or replaces an object of the given type in the
   database, e.g. ``remote-option4-global-set``.

All types of commands accept an optional ``remote`` map which selects the
database instance to which the command refers. For example:

::

   {
       "command": "remote-subnet4-list",
       "arguments": {
           "remote": {
               "type": "mysql",
               "host": "192.0.2.33",
               "port": 3302
           }
       }
   }

selects the MySQL database, running on host 192.0.2.33 and port 3302, to
fetch the list of subnets from. All parameters in the ``remote`` argument are
optional. The ``port`` parameter can be only specified in conjunction
with the ``host``. If no options in the ``remote`` parameter are to
be specified, the parameter should be omitted. In this case, the server
will use the first backend listed in the ``config-control`` map within
the configuration of the server receiving the command.

.. note::

   As of the Kea 1.6.0 release, it is possible to configure the Kea server
   to use only one configuration backend. Strictly speaking, it is
   possible to point the Kea server to at most one MySQL database using the
   ``config-control`` parameter. That's why, in this release, the
   ``remote`` parameter may be omitted in the commands, because the
   cb_cmds hooks library will use the sole backend by default.

.. _cb-cmds-dhcp:

Control Commands for DHCP Servers
---------------------------------

This section describes and gives some examples of the control commands
implemented by the ``cb_cmds`` hooks library, to manage the
configuration information of the DHCPv4 and DHCPv6 servers. Many of the
commands are almost identical between DHCPv4 and DHCPv6; they only
differ by the command name. Other commands differ slightly by the
structure of the inserted data; for example, the structure of the IPv4 subnet
information is different than that of the IPv6 subnet.
Nevertheless, they still share the structure of their command arguments
and thus it makes sense to describe them together.

In the following sections, various commands are described and some usage
examples are provided. In the sections jointly describing the DHCPv4 and
DHCPv6 variants of the particular command, we sometimes use the following
notation: the ``remote-subnet[46]-set`` is the wildcard name for the
two commands: ``remote-subnet4-set`` and ``remote-subnet6-set``.

In addition, whenever the text in the subsequent sections refers to a
DHCP command or DHCP parameter, it refers to both DHCPv4 and DHCPv6
variants. The text specific to the particular server type refers to them
as: DHCPv4 command, DHCPv4 parameter, DHCPv6 command, DHCPv6 parameter,
etc.

.. _cb-cmds-metadata:

Metadata
~~~~~~~~

The typical response to the ``get`` or ``list`` command includes a list
of returned objects (e.g. subnets), and each such object contains the
``metadata`` map with some database-specific information describing this
object. In other words, the metadata contains any information about the
fetched object which may be useful for the administrator, but which is not
part of the object specification from the DHCP server standpoint. In the
Kea 1.6.0 release, the metadata is limited to the ``server-tag``, which
describes the association of the object with a particular server or
all servers. The server tag is always set to ``all`` in the Kea 1.6.0
beta release.

The following is the example response to the ``remote-network4-list``
command, which includes the metadata:

::

   {
       "result": 0,
       "text": "1 IPv4 shared network(s) found.",
       "arguments": {
           "shared-networks": [
               {
                   "name": "level3",
                   "metadata": {
                       "server-tag": "all"
                   }
               }
           ],
           "count": 1
       }
   }


Client implementations must not assume that the metadata contains only
the ``server-tag`` parameter. In future releases, this map will be
extended with additional information, e.g. object modification time, log
message created during the last modification, etc.

.. _command-remote-global-parameter4-del:

The remote-global-parameter4-del, remote-global-parameter6-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete a global DHCP parameter from the
configuration database. When the parameter is deleted from the database,
the server will use the value specified in the configuration file for
this parameter, or a default value if the parameter is not specified in
the configuration file.

The following command attempts to delete the DHCPv4 ``renew-timer``
parameter from the database:

::

   {
       "command": "remote-global-parameter4-del",
       "arguments": {
           "parameters": [ "renew-timer" ],
           "remote": {
               "type": "mysql"
            }
       }
   }


.. _command-remote-global-parameter4-get:

The remote-global-parameter4-get, remote-global-parameter6-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch a scalar global DHCP parameter from the
configuration database.

The following command attempts to fetch the ``boot-file-name``
parameter:

::

   {
       "command": "remote-global-parameter4-get",
       "arguments": {
           "parameters": [ "boot-file-name" ],
            "remote": {
                "type": "mysql"
            }
       }
   }


The returned value has one of the four scalar types: string, integer,
real, or boolean. Non-scalar global configuration parameters, such as map
or list, are not returned by this command.

In the case of the example above, the string value is returned, e.g.:

::

   {
       "result": 0,
       "text": "1 DHCPv4 global parameter found.",
       "arguments": {
           "parameters": {
               "boot-file-name": "/dev/null",
               "metadata": {
                   "server-tag": "all"
               }
           },
           "count": 1
       }
   }


The example response for the integer value is:

::

   {
       "result": 0,
       "text": "1 DHCPv4 global parameter found.",
       "arguments": {
           "parameters": {
               "renew-timer": 2000,
               "metadata": {
                   "server-tag": "all"
               }
           },
           "count": 1
       }
   }


The real value:

::

   {
       "result": 0,
       "text": "1 DHCPv4 global parameter found.",
       "arguments": {
           "parameters": {
               "t1-percent": 0.85,
               "metadata": {
                   "server-tag": "all"
               }
           },
           "count": 1
       }
   }


Finally, the boolean value:

::

   {
       "result": 0,
       "text": "1 DHCPv4 global parameter found.",
       "arguments": {
           "parameters": {
               "match-client-id": true,
               "metadata": {
                   "server-tag": "all"
               }
           },
           "count": 1
       }
   }


.. _command-remote-global-parameter4-get-all:

The remote-global-parameter4-get-all, remote-global-parameter6-get-all Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch all global DHCP parameters from the
database. They include no arguments besides the optional ``remote`` map.

.. _command-remote-global-parameter4-set:

The remote-global-parameter4-set Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to create scalar global DHCP parameters in the
database. If any of the parameters already exists, its value is replaced
as a result of this command. It is possible to set multiple parameters
within a single command, each having one of the four types: string,
integer, real, and boolean. For example:

::

   {
       "command": "remote-global-parameter4-set"
       "arguments": {
           "parameters": {
               "boot-file-name": "/dev/null",
               "renew-timer": 2000,
               "t1-percent": 0.85,
               "match-client-id": true
           },
           "remote": {
               "type": "mysql"
           }
       }
   }


An error is returned if any of the parameters is not supported by the
DHCP server or its type does not match. Care should be taken when
multiple parameters are specified in a single command, because it is
possible that only some of the parameters are stored successfully and
some fail. If an error occurs when processing this command, it is
recommended to use ``remote-global-parameter[46]-get-all`` to check
which of the parameters have been stored/updated successfully and which
have failed.

.. _command-remote-network4-del:

The remote-network4-del, remote-network6-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete an IPv4 or IPv6 shared network from
the database. The optional parameter ``subnets-action`` determines
whether the subnets belonging to the deleted shared network should also
be deleted or preserved. The ``subnets-action`` parameter defaults to ``keep``,
which preserves the subnets. If it is set to ``delete``, the subnets are
deleted along with the shared network.

The following command:

::

   {
       "command": "remote-network6-del",
       "arguments": {
           "shared-networks": [
               {
                   "name": "level3"
               }
           ],
           "subnets-action": "keep",
           "remote": {
               "type": "mysql"
           }
       }
   }


deletes the "level3" IPv6 shared network. The subnets are preserved, but
they are disassociated from the deleted shared network and become
global. This behavior corresponds to the behavior of the
``network[46]-del`` commands with respect to the ``subnets-action`` parameter.

.. _command-remote-network4-get:

The remote-network4-get, remote-network6-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to retrieve information about an IPv4 or
IPv6 shared network. The optional parameter ``subnets-include`` denotes
whether the subnets belonging to the shared network should also be
returned. This parameter defaults to ``no``, in which case the subnets
are not returned. If this parameter is set to ``full``, the subnets are
returned together with the shared network.

The following command fetches the "level3" IPv6 shared network along
with the full information about the subnets belonging to it:

::

   {
       "command": "remote-network6-get",
       "arguments": {
           "shared-networks": [
               {
                   "name": "level3"
               }
           ],
           "subnets-include": "full",
           "remote": {
               "type": "mysql"
           }
       }
   }


.. _command-remote-network4-list:

The remote-network4-list, remote-network6-list Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to list all IPv4 or IPv6 shared networks in the
particular database. The returned information about each shared network
merely contains the shared network name and the metadata. To
fetch detailed information about the selected shared network, use
the ``remote-network[46]-get`` command.

The ``remote-network[46]-list`` takes no argument except the optional
``remote`` map.

.. _command-remote-network4-set:

The remote-network4-set, remote-network6-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands create a new or replace an existing IPv4 or IPv6 shared
network in the database. The structure of the shared network information
is the same as in the Kea configuration file (see
:ref:`shared-network4` and :ref:`shared-network6` for details),
except that specifying subnets along with the shared
network information is not allowed. Including the ``subnet4`` or ``subnet6`` parameter
within the shared network information will result in an error.

These commands are intended to be used for managing the shared
network-specific information and DHCP options. In order to associate and
disassociate the subnets with the shared networks, the
``remote-subnet[46]-set`` commands should be used.

The following command adds the IPv6 shared network "level3" to the
database:

::

   {
       "command": "remote-network6-set",
       "arguments": {
           "shared-networks": [
               {
                   "name": "level3",
                   "interface": "eth0",
                   "option-data": [ {
                       "name": "sntp-servers",
                       "data": "2001:db8:1::1"
                   } ],
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


This command includes the ``interface`` parameter, which sets the shared
network-level interface name. Any remaining shared network-level parameters,
which are not specified with the command, will be marked as
"unspecified" in the database. The DHCP server will use the global
values for unspecified parameters or, if the global values are not
specified, the default values will be used.

.. note::

   As with other "set" commands, this command replaces all the
   information about the given shared network in the database, if the
   shared network already exists. Therefore, when sending this command,
   make sure to always include all parameters that must be specified for
   the updated shared-network instance. Any unspecified parameter will
   be marked unspecified in the database, even if its value was present
   prior to sending the command.

.. _command-remote-option-def4-del:

The remote-option-def4-del, remote-option-def6-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete a DHCP option definition from the
database. The option definition is identified by an option code and
option space. For example:

::

   {
       "command": "remote-option-def6-del",
       "arguments": {
           "option-defs": [
               {
                   "code": 1,
                   "space": "isc"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


deletes the definition of the option having the code of 1 and belonging
to the option space "isc". The default option spaces are "dhcp4" and
"dhcp6" for the DHCPv4 and DHCPv6 top-level options, respectively.

.. _command-remote-option-def4-get:

The remote-option-def4-get, remote-option-def6-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch a specified DHCP option definition from
the database. The option definition is identified by the option code and
option space. The default option spaces are "dhcp4" and "dhcp6" for the
DHCPv4 and DHCPv6 top-level options, respectively.

The following command retrieves a DHCPv4 option definition having the
code of 1 and belonging to option space "isc":

::

   {
       "command": "remote-option-def4-get"
       "arguments": {
           "option-defs": [
               {
                   "code": 1,
                   "space": "isc"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


.. _command-remote-option-def4-get-all:

The remote-option-def4-get-all, remote-option-def6-get-all Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch all DHCP option definitions from the
database. They take no arguments except the optional ``remote`` map.

.. _command-remote-option-def4-set:

The remote-option-def4-set, remote-option-def6-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands create a new DHCP option definition or replace an
existing option definition in the database. The structure of the option
definition information is the same as in the Kea configuration file (see
:ref:`dhcp4-custom-options` and :ref:`dhcp6-custom-options`).
The following command creates the DHCPv4 option definition in the
top-level "dhcp4" option space:

::

   {
       "command": "remote-option-def4-set",
       "arguments": {
           "option-defs": [
               {
                   "name": "foo",
                   "code": 222,
                   "type": "uint32",
                   "array": false,
                   "record-types": "",
                   "space": "dhcp4",
                   "encapsulate": ""
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


.. _command-remote-option4-global-del:

The remote-option4-global-del, remote-option6-global-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete a global DHCP option from the
database. The option is identified by an option code and option space.
For example:

::

   {
       "command": "remote-option4-global-del",
       "arguments": {
           "options": [
               {
                   "code": 5
                   "space": "dhcp4"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


The "dhcp4" is the top-level option space where the standard DHCPv4
options belong.

.. _command-remote-option4-global-get:

The remote-option4-global-get, remote-option6-global-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch a global DHCP option from the database.
The option is identified by the code and option space. The top-level
option spaces where DHCP standard options belong are called "dhcp4" and
"dhcp6" for the DHCPv4 and DHCPv6 servers, respectively.

The following command retrieves the IPv6 "DNS Servers" (code 23) option:

::

   {
       "command": remote-option6-global-get",
       "arguments": {
           "options": [
               {
                   "code": 23,
                   "space": "dhcp6"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


.. _command-remote-option4-global-get-all:

The remote-option4-global-get-all, remote-option6-global-get-all Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch all global DHCP options from the
configuration database. They take no arguments except the optional
``remote`` map.

.. _command-remote-option4-global-set:

The remote-option4-global-set, remote-option6-global-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands create a new global DHCP option or replace an existing
option in the database. The structure of the option information is the
same as in the Kea configuration file (see :ref:`dhcp4-std-options`
and :ref:`dhcp4-std-options`). For example:

::

   {
       "command": "remote-option6-global-set",
       "arguments": {
           "options": [
               {
                   "name": "dns-servers",
                   "data": "2001:db8:1::1"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


Note that specifying an option name instead of the option code only
works reliably for the standard DHCP options. When specifying a value
for the user-defined DHCP option, the option code should be specified
instead of the name. For example:

::

   {
       "command": "remote-option6-global-set",
       "arguments": {
           "options": [
               {
                   "code": 1,
                   "space": "isc",
                   "data": "2001:db8:1::1"
               }
           ]
       }
   }


.. _command-remote-subnet4-del-by-id:

The remote-subnet4-del-by-id, remote-subnet6-del-by-id Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the first variant of the commands used to delete an IPv4 or IPv6
subnet from the database. It uses the subnet ID to identify the subnet. For
example, to delete the IPv4 subnet with an ID of 5:

::

   {
       "command": "remote-subnet4-del-by-id",
       "arguments": {
           "subnets": [
               {
                   "id": 5
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


.. _command-remote-subnet4-del-by-prefix:

The remote-subnet4-del-by-prefix, remote-subnet6-del-by-prefix Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the second variant of the commands used to delete an IPv4 or
IPv6 subnet from the database. It uses the subnet prefix to identify the
subnet. For example:

::

   {
       "command": "remote-subnet6-del-by-prefix",
       "arguments": {
           "subnets": [
               {
                   "subnet": "2001:db8:1::/64"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


.. _command-remote-subnet4-get-by-id:

The remote-subnet4-get-by-id, remote-subnet6-get-by-id Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the first variant of the commands used to fetch an IPv4 or IPv6
subnet from the database. It uses a subnet ID to identify the subnet.
For example:

::

   {
       "command": "remote-subnet4-get-by-id",
       "arguments": {
           "subnets": [
               {
                   "id": 5
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


.. _command-remote-subnet4-get-by-prefix:

The remote-subnet4-get-by-prefix, remote-subnet6-get-by-prefix Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the second variant of the commands used to fetch an IPv4 or IPv6
subnet from the database. It uses a subnet prefix to identify the
subnet. For example:

::

   {
       "command": "remote-subnet6-get-by-prefix",
       "arguments": {
           "subnets": [
               {
                   "subnet": "2001:db8:1::/64"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


.. _command-remote-subnet4-list:

The remote-subnet4-list, remote-subnet6-list Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to list all IPv4 or IPv6 subnets from the
database. They take no parameters except the optional ``remote`` map. The
returned information about each subnet is limited to subnet identifier,
prefix, and associated shared network name. To retrieve full
information about the selected subnet, use the
``remote-subnet[46]-get-by-id`` or ``remote-subnet[46]-get-by-prefix`` command.

.. _command-remote-subnet4-set:

The remote-subnet4-set, remote-subnet6-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to create a new IPv4 or IPv6 subnet or replace
an existing subnet in the database. Setting the subnet also associates
or disassociates the subnet with a shared network.

The structure of the subnet information is similar to the structure used
in the configuration file (see :ref:`dhcp4-configuration` and
:ref:`dhcp6-configuration`). The subnet information conveyed in the
``remote-subnet[46]-set`` command must include the additional parameter
``shared-network-name``, which denotes whether the subnet belongs to a
shared network.

Consider the following example:

::

   {
       "command": "remote-subnet4-set",
       "arguments": {
           "subnets": [
               {
                   "id": 5,
                   "subnet": "192.0.2.0/24",
                   "shared-network-name": "level3",
                   "pools": [ { "pool": "192.0.2.100-192.0.2.200" } ],
                   "option-data": [ {
                       "name": "routers",
                       "data": "192.0.2.1"
                   } ]
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }


It creates the subnet and associates it with the "level3" shared
network. The "level3" shared network must be created with the ``remote-network4-set``
command prior to creating the subnet.

If the created subnet must be global - that is, not associated with any shared
network - the ``shared-network-name`` must be explicitly set to
``null``:

::

   {
       "command": "remote-subnet4-set",
       "arguments": {
           "subnets": [
               {
                   "id": 5,
                   "subnet": "192.0.2.0/24",
                   "shared-network-name": null,
                   "pools": [ { "pool": "192.0.2.100-192.0.2.200" } ],
                   "option-data": [ {
                       "name": "routers",
                       "data": "192.0.2.1"
                   } ]
              }
           ]
       }
   }


The subnet created in the previous example is replaced with the new
subnet having the same parameters, but it becomes global.

The ``shared-network-name`` parameter is mandatory for the
``remote-subnet4-set`` command.

.. note::

   As with other "set" commands, this command replaces all the
   information about the particular subnet in the database, if the
   subnet information is already present. Therefore, when sending this
   command, make sure to always include all parameters that must be
   specified for the updated subnet instance. Any unspecified parameter
   will be marked as unspecified in the database, even if its value was
   present prior to sending the command.
