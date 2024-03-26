.. ischooklib:: libdhcp_perfmon.so
.. _hooks-perfmon:

``libdhcp_perfmon.so``: PerfMon
===============================

This hook library can be loaded by either kea-dhcp4 or kea-dhcp6 servers
to extend them with the ability to track and report performance related data.

.. note::

    This library is currently under development and not fully functional.

Overview
~~~~~~~~

The library, added in Kea 2.5.6, can be loaded by the :iscman:`kea-dhcp4` or
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

It tracks the life cycle of client query packets as they are processed by Kea,
beginning with when the query was received by the kernel to when the response
is ready to be sent.  This tracking is driven by a packet event stack which
contains a list of event/timestamp pairs for significant milestones that
occur during the processing of a client query.  The list of possible events is
shown below:

#. socket_received - Kernel placed the client query into the socket buffer
#. buffer_read - Server read the client query from the socket buffer
#. mt_queued - Server placed the client query into its thread-pool work queue (MT mode only)
#. process_started - Server has begun processing the query
#. process_completed - Server has constructed the response and is ready to send it

This list is likely to expand over time. It will also be possible for hook developers
to add their own events. This will be detailed in a future release.

Passive Event Logging
~~~~~~~~~~~~~~~~~~~~~

As long as the PerfMon hook library is loaded it will log the packet event stack
contents for each client query which generates a response packet.  The log entry
will contain client query identifiers followed the list of event/timestamp pairs
as they occurred in the order they occurred.

For :iscman:`kea-dhcp4` the log is identified by the label, ``PERFMON_DHCP4_PKT_EVENTS``,
and emitted at logger debug level 50 or higher. For a DHCPDISCOVER it is emitted
once the DHCPOFFER is ready to send and will look similar to the following (see
the second entry)::

   2024-03-20 10:52:20.069 INFO  [kea-dhcp4.leases/50033.140261252249344] DHCP4_LEASE_OFFER [hwtype=1 08:00:27:25:d3:f4], cid=[no info], tid=0xc288f9: lease 178.16.2.0 will be offered
   2024-03-20 10:52:20.070 DEBUG [kea-dhcp4.perfmon-hooks/50033.140261252249344] PERFMON_DHCP4_PKT_EVENTS query: [hwtype=1 08:00:27:25:d3:f4], cid=[no info], tid=0xc288f9 events=[2024-Mar-20 14:52:20.067563 : socket_received, 2024-Mar-20 14:52:20.067810 : buffer_read, 2024-Mar-20 14:52:20.067897 : mt_queued, 2024-Mar-20 14:52:20.067952 : process_started, 2024-Mar-20 14:52:20.069614 : process_completed]

..

For :iscman:`kea-dhcp6` the log is identified by the label, ``PERFMON_DHCP6_PKT_EVENTS``,
and emitted only at logger debug level 50 or higher. For a DHCPV6_SOLICIT it is emitted
once the DHCPV6_ADVERTISE is ready to send and will look similar to the following (see
the second entry)::

   2024-03-20 10:22:14.030 INFO  [kea-dhcp6.leases/47195.139913679886272] DHCP6_LEASE_ADVERT duid=[00:03:00:01:08:00:27:25:d3:f4], [no hwaddr info], tid=0xb54806: lease for address 3002:: and iaid=11189196 will be advertised
   2024-03-20 10:22:14.031 DEBUG [kea-dhcp6.perfmon-hooks/47195.139913679886272] PERFMON_DHCP6_PKT_EVENTS query: duid=[00:03:00:01:08:00:27:25:d3:f4], [no hwaddr info], tid=0xb54806 events=[2024-Mar-20 14:22:14.028729 : socket_received, 2024-Mar-20 14:22:14.028924 : buffer_read, 2024-Mar-20 14:22:14.029005 : process_started, 2024-Mar-20 14:22:14.030566 : process_completed]

..

Duration Monitoring
~~~~~~~~~~~~~~~~~~~

When monitoring is enabled, stack event data will be aggregated over a specified interval. These
aggregates are referred to as monitored durations or simply durations for ease. Durations are
uniquely identified by a "duration key" which consists of the following values:

* query message type - Message type of the client query (e.g.DHCPDISCOVER, DHCPV6_REQUEST)
* response message type - Message type of the server response (e.g. DHCPOFFER, DHCPV6_REPLY)
* start event label - Event that defines the beginning of the task (e.g. socket_received, process_started)
* stop event label - Event that defines the end of the task (e.g. buffer_read, process_completed)
* subnet id - subnet selected during message processing (or 0 for global durations)

Once the server has finished constructing a response to a query, the query's event stack
is processed into a series of updates to monitored durations.  If upon updating, a
duration's sample interval is found to have been completed, it is sent to reporting
and a new sample  interval is begun.

.. Note:
    Monitoring is not yet functional.

Alarms
~~~~~~

Alarms may be defined to watch specific durations. Each alarm defines a high-water mark and a
low-water mark.  When the reported average value for duration exceeds the high-water mark, a
WARN level alarm log will be emitted at which point the alarm is considered "triggered".  Once
triggered the WARN level log will be repeated at a specified alarm report interval as long the
reported average for the duration remains above the low-water mark.  Once the average falls
below the low-water mark the alarm is "cleared" and an INFO level log will be emitted.

.. Note:
    Alarms are not yet functional.

API Commands
~~~~~~~~~~~~

    Commands to enable or disable monitoring, clear or alter alarms, and fetch duration data
    are anticipated but not yet supported.

Configuration
~~~~~~~~~~~~~

An example of the anticipated configuration is shown below:

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

Where:

* enable-monitoring
    Enables event data aggregation for reporting, statisitcs, and alarms. Defaults to false.
* interval-width-secs
    The amount of time, in seconds, that individual task durations are accumulated into an
    aggregate before it is reported. Default is 60 seconds.
* stats-mgr-reporting
    Enables reporting aggregates to StatsMgr. Defaults to true.
* alarm-report-secs
    The amount of time, in seconds, between logging for an alarm once it has been triggered.
    Defaults to 300 seconds.
* alarms
    A optional list of alarms that monitor specific duration aggregates. Each alarm is
    defined by the following:

  * duration-key
        Idenitifies the monitored duration to watch

    * query-type - Message type of the client query (e.g.DHCPDISCOVER, DHCPV6_REQUEST)
    * response-type - Message type of the server response  (e.g. DHCPOFFER, DHCPV6_REPLY)
    * start-event - Event that defines the beginning of the task (e.g. socket_received, process_started)
    * stop-event - Event that defines the end of the task
    * subnet-id - subnet selected during message processing (or 0 for global durations)

  * enable-alarm
        Enables or disables this alarm. Defaults to true.

  * high-water-ms
        The value, in milliseconds, that must be exceeded to trigger this alarm.
        Must be greater than zero.

  * low-water-ms
        The value, in milliseconds, that must be subceeded to clear this alarm
        Must be greater than zero but less than high-water-ms.

.. note::
    Passive event logging is always enabled, even without specifying the 'parameters' section.

