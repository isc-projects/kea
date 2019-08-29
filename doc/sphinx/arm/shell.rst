.. _kea-shell:

*************
The Kea Shell
*************

.. _shell-overview:

Overview of the Kea Shell
=========================

Kea 1.2.0 introduced the Control Agent (CA, see
:ref:`kea-ctrl-agent`), which provides a RESTful control interface
over HTTP. That API is typically expected to be used by various IPAMs
and similar management systems. Nevertheless, there may be cases when an
administrator wants to send a command to the CA directly, and the Kea shell
provides a way to do this. It is a simple command-line,
scripting-friendly, text client that is able to connect to the CA, send
it commands with parameters, retrieve the responses, and display them.

As the primary purpose of the Kea shell is as a tool in a scripting
environment, it is not interactive. However, following simple guidelines it can
be run manually.

Shell Usage
===========

``kea-shell`` is run as follows:

.. code-block:: console

   $ kea-shell [--host hostname] [--port number] [--path path] [--timeout seconds] [--service service-name] [command]

where:

-  ``--host hostname`` specifies the hostname of the CA. If not
   specified, "localhost" is used.

-  ``--port number`` specifies the TCP port on which the CA listens. If
   not specified, 8000 is used.

-  ``--path path`` specifies the path in the URL to connect to. If not
   specified, an empty path is used. As the CA listens at the empty
   path, this parameter is useful only with a reverse proxy.

-  ``--timeout seconds`` specifies the timeout (in seconds) for the
   connection. If not given, 10 seconds is used.

-  ``--service service-name`` specifies the target of a command. If not
   given, the CA will be used as the target. May be used more than once
   to specify multiple targets.

-  ``command`` specifies the command to be sent. If not specified, the
   ``list-commands`` command is used.

Other switches are:

-  ``-h`` - prints a help message.

-  ``-v`` - prints the software version.

Once started, the shell reads parameters for the command from standard
input, which are expected to be in JSON format. When all have been read,
the shell establishes a connection with the CA using HTTP, sends the
command, and awaits a response. Once that is received, it is displayed
on standard output.

For a list of available commands, see :ref:`ctrl-channel`;
additional commands may be provided by hooks libraries. For a list of
all supported commands from the CA, use the ``list-commands`` command.

The following shows a simple example of usage:

.. code-block:: console

   $ kea-shell --host 192.0.2.1 --port 8001 --service dhcp4 list-commands
   ^D

After the command line is entered, the program waits for command
parameters to be entered. Since ``list-commands`` does not take any
arguments, CTRL-D (represented in the above example by "^D") is pressed
to indicate end-of-file and terminate the parameter input. The shell
then contacts the CA and prints out the list of available commands
returned for the service named ``dhcp4``.

It is envisaged that the Kea shell will be most frequently used in
scripts; the next example shows a simple scripted execution. It sends
the command "config-write" to the CA (the ``--service`` parameter has not
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

The Kea shell requires Python to to be installed on the system. It has been
tested with Python 2.7 and various versions of Python 3, up to 3.5.
Since not every Kea deployment uses this feature and there are
deployments that do not have Python, the Kea shell is not enabled by
default. To use it, specify ``--enable-shell`` when running "configure"
during the installation of Kea. When building on Debian systems, also
``--with-site-packages=...`` may be useful.

The Kea shell is intended to serve more as a demonstration of the
RESTful interface's capabilities (and, perhaps, an illustration for
people interested in integrating their management environments with Kea)
than as a serious management client. It is not likely to be
significantly expanded in the future; it is, and will remain, a simple
tool.
