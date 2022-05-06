.. _hooks-limits:

``limits``: Rate Limiting
=========================

This hook library enables limiting the rate at which packets are being processed.
The limits hook library is part of the subscription package.

Configuration
~~~~~~~~~~~~~

The library can be loaded by both ``kea-dhcp4`` and ``kea-dhcp6`` servers by adding its path along with any parameters to the ``"hooks-libraries"`` element of the server's configuration. Here is an example:

.. code-block:: json

    {
        "DhcpX": {
            "hooks-libraries": [
                {
                    "library": "/usr/local/lib/libdhcp_limits.so"
                    "limits": [
                        {
                          "client-classes": ["ALL"],
                          "rate-limit": "1000 packets per second"
                        },
                        {
                          "client-classes": [ "bronze" ],
                          "rate-limit": "100 packets per minute"
                        }
                        {
                          "subnet-ids": [ 1, 2 ],
                          "rate-limit": "1 packet per second"
                        }
                    ]
                }
            ]
        }
    }

There are two possible packet identification criteria: client classes and subnet IDs. For easier
configuration, you may provide multiple such criteria to a single rate limit.

The rate limit can be specified in the format ``"<p> packets per <time-unit>"``. ``<p>`` is any
number that can be represented by an unsigned integer on 32 bits i.e. between ``0`` and
``4,294,967,295``. ``<time-unit>`` can be any of ``second``, ``minute``, ``hour``, ``day``,
``week``, ``month``, ``year``. ``month`` is considered 30 days for simplicity. Similarly, ``year``
is considered 365 days. This syntax covers a high range of rates from one lease per year to four
billion leases per second.

The configured value of ``0`` packets can be a convenient way of disabling packet processing for
certain clients entirely. As such, it means its literary value and is not a special value for
disabling rate limiting. Disabling limiting altogether is achieved by removing the leaf
configuration entry, the map around it or the entire hook library configuration.
