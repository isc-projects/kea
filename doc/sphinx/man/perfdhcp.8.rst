..
   Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.


perfdhcp - DHCP benchmarking tool
---------------------------------

Synopsis
~~~~~~~~

:program:`perfdhcp` [**-1**] [**-4**|**-6**] [**-A** encapsulation-level] [**-b** base] [**-B**] [**-c**] [**-d** drop-time] [**-D** max-drop] [-e lease-type] [**-E** time-offset] [**-f** renew-rate] [**-F** release-rate] [**-g** thread-mode] [**-h**] [**-i**] [**-I** ip-offset] [**-l** local-address|interface] [**-L** local-port] [**-M** mac-list-file] [**-n** num-request] [**-N** remote-port] [**-O** random-offset] [**-o** code,hexstring] [**-p** test-period] [**-P** preload] [**-r** rate] [**-R** num-clients] [**-s** seed] [**-S** srvid-offset] [**--scenario** name] [**-t** report] [**-T** template-file] [**-v**] [**-W** exit-wait-time] [**-w** script_name] [**-x** diagnostic-selector] [**-X** xid-offset] [server]

Description
~~~~~~~~~~~

``perfdhcp`` is a DHCP benchmarking tool. It provides a way of measuring
the performance of DHCP servers by generating large amounts of traffic
from simulated multiple clients. It is able to test both IPv4 and IPv6
servers, and provides statistics concerning response times and the
number of requests that are dropped.

The tool supports scenarios, which offer certain behaviours.
By default (basic scenario) tests are run using the full four-packet exchange sequence
(DORA for DHCPv4, SARR for DHCPv6). An option is provided to run tests
using the initial two-packet exchange (DO and SA) instead. It is also
possible to configure ``perfdhcp`` to send DHCPv6 RENEW and RELEASE messages
at a specified rate in parallel with the DHCPv6 four-way exchanges. By
default, if there is no response received with 1 second, a response is
considered lost and perfdhcp continues with other transactions.

Second scenario is called avalanche, which is selected by ``--scenario avalanche``.
It first sends as many Discovery or Solicit messages as request in -R option then
a retransmission (with exponential back off mechanism) is used for each simulated client until all requests are
answered. It will generate report when all clients get their addresses or when
it will be manually stopped. This scenario attempts to replicate a
case where the server is not able to handle the traffic swiftly
enough. Real clients will assume the packet or the response was lost
and will retransmit, further increasing DHCP traffic. This is
sometimes called avalanche effect, thus the scenario name.
Option ``-p`` is ignored in avalanche scenario.

When running a performance test, ``perfdhcp`` will exchange packets with
the server under test as fast as possible unless the ``-r`` parameter is used to
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

Up to two template files can be specified on the command line, each file
representing the contents of a particular type of packet, the type being
determined by the test being carried out. For example, if testing
DHCPv6:

-  With no template files specified on the command line, ``perfdhcp``
   will generate both SOLICIT and REQUEST packets.

-  With one template file specified, that file will be used as the
   pattern for SOLICIT packets: ``perfdhcp`` will generate the REQUEST
   packets.

-  With two template files given on the command line, the first will be
   used as the pattern for SOLICIT packets, the second as the pattern
   for REQUEST packets.

(Similar determination applies to DHCPv4's DISCOVER and REQUEST
packets.)

The template file holds the DHCP packet represented as a stream of ASCII
hexadecimal digits and it excludes any IP/UDP stack headers. The
template file must not contain any characters other than hexadecimal
digits and spaces. Spaces are discarded when the template file is parsed;
in the file, '12B4' is the same as '12 B4' which is the same as '1 2
B 4'.

The template files should be used in conjunction with the command-line
parameters which specify offsets of the data fields being modified in
outbound packets. For example, the ``-E time-offset`` switch specifies
the offset of the DHCPv6 Elapsed Time option in the packet template.
If the offset is specified, ``perfdhcp`` will inject the current elapsed-time
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
randomization offset points) will be randomized. If the number of
simulated clients is between 256 and 65535, two bytes will be
randomized. Note that the last two bytes of the client identifier will be
randomized in this case: the byte which the randomization offset parameter
points to, and the one which precedes it (random-offset - 1). If the
number of simulated clients exceeds 65535, three bytes will be
randomized, and so on.

Templates may currently be used to generate packets being sent to the
server in 4-way exchanges, i.e. SOLICIT, REQUEST (DHCPv6) and DISCOVER,
REQUEST (DHCPv4). They cannot be used when RENEW or RELEASE packets are
being sent.

Options
~~~~~~~

``-1``
   Takes the server-ID option from the first received message.

``-4``
   Establishes DHCPv4 operation; this is the default. It is incompatible with the
   ``-6`` option.

``-6``
   Establishes DHCPv6 operation. This is incompatible with the ``-4`` option.

``-b basetype=value``
   Indicates the base MAC or DUID used to simulate different clients. The basetype
   may be "mac" or "duid". (The keyword "ether" may alternatively used
   for MAC.) The ``-b`` option can be specified multiple times. The MAC
   address must consist of six octets separated by single (:) or double
   (::) colons, for example: mac=00:0c:01:02:03:04. The DUID value is a
   hexadecimal string; it must be at least six octets long and not
   longer than 64 bytes, and the length must be less than 128
   hexadecimal digits, for example: duid=0101010101010101010110111F14.

``-d drop-time``
   Specifies the time after which a request is treated as having been
   lost. The value is given in seconds and may contain a fractional
   component. The default is 1 second.

``-e lease-type``
   Specifies the type of lease being requested from the server. It may
   be one of the following:

   **address-only**
      Only regular addresses (v4 or v6) will be requested.

   **prefix-only**
      Only IPv6 prefixes will be requested.

   **address-and-prefix**
      Both IPv6 addresses and prefixes will be requested.

   The ``-e prefix-only`` and ``-e address-and-prefix`` forms may not be used
   with the ``-4`` option.

``-f renew-rate``
   Specifies the rate at which DHCPv4 or DHCPv6 renew requests are sent to a server.
   This value is only valid when used in conjunction with the exchange
   rate (given by ``-r rate``). Furthermore, the sum of this value and
   the release-rate (given by ``-F rate``) must be equal to or less than the
   exchange rate.

``-g thread-mode``
   Allows selection of thread-mode, which can be either 'single' or 'multi'. In multi-thread mode
   packets are received in a separate thread, which allows better
   utilisation of CPUs. In a single-CPU system it is better to run in one
   thread to avoid threads blocking each other. If more than one CPU is
   present in the system, multi-thread mode is the default; otherwise
   single-thread is the default.

``-h``
   Prints help and exits.

``-i``
   Performs only the initial part of the exchange: DISCOVER-OFFER if ``-4`` is
   selected, SOLICIT-ADVERTISE if ``-6`` is chosen.

   ``-i`` is incompatible with the following options: ``-1``, ``-d``,
   ``-D``, ``-E``, ``-S``, ``-I`` and ``-F``. In addition, it cannot be
   used with multiple instances of ``-O``, ``-T`` and ``-X``.

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
   provided, a MAC address will be chosen randomly from this list for
   every new exchange. In DHCPv6, MAC addresses are used to
   generate DUID-LLs. This parameter must not be used in conjunction
   with the -b parameter.

``-N remote-port``
   Specifies the remote port to use. This must be zero or a positive
   integer up to 65535. A value of 0 (the default) allows ``perfdhcp``
   to choose the standard service port.

``-o code,hexstring``
   Forces ``perfdhcp`` to insert the specified extra option (or options if
   used several times) into packets being transmitted. The code
   specifies the option code and the hexstring is a hexadecimal string that
   defines the content of the option. Care should be taken as ``perfdhcp``
   does not offer any kind of logic behind those options; they are simply
   inserted into packets and sent as is. Be careful not to duplicate
   options that are already inserted. For example, to insert client
   class identifier (option code 60) with a string 'docsis', use
   -o 60,646f63736973. The ``-o`` may be used multiple times. It is
   necessary to specify the protocol family (either ``-4`` or ``-6``) before
   using ``-o``.

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
   default), all requests seem to come from the same client.
   Must be a positive number.

``-s seed``
   Specifies the seed for randomization, making runs of ``perfdhcp``
   repeatable. This must be 0 or a positive integer. The value 0 means that a
   seed is not used; this is the default.

``--scenario name``
   Specifies type of the scenario, can be **basic** (default) or **avalanche**.

``-T template-file``
   Specifies a file containing the template to use as a stream of
   hexadecimal digits. This may be specified up to two times and
   controls the contents of the packets sent (see the "Templates"
   section above).

``-v``
   Prints the version of this program.

``-W exit-wait-time``
   Specifies the exit-wait-time parameter, which causes ``perfdhcp`` to wait for
   exit-wait-time after an exit condition has been met, to receive all
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

   **a**
      Prints the decoded command line arguments.

   **e**
      Prints the exit reason.

   **i**
      Prints the rate processing details.

   **s**
      Prints the first server-ID.

   **t**
      When finished, prints timers of all successful exchanges.

   **T**
      When finished, prints templates.

DHCPv4-Only Options
~~~~~~~~~~~~~~~~~~~

The following options only apply for DHCPv4 (i.e. when ``-4`` is given).

``-B``
   Forces broadcast handling.

DHCPv6-Only Options
~~~~~~~~~~~~~~~~~~~

The following options only apply for DHCPv6 (i.e. when ``-6`` is given).

``-c``
   Adds a rapid-commit option (exchanges will be SOLICIT-ADVERTISE).

``-F release-rate``
   Specifies the rate at which IPv6 RELEASE requests are sent to a server. This value
   is only valid when used in conjunction with the exchange rate (given
   by ``-r rate``). Furthermore, the sum of this value and the renew-rate
   (given by ``-f rate``) must be equal to or less than the exchange
   rate value.

``-A encapsulation-level``
   Specifies that relayed traffic must be generated. The argument
   specifies the level of encapsulation, i.e. how many relay agents are
   simulated. Currently the only supported encapsulation-level value is
   1, which means that the generated traffic is equivalent to the amount of
   traffic passing through a single relay agent.

Template-Related Options
~~~~~~~~~~~~~~~~~~~~~~~~

The following options may only be used in conjunction with ``-T`` and
control how ``perfdhcp`` modifies the template. The options may be
specified multiple times on the command line; each occurrence affects
the corresponding template file (see "Templates" above).

``-E time-offset``
   Specifies the offset of the secs field (DHCPv4) or elapsed-time option (DHCPv6) in the
   second (i.e. REQUEST) template; must be 0 or a positive integer. A
   value of 0 disables this.

``-I ip-offset``
   Specifies the offset of the IP address (DHCPv4) in the requested-IP
   option or IA_NA option (DHCPv6) in the second (REQUEST) template.

``-O random-offset``
   Specifies the offset of the last octet to randomize in the template. This
   must be an integer greater than 3. The ``-T`` switch must be given to
   use this option.

``-S srvid-offset``
   Specifies the offset of the server-ID option in the second (REQUEST) template.
   This must be a positive integer, and the switch can only be used
   when the template option (``-T``) is also given.

``-X xid-offset``
   Specifies the offset of the transaction ID (xid) in the template. This must be a
   positive integer, and the switch can only be used when the template
   option (``-T``) is also given.

Options Controlling a Test
~~~~~~~~~~~~~~~~~~~~~~~~~~

``-D max-drop``
   Aborts the test immediately if **max-drop** requests have been dropped.
   Use ``-D 0`` to abort if even a single request has
   been dropped. **max-drop** must be a positive integer. If **max-drop**
   includes the suffix '%', it specifies a maximum percentage of
   requests that may be dropped before abort. In this case, testing of
   the threshold begins after 10 requests have been expected to be
   received.

``-n num-requests``
   Initiates **num-request** transactions. No report is generated until all
   transactions have been initiated/waited-for, after which a report is
   generated and the program terminates.

``-p test-period``
   Sends requests for **test-period**, which is specified in the same manner
   as ``-d``. This can be used as an alternative to ``-n`` or both
   options can be given, in which case the testing is completed when
   either limit is reached.

``-t interval``
   Sets the delay (in seconds) between two successive reports.

Arguments
~~~~~~~~~

server
   Indicates the server to test, specified as an IP address. In the DHCPv6 case, the
   special name 'all' can be used to refer to
   All_DHCP_Relay_Agents_and_Servers (the multicast address FF02::1:2),
   or the special name 'servers' to refer to All_DHCP_Servers (the
   multicast address FF05::1:3). The server is mandatory except where
   the ``-l`` option is given to specify an interface, in which case it
   defaults to 'all'.

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

``perfdhcp`` can exit with one of the following status codes:

0
   Success.

1
   General error.

2
   Error in command-line arguments.

3
   No general failures in operation, but one or more exchanges were
   unsuccessful.

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
