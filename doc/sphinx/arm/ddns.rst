.. _dhcp-ddns-server:

********************
The DHCP-DDNS Server
********************

.. _dhcp-ddns-overview:

Overview
========

The DHCP-DDNS Server (``kea-dhcp-ddns``, known informally as D2) conducts
the client side of the Dynamic DNS protocol (DDNS, defined in `RFC
2136 <https://tools.ietf.org/html/rfc2136>`__) on behalf of the DHCPv4
and DHCPv6 servers (``kea-dhcp4`` and ``kea-dhcp6`` respectively). The DHCP
servers construct DDNS update requests, known as NameChangeRequests
(NCRs), based on DHCP lease change events and then post them to D2. D2
attempts to match each request to the appropriate DNS server(s) and
carries out the necessary conversation with those servers to update the
DNS data.

.. _dhcp-ddns-dns-server-selection:

DNS Server Selection
--------------------

To match a request to the appropriate DNS servers, D2 must have
a catalog of servers from which to select. In fact, D2 has two such
catalogs, one for forward DNS and one for reverse DNS; these catalogs
are referred to as "DDNS domain lists." Each list consists of one or more
named DDNS domains. Further, each DDNS domain has a list of one or more
DNS servers that publish the DNS data for that domain.

When conducting forward-domain matching, D2 compares the fully qualified
domain name (FQDN) in the request against the name of each forward DDNS
domain in its catalog. The domain whose name matches the longest portion
of the FQDN is considered the best match. For example, if the FQDN is
"myhost.sample.example.com.", and there are two forward domains in the
catalog, "sample.example.com." and "example.com.", the former is
regarded as the best match. In some cases, it may not be possible to
find a suitable match. Given the same two forward domains there would be
no match for the FQDN "bogus.net", so the request would be rejected.
Finally, if there are no forward DDNS domains defined, D2 simply
disregards the forward-update portion of requests.

When conducting reverse-domain matching, D2 constructs a reverse FQDN
from the lease address in the request and compares that against the name
of each reverse DDNS domain. Again, the domain whose name matches the
longest portion of the FQDN is considered the best match. For instance,
if the lease address is "172.16.1.40" and there are two reverse domains
in the catalog, "1.16.172.in-addr.arpa." and "16.172.in-addr.arpa", the
former is the best match. As with forward matching, D2 may not find a
suitable match. Given the same two domains, there would be no match for
the lease address, "192.168.1.50", and the request would be rejected.
As with forward-domain matching, if there are no reverse DDNS domains defined, D2 simply
disregards the reverse-update portion of requests.

.. _dhcp-ddns-conflict-resolution:

Conflict Resolution
-------------------

D2 implements the conflict resolution strategy prescribed by `RFC
4703 <https://tools.ietf.org/html/rfc4703>`__. Conflict resolution is
intended to prevent different clients from mapping to the same FQDN at
the same time. To make this possible, the RFC requires that forward DNS
entries for a given FQDN must be accompanied by a DHCID resource record
(RR). This record contains a client identifier that uniquely identifies
the client to whom the name belongs. Furthermore, any DNS updater that
wishes to update or remove existing forward entries for an FQDN may only
do so if their client matches that of the DHCID RR.

In other words, the DHCID RR maps an FQDN to the client to whom it
belongs, and thereafter changes to that mapping can only be done by
or at the behest of that client.

Conflict resolution can be indirectly enabled or disabled via
the configuration parameter ``ddns-use-conflict-resolution``, supported
by both ``kea-dhcp4`` and ``kea-dhcp6``. These servers use this parameter to
set a flag within each NameChangeRequest they send that tells D2
whether conflict resolution should be employed for that request.
By default, conflict resolution is enabled. For more details, please refer
to discussions of ``ddns-use-conflict-resolution`` in :ref:`dhcp4-ddns-config` and :ref:`dhcp6-ddns-config`.

When conflict resolution is disabled, D2 still adds DHCID RRs but does
not use them to enforce client ownership of DNS entries. Disabling it should
only be used after careful consideration.

.. _dhcp-ddns-dual-stack:

Dual-Stack Environments
-----------------------

`RFC 4703, section
5.2, <https://tools.ietf.org/html/rfc4703#section-5.2>`__ describes
issues that may arise with dual-stack clients. These are clients that
wish to have both IPv4 and IPv6 mappings for the same FQDN.
To work properly, clients must embed their IPv6 DUID
within their IPv4 client identifier option, as described in `RFC
4361 <https://tools.ietf.org/html/rfc4361>`__. In this way, DNS updates
for both IPv4 and IPv6 can be managed under the same DHCID RR. This feature
is supported by Kea beginning with release 2.1.2.

.. _dhcp-ddns-server-start-stop:

Starting and Stopping the DHCP-DDNS Server
==========================================

``kea-dhcp-ddns`` is the Kea DHCP-DDNS server and, due to the nature of
DDNS, it runs alongside either the DHCPv4 or DHCPv6 component (or both).
Like other parts of Kea, it is a separate binary that can be run on its
own or through ``keactrl`` (see :ref:`keactrl`). In normal
operation, controlling ``kea-dhcp-ddns`` with ``keactrl`` is
recommended; however, it is also possible to run the DHCP-DDNS server
directly. It accepts the following command-line switches:

-  ``-c file`` - specifies the configuration file. This is the only
   mandatory switch.

-  ``-d`` - specifies whether server logging should be switched to
   debug/verbose mode. In verbose mode, the logging severity and
   debuglevel specified in the configuration file are ignored and
   "debug" severity and the maximum debuglevel (99) are assumed. The
   flag is convenient for temporarily switching the server into maximum
   verbosity, e.g. when debugging.

-  ``-v`` - displays the Kea version and exits.

-  ``-W`` - displays the Kea configuration report and exits. The report
   is a copy of the ``config.report`` file produced by ``./configure``;
   it is embedded in the executable binary.

-  ``-t file`` - specifies the configuration file to be tested.
   ``kea-dhcp-ddns`` attempts to load it and conducts sanity checks.
   Certain checks are possible only while running the actual
   server. The actual status is reported with an exit code (0 =
   configuration looks okay, 1 = error encountered). Kea prints out log
   messages to standard output and errors to standard error when testing
   the configuration.

The ``config.report`` file may also be accessed directly, via the
following command. The binary ``path`` may be found in the install
directory or in the ``.libs`` subdirectory in the source tree. For
example: ``kea/src/bin/d2/.libs/kea-dhcp-ddns``.

::

   strings path/kea-dhcp-ddns | sed -n 's/;;;; //p'

Upon startup, the module loads its configuration and begins listening
for NCRs based on that configuration.

During startup, the server attempts to create a PID file of the form:
``[runstatedir]/[conf name].kea-dhcp-ddns.pid`` where:

-  ``runstatedir`` - is the value as passed into the build configure
   script; it defaults to "/usr/local/var/run". Note that this value may be
   overridden at runtime by setting the environment variable
   ``KEA_PIDFILE_DIR``. This is intended primarily for testing purposes.

-  ``conf name`` - is the configuration file name used to start the server,
   minus all preceding paths and the file extension. For example, given
   a pathname of "/usr/local/etc/kea/myconf.txt", the portion used would
   be "myconf".

If the file already exists and contains the PID of a live process, the
server issues a ``DHCP_DDNS_ALREADY_RUNNING`` log message and exits. It
is possible, though unlikely, that the file is a remnant of a system
crash and the process to which the PID belongs is unrelated to Kea. In
such a case it is necessary to manually delete the PID file.

.. _d2-configuration:

Configuring the DHCP-DDNS Server
================================

Before starting the ``kea-dhcp-ddns`` module for the first time, a
configuration file must be created. The following default configuration
is a template that can be customized to individual requirements.

::

   "DhcpDdns": {
       "ip-address": "127.0.0.1",
       "port": 53001,
       "dns-server-timeout": 100,
       "ncr-protocol": "UDP",
       "ncr-format": "JSON",
       "tsig-keys": [ ],
       "forward-ddns": {
           "ddns-domains": [ ]
       },
       "reverse-ddns": {
           "ddns-domains": [ ]
       }
   }

The configuration can be divided into the following sections, each of
which is described below:

-  *Global Server Parameters* - define values which control connectivity and
   global server behavior.

-  *Control Socket* - defines the Control Socket type and name.

-  *TSIG Key Info* - defines the TSIG keys used for secure traffic with
   DNS servers.

-  *Forward DDNS* - defines the catalog of forward DDNS domains.

-  *Reverse DDNS* - defines the catalog of reverse DDNS domains.

.. _d2-server-parameter-config:

Global Server Parameters
------------------------

-  ``ip-address`` - the IP address on which D2 listens for requests. The
   default is the local loopback interface at address 127.0.0.1.
   Either an IPv4 or IPv6 address may be specified.

-  ``port`` - the port on which D2 listens for requests. The default value
   is 53001.

-  ``dns-server-timeout`` - the maximum amount of time, in milliseconds,
   that D2 will wait for a response from a DNS server to a single DNS
   update message.

-  ``ncr-protocol`` - the socket protocol to use when sending requests to
   D2. Currently only UDP is supported.

-  ``ncr-format`` - the packet format to use when sending requests to D2.
   Currently only JSON format is supported.

D2 must listen for change requests on a known address and port. By
default it listens at 127.0.0.1 on port 53001. The following example
illustrates how to change D2's global parameters so it will listen at
192.168.1.10 port 900:

::

   "DhcpDdns": {
       "ip-address": "192.168.1.10",
       "port": 900,
       ...
       }
   }

.. warning::

   It is possible for a malicious attacker to send bogus
   NameChangeRequests to the DHCP-DDNS server. Addresses other than the
   IPv4 or IPv6 loopback addresses (127.0.0.1 or ::1) should only be
   used for testing purposes; note that local users may still
   communicate with the DHCP-DDNS server.

.. note::

   If the ``ip-address`` and ``port`` are changed, the corresponding values in
   the DHCP servers' ``dhcp-ddns`` configuration section must be changed.

.. _d2-ctrl-channel:

Management API for the D2 Server
--------------------------------

The management API allows the issuing of specific management commands,
such as configuration retrieval or shutdown. For more details, see
:ref:`ctrl-channel`. Currently, the only supported communication
channel type is the UNIX stream socket. By default there are no sockets
open; to instruct Kea to open a socket, the following entry in the
configuration file can be used:

::

   "DhcpDdns": {
       "control-socket": {
           "socket-type": "unix",
           "socket-name": "/path/to/the/unix/socket"
       },
       ...
   }

The length of the path specified by the ``socket-name`` parameter is
restricted by the maximum length for the UNIX socket name on the
operating system, i.e. the size of the ``sun_path`` field in the
``sockaddr_un`` structure, decreased by 1. This value varies on
different operating systems, between 91 and 107 characters. Typical
values are 107 on Linux and 103 on FreeBSD.

Communication over the control channel is conducted using JSON structures.
See the `Control Channel section in the Kea Developer's
Guide <https://reports.kea.isc.org/dev_guide/d2/d96/ctrlSocket.html>`__
for more details.

The D2 server supports the following operational commands:

-  build-report
-  config-get
-  config-reload
-  config-set
-  config-test
-  config-write
-  list-commands
-  shutdown
-  status-get
-  version-get

Since Kea version 2.0.0, the D2 server also supports the following
operational commands for statistics:

-  statistic-get
-  statistic-get-all
-  statistic-reset
-  statistic-reset-all

The ``shutdown`` command supports the extra ``type`` argument, which controls the
way the D2 server cleans up on exit.
The supported shutdown types are:

-  ``normal`` - stops the queue manager and finishes all current transactions
   before exiting. This is the default.

-  ``drain_first`` - stops the queue manager but continues processing requests
   from the queue until it is empty.

-  ``now`` - exits immediately.

An example command may look like this:

::

   {
       "command": "shutdown"
       "arguments": {
           "exit-value": 3,
           "type": "drain_first"
       }
   }

.. _d2-tsig-key-list-config:

TSIG Key List
-------------

A DDNS protocol exchange can be conducted with or without a transaction
signature, or TSIG (defined
in `RFC 2845 <https://tools.ietf.org/html/rfc2845>`__). This
configuration section allows the administrator to define the set of TSIG
keys that may be used in such exchanges.

To use TSIG when updating entries in a DNS domain, a key must be defined
in the TSIG key list and referenced by name in that domain's
configuration entry. When D2 matches a change request to a domain, it
checks whether the domain has a TSIG key associated with it. If so, D2
uses that key to sign DNS update messages sent to and verify
responses received from the domain's DNS server(s). For each TSIG key
required by the DNS servers that D2 is working with, there must be
a corresponding TSIG key in the TSIG key list.

As one might gather from the name, the ``tsig-key`` section of the D2
configuration lists the TSIG keys. Each entry describes a TSIG key used
by one or more DNS servers to authenticate requests and sign responses.
Every entry in the list has three parameters:

-  ``name`` - is a unique text label used to identify this key within the
   list. This value is used to specify which key (if any) should be used
   when updating a specific domain. As long as the name is unique its
   content is arbitrary, although for clarity and ease of maintenance it
   is recommended that it match the name used on the DNS server(s). This
   field cannot be blank.

-  ``algorithm`` - specifies which hashing algorithm should be used with
   this key. This value must specify the same algorithm used for the key
   on the DNS server(s). The supported algorithms are listed below:

   -  HMAC-MD5
   -  HMAC-SHA1
   -  HMAC-SHA224
   -  HMAC-SHA256
   -  HMAC-SHA384
   -  HMAC-SHA512

   This value is not case-sensitive.

-  ``digest-bits`` - is used to specify the minimum truncated length in
   bits. The default value 0 means truncation is forbidden; non-zero
   values must be an integral number of octets, and be greater than both
   80 and half of the full length. (Note that in BIND 9 this parameter
   is appended to the algorithm name, after a dash.)

-  ``secret`` - is used to specify the shared secret key code for this
   key. This value is case-sensitive and must exactly match the value
   specified on the DNS server(s). It is a base64-encoded text value.

As an example, suppose that a domain D2 will be updating is maintained
by a BIND 9 DNS server, which requires dynamic updates to be secured
with TSIG. Suppose further that the entry for the TSIG key in BIND 9's
named.conf file looks like this:

::

      :
      key "key.four.example.com." {
          algorithm hmac-sha224;
          secret "bZEG7Ow8OgAUPfLWV3aAUQ==";
      };
      :

By default, the TSIG key list is empty:

::

   "DhcpDdns": {
      "tsig-keys": [ ],
      ...
   }

A new key must be added to the list:

::

   "DhcpDdns": {
       "tsig-keys": [
           {
               "name": "key.four.example.com.",
               "algorithm": "HMAC-SHA224",
               "secret": "bZEG7Ow8OgAUPfLWV3aAUQ=="
           }
       ],
       ...
   }

These steps must be repeated for each TSIG key needed, although the
same TSIG key can be used with more than one domain.

.. _d2-forward-ddns-config:

Forward DDNS
------------

The forward DDNS section is used to configure D2's forward-update
behavior. Currently it contains a single parameter, the catalog of
forward DDNS domains, which is a list of structures.

::

   "DhcpDdns": {
       "forward-ddns": {
           "ddns-domains": [ ]
       },
       ...
   }

By default, this list is empty, which causes the server to ignore
the forward-update portions of requests.

.. _add-forward-ddns-domain:

Adding Forward DDNS Domains
~~~~~~~~~~~~~~~~~~~~~~~~~~~

A forward DDNS domain maps a forward DNS zone to a set of DNS servers
which maintain the forward DNS data (i.e. name-to-address mapping) for
that zone. Each zone served needs one forward DDNS domain.
Some or all of the zones may be maintained by the same
servers, but one DDNS domain is still needed for each zone. Remember that
matching a request to the appropriate server(s) is done by zone and a
DDNS domain only defines a single zone.

This section describes how to add forward DDNS domains; repeat these
steps for each forward DDNS domain desired. Each forward DDNS domain has
the following parameters:

-  ``name`` - this is the fully qualified domain name (or zone) that this DDNS
   domain can update. This value is compared against the request FQDN
   during forward matching. It must be unique within the catalog.

-  ``key-name`` - if TSIG is used with this domain's servers, this value
   should be the name of the key from the TSIG key list. If the
   value is blank (the default), TSIG will not be used in DDNS
   conversations with this domain's servers.

-  ``dns-servers`` - this is a list of one or more DNS servers which can conduct
   the server side of the DDNS protocol for this domain. The servers are
   used in a first-to-last preference; in other words, when D2 begins to
   process a request for this domain, it will pick the first server in
   this list and attempt to communicate with it. If that attempt fails,
   D2 will move to the next one in the list and so on, until either it
   is successful or the list is exhausted.

To create a new forward DDNS domain, add a new domain element and set
its parameters:

::

   "DhcpDdns": {
       "forward-ddns": {
           "ddns-domains": [
               {
                   "name": "other.example.com.",
                   "key-name": "",
                   "dns-servers": [
                   ]
               }
           ]
       }
   }

It is possible to add a domain without any servers; however, if that
domain matches a request, the request will fail. To make the domain
useful, at least one DNS server must be added to it.

.. _add-forward-dns-servers:

Adding Forward DNS Servers
^^^^^^^^^^^^^^^^^^^^^^^^^^

This section describes how to add DNS servers to a forward DDNS domain.
Repeat these instructions as needed for all the servers in each domain.

Forward DNS server entries represent actual DNS servers which support
the server side of the DDNS protocol. Each forward DNS server has the
following parameters:

-  ``hostname`` - the resolvable host name of the DNS server; this
   parameter is not yet implemented.

-  ``ip-address`` - the IP address at which the server listens for DDNS
   requests. This may be either an IPv4 or an IPv6 address.

-  ``port`` - the port on which the server listens for DDNS requests. It
   defaults to the standard DNS service port of 53.

To create a new forward DNS server, a new server element must be added to
the domain and its parameters filled in. If, for example, the service is
running at "172.88.99.10", set the forward DNS server as follows:

::

   "DhcpDdns": {
       "forward-ddns": {
           "ddns-domains": [
               {
                   "name": "other.example.com.",
                   "key-name": "",
                   "dns-servers": [
                       {
                           "ip-address": "172.88.99.10",
                           "port": 53
                       }
                   ]
               }
           ]
       }
   }

.. note::

   Since ``hostname`` is not yet supported, the parameter ``ip-address``
   must be set to the address of the DNS server.

.. _d2-reverse-ddns-config:

Reverse DDNS
------------

The reverse DDNS section is used to configure D2's reverse update
behavior, and the concepts are the same as for the forward DDNS section.
Currently it contains a single parameter, the catalog of reverse DDNS
domains, which is a list of structures.

::

   "DhcpDdns": {
       "reverse-ddns": {
           "ddns-domains": [ ]
       }
       ...
   }

By default, this list is empty, which causes the server to ignore
the reverse-update portions of requests.

.. _add-reverse-ddns-domain:

Adding Reverse DDNS Domains
~~~~~~~~~~~~~~~~~~~~~~~~~~~

A reverse DDNS domain maps a reverse DNS zone to a set of DNS servers
which maintain the reverse DNS data (address-to-name mapping) for that
zone. Each zone served needs one reverse DDNS domain.
Some or all of the zones may be maintained by the same servers, but
one DDNS domain entry is needed for each zone. Remember that
matching a request to the appropriate server(s) is done by zone and a
DDNS domain only defines a single zone.

This section describes how to add reverse DDNS domains; repeat these
steps for each reverse DDNS domain desired. Each reverse DDNS domain has
the following parameters:

-  ``name`` - this is the fully qualified reverse zone that this DDNS domain can
   update. This is the value used during reverse matching, which
   compares it with a reversed version of the request's lease address.
   The zone name should follow the appropriate standards; for example,
   to support the IPv4 subnet 172.16.1, the name should be
   "1.16.172.in-addr.arpa.". Similarly, to support an IPv6 subnet of
   2001:db8:1, the name should be "1.0.0.0.8.B.D.0.1.0.0.2.ip6.arpa."
   The name must be unique within the catalog.

-  ``key-name`` - if TSIG is used with this domain's servers,
   this value should be the name of the key from the TSIG key list. If
   the value is blank (the default), TSIG will not be used in DDNS
   conversations with this domain's servers.

-  ``dns-servers`` - this is a list of one or more DNS servers which can conduct
   the server side of the DDNS protocol for this domain. Currently, the
   servers are used in a first-to-last preference; in other words, when
   D2 begins to process a request for this domain, it will pick the
   first server in this list and attempt to communicate with it. If that
   attempt fails, D2 will move to the next one in the list and so on,
   until either it is successful or the list is exhausted.

To create a new reverse DDNS domain, a new domain element must be added
and its parameters set. For example, to support subnet 2001:db8:1::, the
following configuration could be used:

::

   "DhcpDdns": {
       "reverse-ddns": {
           "ddns-domains": [
               {
                   "name": "1.0.0.0.8.B.D.0.1.0.0.2.ip6.arpa.",
                   "key-name": "",
                   "dns-servers": [
                   ]
               }
           ]
       }
   }

It is possible to add a domain without any servers; however, if that
domain matches a request, the request will fail. To make the domain
useful, at least one DNS server must be added to it.

.. _add-reverse-dns-servers:

Adding Reverse DNS Servers
^^^^^^^^^^^^^^^^^^^^^^^^^^

This section describes how to add DNS servers to a reverse DDNS domain.
Repeat these instructions as needed for all the servers in each domain.

Reverse DNS server entries represent actual DNS servers which support
the server side of the DDNS protocol. Each reverse DNS server has the
following parameters:

-  ``hostname`` - the resolvable host name of the DNS server; this value
   is currently ignored.

-  ``ip-address`` - the IP address at which the server listens for DDNS
   requests.

-  ``port`` - the port on which the server listens for DDNS requests. It
   defaults to the standard DNS service port of 53.

To create a new reverse DNS server, a new server
element must be added to the domain and its parameters specified. If, for example, the
service is running at "172.88.99.10", then set it as follows:

::

   "DhcpDdns": {
       "reverse-ddns": {
           "ddns-domains": [
               {
                   "name": "1.0.0.0.8.B.D.0.1.0.0.2.ip6.arpa.",
                   "key-name": "",
                   "dns-servers": [
                       {
                           "ip-address": "172.88.99.10",
                           "port": 53
                       }
                   ]
               }
           ]
       }
   }

.. note::

   Since ``hostname`` is not yet supported, the parameter ``ip-address``
   must be set to the address of the DNS server.

.. _per-server-keys:

Per-DNS-Server TSIG Keys
~~~~~~~~~~~~~~~~~~~~~~~~

Since Kea version 2.0.0, a TSIG key can be specified in a DNS server
configuration. The priority rule is:

-  if a not-empty key name is specified in a DNS server entry, this TSIG
   key protects DNS updates sent to this server.

-  if the DNS server entry is empty, but a
   not-empty key name is specified in the parent's domain entry, the parent domain's
   TSIG key protects DNS updates sent to this server.

-  if the DNS server entry is empty, and no key name is specified in its parent
   domain entry, no TSIG protects DNS updates sent to this server.

For instance, in this configuration:

::

   "DhcpDdns": {
       "forward-ddns": {
           "ddns-domains": [
               {
                   "name": "other.example.com.",
                   "key-name": "foo",
                   "dns-servers": [
                       {
                           "ip-address": "172.88.99.10",
                           "port": 53
                       },
                       {
                           "ip-address": "172.88.99.11",
                           "port": 53,
                           "key-name": "bar"
                       }
                   ]
               }
           ]
       },
       "reverse-ddns": {
           "ddns-domains": [
               {
                   "name": "1.0.0.0.8.B.D.0.1.0.0.2.ip6.arpa.",
                   "dns-servers": [
                       {
                           "ip-address": "172.88.99.12",
                           "port": 53
                       },
                       {
                           "ip-address": "172.88.99.13",
                           "port": 53,
                           "key-name": "bar"
                       }
                   ]
               }
           ]
       },
       "tsig-keys": [
           {
               "name": "foo",
               "algorithm": "HMAC-MD5",
               "secret": "LSWXnfkKZjdPJI5QxlpnfQ=="
           },
           {
               "name": "bar",
               "algorithm": "HMAC-SHA224",
               "secret": "bZEG7Ow8OgAUPfLWV3aAUQ=="
           }
       ]
   }


The 172.88.99.10 server will use the "foo" TSIG key, the 172.88.99.11 and
172.88.99.13 servers will use the "bar" key. and 172.88.99.12 will not use TSIG.

.. _d2-user-contexts:

User Contexts in DDNS
---------------------

See :ref:`user-context` for additional background regarding the user
context idea.

User contexts can be specified on a global scope, a DDNS domain, a DNS server,
a TSIG key, and loggers. One other useful usage is the ability to store
comments or descriptions; the parser translates a "comment" entry into a
user context with the entry, which allows a comment to be attached
inside the configuration itself.

.. _d2-example-config:

Example DHCP-DDNS Server Configuration
--------------------------------------

This section provides a sample DHCP-DDNS server configuration, based on
a small example network. Let's suppose our example network has three
domains, each with their own subnet.

.. table:: Our example network

   +------------------+-----------------+-----------------+-----------------+
   | Domain           | Subnet          | Forward DNS     | Reverse DNS     |
   |                  |                 | Servers         | Servers         |
   +==================+=================+=================+=================+
   | four.example.com | 192.0.2.0/24    | 172.16.1.5,     | 172.16.1.5,     |
   |                  |                 | 172.16.2.5      | 172.16.2.5      |
   +------------------+-----------------+-----------------+-----------------+
   | six.example.com  | 2001:db8:1::/64 | 3001:1::50      | 3001:1::51      |
   +------------------+-----------------+-----------------+-----------------+
   | example.com      | 192.0.0.0/16    | 172.16.2.5      | 172.16.2.5      |
   +------------------+-----------------+-----------------+-----------------+

We need to construct three forward DDNS domains:

.. table:: Forward DDNS domains needed

   +----+-------------------+------------------------+
   | #  | DDNS Domain Name  | DNS Servers            |
   +====+===================+========================+
   | 1. | four.example.com. | 172.16.1.5, 172.16.2.5 |
   +----+-------------------+------------------------+
   | 2. | six.example.com.  | 3001:1::50             |
   +----+-------------------+------------------------+
   | 3. | example.com.      | 172.16.2.5             |
   +----+-------------------+------------------------+

As discussed earlier, FQDN-to-domain matching is based on the longest
match. The FQDN "myhost.four.example.com." matches the first domain
("four.example.com"), while "admin.example.com." matches the third
domain ("example.com"). The FQDN "other.example.net." fails to
match any domain and is rejected.

The following example configuration specifies the forward DDNS domains.

::

   "DhcpDdns": {
       "comment": "example configuration: forward part",
       "forward-ddns": {
           "ddns-domains": [
               {
                   "name": "four.example.com.",
                   "key-name": "",
                   "dns-servers": [
                       { "ip-address": "172.16.1.5" },
                       { "ip-address": "172.16.2.5" }
                   ]
               },
               {
                   "name": "six.example.com.",
                   "key-name": "",
                   "dns-servers": [
                       { "ip-address": "2001:db8::1" }
                   ]
               },
               {
                   "name": "example.com.",
                   "key-name": "",
                   "dns-servers": [
                       { "ip-address": "172.16.2.5" }
                   ],
                   "user-context": { "backup": false }
               },

           ]
       }
   }

Similarly, we need to construct the three reverse DDNS domains:

.. table:: Reverse DDNS domains needed

   +----+-----------------------------------+------------------------+
   | #  | DDNS Domain Name                  | DNS Servers            |
   +====+===================================+========================+
   | 1. | 2.0.192.in-addr.arpa.             | 172.16.1.5, 172.16.2.5 |
   +----+-----------------------------------+------------------------+
   | 2. | 1.0.0.0.8.d.b.0.1.0.0.2.ip6.arpa. | 3001:1::50             |
   +----+-----------------------------------+------------------------+
   | 3. | 0.182.in-addr.arpa.               | 172.16.2.5             |
   +----+-----------------------------------+------------------------+

An address of "192.0.2.150" matches the first domain,
"2001:db8:1::10" matches the second domain, and "192.0.50.77" matches the
third domain.

These reverse DDNS domains are specified as follows:

::

   "DhcpDdns": {
       "comment": "example configuration: reverse part",
       "reverse-ddns": {
           "ddns-domains": [
               {
                   "name": "2.0.192.in-addr.arpa.",
                   "key-name": "",
                   "dns-servers": [
                       { "ip-address": "172.16.1.5" },
                       { "ip-address": "172.16.2.5" }
                   ]
               }
               {
                   "name": "1.0.0.0.8.B.D.0.1.0.0.2.ip6.arpa.",
                   "key-name": "",
                   "dns-servers": [
                       { "ip-address": "2001:db8::1" }
                   ]
               }
               {
                   "name": "0.192.in-addr.arpa.",
                   "key-name": "",
                   "dns-servers": [
                       { "ip-address": "172.16.2.5" }
                   ]
               }
           ]
       }
   }

DHCP-DDNS Server Statistics
===========================

Kea version 2.0.0 introduced statistics support for DHCP-DDNS.

Statistics are divided into three groups: NameChangeRequests, DNS updates,
and per-TSIG-key DNS updates. While the statistics of the first two groups
are cumulative, i.e. not affected by configuration change or reload,
per-key statistics are reset to 0 when the underlying object is
(re)created.

Currently Kea's statistics management has the following limitations:

-  only integer samples (i.e. a counter and a timestamp) are used;
-  the maximum sample count is 1;
-  there is no API to remove one or all statistics;
-  there is no API to set the maximum sample count or age.

.. note::

    Hook libraries, such as the the ISC subscriber-only GSS-TSIG library,
    make new statistics available in Kea.

More information about Kea statistics can be found at :ref:`stats`.

NCR Statistics
--------------

The NameChangeRequest statistics are:

-  ``ncr-received`` - the number of received valid NCRs
-  ``ncr-invalid`` - the number of received invalid NCRs
-  ``ncr-error`` - the number of errors in NCR receptions other than an I/O cancel on shutdown

DNS Update Statistics
---------------------

The global DNS update statistics are:

-  ``update-sent`` - the number of DNS updates sent
-  ``update-signed`` - the number of DNS updates sent and protected by TSIG
-  ``update-unsigned`` - the number of DNS updates sent and not protected by TSIG
-  ``update-success`` - the number of DNS updates which successfully completed
-  ``update-timeout`` - the number of DNS updates which completed on timeout
-  ``update-error`` - the number of DNS updates which completed with an error other than
   timeout

Per-TSIG-Key DNS Update Statistics
----------------------------------

The per TSIG key DNS update statistics are:

-  ``update-sent`` - the number of DNS updates sent
-  ``update-success`` - the number of DNS updates which successfully completed
-  ``update-timeout`` - the number of DNS updates which completed on timeout
-  ``update-error`` - the number of DNS updates which completed with an error other than
   timeout

The name format for per-key statistics is ``key[<key-DNS-name>].<stat-name>``:
for instance, the name of the ``update-sent`` statistics for the
``key.example.com.`` TSIG key is ``key[key.example.com.].update-sent``.

DHCP-DDNS Server Limitations
============================

The following are the current limitations of the DHCP-DDNS server.

-  Requests received from the DHCP servers are placed in a queue until
   they are processed. Currently, all queued requests are lost if the
   server shuts down.

Supported Standards
===================

The following RFCs are supported by the DHCP-DDNS server:

- *Secret Key Transaction Authentication for DNS (TSIG)*, `RFC 2845
  <https://tools.ietf.org/html/rfc2845>`__: All DNS update packets sent and
  received by the DHCP-DDNS server can be protected by TSIG signatures.

- *Dynamic Updates in the Domain Name System (DNS UPDATE)*, `RFC 2136
  <https://tools.ietf.org/html/rfc2136>`__: The complete DNS update mechanism is
  supported.

- *Resolution of Fully Qualified Domain Name (FQDN) Conflicts among Dynamic Host
  Configuration Protocol (DHCP) Clients*, `RFC 4703
  <https://tools.ietf.org/html/rfc4703>`__: DHCP-DDNS takes care of
  conflict resolution, for both DHCPv4 and DHCPv6 servers.

- *A DNS Resource Record (RR) for Encoding Dynamic Host Configuration Protocol
  (DHCP) Information (DHCID RR)*, `RFC 4701
  <https://tools.ietf.org/html/rfc4701>`__: The DHCP-DDNS server uses DHCID
  records.
