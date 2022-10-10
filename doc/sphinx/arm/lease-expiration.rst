.. _lease-expiration:

****************
Lease Expiration
****************

The primary role of the DHCP server is to assign addresses and/or
delegate prefixes to DHCP clients. These addresses and prefixes are
often referred to as "leases." Leases are typically assigned to clients
for a finite amount of time, known as the "valid lifetime." DHCP clients
who wish to continue using their assigned leases periodically renew
them by sending the appropriate message to the DHCP server. The DHCP
server records the time when these leases are renewed and calculates new
expiration times for them.

If the client does not renew a lease before its valid lifetime elapses,
the lease is considered expired. There are many situations when the
client may cease lease renewals; common scenarios include when the machine
running the client shuts down for an extended period of time, or when a
mobile device leaves the vicinity of a network.

The process through which the DHCP server makes expired leases available
for reassignment is referred to as "lease reclamation," and expired
leases returned to availability through this process are referred to as
"reclaimed." The DHCP server attempts to reclaim an expired lease as
soon as it detects that it has expired. The server has several possible
ways to detect expiration: it may attempt to allocate a lease to a
client but find this lease already present in the database and expired;
or it can periodically query the lease database for expired leases.
Regardless of how an expired lease is detected, it must be reclaimed
before it can be assigned to a client.

This chapter explains how to configure the server to periodically query
for the expired leases, and how to minimize the impact of the periodic
lease-reclamation process on the server's responsiveness. Finally, it
explains "lease affinity," which provides the means to assign the same
lease to a returning client after its lease has expired.

Although all configuration examples in this section are provided for the
DHCPv4 server, the same parameters may be used for DHCPv6 server
configuration.

.. _lease-reclamation:

Lease Reclamation
=================

Lease reclamation is the process through which an expired lease becomes
available for assignment to the same or a different client. This process
involves the following steps for each reclaimed lease:

-  Invoke callouts for the ``lease4_expire`` or ``lease6_expire`` hook
   points, if hook libraries supporting those callouts are currently
   loaded.

-  Update the DNS, i.e. remove any DNS entries associated with the
   expired lease.

-  Update lease information in the lease database to indicate that the
   lease is now available for reassignment.

-  Update counters on the server, a process that includes increasing the
   number of reclaimed leases and decreasing the number of assigned
   addresses or delegated prefixes.

Please refer to :ref:`dhcp-ddns-server` to see how to configure DNS
updates in Kea, and to :ref:`hooks-libraries` for information about
using hooks libraries.

.. _lease-reclamation-defaults:

Lease Reclamation Configuration Parameters
==========================================

The following list presents all the configuration parameters pertaining to
processing expired leases, with their default values:

-  ``reclaim-timer-wait-time`` - this parameter governs intervals
   between the completion of the previous reclamation cycle and the start of the
   next one. Specified in seconds; the default value is 10.

-  ``flush-reclaimed-timer-wait-time`` - this parameter controls how
   often the server initiates the lease reclamation procedure. Expressed in
   seconds; the default value is 25. If both ``flush-reclaimed-timer-wait-time``
   and ``hold-reclaimed-time`` are not 0, when the client sends a release
   message the lease is expired instead of being deleted from the lease storage.

-  ``hold-reclaimed-time`` - this parameter governs how long the lease
   should be kept after it is reclaimed. This enables lease affinity
   when set to a non-zero value. Expressed in seconds; the default value
   is 3600. If both ``flush-reclaimed-timer-wait-time`` and
   ``hold-reclaimed-time`` are not 0, when the client sends a release message
   the lease is expired instead of being deleted from the lease storage.

-  ``max-reclaim-leases`` - this parameter specifies the maximum number
   of reclaimed leases that can be processed at one time. Zero means
   unlimited (i.e. process all reclaimed leases). The default value is
   100.

-  ``max-reclaim-time`` - this parameter specifies an upper limit to the
   length of time a lease reclamation procedure can take. Zero means no time
   limit. Expressed in milliseconds; the default value is 250.

-  ``unwarned-reclaim-cycles`` - if lease reclamation limits are
   specified (``max-reclaim-leases`` and/or ``max-reclaim-time``), then
   under certain circumstances the server may not be able to deal with
   the leases to be reclaimed fast enough. This parameter specifies how many
   consecutive clean-up cycles must end with remaining leases to be
   processed before a warning is printed. The default is 5 cycles.

The parameters are explained in more detail in the rest of this chapter.

The default value for any parameter is used when the parameter is not
explicitly specified in the configuration. If the
``expired-leases-processing`` map is omitted entirely in the
configuration, the default values are used for all
parameters listed above.

.. _lease-reclaim-config:

Configuring Lease Reclamation
=============================

Kea can be configured to periodically detect and reclaim expired leases.
During this process the lease entries in the database are modified or
removed. While this is happening the server does not process incoming
DHCP messages, to avoid issues with concurrent access to database
information. As a result, the server is unresponsive while lease
reclamation is performed and DHCP queries will accumulate; responses
will be sent once the lease-reclamation cycle is complete.

In deployments where response time is critical, administrators may wish
to minimize the interruptions in service caused by lease reclamation.
To this end, Kea provides configuration parameters to control the
frequency of lease reclamation cycles, the maximum number of leases
processed in a single reclamation cycle, and the maximum amount of time
a single reclamation cycle is allowed to run before being interrupted.
The following examples demonstrate how these parameters can be used:

.. code-block:: json

   {
     "Dhcp4": {
       "expired-leases-processing": {
           "reclaim-timer-wait-time": 5,
           "max-reclaim-leases": 0,
           "max-reclaim-time": 0
       }
     }
   }

The first parameter is expressed in seconds and specifies an interval
between the two consecutive lease reclamation cycles. This is explained
by the following diagram:

::


   |  c1  |            | c2 |            |c3|            | c4 |
   |<---->|<---------->|<-->|<---------->|<>|<---------->|<-->|<--
   ------------------------------------------------------------------>
   |      |     5s     |    |     5s     |  |     5s     |    | time

This diagram shows four lease-reclamation cycles (c1 through c4) of
variable duration. The duration of the reclamation cycle
depends on the number of expired leases detected and processed in a
particular cycle. This duration is usually significantly shorter than
the interval between the cycles.

According to the ``reclaim-timer-wait-time``, the server keeps fixed
intervals of five seconds between the end of one cycle and the start of
the next cycle. This guarantees the presence of 5-second-long periods during
which the server remains responsive to DHCP queries and does not perform
lease reclamation. The ``max-reclaim-leases`` and ``max-reclaim-time``
are set to 0, which sets no restriction on the maximum number of leases
reclaimed in the particular cycle, or on the maximum duration of each
cycle.

In deployments with high lease-pool utilization, relatively short valid
lifetimes, and frequently disconnecting clients which allow leases to
expire, the number of expired leases requiring reclamation at any given
time may rise significantly. In this case, it is often desirable to
apply restrictions to the maximum duration of a reclamation cycle or the
maximum number of leases reclaimed in a cycle. The following
configuration demonstrates how this can be done:

.. code-block:: json

   {
     "Dhcp4": {
       "expired-leases-processing": {
           "reclaim-timer-wait-time": 3,
           "max-reclaim-leases": 100,
           "max-reclaim-time": 50,
           "unwarned-reclaim-cycles": 10
       }
     }
   }

In this example, the ``max-reclaim-leases`` parameter limits the number of leases
reclaimed in a single cycle to 100, and the ``max-reclaim-time`` limits the
maximum duration of each cycle to 50ms. The lease-reclamation cycle will
be interrupted if either of these limitations is reached. The
reclamation of any unreclaimed leases will be attempted in subsequent
cycles.

The following diagram illustrates the behavior of the system in the
presence of many expired leases, when the limits are applied for the
reclamation cycles:

::


   | c1 |                | c2 |                | c3 |                | c4 |
   |<-->|<-------------->|<-->|<-------------->|<-->|<-------------->|<-->|<--
   ------------------------------------------------------------------------------>
   |50ms|       3s       |50ms|       3s       |50ms|       3s       |50ms|  time

In this case, if any reclamation cycle takes
more than 50ms, it is interrupted according to the value of the
``max-reclaim-time``. This results in equal durations of all reclamation
cycles over time. In this example, the limitation of the
maximum 100 leases is not reached. This may be the case when database
transactions or callouts in the hook libraries attached to the
server are slow. Regardless, the chosen values for either the maximum
number of leases or a maximum cycle time strongly depend on the
particular deployment, the lease database backend being used, any
hook libraries, etc. Administrators may need to experiment to tune the
system to suit the dynamics of their deployment.

It is important to realize that with the use of these limits, there is a
risk that expired leases will accumulate faster than the server can
reclaim them. This should not be a problem if the server is dealing with
a temporary burst of expirations, because it should be able to
eventually deal with them over time. However, if leases expire at a high
rate for a long period of time, the unreclaimed leases will pile up in
the database. To notify the administrator that the current configuration
does not satisfy the needs for reclamation of expired leases, the server
issues a warning message in the log if it is unable to reclaim all
leases within several reclamation cycles. The number of cycles after
which such a warning is issued is specified with the
``unwarned-reclaim-cycles`` configuration parameter.

Setting the ``reclaim-timer-wait-time`` to 0 disables periodic
reclamation of the expired leases.

.. _lease-affinity:

Configuring Lease Affinity
==========================

Suppose that a laptop goes into sleep mode after a period of user
inactivity. While the laptop is in sleep mode, its DHCP client does not
renew leases obtained from the server and these leases will eventually
expire. When the laptop wakes up, it is often desirable for it to
continue using its previous assigned IP addresses. To facilitate this,
the server needs to correlate returning clients with their expired
leases. When the client returns, the server first checks for those
leases and reassigns them if they have not been assigned to another
client. The ability of the server to reassign the same lease to a
returning client is referred to as "lease affinity."

When lease affinity is enabled (i.e. when ``hold-reclaimed-time`` is configured
to a value greater than zero), the server still reclaims leases according to the
parameters described in :ref:`lease-reclaim-config`, but the reclaimed leases
are held in the database for a specified amount of time rather than removed.
If both ``flush-reclaimed-timer-wait-time`` and ``hold-reclaimed-time`` are
greater than zero, the lease is expired immediately when the client sends a
release message instead of being deleted from the lease storage. When the client
returns, the server first verifies whether there are any reclaimed leases
associated with this client and then reassigns them if possible. However, it is
important to note that any reclaimed lease may be assigned to another client if
that client specifically asks for it. Therefore, lease affinity does not
guarantee that the reclaimed lease will be available for the client who used it
before; it merely increases the chances of the client being assigned the same
lease. If the lease pool is small - namely, in DHCPv4, for which address space
is limited - there is an increased likelihood that the expired lease will be
assigned to another client.

Consider the following configuration:

::

   "Dhcp4": {
       ...

       "expired-leases-processing": {
           "reclaim-timer-wait-time": 3,
           "hold-reclaimed-time": 1800,
           "flush-reclaimed-timer-wait-time": 5
       },

       ...
   }

The ``hold-reclaim-time`` specifies how many seconds after an expiration
a reclaimed lease should be held in the database for reassignment to
the same client. In the example given above, reclaimed leases are
held for 30 minutes (1800 seconds) after their expiration. During this time,
the server will likely be able to reassign the same lease to the
returning client, unless another client specifically requests this lease and the
server assigns it.

The server must periodically remove reclaimed leases for which the time
indicated by ``hold-reclaim-time`` has elapsed. The
``flush-reclaimed-timer-wait-time`` parameter controls how often the
server removes such leases. In the example provided above, the server
initiates removal of such leases five seconds after the previous
removal attempt was completed. Setting this value to 0 disables lease
affinity, meaning leases are removed from the lease database
when they are reclaimed. If lease affinity is enabled, it is recommended
that the ``hold-reclaim-time`` be set to a value significantly higher than
the ``reclaim-timer-wait-time``, as timely removal of expired-reclaimed
leases is less critical than the removal process, which may impact
server responsiveness.

There is no guarantee that lease affinity will work every time; if a
server is running out of addresses, it will reassign expired addresses
to new clients. Also, clients can request specific addresses and the
server tries to honor such requests if possible. Administrators who want to
ensure a client keeps its address, even after periods of inactivity,
should consider using host reservations or leases with very long lifetimes.

.. _leases-reclamation-using-command:

Reclaiming Expired Leases via Command
=====================================

The ``leases-reclaim`` command can be used to trigger lease reclamation at
any time. Please consult the :ref:`command-leases-reclaim` section
for details about using this command.
