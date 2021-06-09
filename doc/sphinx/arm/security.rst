.. _security:

************
Kea Security
************

Kea was designed to be installed into a protected environment in a network datacenter. It was not hardened from a security perspective. However, we have recently added support for basic HTTP authentication and TLS.

.. _tls:

TLS/HTTPS support
=================

Kea versions 1.9.6 and later include TLS support for better security.
TLS is used to secure HTTP communication.  There are three levels of
protection possible:

- no TLS. The connection is plain text, unencrypted HTTP. This is
  the only option available in versions prior to Kea 1.9.6.

- encryption, which protects against passive attacks and
  eavesdropping. In this case the server is authenticated but the client is
  not. This is the typical mode when securing a web site, where
  clients and servers are not under the control of a common entity.

- mutual authentication between the client and the server. This is the
  strictest security mode and is the default when TLS is
  enabled.

.. note::

   TLS mutual authentication is for TLS entities only. When TLS and
   an HTTP authentication scheme are used together, there is no binding between
   the two security mechanisms and therefore no proof that the TLS client and server
   are the same as the HTTP authentication client and server.

.. _tls_config:

Building Kea with TLS/HTTPS support
---------------------------------------

TLS/HTTPS support is available with either the OpenSSL or the Botan
cryptographic libraries. There are some constraints on the boost library
that must be used:

- OpenSSL versions older than 1.0.2 are obsolete and should not be used.
  Kea TLS support was not tested with and is not supported on these versions.

- OpenSSL version 1.0.2 has extended support for OpenSSL premium customers
  so should not be considered except for these premium customers.
  Kea TLS support was tested but is not supported on this version.

- OpenSSL versions >= 1.1.x were tested and are supported. Many
  recent operating system versions include TLS 1.3 support.

- OpenSSL 3.x is not yet released and Kea does not build with it.

- LibreSSL 3.2.4 was tested. LibreSSL shares the OpenSSL 1.0.2 API so
  it should work but is not supported.

- Botan 1.x versions are obsolete and should not be used.
  Kea TLS support was not tested and is not supported with these versions.

- Botan versions >= 2.14.0 were tested and are supported. Note the TLS
  support requires the four asio header files which are included in Botan
  packages / installation only when Botan was configured with the
  ``--with-boost`` option.

  Sadly, many packages provided by operating systems, such as Ubuntu 20.10,
  did not build Botan with boost support, therefore making those packages
  unusable directly for Kea.

  It is still possible to take these files from the corresponding
  Botan distribution and to install them manually in the Botan include
  directory but of course this should be a last resort procedure.

  Note that without these header files or with a Botan version older
  than 2.14.0 Kea can still build but the TLS/HTTPS support is disabled:
  any attempt to use it will fail with a fatal error.

- Very old boost versions provide SSL support (based on OpenSSL)
  without offering a choice of the TLS version: Kea can still use them
  but they are not recommended.

- Boost versions older than 1.64 provide SSL support with a fixed
  choice of the TLS version: Kea enforces the use of TLS 1.2 with them.

- Boost versions 1.64 or newer provide SSL support with a generic
  TLS version: the best (highest) version available on both peers is
  selected.


TLS/HTTPS configuration
-----------------------

The TLS configuration parameters are:

- the ``trust-anchor`` string parameter specifies the name of a file
  or directory where the certification authority (CA) certificate of
  the other peer can be found. With OpenSSL the directory must include
  hash symbolic links. With Botan the directory is recursively
  searched for certificates.

- the ``cert-file`` string parameter specifies the name of the file
  containing the end-entity certificate of the Kea instance
  being configured.

- the ``key-file`` string parameter specifies the private key of the
  end-entity certificate of the Kea instance being configured.
  The file must not be encrypted and it is highly recommended to
  restrict its access.

The three string parameters must be either all unspecified (TLS disabled)
or all specified (TLS enabled).

TLS is asymmetric: the authentication of the server by the client is
mandatory but the authentication of the client by the server is optional.
In TLS terms this means the server can require the client certificate or
not so there is a server-specific TLS parameter.

- the ``cert-required`` boolean parameter allows a server to not
  require the client certificate. Its default value is true which
  means to require the client certificate and to authenticate the
  client. This flag has no meaning on the client side: the server
  always provides a certificate which is validated by the client.

Objects in files must be in the PEM format. Files can contain more
than one certificate but this was not tested and is not supported.

Botan requires CA certificates to have the standard CA certificate
attributes, verifies that end-entity certificates are version 3
certificates (as required by the TLS standard) and supports only PKCS 8
files for the private key.

.. note::

   Some cryptographic libraries (e.g. Botan and recent OpenSSL) enforce
   minimal strength (i.e. key length), e.g. at least 2048 for RSA.

A sample set of certificates and associated objects is available at
``src/lib/asiolink/testutils/ca`` in sources with a ``doc.txt`` file
explaining how they were generated using the openssl command. These
files are for testing purposes only. **Do not use them in production,**

TLS handshake, the phase where the cryptographic parameters are exchanged
and authentication is verified, can fail in multiple ways. Error messages
often do not really help to find the source of the problem.
Both OpenSSL and Botan provide a command line tool with a verify command
which can be used to understand and fix it.

Securing Kea deployment
=======================

Below is a list of considerations should the administrator wish to improve Kea's security. In many cases, there are trade-offs between convenience and security.

Component-based design
----------------------

The Kea architecture is modular, with separate daemons for separate tasks.
A Kea deployment could include DHCPv4, DHCPv6, and Dynamic DNS daemons, a control agent daemon run on each application server, the kea-lfc utility for doing periodic lease file cleanup, and MySQL and or PostgreSQL databases, run either locally on the application servers or accessed over the internal network, and a Stork monitoring system.
This modular architecture allows the administrator to minimize the attack surface by minimizing the code that is loaded and running.
For example, kea-dhcp-ddns should not be run unless DNS updates are required. Similarly, kea-lfc will never be triggered (and can be safely removed or never installed) if memfile is not used.
You can minimize potential Kea security issues by running only those processes required in your environment.

Limiting application permissions
----------------------------------

The DHCPv4 and DHCPv6 protocols assume the server will open privileged UDP port 67
(DHCPv4) or 547 (DHCPv6). Under normal circumstances that requires root access. However, with the
use of the capabilities mechanism on Linux systems, Kea can run from an unprivileged account. See
:ref:`non-root` Section for details on how to run Kea without root access.

The CA (Control Agent) can accept incoming HTTP or HTTPS connections. The default port is 8000, which
doesn't require privileged access.

Securing Kea administrative access
----------------------------------

The three primary Kea daemons (`kea-dhcp4`, `kea-dhcp6` and `kea-dhcp-ddns`) all support a control
channel, which is implemented as a UNIX socket. The control channel is disabled by default, but most
configuration examples have it enabled as it's a very popular feature. It opens a UNIX socket. To
read from or write to this socket, generally root access is required, although if Kea is configured
to run as non-root, the owner of the process can write to it. Access can be controlled using normal
file access control on POSIX systems (owner, group, others, read/write).

Kea configuration is controlled by a JSON file on the Kea server. This file can be viewed or edited
by anyone with file permissions (permissions controlled by the operating system). Note that
passwords are stored in clear text in the configuration file, so anyone with access to read the
configuration file can find this information. As a practical matter, anyone with permission to edit
the configuration file has control over Kea.
Limiting user permission to read or write the Kea configuration file is an important security step.

Securing database connections
-----------------------------

Kea can optionally use an external MySQL, PostgreSQL or Cassandra database to store configuration,
host reservations, leases or for forensic logging. The use of databases is a popular feature, but it
is optional. It's also possible to store data in a flat file on disk.

When using a database, Kea will store and use credentials in the form of username, password, host,
port and database name in order to authenticate with the database. **These are stored in clear text
in the configuration file.**

Depending on the database configuration, it's also possible to check if the system user matches the
database username. Consult MySQL or PostgreSQL manuals for details.

Kea does not support SSL/TLS connection to databases yet. There is a community contributed patch
available for `SSL support for MySQL <https://github.com/isc-projects/kea/pull/15>`_ and `SSL support
for Cassandra <https://github.com/isc-projects/kea/pull/118>`_. If the communication channel to the
database is a concern, the database can be run locally on the Kea server.

Information leakage through logging
-----------------------------------

Kea can log a whole configuration with included passwords and secrets in it. This problem has been
fixed in Kea 1.9.7 by replacing the value of all entries finishing by `password` or `secret` with
asterisks as it is already done for database logs.

Logs are sent to stdout, stderr, files or syslog. System file permissions system apply to stdout/stderr and files.  Syslog may export the logs over the network exposing them further to possible snooping.

Cryptography components
-----------------------

Kea has support for two cryptographic libraries: Botan and OpenSSL. This creates both compile and run-time
dependencies. The library is chosen at compilation time. The binaries use only one library that is
chosen at compilation time. Most deployments use OpenSSL, because it's much more popular, but Botan
remains a fully supported alternative.

The primary use cases for the cryptographic libraries are:

- TLS support for CA (Control Agent), introduced in Kea 1.9.6
- TSIG signatures when sending DNS Updates
- calculating DHCID records when sending DNS Updates.
- random number generation (but not for usage requiring a crypto grade generator).

For OpenSSL and Botan, only the low level crypto interface is used (e.g. libcrypto). Kea does not link
with libssl. Some dependent software systems, for instance database client libraries, can also depend on a crypto
library.

One way to limit exposure for potential OpenSSL or Botan vulnerabilities is to not use the DDNS. The
libraries would still be needed to build and run Kea, but the code would never be used, so any
potential bugs in the libraries would not be exploitable.

TSIG signatures
---------------

Kea supports the following algorithms when signing DNS Updates with TSIG signatures:

- HMAC-MD5
- HMAC-SHA1
- HMAC-SHA224
- HMAC-SHA256
- HMAC-SHA384
- HMAC-SHA512

See :ref:`d2-tsig-key-list-config` Section for an up to date list.

Kea uses SHA256 to calculate DHCID records. This is irrelevant from the cryptography perspective, as
the DHCID record is only used to generate unique identifiers for two devices that may have been
assigned the same IP address at different times.

Raw socket support
------------------

In principle, Kea DHCPv4 uses raw sockets to receive traffic from clients. The difficulty is with
receiving packets from devices that don't have an IPv4 address yet. When dealing with direct traffic
(where both client and server are connected to the same link, not separated by relays), the kernel
normally drops the packet as the source IP address is 0.0.0.0. Therefore Kea needs to open raw
sockets to be able to receive this traffic.

However, this is not necessary if all the traffic is coming via relays, which is often the case in
many networks. In that case normal UDP sockets can be used instead. There is a `dhcp-socket-type`
parameter that controls that behavior.

The default is to permit raw socket usage, as it is most versatile.

When using raw sockets, Kea is able to receive raw layer 2 packets, bypassing most firewalls
(including iptables). This effectively means that when raw sockets are used, the iptables can't be
used to block DHCP traffic. This is a design choice of the Linux kernel.

Kea can be switched to use UDP sockets. This is an option when all traffic is relayed. It will not work for directly connected devices. While Kea is limited to UDP sockets,
iptables should work properly.

If raw sockets are not required, disabling this access can improve security.

Remote Administrative Access
----------------------------

Kea's Control Agent (CA) exposes a REST API over HTTP or HTTPS (HTTP over TLS). The CA is an
optional feature that is disabled by default, but it is very popular. When enabled, it listens on the
loopback address (127.0.0.1 or ::1) by default, unless configured otherwise. See :ref:`tls` Section
about protecting the TLS traffic. Limiting the incoming connections with a firewall, such as
iptables, is generally a good idea.

Note that in HA (High Availability) deployments, DHCP partners connect to each other using CA
connection.

Authentication for Kea's REST API
---------------------------------

Kea 1.9.0 added support for basic HTTP authentication `RFC 7617 <https://tools.ietf.org/html/rfc7617>`_
to control access for incoming REST commands over HTTP. The credentials (username, password) are
stored in a local Kea configuration file on disk. The username is logged with the API command so it
is possible to determine which authenticated user performed each command. The access control details
are logged using a dedicated ``auth`` logger. Basic HTTP
authentication is weak on its own as there are known dictionary attacks, but those attacks require
man-in-the-middle to get access to the HTTP traffic. That can be eliminated by using basic HTTP
authentication exclusively over TLS. In fact, if possible, using client certificates for TLS is better than
using basic HTTP authentication.

Kea 1.9.2 introduced a new ``auth`` hook point. With this new hook point, it is possible to develop an external
hook library to extend the access controls, integrate with another authentication authority, or add role-based
access control to the Control Agent.

Kea security processes
======================

The following sections discuss how the development team ensures code quality and handles vulnerabilities.

Vulnerability Handling
----------------------

ISC is an experienced and active participant in the industry standard vulnerability disclosure
process and maintains accurate documentation on our process and vulnerabilities in ISC software.
See https://kb.isc.org/docs/aa-00861 for ISC's Software Defect and Security Vulnerability Disclosure Policy.

In case of a security vulnerability in Kea, ISC will notify support customers ahead of the public
disclosure, and will provide a patch and/or updated installer package that remediates the
vulnerability.

When a security update is published, both the source tarballs and the ISC-maintained packages are
published on the same day. This enables users of the native Linux update mechanisms (such as
Debian's and Ubuntu's apt or RedHat's dnf) to update their systems promptly.

Code quality and testing
------------------------

Kea undergoes extensive tests during its development. The following is an excerpt from all the
processes that are used to ensure adequate code quality:

- Each line of code goes through a formal review before it is accepted. The review process is
  documented and available publicly.
- Roughly 50% of the source code is dedicated to unit tests. As of Dec. 2020, there are over 6000
  unit tests and the number is increasing with time. Unit tests are required to commit any new feature.
- There are around 1500 system tests for Kea. These simulate both correct and invalid
  situations, covering network packets (mostly DHCP, but also DNS, HTTP, HTTPS and others),
  command-line usage, API calls, database interactions, scripts and more.
- There are performance tests with over 80 scenarios that test Kea overall performance and
  resiliency to various levels of traffic, measuring various metrics (latency, leases per seconds,
  packets per seconds, CPU usage, memory utilization and others).
- Kea uses CI (Continuous Integration). This means that the great majority of tests (all unit and system
  tests, and in some cases also performance tests) are run for every commit. Many lighter tests are
  run on branches, before the code is even accepted.
- Negative testing. Many unit and system tests check for negative scenarios, such as incomplete,
  broken, truncated packets, API commands, configuration files, incorrect sequences (such as sending
  packets in invalid order) and more.
- The Kea development team uses many tools that perform automatic code quality checks, such as danger, as well as
  internally-developed sanity checkers.
- The Kea team uses static code analyzers: Coverity Scan, shellcheck, danger.
- The Kea team uses dynamic code analyzers: Valgrind, Thread Sanitizer (TSAN).

Fuzz testing
------------

The Kea team has a process for running fuzz testing, using `AFL <https://github.com/google/AFL>`_. There
are two modes which are run. The first mode fuzzes incoming packets, effectively throwing millions of mostly
broken packets at Kea per day. The second mode fuzzes configuration structures and forces Kea to
attempt to load them. Kea has been fuzzed since around 2018 in both modes. The input seeds
(the data being used to generate or "fuzz" other input) are changed periodically.

Release integrity
-----------------

Software releases are signed with PGP, and distributed via the ISC web site, which is itself
DNSSEC-signed, so you can be confident the software has not been tampered with.

Bus Factor
----------

According to `Core Infrastructure project <https://bestpractices.coreinfrastructure.org/>`_, a "bus
factor" or a "truck factor" is the minimum number of project members that have to suddenly disappear
from a project ("hit by a bus") before the project stalls due to lack of knowledgeable or competent
personnel. It's hard to estimate precisely, but the bus factor for Kea is somewhere around 5. As of
2021, there are 6 core developers and 2 QA engineers, with many additional casual contributors (product manager, support team, IT, etc). The team is geographically dispersed.
