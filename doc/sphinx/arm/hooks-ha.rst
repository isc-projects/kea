.. _high-availability-library:

ha: High Availability
=====================

This section describes the High Availability hooks library, which can be
loaded on a pair of DHCPv4 or DHCPv6 servers to increase the reliability
of the DHCP service in the event of an outage of one of the servers.
This library was previously only available to ISC's paid subscribers,
but is now part of the open source Kea, available to all users.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or
   ``kea-dhcp6`` process.

High Availability (HA) of the DHCP service is provided by running
multiple cooperating server instances. If any of these instances becomes
unavailable for any reason (DHCP software crash, Control Agent software
crash, power outage, hardware failure), a surviving server instance can
continue providing reliable service to clients. Many DHCP server
implementations include the "DHCP Failover" protocol, whose most
significant features are communication between the servers, partner
failure detection, and lease synchronization between the servers.
However, the DHCPv4 failover standardization process was never completed
by the IETF. The DHCPv6 failover standard (RFC 8156) was published, but
it is complex, difficult to use, has significant operational
constraints, and is different than its v4 counterpart. Although it may
be useful for some users to use a "standard" failover protocol, it seems
that most Kea users are simply interested in a working solution which
guarantees high availability of the DHCP service. Therefore, the Kea HA
hook library derives major concepts from the DHCP Failover protocol but
uses its own solutions for communication and configuration. It offers
its own state machine, which greatly simplifies its implementation and
generally fits better into Kea, and it provides the same features in
both DHCPv4 and DHCPv6. This document intentionally uses the term "High
Availability" rather than "Failover" to emphasize that it is not the
Failover protocol implementation.

The following sections describe the configuration and operation of the
Kea HA hook library.

Supported Configurations
~~~~~~~~~~~~~~~~~~~~~~~~

The Kea HA hook library supports two configurations, also known as HA
modes: load-balancing and hot-standby. In the load-balancing mode, two
servers respond to DHCP requests. The load-balancing function is
implemented as described in `RFC
3074 <https://tools.ietf.org/html/rfc3074>`__, with each server
responding to half the received DHCP queries. When one of the servers
allocates a lease for a client, it notifies the partner server over the
control channel (the RESTful API), so the partner can save the lease
information in its own database. If the communication with the partner
is unsuccessful, the DHCP query is dropped and the response is not
returned to the DHCP client. If the lease update is successful, the
response is returned to the DHCP client by the server which has
allocated the lease. By exchanging lease updates, both servers get a
copy of all leases allocated by the entire HA setup, and either server
can be switched to handle the entire DHCP traffic if its partner becomes
unavailable.

In the load-balancing configuration, one of the servers must be
designated as "primary" and the other as "secondary." Functionally,
there is no difference between the two during normal operation. This
distinction is required when the two servers are started at (nearly) the
same time and have to synchronize their lease databases. The primary
server synchronizes the database first. The secondary server waits for
the primary server to complete the lease database synchronization before
it starts the synchronization.

In the hot-standby configuration, one of the servers is also designated
as "primary" and the second as "secondary." However, during normal
operation, the primary server is the only one that responds to DHCP
requests. The secondary or standby server receives lease updates from
the primary over the control channel; however, it does not respond to
any DHCP queries as long as the primary is running or, more accurately,
until the secondary considers the primary to be offline. If the
secondary server detects the failure of the primary, it starts
responding to all DHCP queries.

In the configurations described above, the primary and secondary/standby
are referred to as "active" servers, because they receive lease
updates and can automatically react to the partner's failures by
responding to the DHCP queries which would normally be handled by the
partner. The HA hook library supports another server type/role: backup
server. The use of a backup server is optional, and can be implemented in both
load-balancing and hot-standby setup, in addition to the active servers.
There is no limit on the number of backup servers in the HA setup;
however, the presence of backup servers increases the latency of DHCP
responses, because not only do active servers send lease updates to each
other, but also to the backup servers.

Clocks on Active Servers
~~~~~~~~~~~~~~~~~~~~~~~~

Synchronized clocks are essential for the HA setup to operate reliably.
The servers share lease information via lease updates and during
synchronization of the databases. The lease information includes the
time when the lease was allocated and when it expires. Some clock
skew between the servers participating in the HA setup usually exists;
this is acceptable as long as the clock skew is relatively low, compared
to the lease lifetimes. However, if the clock skew becomes too high, the
different lease expiration times on different servers may cause the HA
system to malfunction. For example, one server may consider a lease to
be expired when it is actually still valid. The lease reclamation
process may remove a name associated with this lease from the DNS,
causing problems when the client later attempts to renew the lease.

Each active server monitors the clock skew by comparing its current time
with the time returned by its partner in response to the heartbeat
command. This gives a good approximation of the clock skew, although it
doesn't take into account the time between sending the response by the
partner and receiving this response by the server which sent the
heartbeat command. If the clock skew exceeds 30 seconds, a warning log
message is issued. The administrator may correct this problem by
synchronizing the clocks (e.g. using NTP); the servers should notice the
clock skew correction and stop issuing the warning.

If the clock skew is not corrected and exceeds 60 seconds, the HA
service on each of the servers is terminated, i.e. the state machine
enters the ``terminated`` state. The servers will continue to respond to
DHCP clients (as in the load-balancing or hot-standby mode), but will
exchange neither lease updates nor heartbeats and their lease databases
will diverge. In this case, the administrator should synchronize the
clocks and restart the servers.

.. _ha-server-states:

Server States
~~~~~~~~~~~~~

A DHCP server operating within an HA setup runs a state machine, and the
state of the server can be retrieved by its peers using the
``ha-heartbeat`` command sent over the RESTful API. If the partner
server doesn't respond to the ``ha-heartbeat`` command within the
specified amount of time, the communication is considered interrupted
and the server may, depending on the configuration, use additional
measures (described later in this document) to verify that the partner
is still operating. If it finds that the partner is not operating, the
server transitions to the ``partner-down`` state to handle all the
DHCP traffic directed to the system.

In this case, the surviving server continues to send the
``ha-heartbeat`` command to detect when the partner wakes up. At that
time, the partner synchronizes the lease database and when it is again
ready to operate, the surviving server returns to normal operation, i.e.
the ``load-balancing`` or ``hot-standby`` state.

The following is the list of all possible server states:

-  ``backup`` - normal operation of the backup server. In this state it
   receives lease updates from the active servers.

-  ``hot-standby`` - normal operation of the active server running in
   the hot-standby mode; both the primary and the standby server are in
   this state during their normal operation. The primary server responds
   to DHCP queries and sends lease updates to the standby server and to
   any backup servers that are present.

-  ``load-balancing`` - normal operation of the active server running in
   the load-balancing mode; both the primary and the secondary server
   are in this state during their normal operation. Both servers respond
   to DHCP queries and send lease updates to each other and to any
   backup servers that are present.

-  ``in-maintenance`` - an active server transitions to this state as a result
   of being notified by its partner that the administrator requested
   maintenance of the HA setup. The administrator requests the maintenance
   by sending the ``ha-maintenance-start`` to the server which is supposed
   to take over the responsibility for responding to the DHCP clients while
   the other server is taken offline for maintenance. If the server is
   in the ``in-maintenance`` state it can be safely shut down. The partner
   is in the ``partner-in-maintenance`` state from which it will transition
   to the ``partner-down`` state immediately after it finds that the
   server in maintenance was shut down.

-  ``partner-down`` - an active server transitions to this state after
   detecting that its partner (another active server) is offline. The
   server does not transition to this state if only a backup server is
   unavailable. In the ``partner-down`` state the active server responds
   to all DHCP queries, including those queries which are normally
   handled by the server that is now unavailable.

-  ``partner-in-maintenance`` - an active server transitions to this state
   after receiving a ``ha-maintenance-start`` command from the
   administrator. The server in this state becomes responsible
   for responding to all DHCP requests. The server sends
   ``ha-maintenance-notify`` command to the partner which is supposed
   to enter the ``in-maintenance`` state. If that is the case, the server
   remaining in the ``partner-in-maintenance`` state keeps sending lease
   updates to the partner until it finds that the parter stops
   responding to those lease updates, heartbeats or any other commands.
   In this case, the server in the ``partner-in-maintenance`` state
   transitions to the ``partner-down`` state and keeps responding to
   the queries, but no longer sends lease updates.

-  ``ready`` - an active server transitions to this state after
   synchronizing its lease database with an active partner. This state
   indicates to the partner - which may be in the ``partner-down`` state
   - that it should return to normal operation. If and when it does, the
   server in the ``ready`` state will also start normal operation.

-  ``syncing`` - an active server transitions to this state to fetch
   leases from the active partner and update the local lease database.
   When in this state, the server issues the ``dhcp-disable`` command to
   disable the DHCP service of the partner from which the leases are
   fetched. The DHCP service is disabled for a maximum time of 60
   seconds, after which it is automatically re-enabled, in case the
   syncing partner was unable to re-enable the service. If the
   synchronization is completed, the syncing server issues the
   ``dhcp-enable`` command to re-enable the DHCP service of its partner.
   The syncing operation is synchronous; the server waits for an answer
   from the partner and does nothing else while the lease
   synchronization takes place. A server that is configured not to
   synchronize the lease database with its partner, i.e. when the
   ``sync-leases`` configuration parameter is set to ``false``, will
   never transition to this state. Instead, it will transition directly
   from the ``waiting`` state to the ``ready`` state.

-  ``terminated`` - an active server transitions to this state when the
   High Availability hooks library is unable to further provide reliable
   service and a manual intervention of the administrator is required to
   correct the problem. Various issues with the HA setup may cause the
   server to transition to this state. While in this state, the server
   continues responding to DHCP clients based on the HA mode selected
   (load-balancing or hot-standby), but the lease updates are not
   exchanged and the heartbeats are not sent. Once a server has entered
   the "terminated" state, it will remain in this state until it is
   restarted. The administrator must correct the issue which caused this
   situation prior to restarting the server (e.g. synchronize the clocks);
   otherwise, the server will return to the "terminated" state once it
   finds that the issue persists.

-  ``waiting`` - each started server instance enters this state. The
   backup server transitions directly from this state to the ``backup``
   state. An active server sends a heartbeat to its partner to check its
   state; if the partner appears to be unavailable, the server
   transitions to the ``partner-down`` state. If the partner is
   available, the server transitions to the ``syncing`` or ``ready``
   state, depending on the setting of the ``sync-leases`` configuration
   parameter. If both servers appear to be in the ``waiting`` state
   (concurrent startup), the primary server transitions to the next
   state first. The secondary or standby server remains in the
   ``waiting`` state until the primary transitions to the ``ready``
   state.

..

.. note::

   Currently, restarting the HA service from the ``terminated`` state
   requires restarting the DHCP server or reloading its configuration.

Whether the server responds to the DHCP queries and which queries it
responds to is a matter of the server's state, if no administrative
action is performed to configure the server otherwise. The following
table provides the default behavior for various states.

The ``DHCP Server Scopes`` denote what group of received DHCP queries
the server responds to in the given state. An in-depth explanation of
the scopes can be found below.

.. table:: Default Behavior of the Server in Various HA States

   +------------------------+-----------------+-----------------+-----------------+
   | State                  | Server Type     | DHCP Service    | DHCP Service    |
   |                        |                 |                 | Scopes          |
   +========================+=================+=================+=================+
   | backup                 | backup server   | disabled        | none            |
   +------------------------+-----------------+-----------------+-----------------+
   | hot-standby            | primary or      | enabled         | ``HA_server1``  |
   |                        | standby         |                 | if primary,     |
   |                        | (hot-standby    |                 | none otherwise  |
   |                        | mode)           |                 |                 |
   +------------------------+-----------------+-----------------+-----------------+
   | load-balancing         | primary or      | enabled         | ``HA_server1``  |
   |                        | secondary       |                 | or              |
   |                        | (load-balancing |                 | ``HA_server2``  |
   |                        | mode)           |                 |                 |
   +------------------------+-----------------+-----------------+-----------------+
   | in-maintenance         | active server   | disabled        | none            |
   +------------------------+-----------------+-----------------+-----------------+
   | partner-down           | active server   | enabled         | all scopes      |
   +------------------------+-----------------+-----------------+-----------------+
   | partner-in-maintenance | active server   | enabled         | all scopes      |
   +------------------------+-----------------+-----------------+-----------------+
   | ready                  | active server   | disabled        | none            |
   +------------------------+-----------------+-----------------+-----------------+
   | syncing                | active server   | disabled        | none            |
   +------------------------+-----------------+-----------------+-----------------+
   | terminated             | active server   | enabled         | same as in the  |
   |                        |                 |                 | load-balancing  |
   |                        |                 |                 | or hot-standby  |
   |                        |                 |                 | state           |
   +------------------------+-----------------+-----------------+-----------------+
   | waiting                | any server      | disabled        | none            |
   +------------------------+-----------------+-----------------+-----------------+

The DHCP service scopes require some explanation. The HA configuration
must specify a unique name for each server within the HA setup. This
document uses the following convention within the provided examples:
``server1`` for a primary server, ``server2`` for the secondary or
standby server, and ``server3`` for the backup server. In real life any
names can be used as long as they remain unique.

In the load-balancing mode there are two scopes specified for the active
servers: ``HA_server1`` and ``HA_server2``. The DHCP queries
load-balanced to ``server1`` belong to the ``HA_server1`` scope and the
queries load-balanced to ``server2`` belong to the ``HA_server2`` scope.
If either of the servers is in the ``partner-down`` state, the active
partner is responsible for serving both scopes.

In the hot-standby mode, there is only one scope - ``HA_server1`` -
because only ``server1`` is responding to DHCP queries. If that server
becomes unavailable, ``server2`` becomes responsible for this scope.

The backup servers do not have their own scopes. In some cases they can
be used to respond to queries belonging to the scopes of the active
servers. Also, a server which is neither in the partner-down state nor
in normal operation serves no scopes.

The scope names can be used to associate pools, subnets, and networks
with certain servers, so only these servers can allocate addresses or
prefixes from those pools, subnets, or networks. This is done via the
client classification mechanism (see :ref:`ha-load-balancing-advanced-config`
for more details).

.. _ha-scope-transition:

Scope Transition in a Partner-Down Case
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When one of the servers finds that its partner is unavailable, it starts
serving clients from both its own scope and the scope of the unavailable
partner. This is straightforward for new clients, i.e. those sending
DHCPDISCOVER (DHCPv4) or Solicit (DHCPv6), because those requests are
not sent to any particular server. The available server will respond to
all such queries when it is in the ``partner-down`` state.

When a client renews a lease, it sends its DHCPREQUEST (DHCPv4) or Renew
(DHCPv6) message directly to the server which has allocated the lease
being renewed. If this server is no longer available, the client will
get no response. In that case, the client continues to use its lease and
attempts to renew until the rebind timer (T2) elapses. The client then
enters the rebinding phase, in which it sends a DHCPREQUEST (DHCPv4) or
Rebind (DHCPv6) message to any available server. The surviving server
will receive the rebinding request and will typically extend the
lifetime of the lease. The client then continues to contact that new
server to renew its lease as appropriate.

If and when the other server once again becomes available, both active
servers will eventually transition to the ``load-balancing`` or
``hot-standby`` state, in which they will again be responsible for their
own scopes. Some clients belonging to the scope of the restarted server
will try to renew their leases via the surviving server, but this server
will not respond to them anymore; the client will eventually transition
back to the correct server via the rebinding mechanism.

.. _ha-load-balancing-config:

Load-Balancing Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following is the configuration snippet to enable high availability
on the primary server within the load-balancing configuration. The same
configuration should be applied on the secondary and backup servers,
with the only difference that ``this-server-name`` should be set to
``server2`` and ``server3`` on those servers, respectively.

::

   "Dhcp4": {
       "hooks-libraries": [{
           "library": "/usr/lib/kea/hooks/libdhcp_lease_cmds.so",
           "parameters": { }
       }, {
           "library": "/usr/lib/kea/hooks/libdhcp_ha.so",
           "parameters": {
               "high-availability": [{
                   "this-server-name": "server1",
                   "mode": "load-balancing",
                   "heartbeat-delay": 10000,
                   "max-response-delay": 10000,
                   "max-ack-delay": 5000,
                   "max-unacked-clients": 5,
                   "peers": [{
                       "name": "server1",
                       "url": "http://192.168.56.33:8000/",
                       "role": "primary",
                       "auto-failover": true
                   }, {
                       "name": "server2",
                       "url": "http://192.168.56.66:8000/",
                       "role": "secondary",
                       "auto-failover": true
                   }, {
                       "name": "server3",
                       "url": "http://192.168.56.99:8000/",
                       "role": "backup",
                       "auto-failover": false
                   }]
               }]
           }
       }],

       "subnet4": [{
           "subnet": "192.0.3.0/24",
           "pools": [{
               "pool": "192.0.3.100 - 192.0.3.150",
               "client-class": "HA_server1"
            }, {
               "pool": "192.0.3.200 - 192.0.3.250",
               "client-class": "HA_server2"
            }],

            "option-data": [{
               "name": "routers",
               "data": "192.0.3.1"
            }],

            "relay": { "ip-address": "10.1.2.3" }
       }]
   }

Two hooks libraries must be loaded to enable HA:
``libdhcp_lease_cmds.so`` and ``libdhcp_ha.so``. The latter implements
the HA feature, while the former enables control commands required by HA
to fetch and manipulate leases on the remote servers. In the example
provided above, it is assumed that Kea libraries are installed in the
``/usr/lib`` directory. If Kea is not installed in the /usr directory,
the hooks libraries locations must be updated accordingly.

The HA configuration is specified within the scope of ``libdhcp_ha.so``.
Note that the top-level parameter ``high-availability`` is a list, even
though it currently contains only one entry.

The following are the global parameters which control the server's
behavior with respect to HA:

-  ``this-server-name`` - is a unique identifier of the server within
   this HA setup. It must match with one of the servers specified within
   the ``peers`` list.

-  ``mode`` - specifies an HA mode of operation. Currently supported
   modes are ``load-balancing`` and ``hot-standby``.

-  ``heartbeat-delay`` - specifies a duration in milliseconds between
   sending the last heartbeat (or other command sent to the partner) and
   the next heartbeat. The heartbeats are sent periodically to gather
   the status of the partner and to verify whether the partner is still
   operating. The default value of this parameter is 10000 ms.

-  ``max-response-delay`` - specifies a duration in milliseconds since
   the last successful communication with the partner, after which the
   server assumes that communication with the partner is interrupted.
   This duration should be greater than the ``heartbeat-delay``. Usually
   it is greater than the duration of multiple ``heartbeat-delay``
   values. When the server detects that communication is interrupted, it
   may transition to the ``partner-down`` state (when
   ``max-unacked-clients`` is 0) or trigger the failure-detection
   procedure using the values of the two parameters below. The default
   value of this parameter is 60000 ms.

-  ``max-ack-delay`` - is one of the parameters controlling partner
   failure-detection. When communication with the partner is
   interrupted, the server examines the values of the ``secs`` field
   (DHCPv4) or ``Elapsed Time`` option (DHCPv6), which denote how long
   the DHCP client has been trying to communicate with the DHCP server.
   This parameter specifies the maximum time in milliseconds for the
   client to try to communicate with the DHCP server, after which this
   server assumes that the client failed to communicate with the DHCP
   server (is "unacked"). The default value of this parameter is 10000.

-  ``max-unacked-clients`` - specifies how many "unacked" clients are
   allowed (see ``max-ack-delay``) before this server assumes that the
   partner is offline and transitions to the ``partner-down`` state. The
   special value of 0 is allowed for this parameter, which disables the
   failure-detection mechanism. In this case, a server that can't
   communicate with its partner over the control channel assumes that
   the partner server is down and transitions to the ``partner-down``
   state immediately. The default value of this parameter is 10.

The values of ``max-ack-delay`` and ``max-unacked-clients`` must be
selected carefully, taking into account the specifics of the network in
which the DHCP servers are operating. Note that the server in question
may not respond to some DHCP clients because these clients are not to be
serviced by this server according to administrative policy. The server
may also drop malformed queries from clients. Therefore, selecting too
low a value for the ``max-unacked-clients`` parameter may result in a
transition to the ``partner-down`` state even though the partner is
still operating. On the other hand, selecting too high a value may
result in never transitioning to the ``partner-down`` state if the DHCP
traffic in the network is very low (e.g. at nighttime), because the number
of distinct clients trying to communicate with the server could be lower
than the ``max-unacked-clients`` setting.

In some cases it may be useful to disable the failure-detection
mechanism altogether, if the servers are located very close to each
other and network partitioning is unlikely, i.e. failure to respond to
heartbeats is only possible when the partner is offline. In such cases,
set the ``max-unacked-clients`` to 0.

The ``peers`` parameter contains a list of servers within this HA setup.
This configuration must contain at least one primary and one secondary
server. It may also contain an unlimited number of backup servers. In
this example, there is one backup server which receives lease updates
from the active servers.

These are the parameters specified for each of the peers within this
list:

-  ``name`` - specifies a unique name for the server.

-  ``url`` - specifies the URL to be used to contact this server over
   the control channel. Other servers use this URL to send control
   commands to that server.

-  ``role`` - denotes the role of the server in the HA setup. The
   following roles are supported in the load-balancing configuration:
   ``primary``, ``secondary``, and ``backup``. There must be exactly one
   primary and one secondary server in the load-balancing setup.

-  ``auto-failover`` - a boolean value which denotes whether a server
   detecting a partner's failure should automatically start serving the
   partner's clients. The default value of this parameter is true.

In our example configuration, both active servers can allocate leases
from the subnet "192.0.3.0/24". This subnet contains two address pools:
"192.0.3.100 - 192.0.3.150" and "192.0.3.200 - 192.0.3.250", which are
associated with HA server scopes using client classification. When
``server1`` processes a DHCP query, it uses the first pool for lease
allocation. Conversely, when ``server2`` processes a DHCP query it uses
the second pool. When either of the servers is in the ``partner-down``
state, it can serve leases from both pools and it selects the pool which
is appropriate for the received query. In other words, if the query
would normally be processed by ``server2`` but this server is not
available, ``server1`` will allocate the lease from the pool of
"192.0.3.200 - 192.0.3.250".

.. _ha-load-balancing-advanced-config:

Load Balancing with Advanced Classification
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the previous section, we provided an example of a load-balancing
configuration with client classification limited to the ``HA_server1``
and ``HA_server2`` classes, which are dynamically assigned to the
received DHCP queries. In many cases, HA will be needed in deployments
which already use some other client classification.

Suppose there is a system which classifies devices into two groups:
phones and laptops, based on some classification criteria specified in the
Kea configuration file. Both types of devices are allocated leases from
different address pools. Introducing HA in the load-balancing mode
results in a further split of each of those pools, as each server
allocates leases for some phones and some laptops. This requires each of
the existing pools to be split between ``HA_server1`` and
``HA_server2``, so we end up with the following classes:

-  phones_server1

-  laptops_server1

-  phones_server2

-  laptops_server2

The corresponding server configuration using advanced classification
(and the ``member`` expression) is provided below. For brevity's sake, the
HA hook library configuration has been removed from this example.

::

   "Dhcp4": {
       "client-classes": [{
           "name": "phones",
           "test": "substring(option[60].hex,0,6) == 'Aastra'",
       }, {
           "name": "laptops",
           "test": "not member('phones')"
       }, {
           "name": "phones_server1",
           "test": "member('phones') and member('HA_server1')"
       }, {
           "name": "phones_server2",
           "test": "member('phones') and member('HA_server2')"
       }, {
           "name": "laptops_server1",
           "test": "member('laptops') and member('HA_server1')"
       }, {
           "name": "laptops_server2",
           "test": "member('laptops') and member('HA_server2')"
       }],

       "hooks-libraries": [{
           "library": "/usr/lib/kea/hooks/libdhcp_lease_cmds.so",
           "parameters": { }
       }, {
           "library": "/usr/lib/kea/hooks/libdhcp_ha.so",
           "parameters": {
               "high-availability": [{
                  ...
               }]
           }
       }],

       "subnet4": [{
           "subnet": "192.0.3.0/24",
           "pools": [{
               "pool": "192.0.3.100 - 192.0.3.125",
               "client-class": "phones_server1"
           }, {
               "pool": "192.0.3.126 - 192.0.3.150",
               "client-class": "laptops_server1"
           }, {
               "pool": "192.0.3.200 - 192.0.3.225",
               "client-class": "phones_server2"
           }, {
               "pool": "192.0.3.226 - 192.0.3.250",
               "client-class": "laptops_server2"
           }],

           "option-data": [{
               "name": "routers",
               "data": "192.0.3.1"
           }],

           "relay": { "ip-address": "10.1.2.3" }
       }],
   }

The configuration provided above splits the address range into four
pools: two pools dedicated to server1 and two to server2. Each server
can assign leases to both phones and laptops. Both groups of devices are
assigned addresses from different pools. The ``HA_server1`` and
``HA_server2`` classes are built-in (see
:ref:`classification-using-vendor`) and do not need to be declared.
They are assigned dynamically by the HA hook library as a result of the
load-balancing algorithm. ``phones_*`` and ``laptop_*`` evaluate to
"true" when the query belongs to a given combination of other classes,
e.g. ``HA_server1`` and ``phones``. The pool is selected accordingly as
a result of such an evaluation.

Consult :ref:`classify` for details on how to use the ``member``
expression and class dependencies.

.. _ha-hot-standby-config:

Hot-Standby Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~

The following is an example configuration of the primary server in the
hot-standby configuration:

::

   "Dhcp4": {
       "hooks-libraries": [{
           "library": "/usr/lib/kea/hooks/libdhcp_lease_cmds.so",
           "parameters": { }
       }, {
           "library": "/usr/lib/kea/hooks/libdhcp_ha.so",
           "parameters": {
               "high-availability": [{
                   "this-server-name": "server1",
                   "mode": "hot-standby",
                   "heartbeat-delay": 10000,
                   "max-response-delay": 10000,
                   "max-ack-delay": 5000,
                   "max-unacked-clients": 5,
                   "peers": [{
                       "name": "server1",
                       "url": "http://192.168.56.33:8000/",
                       "role": "primary",
                       "auto-failover": true
                   }, {
                       "name": "server2",
                       "url": "http://192.168.56.66:8000/",
                       "role": "standby",
                       "auto-failover": true
                   }, {
                       "name": "server3",
                       "url": "http://192.168.56.99:8000/",
                       "role": "backup",
                       "auto-failover": false
                   }]
               }]
           }
       }],

       "subnet4": [{
           "subnet": "192.0.3.0/24",
           "pools": [{
               "pool": "192.0.3.100 - 192.0.3.250",
               "client-class": "HA_server1"
           }],

           "option-data": [{
               "name": "routers",
               "data": "192.0.3.1"
           }],

           "relay": { "ip-address": "10.1.2.3" }
       }]
   }

This configuration is very similar to the load-balancing configuration
described in :ref:`ha-load-balancing-config`, with a few notable
differences.

The ``mode`` is now set to ``hot-standby``, in which only one server
responds to DHCP clients. If the primary server is online, it responds
to all DHCP queries. The ``standby`` server takes over all DHCP traffic
if it discovers that the primary is unavailable.

In this mode, the non-primary active server is called ``standby`` and
that is its role.

Finally, because there is always one server responding to DHCP queries,
there is only one scope - ``HA_server1`` - in use within pools
definitions. In fact, the ``client-class`` parameter could be removed
from this configuration without harm, because there can be no conflicts
in lease allocations by different servers as they do not allocate leases
concurrently. The ``client-class`` remains in this example mostly for
demonstration purposes, to highlight the differences between the
hot-standby and load-balancing modes of operation.

.. _ha-sharing-lease-info:

Lease Information Sharing
~~~~~~~~~~~~~~~~~~~~~~~~~

An HA-enabled server informs its active partner about allocated or
renewed leases by sending appropriate control commands, and the partner
updates the lease information in its own database. When the server
starts up for the first time or recovers after a failure, it
synchronizes its lease database with its partner. These two mechanisms
guarantee consistency of the lease information between the servers and
allow the designation of one of the servers to handle the entire DHCP
traffic load if the other server becomes unavailable.

In some cases, though, it is desirable to disable lease updates and/or
database synchronization between the active servers, if the exchange of
information about the allocated leases is performed using some other
mechanism. Kea supports various database types that can be used to store
leases, including MySQL, PostgreSQL, and Cassandra. Those databases
include built-in solutions for data replication which are often used by
Kea administrators to provide redundancy.

The HA hook library supports such scenarios by disabling lease updates
over the control channel and/or lease database synchronization, leaving
the server to rely on the database replication mechanism. This is
controlled by the two boolean parameters ``send-lease-updates`` and
``sync-leases``, whose values default to true:

::

   {
   "Dhcp4": {

       ...

       "hooks-libraries": [
           {
               "library": "/usr/lib/kea/hooks/libdhcp_lease_cmds.so",
               "parameters": { }
           },
           {
               "library": "/usr/lib/kea/hooks/libdhcp_ha.so",
               "parameters": {
                   "high-availability": [ {
                       "this-server-name": "server1",
                       "mode": "load-balancing",
                       "send-lease-updates": false,
                       "sync-leases": false,
                       "peers": [
                           {
                               "name": "server1",
                               "url": "http://192.168.56.33:8000/",
                               "role": "primary"
                           },
                           {
                               "name": "server2",
                               "url": "http://192.168.56.66:8000/",
                               "role": "secondary"
                           }
                       ]
                   } ]
               }
           }
       ],

       ...

   }

In the most typical use case, both parameters are set to the same value,
i.e. both are ``false`` if database replication is in use, or both are
``true`` otherwise. Introducing two separate parameters to control lease
updates and lease-database synchronization is aimed at possible special
use cases; for example, when synchronization is performed by copying a
lease file (therefore ``sync-leases`` is set to ``false``), but lease
updates should be conducted as usual (``send-lease-updates`` is set to
``true``). It should be noted that Kea does not natively support such
use cases, but users may develop their own scripts and tools around Kea
to provide such mechanisms. The HA hooks library configuration is
designed to maximize flexibility of administration.

.. _ha-syncing-page-limit:

Controlling Lease-Page Size Limit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

An HA-enabled server initiates synchronization of the lease database
after downtime or upon receiving the ``ha-sync`` command. The server
uses commands described in :ref:`lease-get-page-cmds` to fetch
leases from its partner server (lease queries). The size of the results
page (the maximum number of leases to be returned in a single response
to one of these commands) can be controlled via configuration of the HA hooks
library. Increasing the page size decreases the number of lease
queries sent to the partner server, but it causes the partner server to
generate larger responses, which lengthens transmission time as well as
increases memory and CPU utilization on both servers. Decreasing the
page size helps to decrease resource utilization, but requires more
lease queries to be issued to fetch the entire lease database.

The default value of the ``sync-page-limit`` command controlling the
page size is 10000. This means that the entire lease database can be
fetched with a single command if the size of the database is equal to or
less than 10000 lines.

.. _ha-syncing-timeouts:

Timeouts
~~~~~~~~

In deployments with a large number of clients connected to the network,
lease-database synchronization after a server failure may be a
time-consuming operation. The synchronizing server must gather all
leases from its partner, which yields a large response over the RESTful
interface. The server receives leases using the paging mechanism
described in :ref:`ha-syncing-page-limit`. Before the page of leases is fetched,
the synchronizing server sends a ``dhcp-disable`` command to disable the
DHCP service on the partner server. If the service is already disabled,
this command will reset the timeout for the DHCP service being disabled.
This timeout value is by default set to 60 seconds. If fetching a single
page of leases takes longer than the specified time, the partner server
will assume that the synchronizing server died and will resume its DHCP
service. The connection of the synchronizing server with its partner is
also protected by the timeout. If the synchronization of a single page
of leases takes longer than the specified time, the synchronizing server
terminates the connection and the synchronization fails. Both timeout
values are controlled by a single configuration parameter,
``sync-timeout``. The following configuration snippet demonstrates how
to modify the timeout for automatic re-enabling of the DHCP service on
the partner server and how to increase the timeout for fetching a single
page of leases from 60 seconds to 90 seconds:

::

   {
   "Dhcp4": {

       ...

       "hooks-libraries": [
           {
               "library": "/usr/lib/kea/hooks/libdhcp_lease_cmds.so",
               "parameters": { }
           },
           {
               "library": "/usr/lib/kea/hooks/libdhcp_ha.so",
               "parameters": {
                   "high-availability": [ {
                       "this-server-name": "server1",
                       "mode": "load-balancing",
                       "sync-timeout": 90000,
                       "peers": [
                           {
                               "name": "server1",
                               "url": "http://192.168.56.33:8000/",
                               "role": "primary"
                           },
                           {
                               "name": "server2",
                               "url": "http://192.168.56.66:8000/",
                               "role": "secondary"
                           }
                       ]
                   } ]
               }
           }
       ],

       ...

   }

It is important to note that extending this ``sync-timeout`` value may
sometimes be insufficient to prevent issues with timeouts during
lease-database synchronization. The control commands travel via the
Control Agent, which also monitors incoming (with a synchronizing
server) and outgoing (with a DHCP server) connections for timeouts. The
DHCP server also monitors the connection from the Control Agent for
timeouts. Those timeouts cannot currently be modified via configuration;
extending these timeouts is only possible by modifying them in the Kea
code and recompiling the server. The relevant constants are located in
the Kea source at: ``src/lib/config/timeouts.h``.

.. _ha-pause-state-machine:

Pausing the HA State Machine
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The high-availability state machine includes many different states
described in detail in :ref:`ha-server-states`. The server
enters each state when certain conditions are met, most often taking
into account the partner server's state. In some states the server
performs specific actions, e.g. synchronization of the lease database in
the ``syncing`` state or responding to DHCP queries according to the
configured mode of operation in the ``load-balancing`` and
``hot-standby`` states.

By default, transitions between the states are performed automatically
and the server administrator has no direct control when the transitions
take place; in most cases, the administrator does not need such control.
In some situations, however, the administrator may want to "pause" the
HA state machine in a selected state to perform some additional
administrative actions before the server transitions to the next state.

Consider a server failure which results in the loss of the entire lease
database. Typically, the server will rebuild its lease database when it
enters the ``syncing`` state by querying the partner server for leases,
but it is possible that the partner was also experiencing a failure and
lacks lease information. In this case, it may be required to reconstruct
lease databases on both servers from some external source, e.g. a backup
server. If the lease database is to be reconstructed via the RESTful API,
the servers should be started in the initial, i.e. ``waiting``, state
and remain in this state while leases are being added. In particular,
the servers should not attempt to synchronize their lease databases nor
start serving DHCP clients.

The HA hooks library provides configuration parameters and a command to
control when the HA state machine should be paused and resumed. The
following configuration causes the HA state machine to pause in the
``waiting`` state after server startup.

::

   "Dhcp4": {

       ...

       "hooks-libraries": [
           {
               "library": "/usr/lib/kea/hooks/libdhcp_lease_cmds.so",
               "parameters": { }
           },
           {
               "library": "/usr/lib/kea/hooks/libdhcp_ha.so",
               "parameters": {
                   "high-availability": [ {
                       "this-server-name": "server1",
                       "mode": "load-balancing",
                       "peers": [
                           {
                               "name": "server1",
                               "url": "http://192.168.56.33:8000/",
                               "role": "primary"
                           },
                           {
                               "name": "server2",
                               "url": "http://192.168.56.66:8000/",
                               "role": "secondary"
                           }
                       ],
                       "state-machine": {
                           "states":  [
                               {
                                   "state": "waiting",
                                   "pause": "once"
                               }
                           ]
                       }
                   } ]
               }
           }
       ],

       ...

   }

The ``pause`` parameter value ``once`` denotes that the state machine
should be paused upon the first transition to the ``waiting`` state;
later transitions to this state will not cause the state machine to
pause. Two other supported values of the ``pause`` parameter are
``always`` and ``never``. The latter is the default value for each
state, which instructs the server never to pause the state machine.

In order to "unpause" the state machine, the ``ha-continue`` command
must be sent to the paused server. This command does not take any
arguments. See :ref:`ha-control-commands` for details about commands
specific to the HA hooks library.

It is possible to configure the state machine to pause in more than one
state. Consider the following configuration:

::

   "Dhcp4": {

       ...

       "hooks-libraries": [
           {
               "library": "/usr/lib/kea/hooks/libdhcp_lease_cmds.so",
               "parameters": { }
           },
           {
               "library": "/usr/lib/kea/hooks/libdhcp_ha.so",
               "parameters": {
                   "high-availability": [ {
                       "this-server-name": "server1",
                       "mode": "load-balancing",
                       "peers": [
                           {
                               "name": "server1",
                               "url": "http://192.168.56.33:8000/",
                               "role": "primary"
                           },
                           {
                               "name": "server2",
                               "url": "http://192.168.56.66:8000/",
                               "role": "secondary"
                           }
                       ],
                       "state-machine": {
                           "states": [
                               {
                                   "state": "ready",
                                   "pause": "always"
                               },
                               {
                                   "state": "partner-down",
                                   "pause": "once"
                               }
                           ]
                       }
                   } ]
               }
           }
       ],

       ...

   }

This configuration instructs the server to pause the state machine every
time it transitions to the ``ready`` state and upon the first transition
to the ``partner-down`` state.

Refer to :ref:`ha-server-states` for a complete list of
server states. The state machine can be paused in any of the supported
states; however, it is not practical for the ``backup`` and
``terminated`` states because the server never transitions out of these
states anyway.

.. note::

   In the ``syncing`` state the server is paused before it makes an
   attempt to synchronize the lease database with a partner. To pause
   the state machine after lease-database synchronization, use the
   ``ready`` state instead.

..

.. note::

   The state of the HA state machine depends on the state of the
   cooperating server. Therefore, it must be taken into account that
   pausing the state machine of one server may affect the operation of
   the partner server. For example: if the primary server is paused in
   the ``waiting`` state, the partner server will also remain in the
   ``waiting`` state until the state machine of the primary server is
   resumed and that server transitions to the ``ready`` state.

.. _ha-ctrl-agent-config:

Control Agent Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~

:ref:`kea-ctrl-agent` describes in detail the Kea daemon, which
provides a RESTful interface to control the Kea servers. The same
functionality is used by the High Availability hooks library to establish
communication between the HA peers. Therefore, the HA library requires
that the Control Agent (CA) be started for each DHCP instance within the
HA setup. If the Control Agent is not started, the peers will not be
able to communicate with the particular DHCP server (even if the DHCP
server itself is online) and may eventually consider this server to be
offline.

The following is an example configuration for the CA running on the same
machine as the primary server. This configuration is valid for both the
load-balancing and the hot-standby cases presented in previous sections.

::

   {
   "Control-agent": {
       "http-host": "192.168.56.33",
       "http-port": 8000,

       "control-sockets": {
           "dhcp4": {
               "socket-type": "unix",
               "socket-name": "/tmp/kea-dhcp4-ctrl.sock"
           },
           "dhcp6": {
               "socket-type": "unix",
               "socket-name": "/tmp/kea-dhcp6-ctrl.sock"
           }
       }
   }
   }

.. _ha-maintenance:

Controlled Shutdown and Maintenance of DHCP servers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Having a pair of servers providing High Availability allows for controlled
shutdown and maintenance of those servers without disrupting the DHCP
service. For example, an administrator can perform an upgrade of one of
the servers while the other one continues to respond to the DHCP queries.
When the upgraded server is back online, the upgrade can be performed for
the second server. The typical problem reported for the earlier versions
of the High Availability hooks library was that the administrator did not
have a direct control over the state of the DHCP server. Shutting down
one of the servers for maintenance didn't necessarily cause the other
server to start reponding to all DHCP queries because the failure
detection algorithm described in :ref:`ha-scope-transition` requires that
the partner does not respond for a configured period of time and,
depending on the configuration, may also require that a number of DHCP
requests are not responded for a configured period of time. The
maintenance procedure, however, requires that the administrator is able
to instruct one of the servers to instantly start serving all DHCP clients
and the other server to instantly stop serving any DHCP clients so as it
can be safely shut down.

The maintenance feature of the High Availability hooks library addresses
this problem. The ``ha-maintenance-start`` command was introduced to allow
the administrator to put the pair of the active servers in states in which
one of them is responding to all DHCP queries and the other one is awaiting
a shutdown.

Suppose that the HA setup includes two active servers, e.g. ``server1``
and ``server2`` and the latter needs to be shut down for the maintenance.
The administrator should send the ``ha-maintenance-start`` to server1,
as this is the server which is going to handle the DHCP traffic while the
other one is offline. The server1 may respond with an error if its state
or the partner's state does not allow for the maintenance. For example,
the maintenance is not supported for the backup server or the server being
in the terminated state. Also, an error will be returned if the maintenance
request was already sent to the other server.

Upon receiving the ``ha-maintenance-start`` command, the server1 will
send the ``ha-maintenance-notify`` command to the server2 to put this
server in the ``in-maintenance`` state. If the server2 confirms, the server1
will transition to the ``partner-in-maintenance`` state. This is similar
to the ``partner-down`` state, except that in the ``partner-in-maintenance``
state the server1 continues to send lease updates to the server2 until
the administrator shuts down the server2. The server1 now responds to all
DHCP queries.

The administrator may safely shut down the server2 being in the
``in-maintenance`` state and perform necessary maintenance actions. When
the server2 is offline, the server1 will encounter communication issues
with the partner and will immediately transition to the ``partner-down``
state in which it will continue to respond to all DHCP queries but will
no longer send lease updates to the server2. Starting the server2 after
the maintenance will trigger normal state negotiation, lease database
synchronization and, ultimately, a transition to the load-balancing or
hot-standby state. The maintenance can now be performed for the server1.
It should be initiated by sending the ``ha-maintenance-start`` to the
server2.

If the ``ha-maintenance-start`` command was sent to the server and the
server has transitioned to the ``partner-in-maintenance`` state it is
possible to transition it and its partner back to the previous states
to resume the normal operation of the HA pair. This is achieved by
sending the ``ha-maintenance-cancel`` command to the server being
in the ``partner-in-maintenance`` state. However, if the server has
already transitioned to the ``partner-down`` state as a result of
detecting that the partner is offline, canceling the maintenance
is no longer possible.

Upgrading from Older HA Versions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The maintenance mechanism was first introduced in the Kea 1.7.4 release.
In order to upgrade the HA hooks library from the older version the
administrator must shut down one of the servers and rely on the
failover mechanism to get the online server to transition to the
partner-down state and start serving all DHCP clients. After the
successful upgrade of one of the servers to the version supporting
the maintenance mechanism it is possible to benefit from this
mechanism during the upgrade of the second server.

In such case, shut down the server running the old version. Next,
send the ``ha-maintenance-start`` to the server that has been
upgraded and supports the maintenance mechanism. This server should
immediately transition to the partner-down state as it cannot
communicate with the partner being offline. In the partner-down
state the server will be responding to all DHCP requests.

.. note::

   Do not send the ``ha-maintenance-start`` command while the server
   running the old version is still online. The server receiving
   this command will return an error seeing that the partner does
   not support the maintenance mechanism.


.. _ha-control-commands:

Control Commands for High Availability
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Even though the HA hook library is designed to automatically resolve
issues with DHCP service interruptions by redirecting the DHCP traffic
to a surviving server and synchronizing the lease database when
required, it may be useful for the administrator to have more control
over the server behavior. In particular, it may be useful to be able to
trigger lease-database synchronization on demand. It may also be useful
to manually set the HA scopes that are being served.

Note that the backup server can sometimes be used to handle DHCP traffic
if both active servers are down. The backup server does not perform
failover function automatically; thus, in order to use the backup server
to respond to DHCP queries, the server administrator must enable this
function manually.

The following sections describe commands supported by the HA hooks
library which are available for the administrator.

.. _command-ha-sync:

The ha-sync Command
-------------------

The ``ha-sync`` command instructs the server to synchronize its local
lease database with the selected peer. The server fetches all leases
from the peer and updates those locally stored leases which are older
than those fetched. It also creates new leases when any of those fetched
do not exist in the local database. All leases that are not returned by
the peer but are in the local database are preserved. The database
synchronization is unidirectional; only the database on the server to
which the command has been sent is updated. In order to synchronize the
peer's database a separate ``ha-sync`` command must be issued to that peer.

Database synchronization may be triggered for both active and backup
server types. The ``ha-sync`` command has the following structure
(DHCPv4 server case):

::

   {
       "command": "ha-sync",
       "service": [ "dhcp4 "],
       "arguments": {
           "server-name": "server2",
           "max-period": 60
       }
   }

When the server receives this command it first disables the DHCP service
of the server from which it will be fetching leases, by sending the
``dhcp-disable`` command to that server. The ``max-period`` parameter
specifies the maximum duration (in seconds) for which the DHCP service
should be disabled. If the DHCP service is successfully disabled, the
synchronizing server fetches leases from the remote server by issuing
one or more ``lease4-get-page`` commands. When the lease-database
synchronization is complete, the synchronizing server sends the
``dhcp-enable`` command to the peer to re-enable its DHCP service.

The ``max-period`` value should be sufficiently long to guarantee that
it does not elapse before the synchronization is completed. Otherwise,
the DHCP server will automatically enable its DHCP function while the
synchronization is still in progress. If the DHCP server subsequently
allocates any leases during the synchronization, those new (or updated)
leases will not be fetched by the synchronizing server, leading to
database inconsistencies.

.. _command-ha-scopes:

The ha-scopes Command
---------------------

This command allows modification of the HA scopes that the server is
serving. Consult :ref:`ha-load-balancing-config` and
:ref:`ha-hot-standby-config` to learn what scopes are
available for different HA modes of operation. The ``ha-scopes`` command
has the following structure (DHCPv4 server case):

::

   {
       "command": "ha-scopes",
       "service": [ "dhcp4" ],
       "arguments": {
           "scopes": [ "HA_server1", "HA_server2" ]
       }
   }

This command configures the server to handle traffic from both the
``HA_server1`` and ``HA_server2`` scopes. To disable all scopes
specify an empty list:

::

   {
       "command": "ha-scopes",
       "service": [ "dhcp4 "],
       "arguments": {
           "scopes": [ ]
       }
   }

.. _command-ha-continue:

The ha-continue Command
-----------------------

This command is used to resume the operation of the paused HA state
machine, as described in :ref:`ha-pause-state-machine`. It takes no arguments, so the
command structure is as simple as:

::

   {
       "command": "ha-continue",
       "service": [ "dhcp4" ]
   }

.. _command-ha-heartbeat:

The ha-heartbeat Command
------------------------

The :ref:`ha-server-states` describes how the ``ha-heartbeat`` command is used by
the active HA servers to detect a failure of one of them. This command, however,
can also be sent by the system administrator to one or both servers to check their
state with regards to the HA relationship. This allows for hooking up a monitoring
system to the HA enabled servers to periodically check if they are operational
or if any manual intervention is required. The ``ha-heartbeat`` command takes no
arguments, e.g.:

::

   {
       "command": "ha-heartbeat",
       "service": [ "dhcp4" ]
   }

Upon successful communication with the server a response similar to this should
be returned:

::

   {
      "result": 0,
      "text": "HA peer status returned.",
      "arguments":
          {
              "state": "partner-down",
              "date-time": "Thu, 07 Nov 2019 08:49:37 GMT"
          }
   }

The returned state value may be one of the values listed in :ref:`ha-server-states`.
In the example above the ``partner-down`` state is returned, which indicates that
the server which responded to the command is assuming that its partner is offline,
thus it is serving all DHCP requests sent to the servers. In order to ensure that
the partner is indeed offline the administrator should send the ``ha-heartbeat``
command to the second server. If sending the command fails, e.g. as a result of
inability to establish TCP connection to the Control Agent or the Control Agent
reports issues with communication with the DHCP server, it is very likely that
the server is not running.

The typical response returned by one of the servers when both servers are
operational is:

::

   {
      "result": 0,
      "text": "HA peer status returned.",
      "arguments":
          {
              "state": "load-balancing",
              "date-time": "Thu, 07 Nov 2019 08:49:37 GMT"
          }
   }

In most cases it is desired to send the ``ha-heartbeat`` command to both HA
enabled servers to verify the state of the entire HA setup. In particular,
if the response sent to one of the servers indicates that the server is in the
``load-balancing`` state, it merely means that this server is operating as if
the partner is still functional. When the partner dies it actually takes some
time for the surviving server to realize it. The :ref:`ha-scope-transition`
section describes the algorithm which the surviving server follows before
it transitions to the ``partner-down`` state. If the ``ha-heartbeat`` command
is sent during the time window between the failure of one of the servers and the
transition of the surviving server to the ``partner-down`` state, the response
from the surviving server doesn't reflect the failure. Sending the command
to the failing server allows for detecting the failure.

.. note::

  Remember! Always send the ``ha-heartbeat`` command to both active HA servers
  to check the state of the entire HA setup. Sending it to only one of the
  servers may not reflect issues with one of the servers that just began.


.. _command-ha-status-get:

The status-get Command
------------------------

The ``status-get`` is the general purpose command supported by several Kea deamons,
not only DHCP servers. However, when sent to the DHCP server with HA enabled, it
can be used to get insight into the details of the HA specific status information
of the servers being in the HA configuration. Not only does the response contain
the status information of the server receiving this command but also the
information about its partner, if this information is available.

The following is the example response to the ``status-get`` command including
the HA status of two load balancing servers:

::

   {
       "result": 0,
       "text": "",
       "arguments": {
           "pid": 1234,
           "uptime": 3024,
           "reload": 1111,
           "ha-servers": {
               "local": {
                   "role": "primary",
                   "scopes": [ "server1" ],
                   "state": "load-balancing"
               },
                "remote": {
                   "age": 10,
                   "in-touch": true,
                   "role": "secondary",
                   "last-scopes": [ "server2" ],
                   "last-state": "load-balancing"
               }
           }
       }
   }


The ``ha-servers`` map contains two structures: ``local`` and ``remote``. The former
contains the status information of the server which received the command. The
latter contains the status information known to the local server about the
partner. The ``role`` of the partner server is gathered from the local
configuration file, therefore it should always be available. The remaining
status information such as ``last-scopes`` and ``last-state`` is not available
until the local server communicates with the remote by successfully sending
the ``ha-heartbeat`` command. If at least one such communication took place,
the returned value of ``in-touch`` parameter is set to ``true``. By examining
this value, the command sender can determine whether the information about
the remote server is reliable.

The ``last-scopes`` and ``last-state`` contain the information about the
HA scopes served by the partner and its state. Note that this information
is gathered during the heartbeat command exchange, so it may not be
accurate if the communication problem occur between the partners and this
status information is not refreshed. In such case, it may be useful to
send the ``status-get`` command to the partner server directly to check
its current state. The ``age`` parameter specifies the number of seconds
since the information from the partner was gathered (the age of this
information).

.. _command-ha-maintenance-start:

The ha-maintenance-start Command
--------------------------------

This command is used to initiate transition of the server's partner into
the ``in-maintenance`` state and the transition of the server receiving the
command into the ``partner-in-maintenance`` state. See the
:ref:`ha-maintenance` for the details.


::

   {
       "command": "ha-maintenance-start",
       "service": [ "dhcp4" ]
   }


.. _command-ha-maintenance-cancel:

The ha-maintenance-cancel Command
---------------------------------

This command is used to cancel the maintenance previously initiated using
the ``ha-maintenance-start`` command. The server receiving this command
will first send the ``ha-maintenance-notify`` with the cancel flag set
to true to its partner. Next, the server will revert from the
``partner-in-maintenance`` state to the previous state. See the
:ref:`ha-maintenance` for the details.

::

   {
       "command": "ha-maintenance-cancel",
       "service": [ "dhcp4" ]
   }


.. _command-ha-maintenance-notify:

The ha-maintenance-notify Command
---------------------------------

This command is sent by the server receiving the ``ha-maintenance-start``
or the ``ha-maintenance-cancel`` command to its partner to cause the
partner to transition to the ``in-maintenance`` state or to revert from this
state to a previous state. See the :ref:`ha-maintenance` for the details.

::

   {
       "command": "ha-maintenance-notify",
       "service": [ "dhcp4" ],
       "arguments": {
           "cancel": false
       }
   }

.. warning::

   The ``ha-maintenance-notify`` command is not meant to be used by the
   system administrators. It is used for internal communication between
   a pair of HA enabled DHCP servers. Direct use of this command is not
   supported and may produce unintended consequences.

