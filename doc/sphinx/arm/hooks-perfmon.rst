.. ischooklib:: libdhcp_perfmon.so
.. _hooks-perfmon:

``libdhcp_perfmon.so``: Performance Monitoring
==============================================

The Performance Monitoring (perfmon) hook library gives the Kea DHCPv4 and DHCPv6 server
the ability to track and report performance-related data.

.. note::

    This library is experimental and not recommended for use in production
    environments.

.. note::

    :ischooklib:`libdhcp_perfmon.so` is part of the open source code and is
    available to every Kea user.

Overview
~~~~~~~~

The perfmon library, added in Kea 2.5.6, can be loaded by the :iscman:`kea-dhcp4` or
:iscman:`kea-dhcp6` daemon by adding it to the ``hooks-libraries`` element of
the server's configuration:

.. code-block:: javascript

    {
        "hooks-libraries": [
            {
                "library": "/usr/local/lib/libdhcp_perfmon.so",
                "parameters": {
                    ...
                }
            },
            ...
        ],
        ...
    }

The library tracks the lifecycle of client query packets as they are processed by Kea,
from when the query was received by the kernel to when the response
is ready to be sent. This tracking is driven by a packet event stack, which
contains a list of event/timestamp pairs for significant milestones that
occur during the processing of a client query. The list of possible events is
shown below:

#. socket_received - kernel placed the client query into the socket buffer
#. buffer_read - server read the client query from the socket buffer
#. mt_queued - server placed the client query into its thread-pool work queue (multi-threaded mode only)
#. process_started - server has begun processing the query
#. process_completed - server has constructed the response and is ready to send it

This list is likely to expand over time; it will also be possible for hook developers
to add their own events. This will be detailed in future releases.

Passive Event Logging
~~~~~~~~~~~~~~~~~~~~~

When the perfmon hook library is loaded, it logs the packet event stack
contents for each client query that generates a response packet. The log entry
contains client query identifiers, followed by the list of event/timestamp pairs
in the order that they occurred.

For :iscman:`kea-dhcp4`, the log is identified by the label ``PERFMON_DHCP4_PKT_EVENTS``,
and emitted at logger debug level 50 or higher. For a DHCPDISCOVER it is emitted
once the DHCPOFFER is ready to send, and looks similar to the following (see
the second entry)::

   2024-03-20 10:52:20.069 INFO  [kea-dhcp4.leases/50033.140261252249344] DHCP4_LEASE_OFFER [hwtype=1 08:00:27:25:d3:f4], cid=[no info], tid=0xc288f9: lease 178.16.2.0 will be offered
   2024-03-20 10:52:20.070 DEBUG [kea-dhcp4.perfmon-hooks/50033.140261252249344] PERFMON_DHCP4_PKT_EVENTS query: [hwtype=1 08:00:27:25:d3:f4], cid=[no info], tid=0xc288f9 events=[2024-Mar-20 14:52:20.067563 : socket_received, 2024-Mar-20 14:52:20.067810 : buffer_read, 2024-Mar-20 14:52:20.067897 : mt_queued, 2024-Mar-20 14:52:20.067952 : process_started, 2024-Mar-20 14:52:20.069614 : process_completed]

..

For :iscman:`kea-dhcp6`, the log is identified by the label ``PERFMON_DHCP6_PKT_EVENTS``,
and emitted at logger debug level 50 or higher. For a DHCPV6_SOLICIT it is emitted
once the DHCPV6_ADVERTISE is ready to send, and looks similar to the following (see
the second entry)::

   2024-03-20 10:22:14.030 INFO  [kea-dhcp6.leases/47195.139913679886272] DHCP6_LEASE_ADVERT duid=[00:03:00:01:08:00:27:25:d3:f4], [no hwaddr info], tid=0xb54806: lease for address 3002:: and iaid=11189196 will be advertised
   2024-03-20 10:22:14.031 DEBUG [kea-dhcp6.perfmon-hooks/47195.139913679886272] PERFMON_DHCP6_PKT_EVENTS query: duid=[00:03:00:01:08:00:27:25:d3:f4], [no hwaddr info], tid=0xb54806 events=[2024-Mar-20 14:22:14.028729 : socket_received, 2024-Mar-20 14:22:14.028924 : buffer_read, 2024-Mar-20 14:22:14.029005 : process_started, 2024-Mar-20 14:22:14.030566 : process_completed]

..

Duration Monitoring
~~~~~~~~~~~~~~~~~~~

When monitoring is enabled, stack event data is aggregated over a specified interval. These
aggregates are referred to as "monitored durations" or simply "durations" for ease. Durations are
uniquely identified by a "duration key" which consists of the following values:

* query message type - message type of the client query (e.g.DHCPDISCOVER, DHCPV6_REQUEST)
* response message type - message type of the server response (e.g. DHCPOFFER, DHCPV6_REPLY)
* start event label - event that defines the beginning of the task (e.g. socket_received, process_started)
* stop event label - event that defines the end of the task (e.g. buffer_read, process_completed)
* subnet id - subnet selected during message processing (or 0 for global durations)

Once the server has finished constructing a response to a query, the query's event stack
is processed into a series of updates to monitored durations. If, upon updating, a
duration's sample interval is found to have been completed, it is sent to reporting
and a new sample interval is begun. The interval width is dictated by configuration
parameter ``interval-width-secs``.

The event stack for the multi-threaded mode DHCPDISCOVER/DHCPOFFER cycle shown above
contains the following events:

    +-----------------------------+--------------------+
    | Event Timestamp             | Event Label        |
    +=============================+====================+
    | 2024-Mar-20 14:52:20.067563 | socket_received    |
    +-----------------------------+--------------------+
    | 2024-Mar-20 14:52:20.067810 | buffer_read        |
    +-----------------------------+--------------------+
    | 2024-Mar-20 14:52:20.067897 | mt_queued          |
    +-----------------------------+--------------------+
    | 2024-Mar-20 14:52:20.067952 | process_started    |
    +-----------------------------+--------------------+
    | 2024-Mar-20 14:52:20.069614 | process_completed  |
    +-----------------------------+--------------------+

Assuming the selected subnet's ID was 100, the duration updates created by perfmon
from these events are shown below:

    +--------------------------------------------------------------+--------------+
    | Duration Keys for SubnetID 100                               | Update in    |
    |                                                              | microseconds |
    +==============================================================+==============+
    | DHCPDISCOVER.DHCPOFFER.socket_received-buffer_read.100       |          247 |
    +--------------------------------------------------------------+--------------+
    | DHCPDISCOVER.DHCPOFFER.buffer_read-mt_queue.100              |           87 |
    +--------------------------------------------------------------+--------------+
    | DHCPDISCOVER.DHCPOFFER.mt_queued-process_started.100         |           55 |
    +--------------------------------------------------------------+--------------+
    | DHCPDISCOVER.DHCPOFFER.process_started-process_completed.100 |         1662 |
    +--------------------------------------------------------------+--------------+
    | DHCPDISCOVER.DHCPOFFER.composite-total_response.100          |         2051 |
    +--------------------------------------------------------------+--------------+

Notice that in addition to the adjacent event updates, there is an additional duration
update for the total duration of the entire stack whose key contains the event-pair
``composite-total_response``. This tracks the total time to respond from when the query
is received until the response is ready to send. Finally, there are also global
duration updates for each of the above:

    +--------------------------------------------------------------+--------------+
    |  Global Duration Keys                                        | Update in    |
    |                                                              | microseconds |
    +==============================================================+==============+
    | DHCPDISCOVER.DHCPOFFER.socket_received-buffer_read.0         |          247 |
    +--------------------------------------------------------------+--------------+
    | DHCPDISCOVER.DHCPOFFER.buffer_read-mt_queue.0                |           87 |
    +--------------------------------------------------------------+--------------+
    | DHCPDISCOVER.DHCPOFFER.mt_queued-process_started.0           |           55 |
    +--------------------------------------------------------------+--------------+
    | DHCPDISCOVER.DHCPOFFER.process_started-process_completed.0   |         1662 |
    +--------------------------------------------------------------+--------------+
    | DHCPDISCOVER.DHCPOFFER.composite-total_response.0            |         2051 |
    +--------------------------------------------------------------+--------------+

Statistics Reporting
~~~~~~~~~~~~~~~~~~~~

When enabled, perfmon reports a duration's data each time the duration completes a
sampling interval (see ``stats-mgr-reporting`` under :ref:`perfmon-configuration`). Each
statistic employs the following naming convention:

::

    {subnet-id[x]}.perfmon.<query type>-<response type>.<start event>-<end event>.<value-name>

There is both a global and a subnet-specific value for each. Currently, the only
value reported for a given duration key is ``averages-usecs``; this statistic is the average time
between the duration's event pair over the most recently completed interval. In other
words, if during a given interval there were seven occurrences (i.e. updates) totaling
3500us, the ``average-usecs`` reported would be 500us. Continuing with the example above, the
statistics reported are named as follows for the subnet-level values:

::

    subnet[100].perfmon.DHCPDISCOVER.DHCPOFFER.socket_received-buffer_read.average-usecs
    subnet[100].perfmon.DHCPDISCOVER.DHCPOFFER.buffer_read-mt_queue.average-usecs
    subnet[100].perfmon.DHCPDISCOVER.DHCPOFFER.mt_queued-process_started.average-usecs
    subnet[100].perfmon.DHCPDISCOVER.DHCPOFFER.process_started-process_completed.average-usecs
    subnet[100].perfmon.DHCPDISCOVER.DHCPOFFER.composite-total_response.average-usecs

and as shown for global values:

::

    perfmon.DHCPDISCOVER.DHCPOFFER.socket_received-buffer_read.average-usecs
    perfmon.DHCPDISCOVER.DHCPOFFER.buffer_read-mt_queue.average-usecs
    perfmon.DHCPDISCOVER.DHCPOFFER.mt_queued-process_started.average-usecs
    perfmon.DHCPDISCOVER.DHCPOFFER.process_started-process_completed.average-usecs
    perfmon.DHCPDISCOVER.DHCPOFFER.composite-total_response.average-usecs

The results are reported to StatsMgr, an internal Kea component that reports data as statistics
that can be retrieved using statistics commands. They can be fetched using the commands
:isccmd:`statistic-get-all` or :isccmd:`statistic-get`.

Alarms
~~~~~~

Alarms may be defined to watch specific durations. Each alarm defines a high-water mark,
``high-water-ms``, and a low-water mark, ``low-water-ms``. If the reported average value
for the duration exceeds the high-water mark a WARN level alarm log is emitted, at which
point the alarm is considered "triggered." Once triggered, the WARN level log is
repeated at the alarm report interval specified by ``alarm-report-secs``, as long as the reported
average for the duration remains above the low-water mark. Once the average falls below the
low-water mark the alarm is cleared and an INFO level log is emitted.

The alarm-triggered WARN log looks similar to the following:

::

    2024-03-20 10:22:14.030 WARN [kea-dhcp6.leases/47195.139913679886272] PERFMON_ALARM_TRIGGERED Alarm for DHCPDISCOVER.DHCPOFFER.composite-total_response.0 has been triggered since 2024-03-20 10:18:20.070000, reported average duration 00:00:00.700000 exceeds high-water-ms: 500


The alarm-cleared INFO log looks like this:

::

     2024-03-20 10:30:14.030 INFO [kea-dhcp6.leases/47195.139913679886272] PERFMON_ALARM_CLEARED Alarm for DHCPDISCOVER.DHCPOFFER.composite-total_response.0 has been cleared, reported average duration 00:00:00.010000 is now below low-water-ms: 25

API Commands
~~~~~~~~~~~~

The ``perfmon-control`` Command
-------------------------------

.. isccmd:: command-perfmon-control:
.. _command-perfmon-control:

This command can be used to enable or disable active monitoring and statistics
reporting at runtime without altering or reloading configuration.

::

   {
       "command": "perfmon-control"
        "arguments": {
            "enable-monitoring": true,
            "stats-mgr-reporting": false"
        }
   }

Regardless of the arguments (if any) supplied, the resulting values of both
flags are always returned:

::

   {
       "result": 0,
       "text": "perfmon-control success",
       "arguments": {
            "enable-monitoring": true,
            "stats-mgr-reporting": false"
       }
   }

The ``perfmon-get-all-durations`` Command
-----------------------------------------

.. isccmd:: perfmon-get-all-durations:
.. _command-perfmon-get-all-durations:

This command fetches all monitored duration data currently held in memory by
the Perfmon hook library.

::

    {
        "command": "perfmon-get-all-durations",
        "arguments": {
            "result-set-format\": true"
        }
    }

A result of 0 is returned if command succeeds along with monitored duration data,
while a result of 1 is returned if command is invalid or command processing
encounters an error.

The format of the monitored duration data returned is determined by the
optional argument, ``result-set-format``.  When false, (the default), the list
of durations will be returned as a list of individual elements as shown below:

::

    {
        "arguments": {
           "durations\": [{
               "duration-key": {
                   "query-type": "DHCPDISCOVER",
                   "response-type": "DHCPOFFER",
                   "start-event": "buffer_read",
                   "stop-event": "mt_queued",
                   "subnet-id": 0
               },
               "max-duration-usecs": 118,
               "min-duration-usecs": 31,
               "occurrences": 501,
               "start-time": "2024-06-12 17:52:06.814884",
               "total-duration-usecs": 23951,
               "ave-duration-usecs\": 47
           },
           ..,
           ]",
           "result-set-format": false,
           "interval-width-secs": 5,
           "timestamp": "2024-06-12 17:52:22.397233"
       },
    "result": 0,
    "text": "perfmon-get-all-durations: n found"
    }

When ``result-set-format`` is true, the list of durations will be returned in
a format similar to an SQL result set as follows:

::

    {
        "arguments": {
            "durations-result-set": {
                "columns": [
                    "query-type",
                    "response-type",
                    "start-event",
                    "end-event",
                    "subnet-id",
                    "interval-start",
                    "occurences",
                    "min-duration-usecs",
                    "max-duration-usecs",
                    "total-duration-usecsave-duration-usecs"
                ],
                "rows": [ [
                    "DHCPDISCOVER",
                    "DHCPOFFER",
                    "buffer_read",
                    "mt_queued",
                    0,
                    "2024-06-12 17:52:06.814884",
                    501,
                    31,
                    118,
                    23951,
                    47
                    ],
                ..
                ]
            }
            "result-set-format": true,
            "interval-width-secs": 5,
            "timestamp": "2024-06-12 17:52:22.397233"
        },
        "result": 0,
        "text": "perfmon-get-all-durations: n found"
    }

The data values for each duration will be from the duration's last completed data
interval.  If a duration has no such interval, ``interval-start`` will be reported
as "<none>" and the remaining values will be zero.

.. _perfmon-configuration:


Configuration
~~~~~~~~~~~~~

Use of the performance monitoring hook library is configured via several parameters:

* enable-monitoring
    This parameter enables event data aggregation for reporting, statistics, and alarms. It defaults to ``false``.
* interval-width-secs
    This specifies the amount of time, in seconds, that individual task durations are accumulated into an
    aggregate before they are reported. The default is 60 seconds.
* stats-mgr-reporting
    This enables the reporting of aggregates to StatsMgr. It defaults to ``true``.
* alarm-report-secs
    This specifies the amount of time, in seconds, between logging instances for an alarm once it has been triggered.
    It defaults to 300 seconds.
* alarms
    This is an optional list of alarms that monitor specific duration aggregates. Each alarm is
    defined by these four parameters:

  * duration-key
        Identifies the monitored duration for the following:

    * query-type - message type of the client query (e.g.DHCPDISCOVER, DHCPV6_REQUEST)
    * response-type - message type of the server response (e.g. DHCPOFFER, DHCPV6_REPLY)
    * start-event - event that defines the beginning of the task (e.g. socket_received, process_started)
    * stop-event - event that defines the end of the task
    * subnet-id - subnet selected during message processing (or 0 for global durations)

  * enable-alarm
        Enables or disables this alarm; defaults to ``true``.

  * high-water-ms
        Specifies the value, in milliseconds, over which the duration must occur to trigger this alarm;
        must be greater than zero.

  * low-water-ms
        Specifies the value, in milliseconds, under which the duration must fall to clear this alarm;
        must be greater than zero but less than ``high-water-ms``.

.. note::
    Passive event logging is always enabled, even without specifying the "parameters" section.

A sample configuration is shown below:

.. code-block:: javascript

    {
        "hooks-libraries": [
        {
            "library": "lib/kea/hooks/libdhcp_perfmon.so",
            "parameters": {
                "enable-monitoring": true,
                "interval-width-secs": 5,
                "stats-mgr-reporting": true,
                "alarm-report-secs": 600,
                "alarms": [
                {
                    "duration-key": {
                        "query-type": "DHCPDISCOVER",
                        "response-type": "DHCPOFFER",
                        "start-event": "process-started",
                        "stop-event": "process-completed",
                        "subnet-id": 0
                    },
                    "enable-alarm": true,
                    "high-water-ms": 500,
                    "low-water-ms": 25
                }]
            }
        }]
    }
