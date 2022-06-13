.. _hooks-legal-log:

``legal_log``: Forensic Logging
===============================

The Forensic Logging hook library provides
hooks that record a detailed log of assignments, renewals, releases, and other
lease events into a set of log files.

Currently this library is only available to ISC customers with a paid support
contract.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or ``kea-dhcp6``
   process.

In many legal jurisdictions, companies - especially ISPs - must record
information about the addresses they have leased to DHCP clients. This
library is designed to help with that requirement. If the information
that it records is sufficient, it may be used directly.

If a jurisdiction requires that different information be saved, users
may use the custom formatting capability to extract information from the inbound
request packet, or from the outbound response packet. Administrators are advised
to use this feature with caution, as it may affect server performance.
The custom format cannot be used for control channel commands.

Alternatively, this library may be used as a template or an example for the
user's own custom logging hook. The logging is done as a set of hooks to allow
it to be customized to any particular need; modifying a hook library is easier
and safer than updating the core code. In addition, by using the hooks features,
users who do not need to log this information can leave it out and avoid
any performance penalties.

Log File Naming
~~~~~~~~~~~~~~~

The names of the log files follow a set pattern.

If using ``day``, ``month``, or ``year`` as the time unit, the file name follows
the format:

::

   path/base-name.CCYYMMDD.txt

where ``CC`` represents the century, ``YY`` represents the year,
``MM`` represents the month, and ``DD`` represents the day.

If using ``second`` as the time unit the file name follows the format:

::

   path/base-name.TXXXXXXXXXXXXXXXXXXXX.txt

where ``XXXXXXXXXXXXXXXXXXXX`` represents the time in seconds since the beginning
of the UNIX epoch.

When using ``second`` as the time unit, the file is rotated when
the ``count`` number of seconds pass. In contrast, when using ``day``, ``month``,
or ``year`` as the time unit, the file is rotated whenever the ``count`` of day,
month, or year starts, as applicable.

The ``"path"`` and ``"base-name"`` are supplied in the configuration as
described below; see :ref:`forensic-log-configuration`.

.. note::

   When running Kea servers for both DHCPv4 and DHCPv6, the log names
   must be distinct. See the examples in :ref:`forensic-log-configuration`.

.. _forensic-log-configuration:

Configuring the Forensic Logging Hooks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To use this functionality, the hook library must be included in the
configuration of the desired DHCP server modules. The ``legal_log`` library
can save logs to a text file or to a database (created using
``kea-admin``; see :ref:`mysql-database-create` and :ref:`pgsql-database-create`).
The library is installed alongside the Kea libraries in
``[kea-install-dir]/var/lib/kea``, where ``kea-install-dir`` is determined
by the ``--prefix`` option of the configure script; it defaults to
``/usr/local``. Assuming the default value, ``kea-dhcp4`` can be configured to load
the ``legal_log`` library like this:

.. code-block:: json

    {
        "Dhcp4": {
            "hooks-libraries": [
                {
                    "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
                    "parameters": {
                        "path": "/var/lib/kea/log",
                        "base-name": "kea-forensic4"
                    }
                }
            ]
        }
    }

For ``kea-dhcp6``, the configuration is:

.. code-block:: json

    {
        "Dhcp6": {
            "hooks-libraries": [
                {
                    "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
                    "parameters": {
                        "path": "/var/lib/kea/log",
                        "base-name": "kea-forensic6"
                    }
                }
            ]
        }
    }

The hook library parameters for the text file configuration are:

-  ``path`` - the directory in which the forensic file(s) will be written.
   The default value is ``[prefix]/var/lib/kea``. The directory must exist.

-  ``base-name`` - an arbitrary value which is used in conjunction with the
   current system date to form the current forensic file name. It
   defaults to ``kea-legal``.

-  ``time-unit`` - configures the time unit used to rotate the log file. Valid
   values are ``second``, ``day``, ``month``, or ``year``. It defaults to
   ``day``.

-  ``count`` - configures the number of time units that need to pass until the
   log file is rotated. It can be any positive number, or 0, which disables log
   rotation. It defaults to 1.

If log rotation is disabled, a new file is created when the library is
loaded; the new file name is different from any previous file name.

Additional actions can be performed just before closing the old file and after
opening the new file. These actions must point to an external executable or
script and are configured with the following settings:

-  ``prerotate`` - an external executable or script called with the name of the
   file that will be closed. Kea does not wait for the process to finish.

-  ``postrotate`` - an external executable or script called with the name of the
   file that was opened. Kea does not wait for the process to finish.

Custom formatting can be enabled for logging information that can be extracted
either from the client's request packet or from the server's response packet.
Use with caution as this might affect server performance.
The custom format cannot be used for control channel commands.
Two parameters can be used towards this goal, either together or separately:

-  ``request-parser-format`` - an evaluated parsed expression used to extract and
   log data from the incoming packet.

-  ``response-parser-format`` - an evaluated parsed expression used to extract and
   log data from the server response packet.

See :ref:`classification-using-expressions` for a list of expressions.
If either ``request-parser-format`` or ``response-parser-format`` is
configured, the default logging format is not used. If both of them are
configured, the resulting log message is constructed by concatenating the
data extracted from the request and the data extracted from the response.

The custom formatting permits logging on multiple lines using the hexstring 0x0a
(ASCII code for new line). In the log file, each line is prepended
with the log timestamp. For the database backend, the data is stored
(including the newline character) in the same entry.

Examples:

.. code-block:: json

    {
        "Dhcp6": {
            "hooks-libraries": [
                {
                    "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
                    "parameters": {
                        "path": "/var/lib/kea/log",
                        "base-name": "kea-forensic6",
                        "request-parser-format": "'first line' + 0x0a + 'second line'",
                        "response-parser-format": "'also second line' + 0x0a + 'third line'"
                    }
                }
            ]
        }
    }

Some data might be available in the request or only in the response; the
data in the request packet might differ from that in the response packet.

The lease-client context can only be printed using the default format, as this
information is not directly stored in the request packet or in the response
packet.

The ``timestamp-format`` parameter can be used to change the timestamp logged
at the beginning of each line. Permissible formatting is the one supported by
strftime plus the '%Q' extra format which adds the microseconds subunits. The
default is: "%Y-%m-%d %H:%M:%S %Z". This parameter has no effect for the
database backends, where the timestamp is defined at the schema level.

Examples:

.. code-block:: json

    {
        "Dhcp6": {
            "hooks-libraries": [
                {
                    "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
                    "parameters": {
                        "path": "/var/lib/kea/log",
                        "base-name": "kea-forensic6",
                        "timestamp-format": "%H%t%w %F%%"
                    }
                }
            ]
        }
    }

Additional parameters for the database connection can be specified, e.g:

.. code-block:: json

    {
      "Dhcp6": {
        "hooks-libraries": [
          {
            "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
            "parameters": {
              "name": "database-name",
              "password": "passwd",
              "type": "mysql",
              "user": "user-name"
            }
          }
        ]
      }
    }

For more specific information about database-related parameters, please refer to
:ref:`database-configuration4` and :ref:`database-configuration6`.

If it is desired to restrict forensic logging to certain subnets, the
``"legal-logging"`` boolean parameter can be specified within a user context
of these subnets. For example:

.. code-block:: json

    {
        "Dhcp4": {
            "subnet4": [
                {
                    "subnet": "192.0.2.0/24",
                    "pools": [
                        {
                            "pool": "192.0.2.1 - 192.0.2.200"
                        }
                    ],
                    "user-context": {
                        "legal-logging": false
                    }
                }
            ]
        }
    }

This configuration disables legal logging for the subnet "192.0.2.0/24". If the
``"legal-logging"`` parameter is not specified, it defaults to ``true``, which
enables legal logging for the subnet.

The following example demonstrates how to selectively disable legal
logging for an IPv6 subnet:

.. code-block:: json

    {
        "Dhcp6": {
            "subnet6": [
                {
                    "subnet": "2001:db8:1::/64",
                    "pools": [
                        {
                            "pool": "2001:db8:1::1-2001:db8:1::ffff"
                        }
                    ],
                    "user-context": {
                        "legal-logging": false
                    }
                }
            ]
        }
    }

See :ref:`dhcp4-user-contexts` and :ref:`dhcp6-user-contexts` to
learn more about user contexts in Kea configuration.

DHCPv4 Log Entries
~~~~~~~~~~~~~~~~~~

For DHCPv4, the library creates entries based on DHCPREQUEST, DHCPDECLINE,
and DHCPRELEASE messages, et al., and their responses. The resulting packets and
leases are taken into account, intercepted through the following hook points:

* ``pkt4_receive``
* ``leases4_committed``
* ``pkt4_send``
* ``lease4_release``
* ``lease4_decline``

An entry is a single string with no embedded end-of-line markers and a
prepended timestamp, and has the following sections:

::

   timestamp address duration device-id {client-info} {relay-info} {user-context}

Where:

-  ``timestamp`` - the date and time the log entry was written, in
   "%Y-%m-%d %H:%M:%S %Z" strftime format ("%Z" is the time zone name).

-  ``address`` - the leased IPv4 address given out, and whether it was
   assigned, renewed, or released.

-  ``duration`` - the lease lifetime expressed in days (if present), hours,
   minutes, and seconds. A lease lifetime of 0xFFFFFFFF will be denoted
   with the text "infinite duration." This information is not given
   when the lease is released.

-  ``device-id`` - the client's hardware address shown as a numerical type and
   hex-digit string.

-  ``client-info`` - the DHCP client id option (61) if present, shown as a
   hex string. When its content is printable it is displayed.

-  ``relay-info`` - for relayed packets, the ``giaddr`` and the RAI ``circuit-id``,
   ``remote-id``, and ``subscriber-id`` options (option 82 sub options: 1, 2 and 6),
   if present. The ``circuit-id`` and ``remote-id`` are presented as hex
   strings. When their content is printable it is displayed.

-  ``user-context`` - the optional user context associated with the lease.

For instance (line breaks are added here for readability; they are not
present in the log file):

::

   2018-01-06 01:02:03 CET Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:
   hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33,
   identified by circuit-id: 68:6f:77:64:79 (howdy) and remote-id: 87:f6:79:77:ef

or for a release:

::

   2018-01-06 01:02:03 CET Address: 192.2.1.100 has been released from a device with hardware address:
   hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33,
   identified by circuit-id: 68:6f:77:64:79 (howdy) and remote-id: 87:f6:79:77:ef

In addition to logging lease activity driven by DHCPv4 client traffic,
the hook library also logs entries for the following lease management control
channel commands: ``lease4-add``, ``lease4-update``, and ``lease4-del``. These cannot have
custom formatting. Each entry is a single string with no embedded end-of-line
markers, and it will typically have the following form:

``lease4-add:``

::

   *timestamp* Administrator added a lease of address: *address* to a device with hardware address: *device-id*

Depending on the arguments of the add command, it may also include the
client-id and duration.

Example:

::

   2018-01-06 01:02:03 CET Administrator added a lease of address: 192.0.2.202 to a device with hardware address:
   1a:1b:1c:1d:1e:1f for 1 days 0 hrs 0 mins 0 secs

``lease4-update:``

::

   *timestamp* Administrator updated information on the lease of address: *address* to a device with hardware address: *device-id*

Depending on the arguments of the update command, it may also include
the client-id and lease duration.

Example:

::

   2018-01-06 01:02:03 CET Administrator updated information on the lease of address: 192.0.2.202 to a device
   with hardware address: 1a:1b:1c:1d:1e:1f, client-id: 1234567890

``lease4-del:`` deletes have two forms, one by address and one by
identifier and identifier type:

::

   *timestamp* Administrator deleted the lease for address: *address*

or

::

   *timestamp* Administrator deleted a lease for a device identified by: *identifier-type* of *identifier*

Currently only a type of ``@b hw-address`` (hardware address) is supported.

Examples:

::

   2018-01-06 01:02:03 CET Administrator deleted the lease for address: 192.0.2.202

   2018-01-06 01:02:12 CET Administrator deleted a lease for a device identified by: hw-address of 1a:1b:1c:1d:1e:1f

The ``request-parser-format`` and ``response-parser-format`` options can be used to
extract and log data from the incoming packet and server response packet,
respectively. The configured value is an evaluated parsed expression returning a
string. A list of tokens is described in the server classification process.
Use with caution as this might affect server performance.
If either of them is configured, the default logging format is not used.
If both of them are configured, the resulting log message is constructed by
concatenating the logged data extracted from the request and the logged data
extracted from the response.

The custom formatting permits logging on multiple lines using the hexstring 0x0a
(ASCII code for new line). In the case of the log file, each line is prepended
with the log timestamp. For the database backend, the data is stored
(including the newline character) in the same entry.

Examples:

.. code-block:: json

    {
      "Dhcp4": {
        "hooks-libraries": [
          {
            "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
            "parameters": {
              "name": "database-name",
              "password": "passwd",
              "type": "mysql",
              "user": "user-name",
              "request-parser-format": "'log entry' + 0x0a + 'same log entry'",
              "response-parser-format": "'also same log entry' + 0x0a + 'again same log entry'"
            }
          }
        ]
      }
    }

Some data might be available in the request or in the response only, and some
data might differ in the incoming packet from the one in the response packet.

Examples:

.. code-block:: json

    {
        "request-parser-format": "ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7, 'Address: ' + ifelse(option[50].exists, addrtotext(option[50].hex), addrtotext(pkt4.ciaddr)) + ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') + ifelse(option[61].exists, ', client-id: ' + hexstring(option[61].hex, ':'), '') + ifelse(pkt4.giaddr == 0.0.0.0, '', ' connected via relay at address: ' + addrtotext(pkt4.giaddr) + ifelse(option[82].option[1].exists, ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'), '') + ifelse(option[82].option[2].exists, ', remote-id: ' + hexstring(option[82].option[2].hex, ':'), '') + ifelse(option[82].option[6].exists, ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'), '')), '')",
        "response-parser-format": "ifelse(pkt4.msgtype == 5, 'Address: ' + addrtotext(pkt4.yiaddr) + ' has been assigned for ' + uint32totext(option[51].hex) + ' seconds to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') + ifelse(option[61].exists, ', client-id: ' + hexstring(option[61].hex, ':'), '') + ifelse(pkt4.giaddr == 0.0.0.0, '', ' connected via relay at address: ' + addrtotext(pkt4.giaddr) + ifelse(option[82].option[1].exists, ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'), '') + ifelse(option[82].option[2].exists, ', remote-id: ' + hexstring(option[82].option[2].hex, ':'), '') + ifelse(option[82].option[6].exists, ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'), '')), '')"
    }

.. raw:: html

    <details><summary>Expand here!</summary>
    <pre>{
        "request-parser-format":
            "ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7,
                'Address: ' +
                ifelse(option[50].exists,
                    addrtotext(option[50].hex),
                    addrtotext(pkt4.ciaddr)) +
                ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
                ifelse(option[61].exists,
                    ', client-id: ' + hexstring(option[61].hex, ':'),
                    '') +
                ifelse(pkt4.giaddr == 0.0.0.0,
                    '',
                    ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                    ifelse(option[82].option[1].exists,
                        ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                        '') +
                    ifelse(option[82].option[2].exists,
                        ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                        '') +
                    ifelse(option[82].option[6].exists,
                        ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                        '')),
                '')",
        "response-parser-format":
            "ifelse(pkt4.msgtype == 5,
                'Address: ' + addrtotext(pkt4.yiaddr) + ' has been assigned for ' + uint32totext(option[51].hex) + ' seconds to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
                ifelse(option[61].exists,
                    ', client-id: ' + hexstring(option[61].hex, ':'),
                    '') +
                ifelse(pkt4.giaddr == 0.0.0.0,
                    '',
                    ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                    ifelse(option[82].option[1].exists,
                        ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                        '') +
                    ifelse(option[82].option[2].exists,
                        ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                        '') +
                    ifelse(option[82].option[6].exists,
                        ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                        '')),
                '')"
    }</pre>
    </details><br>

This will log the following data on request and renew:

::

   Address: 192.2.1.100 has been assigned for 6735 seconds to a device with hardware address: hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33, circuit-id: 68:6f:77:64:79, remote-id: 87:f6:79:77:ef, subscriber-id: 1a:2b:3c:4d:5e:6f

This will log the following data on release and decline:

::

   Address: 192.2.1.100 has been released from a device with hardware address: hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33, circuit-id: 68:6f:77:64:79, remote-id: 87:f6:79:77:ef, subscriber-id: 1a:2b:3c:4d:5e:6f

A similar result can be obtained by configuring only ``request-parser-format``.

Examples:

.. code-block:: json

    {
        "request-parser-format": "ifelse(pkt4.msgtype == 3, 'Address: ' + ifelse(option[50].exists, addrtotext(option[50].hex), addrtotext(pkt4.ciaddr)) + ' has been assigned' + ifelse(option[51].exists, ' for ' + uint32totext(option[51].hex) + ' seconds', '') + ' to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') + ifelse(option[61].exists, ', client-id: ' + hexstring(option[61].hex, ':'), '') + ifelse(pkt4.giaddr == 0.0.0.0, '', ' connected via relay at address: ' + addrtotext(pkt4.giaddr) + ifelse(option[82].option[1].exists, ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'), '') + ifelse(option[82].option[2].exists, ', remote-id: ' + hexstring(option[82].option[2].hex, ':'), '') + ifelse(option[82].option[6].exists, ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'), '')), ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7, 'Address: ' + ifelse(option[50].exists, addrtotext(option[50].hex), addrtotext(pkt4.ciaddr)) + ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') + ifelse(option[61].exists, ', client-id: ' + hexstring(option[61].hex, ':'), '') + ifelse(pkt4.giaddr == 0.0.0.0, '', ' connected via relay at address: ' + addrtotext(pkt4.giaddr) + ifelse(option[82].option[1].exists, ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'), '') + ifelse(option[82].option[2].exists, ', remote-id: ' + hexstring(option[82].option[2].hex, ':'), '') + ifelse(option[82].option[6].exists, ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'), '')), ''))"
    }

.. raw:: html

    <details><summary>Expand here!</summary>
    <pre>{
        "request-parser-format":
            "ifelse(pkt4.msgtype == 3,
                'Address: ' +
                ifelse(option[50].exists,
                    addrtotext(option[50].hex),
                    addrtotext(pkt4.ciaddr)) +
                ' has been assigned' +
                ifelse(option[51].exists,
                    ' for ' + uint32totext(option[51].hex) + ' seconds',
                    '') +
                ' to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
                ifelse(option[61].exists,
                    ', client-id: ' + hexstring(option[61].hex, ':'),
                    '') +
                ifelse(pkt4.giaddr == 0.0.0.0,
                    '',
                    ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                    ifelse(option[82].option[1].exists,
                        ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                        '') +
                    ifelse(option[82].option[2].exists,
                        ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                        '') +
                    ifelse(option[82].option[6].exists,
                        ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                        '')),
                ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7,
                    'Address: ' +
                    ifelse(option[50].exists,
                        addrtotext(option[50].hex),
                        addrtotext(pkt4.ciaddr)) +
                    ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
                    ifelse(option[61].exists,
                        ', client-id: ' + hexstring(option[61].hex, ':'),
                        '') +
                    ifelse(pkt4.giaddr == 0.0.0.0,
                        '',
                        ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                        ifelse(option[82].option[1].exists,
                            ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                            '') +
                        ifelse(option[82].option[2].exists,
                            ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                            '') +
                        ifelse(option[82].option[6].exists,
                            ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                            '')),
                    ''))"
    }</pre>
    </details><br>

DHCPv6 Log Entries
~~~~~~~~~~~~~~~~~~

For DHCPv6, the library creates entries based on REQUEST, RENEW, RELEASE,
and DECLINE messages, et al. and their responses. The resulting packets and leases
are taken into account, intercepted through the following hook points:

* ``pkt6_receive``
* ``leases6_committed``
* ``pkt6_send``
* ``lease6_release``
* ``lease6_decline``

An entry is a single string with no embedded end-of-line markers and a
prepended timestamp, and has the following sections:

::

   timestamp address duration device-id {relay-info}* {user-context}

Where:

-  ``timestamp`` - the date and time the log entry was written, in
   "%Y-%m-%d %H:%M:%S %Z" strftime format ("%Z" is the time zone name).

-  ``address`` - the leased IPv6 address or prefix given out, and whether it
   was assigned, renewed, or released.

-  ``duration`` - the lease lifetime expressed in days (if present), hours,
   minutes, and seconds. A lease lifetime of 0xFFFFFFFF will be denoted
   with the text "infinite duration." This information is not given
   when the lease is released.

-  ``device-id`` - the client's DUID and hardware address (if present).

-  ``relay-info`` - for relayed packets the content of relay agent messages, and the
   ``remote-id`` (code 37), ``subscriber-id`` (code 38), and ``interface-id`` (code 18)
   options, if present. Note that the ``interface-id`` option, if present,
   identifies the whole interface on which the relay agent received the message.
   This typically translates to a single link in the network, but
   it depends on the specific network topology. Nevertheless, this is
   useful information to better pinpoint the location of the device,
   so it is recorded, if present.

-  ``user-context`` - the optional user context associated with the lease.

For instance (line breaks are added here for readability; they are not
present in the log file):

::

   2018-01-06 01:02:03 PST Address:2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs
   to a device with DUID: 17:34:e2:ff:09:92:54 and hardware address: hwtype=1 08:00:2b:02:3f:4e
   (from Raw Socket) connected via relay at address: fe80::abcd for client on link address: 3001::1,
   hop count: 1, identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f and subscriber-id: 1a:2b:3c:4d:5e:6f

or for a release:

::

   2018-01-06 01:02:03 PST Address:2001:db8:1:: has been released
   from a device with DUID: 17:34:e2:ff:09:92:54 and hardware address: hwtype=1 08:00:2b:02:3f:4e
   (from Raw Socket) connected via relay at address: fe80::abcd for client on link address: 3001::1,
   hop count: 1, identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f and subscriber-id: 1a:2b:3c:4d:5e:6f

In addition to logging lease activity driven by DHCPv6 client traffic,
the hook library also logs entries for the following lease management control channel
commands: ``lease6-add``, ``lease6-update``, and ``lease6-del``. Each entry is a
single string with no embedded end-of-line markers, and it will
typically have the following form:

``lease6-add:``

::

   *timestamp* Administrator added a lease of address: *address* to a device with DUID: *DUID*

Depending on the arguments of the add command, it may also include the
hardware address and duration.

Example:

::

   2018-01-06 01:02:03 PST Administrator added a lease of address: 2001:db8::3 to a device with DUID:
   1a:1b:1c:1d:1e:1f:20:21:22:23:24 for 1 days 0 hrs 0 mins 0 secs

``lease6-update:``

::

   *timestamp* Administrator updated information on the lease of address: *address* to a device with DUID: *DUID*

Depending on the arguments of the update command, it may also include
the hardware address and lease duration.

Example:

::

   2018-01-06 01:02:03 PST Administrator updated information on the lease of address: 2001:db8::3 to a device with
   DUID: 1a:1b:1c:1d:1e:1f:20:21:22:23:24, hardware address: 1a:1b:1c:1d:1e:1f

``lease6-del:`` deletes have two forms, one by address and one by
identifier and identifier type:

::

   *timestamp* Administrator deleted the lease for address: *address*

or

::

   *timestamp* Administrator deleted a lease for a device identified by: *identifier-type* of *identifier*

Currently only a type of ``DUID`` is supported.

Examples:

::

   2018-01-06 01:02:03 PST Administrator deleted the lease for address: 2001:db8::3

   2018-01-06 01:02:11 PST Administrator deleted a lease for a device identified by: duid of 1a:1b:1c:1d:1e:1f:20:21:22:23:24

The ``request-parser-format`` and ``response-parser-format`` options can be used to
extract and log data from the incoming packet and server response packet,
respectively. The configured value is an evaluated parsed expression returning a
string. A list of tokens is described in the server classification process.
Use with caution as this might affect server performance.
If either of them is configured, the default logging format is not used.
If both of them are configured, the resulting log message is constructed by
concatenating the logged data extracted from the request and the logged data
extracted from the response.

The custom formatting permits logging on multiple lines using the hexstring 0x0a
(ASCII code for new line). In the case of the log file, each line is prepended
with the log timestamp. For the database backend, the data is stored
(including the newline character) in the same entry.

Examples:

.. code-block:: json

    {
      "Dhcp6": {
        "hooks-libraries": [
          {
            "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
            "parameters": {
              "name": "database-name",
              "password": "passwd",
              "type": "mysql",
              "user": "user-name",
              "request-parser-format": "'log entry' + 0x0a + 'same log entry'",
              "response-parser-format": "'also same log entry' + 0x0a + 'again same log entry'"
            }
          }
        ]
      }
    }

Some data might be available in the request or in the response only, and some
data might differ in the incoming packet from the one in the response packet.

Notes:

In the case of IPv6, the packets can contain multiple IA_NA (3) or IA_PD (25)
options, each containing multiple options, including OPTION_IAADDR (5) or
OPTION_IAPREFIX (25) suboptions.
To be able to print the current lease associated with the log entry, the
forensic log hook library internally isolates the corresponding IA_NA or IA_PD
option and respective suboption matching the current lease.
The hook library will iterate over all new allocated addresses and all deleted
addresses, making each address available for logging as the current lease for
the respective logged entry.

They are accessible using the following parser expressions:

Current lease associated with OPTION_IAADDR:

::

    addrtotext(substring(option[3].option[5].hex, 0, 16))

Current lease associated with OPTION_IAPREFIX:

::

    addrtotext(substring(option[25].option[26].hex, 9, 16))

All other parameters of the options are available at their respective offsets
in the option. Please read RFC8415 for more details.

Examples:

.. code-block:: json

    {
        "request-parser-format": "ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9, ifelse(option[3].option[5].exists, 'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), '') + ifelse(option[25].option[26].exists, 'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), ''), '')",
        "response-parser-format": "ifelse(pkt6.msgtype == 7, ifelse(option[3].option[5].exists and not (substring(option[3].option[5].hex, 20, 4) == 0), 'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), '') + ifelse(option[25].option[26].exists and not (substring(option[25].option[26].hex, 4, 4) == 0), 'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), ''), '')"
    }

.. raw:: html

    <details><summary>Expand here!</summary>
    <pre>{
        "request-parser-format":
            "ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9,
                ifelse(option[3].option[5].exists,
                    'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    '') +
                ifelse(option[25].option[26].exists,
                    'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    ''),
                '')",
        "response-parser-format":
            "ifelse(pkt6.msgtype == 7,
                ifelse(option[3].option[5].exists and not (substring(option[3].option[5].hex, 20, 4) == 0),
                    'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    '') +
                ifelse(option[25].option[26].exists and not (substring(option[25].option[26].hex, 4, 4) == 0),
                    'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    ''),
                '')"
    }</pre>
    </details><br>

This will log the following data on request, renew, and rebind for NA:

::

   Address: 2001:db8:1:: has been assigned for 713 seconds to a device with DUID: 17:34:e2:ff:09:92:54 connected via relay at address: fe80::abcd for client on link address: 3001::1, remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f, subscriber-id: 1a:2b:3c:4d:5e:6f, connected at location interface-id: 72:65:6c:61:79:31:3a:65:74:68:30

This will log the following data on request, renew and rebind for PD:

::

   Prefix: 2001:db8:1::/64 has been assigned for 713 seconds to a device with DUID: 17:34:e2:ff:09:92:54 connected via relay at address: fe80::abcd for client on link address: 3001::1, remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f, subscriber-id: 1a:2b:3c:4d:5e:6f, connected at location interface-id: 72:65:6c:61:79:31:3a:65:74:68:30

This will log the following data on release and decline for NA:

::

   Address: 2001:db8:1:: has been released from a device with DUID: 17:34:e2:ff:09:92:54 connected via relay at address: fe80::abcd for client on link address: 3001::1, remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f, subscriber-id: 1a:2b:3c:4d:5e:6f, connected at location interface-id: 72:65:6c:61:79:31:3a:65:74:68:30

This will log the following data on release and decline for PD:

::

   Prefix: 2001:db8:1::/64 has been released from a device with DUID: 17:34:e2:ff:09:92:54 connected via relay at address: fe80::abcd for client on link address: 3001::1, remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f, subscriber-id: 1a:2b:3c:4d:5e:6f, connected at location interface-id: 72:65:6c:61:79:31:3a:65:74:68:30

A similar result can be obtained by configuring only ``request-parser-format``.

Examples:

.. code-block:: json

    {
        "request-parser-format": "ifelse(pkt6.msgtype == 3 or pkt6.msgtype == 5 or pkt6.msgtype == 6, ifelse(option[3].option[5].exists, 'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), '') + ifelse(option[25].option[26].exists, 'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), ''), ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9, ifelse(option[3].option[5].exists, 'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), '') + ifelse(option[25].option[26].exists, 'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), ''), ''))"
    }

.. raw:: html

    <details><summary>Expand here!</summary>
    <pre>{
        "request-parser-format":
            "ifelse(pkt6.msgtype == 3 or pkt6.msgtype == 5 or pkt6.msgtype == 6,
                ifelse(option[3].option[5].exists,
                    'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    '') +
                ifelse(option[25].option[26].exists,
                    'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    ''),
                ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9,
                    ifelse(option[3].option[5].exists,
                        'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                        ifelse(relay6[0].peeraddr == '',
                            '',
                            ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                            ifelse(relay6[0].option[37].exists,
                                ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                                '') +
                            ifelse(relay6[0].option[38].exists,
                                ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                                '') +
                            ifelse(relay6[0].option[18].exists,
                                ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                                '')),
                        '') +
                    ifelse(option[25].option[26].exists,
                        'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                        ifelse(relay6[0].peeraddr == '',
                            '',
                            ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                            ifelse(relay6[0].option[37].exists,
                                ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                                '') +
                            ifelse(relay6[0].option[38].exists,
                                ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                                '') +
                            ifelse(relay6[0].option[18].exists,
                                ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                                '')),
                        ''),
                    ''))"
    }</pre>
    </details><br>

.. _forensic-log-database:

Database Backend
~~~~~~~~~~~~~~~~

Log entries can be inserted into a database when Kea is configured with
database backend support. Kea uses a table named ``logs``, that includes a
timestamp generated by the database software, and a text log with the same
format as files without the timestamp.

Please refer to :ref:`mysql-database` for information on using a MySQL database;
or to :ref:`pgsql-database` for PostgreSQL database information. The ``logs``
table is part of the Kea database schemas.

Configuration parameters are extended by standard lease database
parameters as defined in :ref:`database-configuration4`. The ``type``
parameter should be ``mysql``, ``postgresql`` or ``logfile``; when
it is absent or set to ``logfile``, files are used.

This database feature is experimental. No specific tools are provided
to operate the database, but standard tools may be used, for example,
to dump the logs table from a MYSQL database:

::

   $ mysql --user keatest --password keatest -e "select * from logs;"
   +---------------------+--------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------+----+
   | timestamp           | address      | log                                                                                                                                                             | id |
   +---------------------+--------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------+----+
   | 2022-03-30 17:38:41 | 192.168.50.1 | Address: 192.168.50.1 has been assigned for 0 hrs 10 mins 0 secs to a device with hardware address: hwtype=1 ff:01:02:03:ff:04, client-id: 00:01:02:03:04:05:06 | 31 |
   | 2022-03-30 17:38:43 | 192.168.50.1 | Address: 192.168.50.1 has been assigned for 0 hrs 10 mins 0 secs to a device with hardware address: hwtype=1 ff:01:02:03:ff:04, client-id: 00:01:02:03:04:05:06 | 32 |
   | 2022-03-30 17:38:45 | 192.168.50.1 | Address: 192.168.50.1 has been assigned for 0 hrs 10 mins 0 secs to a device with hardware address: hwtype=1 ff:01:02:03:ff:04, client-id: 00:01:02:03:04:05:06 | 33 |
   +---------------------+--------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------+----+

Like all the other database-centric features, forensic logging supports database
connection recovery, which can be enabled by setting the ``on-fail`` parameter.
If not specified, the ``on-fail`` parameter in forensic logging defaults to
``serve-retry-continue``;
this is a change from its behavior in the Lease Commands, Host Commands, and
Configuration Backend hook libraries, where
``on-fail`` defaults to ``stop-retry-exit``. In this case, the server continues
serving clients and does not shut down even if the recovery mechanism fails.
If ``on-fail`` is set to ``serve-retry-exit``, the server will shut down if
the connection to the database backend is not restored according to the
``max-reconnect-tries`` and ``reconnect-wait-time`` parameters, but it
continues serving clients while this mechanism is activated.
