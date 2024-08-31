.. ischooklib:: libdhcp_host_cache.so
.. _hooks-host-cache:

``libdhcp_host_cache.so``: Host Cache Reservations for Improved Performance
===========================================================================

Some database backends, such as RADIUS, are slow and may take
a long time to respond. Since Kea in general is synchronous, backend
performance directly affects DHCP performance. To minimize the
impact and improve performance, the Host Cache library provides a way to
cache information from the database locally. This includes negative
caching, i.e. the ability to remember that there is no client
information in the database.

.. note::

    :ischooklib:`libdhcp_host_cache.so` is available only to ISC customers with
    a paid support contract. For more information on subscription options,
    please complete the form at https://www.isc.org/contact.

.. note::

   This library can only be loaded by the :iscman:`kea-dhcp4` or
   :iscman:`kea-dhcp6` process.

In principle, this hook library can be used with any backend that may
introduce performance degradation (MySQL, PostgreSQL or RADIUS). Host Cache
must be loaded for the RADIUS accounting mechanism to work.

The Host Cache hook library is very simple. It takes only one
optional parameter (``maximum``), which defines the maximum number of hosts
to be cached. If not specified, the default value of 0 is used, which
means there is no limit. This hook library can be loaded the same way as
any other hook library; for example, this configuration could be used:

::

     "Dhcp4": {

     # Your regular DHCPv4 configuration parameters here.

     "hooks-libraries": [
     {
         "library": "/usr/local/lib/kea/hooks/libdhcp_host_cache.so",
         "parameters": {

             # Tells Kea to never cache more than 1000 hosts.
             "maximum": 1000

         }
     } ],
     ...
     }

Once loaded, the Host Cache hook library provides a number of new
commands which can be used either over the control channel (see
:ref:`ctrl-channel-client`) or the RESTful API (see
:ref:`agent-overview`). An example RESTful API client is described in
:ref:`shell-overview`. The following sections describe the commands
available.

.. isccmd:: cache-flush
.. _command-cache-flush:

The ``cache-flush`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command allows removal of a specified number of cached host
entries. It takes one parameter, which defines the number of hosts to be
removed. An example usage looks as follows:

::

   {
       "command": "cache-flush",
       "arguments": 1000
   }

This command removes 1000 hosts; to delete *all* cached
hosts, use :isccmd:`cache-clear` instead. The hosts are stored in FIFO
(first-in, first-out) order, so the oldest entries are always removed.

.. isccmd:: cache-clear
.. _command-cache-clear:

The ``cache-clear`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command allows removal of all cached host entries. An example usage
looks as follows:

::

   {
       "command": "cache-clear"
   }

This command removes all hosts. To delete only a certain
number of cached hosts, please use :isccmd:`cache-flush` instead.

.. isccmd:: cache-size
.. _command-cache-size:

The ``cache-size`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~

This command returns the number of host entries. An example usage looks
as follows:

::

   {
       "command": "cache-size"
   }

.. isccmd:: cache-write
.. _command-cache-write:

The ``cache-write`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

In general, the cache content is considered a runtime state and the
server can be shut down or restarted as usual; the cache is then
repopulated after restart. However, there are some cases when it is
useful to store the contents of the cache. One such case is RADIUS,
where the cached hosts also retain additional cached RADIUS attributes;
there is no easy way to obtain this information again, because renewing
clients send their packet to the DHCP server directly. Another use case
is when an administrator wants to restart the server and, for performance reasons,
wants it to start with a hot (populated) cache.

This command allows writing the contents of the in-memory cache to a
file on disk. It takes one parameter, which defines the filename. An
example usage looks as follows:

::

   {
       "command": "cache-write",
       "arguments": "/tmp/kea-host-cache.json"
   }

This causes the contents to be stored in the ``/tmp/kea-host-cache.json``
file. That file can then be loaded with the :isccmd:`cache-load` command or
processed by any other tool that is able to understand JSON format.

.. isccmd:: cache-load
.. _command-cache-load:

The ``cache-load`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~

See the previous section for a discussion of use cases where it may be
useful to write and load contents of the host cache to disk.

This command allows the contents of a file on disk to be loaded into an
in-memory cache. It takes one parameter, which defines the filename. An
example usage looks as follows:

::

   {
       "command": "cache-load",
       "arguments": "/tmp/kea-host-cache.json"
   }

This command stores the contents to the ``/tmp/kea-host-cache.json``
file. That file can then be loaded with the :isccmd:`cache-load` command or
processed by any other tool that is able to understand JSON format.

.. isccmd:: cache-get
.. _command-cache-get:

The ``cache-get`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~

This command is similar to :isccmd:`cache-write`, but instead of writing the cache
contents to disk, it returns the contents to whoever sent the command.

This command allows the contents of a file on disk to be loaded into an
in-memory cache. It takes one parameter, which defines the filename. An
example usage looks as follows:

::

   {
       "command": "cache-get"
   }

This command returns all the cached hosts; the response
may be large.

.. isccmd:: cache-get-by-id
.. _command-cache-get-by-id:

The ``cache-get-by-id`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is similar to :isccmd:`cache-get`, but instead of returning the whole
content it returns only the entries matching the given identifier.

It takes one parameter, which defines the identifier of wanted cached
host reservations. An example usage looks as follows:

::

   {
       "command": "cache-get-by-id",
       "arguments": {
           "hw-address": "01:02:03:04:05:06"
       }
   }

This command returns all the cached hosts with the given hardware
address.

.. isccmd:: cache-insert
.. _command-cache-insert:

The ``cache-insert`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command may be used to manually insert a host into the cache; there
are very few use cases when this command might be useful. This command
expects its arguments to follow the usual syntax for specifying host
reservations (see :ref:`host-reservation-v4` or
:ref:`host-reservation-v6`), with one difference: the ``subnet-id``
value must be explicitly specified.

An example command to insert an IPv4 host into the host cache
looks as follows:

::

   {
       "command": "cache-insert",
       "arguments": {
           "hw-address": "01:02:03:04:05:06",
           "subnet-id4": 4,
           "subnet-id6": 0,
           "ip-address": "192.0.2.100",
           "hostname": "somehost.example.org",
           "client-classes4": [ ],
           "client-classes6": [ ],
           "option-data4": [ ],
           "option-data6": [ ],
           "next-server": "192.0.0.2",
           "server-hostname": "server-hostname.example.org",
           "boot-file-name": "bootfile.efi",
           "host-id": 0
       }
   }

An example command to insert an IPv6 host into the host cache
looks as follows:

::

   {
       "command": "cache-insert",
       "arguments": {
           "hw-address": "01:02:03:04:05:06",
           "subnet-id4": 0,
           "subnet-id6": 6,
           "ip-addresses": [ "2001:db8::cafe:babe" ],
           "prefixes": [ "2001:db8:dead:beef::/64" ],
           "hostname": "",
           "client-classes4": [ ],
           "client-classes6": [ ],
           "option-data4": [ ],
           "option-data6": [ ],
           "next-server": "0.0.0.0",
           "server-hostname": "",
           "boot-file-name": "",
           "host-id": 0
       }
   }

.. isccmd:: cache-remove
.. _command-cache-remove:

The ``cache-remove`` Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sometimes it is useful to remove a single entry from the host cache: for
example, consider a situation where the device is active, Kea has already
provided configuration, and the host entry is in cache. As a result of
administrative action (e.g. the customer hasn't paid their bills or has
been upgraded to better service), the information in the backend database
(e.g. MySQL or RADIUS) is being updated. However, since the cache is in use,
Kea does not notice the change as the cached values are used. The
:isccmd:`cache-remove` command can solve this problem by removing a cached entry
after administrative changes.

The :isccmd:`cache-remove` command works similarly to the :isccmd:`reservation-get` command.
It allows querying by two parameters: either ``subnet-id4`` or ``subnet-id6``;
or ``ip-address`` (may be an IPv4 or IPv6 address), ``hw-address`` (specifies
a hardware/MAC address), ``duid``, ``circuit-id``, ``client-id``, or ``flex-id``.

An example command to remove an IPv4 host with reserved address
192.0.2.1 from a subnet with a ``subnet-id`` 123 looks as follows:

::

   {
       "command": "cache-remove",
       "arguments": {
           "ip-address": "192.0.2.1",
           "subnet-id": 123
       }
   }

Another example that removes an IPv6 host identifier by DUID and
specific ``subnet-id`` is:

::

   {
       "command": "cache-remove",
       "arguments": {
           "duid": "00:01:ab:cd:f0:a1:c2:d3:e4",
           "subnet-id": 123
       }
   }
