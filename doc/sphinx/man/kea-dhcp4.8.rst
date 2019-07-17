:orphan:

kea-dhcp4
8
Kea
kea-dhcp4
DHCPv4 server in Kea
2011-2018
Internet Systems Consortium, Inc. ("ISC")
kea-dhcp4
-v
-V
-W
-d
-c
config-file
-t
config-file
-p
server-port-number
-P
client-port-number
DESCRIPTION
===========

The ``kea-dhcp4`` daemon provides the DHCPv4 server implementation.

ARGUMENTS
=========

The arguments are as follows:

``-v``
   Display the version.

``-V``
   Display the extended version.

``-W``
   Display the configuration report.

``-d``
   Enable the debug mode with extra verbosity.

``-c``
   Configuration file including the configuration for DHCPv4 server. It
   may also contain configuration entries for other Kea services.

``-t``
   Check the configuration file and report the first error if any. Note
   that not all parameters are completely checked, in particular,
   service and control channel sockets are not opened, and hook
   libraries are not loaded.

``-p``
   Server port number (1-65535) on which the server listens. This is
   useful for testing purposes only.

``-P``
   Client port number (1-65535) to which the server responds. This is
   useful for testing purposes only.

DOCUMENTATION
=============

Kea comes with an extensive Kea User's Guide documentation that covers
all aspects of running the Kea software - compilation, installation,
configuration, configuration examples and many more. Kea also features a
Kea Messages Manual, which lists all possible messages Kea can print
with a brief description for each of them. Both documents are typically
available in various formats (txt, html, pdf) with your Kea
distribution. The Kea documentation is available at
https://kb.isc.org/docs/kea-administrator-reference-manual .

Kea source code is documented in the Kea Developer's Guide. Its on-line
version is available at https://jenkins.isc.org/job/Kea_doc/doxygen/.

Kea project website is available at: https://kea.isc.org.

MAILING LISTS AND SUPPORT
=========================

There are two mailing lists available for Kea project. kea-users
(kea-users at lists.isc.org) is intended for Kea users, while kea-dev
(kea-dev at lists.isc.org) is intended for Kea developers, prospective
contributors and other advanced users. Both lists are available at
http://lists.isc.org. The community provides best effort type of support
on both of those lists.

ISC provides professional support for Kea services. See
https://www.isc.org/kea/ for details.

HISTORY
=======

The ``b10-dhcp4`` daemon was first coded in November 2011 by Tomek
Mrugalski.

In the mid 2014 Kea was decoupled from the BIND10 framework and became a
standalone DHCP server. The DHCPv4 server binary was renamed to
kea-dhcp4. Kea 1.0.0 was released in December 2015.

SEE ALSO
========

kea-dhcp6 8, kea-dhcp-ddns 8, kea-ctrl-agent 8, kea-admin 8, keactrl 8,
kea-netconf 8, perfdhcp 8, kea-lfc 8, Kea Administrator's Guide.
