..
   Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.


``kea-ctrl-agent`` - Control Agent process in Kea
-------------------------------------------------

Synopsis
~~~~~~~~

:program:`kea-ctrl-agent` [**-v**] [**-V**] [**-W**] [**-d**] [**-c** config-file] [**-t** config-file]

Description
~~~~~~~~~~~

The ``kea-ctrl-agent`` provides a REST service for controlling Kea
services. The received HTTP requests are decapsulated and forwarded to
the respective Kea services in JSON format. Received JSON responses are
encapsulated within HTTP responses and returned to the controlling
entity. Some commands may be handled by the Control Agent directly, and
not forwarded to any Kea service.

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
   Sets the logging level to debug with extra verbosity. This is primarily for
   development purposes in stand-alone mode.

``-c config-file``
   Specifies the file with the configuration for the Control Agent
   server. It may also contain configuration entries for other Kea
   services.

``-t config-file``
   Checks the syntax of the configuration file and reports the first error,
   if any. Note that not all parameters are completely checked; in
   particular, service and client sockets are not opened, and hook
   libraries are not loaded.

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

Kea source code is documented in the Kea Developer's Guide,
available at https://reports.kea.isc.org/dev_guide/.

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

The ``kea-ctrl-agent`` was first coded in December 2016 by Marcin
Siodelski.

See Also
~~~~~~~~

:manpage:`kea-dhcp4(8)`, :manpage:`kea-dhcp6(8)`,
:manpage:`kea-dhcp-ddns(8)`, :manpage:`kea-admin(8)`, :manpage:`keactrl(8)`,
:manpage:`perfdhcp(8)`, :manpage:`kea-lfc(8)`, Kea Administrator Reference Manual.
