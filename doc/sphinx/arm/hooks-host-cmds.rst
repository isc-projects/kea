.. _hooks-host-cmds:

``host_cmds``: Host Commands
============================

Kea can store host reservations in a database; in many larger deployments,
it is useful to be able to manage that information while the server is
running. The Host Commands library provides management commands for adding, querying,
and deleting host reservations in a safe way without restarting the
server. In particular, it validates the parameters, so an attempt to
insert incorrect data - such as adding a host with a conflicting identifier in the
same subnet - is rejected. Those commands are exposed via the command
channel (JSON over UNIX sockets) and the Control Agent (JSON over a RESTful
interface).

This library is only available to ISC customers with a paid support
contract.

.. note::

   This library can only be loaded by the ``kea-dhcp4`` or ``kea-dhcp6``
   process.

Currently, the following commands are supported:

- ``reservation-add``, which adds a new host reservation.

- ``reservation-get``, which returns an existing reservation if specified
  criteria are matched.

- ``reservation-get-all``, which returns all reservations in a specified subnet.

- ``reservation-get-page``, a variant of ``reservation-get-all`` that returns
  reservations by pages, either all or in a specified subnet.

- ``reservation-get-by-hostname``, which returns all reservations with a
  specified hostname and optionally in a subnet.

- ``reservation-get-by-id``, which returns all reservations with a specified
  identifier (since Kea version 1.9.0).

- ``reservation-del``, which attempts to delete a reservation matching specified
  criteria.

To use the commands that change reservation information
(i.e. ``reservation-add`` and ``reservation-del``), the hosts database must be
specified and it must not operate in read-only mode (for details, see
the ``hosts-databases`` descriptions in :ref:`hosts-databases-configuration4`
and :ref:`hosts-databases-configuration6`). If the ``hosts-databases`` are not specified or are
running in read-only mode, the ``host_cmds`` library will load, but any
attempts to use ``reservation-add`` or ``reservation-del`` will fail.

For a description of proposed future commands, see the `Control API
Requirements <https://gitlab.isc.org/isc-projects/kea/wikis/designs/commands>`__
document.

All host commands use JSON syntax. They can be issued either using the
control channel (see :ref:`ctrl-channel`) or via the Control Agent (see
:ref:`kea-ctrl-agent`).

The library can be loaded similarly to other hook libraries. It
does not take any parameters, and it supports both the DHCPv4 and DHCPv6
servers.

::

   "Dhcp6": {
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_host_cmds.so"
           }
           ...
       ]
   }

The ``subnet-id`` Parameter
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Before examining the individual commands, it is worth discussing the
parameter ``subnet-id``. Currently this parameter is mandatory for all of the
commands supplied by this library, with the exception of
``reservation-get-by-hostname``, where it is optional. Since Kea 1.9.0,
``subnet-id`` is also optional in ``reservation-get-page``, and
it is forbidden in ``reservation-get-by-id``.

Reservations can be specified globally, and are not necessarily specific to any
subnet. When reservations are supplied via the configuration file, the
ID of the containing subnet (or lack thereof) is implicit in the
configuration structure. However, when managing reservations using
host commands, it is necessary to explicitly identify the scope to which
the reservation belongs. This is done via the ``subnet-id`` parameter.
For global reservations, use a value of zero (0). For reservations
scoped to a specific subnet, use that subnet's ID.

On the other hand, when the ``subnet-id`` is not specified in the command
parameters, it is added to each host in responses. If the ``subnet-id``
has the unused special value, this means the host entry belongs only
to the other IP version (i.e. IPv6 in DHCPv4 server or IPv4 in DHCPv6
server) and this entry is ignored.

.. _command-reservation-add:

The ``reservation-add`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-add`` allows for the insertion of a new host. It takes a
set of arguments that vary depending on the nature of the host
reservation. Any parameters allowed in the configuration file that
pertain to host reservation are permitted here. For details regarding
IPv4 reservations, see :ref:`host-reservation-v4`; for IPv6 reservations, see
:ref:`host-reservation-v6`. The ``subnet-id`` is mandatory. Use a
value of zero (0) to add a global reservation, or the ID of the subnet
to which the reservation should be added. An example command can be as
simple as:

.. code-block:: json

   {
       "command": "reservation-add",
       "arguments": {
           "reservation": {
               "subnet-id": 1,
               "hw-address": "1a:1b:1c:1d:1e:1f",
               "ip-address": "192.0.2.202"
           }
       }
   }

but it can also take many more parameters, for example:

.. code-block:: json

   {
       "command": "reservation-add",
       "arguments": {
           "reservation": {
               "subnet-id": 1,
               "client-id": "01:0a:0b:0c:0d:0e:0f",
               "ip-address": "192.0.2.205",
               "next-server": "192.0.2.1",
               "server-hostname": "hal9000",
               "boot-file-name": "/dev/null",
               "option-data": [
                   {
                       "name": "domain-name-servers",
                       "data": "10.1.1.202,10.1.1.203"
                   }
               ],
               "client-classes": [ "special_snowflake", "office" ]
           }
       }
   }

Here is an example of a complex IPv6 reservation:

.. code-block:: json

   {
       "command": "reservation-add",
       "arguments": {
           "reservation": {
               "subnet-id": 1,
               "duid": "01:02:03:04:05:06:07:08:09:0A",
               "ip-addresses": [ "2001:db8:1:cafe::1" ],
               "prefixes": [ "2001:db8:2:abcd::/64" ],
               "hostname": "foo.example.com",
               "option-data": [
                   {
                       "name": "vendor-opts",
                       "data": "4491"
                   },
                   {
                       "name": "tftp-servers",
                       "space": "vendor-4491",
                       "data": "3000:1::234"
                   }
               ]
           }
       }
   }

The command returns a status that indicates either success (result 0)
or failure (result 1). A failed command always includes a text parameter
that explains the cause of the failure. Here's an example of a successful
addition:

::

   { "result": 0, "text": "Host added." }

And here's an example of a failure:

::

   { "result": 1, "text": "Mandatory 'subnet-id' parameter missing." }

As ``reservation-add`` is expected to store the host, the ``hosts-databases``
parameter must be specified in the configuration, and databases must not
run in read-only mode.

.. _command-reservation-get:

The ``reservation-get`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get`` can be used to query the host database and retrieve
existing reservations. This command supports two types of parameters:
(``subnet-id``, ``address``) or (``subnet-id``, ``identifier-type``,
``identifier``). The first type of query is used when the address (either
IPv4 or IPv6) is known, but the details of the reservation are not. One
common use for this type of query is to find out whether a given
address is reserved. The second query uses identifiers. For
maximum flexibility, Kea stores the host identifying information as a
pair of values: the type and the actual identifier. Currently supported
identifiers are ``"hw-address"``, ``"duid"``, ``"circuit-id"``, ``"client-id"``, and
``"flex-id"``. The ``subnet-id`` is mandatory. Use a value
of zero (0) to fetch a global reservation, or the ID of the subnet to
which the reservation belongs.

An example command for getting a host reservation by a (``subnet-id``,
``address``) pair looks as follows:

::

   {
       "command": "reservation-get",
       "arguments": {
           "subnet-id": 1,
           "ip-address": "192.0.2.202"
       }
   }

An example query by (``subnet-id``, ``identifier-type``, ``identifier``) looks as
follows:

::

   {
       "command": "reservation-get",
       "arguments": {
           "subnet-id": 4,
           "identifier-type": "hw-address",
           "identifier": "01:02:03:04:05:06"
       }
   }

``reservation-get`` typically returns the result 0 when a query was
conducted properly. In particular, 0 is returned when the host was not
found. If the query was successful, the host parameters are
returned. An example of a query that did not find the host looks as
follows:

::

   { "result": 0, "text": "Host not found." }

Here's an example of a result returned when the host was found successfully:

::

   {
     "arguments": {
       "boot-file-name": "bootfile.efi",
       "client-classes": [

       ],
       "hostname": "somehost.example.org",
       "hw-address": "01:02:03:04:05:06",
       "ip-address": "192.0.2.100",
       "next-server": "192.0.0.2",
       "option-data": [

       ],
       "server-hostname": "server-hostname.example.org",
       "subnet-id": 4
     },
     "result": 0,
     "text": "Host found."
   }

An example result returned when the query was malformed might look like this:

::

   { "result": 1, "text": "No 'ip-address' provided and 'identifier-type'
                           is either missing or not a string." }

.. _command-reservation-get-all:

The ``reservation-get-all`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-all`` can be used to query the host database and
retrieve all reservations in a specified subnet. This command uses
parameters providing the mandatory ``subnet-id``. Global host reservations
can be retrieved by using a ``subnet-id`` value of zero (0).

For instance, retrieving host reservations for the subnet 1:

::

   {
       "command": "reservation-get-all",
       "arguments": {
           "subnet-id": 1
        }
   }

returns some IPv4 hosts:

::

   {
       "arguments": {
           "hosts": [
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "somehost.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.100",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org",
                   "subnet-id": 1
               },
               ...
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "otherhost.example.org",
                   "hw-address": "01:02:03:04:05:ff",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org",
                   "subnet-id": 1
               }
           ]
       },
       "result": 0,
       "text": "72 IPv4 host(s) found."
   }

The response returned by ``reservation-get-all`` can be very long. The
DHCP server does not handle DHCP traffic while preparing a response to
``reservation-get-all``, so if there are many reservations in a subnet, this
may be disruptive; use with caution. For larger deployments, please
consider using ``reservation-get-page`` instead (see
:ref:`command-reservation-get-page`).

For more information, see :ref:`command-reservation-get-all`.

.. _command-reservation-get-page:

The ``reservation-get-page`` command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-page`` can be used to query the host database and
retrieve all reservations in a specified subnet, by pages. This command
uses parameters providing the mandatory ``subnet-id``. Use a value of zero
(0) to fetch global reservations. The second mandatory parameter is the
page size limit. The optional ``source-index`` and ``from-host-id`` parameters, both
of which default to 0, are used to chain page queries.
Since Kea version 1.9.0, the ``subnet-id`` parameter is optional.

The usage of the ``from`` and ``source-index`` parameters requires additional
explanation. For the first call, those parameters should not be specified
(or should be specified as zeros). For any follow-up calls, they should be set to
the values returned in previous calls, in a next map holding ``from`` and
``source-index`` values. Subsequent calls should be issued until all
reservations are returned. The end is reached once the returned list is
empty, the count is 0, no next map is present, and result status 3 (empty) is
returned.

.. note::

   The ``from`` and ``source-index`` parameters reflect the internal state of
   the search. There is no need to understand what they represent; it is
   simply a value that should be copied from one response to the
   next query. However, for those who are curious, the ``from`` field represents a
   64-bit representation of the host identifier used by a host backend. The
   ``source-index`` is an internal representation of multiple host
   backends: 0 is used to represent hosts defined in a configuration
   file, and 1 represents the first database backend. In some uncommon cases
   there may be more than one database backend configured, so
   potentially there may be a 2. In any case, Kea iterates over all
   backends configured.

For instance, retrieving host reservations for the subnet 1 and
requesting the first page can be done by:

::

   {
       "command": "reservation-get-page",
       "arguments": {
           "subnet-id": 1,
           "limit": 10
        }
   }

Since this is the first call, ``source-index`` and ``from`` should not be
specified. They are set to their zero default values.

Some hosts are returned with information to get the next page:

::

   {
       "arguments": {
           "count": 72,
           "hosts": [
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "somehost.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.100",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               },
               ...
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "otherhost.example.org",
                   "hw-address": "01:02:03:04:05:ff",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               }
           ],
           "next": {
               "from": 1234567,
               "source-index": 1
           }
       },
       "result": 0,
       "text": "72 IPv4 host(s) found."
   }

Note that the ``from`` and ``source-index`` fields were specified in the response in
the next map. Those two must be copied to the next command, so Kea
continues from the place where the last command finished. To get the
next page the following command can be sent:

::

   {
       "command": "reservation-get-page",
       "arguments": {
           "subnet-id": 1,
           "source-index": 1,
           "from": 1234567,
           "limit": 10
        }
   }

The response will contain a list of hosts with updated ``source-index``
and ``from`` fields. Continue calling the command until the last
page is received. Its response will look like this:

.. code-block:: json

   {
       "arguments": {
           "count": 0,
           "hosts": [ ]
       },
       "result": 3,
       "0 IPv4 host(s) found."
   }

This command is more complex than ``reservation-get-all``, but lets
users retrieve larger host reservations lists in smaller chunks. For
small deployments with few reservations, it is easier to use
``reservation-get-all`` (see :ref:`command-reservation-get-all`).

.. _command-reservation-get-by-hostname:

The ``reservation-get-by-hostname`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-by-hostname`` can be used to query the host database and
retrieve all reservations with a specified hostname or in
a specified subnet. This command uses parameters providing the mandatory
``hostname`` and the optional ``subnet-id``. Global host reservations
can be retrieved by using a ``subnet-id`` value of zero (0).
Hostname matching is case-insensitive.

For instance, retrieving host reservations for "foobar" in the subnet 1:

::

   {
       "command": "reservation-get-by-hostname",
       "arguments": {
           "hostname": "foobar.example.org",
           "subnet-id": 1
        }
   }

returns some IPv4 hosts:

::

   {
       "arguments": {
           "hosts": [
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "foobar.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.100",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               },
               ...
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "foobar.example.org",
                   "hw-address": "01:02:03:04:05:ff",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               }
           ]
       },
       "result": 0,
       "text": "5 IPv4 host(s) found."
   }

The response returned by ``reservation-get-by-hostname`` can be long,
particularly when responses are not limited to a subnet.

For more information, see :ref:`command-reservation-get-by-hostname`.

.. note::

   When using MySQL as the host backend, this command relies on the fact
   that the hostname column in the hosts table uses a case-insensitive
   collation, as explained in the :ref:`mysql-database` section of
   :ref:`admin`.

.. _command-reservation-get-by-id:

The ``reservation-get-by-id`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-by-id`` can be used to query the host database and
retrieve all reservations with a specified identifier (``identifier-type``
and ``identifier`` parameters), independently of subnets. The syntax for
parameters is the same as for ref:`command-reservation-get`.
The ``subnet-id`` parameter cannot be used, to avoid confusion.
This command is available since Kea version 1.9.0.

For instance, retrieving host reservations for the 01:02:03:04:05:06 MAC
address:

::

   {
       "command": "reservation-get-by-id",
       "arguments": {
           "identifier-type": "hw-address",
           "identifier": "01:02:03:04:05:06"
        }
    }

returns some IPv4 hosts:

::

   {
       "arguments": {
           "hosts": [
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "foo.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.100",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org",
                   "subnet-id": 123
               },
               ...
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "bar.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org",
                   "subnet-id": 345
               }
           ]
       },
       "result": 0,
       "text": "5 IPv4 host(s) found."
   }

The response returned by ``reservation-get-by-id`` can be long,
particularly when responses are not limited to a subnet.

For more information, see :ref:`command-reservation-get-by-id`.

.. _command-reservation-del:

The ``reservation-del`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-del`` can be used to delete a reservation from the host
database. This command supports two types of parameters:
(``subnet-id``, ``address``) or (``subnet-id``, ``identifier-type``, ``identifier``). The
first type of query is used when the address (either IPv4 or IPv6) is
known, but the details of the reservation are not. One common use for
this type of query is to remove a reservation (e.g. a specific
address should no longer be reserved). The second query uses identifiers.
For maximum flexibility, Kea stores the host identifying information as
a pair of values: the type and the actual identifier. Currently supported
identifiers are ``"hw-address"``, ``"duid"``, ``"circuit-id"``, ``"client-id"``, and
``"flex-id"``. The ``subnet-id`` is mandatory. Use a value
of zero (0) to delete a global reservation, or the ID of the subnet from
which the reservation should be deleted.

An example command for deleting a host reservation by (``subnet-id``,
``address``) pair looks as follows:

::

   {
       "command": "reservation-del",
       "arguments": {
           "subnet-id": 1,
           "ip-address": "192.0.2.202"
       }
   }

An example deletion by (``subnet-id``, ``identifier-type``, ``identifier``) looks as
follows:

::

   {
       "command": "reservation-del",
       "arguments":
           "subnet-id": 4,
           "identifier-type": "hw-address",
           "identifier": "01:02:03:04:05:06"
       }
   }

``reservation-del`` returns a result of 0 when the host deletion was
successful, or 1 if it failed. Descriptive text is provided in the event of
an error. Here are some examples of possible results:

::

   {
       "result": 1,
       "text": "Host not deleted (not found)."
   }

::

   {
       "result": 0,
       "text": "Host deleted."
   }

::

   {
       "result": 1,
       "text": "Unable to delete a host because there is no hosts-database
                configured."
   }

.. note::

   The host cache and RADIUS hook libraries are two host backends that do not
   contribute to commands returning a collection of host reservations, such as
   ``reservation-get-all``. Commands returning one host entry or dedicated host
   cache commands should be used instead.
