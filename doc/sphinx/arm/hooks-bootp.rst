.. _hooks-bootp:

BOOTP Support
=============

This hook library adds support for BOOTP with vendor-information extensions
(`RFC 1497 <https://tools.ietf.org/html/rfc1497>`__). Received BOOTP
requests are recognized, translated into DHCPREQUEST packets by adding
a ``dhcp-message-type`` option, and put into the "BOOTP" client class.
Members of this class get infinite lifetime leases but the class can
also be used to guard a pool of addresses.

The DHCP-specific options, such as ``dhcp-message-type``, are removed from
the server's responses; responses shorter than the BOOTP minimum
size of 300 octets are padded to this size.

This open source library is loaded
similarly to other hook libraries by the ``kea-dhcp4`` process, and
it takes no parameters.

::

    "Dhcp4": {
        "hooks-libraries": [
            {   "library": "/usr/local/lib/libdhcp_bootp.so" },
            ...
        ]
    }


.. note::

   This library can only be loaded by the ``kea-dhcp4`` process,
   as there is no BOOTP protocol for IPv6.

.. note::

   A host reservation for a BOOTP client should use the hardware address
   as the identifier (the ``client-id`` option is a DHCP-specific option).

.. _hooks-bootp-config:

Incoming BOOTP packets are added to the BOOTP class, allowing administrators
to segregate BOOTP clients into separate pools. For example:

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

BOOTP Hooks Limitations
~~~~~~~~~~~~~~~~~~~~~~~

Currently the BOOTP library has the following limitation:

- Basic BOOTP, as defined in `RFC 951
  <https://tools.ietf.org/html/rfc951>`__, is not supported. Kea only
  supports BOOTP with vendor-information extensions.
