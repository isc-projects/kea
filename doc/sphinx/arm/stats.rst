.. _stats:

**********
Statistics
**********

Statistics Overview
===================

Both Kea DHCP servers support statistics gathering. A working DHCP
server encounters various events that can cause certain statistics to be
collected. For example, a DHCPv4 server may receive a packet
(the ``pkt4-received`` statistic increases by one) that after parsing is
identified as a DHCPDISCOVER (``pkt4-discover-received``). The server
processes it and decides to send a DHCPOFFER representing its answer
(the ``pkt4-offer-sent`` and ``pkt4-sent statistics`` increase by one). Such
events happen frequently, so it is not uncommon for the statistics to have
values in the high thousands. They can serve as an easy and powerful
tool for observing a server's and a network's health. For example, if
the ``pkt4-received`` statistic stops growing, it means that the clients'
packets are not reaching the server.

There are four types of statistics:

-  *integer* - this is the most common type. It is implemented as a
   64-bit integer (int64_t in C++), so it can hold any value between
   -2^63 to 2^63-1.

-  *big integer* - this type is intended to hold large numbers. It is
   implemented as a 128-bit integer (boost::multiprecision::int128_t in C++), so
   it can hold any value between -2^127 to 2^127-1.

-  *floating point* - this type is intended to store floating-point
   precision. It is implemented as a C++ double type.

-  *duration* - this type is intended for recording time periods. It
   uses the \`boost::posix_time::time_duration type, which stores hours,
   minutes, seconds, and microseconds.

-  *string* - this type is intended for recording statistics in text
   form. It uses the C++ std::string type.

During normal operation, the DHCPv4 and DHCPv6 servers gather
statistics. For a list of DHCPv4 and DHCPv6 statistics, see
:ref:`dhcp4-stats` and :ref:`dhcp6-stats`, respectively.

To extract data from the statistics module, the control channel can be
used. See :ref:`ctrl-channel` for details. It is possible to
retrieve a single statistic or all statistics, reset the statistics (i.e.
set them to a neutral value, typically zero), or even completely remove a
single statistic or all statistics. See the section :ref:`command-stats`
for a list of statistics-oriented commands.

Statistics can be used by external tools to monitor Kea. One example of such a tool is Stork.
See :ref:`stork` for details on how to use it and other data sources to retrieve statistics periodically
to get better insight into Kea's health and operational status.

.. _stats-lifecycle:

Statistics Lifecycle
====================

All of the statistics supported by Kea's servers are initialized upon the servers' startup
and are returned in response to the commands such as
:isccmd:`statistic-get-all`. The runtime statistics concerning DHCP packets
processed are initially set to 0 and are reset upon the server
restart.

Per-subnet statistics are recalculated when reconfiguration takes place.

In general, once a statistic is initialized it is held in the manager until
explicitly removed, via :isccmd:`statistic-remove` or
:isccmd:`statistic-remove-all`,
or when the server is shut down.

Removing a statistic that is updated frequently makes little sense, as
it will be re-added when the server code next records that statistic.
The :isccmd:`statistic-remove` and
:isccmd:`statistic-remove-all` commands are
intended to remove statistics that are not expected to be observed in
the near future. For example, a misconfigured device in a network may
cause clients to report duplicate addresses, so the server will report
increasing values of ``pkt4-decline-received``. Once the problem is found
and the device is removed, the system administrator may want to remove
the ``pkt4-decline-received`` statistic so that it is no longer reported, until
and unless a duplicate address is again detected.

.. isccmd:: stats
.. _command-stats:

Commands for Manipulating Statistics
====================================

There are several commands defined that can be used for accessing
(``-get``), resetting to zero or a neutral value (``-reset``), or removing a
statistic completely (``-remove``). The statistics time-based
limit (``-sample-age-set``) and size-based limit (``-sample-count-set``), which
control how long or how many samples of a given statistic are retained, can also
be changed.

The difference between ``-reset`` and ``-remove`` is somewhat subtle.
The ``-reset`` command sets the value of the statistic to zero or a neutral value,
so that after this operation, the statistic has a value of 0 (integer),
0.0 (float), 0h0m0s0us (duration), or "" (string).
When requested, a statistic with the values mentioned is returned.
``-remove`` removes a statistic completely, so the statistic is no longer
reported. However, the server code may add it back if there is a reason
to record it.

.. note::

   The following sections describe commands that can be sent to the
   server; the examples are not fragments of a configuration file. For
   more information on sending commands to Kea, see
   :ref:`ctrl-channel`.

.. isccmd:: statistic-get
.. _command-statistic-get:

The ``statistic-get`` Command
-----------------------------

The :isccmd:`statistic-get` command retrieves a single statistic. It takes a
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
``arguments`` parameter. If the requested statistic is not found, the
response contains an empty map, i.e. only { } as an argument, but
the status code still indicates success (0).

Here is an example response:

::

   {
       "command": "statistic-get",
       "arguments": {
           "pkt4-received": [ [ 125, "2019-07-30 10:11:19.498739" ], [ 100, "2019-07-30 10:11:19.498662" ] ]
       },
       "result": 0
   }

.. isccmd:: statistic-reset
.. _command-statistic-reset:

The ``statistic-reset`` Command
-------------------------------

The :isccmd:`statistic-reset` command sets the specified statistic to its
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

.. isccmd:: statistic-remove
.. _command-statistic-remove:

The ``statistic-remove`` Command
--------------------------------

The :isccmd:`statistic-remove` command deletes a single statistic. It
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

.. isccmd:: statistic-get-all
.. _command-statistic-get-all:

The ``statistic-get-all`` Command
---------------------------------

The :isccmd:`statistic-get-all` command retrieves all statistics recorded. An
example command may look like this:

::

   {
       "command": "statistic-get-all",
       "arguments": { }
   }

The server responds with details of all recorded statistics, with a
result set to 0 to indicate that it iterated over all statistics (even
when the total number of statistics is zero).

Here is an example response returning all collected statistics:

::

   {
       "command": "statistic-get-all",
       "arguments": {
           "cumulative-assigned-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836166"
               ]
           ],
           "declined-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836156"
               ]
           ],
           "pkt4-ack-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616247"
               ]
           ],
           "pkt4-ack-sent": [
               [
                   0,
                   "2023-06-13 20:42:46.616290"
               ]
           ],
           "pkt4-decline-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616296"
               ]
           ],
           "pkt4-discover-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616303"
               ]
           ],
           "pkt4-inform-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616308"
               ]
           ],
           "pkt4-nak-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616312"
               ]
           ],
           "pkt4-nak-sent": [
               [
                   0,
                   "2023-06-13 20:42:46.616314"
               ]
           ],
           "pkt4-offer-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616318"
               ]
           ],
           "pkt4-offer-sent": [
               [
                   0,
                   "2023-06-13 20:42:46.616323"
               ]
           ],
           "pkt4-parse-failed": [
               [
                   0,
                   "2023-06-13 20:42:46.616326"
               ]
           ],
           "pkt4-receive-drop": [
               [
                   0,
                   "2023-06-13 20:42:46.616330"
               ]
           ],
           "pkt4-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616335"
               ]
           ],
           "pkt4-release-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616339"
               ]
           ],
           "pkt4-request-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616343"
               ]
           ],
           "pkt4-sent": [
               [
                   0,
                   "2023-06-13 20:42:46.616348"
               ]
           ],
           "pkt4-unknown-received": [
               [
                   0,
                   "2023-06-13 20:42:46.616354"
               ]
           ],
           "reclaimed-declined-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836159"
               ]
           ],
           "reclaimed-leases": [
               [
                   0,
                   "2023-06-13 20:42:46.836163"
               ]
           ],
           "subnet[1].assigned-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836173"
               ]
           ],
           "subnet[1].cumulative-assigned-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836098"
               ]
           ],
           "subnet[1].declined-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836178"
               ]
           ],
           "subnet[1].pool[0].assigned-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836205"
               ]
           ],
           "subnet[1].pool[0].cumulative-assigned-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836137"
               ]
           ],
           "subnet[1].pool[0].declined-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836213"
               ]
           ],
           "subnet[1].pool[0].reclaimed-declined-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836225"
               ]
           ],
           "subnet[1].pool[0].reclaimed-leases": [
               [
                   0,
                   "2023-06-13 20:42:46.836236"
               ]
           ],
           "subnet[1].pool[0].total-addresses": [
               [
                   11010049,
                   "2023-06-13 20:42:46.836128"
               ]
           ],
           "subnet[1].reclaimed-declined-addresses": [
               [
                   0,
                   "2023-06-13 20:42:46.836186"
               ]
           ],
           "subnet[1].reclaimed-leases": [
               [
                   0,
                   "2023-06-13 20:42:46.836194"
               ]
           ],
           "subnet[1].total-addresses": [
               [
                   11010049,
                   "2023-06-13 20:42:46.836083"
               ]
           ],
           "subnet[1].v4-lease-reuses": [
               [
                   0,
                   "2023-06-13 20:42:46.836105"
               ]
           ],
           "subnet[1].v4-reservation-conflicts": [
               [
                   0,
                   "2023-06-13 20:42:46.836111"
               ]
           ],
           "v4-allocation-fail": [
               [
                   0,
                   "2023-06-13 20:42:46.616358"
               ]
           ],
           "v4-allocation-fail-classes": [
               [
                   0,
                   "2023-06-13 20:42:46.616363"
               ]
           ],
           "v4-allocation-fail-no-pools": [
               [
                   0,
                   "2023-06-13 20:42:46.616368"
               ]
           ],
           "v4-allocation-fail-shared-network": [
               [
                   0,
                   "2023-06-13 20:42:46.616372"
               ]
           ],
           "v4-allocation-fail-subnet": [
               [
                   0,
                   "2023-06-13 20:42:46.616376"
               ]
           ],
           "v4-lease-reuses": [
               [
                   0,
                   "2023-06-13 20:42:46.616410"
               ]
           ],
           "v4-reservation-conflicts": [
               [
                   0,
                   "2023-06-13 20:42:46.616412"
               ]
           ]
       },
       "result": 0
   }

or

::

   {
       "command": "statistic-get-all",
       "arguments": {
           "cumulative-assigned-nas": [
               [
                   0,
                   "2023-06-13 21:28:57.196757"
               ]
           ],
           "cumulative-assigned-pds": [
               [
                   0,
                   "2023-06-13 21:28:57.196758"
               ]
           ],
           "declined-addresses": [
               [
                   0,
                   "2023-06-13 21:28:57.196754"
               ]
           ],
           "pkt6-advertise-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177731"
               ]
           ],
           "pkt6-advertise-sent": [
               [
                   0,
                   "2023-06-13 21:28:57.177739"
               ]
           ],
           "pkt6-decline-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177739"
               ]
           ],
           "pkt6-dhcpv4-query-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177740"
               ]
           ],
           "pkt6-dhcpv4-response-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177740"
               ]
           ],
           "pkt6-dhcpv4-response-sent": [
               [
                   0,
                   "2023-06-13 21:28:57.177741"
               ]
           ],
           "pkt6-infrequest-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177742"
               ]
           ],
           "pkt6-parse-failed": [
               [
                   0,
                   "2023-06-13 21:28:57.177742"
               ]
           ],
           "pkt6-rebind-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177743"
               ]
           ],
           "pkt6-receive-drop": [
               [
                   0,
                   "2023-06-13 21:28:57.177743"
               ]
           ],
           "pkt6-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177744"
               ]
           ],
           "pkt6-release-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177744"
               ]
           ],
           "pkt6-renew-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177745"
               ]
           ],
           "pkt6-reply-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177745"
               ]
           ],
           "pkt6-reply-sent": [
               [
                   0,
                   "2023-06-13 21:28:57.177746"
               ]
           ],
           "pkt6-request-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177747"
               ]
           ],
           "pkt6-sent": [
               [
                   0,
                   "2023-06-13 21:28:57.177747"
               ]
           ],
           "pkt6-solicit-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177748"
               ]
           ],
           "pkt6-unknown-received": [
               [
                   0,
                   "2023-06-13 21:28:57.177748"
               ]
           ],
           "reclaimed-declined-addresses": [
               [
                   0,
                   "2023-06-13 21:28:57.196755"
               ]
           ],
           "reclaimed-leases": [
               [
                   0,
                   "2023-06-13 21:28:57.196756"
               ]
           ],
           "subnet[1].assigned-nas": [
               [
                   0,
                   "2023-06-13 21:28:57.196760"
               ]
           ],
           "subnet[1].assigned-pds": [
               [
                   0,
                   "2023-06-13 21:28:57.196761"
               ]
           ],
           "subnet[1].cumulative-assigned-nas": [
               [
                   0,
                   "2023-06-13 21:28:57.196727"
               ]
           ],
           "subnet[1].cumulative-assigned-pds": [
               [
                   0,
                   "2023-06-13 21:28:57.196729"
               ]
           ],
           "subnet[1].declined-addresses": [
               [
                   0,
                   "2023-06-13 21:28:57.196763"
               ]
           ],
           "subnet[1].pd-pool[0].assigned-pds": [
               [
                   0,
                   "2023-06-13 21:28:57.196785"
               ]
           ],
           "subnet[1].pd-pool[0].cumulative-assigned-pds": [
               [
                   0,
                   "2023-06-13 21:28:57.196744"
               ]
           ],
           "subnet[1].pd-pool[0].reclaimed-leases": [
               [
                   0,
                   "2023-06-13 21:28:57.196789"
               ]
           ],
           "subnet[1].pd-pool[0].total-pds": [
               [
                   256,
                   "2023-06-13 21:28:57.196741"
               ]
           ],
           "subnet[1].pool[0].assigned-nas": [
               [
                   0,
                   "2023-06-13 21:28:57.196773"
               ]
           ],
           "subnet[1].pool[0].cumulative-assigned-nas": [
               [
                   0,
                   "2023-06-13 21:28:57.196739"
               ]
           ],
           "subnet[1].pool[0].declined-addresses": [
               [
                   0,
                   "2023-06-13 21:28:57.196775"
               ]
           ],
           "subnet[1].pool[0].reclaimed-declined-addresses": [
               [
                   0,
                   "2023-06-13 21:28:57.196779"
               ]
           ],
           "subnet[1].pool[0].reclaimed-leases": [
               [
                   0,
                   "2023-06-13 21:28:57.196783"
               ]
           ],
           "subnet[1].pool[0].total-nas": [
               [
                   281474976710656,
                   "2023-06-13 21:28:57.196736"
               ]
           ],
           "subnet[1].reclaimed-declined-addresses": [
               [
                   0,
                   "2023-06-13 21:28:57.196766"
               ]
           ],
           "subnet[1].reclaimed-leases": [
               [
                   0,
                   "2023-06-13 21:28:57.196770"
               ]
           ],
           "subnet[1].total-nas": [
               [
                   281474976710656,
                   "2023-06-13 21:28:57.196720"
               ]
           ],
           "subnet[1].total-pds": [
               [
                   256,
                   "2023-06-13 21:28:57.196724"
               ]
           ],
           "subnet[1].v6-ia-na-lease-reuses": [
               [
                   0,
                   "2023-06-13 21:28:57.196731"
               ]
           ],
           "subnet[1].v6-ia-pd-lease-reuses": [
               [
                   0,
                   "2023-06-13 21:28:57.196733"
               ]
           ],
           "v6-allocation-fail": [
               [
                   0,
                   "2023-06-13 21:28:57.177749"
               ]
           ],
           "v6-allocation-fail-classes": [
               [
                   0,
                   "2023-06-13 21:28:57.177755"
               ]
           ],
           "v6-allocation-fail-no-pools": [
               [
                   0,
                   "2023-06-13 21:28:57.177756"
               ]
           ],
           "v6-allocation-fail-shared-network": [
               [
                   0,
                   "2023-06-13 21:28:57.177756"
               ]
           ],
           "v6-allocation-fail-subnet": [
               [
                   0,
                   "2023-06-13 21:28:57.177757"
               ]
           ],
           "v6-ia-na-lease-reuses": [
               [
                   0,
                   "2023-06-13 21:28:57.177757"
               ]
           ],
           "v6-ia-pd-lease-reuses": [
               [
                   0,
                   "2023-06-13 21:28:57.177758"
               ]
           ]
       },
       "result": 0
   }

or

::

   {
       "command": "statistic-get-all",
       "arguments": {
           "ncr-error": [
               [
                   0,
                   "2023-06-13 21:42:54.627751"
               ]
           ],
           "ncr-invalid": [
               [
                   0,
                   "2023-06-13 21:42:54.627749"
               ]
           ],
           "ncr-received": [
               [
                   0,
                   "2023-06-13 21:42:54.627737"
               ]
           ],
           "queue-mgr-queue-full": [
               [
                   0,
                   "2023-06-13 21:42:54.627737"
               ]
           ],
           "update-error": [
               [
                   0,
                   "2023-06-13 21:42:54.627759"
               ]
           ],
           "update-sent": [
               [
                   0,
                   "2023-06-13 21:42:54.627752"
               ]
           ],
           "update-signed": [
               [
                   0,
                   "2023-06-13 21:42:54.627753"
               ]
           ],
           "update-success": [
               [
                   0,
                   "2023-06-13 21:42:54.627755"
               ]
           ],
           "update-timeout": [
               [
                   0,
                   "2023-06-13 21:42:54.627757"
               ]
           ],
           "update-unsigned": [
               [
                   0,
                   "2023-06-13 21:42:54.627754"
               ]
           ]
       },
       "result": 0
   }

.. isccmd:: statistic-reset-all
.. _command-statistic-reset-all:

The ``statistic-reset-all`` Command
-----------------------------------

The :isccmd:`statistic-reset` command sets all statistics to their neutral
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

.. isccmd:: statistic-remove-all
.. _command-statistic-remove-all:

The ``statistic-remove-all`` Command
------------------------------------

The :isccmd:`statistic-remove-all` command attempts to delete all statistics. An
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

.. isccmd:: statistic-sample-age-set
.. _command-statistic-sample-age-set:

The ``statistic-sample-age-set`` Command
----------------------------------------

The :isccmd:`statistic-sample-age-set` command sets a time-based limit
on samples for a given statistic. It takes two parameters: a string
called ``name``, which specifies the statistic name, and an integer value called
``duration``, which specifies the time limit for the given statistic in seconds.
An example command may look like this:

::

   {
       "command": "statistic-sample-age-set",
       "arguments": {
           "name": "pkt4-received",
           "duration": 1245
       }

   }

If the command is successful, the server responds with a status of
0, indicating success,
and an empty parameters field. If an error is encountered (e.g. the
requested statistic was not found), the server returns a status code
of 1 (error) and the text field contains the error description.

.. isccmd:: statistic-sample-age-set-all
.. _command-statistic-sample-age-set-all:

The ``statistic-sample-age-set-all`` Command
--------------------------------------------

The :isccmd:`statistic-sample-age-set-all` command sets time-based limits
on samples for all statistics. It takes a single-integer parameter
called ``duration``, which specifies the time limit for the statistic
in seconds. An example command may look like this:

::

   {
       "command": "statistic-sample-age-set-all",
       "arguments": {
           "duration": 1245
       }

   }

If the command is successful, the server responds with a status of
0, indicating success,
and an empty parameters field. If an error is encountered, the server returns
a status code of 1 (error) and the text field contains the error description.

.. isccmd:: statistic-sample-count-set
.. _command-statistic-sample-count-set:

The ``statistic-sample-count-set`` Command
------------------------------------------

The :isccmd:`statistic-sample-count-set` command sets a size-based limit
on samples for a given statistic. An example command may look
like this:

::

   {
       "command": "statistic-sample-count-set",
       "arguments": {
           "name": "pkt4-received",
           "max-samples": 100
       }

   }

If the command is successful, the server responds with a status of
0, indicating success,
and an empty parameters field. If an error is encountered (e.g. the
requested statistic was not found), the server returns a status code
of 1 (error) and the text field contains the error description.

.. isccmd:: statistic-sample-count-set-all
.. _command-statistic-sample-count-set-all:

The ``statistic-sample-count-set-all`` Command
----------------------------------------------

The :isccmd:`statistic-sample-count-set-all` command sets size-based limits
on samples for all statistics. An example command may look
like this:

::

   {
       "command": "statistic-sample-count-set-all",
       "arguments": {
           "max-samples": 100
       }

   }

If the command is successful, the server responds with a status of
0, indicating success,
and an empty parameters field. If an error is encountered, the server returns
a status code of 1 (error) and the text field contains the error description.

.. _time-series:

Time Series
===========

With certain statistics, a single isolated data point may be useful. However,
some statistics, such as received
packet size, packet processing time, or number of database queries needed to
process a packet, are not cumulative and it is useful to keep many data
points, perhaps to do some statistical analysis afterwards.


Each Kea statistic holds 20 data points; setting such
a limit prevents unlimited memory growth.
There are two ways to define the limits: time-based (e.g. keep samples from
the last 5 minutes) and size-based. The size-based
limit can be changed using one of two commands: :isccmd:`statistic-sample-count-set`,
to set a size limit for a single statistic, and :isccmd:`statistic-sample-count-set-all`,
to set size-based limits for all statistics. To set time-based
limits for a single statistic, use :isccmd:`statistic-sample-age-set`; use
:isccmd:`statistic-sample-age-set-all` to set time-based limits for all statistics.
For a given statistic only one type of limit can be active; storage
is limited by either time or size, not both.
