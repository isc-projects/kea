kea-dhcp-ddns
8
Kea
kea-dhcp-ddns
DHCP-DDNS process in Kea
2013-2018
Internet Systems Consortium, Inc. ("ISC")
kea-dhcp-ddns
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

The ``kea-dhcp-ddns`` service process requests to update DNS mapping
based on DHCP lease change events. It runs as a separate process that
expects to receive Name Change Requests from Kea DHCP servers.

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
   Configuration file including the configuration for DHCP-DDNS server.
   It may also contain configuration entries for other Kea services.

``-t``
   Check the syntax of the configuration file and report the first error
   if any. Note that not all parameters are completely checked, in
   particular, service socket is not opened.

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

The ``b10-dhcp-ddns`` process was first coded in May 2013 by Thomas
Markwalder.

Kea became a standalone server and the BIND10 framework was removed. The
DHCP-DDNS server binary was renamed to kea-dhcp-ddns in July 2014. Kea
1.0.0 was released in December 2015.

SEE ALSO
========

kea-dhcp4 8, kea-dhcp6 8, kea-ctrl-agent 8, kea-admin 8, keactrl 8,
kea-netconf 8, perfdhcp 8, kea-lfc 8, Kea Administrator's Guide.
