.. ischooklib:: libdhcp_stat_cmds.so
.. _hooks-stat-cmds:

``libdhcp_stat_cmds.so``: Statistics Commands for Supplemental Lease Statistics
===============================================================================

This library provides additional commands for retrieving lease
statistics from Kea DHCP servers. These commands were added to address
an issue with obtaining accurate lease statistics in deployments running
multiple Kea servers that use a shared lease backend. The in-memory
statistics kept by individual servers only track lease changes made by
that server; thus, in a deployment with multiple servers (e.g. two
:iscman:`kea-dhcp6` servers using the same PostgreSQL database for lease storage),
these statistics are incomplete. The MySQL and PostgreSQL backends in
Kea track lease allocation changes as they occur via database triggers.
Additionally, all the lease backends were extended to support
retrieving lease statistics for a single subnet, a range
of subnets, or all subnets. Finally, this library provides commands
for retrieving these statistics.

.. note::

    :ischooklib:`libdhcp_stat_cmds.so` is part of the open source code and is
    available to every Kea user.

.. note::

   This library can only be loaded by the :iscman:`kea-dhcp4` or
   :iscman:`kea-dhcp6` process.

The commands provided by this library are:

-  :isccmd:`stat-lease4-get` - fetches DHCPv4 lease statistics.

-  :isccmd:`stat-lease6-get` - fetches DHCPv6 lease statistics.

The Statistics Commands library is part of the open source code and is
available to every Kea user.

All commands use JSON syntax and can be issued directly to the servers
via either the control channel (see :ref:`ctrl-channel`) or the
Control Agent (see :ref:`kea-ctrl-agent`).

This library is loaded in the same way as other libraries and currently has no
parameters:

::

   "Dhcp6": {
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_stat_cmds.so"
           },
           ...
       ]
   }

In a deployment with multiple Kea DHCP servers sharing a common lease
storage, this hook library can be loaded by any or all of the servers. However,
a server's response to a :isccmd:`stat-lease4-get` / :isccmd:`stat-lease6-get`
command will only contain data for subnets known to
that server. In other words, if a subnet does not appear in a server's
configuration, Kea will not retrieve statistics for it.

.. isccmd:: stat-lease4-get
.. _command-stat-lease4-get:

.. isccmd:: stat-lease6-get
.. _command-stat-lease6-get:

The ``stat-lease4-get``, ``stat-lease6-get`` Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :isccmd:`stat-lease4-get` and
:isccmd:`stat-lease6-get` commands fetch lease
statistics for a range of known subnets. The range of subnets is
determined through the use of optional command input parameters:

-  ``subnet-id`` - the ID of the subnet for which lease statistics
   should be fetched; used to get statistics for a single subnet. If
   the subnet does not exist, the command result code is 3 (i.e.
   ``CONTROL_RESULT_EMPTY``).

-  ``subnet-range`` - a pair of subnet IDs which describe an inclusive
   range of subnets for which statistics should be retrieved. The range
   may include one or more IDs that correspond to no subnet; in this
   case, the command only outputs lease statistics for those that
   exist. However, if the range does not include any known subnets, the
   command result code is 3 (i.e. ``CONTROL_RESULT_EMPTY``).

   -  ``first-subnet-id`` - the ID of the first subnet in the range.

   -  ``last-subnet-id`` - the ID of the last subnet in the range.

The use of ``subnet-id`` and ``subnet-range`` are mutually exclusive. If no
parameters are given, the result will contain data for all known
subnets. Note that in configurations with many subnets, this
can result in a large response.

The following command fetches lease statistics for all known subnets
from a :iscman:`kea-dhcp4` server:

::

   {
     "command": "stat-lease4-get"
   }

The following command fetches lease statistics for subnet ID 10 from a
:iscman:`kea-dhcp6` server:

::

   {
     "command": "stat-lease6-get",
     "arguments": {
       "subnet-id" : 10
     }
   }

The following command fetches lease statistics for all subnets with IDs
in the range 10 through 50 from a :iscman:`kea-dhcp4` server:

.. code-block:: json

   {
     "command": "stat-lease4-get",
     "arguments": {
       "subnet-range": {
         "first-subnet-id": 10,
         "last-subnet-id": 50
       }
     }
   }

The response to either command will contain three elements:

-  ``result`` - a numeric value indicating the outcome of the command
   where:

   -  ``0`` - the command was successful;

   -  ``1`` - an error occurred, and an explanation is the "text"
      element; or

   -  ``2`` - the fetch found no matching data.

-  ``text`` - an explanation of the command outcome. When the command
   succeeds, it contains the command name along with the number of
   rows returned.

-  ``arguments`` - a map containing the data returned by the command as
   the element "result-set", which is patterned after SQL statement
   responses:

   -  ``columns`` - a list of text column labels.

      The columns returned for DHCPv4 are:

      -  ``subnet-id`` - the ID of the subnet.

      -  ``total-addresses`` - the total number of addresses available for
         DHCPv4 management in the subnet. In other words, this is the
         count of all addresses in all the configured pools in the subnet.

      -  ``cumulative-assigned-addresses`` - the cumulative number of addresses
         in the subnet that have been assigned to a client by the server
         since it started.

      -  ``assigned-addresses`` - the number of addresses in the subnet that
         are currently assigned to a client.

      -  ``declined-addresses`` - the number of addresses in the subnet that
         are currently declined and are thus unavailable for assignment.

      The columns returned for DHCPv6 are:

      -  ``subnet-id`` - the ID of the subnet.

      -  ``total-nas`` - the number of NA addresses available for DHCPv6
         management in the subnet. In other words, this is the count of
         all the NA addresses in all the configured NA pools in the
         subnet.

      -  ``cumulative-assigned-nas`` - the cumulative number of NA addresses
         in the subnet that have been assigned to a client by the server
         since it started.

      -  ``assigned-nas`` - the number of NA addresses in the subnet that
         are currently assigned to a client.

      -  ``declined-addresses`` - the number of NA addresses that are currently
         declined and are thus unavailable for assignment.

      -  ``total-pds`` - the total number of PD prefixes available of DHCPv6
         management in the subnet. In other words, this is the count of
         all prefixes in all the configured prefix pools in the subnet.

      -  ``cumulative-assigned-pds`` - the cumulative number of PD prefixes
         in the subnet that have been assigned to a client by the server
         since it started.

      -  ``assigned-pds`` - the number of PD prefixes in the subnet that are
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
           "columns": [ "subnet-id", "total-addresses", "cumulative-assigned-addresses", "assigned-addresses", "declined-addresses" ],
           "rows": [
             [ 10, 256, 300, 111, 0 ],
             [ 20, 4098, 2034, 2034, 4 ]
           ],
           "timestamp": "2018-05-04 15:03:37.000000"
         }
       }
     }

The response to a DHCPv6 command might look as follows, assuming subnet 10 has no
prefix pools, subnet 20 has no NA pools, and subnet 30 has both NA and
PD pools:

::

     {
       "result": 0,
       "text": "stat-lease6-get: 2 rows found",
       "arguments": {
         "result-set": {
           "columns": [ "subnet-id", "total-nas", "cumulative-assigned-nas", "assigned-nas", "declined-addresses", "total-pds", "cumulative-assigned-pds", "assigned-pds" ],
           "rows": [
             [ 10, 4096, 5000, 2400, 3, 0, 0, 0],
             [ 20, 0, 0, 0, 0, 1048, 300, 233 ],
             [ 30, 256, 60, 60, 0, 1048, 15, 15 ]
           ],
           "timestamp": "2018-05-04 15:03:37.000000"
         }
       }
     }
