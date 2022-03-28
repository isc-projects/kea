.. _hooks-ddns-tuning:

``ddns_tuning``: Tuning DNS updates
===================================

This hook library adds support for fine tuning various DNS update aspects.
Currently is supports procedural hostname generation and an ability to fine
tune which devices should do the DNS update. The DDNS Tuning hook is a premium
feature.

The library, which was added in Kea 2.1.4, can be loaded in a
similar way to other hook libraries by the ``kea-dhcp4`` and
``kea-dhcp6`` processes.

.. code-block:: javascript

    {
        "hooks-libraries": [
            {
                "library": "/usr/local/lib/libdhcp_ddns_tuning.so",
                "parameters": {
                    "hostname-expr": "'host-'+hexstring(pkt4.mac,'-')"
                }
            }
        ]
    }

This hook allows generating the hostname procedurally, based on an expression.

The expression can be defined globally in the hook parameters, using `hostname-expr`.
If defined globally, it will apply to all hosts in all subnets. The expressions can use
all tokens defined in :ref:`classify`.

It is also possible to define this parameter in a subnet, using user context mechanism.
If defined at the subnet level, the expression applies to specific subnet only.

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
   The expression value above uses a slash, '\', to show line continuation.  This is for
   clarity only and is not valid JSON supported by Kea parsing.  The actually value has
   to be expressed in a single line.

.. note::

   Privacy should be taken into consideration when generating a hostname. The hostname is
   usually inserted into the DNS, which is a public system. Exposing identifiers that
   can be used to track devices, such as MAC address, are usually a very bad idea.
   The global expression example used MAC address for simplicity.
