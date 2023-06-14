.. ischooklib:: libdhcp_host_cmds.so
.. _hooks-host-cmds:

``libdhcp_host_cmds.so``: Host Commands
=======================================

Kea can store host reservations in a database; in many larger deployments,
it is useful to be able to manage that information while the server is
running. The Host Commands library provides management commands for adding, querying,
and deleting host reservations in a safe way without restarting the
server. In particular, it validates the parameters, so an attempt to
insert incorrect data - such as adding a host with a conflicting identifier in the
same subnet - is rejected. Those commands are exposed via the command
channel (JSON over UNIX sockets) and the Control Agent (JSON over a RESTful
interface).

.. note::

    :ischooklib:`libdhcp_host_cmds.so` is available as a premium
    hook library from ISC. Please visit https://www.isc.org/shop/ to purchase
    the premium hook libraries, or contact us at https://www.isc.org/contact for
    more information.

.. note::

   This library can only be loaded by the :iscman:`kea-dhcp4` or :iscman:`kea-dhcp6`
   process.

Currently, the following commands are supported:

- :isccmd:`reservation-add`, which adds a new host reservation.

- :isccmd:`reservation-get`, which returns an existing reservation if specified
  criteria are matched.

- :isccmd:`reservation-get-all`, which returns all reservations in a specified subnet.

- :isccmd:`reservation-get-page`, a variant of :isccmd:`reservation-get-all` that returns
  reservations by pages, either all or in a specified subnet.

- :isccmd:`reservation-get-by-hostname`, which returns all reservations with a
  specified hostname and optionally in a subnet.

- :isccmd:`reservation-get-by-id`, which returns all reservations with a specified
  identifier (since Kea version 1.9.0).

- :isccmd:`reservation-del`, which attempts to delete a reservation matching specified
  criteria.

- :isccmd:`reservation-update`, which updates (replaces) an existing reservation
  matching the given identifiers in a subnet.

To use the commands that change reservation information
(i.e. :isccmd:`reservation-add`, :isccmd:`reservation-del`, and :isccmd:`reservation-update`) to
modify data stored in the host database, the hosts database must be specified
and it must not operate in read-only mode (for details, see the
``hosts-databases`` descriptions in :ref:`hosts-databases-configuration4` and
:ref:`hosts-databases-configuration6`). If the ``hosts-databases`` are not
specified or are running in read-only mode, :ischooklib:`libhost_cmds.so` will
load, but any attempts to use :isccmd:`reservation-add`, :isccmd:`reservation-del`, and
:isccmd:`reservation-update` to modify data in that database will fail.

These commands can also modify hosts from the JSON configuration independently
from the hosts database. The changes provided in the JSON configuration are
volatile and can be made permanent by sending the :isccmd:`config-write` command.

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
           },
           ...
       ]
   }

The ``subnet-id`` Parameter
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Before examining the individual commands, it is worth discussing the
parameter ``subnet-id``. Currently this parameter is mandatory for all of the
commands supplied by this library, with the exception of
:isccmd:`reservation-get-by-hostname`, where it is optional. Since Kea 1.9.0,
``subnet-id`` is also optional in :isccmd:`reservation-get-page`, and
it is forbidden in :isccmd:`reservation-get-by-id`.

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

The ``operation-target`` Parameter
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Most host commands accept the ``operation-target`` parameter that specifies the
database(s) to query. The commands may process data from the JSON configuration
(primary source), the hosts database (alternate source), or both of them
(all sources). The operation target parameter is optional. By default, the
commands that only read the data use all data sources (JSON configuration and
hosts database); the commands that modify the state (as :isccmd:`reservation-add`,
:isccmd:`reservation-del`, and :isccmd:`reservation-update`) only use the alternate source.

The operation target accepts the following values:

- ``primary`` - query the primary source - JSON configuration.
- ``alternate`` - query the alternate source - hosts database(s).
- ``all`` - query both sources - JSON configuration and host database(s).
- ``default`` - query the default source - it's command specific.

.. isccmd:: reservation-add
.. _command-reservation-add:

The ``reservation-add`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`reservation-add` allows for the insertion of a new host. It takes a
set of arguments that vary depending on the nature of the host
reservation. Any parameters allowed in the configuration file that
pertain to host reservation are permitted here. For details regarding
IPv4 reservations, see :ref:`host-reservation-v4`; for IPv6 reservations, see
:ref:`host-reservation-v6`. The ``subnet-id`` is mandatory. Use a
value of zero (0) to add a global reservation, or the ID of the subnet
to which the reservation should be added. The command can be as simple as having
only the two mandatory entries:

.. code-block:: json

   {
       "command": "reservation-add",
       "arguments": {
           "reservation": {
               "subnet-id": 1,
               "hw-address": "1a:1b:1c:1d:1e:1f"
           }
       }
   }

In that case, however, it does not assign any resources to the host. An IPv4
address can be assigned like so:

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

It can also take many more parameters, for example:

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

The command accepts the ``operation-target`` argument. By default, it adds the
reservation to the hosts database only.

.. code-block:: json

   {
       "command": "reservation-add",
       "arguments": {
           "reservation": {},
           "operation-target": "all"
       }
   }

The command returns a status that indicates either success (result 0)
or failure (result 1). A failed command always includes a text parameter
that explains the cause of the failure. Here's an example of a successful
addition:

.. code-block:: json

   {
       "result": 0,
       "text": "Host added."
   }

And here's an example of a failure:

.. code-block:: json

   {
       "result": 1,
       "text": "Mandatory 'subnet-id' parameter missing."
   }


As :isccmd:`reservation-add` is expected to store the host, the ``hosts-databases``
parameter must be specified in the configuration, and databases must not
run in read-only mode.

.. isccmd:: reservation-get
.. _command-reservation-get:

The ``reservation-get`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`reservation-get` can be used to query the host database and retrieve
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

The command accepts the ``operation-target`` argument. By default, it gets the
reservation from both JSON configuration and the hosts database.

.. code-block:: json

   {
       "command": "reservation-get",
       "arguments": {
           "subnet-id": 1,
           "ip-address": "192.0.2.202",
           "operation-target": "alternate"
       }
   }

Command :isccmd:`reservation-get` typically returns the result 0 when a query was
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

   { "result": 1, "text": "No 'ip-address' provided and 'identifier-type' is either missing or not a string." }

.. _command-reservations-get:

The ``reservations-get`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservations-get`` can be used to query the host database and
retrieve all reservations in a specified subnet for given ip address.

.. isccmd:: reservation-get-all
.. _command-reservation-get-all:

The ``reservation-get-all`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`reservation-get-all` can be used to query the host database and
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
               },
               ...
           ]
       },
       "result": 0,
       "text": "72 IPv4 host(s) found."
   }

The response returned by :isccmd:`reservation-get-all` can be very long. The
DHCP server does not handle DHCP traffic while preparing a response to
:isccmd:`reservation-get-all`, so if there are many reservations in a subnet, this
may be disruptive; use with caution. For larger deployments, please
consider using :isccmd:`reservation-get-page` instead.

The command accepts the ``operation-target`` argument. By default, it gets the
reservation from both JSON configuration and the hosts database.

.. code-block:: json

   {
       "command": "reservation-get-all",
       "arguments": {
           "subnet-id": 1,
           "operation-target": "alternate"
       }
   }

For more information, see :ref:`command-reservation-get-all`.

.. isccmd:: reservation-get-page
.. _command-reservation-get-page:

The ``reservation-get-page`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`reservation-get-page` can be used to query the host database and
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
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "otherhost.example.org",
                   "hw-address": "01:02:03:04:05:ff",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               },
               ...
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
       "text": "0 IPv4 host(s) found."
   }

The command doesn't accept the ``operation-target`` argument.

This command is more complex than :isccmd:`reservation-get-all`, but lets
users retrieve larger host reservations lists in smaller chunks. For
small deployments with few reservations, it is easier to use
:isccmd:`reservation-get-all`.

.. isccmd:: reservation-get-by-hostname
.. _command-reservation-get-by-hostname:

The ``reservation-get-by-hostname`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`reservation-get-by-hostname` can be used to query the host database and
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
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "foobar.example.org",
                   "hw-address": "01:02:03:04:05:ff",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               },
               ...
           ]
       },
       "result": 0,
       "text": "5 IPv4 host(s) found."
   }

The response returned by :isccmd:`reservation-get-by-hostname` can be long,
particularly when responses are not limited to a subnet.

The command accepts the ``operation-target`` argument. By default, it gets the
reservation from both JSON configuration and the hosts database.

.. code-block:: json

   {
       "command": "reservation-get-by-hostname",
       "arguments": {
           "hostname": "foobar.example.org",
           "subnet-id": 1,
           "operation-target": "alternate"
       }
   }

For more information, see :ref:`command-reservation-get-by-hostname`.

.. note::

   When using MySQL as the host backend, this command relies on the fact
   that the hostname column in the hosts table uses a case-insensitive
   collation, as explained in the :ref:`mysql-database` section of
   :ref:`admin`.

.. isccmd:: reservation-get-by-id
.. _command-reservation-get-by-id:

The ``reservation-get-by-id`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`reservation-get-by-id` can be used to query the host database and
retrieve all reservations with a specified identifier (``identifier-type``
and ``identifier`` parameters), independently of subnets. The syntax for
parameters is the same as for :isccmd:`reservation-get`.
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
               },
               ...
           ]
       },
       "result": 0,
       "text": "5 IPv4 host(s) found."
   }

The response returned by :isccmd:`reservation-get-by-id` can be long,
particularly when responses are not limited to a subnet.

The command accepts the ``operation-target`` argument. By default, it gets the
reservation from both JSON configuration and the hosts database.

.. code-block:: json

   {
       "command": "reservation-get-by-id",
       "arguments": {
           "identifier-type": "hw-address",
           "identifier": "01:02:03:04:05:06",
           "operation-target": "alternate"
       }
   }

For more information, see :ref:`command-reservation-get-by-id`.

.. isccmd:: reservation-del
.. _command-reservation-del:

The ``reservation-del`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`reservation-del` can be used to delete a reservation from the host
database and/or JSON configuration. This command supports two types of parameters:
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
       "arguments": {
           "subnet-id": 4,
           "identifier-type": "hw-address",
           "identifier": "01:02:03:04:05:06"
       }
   }

Command :isccmd:`reservation-del` returns a result of 0 when the host deletion was
successful, or 1 if it failed. Descriptive text is provided in the event of
an error. Here are some examples of possible results:

::

   {
       "result": 1,
       "text": "Host not deleted (not found)."
   }

or

::

   {
       "result": 0,
       "text": "Host deleted."
   }

or

::

   {
       "result": 1,
       "text": "Unable to delete a host because there is no hosts-database configured."
   }

The command accepts the ``operation-target`` argument. By default, it removes
the reservation from the hosts database only.

.. code-block:: json

   {
       "command": "reservation-del",
       "arguments": {
           "subnet-id": 4,
           "identifier-type": "hw-address",
           "identifier": "01:02:03:04:05:06",
           "operation-target": "primary"
       }
   }

.. isccmd:: reservation-update
.. _command-reservation-update:

The ``reservation-update`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`reservation-update` allows for the update of an existing host. It takes the
same set of arguments as :isccmd:`reservation-add`, and just as well,
requires a host identifier and a subnet ID to identify the host that is being
updated. The command can be as simple as having only the two mandatory entries:

.. code-block:: json

   {
       "command": "reservation-update",
       "arguments": {
           "reservation": {
               "subnet-id": 1,
               "hw-address": "1a:1b:1c:1d:1e:1f"
           }
       }
   }

In that case, however, it does not assign any resources to the host. An IPv4
address can be assigned like so:

.. code-block:: json

    {
        "command": "reservation-update",
        "arguments": {
            "reservation": {
                "subnet-id": 1,
                "hw-address": "1a:1b:1c:1d:1e:1f",
                "ip-address": "192.0.2.202"
            }
        }
    }

It can also take many more parameters, for example:

.. code-block:: json

    {
        "command": "reservation-update",
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
                "client-classes": [
                    "office",
                    "special_snowflake"
                ]
            }
        }
    }

Here is an example of a complex IPv6 reservation update:

.. code-block:: json

    {
        "command": "reservation-update",
        "arguments": {
            "reservation": {
                "subnet-id": 1,
                "duid": "01:02:03:04:05:06:07:08:09:0A",
                "ip-addresses": [
                    "2001:db8:1:cafe::1"
                ],
                "prefixes": [
                    "2001:db8:2:abcd::/64"
                ],
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

The command returns a status that indicates either success (result ``0``) or
failure (result ``1``) and a text parameter that confirms success or explains
the cause of the failure. Here's an example of a successful update:

.. code-block:: json

   {
       "result": 0,
       "text": "Host updated."
   }

And here's an example of a failure:

.. code-block:: json

   {
       "result": 1,
       "text": "Mandatory 'subnet-id' parameter missing."
   }

The command accepts the ``operation-target`` argument. By default, it adds the
reservation to the hosts database only. As :isccmd:`reservation-update` is expected
to store the host, the ``hosts-databases`` parameter must be specified in the
configuration, and databases must not run in read-only mode if the operation
target is not the JSON configuration.

As with other update and set commands, this command overwrites all the contents
of the entry. If the host previously had a resource assigned to it, and the
:isccmd:`reservation-update` command is missing the resource, it is deleted from the
database. If an incremental update of the host is desired, then this can be
achieved by doing a :isccmd:`reservation-get-by-id` to get the current state of the
host, picking the host out of the response, modifying it to the required
outcome, and then issuing the :isccmd:`reservation-update` command with the resulting
host attached.

.. _hooks-host-cmds-general-mentions:

General Mentions
~~~~~~~~~~~~~~~~

.. note::

   The host cache and RADIUS hook libraries are two host backends that do not
   respond to commands that return a collection of host reservations, such as
   :isccmd:`reservation-get-all`. Commands returning one host entry or dedicated host
   cache commands should be used instead.
