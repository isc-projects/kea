.. _hooks-lease-query:

``lease_query``: Leasequery Support
===================================

This library provides support for DHCPv4 Leasequery as described in
`RFC 4388 <https://tools.ietf.org/html/rfc4388>`__; and for DHCPv6
Leasequery (`RFC 5007 <https://tools.ietf.org/html/rfc5007>`__).

.. note::

   This library can only be loaded by the ``kea-dhcp4`` or
   ``kea-dhcp6`` process.

Kea version 2.3.4 added support for DHCPv6 Bulk Leasequery
(`RFC 5460  <https://tools.ietf.org/html/rfc5460>`__) and
Kea version 2.3.5 added support for DHCPv4 Bulk Leasequery
(`RFC 6926  <https://tools.ietf.org/html/rfc6926>`__) using
the memfile lease backend.

The Leasequery library is only available to ISC customers with a paid support contract.

.. _lease-query-dhcpv4:

DHCPv4 Leasequery
~~~~~~~~~~~~~~~~~

DHCPv4 simple Leasequery provides a requester the ability to query for
active lease information for either a single IP address or a single client.
RFC 4388 calls for three such queries:

- Query by IP address

    The IP address of interest is contained within the ``ciaddr`` field of
    the query.
- Query by hardware address

    The hardware address of interest is contained with the ``chaddr`` field
    of the query.
- Query by client identifier

    The client identifier of interest is sent in the ``dhcp-client-identifier``
    option (61) of the query.

The inbound DHCPLEASEQUERY packet must supply only one of the three values
above. Queries which supply more than one of these values are dropped.

In addition, the query must contain the IP address of the requester in
``giaddr``. This value is used not only as the destination for the
query response but also to validate the requester against a known
list of IP addresses which are permitted to query. This list of valid
requester addresses is specified as part of the Leasequery hook library's
configuration (see the section on configuration below).

In response to a valid query, the server returns one of three message
types:

- DHCPLEASEUNKNOWN

    Returned when the IP address of interest is not one the server knows
    about (query by IP address); or there are no active leases for the
    client of interest (query by hardware address or client ID).

- DHCPLEASEUNASSIGNED

    Returned when the IP address is one the server knows of but for which
    there are no active leases (applies only to query by IP address).

- DHCPLEASEACTIVE

    Returned when there is at least one active lease found matching the
    criteria.

For both DHCPLEASEUNKNOWN and DHCPLEASEUNASSIGNED responses, the only
information sent back to the requester in response is the query parameter
itself (i.e. one of: IP address, hardware address, or client identifier).

For DHCPLEASEACTIVE the server provides the following information
for the newest active lease that matches the criteria, in the response:

- ``ciaddr`` - set to the lease's IP address
- ``chaddr`` - set to the lease's hardware address

In addition, one or more of the following options are included:

.. tabularcolumns:: |p{0.2\linewidth}|p{0.1\linewidth}|p{0.7\linewidth}|

.. table:: DHCPLEASEACTIVE options
   :class: longtable
   :widths: 30 10 70

   +------------------------------+-------+-----------------------------------------------+
   | Option                       | Code  | Content                                       |
   +==============================+=======+===============================================+
   | dhcp-client-identifier       |  61   | copied from the lease (if appropriate)        |
   +------------------------------+-------+-----------------------------------------------+
   | client-last-transaction-time |  91   | the amount of time that has elapsed since the |
   |                              |       | lease's client-last-transaction-time (CLTT).  |
   |                              |       | This value is also used by the server to      |
   |                              |       | adjust lifetime and timer values.             |
   +------------------------------+-------+-----------------------------------------------+
   | dhcp-lease-time              |  51   | lease's lifetime reduced by CLTT              |
   +------------------------------+-------+-----------------------------------------------+
   | dhcp-renewal-time            |  58   | as controlled by kea-dhcp4 configuration and  |
   |                              |       | then reduced by CLTT                          |
   +------------------------------+-------+-----------------------------------------------+
   | dhcp-rebind-time             |  59   | as dictated by kea-dhcp4 configuration and    |
   |                              |       | then reduced by CLTT                          |
   +------------------------------+-------+-----------------------------------------------+
   | dhcp-agent-options           |  82   | if stored on the lease. (See                  |
   |                              |       | :ref:`dhcp4-store-extended-info`)             |
   +------------------------------+-------+-----------------------------------------------+
   | associated-ip                |  92   | a list of all other IP addresses for which    |
   |                              |       | the client has active leases. (Does not apply |
   |                              |       | to query by IP address)                       |
   +------------------------------+-------+-----------------------------------------------+

The ``dhcp-server-identifier`` option (54) is returned in all responses in keeping with
RFC 2131, section 4.3.1.

RFC 4388 allows requesters to ask for specific options via the
``dhcp-parameter-request-list`` (PRL, option 55). This is not currently supported in Kea.

.. _lease-query-dhcpv4-config:

DHCPv4 Leasequery Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Configuring the Leasequery hook library for use is straightforward. It
supports a single parameter, ``requesters``, which is a list of IP addresses from
which DHCPLEASEQUERY packets are accepted. In other words, it is a list of
known requesters. The following code shows an example configuration with two requester
addresses:

::

 :
    "store-extended-info": true,
 :
    "hooks-libraries": [
        {
            "library": "lib/kea/hooks/libdhcp_lease_query.so",
            "parameters": {
                "requesters": [ "192.0.1.1", "10.0.0.2" ]
            }
        }
    ],
 :

.. note::

    For security purposes, there is no way to specify wildcards. Each requester address
    must be explicitly listed.

.. _lease-query-dhcpv6:

DHCPv6 Leasequery
~~~~~~~~~~~~~~~~~

DHCPv6 simple Leasequery gives a requester the ability to query for
active lease information for either a single IP address or a single client
DUID. The query type and parameters are conveyed in an ``lq-query`` option (44)
attached to a ``DHCPV6_LEASEQUERY`` message:

- ``query-type``

    This is either ``query-by-address`` (1) or ``query-by-clientid`` (2)

- ``link-address``

    The global link address, when not empty, instructs the query to be
    limited to leases within that "link." Kea uses this value to
    select only leases that belong to subnets whose prefix matches
    this value. Active leases for prefix delegations for
    a matched subnet are included in the query reply, even if the
    delegated prefix itself falls outside the subnet prefix.

- ``query-options``

    A single ``iaaddr`` option (12) must be supplied when querying by address.
    When querying by client ID, a single ``clientid`` option (1) must be
    supplied. RFC 5007 also calls for an optional, ``oro`` option (6), to
    request specific options be returned for matched leases. This is
    not currently implemented.

.. note::

    `RFC 5007, Section 3.3 <https://tools.ietf.org/html/rfc5007#section-3.3>`__
    states that querying by IP address should return either a lease (e.g.
    binding) for the address itself or a lease for a delegated prefix that
    contains the address. The latter is not currently implemented. Leases for
    delegated prefixes may only be returned when querying by client ID. See
    `GitLab issue #1275 <https://gitlab.isc.org/isc-projects/kea/-/issues/1275>`__

``DHCPV6_LEASEQUERY`` queries are only honored if the source address of
the query matches an entry in a list of known IP addresses which are
permitted to query. This list of valid requester addresses is specified
as part of the Leasequery hook library’s configuration (see the section
on configuration below). Queries received from unknown requesters are
logged and dropped.

In response to a valid query, the server carries out the requisite
activities and returns a ``DHCPV6_LEASEQUERY_REPLY``. All replies contain
at least a ``status-code`` option (13) that indicates the outcome of the query
as detailed in the following table:

.. tabularcolumns:: |p{0.5\linewidth}|p{0.3\linewidth}|p{0.1\linewidth}|p{0.3\linewidth}|

.. table:: DHCPV6_LEASEQUERY_REPLY status option values per query outcome
   :class: longtable
   :widths: 50 30 10 30

   +--------------------------------------+-------------------------+--------+------------------------------+
   |                                      | Status                  | Status |  Status                      |
   | Query Outcome                        | Label                   | Code   |  Text                        |
   +======================================+=========================+========+==============================+
   | Invalid query type field             | STATUS_UnknownQueryType |   7    | "unknown query-type"         |
   +--------------------------------------+-------------------------+--------+------------------------------+
   | Query by IP address that does not    | STATUS_Malformed        |   10   | "missing D6O_IAADDR"         |
   | contain an address option            |                         |        |                              |
   +--------------------------------------+-------------------------+--------+------------------------------+
   | Query by IP address for an address   | STATUS_NotConfigured    |    9   | "address not in a configured |
   | that does fall within any configured |                         |        | pool"                        |
   | pools                                |                         |        |                              |
   +--------------------------------------+-------------------------+--------+------------------------------+
   | Query by IP address which found only | STATUS_Success          |    0   | "inactive lease exists"      |
   | an inactive lease (e.g. expired,     |                         |        |                              |
   | declined, reclaimed-expired)         |                         |        |                              |
   +--------------------------------------+-------------------------+--------+------------------------------+
   | Query by IP address that found no    | STATUS_Success          |    0   | "no active lease"            |
   | leases (active or otherwise)         |                         |        |                              |
   +--------------------------------------+-------------------------+--------+------------------------------+
   | Query by IP address that found an    | STATUS_Success          |    0   | "active lease found"         |
   | active lease for the address         |                         |        |                              |
   +--------------------------------------+-------------------------+--------+------------------------------+
   | Query by Client ID that does not     | STATUS_Malformed        |   10   | "missing D6O_CLIENTID"       |
   | contain a client ID option           |                         |        |                              |
   +--------------------------------------+-------------------------+--------+------------------------------+
   | Query by Client ID with a link       | STATUS_NotConfigured    |    9   | "not a configured link"      |
   | address that does not match any      |                         |        |                              |
   | configured subnets                   |                         |        |                              |
   +--------------------------------------+-------------------------+--------+------------------------------+
   | Query by client ID which found no    | STATUS_Success          |    0   | "no active leases"           |
   | matching leases                      |                         |        |                              |
   +--------------------------------------+-------------------------+--------+------------------------------+
   | Query by client ID which found one   | STATUS_Success          |    0   | "active lease(s) found"      |
   | or more active leases                |                         |        |                              |
   +--------------------------------------+-------------------------+--------+------------------------------+

For those scenarios where the query was either invalid or for which no matching active
leases were found, the ``DHCPV6_LEASEQUERY_REPLY`` only contains the ``status-code``
option (12) per the above table.

When a query finds active leases in more than one subnet and the query's ``link-address``
is empty, then, in addition to the status-code, the ``DHCPV6_LEASEQUERY_REPLY``
contains a ``lq-client-link`` option (48). The ``lq-client-link`` contains a list of
IPv6 addresses, one for each subnet in which a lease was found (see
`RFC 5007, Section 4.1.2.5 <https://tools.ietf.org/html/rfc5007#section-4.1.2.5>`__)
If, however, the query's ``link-address`` is not empty, the list of queries is
pruned to contain only leases that belong to that subnet.

When the query results in one or more active leases which all belong to a single
subnet, in addition to the ``status-code``, the ``DHCPV6_LEASEQUERY_REPLY`` contains a
``client-data`` option (45) (see
`RFC 5007, Section 4.1.2.2 <https://tools.ietf.org/html/rfc5007#section-4.1.2.2>`__).
The client-data option encapsulates the following options:

.. tabularcolumns:: |p{0.2\linewidth}|p{0.1\linewidth}|p{0.7\linewidth}|

.. table:: OPTION_CLIENT_DATA returned when active lease(s) are found
   :class: longtable
   :widths: 30 10 70

   +------------------------------+-------+-----------------------------------------------+
   | Option                       | Code  | Content                                       |
   +==============================+=======+===============================================+
   | clientid                     |   1   | copied from the lease (if one exists)         |
   +------------------------------+-------+-----------------------------------------------+
   | clt-time                     |  46   | amount of time that has elapsed since the     |
   |                              |       | lease's client-last-transaction-time (CLTT).  |
   |                              |       | This value will also be used by the server to |
   |                              |       | adjust lifetime and timer values.             |
   +------------------------------+-------+-----------------------------------------------+
   | iaaddr                       |   5   | One option per matched address. Fields in     |
   |                              |       | each option:                                  |
   |                              |       | - lease address                               |
   |                              |       | - valid lifetime reduced by CLTT              |
   |                              |       | - preferred lifetime reduced by CLTT          |
   +------------------------------+-------+-----------------------------------------------+
   | iaprefix                     |   26  | One option per matched prefix. Fields in      |
   |                              |       | each option:                                  |
   |                              |       | - prefix                                      |
   |                              |       | - prefix length                               |
   |                              |       | - valid lifetime reduced by CLTT              |
   |                              |       | - preferred lifetime reduced by CLTT          |
   +------------------------------+-------+-----------------------------------------------+

If the lease with the most recent client-last-transaction-time (CLTT)
value has relay information in its user-context (``store-extended-info``, see
:ref:`store-extended-info-v6`), then an ``OPTION_LQ_RELAY_DATA`` option is
added to the reply (see
`RFC 5007, Section 4.1.2.4 <https://tools.ietf.org/html/rfc5007#section-4.1.2.4>`__).

The relay information on the lease is a list with an entry for each
relay layer the client packet (e.g. ``DHCPV6_REQUEST``) traversed, with the
first entry in the list being the outermost layer (closest to the server). The
``peer-address`` field of the ``lq-rely-option`` is set to the peer address of this
relay. The list of relays is then used to construct a ``DHCPV6_RELAY_FORW`` message
equivalent to that which contained the client packet, minus the client packet.
This message is stored in the ``DHCP-relay-message`` field of the ``lq-relay-data`` option.

.. _lease-query-dhcpv6-config:

DHCPv6 Leasequery Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Configuring the Leasequery hook library for use is straightforward. It
supports a single parameter, ``requesters``, which is a list of IP addresses from
which DHCPV6_LEASEQUERY packets are accepted. In other words, it is a list of
known requesters. The following code shows an example configuration with two requester
addresses:

::

 :
    "store-extended-info": true,
 :
    "hooks-libraries": [
        {
            "library": "lib/kea/hooks/libdhcp_lease_query.so",
            "parameters": {
                "requesters": [ "2001:db8:1::1", "2001:db8:2::1" ]
            }
        }
    ],
 :

.. note::

    For security purposes, there is no way to specify wildcards. Each requester address
    must be explicitly listed.

.. _bulk-lease-query-dhcpv4:

DHCPv4 Bulk Leasequery
~~~~~~~~~~~~~~~~~~~~~~

DHCPv4 Bulk Leasequery gives a requester the ability to query for
active lease information over a TCP connection. This allows the server
to return all leases matching a query.

Query types specified by RFC 6926 are query by hardware address and
query by client identifier from Lease Query (RFC 4388, note the query
by IP address is not available for Bulk Leasequery), and new query
types are defined:

- Query by relay identifier

    The query carries a RAI (dhcp-agent-options (82) option) with
    a relay-id (12) sub-option.

- Query by remote identifier

    The query carries a RAI (dhcp-agent-options (82) option) with
    a remote-id (2) sub-option.

- Query for all configured IP addresses

    This query type is selected when no other query type is specified.

New options are defined for Bulk Leasequery:

- status-code (151)

    This reply option carries a status code such as MalformedQuery or
    NotAllowed with an optional text message.

- base-time (152)

    This reply option carries the absolute current time the response
    was created. All other time-based reply options are related to
    this value.

- start-time-of-state (153)

    This reply option carries the time of the lease transition into its
    current state.

- query-start-time (154)

    This query option specifies a start query time: replies will only
    contain leases that are older than this value.

- query-end-time (155)

    This query option specifies an end query time: replies will only
    contain leases that are younger than this value.

- dhcp-state (156)

    This reply option carries the lease state.

- data-source (157)

    This reply option carries the source of the data as a remote flag.

RFC 6926 reuses and extends the Virtual Subnet Selection option (221)
defined in RFC 6607.

.. note::

   Kea does not support the query for all configured IP addresses yet
   so do not use the dhcp-state option as only active leases can be
   returned in replies. It does not keep the start time of state,
   nor the local / remote information so does not emit corresponding
   start-time-of-state and data-source options. Kea does not support VPNs
   so the presence of the option 221 in the query is considered as a
   (NotAllowed) error.

.. note::

   New query types are supported only with the memfile lease backend,
   and only when the ``store-extended-info`` option is enabled.

.. _bulk-lease-query-dhcpv6:

DHCPv6 Bulk Leasequery
~~~~~~~~~~~~~~~~~~~~~~

DHCPv6 Bulk Leasequery gives a requester the ability to query for
active lease information over a TCP connection. This allows the server
to return all active leases matching a query.

New query types are available: ``query-by-relay-id`` (3),
``query-by-link-address`` (4) and ``query-by-remote-id`` (5).

A new status code was defined: ``STATUS_QueryTerminated`` (11) but it is
not yet used by the hook library.

.. note::

   Kea attempts to map link address parameters to the prefixes of configured
   subnets.  If a given address falls outside all configured subnet prefixes
   the query will fail with a status code of STATUS_NotConfigured.  Also note if
   the link address parameter for ``query-by-relay-id`` or ``query-by-remote-id``
   is not :: (i.e. not empty) only delegated prefixes that lie within matching
   subnet prefixes will be returned.  Currently ``query-by-address`` does not
   support finding delegated prefixes by specifying an address that lies within
   the prefix.

.. note::

   New query types are supported only with the memfile lease backend,
   and only when the ``store-extended-info`` option is enabled.

.. _bulk-lease-query-dhcpv6-config:

Bulk Leasequery Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Bulk Leasequery configuration is done with a new map parameter ``advanced``
with possible entries:

- ``bulk-query-enabled``

    When true, Kea will accept connections from IPs in the requesters
    list and process received Bulk Leasequeries. Default is false.

- ``active-query-enabled``

    Anticipated parameter: if set must be false.

- ``extended-info-tables-enabled``

    When true the lease backend manages DHCPv6 lease extended info
    (aka relay info) in tables to support by-relay-id and by-remote-id
    DHCPv6 Bulk Leasequery new query types. Default is to use the
    same value as ``bulk-query-enabled``.

    This option does nothing if ``store-extended-info`` is disabled.

- ``lease-query-ip``

    IP address upon which to listen for connections. The address must be
    of the same family as the server, e.g. IPv6 for DHCPv6 server.

- ``lease-query-port``

    Port upon which to listen. Default to 67 for IPv4 and 547 for IPv6,
    i.e. the same value as for the UDP DHCP service but for TCP.

- ``max-bulk-query-threads``

    Indicates the maximum number of threads the Bulk Lease Query processing
    should use. A value of 0 instructs the server to use the same number of
    threads that the Kea core is using for DHCP multi-threading.
    The default is 0.

- ``max-requester-connections``

    Maximum number of concurrent requester connections (default 10, must be
    greater than 0).

- ``max-concurrent-queries``

    Maximum number of concurrent queries per connection. A value 0
    leaves the number for Kea to determine and is the default.

- ``max-requester-idle-time``

    Amount time that may elapse between receiving data from a requester
    before its connection is closed as idle. In seconds with a default
    of 300 seconds.

- ``max-leases-per-fetch``

    Maximum number of leases to return in a single fetch (default 100).

There should be common TLS parameters once TLS is supported.

For instance for DHCPv4:

::

  :
     "hooks-libraries": [
         {
             "library": "lib/kea/hooks/libdhcp_lease_query.so",
             "parameters": {
                 "requesters": [ "192.0.2.1", "192.0.2.2" ],
                 "advanced" : {
                      "bulk-query-enabled": true,
                      "active-query-enabled": false,

                      "lease-query-ip": "127.0.0.1",
                      "lease-query-tcp-port": 67,

                      "max-bulk-query-threads": 0,
                      "max-requester-connections": 10,
                      "max-concurrent-queries": 4,
                      "max-requester-idle-time": 300,
                      "max-leases-per-fetch": 100
                 }
             }
         }
     ],
 :

or for DHCPv6:

::

  :
     "hooks-libraries": [
         {
             "library": "lib/kea/hooks/libdhcp_lease_query.so",
             "parameters": {
                 "requesters": [ "2001:db8:1::1", "2001:db8:2::1" ],
                 "advanced" : {
                      "bulk-query-enabled": true,
                      "active-query-enabled": false,

                      "extended-info-tables-enabled": true,

                      "lease-query-ip": "::1",
                      "lease-query-tcp-port": 547,

                      "max-bulk-query-threads": 0,
                      "max-requester-connections": 10,
                      "max-concurrent-queries": 4,
                      "max-requester-idle-time": 300,
                      "max-leases-per-fetch": 100
                 }
             }
         }
     ],
 :
