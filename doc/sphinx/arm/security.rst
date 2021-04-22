.. _security:

************
Kea Security
************

Kea was designed to address a wide variety of deployments with varying expectations
regarding ease of use, security and generally working out-of-the-box experience.
Many aspects can be tweaked and this section discusses them from the point of security.
Please keep in mind that there often no strict recommendations. In many cases, there's
a trade-off between convenience and higher security. It is up to the administrator
to make those choices.

Component-based design
======================

The Kea architecture is modular, with separate daemons for separate tasks. A
typical Kea deployment will consist of: DHCPv4, DHCPv6, and Dynamic DNS daemons,
a control agent daemon run on each application server, the `kea-lfc` utility for doing
periodic lease file cleanup, and MySQL and or PostgreSQL databases, run either locally
on the application servers or accessed over the internal network.

This modular architecture minimizes the attack surface by minimizing the code that is
loaded and running. For example, `kea-dhcp-ddns` should not be run unless DNS updates
are required. Similarly, `kea-lfc` will never be triggered (and can be safely removed
or never installed) if memfile is not used. If your deployment is IPv4 only, the IPv6
component should not be running. The opposite is also true. If you don't need remote
management, do not start CA.

That is in contrast to ISC DHCP's server `dhcpd`, which is a single binary that does
everything.

.. _tls:

TLS/HTTPS support
=================

Since version 1.9.6 Kea includes TLS support for better security.
TLS is used on HTTP communication providing three increasing levels of
protection:

- no TLS. The connection is plain text, unencrypted HTTP. This is
  the only option available in prior versions.

- encryption i.e. protection against passive attacks and
  eavesdropping, the server is still authenticated but the client is
  not. This is the typical mode when securing a web site, where
  clients and servers are not under the control of a common entity.

- mutual authentication between the client and the server. This mode
  is stricter than the previous one and is the default when TLS is
  enabled.

.. note::

   The mutual authentication is for the TLS entities. When TLS and
   a HTTP authentication scheme are used there is no binding between
   the two security mechanisms so no proof that the TLS client and server
   are the same as the HTTP authentication client and server.

.. _tls_config:

Kea Installation with TLS/HTTPS support
---------------------------------------

TLS/HTTPS support is available with OpenSSL and Botan cryptographic backends
with some constraints including on the boost library:

- OpenSSL versions older than 1.0.2 are obsolete so should not be considered.
  The TLS support was not tested and is not supported on these versions.

- OpenSSL version 1.0.2 has extended support for OpenSSL premium customers
  so should not be considered at the exception of these premium customers.
  The TLS support was tested but is not supported on this version.

- OpenSSL versions >= 1.1.x were tested and are supported. Note enough
  recent versions include TLS 1.3 support.

- OpenSSL 3.x was not yet released and Kea does not build with it.

- LibreSSL 3.2.4 was tested. LibreSSL shares the OpenSSL 1.0.2 API so
  it should work but is not supported.

- Botan 1.x versions are obsolete so should not be considered.
  The TLS support was not tested and is not supported on these versions.

- Botan 2.x versions were tested and are supported. Note the TLS support
  requires the four asio header files which are included in Botan
  packages / installation only when Botan was configured with the
  ``--with-boost`` option. It is still possible to take these files
  from the corresponding Botan distribution and to install them manually
  in the Botan include directory but of course this should be a last
  resort procedure. Note that without these header files Kea can still
  build but the TLS support is disabled: any attempt to use it will fail
  with a fatal error.

- very old boost versions provide SSL support (based on OpenSSL) without
  choice of the TLS version: Kea can still use them but they are not
  recommended.

- boost versions older than 1.64 provide SSL support with a rigid
  choice of the TLS version: Kea enforces the use of TLS 1.2 with them.

- boost versions 1.64 or newer provide SSL support with a generic
  TLS version: the best (higher) version available on both peers is
  selected.


TLS/HTTPS configuration
-----------------------

The new TLS configuration parameters are:

- the ``trust-anchor`` string parameter specifies the name of a file
  or directory where the certification authority (CA) certificate of
  the other peer can be found. With OpenSSL the directory must include
  hash symbolic links. With Botan the directory is recursively
  searched for certificates.

- the ``cert-file`` string parameter specifies the name of the file
  containing the end-entity certificate of the Kea instance
  being configured.

- the ``key-file`` string parameter specifies the private key of the
  end-entity certificate of Kea instance being configured.
  The file must not be encrypted and it is highly recommended to
  restrict its access.

The three string parameters must be either all not specified (TLS disabled)
or all specified (TLS enabled).

TLS is asymmetric: the authentication of the server by the client is
mandatory but the authentication of the client by the server is optional.
In TLS terms this means the server can require the client certificate or
not so there is a server specific TLS parameter.

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
and authentication is verified, can fail in a lot of ways. Error messages
often do not really help to find the source of the problem.
Both OpenSSL and Botan provide a command line tool with a verify command
which can be used to understand and fix it.

Securing Kea deployment
=======================

The following sections discuss various configuration options that may
have an impact on deployment security.

Access permissions and root access
----------------------------------

Kea uses the DHCPv4 and DHCPv6 protocols, which assume the server will open privileged
UDP port 67 (DHCPv4) or 547 (DHCPv6). Under normal circumstances that requires
root access. However, with the use of the capabilities mechanism on Linux systems,
Kea can run from an unprivileged account. See :ref:`non-root` for details.

CA (Control Agent) can accept incoming http or https connections. The default port is 8000,
which doesn't require privileged access.

Kea Administrative access
-------------------------

The three primary Kea daemons (`kea-dhcp4`, `kea-dhcp6` and `kea-dhcp-ddns`) all support
a control channel, which is implemented as a UNIX socket. The control channel is disabled
by default, but most configuration examples have it enabled as it's a very popular feature.
It opens a UNIX socket. To read from or write to this socket, generally root access is
required, although if Kea is configured to run as non-root, the owner of the process can
write to it. Access can be controlled using normal file access control on POSIX systems
(owner, group, others, read/write).

Kea configuration is controlled by a JSON file on the Kea server. This file can be viewed
or edited by anyone with file permissions (permissions controlled by the operating system).
Note that passwords are stored in clear text in the configuration file, so anyone with access
to read the configuration file can find this information. As a practical matter, anyone with
permission to edit the configuration file has control over Kea.

Database connections
--------------------

Kea can optionally use an external MySQL, PostgreSQL or Cassandra database to store configuration,
host reservations, leases or for forensic logging. The use of databases is a popular feature, but
it is optional. It's also possible to store data in a flat file on disk.

When using a database, Kea will store and use credentials in the form of username, password, host,
port and database name in order to authenticate with the database. **These are stored in clear text
in the configuration file.**

Depending on the database configuration, it's also possible to check if the system user matches
the database username. Consult MySQL or PostgreSQL manuals for details.

Kea does not support SSL/TLS connection to databases yet. There is a community contributed patch
available for [SSL support for MySQL](https://github.com/isc-projects/kea/pull/15) and
[SSL support for Cassandra](https://github.com/isc-projects/kea/pull/118).
If the communication channel to the database is a concern, the database can be run locally on the
Kea server.

Kea Logging
-----------

Kea can log a whole configuration with included passwords and secrets in it. This problem has been
fixed in 1.9.7 by replacing the value of all entries finishing by `password` or `secret` with
asterisks as it is already done for database logs.

Logs are sent to stdout, stderr, files or syslog. For the first three, the file permissions of the
system apply. Syslog can export the logs over the network so is harder to secure.

Cryptography components
-----------------------

Kea has support for two cryptographic libraries: Botan and OpenSSL. This is both compile and run-time
dependency. The library is chosen at compilation time. The binaries use only one library that is
chosen at compilation time. Most deployments use OpenSSL, because it's much more popular, but Botan
remains a fully supported alternative.

The primary use cases for the cryptographic libraries are:

- TLS support for CA (Control Agent), introduced in Kea 1.9.6
- TSIG signatures when sending DNS Updates
- calculating DHCID records when sending DNS Updates.
- random number generation (but not for usage requiring a crypto grade generator).

For OpenSSL and Botan, only low level crypto interface is used (e.g. libcrypto). Kea does not link
with libssl. Some dependencies, for instance database client libraries, can also depend on a crypto library.

One way to limit exposure for potential OpenSSL or Botan vulnerabilities is to not use the DDNS.
The libraries would still be necessary to build and run Kea, but the code would never be used, so any
potential bugs in the libraries would never had a chance to be exploited.

TSIG signatures
---------------

Kea supports the following algorithms when signing DNS Updates with TSIG signature:

- HMAC-MD5
- HMAC-SHA1
- HMAC-SHA224
- HMAC-SHA256
- HMAC-SHA384
- HMAC-SHA512

See :ref:`d2-tsig-key-list-config` for an up to date list.

Kea uses SHA256 to calculate DHCID records. This is irrelevant from the cryptography perspective,
as the DHCID record is only used to generate unique identifiers for two devices that may have been
assigned the same IP address at different times.

Raw socket support
------------------

In principle, Kea DHCPv4 uses raw sockets to receive traffic from clients. The difficulty is with receiving
packets from devices that don't have an IPv4 address yet. When dealing with direct traffic (where both client
and server are connected to the same link, not separated by relays), the kernel normally drops the packet as
the source IP address is 0.0.0.0. Therefore Kea needs to open raw sockets to be able to receive this traffic.

However, this is not necessary if all the traffic is coming via relays, which is often the case in many networks.
In that case normal UDP sockets can be used instead. There is a `dhcp-socket-type` parameter that controls that
behavior.

The default is to permit raw socket usage, as it is most versatile.

When using raw sockets, Kea is able to receive raw layer 2 packet, bypassing most firewalls (including iptables).
This effectively means that when raw sockets are used, the iptables can't be used to block DHCP traffic. This is
a design choice of the Linux kernel.

Kea can be switched to use UDP sockets. This will work when only relayed traffic (via relays) is received. It
will not work for directly connected devices. While Kea is running with UDP sockets, iptables are working properly.

Remote Administrative Access
----------------------------

Kea's Control Agent (CA) exposes a REST API over HTTP or HTTPS (HTTP over TLS). The CA is an optional feature that
is disabled by default, but it is very popular. When enabled, it listens on loopback address (127.0.0.1 or ::1) by
default, unless configured otherwise. See :ref:`tls` section about protecting the TLS traffic. Limiting the incoming
connections with a firewall, such as iptables, is generally a good idea.

Note that in HA (High Availability) deployments, DHCP partners connect to each other using CA connection.

Authentication for REST API
---------------------------

Kea 1.9.0 added support for basic HTTP authentication [RFC7617](https://tools.ietf.org/html/rfc7617) to control
access for incoming REST commands over HTTP. The credentials (username, password) are stored in a local Kea
configuration file on disk.  The username is logged with the API command so it is possible to determine which
authenticated user performed each command. The basic HTTP authentication is weak on its own as there are known
dictionary attacks, but those attacks require man-in-the-middle to get access to the HTTP traffic. That can be
eliminated by using basic HTTP authentication only over TLS. In fact, if possible, using client cerificates for
TLS is better than using basic HTTP authentication.

Kea 1.9.2 introduced a new `auth` hook point. With this new hook point it is now possible to develop an external
hook library to extend the access controls, integrate with another authentication authority or add role-based
access control to the Control Agent.

Kea processes
=============

The following sections discuss various aspects of Kea as project and how the team handles vulnerabilities, testing
and other related aspects.

Vulnerability Handling
----------------------

ISC is an experienced and active participant in the industry standard vulnerability disclosure process and
maintains accurate documentation on our process and vulnerabilities in ISC software.  Any critical vulnerabilities
(those that score >5.0 on CVSSv3) are publicly disclosed and documented and reported to Mitre/CERT.

In case of a security vulnerability in Kea, ISC will notify support customers ahead of the public disclosure, and
will provide a patch and/or updated installer package that remediates the vulnerability.

When security update is published, both source code and the native (DEB, RPM and APK) packages are published on the
same day. This helps taking leverage of the native Linux mechanisms (such as Debian's and Ubuntu's apt or RedHat's dnf)
to update quickly.

Code quality and testing
------------------------

Kea undergoes extensive tests during its development. The following is an excerpt from all the processes that are used
to ensure adequate code quality:

- Each line of code goes through a formal review before it is accepted. The review process is documented and available
  publicly.
- Roughly 50% of the source code is dedicated to unit tests. As of Dec. 2020, there are over 6000 unit tests and the number
  is growing with most completed tickets. There is a requirement that every new piece of code has to come with unit tests
  before it is accepted.
- There are around 1500 system tests available that test Kea. Those simulate correct and invalid situations, covering
  network packets (mostly DHCP, but also DNS, HTTP, HTTPS and others), command-line usage, API calls, database interactions,
  scripts and more.
- There are performance tests with over 80 scenarios that test Kea overall performance and resiliency to various levels
  of traffic, measuring various metrics (latency, leases per seconds, packets per seconds, CPU usage, memory utilization and
  others).
- Kea uses CI (Continuous Integration). This means that great majority of tests (all unit and system tests, and in some cases
  also performance tests) are run for every commit. Many lighter tests are ran on branches, before the code is even accepted.
- Negative testing. Many unit and system tests check for negative scenarios, such as incomplete, broken, truncated packets,
  API commands, configuration files, incorrect sequences (such as sending packets in invalid order) and more.
- Kea team uses many tools that perform automatic code quality checks, such as danger or our own internal sanity checkers.
- Kea team uses static code analyzers: Coverity Scan, shellcheck, danger.
- Kea team uses dynamic code analyzers: Valgrind, Thread Sanitizer (TSAN).

Fuzz testing
------------

Kea team has a process for running fuzz testing, using [AFL](https://github.com/google/AFL). There are two modes which are run.
First fuzzes incoming packets, effectively throwing millions of mostly broken packets at Kea per day. The second mode
fuzzes configuration structures and forces Kea to attempt to load them. Those two modes are being run continuously since
around 2018. The input seeds (the data being used to generate or "fuzz" other input) are changed every once in a while.

Release integrity
-----------------

Software releases are signed with PGP, and distributed via the ISC web site, which is itself DNSSEC-signed, so you can be
confident the software has not been tampered with.

Bus Factor
----------

According to [coreinfrastructure](https://bestpractices.coreinfrastructure.org/), a "bus factor" or a "truck factor" is the
minimum number of project members that have to suddenly disappear from a project ("hit by a bus") before the project stalls due
to lack of knowledgeable or competent personnel. It's hard to estimate precisely, but the bus factor for Kea is somewhere around
5. As of 2021, there are 6 core developers and 2 QA engineers, with many more additional persons getting involved frequently
(product manager, support team, IT, etc). The team is dispersed around the US and Europe.
