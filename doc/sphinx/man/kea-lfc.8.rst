..
   Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.


``kea-lfc`` - Lease File Cleanup process in Kea
-----------------------------------------------

Synopsis
~~~~~~~~

:program:`kea-lfc` [**-4**|**-6**] [**-c** config-file] [**-p** pid-file] [**-x** previous-file] [**-i** copy-file] [**-o** output-file] [**-f** finish-file] [**-v**] [**-V**] [**-W**] [**-d**] [**-h**]

Description
~~~~~~~~~~~

The ``kea-lfc`` service process removes redundant information from the
files used to provide persistent storage for the memfile database
backend. The service is written to run as a stand-alone process. While
it can be started externally, there is usually no need to do this. It
is run periodically by the Kea DHCP servers.

Arguments
~~~~~~~~~

The arguments are as follows:

``-4 | -6``
   Indicates the protocol version of the lease files; must be either 4 or 6.

``-c config-file``
   Specifies the file with the configuration for the ``kea-lfc``
   process. It may also contain configuration entries for other Kea
   services. Currently ``kea-lfc`` gets all of its arguments from the
   command line.

``-p pid-file``
   Specifies the PID file. When the ``kea-lfc`` process starts, it attempts to
   determine if another instance of the process is already running, by
   examining the PID file. If one is already running, the new process is
   terminated. If one is not running, Kea writes its PID into the PID file.

``-x previous-file``
   Specifies the previous or ex-lease file. When ``kea-lfc`` starts, this is the
   result of any previous run of ``kea-lfc``; when ``kea-lfc`` finishes,
   it is the result of the current run. If ``kea-lfc`` is interrupted before
   completing, this file may not exist.

``-i copy-file``
   Specifies the input or copy of lease file. Before the DHCP server invokes
   ``kea-lfc``, it moves the current lease file here and then calls
   ``kea-lfc`` with this file.

``-o output-file``
   Specifies the output lease file, which is the temporary file ``kea-lfc`` should use to
   write the leases. Once this file is finished writing, it is
   moved to the finish file (see below).

``-f finish-file``
   Specifies the finish or completion file, another temporary file ``kea-lfc`` uses
   for bookkeeping. When ``kea-lfc`` finishes writing the output file,
   it moves it to this file name. After ``kea-lfc`` finishes deleting
   the other files (previous and input), it moves this file to the previous
   lease file. By moving the files in this fashion, the ``kea-lfc`` and
   the DHCP server processes can determine the correct file to use even
   if one of the processes was interrupted before completing its task.

``-v``
   Causes the version stamp to be printed.

``-V``
   Causes a longer form of the version stamp to be printed.

``-W``
   Displays the configuration report.

``-d``
   Sets the logging level to debug with extra verbosity. This is primarily for
   development purposes in stand-alone mode.

``-h``
   Causes the usage string to be printed.

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

The ``kea-lfc`` process was first coded in January 2015 by the ISC
Kea/DHCP team.

See Also
~~~~~~~~

:manpage:`kea-dhcp4(8)`, :manpage:`kea-dhcp6(8)`, :manpage:`kea-dhcp-ddns(8)`,
:manpage:`kea-ctrl-agent(8)`, :manpage:`kea-admin(8)`, :manpage:`keactrl(8)`,
:manpage:`perfdhcp(8)`, :manpage:`kea-netconf(8)`, Kea Administrator Reference Manual.
