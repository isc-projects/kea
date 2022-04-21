.. _hooks-ddns-tuning:

``ddns_tuning``: Tuning DNS updates
===================================

This hook library adds support for fine tuning various DNS update aspects.
Currently it supports procedural host name generation. The DDNS Tuning hook
is a premium feature.

The library, which was added in Kea 2.1.5, can be loaded by the ``kea-dhcp4``
and ``kea-dhcp6`` daemons by adding it to ``hooks-libraries`` element of the
server's configuration:

.. code-block:: javascript

    {
        "hooks-libraries": [
            :
            ,
            {
                "library": "/usr/local/lib/libdhcp_ddns_tuning.so",
                "parameters": {
                    :
                }
            },
            :
        ]
    }

Procedural Host name generation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This hook library provides the ability to generate host names, procedurally, based on
an expression. The expression can be defined globally in the hook parameters, using
`hostname-expr`. If defined globally, it will apply to all hosts in all subnets. The
expressions can use all tokens defined in :ref:`classify`. An example of a global
expression is shown below:

.. code-block:: javascript

    {
        "hooks-libraries": [
            :
            ,
            {
                "library": "/usr/local/lib/libdhcp_ddns_tuning.so",
                "parameters": {
                    :
                    "hostname-expr": "'host-'+hexstring(pkt4.mac,'-')"
                }
            },
            :
        ]
    }

It is also possible to define this parameter in a subnet, using user-context mechanism.
If defined at the subnet level, the expression applies to specific subnet only. If the
subnet expression is defined as empty, "", it suppresses (or disables) the use of a
global expression for that subnet. An example subnet expression is shown below:

.. code-block:: javascript

    "subnet4": [{
        "subnet": "192.0.2.0/24",
        "pools": [{
            "pool": "192.0.2.10 - 192.0.2.20",
        } ],

        // This is a subnet-specific user context.
        "user-context": {
            "ddns-tuning:" {
                "hostame-expr": "'guest-'+Int8ToText(substring(pkt4.yiaddr, 0,1))+'-' \
                                         +Int8ToText(substring(pkt4.yiaddr, 1,2))+'-' \
                                         +Int8ToText(substring(pkt4.yiaddr, 2,3))+'-' \
                                         +Int8ToText(substring(pkt4.yiaddr, 3,4))",
            },
            "last-modified": "2017-09-04 13:32",
            "description": "you can put anything you like here",
            "phones": [ "x1234", "x2345" ],
            "devices-registered": 42,
            "billing": false
        }
    }]

.. note::

   The expression value above uses a slash, '\', to show line continuation. This is for
   clarity only and is not valid JSON supported by Kea parsing. The actual value has
   to be expressed in a single line.

.. note::

   Privacy should be taken into consideration when generating a host name. The host name
   is usually inserted into the DNS, which is a public system. Exposing identifiers that
   can be used to track devices, such as MAC address, are usually a very bad idea.
   The global expression example used MAC address for simplicity.

DHCPv4 host name generation
---------------------------

With this library installed the behavior for ``kea-dhcp4`` when forming host names in
response to a client query (e.g. DISCOVER, REQUEST) is as follows:

  1. If a host name is supplied via a host reservation use it along with the DDNS
  behavioral parameters to form the final host name. Goto step 4.

  2. If the client supplied an FQDN option (option 81) use the domain name value
  specified within it along with the DDNS behavioral parameters to form the final
  host name. Goto step 4.

  3. If the client supplied a host name option (option 12) use the host name specified
  within it along with the DDNS behavioral parameters to form the final host name.

  4. If there is an ddns-tuning in-scope host name expression (either global or subnet),
  calculate the host name using the expression. If the calculated value is not a fully
  qualified name and there is an in-scope ddns-qualifying-suffix, append the suffix.

  5. If the value calculated by the hook is not an empty string and is different than
  the host name formed in the prior steps (1 or 2), the calculated value becomes the
  final host name.

DHCPv6 host name generation
---------------------------

With this library installed the behavior for ``kea-dhcp6`` when forming host names in
response to a client query (e.g. SOLICIT, REQUEST, RENEW, REBIND) is as follows:

  1. If the client supplied an FQDN option (option 39) use the domain name value
  specified within it along with the DDNS behavioral parameters to form the final
  host name. Goto step 4.

  2. If the client did not supply an FQDN but ddns-replace-client-name is either
  ``always`` or ``when-not-present``, then calculate the final form of the host
  name and use it to create an outbound FQDN. Goto step 4.

  3. If there is no outbound FQDN at this point, client name processing for this
  packet stops. Without an outbound FQDN there is no way to communicate a host
  name to the client.

  4. If a host name is supplied via a host reservation use it along with the DDNS
  behavioral parameters to form the final host name, and supersedes the FQDN value
  calculated in steps 1 or 2.

  5. If there is a ddns-tuning in-scope host name expression (either global or subnet),
  calculate the host name using the expression. If the calculated value is not a fully
  qualified name and there is an in-scope ddns-qualifying-suffix, append the suffix.

  6. If the value calculated by the hook is not an empty string and is different than
  the host name formed in the prior steps (1 or 2), the calculated value becomes the
  final host name.
