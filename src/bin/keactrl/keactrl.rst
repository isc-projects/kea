keactrl
8
Kea
keactrl
Shell script for managing Kea
2014-2018
Internet Systems Consortium, Inc. ("ISC")
keactrl
command
-c
keactrl-config-file
-s
server[,server,...]
-v
DESCRIPTION
===========

keactrl is a shell script which controls the startup, shutdown and
reconfiguration of the Kea servers (``kea-dhcp4``, ``kea-dhcp6``,
``kea-dhcp-ddns``, ``kea-ctrl-agent`` and ``kea-netconf``). It also
provides the means for checking the current status of the servers and
determining the configuration files in use.

CONFIGURATION FILE
==================

Depending on requirements, not all of the available servers need be run.
The keactrl configuration file sets which servers are enabled and which
are disabled. By default the configuration file is
``[kea-install-dir]/etc/kea/keactrl.conf``.

See the Kea Administrator's Guide for the documentation of the
parameters in the ``keactrl`` configuration file.

OPTIONS
=======

``command``
   Command to be issued to the servers. It can be one of the following:

   start
      Start the servers.

   stop
      Stop the servers.

   reload
      Instructs the servers to re-read the kea configuration file. This
      command is not supported by the Netconf agent.

   status
      Print the status of the servers.

``-c|--ctrl-config keactrl-config-file``
   Specify the ``keactrl`` configuration file. Without this switch, the
   ``keactrl`` will attempt to use the file
   ``[kea-install-dir]/etc/kea/keactrl.conf``.

``-s|--server server[,server,...]``
   Specifies a subset of the enabled servers to which the command should
   be issued. The list of servers should be separated by commas with no
   intervening spaces. Acceptable values are:

   dhcp4
      DHCPv4 server (``kea-dhcp4``).

   dhcp6
      DHCPv6 server (``kea-dhcp6``).

   dhcp_ddns
      DHCP DDNS server (``kea-dhcp-ddns``).

   ctrl_agent
      Control Agent (``kea-ctrl-agent``).

   netconf
      Netconf agent (``kea-netconf``).

   all
      All servers (default) including Netconf if it was configured to be
      built.

``-v|--version``
   Prints keactrl version and quits.

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

The Kea project website is available at: https://kea.isc.org.

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

SEE ALSO
========

kea-dhcp4 8, kea-dhcp6 8, kea-dhcp-ddns 8, kea-ctrl-agent 8, kea-netconf
8, kea-admin 8, kea-netconf 8, perfdhcp 8, kea-lfc 8, Kea
Administrator's Guide.
