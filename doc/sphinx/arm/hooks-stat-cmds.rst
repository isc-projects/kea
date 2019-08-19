.. _hooks-stat-cmds:

stat_cmds: Supplemental Statistics Commands
===========================================

This library provides additional commands for retrieving lease
statistics from Kea DHCP servers. These commands were added to address
an issue with obtaining accurate lease statistics in deployments running
multiple Kea servers that use a shared lease backend. The in-memory
statistics kept by individual servers only track lease changes made by
that server; thus, in a deployment with multiple servers (e.g. two
kea-dhcp6 servers using the same PostgreSQL database for lease storage),
these statistics are incomplete. The MySQL and PostgreSQL backends in
Kea track lease allocation changes as they occur via database triggers.
Additionally, all four lease backends were extended to support
retrieving lease statistics for all subnets, a single subnet, or a range
of subnets. Finally, this library was constructed to provide commands
for retrieving these statistics.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or
   ``kea-dhcp6`` process.

The commands currently provided by this library are:

-  ``stat-lease4-get`` - fetches DHCPv4 lease statistics.

-  ``stat-lease6-get`` - fetches DHCPv6 lease statistics.

The stat commands library is part of the open source code and is
available to every Kea user.

All commands use JSON syntax and can be issued directly to the servers
via either the control channel (see :ref:`ctrl-channel`) or the
Control Agent (see :ref:`kea-ctrl-agent`).

This library may be loaded by both the kea-dhcp4 and kea-dhcp6 servers. It
is loaded in the same way as other libraries and currently has no
parameters:

::

   "Dhcp6": {
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_stat_cmds.so"
           }
           ...
       ]
   }

In a deployment with multiple Kea DHCP servers sharing a common lease
storage, this hooks library may be loaded by any or all of the servers. However, one
thing to keep in mind is that a server's response to a
stat-lease[46]-get command will only contain data for subnets known to
that server. In other words, if a subnet does not appear in a server's
configuration, Kea will not retrieve statistics for it.

.. _command-stat-lease4-get:

.. _command-stat-lease6-get:

The stat-lease4-get, stat-lease6-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``stat-lease4-get`` and ``stat-lease6-get`` commands fetch lease
statistics for a range of known subnets. The range of subnets is
determined through the use of optional command input parameters:

-  ``subnet-id`` - the ID of the subnet for which lease statistics
   should be fetched. Use this to get statistics for a single subnet. If
   the subnet does not exist, the command result code is 3 (i.e.
   CONTROL_RESULT_EMPTY).

-  ``subnet-range`` - a pair of subnet IDs which describe an inclusive
   range of subnets for which statistics should be retrieved. The range
   may include one or more IDs that correspond to no subnet; in this
   case, the command will only output lease statistics for those that
   exist. However, if the range does not include any known subnets, the
   command result code is 3 (i.e. CONTROL_RESULT_EMPTY).

   -  ``first-subnet-id`` - the ID of the first subnet in the range.

   -  ``last-subnet-id`` - the ID of the last subnet in the range.

The use of subnet-id and subnet-range are mutually exclusive. If no
parameters are given, the result will contain data for all known
subnets. Note that in configurations with large numbers of subnets, this
can result in a large response.

The following command fetches lease statistics for all known subnets
from a kea-dhcp4 server:

::

   {
     "command": "stat-lease4-get"
   }

The following command fetches lease statistics for subnet ID 10 from a
kea-dhcp6 server:

::

   {
     "command": "stat-lease6-get",
     "arguments": {
       "subnet-id" : 10
     }
   }

The following command fetches lease statistics for all subnets with IDs
in the range 10 through 50 from a kea-dhcp4 server:

::

   {
     "command": "stat-lease4-get",
     "arguments": {
       "subnet-range" {
         "first-subnet-id": 10,
         "last-subnet-id": 50,
       }
     }
   }

The response to either command will contain three elements:

-  ``result`` - a numeric value indicating the outcome of the command
   where:

   -  ``0`` - the command was successful;

   -  ``1`` - an error occurred, and an explanation will be the "text"
      element; or

   -  ``2`` - the fetch found no matching data.

-  ``text`` - an explanation of the command outcome. When the command
   succeeds it will contain the command name along with the number of
   rows returned.

-  ``arguments`` - a map containing the data returned by the command as
   the element "result-set", which is patterned after SQL statement
   responses:

   -  ``columns`` - a list of text column labels. The columns returned
      for DHCPv4 are:

      -  ``subnet-id`` - the ID of the subnet.

      -  ``total-addresses`` - the total number of addresses available for
         DHCPv4 management in the subnet. In other words, this is the
         sum of all addresses in all the configured pools in the subnet.

      -  ``assigned-addresses`` - the number of addresses in the subnet that
         are currently assigned to a client.

      -  ``declined-addresses`` - the number of addresses in the subnet that
         are currently declined and are thus unavailable for assignment.

   -  The columns returned for DHCPv6 are:

      -  ``subnet-id`` - the ID of the subnet.

      -  ``total-nas`` - the number of NA addresses available for DHCPv6
         management in the subnet. In other words, this is the sum of
         all the NA addresses in all the configured NA pools in the
         subnet.

      -  ``assigned-nas`` - the number of NA addresses in the subnet that
         are currently assigned to a client.

      -  ``declined-nas`` - the number of NA addresses that are currently
         declined and are thus unavailable for assignment.

      -  ``total-pds`` - the total number of prefixes available of DHCPv6
         management in the subnet. In other words, this is the sum of
         all prefixes in all the configured prefix pools in the subnet.

      -  ``assigned-pds`` - the number of prefixes in the subnet that are
         currently assigned to a client.

   -  ``rows`` - a list of rows, one per subnet ID. Each row contains a
      data value corresponding to and in the same order as each column
      listed in "columns" for a given subnet.

   -  ``timestamp`` - the textual date and time the data were fetched,
      expressed as GMT.

The response to a DHCPv4 command might look as follows:

::

     {
       "result": 0,
       "text": "stat-lease4-get: 2 rows found",
       "arguments": {
         "result-set": {
           "columns": [ "subnet-id", "total-addresses", "assigned-addresses", "declined-addresses" ]
           "rows": [
             [ 10, 256, 111, 0 ],
             [ 20, 4098, 2034, 4 ]
           ],
         "timestamp": "2018-05-04 15:03:37.000000"
         }
       }
     }

The response to a DHCPv6 command might look as follows (subnet 10 has no
prefix pools, subnet 20 has no NA pools, and subnet 30 has both NA and
PD pools):

::

     {
       "result": 0,
       "text": "stat-lease6-get: 2 rows found",
       "arguments": {
         "result-set": {
           "columns": [ "subnet-id", "total-nas", "assigned-nas", "declined-nas", "total-pds", "assigned-pds" ]
           "rows": [
             [ 10, 4096, 2400, 3, 0, 0],
             [ 20, 0, 0, 0, 1048, 233 ]
             [ 30, 256, 60, 0, 1048, 15 ]
           ],
         "timestamp": "2018-05-04 15:03:37.000000"
         }
       }
     }
