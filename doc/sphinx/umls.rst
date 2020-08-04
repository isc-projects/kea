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

These flow diagram files describe the Kea DHCPv4 server implementation.
They are provided in UML (source), PNG and SVG formats.

The main loop is common to DHCPv4 and DHPCv6 servers.

.. figure:: uml/main-loop.*

    DHCP server main loop

Next is the DHCPv4 packet processing.

.. figure:: uml/packet4.*

    DHCPv4 packet processing

With more details for DHCPREQUEST processing.

.. figure:: uml/request4.*

    DHCPREQUEST processing

Packet processing begins by the subnet selection i.e. the localization
of the sender of the query. Note that when the selected subnet is a
member of a shared network in fact the whole shared network was selected.

.. figure:: uml/select4.*

    DHCPv4 subnet selection

After the subnet selection and before the lease allocation the DHCPv4
server handles specific case as the INIT-REBOOT client state.

.. note::

    The "Request lease" box will be expanded below as lease allocation.

.. figure:: uml/assign-lease4.*

    DHCPv4 Assign Lease

The allocation of a lease (or not) to an incoming request is very complex
so is given too as an algorithm summary.

.. figure:: uml/request4-lease.*

    Allocate a lease for DHCPREQUEST

.. figure:: uml/requestLease4.*

    requestLease4 algorithm

The different lease states including the free one where no lease object exists.

.. note::

    In statistics declined addresses are counted with the assigned addresses
    so the :math:`assigned + free = total` equation stands.

.. figure:: uml/lease-states.*

    lease states

The allocation engine maintains a notion of current subnet and host
reservation.

.. note::

    Beware that to find a free lease the allocation engine starts from
    the *preferred* subnet i.e. the last used one so the current subnet
    can depend on the history, not only from the incoming query...

.. figure:: uml/currentHost4.*

    currentHost

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

