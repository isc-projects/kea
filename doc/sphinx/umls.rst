..
   Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.

.. _umls:

Kea Flow Diagrams
=================

These flow diagrams describe the Kea DHCPv4 server implementation. They may be useful for system administrators to understand for several reasons. In order to design a configuration that will result in clients getting the intended addresses and options it is important to understand the sequence of request processing steps. For example, Kea will iterate looking for a suitable address, and will conditionally accept the first available address, so the order in which addresses are evaluated matters.

It is also useful to understand Kea's processing logic because there are configuration choices which can make the process far more efficient. Kea is very flexible so that it can be applied to very different use cases and in different environments.  In an environment where throughput and efficiency are a priority, the administrator can choose to limit some of the processing steps. For example, it is possible to limit the number of different client identifiers Kea evaluates in looking for a host reservation, or even to skip the whole step of checking for host reservations.

These diagrams are focused on those aspects of Kea processing that will be most useful to operators. The diagrams illustrate DHCPv4 request processing, but most of the logic applies to DHCPv6. Following the title of each diagram is a Kea version number. Kea behavior has evolved over time, and the diagrams document the behavior as of the Kea version indicated. The diagrams are provided in the Kea source tree in UML (source), PNG and SVG formats.

Main Loop
^^^^^^^^^

The main loop is common to both DHCPv4 and DHPCv6 servers.

.. figure:: uml/main-loop.*

    DHCP server main loop


.. _uml_packet4:

DHCPv4 Packet Processing
^^^^^^^^^^^^^^^^^^^^^^^^

Next is the DHCPv4 packet processing, where we determine what sort of DHCP message this is, Discover, Request, Release, Decline or Inform. This diagram shows the general, high level flow for processing an inbound client DHCP packet (e.g. Discover, Request, Release, etc) from receipt to the server's response..

.. figure:: uml/packet4.*

    DHCPv4 packet processing


.. _uml_request4:

DHCP Request Processing
^^^^^^^^^^^^^^^^^^^^^^^

The following diagrams focus on DHCPREQUEST processing. This chart gives an overview of the process, beginning with subnet selection, proceeding to checking for Host Reservations and evaluating client classes. Finally, before acknowledging the lease, the options are evaluated and added to the message.

.. figure:: uml/request4.*

    DHCPREQUEST processing

.

.. _uml_select4:

DHCPv4 Subnet Selection
^^^^^^^^^^^^^^^^^^^^^^^

Subnet selection is the process of choosing a subnet that is topologically appropriate for the client. Note that when the selected subnet is a member of a shared network the whole shared network is selected.  During subnet selection the client class may be checked more than once while iterating through subnets, to determine if it is permitted in the selected subnet.


.. figure:: uml/select4.*

    DHCPv4 subnet selection


.. _uml_assign-lease4:

DHCPv4 Special Case of Double-booting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After the subnet selection and before the lease allocation the DHCPv4 server handles the special case of clients restarting with an image provided by PXE boot or bootp.  Note that the Lease Request box is expanded below.

.. figure:: uml/assign-lease4.*

    DHCPv4 Assign Lease


.. _uml_request4-lease:

DHCPv4 Allocate Lease
^^^^^^^^^^^^^^^^^^^^^

This diagram provides the details of the processing the client request, showing renewing an existing lease, assigning a reserved lease and allocating an unreserved lease. The next diagram after this one shows the algorithm in more detail.

.. figure:: uml/request4-lease.*

    Allocate a lease for DHCPREQUEST

This diagram shows the algorithm used to validate a requested lease or select a new address to offer. The far right side of the diagram shows how a new address is selected when a new lease is required and the client has neither a requested address nor a reservation. Note that when a new lease is required and Kea iterates over pools and subnets, it starts with the subnet selected above in the subnet selection process.

.. figure:: uml/requestLease4.*

    requestLease4 algorithm


.. note::

    Declined addresses are included in the statistic for assigned addresses
    so the :math:`assigned + free = total` equation is true.

.. _uml_lease-states:

Lease States
^^^^^^^^^^^^

This diagram illustrates the different lease states including the free one where no lease object exists.

.. figure:: uml/lease-states.*

    lease states


.. _uml_currentHost4:

Checking for Host Reservations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The allocation engine checks for host reservations after selecting a subnet. This diagram shows the details of that operation. Subnet selection is based on network topology. Host reservations are primarily for assigning options, and options are evaluated after subnet selection. However if client classes are added in the host reservation, those will also be evaluated against the selected subnet in a further check (added in Kea 1.7.10).  Kea includes several options to skip checking for host reservations, which can make this process much more efficient if you are not using reservations.

.. note::

    To find a free lease the allocation engine begins with evaluating the most recently used subnet.
    The current subnet depends on the history of prior queries.


.. figure:: uml/currentHost4.*

    currentHost

.. _uml_CfgOptionList:

Building the Options List
^^^^^^^^^^^^^^^^^^^^^^^^^

Before sending a response, options are added:
 - evaluate required client classes
 - build the configured option list
 - append requested options
 - append requested vendor options
 - append basic options

.. figure:: uml/buildCfgOptionList.*

    buildCfgOptionList (build configured option list) algorithm

.. figure:: uml/appendRequestedOptions.*

    appendRequestedOptions (append requested options) algorithm

.. figure:: uml/appendRequestedVendorOptions.*

    appendRequestedVendorOptions (append vendor requested options) algorithm
