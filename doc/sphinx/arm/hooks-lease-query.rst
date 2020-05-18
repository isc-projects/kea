.. lease-query:

lease_query: Leasequery
=======================

This library provides support for DHCPv4 Leasequery as described in
`RFC 4388 <https://tools.ietf.org/html/rfc4388>`__.  Support for DHCPv6
Lease Query (`RFC 5007 <https://tools.ietf.org/html/rfc5007>`__) will be
added in the near future.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or
   ``kea-dhcp6`` process.

The Leasequery library is part of the premium source code and is
available to ISC's paid support customers. 

.. lease-query-dhcpv4:

DHCPv4 Leasequery
~~~~~~~~~~~~~~~~~

DHCPv4 simple Leasequery provides a requestor the ability to query for 
active lease information for either a single IP address or a single client.
RFC 4388 calls for three such queries: 

- Query by IP address
    The IP address of interest is contained within the ``ciaddr`` field of
    the query.
- Query by hardware address
    The hardware address of interest is contained with the ``chaddr`` field
    of the query.  
- Query by client identifier
    The client identifier of interest is sent in the dhcp-client-identifier
    option (61) of the query.

The inbound DHCPLEASEQUERY packet must supply only one of the three values 
above.  Queries which supply more than one of these values are dropped.

In addition, the query must contain the IP address of the requester in
``giaddr.`` This value will be used not only as the destination for the
query response but also to validate the requester against a known
list of IP addresses which are permitted to query.  This list of valid
requester addresses is specified as part of the Leasequery hook library's
configuration (See the section on configuration below).

In response to a valid query, the server will return one of three message 
types:

- DHCPLEASEUNKNOWN 
    Returned when the IP address of interest is not one the server knows 
    about (query by IP address); or there are no active leases for the 
    client of interest (query by hardware address or client id).

- DHCPLEASEUNASSIGNED 
    Returned when the IP address is one the server knows of but for which
    there are no active leases (applies only to query by IP address).

- DHCPLEASEACTIVE
    Returned when there is at least one active lease found matching the
    criteria. 

For both DHCPLEASEUNKNOWN and DHCPLEASEUNASSIGNED responses, the only
information sent back to the requester in response is the query parameter
itself (i.e. one of: IP address, hardware address, or client identifier).

For DHCPLEASEACTIVE the server will provide the following information
for the newest active lease that matches the criteria, in the response:

- ciaddr - set to the lease's IP address
- chaddr - set to the lease's hardware address

In addition, one or more of the following options will be included:

.. tabularcolumns:: |p{0.2\linewidth}|p{0.1\linewidth}|p{0.7\linewidth}|

.. table:: DHCPLEASEACTIVTE Options
   :class: longtable
   :widths: 20 10 70

   +-----------------------------+-------+-----------------------------------------------+
   | Option                      | Code  | Content                                       |
   +=============================+=======+===============================================+
   | dhcp-client-identifier      |  61   | copied from the lease (if one)                |
   +-----------------------------+-------+-----------------------------------------------+
   | client-last-transction-time |  91   | amount of time that has elapsed since the     |
   | (CLTT)                      |       | lease's actual CLTT.  This value will also be | 
   |                             |       | used by the server to adjust life time and    |
   |                             |       | timer values.                                 |
   +-----------------------------+-------+-----------------------------------------------+
   | dhcp-lease-time             |  51   | lease's life time reduced by CLTT             | 
   +-----------------------------+-------+-----------------------------------------------+
   | dhcp-renewal-time           |  58   | as controlled by kea-dhcp4 configuration and  |
   |                             |       | then reduced by CLTT                          |
   +-----------------------------+-------+-----------------------------------------------+
   | dhcp-rebind-time            |  59   | as dictacted by kea-dhcp4 configuration and   |
   |                             |       | then reduced by CLTT                          |
   +-----------------------------+-------+-----------------------------------------------+
   | dhcp-agent-options          |  82   | if stored on the lease. (See                  |
   |                             |       | :ref:`dhcp4-store-extended-info`)             |
   +-----------------------------+-------+-----------------------------------------------+
   | associated-ip               |  92   | a list of all other IP addresses for which the|
   |                             |       | the client has active leases. (Does not apply |
   |                             |       | to query by IP address)                       |
   +-----------------------------+-------+-----------------------------------------------+

The dhcp-server-identifier option (54) will be returned in all responses in keeping with
RFC 2131 section 4.3.1.

RFC 4388 allows requestors to request specific options via a PRL (Option 55).
This is not currently supported but may be added at a future date.

.. lease-query-dhcpv4-config:

DHCPv4 Leasequery Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Configuring the Leasequery hook library for use is straight forward.  It currently
supports a single parameter, ``requesters``, which is a list of IP addresses from
which DHCPLEASEQUERY packets will be accepted.  In other words, it is a list of
known requesters.  The following shows an example configuration with two requester
addresses:  

::

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
