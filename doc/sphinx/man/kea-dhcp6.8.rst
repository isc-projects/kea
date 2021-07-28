..
   Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.


kea-dhcp6 - DHCPv6 server in Kea
--------------------------------

Synopsis
~~~~~~~~

:program:`kea-dhcp6` [**-v**] [**-V**] [**-W**] [**-d**] [**-c** config-file] [**-t** config-file] [**-p** server-port-number] [**-P** client-port-number]

Description
~~~~~~~~~~~

The ``kea-dhcp6`` daemon provides the DHCPv6 server implementation.

Arguments
~~~~~~~~~

The arguments are as follows:

``-v``
   Displays the version.

``-V``
   Displays the extended version.

``-W``
   Displays the configuration report.

``-d``
   Enables the debug mode with extra verbosity.

``-c config-file``
   Specifies the configuration file with the configuration for the DHCPv6 server. It
   may also contain configuration entries for other Kea services.

``-t config-file``
   Checks the configuration file and reports the first error, if any. Note
   that not all parameters are completely checked; in particular,
   service and control channel sockets are not opened, and hook
   libraries are not loaded.

``-p server-port-number``
   Specifies the server port number (1-65535) on which the server listens. This is
   useful for testing purposes only.

``-P client-port-number``
   Specifies the client port number (1-65535) to which the server responds. This is
   useful for testing purposes only.

Documentation
~~~~~~~~~~~~~

Kea comes with an extensive Kea Administrator Reference Manual that covers
all aspects of running the Kea software - compilation, installation,
configuration, configuration examples, and much more. Kea also features a
Kea Messages Manual, which lists all possible messages Kea can print
with a brief description for each of them. Both documents are
available in various formats (.txt, .html, .pdf) with the Kea
distribution. The Kea documentation is available at
https://kea.readthedocs.io.

Kea source code is documented in the Kea Developer's Guide. Its online
version is available at https://reports.kea.isc.org/dev_guide/.

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

History
~~~~~~~

The ``b10-dhcp6`` daemon was first coded in June 2011 by Tomek
Mrugalski.

Kea became a standalone server and the BIND 10 framework was removed. The
DHCPv6 server binary was renamed to kea-dhcp6 in July 2014.

See Also
~~~~~~~~

:manpage:`kea-dhcp4(8)`, :manpage:`kea-dhcp-ddns(8)`,
:manpage:`kea-ctrl-agent(8)`, :manpage:`kea-admin(8)`, :manpage:`keactrl(8)`,
:manpage:`perfdhcp(8)`, :manpage:`kea-netconf(8)`, :manpage:`kea-lfc(8)`,
Kea Administrator Reference Manual.
