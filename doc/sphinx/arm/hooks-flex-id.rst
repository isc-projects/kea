.. _hooks-flex-id:

``flex_id``: Flexible Identifier for Host Reservations
======================================================

The Kea software provides a way to handle
host reservations that include addresses, prefixes, options, client
classes, and other features. The reservation can be based on hardware
address, DUID, circuit-id, or client-id in DHCPv4 and on hardware
address or DUID in DHCPv6. However, there are sometimes scenarios where
the reservation is more complex; it may use options other than those mentioned
above, use parts of specific options, or perhaps even use a combination of
several options and fields to uniquely identify a client. Those
scenarios are addressed by the Flexible Identifiers hook application.

The Flexible Identifier library is only available to ISC customers with a paid support
contract.

.. note::

   This library can only be loaded by the ``kea-dhcp4`` or ``kea-dhcp6``
   process.

The ``flex_id`` library allows the definition of an expression, using notation initially
used only for client classification. (See
:ref:`classification-using-expressions` for a detailed description of
the syntax available.) One notable difference is that for client
classification, the expression currently has to evaluate to either ``true``
or ``false``, while the flexible identifier expression is expected to
evaluate to a string that will be used as an identifier. It is a valid case
for the expression to evaluate to an empty string (e.g. in cases where a
client does not send specific options). This expression is then
evaluated for each incoming packet, and this evaluation generates an
identifier that is used to identify the client. In particular, there may
be host reservations that are tied to specific values of the flexible
identifier.

The library can be loaded similarly to other hook libraries. It
takes a mandatory parameter ``identifier-expression`` and some optional boolean
parameters like ``replace-client-id`` and ``ignore-iaid``:

::

   "Dhcp6": {
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_flex_id.so",
               "parameters": {
                   "identifier-expression": "expression",
                   "replace-client-id": false,
                   "ignore-iaid": false
               }
           },
           ...
       ]
   }

The flexible identifier library supports both DHCPv4 and DHCPv6.

Let's consider a case of an IPv6 network that has an
independent interface for each of its connected customers. Customers are
able to plug in whatever device they want, so any type of identifier
(e.g. a client-id) is unreliable. Therefore, the operator may decide to
use an option inserted by a relay agent to differentiate between
clients. In this particular deployment, the operator has verified that the
interface-id is unique for each customer-facing interface, so it
is suitable for usage as a reservation. However, only the first six bytes of
the interface-id are interesting, because the remaining bytes are either
randomly changed or not unique between devices. Therefore, the customer
decides to use the first six bytes of the interface-id option inserted by the
relay agent. After adding ``flex-id``, the ``host-reservation-identifiers`` goal
can be achieved by using the following configuration:

::

   "Dhcp6": {
       "subnet6": [{ ..., # subnet definition starts here
       "reservations": [
           "flex-id": "'port1234'", # value of the first 8 bytes of the interface-id
           "ip-addresses": [ "2001:db8::1" ]
       ],
       }], # end of subnet definitions
       "host-reservation-identifiers": ["duid", "flex-id"], # add "flex-id" to reservation identifiers
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_flex_id.so",
               "parameters": {
                   "identifier-expression": "substring(relay6[0].option[18].hex,0,8)"
               }
           },
           ...
       ]
   }

.. note::

  Care should be taken when adjusting the expression. If the expression
  changes, then all the ``flex-id`` values may change, possibly rendering
  all reservations based on ``flex-id`` unusable until they are manually updated.
  It is strongly recommended that administrators start with the expression and a
  handful of reservations, and then adjust the expression as needed. Once
  the desired result is obtained with the expression, host reservations
  can be deployed on a broader scale.

``flex-id`` values in host reservations can be specified in two ways. First,
they can be expressed as a hex string, e.g. the string "bar" can be represented
as 626174. Alternatively, it can be expressed as a quoted value (using
double and single quotes), e.g. "'bar'". The former is more convenient
for printable characters, while hex string values are more convenient
for non-printable characters and do not require the use of the
``hexstring`` operator.

::

   "Dhcp6": {
       "subnet6": [{ ..., # subnet definition starts here
       "reservations": [
           "flex-id": "01:02:03:04:05:06", # value of the first 8 bytes of the interface-id
           "ip-addresses": [ "2001:db8::1" ]
       ],
       }], # end of subnet definitions
       "host-reservation-identifiers": ["duid", "flex-id"], # add "flex-id" to reservation identifiers
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_flex_id.so",
               "parameters": {
                   "identifier-expression": "vendor[4491].option[1026].hex"
               }
           },
           ...
       ]
   }

The ``replace-client-id`` Flag
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When ``replace-client-id`` is set to ``false`` (which is the default setting),
the ``flex-id`` hook library uses the evaluated flexible identifier solely for
identifying host reservations, i.e. searching for reservations within a
database. This is the functional equivalent of other identifiers, similar
to hardware address or circuit-id. However, this mode of operation
implies that if a client device is replaced, it may cause a
conflict between an existing lease (allocated to the old device) and the
new lease being allocated to the new device. The conflict arises
because the same flexible identifier is computed for the replaced device,
so the server will try to allocate the same lease. The mismatch between
client identifiers sent by the new device and the old device causes the server
to refuse this new allocation until the old lease expires. A
manifestation of this problem is dependent on the specific expression used
as the flexible identifier, and is likely to appear if only options
and other parameters are used that identify where the device is connected
(e.g. circuit-id), rather than the device identification itself (e.g.
MAC address).

The ``flex-id`` library offers a way to overcome the problem with lease
conflicts by dynamically replacing the client identifier (or DUID in DHCPv6)
with a value derived from the flexible identifier. The server
processes the client's query as if the flexible identifier were sent in the
client identifier (or DUID) option. This guarantees that a returning
client (for which the same flexible identifier is evaluated) will be
assigned the same lease, despite the client identifier and/or MAC address
change.

The following is a stub configuration that enables this behavior:

::

   "Dhcp4": {
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_flex_id.so",
               "parameters": {
                   "identifier-expression": "expression",
                   "replace-client-id": true
               }
           },
           ...
       ]
   }

In the DHCPv4 case, the value derived from the flexible identifier is
formed by prepending one byte with a value of zero to the flexible identifier.
In the DHCPv6 case, it is formed by prepending two zero bytes before the
flexible identifier.

Note that for this mechanism to take effect, the DHCPv4 server must be
configured to respect the client identifier option value during lease
allocation, i.e. ``match-client-id`` must be set to ``true``. See
:ref:`dhcp4-match-client-id` for details. No additional settings are
required for DHCPv6.

If the ``replace-client-id`` option is set to ``true``, the value of the
``echo-client-id`` parameter (which governs whether to send back a
client-id option) is ignored.

The :ref:`hooks-lease-cmds` section describes commands used to retrieve,
update, and delete leases using various identifiers, such as ``hw-address`` and
``client-id``. The ``lease_cmds`` library does not natively support querying
for leases by flexible identifier. However, when ``replace-client-id`` is
set to ``true``, it makes it possible to query for leases using a value
derived from the flexible identifier. In DHCPv4, the query
looks similar to this:

::

   {
       "command": "lease4-get",
       "arguments": {
           "identifier-type": "client-id",
           "identifier": "00:54:64:45:66",
           "subnet-id": 44
       }
   }

where the hexadecimal value of "54:64:45:66" is a flexible identifier
computed for the client.

In DHCPv6, the corresponding query looks something like this:

::

   {
       "command": "lease6-get",
       "arguments": {
           "identifier-type": "duid",
           "identifier": "00:00:54:64:45:66",
           "subnet-id": 10
       }
   }

The ``ignore-iaid`` Flag
~~~~~~~~~~~~~~~~~~~~~~~~

When ``ignore-iaid`` is set to ``true`` (default value is ``false``), the
``flex-id`` hooks library will make the Kea DHCPv6 server ignore IAID value
from incoming IPv6 packets. This parameter is ignored by the Kea DHCPv4 server.

If the packet contains only one IA_NA, the IAID value will be changed to ``0``
and stored as such in the lease storage. Similarly if the packet contains only
one IA_PD, the IAID value will be changed to ``0`` and stored as such in the
lease storage. The IAID is restored to its initial value in the response back
to the client. The change is visible in the identifier expression if the IAID is
part of the expression.

.. note::

   To avoid lease conflicts, if the incoming packet contains more than one
   IA_NA, the IAID value will not be changed on any of the IA_NAs. Similarly,
   if the incoming packet contains more than one IA_PD, the IAID value will not
   be changed on any of the IA_PDs.

.. warning::

   This functionality breaks RFC compliance and should be enabled only if
   required. When enabled, a warning message is issued at configure time.
