.. _kea-shell:

*************
The Kea Shell
*************

.. _shell-overview:

Overview of the Kea Shell
=========================

The Kea Control Agent (CA, see
:ref:`kea-ctrl-agent`) provides a RESTful control interface
over HTTP. That API is typically expected to be used by various IPAMs
and similar management systems. Nevertheless, there may be cases when an
administrator wants to send a command to the CA directly, and the Kea shell
provides a way to do this. It is a simple command-line,
scripting-friendly, text client that is able to connect to the CA, send
it commands with parameters, retrieve the responses, and display them.

As the primary purpose of the Kea shell is as a tool in a scripting
environment, it is not interactive. However, by following simple guidelines it can
be run manually.

Kea 1.9.0 introduced basic HTTP authentication support.

Shell Usage
===========

``kea-shell`` is run as follows:

.. code-block:: console

   $ kea-shell [--host hostname] [--port number] [--path path] [--auth-user] [--auth-password] [--timeout seconds] [--service service-name] [command]

where:

-  ``--host hostname`` specifies the hostname of the CA. If not
   specified, "localhost" is used.

-  ``--port number`` specifies the TCP port on which the CA listens. If
   not specified, 8000 is used.

-  ``--path path`` specifies the path in the URL to connect to. If not
   specified, an empty path is used. As the CA listens at the empty
   path, this parameter is useful only with a reverse proxy.

-  ``--auth-user`` specifies the user ID for basic HTTP authentication.
   If not specified or specified as the empty string, authentication is
   not used.

-  ``--auth-password`` specifies the password for basic HTTP authentication.
   If not specified but the user ID is specified, an empty password is used.

-  ``--timeout seconds`` specifies the timeout (in seconds) for the
   connection. If not given, 10 seconds is used.

-  ``--service service-name`` specifies the target of a command. If not
   given, the CA is used as the target. This may be used more than once
   to specify multiple targets.

-  ``command`` specifies the command to be sent. If not specified, the
   ``list-commands`` command is used.

Other switches are:

-  ``-h`` - prints a help message.

-  ``-v`` - prints the software version.

See :ref:`shell-tls` for new command-line arguments associated with TLS/HTTPS support.

Once started, the shell reads the parameters for the command from standard
input, which are expected to be in JSON format. When all have been read,
the shell establishes a connection with the CA using HTTP, sends the
command, and awaits a response. Once that is received, it is displayed
on standard output.

For a list of available commands, see :ref:`ctrl-channel`;
additional commands may be provided by hook libraries. For a list of
all supported commands from the CA, use the ``list-commands`` command.

The following shows a simple example of usage:

.. code-block:: console

   $ kea-shell --host 192.0.2.1 --port 8001 --service dhcp4 list-commands
   ^D

After the command line is entered, the program waits for command
parameters to be entered. Since ``list-commands`` does not take any
arguments, Ctrl-D (represented in the above example by "^D")
indicates end-of-file and terminates the parameter input. The shell
then contacts the CA and prints out the list of available commands
returned for the service named ``dhcp4``.

The Kea shell will likely be most frequently used in
scripts; the next example shows a simple scripted execution. It sends
the command ``config-write`` to the CA (the ``--service`` parameter has not
been used), along with the parameters specified in param.json. The
result will be stored in result.json.

.. code-block:: console

   $ cat param.json
   "filename": "my-config-file.json"
   $ cat param.json | kea-shell --host 192.0.2.1 config-write > result.json

When a reverse proxy is used to de-multiplex requests to different
servers, the default empty path in the URL is not enough, so the
``--path`` parameter should be used. For instance, if requests to the
"/kea" path are forwarded to the CA this can be used:

.. code-block:: console

   $ kea-shell --host 192.0.2.1 --port 8001 --path kea ...

The Kea shell requires Python to be installed on the system. It has been
tested with Python 2.7 and various versions of Python 3, up to 3.5.
Since not every Kea deployment uses this feature and there are
deployments that do not have Python, the Kea shell is not enabled by
default. To use it, specify ``--enable-shell`` when running ``configure``
during the installation of Kea. When building on Debian systems,
``--with-site-packages=...`` may also be useful.

The Kea shell is intended to serve more as a demonstration of the
RESTful interface's capabilities (and, perhaps, an illustration for
people interested in integrating their management environments with Kea)
than as a serious management client. It is not likely to be
significantly expanded in the future; it is, and will remain, a simple
tool.

.. note::

   When using this tool with basic HTTP authentication, please keep in
   mind that command-line arguments are not hidden from local users.

.. _shell-tls:

TLS Support
===========

Since Kea 1.9.6, ``kea-shell`` supports HTTPS connections. The TLS/HTTPS
support requires Python 3. The additional command-line arguments are:

-  ``--ca`` specifies the file or directory name of the Certification
   Authority. If not specified, HTTPS is not used.

-  ``--cert`` specifies the file name of the user end-entity public key
   certificate. If specified, the file name of the user key must also be specified.

-  ``--key`` specifies the file name of the user key file. If specified,
   the file name of the user certificate must also be specified.
   Encrypted key files are not supported.

For example, a basic HTTPS request to get a list of commands could
look like this:

.. code-block:: console

   $ kea-shell --host 127.0.0.1 --port 8000 --ca ./kea-ca.crt list-commands
