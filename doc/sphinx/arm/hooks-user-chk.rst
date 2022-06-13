.. _hooks-user-chk:

``user_chk``: User Check
========================

This library serves several purposes:

-  To assign "new" or "unregistered" users to a restricted subnet, while
   "known" or "registered" users are assigned to unrestricted subnets.

-  To allow DHCP response options or vendor option values to be
   customized based on user identity.

-  To provide a real-time record of user registration activity, which
   can be sampled by an external consumer.

-  To serve as a demonstration of various capabilities possible using
   the hooks interface.

This library is part of the Kea open source and is available to all users.

Once loaded, the library allows the separation of incoming requests into known
and unknown clients. For known clients, packets are processed
as usual, although it is possible to override the sending of certain options
on a per-host basis. Clients that are not on the known
hosts list are treated as unknown and are assigned to the last
subnet defined in the configuration file.

As an example of a use case, this behavior may be implemented to put unknown users
into a separate subnet that leads to a "walled garden," where they can
only access a registration portal. Once they fill in necessary data,
their details are added to the known clients file and they get a proper
address after their device is restarted.

.. note::

   This library was developed several years before the host reservation
   mechanism became available. Host reservation is much
   more powerful and flexible, but the ability of ``user_chk``
   to consult an external source of information about clients and alter
   Kea's behavior remains useful and of educational value.

The library reads the ``/tmp/user_chk_registry.txt`` file while being loaded
and each time an incoming packet is processed. Each line of the file is expected to
contain a self-contained JSON snippet which must have the
following two entries:

-  ``type`` - whose value is ``"HW_ADDR"`` for IPv4 users or ``"DUID"`` for IPv6
   users.

-  ``id`` - whose value is either the hardware address or the DUID from
   the request formatted as a string of hex digits, with or without ":"
   delimiters.

and may have zero or more of the following entries:

-  ``bootfile`` - whose value is the pathname of the desired file.

-  ``tftp_server`` - whose value is the hostname or IP address of the
   desired server.

A sample user registry file is shown below:

::

   { "type" : "HW_ADDR", "id" : "0c:0e:0a:01:ff:04", "bootfile" : "/tmp/v4bootfile" }
   { "type" : "HW_ADDR", "id" : "0c:0e:0a:01:ff:06", "tftp_server" : "tftp.v4.example.com" }
   { "type" : "DUID", "id" : "00:01:00:01:19:ef:e6:3b:00:0c:01:02:03:04", "bootfile" : "/tmp/v6bootfile" }
   { "type" : "DUID", "id" : "00:01:00:01:19:ef:e6:3b:00:0c:01:02:03:06", "tftp_server" : "tftp.v6.example.com" }

As with any other hook libraries provided by ISC, internals of the
``user_chk`` code are well-documented. Users may refer to the `user_chk
library section of the Kea Developer's Guide
<https://reports.kea.isc.org/dev_guide/d8/db2/libdhcp_user_chk.html>`__
for information on how the code works internally. That, together with the
`Hooks Framework section of the Kea Developer's Guide
<https://reports.kea.isc.org/dev_guide/index.html#hooksFramework>`__ should give users
some pointers on how to extend this library and perhaps even write one
from scratch.
