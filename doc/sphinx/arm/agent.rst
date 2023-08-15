.. _kea-ctrl-agent:

*********************
The Kea Control Agent
*********************

.. _agent-overview:

Overview of the Kea Control Agent
=================================

The Kea Control Agent (CA) is a daemon which exposes a RESTful control
interface for managing Kea servers. The daemon can receive control
commands over HTTP and either forward these commands to the respective
Kea servers or handle these commands on its own. The determination
whether the command should be handled by the CA or forwarded is made by
checking the value of the ``service`` parameter, which may be included in
the command from the controlling client. The details of the supported
commands, as well as their structures, are provided in
:ref:`ctrl-channel`.

The CA can use hook libraries to provide support for additional commands
or to program custom behavior of existing commands. Such hook libraries must
implement callouts for the ``control_command_receive`` hook point. Details
about creating new hook libraries and supported hook points can be found
in the `Kea Developer's
Guide <https://reports.kea.isc.org/dev_guide/>`__.

The CA processes received commands according to the following algorithm:

-  Pass command into any installed hooks (regardless of service
   value(s)). If the command is handled by a hook, return the response.

-  If the service specifies one or more services, forward the command to
   the specified services and return the accumulated responses.

-  If the service is not specified or is an empty list, handle the
   command if the CA supports it.

.. _agent-configuration:

Configuration
=============

The following example demonstrates the basic CA configuration.

.. code-block:: json

   {
       "Control-agent": {
           "http-host": "10.20.30.40",
           "http-port": 8000,
           "trust-anchor": "/path/to/the/ca-cert.pem",
           "cert-file": "/path/to/the/agent-cert.pem",
           "key-file": "/path/to/the/agent-key.pem",
           "cert-required": true,
           "authentication": {
               "type": "basic",
               "realm": "kea-control-agent",
               "clients": [
               {
                   "user": "admin",
                   "password": "1234"
               } ]
           },

           "control-sockets": {
               "dhcp4": {
                   "comment": "main server",
                   "socket-type": "unix",
                   "socket-name": "/path/to/the/unix/socket-v4"
               },
               "dhcp6": {
                   "socket-type": "unix",
                   "socket-name": "/path/to/the/unix/socket-v6",
                   "user-context": { "version": 3 }
               },
               "d2": {
                   "socket-type": "unix",
                   "socket-name": "/path/to/the/unix/socket-d2"
               }
           },

           "hooks-libraries": [
           {
               "library": "/opt/local/custom_hooks_example.so",
               "parameters": {
                   "param1": "foo"
               }
           } ],

           "loggers": [ {
               "name": "kea-ctrl-agent",
               "severity": "INFO"
           } ]
       }
   }

The ``http-host`` and ``http-port`` parameters specify an IP address and
port to which HTTP service will be bound. In the example configuration
provided above, the RESTful service will be available at the URL
``https://10.20.30.40:8000/``. If these parameters are not specified, the
default URL is ``http://127.0.0.1:8000/``.

When using Kea's HA hook library with multi-threading,
the address:port combination used for CA must be
different from the HA peer URLs, which are strictly
for internal HA traffic between the peers. User commands should
still be sent via the CA.

The ``trust-anchor``, ``cert-file``, ``key-file``, and ``cert-required``
parameters specify the TLS setup for HTTP, i.e. HTTPS. If these parameters
are not specified, HTTP is used. The TLS/HTTPS support in Kea is
described in :ref:`tls`.

As mentioned in :ref:`agent-overview`, the CA can forward
received commands to the Kea servers for processing. For example,
:isccmd:`config-get` is sent to retrieve the configuration of one of the Kea
services. When the CA receives this command, including a ``service``
parameter indicating that the client wishes to retrieve the
configuration of the DHCPv4 server, the CA forwards the command to that
server and passes the received response back to the client. More about
the ``service`` parameter and the general structure of commands can be
found in :ref:`ctrl-channel`.

The CA uses UNIX domain sockets to forward control commands and receive
responses from other Kea services. The ``dhcp4``, ``dhcp6``, and ``d2``
maps specify the files to which UNIX domain sockets are bound. In the
configuration above, the CA connects to the DHCPv4 server via
``/path/to/the/unix/socket-v4`` to forward the commands to it.
Obviously, the DHCPv4 server must be configured to listen to connections
via this same socket. In other words, the command-socket configuration
for the DHCPv4 server and the CA (for that server) must match. Consult
:ref:`dhcp4-ctrl-channel`, :ref:`dhcp6-ctrl-channel`, and
:ref:`d2-ctrl-channel` to learn how the socket configuration is
specified for the DHCPv4, DHCPv6, and D2 services.

User contexts can store arbitrary data as long as they are in valid JSON
syntax and their top-level element is a map (i.e. the data must be
enclosed in curly brackets). Some hook libraries may expect specific
formatting; please consult the relevant hook library documentation for
details.

User contexts can be specified on either global scope, control socket,
basic authentication, or loggers. One other useful feature is the
ability to store comments or descriptions; the parser translates a
"comment" entry into a user context with the entry, which allows a
comment to be attached within the configuration itself.

Basic HTTP authentication protects
against unauthorized uses of the control agent by local users. For
protection against remote attackers, HTTPS and reverse proxy of
:ref:`agent-secure-connection` provide stronger security.

The authentication is described in the ``authentication`` block
with the mandatory ``type`` parameter, which selects the authentication.
Currently only the basic HTTP authentication (type basic) is supported.

The ``realm`` authentication parameter is used for error messages when
the basic HTTP authentication is required but the client is not
authorized.

When the ``clients`` authentication list is configured and not empty,
basic HTTP authentication is required. Each element of the list
specifies a user ID and a password. The user ID is mandatory, must
be not empty, and must not contain the colon (:) character. The
password is optional; when it is not specified an empty password
is used.

.. note::

   The basic HTTP authentication user ID and password are encoded
   in UTF-8, but the current Kea JSON syntax only supports the Latin-1
   (i.e. 0x00..0xff) Unicode subset.

To avoid exposing the user ID and/or the associated
password, these values can be read from files. The syntax is extended by:

-  The ``directory`` authentication parameter, which handles the common
   part of file paths. The default value is the empty string.

-  The ``password-file`` client parameter, which, alongside the ``directory``
   parameter, specifies the path of a file that can contain the password,
   or when no user ID is given, the whole basic HTTP authentication secret.

-  The ``user-file`` client parameter, which, with the ``directory`` parameter,
   specifies the path of a file where the user ID can be read.

When files are used, they are read when the configuration is loaded,
to detect configuration errors as soon as possible.

Hook libraries can be loaded by :iscman:`kea-ctrl-agent` in the same way as
they are loaded by :iscman:`kea-dhcp4` and :iscman:`kea-dhcp6`. The CA currently
supports one hook point - ``control_command_receive`` - which makes it
possible to delegate the processing of some commands to the hook library.
The ``hooks-libraries`` list contains the list of hook libraries that
should be loaded by :iscman:`kea-ctrl-agent`, along with their configuration information
specified with ``parameters``.

Please consult :ref:`logging` for the details on how to configure
logging. The CA's root logger's name is :iscman:`kea-ctrl-agent`, as given in
the example above.

.. _agent-secure-connection:

Secure Connections
==================

The Kea Control Agent natively supports secure
HTTP connections using TLS. This allows protection against users from
the node where the agent runs, something that a reverse proxy cannot
provide. More about TLS/HTTPS support in Kea can be found in :ref:`tls`.

TLS is configured using three string parameters with file names, and
a boolean parameter:

-  The ``trust-anchor`` specifies the Certification Authority file name or
   directory path.

-  The ``cert-file`` specifies the server certificate file name.

-  The ``key-file`` specifies the private key file name. The file must not
   be encrypted.

-  The ``cert-required`` specifies whether client certificates are required
   or optional. The default is to require them and to perform mutual
   authentication.

The file format is PEM. Either all the string parameters are specified and
HTTP over TLS (HTTPS) is used, or none is specified and plain HTTP is used.
Configuring only one or two string parameters results in an error.

.. note::

   When client certificates are not required, only the server side is
   authenticated, i.e. the communication is encrypted with an unknown
   client. This protects only against passive attacks; active
   attacks, such as "man-in-the-middle," are still possible.

.. note::

   No standard HTTP authentication scheme cryptographically binds its end
   entity with TLS. This means that the TLS client and server can be
   mutually authenticated, but there is no proof they are the same as
   for the HTTP authentication.

The :iscman:`kea-shell` tool also supports TLS.

.. _agent-launch:

Starting and Stopping the Control Agent
=======================================

:iscman:`kea-ctrl-agent` accepts the following command-line switches:

-  ``-c file`` - specifies the configuration file.

-  ``-d`` - specifies whether the agent logging should be switched to
   debug/verbose mode. In verbose mode, the logging severity and
   debuglevel specified in the configuration file are ignored and
   "debug" severity and the maximum debuglevel (99) are assumed. The
   flag is convenient for temporarily switching the server into maximum
   verbosity, e.g. when debugging.

-  ``-t file`` - specifies the configuration file to be tested.
   :iscman:`kea-netconf` attempts to load it and conducts sanity checks;
   certain checks are possible only while running the actual server. The
   actual status is reported with exit code (0 = configuration appears valid,
   1 = error encountered). Kea prints out log messages to standard
   output and error to standard error when testing the configuration.

-  ``-v`` - displays the version of :iscman:`kea-ctrl-agent` and exits.

-  ``-V`` - displays the extended version information for :iscman:`kea-ctrl-agent`
   and exits. The listing includes the versions of the libraries
   dynamically linked to Kea.

-  ``-W`` - displays the Kea configuration report and exits. The report
   is a copy of the ``config.report`` file produced by ``./configure``;
   it is embedded in the executable binary.

   The contents of the ``config.report`` file may also be accessed by examining
   certain libraries in the installation tree or in the source tree.

   .. code-block:: shell

    # from installation using libkea-process.so
    $ strings ${prefix}/lib/libkea-process.so | sed -n 's/;;;; //p'

    # from sources using libkea-process.so
    $ strings src/lib/process/.libs/libkea-process.so | sed -n 's/;;;; //p'

    # from sources using libkea-process.a
    $ strings src/lib/process/.libs/libkea-process.a | sed -n 's/;;;; //p'

    # from sources using libcfgrpt.a
    $ strings src/lib/process/cfgrpt/.libs/libcfgrpt.a | sed -n 's/;;;; //p'

The CA is started by running its binary and specifying the configuration
file it should use. For example:

.. code-block:: console

   $ ./kea-ctrl-agent -c /usr/local/etc/kea/kea-ctrl-agent.conf

It can be started by :iscman:`keactrl` as well (see :ref:`keactrl`).

.. _agent-clients:

Connecting to the Control Agent
===============================

For an example of a tool that can take advantage of the RESTful API, see
:ref:`kea-shell`.
