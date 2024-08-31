..
   Copyright (C) 2019-2024 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.

.. iscman:: perfdhcp

``perfdhcp`` - DHCP benchmarking tool
-------------------------------------

Synopsis
~~~~~~~~

:program:`perfdhcp` [**-1**] [**-4** | **-6**] [**-A** encapsulation-level] [**-b** base] [**-B**] [**-c**] [**-C** separator] [**-d** drop-time] [**-D** max-drop] [-e lease-type] [**-E** time-offset] [**-f** renew-rate] [**-F** release-rate] [**-g** thread-mode] [**-h**] [**-i**] [**-I** ip-offset] [**-J** remote-address-list-file] [**-l** local-address|interface] [**-L** local-port] [**-M** mac-list-file] [**-n** num-request] [**-N** remote-port] [**-O** random-offset] [**-o** code,hexstring] [**--or** encapsulation-level:code,hexstring] [**-p** test-period] [**-P** preload] [**-r** rate] [**-R** num-clients] [**-s** seed] [**-S** srvid-offset] [**--scenario** name] [**-t** report] [**-T** template-file] [**-u**] [**-v**] [**-W** exit-wait-time] [**-w** script_name] [**-x** diagnostic-selector] [**-X** xid-offset] [server]

Description
~~~~~~~~~~~

``perfdhcp`` is a DHCP benchmarking tool. It provides a way to measure
the performance of DHCP servers by generating large amounts of traffic
from multiple simulated clients. It is able to test both IPv4 and IPv6
servers, and provides statistics concerning response times and the
number of requests that are dropped.

The tool supports two different scenarios, which offer certain behaviors to be tested.
By default (the basic scenario), tests are run using the full four-packet exchange sequence
(DORA for DHCPv4, SARR for DHCPv6). An option is provided to run tests
using the initial two-packet exchange (DO and SA) instead. It is also
possible to configure ``perfdhcp`` to send DHCPv6 RENEW and RELEASE messages
at a specified rate, in parallel with the DHCPv6 four-way exchanges. By
default, if there is no response received with one second, a response is
considered lost and ``perfdhcp`` continues with other transactions.

A second scenario, called avalanche, is selected via ``--scenario avalanche``.
It first sends the number of Discovery or Solicit messages specified by the ``-R`` option; then
a retransmission (with an exponential back-off mechanism) is used for each simulated client, until all requests are
answered. It generates a report when all clients receive their addresses, or when
it is manually stopped. This scenario attempts to replicate a
case where the server is not able to handle the traffic swiftly
enough. Real clients will assume the packet or response was lost
and will retransmit, further increasing DHCP traffic. This is
sometimes called an avalanche effect, thus the scenario name.
Option ``-p`` is ignored in the avalanche scenario.

When running a performance test, ``perfdhcp`` exchanges packets with
the server under test as quickly as possible, unless the ``-r`` parameter is used to
limit the request rate. The length of the test can be limited by setting
a threshold on any or all of the number of requests made by
``perfdhcp``, the elapsed time, or the number of requests dropped by the
server.

Templates
~~~~~~~~~

To allow the contents of packets sent to the server to be customized,
``perfdhcp`` allows the specification of template files that determine
the contents of the packets. For example, the customized packet may
contain a DHCPv6 ORO to request a set of options to be returned by the
server, or it may contain the Client FQDN option to request that the server
perform DNS updates. This may be used to discover performance
bottlenecks for different server configurations (e.g. DDNS enabled or
disabled).

Up to two template files can be specified on the command line, with each file
representing the contents of a particular type of packet, and the type being
determined by the test being carried out. For example, if testing
DHCPv6:

-  With no template files specified on the command line, ``perfdhcp``
   generates both Solicit and Request packets.

-  With one template file specified, that file is used as the
   pattern for Solicit packets: ``perfdhcp`` generates the Request
   packets.

-  With two template files given on the command line, the first is
   used as the pattern for Solicit packets, and the second as the pattern
   for Request packets.

(A similar determination applies to DHCPv4's DHCPDISCOVER and DHCPREQUEST
packets.)

The template file holds the DHCP packet, represented as a stream of ASCII
hexadecimal digits; it excludes any IP/UDP stack headers. The
template file must not contain any characters other than hexadecimal
digits and spaces. Spaces are discarded when the template file is parsed;
in the file, ``12B4`` is the same as ``12 B4``, which is the same as
``1 2 B 4``.

The template files should be used in conjunction with the command-line
parameters which specify offsets of the data fields being modified in
outbound packets. For example, the ``-E time-offset`` switch specifies
the offset of the DHCPv6 Elapsed Time option in the packet template.
If the offset is specified, ``perfdhcp`` injects the current elapsed-time
value into this field before sending the packet to the server.

In many scenarios, ``perfdhcp`` needs to simulate multiple clients,
each having a unique client identifier. Since packets for each client are
generated from the same template file, it is necessary to randomize the
client identifier (or HW address in DHCPv4) in the packet created from
it. The ``-O random-offset`` option allows specification of the offset in
the template where randomization should be performed. It is important to
note that this offset points to the end (not the beginning) of the
client identifier (or HW address field). The number of bytes being
randomized depends on the number of simulated clients. If the number of
simulated clients is between 1 and 255, only one byte (to which the
randomization offset points) is randomized. If the number of
simulated clients is between 256 and 65535, two bytes are
randomized. Note that the last two bytes of the client identifier are
randomized in this case: the byte which the randomization offset parameter
points to, and the one which precedes it (random-offset - 1). If the
number of simulated clients exceeds 65535, three bytes are
randomized, and so on.

``perfdhcp`` can simulate traffic from multiple subnets by enabling option
``-J`` and passing a path to a file that contains v4 or v6 addresses to be
used as relays in generated messages. That enables testing of vast numbers
of Kea shared networks. While testing DHCPv4, Kea should be started with the
``KEA_TEST_SEND_RESPONSES_TO_SOURCE`` environment variable, to force Kea
to send generated messages to the source address of the incoming packet.

Templates may currently be used to generate packets being sent to the
server in 4-way exchanges, i.e. Solicit, Request (DHCPv6) and DHCPDISCOVER,
DHCPREQUEST (DHCPv4). They cannot be used when Renew or DHCPRELEASE packets are
being sent.

Options
~~~~~~~

``-1``
   Takes the ``server-id`` option from the first received message.

``-4``
   Establishes DHCPv4 operation; this is the default. It is incompatible with the
   ``-6`` option.

``-6``
   Establishes DHCPv6 operation. It is incompatible with the ``-4`` option.

``-b basetype=value``
   Indicates the base MAC or DUID used to simulate different clients. The basetype
   may be "mac" or "duid". (The keyword "ether" may alternatively used
   for MAC.) The ``-b`` option can be specified multiple times. The MAC
   address must consist of six octets separated by single (:) or double
   (::) colons; for example: mac=00:0c:01:02:03:04. The DUID value is a
   hexadecimal string; it must be at least six octets long and not
   longer than 64 bytes, and the length must be less than 128
   hexadecimal digits. For example: duid=0101010101010101010110111F14.

``-d drop-time``
   Specifies the time after which a request is treated as having been
   lost. The value is given in seconds and may contain a fractional
   component. The default is 1.

``-e lease-type``
   Specifies the type of lease being requested from the server. It may
   be one of the following:

   ``address-only``
      Only regular addresses (v4 or v6) are requested.

   ``prefix-only``
      Only IPv6 prefixes are requested.

   ``address-and-prefix``
      Both IPv6 addresses and prefixes are requested.

   The ``-e prefix-only`` and ``-e address-and-prefix`` forms may not be used
   with the ``-4`` option.

``-F release-rate``
   Specifies the rate at which DHCPv4 DHCPRELEASE or DHCPv6 Release requests are sent to a server. This value
   is only valid when used in conjunction with the exchange rate (given
   by ``-r rate``). Furthermore, the sum of this value and the renew-rate
   (given by ``-f rate``) must be equal to or less than the exchange
   rate value.

``-f renew-rate``
   Specifies the rate at which DHCPv4 DHCPREQUEST or DHCPv6 Renew requests are sent to a server.
   This value is only valid when used in conjunction with the exchange
   rate (given by ``-r rate``). Furthermore, the sum of this value and
   the release-rate (given by ``-F rate``) must be equal to or less than the
   exchange rate.

``-g thread-mode``
   Allows selection of thread-mode, which can be either ``single`` or ``multi``. In multi-thread mode,
   packets are received in a separate thread, which allows better
   utilisation of CPUs. In a single-CPU system it is better to run in one
   thread, to avoid threads blocking each other. If more than one CPU is
   present in the system, multi-thread mode is the default; otherwise
   single-thread is the default.

``-h``
   Prints help and exits.

``-i``
   Performs only the initial part of the exchange: DISCOVER-OFFER if ``-4`` is
   selected, Solicit-Advertise if ``-6`` is chosen.

   ``-i`` is incompatible with the following options: ``-1``, ``-d``,
   ``-D``, ``-E``, ``-S``, ``-I`` and ``-F``. In addition, it cannot be
   used with multiple instances of ``-O``, ``-T``, and ``-X``.

``-J remote-address-list-file``
    Specifies a text file that includes multiple addresses, and is
    designed to test shared networks. If provided, ``perfdhcp``
    randomly chooses one of the addresses for each exchange, to generate traffic
    from multiple subnets. When testing DHCPv4, it
    should be started with the ``KEA_TEST_SEND_RESPONSES_TO_SOURCE=ENABLE``
    environment variable; otherwise, ``perfdhcp`` will not be able to receive responses.

``-l local-addr|interface``
   For DHCPv4 operation, specifies the local hostname/address to use when
   communicating with the server. By default, the interface address
   through which traffic would normally be routed to the server is used.
   For DHCPv6 operation, specifies the name of the network interface
   through which exchanges are initiated.

``-L local-port``
   Specifies the local port to use. This must be zero or a positive
   integer up to 65535. A value of 0 (the default) allows ``perfdhcp``
   to choose its own port.

``-M mac-list-file``
   Specifies a text file containing a list of MAC addresses, one per line. If
   provided, a MAC address is chosen randomly from this list for
   every new exchange. In DHCPv6, MAC addresses are used to
   generate DUID-LLs. This parameter must not be used in conjunction
   with the ``-b`` parameter.

``-N remote-port``
   Specifies the remote port to use. This must be zero or a positive
   integer up to 65535. A value of 0 (the default) allows ``perfdhcp``
   to choose the standard service port.

``-o code,hexstring``
   Forces ``perfdhcp`` to insert the specified extra option (or options if
   used multiple times) into packets being transmitted. The code
   specifies the option code, and the hexstring is a hexadecimal string that
   defines the content of the option. Care should be taken, as ``perfdhcp``
   does not offer any kind of logic behind the options; they are simply
   inserted into packets and sent as is. Be careful not to duplicate
   options that are already inserted. For example, to insert the
   client-class identifier (option code 60) with the string "docsis", use
   ``-o 60,646f63736973``. The ``-o`` may be used multiple times. The protocol
   family (``-4`` or ``-6``) must be specified before using ``-o``.

``-P preload``
   Initiates preload exchanges back-to-back at startup. Must be 0
   (the default) or a positive integer.

``-r rate``
   Initiates the rate of DORA/SARR (or if ``-i`` is given, DO/SA) exchanges per
   second. A periodic report is generated showing the number of
   exchanges which were not completed, as well as the average response
   latency. The program continues until interrupted, at which point a
   final report is generated.

``-R num-clients``
   Specifies how many different clients are used. With a value of 1 (the
   default), all requests appear to come from the same client.
   Must be a positive number.

``-s seed``
   Specifies the seed for randomization, making runs of ``perfdhcp``
   repeatable. This must be 0 or a positive integer. The value 0 means that a
   seed is not used; this is the default.

``--scenario name``
   Specifies the type of scenario, and can be ``basic`` (the default) or ``avalanche``.

``-T template-file``
   Specifies a file containing the template to use as a stream of
   hexadecimal digits. This may be specified up to two times and
   controls the contents of the packets sent (see the "Templates"
   section above).

``-u``
   Enables checks for address uniqueness. The lease valid-lifetime should not be shorter
   than the test duration, and clients should not request an address more than once without
   releasing it.

``-v``
   Displays the Kea version.

``-V``
   Displays the extended Kea version.

``-W exit-wait-time``
   Specifies the exit-wait-time parameter, which causes ``perfdhcp`` to wait for
   a certain amount of time after an exit condition has been met, to receive all
   packets without sending any new packets. Expressed in microseconds.
   If not specified, 0 is used (i.e. exit immediately after exit
   conditions are met).

``-w script_name``
   Specifies the name of the script to be run before/after ``perfdhcp``.
   When called, the script is passed a single parameter, either "start" or
   "stop", indicating whether it is being called before or after ``perfdhcp``.

``-x diagnostic-selector``
   Includes extended diagnostics in the output. This is a
   string of single keywords specifying the operations for which verbose
   output is desired. The selector key letters are:

   ``a``
      Prints the decoded command-line arguments.

   ``e``
      Prints the exit reason.

   ``i``
      Prints the rate-processing details.

   ``l``
      Prints the received leases.

   ``s``
      Prints the first server ID.

   ``t``
      When finished, prints timers of all successful exchanges.

   ``T``
      When finished, prints templates.

``-Y seconds``
   Time in seconds after which ``perfdhcp`` starts simulating the client waiting longer for server responses. This increases the
   ``secs`` field in DHCPv4 and sends increased values in the ``Elapsed Time`` option in DHCPv6. Must be used with ``-y``.

``-y seconds``
   Time in seconds during which ``perfdhcp`` simulates the client waiting longer for server responses. This increases
   the ``secs`` field in DHCPv4 and sends increased values in the ``Elapsed Time`` option in DHCPv6. Must be used with ``-Y``.

DHCPv4-Only Options
~~~~~~~~~~~~~~~~~~~

The following options only apply for DHCPv4 (i.e. when ``-4`` is given).

``-B``
   Forces broadcast handling.

DHCPv6-Only Options
~~~~~~~~~~~~~~~~~~~

The following options only apply for DHCPv6 (i.e. when ``-6`` is given).

``-c``
   Adds a rapid-commit option (exchanges are Solicit-Advertise).

``-A encapsulation-level``
   Specifies that relayed traffic must be generated. The argument
   specifies the level of encapsulation, i.e. how many relay agents are
   simulated. Currently the only supported encapsulation-level value is
   1, which means that the generated traffic is equivalent to the amount of
   traffic passing through a single relay agent.

``--or encapsulation-level:code,hexstring``
   Forces ``perfdhcp`` to insert the specified extra option (or options if
   used multiple times) into a relayed DHCPv6 message at the given level of
   encapsulation; currently, the only supported encapsulation-level value is 1.
   This option is very similar to ``-o``: the code
   specifies the option code, and the hexstring is a hexadecimal string that
   defines the content of the option. Care should be taken, as ``perfdhcp``
   does not offer any kind of logic behind the options; they are simply
   inserted into packets and sent as is. ``encapsulation-level:``
   is optional; if it is omitted, the default encapsulation-level value 1 is used.
   For example, to insert the Subscriber identifier (option code 38) with a
   value 1234 at the first level of encapsulation, use ``--or 38,31323334``
   or ``--or 1:38,31323334``. The ``--or`` may be used multiple times, and
   it must be used in conjunction with ``-A``.

Template-Related Options
~~~~~~~~~~~~~~~~~~~~~~~~

The following options may only be used in conjunction with ``-T`` and
control how ``perfdhcp`` modifies the template. The options may be
specified multiple times on the command line; each occurrence affects
the corresponding template file (see "Templates" above).

``-E time-offset``
   Specifies the offset of the ``secs`` field (DHCPv4) or ``Elapsed Time`` option (DHCPv6) in the
   second (i.e. Request) template; must be 0 or a positive integer. A
   value of 0 disables this.

``-I ip-offset``
   Specifies the offset of the IP address (DHCPv4) in the ``requested-ip``
   option or ``IA_NA`` option (DHCPv6) in the second (Request) template.

``-O random-offset``
   Specifies the offset of the last octet to randomize in the template. This
   must be an integer greater than 3. The ``-T`` switch must be given to
   use this option.

``-S srvid-offset``
   Specifies the offset of the ``server-id`` option in the second (Request) template.
   This must be a positive integer, and the switch can only be used
   when the template option (``-T``) is also given.

``-X xid-offset``
   Specifies the offset of the transaction ID (xid) in the template. This must be a
   positive integer, and the switch can only be used when the template
   option (``-T``) is also given.

Options Controlling a Test
~~~~~~~~~~~~~~~~~~~~~~~~~~

``-D max-drop``
   Aborts the test immediately if "max-drop" requests have been dropped.
   Use ``-D 1`` to abort if even a single request has
   been dropped. "max-drop" must be a positive integer. If "max-drop"
   includes the suffix ``%``, it specifies the maximum percentage of
   requests that may be dropped before aborting. In this case, testing of
   the threshold begins after 10 requests are expected to have been
   received.

``-n num-requests``
   Initiates "num-request" transactions. No report is generated until all
   transactions have been initiated/waited-for, after which a report is
   generated and the program terminates.

``-p test-period``
   Sends requests for "test-period", which is specified in the same manner
   as ``-d``. This can be used as an alternative to ``-n``, or both
   options can be given, in which case the testing is completed when
   either limit is reached.

``-t interval``
   Sets the delay (in seconds) between two successive reports.

``-C separator``
   Suppresses the preliminary output and causes the interim data to
   only contain the values delimited by ``separator``. Used in
   conjunction with ``-t`` to produce easily parsable
   reports at ``-t`` intervals.

Arguments
~~~~~~~~~

``server``
   Indicates the server to test, specified as an IP address. In the DHCPv6 case, the
   special name ``all`` can be used to refer to
   ``All_DHCP_Relay_Agents_and_Servers`` (the multicast address FF02::1:2),
   or the special name ``servers`` to refer to ``All_DHCP_Servers`` (the
   multicast address FF05::1:3). The server is mandatory except where
   the ``-l`` option is given to specify an interface, in which case it
   defaults to ``all``.

Errors
~~~~~~

``perfdhcp`` can report the following errors in the packet exchange:

tooshort
   A message was received that was too short.

orphans
   A message was received which does not match one sent to the server (i.e.
   it is a duplicate message, a message that has arrived after an
   excessive delay, or one that is just not recognized).

locallimit
   Local system limits have been reached when sending a message.

Exit Status
~~~~~~~~~~~

``perfdhcp`` exits with one of the following status codes:

0
   Success.

1
   General error.

2
   Error in command-line arguments.

3
   No general failures in operation, but one or more exchanges were
   unsuccessful.

Usage Examples
~~~~~~~~~~~~~~

Here is an example that simulates regular DHCPv4 traffic of 100 DHCPv4 devices (-R 100),
10 packets per second (-r 10), shows the query/response rate details (-xi),
shows a report every 2 seconds (-t 2), and sends the packets to the IP 192.0.2.1:

.. code-block:: console

   sudo perfdhcp -xi -t 2 -r 10 -R 100 192.0.2.1

Here's a similar case, but for DHCPv6. Note that the DHCPv6 protocol uses link-local
addresses, so the interface (eth0 in this example) must be specified on which to send the
traffic. ``all`` is a convenience alias for ``All_DHCP_Relay_Agents_and_Servers``
(the multicast address FF02::1:2). It is also possible to use the ``servers`` alias
to refer to ``All_DHCP_Servers`` (the multicast address FF05::1:3). The default is ``all``.

.. code-block:: console

   sudo perfdhcp -6 -xi -t 1 -r 1 -R 10 -l eth0 all

The following examples simulate normal DHCPv4 and DHCPv6 traffic that, after 3 seconds,
starts pretending not to receive any responses from the server for 10 seconds. The
DHCPv4 protocol signals this by an increased ``secs`` field, while DHCPv6 uses the
``Elapsed Time`` option. In real networks, this indicates that clients are not getting
responses in a timely matter. This can be used to simulate some HA scenarios, as Kea
uses the ``secs`` field and ``Elapsed Time`` option value as one of the indicators
that the HA partner is not responding. When enabled with ``-y`` and ``-Y``, the ``secs``
and ``Elapsed Time`` values increase steadily.

.. code-block:: console

   sudo perfdhcp -xi -t 1 -r 1 -y 10 -Y 3 192.0.2.1

   sudo perfdhcp -6 -xi -t 1 -r 1 -y 10 -Y 3 2001:db8::1

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

The ``perfdhcp`` tool was initially coded in October 2011 by John
DuBois, Francis Dupont, and Marcin Siodelski of ISC. Kea 1.0.0, which
included ``perfdhcp``, was released in December 2015.

See Also
~~~~~~~~

:manpage:`kea-dhcp4(8)`, :manpage:`kea-dhcp6(8)`, :manpage:`kea-dhcp-ddns(8)`,
:manpage:`kea-ctrl-agent(8)`, :manpage:`kea-admin(8)`, :manpage:`kea-netconf(8)`,
:manpage:`keactrl(8)`, :manpage:`kea-lfc(8)`, Kea Administrator Reference Manual.
