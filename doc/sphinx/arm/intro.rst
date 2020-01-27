.. _intro:

************
Introduction
************

Kea is the next generation of DHCP software developed by ISC. It
supports both DHCPv4 and DHCPv6 protocols along with their extensions,
e.g. prefix delegation and dynamic updates to DNS.

This guide covers Kea version |release|.

Supported Platforms
===================

Kea is officially supported on CentOS, Fedora, Ubuntu, Debian, and
FreeBSD systems. It is also likely to work on many other systems.
Kea-|release| builds have been tested on:

-  CentOS Linux — 7, 8
-  Fedora — 30, 31
-  Ubuntu — 16.04, 18.04, 19.04
-  Debian GNU/Linux — 9, 10
-  FreeBSD — 11.3, 12.0
-  Alpine Linux — 3.10
-  macOS — 10.13, 10.14

There are currently no plans to port Kea to Windows systems.

.. _required-software:

Required Software at Run-Time
=============================

Running Kea uses various extra software packages which may not be
provided in the default installation of some operating systems, nor in
the standard package collections. You may need to install this required
software separately. (For the build requirements, also see :ref:`build-requirements`.)

-  Kea supports two cryptographic libraries: Botan and OpenSSL. Only one
   of them is required to be installed during compilation. Kea uses the
   Botan library for C++ (https://botan.randombit.net/), version 2.0 or
   later. Note that support for Botan versions earlier than 2.0 was
   removed in Kea 1.7.0 and later. As an alternative to Botan, Kea can
   use the OpenSSL cryptographic library (https://www.openssl.org/),
   version 1.0.2 or later.

-  Kea uses the log4cplus C++ logging library
   (https://sourceforge.net/p/log4cplus/wiki/Home/). It requires log4cplus version
   1.0.3 or later.

-  Kea requires the Boost system library (https://www.boost.org/).
   Building with the header-only version of Boost is no longer
   recommended.

-  To store lease information in a MySQL database, Kea requires
   MySQL headers and libraries. This is an optional dependency;
   Kea can be built without MySQL support.

-  To store lease information in a PostgreSQL database, Kea
   requires PostgreSQL headers and libraries. This is an optional
   dependency; Kea can be built without PostgreSQL support.

-  To store lease information in a Cassandra database (CQL),
   Kea requires Cassandra headers and libraries. This is an optional
   dependency; Kea can be built without Cassandra support.

-  Integration with RADIUS is provided in Kea via the hooks library
   available to our paid support customers. Use of this library requires
   the FreeRadius-client library to be present on the system where Kea
   is running. This is an optional dependency; Kea can be built
   without RADIUS support.

-  Kea provides a NETCONF interface with the
   kea-netconf agent. This Kea module is built optionally and requires
   Sysrepo software when used. Building Kea with NETCONF support
   requires many dependencies to be installed, which are described in
   more detail in :ref:`netconf-install`.

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
