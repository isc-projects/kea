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

::

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
               },
           },

           "hooks-libraries": [
           {
               "library": "/opt/local/control-agent-commands.so",
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

When using Kea's HA hook library with multi-threading, make sure
that the address:port combination used for CA is
different from the HA peer URLs, which are strictly
for internal HA traffic between the peers. User commands should
still be sent via CA.

The ``trust-anchor``, ``cert-file``, ``key-file``, and ``cert-required``
parameters specify the TLS setup for HTTP, i.e. HTTPS. If these parameters
are not specified, HTTP is used. The TLS/HTTPS support in Kea is
described in :ref:`tls`.

As mentioned in :ref:`agent-overview`, the CA can forward
received commands to the Kea servers for processing. For example,
``config-get`` is sent to retrieve the configuration of one of the Kea
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

Basic HTTP authentication was added in Kea 1.9.0; it protects
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

To avoid to expose the password or both the user ID and the associated
password these values can be read from files. The syntax was extended by:

-  The ``directory`` authentication parameter which handles the common
   part of file paths. By default the value is the empty string.

-  The``password-file`` client parameter which with the ``directory``
   parameter specifies the path of a file where the password or when no
   user ID is given the whole basic HTTP authentication secret before
   encoding can be read.

-  The ``user-file`` client parameter which with the ``directory`` parameter
   specifies the path of a file where the user ID can be read.

When files are used they are read when the configuration is loaded in order
to detect configuration errors as soon as possible.

Hook libraries can be loaded by the Control Agent in the same way as
they are loaded by the DHCPv4 and DHCPv6 servers. The CA currently
supports one hook point - ``control_command_receive`` - which makes it
possible to delegate processing of some commands to the hook library.
The ``hooks-libraries`` list contains the list of hook libraries that
should be loaded by the CA, along with their configuration information
specified with ``parameters``.

Please consult :ref:`logging` for the details on how to configure
logging. The CA's root logger's name is ``kea-ctrl-agent``, as given in
the example above.

.. _agent-secure-connection:

Secure Connections (in Versions Prior to Kea 1.9.6)
===================================================

The Control Agent does not natively support secure HTTP connections, like
SSL or TLS, before Kea 1.9.6.

To set up a secure connection, please use one of the
available third-party HTTP servers and configure it to run as a reverse
proxy to the Control Agent. Kea has been tested with two major HTTP
server implementations working as a reverse proxy: Apache2 and nginx.
Example configurations, including extensive comments, are provided in
the ``doc/examples/https/`` directory.

The reverse proxy forwards HTTP requests received over a secure
connection to the Control Agent using unsecured HTTP. Typically, the
reverse proxy and the Control Agent are running on the same machine, but
it is possible to configure them to run on separate machines as well. In
this case, security depends on the protection of the communications
between the reverse proxy and the Control Agent.

Apart from providing the encryption layer for the control channel, a
reverse proxy server is also often used for authentication of the
controlling clients. In this case, the client must present a valid
certificate when it connects via reverse proxy. The proxy server
authenticates the client by checking whether the presented certificate
is signed by the certificate authority used by the server.

To illustrate this, the following is a sample configuration for the
nginx server running as a reverse proxy to the Kea Control Agent. The
server enables authentication of the clients using certificates.

::

   #   The server certificate and key can be generated as follows:
   #
   #   openssl genrsa -des3 -out kea-proxy.key 4096
   #   openssl req -new -x509 -days 365 -key kea-proxy.key -out kea-proxy.crt
   #
   #   The CA certificate and key can be generated as follows:
   #
   #   openssl genrsa -des3 -out ca.key 4096
   #   openssl req -new -x509 -days 365 -key ca.key -out ca.crt
   #
   #
   #   The client certificate needs to be generated and signed:
   #
   #   openssl genrsa -des3 -out kea-client.key 4096
   #   openssl req -new -key kea-client.key -out kea-client.csr
   #   openssl x509 -req -days 365 -in kea-client.csr -CA ca.crt \
   #           -CAkey ca.key -set_serial 01 -out kea-client.crt
   #
   #   Note that the "common name" value used when generating the client
   #   and the server certificates must differ from the value used
   #   for the CA certificate.
   #
   #   The client certificate must be deployed on the client system.
   #   In order to test the proxy configuration with "curl", run a
   #   command similar to the following:
   #
   #   curl -k --key kea-client.key --cert kea-client.crt -X POST \
   #        -H Content-Type:application/json -d '{ "command": "list-commands" }' \
   #         https://kea.example.org/kea
   #
   #   curl syntax for basic authentication is -u user:password
   #
   #
   #   nginx configuration starts here.

   events {
   }

   http {
           #   HTTPS server
       server {
           #     Use default HTTPS port.
           listen 443 ssl;
           #     Set server name.
           server_name kea.example.org;

           #   Server certificate and key.
           ssl_certificate /path/to/kea-proxy.crt;
           ssl_certificate_key /path/to/kea-proxy.key;

           #   Certificate Authority. Client certificates must be signed by the CA.
           ssl_client_certificate /path/to/ca.crt;

           # Enable verification of the client certificate.
           ssl_verify_client on;

           # For URLs such as https://kea.example.org/kea, forward the
           # requests to http://127.0.0.1:8000.
           location /kea {
               proxy_pass http://127.0.0.1:8000;
           }
       }
   }

.. note::

   The configuration snippet provided above is for testing
   purposes only. It should be modified according to the security
   policies and best practices of the administrator's organization.

When using an HTTP client without TLS support, such as ``kea-shell``, it
is possible to use an HTTP/HTTPS translator such as ``stunnel`` in client mode. A
sample configuration is provided in the ``doc/examples/https/shell/``
directory.

Secure Connections (in Kea 1.9.6 and Newer)
===========================================

Since Kea 1.9.6, the Control Agent natively supports secure
HTTP connections using TLS. This allows protection against users from
the node where the agent runs, something that a reverse proxy cannot
provide. More about TLS/HTTPS support in Kea can be found in :ref:`tls`.

TLS is configured using three string parameters, giving file names and
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

Since Kea 1.9.6, the ``kea-shell`` tool supports TLS.

.. _agent-launch:

Starting the Control Agent
==========================

The CA is started by running its binary and specifying the configuration
file it should use. For example:

.. code-block:: console

   $ ./kea-ctrl-agent -c /usr/local/etc/kea/kea-ctrl-agent.conf

It can be started by ``keactrl`` as well (see :ref:`keactrl`).

.. _agent-clients:

Connecting to the Control Agent
===============================

For an example of a tool that can take advantage of the RESTful API, see
:ref:`kea-shell`.
