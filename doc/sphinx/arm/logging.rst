.. _logging:

*******
Logging
*******

Logging Configuration
=====================

During its operation Kea may produce many log messages. They differ in
severity (some are more important than others) and source (different
components, like hooks, produce different messages). It is useful to
understand which log messages are critical and which are not, and to
configure logging appropriately. For example, debug-level messages
can be safely ignored in a typical deployment. They are, however, very
useful when debugging a problem.

The logging system in Kea is configured through the ``loggers`` entry in the
server section of the configuration file.

Loggers
-------

Within Kea, a message is logged through an entity called a "logger."
Different components log messages through different loggers, and each
logger can be configured independently of the others. Some components,
in particular the DHCP server processes, may use multiple loggers to log
messages pertaining to different logical functions of the component. For
example, the DHCPv4 server uses one logger for messages about packet
reception and transmission, another logger for messages related to lease
allocation, and so on. Some of the libraries used by the Kea server,
such as libdhcpsrv, use their own loggers.

Users implementing hook libraries (code attached to the server at
runtime) are responsible for creating the loggers used by those
libraries. Such loggers should have unique names, different from the
logger names used by Kea. That way, the messages produced by the hook
library can be distinguished from messages issued by the core Kea code.
Unique names also allow the hook loggers to be configured independently of
loggers used by Kea. Whenever it makes sense, a hook library can use
multiple loggers to log messages pertaining to different logical parts
of the library.

In the server section of a configuration file, the
configuration for zero or more loggers (including loggers used by the
proprietary hook libraries) can be specified. If there are no loggers specified, the
code uses default values; these cause Kea to log messages of INFO
severity or greater to standard output. There is a small time window
after Kea has been started but before it has read its configuration;
logging in this short period can be controlled using environment
variables. For details, see :ref:`logging-during-startup`.

The three main elements of a logger configuration are: ``name`` (the
component that is generating the messages), ``severity`` (what to log),
and ``output_commands`` (where to log). There is also a ``debuglevel``
element, which is only relevant if debug-level logging has been
selected.

The ``name`` (string) Logger
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each logger in the system has a name: that of the component binary file
using it to log messages. For instance, to configure logging
for the DHCPv4 server, add an entry for a logger named “kea-dhcp4”.
This configuration will then be used by the loggers in the DHCPv4
server and all the libraries used by it, unless a library defines its
own logger and there is a specific logger configuration that applies to
that logger.

When tracking down an issue with the server's operation, use of DEBUG
logging is required to obtain the verbose output needed for problem
diagnosis. However, the high verbosity is likely to overwhelm the
logging system in cases where the server is processing high-volume
traffic. To mitigate this problem, Kea can use multiple loggers, for
different functional parts of the server, that can each be configured
independently. If the user is reasonably confident that a problem
originates in a specific function of the server, or that the problem is
related to a specific type of operation, they may enable high verbosity
only for the relevant logger, thereby limiting the DEBUG messages to the
required minimum.

The loggers are associated with a particular library or binary of Kea.
However, each library or binary may (and usually does) include multiple
loggers. For example, the DHCPv4 server binary contains separate loggers
for packet parsing, dropped packets, callouts, etc.

The loggers form a hierarchy. For each program in Kea, there is a "root"
logger, named after the program (e.g. the root logger for :iscman:`kea-dhcp4`, the
DHCPv4 server, is named :iscman:`kea-dhcp4`). All other loggers are children of
this logger and are named accordingly, e.g. the allocation engine in the
DHCPv4 server logs messages using a logger called
``kea-dhcp4.alloc-engine``.

This relationship is important, as each child logger derives its default
configuration from its parent root logger. In the typical case, the root
logger configuration is the only logging configuration specified in the
configuration file and so applies to all loggers. If an entry is made
for a given logger, any attributes specified override those of the root
logger, whereas any not specified are inherited from it.

To illustrate this, suppose we are using the DHCPv4 server with the
root logger :iscman:`kea-dhcp4` logging at the INFO level. In order to enable
DEBUG verbosity for DHCPv4 packet drops, we must create a configuration
entry for the logger with ``"name": "kea-dhcp4.bad-packets”``,
``"severity": "DEBUG"``, and an explicit debug level. All other configuration
parameters may be omitted for this logger if it should use the default values
specified in the root logger's configuration.

``debuglevel`` is inherited only if ``severity`` is missing as well. For
predictable results, if ``severity`` is ``"DEBUG"``, these two attributes
should always be explicitly specified or omitted together. An entry with an
explicit ``"DEBUG"`` severity does not inherit ``debuglevel`` from the root
logger and defaults to ``0`` if missing, resulting in no debug messages
being logged. This is a consequence of relying on the log4cplus inheritance
mechanism.

If there are multiple logger specifications in the configuration that
might match a particular logger, the specification with the more
specific logger name takes precedence. For example, if there are entries
for both :iscman:`kea-dhcp4` and ``kea-dhcp4.dhcpsrv``, the main DHCPv4 server
program — and all libraries it uses other than the ``dhcpsrv`` library
(libdhcpsrv) — logs messages according to the configuration in the
first entry (:iscman:`kea-dhcp4`). Messages generated by the ``dhcpsrv`` library
are logged according to the configuration set by the second entry.

Currently defined loggers are listed in the following table. The
"Software Package" column of this table specifies whether the particular
loggers belong to the core Kea code (open source Kea binaries and
libraries), or hook libraries (open source or premium).

.. tabularcolumns:: |p{0.2\linewidth}|p{0.2\linewidth}|p{0.6\linewidth}|

.. table:: List of loggers supported by Kea servers and hook libraries shipped with Kea/premium packages
   :class: longtable
   :widths: 20 20 60

   +----------------------------------+---------------------------------------+--------------------------------+
   | Logger Name                      | Software Package                      | Description                    |
   +==================================+=======================================+================================+
   | ``kea-ctrl-agent``               | core                                  | The root logger for            |
   |                                  |                                       | the Control Agent              |
   |                                  |                                       | exposing the RESTful           |
   |                                  |                                       | control API. All               |
   |                                  |                                       | components used by             |
   |                                  |                                       | the Control Agent              |
   |                                  |                                       | inherit the settings           |
   |                                  |                                       | from this logger.              |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-ctrl-agent.auth``          | core                                  | A logger which covers          |
   |                                  |                                       | access control details, such as|
   |                                  |                                       | a result of the basic HTTP     |
   |                                  |                                       | authentication.                |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-ctrl-agent.ctrl-agent``    | core                                  | Used to log results of         |
   |                                  |                                       | configuration checks,          |
   |                                  |                                       | information about services     |
   |                                  |                                       | starting or failing to start,  |
   |                                  |                                       | command receival and           |
   |                                  |                                       | forwarding.                    |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-ctrl-agent.http``          | core                                  | A logger which                 |
   |                                  |                                       | outputs log messages           |
   |                                  |                                       | related to receiving,          |
   |                                  |                                       | parsing, and sending           |
   |                                  |                                       | HTTP messages.                 |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-ctrl-agent.rbac-hooks``    | :ischooklib:`libca_rbac.so`           | Used to log messages related   |
   |                                  | enterprise hook library               | to the operation of the RBAC   |
   |                                  |                                       | hook library.                  |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4``                    | core                                  | The root logger for            |
   |                                  |                                       | the DHCPv4 server.             |
   |                                  |                                       | All components used            |
   |                                  |                                       | by the DHCPv4 server           |
   |                                  |                                       | inherit the settings           |
   |                                  |                                       | from this logger.              |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp6``                    | core                                  | The root logger for            |
   |                                  |                                       | the DHCPv6 server.             |
   |                                  |                                       | All components used            |
   |                                  |                                       | by the DHCPv6 server           |
   |                                  |                                       | inherit the settings           |
   |                                  |                                       | from this logger.              |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.alloc-engine``,      | core                                  | Used by the lease              |
   | ``kea-dhcp6.alloc-engine``       |                                       | allocation engine,             |
   |                                  |                                       | which is responsible           |
   |                                  |                                       | for managing leases            |
   |                                  |                                       | in the lease                   |
   |                                  |                                       | database, i.e.                 |
   |                                  |                                       | creating, modifying,           |
   |                                  |                                       | and removing DHCP              |
   |                                  |                                       | leases as a result of          |
   |                                  |                                       | processing messages            |
   |                                  |                                       | from clients.                  |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-ctrl-agent.auth``,         | core                                  | Used to log malformed HTTP     |
   | ``kea-dhcp4.auth``,              |                                       | packets when using basic       |
   | ``kea-dhcp6.auth``               |                                       | authentication.                |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.bad-packets``,       | core                                  | Used by the DHCP               |
   | ``kea-dhcp6.bad-packets``        |                                       | servers for logging            |
   |                                  |                                       | inbound client                 |
   |                                  |                                       | packets that were              |
   |                                  |                                       | dropped or to which            |
   |                                  |                                       | the server responded           |
   |                                  |                                       | with a DHCPNAK. It             |
   |                                  |                                       | allows administrators          |
   |                                  |                                       | to configure a                 |
   |                                  |                                       | separate log output            |
   |                                  |                                       | that contains only             |
   |                                  |                                       | packet drop and                |
   |                                  |                                       | reject entries.                |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.bootp-hooks``        | :ischooklib:`libdhcp_bootp.so`        | This logger is used to log     |
   |                                  | open-source hook library              | messages related to the        |
   |                                  |                                       | operation of the BOOTP hook    |
   |                                  |                                       | library.                       |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-ctrl-agent.callouts``,     | core                                  | Used to log messages           |
   | ``kea-dhcp4.callouts``,          |                                       | pertaining to the              |
   | ``kea-dhcp6.callouts``,          |                                       | callouts registation and       |
   | ``kea-dhcp-ddns.callouts``       |                                       | execution for a particular     |
   |                                  |                                       | hook point.                    |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.cb-cmds-hooks``,     | :ischooklib:`libdhcp_cb_cmds.so`      | Used to log messages related   |
   | ``kea-dhcp6.cb-cmds-hooks``      | subscription hook library             | to the operation of the        |
   |                                  |                                       | Config Backend Commands        |
   |                                  |                                       | hook library.                  |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.class-cmds-hooks``,  | :ischooklib:`libdhcp_class_cmds.so`   | Used to log messages related   |
   | ``kea-dhcp6.class-cmds-hooks``   | subscription hook library             | to the operation of the        |
   |                                  |                                       | Class Commands                 |
   |                                  |                                       | hook library.                  |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.commands``,          | core                                  | Used to log messages           |
   | ``kea-dhcp6.commands``           |                                       | relating to the                |
   |                                  |                                       | handling of commands           |
   |                                  |                                       | received by the DHCP           |
   |                                  |                                       | server over the                |
   |                                  |                                       | command channel.               |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.database``,          | core                                  | Used to log messages           |
   | ``kea-dhcp6.database``           |                                       | relating to general            |
   |                                  |                                       | operations on the              |
   |                                  |                                       | relational databases.          |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.ddns-tuning-hooks``, | :ischooklib:`libdhcp_ddns_tuning.so`  | Used to log messages related   |
   | ``kea-dhcp6.ddns-tuning-hooks``  | premium hook library                  | to the operation of the        |
   |                                  |                                       | DDNS Tuning hook library.      |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.ddns``,              | core                                  | Used by the DHCP               |
   | ``kea-dhcp6.ddns``               |                                       | server to log                  |
   |                                  |                                       | messages related to            |
   |                                  |                                       | Client FQDN and                |
   |                                  |                                       | Hostname option                |
   |                                  |                                       | processing. It also            |
   |                                  |                                       | includes log messages          |
   |                                  |                                       | related to the                 |
   |                                  |                                       | relevant DNS updates.          |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.dhcp4``,             | core                                  | Used to log basic operations.  |
   | ``kea-dhcp6.dhcp6``              |                                       |                                |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.dhcpsrv``,           | core                                  | The base loggers for the       |
   | ``kea-dhcp6.dhcpsrv``            |                                       | ``libkea-dhcpsrv.so`` library. |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.eval``,              | core                                  | Used to log messages           |
   | ``kea-dhcp6.eval``               |                                       | relating to the                |
   |                                  |                                       | client classification          |
   |                                  |                                       | expression evaluation          |
   |                                  |                                       | code.                          |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.flex-id-hooks``,     | :ischooklib:`libdhcp_flex_id.so`      | Used                           |
   | ``kea-dhcp6.flex-id-hooks``      | premium hook library                  | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the               |
   |                                  |                                       | Flexible Identifier            |
   |                                  |                                       | hook library.                  |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.flex-option-hooks``, | :ischooklib:`libdhcp_flex_option.so`  | Used to log messages related   |
   | ``kea-dhcp6.flex-option-hooks``  | open-source hook library              | to the operaton of             |
   |                                  |                                       | the Flexible Option            |
   |                                  |                                       | hook library.                  |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.ha-hooks``,          | :ischooklib:`libdhcp_ha.so`           | Used                           |
   | ``kea-dhcp6.ha-hooks``           | open-source hook library              | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the High          |
   |                                  |                                       | Availability hook              |
   |                                  |                                       | library.                       |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-ctrl-agent.hooks``,        | core                                  | Used to log messages related   |
   | ``kea-dhcp4.hooks``,             |                                       | to the maagemet of hook        |
   | ``kea-dhcp6.hooks``,             |                                       | libraries, e.g.                |
   | ``kea-dhcp-ddns.hooks``          |                                       | registatin and                 |
   |                                  |                                       | deregistration of the          |
   |                                  |                                       | libraries, and to the          |
   |                                  |                                       | initialization of the          |
   |                                  |                                       | callouts execution             |
   |                                  |                                       | for various hook               |
   |                                  |                                       | points within the              |
   |                                  |                                       | DHCP server.                   |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.host-cache-hooks``,  | :ischooklib:`libdhcp_host_cache.so`   | Used                           |
   | ``kea-dhcp6.host-cache-hooks``   | subscription hook library             | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the Host          |
   |                                  |                                       | Cache hook library.            |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.host-cmds-hooks``,   | :ischooklib:`libdhcp_host_cmds.so`    | Used                           |
   | ``kea-dhcp6.host-cmds-hooks``    | premium hook library                  | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the Host          |
   |                                  |                                       | Commands hook                  |
   |                                  |                                       | library. In general,           |
   |                                  |                                       | these pertain to               |
   |                                  |                                       | the loading and                |
   |                                  |                                       | unloading of the               |
   |                                  |                                       | library and the                |
   |                                  |                                       | execution of commands          |
   |                                  |                                       | by the library.                |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.hosts``,             | core                                  | Used within                    |
   | ``kea-dhcp6.hosts``              |                                       | ``libdhcpsrv``, it logs        |
   |                                  |                                       | messages related to            |
   |                                  |                                       | the management of              |
   |                                  |                                       | DHCP host                      |
   |                                  |                                       | reservations, i.e.             |
   |                                  |                                       | retrieving                     |
   |                                  |                                       | reservations and               |
   |                                  |                                       | adding new                     |
   |                                  |                                       | reservations.                  |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.lease-cmds-hooks``,  | :ischooklib:`libdhcp_lease_cmds.so`   | Used                           |
   | ``kea-dhcp6.lease-cmds-hooks``   | open-source hook library              | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the               |
   |                                  |                                       | Lease Commands hook            |
   |                                  |                                       | library. In general,           |
   |                                  |                                       | these pertain to               |
   |                                  |                                       | the loading and                |
   |                                  |                                       | unloading of the               |
   |                                  |                                       | library and the                |
   |                                  |                                       | execution of commands          |
   |                                  |                                       | by the library.                |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.limits-hooks``,      | :ischooklib:`libdhcp_limits.so`       | Used to log messages related   |
   | ``kea-dhcp6.limits-hooks``       | subscription hook library             | to the operation of the        |
   |                                  |                                       | Limits hook library.           |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.lease-query-hooks``, | :ischooklib:`libdhcp_lease_query.so`  | Used                           |
   | ``kea-dhcp6.lease-query-hooks``  | premium hook library                  | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the               |
   |                                  |                                       | Leasequery hook library.       |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.leases``,            | core                                  | Used by the DHCP               |
   | ``kea-dhcp6.leases``             |                                       | server to log                  |
   |                                  |                                       | messages related to            |
   |                                  |                                       | lease allocation. The          |
   |                                  |                                       | messages include               |
   |                                  |                                       | detailed information           |
   |                                  |                                       | about the allocated            |
   |                                  |                                       | or offered leases,             |
   |                                  |                                       | errors during the              |
   |                                  |                                       | lease allocation,              |
   |                                  |                                       | etc.                           |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.legal-log-hooks``,   | :ischooklib:`libdhcp_legal_log.so`    | Used                           |
   | ``kea-dhcp6.legal-log-hooks``    | premium hook library                  | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the               |
   |                                  |                                       | Forensic Logging               |
   |                                  |                                       | hook library.                  |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.mysql-cb-hooks``,    | :ischooklib:`libdhcp_mysql_cb.so`     | Used                           |
   | ``kea-dhcp6.mysql-cb-hooks``     | open-source hook library              | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the               |
   |                                  |                                       | MySQL Configuration            |
   |                                  |                                       | Backend hook                   |
   |                                  |                                       | library.                       |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.options``,           | core                                  | Used by the DHCP               |
   | ``kea-dhcp6.options``            |                                       | server to log                  |
   |                                  |                                       | messages related to            |
   |                                  |                                       | the processing of              |
   |                                  |                                       | options in the DHCP            |
   |                                  |                                       | messages, i.e.                 |
   |                                  |                                       | parsing options,               |
   |                                  |                                       | encoding options into          |
   |                                  |                                       | on-wire format, and            |
   |                                  |                                       | packet classification          |
   |                                  |                                       | using options                  |
   |                                  |                                       | contained in the               |
   |                                  |                                       | received packets.              |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.packets``,           | core                                  | Mostly                         |
   | ``kea-dhcp6.packets``            |                                       | used to log messages           |
   |                                  |                                       | related to                     |
   |                                  |                                       | transmission of the            |
   |                                  |                                       | DHCP packets, i.e.             |
   |                                  |                                       | packet reception and           |
   |                                  |                                       | the sending of a               |
   |                                  |                                       | response. Such                 |
   |                                  |                                       | messages include               |
   |                                  |                                       | information about the          |
   |                                  |                                       | source and                     |
   |                                  |                                       | destination IP                 |
   |                                  |                                       | addresses and                  |
   |                                  |                                       | interfaces used to             |
   |                                  |                                       | transmit packets. The          |
   |                                  |                                       | logger is also used            |
   |                                  |                                       | to log messages                |
   |                                  |                                       | related to subnet              |
   |                                  |                                       | selection, as this             |
   |                                  |                                       | selection is usually           |
   |                                  |                                       | based on the IP                |
   |                                  |                                       | addresses, relay               |
   |                                  |                                       | addresses, and/or              |
   |                                  |                                       | interface names,               |
   |                                  |                                       | which can be                   |
   |                                  |                                       | retrieved from the             |
   |                                  |                                       | received packet even           |
   |                                  |                                       | before the DHCP                |
   |                                  |                                       | message carried in             |
   |                                  |                                       | the packet is parsed.          |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.perfmon-hooks``,     | :ischooklib:`libdhcp_perfmon.so`      | Used to log messages related   |
   | ``kea-dhcp6.perfmon-hooks``      | open-source hook library              | to performance monitoring.     |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.ping-check-hooks``   | :ischooklib:`libdhcp_ping_check.so`   | Used                           |
   |                                  | subscription hook library             | to log messages related to     |
   |                                  |                                       | carrying out pre-offer ping    |
   |                                  |                                       | checks of candidate leases.    |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.pgsql-cb-hooks``,    | :ischooklib:`libdhcp_pgsql_cb.so`     | Used                           |
   | ``kea-dhcp6.pgsql-cb-hooks``     | open-source hook library              | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the               |
   |                                  |                                       | PostgreSQL Configuration       |
   |                                  |                                       | Backend hook                   |
   |                                  |                                       | library.                       |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.run-script-hooks``,  | :ischooklib:`libdhcp_run_script.so`   | Used to log messages related   |
   | ``kea-dhcp6.run-script-hooks``   | open-source hook library              | to the operation of the        |
   |                                  |                                       | Run Script hook library.       |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.radius-hooks``,      | :ischooklib:`libdhcp_radius.so`       | Used                           |
   | ``kea-dhcp6.radius-hooks``       | premium hook library                  | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the               |
   |                                  |                                       | RADIUS hook library.           |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.stat-cmds-hooks``,   | :ischooklib:`libdhcp_stat_cmds.so`    | Used                           |
   | ``kea-dhcp6.stat-cmds-hooks``    | opens-source hook library             | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the               |
   |                                  |                                       | Statistics Commands            |
   |                                  |                                       | hook library. In               |
   |                                  |                                       | general, these                 |
   |                                  |                                       | pertain to loading             |
   |                                  |                                       | and unloading the              |
   |                                  |                                       | library and the                |
   |                                  |                                       | execution of commands          |
   |                                  |                                       | by the library.                |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.subnet-cmds-hooks``, | :ischooklib:`libdhcp_subnet_cmds.so`  | Used                           |
   | ``kea-dhcp6.subnet-cmds-hooks``  | premium hook library                  | to log messages                |
   |                                  |                                       | related to the                 |
   |                                  |                                       | operation of the               |
   |                                  |                                       | Subnet Commands hook           |
   |                                  |                                       | library. In general,           |
   |                                  |                                       | these pertain to               |
   |                                  |                                       | loading and unloading          |
   |                                  |                                       | the library and the            |
   |                                  |                                       | execution of commands          |
   |                                  |                                       | by the library.                |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.tcp``,               | core                                  | Used to log messages related   |
   | ``kea-dhcp6.tcp``                |                                       | to TCP traffic.                |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp4.user_chk``,          | :ischooklib:`libdhcp_user_chk.so`     | Used to log messages related   |
   | ``kea-dhcp6.user_chk``           | hook library                          | to the operaton of the         |
   |                                  |                                       | User Check hook library.       |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp-ddns``                | core                                  | The root logger for            |
   |                                  |                                       | the :iscman:`kea-dhcp-ddns`    |
   |                                  |                                       | daemon. All                    |
   |                                  |                                       | components used by             |
   |                                  |                                       | this daemon inherit            |
   |                                  |                                       | the settings from              |
   |                                  |                                       | this logger unless             |
   |                                  |                                       | there are                      |
   |                                  |                                       | configurations for             |
   |                                  |                                       | more specialized               |
   |                                  |                                       | loggers.                       |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-ctrl-agent.dctl``,         | core                                  | Used to log basic inofrmaton   |
   | ``kea-dhcp-ddns.dctl``           |                                       | about the process,             |
   |                                  |                                       | received signals, and          |
   |                                  |                                       | triggered                      |
   |                                  |                                       | reconfigurations.              |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp-ddns.asiodns``,       | core                                  | Used to log messages about     |
   |                                  |                                       | network events in DDNS         |
   |                                  |                                       | operations.                    |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp-ddns.dhcpddns``       | core                                  | Used by                        |
   |                                  |                                       | the :iscman:`kea-dhcp-ddns`    |
   |                                  |                                       | daemon to log                  |
   |                                  |                                       | events related to              |
   |                                  |                                       | DDNS operations.               |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp-ddns.dhcp-to-d2``     | core                                  | Used by the                    |
   |                                  |                                       | :iscman:`kea-dhcp-ddns` daemon |
   |                                  |                                       | to log                         |
   |                                  |                                       | information about              |
   |                                  |                                       | events dealing with            |
   |                                  |                                       | receiving messages             |
   |                                  |                                       | from the DHCP servers          |
   |                                  |                                       | and adding them to             |
   |                                  |                                       | the queue for                  |
   |                                  |                                       | processing.                    |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp-ddns.d2-to-dns``      | core                                  | Used by the                    |
   |                                  |                                       | :iscman:`kea-dhcp-ddns` daemon |
   |                                  |                                       | to log                         |
   |                                  |                                       | information about              |
   |                                  |                                       | events dealing with            |
   |                                  |                                       | sending and receiving          |
   |                                  |                                       | messages to and from           |
   |                                  |                                       | the DNS servers.               |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp-ddns.gss-tsig-hooks`` | :ischooklib:`libddns_gss_tsig.so`     | Used to log messages related   |
   |                                  | subscription hook library             | to the operation of the        |
   |                                  |                                       | GSS-TSIG hook library.         |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-dhcp-ddns.libdhcp-ddns``   | core                                  | Used to log events related to  |
   |                                  |                                       | DDNS operations.               |
   +----------------------------------+---------------------------------------+--------------------------------+
   | ``kea-netconf``                  | core                                  | The root logger for            |
   |                                  |                                       | the NETCONF agent.             |
   |                                  |                                       | All components used            |
   |                                  |                                       | by NETCONF inherit             |
   |                                  |                                       | the settings from              |
   |                                  |                                       | this logger if there           |
   |                                  |                                       | is no specialized              |
   |                                  |                                       | logger provided.               |
   +----------------------------------+---------------------------------------+--------------------------------+

Note that user-defined hook libraries should not use any of the loggers
mentioned above, but should instead define new loggers with names that
correspond to the libraries using them. Suppose that a user created
a library called “libdhcp-packet-capture” to dump packets received and
transmitted by the server to a file. An appropriate name for the
logger could be ``kea-dhcp4.packet-capture-hooks``. (Note that the hook
library implementer only specifies the second part of this name, i.e.
“packet-capture”. The first part is a root-logger name and is prepended
by the Kea logging system.) It is also important to note that since this
new logger is a child of a root logger, it inherits the configuration
from the root logger, something that can be overridden by an entry in
the configuration file.

The easiest way to find a logger name is to configure all logging to go
to a single destination and look there for specific logger names. See
:ref:`logging-message-format` for details.

The ``severity`` (string) Logger
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This specifies the category of messages logged. Each message is logged
with an associated severity, which may be one of the following (in
descending order of severity):

-  FATAL - associated with messages generated by a condition that is so
   serious that the server cannot continue executing.

-  ERROR - associated with messages generated by an error condition. The
   server continues executing, but the results may not be as
   expected.

-  WARN - indicates an out-of-the-ordinary condition. However, the
   server continues executing normally.

-  INFO - an informational message marking some event.

-  DEBUG - messages produced for debugging purposes.

When the severity of a logger is set to one of these values, it
only logs messages of that severity and above (e.g. setting the logging
severity to INFO logs INFO, WARN, ERROR, and FATAL messages). The
severity may also be set to NONE, in which case all messages from that
logger are inhibited.

.. note::

   The :iscman:`keactrl` tool, described in :ref:`keactrl`, can be configured
   to start the servers in verbose mode. If this is the case, the
   settings of the logging severity in the configuration file have
   no effect; the servers use a logging severity of DEBUG
   regardless of the logging settings specified in the configuration
   file. To control severity via the configuration file,
   please make sure that the ``kea_verbose`` value is set to "no" within
   the :iscman:`keactrl` configuration.

.. _debuglevel:

The ``debuglevel`` (integer) Logger
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When a logger's severity is set to DEBUG, this value specifies the
level of debug messages to be printed. It ranges from 0 (least
verbose) to 99 (most verbose). If severity for the logger is not DEBUG,
this value is ignored.

The ``output-options`` (list) Logger
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each logger can have zero or more ``output-options``. These specify
where log messages are sent and are explained in detail below.

.. note::

   As of Kea 2.5.1, alias ``output-options`` was added that can be used
   interchangeably with previous ``output_options`` configuration key.
   The reason behind this was to keep all configuration keys consistent i.e.
   to use "dash" instead of "underscore" in the key name. For the time being
   both configuration keys are considered correct and mean the same to Kea parsers.

   As of Kea 2.5.2, the ``output-options`` becomes the default configuration key
   and ``output_options`` can be used as an alias.

The ``output`` (string) Option
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This value determines the type of output. There are several special
values allowed here: ``stdout`` (messages are printed on standard
output), ``stderr`` (messages are printed on stderr), ``syslog``
(messages are logged to syslog using the default name), ``syslog:name``
(messages are logged to syslog using a specified name). Any other value is
interpreted as a filename to which messages should be written.

The ``flush`` (boolean) Option
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This flushes the buffers after each log message. Doing this reduces performance
but ensures that if the program terminates abnormally, all messages
up to the point of termination are output. The default is ``true``.

The ``maxsize`` (integer) Option
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This option is only relevant when the destination is a file; this is the maximum size
in bytes that a log file may reach. When the maximum size is reached,
the file is renamed and a new file created. Initially, a ".1" is
appended to the name; if a ".1" file exists, it is renamed ".2", etc.
This is referred to as rotation.

The default value is 10240000 (10MB). The smallest value that can be
specified without disabling rotation is 204800. Any value less than
this, including 0, disables rotation. The greatest possible value is INT_MAX MB, which is
approximately 2PB.

.. note::

   Due to a limitation of the underlying logging library (log4cplus),
   rolling over the log files (from ".1" to ".2", etc.) may show odd
   results; there can be multiple small files at the timing of rollover.
   This can happen when multiple processes try to roll over the
   files simultaneously. Version 1.1.0 of log4cplus solved this problem,
   so if this version or later of log4cplus is used to build Kea, the
   issue should not occur. Even with older versions, it is normally
   expected to happen rarely unless the log messages are produced very
   frequently by multiple different processes.

The ``maxver`` (integer) Option
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This option is only relevant when the destination is a file and rotation is enabled
(i.e. maxsize is large enough). This is the maximum number of rotated
versions that will be kept. Once that number of files has been reached,
the oldest file, "log-name.maxver", is discarded each time the log
rotates. In other words, at most there will be the active log file plus
maxver rotated files. The minimum and default value is 1.

The ``pattern`` (string) Option
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This option can be used to specify the layout pattern of messages for
a logger. Kea logging is implemented using the log4cplus library and its
output formatting is based, conceptually, on the printf formatting from C;
this is discussed in detail in the next section,
:ref:`logging-message-format`.

Each output type (``stdout``, file, or ``syslog``) has a default ``pattern`` which
describes the content of its log messages. This parameter can be used to
specify a desired pattern. The pattern for each logger is governed
individually, so each configured logger can have its own pattern. Omitting
the ``pattern`` parameter or setting it to an empty string, "", causes
Kea to use the default pattern for that logger's output type.

In addition to the log text itself, the default patterns used for ``stdout``
and files contain information such as date and time, logger level, and
process information. The default pattern for ``syslog`` is limited primarily
to log level, source, and the log text. This avoids duplicating information
which is usually supplied by syslog.

.. warning::
    Users are strongly encouraged to test their pattern(s) on a local,
    non-production instance of Kea, running in the foreground and
    logging to ``stdout``.

.. _logging-message-format:

Logging Message Format
----------------------

As mentioned above, Kea log message content is controlled via a scheme similar
to the C language's printf formatting. The "pattern" used for each message is
described by a string containing one or more format components as part of a
text string.  In addition to the components, the string may contain any other
useful text for the administrator.

The behavior of Kea's format strings is determined by log4cplus. The following
time format options are possible enclosed in ``%D{}`` or ``%d{}``:

.. table:: List of supported time format string components by Kea's logger
   :class: longtable
   :widths: 8 40

   +-----------+-----------------------------------------------+
   | Component | Value                                         |
   +===========+===============================================+
   | ``%a``    | Abbreviated weekday name                      |
   +-----------+-----------------------------------------------+
   | ``%A``    | Full weekday name                             |
   +-----------+-----------------------------------------------+
   | ``%b``    | Abbreviated month name                        |
   +-----------+-----------------------------------------------+
   | ``%B``    | Full month name                               |
   +-----------+-----------------------------------------------+
   | ``%c``    | Standard date and time string                 |
   +-----------+-----------------------------------------------+
   | ``%d``    | Day of month as a decimal(1-31)               |
   +-----------+-----------------------------------------------+
   | ``%H``    | Hour(0-23)                                    |
   +-----------+-----------------------------------------------+
   | ``%I``    | Hour(1-12)                                    |
   +-----------+-----------------------------------------------+
   | ``%j``    | Day of year as a decimal(1-366)               |
   +-----------+-----------------------------------------------+
   | ``%m``    | Month as decimal(1-12)                        |
   +-----------+-----------------------------------------------+
   | ``%M``    | Minute as decimal(0-59)                       |
   +-----------+-----------------------------------------------+
   | ``%p``    | Locale's equivalent of AM or PM               |
   +-----------+-----------------------------------------------+
   | ``%q``    | milliseconds as decimal(0-999)                |
   +-----------+-----------------------------------------------+
   | ``%Q``    | microseconds as decimal(0-999.999)            |
   +-----------+-----------------------------------------------+
   | ``%S``    | Second as decimal(0-59)                       |
   +-----------+-----------------------------------------------+
   | ``%U``    | Week of year, Sunday being first day(0-53)    |
   +-----------+-----------------------------------------------+
   | ``%w``    | Weekday as a decimal(0-6, Sunday being 0)     |
   +-----------+-----------------------------------------------+
   | ``%W``    | Week of year, Monday being first day(0-53)    |
   +-----------+-----------------------------------------------+
   | ``%x``    | Standard date string                          |
   +-----------+-----------------------------------------------+
   | ``%X``    | Standard time string                          |
   +-----------+-----------------------------------------------+
   | ``%y``    | Year in decimal without century(0-99)         |
   +-----------+-----------------------------------------------+
   | ``%Y``    | Year including century as decimal             |
   +-----------+-----------------------------------------------+
   | ``%Z``    | Time zone name                                |
   +-----------+-----------------------------------------------+
   | ``%%``    | The percent sign                              |
   +-----------+-----------------------------------------------+

Refer to the documentation for the ``strftime()`` function found in the
``<ctime>`` header or the ``strftime(3)`` UNIX manual page for more
information.

It is probably easiest to understand this by examining the default pattern
for stdout and files; currently they are the same. That pattern is shown
below:

::

    "%D{%Y-%m-%d %H:%M:%S.%q} %-5p [%c/%i.%t] %m\n"

and a typical log produced by this pattern looks something like this:

::

    2019-08-05 14:27:45.871 DEBUG [kea-dhcp4.dhcpsrv/8475.12345] DHCPSRV_TIMERMGR_START_TIMER starting timer: reclaim-expired-leases

That breaks down to:

  - ``%D{%Y-%m-%d %H:%M:%S.%q}``
    "%D" is the local date and time when the log message is generated,
    while everything between the curly braces, "{}", are date and time components.
    From the example log above this produces:
    ``2019-08-05 14:27:45.871``

  - ``%-5p``
    The severity of the message, output as a minimum of five characters,
    using right-padding with spaces. In our example log: ``DEBUG``

  - ``%c``
    The log source. This includes two elements: the Kea process generating the
    message, in this case, :iscman:`kea-dhcp4`; and the component within the program
    from which the message originated, ``dhcpsrv`` (e.g.  the name of the
    library used by DHCP server implementations).

  - ``%i``
    The process ID. From the example log: ``8475``.

  - ``%t``
    The thread ID. From the example log: ``12345``.
    The format of the thread ID is OS-dependent: e.g. on some systems
    it is an address, so it is displayed in hexadecimal.

  - ``%m``
    The log message itself. Kea log messages all begin with a message identifier
    followed by arbitrary log text. Every message in Kea has a unique
    identifier, which can be used as an index to the :ref:`kea-messages`, where
    more information can be obtained. In our example log above, the identifier
    is ``DHCPSRV_TIMERMGR_START_TIMER``. The log text is typically a brief
    description detailing the condition that caused the message to be logged. In
    our example, the information logged,
    ``starting timer: reclaim-expired-leases``, explains that the timer for the
    expired lease reclamation cycle has been started.

.. Warning::

    Omitting ``%m`` omits the log message text from the output, making it
    rather useless. ``%m`` should be considered mandatory.

Finally, note that spacing between components, the square brackets around the
log source and PID, and the final carriage return ``\n`` are all literal text
specified as part of the pattern.

.. Warning::

    To ensure that each log entry is a separate line, patterns
    must end with an ``\n``. There may be use cases where it is not desired
    so we do not enforce its inclusion. If it is omitted from
    the pattern, the log entries will run together in one long "line".

The default pattern for ``syslog`` output is:

::

    "%-5p [%c.%t] %m\n"

It omits the date and time as well as the process ID, as this
information is typically output by ``syslog``. Note that Kea uses the pattern
to construct the text it sends to ``syslog`` (or any other destination). It has
no influence on the content ``syslog`` may add or formatting it may do.

Consult the OS documentation for ``syslog`` behavior, as there are multiple
implementations.

A complete list of logging parameters supported by Kea is shown in the table below:

.. table:: List of supported format string components by Kea's logger
   :class: longtable
   :widths: 8 40

   +-----------+------------------------------------------------------------------------+
   | Component | Value                                                                  |
   +===========+========================================================================+
   | ``%b``    | Outputs file that called the log e.g., logger_impl.cc                  |
   +-----------+------------------------------------------------------------------------+
   | ``%c``    | Outputs the logger of the event e.g., kea-dhcp4.hosts                  |
   +-----------+------------------------------------------------------------------------+
   | ``%d``    | ``%d{}`` formats UTC time output e.g., ``%d{%Y-%m-%d %H:%M:%S.%q}``    |
   +-----------+------------------------------------------------------------------------+
   | ``%D``    | ``%D{}`` formats LOCAL time output e.g., ``%D{%Y-%m-%d %H:%M:%S.%q}``  |
   +-----------+------------------------------------------------------------------------+
   | ``%E``    | Outputs environment variables e.g., ``%E{PATH}``                       |
   +-----------+------------------------------------------------------------------------+
   | ``%F``    | Outputs filename where logging request was issued e.g., logger_impl.cc |
   +-----------+------------------------------------------------------------------------+
   | ``%h``    | Outputs hostname of the system e.g., host-1                            |
   +-----------+------------------------------------------------------------------------+
   | ``%H``    | Outputs fully qualified domain name e.g., host-1.example.com           |
   +-----------+------------------------------------------------------------------------+
   | ``%l``    | Equivalent to ``%F:%L`` e.g., logger_impl.cc:179                       |
   +-----------+------------------------------------------------------------------------+
   | ``%L``    | Outputs the line number where the log was called e.g., 179             |
   +-----------+------------------------------------------------------------------------+
   | ``%m``    | Outputs the actual log message                                         |
   +-----------+------------------------------------------------------------------------+
   | ``%M``    | Outputs caller (function name) of the log message                      |
   +-----------+------------------------------------------------------------------------+
   | ``%n``    | Outputs line separator suppored by platform e.g., ``\n`` in Linux      |
   +-----------+------------------------------------------------------------------------+
   | ``%p``    | Outputs log severity e.g., INFO                                        |
   +-----------+------------------------------------------------------------------------+
   | ``%r``    | Outputs milliseconds since program start e.g., 1235                    |
   +-----------+------------------------------------------------------------------------+
   | ``%t``    | Outputs thread id that generated the log message e.g., 281472855306256 |
   +-----------+------------------------------------------------------------------------+
   | ``%T``    | Outputs thread name that generated the log message e.g., 168005        |
   +-----------+------------------------------------------------------------------------+
   | ``%i``    | Outputs process id that generated the log message e.g., 168030         |
   +-----------+------------------------------------------------------------------------+
   | ``%%``    | Outputs a literal percent sign                                         |
   +-----------+------------------------------------------------------------------------+

Padding and truncation are also possible with modifiers preceeding the component.  This is
done by placing a number and other modifier characters between the component and the %
sign. There are five ways of modifying the output shown by example here.

  - ``%20p``
    Left pads with spaces (align right) if the severity is shorter than 20 characters.

  - ``%-15r``
    Right pads with spaces (align left) if the milliseconds since program start is shorter
    than 15 characters.

  - ``%.30m``
    Truncates from the beginning of the message if the message is longer than 30
    characters.

  - ``%10.35E{PATH}``
    Left pad with spaces (align right) if the environment variable "PATH" is shorter than
    10 characters.  If the content is longer than 35 characters, then truncate from the
    beginning of the string.

  - ``%-15.40m``
    Right pad with spaces (align left) if the log message is shorter than 15 characters.
    If the message is longer than 40 characters, truncate from the beginning.

Supported parameters depend on the liblog4cplus version used to compile Kea.  This can
be checked by executing ``kea-dhcp4 -W | grep -i log4cplus`` which will produce output
like this: ``LOG4CPLUS_VERSION:  2.0.5``.  Consult the documentation in the
`log4cplus wiki <https://github.com/log4cplus/log4cplus/wiki>`__ for further information
about the version you have installed.

Example Logger Configurations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this example, we want to set the server logging to write to the
console using standard output.

::

   "Server": {
       "loggers": [
           {
               "name": "kea-dhcp4",
               "output-options": [
                   {
                       "output": "stdout"
                   }
               ],
               "severity": "WARN"
           }
       ]
   }

As a second example, we want to store DEBUG log messages in a file
that is at most 2MB and keep up to eight copies of old log files. Once the
logfile grows to 2MB, it should be renamed and a new file should be created.

::

   "Server": {
       "loggers": [
           {
               "name": "kea-dhcp6",
               "output-options": [
                   {
                       "output": "/var/log/kea-debug.log",
                       "maxver": 8,
                       "maxsize": 204800,
                       "flush": true,
                       "pattern": "%d{%j %H:%M:%S.%q} %c %m\n"
                   }
               ],
               "severity": "DEBUG",
               "debuglevel": 99
           }
      ]
   }

Notice that the above configuration uses a custom pattern which produces output like this:

::

    220 13:50:31.783 kea-dhcp4.dhcp4 DHCP4_STARTED Kea DHCPv4 server version 1.6.0-beta2-git started


.. _logging-during-startup:

Logging During Kea Startup
--------------------------

The logging configuration is specified in the configuration file.
However, when Kea starts, the configuration file is not read until partway into the
initialization process. Prior to that, the logging settings are set to
default values, although it is possible to modify some aspects of the
settings by means of environment variables. In the absence of
any logging configuration in the configuration file, the settings of the
(possibly modified) default configuration will persist while the program
is running.

The following environment variables can be used to control the behavior
of logging during startup:

``KEA_LOCKFILE_DIR``

   Specifies a directory where the logging system should create its lock
   file. If not specified, it is prefix/var/run/kea, where "prefix"
   defaults to /usr/local. This variable must not end with a slash.
   There is one special value: "none", which instructs Kea not to create
   a lock file at all. This may cause issues if several processes log to
   the same file.

``KEA_LOGGER_DESTINATION``

   Specifies logging output. There are several special values:

   ``stdout``
   Log to standard output.

   ``stderr``
   Log to standard error.

   ``syslog[:fac]``
   Log via syslog. The optional "fac" (which is separated from the word
   "syslog" by a colon) specifies the facility to be used for the log
   messages. Unless specified, messages are logged using the
   facility "local0".

   Any other value is treated as a name of the output file. If not
   otherwise specified, Kea logs to standard output.

Logging Levels
==============

All Kea servers follow the overall intention to let the user
know what is going on while not overloading the logging system with too much information, as that
could easily be used as a denial-of-service attack.

Unlike the FATAL, ERROR, WARN and
INFO levels, DEBUG has additional parameters. The following list details
the basic information that is logged on each level. Sometimes the circumstances
determine whether a piece of information is logged on a higher
or lower level. For example, if a packet is being dropped due to configured classification, that
is an execution of the configured policy and would be logged on debuglevel 15. However, if the
packet is dropped due to an exception being thrown, it is much more important, as it may indicate
a software bug, serious problems with memory, or database connectivity problems. As such it may
be logged on much higher levels, such as WARN or even ERROR.

- 0 - singular messages printed during startup or shutdown of the server.
- 10 - log information about received API commands.
- 15 - information about reasons why a packet was dropped.
- 40 - tracing information, including processing decisions, results
  of expression evaluations, and more.
- 45 - similar to level 40, but with more details, e.g. the subnet being
  selected for an incoming packet.
- 50 - evaluations of expressions, status received from hook points, lease
  processing, packet processing details, including unpacking, packing, sending, etc.
- 55 - includes all details available, including full packet contents
  with all options printed.

The debug levels apply only to messages logged on DEBUG, and are configured using
the ``debuglevel`` option. See the :ref:`debuglevel` section for details.
