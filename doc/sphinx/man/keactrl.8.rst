..
   Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.


keactrl - Shell script for managing Kea
---------------------------------------

Synopsis
~~~~~~~~

:program:`keactrl` [**command**] [**-c** keactrl-config-file] [**-s** server[,server,...]] [**-v**]

Description
~~~~~~~~~~~

``keactrl`` is a shell script which controls the startup, shutdown, and
reconfiguration of the Kea servers (``kea-dhcp4``, ``kea-dhcp6``,
``kea-dhcp-ddns``, ``kea-ctrl-agent``, and ``kea-netconf``). It also
provides the means for checking the current status of the servers and
determining the configuration files in use.

Configuration File
~~~~~~~~~~~~~~~~~~

Depending on the user's requirements, not all of the available servers need be run.
The ``keactrl`` configuration file specifies which servers are enabled and which
are disabled. By default the configuration file is
``[kea-install-dir]/etc/kea/keactrl.conf``.

See the Kea Administrator Reference Manual for documentation of the
parameters in the ``keactrl`` configuration file.

Options
~~~~~~~

``command``
   Specifies the command to be issued to the servers. It can be one of the following:

   **start**
      Starts the servers.

   **stop**
      Stops the servers.

   **reload**
      Instructs the servers to re-read the Kea configuration file. This
      command is not supported by the Netconf agent.

   **status**
      Prints the status of the servers.

``-c|--ctrl-config keactrl-config-file``
   Specifies the ``keactrl`` configuration file. Without this switch,
   ``keactrl`` attempts to use the file
   ``[kea-install-dir]/etc/kea/keactrl.conf``.

``-s|--server server[,server,...]``
   Specifies a subset of the enabled servers to which the command should
   be issued. The list of servers should be separated by commas with no
   intervening spaces. Acceptable values are:

   **dhcp4**
      DHCPv4 server (``kea-dhcp4``).

   **dhcp6**
      DHCPv6 server (``kea-dhcp6``).

   **dhcp_ddns**
      DHCP DDNS server (``kea-dhcp-ddns``).

   **ctrl_agent**
      Control Agent (``kea-ctrl-agent``).

   **netconf**
      Netconf agent (``kea-netconf``).

   **all**
      All servers, including Netconf if it was configured to be
      built. This is the default.

``-v|--version``
   Prints the ``keactrl`` version and quits.

Documentation
~~~~~~~~~~~~~

Kea comes with an extensive Kea Administrator Reference Manual that covers
all aspects of running the Kea software - compilation, installation,
configuration, configuration examples, and much more. Kea also features a
Kea Messages Manual, which lists all possible messages Kea can print
with a brief description for each of them. Both documents are
available in various formats (.txt, .html, .pdf) with the Kea
distribution. The Kea documentation is available at
https://kb.isc.org/docs/kea-administrator-reference-manual .

Kea source code is documented in the Kea Developer's Guide. Its online
version is available at https://jenkins.isc.org/job/Kea_doc/doxygen/.

The Kea project website is available at https://kea.isc.org.

Mailing Lists and Support
~~~~~~~~~~~~~~~~~~~~~~~~~

There are two public mailing lists available for the Kea project. **kea-users**
(kea-users at lists.isc.org) is intended for Kea users, while **kea-dev**
(kea-dev at lists.isc.org) is intended for Kea developers, prospective
contributors, and other advanced users. Both lists are available at
https://lists.isc.org. The community provides best-effort support
on both of those lists.

ISC provides professional support for Kea services. See
https://www.isc.org/kea/ for details.

See Also
~~~~~~~~

:manpage:`kea-dhcp4(8)`, :manpage:`kea-dhcp6(8)`, :manpage:`kea-dhcp-ddns(8)`,
:manpage:`kea-ctrl-agent(8)`, :manpage:`kea-admin(8)`, :manpage:`kea-netconf(8)`,
:manpage:`perfdhcp(8)`, :manpage:`kea-lfc(8)`, Kea Administrator Reference Manual.
