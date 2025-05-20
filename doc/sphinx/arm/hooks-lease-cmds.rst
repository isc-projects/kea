.. ischooklib:: libdhcp_lease_cmds.so
.. _hooks-lease-cmds:

``libdhcp_lease_cmds.so``: Lease Commands for Easier Lease Management
=====================================================================

Kea allows users to store lease information in several
backends (memfile, MySQL, and PostgreSQL), and the Lease Commands library provides an
interface that can manipulate leases in a unified, safe way.
In particular, it allows things that were previously impossible: lease
manipulation in memfile while Kea is running, sanity check changes,
lease existence checks, and removal of all leases belonging to a
specific subnet. The hook library can also catch more obscure errors, like an attempt
to add a lease with a ``subnet-id`` that does not exist in the
configuration, or configuring a lease to use an address that is outside
of the subnet to which it is supposed to belong. The library also
provides a non-programmatic way to manage user contexts associated with
leases.

.. note::

    :ischooklib:`libdhcp_lease_cmds.so` is part of the open source code and is
    available to every Kea user.

.. note::

   This library can only be loaded by the :iscman:`kea-dhcp4` or the
   :iscman:`kea-dhcp6` process.

There are many situations where an administrative command may be useful;
for example, during migration between servers or different vendors, when
a certain network is being retired, or when a device has been
disconnected and the system administrator knows that it will not be coming
back. The ``get`` queries may be useful for automating certain management
and monitoring tasks, and they can also act as preparatory steps for lease
updates and removals.

This library provides the following commands:

-  :isccmd:`lease4-add` - adds a new IPv4 lease.

-  :isccmd:`lease6-add` - adds a new IPv6 lease.

-  :isccmd:`lease6-bulk-apply` - creates, updates, and/or deletes multiple
   IPv6 leases in a single transaction.

-  :isccmd:`lease4-get` - checks whether an IPv4 lease with the specified
   parameters exists and returns it if it does.

-  :isccmd:`lease6-get` - checks whether an IPv6 lease with the specified
   parameters exists and returns it if it does.

-  :isccmd:`lease4-get-all` - returns all IPv4 leases or all IPv4 leases for
   the specified subnets.

-  :isccmd:`lease6-get-all` - returns all IPv6 leases or all IPv6 leases for
   the specified subnets.

-  :isccmd:`lease4-get-page` - returns a set ("page") of leases from the list
   of all IPv4 leases in the database. By iterating through the pages it
   is possible to retrieve all the leases.

-  :isccmd:`lease6-get-page` - returns a set ("page") of leases from the list
   of all IPv6 leases in the database. By iterating through the pages it
   is possible to retrieve all the leases.

-  :isccmd:`lease4-get-by-hw-address` - returns all IPv4 leases with the specified
   hardware address.

-  :isccmd:`lease4-get-by-client-id` - returns all IPv4 leases with the specified
   ``client-id``.

-  :isccmd:`lease6-get-by-duid` - returns all IPv6 leases with the specified DUID.

-  :isccmd:`lease4-get-by-hostname` - returns all IPv4 leases with the specified
   hostname.

-  :isccmd:`lease6-get-by-hostname` - returns all IPv6 leases with the specified
   hostname.

-  :isccmd:`lease4-del` - deletes an IPv4 lease with the specified parameters.

-  :isccmd:`lease6-del` - deletes an IPv6 lease with the specified parameters.

-  :isccmd:`lease4-update` - updates (replaces) an existing IPv4 lease.

-  :isccmd:`lease6-update` - updates (replaces) an existing IPv6 lease.

-  :isccmd:`lease4-wipe` - removes all leases from a specific IPv4 subnet or
   from all subnets. This command is deprecated and it will be removed
   in the future.

-  :isccmd:`lease6-wipe` - removes all leases from a specific IPv6 subnet or
   from all subnets. This command is deprecated and it will be removed
   in the future.

-  :isccmd:`lease4-resend-ddns` - resends a request to update DNS entries for
   an existing lease.

-  :isccmd:`lease6-resend-ddns` - resends a request to update DNS entries for
   an existing lease.

-  :isccmd:`lease4-write` - writes the IPv4 memfile lease database into a file.

-  :isccmd:`lease6-write` - writes the IPv6 memfile lease database into a file.

All commands use JSON syntax and can be issued either using the control
channel (see :ref:`ctrl-channel`) or Control Agent (see
:ref:`kea-ctrl-agent`).

The library can be loaded in the same way as other hook libraries, and
it does not take any parameters. It supports both the DHCPv4 and DHCPv6
servers.

::

   "Dhcp6": {
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_lease_cmds.so"
           },
           ...
       ]
   }

.. isccmd:: lease4-add
.. _command-lease4-add:

.. isccmd:: lease6-add
.. _command-lease6-add:

The ``lease4-add``, ``lease6-add`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :isccmd:`lease4-add` and
:isccmd:`lease6-add` commands allow a new lease
to be created. Typically Kea creates a lease when it first sees a new
device; however, sometimes it may be convenient to create the lease
manually. The :isccmd:`lease4-add` command requires at least two parameters:
an IPv4 address and an identifier, i.e. hardware (MAC) address. A third
parameter, ``subnet-id``, is optional. If the ``subnet-id`` is not specified or
the specified value is 0, Kea tries to determine the value by running
a subnet-selection procedure. If specified, however, its value must
match the existing subnet. The simplest successful call might look as
follows:

::

   {
       "command": "lease4-add",
       "arguments": {
           "ip-address": "192.0.2.202",
           "hw-address": "1a:1b:1c:1d:1e:1f"
       }
   }

The :isccmd:`lease6-add` command requires three parameters: an IPv6 address,
an IAID value (identity association identifier, a value sent by
clients), and a DUID. As with :isccmd:`lease4-add`, the ``subnet-id`` parameter is
optional. If the ``subnet-id`` is not specified or the provided value is 0,
Kea tries to determine the value by running a subnet-selection
procedure. If specified, however, its value must match the existing
subnet. For example:

::

   {
       "command": "lease6-add",
       "arguments": {
           "subnet-id": 66,
           "ip-address": "2001:db8::3",
           "duid": "1a:1b:1c:1d:1e:1f:20:21:22:23:24",
           "iaid": 1234
       }
   }

The :isccmd:`lease6-add` command can also be used to add leases for IPv6 prefixes.
In this case there are three additional parameters that must be specified:
``subnet-id``, ``type`` (set to "IA_PD"), and prefix length. The actual
prefix is set using the ``ip-address`` field. Note that Kea cannot guess
``subnet-id`` values for prefixes; they must be specified explicitly. For
example, to configure a lease for prefix 2001:db8:abcd::/48, the
following command can be used:

::

   {
       "command": "lease6-add",
       "arguments": {
           "subnet-id": 66,
           "type": "IA_PD",
           "ip-address": "2001:db8:abcd::",
           "prefix-len": 48,
           "duid": "1a:1b:1c:1d:1e:1f:20:21:22:23:24",
           "iaid": 1234
       }
   }

The commands can take several additional optional parameters:

-  ``valid-lft`` - specifies the lifetime of the lease, expressed in
   seconds. If not specified, the value configured in the subnet related
   to the specified ``subnet-id`` is used.

-  ``expire`` - creates a timestamp of the lease expiration time,
   expressed in UNIX format (seconds since 1 Jan 1970). If not
   specified, the default value is the current time plus the lease lifetime (the value
   of ``valid-lft``).

-  ``fqdn-fwd`` - specifies whether the lease should be marked as if a
   forward DNS update were conducted. This only affects the
   data stored in the lease database, and no DNS update will be
   performed. If configured, a DNS update to remove the A or AAAA
   records will be conducted when the lease is removed due to expiration
   or being released by a client. If not specified, the default value is
   ``false``. The hostname parameter must be specified if ``fqdn-fwd`` is set to
   ``true``.

-  ``fqdn-rev`` - specifies whether the lease should be marked as if
   reverse DNS update were conducted. This only affects the
   data stored in the lease database, and no DNS update will be
   performed.. If configured, a DNS update to remove the PTR record will
   be conducted when the lease is removed due to expiration or being
   released by a client. If not specified, the default value is ``false``.
   The hostname parameter must be specified if ``fqdn-fwd`` is set to ``true``.

-  ``hostname`` - specifies the hostname to be associated with this
   lease. Its value must be non-empty if either ``fqdn-fwd`` or ``fqdn-rev`` are
   set to ``true``. If not specified, the default value is an empty string.

-  ``hw-address`` - optionally specifies a hardware (MAC) address for an
   IPv6 lease. It is a mandatory parameter for an IPv4 lease.

-  ``client-id`` - optionally specifies a client identifier for an IPv4
   lease.

-  ``preferred-lft`` - optionally specifies a preferred lifetime for
   IPv6 leases. If not specified, the value configured for the subnet
   corresponding to the specified ``subnet-id`` is used. This parameter is
   not used when adding an IPv4 lease.

-  ``state`` - specifies the state of an added lease, which can be 0 for ``default``,
   1 for ``declined``, and 2 for the ``expired-reclaimed`` state. Any other
   value causes an error. Using 1 for a ``"IA_PD"`` lease type is
   illegal and will be rejected.

-  ``user-context`` - specifies the user context to be associated with
   this lease. It must be a JSON map.

Here is an example of a fairly complex lease addition:

::

   {
       "command": "lease6-add",
       "arguments": {
           "subnet-id": 66,
           "ip-address": "2001:db8::3",
           "duid": "01:02:03:04:05:06:07:08",
           "iaid": 1234,
           "hw-address": "1a:1b:1c:1d:1e:1f",
           "preferred-lft": 500,
           "valid-lft": 1000,
           "expire": 12345678,
           "fqdn-fwd": true,
           "fqdn-rev": true,
           "state": 0,
           "hostname": "urania.example.org",
           "user-context": { "version": 1 }
       }
   }

The command returns a status that indicates either success (result 0)
or failure (result 1). A failed command always includes a text
parameter that explains the cause of failure. For example:

::

   { "result": 0, "text": "Lease added." }

Example failure:

::

   { "result": 1, "text": "missing parameter 'ip-address' (<string>:3:19)" }


.. isccmd:: lease6-bulk-apply
.. _command-lease6-bulk-apply:

The ``lease6-bulk-apply`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :isccmd:`lease6-bulk-apply` was implemented to address
the performance penalty in High-Availability mode when a single DHCPv6
transaction resulted in multiple lease updates sent to the partner, if
multiple address and/or prefix leases were allocated. Consider the case
when a DHCPv6 client requests the assignment of two IPv6 addresses and two IPv6
prefixes: it may result in the allocation of four leases. In addition,
DHCPv6 may assign a different address than the one requested by the client during
the renew or rebind stage, and delete the leases previously used by this client.
There are six lease changes sent between the HA partners in this case.
Sending these updates as individual commands, e.g. via :isccmd:`lease6-update`,
is highly inefficient and produces unnecessary delays in communication,
both between the HA partners and in sending the response to the DHCPv6 client.

The :isccmd:`lease6-bulk-apply` command deals with this
problem by aggregating all lease changes - both deleted leases and
new or updated leases - in a single command.
The receiving server iterates over the deleted leases and deletes them
from its lease database. Next, it iterates over the new/updated leases
and adds them to the database or updates them if they already exist.

Even though High Availability is the major application for
this command, it can be freely used in all cases when it is desirable to
send multiple lease changes in a single command.

In the following example, we delete two leases and add
or update two other leases in the database:


::

    {
      "command": "lease6-bulk-apply",
      "arguments": {
          "deleted-leases": [
              {
                  "ip-address": "2001:db8:abcd::",
                  "type": "IA_PD",
                  ...
              },
              {
                  "ip-address": "2001:db8:abcd::234",
                  "type": "IA_NA",
                  ...
              }
          ],
          "leases": [
              {
                  "subnet-id": 66,
                  "ip-address": "2001:db8:cafe::",
                  "type": "IA_PD",
                   ...
              },
              {
                  "subnet-id": 66,
                  "ip-address": "2001:db8:abcd::333",
                  "type": "IA_NA",
                  ...
              }
          ]
       }
   }

If any of the leases are malformed, no lease changes are applied
to the lease database. If the leases are well-formed but there is a
failure to apply any of the lease changes to the database, the command
continues to be processed for other leases. All the leases for which
the command was unable to apply the changes in the database are
listed in the response. For example:

::

    {
        "result": 0,
        "text": "Bulk apply of 2 IPv6 leases completed",
        "arguments": {
            "failed-deleted-leases": [
                {
                    "ip-address": "2001:db8:abcd::",
                    "type": "IA_PD",
                    "result": 3,
                    "error-message": "no lease found"
                }
            ],
            "failed-leases": [
                {
                    "ip-address": "2001:db8:cafe::",
                    "type": "IA_PD",
                    "result": 1,
                    "error-message": "unable to communicate with the lease database"
                }
            ]
        }
    }

The response above indicates that the hook library was unable to
delete the lease for prefix "2001:db8:abcd::" and add or update the lease
for prefix "2001:db8:cafe::". However, there are two other lease changes
which have been applied as indicated by the text message. The
``result`` is the status constant that indicates the type
of the error experienced for the particular lease. The meanings of the
returned codes are the same as the results returned for the commands.
In particular, the result of 1 indicates an error while processing the
lease, e.g. a communication error with the database. The result of 3
indicates that an attempt to delete the lease was unsuccessful because
such a lease doesn't exist (an empty result).

.. isccmd:: lease4-get
.. _command-lease4-get:

.. isccmd:: lease6-get
.. _command-lease6-get:

The ``lease4-get``, ``lease6-get`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`lease4-get` and :isccmd:`lease6-get` can be used to query the lease database
and retrieve existing leases. There are two types of parameters the
:isccmd:`lease4-get` command supports: (``address``) or (``subnet-id``,
``identifier-type``, ``identifier``). There are also two types for
:isccmd:`lease6-get`: (``address``, ``type``) or (``subnet-id``, ``identifier-type``,
``identifier``, ``IAID``, ``type``). The first type of query is used when the
address (either IPv4 or IPv6) is known, but the details of the lease are
not; one common use case of this type of query is to find out whether a
given address is being used. The second query uses identifiers;
currently supported identifiers for leases are: ``"hw-address"`` (IPv4
only), ``"client-id"`` (IPv4 only), and ``"duid"`` (IPv6 only).

An example :isccmd:`lease4-get` command for getting a lease using an IPv4
address is:

::

   {
       "command": "lease4-get",
       "arguments": {
           "ip-address": "192.0.2.1"
       }
   }

An example of the :isccmd:`lease6-get` query is:

::

   {
     "command": "lease6-get",
     "arguments": {
       "ip-address": "2001:db8:1234:ab::",
       "type": "IA_PD"
     }
   }

An example query by ``"hw-address"`` for an IPv4 lease looks as follows:

::

   {
       "command": "lease4-get",
       "arguments": {
           "identifier-type": "hw-address",
           "identifier": "08:08:08:08:08:08",
           "subnet-id": 44
       }
   }

An example query by ``"client-id"`` for an IPv4 lease looks as follows:

::

   {
       "command": "lease4-get",
       "arguments": {
           "identifier-type": "client-id",
           "identifier": "01:01:02:03:04:05:06",
           "subnet-id": 44
       }
   }

An example query by (``subnet-id``, ``identifier-type``, ``identifier``, ``iaid``, ``type``)
for an IPv6 lease is:

::

   {
       "command": "lease6-get",
       "arguments": {
           "identifier-type": "duid",
           "identifier": "08:08:08:08:08:08",
           "iaid": 1234567,
           "type": "IA_NA",
           "subnet-id": 44
       }
   }

The ``type`` is an optional parameter. Supported values are: ``IA_NA``
(non-temporary address) and ``IA_PD`` (IPv6 prefix). If not specified, ``IA_NA``
is assumed.

:isccmd:`lease4-get` and :isccmd:`lease6-get` return an indication of the result of the operation
and lease details, if found. The result has one of the following values: 0
(success), 1 (error), or 3 (empty). An empty result means that a query
has been completed properly, but the object (a lease in this case) has
not been found.
The lease parameters, if found, are returned as arguments.
``client-id`` is not returned if empty.

An example result returned when the host was found:

::

   {
     "arguments": {
       "client-id": "42:42:42:42:42:42:42:42",
       "cltt": 12345678,
       "fqdn-fwd": false,
       "fqdn-rev": true,
       "hostname": "myhost.example.com.",
       "hw-address": "08:08:08:08:08:08",
       "ip-address": "192.0.2.1",
       "state": 0,
       "subnet-id": 44,
       "valid-lft": 3600
     },
     "result": 0,
     "text": "IPv4 lease found."
   }

.. note::

   The client last transaction time (``cltt`` field) is bound to the
   valid lifetime (``valid-lft``) and to the expire date (not reported
   here but stored in databases) by the equation
   :math:`cltt + valid\_lft = expire`

   at the exception of the infinite valid lifetime coded by the
   0xfffffff (4294967295) special value which makes the expire value
   to overflow on MySQL and old PostgreSQL backends where timestamps
   are 32 bit long. So in these lease databases the expire date is the
   same as the cltt i.e.
   :math:`cltt = expire` when :math:`valid\_lft = 4294967295` and the
   lease backend is MySQL or PostgreSQL.

.. isccmd:: lease4-get-all
.. _command-lease4-get-all:

.. isccmd:: lease6-get-all
.. _command-lease6-get-all:

The ``lease4-get-all``, ``lease6-get-all`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`lease4-get-all` and :isccmd:`lease6-get-all` are used to retrieve all IPv4
or IPv6 leases, or all leases for the specified set of subnets. All
leases are returned when there are no arguments specified with the
command, as in the following example:

::

   {
       "command": "lease4-get-all"
   }

If arguments are provided, it is expected that they contain the
``"subnets"`` parameter, which is a list of subnet identifiers for which
leases should be returned. For example, to retrieve all IPv6
leases belonging to the subnets with identifiers 1, 2, 3, and 4:

::

   {
       "command": "lease6-get-all",
       "arguments": {
           "subnets": [ 1, 2, 3, 4 ]
       }
   }

The returned response contains a detailed list of leases in the
following format:

::

   {
       "arguments": {
           "leases": [
               {
                   "cltt": 12345678,
                   "duid": "42:42:42:42:42:42:42:42",
                   "fqdn-fwd": false,
                   "fqdn-rev": true,
                   "hostname": "myhost.example.com.",
                   "hw-address": "08:08:08:08:08:08",
                   "iaid": 1,
                   "ip-address": "2001:db8:2::1",
                   "preferred-lft": 500,
                   "state": 0,
                   "subnet-id": 44,
                   "type": "IA_NA",
                   "valid-lft": 3600
               },
               {
                   "cltt": 12345678,
                   "duid": "21:21:21:21:21:21:21:21",
                   "fqdn-fwd": false,
                   "fqdn-rev": true,
                   "hostname": "",
                   "iaid": 1,
                   "ip-address": "2001:db8:0:0:2::",
                   "preferred-lft": 500,
                   "prefix-len": 80,
                   "state": 0,
                   "subnet-id": 44,
                   "type": "IA_PD",
                   "valid-lft": 3600
               }
           ]
       },
       "result": 0,
       "text": "2 IPv6 lease(s) found."
   }

.. warning::

   The :isccmd:`lease4-get-all` and
   :isccmd:`lease6-get-all` commands may result in
   very large responses. This may have a negative impact on the DHCP
   server's responsiveness while the response is generated and
   transmitted over the control channel, as the server imposes no
   restriction on the number of leases returned as a result of this
   command.

.. isccmd:: lease4-get-page
.. _command-lease4-get-page:

.. isccmd:: lease6-get-page
.. _command-lease6-get-page:

The ``lease4-get-page``, ``lease6-get-page`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :isccmd:`lease4-get-all` and
:isccmd:`lease6-get-all` commands may result in
very large responses; generating such a response may consume CPU
bandwidth as well as memory. It may even cause the server to become
unresponsive. In the case of large lease databases it is usually better to
retrieve leases in chunks, using the paging mechanism.
:isccmd:`lease4-get-page` and :isccmd:`lease6-get-page` implement a paging mechanism
for DHCPv4 and DHCPv6 servers, respectively. The following command
retrieves the first 1024 IPv4 leases:

::

   {
       "command": "lease4-get-page",
       "arguments": {
           "from": "start",
           "limit": 1024
       }
   }

The keyword ``start`` denotes that the first page of leases should be
retrieved. Alternatively, an IPv4 zero address can be specified to
retrieve the first page:

::

   {
       "command": "lease4-get-page",
       "arguments": {
           "from": "0.0.0.0",
           "limit": 1024
       }
   }

Similarly, the IPv6 zero address can be specified in the
:isccmd:`lease6-get-page` command:

::

   {
       "command": "lease6-get-page",
       "arguments": {
           "from": "::",
           "limit": 6
       }
   }

The response has the following structure:

::

   {
       "arguments": {
           "leases": [
               {
                   "ip-address": "2001:db8:2::1",
                   ...
               },
               {
                   "ip-address": "2001:db8:2::9",
                   ...
               },
               {
                   "ip-address": "2001:db8:3::1",
                   ...
               },
               {
                   "ip-address": "2001:db8:5::3",
                   ...
               },
               {
                   "ip-address": "2001:db8:4::1",
                   ...
               },
               {
                   "ip-address": "2001:db8:2::7",
                   ...
               },
               ...
           ],
           "count": 6
       },
       "result": 0,
       "text": "6 IPv6 lease(s) found."
   }

Note that the leases' details were excluded from the response above for
brevity.

Generally, the returned list is not sorted in any particular order. Some
lease database backends may sort leases in ascending order of addresses,
but the controlling client must not rely on this behavior.

The ``count`` parameter contains the number of returned leases on the
page.

To fetch the next page, the client must use the last address of the
current page as an input to the next :isccmd:`lease4-get-page` or
:isccmd:`lease6-get-page` command call. In this example it is:

::

   {
       "command": "lease6-get-page",
       "arguments": {
           "from": "2001:db8:2::7",
           "count": 6
       }
   }

because 2001:db8:2::7 is the last address on the current page.

The client may assume that it has reached the last page when the
``count`` value is lower than that specified in the command; this
includes the case when the ``count`` is equal to 0, meaning that no
leases were found.

.. isccmd:: lease4-get-by-hw-address
.. _command-lease4-get-by-hw-address:

.. isccmd:: lease4-get-by-client-id
.. _command-lease4-get-by-client-id:

.. isccmd:: lease6-get-by-duid
.. _command-lease6-get-by-duid:

.. isccmd:: lease4-get-by-hostname
.. _command-lease4-get-by-hostname:

.. isccmd:: lease6-get-by-hostname
.. _command-lease6-get-by-hostname:

The ``lease4-get-by-*``, ``lease6-get-by-*`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``lease4-get-by-*`` and ``lease6-get-by-*`` can be used to query the lease database and
retrieve all existing leases matching a given feature (denoted by the ``*``). These
can include a specified hardware address (IPv4
only), ``client-id`` IPv4 only), ``duid`` (IPv6 only) identifiers, or hostname.

An example :isccmd:`lease4-get-by-hw-address` command for getting IPv4 leases
with a given hardware address is:

::

    {
        "command": "lease4-get-by-hw-address",
        "arguments": {
            "hw-address": "08:08:08:08:08:08"
        }
    }

An example of the :isccmd:`lease6-get-by-hostname` is:

::

    {
        "command": "lease6-get-by-hostname",
        "arguments": {
            "hostname": "myhost.example.org"
        }
    }

The ``by`` key is the only parameter. The returned response contains a detailed
list of leases in the same format as :isccmd:`lease4-get-all` or :isccmd:`lease6-get-all`. This list can be
empty and is usually not large.

.. isccmd:: lease4-del
.. _command-lease4-del:

.. isccmd:: lease6-del
.. _command-lease6-del:

The ``lease4-del``, ``lease6-del`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`lease4-del` and :isccmd:`lease6-del` can be used to delete a lease from the lease database.
There are two types of parameters these commands support, similar to the
:isccmd:`lease4-get` and :isccmd:`lease6-get` commands: (``address``) for both v4 and v6, (``subnet-id``,
``identifier-type``, ``identifier``) for v4, and (``subnet-id``, ``identifier-type``,
``identifier``, ``type``, ``IAID``) for v6. The first type of query is used when the
address (either IPv4 or IPv6) is known, but the details of the lease are
not. One common use case is where an administrator wants a specified
address to no longer be used. The second form of the command uses
identifiers. For maximum flexibility, this interface uses identifiers as
a pair of values: the type and the actual identifier. The currently
supported identifiers are ``"hw-address"`` (IPv4 only), ``"client-id"`` (IPv4
only), and ``"duid"`` (IPv6 only).

An example command for deleting an IPv4 lease by address is:

::

   {
       "command": "lease4-del",
       "arguments": {
           "ip-address": "192.0.2.202"
       }
   }

An example IPv4 lease deletion by ``"hw-address"`` is:

::

   {
     "command": "lease4-del",
     "arguments": {
       "identifier": "08:08:08:08:08:08",
       "identifier-type": "hw-address",
       "subnet-id": 44
     }
   }

The IPv6 address leases are deleted the same way, but using :isccmd:`lease6-del`. The
IPv6 prefix leases are also deleted using :isccmd:`lease6-del`, but with some extra
steps. The prefix should be referenced by its address and prefix length should be ignored.
For example, to delete 2001:db8:1::/48, the following command can be used. The
``subnet-id`` parameter is optional.

::

    {
        "command": "lease6-del",
        "arguments": {
            "ip-address": "2001:db8:1::",
            "type": "IA_PD",
            "subnet-id": 1
        }
    }

Another parameter called ``update-ddns``, when ``true``, instructs the server to
queue a request to :iscman:`kea-dhcp-ddns` to remove DNS entries after the lease is
successfully deleted if:

- DDNS updating is enabled (i.e. ``"dhcp-ddns":{ "enable-updates": true }``).
- The lease's hostname is not empty.
- At least one of the lease's DNS direction flags (``fqdn_fwd`` or ``fqdn_rev``) is true.

This parameter defaults to ``false``. An example of its use is shown below:

::

   {
       "command": "lease4-del",
       "arguments": {
           "ip-address": "192.0.2.202",
           "update-ddns": true
       }
   }


Commands :isccmd:`lease4-del` and :isccmd:`lease6-del` return a result that indicates the outcome
of the operation. It has one of the following values: 0 (success), 1 (error),
or 3 (empty). The empty result means that a query has been completed properly,
but the object (a lease, in this case) has not been found.

.. isccmd:: lease4-update
.. _command-lease4-update:

.. isccmd:: lease6-update
.. _command-lease6-update:

The ``lease4-update``, ``lease6-update`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :isccmd:`lease4-update` and
:isccmd:`lease6-update` commands can be used to
update existing leases. Since all lease database backends are indexed by
IP addresses, it is not possible to update an address, but all other
fields may be altered. If an address needs to be changed, please use
:isccmd:`lease4-del` / :isccmd:`lease6-del` followed by :isccmd:`lease4-add` / :isccmd:`lease6-add`.

The ``subnet-id`` parameter is optional. If not specified, or if the
specified value is 0, Kea tries to determine its value by running a
subnet-selection procedure. If specified, however, its value must match
the existing subnet.

The optional boolean parameter ``"force-create"`` specifies whether the
lease should be created if it does not exist in the database. It defaults
to ``false``, which indicates that the lease is not created if it does not
exist. In such a case, an error is returned when trying to
update a non-existing lease. If the ``"force-create"`` parameter is set to
``true`` and the updated lease does not exist, the new lease is created as a
result of receiving the :isccmd:`lease4-update` / :isccmd:`lease6-update` command.

An example of a command to update an IPv4 lease is:

::

   {
     "command": "lease4-update",
     "arguments": {
       "ip-address": "192.0.2.1",
       "hostname": "newhostname.example.org",
       "hw-address": "1a:1b:1c:1d:1e:1f",
       "subnet-id": 44,
       "force-create": true
     }
   }

An example of a command to update an IPv6 lease is:

::

   {
     "command": "lease6-update",
     "arguments": {
       "ip-address": "2001:db8::1",
       "duid": "88:88:88:88:88:88:88:88",
       "iaid": 7654321,
       "hostname": "newhostname.example.org",
       "subnet-id": 66,
       "force-create": false
     }
   }

As with other update commands, this command overwrites all the contents of the
entry. If the lease previously had a resource assigned to it, and the
:isccmd:`lease4-update` / :isccmd:`lease6-update` command is missing the resource, it is
deleted from the lease database. If an incremental update of the lease is
desired, then this can be achieved by issuing a :isccmd:`lease4-get` / :isccmd:`lease6-get`
command to get the current state of the lease, selecting the lease from the
response, modifying it to the required outcome, and then issuing the
:isccmd:`lease4-update` / :isccmd:`lease6-update` command with the resulting lease attached.

.. isccmd:: lease4-wipe
.. _command-lease4-wipe:

.. isccmd:: lease6-wipe
.. _command-lease6-wipe:

The ``lease4-wipe``, ``lease6-wipe`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. warning::

   The :isccmd:`lease4-wipe` and :isccmd:`lease6-wipe` commands are deprecated
   and they will be removed in the future.

:isccmd:`lease4-wipe` and :isccmd:`lease6-wipe` are designed to remove all leases
associated with a given subnet. This administrative task is expected to
be used when an existing subnet is being retired. The leases
are not properly expired; no DNS updates are carried out, no log
messages are created, and hooks are not called for the leases being
removed.

An example of :isccmd:`lease4-wipe` is:

::

   {
     "command": "lease4-wipe",
     "arguments": {
       "subnet-id": 44
     }
   }

An example of :isccmd:`lease6-wipe` is:

::

   {
     "command": "lease6-wipe",
     "arguments": {
       "subnet-id": 66
     }
   }

The commands return a text description of the number of leases removed,
plus the status code 0 (success) if any leases were removed or 3 (empty)
if there were no leases. Status code 1 (error) may be returned if the
parameters are incorrect or some other exception is encountered.

``subnet-id`` 0 has a special meaning; it tells Kea to delete leases from
all configured subnets. Also, the ``subnet-id`` parameter may be omitted. If
not specified, leases from all subnets are wiped.

Note: currently only memfile lease storage supports this command.

.. isccmd:: lease4-resend-ddns
.. _command-lease4-resend-ddns:

.. isccmd:: lease6-resend-ddns
.. _command-lease6-resend-ddns:

The ``lease4-resend-ddns``, ``lease6-resend-ddns`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`lease4-resend-ddns` and :isccmd:`lease6-resend-ddns` can be used to generate
a request to :iscman:`kea-dhcp-ddns` to update the DNS entries for an existing
lease.  The desired lease is selected by a single parameter, ``"ip-address"``.
For an update request to be generated, DDNS updating must be enabled
and DNS entries must have already been made (or attempted) for the lease.
In other words, all of the following must be true:

- DDNS updating must be enabled (i.e. ``"dhcp-ddns":{ "enable-updates": true"}``).
- The lease's hostname must not be empty.
- At least one of the lease's DNS direction flags (``fqdn_fwd`` or ``fqdn_rev``) must be true.

An example :isccmd:`lease4-resend-ddns` command for getting a lease using an IPv4
address is:

::

   {
       "command": "lease4-resend-ddns",
       "arguments": {
           "ip-address": "192.0.2.1"
       }
   }

An example of the :isccmd:`lease6-resend-ddns` query is:

::

   {
     "command": "lease6-resend-ddns",
     "arguments": {
       "ip-address": "2001:db8:1::1"
     }
   }

Commands :isccmd:`lease4-resend-ddns` and :isccmd:`lease6-resend-ddns` return an indication of the
result of the operation. It has one of the following values: 0 (success), 1 (error),
or 3 (empty). An empty result means that a query has been completed properly, but the
object (a lease in this case) has not been found.

A successful result does not mean that DNS has been successfully updated; it
indicates that a request to update DNS has been successfully created and
queued for transmission to :iscman:`kea-dhcp-ddns`.

Here's an example of a result returned when the lease was found:

::

   {
     "result": 0,
     "text": "NCR generated for: 2001:db8:1::1, hostname: example.com."
   }

.. isccmd:: lease4-write
.. _command-lease4-write:

.. isccmd:: lease6-write
.. _command-lease6-write:

The ``lease4-write``, ``lease6-write`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:isccmd:`lease4-write` and :isccmd:`lease6-write` can be used for recovery in emergency
situations where the memfile lease file is damaged, e.g. removed by
accident or truncated by a full file system, but the in-memory database
is still valid. These commands are supported only by the memfile database
backend and write the lease database into a CSV file. They take the path
of the file as the ``filename`` argument. If the specified output file
is the same as the configured memfile one, the backend closes and reopens
the file in an attempt to synchronize both the files and the in-memory images
of the lease database. The extension ``.bak`` and the server PID number are added
to the previous filename: for example, ``.bak14326``.

.. note::

    As of Kea 2.6.3, the lease file may only be written to the data directory
    determined during compilation: ``"[kea-install-dir]/var/lib/kea"``. This
    path may be overridden at startup by setting the environment variable
    ``KEA_DHCP_DATA_DIRECTORY`` to the desired path.  If a path other than
    this value is used in ``filename``, Kea will emit an error and refuse to start
    or, if already running, log an unrecoverable error.  For ease of use in
    specifying a custom file name simply omit the path portion from ``filename``.

.. note::

   These commands do not replace the LFC mechanism; they should be used
   only in exceptional circumstances, such as when recovering after
   running out of disk space.
