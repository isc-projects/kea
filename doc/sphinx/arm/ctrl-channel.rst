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
Therefore, Kea includes a component called the Control Agent (or CA), which
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
will assume that the control command is targeted at the CA itself and
will try to handle it on its own.

Control connections over both HTTP and UNIX domain sockets are guarded
with timeouts. The default timeout value is set to 10 seconds and is not
configurable.

.. _ctrl-channel-syntax:

Data Syntax
===========

Communication over the control channel is conducted using JSON
structures. If configured, Kea will open a socket and listen for
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

The same command sent over the RESTful interface to the CA will have the
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
DHCPv4 server. In most cases, the CA will simply forward this command to
the DHCPv4 server for processing via a UNIX domain socket. Sometimes,
the command including a service value may also be processed by the CA,
if the CA is running a hooks library which handles such a command for
the given server. As an example, the hooks library loaded by the CA may
perform some operations on the database, such as adding host
reservations, modifying leases, etc. An advantage of performing
DHCPv4-specific administrative operations in the CA, rather than
forwarding it to the DHCPv4 server, is the ability to perform these
operations without disrupting the DHCPv4 service, since the DHCPv4
server doesn't have to stop processing DHCP messages to apply changes to
the database. Nevertheless, these situations are rather rare and, in
most cases, when the ``service`` parameter contains a name of the
service the commands are simply forwarded by the CA. The forwarded
command includes the ``service`` parameter but this parameter is ignored
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

-  ``d2`` - the command is forwarded to the ``kea-d2`` server.

The server processing the incoming command will send a response of the
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
subnet-id and there is no subnet with such an id, the result is 3.

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
`Using Control Channel <https://jenkins.isc.org/job/Kea_doc/doxygen/d2/d96/ctrlSocket.html#ctrlSocketClient>`__
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

The build-report Command
------------------------

The ``build-report`` command returns on the control channel what the
command line ``-W`` argument displays, i.e. the embedded content of the
``config.report`` file. This command does not take any parameters.

::

   {
       "command": "build-report"
   }

.. _command-config-get:

The config-get Command
----------------------

The ``config-get`` command retrieves the current configuration used by the
server. This command does not take any parameters. The configuration
returned is roughly equal to the configuration that was loaded using the
-c command line option during server start-up or later set using the
``config-set`` command. However, there may be certain differences, as
comments are not retained. If the original configuration used file
inclusion, the returned configuration will include all parameters from
all the included files.

Note that the returned configuration is not redacted, i.e. it will
contain database passwords in plain text if those were specified in the
original configuration. Care should be taken not to expose the command
channel to unprivileged users.

An example command invocation looks like this:

::

   {
       "command": "config-get"
   }

.. _command-config-reload:

The config-reload Command
-------------------------

The ``config-reload`` command instructs Kea to load again the
configuration file that was used previously. This operation is useful if
the configuration file has been changed by some external source; for
example, a sysadmin can tweak the configuration file and use this
command to force Kea pick up the changes.

Caution should be taken when mixing this with ``config-set`` commands. Kea
remembers the location of the configuration file it was started with,
and this configuration can be significantly changed using the ``config-set``
command. When ``config-reload`` is issued after ``config-set``, Kea will attempt
to reload its original configuration from the file, possibly losing all
changes introduced using ``config-set`` or other commands.

``config-reload`` does not take any parameters. An example command
invocation looks like this:

::

   {
       "command": "config-reload"
   }

.. _command-config-test:

The config-test Command
-----------------------

The ``config-test`` command instructs the server to check whether the new
configuration supplied in the command's arguments can be loaded. The
supplied configuration is expected to be the full configuration for the
target server, along with an optional Logger configuration. As for the
``-t`` command, some sanity checks are not performed, so it is possible a
configuration which successfully passes this command will still fail in
the ``config-set`` command or at launch time. The structure of the
command is as follows:

::

   {
       "command": "config-test",
       "arguments":  {
           "<server>": {
           }
        }
   }

where <server> is the configuration element name for a given server such
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

The server's response will contain a numeric code, "result" (0 for
success, non-zero on failure), and a string, "text", describing the
outcome:

::

       {"result": 0, "text": "Configuration seems sane..." }

       or

       {"result": 1, "text": "unsupported parameter: BOGUS (<string>:16:26)" }

.. _command-config-write:

The config-write Command
------------------------

The ``config-write`` command instructs the Kea server to write its current
configuration to a file on disk. It takes one optional argument, called
"filename", that specifies the name of the file to write the
configuration to. If not specified, the name used when starting Kea
(passed as a -c argument) will be used. If a relative path is specified,
Kea will write its files only in the directory it is running.

An example command invocation looks like this:

::

   {
       "command": "config-write",
       "arguments": {
           "filename": "config-modified-2017-03-15.json"
       }
   }

.. _command-leases-reclaim:

The leases-reclaim Command
--------------------------

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
reclaimed leases should be removed from the lease database (if true), or
left in the "expired-reclaimed" state (if false). The latter facilitates
lease affinity, i.e. the ability to re-assign an expired lease to the
same client that used this lease before. See :ref:`lease-affinity`
for the details. Also, see :ref:`lease-reclamation` for general
information about the processing of expired leases (lease reclamation).

.. _command-libreload:

The libreload Command
---------------------

The ``libreload`` command first unloads and then loads all currently
loaded hooks libraries. This is primarily intended to allow one or more
hooks libraries to be replaced with newer versions without requiring Kea
servers to be reconfigured or restarted. Note that the hooks libraries
are passed the same parameter values (if any) that were passed when they
originally loaded.

::

   {
       "command": "libreload",
       "arguments": { }
   }

The server will respond with a result of either 0, indicating success,
or 1, indicating failure.

.. _command-list-commands:

The list-commands Command
-------------------------

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

The config-set Command
----------------------

The ``config-set`` command instructs the server to replace its current
configuration with the new configuration supplied in the command's
arguments. The supplied configuration is expected to be the full
configuration for the target server, along with an optional Logger
configuration. While optional, the Logger configuration is highly
recommended, as without it the server will revert to its default logging
configuration. The structure of the command is as follows:

::

   {
       "command": "config-set",
       "arguments":  {
           "<server>": {
           }
        }
   }

where <server> is the configuration element name for a given server such
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
current configuration. Please note that the new configuration is
retained in memory only; if the server is restarted or a configuration
reload is triggered via a signal, the server uses the configuration
stored in its configuration file. The server's response contains a
numeric code, "result" (0 for success, non-zero on failure), and a
string, "text", describing the outcome:

::

       {"result": 0, "text": "Configuration successful." }

       or

       {"result": 1, "text": "unsupported parameter: BOGUS (<string>:16:26)" }

.. _command-shutdown:

The shutdown Command
--------------------

The ``shutdown`` command instructs the server to initiate its shutdown
procedure. It is the equivalent of sending a SIGTERM signal to the
process. This command does not take any arguments. An example command
may look like this:

::

   {
       "command": "shutdown"
   }

The server responds with a confirmation that the shutdown procedure has
been initiated.

.. _command-dhcp-disable:

The dhcp-disable Command
------------------------

The ``dhcp-disable`` command globally disables the DHCP service. The
server continues to operate, but it drops all received DHCP messages.
This command is useful when the server's maintenance requires that the
server temporarily stop allocating new leases and renew existing leases.
It is also useful in failover-like configurations during a
synchronization of the lease databases at startup, or recovery after a
failure. The optional parameter "max-period" specifies the time in
seconds after which the DHCP service should be automatically re-enabled,
if the ``dhcp-enable`` command is not sent before this time elapses.

::

   {
       "command": "dhcp-disable",
       "arguments": {
           "max-period": 20
       }
   }

.. _command-dhcp-enable:

The dhcp-enable Command
-----------------------

The ``dhcp-enable`` command globally enables the DHCP service.

::

   {
       "command": "dhcp-enable"
   }

.. _command-status-get:

The status-get Command
----------------------

The ``status-get`` command returns server's runtime information:

 - pid: process id.

 - uptime: number of seconds since the start of the server.

 - reload: number of seconds since the last configuration (re)load.

 - ha-servers: HA specific status information about the DHCP servers
   configured to use HA hooks library:

     * local: for the local server the state, the role (primary,
       secondary, ...) and scopes (i.e. what the server is actually
       processing).

     * remote: for the remote server the last known state, served
       HA scopes and the role of the server in HA relationship.

The ``ha-servers`` information is only returned when the command is
sent to the DHCP servers being in the HA setup. This parameter is
never returned when the ``status-get`` command is sent to the
Control Agent or DDNS deamon.

To learn more about the HA status information returned by the
``status-get`` command please refer to the the :ref:`command-ha-status-get`
section.


.. _command-server-tag-get:

The server-tag-get Command:
---------------------------

The ``server-tag-get`` command returns the configured server tag of
the DHCPv4 or DHCPv6 server (:ref:`cb-sharing` explains the server tag concept)

.. _command-config-backend-pull:

The config-backend-pull Command:
--------------------------------

The ``config-backend-pull`` command triggers the polling of Config Backends
(which should be configured for this command to do something)
explained in :ref:`dhcp4-cb-json`.

.. _command-version-get:

The version-get Command
-----------------------

The ``version-get`` command returns extended information about the Kea
version. It is the same information available via the ``-V``
command-line argument. This command does not take any parameters.

::

   {
       "command": "version-get"
   }

Commands Supported by the D2 Server
===================================

The D2 server supports only a subset of DHCPv4 / DHCPv6 server commands:

-  build-report

-  config-get

-  config-reload

-  config-set

-  config-test

-  config-write

-  list-commands

-  shutdown

-  status-get

-  version-get

.. _agent-commands:

Commands Supported by the Control Agent
=======================================

The following commands listed in :ref:`commands-common` are also supported by the
Control Agent, i.e. when the ``service`` parameter is blank, the
commands are handled by the CA and they relate to the CA process itself:

-  build-report

-  config-get

-  config-reload

-  config-set

-  config-test

-  config-write

-  list-commands

-  shutdown

-  status-get

-  version-get
