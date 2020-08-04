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

These diagrams are focused on those aspects of Kea processing that will be most useful to operators. The diagrams illustrate DHCPv4 request processing, but most of the logic applies to DHCPv6. The diagrams are provided in the Kea source tree in UML (source), PNG and SVG formats.

Main Loop
=========

The main loop is common to DHCPv4 and DHPCv6 servers.

.. figure:: uml/main-loop.*

    DHCP server main loop


.. _uml_packet4:
DHCPv4 Packet Processing
========================

Next is the DHCPv4 packet processing.

.. figure:: uml/packet4.*

    DHCPv4 packet processing


.. _uml_request4:
DHCP Request Processing
=======================

With more details for DHCPREQUEST processing.

.. figure:: uml/request4.*

    DHCPREQUEST processing

Packet processing begins by the subnet selection i.e. the localization
of the sender of the query. Note that when the selected subnet is a
member of a shared network in fact the whole shared network was selected.

.. _uml_select4:
DHCPv4 Subnet Selection
=======================

.. figure:: uml/select4.*

    DHCPv4 subnet selection

After the subnet selection and before the lease allocation the DHCPv4
server handles specific case as the INIT-REBOOT client state.

.. note::

    The "Request lease" box will be expanded below as lease allocation.

.. _uml_assign-lease4:
DHCPv4 Assign Lease
===================

.. figure:: uml/assign-lease4.*

    DHCPv4 Assign Lease

The allocation of a lease (or not) to an incoming request is very complex
so is given too as an algorithm summary.

.. _uml_request4-lease:
DHCPv4 Allocate Lease
====================

.. figure:: uml/request4-lease.*

    Allocate a lease for DHCPREQUEST

.. figure:: uml/requestLease4.*

    requestLease4 algorithm

The different lease states including the free one where no lease object exists.

.. note::

    In statistics declined addresses are counted with the assigned addresses
    so the :math:`assigned + free = total` equation stands.

.. _uml_lease-states:
Lease States
============

.. figure:: uml/lease-states.*

    lease states

The allocation engine maintains a notion of current subnet and host
reservation.

.. note::

    Beware that to find a free lease the allocation engine starts from
    the *preferred* subnet i.e. the last used one so the current subnet
    can depend on the history, not only from the incoming query...

.. _uml_currentHost4:
Checking for Host Reservations
===================

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

