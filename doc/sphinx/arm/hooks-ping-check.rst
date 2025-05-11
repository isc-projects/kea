.. ischooklib:: libdhcp_ping_check.so
.. _hooks-ping-check:

``libdhcp_ping_check.so``: Ping Check
=====================================

This hook library adds the ability to perform a "ping check" of a candidate
IPv4 address prior to offering it to a DHCP client. This feature is similar
to a behavior available in ISC DHCP and one suggested in `RFC
2131 <https://tools.ietf.org/html/rfc2131>`__, section 3.1, item 2.

.. note::

    :ischooklib:`libdhcp_ping_check.so` is part of the open source code and is
    available to every Kea user.
    It was previously available only to ISC customers with a paid support contract.

Overview
~~~~~~~~

The Ping Check library, added in Kea 2.5.4, can be loaded by the :iscman:`kea-dhcp4` daemon
by adding it to the ``hooks-libraries`` element of the server's configuration:

.. code-block:: javascript

    {
        "hooks-libraries": [
            {
                "library": "/usr/local/lib/libdhcp_ping_check.so",
                "parameters": {
                    ...
                }
            },
            ...
        ],
        ...
    }

When the library is loaded, :iscman:`kea-dhcp4` conducts a ping check prior to
offering a lease to a client if all of the following conditions are true:

1. The ping check hook library is loaded.

2. Ping checking is enabled.

3. The server is responding to a DHCPDISCOVER.

4. The candidate lease is neither active nor reserved.

5. Any of the following are true:

    a. This is the first offer of this lease to this client. This check
    can only be done if ``offer-lifetime`` is greater than zero (i.e. temporary
    allocation on DHCPDISCOVER is enabled). If ``offer-lifetime`` is zero
    ping checks are done for every DHCPOFFER, as the server has no way to
    know whether prior offers were made.

    b. The lease is being offered to a client other than its previous owner.

    c. The lease is being offered to its previous owner and more than the
    number of seconds specified by ``ping-cltt-secs`` have elapsed since the
    CLTT of the original lease.

When the ping check library is loaded, the :iscman:`kea-dhcp4` server
responds to a DHCPDISCOVER by:

1. Selecting a candidate IPv4 address through normal processes and using it to
construct a DHCPOFFER.

2. Parking the DHCPOFFER and requesting a ping check from the ping check hook
library, via its ``lease4_offer`` callout. Refer to :ref:`parked-packet-limit` for
a basic introduction to packet parking.

3. Testing the callout conditions described above: if they are not
satisfied, it returns without conducting a check, and the server
sends the DHCPOFFER to the client. Otherwise, the callout
initiates a ping check for the lease address.

4. Upon conclusion of the ping check, the server either sends the DHCPOFFER
to the client, if the check concluded that the address is available, or discards
the DHCPFOFFER and creates a DECLINED lease for the address.

Each ping check consists of the following steps:

1. If the number of ECHO REPLYs sent is less than the configured
minimum number to send, send an ICMP ECHO REQUEST to the lease address.
Otherwise, conclude that the address is available.

2. If no ECHO REPLY is received within a configurable amount of time,
return to step 1.

3. Upon receipt of an ICMP ECHO REPLY, conclude that the lease is NOT available.

4. If any of the following occur:

    a. Receipt of an ICMP DESTINATION UNREACHABLE message
    b. Send failure of an ICMP ECHO REQUEST due to a network error (e.g. network is unreachable)
    c. Send failure of an ICMP ECHO REQUEST due to a permissions error (e.g. lease address is a broadcast address)
    d. Send failure of an ICMP ECHO REQUEST with socket buffer full error

    skip the address check and treat it as available.

.. note::

    "Socket buffer full" errors indicate that the OS rate limits on ICMP are
    being exceeded. The server does not retry them, as this would likely only
    exacerbate the situation. If this occurs continuously, then the client load
    on the server may be too high to accommodate ping checking. Ping checking is
    not recommended for systems with high throughput demands.

Configuration
~~~~~~~~~~~~~

The ping check hook library currently supports the following configuration parameters
that may be set at the global and subnet levels; subnet values override global values:

- ``enable-ping-check`` - This parameter enables or disables ping checking at a given scope.

- ``min-ping-requests`` - This is the minimum number of ECHO REQUESTs sent without receiving a reply, before an address is declared available. The default is 1; it must be greater than zero.

- ``reply-timeout`` - This is the maximum amount of time to wait for a reply to a single ECHO REQUEST. Specified in milliseconds, it must be greater than zero; the default is 100.

- ``ping-cltt-secs`` - This specifies the number of seconds that must elapse after the lease's CLTT before a ping check is conducted, when the client is the lease's previous owner. The default value is 60 seconds.

The following parameter is only supported at the global level:

- ``ping-channel-threads`` - In multi-threaded mode, this is the number of threads in the channel's thread pool. The default is 0, which instructs the library to use the same number of threads as the Kea core. This value is ignored if given when Kea is in single-threaded mode.

The following configuration excerpt illustrates a global-level configuration:

.. code-block:: javascript

    {
        "hooks-libraries": [{
            "library": "lib/kea/hooks/libdhcp_ping_check.so",
            "parameters": {
                "enable-ping-check" : true,
                "min-ping-requests" : 1,
                "reply-timeout" : 100,
                "ping-cltt-secs" : 60,
                "ping-channel-threads" : 0
            }
        }]
    }

The following excerpt demonstrates a subnet-level configuration:

.. code-block:: javascript

    {
    "subnet4": [{
        "subnet": "192.0.2.0/24",
        "pools": [{
            "pool": "192.0.2.10 - 192.0.2.20"
        }],

        "user-context": {
            "enable-ping-check" : true,
            "min-ping-requests" : 2,
            "reply-timeout" : 250,
            "ping-cltt-secs" : 120
        }
    }]
   }
