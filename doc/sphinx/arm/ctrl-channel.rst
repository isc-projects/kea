.. _ctrl-channel:

**************
Management API
**************

A classic approach to daemon configuration assumes that the server's
configuration is stored in configuration files and, when the
configuration is changed, the daemon is restarted. This approach has the
significant disadvantage of introducing periods of downtime when client
traffic is not handled. Another risk is that if the new configuration is
invalid for any reason, the server may refuse to start, which will
further extend the downtime period until the issue is resolved.

To avoid such problems, the DHCPv4, DHCPv6, and D2 servers in Kea include
support for a mechanism that allows online reconfiguration without
requiring server shutdown. Both servers can be instructed to open
control sockets, which is a communications channel. The server is able
to receive commands on that channel, act on them, and report back
status.

The DHCPv4, DHCPv6, and D2 servers receive commands over the UNIX domain
sockets. For details on how to configure these sockets, see
:ref:`dhcp4-ctrl-channel` and :ref:`dhcp6-ctrl-channel`. While
it is possible to control the servers directly using UNIX domain sockets,
that requires that the controlling client be running on the same machine
as the server. SSH is usually used to connect remotely to the controlled
machine.

Network administrators usually prefer using some form of a RESTful API
to control the servers, rather than using UNIX domain sockets directly.
Therefore, Kea includes a component called the Control Agent (CA), which
exposes a RESTful API to the controlling clients and can forward
commands to the respective Kea services over the UNIX domain sockets.
The CA configuration is described in
:ref:`agent-configuration`.

The HTTP requests received by the CA contain the control commands
encapsulated within HTTP requests. Simply speaking, the CA is
responsible for stripping the HTTP layer from the received commands and
forwarding the commands in a JSON format over the UNIX domain sockets to
the respective services. Because the CA receives commands for all
services, it requires additional "forwarding" information to be included
in the client's messages. This forwarding information is carried within
the ``service`` parameter of the received command. If the ``service``
parameter is not included, or if the parameter is a blank list, the CA
assumes that the control command is targeted at the CA itself and
attempts to respond.

Control connections over both HTTP and UNIX domain sockets are guarded
with timeouts. The timeout value is set to 10 seconds and is not
configurable.

This API can be used by external tools to manage and monitor Kea operation.
An example of such a monitoring tool is ISC's Stork. For details, see
:ref:`stork`.

.. _ctrl-channel-syntax:

Data Syntax
===========

Communication over the control channel is conducted using JSON
structures. If configured, Kea opens a socket and listens for
incoming connections. A process connecting to this socket is expected to
send JSON commands structured as follows:

::

   {
       "command": "foo",
       "service": [ "dhcp4" ]
       "arguments": {
           "param1": "value1",
           "param2": "value2",
           ...
       }
   }

The same command sent over the RESTful interface to the CA has the
following structure:

::

       POST / HTTP/1.1\r\n
       Content-Type: application/json\r\n
       Content-Length: 147\r\n\r\n
       {
           "command": "foo",
           "service": [ "dhcp4" ]
           "arguments": {
               "param1": "value1",
               "param2": "value2",
               ...
           }
       }

``command`` is the name of the command to execute and is mandatory.
``arguments`` is a map of the parameters required to carry out the given
command. The exact content and format of the map are command-specific.

``service`` is a list of the servers at which the control command is
targeted. In the example above, the control command is targeted at the
DHCPv4 server. In most cases, the CA simply forwards this command to
the DHCPv4 server for processing via a UNIX domain socket. Sometimes,
the command including a service value may also be processed by the CA,
if the CA is running a hook library which handles such a command for
the given server. As an example, the hook library loaded by the CA may
perform some operations on the database, such as adding host
reservations, modifying leases, etc. An advantage of performing
DHCPv4-specific administrative operations in the CA, rather than
forwarding it to the DHCPv4 server, is the ability to perform these
operations without disrupting the DHCPv4 service, since the DHCPv4
server does not have to stop processing DHCP messages to apply changes to
the database. Nevertheless, these situations are rather rare; in
most cases, when the ``service`` parameter contains a name of the
service, the commands are simply forwarded by the CA. The forwarded
command includes the ``service`` parameter, but this parameter is ignored
by the receiving server. This parameter is only meaningful to the CA.

If the command received by the CA does not include a ``service``
parameter or this list is empty, the CA simply processes this message on
its own. For example, a ``config-get`` command which includes no service
parameter returns the Control Agent's own configuration. The
``config-get`` command with a service value "dhcp4" is forwarded to the DHCPv4
server and returns the DHCPv4 server's configuration.

The following list shows the mapping of the values carried within the
``service`` parameter to the servers to which the commands are
forwarded:

-  ``dhcp4`` - the command is forwarded to the ``kea-dhcp4`` server.

-  ``dhcp6`` - the command is forwarded to the ``kea-dhcp6`` server.

-  ``d2`` - the command is forwarded to the ``kea-dhcp-ddns`` server.

The server processing the incoming command sends a response of the
form:

::

   {
       "result": 0|1|2|3,
       "text": "textual description",
       "arguments": {
           "argument1": "value1",
           "argument2": "value2",
           ...
       }
   }

``result`` indicates the outcome of the command. A value of 0 means
success, while any non-zero value designates an error or a failure to
complete the requested action. Currently 1 indicates a generic error, 2
means that a command is not supported, and 3 means that the requested
operation was completed, but the requested object was not found. For
example, a well-formed command that requests a subnet that exists in a
server's configuration returns the result 0. If the server encounters an
error condition, it returns 1. If the command asks for the IPv6 subnet,
but was sent to a DHCPv4 server, it returns 2. If the query asks for a
``subnet-id`` and there is no subnet with such an ID, the result is 3.

The ``text`` field typically appears when the result is non-zero and
contains a description of the error encountered, but it often also
appears for successful outcomes. The exact text is command-specific, but
in general uses plain English to describe the outcome of the command.
``arguments`` is a map of additional data values returned by the server
which are specific to the command issued. The map may be present, but
that depends on the specific command.

.. note::

   When sending commands via the Control Agent, it is possible to specify
   multiple services at which the command is targeted. CA forwards this
   command to each service individually. Thus, the CA response to the
   controlling client contains an array of individual responses.

.. note::

   Since Kea 1.9.7, it is possible to put comments in commands as
   in the configuration file. For instance:

::

   {
       "command": "foo",
       // service is a list
       "service": [ "dhcp4" ]
       # command arguments are here.
       "arguments": {
           "param1": "value1"/*,
           "param2": "value2",
           ...*/
       }
   }

.. _ctrl-channel-client:

Using the Control Channel
=========================

The easiest way to start interacting with the control API is to use
common UNIX/Linux tools such as ``socat`` and ``curl``.

In order to control the given Kea service via a UNIX domain socket, use
``socat`` in interactive mode as follows:

.. code-block:: console

   $ socat UNIX:/path/to/the/kea/socket -

or in batch mode, include the "ignoreeof" option as shown below to
ensure ``socat`` waits long enough for the server to respond:

.. code-block:: console

   $ echo "{ some command...}" | socat UNIX:/path/to/the/kea/socket -,ignoreeof

where ``/path/to/the/kea/socket`` is the path specified in the
``Dhcp4/control-socket/socket-name`` parameter in the Kea configuration
file. Text passed to ``socat`` is sent to Kea and the responses received
from Kea are printed to standard output. This approach communicates with
the specific server directly and bypasses the Control Agent.

It is also easy to open a UNIX socket programmatically. An example of a
simple client written in C is available in the Kea Developer's Guide, in
the Control Channel Overview chapter, in the
`Using Control Channel <https://reports.kea.isc.org/dev_guide/d2/d96/ctrlSocket.html#ctrlSocketClient>`__
section.

To use Kea's RESTful API with ``curl``, use the following:

.. code-block:: console

   $ curl -X POST -H "Content-Type: application/json" -d '{ "command": "config-get", "service": [ "dhcp4" ] }' http://ca.example.org:8000/

This assumes that the Control Agent is running on host
``ca.example.org`` and is running the RESTful service on port 8000.

.. _commands-common:

Commands Supported by Both the DHCPv4 and DHCPv6 Servers
========================================================

.. _command-build-report:

The ``build-report`` Command
----------------------------

The ``build-report`` command returns on the control channel what the
command line ``-W`` argument displays, i.e. the embedded content of the
``config.report`` file. This command does not take any parameters.

::

   {
       "command": "build-report"
   }

.. _command-config-get:

The ``config-get`` Command
--------------------------

The ``config-get`` command retrieves the current configuration used by the
server. This command does not take any parameters. The configuration
returned is roughly equal to the configuration that was loaded using the
``-c`` command-line option during server start-up, or was later set using the
``config-set`` command. However, there may be certain differences, as
comments are not retained. If the original configuration used file
inclusion, the returned configuration will include all parameters from
all included files.

.. warning::

   The returned configuration is not redacted, i.e. it
   contains database passwords in plain text, if those were specified in the
   original configuration. Care should be taken not to expose the command
   channel to unprivileged users.

An example command invocation looks like this:

::

   {
       "command": "config-get"
   }

.. _command-config-reload:

The ``config-reload`` Command
-----------------------------

The ``config-reload`` command instructs Kea to load again the
configuration file that was used previously. This operation is useful if
the configuration file has been changed by some external source; for
example, a system administrator can tweak the configuration file and use this
command to force Kea pick up the changes.

Caution should be taken when mixing this with ``config-set`` commands. Kea
remembers the location of the configuration file it was started with,
and this configuration can be significantly changed using the ``config-set``
command. When ``config-reload`` is issued after ``config-set``, Kea attempts
to reload its original configuration from the file, possibly losing all
changes introduced using ``config-set`` or other commands.

``config-reload`` does not take any parameters. An example command
invocation looks like this:

::

   {
       "command": "config-reload"
   }

If the configuration file is incorrect, reloading it can raise an error
which leaves the server in an unusable state. See :ref:`command-config-set`
to learn how to recover from a non-working server.

.. _command-config-test:

The ``config-test`` Command
---------------------------

The ``config-test`` command instructs the server to check whether the new
configuration supplied in the command's arguments can be loaded. The
supplied configuration is expected to be the full configuration for the
target server, along with an optional logger configuration. The configuration
is sanity-checked to the extent possible without the server actually
attempting to load it; it is possible for a configuration which successfully
passes this command to still fail in the ``config-set`` command or at launch
time. The structure of the command is as follows:

::

   {
       "command": "config-test",
       "arguments":  {
           "<server>": {
           }
        }
   }

where <server> is the configuration element name for a given server, such
as "Dhcp4" or "Dhcp6". For example:

::

   {
       "command": "config-test",
       "arguments":  {
           "Dhcp6": {
               :
           }
        }
   }

The server's response contains a numeric code, ``result`` (0 for
success, non-zero on failure), and a string, ``text``, describing the
outcome:

::

       {"result": 0, "text": "Configuration seems sane..." }

       or

       {"result": 1, "text": "unsupported parameter: BOGUS (<string>:16:26)" }

.. _command-config-write:

The ``config-write`` Command
----------------------------

The ``config-write`` command instructs the Kea server to write its current
configuration to a file on disk. It takes one optional argument, called
"filename", that specifies the name of the file to write the
configuration to. If not specified, the name used when starting Kea
(passed as a ``-c`` argument) is used. If a relative path is specified,
Kea writes its files only in the directory where it is running.

An example command invocation looks like this:

::

   {
       "command": "config-write",
       "arguments": {
           "filename": "config-modified-2017-03-15.json"
       }
   }

.. _command-leases-reclaim:

The ``leases-reclaim`` Command
------------------------------

The ``leases-reclaim`` command instructs the server to reclaim all expired
leases immediately. The command has the following JSON syntax:

::

   {
       "command": "leases-reclaim",
       "arguments": {
           "remove": true
       }
   }

The ``remove`` boolean parameter is mandatory and indicates whether the
reclaimed leases should be removed from the lease database (if ``true``), or
left in the ``expired-reclaimed`` state (if ``false``). The latter facilitates
lease affinity, i.e. the ability to re-assign an expired lease to a
returning client that previously used that lease. See :ref:`lease-affinity`
for details. Also, see :ref:`lease-reclamation` for general
information about the processing of expired leases (lease reclamation).

.. _command-libreload:

The ``libreload`` Command
-------------------------

The ``libreload`` command first unloads and then loads all currently
loaded hook libraries. This is primarily intended to allow one or more
hook libraries to be replaced with newer versions, without requiring Kea
servers to be reconfigured or restarted. The hook libraries
are passed the same parameter values (if any) that were passed when they
originally loaded.

::

   {
       "command": "libreload",
       "arguments": { }
   }

The server responds with a result of either 0, indicating success,
or 1, indicating failure.

.. _command-list-commands:

The ``list-commands`` Command
-----------------------------

The ``list-commands`` command retrieves a list of all commands supported
by the server. It does not take any arguments. An example command may
look like this:

::

   {
       "command": "list-commands",
       "arguments": { }
   }

The server responds with a list of all supported commands. The arguments
element is a list of strings, each of which conveys one supported
command.

.. _command-config-set:

The ``config-set`` Command
--------------------------

The ``config-set`` command instructs the server to replace its current
configuration with the new configuration supplied in the command's
arguments. The supplied configuration is expected to be the full
configuration for the target server, along with an optional logger
configuration. While optional, the logger configuration is highly
recommended, as without it the server reverts to its default logging
configuration. The structure of the command is as follows:

::

   {
       "command": "config-set",
       "arguments":  {
           "<server>": {
           }
        }
   }

where <server> is the configuration element name for a given server, such
as "Dhcp4" or "Dhcp6". For example:

::

   {
       "command": "config-set",
       "arguments":  {
           "Dhcp6": {
               :
           }
        }
   }

If the new configuration proves to be invalid, the server retains its
current configuration; however, in some cases a fatal error message is logged
indicating that the server no longer provides any service: a working
configuration must be loaded as soon as possible. If the control channel
is dead, the configuration file can still be reloaded using the ``SIGHUP``
signal. If that is unsuccessful, restart the server.

Please note that the new configuration is
retained in memory only; if the server is restarted or a configuration
reload is triggered via a signal, the server uses the configuration
stored in its configuration file. The server's response contains a
numeric code, ``result`` (0 for success, non-zero on failure), and a
string, ``text``, describing the outcome:

::

       {"result": 0, "text": "Configuration successful." }

       or

       {"result": 1, "text": "unsupported parameter: BOGUS (<string>:16:26)" }

.. _command-shutdown:

The ``shutdown`` Command
------------------------

The ``shutdown`` command instructs the server to initiate its shutdown
procedure. It is the equivalent of sending a ``SIGTERM`` signal to the
process. This command does not take any arguments. An example command
may look like this:

::

   {
       "command": "shutdown"
       "arguments": {
           "exit-value": 3
       }
   }

The server responds with a confirmation that the shutdown procedure has
been initiated.  The optional parameter, ``exit-value``, specifies the
numeric value with which the server process exits to the system.
The default value is zero.

The DDNS daemon supports an extra parameter, ``type``, which controls the way
the process cleans up on exit. The supported shutdown types are:

 -  "normal" - stops the queue manager and finishes all current transactions
    before exiting. This is the default.

 -  "drain_first" - stops the queue manager but continues processing requests
    from the queue until it is empty.

 -  "now" - exits immediately.

An example command may look like this:

::

   {
       "command": "shutdown"
       "arguments": {
           "exit-value": 3,
           "type": "drain_first"
       }
   }

.. _command-dhcp-disable:

The ``dhcp-disable`` Command
----------------------------

The ``dhcp-disable`` command globally disables the DHCP service. The
server continues to operate, but it drops all received DHCP messages.
This command is useful when the server's maintenance requires that the
server temporarily stop allocating new leases and renew existing leases.
It is also useful in failover-like configurations during a
synchronization of the lease databases at startup, or recovery after a
failure. The optional parameter ``max-period`` specifies the time in
seconds after which the DHCP service should be automatically re-enabled,
if the ``dhcp-enable`` command is not sent before this time elapses.

Since Kea 1.9.4, there is an additional ``origin`` parameter that specifies the
command source. A server administrator should typically omit this parameter
because the default value "user" indicates that the administrator sent the
command. This command can also be sent by the partner server running HA hooks
library. In that case, the partner server sets the parameter to "ha-partner".
This value is reserved for the communication between HA partners and should not
be specified in the administrator's commands, as it may interfere with
HA operation. The administrator should either omit this parameter or set it to
"user".

::

   {
       "command": "dhcp-disable",
       "arguments": {
           "max-period": 20,
           "origin": "user"
       }
   }

.. _command-dhcp-enable:

The ``dhcp-enable`` Command
---------------------------

The ``dhcp-enable`` command globally enables the DHCP service.

Since Kea 1.9.4, there is an additional ``origin`` parameter that specifies the
command source. A server administrator should typically omit this parameter
because the default value "user" indicates that the administrator sent the
command. This command can also be sent by the partner server running the HA hook
library. In that case, the partner server sets the parameter to "ha-partner".
This value is reserved for the communication between HA partners and should not
be specified in the administrator's commands, as it may interfere with
HA operation. The administrator should either omit this parameter or set it to
"user".

::

   {
       "command": "dhcp-enable",
       "arguments": {
           "origin": "user"
       }
   }

.. _command-status-get:

The ``status-get`` Command
--------------------------

The ``status-get`` command returns the server's runtime information:

 - ``pid``: the process ID.

 - ``uptime``: the number of seconds since the start of the server.

 - ``reload``: the number of seconds since the last configuration (re)load.

 - ``high-availability``: HA-specific status information about the DHCP servers
   configured to use the HA hook library:

     * ``local``: the state, the role (primary,
       secondary, ...), and the scopes (i.e. what the server is actually
       processing) of the local server.

     * ``remote``: the remote server's last known state, its served
       HA scopes, and the role of the remote server in the HA relationship.

 - ``multi-threading-enabled``: a flag indicating whether multi-threading is enabled.

 - ``thread-pool-size``: the number of DHCP service threads.

 - ``packet-queue-size``: the maximum size of the packet queue. There is one queue,
   regardless of the number of running threads.

 - ``packet-queue-statistics``: the average queue size for the last 10, 100, and 1000
   packets, using an approach similar to the UNIX ``top`` command.
   The average queue size for the last 10 packets can be considered an
   instantaneous value, while the average for the last 1000 packets shows
   a longer-term trend.

The ``high-availability`` information is returned only when the command is
sent to the DHCP servers in an HA setup. This parameter is
never returned when the ``status-get`` command is sent to the
Control Agent or DDNS daemon.

The ``thread-pool-size``, ``packet-queue-size`` and
``packet-queue-statistics`` parameters are returned only when the
command is sent to DHCP servers with multi-threading enabled. These
three parameters and ``multi-threading-enabled`` are never returned when
the ``status-get`` command is sent to the Control Agent or DDNS daemon.

To learn more about the HA status information returned by the
``status-get`` command, please refer to the :ref:`command-ha-status-get`
section.


.. _command-server-tag-get:

The ``server-tag-get`` Command:
-------------------------------

The ``server-tag-get`` command returns the configured server tag of
the DHCPv4 or DHCPv6 server (:ref:`cb-sharing` explains the server tag concept).

.. _command-config-backend-pull:

The ``config-backend-pull`` Command:
------------------------------------

The ``config-backend-pull`` command triggers the polling of configuration backends
(which must be configured for this command to have an effect),
explained in :ref:`dhcp4-cb-json`.

.. _command-version-get:

The ``version-get`` Command
---------------------------

The ``version-get`` command returns extended information about the Kea
version. It is the same information available via the ``-V``
command-line argument. This command does not take any parameters.

::

   {
       "command": "version-get"
   }

Commands Supported by the D2 Server
===================================

The D2 server supports only a subset of the DHCPv4/DHCPv6 server commands:

-  ``build-report``

-  ``config-get``

-  ``config-reload``

-  ``config-set``

-  ``config-test``

-  ``config-write``

-  ``list-commands``

-  ``shutdown``

-  ``status-get``

- ``version-get``

.. _agent-commands:

Commands Supported by the Control Agent
=======================================

The following commands, listed in :ref:`commands-common`, are also supported by the
Control Agent; when the ``service`` parameter is blank, the
commands are handled by the CA and they relate to the CA process itself:

-  ``build-report``

-  ``config-get``

-  ``config-reload``

-  ``config-set``

-  ``config-test``

-  ``config-write``

-  ``list-commands``

-  ``shutdown``

-  ``status-get``

-  ``version-get``
