.. _gss-tsig:

GSS-TSIG
========

.. _gss-tsig-overview:

GSS-TSIG Overview
-----------------

Kea provides support for DNS updates, which can be protected using
Transaction Signatures (or TSIG). This protection is often adequate.
However, some systems, in particular Active Directory (AD) on Microsoft
Windows servers, have chosen to adopt a more complex GSS-TSIG approach that offers
additional capabilities, such as using negotiated dynamic keys.

Kea supports GSS-TSIG to protect DNS updates sent by
the Kea DHCP-DDNS (D2) server in a premium hook, called ``gss_tsig``.

GSS-TSIG is defined in `RFC 3645 <https://tools.ietf.org/html/rfc3645>`__.
The GSS-TSIG protocol itself is an implementation of generic GSS-API v2
services, defined in `RFC 2743 <https://tools.ietf.org/html/rfc2743>`__.

Many protocols are involved in this mechanism:

 - Kerberos 5 - `RFC 4120 <https://tools.ietf.org/html/rfc4120>`__, which
   provides the security framework;
 - GSS-API (Generic Security Services Application Program Interface) -
   `RFC 2743 <https://tools.ietf.org/html/rfc2743>`__ for the API,
   `RFC 2744 <https://tools.ietf.org/html/rfc2743>`__ for the C bindings, and
   `RFC 4121 <https://tools.ietf.org/html/rfc4121>`__ for the application
   to Kerberos 5;
 - SPNEGO (Simple and Protected GSS-API Negotiation Mechanism) -
   `RFC 4178 <https://tools.ietf.org/html/rfc4178>`__ for the negotiation;
 - DNS update `RFC 2136 <https://tools.ietf.org/html/rfc2136>`__;
 - TSIG (Secret Key Transaction Authentication for DNS) -
   `RFC 8945 <https://tools.ietf.org/html/rfc8945>`__, which
   protects DNS exchanges;
 - Secure Domain Name System (DNS) Dynamic Update -
   `RFC 3007 <https://tools.ietf.org/html/rfc3007>`__, which is the
   application of TSIG to DNS update protection;
 - TKEY (Secret Key Establishment for DNS) -
   `RFC 2930 <https://tools.ietf.org/html/rfc2930>`__, which establishes
   secret keys for TSIG by transmitting crypto payloads between DNS
   parties; and
 - GSS-TSIG - `RFC 3645 <https://tools.ietf.org/html/rfc3645>`__, which
   is the application of GSS-API to TSIG.

To summarize, GSS-API for Kerberos 5 with SPNEGO and TKEY are used to
negotiate a security context between the Kea D2 server and a DNS server:

.. figure:: ../uml/tkey.*

The security context is then used by GSS-TSIG to protect updates:

.. figure:: ../uml/update.*

The Kea implementation of GSS-TSIG uses a GSS-API for Kerberos 5 with
the SPNEGO library. Two implementations meet this criteria: MIT Kerberos
5 and Heimdal.

.. _gss-tsig-install:

GSS-TSIG Compilation
--------------------

The following procedure was tested on Ubuntu 20.10 and 21.04. A similar
approach can be applied to other systems.

1.  Obtain the Kea sources and premium packages, extract the Kea sources,
    and then extract the premium packages into the ``premium/`` directory within the Kea
    source tree.

2. Run autoreconf:

.. code-block:: console

    autoreconf -i

3. Make sure ``./configure --help`` shows the ``--with-gssapi`` option.

4. Install either the MIT (``libkrb5-dev``) or the Heimdal (``heimdal-dev``) library,
   for instance:

.. code-block:: console

    sudo apt install libkrb5-dev

5. Run ``configure`` with the ``--with-gssapi`` option:

.. code-block:: console

    ./configure --with-gssapi

.. note:

    It is ``--with-gssapi`` (with no dash between "gss" and "api"), to maintain
    consistency with the BIND 9 option.

The ``--with-gssapi`` parameter requires the ``krb5-config`` tool to be present. This
tool is provided by both MIT Kerberos 5 and Heimdal; however, on some systems
where both Kerberos 5 and Heimdal are installed, it is a symbolic link
to one of them. If the tool is not in the standard location, it can be specified
with ``--with-gssapi=/path/to/krb5-config``. It is strongly recommended
to use the default installation locations provided by the packages.

The ``./configure`` script should complete with a successful GSS-API
detection, similar to this:

::

    GSS-API support:
      GSSAPI_CFLAGS:         -isystem /usr/include/mit-krb5
      GSSAPI_LIBS:           -L/usr/lib/x86_64-linux-gnu/mit-krb5 -Wl,-Bsymbolic-functions -Wl,-z,relro -lgssapi_krb5 -lkrb5 -lk5crypto -lcom_err

6.  Compile ``make -jX``, where X is the number of CPU cores
    available.

7.  After compilation, the ``gss_tsig`` hook is available in the
    ``premium/src/hooks/d2/gss_tsig`` directory. It can be loaded by
    the Kea DHCP-DDNS (D2) daemon.

The ``gss_tsig`` hook library was developed using the MIT Kerberos 5 implementation, but
Heimdal is also supported. Note that Heimdal is picky about
security-sensitive file permissions and is known to emit an unclear error message.
It is a good idea to keep these files plain, with one link and no
access for the group or other users.

The ``krb5-config`` script should provide an ``--all`` option which
identifies the implementation.

.. _gss-tsig-deployment:

GSS-TSIG Deployment
-------------------

Before using GSS-TSIG, a GSS-TSIG capable DNS server, such as BIND 9
or Microsoft Active Directory (AD), must be deployed. Other
GSS-TSIG capable implementations may work, but have not been tested.

Kerberos 5 Setup
~~~~~~~~~~~~~~~~

There are two kinds of key tables (keytab files): the system one used
by servers, and client tables used by clients. For Kerberos 5, Kea is a
**client**.

Install the Kerberos 5 client library and ``kadmin`` tool:

.. code-block:: console

    sudo apt install krb5-kdc krb5-admin-server

The following examples use the ``EXAMPLE.ORG`` realm to demonstrate required
configuration steps and settings.

The Kerberos 5 client library must be configured to accept incoming requests
for the realm ``EXAMPLE.ORG`` by updating the ``krb5.conf`` file
(e.g. on Linux: /etc/krb5.conf):

.. code-block:: ini

    [libdefaults]
        default_realm = EXAMPLE.ORG
        kdc_timesync = 1
        ccache_type = 4
        forwardable = true
        proxiable = true

    [realms]
        EXAMPLE.ORG = {
                kdc = kdc.example.org
                admin_server = kdc.example.org
        }

In addition to the ``krb5.conf`` file, the ``kdc.conf`` file can be used
(e.g. on Linux: /etc/krb5kdc/kdc.conf):

.. code-block:: ini

    [kdcdefaults]
        kdc_ports = 750,88

    [realms]
        EXAMPLE.ORG = {
            database_name = /var/lib/krb5kdc/principal
            admin_keytab = FILE:/etc/krb5kdc/kadm5.keytab
            acl_file = /etc/krb5kdc/kadm5.acl
            key_stash_file = /etc/krb5kdc/stash
            kdc_ports = 750,88
            max_life = 10h 0m 0s
            max_renewable_life = 7d 0h 0m 0s
            master_key_type = des3-hmac-sha1
            #supported_enctypes = aes256-cts:normal aes128-cts:normal
            default_principal_flags = +preauth
        }

The ``kadmind`` daemon Access Control List (ACL) must be configured to give
permissions to the DNS client principal to access the Kerberos 5 database
(e.g. on Linux: /etc/krb5kdc/kadm5.acl):

.. code-block:: ini

    DHCP/admin.example.org@EXAMPLE.ORG       *

The administrator password for the default realm must be set:

.. code-block:: console

    krb5_newrealm

After the following message is displayed, enter
the password for the default realm:

.. code-block:: console

    This script should be run on the master KDC/admin server to initialize
    a Kerberos realm.  It will ask you to type in a master key password.
    This password will be used to generate a key that is stored in
    /etc/krb5kdc/stash.  You should try to remember this password, but it
    is much more important that it be a strong password than that it be
    remembered.  However, if you lose the password and /etc/krb5kdc/stash,
    you cannot decrypt your Kerberos database.
    Loading random data
    Initializing database '/var/lib/krb5kdc/principal' for realm 'EXAMPLE.ORG',
    master key name 'K/M@EXAMPLE.ORG'
    You will be prompted for the database Master Password.
    It is important that you NOT FORGET this password.
    Enter KDC database master key:

Then retype the password:

.. code-block:: console

    Re-enter KDC database master key to verify:

If successfully applied, the following message is displayed:

.. code-block:: console

    Now that your realm is set up you may wish to create an administrative
    principal using the addprinc subcommand of the kadmin.local program.
    Then, this principal can be added to /etc/krb5kdc/kadm5.acl so that
    you can use the kadmin program on other computers.  Kerberos admin
    principals usually belong to a single user and end in /admin.  For
    example, if jruser is a Kerberos administrator, then in addition to
    the normal jruser principal, a jruser/admin principal should be
    created.

    Don't forget to set up DNS information so your clients can find your
    KDC and admin servers.  Doing so is documented in the administration
    guide.

The next step is to create the principals for the BIND 9 DNS server
(the service protected by the GSS-TSIG TKEY) and for the DNS client
(the Kea DHCP-DDNS server).

The BIND 9 DNS server principal (used for authentication) is created the
following way:

.. code-block:: console

    kadmin.local -q "addprinc -randkey DNS/server.example.org"

If successfully created, the following message is displayed:

.. code-block:: console

    No policy specified for DNS/server.example.org@EXAMPLE.ORG; defaulting to no policy
    Authenticating as principal root/admin@EXAMPLE.ORG with password.
    Principal "DNS/server.example.org@EXAMPLE.ORG" created.

The DNS server principal must be exported so that it can be used by the BIND 9
DNS server. Only this principal is required, and it is exported to the keytab
file with the name ``dns.keytab``.

.. code-block:: console

    kadmin.local -q "ktadd -k /tmp/dns.keytab DNS/server.example.org"

If successfully exported, the following message is displayed:

.. code-block:: console

    Authenticating as principal root/admin@EXAMPLE.ORG with password.
    Entry for principal DNS/server.example.org with kvno 2, encryption type aes256-cts-hmac-sha1-96 added to keytab WRFILE:/tmp/dns.keytab.
    Entry for principal DNS/server.example.org with kvno 2, encryption type aes128-cts-hmac-sha1-96 added to keytab WRFILE:/tmp/dns.keytab.

The DHCP client principal (used by the Kea DHCP-DDNS server) is created the
following way:

.. code-block:: console

    kadmin.local -q "addprinc -randkey DHCP/admin.example.org"

If successfully created, the following message is displayed:

.. code-block:: console

    No policy specified for DHCP/admin.example.org@EXAMPLE.ORG; defaulting to no policy
    Authenticating as principal root/admin@EXAMPLE.ORG with password.
    Principal "DHCP/admin.example.org@EXAMPLE.ORG" created.

The DHCP client principal must be exported so that it can be used by the
Kea DHCP-DDNS server and the GSS-TSIG hook library. It is exported to the client
keytab file with the name ``dhcp.keytab``.

.. code-block:: console

    kadmin.local -q "ktadd -k /tmp/dhcp.keytab DHCP/admin.example.org"

Finally, the ``krb5-admin-server`` must be restarted:

.. code-block:: console

    systemctl restart krb5-admin-server.service

BIND 9 with GSS-TSIG Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The BIND 9 DNS server must be configured to use GSS-TSIG, and to use the
previously exported DNS server principal from the keytab file ``dns.keytab``.
Updating the ``named.conf`` file is required:

.. code-block:: console

    options {
        ...
        directory "/var/cache/bind";
        dnssec-validation auto;
        listen-on-v6 { any; };
        tkey-gssapi-keytab "/etc/bind/dns.keytab";
    };
    zone "example.org" {
        type master;
        file "/var/lib/bind/db.example.org";
        update-policy {
            grant "DHCP/admin.example.org@EXAMPLE.ORG" zonesub any;
        };
    };
    zone "84.102.10.in-addr.arpa" {
        type master;
        file "/etc/bind/db.10";
    };

The zone files should have an entry for the server principal FQDN
``server.example.org``.

The ``/etc/bind/db.10`` file needs to be created or updated:

.. code-block:: console

    ;
    ; BIND reverse data file for local loopback interface
    ;
    $TTL    604800                      ; 1 week
    @       IN      SOA      server.example.org. root.example.org. (
                             2          ; Serial
                             604800     ; Refresh
                             86400      ; Retry
                             2419200    ; Expire
                             604800     ; Negative Cache TTL
                             )
    ;
    @       IN      NS      ns.
    40      IN      PTR     ns.example.org.

The ``/var/lib/bind/db.example.org`` file needs to be created or updated:

.. code-block:: console

    $ORIGIN .
    $TTL                604800             ; 1 week
    example.org         IN SOA  server.example.org. root.example.org. (
                                8          ; serial
                                604800     ; refresh (1 week)
                                86400      ; retry (1 day)
                                2419200    ; expire (4 weeks)
                                604800     ; minimum (1 week)
                                )
                        NS      example.org.
                        A       ${BIND9_IP_ADDR}
                        AAAA    ::1
    $ORIGIN example.org.
    kdc                 A       ${KDC_IP_ADDR}
    server              A       ${BIND9_IP_ADDR}

After any configuration change the server must be reloaded or
restarted:

.. code-block:: console

    systemctl restart named.service

It is possible to get the status or restart the logs:

.. code-block:: console

    systemctl status named.service
    journalctl -u named | tail -n 30

Windows Active Directory Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This sub-section is based on an Amazon AWS provided Microsoft Windows Server
2016 with Active Directory pre-installed, so it describes only the steps used
for GSS-TSIG deployment. (For the complete configuration process, please refer to
Microsoft's documentation or other external resources. We found `this <https://www.tenforums.com/tutorials/51456-windows-server-2016-setup-local-domain-controller.html>`__ tutorial very
useful during configuration of our internal QA testing systems.)

Two Active Directory (AD) user accounts are needed:
 - the first account is used to download AD information, such as
   the client key table of Kea
 - the second account is mapped to the Kea DHCP client principal

Kea needs to know:
 - the server IP address
 - the domain/realm name: the domain is in lower case, the realm in upper
   case, both without a final dot
 - the server name

The second account (named ``kea`` below) is used to create a Service
Principal Name (SPN):

.. code-block:: console

    setspn -S DHCP/kea.<domain> kea

After a shared secret key is generated and put in a key table file:

.. code-block:: console

    ktpass -princ DHCP/kea.<domain>@<REALM> -mapuser kea +rndpass -mapop set -ptype KRB5_NT_PRINCIPAL -out dhcp.keytab

The ``dhcp.keytab`` takes the same usage as for UNIX Kerberos.

GSS-TSIG Troubleshooting
~~~~~~~~~~~~~~~~~~~~~~~~

While testing GSS-TSIG integration with Active Directory we came across
one very cryptic error:

.. code-block:: console

   INFO  [kea-dhcp-ddns.gss-tsig-hooks/4678.139690935890624] GSS_TSIG_VERIFY_FAILED GSS-TSIG verify failed: gss_verify_mic failed with GSSAPI error:
   Major = 'A token had an invalid Message Integrity Check (MIC)' (393216), Minor = 'Packet was replayed in wrong direction' (100002).

In our case, the problem was that the Kea D2 server was trying to perform an update of a reverse
DNS zone while it was not configured. An easy solution is to add a reverse DNS
zone similar to the one configured in Kea. To do that, open the "DNS Manager" and choose
"DNS" from the list; from the dropdown list, choose "Reverse Lookup Zones"; then
click "Action" and "New Zone"; finally, follow the New Zone Wizard to add a new zone.

The standard requires both anti-replay and sequence services. Experiences with the BIND 9 nsupdate
showed the sequence service led to problems so it is disabled by default in the hook. It seems
the anti-replay service can also lead to problems with Microsoft DNS servers so it is now
configurable. Note that these security services are useless for DNS dynamic update which was
designed to run over UDP so with out of order and duplicated messages.

.. _gss-tsig-using:

Using GSS-TSIG
--------------

There are a number of steps required to enable the GSS-TSIG mechanism:

1. The ``gss_tsig`` hook library must be loaded by the D2 server.
2. The GSS-TSIG-capable DNS servers must be specified with their parameters.

An excerpt from a D2 server configuration is provided below; more examples are available in the
``doc/examples/ddns`` directory in the Kea sources.

.. code-block:: javascript
   :linenos:
   :emphasize-lines: 57-117


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
                            "ip-address": "192.0.2.2",
                            "port": 5300
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
                            // There is a GSS-TSIG definition for this server (see
                            // DhcpDdns/gss-tsig/servers), so it will use
                            // Krb/GSS-TSIG.
                            "ip-address": "192.0.2.1"
                        }
                    ]
                }
            ]
        },

        // The GSS-TSIG hook is loaded and its configuration is specified here.
        "hooks-libraries": [
        {
            "library": "/opt/lib/libddns_gss_tsig.so",
            "parameters": {
                // This section governs the GSS-TSIG integration. Each server
                // mentioned in forward-ddns and/or reverse-ddns needs to have
                // an entry here to be able to use GSS-TSIG defaults (optional,
                // if specified they apply to all the GSS-TSIG servers, unless
                // overwritten on specific server level).

                "server-principal": "DNS/server.example.org@EXAMPLE.ORG",
                "client-principal": "DHCP/admin.example.org@EXAMPLE.ORG",

                // client-keytab and credentials-cache can both be used to
                // store client keys. As credentials cache is more flexible,
                // it is recommended to use it. Typically, using both at the
                // same time may cause problems.
                //
                // "client-keytab": "FILE:/etc/dhcp.keytab", // toplevel only
                "credentials-cache": "FILE:/etc/ccache", // toplevel only
                "gss-replay-flag": true, // GSS anti replay service
                "gss-sequence-flag": false, // no GSS sequence service
                "tkey-lifetime": 3600, // 1 hour
                "rekey-interval": 2700, // 45 minutes
                "retry-interval": 120, // 2 minutes
                "tkey-protocol": "TCP",
                "fallback": false,

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
                        "gss-replay-flag": false, // no GSS anti replay service
                        "gss-sequence-flag": false, // no GSS sequence service
                        "tkey-lifetime": 7200, // 2 hours
                        "rekey-interval": 5400, // 90 minutes
                        "retry-interval": 240, // 4 minutes
                        "tkey-protocol": "TCP",
                        "fallback": true // if no key is available fallback to the
                                         // standard behavior (vs skip this server)
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
identified by their IP+port pairs is defined. If the port is not
specified, the default of 53 is assumed. This is similar to basic mode, with no
authentication done using TSIG keys, with the
exception that static TSIG keys are not referenced by name.

Second, the ``libddns_gss_tsig.so`` library must be specified on the
``hooks-libraries`` list. This hook takes many parameters. The most important
one is ``servers``, which is a list of GSS-TSIG-capable servers. If there are
several servers and they share some characteristics, the values can be specified
in the ``parameters`` scope as defaults. In the example above, the defaults that apply
to all servers, unless otherwise specified on a per-server scope, are defined in
lines 63 through 68. The defaults can be skipped if there is only one server
defined, or if all servers have different values.

.. table:: List of available parameters

   +-------------------+----------+---------+---------------------+--------------------------------+
   | Name              | Scope    | Type    | Default value       | Description                    |
   |                   |          |         |                     |                                |
   +===================+==========+=========+=====================+================================+
   | client-keytab     | global / | string  | empty               | the Kerberos **client** key    |
   |                   | server   |         |                     | table                          |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | credentials-cache | global / | string  | empty               | the Kerberos credentials cache |
   |                   | server   |         |                     |                                |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | server-principal  | global / | string  | empty               | the Kerberos principal name of |
   |                   | server   |         |                     | the DNS server that will       |
   |                   |          |         |                     | receive updates                |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | client-principal  | global / | string  | empty               | the Kerberos principal name of |
   |                   | server   |         |                     | the Kea D2 service             |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | gss-replay-flag   | global / | true /  | true                | require the GSS anti replay    |
   |                   | server   | false   |                     | service (GSS_C_REPLAY_FLAG)    |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | gss-sequence-flag | global / | true /  | false               | require the GSS sequence       |
   |                   | server   | false   |                     | service (GSS_C_SEQUENCE_FLAG)  |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | tkey-protocol     | global / | string  | "TCP"               | the protocol used to establish |
   |                   | server   | "TCP" / |                     | the security context with the  |
   |                   |          | "UDP"   |                     | DNS servers                    |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | tkey-lifetime     | global / | uint32  | | 3600 seconds      | the lifetime of GSS-TSIG keys  |
   |                   | server   |         | | ( 1 hour )        |                                |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | rekey-interval    | global / | uint32  | | 2700 seconds      | the time interval the keys are |
   |                   | server   |         | | ( 45 minutes )    | checked for rekeying           |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | retry-interval    | global / | uint32  | | 120 seconds       | the time interval to retry to  |
   |                   | server   |         | | ( 2 minutes )     | create a key if any error      |
   |                   |          |         |                     | occurred previously            |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | fallback          | global / | true /  | false               | the behavior to fallback to    |
   |                   | server   | false   |                     | non-GSS-TSIG when GSS-TSIG     |
   |                   |          |         |                     | should be used but no GSS-TSIG |
   |                   |          |         |                     | key is available.              |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | exchange-timeout  | global / | uint32  | | 3000 milliseconds | the time used to wait for the  |
   |                   | server   |         | | ( 3 seconds )     | GSS-TSIG TKEY exchange to      |
   |                   |          |         |                     | finish before it timeouts      |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | user-context      | global / | string  | empty               | the user-provided data in JSON |
   |                   | server   |         |                     | format (not used by            |
   |                   |          |         |                     | the GSS-TSIG hook)             |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | comment           | global / | string  | empty               | ignored                        |
   |                   | server   |         |                     |                                |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | id                | server   | string  | empty               | identifier to a DNS server     |
   |                   |          |         |                     | (required)                     |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | domain-names      | server   | list of | empty               | the many-to-one relationship   |
   |                   |          | strings |                     | between D2 DNS servers and     |
   |                   |          |         |                     | GSS-TSIG DNS servers           |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | ip-address        | server   | IPv4 /  | empty               | the IP address at which the    |
   |                   |          | IPv6    |                     | GSS-TSIG DNS server listens    |
   |                   |          | address |                     | for DDNS and TKEY requests     |
   |                   |          |         |                     | (required)                     |
   +-------------------+----------+---------+---------------------+--------------------------------+
   | port              | server   | uint16  | 53                  | the DNS transport port at      |
   |                   |          |         |                     | which the GSS-TSIG DNS server  |
   |                   |          |         |                     | listens for DDNS and TKEY      |
   |                   |          |         |                     | requests                       |
   +-------------------+----------+---------+---------------------+--------------------------------+

The global parameters are described below:

- ``client-keytab`` specifies the Kerberos **client** key table.
  For instance, ``FILE:<filename>`` can be used to point to a specific file.
  This parameter can be specified only once, in the parameters scope,
  and is the equivalent of setting the ``KRB5_CLIENT_KTNAME`` environment
  variable. An empty value is silently ignored.

- ``credentials-cache`` specifies the Kerberos credentials cache.
  For instance, ``FILE:<filename>`` can be used to point to a file or,
  if using a directory which supports more than one principal,
  ``DIR:<directory-path>``.
  This parameter can be specified only once, in the parameters scope,
  and is the equivalent of setting the ``KRB5CCNAME`` environment
  variable. An empty value is silently ignored.

- ``server-principal`` is the Kerberos principal name of the DNS
  server that receives updates. In other words, this is the
  DNS server's name in the Kerberos system. This parameter is
  mandatory, and uses the typical Kerberos notation:
  ``<SERVICE-NAME>/<server-domain-name>@<REALM>``.

- ``client-principal`` is the Kerberos principal name of the Kea D2
  service. It is optional, and uses the typical Kerberos notation:
  ``<SERVICE-NAME>/<server-domain-name>@<REALM>``.

- ``gss-replay-flag`` determines if the GSS anti replay service is
  required. It is by default but this can be disabled.

- ``gss-sequence-flag`` determines if the GSS sequence service is
  required. It is not by default but is required by the standard
  so it can be enabled.

- ``tkey-protocol`` determines which protocol is used to establish the
  security context with the DNS servers. Currently, the only supported
  values are TCP (the default) and UDP.

- ``tkey-lifetime`` determines the lifetime of GSS-TSIG keys in the
  TKEY protocol. The value must be greater than the ``rekey-interval``
  value. It is expressed in seconds and defaults to 3600 (one hour).

- ``rekey-interval`` governs the time interval at which the keys for each configured
  server are checked for rekeying, i.e. when a new key is created to replace the
  current usable one if its age is greater than the ``rekey-interval`` value.
  The value must be smaller than the ``tkey-lifetime`` value (it is recommended
  to be set between 50% and 80% of the ``tkey-lifetime`` value). It is expressed in
  seconds and defaults to 2700 (45 minutes, or 75% of one hour).

- ``retry-interval`` governs the time interval at which to retry to create a key if any
  error occurred previously for any configured server. The value must be smaller
  than the ``rekey-interval`` value, and should be at most 1/3 of the difference
  between ``tkey-lifetime`` and ``rekey-interval``. It is expressed in seconds
  and defaults to 120 (2 minutes).

- ``fallback`` governs the behavior when GSS-TSIG should be used (a
  matching DNS server is configured) but no GSS-TSIG key is available.
  If set to ``false`` (the default), this server is skipped; if
  set to ``true``, the DNS server is ignored and the DNS update
  is sent with the configured DHCP-DDNS protection (e.g. TSIG key), or
  without any protection when none was configured.

- ``exchange-timeout`` governs the amount of time to wait for the GSS-TSIG TKEY
  exchange to finish before the process times out. It is expressed in milliseconds and
  defaults to 3000 (3 seconds).

- ``user-context`` is an optional parameter (see :ref:`user-context`
  for a general description of user contexts in Kea).

- ``comment`` is allowed but currently ignored.

- ``servers`` specifies the list of DNS servers where GSS-TSIG is enabled.

The server map parameters are described below:

- ``id`` assigns an identifier to a DNS server. It is used for statistics
  and commands. It is required, and must be both not empty and unique.

- ``domain-names`` governs the many-to-one relationship between D2 DNS
  servers and GSS-TSIG DNS servers: for each domain name on this list,
  Kea looks for a D2 DNS server for this domain with the specified IP address
  and port. An empty list (the default) means that all domains
  match.

- ``ip-address`` specifies the IP address at which the GSS-TSIG DNS server
  listens for DDNS and TKEY requests. It is a mandatory parameter.

- ``port`` specifies the DNS transport port on which the GSS-TSIG DNS server
  listens for DDNS and TKEY requests. It defaults to 53.

- ``server-principal`` is the Kerberos principal name of the DNS server
  that receives updates. The ``server-principal`` parameter set at the per-server
  level takes precedence over one set at the global level. It is a mandatory parameter which must be specified at
  either the global or the server level.

- ``client-principal`` is the Kerberos principal name of the Kea D2
  service for this DNS server. The ``client-principal`` parameter set at the per-server
  level takes precedence over one set at the global level. It is an optional parameter.

- ``gss-replay-flag`` determines if the GSS anti replay service is
  required. The ``gss-replay-flag`` parameter set at the per-server
  level takes precedence over one set at the global level. It is an optional parameter
  which defaults to true.

- ``gss-sequence-flag`` determines if the GSS sequence service is
  required. The ``gss-sequence-flag`` parameter set at the per-server
  level takes precedence over one set at the global level. It is an optional parameter
  which defaults to false.

- ``tkey-protocol`` determines which protocol is used to establish the
  security context with the DNS server. The ``tkey-protocol`` parameter set at the per-server
  level takes precedence over one set at the global level. The default and supported values
  for the per-server level parameter are the same as
  for the global-level parameter.

- ``tkey-lifetime`` determines the lifetime of GSS-TSIG keys in the
  TKEY protocol for the DNS server. The ``tkey-lifetime`` parameter set at the per-server
  level takes precedence over one set at the global level. The default and supported values
  for the per-server level parameter are the same as
  for the global-level parameter.

- ``rekey-interval`` governs the time interval at which the keys for this particular
  server are checked for rekeying, i.e. when a new key is created to replace the
  current usable one if its age is greater than the ``rekey-interval`` value.
  The value must be smaller than the ``tkey-lifetime`` value (it is recommended
  to be set between 50% and 80% of the ``tkey-lifetime`` value). The ``rekey-interval``
  parameter set at the per-server level takes precedence over one set at the global
  level. The default and supported values for the per-server level parameter are the same as
  for the global-level parameter.

- ``retry-interval`` governs the time interval at which to retry to create a key if any
  error occurred previously for this particular server. The value must be
  smaller than the ``rekey-interval`` value, and should be at most 1/3 of the
  difference between ``tkey-lifetime`` and ``rekey-interval``. The
  ``retry-interval`` parameter set at the per-server level takes precedence over one set at the global
  level. The default and supported values for the per-server level parameter are the same as
  for the global-level parameter.

- ``fallback`` governs the behavior when GSS-TSIG should be used (a
  matching DNS server is configured) but no GSS-TSIG key is available.
  The ``fallback`` parameter set at the per-server level takes precedence over one set at the global
  level. The default and supported values for the per-server level parameter are the same as
  for the global-level parameter..

- ``exchange-timeout`` governs the amount of time to wait for the GSS-TSIG TKEY
  exchange to finish before the process times out. The ``exchange-timeout`` parameter
  set at the per-server level takes precedence over one set at the global
  level. The default and supported values for the per-server level parameter are the same as
  for the global-level parameter.

- ``user-context`` is an optional parameter (see :ref:`user-context`
  for a general description of user contexts in Kea).

- ``comment`` is allowed but currently ignored.

.. note::

    Generally it is not recommended to specify both the client keytab (``client-keytab``)
    and the credentials cache (``credentials-cache``), although this may
    differ between Kerberos implementations. The client keytab is just for
    the client key and is typically used to specify the key explicitly in more
    static manner, while the credentials cache can be used to store multiple
    credentials and can be dynamically updated by the Kerberos library. As such,
    the credentials-cache is more flexible and thus the recommended alternative.

    Also note that only the read access right is needed to use the cache.
    Fetching credentials and updating the cache requires the write access
    right.


GSS-TSIG Automatic Key Removal
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The server periodically deletes keys after they have been expired more than three times the
length of the maximum key lifetime (the ``tkey-lifetime`` parameter).
The user has the option to purge keys on demand by using the ``gss-tsig-purge-all``
command (see :ref:`command-gss-tsig-purge-all`) or the ``gss-tsig-purge`` command
(see :ref:`command-gss-tsig-purge`).


GSS-TSIG Configuration for Deployment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When using Kerberos 5 and BIND 9 as described in :ref:`gss-tsig-deployment`,
the local resolver must point to the BIND 9 ``named`` server address. The
local Kerberos must also be configured by putting the following text into the ``krb5.conf`` file:

.. code-block:: ini

    [libdefaults]
        default_realm = EXAMPLE.ORG
        kdc_timesync = 1
        ccache_type = 4
        forwardable = true
        proxiable = true
    [realms]
        EXAMPLE.ORG = {
                kdc = kdc.example.org
                admin_server = kdc.example.org
        }

With Windows AD, the DNS service is provided by AD, which also provides
the Kerberos service. The required text in the ``krb5.conf`` file becomes:

.. code-block:: ini

    [libdefaults]
        default_realm = <REALM>
        kdc_timesync = 1
        ccache_type = 4
        forwardable = true
        proxiable = true
    [realms]
        ${REALM} = {
                kdc = <AD_IP_ADDR>
                admin_server = <AD_IP_ADDR>
        }

Even when the GSS-API library can use the secret from the client key
table, it is far better for performance to get and cache credentials.

This can be done manually via the command:

.. code-block:: console

    kinit -k -t /tmp/dhcp.keytab DHCP/admin.example.org

or, when using AD:

.. code-block:: console

    kinit -k -t /tmp/dhcp.keytab DHCP/kea.<domain>

The credential cache can be displayed using ``klist``.

In production, it is better to rely on a Kerberos Credential Manager as
the System Security Services Daemon (``sssd``).

When using BIND 9, the server principal is in the form "DNS/server.example.org@EXAMPLE.ORG¨;
with AD, the format is "DNS/<server>.<domain>@<REALM>".

.. _stats-gss-tsig:

GSS-TSIG Statistics
-------------------

The GSS-TSIG hook library introduces new statistics at global and
per-DNS-server levels:

-  ``gss-tsig-key-created`` - the number of created GSS-TSIG keys
-  ``tkey-sent`` - the number of sent TKEY exchange initial requests
-  ``tkey-success`` - the number of TKEY exchanges which completed with a success
-  ``tkey-timeout`` - the number of TKEY exchanges which completed on timeout
-  ``tkey-error`` - the number of TKEY exchanges which completed with an error other than
   a timeout

The relationship between keys and DNS servers is very different between
the D2 code and static TSIG keys, and GSS-TSIG keys and DNS servers:

 - a static TSIG key can be shared between many DNS servers;
 - a GSS-TSIG key is only used by one DNS server inside a dedicated
   set of keys.

.. _commands-gss-tsig:

GSS-TSIG Commands
-----------------

The GSS-TSIG hook library supports some commands, which are described below.

.. _command-gss-tsig-get-all:

The ``gss-tsig-get-all`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command lists all the GSS-TSIG servers and keys.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-get-all"
    }

Here is an example of a response returning one GSS-TSIG server and one key:

.. code-block:: json

    {
        "result": 0,
        "text": "1 GSS-TSIG servers and 1 keys",
        "arguments": {
            "gss-tsig-servers": [
                {
                    "id": "foo",
                    "ip-address": "192.1.2.3",
                    "port": 53,
                    "server-principal": "DNS/foo.com@FOO.COM",
                    "key-name-suffix": "foo.com.",
                    "tkey-lifetime": 3600,
                    "tkey-protocol": "TCP",
                    "keys": [
                        {
                            "name": "1234.sig-foo.com.",
                            "inception-date": "2021-09-05 12:23:36.281176",
                            "server-id": "foo",
                            "expire-date": "2021-09-05 13:23:36.281176",
                            "status": "not yet ready",
                            "tkey-exchange": true
                        }
                    ]
                },
                {
                    "id": "bar",
                    "ip-address": "192.1.2.4",
                    "port": 53,
                    "server-principal": "DNS/bar.com@FOO.COM",
                    "key-name-suffix": "bar.com.",
                    "tkey-lifetime": 7200,
                    "tkey-protocol": "UDP",
                    "keys": [ ]
                }
            ]
        }
    }

.. _command-gss-tsig-get:

The ``gss-tsig-get`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command retrieves information about the specified GSS-TSIG server.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-get",
        "arguments": {
            "server-id": "foo"
        }
    }

Here is an example of a response returning information about the server "foo":

.. code-block:: json

    {
        "result": 0,
        "text": "GSS-TSIG server[foo] found",
        "arguments": {
            "id": "foo",
            "ip-address": "192.1.2.3",
            "port": 53,
            "server-principal": "DNS/foo.com@FOO.COM",
            "key-name-suffix": "foo.com.",
            "tkey-lifetime": 3600,
            "tkey-protocol": "TCP",
            "keys": [
                {
                    "name": "1234.sig-foo.com.",
                    "server-id": "foo",
                    "inception-date": "2021-09-05 12:23:36.281176",
                    "expire-date": "2021-09-05 13:23:36.281176",
                    "status": "not yet ready",
                    "tkey-exchange": true
                }
            ]
        }
    }

.. _command-gss-tsig-list:

The ``gss-tsig-list`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command generates a list of GSS-TSIG server IDs and key names.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-list"
    }

Here is an example of a response returning two GSS-TSIG servers and three keys:

.. code-block:: json

    {
        "result": 0,
        "text": "2 GSS-TSIG servers and 3 keys",
        "arguments": {
            "gss-tsig-servers": [
                "foo",
                "bar"
            ],
            "gss-tsig-keys": [
                "1234.example.com.",
                "5678.example.com.",
                "43888.example.org."
            ]
        }
    }

.. _command-gss-tsig-key-get:

The ``gss-tsig-key-get`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command retrieves information about the specified GSS-TSIG key.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-key-get",
        "arguments": {
            "key-name": "1234.sig-foo.com."
        }
    }

Here is an example of a response returning information about GSS-TSIG key "1234.sig-foo.com.":

.. code-block:: json

    {
        "result": 0,
        "text": "GSS-TSIG key '1234.sig-foo.com.' found",
        "arguments": {
            "name": "1234.sig-foo.com.",
            "server-id": "foo",
            "inception-date": "2021-09-05 12:23:36.281176",
            "expire-date": "2021-09-05 13:23:36.281176",
            "status": "not yet ready",
            "tkey-exchange": true
        }
    }

.. _command-gss-tsig-key-expire:

The ``gss-tsig-key-expire`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command expires the specified GSS-TSIG key.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-key-expire",
        "arguments": {
            "key-name": "1234.sig-foo.com."
        }
    }

Here is an example of a response indicating that GSS-TSIG key "1234.sig-foo.com." has been expired:

.. code-block:: json

    {
        "result": 0,
        "text": "GSS-TSIG key '1234.sig-foo.com.' expired"
    }

.. _command-gss-tsig-key-del:

The ``gss-tsig-key-del`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command deletes the specified GSS-TSIG key.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-key-del",
        "arguments": {
            "key-name": "1234.sig-foo.com."
        }
    }

Here is an example of a response indicating that GSS-TSIG key "1234.sig-foo.com." has been deleted:

.. code-block:: json

    {
        "result": 0,
        "text": "GSS-TSIG key '1234.sig-foo.com.' deleted"
    }

.. _command-gss-tsig-purge-all:

The ``gss-tsig-purge-all`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command removes all unusable GSS-TSIG keys.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-purge-all"
    }

Here is an example of a response indicating that two GSS-TSIG keys have been purged:

.. code-block:: json

    {
        "result": 0,
        "text": "2 purged GSS-TSIG keys"
    }

.. _command-gss-tsig-purge:

The ``gss-tsig-purge`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command removes unusable GSS-TSIG keys for the specified server.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-purge",
        "arguments": {
            "server-id": "foo"
        }
    }

Here is an example of a response indicating that two GSS-TSIG keys for server "foo" have been purged:

.. code-block:: json

    {
        "result": 0,
        "text": "2 purged keys for GSS-TSIG server[foo]"
    }

.. _command-gss-tsig-rekey-all:

The ``gss-tsig-rekey-all`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command unconditionally creates new GSS-TSIG keys (rekeys) for
all DNS servers.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-rekey-all"
    }

Here is an example of a response indicating that a rekey was performed:

.. code-block:: json

    {
        "result": 0,
        "text": "rekeyed"
    }

This command is useful when, for instance, the DHCP-DDNS server is
reconnected to the network.

.. _command-gss-tsig-rekey:

The ``gss-tsig-rekey`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command unconditionally creates new GSS-TSIG keys (rekeys) for
a specified DNS server.

An example command invocation looks like this:

.. code-block:: json

    {
        "command": "gss-tsig-rekey",
        "arguments": {
            "server-id": "foo"
        }
    }

Here is an example of a response indicating that a rekey was performed:

.. code-block:: json

    {
        "result": 0,
        "text": "GSS-TSIG server[foo] rekeyed"
    }

This command is typically used when a DNS server has been rebooted, so
that existing GSS-TSIG keys shared with this server can no longer be used.
