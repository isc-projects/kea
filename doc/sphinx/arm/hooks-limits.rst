.. _hooks-limits:

``limits``: Limits to Manage Lease Allocation and Packet Processing
===================================================================

This hook library enables two types of limits:

1. Lease limiting: allow a maximum of `n` leases assigned at any one time.
2. Rate limiting: allow a maximum of `n` packets per `time_unit` to receive a response.

The Limits hook library is only available to ISC customers with a paid support contract.

.. _hooks-limits-configuration:

Configuration
~~~~~~~~~~~~~

The following examples are for ``kea-dhcp6``, but they can be easily extrapolated to its
``kea-dhcp4`` counterpart. Wildcards ``"<limit-key>"`` and ``"<limit-value>"`` need be replaced
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

A trick to enforce a global limit (same limit for all clients) is to define the special client class
``"ALL"`` and assign the limit to it.

.. code-block:: json

    {
      "Dhcp6": {
        "client-classes": [
          {
            "name": "ALL",
            "user-context": {
              "limits": {
                "<limit>": "<limit-value>"
              }
            }
          }
        ]
      }
    }

.. note::

    The Limits hook library uses the name to identify a client class and the ID to identify a subnet.
    Changing a test expression in a client class or the network range of a subnet while leaving the
    name, or the ID respectively, unchanged will not reset the limit for the respective client class
    or subnet. What counted towards the limit prior to the change will continue to take effect.
    To start over, consider changing the client class name or the subnet ID.

.. _hooks-limits-lease-limiting:

Lease Limiting
~~~~~~~~~~~~~~

It is possible to limit the number of leases that a group of clients can get from a Kea DHCP server
or from a set of collaborating Kea DHCP servers.

The value of a lease limit can be specified as an unsigned integer on 32 bits i.e. between ``0`` and
``4,294,967,295``. Each lease type can be limited individually. IPv4 leases and IPv6 IA_NA leases
are limited through the ``"address-limit"`` configuration entry. IPv6 IA_PD leases are limited
through the ``"prefix-limit"`` configuration entry. Here are some examples:

* ``"address-limit": 4``
* ``"prefix-limit": 2``

Inasmuch as lease limiting is regarded, client classes and the associated lease counts that are
checked against the configued limits, are updated for each lease in the following hook callouts:

* ``lease4_select``
* ``lease4_renew``
* ``lease6_select``
* ``lease6_renew``
* ``lease6_rebind``

As a result, packets that are marked with ``"only-if-required": true`` cannot be lease limited.
See :ref:`the classification steps <classify-classification-steps>` to have the full picture on what
client classes can be used to limit the number of leases.

.. warning::

    Due to technical conveniences, lease limits are not strictly enforced. Occasionally, a Kea DHCP
    server may allocate more leases than the limit would strictly allow. This only has a chance of
    happening during high traffic surges coming from clients belonging to the same class or to the
    same subnet (based on what is limited). Even in those scenarios and other circumstances that
    would favor the race condition that causes surpassing the limit e.g. a global rate of inbound
    packets that matches the server's response rate performance, and a thread count close to the
    the number of cores, empirically, it seems that the unfortunate event is rare and only results
    in one lease past the limit. One hard guarantee is that the race can only happen again after the
    lease count has retreated below the limit. For an airtight solution, follow the development of
    `GitLab issue #2449 atomic lease limits <https://gitlab.isc.org/isc-projects/kea/-/issues/2449>`__.

.. _hooks-limits-rate-limiting:

Rate Limiting
~~~~~~~~~~~~~

It is possible to limit the frequency or rate at which inbound packets receive a response.

The value of a rate limit can be specified in the format ``"<p> packets per <time-unit>"``. ``<p>``
is any number that can be represented by an unsigned integer on 32 bits i.e. between ``0`` and
``4,294,967,295``. ``<time-unit>`` can be any of ``second``, ``minute``, ``hour``, ``day``,
``week``, ``month``, ``year``. ``month`` is considered to be 30 days for simplicity. Similarly,
``year`` is 365 days for all intents and purposes of limiting. This syntax covers a high range of
rates from one lease per year to four billion leases per second. This vaue is assigned to the
``"rate-limit"`` configuration entry. Here are some examples:

* ``"rate-limit": 1 packet per second``
* ``"rate-limit": 4 packets per minute``
* ``"rate-limit": 16 packets per hour``

The configured value of ``0`` packets is a convenient way of disabling packet processing for certain
clients entirely. As such, it means its literal value and is not a special value for disabling
limiting altogether as it might be imagined. Disabling limiting altogether is achieved by removing
the ``"rate-limit"`` leaf configuration entry, the ``"limits"`` map around it or the user context
around it or the hook library configuration. The same can be said about the value of ``0`` in lease
limiting. However, that use case is best achieved with rate limiting as it puts less computational
strain on Kea since the action of dropping the request or sending a NAK is decided earlier on.

Inasmuch as rate limiting is regarded, client classes are evalated at the ``pkt4_receive`` and the
``pkt6_receive`` callout respectively so that rate limits are checked as early as possible in the
packet processing cycle. Thus, only those classes which are assigned to the packet solely via an
independent test expression can be used. Classes that depend on host reservations or the special
``BOOTP`` or ``KNOWN`` classes, and classes that are marked with ``"only-if-required": true``,
cannot be rate limited. See :ref:`the classification steps <classify-classification-steps>` to
have the full picture on what client classes can be used to limit packet rate.

Rate limits based on subnet are enforced only on the initially selected subnet for a given packet.
If the selected subnet is subsequently changed, as may be the case for subnets in a
shared-network or when reselection is enabled in libraries such as the RADIUS hook, rate
limits on the newly selected subnet will be ignored. In other words, packets are gated only by
the rate limit on the original subnet.

.. note::

    It can be tempting to think that assigning a rate limit of ``n`` packets per time unit results
    in ``n`` DORA or ``n`` SARR exchanges. By default, all inbound packets are counted. That means
    that a full message exchange accounts for 2 packets. To achieve the desired effect of counting an
    exchange only once, you may use client class rate limiting with a test expression that binds
    ``pkt4.msgtype`` to DHCPDISCOVER messages or ``pkt6.msgtype`` to SOLICIT messages.
