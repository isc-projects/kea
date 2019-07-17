:orphan:

kea-shell
8
Kea
kea-shell
Text client for Control Agent process
2017-2018
Internet Systems Consortium, Inc. ("ISC")
kea-shell
-h
-v
--host
--port
--path
--timeout
--service
command
DESCRIPTION
===========

The ``kea-shell`` provides a REST client for the Kea Control Agent (CA).
It takes command as a command-line parameter that is being sent to CA
with proper JSON encapsulation. Optional arguments may be specified on
the standard input. The request it sent of HTTP and a response is
retrieved. That response is displayed out on the standard output.

ARGUMENTS
=========

The arguments are as follows:

``-h``
   Displays help regarding command line parameters.

``-v``
   Display the version.

``--host``
   Specifies the host to connect to. Control Agent must be running at
   specified host. If not specified, 127.0.0.1 is used.

``--port``
   Specifies the TCP port to connect to. Control Agent must be listening
   at specified port. If not specified, 8000 is used.

``--path``
   Specifies the path in the URL to connect to. If not specified, empty
   path is used. As Control Agent listens at the empty path this
   parameter is useful only with a reverse proxy.

``--timeout``
   Specifies the connection timeout in seconds. If not specified, 10
   (seconds) is used.

``--service``
   Specifies the service that is the target of a command. If not
   specified, Control Agent will be targeted. May be used more than once
   to specify multiple targets.

``command``
   Specifies the command to be sent to CA. If not specified,
   "list-commands" is used.

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

The ``kea-shell`` was first coded in March 2017 by Tomek Mrugalski.

SEE ALSO
========

kea-ctrl-agent 8, kea-dhcp4 8, kea-dhcp6 8, kea-dhcp-ddns 8, kea-admin
8, keactrl 8, perfdhcp 8, kea-lfc 8, Kea Administrator's Guide.
