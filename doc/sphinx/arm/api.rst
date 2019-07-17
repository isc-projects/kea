.. _api:

*************
API Reference
*************

Kea currently supports 121 commands: ``build-report`` , ``cache-clear``
, ``cache-get`` , ``cache-get-by-id`` , ``cache-insert`` ,
``cache-load`` , ``cache-remove`` , ``cache-size`` , ``cache-write`` ,
``class-add`` , ``class-del`` , ``class-get`` , ``class-list`` ,
``class-update`` , ``config-get`` , ``config-reload`` , ``config-set`` ,
``config-test`` , ``config-write`` , ``dhcp-disable`` , ``dhcp-enable``
, ``ha-continue`` , ``ha-heartbeat`` , ``ha-scopes`` , ``ha-sync`` ,
``lease4-add`` , ``lease4-del`` , ``lease4-get`` , ``lease4-get-all`` ,
``lease4-update`` , ``lease4-wipe`` , ``lease6-add`` , ``lease6-del`` ,
``lease6-get`` , ``lease6-get-all`` , ``lease6-update`` ,
``lease6-wipe`` , ``leases-reclaim`` , ``libreload`` , ``list-commands``
, ``network4-add`` , ``network4-del`` , ``network4-get`` ,
``network4-list`` , ``network4-subnet-add`` , ``network4-subnet-del`` ,
``network6-add`` , ``network6-del`` , ``network6-get`` ,
``network6-list`` , ``network6-subnet-add`` , ``network6-subnet-del`` ,
``remote-global-parameter4-del`` , ``remote-global-parameter4-get`` ,
``remote-global-parameter4-get-all`` , ``remote-global-parameter4-set``
, ``remote-global-parameter6-del`` , ``remote-global-parameter6-get`` ,
``remote-global-parameter6-get-all`` , ``remote-global-parameter6-set``
, ``remote-network4-del`` , ``remote-network4-get`` ,
``remote-network4-list`` , ``remote-network4-set`` ,
``remote-network6-del`` , ``remote-network6-get`` ,
``remote-network6-list`` , ``remote-network6-set`` ,
``remote-option-def4-del`` , ``remote-option-def4-get`` ,
``remote-option-def4-get-all`` , ``remote-option-def4-set`` ,
``remote-option-def6-del`` , ``remote-option-def6-get`` ,
``remote-option-def6-get-all`` , ``remote-option-def6-set`` ,
``remote-option4-global-del`` , ``remote-option4-global-get`` ,
``remote-option4-global-get-all`` , ``remote-option4-global-set`` ,
``remote-option6-global-del`` , ``remote-option6-global-get`` ,
``remote-option6-global-get-all`` , ``remote-option6-global-set`` ,
``remote-subnet4-del-by-id`` , ``remote-subnet4-del-by-prefix`` ,
``remote-subnet4-get-by-id`` , ``remote-subnet4-get-by-prefix`` ,
``remote-subnet4-list`` , ``remote-subnet4-set`` ,
``remote-subnet6-del-by-id`` , ``remote-subnet6-del-by-prefix`` ,
``remote-subnet6-get-by-id`` , ``remote-subnet6-get-by-prefix`` ,
``remote-subnet6-list`` , ``remote-subnet6-set`` , ``reservation-add`` ,
``reservation-del`` , ``reservation-get`` , ``reservation-get-all`` ,
``reservation-get-page`` , ``shutdown`` , ``stat-lease4-get`` ,
``stat-lease6-get`` , ``statistic-get`` , ``statistic-get-all`` ,
``statistic-remove`` , ``statistic-remove-all`` , ``statistic-reset`` ,
``statistic-reset-all`` , ``subnet4-add`` , ``subnet4-del`` ,
``subnet4-get`` , ``subnet4-list`` , ``subnet4-update`` ,
``subnet6-add`` , ``subnet6-del`` , ``subnet6-get`` , ``subnet6-list`` ,
``subnet6-update`` , ``version-get`` .

Commands supported by the kea-ctrl-agent daemon: ``build-report`` ,
``config-get`` , ``config-reload`` , ``config-set`` , ``config-test`` ,
``config-write`` , ``list-commands`` , ``shutdown`` , ``version-get`` .

Commands supported by the kea-dhcp-ddns daemon: ``build-report`` ,
``config-get`` , ``config-reload`` , ``config-set`` , ``config-test`` ,
``config-write`` , ``list-commands`` , ``shutdown`` , ``version-get`` .

Commands supported by the kea-dhcp4 daemon: ``build-report`` ,
``cache-clear`` , ``cache-get`` , ``cache-get-by-id`` , ``cache-insert``
, ``cache-load`` , ``cache-remove`` , ``cache-size`` , ``cache-write`` ,
``class-add`` , ``class-del`` , ``class-get`` , ``class-list`` ,
``class-update`` , ``config-get`` , ``config-reload`` , ``config-set`` ,
``config-test`` , ``config-write`` , ``dhcp-disable`` , ``dhcp-enable``
, ``ha-continue`` , ``ha-heartbeat`` , ``ha-scopes`` , ``ha-sync`` ,
``lease4-add`` , ``lease4-del`` , ``lease4-get`` , ``lease4-get-all`` ,
``lease4-update`` , ``lease4-wipe`` , ``leases-reclaim`` , ``libreload``
, ``list-commands`` , ``network4-add`` , ``network4-del`` ,
``network4-get`` , ``network4-list`` , ``network4-subnet-add`` ,
``network4-subnet-del`` , ``remote-global-parameter4-del`` ,
``remote-global-parameter4-get`` , ``remote-global-parameter4-get-all``
, ``remote-global-parameter4-set`` , ``remote-network4-del`` ,
``remote-network4-get`` , ``remote-network4-list`` ,
``remote-network4-set`` , ``remote-option-def4-del`` ,
``remote-option-def4-get`` , ``remote-option-def4-get-all`` ,
``remote-option-def4-set`` , ``remote-option4-global-del`` ,
``remote-option4-global-get`` , ``remote-option4-global-get-all`` ,
``remote-option4-global-set`` , ``remote-subnet4-del-by-id`` ,
``remote-subnet4-del-by-prefix`` , ``remote-subnet4-get-by-id`` ,
``remote-subnet4-get-by-prefix`` , ``remote-subnet4-list`` ,
``remote-subnet4-set`` , ``reservation-add`` , ``reservation-del`` ,
``reservation-get`` , ``reservation-get-all`` , ``reservation-get-page``
, ``shutdown`` , ``stat-lease4-get`` , ``statistic-get`` ,
``statistic-get-all`` , ``statistic-remove`` , ``statistic-remove-all``
, ``statistic-reset`` , ``statistic-reset-all`` , ``subnet4-add`` ,
``subnet4-del`` , ``subnet4-get`` , ``subnet4-list`` ,
``subnet4-update`` , ``version-get`` .

Commands supported by the kea-dhcp6 daemon: ``build-report`` ,
``cache-clear`` , ``cache-get`` , ``cache-get-by-id`` , ``cache-insert``
, ``cache-load`` , ``cache-remove`` , ``cache-size`` , ``cache-write`` ,
``class-add`` , ``class-del`` , ``class-get`` , ``class-list`` ,
``class-update`` , ``config-get`` , ``config-reload`` , ``config-set`` ,
``config-test`` , ``config-write`` , ``dhcp-disable`` , ``dhcp-enable``
, ``ha-continue`` , ``ha-heartbeat`` , ``ha-scopes`` , ``ha-sync`` ,
``lease6-add`` , ``lease6-del`` , ``lease6-get`` , ``lease6-get-all`` ,
``lease6-update`` , ``lease6-wipe`` , ``leases-reclaim`` , ``libreload``
, ``list-commands`` , ``network6-add`` , ``network6-del`` ,
``network6-get`` , ``network6-list`` , ``network6-subnet-add`` ,
``network6-subnet-del`` , ``remote-global-parameter6-del`` ,
``remote-global-parameter6-get`` , ``remote-global-parameter6-get-all``
, ``remote-global-parameter6-set`` , ``remote-network6-del`` ,
``remote-network6-get`` , ``remote-network6-list`` ,
``remote-network6-set`` , ``remote-option-def6-del`` ,
``remote-option-def6-get`` , ``remote-option-def6-get-all`` ,
``remote-option-def6-set`` , ``remote-option6-global-del`` ,
``remote-option6-global-get`` , ``remote-option6-global-get-all`` ,
``remote-option6-global-set`` , ``remote-subnet6-del-by-id`` ,
``remote-subnet6-del-by-prefix`` , ``remote-subnet6-get-by-id`` ,
``remote-subnet6-get-by-prefix`` , ``remote-subnet6-list`` ,
``remote-subnet6-set`` , ``reservation-add`` , ``reservation-del`` ,
``reservation-get`` , ``reservation-get-all`` , ``reservation-get-page``
, ``shutdown`` , ``stat-lease6-get`` , ``statistic-get`` ,
``statistic-get-all`` , ``statistic-remove`` , ``statistic-remove-all``
, ``statistic-reset`` , ``statistic-reset-all`` , ``subnet6-add`` ,
``subnet6-del`` , ``subnet6-get`` , ``subnet6-list`` ,
``subnet6-update`` , ``version-get`` .

.. _commands-cb_cmds-lib:

Commands supported by the Configuration Backend Commands (cb_cmds) hooks library:
``remote-global-parameter4-del`` , ``remote-global-parameter4-get`` ,
``remote-global-parameter4-get-all`` , ``remote-global-parameter4-set``
, ``remote-global-parameter6-del`` , ``remote-global-parameter6-get`` ,
``remote-global-parameter6-get-all`` , ``remote-global-parameter6-set``
, ``remote-network4-del`` , ``remote-network4-get`` ,
``remote-network4-list`` , ``remote-network4-set`` ,
``remote-network6-del`` , ``remote-network6-get`` ,
``remote-network6-list`` , ``remote-network6-set`` ,
``remote-option-def4-del`` , ``remote-option-def4-get`` ,
``remote-option-def4-get-all`` , ``remote-option-def4-set`` ,
``remote-option-def6-del`` , ``remote-option-def6-get`` ,
``remote-option-def6-get-all`` , ``remote-option-def6-set`` ,
``remote-option4-global-del`` , ``remote-option4-global-get`` ,
``remote-option4-global-get-all`` , ``remote-option4-global-set`` ,
``remote-option6-global-del`` , ``remote-option6-global-get`` ,
``remote-option6-global-get-all`` , ``remote-option6-global-set`` ,
``remote-subnet4-del-by-id`` , ``remote-subnet4-del-by-prefix`` ,
``remote-subnet4-get-by-id`` , ``remote-subnet4-get-by-prefix`` ,
``remote-subnet4-list`` , ``remote-subnet4-set`` ,
``remote-subnet6-del-by-id`` , ``remote-subnet6-del-by-prefix`` ,
``remote-subnet6-get-by-id`` , ``remote-subnet6-get-by-prefix`` ,
``remote-subnet6-list`` , ``remote-subnet6-set`` .

.. _commands-class_cmds-lib:

Commands supported by the Class Commands (class_cmds) hooks library: ``class-add`` ,
``class-del`` , ``class-get`` , ``class-list`` , ``class-update`` .

.. _commands-high_availability-lib:

Commands supported by the High Availability (high_availability) hooks library: ``ha-continue`` ,
``ha-heartbeat`` , ``ha-scopes`` , ``ha-sync`` .

.. _commands-host_cache-lib:

Commands supported by the Host Cache (host_cache) hooks library: ``cache-clear`` ,
``cache-get`` , ``cache-get-by-id`` , ``cache-insert`` , ``cache-load``
, ``cache-remove`` , ``cache-size`` , ``cache-write`` .

.. _commands-host_cmds-lib:

Commands supported by the Host Commands (host_cmds) hooks library: ``reservation-add`` ,
``reservation-del`` , ``reservation-get`` , ``reservation-get-all`` ,
``reservation-get-page`` .

.. _commands-lease_cmds-lib:

Commands supported by the Lease Commands (lease_cmds) hooks library: ``lease4-add`` ,
``lease4-del`` , ``lease4-get`` , ``lease4-get-all`` , ``lease4-update``
, ``lease4-wipe`` , ``lease6-add`` , ``lease6-del`` , ``lease6-get`` ,
``lease6-get-all`` , ``lease6-update`` , ``lease6-wipe`` .

.. _commands-stat_cmds-lib:

Commands supported by the Supplemental Statistics Commands (stat_cmds) hooks library: ``stat-lease4-get`` ,
``stat-lease6-get`` .

.. _commands-subnet_cmds-lib:

Commands supported by the Subnet Commands (subnet_cmds) hooks library: ``network4-add`` ,
``network4-del`` , ``network4-get`` , ``network4-list`` ,
``network4-subnet-add`` , ``network4-subnet-del`` , ``network6-add`` ,
``network6-del`` , ``network6-get`` , ``network6-list`` ,
``network6-subnet-add`` , ``network6-subnet-del`` , ``subnet4-add`` ,
``subnet4-del`` , ``subnet4-get`` , ``subnet4-list`` ,
``subnet4-update`` , ``subnet6-add`` , ``subnet6-del`` , ``subnet6-get``
, ``subnet6-list`` , ``subnet6-update`` .

.. _reference-build-report:

build-report reference
======================

``build-report`` - returns a list of compilation options that this
particular binary was built with.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``, ``kea-dhcp-ddns``,
``kea-ctrl-agent``

Availability: 1.2.0 (built-in)

Description and examples: see :ref:`command-build-report`

Command syntax:

::

   {
       "command": "build-report"
   }

Response syntax:

::

   {
       "result": 0,
       "text": <string with build details>
   }

.. _reference-cache-clear:

cache-clear reference
=====================

``cache-clear`` - removes all cached host reservations.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The Host Cache hooks library<commands-host_cache-lib>`)

Description and examples: see :ref:`command-cache-clear`

Command syntax:

::

   {
       "command": "cache-clear"
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-cache-get:

cache-get reference
===================

``cache-get`` - returns full content of the host cache.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The Host Cache hooks library<commands-host_cache-lib>`)

Description and examples: see :ref:`command-cache-get`

Command syntax:

::

   {
       "command": "cache-get"
   }

Response syntax:

::

   {
       "result": 0
       "text": "123 entries returned."
       "arguments": <list of host reservations>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-cache-get-by-id:

cache-get-by-id reference
=========================

``cache-get-by-id`` - returns entries matching the given identifier from
the host cache.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Host Cache hooks library<commands-host_cache-lib>`)

Description and examples: see :ref:`command-cache-get-by-id`

Command syntax:

::

   {
       "command": "cache-get-by-id",
       "arguments": {
           "hw-address": "01:02:03:04:05:06"
       }

Response syntax:

::

   {
       "result": 0
       "text": "2 entries returned."
       "arguments": <list of host reservations>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-cache-insert:

cache-insert reference
======================

``cache-insert`` - manually inserts a host into the cache.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The Host Cache hooks library<commands-host_cache-lib>`)

Description and examples: see :ref:`command-cache-insert`

Command syntax:

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
   },
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

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-cache-load:

cache-load reference
====================

``cache-load`` - allows the contents of a file on disk to be loaded
into an in-memory cache.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The Host Cache hooks library<commands-host_cache-lib>`)

Description and examples: see :ref:`command-cache-load`

Command syntax:

::

   {
       "command": "cache-load",
       "arguments": "/tmp/kea-host-cache.json"
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-cache-remove:

cache-remove reference
======================

``cache-remove`` - works similarly to the reservation-get command.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The Host Cache hooks library<commands-host_cache-lib>`)

Description and examples: see :ref:`command-cache-remove`

Command syntax:

::

   {
       "command": "cache-remove",
       "arguments": {
           "ip-address": "192.0.2.1",
           "subnet-id": 123
       }
   }

   Another example that removes the IPv6 host identifier by DUID and specific subnet-id is:
   {
       "command": "cache-remove",
       "arguments": {
           "duid": "00:01:ab:cd:f0:a1:c2:d3:e4",
           "subnet-id": 123
       }
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-cache-size:

cache-size reference
====================

``cache-size`` - returns the number of entries in the host cache.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Host Cache hooks library<commands-host_cache-lib>`)

Description and examples: see :ref:`command-cache-size`

Command syntax:

::

   {
       "command": "cache-size"
   }

Response syntax:

::

   {
       "result": 0
       "text": "123 entries."
       "arguments": { "size": 123 }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-cache-write:

cache-write reference
=====================

``cache-write`` - instructs Kea to write its host cache content to disk.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The Host Cache hooks library<commands-host_cache-lib>`)

Description and examples: see :ref:`command-cache-write`

Command syntax:

::

   {
       "command": "cache-write",
       "arguments": "/path/to/the/file.json"
   }

The command takes one mandatory argument that specifies a filename path
of a file to be written.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-class-add:

class-add reference
===================

``class-add`` - creates and adds a new class to
the existing server configuration.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.5.0 (:ref:`The Class Commands hooks library<commands-class_cmds-lib>`)

Description and examples: see :ref:`command-class-add`

Command syntax:

::

   {
       "command": "class-add",
       "arguments": {
           "client-classes": [ {
              "name": <name of the class>,
              "test": <test expression to be evaluated on incoming packets>,
              "option-data": [ <option values here> ],
              "option-def": [ <option defintions here> ],
              "next-server": <ipv4 address>,
              "server-hostname": <string>,
              "boot-file-name": <name of the boot file>
           } ]
       }
   }

The ``next-server``, ``server-hostname``, and ``boot-file-name`` commands are
DHCPv4-specific. Only one client class can be added with a single
command.

Response syntax:

::

   {
       "result": 0,
       "text": "Class '<class-name>' added.",
   }

The command will be successful (result 0), unless the class name is a
duplicate or another error occurs (result 1).

.. _reference-class-del:

class-del reference
===================

``class-del`` - removes a client class from the server configuration.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.5.0 (:ref:`The Class Commands hooks library<commands-class_cmds-lib>`)

Description and examples: see :ref:`command-class-del`

Command syntax:

::

   {
       "command": "class-del",
       "arguments": {
           "name": <name of the class>
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "Class '<class-name>' deleted."
   }

The command will return a result of 3 (empty) if the client class
does not exist. If the client class exists, the returned result is 0 if
the deletion was successful and the result is 1 if the deletion is
unsuccessful.

.. _reference-class-get:

class-get reference
===================

``class-get`` - returns detailed information about an existing client class.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.5.0 (:ref:`The Class Commands hooks library<commands-class_cmds-lib>`)

Description and examples: see :ref:`command-class-get`

Command syntax:

::

   {
       "command": "class-get",
       "arguments": {
           "name": <name of the class>
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "Class '<class-name>' definition returned",
       "arguments": {
           "client-classes": [
               {
                   "name": <name of the class>,
                   "only-if-required": <only if required boolean value>,
                   "test": <test expression to be evaluated on incoming packets>,
                   "option-data": [ <option values here> ],
                   "option-def": [ <option defintions here> ],
                   "next-server": <ipv4 address>,
                   "server-hostname": <string>,
                   "boot-file-name": <name of the boot file>
               }
           ]
       }
   }

The returned information depends on the DHCP server type, i.e. some
parameters are specific to DHCPv4 server. Also, some parameters may not
be returned if they are not set for the client class. If a class with the
specified name does not exist, a result of 3 (empty) is returned. If the
client class is found, the result of 0 is returned. If there is an error
while processing the command, the result of 1 is returned.

.. _reference-class-list:

class-list reference
====================

``class-list`` - retrieves a list of all client
classes from the server configuration.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.5.0 (:ref:`The Class Commands hooks library<commands-class_cmds-lib>`)

Description and examples: see :ref:`command-class-list`

Command syntax:

::

   {
       "command": "class-list"
   }

This command includes no arguments.

Response syntax:

::

   {
       "result": 0,
       "text": "<number of> classes found",
       "arguments": {
           "client-classes": [
               {
                   "name": <first class name>
               },
               {
                   "name": <second class name>
               }
           ]
       }
   }

The returned list of classes merely contains their names. To
retrieve full information about one of these classes, use
:ref:`command-class-get`. The returned result is 3 (empty) if no
classes are found. If the command is processed successfully and the list
of client classes is not empty, the result of 0 is returned. If there is
an error while processing the command, the result of 1 is returned.

.. _reference-class-update:

class-update reference
======================

``class-update`` - updates an existing client
class in the server configuration.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.5.0 (:ref:`The Class Commands hooks library<commands-class_cmds-lib>`)

Description and examples: see :ref:`command-class-update`

Command syntax:

::

   {
       "command": "class-update",
       "arguments": {
           "client-classes": [ {
              "name": <name of the class>,
              "test": <test expression to be evaluated on incoming packets>,
              "option-data": [ <option values here> ],
              "option-def": [ <option defintions here> ],
              "next-server": <ipv4 address>,
              "server-hostname": <string>,
              "boot-file-name": <name of the boot file>
           } ]
       }
   }

The ``next-server``, ``server-hostname``, and ``boot-file-name`` commands are
DHCPv4-specific. Only one client class can be updated with a single
command.

Response syntax:

::

   {
       "result": 0,
       "text": "Class '<class-name>' updated.",
   }

The command will return the result of 3 (empty) if the client class
does not exist. If the client class exists, the returned result is 0 if
the update was successful and 1 if the update is unsuccessful.

.. _reference-config-get:

config-get reference
====================

``config-get`` - retrieves the current configuration used by the server.
The configuration is roughly equal to the configuration file, but
includes additional changes made by other commands and due to parameters
inheritance.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``, ``kea-dhcp-ddns``,
``kea-ctrl-agent``

Availability: 1.2.0 (built-in)

Description and examples: see :ref:`command-config-get`

Command syntax:

::

   {
       "command": "config-get"
   }

This command takes no parameters.

Response syntax:

::

   {
       "result": <integer>,
       "arguments": {
           <JSON configuration here, starting with Dhcp4, Dhcp6, or Control-agent object>
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-config-reload:

config-reload reference
=======================

``config-reload`` - instructs Kea to load
again the configuration file that was used previously.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``, ``kea-dhcp-ddns``,
``kea-ctrl-agent``

Availability: 1.2.0 (built-in)

Description and examples: see :ref:`command-config-reload`

Command syntax:

::

   {
       "command": "config-reload"
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-config-set:

config-set reference
====================

``config-set`` - instructs the server to replace
its current configuration with the new configuration supplied in the
command's arguments.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``, ``kea-dhcp-ddns``,
``kea-ctrl-agent``

Availability: 1.2.0 (built-in)

Description and examples: see :ref:`command-config-set`

Command syntax:

::

   {
       "command": "config-set",
       "arguments":  {
           "<server>": {
           }
        }
   }

where <server> is the configuration element name for a given server, such
as "Dhcp4" or "Dhcp6"

Response syntax:

::

       {"result": 0, "text": "Configuration successful." }

       or

       {"result": 1, "text": "unsupported parameter: BOGUS (<string>:16:26)" }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-config-test:

config-test reference
=====================

``config-test`` - instructs the server to check
whether the new configuration supplied in the command's arguments can be
loaded.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``, ``kea-dhcp-ddns``,
``kea-ctrl-agent``

Availability: 1.2.0 (built-in)

Description and examples: see :ref:`command-config-test`

Command syntax:

::

   {
       "command": "config-test",
       "arguments":  {
           "<server>": {
           }
        }
   }

where <server> is the configuration element name for a given server, such
as "Dhcp4" or "Dhcp6"

Response syntax:

::

   {"result": 0, "text": "Configuration seems sane..." }

       or

       {"result": 1, "text": "unsupported parameter: BOGUS (<string>:16:26)" }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-config-write:

config-write reference
======================

``config-write`` - instructs the Kea server to
write its current configuration to a file on disk.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``, ``kea-dhcp-ddns``,
``kea-ctrl-agent``

Availability: 1.2.0 (built-in)

Description and examples: see :ref:`command-config-write`

Command syntax:

::

   {
       "command": "config-write",
       "arguments": {
           "filename": "config-modified-2017-03-15.json"
       }
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-dhcp-disable:

dhcp-disable reference
======================

``dhcp-disable`` - globally disables the DHCP service.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (built-in)

Description and examples: see :ref:`command-dhcp-disable`

Command syntax:

::

   {
       "command": "dhcp-disable",
       "arguments": {
           "max-period": 20
       }
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-dhcp-enable:

dhcp-enable reference
=====================

``dhcp-enable`` - globally enables the DHCP service.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (built-in)

Description and examples: see :ref:`command-dhcp-enable`

Command syntax:

::

   {
       "command": "dhcp-enable"
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-ha-continue:

ha-continue reference
=====================

``ha-continue`` - resumes the operation of the
paused HA state machine.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The High Availability hooks library<commands-high_availability-lib>`)

Description and examples: see :ref:`command-ha-continue`

Command syntax:

::

   {
       "command": "ha-continue"
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-ha-heartbeat:

ha-heartbeat reference
======================

``ha-heartbeat`` - is sent internally by a Kea partner when
operating in High Availability (HA) mode; it retrieves the server HA
state and clock value.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The High Availability hooks library<commands-high_availability-lib>`)

Description and examples: see :ref:`ha-server-states`

Command syntax:

::

   {
       "command": "ha-heartbeat",
       }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The response to this command is different from the typical command
response. The response will include the server state (see
:ref:`ha-server-states` plus the current clock value.

.. _reference-ha-scopes:

ha-scopes reference
===================

``ha-scopes`` - modifies the scope that the server is
responsible for serving when operating in High Availability (HA) mode.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The High Availability hooks library<commands-high_availability-lib>`)

Description and examples: see :ref:`command-ha-scopes`

Command syntax:

::

   {
       "command": "ha-scopes",
       "service": [ <service, typically "dhcp4" or "dhcp6"> ],
       "arguments": {
           "scopes": [ "HA_server1", "HA_server2" ]
       }

In the example given, the arguments configure the server to handle
traffic from both HA_server1 and HA_server2 scopes.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-ha-sync:

ha-sync reference
=================

``ha-sync`` - instructs the server running in HA
mode to synchronize its local lease database with the selected peer.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The High Availability hooks library<commands-high_availability-lib>`)

Description and examples: see :ref:`command-ha-sync`

Command syntax:

::

   {
       "command": "ha-sync",
       "service": [ <service affected:> "dhcp4" or "dhcp6" ],
       "arguments": {
           "server-name": <name of the partner server>,
           "max-period": <integer, in seconds>
       }
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease4-add:

lease4-add reference
====================

``lease4-add`` - adds a new IPv4 lease administratively.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-add`

Command syntax:

::

   {
       "command": "lease4-add",
       "arguments": {
           "ip-address": "192.0.2.202",
           "hw-address": "1a:1b:1c:1d:1e:1f"
       }
   }

Note that Kea 1.4 requires an additional argument, subnet-ID, which is
optional as of Kea 1.5. A number of other more detailed optional
arguments are also supported.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease4-del:

lease4-del reference
====================

``lease4-del`` - deletes a lease from the lease database.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-del`

Command syntax:

::

   {
       "command": "lease4-del",
       "arguments": {
           "ip-address": "192.0.2.202"
       }
   }

Specify the lease to be deleted either by IP address, or by
identifier-type and identifier value. Currently supported identifiers
are "hw-address" and "client-id".

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease4-get:

lease4-get reference
====================

``lease4-get`` - queries the lease database and retrieves existing leases.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-get`

Command syntax:

::

   {
       "command": "lease4-get",
       "arguments": {
           "ip-address": "192.0.2.1"
       }
   }

Response syntax:

::

   {
     "arguments": {
       "client-id": "42:42:42:42:42:42:42:42",
       "cltt": 12345678,
       "fqdn-fwd": false,
       "fqdn-rev": true,
       "hostname": "myhost.example.com.",
       "hw-address": "08:08:08:08:08:08",
       "ip-address": "192.0.2.1",
       "state": 0,
       "subnet-id": 44,
       "valid-lft": 3600
     },
     "result": 0,
     "text": "IPv4 lease found."
   }

``lease4-get`` returns a result that indicates a result of the operation and
lease details, if found. It has one of the following values: 0
(success), 1 (error), or 2 (empty).

.. _reference-lease4-get-all:

lease4-get-all reference
========================

``lease4-get-all`` - retrieves all IPv4 leases
or all leases for the specified set of subnets.

Supported by: ``kea-dhcp4``

Availability: 1.4.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-get-all`

Command syntax:

::

   {
       "command": "lease4-get-all"
       "arguments": "subnets"
   }

The ``lease4-get-all`` command may result in very large responses.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease4-update:

lease4-update reference
=======================

``lease4-update`` - updates existing leases.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-update`

Command syntax:

::

   {
     "command": "lease4-update",
     "arguments": {
       "ip-address": "192.0.2.1",
       "hostname": "newhostname.example.org",
       "hw-address": "1a:1b:1c:1d:1e:1f",
       "subnet-id": 44,
       "force-create": true
     }
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease4-wipe:

lease4-wipe reference
=====================

``lease4-wipe`` - removes all leases associated with a given subnet.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-wipe`

Command syntax:

::

   {
     "command": "lease4-wipe",
     "arguments": {
       "subnet-id": 44
     }
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease6-add:

lease6-add reference
====================

``lease6-add`` - creates a new lease administratively.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-add`

Command syntax:

::

   {
       "command": "lease6-add",
       "arguments": {
           "subnet-id": 66,
           "ip-address": "2001:db8::3",
           "duid": "1a:1b:1c:1d:1e:1f:20:21:22:23:24",
           "iaid": 1234
       }
   }

``lease6-add`` can be also used to add leases for IPv6 prefixes.

Response syntax:

::

   { "result": 0, "text": "Lease added." }
       { "result": 1, "text": "missing parameter 'ip-address' (<string>:3:19)" }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease6-del:

lease6-del reference
====================

``lease6-del`` - deletes a lease from the lease database.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-del`

Command syntax:

::

   {
       "command": "lease6-del",
       "arguments": {
           "ip-address": "192.0.2.202"
       }
   }

``lease6-del`` returns a result that indicates a outcome of the operation.
It has one of the following values: 0 (success), 1 (error), or 3 (empty).

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease6-get:

lease6-get reference
====================

``lease6-get`` - queries the lease database and retrieves existing leases.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-get`

Command syntax:

::

   {
     "command": "lease6-get",
     "arguments": {
       "ip-address": "2001:db8:1234:ab::",
       "type": "IA_PD"
     }
   }

``lease6-get`` returns a result that indicates a result of the operation and
lease details, if found. It has one of the following values: 0
(success), 1 (error), or 2 (empty).

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease6-get-all:

lease6-get-all reference
========================

``lease6-get-all`` - retrieves all IPv6 leases
or all leases for the specified set of subnets.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-get-all`

Command syntax:

::

   {
       "command": "lease6-get-all",
       "arguments": {
           "subnets": [ 1, 2, 3, 4 ]
       }
   }

Response syntax:

::

   {
       "arguments": {
           "leases": [
               {
                   "cltt": 12345678,
                   "duid": "42:42:42:42:42:42:42:42",
                   "fqdn-fwd": false,
                   "fqdn-rev": true,
                   "hostname": "myhost.example.com.",
                   "hw-address": "08:08:08:08:08:08",
                   "iaid": 1,
                   "ip-address": "2001:db8:2::1",
                   "preferred-lft": 500,
                   "state": 0,
                   "subnet-id": 44,
                   "type": "IA_NA",
                   "valid-lft": 3600
               },
               {
                   "cltt": 12345678,
                   "duid": "21:21:21:21:21:21:21:21",
                   "fqdn-fwd": false,
                   "fqdn-rev": true,
                   "hostname": "",
                   "iaid": 1,
                   "ip-address": "2001:db8:0:0:2::",
                   "preferred-lft": 500,
                   "prefix-len": 80,
                   "state": 0,
                   "subnet-id": 44,
                   "type": "IA_PD",
                   "valid-lft": 3600
               }
           ]
       },
       "result": 0,
       "text": "2 IPv6 lease(s) found."
   }

The ``lease6-get-all`` command may result in very large responses.

.. _reference-lease6-update:

lease6-update reference
=======================

``lease6-update`` - updates existing leases.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-update`

Command syntax:

::

   {
     "command": "lease6-update",
     "arguments": {
       "ip-address": "2001:db8::1",
       "duid": "88:88:88:88:88:88:88:88",
       "iaid": 7654321,
       "hostname": "newhostname.example.org",
       "subnet-id": 66,
       "force-create": false
     }
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-lease6-wipe:

lease6-wipe reference
=====================

``lease6-wipe`` - removes all leases associated with a given subnet.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Lease Commands hooks library<commands-lease_cmds-lib>`)

Description and examples: see :ref:`command-lease4-wipe`

Command syntax:

::

   {
     "command": "lease6-wipe",
     "arguments": {
       "subnet-id": 66
     }
   }

Note: not all backends support this command.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-leases-reclaim:

leases-reclaim reference
========================

``leases-reclaim`` - instructs the server to
reclaim all expired leases immediately.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.0.0 (built-in)

Description and examples: see :ref:`command-leases-reclaim`

Command syntax:

::

   {
       "command": "leases-reclaim",
       "arguments": {
           "remove": true
       }
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-libreload:

libreload reference
===================

``libreload`` - unloads and then loads all currently loaded hook libraries.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.2.0 (built-in)

Description and examples: see :ref:`command-libreload`

Command syntax:

::

   {
       "command": "libreload",
       "arguments": { }
   }

The server will respond with a result of 0 indicating success, or 1
indicating a failure.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-list-commands:

list-commands reference
=======================

``list-commands`` - retrieves a list of all commands supported by the server.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``, ``kea-dhcp-ddns``,
``kea-ctrl-agent``

Availability: 1.0.0 (built-in)

Description and examples: see :ref:`command-list-commands`

Command syntax:

::

   {
       "command": "list-commands",
       "arguments": { }
   }

The server will respond with a list of all supported commands.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network4-add:

network4-add reference
======================

``network4-add`` - adds a new shared network.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-add`

Command syntax:

::

   {
       "command": "network4-add",
       "arguments": {
           "shared-networks": [ {
               "name": "floor13",
               "subnet4": [
               {
                   "id": 100,
                   "pools": [ { "pool": "192.0.2.2-192.0.2.99" } ],
                   "subnet": "192.0.2.0/24",
                   "option-data": [
                       {
                           "name": "routers",
                           "data": "192.0.2.1"
                       }
                   ]
               },
               {
                   "id": 101,
                   "pools": [ { "pool": "192.0.3.2-192.0.3.99" } ],
                   "subnet": "192.0.3.0/24",
                   "option-data": [
                       {
                           "name": "routers",
                           "data": "192.0.3.1"
                       }
                   ]
               } ]
           } ]
       }
   }

Response syntax:

::

   {
       "arguments": {
           "shared-networks": [ { "name": "floor13" } ]
       },
       "result": 0,
       "text": "A new IPv4 shared network 'floor13' added"
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network4-del:

network4-del reference
======================

``network4-del`` - deletes existing shared networks.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-del`

Command syntax:

::

   {
       "command": "network4-del",
       "arguments": {
           "name": "floor13"
       }
   }

Response syntax:

::

   {
       "arguments": {
           "shared-networks": [
               {
                   "name": "floor13"
               }
           ]
       },
       "result": 0,
       "text": "IPv4 shared network 'floor13' deleted"
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network4-get:

network4-get reference
======================

``network4-get`` - retrieves detailed
information about shared networks, including subnets currently being
part of a given network.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-get`

Command syntax:

::

   {
       "command": "network4-get",
       "arguments": {
           "name": "floor13"
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "Info about IPv4 shared network 'floor13' returned",
       "arguments": {
           "shared-networks": [
           {
               "match-client-id": true,
               "name": "floor13",
               "option-data": [ ],
               "rebind-timer": 90,
               "relay": {
                   "ip-address": "0.0.0.0"
               },
               "renew-timer": 60,
               "reservation-mode": "all",
               "subnet4": [
                   {
                       "subnet": "192.0.2.0/24",
                       "id": 5,
                       // many other subnet specific details here
                   },
                   {
                       "id": 6,
                       "subnet": "192.0.3.0/31",
                       // many other subnet specific details here
                   }
               ],
               "valid-lifetime": 120
           }
           ]
       }
   }

Note that the actual response contains many additional fields that are
omitted here for clarity.

.. _reference-network4-list:

network4-list reference
=======================

``network4-list`` - retrieves the full list of currently configured shared networks.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-list`

Command syntax:

::

   {
       "command": "network4-list"
   }

Response syntax:

::

   {
       "arguments": {
           "shared-networks": [
               { "name": "floor1" },
               { "name": "office" }
           ]
       },
       "result": 0,
       "text": "2 IPv4 network(s) found"
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network4-subnet-add:

network4-subnet-add reference
=============================

``network4-subnet-add`` - adds existing subnets to existing shared networks.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-subnet-add`

Command syntax:

::

   {
       "command": "network4-subnet-add",
       "arguments": {
           "name": "floor13",
           "id": 5
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now part of shared network 'floor1'"
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network4-subnet-del:

network4-subnet-del reference
=============================

``network4-subnet-del`` - removes a subnet that is part of an existing shared
network and demotes it to a plain, stand-alone subnet.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-subnet-del`

Command syntax:

::

   {
       "command": "network4-subnet-del",
       "arguments": {
           "name": "floor13",
           "id": 5
       }
    }

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now removed from shared network 'floor13'"
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network6-add:

network6-add reference
======================

``network6-add`` - adds a new shared network.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-add`

Command syntax:

::

   {
       "command": "network4-add",
       "arguments": {
           "shared-networks": [ {
               "name": "floor13",
               "subnet4": [
               {
                   "id": 100,
                   "pools": [ { "pool": "192.0.2.2-192.0.2.99" } ],
                   "subnet": "192.0.2.0/24",
                   "option-data": [
                       {
                           "name": "routers",
                           "data": "192.0.2.1"
                       }
                   ]
               },
               {
                   "id": 101,
                   "pools": [ { "pool": "192.0.3.2-192.0.3.99" } ],
                   "subnet": "192.0.3.0/24",
                   "option-data": [
                       {
                           "name": "routers",
                           "data": "192.0.3.1"
                       }
                   ]
               } ]
           } ]
       }
   }

The ``network6-add`` command uses the same syntax for both the query and the
response. However, there are some parameters that are IPv4-only (e.g.
match-client-id) and some that are IPv6-only (e.g. interface-id).

Response syntax:

::

   {
       "arguments": {
           "shared-networks": [ { "name": "floor13" } ]
       },
       "result": 0,
       "text": "A new IPv4 shared network 'floor13' added"
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network6-del:

network6-del reference
======================

``network6-del`` - deletes existing shared networks.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-del`

Command syntax:

::

   {
       "command": "network4-del",
       "arguments": {
           "name": "floor13"
       }
   }

The ``network6-del`` command uses exactly the same syntax as ``network4-del``
for both the command and the response.

Response syntax:

::

   {
       "command": "network4-del",
       "arguments": {
           "name": "floor13",
           "subnets-action": "delete"
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network6-get:

network6-get reference
======================

``network6-get`` - retrieves detailed
information about shared networks, including subnets that are currently
part of a given network.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-get`

Command syntax:

::

   {
       "command": "network4-get",
       "arguments": {
           "name": "floor13"
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "Info about IPv4 shared network 'floor13' returned",
       "arguments": {
           "shared-networks": [
           {
               "match-client-id": true,
               "name": "floor13",
               "option-data": [ ],
               "rebind-timer": 90,
               "relay": {
                   "ip-address": "0.0.0.0"
               },
               "renew-timer": 60,
               "reservation-mode": "all",
               "subnet4": [
                   {
                       "subnet": "192.0.2.0/24",
                       "id": 5,
                       // many other subnet specific details here
                   },
                   {
                       "id": 6,
                       "subnet": "192.0.3.0/31",
                       // many other subnet specific details here
                   }
               ],
               "valid-lifetime": 120
           }
           ]
       }
   }

Note that the actual response contains many additional fields that are
omitted here for clarity.

.. _reference-network6-list:

network6-list reference
=======================

``network6-list`` - retrieves the full list of currently configured shared networks.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-list`

Command syntax:

::

   {
       "command": "network4-list"
   }

The ``network6-list`` command follows exactly the same syntax as ``network4-list`` for
both the query and the response.

Response syntax:

::

   {
       "arguments": {
           "shared-networks": [
               { "name": "floor1" },
               { "name": "office" }
           ]
       },
       "result": 0,
       "text": "2 IPv4 network(s) found"
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network6-subnet-add:

network6-subnet-add reference
=============================

``network6-subnet-add`` - adds existing subnets to existing shared networks.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-subnet-add`

Command syntax:

::

   {
       "command": "network4-subnet-add",
       "arguments": {
           "name": "floor13",
           "id": 5
       }
   }

The ``network6-subnet-add`` command uses exactly the same syntax as
``network4-subnet-add`` for both the command and the response.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now part of shared network 'floor1'"
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-network6-subnet-del:

network6-subnet-del reference
=============================

``network6-subnet-del`` - removes a subnet that is part of an existing shared
network and demotes it to a plain, stand-alone subnet.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-network4-subnet-del`

Command syntax:

::

   {
       "command": "network4-subnet-del",
       "arguments": {
           "name": "floor13",
           "id": 5
       }
    }

The ``network6-subnet-del`` command uses exactly the same syntax as
``network4-subnet-del`` for both the command and the response.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now removed from shared network 'floor13'"
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-global-parameter4-del:

remote-global-parameter4-del reference
======================================

``remote-global-parameter4-del`` - deletes a
global DHCPv4 parameter from the configuration database. The server will
use the value specified in the configuration file or a default value (if
the parameter is not specified in the configuration file) after deleting
the parameter from the database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-global-parameter4-del`

Command syntax:

::

   {
       "command": "remote-global-parameter4-del",
       "arguments": {
           "parameters": [ <parameter name> ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command carries the list including exactly one name of the
parameter to be deleted.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv4 global parameter(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-global-parameter4-get:

remote-global-parameter4-get reference
======================================

``remote-global-parameter4-get`` - fetches the
selected global parameter for the server from the specified database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-global-parameter4-get`

Command syntax:

::

   {
       "command": "remote-global-parameter4-get"
       "arguments": {
           "parameters": [ <parameter name> ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command carries a list including exactly one name of the parameter
to be fetched.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv4 global parameter found.",
       "arguments": {
           "parameters": {
               <parameter name>: <parameter value>,
               "metadata": {
                   "server-tag": <server tag>
               }
           },
           "count": 1
       }
   }

The returned response contains a map with a global parameter name/value
pair. The value may be a JSON string, integer, real, or boolean. The
metadata is included and provides database-specific information
associated with the returned object.

.. _reference-remote-global-parameter4-get-all:

remote-global-parameter4-get-all reference
==========================================

``remote-global-parameter4-get-all`` - fetches all
global parameters for the server from the specified database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-global-parameter4-get-all`

Command syntax:

::

   {
       "command": "remote-global-parameter4-get-all"
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command contains no arguments besides the optional ``remote``.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv4 global parameters found.",
       "arguments": {
           "parameters": [
               {
                   <first parameter name>: <first parameter value>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   <second parameter name>: <second parameter value>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains a list of maps. Each map contains a
global parameter name/value pair. The value may be a JSON string,
integer, real, or boolean. The metadata is appended to each parameter and
provides database-specific information associated with the returned
objects.

.. _reference-remote-global-parameter4-set:

remote-global-parameter4-set reference
======================================

``remote-global-parameter4-set`` - creates or
updates one or more global parameters in the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-global-parameter4-set`

Command syntax:

::

   {
       "command": "remote-global-parameter4-set"
       "arguments": {
           "parameters": {
               <first parameter name>: <first parameter value>,
               <second parameter name>: <second parameter value>
           },
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command carries multiple global parameters with their values. Care
should be taken when specifying more than one parameter, because in some
cases only a subset of the parameters may be successfully stored in the
database and other parameters may fail to be stored. In such cases the
``remote-global-parameter4-get-all`` command may be useful to verify the
contents of the database after the update.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv4 global parameter(s) successfully set."
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-global-parameter6-del:

remote-global-parameter6-del reference
======================================

``remote-global-parameter6-del`` - deletes a
global DHCPv6 parameter from the configuration database. The server will
use the value specified in the configuration file or a default value (if
the parameter is not specified in the configuration file) after deleting
the parameter from the database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-global-parameter4-del`

Command syntax:

::

   {
       "command": "remote-global-parameter6-del",
       "arguments": {
           "parameters": [ <parameter name> ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command carries the list including exactly one name of the
parameter to be deleted.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv6 global parameter(s) deleted.",
       "arguments": {
           "count": 1
       }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-global-parameter6-get:

remote-global-parameter6-get reference
======================================

``remote-global-parameter6-get`` - fetches the
selected global parameter for the server from the specified database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-global-parameter4-get`

Command syntax:

::

   {
       "command": "remote-global-parameter6-get"
       "arguments": {
           "parameters": [ <parameter name> ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command carries a list including exactly one name of the parameter
to be fetched.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv6 global parameter found.",
       "arguments": {
           "parameters": {
               <parameter name>: <parameter value>,
               "metadata": {
                   "server-tag": <server tag>
               }
           },
           "count": 1
       }
   }

The returned response contains a map with a global parameter name/value
pair. The value may be a JSON string, integer, real, or boolean. The
metadata is included and provides database-specific information
associated with the returned object.

.. _reference-remote-global-parameter6-get-all:

remote-global-parameter6-get-all reference
==========================================

``remote-global-parameter6-get-all`` - fetches all
global parameters for the server from the specified database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-global-parameter4-get-all`

Command syntax:

::

   {
       "command": "remote-global-parameter6-get-all"
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command contains no arguments besides the optional ``remote``.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv6 global parameters found.",
       "arguments": {
           "parameters": [
               {
                   <first parameter name>: <first parameter value>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   <second parameter name>: <second parameter value>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains a list of maps. Each map contains a
global parameter name/value pair. The value may be a JSON string,
integer, real, or boolean. The metadata is appended to each parameter and
provides database-specific information associated with the returned
objects.

.. _reference-remote-global-parameter6-set:

remote-global-parameter6-set reference
======================================

``remote-global-parameter6-set`` - creates or
updates one or more global DHCP parameters in the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-global-parameter4-set`

Command syntax:

::

   {
       "command": "remote-global-parameter6-set"
       "arguments": {
           "parameters": {
               <first parameter name>: <first parameter value>,
               <second parameter name>: <second parameter value>
           },
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command carries multiple global parameters with their values. Care
should be taken when specifying more than one parameter, because in some
cases only a subset of the parameters may be successfully stored in the
database and other parameters may fail to be stored. In such cases the
``remote-global-parameter6-get-all`` command may be useful to verify the
contents of the database after the update.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv6 global parameter(s) successfully set."
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-network4-del:

remote-network4-del reference
=============================

``remote-network4-del`` - deletes an IPv4 shared
network from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-network4-del`

Command syntax:

::

   {
       "command": "remote-network4-del",
       "arguments": {
           "shared-networks": [
               {
                   "name": <shared network name>
               }
           ],
           "subnets-action": "keep" | "delete",
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one name of the shared network
to be deleted. The ``subnets-action`` command denotes whether the subnets in
this shared network should be deleted or not.

Response syntax:

::

   {
       "result": 0,
       "text": "1 IPv4 shared network(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-network4-get:

remote-network4-get reference
=============================

``remote-network4-get`` - fetches the selected IPv4
shared network for the server from the specified database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-network4-get`

Command syntax:

::

   {
       "command": "remote-network4-get"
       "arguments": {
           "shared-networks": [
               {
                   "name": <shared network name>
               }
           ],
           "subnets-include": "full" | "no",
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one name of the shared network
to be returned. The ``subnets-include`` optional parameter
specifies whether the subnets belonging to the shared network should
also be returned.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 shared network found.",
       "arguments": {
           "shared-networks": [
               {
                   "name": <shared network name>,
                   "metadata": {
                       "server-tag": <server tag>
                   },
                   <the rest of the shared network information, potentially including subnets>
               }
           ],
           "count": 1
       }
   }

If the subnets are returned with the shared network they are carried in
the ``subnet4`` list within the shared network definition. The metadata
is included in the returned shared network definition and provides
the database-specific information associated with the returned object.

.. _reference-remote-network4-list:

remote-network4-list reference
==============================

``remote-network4-list`` - fetches a list of all
IPv4 shared networks from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-network4-list`

Command syntax:

::

   {
       "command": "remote-network4-list"
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command contains no arguments besides the optional ``remote``.

Response syntax:

::

   {
       "result": 0,
       "text": "2 IPv4 shared network(s) found.",
       "arguments": {
           "shared-networks": [
               {
                   "name": <first shared network name>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   "name": <second shared network name>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains the list of maps. Each map contains the
shared network name and the metadata, which provides database-specific
information associated with the shared network. The returned list does
not contain full definitions of the shared networks; use
``remote-network4-get`` to fetch the complete information about the selected
shared networks.

.. _reference-remote-network4-set:

remote-network4-set reference
=============================

``remote-network4-set`` - creates or replaces an
IPv4 shared network in the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-network4-set`

Command syntax:

::

   {
       "command": "remote-network4-set",
       "arguments": {
           "shared-networks": [
               {
                   <shared network specification excluding subnets list>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The provided list must contain exactly one shared network specification.
It must not contain subnets ("subnet4" parameter); the subnets are added
to the shared network using the ``remote-subnet4-set`` command.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 shared network successfully set."
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-network6-del:

remote-network6-del reference
=============================

``remote-network6-del`` - deletes an IPv6 shared
network from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-network4-del`

Command syntax:

::

   {
       "command": "remote-network6-del",
       "arguments": {
           "shared-networks": [
               {
                   "name": <shared network name>
               }
           ],
           "subnets-action": "keep" | "delete",
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one name of the shared network
to be deleted. The ``subnets-action`` command denotes whether the subnets in
this shared network should be deleted or not.

Response syntax:

::

   {
       "result": 0,
       "text": "1 IPv6 shared network(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-network6-get:

remote-network6-get reference
=============================

``remote-network6-get`` - fetches the selected IPv6
shared network for the server from the specified database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-network4-get`

Command syntax:

::

   {
       "command": "remote-network6-get"
       "arguments": {
           "shared-networks": [
               {
                   "name": <shared network name>
               }
           ],
           "subnets-include": "full" | "no",
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one name of the shared network
to be returned. The ``subnets-include`` optional parameter
specifies whether the subnets belonging to the shared network should
also be returned.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv6 shared network found.",
       "arguments": {
           "shared-networks": [
               {
                   "name": <shared network name>,
                   "metadata": {
                       "server-tag": <server tag>
                   },
                   <the rest of the shared network information, potentially including subnets>
               }
           ],
           "count": 1
       }
   }

If the subnets are returned with the shared network, they are carried in
the ``subnet6`` list within the shared network definition. The metadata
is included in the returned shared network definition and provides
the database-specific information associated with the returned object.

.. _reference-remote-network6-list:

remote-network6-list reference
==============================

``remote-network6-list`` - fetches a list of all
IPv6 shared networks from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-network4-list`

Command syntax:

::

   {
       "command": "remote-network6-list"
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command contains no arguments besides the optional ``remote``.

Response syntax:

::

   {
       "result": 0,
       "text": "2 IPv6 shared network(s) found.",
       "arguments": {
           "shared-networks": [
               {
                   "name": <first shared network name>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   "name": <second shared network name>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains the list of maps. Each map contains the
shared network name and the metadata, which provides database-specific
information associated with the shared network. The returned list does
not contain full definitions of the shared networks; use
``remote-network6-get`` to fetch the complete information about the selected
shared networks.

.. _reference-remote-network6-set:

remote-network6-set reference
=============================

``remote-network6-set`` - creates or replaces an
IPv6 shared network in the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-network4-set`

Command syntax:

::

   {
       "command": "remote-network6-set",
       "arguments": {
           "shared-networks": [
               {
                   <shared network specification excluding subnets list>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The provided list must contain exactly one shared network specification.
It must not contain subnets ("subnet6" parameter); the subnets are added
to the shared network using the ``remote-subnet6-set`` command.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv6 shared network successfully set."
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-option-def4-del:

remote-option-def4-del reference
================================

``remote-option-def4-del`` - deletes a DHCPv4
option definition from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option-def4-del`

Command syntax:

::

   {
       "command": "remote-option-def4-del",
       "arguments": {
           "option-defs": [ {
               "code": <option code>,
               "space": <option space
           } ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one option definition
specification comprising an option name and code.

Response syntax:

::

   {
       "result": 0,
       "text": "1 DHCPv4 option definition(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-option-def4-get:

remote-option-def4-get reference
================================

``remote-option-def4-get`` - fetches a DHCPv4
option definition from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option-def4-get`

Command syntax:

::

   {
       "command": "remote-option-def4-get",
       "arguments": {
           "option-defs": [
               {
                   "code": <option code>,
                   "space": <option space>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The desired option definition is identified by the pair of option
code/space values.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv4 option definition found.",
       "arguments": {
           "option-defs": [
               {
                   <option definition>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 1
       }
   }

The metadata is included and provides database-specific information
associated with the returned object.

.. _reference-remote-option-def4-get-all:

remote-option-def4-get-all reference
====================================

``remote-option-def4-get-all`` - fetches all
DHCPv4 option definitions from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option-def4-get-all`

Command syntax:

::

   {
       "command": "remote-option-def4-get-all"
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command contains no arguments besides the optional ``remote``.

Response syntax:

::

   {
       "result": 0,
       "text": "2 DHCPv4 option definition(s) found.",
       "arguments": {
           "option-defs": [
               {
                   <first option definition>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   <second option definition>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains a list of maps. Each map contains an
option definition specification and the metadata, including
database-specific information associated with the returned objects.

.. _reference-remote-option-def4-set:

remote-option-def4-set reference
================================

``remote-option-def4-set`` - creates or replaces a
DHCPv4 option definition in the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option-def4-set`

Command syntax:

::

   {
       "command": "remote-option-def4-set",
       "arguments": {
           "option-defs": [
               {
                   <option definition specification>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The provided list must contain exactly one option definition
specification.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv4 option definition set."
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-option-def6-del:

remote-option-def6-del reference
================================

``remote-option-def6-del`` - deletes a DHCPv6
option definition from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option-def4-del`

Command syntax:

::

   {
       "command": "remote-option-def6-del",
       "arguments": {
           "option-defs": [
               {
                   "code": <option code>,
                   "space": <option space>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one option definition
specification comprising an option name and code.

Response syntax:

::

   {
       "result": 0,
       "text": "1 DHCPv6 option definition(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-option-def6-get:

remote-option-def6-get reference
================================

``remote-option-def6-get`` - fetches a DHCPv6
option definition from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option-def4-get`

Command syntax:

::

   {
       "command": "remote-option-def6-get",
       "arguments": {
           "option-defs": [
               {
                   "code": <option code>,
                   "space": <option space>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The desired option definition is identified by the pair of the option
code/space values.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv6 option definition found.",
       "arguments": {
           "option-defs": [
               {
                   <option definition>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 1
       }
   }

The metadata is included and provides database-specific information
associated with the returned object.

.. _reference-remote-option-def6-get-all:

remote-option-def6-get-all reference
====================================

``remote-option-def6-get-all`` - fetches all
DHCPv6 option definitions from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option-def4-get-all`

Command syntax:

::

   {
       "command": "remote-option-def6-get-all"
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command contains no arguments besides the optional ``remote``.

Response syntax:

::

   {
       "result": 0,
       "text": "2 DHCPv6 option definition(s) found.",
       "arguments": {
           "option-defs": [
               {
                   <first option definition>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   <second option definition>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains a list of maps. Each map contains an
option definition specification and the metadata, including
database-specific information associated with the returned objects.

.. _reference-remote-option-def6-set:

remote-option-def6-set reference
================================

``remote-option-def6-set`` - creates or replaces a
DHCPv6 option definition in the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option-def4-set`

Command syntax:

::

   {
       "command": "remote-option-def6-set",
       "arguments": {
           "option-defs": [
               {
                   <option definition specification>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The provided list must contain exactly one option definition
specification.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv6 option definition set."
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-option4-global-del:

remote-option4-global-del reference
===================================

``remote-option4-global-del`` - deletes a DHCPv4
global option from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option4-global-del`

Command syntax:

::

   {
       "command": "remote-option4-global-del",
       "arguments": {
           "options": [
               {
                   "code": <option code>
                   "space": <option space>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one option specification
comprising an option name and code.

Response syntax:

::

   {
       "result": 0,
       "text": "1 DHCPv4 option(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-option4-global-get:

remote-option4-global-get reference
===================================

``remote-option4-global-get`` - fetches a global
DHCPv4 option for the server from the specified database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option4-global-get`

Command syntax:

::

   {
       "command": "remote-option4-global-get",
       "arguments": {
           "options": [
               {
                   "code": <option code>,
                   "space": <option space>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
   }

The option is identified by the pair of option code/space values.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv4 option in found.",
       "arguments": {
           "options": [
               {
                   <option information>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ]
       }
   }

The metadata is included and provides database-specific information
associated with the returned object.

.. _reference-remote-option4-global-get-all:

remote-option4-global-get-all reference
=======================================

``remote-option4-global-get-all`` - fetches all
DHCPv4 global options for the server from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option4-global-get-all`

Command syntax:

::

   {
       "command": "remote-option4-global-get-all",
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command takes no arguments besides the optional ``remote`` map.

Response syntax:

::

   {
       "result": 0,
       "text": "2 DHCPv4 option(s) found.",
       "arguments": {
           "options": [
               {
                   <first option specification>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   <second option specification>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains a list of maps. Each map contains a
global option specification and the metadata, including database-specific
information associated with the returned object.

.. _reference-remote-option4-global-set:

remote-option4-global-set reference
===================================

``remote-option4-global-set`` - creates or
replaces a DHCPv4 global option in the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option4-global-set`

Command syntax:

::

   {
       "command": "remote-option4-global-set",
       "arguments": {
           "options": [
               {
                   <global option specification>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The provided list must contain exactly one option specification.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv4 option set.",
       "arguments": {
           "options": [
               {
                   "code": <option code>,
                   "space": <option space>
               }
           ]
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-option6-global-del:

remote-option6-global-del reference
===================================

``remote-option6-global-del`` - deletes a DHCPv6
global option from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option4-global-del`

Command syntax:

::

   {
       "command": "remote-option6-global-del",
       "arguments": {
           "options": [
               {
                   "code": <option code>
                   "space": <option space>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one option specification
comprising an option name and code.

Response syntax:

::

   {
       "result": 0,
       "text": "1 DHCPv6 option(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-option6-global-get:

remote-option6-global-get reference
===================================

``remote-option6-global-get`` - deletes a DHCPv6
global option from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option4-global-get`

Command syntax:

::

   {
       "command": "remote-option6-global-get",
       "arguments": {
           "options": [
               {
                   "code": <option code>,
                   "space": <option space>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
   }

The option is identified by the pair of option code/space values.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv6 option found.",
       "arguments": {
           "options": [
               {
                   <option information>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ]
       }
   }

The metadata is included and provides database-specific information
associated with the returned object.

.. _reference-remote-option6-global-get-all:

remote-option6-global-get-all reference
=======================================

``remote-option6-global-get-all`` - fetches all
DHCPv6 global options for the server from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option4-global-get-all`

Command syntax:

::

   {
       "command": "remote-option6-global-get-all",
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command takes no arguments besides the optional ``remote`` map.

Response syntax:

::

   {
       "result": 0,
       "text": "2 DHCPv6 option(s) found.",
       "arguments": {
           "options": [
               {
                   <first option specification>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   <second option specification>,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains a list of maps. Each map contains a
global option specification and the metadata, including database-specific
information associated with the returned object.

.. _reference-remote-option6-global-set:

remote-option6-global-set reference
===================================

``remote-option6-global-set`` - creates or
replaces a DHCPv6 global option in the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-option4-global-set`

Command syntax:

::

   {
       "command": "remote-option6-global-set",
       "arguments": {
           "options": [
               {
                   <global option specification>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The provided list must contain exactly one option specification.

Response syntax:

::

   {
       "result": 0,
       "text": "DHCPv6 option set.",
       "arguments": {
           "options": [
               {
                   "code": <option code>,
                   "space": <option space>
               }
           ]
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-subnet4-del-by-id:

remote-subnet4-del-by-id reference
==================================

``remote-subnet4-del-by-id`` - deletes an IPv4
subnet by ID from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-del-by-id`

Command syntax:

::

   {
       "command": "remote-subnet4-del-by-id",
       "arguments": {
           "subnets": [
               {
                   "id": <subnet identifier>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one ID of the subnet to be
deleted.

Response syntax:

::

   {
       "result": 0,
       "text": "1 IPv4 subnet(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-subnet4-del-by-prefix:

remote-subnet4-del-by-prefix reference
======================================

``remote-subnet4-del-by-prefix`` - deletes an
IPv4 subnet by prefix from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-del-by-prefix`

Command syntax:

::

   {
       "command": "remote-subnet4-del-by-prefix",
       "arguments": {
           "subnets": [
               {
                   "subnet": <subnet prefix>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one prefix of the subnet to be
deleted.

Response syntax:

::

   {
       "result": 0,
       "text": "1 IPv4 subnet(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-subnet4-get-by-id:

remote-subnet4-get-by-id reference
==================================

``remote-subnet4-get-by-id`` - fetches a selected
IPv4 subnet by ID for the server from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-get-by-id`

Command syntax:

::

   {
       "command": "remote-subnet4-get-by-id"
       "arguments": {
           "subnets": [ {
               "id": <subnet identifier>
           } ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one ID of the subnet to be
returned.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet found.",
       "arguments": {
           "subnets": [ {
               "id": <subnet identifier>
               "subnet": <subnet prefix>,
               "shared-network-name": <shared network name> | null,
               "metadata": {
                   "server-tag": <server tag>
               },
               <the rest of the subnet specification here>
           } ],
           "count": 1
       }
   }

If the shared network name is null, it means that the returned subnet
does not belong to any shared network (global subnet). The metadata is
included in the returned subnet definition and provides
database-specific information associated with the returned object.

.. _reference-remote-subnet4-get-by-prefix:

remote-subnet4-get-by-prefix reference
======================================

``remote-subnet4-get-by-prefix`` - fetches a
selected IPv4 subnet by prefix from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-get-by-prefix`

Command syntax:

::

   {
       "command": "remote-subnet4-get-by-prefix"
       "arguments": {
           "subnets": [ {
               "subnet": <subnet prefix>
           } ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one prefix of the subnet to be
returned.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet found.",
       "arguments": {
           "subnets": [
               {
                   "id": <subnet identifier>
                   "subnet": <subnet prefix>,
                   "shared-network-name": <shared network name> | null,
                   "metadata": {
                       "server-tag": <server tag>
                   },
                   <the rest of the subnet specification here>
               }
           ],
           "count": 1
       }
   }

If the shared network name is null, it means that the returned subnet
does not belong to any shared network (global subnet). The metadata is
included in the returned subnet definition and provides
database-specific information associated with the returned object.

.. _reference-remote-subnet4-list:

remote-subnet4-list reference
=============================

``remote-subnet4-list`` - fetches a list of all
IPv4 subnets from the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-list`

Command syntax:

::

   {
       "command": "remote-subnet4-list"
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes no arguments besides the optional ``remote`` map.

Response syntax:

::

   {
       "result": 0,
       "text": "2 IPv4 subnets found.",
       "arguments": {
           "subnets": [
               {
                   "id": <first subnet identifier>,
                   "subnet": <first subnet prefix>,
                   "shared-network-name": <shared network name> | null,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   "id": <second subnet identifier>,
                   "subnet": <second subnet prefix>,
                   "shared-network-name": <shared network name> | null,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains a list of maps. Each map contains a
subnet identifier, prefix, and shared network name to which the subnet
belongs. If the subnet does not belong to a shared network, the name is
null. The metadata includes database-specific information associated
with the subnets. The returned list does not contain full subnet
definitions; use ``remote-subnet4-get`` to fetch the complete information
about the selected subnets.

.. _reference-remote-subnet4-set:

remote-subnet4-set reference
============================

``remote-subnet4-set`` - creates or replaces an
IPv4 subnet in the configuration database.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-set`

Command syntax:

::

   {
       "command": "remote-subnet4-set",
       "arguments": {
           "subnets": [
               {
                   "id": <subnet identifier>,
                   "subnet": <subnet prefix>,
                   "shared-network-name": <shared network name> | null,
                   <the rest of the subnet specification here>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The provided list must contain exactly one subnet specification. The
``shared-network-name`` parameter is required for these commands; it
associates the subnet with the shared network by its name. If the subnet
must not belong to any shared network (global subnet), the ``null``
value must be specified for the shared network name.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet successfully set.",
       "arguments": {
           "id": <subnet identifier>,
           "subnet": <subnet prefix>
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-subnet6-del-by-id:

remote-subnet6-del-by-id reference
==================================

``remote-subnet6-del-by-id`` - deletes an IPv6
subnet by ID from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-del-by-id`

Command syntax:

::

   {
       "command": "remote-subnet6-del-by-id",
       "arguments": {
           "subnets": [
               {
                   "id": <subnet identifier>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one ID of the subnet to be
deleted.

Response syntax:

::

   {
       "result": 0,
       "text": "1 IPv6 subnet(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-subnet6-del-by-prefix:

remote-subnet6-del-by-prefix reference
======================================

``remote-subnet6-del-by-prefix`` - deletes an
IPv6 subnet by prefix from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-del-by-prefix`

Command syntax:

::

   {
       "command": "remote-subnet6-del-by-prefix",
       "arguments": {
           "subnets": [
               {
                   "subnet": <subnet prefix>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one prefix of the subnet to be
deleted.

Response syntax:

::

   {
       "result": 0,
       "text": "1 IPv6 subnet(s) deleted.",
       "arguments": {
           "count": 1
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-remote-subnet6-get-by-id:

remote-subnet6-get-by-id reference
==================================

``remote-subnet6-get-by-id`` - fetches a selected
IPv6 subnet by ID for the server from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-get-by-id`

Command syntax:

::

   {
       "command": "remote-subnet6-get-by-id"
       "arguments": {
           "subnets": [
               {
                   "id": <subnet identifier>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one ID of the subnet to be
returned.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv6 subnet found.",
       "arguments": {
           "subnets": [
               {
                   "id": <subnet identifier>
                   "subnet": <subnet prefix>,
                   "shared-network-name": <shared network name> | null,
                   "metadata": {
                       "server-tag": <server tag>
                   },
                   <the rest of the subnet specification here>
               }
           ],
           "count": 1
       }
   }

If the shared network name is null, it means that the returned subnet
does not belong to any shared network (global subnet). The metadata is
included in the returned subnet definition and provides
database-specific information associated with the returned object.

.. _reference-remote-subnet6-get-by-prefix:

remote-subnet6-get-by-prefix reference
======================================

``remote-subnet6-get-by-prefix`` - fetches a
selected IPv6 subnet by prefix from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-get-by-prefix`

Command syntax:

::

   {
       "command": "remote-subnet4-get-by-prefix"
       "arguments": {
           "subnets": [
               {
                   "subnet": <subnet prefix>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes a list with exactly one prefix of the subnet to be
returned.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv6 subnet found.",
       "arguments": {
           "subnets": [ {
               "id": <subnet identifier>
               "subnet": <subnet prefix>,
               "shared-network-name": <shared network name> | null,
               "metadata": {
                   "server-tag": <server tag>
               },
               <the rest of the subnet specification here>
           } ],
           "count": 1
       }
   }

If the shared network name is null, it means that the returned subnet
does not belong to any shared network (global subnet). The metadata is
included in the returned subnet definition and provides
database-specific information associated with the returned object.

.. _reference-remote-subnet6-list:

remote-subnet6-list reference
=============================

``remote-subnet6-list`` - fetches a list of all
IPv6 subnets from the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-list`

Command syntax:

::

   {
       "command": "remote-subnet6-list"
       "arguments": {
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

This command includes no arguments besides the optional ``remote`` map.

Response syntax:

::

   {
       "result": 0,
       "text": "2 IPv6 subnets found.",
       "arguments": {
           "subnets": [
               {
                   "id": <first subnet identifier>,
                   "subnet": <first subnet prefix>,
                   "shared-network-name": <shared network name> | null,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               },
               {
                   "id": <second subnet identifier>,
                   "subnet": <second subnet prefix>,
                   "shared-network-name": <shared network name> | null,
                   "metadata": {
                       "server-tag": <server tag>
                   }
               }
           ],
           "count": 2
       }
   }

The returned response contains a list of maps. Each map contains a
subnet identifier, prefix, and shared network name to which the subnet
belongs. If the subnet does not belong to a shared network, the name is
null. The metadata includes database-specific information associated
with the subnets. The returned list does not contain full subnet
definitions; use ``remote-subnet6-get`` to fetch the complete information
about the selected subnets.

.. _reference-remote-subnet6-set:

remote-subnet6-set reference
============================

``remote-subnet6-set`` - creates or replaces an
IPv4 subnet in the configuration database.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Configuration Backend Commands hooks library<commands-cb_cmds-lib>`)

Description and examples: see :ref:`command-remote-subnet4-set`

Command syntax:

::

   {
       "command": "remote-subnet6-set",
       "arguments": {
           "subnets": [
               {
                   "id": <subnet identifier>,
                   "subnet": <subnet prefix>,
                   "shared-network-name": <shared network name> | null,
                   <the rest of the subnet specification here>
               }
           ],
           "remote": {
               <specification of the database to connect to>
           }
       }
   }

The provided list must contain exactly one subnet specification. The
``shared-network-name`` parameter is required for these commands; it
associates the subnet with the shared network by its name. If the subnet
must not belong to any shared network (global subnet), the ``null``
value must be specified for the shared network name.

Response syntax:

::

   {
       "result": 0,
       "text": "IPv6 subnet successfully set.",
       "arguments": {
           "id": <subnet identifier>,
           "subnet": <subnet prefix>
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-reservation-add:

reservation-add reference
=========================

``reservation-add`` - adds a new host reservation. The reservation may
include an IPv4 address, IPv6 addresses, IPv6 prefixes, various
identifiers, a class the client will be assigned to, DHCPv4 and DHCPv6
options, and more.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.2.0 (:ref:`The Host Commands hooks library<commands-host_cmds-lib>`)

Description and examples: see :ref:`command-reservation-add`

Command syntax:

::

   {
       "command": "reservation-add",
       "arguments": {
           "reservation": {
               "boot-file-name": <string>,
               "comment": <string>
               "client-id": <string>,
               "circuit-id": <string>,
               "duid": <string>,
               "flex-id": <string>,
               "ip-address": <string (IPv4 address)>,
               "ip-addresses": [ <comma-separated strings> ],
               "hw-address": <string>,
               "hostname": <string>,
               "next-server": <string (IPv4 address)>,
               "option-data-list": [ <comma-separated structures defining options> ],
               "prefixes": [ <comma-separated IPv6 prefixes> ],
               "reservation-client-classes": [ <comma-separated strings> ],
               "server-hostname": <string>,
               "subnet-id": <integer>,
               "user-context": <any valid JSON>,
           }
       }
   }

Note that ip-address, client-id, next-server, server-hostname, and
boot-file-name are IPv4-specific. duid, ip-addresses, and prefixes are
IPv6-specific.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-reservation-del:

reservation-del reference
=========================

``reservation-del`` - deletes an existing host reservation.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.2.0 (:ref:`The Host Commands hooks library<commands-host_cmds-lib>`)

Description and examples: see :ref:`command-reservation-del`

Command syntax:

::

   {
       "command": "reservation-del",
       "arguments": {
           "subnet-id": <integer>,
           "ip-address": <string>,
           "identifier-type": <one of "hw-address", "duid", "circuit-id", "client-id" and "flex-id">,
           "identifier": <string>
       }
   }

The host reservation can be identified by either the (subnet-id, ip-address)
pair or a triplet of (subnet-id, identifier-type, identifier).

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-reservation-get:

reservation-get reference
=========================

``reservation-get`` - attempts to retrieve an existing host reservation.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.2.0 (:ref:`The Host Commands hooks library<commands-host_cmds-lib>`)

Description and examples: see :ref:`command-reservation-get`

Command syntax:

::

   {
       "command": "reservation-get",
       "arguments": {
           "subnet-id": <integer>,
           "identifier-type": <string with one value out of: hw-address|duid|circuit-id|client-id|flex-id>,
           "identifier": <string>;
       }
   }

The host reservation can be identified by either a (subnet-id, ip-address)
pair or a triplet of (subnet-id, identifier-type, identifier).

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>,
       "arguments": {
           "boot-file-name": <string>,
           "comment": <string>
           "client-id": <string>,
           "circuit-id": <string>,
           "duid": <string>,
           "flex-id": <string>,
           "ip-address": <string (IPv4 address)>,
           "ip-addresses": [ <comma-separated strings> ],
           "hw-address": <string>,
           "hostname": <string>,
           "next-server": <string (IPv4 address)>,
           "option-data-list": [ <comma-separated structures defining options> ],
           "prefixes": [ <comma-separated IPv6 prefixes> ],
           "reservation-client-classes": [ <comma-separated strings> ],
           "server-hostname": <string>,
           "subnet-id": <integer>,
           "user-context": <any valid JSON>,
       }
   }

The arguments object appears only if a host is found. Many fields in the
arguments object appear only if a specific field is set.

.. _reference-reservation-get-all:

reservation-get-all reference
=============================

``reservation-get-all`` - retrieves all host reservations for a specified
subnet.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Host Commands hooks library<commands-host_cmds-lib>`)

Description and examples: see :ref:`command-reservation-get-all`

Command syntax:

::

   {
       "command": "reservation-get-all",
       "arguments": {
           "subnet-id": <integer>
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The ``reservation-get-all`` command may result in very large responses.

.. _reference-reservation-get-page:

reservation-get-page reference
==============================

``reservation-get-page`` - retrieves host reservations for a specified
subnet by page.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Host Commands hooks library<commands-host_cmds-lib>`)

Description and examples: see :ref:`command-reservation-get-page`

Command syntax:

::

   {
       "command": "reservation-get-page",
       "arguments": {
           "subnet-id": <integer>,
           "limit": <integer>,
           "source-index": <integer>,
           "from": <integer>
       }
   }

The "subnet-id" and the "limit" arguments are mandatory. The "limit"
specifies the maximum number of host reservations to be returned, and
the "source-index" and "from" arguments should be set to 0 when retrieving
the first page of host reservations (if they are not specified, they will
default to 0). To fetch subsequent pages of host reservations, the returned
values of "source-index" and "from" must be copied from the previous response.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-shutdown:

shutdown reference
==================

``shutdown`` - instructs the server to initiate its
shutdown procedure.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``, ``kea-dhcp-ddns``,
``kea-ctrl-agent``

Availability: 1.0.0 (built-in)

Description and examples: see :ref:`command-shutdown`

Command syntax:

::

   {
       "command": "shutdown"
   }

The server will respond with a confirmation that the shutdown procedure
has been initiated.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-stat-lease4-get:

stat-lease4-get reference
=========================

``stat-lease4-get`` - fetches lease
statistics for a range of known IPv4 subnets.

Supported by: ``kea-dhcp4``

Availability: 1.4.0 (:ref:`The Supplemental Statistics Commands hooks library<commands-stat_cmds-lib>`)

Description and examples: see :ref:`command-stat-lease4-get`

Command syntax:

::

   {
     "command": "stat-lease4-get"
   }

Response syntax:

::

   {
       "result": 0,
       "text": "stat-lease4-get: 2 rows found",
       "arguments": {
         "result-set": {
           "columns": [ "subnet-id",
                          "total-addresses",
                          "assigned-addresses",
                          "declined-addresses" ]
           "rows": [
             [ 10, 256, 111, 0 ],
             [ 20, 4098, 2034, 4 ]
           ],
         "timestamp": "2018-05-04 15:03:37.000000"
         }
       }
     }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-stat-lease6-get:

stat-lease6-get reference
=========================

``stat-lease6-get`` - fetches lease
statistics for a range of known IPv6 subnets.

Supported by: ``kea-dhcp6``

Availability: 1.4.0 (:ref:`The Supplemental Statistics Commands hooks library<commands-stat_cmds-lib>`)

Description and examples: see :ref:`command-stat-lease4-get`

Command syntax:

::

   {
     "command": "stat-lease6-get",
     "arguments": {
       "subnet-id" : 10
     }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "stat-lease6-get: 2 rows found",
       "arguments": {
         "result-set": {
           "columns": [ "subnet-id", "total-nas", "assigned-nas", "declined-nas", "total-pds", "assigned-pds" ]
           "rows": [
             [ 10, 4096, 2400, 3, 0, 0],
             [ 20, 0, 0, 0, 1048, 233 ]
             [ 30, 256, 60, 0, 1048, 15 ]
           ],
         "timestamp": "2018-05-04 15:03:37.000000"
         }
       }
     }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-statistic-get:

statistic-get reference
=======================

``statistic-get`` - retrieves a single
statistic. It takes a single string parameter, called "name", that specifies
the statistic name.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.0.0 (built-in)

Description and examples: see :ref:`command-statistic-get`

Command syntax:

::

   {
       "command": "statistic-get",
       "arguments": {
           "name": "pkt4-received"
       }
   }

The server will respond with details of the requested statistic, with a
result set to 0 indicating success and the specified statistic as the
value of the "arguments" parameter.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-statistic-get-all:

statistic-get-all reference
===========================

``statistic-get-all`` - retrieves all statistics recorded.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.0.0 (built-in)

Description and examples: see :ref:`command-statistic-get-all`

Command syntax:

::

   {
       "command": "statistic-get-all",
       "arguments": { }
   }

The server will respond with details of all recorded statistics, with a
result of 0 indicating that it iterated over all statistics (even
when the total number of statistics is zero).

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-statistic-remove:

statistic-remove reference
==========================

``statistic-remove`` - attempts to delete a
single statistic. It takes a single string parameter, called "name", that
specifies the statistic name.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.0.0 (built-in)

Description and examples: see :ref:`command-statistic-remove`

Command syntax:

::

   {
       "command": "statistic-remove",
       "arguments": {
           "name": "pkt4-received"
       }
   }

If the specific statistic is found and its removal was successful, the
server will respond with a status of 0, indicating success, and an empty
parameters field. If an error is encountered (e.g. the requested statistic
was not found), the server will return a status code of 1 (error) and
the text field will contain the error description.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-statistic-remove-all:

statistic-remove-all reference
==============================

``statistic-remove-all`` - attempts to
delete all statistics.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.0.0 (built-in)

Description and examples: see :ref:`command-statistic-remove-all`

Command syntax:

::

   {
       "command": "statistic-remove-all",
       "arguments": { }
   }

If the removal of all statistics was successful, the server will respond
with a status of 0, indicating success, and an empty parameters field. If
an error is encountered, the server will return a status code of 1
(error) and the text field will contain the error description.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-statistic-reset:

statistic-reset reference
=========================

``statistic-reset`` - sets the specified
statistic to its neutral value: 0 for integer, 0.0 for float, 0h0m0s0us
for time duration, and "" for string type. It takes a single string
parameter, called "name", that specifies the statistic name.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.0.0 (built-in)

Description and examples: see :ref:`command-statistic-reset`

Command syntax:

::

   {
       "command": "statistic-reset",
       "arguments": {
           "name": "pkt4-received"
       }
   }

If the specific statistic is found and the reset was successful, the server
will respond with a status of 0, indicating success, and an empty
parameters field. If an error is encountered (e.g. the requested statistic
was not found), the server will return a status code of 1 (error) and
the text field will contain the error description.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-statistic-reset-all:

statistic-reset-all reference
=============================

``statistic-reset-all`` - sets all
statistics to their neutral values: 0 for integer, 0.0 for float,
0h0m0s0us for time duration, and "" for string type.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``

Availability: 1.0.0 (built-in)

Description and examples: see :ref:`command-statistic-reset-all`

Command syntax:

::

   {
       "command": "statistic-reset-all",
       "arguments": { }
   }

If the operation is successful, the server will respond with a status of
0, indicating success, and an empty parameters field. If an error is
encountered, the server will return a status code of 1 (error) and the
text field will contain the error description.

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-subnet4-add:

subnet4-add reference
=====================

``subnet4-add`` - creates and adds a new subnet to
the existing server configuration.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet4-add`

Command syntax:

::

   {
       "command": "subnet4-add",
       "arguments": {
           "subnets": [ {
               "id": 123,
               "subnet": "10.20.30.0/24",
               ...
           } ]
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet added",
       "arguments": {
           "subnets": [
               {
                   "id": 123,
                   "subnet": "10.20.30.0/24"
               }
           ]
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-subnet4-del:

subnet4-del reference
=====================

``subnet4-del`` - removes a subnet from the
server's configuration. This command has no effect on other configured
subnets, but administrators should exercise caution when
using this command as removing a subnet may have unintended consequences.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet4-del`

Command syntax:

::

   {
       "command": "subnet4-del",
       "arguments": {
           "id": 123
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet 192.0.2.0/24 (id 123) deleted",
       "arguments": {
           "subnets": [
               {
                   "id": 123,
                   "subnet": "192.0.2.0/24"
               }
           ]
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-subnet4-get:

subnet4-get reference
=====================

``subnet4-get`` - retrieves detailed information
about the specified subnet. This command usually follows the
``subnet4-list`` command, which is used to discover available subnets with their
respective subnet identifiers and prefixes.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet4-get`

Command syntax:

::

   {
       "command": "subnet4-get",
       "arguments": {
           "id": 10
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "Info about IPv4 subnet 10.0.0.0/8 (id 10) returned",
       "arguments": {
           "subnets": [
               {
                   "subnet": "10.0.0.0/8",
                   "id": 1,
                   "option-data": [
                       ....
                   ]
                   ...
               }
           ]
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-subnet4-list:

subnet4-list reference
======================

``subnet4-list`` - lists all currently configured
subnets. The subnets are returned in a brief form, i.e. a subnet
identifier and subnet prefix are included for each subnet.

Supported by: ``kea-dhcp4``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet4-list`

Command syntax:

::

   {
       "command": "subnet4-list"
   }

Response syntax:

::

   {
       "result": 0,
       "text": "2 IPv4 subnets found",
       "arguments": {
       "subnets": [
           {
               "id": 10,
               "subnet": "10.0.0.0/8"
           },
           {
               "id": 100,
               "subnet": "192.0.2.0/24"
           }
       ]
   }

If no IPv4 subnets are found, an error code is returned along with the
error description.

.. _reference-subnet4-update:

subnet4-update reference
========================

``subnet4-update`` - updates a subnet in the
existing server configuration.

Supported by: ``kea-dhcp4``

Availability: 1.6.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet4-update`

Command syntax:

::

   {
       "command": "subnet4-update",
       "arguments": {
           "subnets": [ {
               "id": 123,
               "subnet": "10.20.30.0/24",
               ...
           } ]
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "IPv4 subnet updated",
       "arguments": {
           "subnets": [
               {
                   "id": 123,
                   "subnet": "10.20.30.0/24"
               }
           ]
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-subnet6-add:

subnet6-add reference
=====================

``subnet6-add`` - creates and adds a new subnet to
the existing server configuration. This operation has no impact on other
subnets.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet6-add`

Command syntax:

::

   {
       "command": "subnet6-add",
       "arguments": {
           "subnet6": [ {
               "id": 234,
               "subnet": "2001:db8:1::/64",
               ...
           } ]
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "IPv6 subnet added",
       "arguments": {
           "subnet6": [
               {
                   "id": 234,
                   "subnet": "2001:db8:1::/64"
               }
           ]
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-subnet6-del:

subnet6-del reference
=====================

``subnet6-del`` - removes a subnet from the
server's configuration. This command has no effect on other configured
subnets, but administrators should exercise caution when
using this command as removing a subnet may have unintended consequences.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet6-del`

Command syntax:

::

   {
       "command": "subnet6-del",
       "arguments": {
           "id": 234
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "IPv6 subnet 2001:db8:1::/64 (id 234) deleted",
       "subnets": [
           {
               "id": 234,
               "subnet": "2001:db8:1::/64"
           }
       ]
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-subnet6-get:

subnet6-get reference
=====================

``subnet6-get`` - retrieves detailed information
about the specified subnet. This command usually follows the
``subnet6-list`` command, which is used to discover available subnets with their
respective subnet identifiers and prefixes.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet6-get`

Command syntax:

::

   {
       "command": "subnet6-get",
       "arguments": {
           "id": 11
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "Info about IPv6 subnet 2001:db8:1::/64 (id 11) returned",
       "arguments": {
           "subnets": [
               {
                   "subnet": "2001:db8:1::/64",
                   "id": 1,
                   "option-data": [
                       ...
                   ]
                   ....
               }
           ]
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-subnet6-list:

subnet6-list reference
======================

``subnet6-list`` - lists all currently configured
subnets. The subnets are returned in a brief form, i.e. a subnet
identifier and subnet prefix are included for each subnet.

Supported by: ``kea-dhcp6``

Availability: 1.3.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet6-list`

Command syntax:

::

   {
       "command": "subnet6-list"
   }

Response syntax:

::

   {
       "result": 0,
       "text": "2 IPv6 subnets found",
       "arguments": {
       "subnets": [
           {
               "id": 11,
               "subnet": "2001:db8:1::/64"
           },
           {
               "id": 233,
               "subnet": "3000::/16"
           }
       ]
   }

If no IPv6 subnets are found, an error code is returned along with the
error description.

.. _reference-subnet6-update:

subnet6-update reference
========================

``subnet6-update`` - updates a subnet in the
existing server configuration. This operation has no impact on other
subnets.

Supported by: ``kea-dhcp6``

Availability: 1.6.0 (:ref:`The Subnet Commands hooks library<commands-subnet_cmds-lib>`)

Description and examples: see :ref:`command-subnet6-update`

Command syntax:

::

   {
       "command": "subnet6-update",
       "arguments": {
           "subnet6": [ {
               "id": 234,
               "subnet": "2001:db8:1::/64",
               ...
           } ]
       }
   }

Response syntax:

::

   {
       "result": 0,
       "text": "IPv6 subnet updated",
       "arguments": {
           "subnet6": [
               {
                   "id": 234,
                   "subnet": "2001:db8:1::/64"
               }
           ]
       }
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)

.. _reference-version-get:

version-get reference
=====================

``version-get`` - returns extended information
about the Kea version in operation. The returned string is the same as if Kea were
run with the -V command-line option.

Supported by: ``kea-dhcp4``, ``kea-dhcp6``, ``kea-dhcp-ddns``,
``kea-ctrl-agent``

Availability: 1.2.0 (built-in)

Description and examples: see :ref:`command-version-get`

Command syntax:

::

   {
       "command": "version-get"
   }

Response syntax:

::

   {
       "result": <integer>,
       "text": <string>
   }

The result is an integer representation of the status. Currently supported
statuses are:

-  0 - success

-  1 - error

-  2 - unsupported

-  3 - empty (command was completed successfully, but no data were
   affected or returned)
