.. _hooks-bootp:

BOOTP Support
=============

.. note::

   This library is still in the experimental phase. Use with care!


This hooks library adds support for BOOTP with vendor information extensions
(`RFC 1497 <https://tools.ietf.org/html/rfc1497>`__). Received BOOTP
requests are recognized, translated into DHCPREQUEST packets by adding
a dhcp-message-type option and put into the "BOOTP" client class.
Members of this class get infinite lifetime leases but the class can
be used too for instance to guard a pool of addresses.

The DHCP specific options, such as dhcp-message-type, are removed from
the server's responses and responses shorter than the BOOTP minimum
size (300 octets) are padded to this size.

The library is available since Kea 1.7.2 and can be loaded in a
similar way to other hook libraries by the ``kea-dhcp4`` process.
It takes no parameter.

::

    "Dhcp4": {
        "hooks-libraries": [
            {   "library": "/usr/local/lib/libdhcp_bootp.so" },
            ...
        ]
    }


.. note::

   This library is only meant to be loaded by the ``kea-dhcp4`` process
   as there is no BOOTP protocol for IPv6.

.. note::

   A host reservation for a BOOTP client should use the hardware address
   as the identifier (the client-id option is a DHCP specific option).

.. _hooks-bootp-config:

Incoming BOOTP packets are added to the BOOTP class. This can be used
to segregate BOOTP clients to separate pools. For example you can do
the following:

::

   "Dhcp4": {
       "client-classes": [
           {
               // The DHCP class is the complement of the BOOTP class
               "name": "DHCP",
               "test": "not member('BOOTP')"
           }
       ],
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [
               {
                   // BOOTP clients will be handled here
                   "pool": "192.0.2.200 - 192.0.2.254",
                   "client-class": "BOOTP"
               },
               {
                   // Regular DHCP clients will be handled here
                   "pool": "192.0.2.1 - 192.0.2.199",
                   "client-class": "DHCP"
               }],
               ...
           },
           ...
       ],
       ...
   }


.. _hooks-bootp-limitations:

BOOTP Hooks Limitation
~~~~~~~~~~~~~~~~~~~~~~

Currently the BOOTP library has the following limitation:

- A basic BOOTP as defined in `RFC 951
  <https://tools.ietf.org/html/rfc951>`__ is not supported. Kea only
  supports the BOOTP with vendor information extensions. Depending on
  the demand, this may or may not be implemented in the future.
