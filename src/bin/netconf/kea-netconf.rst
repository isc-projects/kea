kea-netconf
8
Kea
kea-netconf
NETCONF agent for Kea environment
2018
Internet Systems Consortium, Inc. ("ISC")
kea-netconf
-v
-V
-W
-d
-c
config-file
-t
config-file
DESCRIPTION
===========

The ``kea-netconf`` agent provides a YANG/NETCONF interface for the Kea
environment.

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
   Configuration file including the configuration for NETCONF agent.

``-t``
   Check the syntax of the configuration file and report the first error
   if any. Note that not all parameters are completely checked, in
   particular, service and client sockets are not opened, and hook
   libraries are not loaded.

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

Kea project website is available at:
https://gitlab.isc.org/isc-projects/kea.

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

Early prototypes of kea-netconf implementation were written during IETF
Hackathons in Berlin, London and Montreal. An actual production ready
implementation was started in August 2018 by Tomek Mrugalski and Francis
Dupont.

SEE ALSO
========

kea-dhcp4 8, kea-dhcp6 8, kea-dhcp-ddns 8, kea-ctrl-agent 8, kea-admin
8, keactrl 8, perfdhcp 8, kea-lfc 8, Kea Administrator's Guide.
