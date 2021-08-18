.. _netconf:

YANG/NETCONF
============

.. _netconf-overview:

Overview
--------

The Network Configuration Protocol, or NETCONF, is a network management protocol defined
in `RFC 4741 <https://tools.ietf.org/html/rfc4741>`__. It uses YANG modeling language,
defined in `RFC 6020 <https://tools.ietf.org/html/rfc6020>`__, to provide a uniform way
of handling configuration syntax of varied networking devices. Kea provides optional
support for a YANG/NETCONF interface with the ``kea-netconf`` agent.

.. _netconf-install:

Installing NETCONF
------------------

To get its NETCONF capabilities, Kea uses libyang v1.0.240 and sysrepo v1.4.140.
Use packages if they are provided on your system. There is always the
alternative method of building from sources which should work on all popular
OSs:

.. _libyang-install-sources:

Installing libyang From Sources
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: console

    $ git clone https://github.com/CESNET/libyang.git
    $ cd libyang
    $ git checkout v1.0.240
    $ mkdir build
    $ cd build
    $ cmake .. -DGEN_CPP_BINDINGS=ON -DGEN_LANGUAGE_BINDINGS=ON -DGEN_PYTHON_BINDINGS=OFF
    $ make
    $ make install  # without sudo if you're doing development and want to run unit tests

.. _sysrepo-install-sources:

Installing sysrepo From Sources
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: console

    $ git clone https://github.com/sysrepo/sysrepo.git
    $ cd sysrepo
    $ git checkout v1.4.140
    $ mkdir build
    $ cd build
    $ cmake .. -DGEN_CPP_BINDINGS=ON -DGEN_LANGUAGE_BINDINGS=ON -DGEN_PYTHON_BINDINGS=OFF
    $ make
    $ make install  # without sudo if you're doing development and want to run unit tests

.. _sysrepo-overview:

Quick Sysrepo Overview
----------------------

This section offers a rather brief overview of a subset of available
functions in Sysrepo. For more complete information, see the `Sysrepo
homepage <https://www.sysrepo.org>`__.

In YANG, configurations and state data are described in the YANG syntax
in module files named: ``"module-name"``\ ``[@"revision"]``.yang

The revision part is optional and has YYYY-MM-DD format. An alternate
XML syntax YIN is defined but less user-friendly. Top-level modules are
named in Kea models (a short version of schema models).

There are two major modules that Kea is able to support: kea-dhcp4-server and
kea-dhcp6-server. While there is an active effort in the DHC working group at
IETF to develop a DHCPv6 YANG model, a similar initiative in the past for DHCPv4
failed. Therefore, Kea uses its own dedicated models for DHCPv4 and DHCPv6 but
partially supports the IETF model for DHCPv6.

All of the models have extra modules as dependencies. The dependency modules are
also provided in ``src/share/yang/modules`` in sources and in
``share/kea/yang/modules`` in the installation directory.

To install modules from sources, do the following to install all modules:

.. code-block:: console

    $ ./src/share/yang/modules/utils/reinstall.sh

OR if you installed sysrepo in a custom path:

.. code-block:: console

    $ ./src/share/yang/modules/utils/reinstall.sh -s /path/to/sysrepo

If you want to individually install all modules:

.. code-block:: console

    $ cd ./src/share/yang/modules
    $ sysrepoctl -i ./ietf-dhcpv6-server*.yang
    $ sysrepoctl -i ./kea-dhcp4-server*.yang
    $ sysrepoctl -i ./kea-dhcp6-server*.yang
    ...

The installation should look similar to the following:

.. code-block:: console

    $ ./src/share/yang/modules/utils/reinstall.sh
    [INF]: Libyang internal module "yang" was installed.
    [INF]: File "ietf-datastores@2018-02-14.yang" was installed.
    [INF]: Sysrepo internal dependency module "ietf-datastores" was installed.
    [INF]: File "ietf-yang-library@2019-01-04.yang" was installed.
    [INF]: Sysrepo internal module "ietf-yang-library" was installed.
    [INF]: File "sysrepo-monitoring@2021-01-15.yang" was installed.
    [INF]: Sysrepo internal module "sysrepo-monitoring" was installed.
    [INF]: File "sysrepo-plugind@2020-12-10.yang" was installed.
    [INF]: Sysrepo internal module "sysrepo-plugind" was installed.
    [INF]: File "ietf-netconf@2011-06-01.yang" was installed.
    [INF]: Sysrepo internal dependency module "ietf-netconf" was installed.
    [INF]: File "ietf-netconf-with-defaults@2011-06-01.yang" was installed.
    [INF]: Sysrepo internal module "ietf-netconf-with-defaults" was installed.
    [INF]: File "ietf-netconf-notifications@2012-02-06.yang" was installed.
    [INF]: Sysrepo internal module "ietf-netconf-notifications" was installed.
    [INF]: File "ietf-origin@2018-02-14.yang" was installed.
    [INF]: Sysrepo internal module "ietf-origin" was installed.
    [INF]: Connection 20 created.
    [INF]: Module "keatest-module" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: File "keatest-module@2018-11-20.yang" was installed.
    [INF]: Module "keatest-module" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 21 created.
    [INF]: Module "ietf-interfaces" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: File "ietf-interfaces@2018-02-20.yang" was installed.
    [INF]: Module "ietf-interfaces" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 22 created.
    [INF]: Module "ietf-dhcpv6-client" scheduled for installation.
    [INF]: File "ietf-dhcpv6-options@2018-09-04.yang" was installed.
    [INF]: File "ietf-dhcpv6-types@2018-09-04.yang" was installed.
    [INF]: Applying scheduled changes.
    [INF]: File "ietf-dhcpv6-client@2018-09-04.yang" was installed.
    [INF]: Module "ietf-dhcpv6-client" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 23 created.
    [INF]: Module "ietf-dhcpv6-relay" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: File "ietf-dhcpv6-relay@2018-09-04.yang" was installed.
    [INF]: Module "ietf-dhcpv6-relay" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 24 created.
    [INF]: Module "ietf-dhcpv6-server" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: File "ietf-dhcpv6-server@2018-09-04.yang" was installed.
    [INF]: Module "ietf-dhcpv6-server" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 25 created.
    [INF]: Module "ietf-yang-types" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: Module "ietf-yang-types" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 26 created.
    [INF]: Module "ietf-dhcpv6-options" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: Module "ietf-dhcpv6-options" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 27 created.
    [INF]: Module "ietf-dhcpv6-types" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: Module "ietf-dhcpv6-types" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 28 created.
    [INF]: Module "ietf-inet-types" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: Module "ietf-inet-types" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 29 created.
    [INF]: Module "kea-types" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: File "kea-types@2019-08-12.yang" was installed.
    [INF]: Module "kea-types" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 30 created.
    [INF]: Module "kea-dhcp-types" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: File "kea-dhcp-types@2019-08-12.yang" was installed.
    [INF]: Module "kea-dhcp-types" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 31 created.
    [INF]: Module "kea-dhcp-ddns" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: File "kea-dhcp-ddns@2019-08-12.yang" was installed.
    [INF]: Module "kea-dhcp-ddns" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 32 created.
    [INF]: Module "kea-ctrl-agent" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: File "kea-ctrl-agent@2019-08-12.yang" was installed.
    [INF]: Module "kea-ctrl-agent" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 33 created.
    [INF]: Module "kea-dhcp4-server" scheduled for installation.
    [INF]: Applying scheduled changes.
    [INF]: File "kea-dhcp4-server@2019-08-12.yang" was installed.
    [INF]: Module "kea-dhcp4-server" was installed.
    [INF]: Scheduled changes applied.
    [INF]: Connection 34 created.
    [INF]: Module "kea-dhcp6-server" scheduled for installation.

It is possible to confirm whether the models are imported correctly.
To list the currently installed YANG modules:

.. code-block:: console

     $ sysrepoctl -l

After installation the result should be similar to this:

::

    Sysrepo repository: /etc/sysrepo

    Module Name                | Revision   | Flags | Owner         | Permissions | Submodules | Features
    -----------------------------------------------------------------------------------------------------
    ietf-datastores            | 2018-02-14 | I     | user:user     | 664         |            |
    ietf-dhcpv6-client         | 2018-09-04 | I     | user:user     | 600         |            |
    ietf-dhcpv6-options        | 2018-09-04 | I     | user:user     | 600         |            |
    ietf-dhcpv6-relay          | 2018-09-04 | I     | user:user     | 600         |            |
    ietf-dhcpv6-server         | 2018-09-04 | I     | user:user     | 600         |            |
    ietf-dhcpv6-types          | 2018-09-04 | I     | user:user     | 600         |            |
    ietf-inet-types            | 2013-07-15 | I     | user:user     | 664         |            |
    ietf-interfaces            | 2018-02-20 | I     | user:user     | 600         |            |
    ietf-netconf               | 2011-06-01 | I     | user:user     | 664         |            |
    ietf-netconf-notifications | 2012-02-06 | I     | user:user     | 664         |            |
    ietf-netconf-with-defaults | 2011-06-01 | I     | user:user     | 664         |            |
    ietf-origin                | 2018-02-14 | I     | user:user     | 664         |            |
    ietf-yang-library          | 2019-01-04 | I     | user:user     | 664         |            |
    ietf-yang-metadata         | 2016-08-05 | i     |               |             |            |
    ietf-yang-types            | 2013-07-15 | I     | user:user     | 664         |            |
    kea-ctrl-agent             | 2019-08-12 | I     | user:user     | 600         |            |
    kea-dhcp-ddns              | 2019-08-12 | I     | user:user     | 600         |            |
    kea-dhcp-types             | 2019-08-12 | I     | user:user     | 600         |            |
    kea-dhcp4-server           | 2019-08-12 | I     | user:user     | 600         |            |
    kea-dhcp6-server           | 2019-08-12 | I     | user:user     | 600         |            |
    kea-types                  | 2019-08-12 | I     | user:user     | 600         |            |
    keatest-module             | 2018-11-20 | I     | user:user     | 600         |            |
    sysrepo-monitoring         | 2021-01-15 | I     | user:user     | 600         |            |
    sysrepo-plugind            | 2020-12-10 | I     | user:user     | 664         |            |
    yang                       | 2017-02-20 | I     | user:user     | 664         |            |

    Flags meaning: I - Installed/i - Imported; R - Replay support; N - New/X - Removed/U - Updated; F - Feature changes
    Features: ! - Means that the feature is effectively disabled because of its false if-feature(s)

To reinstall a module, if the revision YANG entry was bumped, simply installing
it will update it automatically. Otherwise, it must first be uninstalled:

.. code-block:: console

    $ sysrepoctl -u kea-dhcp4-server

If the module is used (i.e. imported) by other modules, it can be uninstalled
only after the dependant modules have been uninstalled first.
Installation and uninstallation must be done in dependency order and
reverse-dependency order accordingly.

.. _netconf-models:

Supported YANG Models
---------------------

The only currently supported models are ``kea-dhcp4-server`` and
``kea-dhcp6-server``. There is partial support for
``ietf-dhcpv6-server``, but the primary focus of testing has been on Kea DHCP
servers. Several other models (``kea-dhcp-ddns`` and ``kea-ctrl-agent``)
are currently not supported.

.. _using-netconf:

Using the NETCONF Agent
-----------------------

The NETCONF agent follows this algorithm:

-  For each managed server, get the initial configuration from the
   server through the control socket.

-  Open a connection with the Sysrepo environment and establish two
   sessions with the startup and running datastores.

-  Check that used (not essential) and required (essential) modules are
   installed in the Sysrepo repository at the right revision. If an
   essential module - that is, a module where the configuration schema for a
   managed server is defined - is not installed, raise a fatal error.

-  For each managed server, get the YANG configuration from the startup
   datastore, translate it to JSON, and load it onto the server being
   configured.

-  For each managed server, subscribe a module change callback using its
   model name.

-  When a running configuration is changed, try to validate or load the
   updated configuration via the callback to the managed server.

.. _netconf-configuration:

Configuration
-------------

The behavior described in :ref:`using-netconf`
is controlled by a few configuration flags, which can be set in the
global scope or in a specific managed-server scope. In the second case,
the value defined in the managed-server scope takes precedence. These
flags are:

-  ``boot-update`` - controls the initial configuration phase; when
   true (the default), the initial configuration retrieved from the
   classic Kea server JSON configuration file is loaded first, and then
   the startup YANG model is loaded. This setting lets administrators
   define a control socket in the local JSON file and then download the
   configuration from YANG. When set to false, this phase is skipped.

-  ``subscribe-changes`` - controls the module change
   subscription; when true (the default), a module change callback is
   subscribed, but when false the phase is skipped and running
   configuration updates are disabled. When set to true, the running
   datastore is used to subscribe for changes.

-  ``validate-changes`` - controls how Kea monitors changes in
   the Sysrepo configuration. Sysrepo offers two stages where Kea can
   interact: validation and application. At the validation (or
   SR_EV_CHANGE event, in the Sysrepo naming convention) stage, Kea
   retrieves the newly committed configuration and verifies it. If the
   configuration is incorrect for any reason, the Kea servers reject it
   and the error is propagated back to the Sysrepo, which then returns
   an error. This step only takes place if validate-changes is set to
   true. In the application (or SR_EV_UPDATE event in the Sysrepo naming
   convention) stage, the actual configuration is applied. At this stage
   Kea can receive the configuration, but it is too late to signal back
   any errors as the configuration has already been committed.

The idea behind the initial configuration phase is to boot Kea servers
with a minimal configuration which includes only a control socket,
making them manageable. For instance, for the DHCPv4 server:

.. code-block:: json

    {
        "Dhcp4": {
            "control-socket": {
               "socket-name": "/tmp/kea-dhcp4-ctrl.sock",
               "socket-type": "unix"
            }
        }
    }

With module change subscriptions enabled, the ``kea-netconf`` daemon will
monitor any configuration changes as they appear in the Sysrepo. Such
changes can be done using the ``sysrepocfg`` tool or remotely using any
NETCONF client. For details, please see the Sysrepo documentation or
:ref:`operation-example`.
Those tools can be used to modify YANG configurations in the running
datastore. Note that committed configurations are only updated in the
running datastore; to keep them between server reboots they must be
copied to the startup datastore.

When module changes are tracked (using ``subscribe-changes`` set to
true) and the running configuration has changed (e.g. using
``sysrepocfg`` or any NETCONF client), the callback validates the
modified configuration (if ``validate-changes`` was not set to false)
and runs a second time to apply the new configuration. If the validation
fails, the callback is still called again but with an SR_EV_ABORT
(vs. SR_EV_DONE) event with rollback changes.

The returned code of the callback on an SR_EV_DONE event is ignored, as it is
too late to refuse a bad configuration.

There are four ways in which a modified YANG configuration could
possibly be incorrect:

1. It can be non-compliant with the schema, e.g. an unknown entry, missing a
   mandatory entry, a value with a bad type, or not matching a constraint.

2. It can fail to be translated from YANG to JSON, e.g. an invalid user
   context.

3. It can fail Kea server sanity checks, e.g. an out-of-subnet-pool range
   or an unsupported database type.

4. The syntax may be correct and pass server sanity checks but the
   configuration fails to run, e.g. the configuration specifies database
   credentials but the database refuses the connection.

The first case is handled by Sysrepo. The second and third cases are
handled by kea-netconf in the validation phase (if not disabled by
setting ``validate-changes`` to true). The last case causes the
application phase to fail without a sensible report to Sysrepo.

The managed Kea servers or agents are described in the
``managed-servers`` section. Each sub-section begins by the service
name: ``dhcp4``, ``dhcp6``, ``d2`` (the DHCP-DDNS server does not
support the control channel feature yet), and ``ca`` (the control
agent).

Each managed server entry contains optionally:

-  ``boot-update``, ``subscribe-changes``, and ``validate-changes`` -
   control flags.

-  ``model`` - specifies the YANG model / module name. For each service,
   the default is the corresponding Kea YANG model, e.g. for ``"dhcp4"``
   it is ``"kea-dhcp4-server"``.

-  ``control-socket`` - specifies the control socket for managing the
   service configuration.

A control socket is specified by:

-  ``socket-type`` - the socket type is either ``stdout``, ``unix``, or ``http``.
   ``stdout`` is the default;
   it is not really a socket, but it allows ``kea-netconf`` to run in
   debugging mode where everything is printed on stdout, and it can also be
   used to redirect commands easily. ``unix`` is the standard direct
   server control channel, which uses UNIX sockets, and ``http`` uses
   a control agent, which accepts HTTP connections.

-  ``socket-name`` - the local socket name for the ``unix`` socket type
   (default empty string).

-  ``socket-url`` - the HTTP URL for the ``http`` socket type (default
   ``http://127.0.0.1:8000/``).

User contexts can store arbitrary data as long as they are in valid JSON
syntax and their top-level element is a map (i.e. the data must be
enclosed in curly brackets). They are accepted at the NETCONF entry,
i.e. below the top-level, managed-service entry, and control-socket
entry scopes.

Hooks libraries can be loaded by the NETCONF agent just as with other
servers or agents; however, currently no hook points are defined. The
``hooks-libraries`` list contains the list of hooks libraries that
should be loaded by kea-netconf, along with their configuration
information specified with ``parameters``.

Please consult :ref:`logging` for details on how to configure
logging. The name of the NETCONF agent's main logger is ``kea-netconf``, as
given in the example above.

.. _netconf-example:

A kea-netconf Configuration Example
-----------------------------------

The following example demonstrates the basic NETCONF configuration. More
examples are available in the ``doc/examples/netconf`` directory in the
Kea sources.

.. code-block:: javascript

   // This is a simple example of a configuration for the NETCONF agent.
   // This server provides a YANG interface for all Kea servers and the agent.
   {
       "Netconf":
       {
           // Control flags can be defined in the global scope or
           // in a managed server scope. Precedences are:
           // - use the default value (true)
           // - use the global value
           // - use the local value.
           // So this overwrites the default value:
           "boot-update": false,

           // This map specifies how each server is managed. For each server there
           // is a name of the YANG model to be used and the control channel.
           //
           // Currently three control channel types are supported:
           // "stdout" which outputs the configuration on the standard output,
           // "unix" which uses the local control channel supported by the
           // "dhcp4" and "dhcp6" servers ("d2" support is not yet available),
           // and "http" which uses the Control Agent "ca" to manage itself or
           // to forward commands to "dhcp4" or "dhcp6".
           "managed-servers":
           {
               // This is how kea-netconf can communicate with the DHCPv4 server.
               "dhcp4":
               {
                   "comment": "DHCP4 server",
                   "model": "kea-dhcp4-server",
                   "control-socket":
                   {
                       "socket-type": "unix",
                       "socket-name": "/tmp/kea4-ctrl-socket"
                   }
               },

               // DHCPv6 parameters.
               "dhcp6":
               {
                   "model": "kea-dhcp6-server",
                   "control-socket":
                   {
                       "socket-type": "unix",
                       "socket-name": "/tmp/kea6-ctrl-socket"
                   }
               },

               // Currently the DHCP-DDNS (nicknamed D2) server does not support
               // a command channel.
               "d2":
               {
                   "model": "kea-dhcp-ddns",
                   "control-socket":
                   {
                       "socket-type": "stdout",
                       "user-context": { "in-use": false }
                   }
               },

               // Of course the Control Agent (CA) supports HTTP.
               "ca":
               {
                   "model": "kea-ctrl-agent",
                   "control-socket":
                   {
                       "socket-type": "http",
                       "socket-url": "http://127.0.0.1:8000/"
                   }
               }
           },

           // kea-netconf is able to load hooks libraries that augment its operation.
           // Currently there are no hook points defined in kea-netconf
           // processing.
           "hooks-libraries": [
               // The hooks libraries list may contain more than one library.
               {
                   // The only necessary parameter is the library filename.
                   "library": "/opt/local/netconf-commands.so",

                   // Some libraries may support parameters. Make sure you
                   // type this section carefully, as kea-netconf does not
                   // validate it (because the format is library-specific).
                   "parameters": {
                       "param1": "foo"
                   }
               }
           ],

           // Similar to other Kea components, NETCONF also uses logging.
           "loggers": [
               {
                   "name": "kea-netconf",
                   "output_options": [
                       {
                           "output": "/var/log/kea-netconf.log",
                           // Several additional parameters are possible in
                           // addition to the typical output.
                           // Flush determines whether logger flushes output
                           //  to a file.
                           // Maxsize determines maximum filesize before
                           // the file is being rotated.
                           // Maxver specifies the maximum number of
                           //  rotated files being kept.
                           "flush": true,
                           "maxsize": 204800,
                           "maxver": 4
                       }
                   ],
                   "severity": "INFO",
                   "debuglevel": 0
               }
           ]
       }
   }

.. _netconf-start-stop:

Starting and Stopping the NETCONF Agent
---------------------------------------

kea-netconf accepts the following command-line switches:

-  ``-c file`` - specifies the configuration file.

-  ``-d`` - specifies whether the agent logging should be switched to
   debug/verbose mode. In verbose mode, the logging severity and
   debuglevel specified in the configuration file are ignored and
   "debug" severity and the maximum debuglevel (99) are assumed. The
   flag is convenient for temporarily switching the server into maximum
   verbosity, e.g. when debugging.

-  ``-t file`` - specifies the configuration file to be tested.
   Kea-netconf attempts to load it and conducts sanity checks; note that
   certain checks are possible only while running the actual server. The
   actual status is reported with exit code (0 = configuration looks ok,
   1 = error encountered). Kea will print out log messages to standard
   output and error to standard error when testing configuration.

-  ``-v`` - displays the version of kea-netconf and exits.

-  ``-V`` - displays the extended version information for kea-netconf
   and exits. The listing includes the versions of the libraries
   dynamically linked to Kea.

-  ``-W`` - displays the Kea configuration report and exits. The report
   is a copy of the ``config.report`` file produced by ``./configure``;
   it is embedded in the executable binary.

.. _operation-example:

A Step-by-Step NETCONF Agent Operation Example
----------------------------------------------

.. note::

   Copies of example configurations presented within this section can be
   found in the Kea source code, under
   ``doc/examples/netconf/kea-dhcp6-operations``.

.. _operation-example-setup:

Setup of NETCONF Agent Operation Example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The test box has an Ethernet interface named eth1. On some systems it is
possible to rename interfaces, for instance on a Linux with an ens38
interface:

.. code-block:: console

    # ip link set down dev ens38
    # ip link set name eth1 dev ens38
    # ip link set up dev eth1

The interface must have an address in the test prefix:

.. code-block:: console

    # ip -6 addr add 2001:db8::1/64 dev eth1

The Kea DHCPv6 server must be launched with the configuration specifying
a control socket used to receive control commands. The ``kea-netconf``
process uses this socket to communicate with the DHCPv6 server, i.e. it
pushes translated configurations to that server using control commands.
The following is the example control socket specification for the Kea
DHCPv6 server:

.. code-block:: json

    {
        "Dhcp6": {
            "control-socket": {
               "socket-name": "/tmp/kea-dhcp6-ctrl.sock",
               "socket-type": "unix"
            }
        }
    }

In order to launch the Kea DHCPv6 server using the configuration
contained within the ``boot.json`` file, run:

.. code-block:: console

    # kea-dhcp6 -d -c boot.json

The current configuration of the server can be fetched via control
socket by running:

.. code-block:: console

    # echo '{ "command": "config-get" }' | socat UNIX:/tmp/kea-dhcp6-ctrl.sock '-,ignoreeof'

The following is the example ``netconf.json`` configuration for
``kea-netconf``, to manage the Kea DHCPv6 server:

.. code-block:: json

    {
      "Netconf": {
        "loggers": [
          {
            "debuglevel": 99,
            "name": "kea-netconf",
            "output_options": [
              {
                "output": "stderr"
              }
            ],
            "severity": "DEBUG"
          }
        ],
        "managed-servers": {
          "dhcp6": {
            "control-socket": {
              "socket-name": "/tmp/kea-dhcp6-ctrl.sock",
              "socket-type": "unix"
            }
          }
        }
      }
    }

Note that in production there should not be a need to log at the DEBUG level.

The Kea NETCONF agent is launched by:

.. code-block:: console

    # kea-netconf -d -c netconf.json

Now that both ``kea-netconf`` and ``kea-dhcp6`` are running, it is
possible to populate updates to the configuration to the DHCPv6 server.
The following is the configuration extracted from ``startup.xml``:

.. code-block:: xml

   <config xmlns="urn:ietf:params:xml:ns:yang:kea-dhcp6-server">
     <subnet6>
       <id>1</id>
       <pool>
         <start-address>2001:db8::1:0</start-address>
         <end-address>2001:db8::1:ffff</end-address>
         <prefix>2001:db8::1:0/112</prefix>
       </pool>
       <subnet>2001:db8::/64</subnet>
     </subnet6>
     <interfaces-config>
       <interfaces>eth1</interfaces>
     </interfaces-config>
     <control-socket>
       <socket-name>/tmp/kea-dhcp6-ctrl.sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

To populate this new configuration:

.. code-block:: console

    $ sysrepocfg -d startup -f xml -m kea-dhcp6-server --edit=startup.xml

``kea-netconf`` pushes the configuration found in the Sysrepo startup
datastore to all Kea servers during its initialization phase, after it
subscribes to module changes in the Sysrepo running datastore. This
action copies the configuration from the startup datastore to the
running datastore and enables the running datastore, making it
available.

Changes to the running datastore are applied after validation to the Kea
servers. Note that they are not by default copied back to the startup
datastore, i.e. changes are not permanent.

.. _operation-example-errors:

Error Handling in NETCONF Operation Example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are four classes of issues with the configurations applied via
NETCONF:

1. The configuration does not comply with the YANG schema.

2. The configuration cannot be translated from YANG to the Kea JSON.

3. The configuration is rejected by the Kea server.

4. The configuration was validated by the Kea server but cannot be
   applied.

In the first case, consider the following ``BAD-schema.xml``
configuration file:

.. code-block:: xml

   <config xmlns="urn:ietf:params:xml:ns:yang:kea-dhcp6-server">
     <subnet4>
       <id>1</id>
       <pool>
         <start-address>2001:db8::1:0</start-address>
         <end-address>2001:db8::1:ffff</end-address>
         <prefix>2001:db8::1:0/112</prefix>
       </pool>
       <subnet>2001:db8::/64</subnet>
     </subnet6>
     <interfaces-config>
       <interfaces>eth1</interfaces>
     </interfaces-config>
     <control-socket>
       <socket-name>/tmp/kea-dhcp6-ctrl.sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

It is directly rejected by ``sysrepocfg``:

.. code-block:: console

    $ sysrepocfg -d running -f xml -m kea-dhcp6-server --edit=BAD-schema.xml

In the second case, the configuration is rejected by ``kea-netconf``.
For example, consider this ``BAD-translator.xml`` file:

.. code-block:: xml

   <config xmlns="urn:ietf:params:xml:ns:yang:kea-dhcp6-server">
     <subnet6>
       <id>1</id>
       <pool>
         <start-address>2001:db8::1:0</start-address>
         <end-address>2001:db8::1:ffff</end-address>
         <prefix>2001:db8::1:0/112</prefix>
       </pool>
       <subnet>2001:db8::/64</subnet>
     </subnet6>
     <interfaces-config>
       <interfaces>eth1</interfaces>
     </interfaces-config>
     <control-socket>
       <socket-name>/tmp/kea-dhcp6-ctrl.sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
     <user-context>bad</user-context>
   </config>

In the third case, the configuration is presented to the Kea DHCPv6
server and fails to validate as in this ``BAD-config.xml`` file:

.. code-block:: xml

   <config xmlns="urn:ietf:params:xml:ns:yang:kea-dhcp6-server">
     <subnet6>
       <id>1</id>
       <pool>
         <start-address>2001:db8:1::0</start-address>
         <end-address>2001:db8:1::ffff</end-address>
         <prefix>2001:db8:1::0/112</prefix>
       </pool>
       <subnet>2001:db8::/64</subnet>
     </subnet6>
     <interfaces-config>
       <interfaces>eth1</interfaces>
     </interfaces-config>
     <control-socket>
       <socket-name>/tmp/kea-dhcp6-ctrl.sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

In the last case, the misconfiguration is detected too late and the
change must be reverted in Sysrepo, e.g. using the startup datastore as
a backup.

.. _operation-example-2pools:

NETCONF Operation Example with Two Pools
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This example adds a second pool to the initial (i.e. startup)
configuration in the ``twopools.xml`` file:

.. code-block:: xml

   <config xmlns="urn:ietf:params:xml:ns:yang:kea-dhcp6-server">
     <subnet6>
       <id>1</id>
       <pool>
         <start-address>2001:db8::1:0</start-address>
         <end-address>2001:db8::1:ffff</end-address>
         <prefix>2001:db8::1:0/112</prefix>
       </pool>
       <pool>
         <start-address>2001:db8::2:0</start-address>
         <end-address>2001:db8::2:ffff</end-address>
         <prefix>2001:db8::2:0/112</prefix>
       </pool>
       <subnet>2001:db8::/64</subnet>
     </subnet6>
     <interfaces-config>
       <interfaces>eth1</interfaces>
     </interfaces-config>
     <control-socket>
       <socket-name>/tmp/kea-dhcp6-ctrl.sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

This configuration is installed by:

.. code-block:: console

    $ sysrepocfg -d running -f xml -m kea-dhcp6-server --edit=twopools.xml

.. _operation-example-2subnets:

NETCONF Operation Example with Two Subnets
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This example specifies two subnets in the ``twosubnets.xml`` file:

.. code-block:: xml

   <config xmlns="urn:ietf:params:xml:ns:yang:kea-dhcp6-server">
     <subnet6>
       <id>1</id>
       <pool>
         <start-address>2001:db8:1::</start-address>
         <end-address>2001:db8:1::ffff</end-address>
         <prefix>2001:db8:1::/112</prefix>
       </pool>
       <subnet>2001:db8:1::/64</subnet>
     </subnet6>
     <subnet6>
       <id>2</id>
       <pool>
         <start-address>2001:db8:2::</start-address>
         <end-address>2001:db8:2::ffff</end-address>
         <prefix>2001:db8:2::/112</prefix>
       </pool>
       <subnet>2001:db8:2::/64</subnet>
     </subnet6>
     <interfaces-config>
       <interfaces>eth1</interfaces>
     </interfaces-config>
     <control-socket>
       <socket-name>/tmp/kea-dhcp6-ctrl.sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

This configuration is installed by:

.. code-block:: console

    $ sysrepocfg -d running -f xml -m kea-dhcp6-server --edit=twosubnets.xml

.. _operation-example-logging:

NETCONF Operation Example with Logging
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This example adds a logger entry to the initial (i.e. startup)
configuration in the ``logging.xml`` file:

.. code-block:: xml

   <config xmlns="urn:ietf:params:xml:ns:yang:kea-dhcp6-server">
     <interfaces-config>
       <interfaces>eth1</interfaces>
     </interfaces-config>
     <subnet6>
       <id>1</id>
       <pool>
         <start-address>2001:db8::1:0</start-address>
         <end-address>2001:db8::1:ffff</end-address>
         <prefix>2001:db8::1:0/112</prefix>
       </pool>
       <subnet>2001:db8::/64</subnet>
     </subnet6>
     <control-socket>
       <socket-name>/tmp/kea-dhcp6-ctrl.sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
     <logger>
       <name>kea-dhcp6</name>
       <output-option>
         <output>stderr</output>
       </output-option>
       <debuglevel>99</debuglevel>
       <severity>DEBUG</severity>
     </logger>
   </config>

The corresponding Kea configuration in JSON is:

.. code-block:: json

   {
     "Dhcp6": {
       "control-socket": {
         "socket-name": "/tmp/kea-dhcp6-ctrl.sock",
         "socket-type": "unix"
       },
       "interfaces-config": {
         "interfaces": [ "eth1" ]
       },
       "subnet6": [
         {
           "id": 1,
           "pools": [
             {
               "pool": "2001:db8::1:0/112"
             }
           ],
           "subnet": "2001:db8::/64"
         }
       ],
       "loggers": [
         {
           "name": "kea-dhcp6",
           "output_options": [
             {
               "output": "stderr"
             }
           ],
           "severity": "DEBUG",
           "debuglevel": 99
         }
      ]
    }
   }

Finally, any of the previous examples can be replayed by using
``sysrepocfg`` in edit mode as follows:

.. code-block:: console

    $ sysrepocfg -d running -f xml -m kea-dhcp6-server --edit

or by using a NETCONF client like ``netopeer2-cli`` from the
`Netopeer2 <https://github.com/CESNET/Netopeer2>`__ NETCONF Toolset.

.. _migrating-yang-v0-to-v1:

Migrating YANG data from sysrepo v0.x to v1.x
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Start the migration after turning off kea-netconf to make sure that backups done
for both datastores are done at the same configuration state and no change
happens between exporting them.

Unfortunately, sysrepo v0.x does not support import/export of all YANG modules.
This was added in sysrepo v1.x. You will need to do per-module backup. It's
probably for the best, for isolating potential failures and preventing them from
affecting all your modules.

With sysrepo v0.x:

.. code-block:: console

    $ sysrepocfg --datastore running --export=save.xml --format=xml kea-dhcp6-server
    $ sysrepocfg --datastore startup --export=save.xml --format=xml kea-dhcp6-server

Install sysrepo v1.x and then:

.. code-block:: console

    $ sysrepocfg --datastore running --edit=save.xml
    $ sysrepocfg --datastore startup --edit=save.xml

Module name and format are optional for v1.x, they are detected automatically.
In case of trouble, they can be provided with the ``--format xml`` and
``--module kea-dhcp6-server`` flags.

If you upgraded after a long time, there might also be changes to the YANG
modules themselves. In that case the backups will need some minor massaging. But
this will be a dilligence that will have to be carried out occasionally and
completely independent of sysrepo upgrades.
