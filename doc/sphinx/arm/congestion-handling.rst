.. _congestion-handling:

*******************
Congestion Handling
*******************

.. _congestion-handling-background:

What is Congestion?
===================

Congestion occurs when servers are subjected to client queries faster
than those queries can be processed. As a result, the servers begin accumulating
a backlog of pending queries. The longer the high rate of traffic
continues, the farther behind the servers fall. Depending on the client
implementations, those that fail to get leases either give up or simply
continue to retry forever. In the former case, the server may eventually
recover, but the latter case is a vicious cycle from which the server is
unable to escape.

Congestion typically occurs when there is a network event that causes overly large
numbers of clients to simultaneously need leases, such as recovery after
a network outage. In a well-planned deployment, the number and capacity of servers is
matched to the maximum expected client load. If the load is routinely too
heavy, then the deployment needs to be re-evaluated. 

The goal of congestion handling is to help servers mitigate the peak in
traffic by fulfilling as many of the most relevant requests as possible
until the congestion subsides.

.. _congestion-handling-solution:

Configuring Congestion Handling
===============================

Congestion handling
offers the ability to configure the server to use a separate thread to
read packets from the interface socket buffers. As the thread reads
packets from the buffers, they are added to an internal packet queue,
and the server's main application thread processes packets from this
queue rather than from the socket buffers. By structuring it this way, a
configurable layer has been introduced which can make decisions on which
packets to process, how to store them, and the order in which they are
processed by the server.

The default packet queue implementation for both ``kea-dhcp4`` and ``kea-dhcp6``
is a simple ring buffer. Once it reaches capacity, new packets get added
to the back of the queue by discarding packets from the front of the
queue. Rather than always discarding the newest packets, Kea now always
discards the oldest packets. The capacity of the buffer, i.e. the maximum
number of packets the buffer can contain, is configurable. A reasonable
starting point is to match the capacity to the number of leases
per second a specific installation of Kea can handle. This
figure varies widely depending on the specifics of an individual deployment.

As there is no one algorithm that can best handle the dynamics of all
sites, and because over time new approaches will evolve, the packet
queue is implemented as a plug-in, which can be replaced by a custom queue
implementation via a hook library. This should make it straightforward
for interested parties to experiment with their own solutions.
(Developers can refer to ``isc::dhcp::PacketQueue`` and
``isc::dhcp::PacketQueueMgr``, described in the
`Kea Developer's Guide <https://reports.kea.isc.org/dev_guide/index.html>`__.)

Packet queue behavior is configured in both ``kea-dhcp4`` and ``kea-dhcp6``
servers through an optional, top-level, configuration element,
``dhcp-queue-control``. Omitting this element disables packet queueing:

::

      "dhcp-queue-control": {
          "enable-queue": true|false,
          "queue-type": "queue type",
          "capacity" : n
      }

where:

-  ``enable-queue`` - enables or disables packet queueing.
   When ``true``, the server processes packets from the packet queue, which
   is filled by a separate thread. When ``false``, the server processes
   packets directly from the socket buffers in the main thread. It is
   disabled (``false``) by default.

-  ``queue-type`` - the name of the queue implementation to use. This value
   exists so that custom implementations can be registered (via a hook
   library) and then selected. There is a default packet queue
   implementation that is pre-registered during server start up:
   "kea-ring4" for ``kea-dhcp4`` and "kea-ring6" for ``kea-dhcp6``.

-  ``capacity`` - this is the maximum number of packets the
   queue can hold before packets are discarded. The optimal value for
   this is extremely site-dependent. The default value is 64 for both
   "kea-ring4" and "kea-ring6".

The following example enables the default packet queue for ``kea-dhcp4``,
with a queue capacity of 250 packets:

::

   "Dhcp4":
   {
       ...
      "dhcp-queue-control": {
          "enable-queue": true,
          "queue-type": "kea-ring4",
          "capacity" : 250
       },
       ...
   }

The following example enables the default packet queue for ``kea-dhcp6``,
with a queue capacity of 300 packets:

::

   "Dhcp6":
   {
       ...
      "dhcp-queue-control": {
          "enable-queue": true,
          "queue-type": "kea-ring6",
          "capacity" : 300
       },
       ...
   }

.. note:

   Congestion handling is currently incompatible with multi-threading;
   when both are enabled, congestion handling is silently disabled.
