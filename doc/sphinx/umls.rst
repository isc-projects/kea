..
   Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.

.. _umls:

Kea Flow Diagrams
=================

These UML activity diagrams describe the Kea DHCPv4 server implementation. They may be useful for system administrators to understand for several reasons. In order to design a configuration that will result in clients getting the intended addresses and options it is important to understand the sequence of request processing steps. For example, Kea will iterate looking for a suitable address, and will conditionally accept the first available address, so the order in which addresses are evaluated matters.

It is also useful to understand Kea's request processing logic because there are configuration choices which can make the process far more efficient. Kea is very flexible so that it can be applied to very different use cases and in different environments.  In an environment where throughput and efficiency are a priority, the administrator can choose to limit some of the processing steps. For example, it is possible to limit the number of different client identifiers Kea evaluates in looking for a host reservation, or even to skip the whole step of checking for host reservations.

These diagrams are focused on those aspects of Kea processing that will be most useful to operators. The diagrams illustrate DHCPv4 request processing, but most of the logic applies to DHCPv6. Following the title of each diagram is a Kea version number. Kea behavior has evolved over time, and the diagrams document the behavior as of the Kea version indicated. The diagrams are provided in the Kea source tree in UML (source), PNG and SVG formats.

Main Loop
=========

The main loop is common to both DHCPv4 and DHPCv6 servers.

.. figure:: uml/main-loop.*

    DHCP server main loop


.. _uml_packet4:
DHCPv4 Packet Processing
========================

Next is the DHCPv4 packet processing, where we determine what sort of DHCP message this is, Discover, Request, Release, Decline or Inform. 

.. figure:: uml/packet4.*

    DHCPv4 packet processing


.. _uml_request4:
DHCP Request Processing
=======================

The following diagram and subsequent charts focus on DHCPREQUEST processing.  The first step, Subnet Selection, is expanded in a subsequent section :ref:`uml_select4`. There is also a section below that expands on :ref:`CfgOptionList`.

.. figure:: uml/request4.*

    DHCPREQUEST processing

. 

.. _uml_select4:
DHCPv4 Subnet Selection
=======================

Packet processing begins with subnet selection. Subnet selection is the process of ensuring the selected subnet is topologically appropriate for the client. Note that when the selected subnet is a member of a shared network the whole shared network is selected.


.. figure:: uml/select4.*

    DHCPv4 subnet selection


.. _uml_assign-lease4:
DHCPv4 Assign Lease
===================

After the subnet selection and before the lease allocation the DHCPv4 server handles the special case of clients restarting with an image provided by PXE boot or bootp.  The "Request lease" box in this diagram is expanded below as :ref:'request4-lease'.

.. figure:: uml/assign-lease4.*

    DHCPv4 Assign Lease


.. _uml_request4-lease:
DHCPv4 Allocate Lease
====================

This diagram provides the details of the lease request process. Note that when a new lease is required and Kea iterates over pools and subnets, it starts with the subnet selected above in the subnet selection process. 

.. figure:: uml/request4-lease.*

    Allocate a lease for DHCPREQUEST
    

.. figure:: uml/requestLease4.*

    requestLease4 algorithm


.. note::

    In statistics declined addresses are counted with the assigned addresses
    so the :math:`assigned + free = total` equation stands.

.. _uml_lease-states:
Lease States
============

This diagram illustrates the different lease states including the free one where no lease object exists.

.. figure:: uml/lease-states.*

    lease states


.. _uml_currentHost4:
Checking for Host Reservations
===================

The allocation engine checks for host reservations after selecting a subnet. This diagram shows the details of that operation. Subnet selection is based on network topology. Host reservations are primarily for assigning options, and options are evaluated after subnet selection. However if client classes are added in the host reservation, those will also be evaluated against the selected subnet in a further check (added in Kea 1.7.10)

.. note::

    To find a free lease the allocation engine begins with evaluating the most recently used subnet. 
    The current subnet depends on the history of prior queries.

Kea includes several options to minimize checking for host reservations. Storing host reservations in an `optional MySQL or PostgreSQL backend <https://kea.readthedocs.io/en/latest/arm/dhcp4-srv.html#storing-host-reservations-in-mysql-postgresql-or-cassandra/>` is a popular feature. Keep in mind that accessing anything in a separate database will be slower than a lookup in a local in-memory file, so be sure to configure the approriate host reservation mode for more efficient processing when using a host reservation database backend 


.. figure:: uml/currentHost4.*

    currentHost

.. _uml_CfgOptionList:
Building the Options List
=========================

Before sending a response options are added:
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

