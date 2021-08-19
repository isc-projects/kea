
.. _gss-tsig:

GSS-TSIG
========

.. _gss-tsig-overview:

GSS-TSIG Overview
-----------------

Kea provides a support for DNS updates (as defined in `RFC 2136 <https://tools.ietf.org/html/rfc2136>`__),
which can be protected using Transaction Signatures (or TSIG) as defined in
`RFC 2845 <https://tools.ietf.org/html/rfc2845>`__). This protection
is often adequate. However, some systems, in particular Active Directory (AD)
on Microsoft Windows systems, chose to adopt more complex GSS-TSIG
approach that offers additional capabilities as using negotiated dynamic keys.

Kea provides the support of GSS-TSIG to protect DNS updates sent by
the Kea DHCP-DDNS (aka D2) server in a premium hook, called `gss_tsig`.
The GSS-TSIG is defined in `RFC 3645 <https://tools.ietf.org/html/rfc3645>`__.
The GSS-TSIG protocol itself is an implementation of generic GSS-API v2
services, defined in `RFC 2743 <https://tools.ietf.org/html/rfc2743>`__.

The Kea implementation of GSS-TSIG uses a GSS-API for Kerberos 5 with
SPNEGO library.  Two implementations meet this criteria: MIT Kerberos
5 and the Heimdal libraries.

.. note:

    This capability is a work in progress.

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

.. _gss-tsig-using:

Using GSS-TSIG
--------------

There is a number of steps required to enable the GSS-TSIG mechanism:

1. the gss_tsig DSO has to be loaded by the D2 server
2. the GSS-TSIG capable DNS servers have to be specified with their parameters

An excerpt from D2 server is provided below. More examples are available in the
``doc/examples/ddns`` directory in the Kea sources.

.. code-block:: javascript
   :linenos:
   :emphasize-lines: 52-92

    {
    "DhcpDdns": {
        // The following parameters are used to receive NCRs (NameChangeRequests) from the
        // local Kea DHCP server. Make sure your kea-dhcp4 and kea-dhcp6 matches this.
        "ip-address": "127.0.0.1",
        "port": 53001,
        "dns-server-timeout" : 1000,

        // Forward zone: secure.example.org. It uses GSS-TSIG. It is served by two DNS servers,
        // which listen for DDNS requests at 192.0.2.1 and 192.0.2.2.
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
                        { // This server has an entry in gss/servers and thus will use GSS-TSIG.
                            "ip-address": "192.0.2.1"
                        },
                        { // This server also has an entry there, so will use GSS-TSIG, too.
                            "ip-address": "192.0.2.2"
                        }
                    ]
                }
            ]
        },

        // Reverse zone: we want to update the reverse zone "2.0.192.in-addr-arpa".
        "reverse-ddns":
        {
            "ddns-domains":
            [
                {
                    "name": "2.0.192.in-addr.arpa.",
                    "dns-servers":
                    [
                        {
                            // There is GSS definition for this server (see
                            // DhcpDdns/gss/servers), so it will use Krb/GSS-TSIG.
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
                // This section governs the GSS-TSIG integration. Each server mentioned
                // in forward-ddns and/or reverse-ddns needs to have an entry here to
                // be able to use GSS-TSIG.

                // defaults (optional, if specified they apply to all the GSS servers,
                // unless overwritten on specific server level).

                "server-principal": "DNS/server.example.org@REALM",
                "client-principal": "DHCP/admin.example.org@REALM",
                "client-keytab": "FILE:/etc/krb5.keytab", // toplevel only
                "credentials-cache": "FILE:/etc/ccache", // toplevel only
                "tkey-lifetime": 3600,
                "tkey-protocol": "TCP",

                // The list of GSS-TSIG capable servers
                "servers": [
                    {
                        // First server (identification is required)
                        "domain-names": [ ], // if not specified or empty, will match all domains
                                             // that want to use this IP+port tuple
                        "ip-address": "192.0.2.1",
                        "port": 53,
                        "server-principal": "DNS/server1.example.org@REALM",
                        "client-principal": "DHCP/admin1.example.org@REALM",
                        "tkey-lifetime": 86400, // 24h
                        "tkey-protocol": "TCP"
                    },
                    {
                        // The second server (it has most of the parameters missing
                        // as those are using the defaults specified above)
                        "ip-address": "192.0.2.2",
                        "port": 5300
                    }
                ]
            }
        }
        ]

        // Additional parameters, such as logging, control socket and others omited for clarity.
    }

    }

This configuration file contains a number of extra elements.

First, a list of forward and/or reverse domains with related DNS
servers identified by their IP+port tuples. If port is not specified,
the default of 53 is assumed. This is similar to basic mode with no
authentication or authentication done using TSIG keys, with the
exception that static TSIG keys are not referenced by name.

Second, the ``gss_tsig.so`` library has to be specified on the
``hooks-libraries`` list. This hook takes many parameters. The most
important one is `servers`, which is a list of GSS-TSIG capable
servers.  If there are several servers and they share some
characteristics, the values can be specified in `parameters` scope as
defaults. In the example above, the defaults that apply to all servers
unless otherwise specified on per server scope, are defined in lines
63 through 68. The defaults can be skipped if there is only one server
defined or all servers have different values.

The parameters have the following meaning:

- ``client-keytab`` is pointer to the location of the Kerberos key
  tab. This is usually a single file that is located in
  ``/etc/krb5.keytab``. However, some implementations support schemes
  other than ``FILE:`` and whole directory can be specified using
  ``DIR:``. This parameter can be specified only once, in the
  parameters scope.

- ``credentials-cache`` is Kerberos credentials cache file. As there
  is only one cache for the whole system, this parameter can be
  specified only once, in the parameters scope.

- ``server-principal`` is the Kerberos principal name of the DNS
  server that will receive the updates.  In plain words, this is the
  DNS server's name in the Kerberos system. This parameter is
  mandatory.  It uses the typical Kerberos notation:
  ``<SERVICE-NAME>/domain@REALM``.

- ``client-principal`` is the Kerberos principal name of the Kea D2
  service. It is optional. It uses the typical Kerberos notation:
  ``<SERVICE-NAME>/domain@REALM``.

- ``tkey-protocol`` determines which protocol is used to establish the
  security context with the DNS servers.  Currently the only supported
  value is TCP.

- ``tkey-lifetime`` determines the lifetime of the TKEY session,
  expressed in seconds.
