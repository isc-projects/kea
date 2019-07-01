.. _stats:

**********
Statistics
**********

Statistics Overview
===================

Both Kea DHCP servers support statistics gathering. A working DHCP
server encounters various events that can cause certain statistics to be
collected. For example, a DHCPv4 server may receive a packet
(the pkt4-received statistic increases by one) that after parsing is
identified as a DHCPDISCOVER (pkt4-discover-received). The server
processes it and decides to send a DHCPOFFER representing its answer
(the pkt4-offer-sent and pkt4-sent statistics increase by one). Such events
happen frequently, so it is not uncommon for the statistics to have
values in the high thousands. They can serve as an easy and powerful
tool for observing a server's and a network's health. For example, if
the pkt4-received statistic stops growing, it means that the clients'
packets are not reaching the server.

There are four types of statistics:

-  *integer* - this is the most common type. It is implemented as a
   64-bit integer (int64_t in C++), so it can hold any value between
   -2^63 to 2^63-1.

-  *floating point* - this type is intended to store floating-point
   precision. It is implemented as a C++ double type.

-  *duration* - this type is intended for recording time periods. It
   uses the \`boost::posix_time::time_duration type, which stores hours,
   minutes, seconds, and microseconds.

-  *string* - this type is intended for recording statistics in textual
   form. It uses the C++ std::string type.

During normal operation, the DHCPv4 and DHCPv6 servers gather
statistics. For a list of DHCPv4 and DHCPv6 statistics, see
:ref:`dhcp4-stats` and :ref:`dhcp6-stats`, respectively.

To extract data from the statistics module, the control channel can be
used. See :ref:`ctrl-channel` for details. It is possible to
retrieve a single statistic or all statistics, reset statistics (i.e.
set to a neutral value, typically zero), or even completely remove a
single statistic or all statistics. See the section :ref:`command-stats`
for a list of statistics-oriented commands.

.. _stats-lifecycle:

Statistics Lifecycle
====================

It is useful to understand how the Statistics Manager module works. When
the server starts operation, the manager is empty and contains no
statistics. If the ``statistic-get-all`` command is executed at that point, an empty list is
returned. Once the server performs an operation that causes a statistic
to change, the related statistic will be created. In general, once a
statistic is recorded even once, it is kept in the manager until
explicitly removed, by ``statistic-remove`` or ``statistic-remove-all``
being called, or when the server is shut down. Per-subnet statistics are
explicitly removed when reconfiguration takes place.

Statistics are considered runtime properties, so they are not retained
after server restart.

Removing a statistic that is updated frequently makes little sense, as
it will be re-added when the server code next records that statistic.
The ``statistic-remove`` and ``statistic-remove-all`` commands are
intended to remove statistics that are not expected to be observed in
the near future. For example, a misconfigured device in a network may
cause clients to report duplicate addresses, so the server will report
increasing values of pkt4-decline-received. Once the problem is found
and the device is removed, the system administrator may want to remove
the pkt4-decline-received statistic, so it will not be reported anymore. If
a duplicate address is ever detected again, the server will add this
statistic back.

.. _command-stats:

Commands for Manipulating Statistics
====================================

There are several commands defined that can be used for accessing
(-get), resetting to zero or a neutral value (-reset), or removing a
statistic completely (-remove). The difference between reset and remove
is somewhat subtle. The reset command sets the value of the statistic to
zero or a neutral value, so after this operation, the statistic will
have a value of 0 (integer), 0.0 (float), 0h0m0s0us (duration), or ""
(string). When requested, a statistic with the values mentioned will be
returned. ``Remove`` removes a statistic completely, so the statistic
will no longer be reported. Please note that the server code may add
it back if there is a reason to record it.

.. note::

   The following sections describe commands that can be sent to the
   server; the examples are not fragments of a configuration file. For
   more information on sending commands to Kea, see
   :ref:`ctrl-channel`.

.. _command-statistic-get:

The statistic-get Command
-------------------------

The ``statistic-get`` command retrieves a single statistic. It takes a
single-string parameter called ``name``, which specifies the statistic
name. An example command may look like this:

::

   {
       "command": "statistic-get",
       "arguments": {
           "name": "pkt4-received"
       }
   }

The server returns details of the requested statistic, with a result of
0 indicating success and the specified statistic as the value of the
"arguments" parameter. If the requested statistic is not found, the
response will contain an empty map, i.e. only { } as an argument, but
the status code will still indicate success (0).

.. _command-statistic-reset:

The statistic-reset Command
---------------------------

The ``statistic-reset`` command sets the specified statistic to its
neutral value: 0 for integer, 0.0 for float, 0h0m0s0us for time
duration, and "" for string type. It takes a single-string parameter
called ``name``, which specifies the statistic name. An example command
may look like this:

::

   {
       "command": "statistic-reset",
       "arguments": {
           "name": "pkt4-received"
       }
   }

If the specific statistic is found and the reset is successful, the
server responds with a status of 0, indicating success, and an empty
parameters field. If an error is encountered (e.g. the requested
statistic was not found), the server returns a status code of 1 (error)
and the text field contains the error description.

.. _command-statistic-remove:

The statistic-remove Command
----------------------------

The ``statistic-remove`` command attempts to delete a single statistic. It
takes a single-string parameter called ``name``, which specifies the
statistic name. An example command may look like this:

::

   {
       "command": "statistic-remove",
       "arguments": {
           "name": "pkt4-received"
       }
   }

If the specific statistic is found and its removal is successful, the
server responds with a status of 0, indicating success, and an empty
parameters field. If an error is encountered (e.g. the requested
statistic was not found), the server returns a status code of 1 (error)
and the text field contains the error description.

.. _command-statistic-get-all:

The statistic-get-all Command
-----------------------------

The ``statistic-get-all`` command retrieves all statistics recorded. An
example command may look like this:

::

   {
       "command": "statistic-get-all",
       "arguments": { }
   }

The server responds with details of all recorded statistics, with a
result set to 0 to indicate that it iterated over all statistics (even
when the total number of statistics is zero).

.. _command-statistic-reset-all:

The statistic-reset-all Command
-------------------------------

The ``statistic-reset`` command sets all statistics to their neutral
values: 0 for integer, 0.0 for float, 0h0m0s0us for time duration, and
"" for string type. An example command may look like this:

::

   {
       "command": "statistic-reset-all",
       "arguments": { }
   }

If the operation is successful, the server responds with a status of 0,
indicating success, and an empty parameters field. If an error is
encountered, the server returns a status code of 1 (error) and the text
field contains the error description.

.. _command-statistic-remove-all:

The statistic-remove-all Command
--------------------------------

The ``statistic-remove-all`` command attempts to delete all statistics. An
example command may look like this:

::

   {
       "command": "statistic-remove-all",
       "arguments": { }
   }

If the removal of all statistics is successful, the server responds with
a status of 0, indicating success, and an empty parameters field. If an
error is encountered, the server returns a status code of 1 (error) and
the text field contains the error description.
