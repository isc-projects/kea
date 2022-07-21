.. _hooks-high-availability:

``ha``: High Availability Outage Resilience for Kea Servers
===========================================================

This hook library can be loaded on a pair of DHCPv4 or DHCPv6 servers, to
increase the reliability of the DHCP service in the event of an outage on one
server. This library was previously only available to ISC's paid subscribers,
but is now part of the open source Kea, available to all users.

.. note::

   This library can only be loaded by the ``kea-dhcp4`` or ``kea-dhcp6`` process.

High Availability (HA) of the DHCP service is provided by running multiple
cooperating server instances. If any of these instances becomes unavailable for
any reason (DHCP software crash, Control Agent software crash, power outage,
hardware failure), a surviving server instance can continue providing reliable
service to clients. Many DHCP server implementations include the "DHCP Failover"
protocol, whose most significant features are communication between the servers,
partner failure detection, and lease synchronization between the servers.
However, the DHCPv4 failover standardization process was never completed by the
IETF. The DHCPv6 failover standard (RFC 8156) was published, but it is complex
and difficult to use, has significant operational constraints, and is different
from its v4 counterpart. Although it may be useful to use a "standard" failover
protocol, most Kea users are simply interested in a working solution which
guarantees high availability of the DHCP service. Therefore, the Kea HA hook
library derives major concepts from the DHCP failover protocol but uses its own
solutions for communication and configuration. It offers its own state machine,
which greatly simplifies its implementation and generally fits better into Kea,
and it provides the same features in both DHCPv4 and DHCPv6. This document
intentionally uses the term "high availability" rather than "failover" to
emphasize that it is not the failover protocol implementation.

The following sections describe the configuration and operation of the Kea HA
hook library.

.. _ha-supported-configurations:

Supported Configurations
~~~~~~~~~~~~~~~~~~~~~~~~

The Kea HA hook library supports three configurations, also known as HA modes:
``load-balancing``, ``hot-standby``, and ``passive-backup``. In the
``load-balancing`` mode, two servers respond to DHCP requests. The
``load-balancing`` function is implemented as described in `RFC
3074 <https://tools.ietf.org/html/rfc3074>`__, with each server responding to
half the received DHCP queries. When one of the servers allocates a lease for a
client, it notifies the partner server over the control channel (via the RESTful
API), so the partner can save the lease information in its own database. If the
communication with the partner is unsuccessful, the DHCP query is dropped and
the response is not returned to the DHCP client. If the lease update is
successful, the response is returned to the DHCP client by the server which has
allocated the lease. By exchanging lease updates, both servers get a copy of all
leases allocated by the entire HA setup, and either server can be switched to
handle the entire DHCP traffic if its partner becomes unavailable.

In the ``load-balancing`` configuration, one of the servers must be designated
as ``primary`` and the other as ``secondary``. Functionally, there is no
difference between the two during normal operation. However, this distinction is
required when the two servers are started at (nearly) the same time and have to
synchronize their lease databases. The primary server synchronizes the database
first. The secondary server waits for the primary server to complete the lease
database synchronization before it starts the synchronization.

In the ``hot-standby`` configuration, one of the servers is designated as
``primary`` and the other as ``standby``. During normal operation, the primary
server is the only one that responds to DHCP requests. The standby server
receives lease updates from the primary over the control channel; however, it
does not respond to any DHCP queries as long as the primary is running or, more
accurately, until the standby considers the primary to be offline. If the
standby server detects the failure of the primary, it starts responding to all
DHCP queries.

.. note::

   Operators often wonder whether to use ``load-balancing`` or ``hot-standby``
   mode. The ``load-balancing`` mode has the benefit of splitting the DHCP load
   between two instances, reducing the traffic processed by each of them.
   However, it is not always clear to the operators that using the
   ``load-balancing`` mode requires manually splitting the address pools between
   two Kea instances using client classification, to preclude both servers from
   allocating the same address to different clients.
   Such a split is not needed in the ``hot-standby`` mode. Thus, the benefit
   of using ``hot-standby`` over ``load-balancing`` is that the former has a
   simpler configuration. Conversely, ``load-balancing`` has higher performance
   potential at the cost of more complex configuration.
   See :ref:`ha-load-balancing-config` for details on how to split the pools
   using client classification.

In the configurations described above, both the primary and secondary/standby
are referred to as ``active`` servers, because they receive lease updates and
can automatically react to the partner's failures by responding to the DHCP
queries which would normally be handled by the partner. The HA hook library
supports another server type/role: ``backup``. The use of a backup server is
optional, and can be implemented in both ``load-balancing`` and ``hot-standby``
setup, in addition to the active servers. There is no limit on the number of
backup servers in the HA setup; however, the presence of backup servers may
increase the latency of DHCP responses, because not only do active servers send
lease updates to each other, but also to the backup servers. The active servers
do not expect acknowledgments from the backup servers before responding to the
DHCP clients, so the overhead of sending lease updates to the backup servers is
minimized.

In the last supported configuration, ``passive-backup``, there is only one
active server and typically one or more backup servers. A ``passive-backup``
configuration with no backup servers is also accepted, but it is no different
than running a single server with no HA function at all.

The ``passive-backup`` configuration is used in situations when an administrator
wants to take advantage of the backup server(s) as an additional storage for
leases without running the full-blown failover setup. In this case, if the
primary server fails, the DHCP service is lost; it requires the administrator to
manually restart the primary to resume DHCP service. The administrator may also
configure one of the backup servers to provide DHCP service to the clients, as
these servers should have accurate or nearly accurate information about the
allocated leases. The major advantage of the ``passive-backup`` mode is that it
provides some redundancy of the lease information but with better performance of
the primary server responding to the DHCP queries.
The primary server does not have to wait for acknowledgments to the lease
updates from the backup servers before it sends a response to the DHCP client.
This reduces the response time compared to the ``load-balancing`` and
``hot-standby`` cases, in which the server responding to the DHCP query has to
wait for the acknowledgment from the other active server before it can respond
to the client.

.. note::

   An interesting use case for a single active server running in the
   ``passive-backup`` mode is a notification service, in which software
   pretending to be a backup server receives live notifications about allocated
   and deleted leases from the primary server and can display them on a
   monitoring screen, trigger alerts, etc.

Clocks on Active Servers
~~~~~~~~~~~~~~~~~~~~~~~~

Synchronized clocks are essential for the HA setup to operate reliably.
The servers share lease information - via lease updates and during
synchronization of the databases - including the time when the lease was
allocated and when it expires. Some clock skew between the servers participating
in the HA setup usually exists; this is acceptable as long as the clock skew is
relatively low, compared to the lease lifetimes. However, if the clock skew
becomes too high, the different lease expiration times on different servers may
cause the HA system to malfunction. For example, one server may consider a lease
to be expired when it is actually still valid. The lease reclamation process may
remove a name associated with this lease from the DNS, causing problems when the
client later attempts to renew the lease.

Each active server monitors the clock skew by comparing its current time with
the time returned by its partner in response to the heartbeat command. This
gives a good approximation of the clock skew, although it does not take into
account the time between the partner sending the response and the receipt of
this response by the server which sent the heartbeat command. If the clock skew
exceeds 30 seconds, a warning log message is issued. The administrator may
correct this problem by synchronizing the clocks (e.g. using NTP); the servers
should notice the clock skew correction and stop issuing the warning.

If the clock skew is not corrected and exceeds 60 seconds, the HA service on
each of the servers is terminated, i.e. the state machine enters the
``terminated`` state. The servers will continue to respond to DHCP clients (as
in the ``load-balancing`` or ``hot-standby`` mode), but will exchange neither
lease updates nor heartbeats and their lease databases will diverge. In this
case, the administrator should synchronize the clocks and restart the servers.

.. note::

   It is possible to restart the servers one at a time, in no particular order.
   The clocks must be in sync before restarting the servers.

.. note::

   The clock skew is only assessed between two active servers, and only the
   active servers enter the ``terminated`` state if the skew is too high. The
   clock skew between active and backup servers is not assessed, because active
   servers do not exchange heartbeat messages with backup servers.

.. _ha-https-support:

HTTPS Support
~~~~~~~~~~~~~

Since Kea 1.9.7, the High Availability hook library supports HTTPS via TLS, as
described in :ref:`tls`.

The HTTPS configuration parameters are:

-  ``trust-anchor`` - specifies the name of a file or directory where the
   certification authority certificate of a Control Agent can be found.

-  ``cert-file`` - specifies the name of the file containing the end-entity
   certificate to use.

-  ``key-file`` - specifies the private key of the end-entity certificate to use.

These parameters can be configured at the global and peer levels. When
configured at both levels the peer value is used, allowing common values to be
shared.

The three parameters must be either all not specified (HTTPS disabled) or all
specified (HTTPS enabled). Specification of the empty string is considered not
specified; this can be used, for instance, to disable HTTPS for a particular
peer when it is enabled at the global level.

As the High Availability hook library is an HTTPS client, there is no
``cert-required`` parameter in this hook configuration.
This parameter can be set in the Control Agent to require and verify a client
certificate in client-server communication. It does not affect communication
between HA peers at the client side; see below for information on the server
side.

Before Kea 2.1.7 using HTTPS in the HA setup required use of the Control Agent
on all peers. (See :ref:`tls` for Control Agent TLS configuration).

Since Kea 2.1.7 the HTTPS server side is supported:

-  the peer entry for the server name is used for the TLS setting.

-  the new ``require-client-certs`` parameter specifies whether client
   certificates are required and verified, i.e. like ``cert-required``. It
   defaults to ``true`` and is an HA config (vs. peer config) parameter.

Kea 2.1.7 added a new security feature with the ``restrict-commands`` HA config
parameter: when set to ``true``, commands which are not used by the hook are
rejected. The default is ``false``.

The following is an example of an HA server pair and Control Agent configuration
for ``hot-standby`` with TLS.

Server 1:
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
                   "trust-anchor": /usr/lib/kea/CA.pem,
                   "cert-file": /usr/lib/kea/server1_cert.pem,
                   "key-file": /usr/lib/kea/server1_key.pem
                   "mode": "hot-standby",
                   "heartbeat-delay": 10000,
                   "max-response-delay": 60000,
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
                   }]
               }]
           }
       }],

       "subnet4": [{
           "subnet": "192.0.3.0/24",
           "pools": [{
               "pool": "192.0.3.100 - 192.0.3.250",
               }]
       }]
   }

Server 2:
::

   "Dhcp4": {
       "hooks-libraries": [{
           "library": "/usr/lib/kea/hooks/libdhcp_lease_cmds.so",
           "parameters": { }
       }, {
           "library": "/usr/lib/kea/hooks/libdhcp_ha.so",
           "parameters": {
               "high-availability": [{
                   "this-server-name": "server2",
                   "trust-anchor": /usr/lib/kea/CA.pem,
                   "cert-file": /usr/lib/kea/server2_cert.pem,
                   "key-file": /usr/lib/kea/server2_key.pem
                   "mode": "hot-standby",
                   "heartbeat-delay": 10000,
                   "max-response-delay": 60000,
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
                   }]
               }]
           }
       }],

       "subnet4": [{
           "subnet": "192.0.3.0/24",
           "pools": [{
               "pool": "192.0.3.100 - 192.0.3.250",
               }]
       }]
   }

Control Agent on Server 1:
::

    {
        "Control-agent": {
            "http-host": "192.168.56.33",
            "http-port": 8000,
            "control-sockets": {
                "dhcp4": {
                    "socket-type": "unix",
                    "socket-name": "/var/run/kea/control_socket"
                }
            },
            "trust-anchor": "/var/lib/kea/CA.pem",
            "cert-file": "/var/lib/kea/server1_cert.pem",
            "key-file": "/var/lib/kea/server1_key.pem",
            "cert-required": true
        }
    }

Control Agent on Server 2:
::

    {
        "Control-agent": {
            "http-host": "192.168.56.66",
            "http-port": 8000,
            "control-sockets": {
                "dhcp4": {
                    "socket-type": "unix",
                    "socket-name": "/var/run/kea/control_socket"
                }
            },
            "trust-anchor": "/var/lib/kea/CA.pem",
            "cert-file": "/var/lib/kea/server2_cert.pem",
            "key-file": "/var/lib/kea/server2_key.pem",
            "cert-required": true
        }
    }

.. _ha-server-states:

Server States
~~~~~~~~~~~~~

A DHCP server operating within an HA setup runs a state machine, and the state
of the server can be retrieved by its peers using the ``ha-heartbeat`` command
sent over the RESTful API. If the partner server does not respond to the
``ha-heartbeat`` command within the specified amount of time, the communication
is considered interrupted and the server may, depending on the configuration,
use additional measures (described later in this document) to verify that the
partner is still operating. If it finds that the partner is not operating, the
server transitions to the ``partner-down`` state to handle all the DHCP traffic
directed to the system.

In this case, the surviving server continues to send the ``ha-heartbeat``
command to detect when the partner wakes up. At that time, the partner
synchronizes the lease database. When it is again ready to operate, the
surviving server returns to normal operation, i.e. the ``load-balancing`` or
``hot-standby`` state.

The following is the list of all possible server states:

-  ``backup`` - normal operation of the backup server. In this state it receives
   lease updates from the active server(s).

-  ``communication-recovery`` - an active server running in ``load-balancing``
   mode may transition to this state when it experiences communication issues
   with a partner server over the control channel. This is an intermediate state
   between the ``load-balancing`` and ``partner-down`` states. In this state the
   server continues to respond to DHCP queries but does not send lease updates
   to the partner; lease updates are queued and are sent when normal
   communication is resumed. If communication does not resume within the time
   specified, the primary server then transitions to the ``partner-down`` state.
   The ``communication-recovery`` state was introduced to ensure reliable DHCP
   service when both active servers remain operational but the communication
   between them is interrupted for a prolonged period of time. Either server can
   be configured to never enter this state by setting the
   ``delayed-updates-limit`` to 0 (please refer to
   :ref:`ha-load-balancing-config`, later in this chapter, for details on this
   parameter). Disabling entry into the ``communication-recovery`` state causes
   the server to begin testing for the ``partner-down`` state as soon as the
   server is unable to communicate with its partner.

.. note::

   In Kea 1.9.4, with the introduction of ``delayed-updates-limit``, the default
   server's behavior in ``load-balancing`` mode changed. When a server
   experiences communication issues with its partner, it now enters the
   ``communication-recovery`` state and queues lease updates until communication
   is resumed. Prior to Kea 1.9.4, a server that could not communicate with its
   partner in ``load-balancing`` mode would immediately begin the transition to
   the ``partner-down`` state.

-  ``hot-standby`` - normal operation of the active server running in the
   ``hot-standby`` mode; both the primary and the standby server are in this
   state during their normal operation. The primary server responds to DHCP
   queries and sends lease updates to the standby server and to any backup
   servers that are present.

-  ``load-balancing`` - normal operation of the active server running in the
   ``load-balancing`` mode; both the primary and the secondary server are in
   this state during their normal operation. Both servers respond to DHCP
   queries and send lease updates to each other and to any backup servers that
   are present.

-  ``in-maintenance`` - an active server transitions to this state as a result
   of being notified by its partner that the administrator requested maintenance
   of the HA setup. The administrator requests the maintenance by sending the
   ``ha-maintenance-start`` command to the server which is supposed to take over
   the responsibility for responding to the DHCP clients while the other server
   is taken offline for maintenance. If the server is in the ``in-maintenance``
   state it can be safely shut down. The partner transitions to the
   ``partner-down`` state immediately after discovering that the server in
   maintenance has been shut down.

-  ``partner-down`` - an active server transitions to this state after detecting
   that its partner (another active server) is offline. The server does not
   transition to this state if only a backup server is unavailable. In the
   ``partner-down`` state the active server responds to all DHCP queries,
   including those queries which are normally handled by the server that is now
   unavailable.

-  ``partner-in-maintenance`` - an active server transitions to this state
   after receiving a ``ha-maintenance-start`` command from the administrator.
   The server in this state becomes responsible for responding to all DHCP
   requests. The server sends a ``ha-maintenance-notify`` command to the partner,
   which should enter the ``in-maintenance`` state. The server remaining in the
   ``partner-in-maintenance`` state keeps sending lease updates to the partner
   until it finds that the partner has stopped responding to those lease updates,
   heartbeats, or any other commands. In this case, the server in the
   ``partner-in-maintenance`` state transitions to the ``partner-down`` state
   and keeps responding to the queries, but no longer sends lease updates.

-  ``passive-backup`` - a primary server running in the ``passive-backup`` HA
   mode transitions to this state immediately after it boots up. The primary
   server in this state responds to all DHCP traffic and sends lease updates to
   the backup servers it is connected to. By default, the primary server does
   not wait for acknowledgments from the backup servers and responds to a DHCP
   query right after sending lease updates to all backup servers. If any of the
   lease updates fail, a backup server misses the lease update but the DHCP
   client is still provisioned. This default configuration can be changed by
   setting the ``wait-backup-ack`` configuration parameter to ``true``, in which
   case the primary server always waits for the acknowledgements and drops the
   DHCP query if sending any of the corresponding lease updates fails. This
   improves lease database consistency between the primary and the secondary.
   However, if a communication failure between the active server and any of the
   backups occurs, it effectively causes the failure of the DHCP service from
   the DHCP clients' perspective.

-  ``ready`` - an active server transitions to this state after synchronizing
   its lease database with an active partner. This state indicates to the
   partner (which may be in the ``partner-down`` state) that it should return to
   normal operation. If and when it does, the server in the ``ready`` state also
   starts normal operation.

-  ``syncing`` - an active server transitions to this state to fetch leases from
   the active partner and update the local lease database. When in this state,
   the server issues the ``dhcp-disable`` command to disable the DHCP service of
   the partner from which the leases are fetched. The DHCP service is disabled
   for a maximum time of 60 seconds, after which it is automatically re-enabled,
   in case the syncing partner was unable to re-enable the service. If the
   synchronization completes successfully, the synchronizing server issues the
   ``ha-sync-complete-notify`` command to notify the partner. In most states,
   the partner re-enables its DHCP service to continue responding to the DHCP
   queries. In the ``partner-down`` state, the partner first ensures that
   communication between the servers is re-established before enabling the DHCP
   service. The syncing operation is synchronous; the server waits for an answer
   from the partner and does nothing else while the lease synchronization takes
   place. A server that is configured not to synchronize the lease database with
   its partner, i.e. when the ``sync-leases`` configuration parameter is set to
   ``false``, will never transition to this state. Instead, it transitions
   directly from the ``waiting`` state to the ``ready`` state.

-  ``terminated`` - an active server transitions to this state when the High
   Availability hook library is unable to further provide reliable service and a
   manual intervention of the administrator is required to correct the problem.
   Various issues with the HA setup may cause the server to transition to this
   state. While in this state, the server continues responding to DHCP clients
   based on the HA mode selected (``load-balancing`` or ``hot-standby``), but
   lease updates are not exchanged and heartbeats are not sent. Once a server
   has entered the ``terminated`` state, it remains in this state until it is
   restarted. The administrator must correct the issue which caused this
   situation prior to restarting the server (e.g. synchronize the clocks);
   otherwise, the server will return to the ``terminated`` state once it finds
   that the issue persists.

-  ``waiting`` - each started server instance enters this state. A backup server
   transitions directly from this state to the ``backup`` state. An active
   server sends a heartbeat to its partner to check its state; if the partner
   appears to be unavailable, the server transitions to the ``partner-down``
   state. If the partner is available, the server transitions to the ``syncing``
   or ``ready`` state, depending on the setting of the ``sync-leases``
   configuration parameter. If both servers appear to be in the ``waiting``
   state (concurrent startup), the primary server transitions to the next state
   first. The secondary or standby server remains in the ``waiting`` state until
   the primary transitions to the ``ready`` state.

.. note::

   Currently, restarting the HA service from the ``terminated`` state requires
   restarting the DHCP server or reloading its configuration.

Whether the server responds to DHCP queries and which queries it responds to is
a matter of the server's state, if no administrative action is performed to
configure the server otherwise. The following table provides the default
behavior for various states.

The ``DHCP Service Scopes`` denote which group of received DHCP queries the
server responds to in the given state. The HA configuration must specify a
unique name for each server within the HA setup. This document uses the
following convention within the provided examples: "server1" for a primary
server, "server2" for the secondary or standby server, and "server3" for the
backup server. In real life any names can be used as long as they remain unique.

An in-depth explanation of the scopes can be found below.

.. table:: Default behavior of the server in various HA states

   +------------------------+-----------------+-----------------+----------------+
   | State                  | Server Type     | DHCP Service    | DHCP Service   |
   |                        |                 |                 | Scopes         |
   +========================+=================+=================+================+
   | backup                 | backup server   | disabled        | none           |
   +------------------------+-----------------+-----------------+----------------+
   | communication-recovery | primary or      | enabled         | "HA_server1"   |
   |                        | secondary       |                 | or             |
   |                        | (load-balancing |                 | "HA_server2"   |
   |                        | mode only)      |                 |                |
   +------------------------+-----------------+-----------------+----------------+
   | hot-standby            | primary or      | enabled         | "HA_server1"   |
   |                        | standby         |                 | if primary,    |
   |                        | (hot-standby    |                 | none otherwise |
   |                        | mode)           |                 |                |
   +------------------------+-----------------+-----------------+----------------+
   | load-balancing         | primary or      | enabled         | "HA_server1"   |
   |                        | secondary       |                 | or             |
   |                        | (load-balancing |                 | "HA_server2"   |
   |                        | mode)           |                 |                |
   +------------------------+-----------------+-----------------+----------------+
   | in-maintenance         | active server   | disabled        | none           |
   +------------------------+-----------------+-----------------+----------------+
   | partner-down           | active server   | enabled         | all scopes     |
   +------------------------+-----------------+-----------------+----------------+
   | partner-in-maintenance | active server   | enabled         | all scopes     |
   +------------------------+-----------------+-----------------+----------------+
   | passive-backup         | active server   | enabled         | all scopes     |
   +------------------------+-----------------+-----------------+----------------+
   | ready                  | active server   | disabled        | none           |
   +------------------------+-----------------+-----------------+----------------+
   | syncing                | active server   | disabled        | none           |
   +------------------------+-----------------+-----------------+----------------+
   | terminated             | active server   | enabled         | same as in the |
   |                        |                 |                 | load-balancing |
   |                        |                 |                 | or hot-standby |
   |                        |                 |                 | state          |
   +------------------------+-----------------+-----------------+----------------+
   | waiting                | any server      | disabled        | none           |
   +------------------------+-----------------+-----------------+----------------+

In the ``load-balancing`` mode there are two scopes specified for the active
servers: "HA_server1" and "HA_server2". The DHCP queries load-balanced to
``server1`` belong to the "HA_server1" scope and the queries load-balanced to
``server2`` belong to the "HA_server2" scope. If either server is in the
``partner-down`` state, the active partner is responsible for serving both
scopes.

In the ``hot-standby`` mode, there is only one scope - "HA_server1" - because
only ``server1`` is responding to DHCP queries. If that server becomes
unavailable, ``server2`` becomes responsible for this scope.

The backup servers do not have their own scopes. In some cases they can be used
to respond to queries belonging to the scopes of the active servers. Also, a
backup server which is neither in the ``partner-down`` state nor in normal
operation serves no scopes.

The scope names can be used to associate pools, subnets, and networks with
certain servers, so that only these servers can allocate addresses or prefixes
from those pools, subnets, or networks. This is done via the client
classification mechanism (see :ref:`ha-load-balancing-advanced-config` for more
details).

.. _ha-scope-transition:

Scope Transition in a Partner-Down Case
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When one of the servers finds that its partner is unavailable, it starts serving
clients from both its own scope and the scope of the unavailable partner. This
is straightforward for new clients, i.e. those sending DHCPDISCOVER (DHCPv4) or
Solicit (DHCPv6), because those requests are not sent to any particular server.
The available server responds to all such queries when it is in the
``partner-down`` state.

When a client renews a lease, it sends its DHCPREQUEST (DHCPv4) or Renew (DHCPv6)
message directly to the server which has allocated the lease being renewed. If
this server is no longer available, the client will get no response. In that
case, the client continues to use its lease and attempts to renew until the
rebind timer (T2) elapses. The client then enters the rebinding phase, in which
it sends a DHCPREQUEST (DHCPv4) or Rebind (DHCPv6) message to any available
server. The surviving server receives the rebinding request and typically
extends the lifetime of the lease. The client then continues to contact that new
server to renew its lease as appropriate.

If and when the other server once again becomes available, both active servers
will eventually transition to the ``load-balancing`` or ``hot-standby`` state,
in which they will again be responsible for their own scopes. Some clients
belonging to the scope of the restarted server will try to renew their leases
via the surviving server, but this server will no longer respond to them; the
client will eventually transition back to the correct server via the rebinding
mechanism.

.. _ha-load-balancing-config:

Load-Balancing Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following is the configuration snippet to enable high availability on the
primary server within the ``load-balancing`` configuration. The same
configuration should be applied on the secondary and backup servers, with the
only difference that ``this-server-name`` should be set to "server2" and
"server3" on those servers, respectively.

.. note::

   Remember that ``load-balancing`` mode requires the address pools and
   delegated prefix pools to be split between the active servers. During normal
   operation, the servers use non-overlapping pools to avoid allocating the same
   lease to different clients by both instances. A server only uses the pool
   fragments owned by the partner when the partner is not running. See the notes
   in :ref:`ha-supported-configurations` highlighting differences between the
   ``load-balancing`` and ``hot-standby`` modes. The semantics of pool
   partitioning is explained further in this section.
   The :ref:`ha-load-balancing-advanced-config` section provides advanced
   pool-partitioning examples.

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
                   "max-response-delay": 60000,
                   "max-ack-delay": 5000,
                   "max-unacked-clients": 5,
                   "delayed-updates-limit": 100,
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
                       "basic-auth-user": "foo",
                       "basic-auth-password": "bar",
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

Two hook libraries must be loaded to enable HA: ``libdhcp_lease_cmds.so`` and
``libdhcp_ha.so``. The latter implements the HA feature, while the former
enables control commands required by HA to fetch and manipulate leases on the
remote servers. In the example provided above, it is assumed that Kea libraries
are installed in the ``/usr/lib`` directory. If Kea is not installed in the
``/usr`` directory, the hook libraries' locations must be updated accordingly.

The HA configuration is specified within the scope of ``libdhcp_ha.so``.
Note that while the top-level parameter ``high-availability`` is a list, only a
single entry is currently supported.

The following are the global parameters which control the server's behavior with
respect to HA:

-  ``this-server-name`` - is a unique identifier of the server within this HA
   setup. It must match one of the servers specified within the ``peers`` list.

-  ``mode`` - specifies an HA mode of operation. The currently supported modes
   are ``load-balancing`` and ``hot-standby``.

-  ``heartbeat-delay`` - specifies a duration in milliseconds between sending
   the last heartbeat (or other command sent to the partner) and the next
   heartbeat. Heartbeats are sent periodically to gather the status of the
   partner and to verify whether the partner is still operating. The default
   value of this parameter is 10000 ms.

-  ``max-response-delay`` - specifies a duration in milliseconds since the last
   successful communication with the partner, after which the server assumes
   that communication with the partner is interrupted. This duration should be
   greater than the ``heartbeat-delay``; typically it should be a multiple of
   ``heartbeat-delay``. When the server detects that communication is
   interrupted, it may transition to the ``partner-down`` state (when
   ``max-unacked-clients`` is 0) or trigger the failure-detection procedure
   using the values of the two parameters below. The default value of this
   parameter is 60000 ms.

-  ``max-ack-delay`` - is one of the parameters controlling partner
   failure-detection. When communication with the partner is interrupted, the
   server examines the values of the "secs" field (DHCPv4) or "elapsed time"
   option (DHCPv6), which denote how long the DHCP client has been trying to
   communicate with the DHCP server. This parameter specifies the maximum time
   in milliseconds for the client to try to communicate with the DHCP server,
   after which this server assumes that the client failed to communicate with
   the DHCP server (is unacknowledged or "unacked"). The default value of this
   parameter is 10000.

-  ``max-unacked-clients`` - specifies how many "unacked" clients are allowed
   (see ``max-ack-delay``) before this server assumes that the partner is
   offline and transitions to the ``partner-down`` state. The special value of 0
   is allowed for this parameter, which disables the failure-detection mechanism.
   In this case, a server that cannot communicate with its partner over the
   control channel assumes that the partner server is down and transitions to
   the ``partner-down`` state immediately. The default value of this parameter
   is 10.

-  ``delayed-updates-limit`` - specifies the maximum number of lease updates
   which can be queued while the server is in the ``communication-recovery``
   state. This parameter was introduced in Kea 1.9.4. The special value of 0
   configures the server to never transition to the ``communication-recovery``
   state and the server behaves as in earlier Kea versions, i.e. if the server
   cannot reach its partner, it goes straight into the ``partner-down`` state.
   The default value of this parameter is 100.

The values of ``max-ack-delay`` and ``max-unacked-clients`` must be selected
carefully, taking into account the specifics of the network in which the DHCP
servers are operating. The server in question may not respond to some DHCP
clients following administrative policy, or the server may drop malformed
queries from clients. Therefore, selecting too low a value for the
``max-unacked-clients`` parameter may result in a transition to the
``partner-down`` state even though the partner is still operating. On the other
hand, selecting too high a value may result in never transitioning to the
``partner-down`` state if the DHCP traffic in the network is very low (e.g. at
night), because the number of distinct clients trying to communicate with the
server could be lower than the ``max-unacked-clients`` setting.

In some cases it may be useful to disable the failure-detection mechanism
altogether, if the servers are located very close to each other and network
partitioning is unlikely, i.e. failure to respond to heartbeats is only possible
when the partner is offline. In such cases, set ``max-unacked-clients`` to 0.

The ``delayed-updates-limit`` parameter is used to enable or disable the
``communication-recovery`` procedure, and controls the server's behavior in the
``communication-recovery`` state. This parameter can only be used in the
``load-balancing`` mode.

If a server in the ``load-balancing`` state experiences communication issues
with its partner (a heartbeat or lease-update failure), the server transitions
to the ``communication-recovery`` state. In this state, the server keeps
responding to DHCP queries but does not send lease updates to the partner. The
lease updates are queued until communication is re-established, to ensure that
DHCP service remains available even in the event of the communication loss
between the partners. There may appear to be communication loss when either one
of the servers has terminated, or when both servers remain available but cannot
communicate with each other. In the former case, the surviving server will
follow the normal procedure and should eventually transition to the
``partner-down`` state. In the latter case, both servers should transition to
the ``communication-recovery`` state and should never transition to the
``partner-down`` state (if ``max-unacked-clients`` is set to a non-zero value),
because all DHCP queries are answered and neither server would see any unacked
DHCP queries.

Introduction of the ``communication-recovery`` procedure was motivated by issues
which may appear when two servers remain online but the communication between
them remains interrupted for a period of time. In earlier Kea versions, the
servers having communication issues used to drop DHCP packets before
transitioning to the ``partner-down`` state. In some cases they both
transitioned to the ``partner-down`` state, which could potentially result in
allocations of the same IP addresses or delegated prefixes to different clients
by both servers. By entering the intermediate ``communication-recovery`` state,
these problems are avoided.

If a server in the ``communication-recovery`` state re-establishes communication
with its partner, it tries to send the partner all of the outstanding lease
updates it has queued. This is done synchronously and may take a considerable
amount of time before the server transitions to the ``load-balancing`` state and
resumes normal operation.
The maximum number of lease updates which can be queued in the
``communication-recovery`` state is controlled by ``delayed-updates-limit``.
If the limit is exceeded, the server stops queuing lease updates and performs a
full database synchronization after re-establishing the connection with the
partner, instead of sending outstanding lease updates before transitioning to
the ``load-balancing`` state. Even if the limit is exceeded, the server in the
``communication-recovery`` state remains responsive to DHCP clients.

It may be preferable to set higher values of ``delayed-updates-limit`` when
there is a risk of prolonged communication interruption between the servers and
when the lease database is large, to avoid costly lease-database synchronization.
On the other hand, if the lease database is small, the time required to send
outstanding lease updates may be longer than the lease-database synchronization.
In such cases it may be better to use a lower value, e.g. 10. The default value
of 100 is a reasonable compromise and should work well in most deployments with
moderate traffic.

.. note::

   This parameter is new and values for it that work well in some environments
   may not work well in others. Feedback from users will help us build a better
   working set of recommendations.

The ``peers`` parameter contains a list of servers within this HA setup.
This configuration must contain at least one primary and one secondary server.
It may also contain an unlimited number of backup servers. In this example,
there is one backup server which receives lease updates from the active servers.

Since Kea version 1.9.0, basic HTTP authentication is available
to protect the Kea control agent against local attackers.

These are the parameters specified for each of the peers within this
list:

-  ``name`` - specifies a unique name for the server.

-  ``url`` - specifies the URL to be used to contact this server over the
   control channel. Other servers use this URL to send control commands to that
   server.

-  ``basic-auth-user`` - specifies the user ID for basic HTTP authentication. If
   not specified or specified as an empty string, no authentication header is
   added to HTTP transactions. It must not contain the colon (:) character.

-  ``basic-auth-password`` - specifies the password for basic HTTP
   authentication. This parameter is ignored when the user ID is not specified
   or is empty. The password is optional; if not specified, an empty password is
   used.

-  ``basic-auth-password-file`` - is an alternative to ``basic-auth-password``:
   instead of presenting the password in the configuration file it is specified
   in the file indicated by this parameter.

-  ``role`` - denotes the role of the server in the HA setup. The following
   roles are supported in the ``load-balancing`` configuration: ``primary``,
   ``secondary``, and ``backup``. There must be exactly one primary and one
   secondary server in the ``load-balancing`` setup.

-  ``auto-failover`` - a boolean value which denotes whether a server detecting
   a partner's failure should automatically start serving the partner's clients.
   The default value of this parameter is ``true``.

In our example configuration above, both active servers can allocate leases from
the subnet "192.0.3.0/24". This subnet contains two address pools:
"192.0.3.100 - 192.0.3.150" and "192.0.3.200 - 192.0.3.250", which are
associated with HA server scopes using client classification. When ``server1``
processes a DHCP query, it uses the first pool for lease allocation. Conversely,
when ``server2`` processes a DHCP query it uses the second pool. If either of
the servers is in the ``partner-down`` state, the other can serve leases from
both pools; it selects the pool which is appropriate for the received query. In
other words, if the query would normally be processed by ``server2`` but this
server is not available, ``server1`` allocates the lease from the pool of
"192.0.3.200 - 192.0.3.250". The Kea control agent in front of ``server3``
requires basic HTTP authentication, and authorizes the user ID "foo" with the
password "bar".

.. note::

   The ``url`` schema can be ``http`` or ``https``, but since Kea version 1.9.6
   the ``https`` schema requires a TLS setup. The hostname part must be an IPv4
   address or an IPv6 address between square brackets, e.g.
   ``http://[2001:db8::1]:8080/``. Names are not accepted.

.. _ha-load-balancing-advanced-config:

Load Balancing With Advanced Classification
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the previous section, we provided an example of a ``load-balancing``
configuration with client classification limited to the "HA_server1" and
"HA_server2" classes, which are dynamically assigned to the received DHCP
queries. In many cases, HA is needed in deployments which already use some other
client classification.

Suppose there is a system which classifies devices into two groups: "phones" and
"laptops", based on some classification criteria specified in the Kea
configuration file. Both types of devices are allocated leases from different
address pools. Introducing HA in ``load-balancing`` mode results in a further
split of each of those pools, as each server allocates leases for some phones
and some laptops. This requires each of the existing pools to be split between
"HA_server1" and "HA_server2", so we end up with the following classes:

-  "phones_server1"
-  "laptops_server1"
-  "phones_server2"
-  "laptops_server2"

The corresponding server configuration, using advanced classification (and the
``member`` expression), is provided below. For brevity's sake, the HA hook
library configuration has been removed from this example.

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

The configuration provided above splits the address range into four pools: two
pools dedicated to "HA_server1" and two to "HA_server2". Each server can assign
leases to both phones and laptops. Both groups of devices are assigned addresses
from different pools. The "HA_server1" and "HA_server2" classes are built-in
(see :ref:`classification-using-vendor`) and do not need to be declared.
They are assigned dynamically by the HA hook library as a result of the
``load-balancing`` algorithm. "phones_*" and "laptop_*" evaluate to ``true``
when the query belongs to a given combination of other classes, e.g. "HA_server1"
and "phones". The pool is selected accordingly as a result of such an evaluation.

Consult :ref:`classify` for details on how to use the ``member`` expression and
class dependencies.

.. _ha-hot-standby-config:

Hot-Standby Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~

The following is an example configuration of the primary server in a
``hot-standby`` configuration:

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
                   "max-response-delay": 60000,
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
                       "basic-auth-user": "foo",
                       "basic-auth-password": "bar",
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

This configuration is very similar to the ``load-balancing`` configuration
described in :ref:`ha-load-balancing-config`, with a few notable differences.

The ``mode`` is now set to ``hot-standby``, in which only one server responds to
DHCP clients. If the primary server is online, it responds to all DHCP queries.
The ``standby`` server takes over all DHCP traffic only if it discovers that the
primary is unavailable.

In this mode, the non-primary active server is called ``standby`` and that is
its role.

Finally, because there is always only one server responding to DHCP queries,
there is only one scope - "HA_server1" - in use within pool definitions. In fact,
the ``client-class`` parameter could be removed from this configuration without
harm, because there can be no conflicts in lease allocations by different
servers as they do not allocate leases concurrently. The ``client-class``
remains in this example mostly for demonstration purposes, to highlight the
differences between the ``hot-standby`` and ``load-balancing`` modes of
operation.

.. _ha-passive-backup-config:

Passive-Backup Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following is an example configuration file for the primary server in a
``passive-backup`` configuration:

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
                   "mode": "passive-backup",
                   "wait-backup-ack": false,
                   "peers": [{
                       "name": "server1",
                       "url": "http://192.168.56.33:8000/",
                       "role": "primary"
                   }, {
                       "name": "server2",
                       "url": "http://192.168.56.66:8000/",
                       "role": "backup"
                   }, {
                       "name": "server3",
                       "url": "http://192.168.56.99:8000/",
                       "basic-auth-user": "foo",
                       "basic-auth-password": "bar",
                       "role": "backup"
                   }]
               }]
           }
       }],

       "subnet4": [{
           "subnet": "192.0.3.0/24",
           "pools": [{
               "pool": "192.0.3.100 - 192.0.3.250",
           }],

           "option-data": [{
               "name": "routers",
               "data": "192.0.3.1"
           }],

           "relay": { "ip-address": "10.1.2.3" }
       }]
   }

The configurations of three peers are included: one for the primary and two for
the backup servers.

Many of the parameters present in the ``load-balancing`` and ``hot-standby``
configuration examples are not relevant in the ``passive-backup`` mode, thus
they are not specified here. For example: ``heartbeat-delay``,
``max-unacked-clients``, and others related to the automatic failover mechanism
should not be specified in the ``passive-backup`` mode.

The ``wait-backup-ack`` is a boolean parameter not present in previous examples.
It defaults to ``false`` and must not be modified in the ``load-balancing`` and
``hot-standby`` modes. In the ``passive-backup`` mode this parameter can be set
to ``true``, which causes the primary server to expect acknowledgments to the
lease updates from the backup servers prior to responding to the DHCP client. It
ensures that the lease has propagated to all servers before the client is given
the lease, but it poses a risk of losing a DHCP service if there is a
communication problem with one of the backup servers. This setting also
increases the latency of the DHCP response, because of the time that the primary
spends waiting for the acknowledgements. We recommend that the
``wait-backup-ack`` setting be left at its default value (``false``) if the DHCP
service reliability is more important than consistency of the lease information
between the primary and the backups, and in all cases when the DHCP service
latency should be minimal.

.. note::

   Currently, active servers place lease updates to be sent to peers onto
   internal queues (one queue per peer/URL). In ``passive-backup`` mode, active
   servers do not wait for lease updates to be acknowledged; thus during times
   of heavy client traffic it is possible for the number of lease updates queued
   for transmission to accumulate faster than they can be delivered. As client
   traffic lessens the queues begin to empty. Since Kea 2.0.0, active servers
   monitor the size of these queues and emit periodic warnings (see
   HTTP_CLIENT_QUEUE_SIZE_GROWING in :ref:`kea-messages`) if they perceive a
   queue as growing too quickly. The warnings cease once the queue size begins
   to shrink. These messages are intended as a bellwether and seeing them
   sporadically during times of heavy traffic load does not necessarily indicate
   a problem. If, however, they occur continually during times of routine
   traffic load, they likely indicate potential mismatches in server
   capabilities and/or configuration; this should be investigated, as the size
   of the queues may eventually impair an active server's ability to respond to
   clients in a timely manner.

.. _ha-sharing-lease-info:

Lease Information Sharing
~~~~~~~~~~~~~~~~~~~~~~~~~

An HA-enabled server informs its active partner about allocated or renewed
leases by sending appropriate control commands, and the partner updates the
lease information in its own database. When the server starts up for the first
time or recovers after a failure, it synchronizes its lease database with its
partner. These two mechanisms guarantee consistency of the lease information
between the servers and allow the designation of one of the servers to handle
the entire DHCP traffic load if the other server becomes unavailable.

In some cases, though, it is desirable to disable lease updates and/or database
synchronization between the active servers, if the exchange of information about
the allocated leases is performed using some other mechanism. Kea supports
various database types that can be used to store leases, including MySQL and
PostgreSQL. Those databases include built-in solutions for data replication
which are often used by Kea administrators to provide redundancy.

The HA hook library supports such scenarios by disabling lease updates over the
control channel and/or lease-database synchronization, leaving the server to
rely on the database replication mechanism. This is controlled by the two
boolean parameters ``send-lease-updates`` and ``sync-leases``, whose values
default to ``true``:

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

In the most typical use case, both parameters are set to the same value, i.e.
both are ``false`` if database replication is in use, or both are ``true``
otherwise. Introducing two separate parameters to control lease updates and
lease-database synchronization is aimed at possible special use cases; for
example, when synchronization is performed by copying a lease file (therefore
``sync-leases`` is set to ``false``), but lease updates should be conducted as
usual (``send-lease-updates`` is set to ``true``). It should be noted that Kea
does not natively support such use cases, but users may develop their own
scripts and tools around Kea to provide such mechanisms. The HA hook library
configuration is designed to maximize flexibility of administration.

.. _ha-syncing-page-limit:

Controlling Lease-Page Size Limit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

An HA-enabled server initiates synchronization of the lease database after
downtime or upon receiving the ``ha-sync`` command. The server uses commands
described in :ref:`command-lease4-get-page` and :ref:`command-lease6-get-page`
to fetch leases from its partner server (lease queries). The size of the results
page (the maximum number of leases to be returned in a single response to one of
these commands) can be controlled via configuration of the HA hook library.
Increasing the page size decreases the number of lease queries sent to the
partner server, but it causes the partner server to generate larger responses,
which lengthens transmission time as well as increases memory and CPU
utilization on both servers. Decreasing the page size helps to decrease resource
utilization, but requires more lease queries to be issued to fetch the entire
lease database.

The default value of the ``sync-page-limit`` command controlling the page size
is 10000. This means that the entire lease database can be fetched with a single
command if the size of the database is equal to or less than 10000 lines.

.. _ha-syncing-timeouts:

Timeouts
~~~~~~~~

In deployments with a large number of clients connected to the network,
lease-database synchronization after a server failure may be a time-consuming
operation. The synchronizing server must gather all leases from its partner,
which yields a large response over the RESTful interface. The server receives
leases using the paging mechanism described in :ref:`ha-syncing-page-limit`.
Before the page of leases is fetched, the synchronizing server sends a
``dhcp-disable`` command to disable the DHCP service on the partner server. If
the service is already disabled, this command resets the timeout for the DHCP
service being disabled, which by default is set to 60 seconds. If fetching a
single page of leases takes longer than the specified time, the partner server
assumes that the synchronizing server has died and resumes its DHCP service. The
connection of the synchronizing server with its partner is also protected by the
timeout. If the synchronization of a single page of leases takes longer than the
specified time, the synchronizing server terminates the connection and the
synchronization fails. Both timeout values are controlled by a single
configuration parameter, ``sync-timeout``. The following configuration snippet
demonstrates how to modify the timeout for automatic re-enabling of the DHCP
service on the partner server and how to increase the timeout for fetching a
single page of leases from 60 seconds to 90 seconds:

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

It is important to note that extending this ``sync-timeout`` value may sometimes
be insufficient to prevent issues with timeouts during lease-database
synchronization. The control commands travel via the Control Agent, which also
monitors incoming (with a synchronizing server) and outgoing (with a DHCP server)
connections for timeouts. The DHCP server also monitors the connection from the
Control Agent for timeouts. Those timeouts cannot currently be modified via
configuration; extending these timeouts is only possible by modifying them in
the Kea code and recompiling the server. The relevant constants are located in
the Kea source at: ``src/lib/config/timeouts.h``.

.. _ha-pause-state-machine:

Pausing the HA State Machine
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``high-availability`` state machine includes many different states described
in detail in :ref:`ha-server-states`. The server enters each state when certain
conditions are met, most often taking into account the partner server's state.
In some states the server performs specific actions, e.g. synchronization of the
lease database in the ``syncing`` state, or responding to DHCP queries according
to the configured mode of operation in the ``load-balancing`` and ``hot-standby``
states.

By default, transitions between the states are performed automatically and the
server administrator has no direct control over when the transitions take place;
in most cases, the administrator does not need such control. In some situations,
however, the administrator may want to "pause" the HA state machine in a
selected state to perform some additional administrative actions before the
server transitions to the next state.

Consider a server failure which results in the loss of the entire lease database.
Typically, the server rebuilds its lease database when it enters the ``syncing``
state by querying the partner server for leases, but it is possible that the
partner was also experiencing a failure and lacks lease information. In this
case, it may be required to reconstruct lease databases on both servers from
some external source, e.g. a backup server. If the lease database is to be
reconstructed via the RESTful API, the servers should be started in the initial,
i.e. ``waiting``, state and remain in this state while leases are being added.
In particular, the servers should not attempt to synchronize their lease
databases nor start serving DHCP clients.

The HA hook library provides configuration parameters and a command to control
pausing and resuming the HA state machine. The following configuration causes
the HA state machine to pause in the ``waiting`` state after server startup.

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

The ``pause`` parameter value ``once`` denotes that the state machine should be
paused upon the first transition to the ``waiting`` state; later transitions to
this state will not cause the state machine to pause. Two other supported values
of the ``pause`` parameter are ``always`` and ``never``. The latter is the
default value for each state, which instructs the server never to pause the
state machine.

In order to "unpause" the state machine, the ``ha-continue`` command must be
sent to the paused server. This command does not take any arguments. See
:ref:`ha-control-commands` for details about commands specific to the HA hook
library.

It is possible to configure the state machine to pause in more than one state.
Consider the following configuration:

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

This configuration instructs the server to pause the state machine every time it
transitions to the ``ready`` state and upon the first transition to the
``partner-down`` state.

Refer to :ref:`ha-server-states` for a complete list of server states. The state
machine can be paused in any of the supported states; however, it is not
practical to pause in the ``backup`` or ``terminated`` states because the server
never transitions out of these states anyway.

.. note::

   In the ``syncing`` state the server is paused before it makes an attempt to
   synchronize the lease database with a partner. To pause the state machine
   after lease-database synchronization, use the ``ready`` state instead.

.. note::

   The state of the HA state machine depends on the state of the cooperating
   server. Therefore, pausing the state machine of one server may affect the
   operation of the partner server. For example: if the primary server is paused
   in the ``waiting`` state, the partner server will also remain in the
   ``waiting`` state until the state machine of the primary server is resumed
   and that server transitions to the ``ready`` state.

.. _ha-ctrl-agent-config:

Control Agent Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :ref:`kea-ctrl-agent` describes in detail the Kea daemon, which provides a
RESTful interface to control the Kea servers. The same functionality is used by
the High Availability hook library to establish communication between the HA
peers. Therefore, the HA library requires that the Control Agent (CA) be started
for each DHCP instance within the HA setup. If the Control Agent is not started,
the peers cannot communicate with a particular DHCP server (even if the DHCP
server itself is online) and may eventually consider this server to be offline.

The following is an example configuration for the CA running on the same
machine as the primary server. This configuration is valid for both the
``load-balancing`` and the ``hot-standby`` cases presented in previous sections.

::

   {
   "Control-agent": {
       "http-host": "192.168.56.33",

        // If enabling HA and multi-threading, the 8000 port is used by the HA
        // hook library http listener. When using HA hook library with
        // multi-threading to function, make sure the port used by dedicated
        // listener is different (e.g. 8001) than the one used by CA. Note
        // the commands should still be sent via CA. The dedicated listener
        // is specifically for HA updates only.
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

Since Kea 1.9.0, basic HTTP authentication is supported.

.. _ha-mt-config:

Multi-Threaded Configuration (HA+MT)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

HA peer communication consists of specialized API commands sent between HA peers.
Prior to Kea 1.9.7, each peer had to be paired with a local instance of
``kea-ctrl-agent`` in order to exchange commands. The agent received HA commands
via HTTP, communicated via Linux socket with the local peer to carry out the
command, and then sent the response back to the requesting peer via HTTP. To
send HA commands, each peer opened its own HTTP client connection to the URL of
each of its peers.

In Kea 1.9.7 and newer, it is possible to configure HA to use direct
multi-threaded communication between peers. We refer to this mode as HA+MT.
With HA+MT enabled, each peer runs its own dedicated, internal HTTP listener
(i.e. server) which receives and responds to commands directly, thus eliminating
the need for an agent to carry out HA protocol between peers. In addition, both
the listener and client components use multi-threading to support multiple,
concurrent connections between peers. By eliminating the agent and executing
multiple command exchanges in parallel, HA throughput between peers should
improve considerably in most situations.

The following parameters have been added to the HA configuration, to support
HA+MT operation:

-  ``enable-multi-threading`` - enables or disables multi-threading HA peer
   communication (HA+MT). Kea core multi-threading must be enabled for HA+MT to
   operate. When ``false`` (the default), the server operates as in earlier
   versions, relying on ``kea-ctrl-agent`` and using single-threaded HTTP client
   processing.

-  ``http-dedicated-listener`` - enables or disables the creation of a dedicated,
   internal HTTP listener through which the server receives HA messages from its
   peers. The internal listener replaces the role of ``kea-ctrl-agent`` traffic,
   allowing peers to send their HA commands directly to each other. The listener
   listens on the peer's ``url``. When ``false`` (the default), the server
   relies on ``kea-ctrl-agent``. This parameter has been provided largely for
   flexibility and testing; running HA+MT without dedicated listeners enabled
   will substantially limit HA throughput.

-  ``http-listener-threads`` - indicates the maximum number of threads the
   dedicated listener should use. A value of 0 instructs the server to use the
   same number of threads that the Kea core is using for DHCP multi-threading.
   The default is 0.

-  ``http-client-threads`` - indicates the maximum number of threads that should
   be used to send HA messages to its peers. A value of 0 instructs the server
   to use the same number of threads that the Kea core is using for DHCP
   multi-threading. The default is 0.

These parameters are grouped together under a map element, ``multi-threading``,
as illustrated below:

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
                       ...
                       "multi-threading": {
                           "enable-multi-threading": true,
                           "http-dedicated-listener": true,
                           "http-listener-threads": 4,
                           "http-client-threads": 4
                       },
                       ...
                       "peers": [
                         // This is the configuration of this server instance.
                         {
                             "name": "server1",
                             // This specifies the URL of our server instance.
                             // Since the HA+MT uses a direct connection, the
                             // DHCPv4 server open its own socket. Note that it
                             // must be different than the one used by the CA
                             // (typically 8000). In this example, 8001 is used.
                             "url": "http://192.0.2.1:8001/",
                             // This server is primary. The other one must be
                             // secondary.
                             "role": "primary"
                         },
                         // This is the configuration of our HA peer.
                         {
                             "name": "server2",
                             // This specifies the URL of our server instance.
                             // Since the HA+MT uses a direct connection, the
                             // DHCPv4 server open its own socket. Note that it
                             // must be different than the one used by the CA
                             // (typically 8000). In this example, 8001 is used.
                             "url": "http://192.0.2.2:8001/",
                             // The partner is a secondary. This server is a
                             // primary as specified in the previous "peers"
                             // entry and in "this-server-name" before that.
                             "role": "secondary"
                         }
                       ...


In the example above, HA+MT is enabled with four threads for the listener and
four threads for the client.

.. note::

   It is essential to configure the ports correctly. One common mistake is to
   configure CA to listen on port 8000 and also configure dedicated listeners on
   port 8000. In such a configuration, the communication will still work over CA,
   but it will be slow and the DHCP server will fail to bind sockets.
   Administrators should ensure that dedicated listeners use a different port
   (8001 is a suggested alternative); if ports are misconfigured or the ports
   dedicated to CA are used, the performance bottlenecks caused by the
   single-threaded nature of CA and the sequential nature of the UNIX socket
   that connects CA to DHCP servers will nullify any performance gains offered
   by HA+MT.

.. _ha-parked-packet-limit:

Parked-Packet Limit
~~~~~~~~~~~~~~~~~~~

Kea servers contain a mechanism by which the response to a client packet may
be held, pending completion of hook library work. We refer to this as "parking"
the packet. The HA hook library makes use of this mechanism. When an HA server
needs to send a lease update to its peer(s) to notify it of the change to the
lease, it will "park" the client response until the peer acknowledges the lease
update. At that point, the server will "unpark" the response and send it to the
client. This applies to client queries which cause lease changes, such as
DHCPREQUEST for DHCPv4 and Request, Renew, and Rebind for DHCPv6. It does not
apply to DHPCDISCOVERs (v4) or Solicits (v6).

There is a global parameter, ``parked-packet-limit``, that may be used to limit
the number of responses that may be parked at any given time. This acts as a
form of congestion handling and protects the server from being swamped when the
volume of client queries is outpacing the server's ability to respond. Once the
limit is reached, the server emits a log and drops any new responses until
parking spaces are available.

In general, smaller values for the parking lot limit are likely to cause more
drops but with shorter response times. Larger values are likely to result in
fewer drops but with longer response times. Currently, the default value for
``parked-packet-limit`` is 256.

.. warning::

   Using too small a value may result in an unnecessarily high drop rate, while
   using too large a value may lead to response times that are simply too long
   to be useful. A value of 0, while allowed, disables the limit altogether, but
   this is highly discouraged as it may lead to Kea servers becoming
   unresponsive to clients. Choosing the best value is very site-specific; we
   recommend users initially leave it at the default value of 256 and observe
   how the system behaves over time with varying load conditions.

::

   "Dhcp6": {

       ...
       // Limit the number of concurrently parked packets to 128.
       "parked-packet-limit": 128,
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
                       ...

.. note::

   While ``parked-packet-limit`` is not specifically tied to HA, currently HA
   is the only ISC hook that employs packet parking.

.. _ha-maintenance:

Controlled Shutdown and Maintenance of DHCP Servers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Having a pair of servers providing High Availability allows for controlled
shutdown and maintenance of those servers without disrupting the DHCP service.
For example, an administrator can perform an upgrade of one of the servers while
the other one continues to respond to DHCP queries. When the first server is
upgraded and back online, the upgrade can be performed for the second server.

A typical problem reported with early versions of the High Availability hook
library was that the administrator did not have direct control over the state of
the DHCP server. Shutting down one of the servers for maintenance did not
necessarily cause the other server to start responding to all DHCP queries,
because the failure-detection algorithm described in :ref:`ha-scope-transition`
requires that the partner not respond for a configured period of time and,
depending on the configuration, may also require that a number of DHCP requests
not be responded to for a specified period of time. The maintenance procedure,
however, requires that the administrator be able to instruct one of the servers
to instantly start serving all DHCP clients, and the other server to instantly
stop serving any DHCP clients, so it can be safely shut down.

The maintenance feature of the High Availability hook library addresses this
situation. The ``ha-maintenance-start`` command was introduced to allow the
administrator to put the pair of the active servers in a state in which one of
them is responding to all DHCP queries and the other one is awaiting shutdown.

Suppose that the HA setup includes two active servers, ``server1`` and
``server2``, and the latter needs to be shut down for maintenance.
The administrator can send the ``ha-maintenance-start`` command to ``server1``,
as this is the server which is going to handle the DHCP traffic while the other
one is offline. ``server1`` responds with an error if its state or the partner's
state does not allow for a maintenance shutdown: for example, if maintenance is
not supported for the backup server or if the server is in the ``terminated``
state. Also, an error is returned if the ``ha-maintenance-start`` request was
already sent to the other server.

Upon receiving the ``ha-maintenance-start`` command, ``server1`` sends the
``ha-maintenance-notify`` command to ``server2`` to put it in the
``in-maintenance`` state. If ``server2`` confirms, ``server1`` transitions to
the ``partner-in-maintenance`` state. This is similar to the ``partner-down``
state, except that in the ``partner-in-maintenance`` state ``server1`` continues
to send lease updates to ``server2`` until the administrator shuts down
``server2``. ``server1`` now responds to all DHCP queries.

The administrator can now safely shut down ``server2`` in the ``in-maintenance``
state and perform any necessary maintenance actions. While ``server2`` is
offline, ``server1`` will obviously not be able to communicate with its partner,
so it will immediately transition to the ``partner-down`` state; it will
continue to respond to all DHCP queries but will no longer send lease updates to
``server2``. Restarting ``server2`` after the maintenance will trigger normal
state negotiation, lease-database synchronization, and, ultimately, a transition
to the normal ``load-balancing`` or ``hot-standby`` state. Maintenance can then
be performed on ``server1``, after sending the ``ha-maintenance-start`` command
to ``server2``.

If the ``ha-maintenance-start`` command was sent to the server and the server
has transitioned to the ``partner-in-maintenance`` state, it is possible to
transition both it and its partner back to their previous states to resume the
normal operation of the HA pair. This is achieved by sending the
``ha-maintenance-cancel`` command to the server that is in the
``partner-in-maintenance`` state. However, if the server has already
transitioned to the ``partner-down`` state as a result of detecting that the
partner is offline, canceling the maintenance is no longer possible. In that
case, it is necessary to restart the other server and allow it to complete its
normal state negotiation process.

Upgrading From Older HA Versions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To upgrade from an older HA hook library to the current version, the
administrator must shut down one of the servers and rely on the failover
mechanism to force the online server to transition to the ``partner-down`` state,
where it starts serving all DHCP clients. Once the hook library on the first
server is upgraded to a current version, the ``ha-maintenance-start`` command
can be used to upgrade the second server.

In such a case, shut down the server running the old version. Next, send the
``ha-maintenance-start`` command to the server that has been upgraded. This
server should immediately transition to the ``partner-down`` state as it cannot
communicate with its offline partner. In the ``partner-down`` state the first
(upgraded) server will respond to all DHCP requests, allowing the administrator
to perform the upgrade on the second server.

.. note::

   Do not send the ``ha-maintenance-start`` command while the server running the
   old hook library is still online. The server receiving this command will
   return an error.


.. _ha-control-commands:

Control Commands for High Availability
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Even though the HA hook library is designed to automatically resolve issues with
DHCP service interruptions by redirecting the DHCP traffic to a surviving server
and synchronizing the lease database as needed, it may be useful for the
administrator to have more control over both servers' behavior. In particular,
it may be useful to be able to trigger lease-database synchronization on demand,
or to manually set the HA scopes that are being served.

The backup server can sometimes be used to handle DHCP traffic if both active
servers are down. The backup server does not perform the failover function
automatically; thus, in order to use the backup server to respond to DHCP
queries, the server administrator must enable this function manually.

The following sections describe commands supported by the HA hook library which
are available for the administrator.

.. _command-ha-sync:

The ``ha-sync`` Command
-----------------------

The ``ha-sync`` command instructs the server to synchronize its local lease
database with the selected peer. The server fetches all leases from the peer and
updates any locally stored leases which are older than those fetched. It also
creates new leases when any of those fetched do not exist in the local database.
All leases that are not returned by the peer but are in the local database are
preserved. The database synchronization is unidirectional; only the database on
the server to which the command has been sent is updated. To synchronize the
peer's database, a separate ``ha-sync`` command must be issued to that peer.

Database synchronization may be triggered for both active and backup server
types. The ``ha-sync`` command has the following structure (in a DHCPv4 example):

::

   {
       "command": "ha-sync",
       "service": [ "dhcp4 "],
       "arguments": {
           "server-name": "server2",
           "max-period": 60
       }
   }

When the server receives this command it first disables the DHCP service of the
server from which it will be fetching leases, by sending the ``dhcp-disable``
command to that server. The ``max-period`` parameter specifies the maximum
duration (in seconds) for which the DHCP service should be disabled. If the DHCP
service is successfully disabled, the synchronizing server fetches leases from
the remote server by issuing one or more ``lease4-get-page`` commands. When the
lease-database synchronization is complete, the synchronizing server sends the
``dhcp-enable`` command to the peer to re-enable its DHCP service.

The ``max-period`` value should be sufficiently long to guarantee that it does
not elapse before the synchronization is completed. Otherwise, the DHCP server
will automatically enable its DHCP function while the synchronization is still
in progress. If the DHCP server subsequently allocates any leases during the
synchronization, those new (or updated) leases will not be fetched by the
synchronizing server, leading to database inconsistencies.

.. _command-ha-scopes:

The ``ha-scopes`` Command
-------------------------

This command allows an administrator to modify the HA scopes being served.
Consult :ref:`ha-load-balancing-config` and :ref:`ha-hot-standby-config` to
learn which scopes are available for the different HA modes of operation. The
``ha-scopes`` command has the following structure (in a DHCPv4 example):

::

   {
       "command": "ha-scopes",
       "service": [ "dhcp4" ],
       "arguments": {
           "scopes": [ "HA_server1", "HA_server2" ]
       }
   }

This command configures the server to handle traffic from both the "HA_server1"
and "HA_server2" scopes. To disable all scopes specify an empty list:

::

   {
       "command": "ha-scopes",
       "service": [ "dhcp4 "],
       "arguments": {
           "scopes": [ ]
       }
   }

.. _command-ha-continue:

The ``ha-continue`` Command
---------------------------

This command is used to resume the operation of the paused HA state machine, as
described in :ref:`ha-pause-state-machine`. It takes no arguments, so the
command structure is simply:

::

   {
       "command": "ha-continue",
       "service": [ "dhcp4" ]
   }

.. _command-ha-heartbeat:

The ``ha-heartbeat`` Command
----------------------------

The :ref:`ha-server-states` section describes how the ``ha-heartbeat`` command
is used by a pair of active HA servers to detect one partner's failure. This
command, however, can also be sent by the system administrator to one or both
servers to check their HA state. This allows a monitoring system to be deployed
on the HA enabled servers to periodically check whether they are operational or
whether any manual intervention is required. The ``ha-heartbeat`` command takes
no arguments:

::

   {
       "command": "ha-heartbeat",
       "service": [ "dhcp4" ]
   }

Upon successful communication with the server, a response similar to this should
be returned:

::

   {
      "result": 0,
      "text": "HA peer status returned.",
      "arguments":
          {
              "state": "partner-down",
              "date-time": "Thu, 07 Nov 2019 08:49:37 GMT",
              "scopes": [ "server1" ],
              "unsent-update-count": 123
          }
   }

The returned ``state`` value should be one of the values listed in
:ref:`ha-server-states`. In the example above, the ``partner-down`` state is
returned, which indicates that the server which responded to the command
believes that its partner is offline; thus, it is serving all DHCP requests sent
to the servers. To ensure that the partner is indeed offline, the administrator
should send the ``ha-heartbeat`` command to the second server. If sending the
command fails, e.g. due to an inability to establish a TCP connection to the
Control Agent, or if the Control Agent reports issues with communication with
the DHCP server, it is very likely that the server is not running.

The ``date-time`` parameter conveys the server's notion of time.

The ``unsent-update-count`` value is a cumulative count of all unsent lease
updates since the server was booted; its value is set to 0 when the server is
started. It is never reset to 0 during the server's operation, even after the
partner synchronizes the database. It is incremented by the partner sending the
heartbeat response when it cannot send the lease update. For example, suppose
the failure is a result of a temporary communication interruption. In that case,
the partner receiving the ``partner-down`` heartbeat response tracks the value
changes and can determine, once communication is reestablished, whether there
are any new lease updates that it did not receive. If the values on both servers
do not match, it is an indication that the partner should synchronize its lease
database. A non-zero value itself is not an indication of any present issues
with lease updates, but a constantly incrementing value is.

The typical response returned by one server when both are
operational is:

::

   {
      "result": 0,
      "text": "HA peer status returned.",
      "arguments":
          {
              "state": "load-balancing",
              "date-time": "Thu, 07 Nov 2019 08:49:37 GMT",
              "scopes": [ "server1" ],
              "unsent-update-count": 0
          }
   }

In most cases, the ``ha-heartbeat`` command should be sent to both HA-enabled
servers to verify the state of the entire HA setup. In particular, if one of the
servers indicates that it is in the ``load-balancing`` state, it means that this
server is operating as if its partner is functional. When a partner goes down,
it takes some time for the surviving server to realize it. The
:ref:`ha-scope-transition` section describes the algorithm which the surviving
server follows before it transitions to the ``partner-down`` state. If the
``ha-heartbeat`` command is sent during the time window between the failure of
one of the servers and the transition of the surviving server to the
``partner-down`` state, the response from the surviving server does not reflect
the failure. Resending the command detects the failure once the surviving server
has entered the ``partner-down`` state.

.. note:

   Always send the ``ha-heartbeat`` command to both active HA servers to check
   the state of the entire HA setup. Sending it to only one of the servers may
   not reflect issues that just began with one of the servers.

.. _command-ha-status-get:

The ``status-get`` Command
--------------------------

``status-get`` is a general-purpose command supported by several Kea daemons,
not only the DHCP servers. However, when sent to a DHCP server with HA enabled,
it can be used to get insight into the details of the HA-specific server status.
Not only does the response contain the status information of the server
receiving this command, but also the information about its partner if it is
available.

The following is an example response to the ``status-get`` command, including
the HA status of two ``load-balancing`` servers:

.. code-block:: json

   {
       "result": 0,
       "text": "",
       "arguments": {
           "pid": 1234,
           "uptime": 3024,
           "reload": 1111,
           "high-availability": [
               {
                   "ha-mode": "load-balancing",
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
                           "last-state": "load-balancing",
                           "communication-interrupted": true,
                           "connecting-clients": 2,
                           "unacked-clients": 1,
                           "unacked-clients-left": 2,
                           "analyzed-packets": 8
                       }
                   }
               }
           ],
           "multi-threading-enabled": true,
           "thread-pool-size": 4,
           "packet-queue-size": 64,
           "packet-queue-statistics": [ 0.2, 0.1, 0.1 ],
           "sockets": {
               "status": "ready"
           }
       }
   }

The ``high-availability`` argument is a list which currently comprises only one
element.

The ``ha-servers`` map contains two structures: ``local`` and ``remote``. The
former contains the status information of the server which received the command,
while the latter contains the status information known to the local server about
the partner. The ``role`` of the partner server is gathered from the local
configuration file, and thus should always be available. The remaining status
information, such as ``last-scopes`` and ``last-state``, is not available until
the local server communicates with the remote by successfully sending the
``ha-heartbeat`` command. If at least one such communication has taken place,
the returned value of the ``in-touch`` parameter is set to ``true``. By
examining this value, the command's sender can determine whether the information
about the remote server is reliable.

The ``last-scopes`` and ``last-state`` parameters contain information about the
HA scopes served by the partner and its state. This information is gathered
during the heartbeat command exchange, so it may not be accurate if a
communication problem occurs between the partners and this status information is
not refreshed. In such a case, it may be useful to send the ``status-get``
command to the partner server directly to check its current state. The ``age``
parameter specifies the age of the information from the partner, in seconds.

The ``communication-interrupted`` boolean value indicates whether the server
receiving the ``status-get`` command (the local server) has been unable to
communicate with the partner longer than the duration specified as
``max-response-delay``. In such a situation, the active servers are considered
to be in the ``communication-interrupted`` state. At this point, the local
server may start monitoring the DHCP traffic directed to the partner to see if
the partner is responding to this traffic. More about the failover procedure can
be found in :ref:`ha-load-balancing-config`.

The ``connecting-clients``, ``unacked-clients``, ``unacked-clients-left``, and
``analyzed-packets`` parameters were introduced along with the
``communication-interrupted`` parameter and they convey useful information about
the state of the DHCP traffic monitoring in the ``communication-interrupted``
state. Once the server leaves the ``communication-interrupted`` state, these
parameters are all reset to 0.

These parameters have the following meaning in the ``communication-interrupted``
state:

-  ``connecting-clients`` - this is the number of different clients which have
   attempted to get a lease from the remote server. These clients are
   differentiated by their MAC address and client identifier (in DHCPv4) or DUID
   (in DHCPv6). This number includes "unacked" clients (for which the "secs"
   field or "elapsed time" value exceeded the ``max-response-delay``).

-  ``unacked-clients`` - this is the number of different clients which have been
   considered "unacked", i.e. the clients which have been trying to get the
   lease longer than the value of the "secs" field, or for which the
   "elapsed time" exceeded the ``max-response-delay`` setting.

-  ``unacked-clients-left`` - this indicates the number of additional clients
   which have to be considered "unacked" before the server enters the
   ``partner-down`` state. This value decreases when the ``unacked-clients``
   value increases. The local server enters the ``partner-down`` state when this
   value decreases to 0.

-  ``analyzed-packets`` - this is the total number of packets directed to the
   partner server and analyzed by the local server since entering the
   communication interrupted state. It includes retransmissions from the same
   clients.

Monitoring these values helps to predict when the local server will enter the
``partner-down`` state or to understand why the server has not yet entered this
state.

The ``ha-mode`` parameter returns the HA mode of operation selected using the
``mode`` parameter in the configuration file. It can hold one of the following
values: ``load-balancing``, ``hot-standby``, or ``passive-backup``.

The ``status-get`` response has the format described above only in the
``load-balancing`` and ``hot-standby`` modes. In the ``passive-backup`` mode the
``remote`` map is not included in the response because in this mode there is
only one active server (local). The response includes no information about the
status of the backup servers.

.. _command-ha-maintenance-start:

The ``ha-maintenance-start`` Command
------------------------------------

This command is used to initiate the transition of the server's partner into the
``in-maintenance`` state and the transition of the server receiving the command
into the ``partner-in-maintenance`` state. See the :ref:`ha-maintenance` section
for details.

::

   {
       "command": "ha-maintenance-start",
       "service": [ "dhcp4" ]
   }

.. _command-ha-maintenance-cancel:

The ``ha-maintenance-cancel`` Command
-------------------------------------

This command is used to cancel the maintenance previously initiated using the
``ha-maintenance-start`` command. The server receiving this command will first
send ``ha-maintenance-notify``, with the ``cancel`` flag set to ``true``, to its
partner. Next, the server reverts from the ``partner-in-maintenance`` state to
its previous state. See the :ref:`ha-maintenance` section for details.

::

   {
       "command": "ha-maintenance-cancel",
       "service": [ "dhcp4" ]
   }

.. _command-ha-maintenance-notify:

The ``ha-maintenance-notify`` Command
-------------------------------------

This command is sent by the server receiving the ``ha-maintenance-start`` or the
``ha-maintenance-cancel`` command to its partner, to cause the partner to
transition to the ``in-maintenance`` state or to revert from this state to a
previous state. See the :ref:`ha-maintenance` section for details.

::

   {
       "command": "ha-maintenance-notify",
       "service": [ "dhcp4" ],
       "arguments": {
           "cancel": false
       }
   }

.. warning::

   The ``ha-maintenance-notify`` command is not meant to be used by system
   administrators. It is used for internal communication between a pair of
   HA-enabled DHCP servers. Direct use of this command is not supported and may
   produce unintended consequences.

.. _command-ha-reset:

The ``ha-reset`` Command
------------------------

This command causes the server to reset its High Availability state machine by
transitioning it to the ``waiting`` state. A partner in the
``communication-recovery`` state may send this command to cause the server
to synchronize its lease database. Database synchronization is required when the
partner has failed to send all lease database updates after re-establishing
connection after a temporary connection failure. It is also required when the
``delayed-updates-limit`` is exceeded, when the server is in the
``communication-recovery`` state.

A server administrator may send this command to reset a misbehaving state
machine.

This command includes no arguments:

::

   {
       "command": "ha-reset",
       "service": [ "dhcp4" ]
   }

And elicits the response:

::

   {
       "result": 0,
       "text": "HA state machine reset."
   }

If the server receiving this command is already in the ``waiting`` state, the
command has no effect.

.. _command-ha-sync-complete-notify:

The ``ha-sync-complete-notify`` Command
---------------------------------------

A server sends this command to its partner to signal that it has completed
lease-database synchronization. The partner may enable its DHCP service if it
can allocate new leases in its current state. The partner does not enable the
DHCP service in the ``partner-down`` state until it sends a successful heartbeat
test to its partner server. If the connection is still unavailable, the server
in the ``partner-down`` state enables its own DHCP service to continue
responding to clients.

This command includes no arguments:

::

   {
       "command": "ha-sync-complete-notify",
       "service": [ "dhcp4" ]
   }

And elicits the response:

::

   {
       "result": 0,
       "text": "Server successfully notified about the synchronization completion."
   }

.. warning::

   The ``ha-sync-complete-notify`` command is not meant to be used by system
   administrators. It is used for internal communication between a pair of
   HA-enabled DHCP servers. Direct use of this command is not supported and may
   produce unintended consequences.
