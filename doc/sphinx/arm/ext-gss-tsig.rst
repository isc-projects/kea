
.. _gss-tsig:

GSS-TSIG
========

.. _gss-tsig-overview:


.. note::

   This capability is a work in progress.

GSS-TSIG Overview
-----------------

Kea provides a support for DNS updates, which can be protected using
Transaction Signatures (or TSIG). This protection
is often adequate. However, some systems, in particular Active Directory (AD)
on Microsoft Windows systems, chose to adopt more complex GSS-TSIG
approach that offers additional capabilities as using negotiated dynamic keys.

Kea provides the support of GSS-TSIG to protect DNS updates sent by
the Kea DHCP-DDNS (aka D2) server in a premium hook, called `gss_tsig`.
The GSS-TSIG is defined in `RFC 3645 <https://tools.ietf.org/html/rfc3645>`__.
The GSS-TSIG protocol itself is an implementation of generic GSS-API v2
services, defined in `RFC 2743 <https://tools.ietf.org/html/rfc2743>`__.

Many protocols are involved in this mechanism:

 - Kerberos 5 `RFC 4120 <https://tools.ietf.org/html/rfc4120>`__ which
   provides the security framework;
 - GSS-API (Generic Security Services Application Program Interface)
   `RFC 2743 <https://tools.ietf.org/html/rfc2743>`__ for the API,
   `RFC 2744 <https://tools.ietf.org/html/rfc2743>`__ for C bindings and
   `RFC 4121 <https://tools.ietf.org/html/rfc4121>`__ for the application
   to Kerberos 5;
 - SPNEGO (Simple and Protected GSS-API Negotiation Mechanism)
   `RFC 4178 <https://tools.ietf.org/html/rfc4178>`__ for the negotiation;
 - DNS update `RFC 2136 <https://tools.ietf.org/html/rfc2136>`__;
 - TSIG (Secret Key Transaction Authentication for DNS)
   `RFC 8945 <https://tools.ietf.org/html/rfc8945>`__ which
   protects DNS exchanges;
 - Secure Domain Name System (DNS) Dynamic Update
   `RFC 3007 <https://tools.ietf.org/html/rfc3007>`__ which is the
   application of TSIG to the DNS update protection;
 - TKEY (Secret Key Establishment for DNS)
   `RFC 2930 <https://tools.ietf.org/html/rfc2930>`__ which establishes
   secret keys for TSIG by transmitting crypto payloads between DNS
   parties;
 - GSS-TSIG `RFC 3645 <https://tools.ietf.org/html/rfc3645>`__ which
   is the application of GSS-API to TSIG.

To summarize, GSS-API for Kerberos 5 with SPNEGO and TKEY are used to
negotiate a security context between the Kea D2 server and a DNS server:

.. figure:: ../uml/tkey.*

The security context is then used by GSS-TSIG to protect updates:

.. figure:: ../uml/update.*

The Kea implementation of GSS-TSIG uses a GSS-API for Kerberos 5 with
SPNEGO library.  Two implementations meet this criteria: MIT Kerberos
5 and Heimdal.

.. _gss-tsig-install:

GSS-TSIG Compilation
--------------------

The following procedure was tested on Ubuntu 20.10 and 21.04. Similar
approach can be applied to other systems.

1.  Obtain the kea sources and premium packages, extract kea sources,
    then extract premium packages into `premium/` directory within Kea
    source tree.

2. Run autoreconf:

.. code-block:: console

    autoreconf -i

3. Make sure ``./configure --help`` shows the ``--with-gssapi`` option.

4. Install either MIT (``libkrb5-dev``) or Heimdal (``heimdal-dev``) library,
   for instance:

.. code-block:: console

    sudo apt install libkrb5-dev

5. Run configure with the ``--with-gssapi`` option:

.. code-block:: console

    ./configure --with-gssapi

.. note:

    It is ``--with-gssapi`` (without dash between gss and api) to keep
    consistency with BIND 9 option.

The ``--with-gssapi`` requires ``krb5-config`` tool to be present. This
tool is provided by both MIT Kerberos 5 and Heimdal, on some systems
where both Kerberos 5 and Heimdal are installed it is a symbolic link
to one of them. If it's not in your standard location, you may specify
it with ``--with-gssapi=/path/to/krb5-config``. It is strongly recommended
to use default installation locations as provided by packages.

The ``./configure`` script should complete with a successful GSS-API
detection, similar to this:

::

    GSS-API support:
      GSSAPI_CFLAGS:         -isystem /usr/include/mit-krb5
      GSSAPI_LIBS:           -L/usr/lib/x86_64-linux-gnu/mit-krb5 -Wl,-Bsymbolic-functions -Wl,-z,relro -lgssapi_krb5 -lkrb5 -lk5crypto -lcom_err

6.  Compile as usual ``make -jX`` where X is the number of CPU cores
    available.

7.  After compilation, the gss_tsig hook is available in the
    ``premium/src/hooks/d2/gss_tsig`` directory. It can be loaded by
    the DHCP-DDNS (D2) daemon.


The gss_tsig was developed using the MIT Kerberos 5 implementation but
Heimdal is supported too. Note that Heimdal is picky about security
sensitive file permissions and is known to emit an unclear error message.
It is a good idea to keep these files as plain, with one link and and
no access for the group or other users.

The krb5-config script should provide an ``--all`` option which
identifies the implementation: in any report about the GSS-TSIG report
please add the result of the ``--all`` option of the krb5-config used
to configure Kea.

.. _gss-tsig-deployment:

GSS-TSIG Deployment
-------------------

Before using GSS-TSIG, a GSS-TSIG capable DNS server, such as BIND 9
or alternatively Microsoft Active Directory, must be deployed. Other
GSS-TSIG capable implementations may work, but were not tested.

Kerberos 5 Setup
~~~~~~~~~~~~~~~~

To be done. One critical detail: there are two kinds of key tables
(keytab files): the system one used by servers and client tables
used by clients. For Kerberos 5 Kea is a **client**.

Bind 9 with GSS-TSIG Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To be done.


Microsoft Active Directory Setup
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To be done.

.. _gss-tsig-using:

Using GSS-TSIG
--------------

There is a number of steps required to enable the GSS-TSIG mechanism:

1. the gss_tsig hook library has to be loaded by the D2 server
2. the GSS-TSIG capable DNS servers have to be specified with their parameters

An excerpt from D2 server is provided below. More examples are available in the
``doc/examples/ddns`` directory in the Kea sources.

.. code-block:: javascript
   :linenos:
   :emphasize-lines: 57-97

    {
    "DhcpDdns": {
        // The following parameters are used to receive NCRs (NameChangeRequests)
        // from the local Kea DHCP server. Make sure your kea-dhcp4 and kea-dhcp6
        // matches this.
        "ip-address": "127.0.0.1",
        "port": 53001,
        "dns-server-timeout" : 1000,

        // Forward zone: secure.example.org. It uses GSS-TSIG. It is served
        // by two DNS servers, which listen for DDNS requests at 192.0.2.1
        // and 192.0.2.2.
        "forward-ddns":
        {
            "ddns-domains":
            [
                // DdnsDomain for zone "secure.example.org."
                {
                    "name": "secure.example.org.",
                    "comment": "DdnsDomain example",
                    "dns-servers":
                    [
                        { // This server has an entry in gss/servers and
                          // thus will use GSS-TSIG.
                            "ip-address": "192.0.2.1"
                        },
                        { // This server also has an entry there, so will
                          // use GSS-TSIG, too.
                            "ip-address": "192.0.2.2"
                        }
                    ]
                }
            ]
        },

        // Reverse zone: we want to update the reverse zone "2.0.192.in-addr.arpa".
        "reverse-ddns":
        {
            "ddns-domains":
            [
                {
                    "name": "2.0.192.in-addr.arpa.",
                    "dns-servers":
                    [
                        {
                            // There is GSS-TSIG definition for this server (see
                            // DhcpDdns/gss-tsig/servers), so it will use
                            // Krb/GSS-TSIG.
                            "ip-address": "192.0.2.1"
                        }
                    ]
                }
            ]
        },

        // Need to add gss-tsig hook here
        "hooks-libraries": [
        {
            "library": "/opt/lib/libdhcp_gss_tsig.so",
            "parameters": {
                // This section governs the GSS-TSIG integration. Each server
                // mentioned in forward-ddns and/or reverse-ddns needs to have
                // an entry here to be able to use GSS-TSIG defaults (optional,
                // if specified they apply to all the GSS-TSIG servers, unless
                // overwritten on specific server level).

                "server-principal": "DNS/server.example.org@EXAMPLE.ORG",
                "client-principal": "DHCP/admin.example.org@EXAMPLE.ORG",
                "client-keytab": "FILE:/etc/krb5.keytab", // toplevel only
                "credentials-cache": "FILE:/etc/ccache", // toplevel only
                "tkey-lifetime": 3600,
                "tkey-protocol": "TCP",

                // The list of GSS-TSIG capable servers
                "servers": [
                    {
                        // First server (identification is required)
                        "id": "server1",
                        "domain-names": [ ], // if not specified or empty, will
                                             // match all domains that want to
                                             // use this IP+port pair
                        "ip-address": "192.0.2.1",
                        "port": 53,
                        "server-principal": "DNS/server1.example.org@EXAMPLE.ORG",
                        "client-principal": "DHCP/admin1.example.org@EXAMPLE.ORG",
                        "tkey-lifetime": 86400, // 24h
                        "tkey-protocol": "TCP"
                    },
                    {
                        // The second server (it has most of the parameters missing
                        // as those are using the defaults specified above)
                        "id": "server2",
                        "ip-address": "192.0.2.2",
                        "port": 5300
                    }
                ]
            }
        }
        ]

        // Additional parameters, such as logging, control socket and
        // others omitted for clarity.
    }

    }

This configuration file contains a number of extra elements.

First, a list of forward and/or reverse domains with related DNS servers
identified by their IP+port pairs is defined. If port is not
specified, the default of 53 is assumed. This is similar to basic mode with no
authentication or authentication done using TSIG keys, with the
exception that static TSIG keys are not referenced by name.

Second, the ``libdhcp_gss_tsig.so`` library has to be specified on the
``hooks-libraries`` list. This hook takes many parameters. The most
important one is `servers`, which is a list of GSS-TSIG capable
servers.  If there are several servers and they share some
characteristics, the values can be specified in `parameters` scope as
defaults. In the example above, the defaults that apply to all servers
unless otherwise specified on per server scope, are defined in lines
63 through 68. The defaults can be skipped if there is only one server
defined or all servers have different values.

The parameters have the following meaning:

- ``client-keytab`` specifies the Kerberos **client** key table.
  For instance, ``FILE:<filename>`` can be used to point to a specific file.
  This parameter can be specified only once, in the parameters scope,
  and is the equivalent of setting the ``KRB5_CLIENT_KTNAME`` environment
  variable.

- ``credentials-cache`` specifies the Kerberos credentials cache.
  For instance ``FILE:<filename>`` can be used to point to a file or
  if using a directory which supports more than one principal
  ``DIR:<directory-path>``.
  This parameter can be specified only once, in the parameters scope,
  and is the equivalent of setting the ``KRB5CCNAME`` environment
  variable.

- ``server-principal`` is the Kerberos principal name of the DNS
  server that will receive updates.  In plain words, this is the
  DNS server's name in the Kerberos system. This parameter is
  mandatory.  It uses the typical Kerberos notation:
  ``<SERVICE-NAME>/<server-domain-name>@<REALM>``.

- ``client-principal`` is the Kerberos principal name of the Kea D2
  service. It is optional. It uses the typical Kerberos notation:
  ``<SERVICE-NAME>/<server-domain-name>@<REALM>``.

- ``tkey-protocol`` determines which protocol is used to establish the
  security context with the DNS servers.  Currently the only supported
  values are TCP (the default) and UDP.

- ``tkey-lifetime`` determines the lifetime of GSS-TSIG keys in the
  TKEY protocol, expressed in seconds. Default value is 3600 (one hour).

- ``user-context`` is an optional parameter (see :ref:`user-context`
  for a general description of user contexts in Kea).

- ``comment`` is allowed but currently ignored.

- ``servers`` specifies the list of DNS servers where GSS-TSIG is enabled.

The server map parameters are:

- ``id`` assigns an identifier to a DNS server. It is used for statistics
  and commands. It is required, must be not empty and unique.

- ``domain-names`` governs the many to one relationship between D2 DNS
  servers and GSS-TSIG DNS servers: for each domain name of this list,
  a D2 DNS server for this domain with the IP address and port is
  looked for. An empty list (the default) means that all domains
  match.

- ``ip-address`` specifies the IP address at which the GSS-TSIG DNS server
  listens for DDNS and TKEY requests. It is a mandatory parameter.

- ``port`` specifies the DNS transport port at which the GSS-TSIG DNS server
  listens for DDNS and TKEY requests. It defaults to 53.

- ``server-principal`` is the Kerberos principal name of the DNS server
  that will receive updates. The per server server principal takes
  precedence. It is a mandatory parameter which must be specified at
  least at the global or the server level.

- ``client-principal`` is the Kerberos principal name of the Kea D2
  service for this DNS server. The per server client principal takes
  precedence. It is an optional parameter i.e. to not specify it at
  both the global and the server level is accepted.

- ``tkey-protocol`` determines which protocol is used to establish the
  security context with the DNS server. The per server TKEY protocol
  takes precedence. Default and supported values are the same as for
  the global level parameter.

- ``tkey-lifetime`` determines the lifetime of GSS-TSIG keys in the
  TKEY protocol for the DNS server. The per server TKEY lifetime takes
  precedence. Default and supported values are the same as for
  the global level parameter.

- ``user-context`` is an optional parameter (see :ref:`user-context`
  for a general description of user contexts in Kea).

- ``comment`` is allowed but currently ignored.

.. _command-gss-tsig:

GSS-TSIG Commands
-----------------

The GSS-TSIG hook library supports some commands.

To be done (only anchors for external references are provided).

.. _command-gss-tsig-get-all:

The gss-tsig-get-all Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _command-gss-tsig-get:

The gss-tsig-get Command
~~~~~~~~~~~~~~~~~~~~~~~~

.. _command-gss-tsig-list:

The gss-tsig-list Command
~~~~~~~~~~~~~~~~~~~~~~~~~

.. _command-gss-tsig-key-get:

The gss-tsig-key-get Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _command-gss-tsig-key-expire:

The gss-tsig-key-expire Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _command-gss-tsig-key-del:

The gss-tsig-key-del Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _command-gss-tsig-purge-all:

The gss-tsig-purge-all Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _command-gss-tsig-purge:

The gss-tsig-purge Command
~~~~~~~~~~~~~~~~~~~~~~~~~~

