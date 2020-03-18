.. _intro:

************
Introduction
************

Kea is the next generation of DHCP software developed by ISC. It
supports both DHCPv4 and DHCPv6 protocols along with their extensions,
e.g. prefix delegation and dynamic updates to DNS.

This guide covers Kea version |release|.

For information about supported platforms see :ref:`platforms`.

.. include:: platforms.rst

.. _kea_software:

Kea Software
============

Kea is modular. Part of this modularity is accomplished using multiple
cooperating processes which, together, provide the server functionality.
The following software is included with Kea:

-  ``keactrl`` — This tool starts, stops, reconfigures, and reports status for
   the Kea servers.

-  ``kea-dhcp4`` — The DHCPv4 server process. This process responds to
   DHCPv4 queries from clients.

-  ``kea-dhcp6`` — The DHCPv6 server process. This process responds to
   DHCPv6 queries from clients.

-  ``kea-dhcp-ddns`` — The DHCP Dynamic DNS process. This process acts
   as an intermediary between the DHCP servers and DNS servers. It
   receives name update requests from the DHCP servers and sends DNS
   update messages to the DNS servers.

-  ``kea-admin`` — A useful tool for database backend maintenance
   (creating a new database, checking versions, upgrading, etc.).

-  ``kea-lfc`` — This process removes redundant information from the
   files used to provide persistent storage for the memfile database
   backend. While it can be run standalone, it is normally run as and
   when required by the Kea DHCP servers.

-  ``kea-ctrl-agent`` — Kea Control Agent (CA) is a daemon that exposes
   a RESTful control interface for managing Kea servers.

-  ``kea-netconf`` - kea-netconf is an agent that provides a
   YANG/NETCONF interface for the Kea environment.

-  ``kea-shell`` — This simple text client uses the REST interface to
   connect to the Kea Control Agent.

-  ``perfdhcp`` — A DHCP benchmarking tool which simulates multiple
   clients to test both DHCPv4 and DHCPv6 server performance.

The tools and modules are covered in full detail in this guide. In
addition, manual pages are also provided in the default installation.

Kea also provides C++ libraries and programmer interfaces for DHCP.
These include detailed developer documentation and code examples.
