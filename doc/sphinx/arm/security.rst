.. _security:

************
Kea Security
************

Kea was originally designed to be installed in a protected environment, in a network
datacenter; it did not offer hardened security features. However, due to customer demand
and evolving network requirements, support for basic HTTP authentication and Transport
Layer Security (TLS) have been added to Kea.

.. _tls:

TLS/HTTPS Support
=================

Since Kea 1.9.6, TLS can be used to secure HTTP communication. There are three levels of
protection possible:

- No TLS. The connection is plain-text, unencrypted HTTP. (This is
  the only option available in versions prior to Kea 1.9.6.)

- Encryption, which protects against passive attacks and
  eavesdropping. In this case, the server is authenticated but the client is
  not. This is the typical mode when securing a website, where
  clients and servers are not under the control of a common entity.

- Mutual authentication between the client and the server. This is the
  strictest security mode and is the default when TLS is
  enabled.

.. note::

   TLS mutual authentication is for TLS entities only. When TLS and
   an HTTP authentication scheme are used together, there is no binding between
   the two security mechanisms, and therefore no proof that the TLS client and server
   are the same as the HTTP authentication client and server.

.. _tls_config:

Building Kea with TLS/HTTPS Support
-----------------------------------

TLS/HTTPS support is available with either the OpenSSL or the Botan
cryptographic library. There are some constraints on the Boost library
that must be used:

- OpenSSL versions older than 1.0.2 are obsolete and should not be used.
  Kea TLS support has not been tested with and is not supported on these versions.

- OpenSSL version 1.0.2 has extended support, but only for OpenSSL premium
  customers. Kea TLS support has been tested but is not supported on this version.

- OpenSSL versions 1.1.x and later have been tested and are supported. Many
  recent operating system versions include TLS 1.3 support.

- OpenSSL 3.x is not yet released; it is unknown whether Kea will build with it.

- LibreSSL 3.2.4 has been tested. LibreSSL shares the OpenSSL 1.0.2 API, so
  it should work, but is not supported.

- Botan 1.x versions are obsolete and should not be used.
  Kea TLS support has not been tested and is not supported with these versions.

- Botan versions 2.14.0 and later have been tested and are supported. Kea TLS
  support requires the four Asio header files which are included in Botan
  packages and which are installed only if Botan is configured with the
  ``--with-boost`` option.

  Many packages provided by operating systems, such as Ubuntu 20.10,
  do not build Botan with Boost support, making those packages
  unusable for Kea with TLS.

  It is still possible to take these files from the corresponding
  Botan distribution and install them manually in the Botan include
  directory, but this should be a last-resort procedure.

  Without these header files, or with a Botan version prior
  to 2.14.0, Kea can still build, but the TLS/HTTPS support is disabled;
  any attempt to use it will fail with a fatal error.

- Very old Boost versions provide SSL support (based on OpenSSL)
  without offering a choice of the TLS version; Kea can still use them,
  but they are not recommended.

- Boost versions prior to 1.64 provide SSL support with a fixed
  choice of the TLS version; Kea enforces the use of TLS 1.2 with them.

- Boost versions 1.64 or newer provide SSL support with a generic
  TLS version; the best (highest) version available on both peers is
  selected.

TLS/HTTPS Configuration
-----------------------

The TLS configuration parameters are:

- ``trust-anchor`` - this string parameter specifies the name of a file
  or directory where the certification authority (CA) certificate of
  the other peer can be found. With OpenSSL, the directory must include
  hash symbolic links. With Botan, the directory is recursively
  searched for certificates.

- ``cert-file`` - this string parameter specifies the name of the file
  containing the end-entity certificate of the Kea instance
  being configured.

- ``key-file`` - this string parameter specifies the private key of the
  end-entity certificate of the Kea instance being configured.
  The file must not be encrypted; it is highly recommended to
  restrict its access.

The three string parameters must be either all unspecified (TLS disabled)
or all specified (TLS enabled).

TLS is asymmetric: the authentication of the server by the client is
mandatory but the authentication of the client by the server is optional.
In TLS terms, this means the server may require the client certificate, or
may not; there is a server-specific TLS parameter.

- ``cert-required`` - this boolean parameter allows a server to not
  require the client certificate. Its default value is ``true``, which
  means the client certificate is required and the
  client must be authenticated. This flag has no meaning on the client side; the server
  always provides a certificate which is validated by the client.

Objects in files must be in the PEM format. Files can contain more
than one certificate, but this has not been tested and is not supported.

Botan requires CA certificates to have the standard CA certificate
attributes, verifies that end-entity certificates are version 3
certificates (as required by the TLS standard), and supports only PKCS 8
files for the private key.

.. note::

   Some cryptographic libraries (e.g. Botan and recent OpenSSL) enforce
   minimal strength (i.e. key length), e.g. at least 2048 for RSA.

A sample set of certificates and associated objects is available at
``src/lib/asiolink/testutils/ca`` in the Kea sources, with a ``doc.txt`` file
explaining how they were generated using the ``openssl`` command. These
files are for testing purposes only. **Do not use them in production.**

TLS handshake, the phase where the cryptographic parameters are exchanged
and authentication is verified, can fail in multiple ways. Error messages
often do not help to pinpoint the source of the problem.
Both OpenSSL and Botan provide a command-line tool with a ``verify`` command
which can be used to understand and fix handshake issues.

Securing a Kea Deployment
=========================

Below is a list of considerations for administrators wishing to improve Kea's
security. In many cases, there are trade-offs between convenience and security.

Component-Based Design
----------------------

The Kea architecture is modular, with separate daemons for separate tasks.
A Kea deployment may include DHCPv4, DHCPv6, and Dynamic DNS daemons; a Control Agent
daemon run on each application server; the ``kea-lfc utility`` for doing periodic lease
file cleanup; MySQL and or PostgreSQL databases, run either locally on the application
servers or accessed over the internal network; and a Stork monitoring system.
This modular architecture allows the administrator to minimize the attack surface
by minimizing the code that is loaded and running.
For example, ``kea-dhcp-ddns`` should not be run unless DNS updates are required.
Similarly, ``kea-lfc`` is never triggered (and can be safely removed or never installed) if memfile is not used.
Potential Kea security issues can be minimized by running only those processes required in the local environment.

Limiting Application Permissions
--------------------------------

The DHCPv4 and DHCPv6 protocols assume the server opens privileged UDP port 67
(DHCPv4) or 547 (DHCPv6), which requires root access under normal circumstances. However, via the
capabilities mechanism on Linux systems, Kea can run from an unprivileged account. See
:ref:`non-root` for details on how to run Kea without root access.

The Control Agent (CA) can accept incoming HTTP or HTTPS connections. The default port is 8000, which
does not require privileged access.

Securing Kea Administrative Access
----------------------------------

The three primary Kea daemons (``kea-dhcp4``, ``kea-dhcp6`` and ``kea-dhcp-ddns``) all support a control
channel, which is implemented as a UNIX socket. The control channel, which opens a UNIX socket, is disabled by default;
however, many configuration examples have it enabled, as it is a very popular feature. To
read from or write to this socket, root access is generally required, although if Kea is configured
to run as non-root, the owner of the process can write to it. Access can be controlled using normal
file-access control on POSIX systems (owner, group, others, read/write).

Kea configuration is controlled by a JSON file on the Kea server. This file can be viewed or edited
by anyone with file permissions (which are controlled by the operating system). Note that
passwords are stored in clear text in the configuration file, so anyone with access to read the
configuration file can find this information. As a practical matter, anyone with permission to edit
the configuration file has control over Kea.
Limiting user permission to read or write the Kea configuration file is an important security step.

Securing Database Connections
-----------------------------

Kea can use an external MySQL or PostgreSQL database to store configuration,
host reservations, or leases, or for forensic logging. (Support for Cassandra is deprecated.) The use
of databases is a popular feature, but it
is optional; it is also possible to store data in a flat file on disk.

When using a database, Kea stores and uses the following credentials to authenticate with the database:
username, password, host, port, and database name. **These are stored in clear text
in the configuration file.**

Depending on the database configuration, it is also possible to verify whether the system user matches the
database username. Consult the MySQL or PostgreSQL manual for details.

Kea does not currently support SSL/TLS connection to databases. There is a community-contributed patch
available for `SSL support for MySQL <https://github.com/isc-projects/kea/pull/15>`_ and
`SSL support for Cassandra <https://github.com/isc-projects/kea/pull/118>`_. If the communication
channel to the database is a concern, the database can be run locally on the Kea server.

Information Leakage Through Logging
-----------------------------------

It is possible for Kea to log an entire configuration file, including passwords and secrets.
Since Kea 1.9.7, this issue has been resolved by replacing the value of all entries ending in
``password`` or ``secret`` with asterisks, as was already done for database logs.

Logs are sent to stdout, stderr, files, or syslog; system file permissions system apply to
stdout/stderr and files. Syslog may export the logs over the network, exposing them further to possible snooping.

Cryptography Components
-----------------------

Kea supports the use of either of two cryptographic libraries: Botan or OpenSSL.
The choice is made at compile time, and creates both compile and runtime dependencies
between the Kea and the selected library. While OpenSSL is the most popular choice for
deployments, Botan remains a fully supported alternative.

The primary use cases for the cryptographic libraries are:

- TLS support for the Control Agent (CA), introduced in Kea 1.9.6.
- TSIG signatures when sending DNS updates.
- calculating DHCID records when sending DNS updates.
- random number generation (but not for usage requiring a crypto grade generator).

For OpenSSL and Botan, only the low-level crypto interface is used (e.g. libcrypto). Kea does not link
with libssl. Some dependent software systems, such as database client libraries, can also depend on a crypto
library.

One way to limit exposure for potential OpenSSL or Botan vulnerabilities is not to use DDNS. The
libraries would still be needed to build and run Kea, but the code would never be used, so any
potential bugs in the libraries would not be exploitable.

TSIG Signatures
---------------

Kea supports the following algorithms when signing DNS updates with TSIG signatures:

- HMAC-MD5
- HMAC-SHA1
- HMAC-SHA224
- HMAC-SHA256
- HMAC-SHA384
- HMAC-SHA512

See :ref:`d2-tsig-key-list-config` for an up-to-date list.

Kea uses SHA256 to calculate DHCID records. This is irrelevant from the cryptography perspective, as
the DHCID record is only used to generate unique identifiers for two devices that may have been
assigned the same IP address at different times.

Raw Socket Support
------------------

In principle, Kea DHCPv4 uses raw sockets to receive traffic from clients. The difficulty is with
receiving packets from devices that do not yet have an IPv4 address. When dealing with direct traffic
(where both client and server are connected to the same link, not separated by relays), the kernel
normally drops the packet as the source IP address is 0.0.0.0. Therefore, Kea needs to open raw
sockets to be able to receive this traffic.

However, this is not necessary if all the traffic is coming via relays, which is often the case in
many networks. In that case normal UDP sockets can be used instead. There is a ``dhcp-socket-type``
parameter that controls this behavior.

The default is to permit raw socket usage, as it is more versatile.

When using raw sockets, Kea is able to receive raw layer 2 packets, bypassing most firewalls
(including iptables). This effectively means that when raw sockets are used, the iptables cannot be
used to block DHCP traffic. This is a design choice of the Linux kernel.

Kea can be switched to use UDP sockets. This is an option when all traffic is relayed.
However, it does not work for directly connected devices. If Kea is limited to UDP sockets,
iptables should work properly.

If raw sockets are not required, disabling this access can improve security.

Remote Administrative Access
----------------------------

Kea's Control Agent (CA) exposes a RESTful API over HTTP or HTTPS (HTTP over TLS). The CA is an
optional feature that is disabled by default, but it is very popular. When enabled, it listens on the
loopback address (127.0.0.1 or ::1) by default, unless configured otherwise. See :ref:`tls`
for information about protecting the TLS traffic. Limiting the incoming connections with a firewall, such as
iptables, is generally a good idea.

Note that in High Availability (HA) deployments, DHCP partners connect to each other using a CA
connection.

Authentication for Kea's RESTful API
------------------------------------

Kea 1.9.0 added support for basic HTTP authentication (`RFC 7617 <https://tools.ietf.org/html/rfc7617>`_),
to control access for incoming REST commands over HTTP. The credentials (username, password) are
stored in a local Kea configuration file on disk. The username is logged with the API command, so it
is possible to determine which authenticated user performed each command. The access control details
are logged using a dedicated ``auth`` logger. Basic HTTP
authentication is weak on its own as there are known dictionary attacks, but those attacks require
a "man in the middle" to get access to the HTTP traffic. That can be eliminated by using basic HTTP
authentication exclusively over TLS. In fact, if possible, using client certificates for TLS is better than
using basic HTTP authentication.

Kea 1.9.2 introduced a new ``auth`` hook point. With this new hook point, it is possible to develop an external
hook library to extend the access controls, integrate with another authentication authority, or add role-based
access control to the Control Agent.

Kea Security Processes
======================

The following sections discuss how the Kea DHCP development team ensures code quality and handles vulnerabilities.

Vulnerability Handling
----------------------

ISC is an experienced and active participant in the industry-standard vulnerability disclosure
process and maintains accurate documentation on our process and vulnerabilities in ISC software.
See https://kb.isc.org/docs/aa-00861 for ISC's Software Defect and Security Vulnerability Disclosure Policy.

In case of a security vulnerability in Kea, ISC notifies support customers ahead of any public
disclosure, and provides a patch and/or updated installer package to remediate the
vulnerability.

When a security update is published, both the source tarballs and the ISC-maintained packages are
published on the same day. This enables users of the native Linux update mechanisms (such as
Debian's and Ubuntu's apt or RedHat's dnf) to update their systems promptly.

Code Quality and Testing
------------------------

Kea undergoes extensive tests during its development. The following are some of the
processes that are used to ensure adequate code quality:

- Each line of code goes through a formal review before it is accepted. The review process is
  documented and available publicly.
- Roughly 50% of the source code is dedicated to unit tests. As of December 2020, there were over 6000
  unit tests and the number is increasing with time. Unit tests are required to commit any new feature.
- There are around 1500 system tests for Kea. These simulate both correct and invalid
  situations, covering network packets (mostly DHCP, but also DNS, HTTP, HTTPS and others),
  command-line usage, API calls, database interactions, scripts, and more.
- There are performance tests with over 80 scenarios that test Kea overall performance and
  resiliency to various levels of traffic, and measuring various metrics (latency, leases per seconds,
  packets per seconds, CPU usage, memory utilization, and others).
- Kea uses Continuous Integration (CI). This means that the great majority of tests (all unit and system
  tests, and in some cases also performance tests) are run for every commit. Many "lighter" tests are
  run on branches, before the code is even accepted.
- Many unit and system tests check for negative scenarios, such as incomplete,
  broken, or truncated packets, API commands, and configuration files, as well as incorrect sequences (such as sending
  packets in an invalid order) and more.
- The Kea development team uses many tools that perform automatic code quality checks, such as danger, as well as
  internally developed sanity checkers.
- The Kea team uses the following static code analyzers: Coverity Scan, shellcheck, and danger.
- The Kea team uses the following dynamic code analyzers: Valgrind and Thread Sanitizer (TSAN).

Fuzz Testing
------------

The Kea team has a process for running fuzz testing, using `AFL <https://github.com/google/AFL>`_. There
are two modes which are run: the first mode fuzzes incoming packets, effectively throwing millions of mostly
broken packets at Kea per day, while the second mode fuzzes configuration structures and forces Kea to
attempt to load them. Kea has been fuzzed since around 2018 in both modes. The input seeds
(the data being used to generate or "fuzz" other input) are changed periodically.

Release Integrity
-----------------

All ISC software releases are signed with PGP and distributed via the ISC website, which is itself
DNSSEC-signed, so users can be confident the software has not been tampered with.

Bus Factor
----------

According to the `Core Infrastructure project <https://bestpractices.coreinfrastructure.org/>`_, a "bus
factor" or "truck factor" is the minimum number of project members that have to suddenly disappear
from a project ("be hit by a bus") before the project stalls due to lack of knowledgeable or competent
personnel. It is hard to estimate precisely, but the bus factor for Kea is somewhere around five. As of
2021, there are six core developers and two quality assurance engineers, with many additional casual
contributors (product manager, support team, IT, etc.). The team is geographically dispersed.
