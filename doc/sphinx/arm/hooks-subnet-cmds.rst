.. _hooks-subnet-cmds:

``subnet_cmds``: Subnet Commands to Manage Subnets and Shared Networks
======================================================================

This library offers commands used to query and manipulate subnet and shared network
configurations in Kea. These can be very useful in deployments
with a large number of subnets being managed by the DHCP servers,
when those subnets are frequently updated. The commands offer a lightweight
approach for manipulating subnets without needing to fully reconfigure
the server, and without affecting existing servers' configurations. An
ability to manage shared networks (listing, retrieving details, adding
new ones, removing existing ones, and adding subnets to and removing them from
shared networks) is also provided.

This library is only available to ISC customers with a paid support
contract.

.. note::

   This library can only be loaded by the ``kea-dhcp4`` or ``kea-dhcp6``
   process.

The following commands are currently supported:

-  ``subnet4-list``/``subnet6-list`` - lists all configured subnets.

-  ``subnet4-get``/``subnet6-get`` - retrieves detailed information about a
   specified subnet.

-  ``subnet4-add``/``subnet6-add`` - adds a new subnet into the server's
   configuration.

-  ``subnet4-update``/``subnet6-update`` - updates (replaces) a single subnet in
   the server's configuration.

-  ``subnet4-del``/``subnet6-del`` - removes a subnet from the server's
   configuration.

-  ``subnet4-delta-add``/``subnet6-delta-add`` - updates (replaces) parts of a
   single subnet in the server's configuration.

-  ``subnet4-delta-del``/``subnet6-delta-del`` - removes parts of a single subnet in
   the server's configuration.

-  ``network4-list``/``network6-list`` - lists all configured shared networks.

-  ``network4-get``/``network6-get`` - retrieves detailed information about a
   specified shared network.

-  ``network4-add``/``network6-add`` - adds a new shared network to the
   server's configuration.

-  ``network4-del``/``network6-del`` - removes a shared network from the
   server's configuration.

-  ``network4-subnet-add``/``network6-subnet-add`` - adds an existing subnet to
   an existing shared network.

-  ``network4-subnet-del``/``network6-subnet-del`` - removes a subnet from
   an existing shared network and demotes it to a plain subnet.

.. _command-subnet4-list:

The ``subnet4-list`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to list all currently configured subnets. Each
subnet is returned with a subnet identifier and
subnet prefix. To retrieve
detailed information about the subnet, use the ``subnet4-get`` command.

This command has a simple structure:

::

   {
       "command": "subnet4-list"
   }

The list of subnets is returned in the following format:

::

   {
       "result": 0,
       "text": "2 IPv4 subnets found",
       "arguments": {
       "subnets": [
           {
               "id": 10,
               "subnet": "10.0.0.0/8"
           },
           {
               "id": 100,
               "subnet": "192.0.2.0/24"
           }
       ]
   }

If no IPv4 subnets are found, an error code is returned along with the
error description.

.. _command-subnet6-list:

The ``subnet6-list`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to list all currently configured subnets. Each
subnet is returned with a subnet identifier and
subnet prefix. To retrieve
detailed information about the subnet, use the ``subnet6-get`` command.

This command has a simple structure:

::

   {
       "command": "subnet6-list"
   }

The list of subnets is returned in the following format:

::

   {
       "result": 0,
       "text": "2 IPv6 subnets found",
       "arguments": {
       "subnets": [
           {
               "id": 11,
               "subnet": "2001:db8:1::/64"
           },
           {
               "id": 233,
               "subnet": "3000::/16"
           }
       ]
   }

If no IPv6 subnets are found, an error code is returned along with the
error description.

.. _command-subnet4-get:

The ``subnet4-get`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to retrieve detailed information about the
specified subnet. This command usually follows ``subnet4-list``,
which is used to discover available subnets with their respective subnet
identifiers and prefixes. Any of those parameters can then be used in
``subnet4-get`` to fetch subnet information:

::

   {
       "command": "subnet4-get",
       "arguments": {
           "id": 10
       }
   }

or

::

   {
       "command": "subnet4-get",
       "arguments": {
           "subnet": "10.0.0.0/8"
       }
   }

If the subnet exists, the response will be similar to this:

::

   {
       "result": 0,
       "text": "Info about IPv4 subnet 10.0.0.0/8 (id 10) returned",
       "arguments": {
           "subnets": [
               {
                   "subnet": "10.0.0.0/8",
                   "id": 1,
                   "option-data": [
                       ....
                   ]
                   ...
               }
           ]
       }
   }

.. _command-subnet6-get:

The ``subnet6-get`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to retrieve detailed information about the
specified subnet. This command usually follows ``subnet6-list``,
which is used to discover available subnets with their respective subnet
identifiers and prefixes. Any of those parameters can be then used in
``subnet6-get`` to fetch subnet information:

::

   {
       "command": "subnet6-get",
       "arguments": {
           "id": 11
       }
   }

or

::

   {
       "command": "subnet6-get",
       "arguments": {
           "subnet": "2001:db8:1::/64"
       }
   }

If the subnet exists, the response will be similar to this:

::

   {
       "result": 0,
       "text": "Info about IPv6 subnet 2001:db8:1::/64 (id 11) returned",
       "arguments": {
           "subnets": [
               {
                   "subnet": "2001:db8:1::/64",
                   "id": 1,
                   "option-data": [
                       ...
                   ]
                   ....
               }
           ]
       }
   }

.. _command-subnet4-add:

The ``subnet4-add`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to create and add a new subnet to the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier must be specified and must be unique among all subnets. If
the identifier or a subnet prefix is not unique, an error is reported and
the subnet is not added.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations cannot be specified within
``subnet4-add``. The commands described in :ref:`hooks-host-cmds` should be used to
add, remove, and modify static reservations.

::

   {
       "command": "subnet4-add",
       "arguments": {
           "subnet4": [ {
               "id": 123,
               "subnet": "10.20.30.0/24",
               ...
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv4 subnet added",
       "arguments": {
           "subnet4": [
               {
                   "id": 123,
                   "subnet": "10.20.30.0/24"
               }
           ]
       }
   }

.. _command-subnet6-add:

The ``subnet6-add`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to create and add a new subnet to the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier must be specified and must be unique among all subnets. If
the identifier or a subnet prefix is not unique, an error is reported and
the subnet is not added.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations cannot be specified within
``subnet6-add``. The commands described in :ref:`hooks-host-cmds` should be used
to add, remove, and modify static reservations.

::

   {
       "command": "subnet6-add",
       "arguments": {
           "subnet6": [ {
               "id": 234,
               "subnet": "2001:db8:1::/64",
               ...
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv6 subnet added",
       "arguments": {
           "subnet6": [
               {
                   "id": 234,
                   "subnet": "2001:db8:1::/64"
               }
           ]
       }
   }

It is recommended, but not mandatory, to specify the subnet ID. If not
specified, Kea will try to assign the next ``subnet-id`` value. This
automatic ID value generator is simple; it returns the previous
automatically assigned value, increased by 1. This works well, unless
a subnet is manually created with a larger value than one previously used. For
example, if ``subnet4-add`` is called five times, each without an ID, Kea will
assign IDs 1, 2, 3, 4, and 5 and it will work just fine. However, if
``subnet4-add`` is called five times, with the first subnet having the
``subnet-id`` of value 3 and the remaining ones having no ``subnet-id``, the operation will
fail. The first command (with the explicit value) will use ``subnet-id`` 3; the
second command will create a subnet with and ID of 1; the third will use a
value of 2; and finally the fourth will have its ``subnet-id`` value
auto-generated as 3. However, since there is already a subnet with that
ID, the process will fail.

The general recommendation is either never to use explicit values, so
that auto-generated values will always work; or always use explicit
values, so that auto-generation is never used. The two
approaches can be mixed only if the administrator understands how internal
automatic ``subnet-id`` generation works in Kea.

.. note::

   Subnet IDs must be greater than zero and less than 4294967295.

.. _command-subnet4-update:

The ``subnet4-update`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to update (overwrite) a single subnet in the existing
server configuration. This operation has no impact on other subnets. The
subnet identifier is used to identify the subnet to replace; it must be
specified and must be unique among all subnets. The subnet prefix should
not be updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations cannot be specified within
``subnet4-update``. The commands described in :ref:`hooks-host-cmds` should be
used to update, remove, and modify static reservations.

::

   {
       "command": "subnet4-update",
       "arguments": {
           "subnet4": [ {
               "id": 123,
               "subnet": "10.20.30.0/24",
               ...
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv4 subnet updated",
       "arguments": {
           "subnet4": [
               {
                   "id": 123,
                   "subnet": "10.20.30.0/24"
               }
           ]
       }
   }

.. _command-subnet6-update:

The ``subnet6-update`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to update (overwrite) a single subnet in the existing
server configuration. This operation has no impact on other subnets. The
subnet identifier is used to identify the subnet to replace; it must be
specified and must be unique among all subnets. The subnet prefix should
not be updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations cannot be specified within
``subnet6-update``. The commands described in :ref:`hooks-host-cmds` should be
used to update, remove, and modify static reservations.

::

   {
       "command": "subnet6-update",
       "arguments": {
           "subnet6": [ {
               "id": 234,
               "subnet": "2001:db8:1::/64",
               ...
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv6 subnet updated",
       "arguments": {
           "subnet6": [
               {
                   "id": 234,
                   "subnet": "2001:db8:1::/64"
               }
           ]
       }
   }

.. _command-subnet4-del:

The ``subnet4-del`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to remove a subnet from the server's configuration.
This command has no effect on other configured subnets, but removing a
subnet does have certain implications.

In most cases the server has assigned some leases to the clients
belonging to the subnet. The server may also be configured with static
host reservations which are associated with this subnet. The current
implementation of the ``subnet4-del`` command removes neither the leases nor
the host reservations associated with a subnet. This is the safest approach
because the server does not lose track of leases assigned to the clients
from this subnet. However, removal of the subnet may still cause
configuration errors and conflicts. For example: after removal of the
subnet, the server administrator may update a new subnet with the ID
used previously for the removed subnet. This means that the existing
leases and static reservations will be in conflict with this new subnet.
Thus, we recommend that this command be used with extreme caution.

This command can also be used to completely delete an IPv4 subnet that
is part of a shared network. To simply remove the subnet
from a shared network and keep the subnet configuration, use the
``network4-subnet-del`` command instead.

The command has the following structure:

::

   {
       "command": "subnet4-del",
       "arguments": {
           "id": 123
       }
   }

A successful response may look like this:

::

   {
       "result": 0,
       "text": "IPv4 subnet 192.0.2.0/24 (id 123) deleted",
       "arguments": {
           "subnets": [
               {
                   "id": 123,
                   "subnet": "192.0.2.0/24"
               }
           ]
       }
   }

.. _command-subnet6-del:

The ``subnet6-del`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to remove a subnet from the server's configuration.
This command has no effect on other configured subnets, but removing a
subnet does have certain implications.

In most cases the server has assigned some leases to the clients
belonging to the subnet. The server may also be configured with static
host reservations which are associated with this subnet. The current
implementation of the ``subnet6-del`` command removes neither the leases nor
the host reservations associated with a subnet. This is the safest approach
because the server does not lose track of leases assigned to the clients
from this subnet. However, removal of the subnet may still cause
configuration errors and conflicts. For example: after removal of the
subnet, the server administrator may add a new subnet with the ID used
previously for the removed subnet. This means that the existing leases
and static reservations will be in conflict with this new subnet. Thus,
we recommend that this command be used with extreme caution.

This command can also be used to completely delete an IPv6 subnet that
is part of a shared network. To simply remove the subnet
from a shared network and keep the subnet configuration, use the
``network6-subnet-del`` command instead.

The command has the following structure:

::

   {
       "command": "subnet6-del",
       "arguments": {
           "id": 234
       }
   }

A successful response may look like this:

::

   {
       "result": 0,
       "text": "IPv6 subnet 2001:db8:1::/64 (id 234) deleted",
       "subnets": [
           {
               "id": 234,
               "subnet": "2001:db8:1::/64"
           }
       ]
   }

.. _command-subnet4-delta-add:

The ``subnet4-delta-add`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to update a subnet by adding or overwriting its parts in
the existing server configuration. This operation has no impact on other
subnets. The subnet identifier is used to identify the subnet to update; it must
be specified and must be unique among all subnets. The subnet prefix should not
be updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations cannot be specified within
``subnet4-delta-add``. The commands described in :ref:`hooks-host-cmds` should
be used to update, remove, and modify static reservations.

::

   {
       "command": "subnet4-delta-add",
       "arguments": {
           "subnet4": [ {
               "valid-lifetime": 120,
               "id": 123,
               "subnet": "10.20.30.0/24",
               "option-data": [
                   {
                       "always-send": false,
                       "code": 3,
                       "csv-format": true,
                       "data": "192.0.3.1",
                       "name": "routers",
                       "space": "dhcp4"
                   }
               ],
               "pools": [
                   {
                       "pool": "10.20.30.1-10.20.30.10",
                       "option-data": [
                           {
                               "always-send": false,
                               "code": 4,
                               "csv-format": true,
                               "data": "192.0.4.1",
                               "name": "time-servers",
                               "space": "dhcp4"
                           }
                       ]
                   }
               ]
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv4 subnet updated",
       "arguments": {
           "subnet4": [
               {
                   "id": 123,
                   "subnet": "10.20.30.0/24"
               }
           ]
       }
   }

The command updates subnet "10.20.30.0/24" with id 123 by changing the valid
lifetime, adding or changing the subnet level option 3 ("routers"), by adding
or changing the pool "10.20.30.1-10.20.30.10" and by adding or changing the pool
level option 4 ("time-servers").

.. _command-subnet6-delta-add:

The ``subnet6-delta-add`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to update a subnet by adding or overwriting its parts in
the existing server configuration. This operation has no impact on other
subnets. The subnet identifier is used to identify the subnet to update; it must
be specified and must be unique among all subnets. The subnet prefix should not
be updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations cannot be specified within
``subnet6-delta-add``. The commands described in :ref:`hooks-host-cmds` should
be used to update, remove, and modify static reservations.

::

   {
       "command": "subnet6-delta-add",
       "arguments": {
           "subnet6": [ {
               "valid-lifetime": 120,
               "id": 243,
               "subnet": "2001:db8:1::/64",
               "option-data": [
                   {
                       "always-send": false,
                       "code": 23,
                       "csv-format": true,
                       "data": "3000::3:1",
                       "name": "dns-servers",
                       "space": "dhcp6"
                   }
               ],
               "pd-pools": [
                   {
                       "prefix": "2001:db8:2::",
                       "prefix-len": 48,
                       "delegated-len": 64,
                       "option-data": [
                           {
                               "always-send": false,
                               "code": 22,
                               "csv-format": true,
                               "data": "3000::4:1",
                               "name": "sip-server-addr",
                               "space": "dhcp6"
                           }
                       ]
                   }
               ],
               "pools": [
                   {
                       "pool": "2001:db8:1::1-2001:db8:1::10",
                       "option-data": [
                           {
                               "always-send": false,
                               "code": 31,
                               "csv-format": true,
                               "data": "3000::5:1",
                               "name": "sntp-servers",
                               "space": "dhcp6"
                           }
                       ]
                   }
               ]
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv6 subnet updated",
       "arguments": {
           "subnet6": [
               {
                   "id": 234,
                   "subnet": "2001:db8:1::/64"
               }
           ]
       }
   }

The command updates subnet "2001:db8:1::/64" with id 243 by changing the valid
lifetime, adding or changing the subnet level option 23 ("dns-servers"), by
adding or changing the pool "2001:db8:1::1-2001:db8:1::10", by adding or
changing the pool level option 31 ("sntp-servers"), by adding or changing the
pd-pool "2001:db8:2::" with prefix-len 48 and by adding or changing the pd-pool
level option 22 ("sip-server-addr").

.. _command-subnet4-delta-del:

The ``subnet4-delta-del`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to update a subnet by removing its parts in the existing
server configuration. This operation has no impact on other subnets.
The subnet identifier is used to identify the subnet to update; it must be
specified and must be unique among all subnets. The subnet prefix should not be
updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations cannot be specified within
``subnet4-delta-del``. The commands described in :ref:`hooks-host-cmds` should
be used to update, remove, and modify static reservations.

The command is flexible and can delete the part of the subnet by either
specifying the entire object that needs to be deleted, or just the keys
identifying the respective object. The address pools are identified by the
'pool' parameter, the options are identified by the 'name' or 'code' and
'space' parameters. The 'space' parameter can be omitted if the option belongs
to the default 'dhcp4' space.

::

   {
       "command": "subnet4-delta-del",
       "arguments": {
           "subnet4": [ {
               "valid-lifetime": 0,
               "id": 123,
               "subnet": "10.20.30.0/24",
               "option-data" [
                   { "name": "routers" }
               ]
               "pools": [
                   {
                       "option-data": [
                           { "code": 4 }
                       ]
                       "pool": "10.20.30.11-10.20.30.20"
                   },
                   {
                       "pool": "10.20.30.21-10.20.30.30"
                   }
               ]
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv4 subnet updated",
       "arguments": {
           "subnet4": [
               {
                   "id": 123,
                   "subnet": "10.20.30.0/24"
               }
           ]
       }
   }

The command updates subnet "10.20.30.0/24" with id 123 by removing the valid
lifetime, removing the subnet level option 3 ("routers"), by removing the pool
"10.20.30.21-10.20.30.30" and by removing the pool level option 4
("time-servers") in pool "10.20.30.11-10.20.30.20".
The scalar values don't need to match what is configured, but still need to be
present to maintain a valid json structure and to be a valid value to be able to
be parsed.

.. _command-subnet6-delta-del:

The ``subnet6-delta-del`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to update a subnet by removing its parts in the existing
server configuration. This operation has no impact on other subnets.
The subnet identifier is used to identify the subnet to update; it must be
specified and must be unique among all subnets. The subnet prefix should not be
updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations cannot be specified within
``subnet6-delta-del``. The commands described in :ref:`hooks-host-cmds` should
be used to update, remove, and modify static reservations.

The command is flexible and can delete the part of the subnet by either
specifying the entire object that needs to be deleted, or just the keys
identifying the respective object. The address pools are identified by the
'pool' parameter, the prefix pools are identified by the "prefix", "prefix-len"
and "delegated-len" parameters, the options are identified by the 'name' or
'code' and 'space' parameters. The 'space' parameter can be omitted if the
option belongs to the default 'dhcp6' space.

.. code-block:: json

   {
       "command": "subnet6-delta-del",
       "arguments": {
           "subnet6": [ {
               "valid-lifetime": 0,
               "id": 234,
               "subnet": "2001:db8:1::/64",
               "option-data" [
                   { "name": "dns-servers" }
               ]
               "pd-pools": [
                   {
                       "prefix": "2001:db8:3::",
                       "prefix-len": 48,
                       "delegated-len": 64,
                       "option-data": [
                           { "code": 22 }
                       ]
                   },
                   {
                       "prefix": "2001:db8:4::",
                       "prefix-len": 48,
                       "delegated-len": 64
                   }
               ],
               "pools": [
                   {
                       "option-data": [
                           { "code": 31 }
                       ]
                       "pool": "2001:db8:1::11-2001:db8:1::20"
                   },
                   {
                       "pool": "2001:db8:1::21-2001:db8:1::30"
                   }
               ]
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv6 subnet updated",
       "arguments": {
           "subnet6": [
               {
                   "id": 234,
                   "subnet": "2001:db8:1::/64"
               }
           ]
       }
   }

The command updates subnet "2001:db8:1::/64" with id 243 by removing the valid
lifetime, removing the subnet level option 23 ("dns-servers"), by removing the
pool "2001:db8:1::21-2001:db8:1::30", by removing the pool level option 31
("sntp-servers") in pool "2001:db8:1::11-2001:db8:1::20", by removing the
pd-pool "2001:db8:4::" with prefix-len 48, by removing the pd-pool level option
22 ("sip-server-addr") in pd-pool "2001:db8:3::" with prefix-len 48.
The scalar values don't need to match what is configured, but still need to be
present to maintain a valid json structure and to be a valid value to be able to
be parsed.

.. _command-network4-list:

.. _command-network6-list:

The ``network4-list``, ``network6-list`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to retrieve the full list of currently configured
shared networks. The list contains only very basic information about
each shared network. If more details are needed, please use
``network4-get`` or ``network6-get`` to retrieve all information
available. This command does not require any parameters and its
invocation is very simple:

::

   {
       "command": "network4-list"
   }

An example response for ``network4-list`` looks as follows:

::

   {
       "arguments": {
           "shared-networks": [
               { "name": "floor1" },
               { "name": "office" }
           ]
       },
       "result": 0,
       "text": "2 IPv4 network(s) found"
   }

The ``network6-list`` command uses exactly the same syntax for both the
command and the response.

.. _command-network4-get:

.. _command-network6-get:

The ``network4-get``, ``network6-get`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to retrieve detailed information about shared
networks, including subnets that are currently part of a given network.
Both commands take one mandatory parameter, ``name``, which specifies the
name of the shared network. An example command to retrieve details about
an IPv4 shared network with the name "floor13" looks as follows:

::

   {
       "command": "network4-get",
       "arguments": {
           "name": "floor13"
       }
   }

An example response could look as follows:

::

   {
       "result": 0,
       "text": "Info about IPv4 shared network 'floor13' returned",
       "arguments": {
           "shared-networks": [
           {
               "match-client-id": true,
               "name": "floor13",
               "option-data": [ ],
               "rebind-timer": 90,
               "relay": {
                   "ip-address": "0.0.0.0"
               },
               "renew-timer": 60,
               # "reservation-mode": "all",
               # It is replaced by the "reservations-global"
               # "reservations-in-subnet" and "reservations-out-of-pool"
               # parameters.
               # Specify if the server should lookup global reservations.
               "reservations-global": false,
               # Specify if the server should lookup in-subnet reservations.
               "reservations-in-subnet": true,
               # Specify if the server can assume that all reserved addresses
               # are out-of-pool.
               "reservations-out-of-pool": false,
               "subnet4": [
                   {
                       "subnet": "192.0.2.0/24",
                       "id": 5,
                       # many other subnet-specific details here
                   },
                   {
                       "id": 6,
                       "subnet": "192.0.3.0/31",
                       # many other subnet-specific details here
                   }
               ],
               "valid-lifetime": 120
           }
           ]
       }
   }

The actual response contains many additional fields that are
omitted here for clarity. The response format is exactly the same as
used in ``config-get``, just limited to returning the shared network's
information.

.. _command-network4-add:

.. _command-network6-add:

The ``network4-add``, ``network6-add`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to add a new shared network, which must
have a unique name. This command requires one parameter,
``shared-networks``, which is a list and should contain exactly one
entry that defines the network. The only mandatory element for a network
is its name. Although it does not make operational sense, it is possible
to add an empty shared network that does not have any subnets in it.
That is allowed for testing purposes, but having empty networks (or networks with
only one subnet) is discouraged in production environments. For details
regarding syntax, see :ref:`shared-network4` and
:ref:`shared-network6`.

.. note::

   As opposed to parameter inheritance during the processing of a full new
   configuration, this command does not fully handle parameter inheritance.
   Any missing parameters will be filled with default values, rather
   than inherited from the global scope.

An example that showcases how to add a new IPv4 shared network looks as
follows:

::

   {
       "command": "network4-add",
       "arguments": {
           "shared-networks": [ {
               "name": "floor13",
               "subnet4": [
               {
                   "id": 100,
                   "pools": [ { "pool": "192.0.2.2-192.0.2.99" } ],
                   "subnet": "192.0.2.0/24",
                   "option-data": [
                       {
                           "name": "routers",
                           "data": "192.0.2.1"
                       }
                   ]
               },
               {
                   "id": 101,
                   "pools": [ { "pool": "192.0.3.2-192.0.3.99" } ],
                   "subnet": "192.0.3.0/24",
                   "option-data": [
                       {
                           "name": "routers",
                           "data": "192.0.3.1"
                       }
                   ]
               } ]
           } ]
       }
   }

Assuming there was no shared network with a name "floor13" and no subnets
with IDs 100 and 101 previously configured, the command will be
successful and will return the following response:

::

   {
       "arguments": {
           "shared-networks": [ { "name": "floor13" } ]
       },
       "result": 0,
       "text": "A new IPv4 shared network 'floor13' added"
   }

The ``network6-add`` command uses the same syntax for both the query and the
response. However, there are some parameters that are IPv4-only (e.g.
``match-client-id``) and some that are IPv6-only (e.g. ``interface-id``). The same
applies to subnets within the network.

.. _command-network4-del:

.. _command-network6-del:

The ``network4-del``, ``network6-del`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete existing shared networks. Both
commands take exactly one parameter, ``name``, that specifies the name of
the network to be removed. An example invocation of the ``network4-del``
command looks as follows:

::

   {
       "command": "network4-del",
       "arguments": {
           "name": "floor13"
       }
   }

Assuming there was such a network configured, the response will look
similar to the following:

::

   {
       "arguments": {
           "shared-networks": [
               {
                   "name": "floor13"
               }
           ]
       },
       "result": 0,
       "text": "IPv4 shared network 'floor13' deleted"
   }

The ``network6-del`` command uses exactly the same syntax for both the
command and the response.

If there are any subnets belonging to the shared network being deleted,
they will be demoted to a plain subnet. There is an optional parameter
called ``subnets-action`` that, if specified, takes one of two possible
values: ``keep`` (which is the default) and ``delete``. It controls
whether the subnets are demoted to plain subnets or removed. An example
usage in the ``network6-del`` command that deletes the shared network and all
subnets in it could look as follows:

::

   {
       "command": "network4-del",
       "arguments": {
           "name": "floor13",
           "subnets-action": "delete"
       }
   }

Alternatively, to completely remove the subnets, it is possible to use the
``subnet4-del`` or ``subnet6-del`` commands.

.. _command-network4-subnet-add:

.. _command-network6-subnet-add:

The ``network4-subnet-add``, ``network6-subnet-add`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to add existing subnets to existing shared
networks. There are several ways to add a new shared network. The system
administrator can add the whole shared network at once, either by
editing a configuration file or by calling the ``network4-add`` or
``network6-add`` command with the desired subnets in it. This approach
works well for completely new shared subnets. However, there may be
cases when an existing subnet is running out of addresses and needs to
be extended with additional address space; in other words, another subnet
needs to be added on top of it. For this scenario, a system administrator
can use ``network4-add`` or ``network6-add``, and then add an existing
subnet to this newly created shared network using
``network4-subnet-add`` or ``network6-subnet-add``.

The ``network4-subnet-add`` and ``network6-subnet-add`` commands take
two parameters: ``id``, which is an integer and specifies the ID of
an existing subnet to be added to a shared network; and ``name``, which
specifies the name of the shared network to which the subnet will be added. The
subnet must not belong to any existing network; to
reassign a subnet from one shared network to another, use the
``network4-subnet-del`` or ``network6-subnet-del`` commands first.

An example invocation of the ``network4-subnet-add`` command looks as
follows:

::

   {
       "command": "network4-subnet-add",
       "arguments": {
           "name": "floor13",
           "id": 5
       }
   }

Assuming there is a network named "floor13", and there is a subnet with
``subnet-id`` 5 that is not a part of the existing network, the command will
return a response similar to the following:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now part of shared network 'floor13'"
   }

The ``network6-subnet-add`` command uses exactly the same syntax for both the
command and the response.

.. note::

   As opposed to parameter inheritance during the processing of a full new
   configuration or when adding a new shared network with new subnets,
   this command does not fully handle parameter inheritance.
   Any missing parameters will be filled with default values, rather
   than inherited from the global scope or from the shared network.

.. _command-network4-subnet-del:

.. _command-network6-subnet-del:

The ``network4-subnet-del``, ``network6-subnet-del`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to remove a subnet that is part of an existing
shared network and demote it to a plain, stand-alone subnet.
To remove a subnet completely, use the ``subnet4-del`` or ``subnet6-del``
commands instead. The ``network4-subnet-del`` and
``network6-subnet-del`` commands take two parameters: ``id``, which is
an integer and specifies the ID of an existing subnet to be removed from
a shared network; and ``name``, which specifies the name of the shared
network from which the subnet will be removed.

An example invocation of the ``network4-subnet-del`` command looks as
follows:

::

    {
       "command": "network4-subnet-del",
       "arguments": {
           "name": "floor13",
           "id": 5
       }
    }

Assuming there was a subnet with ``subnet-id`` 5, that was part of a
shared network named "floor13", the response would look similar to the
following:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now removed from shared network 'floor13'"
   }

The ``network6-subnet-del`` command uses exactly the same syntax for both the
command and the response.
