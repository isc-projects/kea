:orphan:

kea-ctrl-agent
8
Kea
kea-ctrl-agent
Control Agent process in Kea
2016-2018
Internet Systems Consortium, Inc. ("ISC")
kea-ctrl-agent
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

The ``kea-ctrl-agent`` provides a REST service for controlling Kea
services. The received HTTP requests are decapsulated and forwarded to
the respective Kea services in JSON format. Received JSON responses are
encapsulated within HTTP responses and returned to the controlling
entity. Some commands may be handled by the Control Agent directly, and
not forwarded to any Kea service.

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
   Verbose mode sets the logging level to debug. This is primarily for
   development purposes in stand-alone mode.

``-c``
   Configuration file including the configuration for the Control Agent
   server. It may also contain configuration entries for other Kea
   services.

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

The ``kea-ctrl-agent`` was first coded in December 2016 by Marcin
Siodelski.

SEE ALSO
========

kea-dhcp4 8, kea-dhcp6 8, kea-dhcp-ddns 8, kea-admin 8, keactrl 8,
perfdhcp 8, kea-lfc 8, Kea Administrator's Guide.
