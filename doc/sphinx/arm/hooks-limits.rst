.. _hooks-limits:

``limits``: Limits to Manage Lease Allocation and Packet Processing
===================================================================

This hook library enables two types of limits:

1. Lease limiting: allow a maximum of ``n`` leases assigned at any one time.
2. Rate limiting: allow a maximum of ``n`` packets per ``time_unit`` to receive a response.

The Limits hook library is only available to ISC customers with a paid support contract.

.. _hooks-limits-configuration:

Configuration
~~~~~~~~~~~~~

The following examples are for ``kea-dhcp6``, but they apply equally to
``kea-dhcp4``. The wildcards ``"<limit-type>"`` and ``"<limit-value>"`` need to be replaced
with the respective keys and values for each limit type described in the sections following this
one.

The library can be loaded by both ``kea-dhcp4`` and ``kea-dhcp6`` servers by adding its path in the
``"hooks-libraries"`` element of the server's configuration.

.. code-block:: json

    {
      "Dhcp6": {
        "hooks-libraries": [
          {
            "library": "/usr/local/lib/libdhcp_limits.so"
          }
        ]
      }
    }

This alone does not limit anything. The desired limits are added to the user context in the
configuration portion of the element that identifies the clients to be limited: a client class or a
subnet. Upon reconfiguration, if Kea picked up on the configured limits, it logs one line for
each configured limit. The log message contains ``LIMITS_CONFIGURED`` in its identifier.

This is how a lease limit is defined for a client class:

.. code-block:: json

    {
      "Dhcp6": {
        "client-classes": [
          {
            "name": "cable-modem-1",
            "test": "option[123].hex == 0x000C4B1E",
            "user-context": {
              "limits": {
                "<limit>": "<limit-value>"
              }
            }
          }
        ]
      }
    }

This is how a lease limit is defined for a global subnet:

.. code-block:: json

    {
      "Dhcp6": {
        "subnet6": [
          {
            "id": 1,
            "subnet": "2001:db8::/64",
            "user-context": {
              "limits": {
                "<limit>": "<limit-value>"
              }
            }
          }
        ]
      }
    }

This is how a lease limit is defined for a subnet inside a shared network:

.. code-block:: json

    {
      "Dhcp6": {
        "shared-networks": [
          {
            "subnet6": [
              {
                "id": 1,
                "subnet": "2001:db8::/64",
                "user-context": {
                  "limits": {
                    "<limit>": "<limit-value>"
                  }
                }
              }
            ]
          }
        ]
      }
    }

.. note::

    The Limits hook library uses the class name to identify a client class and the subnet ID to
    identify a subnet.  Changing a test expression in a client class or the network range of a
    subnet while leaving the name or ID unchanged does not reset the lease count for the
    respective client class or subnet. To reset the lease count, change the client class name
    or the subnet ID.

.. _hooks-limits-lease-limiting:

Lease Limiting
~~~~~~~~~~~~~~

It is possible to limit the number of leases that a group of clients can get from a Kea DHCP server
or from a set of collaborating Kea DHCP servers.

The value of a lease limit can be specified as an unsigned integer in 32 bits, i.e. between ``0`` and
``4,294,967,295``. Each lease type can be limited individually. IPv4 leases and IPv6 IA_NA leases
are limited through the ``"address-limit"`` configuration entry. IPv6 IA_PD leases are limited
through the ``"prefix-limit"`` configuration entry. Here are some examples:

* ``"address-limit": 4``
* ``"prefix-limit": 2``

For lease limiting, client classes and the associated lease counts - which are
checked against the configured limits - are updated for each lease in the following hook callouts:

* ``lease4_select``
* ``lease4_renew``
* ``lease6_select``
* ``lease6_renew``
* ``lease6_rebind``

As a result, classes for which ``"only-if-required"`` is "true" cannot be lease-limited.
Please refer to :ref:`the classification steps <classify-classification-steps>` for more information on which
client classes can be used to limit the number of leases.

.. note::

    Under load, a Kea DHCP server may allocate more leases than the limit strictly allows. This only has a chance of
    happening during high traffic surges, coming from clients belonging to the same class or the
    same subnet, depending on what is limited. Users may be interested in following the development of
    `atomic lease limits <https://gitlab.isc.org/isc-projects/kea/-/issues/2449>`__ in ISC's GitLab instance.

.. _hooks-limits-rate-limiting:

Rate Limiting
~~~~~~~~~~~~~

It is possible to limit the frequency or rate at which inbound packets receive a response.

The value of a rate limit can be specified in the format ``"<p> packets per <time-unit>"``. ``<p>``
is any number that can be represented by an unsigned integer in 32 bits, i.e. between ``0`` and
``4,294,967,295``. ``<time-unit>`` can be any of ``second``, ``minute``, ``hour``, ``day``,
``week``, ``month``, or ``year``. A ``month`` is considered to be 30 days for
simplicity; similarly, a ``year`` is 365 days for limiting purposes. This syntax
covers a wide range of rates, from one lease per year to four billion leases per
second. This value is assigned to the ``"rate-limit"`` configuration entry.
Here are some examples:

* ``"rate-limit": 1 packet per second``
* ``"rate-limit": 4 packets per minute``
* ``"rate-limit": 16 packets per hour``

The configured value of ``0`` packets is a convenient way of disabling packet processing for certain
clients entirely. As such, it means its literal value and is not a special value for disabling
limiting altogether, as might be imagined. Disabling limiting entirely is achieved by removing
the ``"rate-limit"`` leaf configuration entry, the ``"limits"`` map or user context
around it, or the hook library configuration. The same applies to the value of ``0`` in lease
limiting. However, that use case is best achieved with rate limiting; it puts less computational
strain on Kea, since the action of dropping the request or sending a NAK is decided earlier.

In terms of rate limiting, client classes are evaluated at the ``pkt4_receive`` and the
``pkt6_receive`` callout, respectively, so that rate limits are checked as early as possible in the
packet-processing cycle. Thus, only those classes which are assigned to the packet solely via an
independent test expression can be used. Classes that depend on host reservations or the special
``BOOTP`` or ``KNOWN`` classes, and classes that are marked with ``"only-if-required": true``,
cannot be rate limited. See :ref:`the classification steps <classify-classification-steps>` for
more details on which client classes can be used to limit the packet rate.

Rate limits based on subnet are enforced only on the initially selected subnet for a given packet.
If the selected subnet is subsequently changed, as may be the case for subnets in a
shared network or when reselection is enabled in libraries such as the RADIUS hook, rate
limits on the newly selected subnet are ignored. In other words, packets are gated only by
the rate limit on the original subnet.

.. note::

    It may seem logical to think that assigning a rate limit of ``n`` packets per time unit results
    in ``n`` DORA or ``n`` SARR exchanges. However, by default, all inbound packets are counted - meaning
    that a full message exchange accounts for two packets. To achieve the effect of counting an
    exchange only once, use client-class rate-limiting with a test expression that binds
    ``pkt4.msgtype`` to DHCPDISCOVER messages or ``pkt6.msgtype`` to SOLICIT messages.
