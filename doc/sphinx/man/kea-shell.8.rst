..
   Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.


``kea-shell`` - Text client for Control Agent process
-----------------------------------------------------

Synopsis
~~~~~~~~

:program:`kea-shell` [**-h**] [**-v**] [**--host**] [**--port**] [**--path**] [**--ca**] [**--cert**] [**--key**] [**--auth-user**] [**--auth-password**] [**--timeout**] [**--service**] [command]

Description
~~~~~~~~~~~

The ``kea-shell`` provides a REST client for the Kea Control Agent (CA).
It takes commands as a command-line parameter that is sent to the CA
with proper JSON encapsulation. Optional arguments may be specified on
the standard input. The request is sent via HTTP and a response is
retrieved, displayed on the standard output. Basic HTTP authentication
and HTTPS, i.e. TLS transport, are supported.


Arguments
~~~~~~~~~

The arguments are as follows:

``-h``
   Displays help regarding command-line parameters.

``-v``
   Displays the version.

``--host``
   Specifies the host to connect to. The Control Agent must be running at the
   specified host. If not specified, 127.0.0.1 is used.

``--port``
   Specifies the TCP port to connect to. Control Agent must be listening
   at the specified port. If not specified, 8000 is used.

``--path``
   Specifies the path in the URL to connect to. If not specified, an empty
   path is used. As Control Agent listens at the empty path, this
   parameter is useful only with a reverse proxy.

``--ca``
   Specifies the file or directory name of the Certification Authority.
   If not specified, HTTPS is not used.

``--cert``
   Specifies the file name of the user end-entity public key certificate.
   If specified, the file name of the user key must also be specified.

``--key``
   Specifies the file name of the user key file. If specified, the file
   name of the user certificate must also be specified.
   Encrypted key files are not supported.

``--auth-user``
   Specifies the user ID for basic HTTP authentication. If not specified,
   or specified as the empty string, authentication is not used.

``--auth-password``
   Specifies the password for basic HTTP authentication. If not specified
   but the user ID is specified, an empty password is used.

``--timeout``
   Specifies the connection timeout, in seconds. The default is 10.

``--service``
   Specifies the service that is the target of a command. If not
   specified, the Control Agent itself is targeted. May be used more than once
   to specify multiple targets.

``command``
   Specifies the command to be sent to the CA. If not specified,
   ``list-commands`` is used.

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

The ``kea-shell`` was first coded in March 2017 by Tomek Mrugalski.

See Also
~~~~~~~~

:manpage:`kea-dhcp4(8)`, :manpage:`kea-dhcp6(8)`, :manpage:`kea-dhcp-ddns(8)`,
:manpage:`kea-ctrl-agent(8)`, :manpage:`kea-admin(8)`, :manpage:`keactrl(8)`,
:manpage:`perfdhcp(8)`, :manpage:`kea-lfc(8)`, Kea Administrator Reference Manual.
