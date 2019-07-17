:orphan:

kea-lfc
8
Kea
kea-lfc
Lease File Cleanup process in Kea
2015-2018
Internet Systems Consortium, Inc. ("ISC")
kea-lfc
-4|-6
-c
config-file
-p
pid-file
-x
previous-file
-i
copy-file
-o
output-file
-f
finish-file
-v
-V
-W
-d
-h
DESCRIPTION
===========

The ``kea-lfc`` service process removes redundant information from the
files used to provide persistent storage for the memfile data base
backend. The service is written to run as a stand alone process. While
it can be started externally, there is usually no need to do this. It
will be run on a periodic basis by the Kea DHCP servers.

ARGUMENTS
=========

The arguments are as follows:

``-d``
   Verbose mode sets the logging level to debug. This is primarily for
   development purposes in stand-alone mode.

``-v``
   version causes the version stamp to be printed.

``-V``
   Version causes a longer form of the version stamp to be printed.

``-W``
   Display the configuration report.

``-h``
   Help causes the usage string to be printed.

``-4 | -6``
   The protocol version of the lease files, must be one of 4 or 6.

``-c``
   Configuration file including the configuration for ``kea-lfc``
   process. It may also contain configuration entries for other Kea
   services. Currently ``kea-lfc`` gets all of its arguments from the
   command line, in the future it will be extended to get some arguments
   from the config file.

``-p``
   PID file - When the ``kea-lfc`` process starts it attempts to
   determine if another instance of the process is already running by
   examining the pid file. If one is already running the new process is
   terminated. If one isn't running it writes its pid into the pid file.

``-x``
   Previous or ex lease file - When ``kea-lfc`` starts this is the
   result of any previous run of ``kea-lfc``. When ``kea-lfc`` finishes
   it is the result of this run. If ``kea-lfc`` is interrupted before
   completing, this file may not exist.

``-i``
   Input or copy of lease file - Before the DHCP server invokes
   ``kea-lfc`` it will move the current lease file here and then call
   ``kea-lfc`` with this file.

``-o``
   Output lease file - The temporary file ``kea-lfc`` should use to
   write the leases. Upon completion of writing this this file it will
   be moved to the finish file (see below).

``-f``
   Finish or completion file - Another temporary file ``kea-lfc`` uses
   for bookkeeping. When ``kea-lfc`` completes writing the output file
   it moves it to this file name. After ``kea-lfc`` finishes deleting
   the other files (previous and input) it moves this file to previous
   lease file. By moving the files in this fashion the ``kea-lfc`` and
   the DHCP server processes can determine the correct file to use even
   if one of the processes was interrupted before completing its task.

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

The ``kea-lfc`` process was first coded in January 2015 by the ISC
Kea/DHCP team.

SEE ALSO
========

kea-dhcp4 8, kea-dhcp6 8, kea-dhcp-ddns 8, kea-ctrl-agent 8, kea-admin
8, kea-netconf 8, keactrl 8, perfdhcp 8, Kea Administrator's Guide.
