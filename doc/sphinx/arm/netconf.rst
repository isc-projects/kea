.. _netconf:

********************
YANG/NETCONF Support
********************

.. _netconf-overview:

Overview
========

Kea 1.5.0 introduced optional support for a YANG/NETCONF interface with
the new ``kea-netconf`` NETCONF agent.

This bare-bones documentation is a work in progress. Its current purpose
is to let engineers joining the project or perhaps advanced early
adopters to get up to speed quickly.

.. _netconf-install:

Installing NETCONF
==================

Note that to get its NETCONF capabilities, Kea uses Sysrepo, which has
many dependencies. Unfortunately, some of them are not available as
packages and need to be compiled manually.

Please note that building libyang requires a minimum gcc version of at
least 4.9, so on some environments - like CentOS 7.5 - the system
compiler cannot be used.

The following sections provide installation instructions for Ubuntu
18.04 and CentOS 7.5. Due to a more modern compiler and many available
packages, the installation procedure is much simpler on Ubuntu.

.. _netconf-ubuntu-install:

Installing NETCONF on Ubuntu 18.04
----------------------------------

For detailed installation instructions, see the `Ubuntu installation notes page <https://gitlab.isc.org/isc-projects/kea/wikis/docs/ubuntu-installation-notes>`__.

.. _netconf-centos-install:

Installing NETCONF on CentOS 7.5
--------------------------------

For detailed installation instructions, see the `CentOS installation notes page <https://gitlab.isc.org/isc-projects/kea/wikis/docs/centos-installation-notes>`__.

CentOS 7.5's gcc compiler (version 4.8.5) is very old. Some Sysrepo
dependencies require at least version 4.9, which unfortunately means
that a new compiler has to be installed. Also, many of the Sysrepo
dependencies are not avalable in CentOS as packages, so for the time
being they must be installed from sources.

Quick Sysrepo Overview
======================

This section offers a rather brief overview of a subset of available
functions in Sysrepo. For more complete information, see the `Sysrepo
homepage <https://www.sysrepo.org>`__.

In YANG, configurations and state data are described in the YANG syntax
in module files named: ``"module-name"``\ ``[@"revision"]``.yang

The revision part is optional and has YYYY-MM-DD format. An alternate
XML syntax YIN is defined but less user-friendly. Top-level modules are
named in Kea models (a short version of schema models).

To list the currently installed YANG modules:

.. code-block:: console

     $ sysrepoctl -l

After installation the result should be similar to this:

::

   Sysrepo schema directory: /home/thomson/devel/sysrepo-0.7.6/build/repository/yang/
   Sysrepo data directory:   /home/thomson/devel/sysrepo-0.7.6/build/repository/data/
   (Do not alter contents of these directories manually)

   Module Name      | Revision   | Conformance | Data Owner | Permissions
   ----------------------------------------------------------------------
   ietf-netconf-    | 2012-02-06 | Installed   | root:root  | 666
     -notifications |            |             |            |
   ietf-netconf     | 2011-06-01 | Imported    |            |
   ietf-netconf-acm | 2012-02-22 | Imported    |            |
   nc-notifications | 2008-07-14 | Installed   | root:root  | 666
   notifications    | 2008-07-14 | Installed   | root:root  | 666
   turing-machine   | 2013-12-27 | Installed   | root:root  | 666
   iana-if-type     | 2014-05-08 | Installed   |            |
   ietf-interfaces  | 2014-05-08 | Installed   | root:root  | 666
   ietf-ip          | 2014-06-16 | Installed   |            |

There are two major modules that Kea is able to support:
kea-dhcp4-server and kea-dhcp6-server. Note that while there is an
active effort in the DHC working group at IETF to develop a DHCPv6 YANG
model, a similar initiative in the past for DHCPv4 failed. Therefore,
Kea uses its own dedicated models for DHCPv4 and DHCPv6 but partially
supports the IETF model for DHCPv6. Those three models have extra
modules as dependencies. The dependency modules are also provided in
``src/share/yang/modules`` in sources and in ``share/kea/yang/modules``
after installation.

To install modules from sources, do the following:

.. code-block:: console

   $ cd src/share/yang/modules
   $ sudo sysrepoctl -i -s /home/thomson/devel/sysrepo-0.7.6/build/repository/yang -s . -g ietf-dhcpv6-server*.yang
   $ sudo sysrepoctl -i -s /home/thomson/devel/sysrepo-0.7.6/build/repository/yang -s . -g kea-dhcp4-server*.yang
   $ sudo sysrepoctl -i -s /home/thomson/devel/sysrepo-0.7.6/build/repository/yang -s . -g kea-dhcp6-server*.yang
   ...

Note that the first -s parameter specifies the location of the YANG
schema repository; it can be verified with sysrepoctl -l. This is a
parameter that is configured during Sysrepo compilation and is detected
by the Kea configuration under the SYSREPO_REPO name.

The installation should look similar to the following:

.. code-block:: console

   $ sudo sysrepoctl -i -s /home/thomson/devel/sysrepo-0.7.6/build/repository/yang -s . -g ietf-dhcpv6-server*.yang
   Installing a new module from file 'ietf-dhcpv6-server@2018-11-20.yang'...
   Installing the YANG file to '/home/thomson/devel/sysrepo-0.7.6/build/repository/yang/ietf-dhcpv6-server@2018-07-14.yang'...
   Resolving dependency: 'ietf-dhcpv6-server' imports 'ietf-dhcpv6-options'...
   Installing the YANG file to '/home/thomson/devel/sysrepo-0.7.6/build/repository/yang/ietf-dhcpv6-options@2018-07-14.yang'...
   Resolving dependency: 'ietf-dhcpv6-options' imports 'ietf-dhcpv6-types'...
   Installing the YANG file to '/home/thomson/devel/sysrepo-0.7.6/build/repository/yang/ietf-dhcpv6-types@2018-07-14.yang'...
   Resolving dependency: 'ietf-dhcpv6-server' imports 'ietf-dhcpv6-types'...
   Installing the YANG file to '/home/thomson/devel/sysrepo-0.7.6/build/repository/yang/ietf-dhcpv6-types@2018-07-14.yang'...
   Resolving dependency: 'ietf-dhcpv6-server' imports 'ietf-interfaces'...
   Schema of the module ietf-interfaces is already installed, skipping...
   Installing data files for module 'ietf-dhcpv6-server'...
   Resolving dependency: 'ietf-dhcpv6-server' imports 'ietf-dhcpv6-options'...
   Skipping installation of data files for module 'ietf-dhcpv6-options'...
   Resolving dependency: 'ietf-dhcpv6-options' imports 'ietf-dhcpv6-types'...
   Skipping installation of data files for module 'ietf-dhcpv6-types'...
   Resolving dependency: 'ietf-dhcpv6-server' imports 'ietf-dhcpv6-types'...
   Skipping installation of data files for module 'ietf-dhcpv6-types'...
   Resolving dependency: 'ietf-dhcpv6-server' imports 'ietf-interfaces'...
   Installing data files for module 'ietf-interfaces'...
   Notifying sysrepo about the change...
   Install operation completed successfully.

It is possible to confirm whether the models are imported correctly by using
sysrepoctl -l:

.. code-block:: console

   $ sysrepoctl -l
   Sysrepo schema directory: /home/thomson/devel/sysrepo-0.7.6/build/repository/yang/
   Sysrepo data directory:   /home/thomson/devel/sysrepo-0.7.6/build/repository/data/
   (Do not alter contents of these directories manually)

   Module Name                | Revision   | Conformance | Data Owner          | Permissions
   -----------------------------------------------------------------------------------------
   ietf-netconf-notifications | 2012-02-06 | Installed   | root:root           | 666
   ietf-netconf               | 2011-06-01 | Imported    |                     |
   ietf-netconf-acm           | 2012-02-22 | Imported    |                     |
   nc-notifications           | 2008-07-14 | Installed   | root:root           | 666
   notifications              | 2008-07-14 | Installed   | root:root           | 666
   turing-machine             | 2013-12-27 | Installed   | root:root           | 666
   iana-if-type               | 2014-05-08 | Installed   |                     |
   ietf-interfaces            | 2014-05-08 | Installed   | root:root           | 666
   ietf-ip                    | 2014-06-16 | Installed   |                     |
   kea-dhcp4-server           | 2018-11-20 | Installed   | root:root           | 666
   kea-dhcp6-server           | 2018-11-20 | Installed   | root:root           | 666
   ietf-dhcpv6-server         | 2018-09-04 | Installed   | root:root           | 666
   ietf-dhcpv6-options        | 2018-09-04 | Imported    |                     |
   ietf-dhcpv6-types          | 2018-01-30 | Imported    |                     |

To install a new revision of a module it must first be uninstalled, e.g.
by:

.. code-block:: console

   sudo sysrepoctl -u -m kea-dhcp4-server

If the module is used (i.e. imported) by other modules, it can be
uninstalled only after those modules have finished using it.
Installation and uninstallation must be done in dependency order and
reverse-dependency order accordingly.

.. _netconf-models:

Supported YANG Models
=====================

The only currently supported models are ``kea-dhcp4-server`` and
``kea-dhcp6-server``. There is partial support for
``ietf-dhcpv6-server``, but the primary focus of testing has been on Kea DHCP
servers. Several other models (``kea-dhcp-ddns`` and ``kea-ctrl-agent``)
are currently not supported.

.. _using-netconf:

Using the NETCONF Agent
=======================

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
=============

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
   SR_EV_VERIFY event, in the Sysrepo naming convention) stage, Kea
   retrieves the newly committed configuration and verifies it. If the
   configuration is incorrect for any reason, the Kea servers reject it
   and the error is propagated back to the Sysrepo, which then returns
   an error. This step only takes place if validate-changes is set to
   true. In the application (or SR_EV_APPLY event in the Sysrepo naming
   convention) stage, the actual configuration is applied. At this stage
   Kea can receive the configuration, but it is too late to signal back
   any errors as the configuration has already been committed.

The idea behind the initial configuration phase is to boot Kea servers
with a minimal configuration which includes only a control socket,
making them manageable. For instance, for the DHCPv4 server:

::

   {
       "Dhcp4": {
           "control-socket": {
               "socket-type": "unix",
               "socket-name": "/tmp/kea4-sock"
           }
       }
   }

Note the alternative to boot with full configurations does not allow
easy tracking of changes or synchronization between the JSON and YANG
configuration sources; therefore, that setup is not really compatible
with the YANG/NETCONF configuration management paradigm, where
everything should be performed in YANG.

With module change subscriptions enabled, the kea-netconf daemon will
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
fails, the callback is still called again but with an ABORT (vs. APPLY)
event with rollback changes.

The returned code of the callback on an APPLY event is ignored, as it is
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
logging. The NETCONF agent's root logger's name is ``kea-netconf``, as
given in the example above.

.. _netconf-example:

A kea-netconf Configuration Example
===================================

The following example demonstrates the basic NETCONF configuration. More
examples are available in the ``doc/examples/netconf`` directory in the
Kea sources.

::

   # This is a simple example of a configuration for the NETCONF agent.
   # This server provides a YANG interface for all Kea servers and the agent.
   {
       "Netconf":
       {
           # Control flags can be defined in the global scope or
           # in a managed server scope. Precedences are:
           # - use the default value (true)
           # - use the global value
           # - use the local value.
           # So this overwrites the default value:
           "boot-update": false,

           # This map specifies how each server is managed. For each server there
           # is a name of the YANG model to be used and the control channel.
           //
           # Currently three control channel types are supported:
           # "stdout" which outputs the configuration on the standard output,
           # "unix" which uses the local control channel supported by the
           # "dhcp4" and "dhcp6" servers ("d2" support is not yet available),
           # and "http" which uses the Control Agent "ca" to manage itself or
           # to forward commands to "dhcp4" or "dhcp6".
           "managed-servers":
           {
               # This is how kea-netconf can communicate with the DHCPv4 server.
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

               # DHCPv6 parameters.
               "dhcp6":
               {
                   "model": "kea-dhcp6-server",
                   "control-socket":
                   {
                       "socket-type": "unix",
                       "socket-name": "/tmp/kea6-ctrl-socket"
                   }
               },

               # Currently the DHCP-DDNS (nicknamed D2) server does not support
               # a command channel.
               "d2":
               {
                   "model": "kea-dhcp-ddns",
                   "control-socket":
                   {
                       "socket-type": "stdout",
                       "user-context": { "in-use": false }
                   }
               },

               # Of course the Control Agent (CA) supports HTTP.
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

           # kea-netconf is able to load hooks libraries that augment its operation.
           # Currently there are no hook points defined in kea-netconf
           # processing.
           "hooks-libraries": [
               # The hooks libraries list may contain more than one library.
               {
                   # The only necessary parameter is the library filename.
                   "library": "/opt/local/netconf-commands.so",

                   # Some libraries may support parameters. Make sure you
                   # type this section carefully, as kea-netconf does not
                   # validate it (because the format is library-specific).
                   "parameters": {
                       "param1": "foo"
                   }
               }
           ],

           # Similar to other Kea components, NETCONF also uses logging.
           "loggers": [
               {
                   "name": "kea-netconf",
                   "output_options": [
                       {
                           "output": "/var/log/kea-netconf.log",
                           # Several additional parameters are possible in
                           # addition to the typical output.
                           # Flush determines whether logger flushes output
                           #  to a file.
                           # Maxsize determines maximum filesize before
                           # the file is being rotated.
                           # Maxver specifies the maximum number of
                           #  rotated files being kept.
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
=======================================

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
==============================================

.. note::

   Copies of example configurations presented within this section can be
   found in the Kea source code, under
   ``doc/examples/netconf/kea-dhcp6-operations``.

.. _operation-example-setup:

Setup of NETCONF Agent Operation Example
----------------------------------------

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

::

   {
       "Dhcp6": {
           "control-socket": {
               "socket-type": "unix",
               "socket-name": "/tmp/kea6-sock"
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

    # echo '{ "command": "config-get" }' | socat UNIX:/tmp/kea6-sock '-,ignoreeof'

The following is the example ``netconf.json`` configuration for
``kea-netconf``, to manage the Kea DHCPv6 server:

::

   {
       "Netconf":
       {
           "managed-servers":
           {
               "dhcp6":
               {
                   "control-socket":
                   {
                       "socket-type": "unix",
                       "socket-name": "/tmp/kea6-sock"
                   }
               }
           },

           "loggers":
           [
               {
                   "name": "kea-netconf",
                   "output_options":
                   [
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
       <socket-name>/tmp/kea6-sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

To populate this new configuration:

.. code-block:: console

    # sysrepocfg -d startup -f xml -i startup.xml kea-dhcp6-server

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
-------------------------------------------

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
       <socket-name>/tmp/kea6-sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

It is directly rejected by ``sysrepocfg``:

.. code-block:: console

    # sysrepocfg -d running -f xml -i BAD-schema.xml kea-dhcp6-server

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
       <socket-name>/tmp/kea6-sock</socket-name>
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
       <socket-name>/tmp/kea6-sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

In the last case, the misconfiguration is detected too late and the
change must be reverted in Sysrepo, e.g. using the startup datastore as
a backup. For this reason, please use the ``sysrepocfg`` ``--permanent``
/ ``-p`` option (or any similar feature of NETCONF clients) with care.

.. _operation-example-2pools:

NETCONF Operation Example with Two Pools
----------------------------------------

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
       <socket-name>/tmp/kea6-sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

This configuration is installed by:

.. code-block:: console

    # sysrepocfg -d running -f xml -i twopools.xml kea-dhcp6-server

.. _operation-example-2subnets:

NETCONF Operation Example with Two Subnets
------------------------------------------

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
       <socket-name>/tmp/kea6-sock</socket-name>
       <socket-type>unix</socket-type>
     </control-socket>
   </config>

This configuration is installed by:

.. code-block:: console

    # sysrepocfg -d running -f xml -i twosubnets.xml kea-dhcp6-server

.. _operation-example-logging:

NETCONF Operation Example with Logging
--------------------------------------

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
       <socket-name>/tmp/kea6-sock</socket-name>
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

::

   {
     "Dhcp6": {
       "control-socket": {
         "socket-name": "/tmp/kea6-sock",
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

Finally, any of the previous examples can be replayed using
``sysrepocfg`` in edit mode as follows:

.. code-block:: console

    # sysrepocfg -d running -f xml -e vi kea-dhcp6-server

or, of course, using a NETCONF client like ``netopeer2-cli`` from the
`Netopeer2 <https://github.com/CESNET/Netopeer2>`__ NETCONF Toolset.
