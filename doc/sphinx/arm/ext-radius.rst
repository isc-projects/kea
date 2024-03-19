.. _radius:

RADIUS
======

.. _radius-overview:

RADIUS Overview
---------------

This hook library allows Kea to interact with two types of RADIUS
services: access and accounting. Although the most common DHCP and RADIUS
integration is done on the DHCP relay-agent level (DHCP clients send
DHCP packets to DHCP relays; those relays contact the RADIUS server and
depending on the response either send the packet to the DHCP server or
drop it), it does require DHCP relay hardware to support RADIUS
communication. Also, even if the relay has the necessary support, it is
often not flexible enough to send and receive additional RADIUS
attributes. As such, the alternative looks more appealing: to extend the
DHCP server to talk to RADIUS directly. That is the goal of this library.

.. note::

   This library can only be loaded by the :iscman:`kea-dhcp4` or the
   :iscman:`kea-dhcp6` process.

The major feature of this hook library is the ability to use RADIUS
authorization. When a DHCP packet is received, the Kea server sends an
Access-Request to the RADIUS server and waits for a response. The server
then sends back either an Access-Accept with specific client attributes,
or an Access-Reject. There are two cases supported here: first, the
Access-Accept includes a Framed-IP-Address attribute (for DHCPv4) or a
Framed-IPv6-Address attribute (for DHCPv6), which are interpreted by Kea as
instructions to assign the specified IPv4 or IPv6 address. This
effectively means RADIUS can act as an address-reservation database.

The second supported case is the ability to assign clients to specific
pools based on a RADIUS response. In this case, the RADIUS server sends
back an Access-Accept with a Framed-Pool attribute.
For both DHCPv4 and DHCPv6, Kea interprets this attribute as a client class.
With the addition of the ability to limit access to pools to
specific classes (see :ref:`classification-pools`), RADIUS can be
used to force the client to be assigned a dynamic address from a
specific pool. Furthermore, the same mechanism can be used to control
what kind of options the client gets if there are DHCP options
specified for a particular class.

.. _radius-config:

RADIUS Hook Library Configuration
---------------------------------

The RADIUS hook is a library that must be loaded by either :iscman:`kea-dhcp4` or
:iscman:`kea-dhcp6` servers. Unlike some other available hook libraries, this one
takes many parameters. For example, this configuration can be used:

.. parsed-literal::

    {
      "Dhcp4": {

        // Your regular DHCPv4 configuration parameters goes here.

        "hooks-libraries": [
          {
            // Note that RADIUS requires host-cache for proper operation,
            // so that library is loaded as well.
            "library": "/usr/local/lib/kea/hooks/libdhcp_host_cache.so"
          },
          {
            "library": "/usr/local/lib/kea/hooks/libdhcp_radius.so",
            "parameters": {

              // Specify where the dictionary is located.
              "dictionary": "/etc/kea/radius/dictionary",

              // Specify which address to use to communicate with RADIUS servers
              "bindaddr": "*"

              // More RADIUS parameters go here.
            }
          }
        ]
      }
    }

RADIUS is a complicated environment. As such, it is not feasible
to provide a default configuration that works for everyone.
However, we do have an example that showcases some of the more common
features. Please see ``doc/examples/kea4/hooks-radius.json`` in the Kea
sources.

The RADIUS hook library supports the following global configuration
flags:

-  ``bindaddr`` (default ``"*"``) - specifies the address to be used by the
   hook library in communication with RADIUS servers. The ``"*"`` special
   value tells the kernel to choose the address at hook library load time.

-  ``canonical-mac-address`` (default ``false``) - specifies whether MAC
   addresses in attributes follow the canonical RADIUS format (lowercase
   pairs of hexadecimal digits separated by ``-``).

-  ``client-id-pop0`` (default ``false``) - is used with
   :ischooklib:`libdhcp_flex_id.so`. Removes the leading zero (or pair of zeroes
   in DHCPv6) type in the client id (duid in DHCPv6). See
   ``client-id-printable`` for any value implications when used in conjunction
   with it.

-  ``client-id-printable`` (default ``false``) - checks whether the
   ``client-id``/``duid`` content is printable and uses it as is instead of in
   hexadecimal. Implies ``client-id-pop0`` and ``extract-duid`` as 0 and 255 are
   not printable.

-  ``deadtime`` (default ``0``) - is a mechanism that helps in sorting the
   servers such that the servers that have proved responsive so far are inquired
   first, and the servers that have proved unresponsive are left at the end. The
   deadtime value specifies the number of seconds after which a server is
   considered unresponsive. 0 disables the mechanism.

-  ``dictionary`` (default ``"/etc/kea/radius/dictionary"``) - is the
   attribute and value dictionary. Note that it is a critical parameter.
   A dictionary is provided by Kea and is set by default.

-  ``extract-duid`` (default ``true``) - extracts the embedded duid from an
   RFC-4361-compliant DHCPv4 client id. See ``client-id-printable`` for any
   value implications when used in conjunction with it.

-  ``identifier-type4`` (default ``"client-id"``) - specifies the identifier
   type to build the User-Name attribute. It should be the same as the
   host identifier. When :ischooklib:`libdhcp_flex_id.so` is used, then
   ``replace-client-id`` must be set to ``true`` and ``client-id`` must be used
   with ``client-id-pop0`` enabled.

-  ``identifier-type6`` (default ``"duid"``) - specifies the identifier type to
   build the User-Name attribute. It should be the same as the host
   identifier. When :ischooklib:`libdhcp_flex_id.so` is used, then
   ``replace-client-id`` must be set to ``true`` and ``duid`` must be used with
   ``client-id-pop0`` enabled.

-  ``nas-ports`` (default ``[]``), specifies the NAS port to use in place of
   a subnet ID (default behavior). It is an array of maps, each map having two
   elements at most: the mandatory NAS port value, and, optionally, a selector
   consisting of either a subnet id, a subnet prefix, or a shared-network name.
   If the selector is applied to the packet, the NAS port is used instead of the
   subnet id. When the subnet id is 0 or missing, the specified NAS port acts as
   a default. Its substition happens for all packets that did not match a
   selector.

-  ``realm`` (default ``""``) - is the default realm.

-  ``reselect-subnet-address`` (default ``false``) - enables subnet reselection
   according to the value of the Framed-IP-Address or, respectively,
   the Framed-IPv6-Address attribute from the RADIUS access response. With this
   flag enabled, if the IP address is not in range of the currently selected
   subnet, but is in range of another subnet that is selectable with regards to
   other criteria, the latter subnet is selected and used further in the lease
   assignment process.

-  ``reselect-subnet-pool`` (default ``false``) - enables subnet reselection
   according to the value of the Framed-Pool attribute from the RADIUS access
   response. With this flag enabled, if the currently selected subnet is not
   guarded by the client class represented by the attribute value, but there is
   another selectable subnet that is guarded by it, the latter subnet is
   selected and used further in the lease assignment process.
   This reselection is attempted first, and if successful, it prevents the
   function of reselect-subnet-address from coming into effect.

-  ``retries`` (default ``3``) - is the number of retries before trying the
   next server.

-  ``session-history`` (default ``""``) - is the name of the file providing
   persistent storage for accounting session history.

 - ``thread-pool-size`` (default ``0``) indicates the number of threads that
   is used for sending RADIUS requests and processing RADIUS responses for both
   access and accounting services before passing it to the core thread pool. A
   value of ``0`` instructs the RADIUS hook library to use the same number of
   threads used for core DHCP processing. This value is only relevant if Kea
   core is configured as multi-threaded. Single-threaded Kea core results in
   single-threaded RADIUS processing.

-  ``timeout`` (default ``10``) - is the number of seconds during which a
   response is awaited.

Two services are supported:

-  ``access`` - the authorization service.

-  ``accounting`` - the accounting service.

At the service level, three sections can be configured:

-  Servers that define RADIUS services that the library is expected to
   contact. Each server may have the following items specified:

   -  ``name`` - specifies the IP address of the server. A domain name may be
      used and will be resolved at hook library load time.

   -  ``port`` - specifies the UDP port of the server. By default, it is 1812
      for access and 1813 for accounting.

   -  ``secret`` - authenticates messages.

   When no server is specified, the service is disabled.

-  Attributes which define additional information that the Kea server
   sends to a RADIUS server. The parameter must be identified either
   by a name or type. Its value can be specified in one of three
   possible ways: ``data`` (which defines a plain text value), ``raw`` (which
   defines the value in hex), or ``expr`` (which defines an expression
   that is evaluated for each incoming packet independently).

   -  ``name`` - the name of the attribute.

   -  ``type`` - the type of the attribute. Either the type or the name must be
      provided, and the attribute must be defined in the dictionary.

   -  ``data`` - the first of three ways to specify the attribute content.
      It specifies the textual representation of the attribute content.

   -  ``raw`` - the second of three ways to specify the attribute content.
      It specifies the content in hexadecimal.

   -  ``expr`` - the last of the three ways to specify the attribute content.
      It specifies an evaluation expression on the DHCP query packet.
      Currently this is restricted to the access service.

    Attributes are supported only for the access service.

- The ``peer-updates`` boolean flag (default ``true``) controls whether lease
  updates coming from an active High-Availability (HA) partner should result in
  an accounting request. This may be desirable to remove duplicates if HA
  partners are configured to send request to the same RADIUS server. The flag is
  only supported by the accounting service. The lease synchronization process at
  the startup of an HA node does not trigger a RADIUS accounting request,
  regardless of the value of this flag.

- The ``max-pending-requests`` positive integer (default ``0``) limits the
  number of pending RADIUS requests. The value ``0`` means no limit. It is
  supported only by the access service. ``64`` can be a good value to set it to.

For example, to specify a single access server available on localhost
that uses ``"xyz123"`` as a secret, and tell Kea to send three additional
attributes (``User-Password``, ``Connect-Info``, and ``Configuration-Token``),
the following snippet could be used:

.. parsed-literal::

    {
      "parameters": {

        // Other RADIUS parameters here

        "access": {

          // This starts the list of access servers.
          "servers": [
            {
              // These are parameters for the first (and only) access server
              "name": "127.0.0.1",
              "port": 1812,
              "secret": "xyz123"
            }
          // Additional access servers could be specified here.
          ],

          // This defines a list of additional attributes Kea will send to each
          // access server in Access-Request.
          "attributes": [
            {
              // This attribute is identified by name (must be present in the
              // dictionary) and has static value (i.e. the same value will be
              // sent to every server for every packet).
              "name": "User-Password",
              "data": "mysecretpassword"
            },
            {
              // It is also possible to specify an attribute using its type,
              // rather than a name. 77 is Connect-Info. The value is specified
              // using hex. Again, this is a static value. It will be sent the
              // same for every packet and to every server.
              "type": 77,
              "raw": "65666a6a71"
            },
            {
               // This example shows how an expression can be used to send dynamic value.
               // The expression (see :ref:`classification-using-expressions`) may take any
               // value from the incoming packet or even its metadata e.g. the
               // interface it was received over from.
               "name": "Configuration-Token",
               "expr": "hexstring(pkt4.mac,':')"
            }
          ] // End of attributes
        }, // End of access

        // Accounting parameters.
        "accounting": {
          // This starts the list of accounting servers.
          "servers": [
            {
              // These are parameters for the first (and only) accounting server
              "name": "127.0.0.1",
              "port": 1813,
              "secret": "sekret"
            }
            // Additional accounting servers could be specified here.
          ]
        }
      }
    }

Customization is sometimes required for certain attributes by devices belonging
to various vendors. This is a great way to leverage the expression evaluation
mechanism. For example, MAC addresses which might be used as a convenience
value for the ``User-Password`` attribute are most likely to appear in colon-hexadecimal
notation (``de:ad:be:ef:ca:fe``), but they might need to be expressed in
hyphen-hexadecimal notation (``de-ad-be-ef-ca-fe``). Here's how to specify that:

.. code-block:: json

   {
      "parameters": {
         "access": {
            "attributes": [
               {
                  "name": "User-Password",
                  "expr": "hexstring(pkt4.mac, '-')"
               }
            ]
         }
      }
   }

And here's how to specify period-separated hexadecimal notation (``dead.beef.cafe``), preferred by Cisco devices:

.. code-block:: json

   {
      "parameters": {
         "access": {
            "attributes": [
               {
                  "name": "User-Password",
                  "expr": "substring(hexstring(pkt4.mac, ''), 0, 4) + '.' + substring(hexstring(pkt4.mac, ''), 4, 4) + '.' + substring(hexstring(pkt4.mac, ''), 8, 4)"
               }
            ]
         }
      }
   }


For :ischooklib:`libdhcp_radius.so` to operate properly in DHCPv4,
:ischooklib:`libdhcp_host_cache.so` must also be loaded. The reason for this
is somewhat complex. In a typical deployment, the DHCP clients send
their packets via DHCP relay, which inserts certain Relay Agent
Information options, such as ``circuit-id`` or ``remote-id``. The values of
those options are then used by the Kea DHCP server to formulate the
necessary attributes in the Access-Request message sent to the RADIUS
server. However, once the DHCP client gets its address, it then renews
by sending packets directly to the DHCP server. As a result, the relays
are not able to insert their RAI options, and the DHCP server cannot send
the Access-Request queries to the RADIUS server by using just the
information from incoming packets. Kea needs to keep the information
received during the initial Discover/Offer exchanges and use it again
later when sending accounting messages.

This mechanism is implemented based on user context in host
reservations. (See :ref:`user-context` and :ref:`user-context-hooks` for
details.) The host-cache mechanism allows the information retrieved by
RADIUS to be stored and later used for sending access and accounting
queries to the RADIUS server. In other words, the host-cache mechanism
is mandatory, unless administrators do not want RADIUS communication for messages
other than Discover and the first Request from each client.

.. note::

   Currently the RADIUS hook library is incompatible with the
   ``early-global-reservations-lookup`` global parameter i.e.
   setting the parameter to ``true`` raises an error when the
   hook library is loaded.

.. note::

   Currently the RADIUS hook library is incompatible with the
   multi-subnet shared networks that have host reservations other
   than global. Loading the RADIUS hook library in a Kea DHCP server
   that has this configuration raises an error.

.. _radius-server-example:

RADIUS Server Setup Example
---------------------------

The RADIUS hook library requires at least one RADIUS server to function. One
popular open-source implementation is FreeRADIUS. This is how it can be
set up to enable basic functionality in Kea.

1. Install FreeRADIUS through the package manager or from the tarballs available
   on [the freeradius.org download page](https://freeradius.org/releases/).

2. Establish the FreeRADIUS configuration directory. It's commonly
   ``/etc/freeradius``, but it may be ``/etc/raddb``.

3. Generate certificates. Go to ``/etc/freeradius/certs``.
   Run ``./bootstrap`` or ``make``.
   Wait until finished. It should take a few seconds.

4. Check that the server is able to start.
   Running with the ``-X`` flag is a good way to display potential errors.
   Run ``radiusd -X`` or ``freeradius -X``, whichever is available.
   It should display ``Ready to process requests`` on the final line.

5. If the Kea DHCP server and the RADIUS server are on different machines,
   edit ``/etc/freeradius/clients.conf`` with the proper address under
   ``ipadddr``. This file is also where the secret is set, which needs to match
   the one set in the hook library's configuration.

6. If RADIUS is used for the purpose of authorizing DHCP clients, each DHCP
   client needs to have an entry in the authorize file, which can be commonly
   found at:

   - ``/etc/raddb/mods-config/files/authorize``
   - ``/etc/freeradius/3.0/mods-config/files/authorize``
   - ``/etc/freeradius/users`` (for RADIUS 2.x series)

   Entries need to have the password set which needs to match the password
   configured in the configuration of the RADIUS hook library under the
   ``User-Password`` attribute. Each entry can have zero, one or multiple
   attributes.

   In the following example, there are 6 entries with the password set to the
   client ID, which would need to be dynamically set in the hook library's
   configuration. Here's how the entries can look like:

   ::

       01:00:0c:01:02:03:04    Cleartext-password := "00:0c:01:02:03:04"

       01:00:0c:01:02:03:05    Cleartext-password := "00:0c:01:02:03:05"
           Framed-IP-Address = "192.0.2.5"

       01:00:0c:01:02:03:06    Cleartext-password := "00:0c:01:02:03:06"
           Framed-IP-Address = "192.0.2.6",
           Framed-Pool = "classical"

       00:03:00:01:00:0c:01:02:03:07    Cleartext-password := "00:0c:01:02:03:07"

       00:03:00:01:00:0c:01:02:03:08    Cleartext-password := "00:0c:01:02:03:08"
           Framed-IPv6-Address = "2001:db8::8"

       00:03:00:01:00:0c:01:02:03:09    Cleartext-password := "00:0c:01:02:03:09"
           Framed-IPv6-Address = "2001:db8::9",
           Framed-Pool = "classroom"

7. Accounting should work out of the box with Kea, but customizations are
   possible in the accounting file, which can be commonly found at:

   - ``/etc/radius-config/mods-config/files/accounting``
   - ``/etc/freeradius/3.0/mods-config/files/accounting``

.. _radius-lease-allocation:

RADIUS Workflows for Lease Allocation
-------------------------------------

The following diagrams show a high level view of how RADIUS assists with the
lease allocation process in :iscman:`kea-dhcp4` and :iscman:`kea-dhcp6`.

.. figure:: ../uml/radius.*

Somewhat tangential to lease allocation, and not shown in the diagrams above,
is the ``command_processed`` callout, which sends Accounting-Request messages
when a lease command is received.

.. _radius-differences:

Differences Between RADIUS Hook Libraries Prior To 2.4.0 and As Of 2.6.0
------------------------------------------------------------------------

The RADIUS hook library in 2.4.0 and prior versions relied on the FreeRADIUS
client library to function. Starting with 2.6.0 and onwards, the RADIUS hook
library is standalone with its own RADIUS client implementation and its own
RADIUS dictionary. There are differences:

.. list-table::
    :header-rows: 1

    * - Feature

      - Old

      - New

    * - Support for Attribute Data Types

      - string, ipaddr, ipv4prefix, integer, integer64, date, ifid, ipv6addr, ipv6prefix, tlv, abinary, byte, ether, short, signed, octets

      - string (can simulate any other unsupported data type too), ipaddr, integer, date (interpreted as integer), ipv6addr, ipv6prefix

    * - Names of Standard Attributes

      - Taken from the FreeRADIUS dictionary.

      - Taken from the Kea RADIUS dictionary and the IANA registry. There is an aliasing mechanism built into the library that ensures backward compatibility e.g. ``Password`` translates to the standard name of the attribute ``User-Password``.

    * - Resolution of RADIUS Server Domain Names

      - At run time.

      - At hook library load time.

    * - Automatic Deduction of Source Address for Reaching RADIUS Servers (configured with ``bindaddr: "*"``)

      - At run time.

      - At hook library load time.

    * - RADIUS Server Limit per Service

      - 8

      - Unlimited

    * - Support for Including Dictionaries Inside Dictionaries

      - Yes

      - No

    * - Support for Vendor Attributes

      - Yes

      - No

    * - Attribute Names and Attribute Values

      - Case-insensitive

      - Case-sensitive

    * - Integer Values

      - Do not require an attribute definition.

      - Must have an associated attribute definition in the dictionary.

    * - Reply-Message Presence in the Kea Logs

      - Only as part of the aggregated list of attributes in ``RADIUS_AUTHENTICATION_ACCEPTED``, ``RADIUS_ACCESS_CACHE_INSERT``, ``RADIUS_ACCESS_CACHE_GET`` log messages.

      - Also has a dedicated ``RADIUS_REPLY_MESSAGE_ATTRIBUTE`` message per each Reply-Message attribute logged after a valid RADIUS reply is received.

    * - Behavior of Multiple Attributes of the Same Type (except Reply-Message)

      - Experimentally, only the **first** attribute on the wire from an Access-Accept message is considered.

      - Experimentally, only the **last** attribute on the wire from an Access-Accept message is considered.
