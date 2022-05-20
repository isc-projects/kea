.. _hooks-limits:

``limits``: Rate Limiting
=========================

This hook library enables limiting the rate at which packets are being processed.
The limits hook library is part of the subscription package.

Configuration
~~~~~~~~~~~~~

The library can be loaded by both ``kea-dhcp4`` and ``kea-dhcp6`` servers by adding its path in the
``"hooks-libraries"`` element of the server's configuration.

The rate limit can be specified in the format ``"<p> packets per <time-unit>"``. ``<p>`` is any
number that can be represented by an unsigned integer on 32 bits i.e. between ``0`` and
``4,294,967,295``. ``<time-unit>`` can be any of ``second``, ``minute``, ``hour``, ``day``,
``week``, ``month``, ``year``. ``month`` is considered to be 30 days for simplicity. Similarly,
``year`` is 365 days for all intents and purposes of limiting. This syntax covers a high range of
rates from one lease per year to four billion leases per second.

The configured value of ``0`` packets is a convenient way of disabling packet processing for certain clients entirely. As such, it means its literary value and is not a special value for disabling
limiting altogether as it might be imagined. Disabling limiting altogether is achieved by removing
the `"rate-limit"` leaf configuration entry, the `"limits"` map around it or the user context around
it or the hook library configuration.

There are two ways to configure what packets get limited. One is through the client classes that are
initially assigned to the packet. In this case, the limit is configured directly in the user context
of the client class definition. As such, if a client class has no dependencies on host reservations,
or on the special `"BOOTP"` or `"KNOWN"` classes, and is not marked with `"only-if-required"`, if
the client class gets assigned to the packet, and it has a configured limit, the packet will be
limited accordingly.

.. note::

    It can be tempting to think that assigning a rate limit of `n` packets per time unit results in
    `n` DORA or `n` SARR exchanges. By default, all inbound packets are counted. That means that
    a full message exchange amounts for 2 packets. To achieve the desired effect of counting an
    exchange only once, you may use client class rate limiting with a test expression that binds
    `pkt4.msgtype` to DHCPDISCOVER messages or `pkt6.msgtype` to SOLICIT messages.

The other way is through the subnet that the Kea selects for the packet. To achieve this, the limit
is added to the user context of the subnet definition.

.. note::

    Subnet reselection mechanisms like the one that can be enabled in the RADIUS hook, can offer the
    illusion that a packet should have been limited, when in reality it was not. The subnet that is
    taken into account depends on which hook library is configured first.

The following is an example that adds one rate limit on a client class and another one in a subnet
in `kea-dhcp6`. A valid configuration for `kea-dhcp4` can be easily extrapolated.

.. code-block:: json

    {
      "Dhcp6": {
        "client-classes": [
          {
            "name": "gold",
            "user-context": {
              "limits": {
                "rate-limit": "1000 packets per second"
              }
            }
          }
        ],
        "hooks-libraries": [
          {
            "library": "/usr/local/lib/libdhcp_limits.so"
          }
        ],
        "subnet6": [
          {
            "id": 1,
            "pools": [
              {
                "pool": "2001:db8::/64"
              }
            ],
            "subnet": "2001:db8::/64",
            "user-context": {
              "limits": {
                "rate-limit": "10 packets per minute"
              }
            }
          }
        ]
      }
