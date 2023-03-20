.. _netconf:

YANG/NETCONF
============

.. _netconf-overview:

Overview
--------

The Network Configuration Protocol, or NETCONF, is a network management protocol defined
in `RFC 4741 <https://tools.ietf.org/html/rfc4741>`__. It uses YANG modeling language,
defined in `RFC 6020 <https://tools.ietf.org/html/rfc6020>`__, to provide a uniform way
of handling the configuration syntax of varied networking devices. Kea provides optional
support for a YANG/NETCONF interface with the ``kea-netconf`` agent.

.. _netconf-install:

Installing NETCONF
------------------

To get its NETCONF capabilities, Kea requires the v2 versions of libyang and
sysrepo. The specific versions that were thoroughly tested with Kea are:

* libyang v2.1.4
* sysrepo v2.2.12
* libyang-cpp v1.1.0 (ae7d649ea75da081725c119dd553b2ef3121a6f8)
* sysrepo-cpp v1.1.0 (02634174ffc60568301c3d9b9b7cf710cff6a586)

.. note::

    If, for whatever reason, an older version is desired, the versions below
    are the furthest back one can go. Backtracking even further has resulted
    either in compilation failure or in improper functioning in ISC internal
    testing, depending on which component is reverted.

    * libyang v2.0.256 (56d4e07ef1cdeab3eb2e6700247f83ec9148edcc)
    * sysrepo v2.1.84
    * libyang-cpp v1.1.0 (7824d9a862f2dc1d8ad4f6a90ab6cee9200f7c81)
    * sysrepo-cpp v1.1.0 (e66b2f0c53a428eeb743d355cf86fb30e8e491f1)

.. note::

    kea-netconf may be compatible with later versions, but if it is
    not hereby documented, it is not guaranteed.

Use packages if they are provided by the system. If not, users can
build from sources, which should work on all popular operating systems.

.. _libyang-install-sources:

Installing ``libyang`` From Sources
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: console

    $ git clone https://github.com/CESNET/libyang.git
    $ cd libyang
    $ git checkout v2.1.4
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ make install

.. _sysrepo-install-sources:

Installing ``sysrepo`` From Sources
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: console

    $ git clone https://github.com/sysrepo/sysrepo.git
    $ cd sysrepo
    $ git checkout v2.2.12
    $ mkdir build
    $ cd build
    $ cmake -DREPO_PATH=/etc/sysrepo ..
    $ make
    $ make install  # without sudo if you're doing development and want to run unit tests

.. _libyang-cpp-install-sources:

Installing ``libyang-cpp`` From Sources
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: console

    $ git clone https://github.com/CESNET/libyang-cpp.git
    $ cd libyang-cpp
    $ git checkout ae7d649ea75da081725c119dd553b2ef3121a6f8
    $ mkdir build
    $ cd build
    $ cmake -DBUILD_TESTING=OFF ..
    $ make
    $ make install

.. _sysrepo-cpp-install-sources:

Installing ``sysrepo-cpp`` From Sources
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: console

    $ git clone https://github.com/sysrepo/sysrepo-cpp.git
    $ cd sysrepo-cpp
    $ git checkout 02634174ffc60568301c3d9b9b7cf710cff6a586
    $ mkdir build
    $ cd build
    $ cmake -DBUILD_TESTING=OFF ..
    $ make
    $ make install

.. _compiling-with-netconf:

Compiling With NETCONF
----------------------

1.  Obtain the Kea sources.

.. code-block:: console

    $ git clone gitlab.isc.org/isc-projects/kea.git
    $ cd kea

2. Configure the build.

.. code-block:: console

    $ autoreconf -f -i
    $ ./configure --with-libyang --with-libyang-cpp --with-sysrepo --with-sysrepo-cpp

.. note::

    If any of the libraries are installed in a custom location, the
    ``--with`` flags accept the installations paths as values.

3. Check ``config.report`` for NETCONF support.

::

    NETCONF:
      yes

      libyang:
        LIBYANG_CPPFLAGS:
        LIBYANG_INCLUDEDIR:    -I/usr/local/include
        LIBYANG_LIBS:          -L/usr/local/lib -lyang -Wl,-R/usr/local/lib -lyang
        LIBYANG_PREFIX:        /usr/local
        LIBYANG_VERSION:       2.1.4

      libyang-cpp:
        LIBYANGCPP_CPPFLAGS:
        LIBYANGCPP_INCLUDEDIR: -I/usr/local/include
        LIBYANGCPP_LIBS:       -L/usr/local/lib -lyang-cpp -Wl,-R/usr/local/lib -lyang-cpp
        LIBYANGCPP_PREFIX:     /usr/local
        LIBYANGCPP_VERSION:    1.1.0

      sysrepo:
        SYSREPO_CPPFLAGS:
        SYSREPO_INCLUDEDIR:    -I/usr/local/include
        SYSREPO_LIBS:          -L/usr/local/lib -lsysrepo -Wl,-R/usr/local/lib -lsysrepo
        SYSREPO_PREFIX:        /usr/local
        SYSREPO_VERSION:       2.2.12

        SR_REPO_PATH:          /etc/sysrepo
        SR_PLUGINS_PATH:       /usr/local/lib/sysrepo/plugins
        SRPD_PLUGINS_PATH:     /usr/local/lib/sysrepo-plugind/plugins

      sysrepo-cpp:
        SYSREPOCPP_CPPFLAGS:
        SYSREPOCPP_INCLUDEDIR: -I/usr/local/include
        SYSREPOCPP_LIBS:       -L/usr/local/lib -lsysrepo-cpp -Wl,-R/usr/local/lib -lsysrepo-cpp
        SYSREPOCPP_PREFIX :    /usr/local
        SYSREPOCPP_VERSION:    1.1.0

4. Build as you normally would.

    $ make

.. _sysrepo-overview:

Quick Sysrepo Overview
----------------------

This section offers a brief overview of a subset of available
functions in Sysrepo. For more complete information, see the
`Sysrepo homepage <https://www.sysrepo.org>`__.

In YANG, configurations and state data are described in YANG syntax
in module files named: ``<module-name>[@<revision>].yang``

The revision part is optional and has ``YYYY-MM-DD`` format. An alternate
XML syntax YIN is defined but less user-friendly. Top-level modules are
named in Kea models (a short version of schema models).

There are two major modules that Kea is able to support: ``kea-dhcp4-server`` and
``kea-dhcp6-server``. While there is an active effort in the DHC working group at
IETF to develop a DHCPv6 YANG model, a similar initiative in the past for DHCPv4
failed. Therefore, Kea uses its own dedicated models for DHCPv4 and DHCPv6 but
partially supports the IETF model for DHCPv6.

All of the models have extra modules as dependencies. The dependency modules are also provided.
All of the modules can be found in ``src/share/yang/modules`` in sources and in
``share/kea/yang/modules`` in the installation directory. This directory will be
referred to as `${share_directory}` in the commands below.

To install modules from sources, or upgrade them if you have older revisions
installed, run the following command. In the case of a revision upgrade, YANG
data will be migrated automatically to the new module schema.

.. code-block:: console

    $ ${share_directory}/yang/modules/utils/reinstall.sh

However, if there is resistance in the upgrade process, and data can be recreated from a NETCONF
client or through other means, Kea modules can be easily uninstalled before installing again with:

.. code-block:: console

    $ ${share_directory}/yang/modules/utils/reinstall.sh -u

The script should be able to pick up on the Sysrepo installation.
If not, there is a flag that was historically used to point to it:

.. code-block:: console

    $ ./src/share/yang/modules/utils/reinstall.sh -s /path/to/sysrepo

To individually install all modules:

.. code-block:: console

    $ cd ./src/share/yang/modules
    $ sysrepoctl -i ./ietf-dhcpv6-server*.yang
    $ sysrepoctl -i ./kea-dhcp4-server*.yang
    $ sysrepoctl -i ./kea-dhcp6-server*.yang
    ...

The installation should look similar to the following:

.. code-block:: console

    $ ./src/share/yang/modules/utils/reinstall.sh
    [INF] Connection 2 created.
    [INF] Module "keatest-module" was installed.
    [INF] File "keatest-module@2022-11-30.yang" was installed.
    [INF] No datastore changes to apply.
    [INF] Connection 4 created.
    [ERR] Module "ietf-interfaces@2018-02-20" already installed.
    [INF] No datastore changes to apply.
    [INF] Connection 7 created.
    [ERR] Module "ietf-dhcpv6-client" is already in sysrepo.
    [INF] No datastore changes to apply.
    [INF] Connection 9 created.
    [ERR] Module "ietf-dhcpv6-relay" is already in sysrepo.
    [INF] No datastore changes to apply.
    [INF] Connection 11 created.
    [ERR] Module "ietf-dhcpv6-server" is already in sysrepo.
    [INF] No datastore changes to apply.
    [INF] Connection 13 created.
    [ERR] Write permission "ietf-yang-types" check failed.
    [INF] No datastore changes to apply.
    [INF] Connection 15 created.
    [ERR] Module "ietf-dhcpv6-options" is already in sysrepo.
    [INF] No datastore changes to apply.
    [INF] Connection 17 created.
    [ERR] Module "ietf-dhcpv6-types" is already in sysrepo.
    [INF] No datastore changes to apply.
    [INF] Connection 21 created.
    [INF] Module "kea-types" was installed.
    [INF] File "kea-types@2019-08-12.yang" was installed.
    [INF] No datastore changes to apply.
    [INF] Connection 23 created.
    [INF] Module "kea-dhcp-types" was installed.
    [INF] File "kea-dhcp-types@2022-11-30.yang" was installed.
    [INF] No datastore changes to apply.
    [INF] Connection 25 created.
    [INF] Module "kea-dhcp-ddns" was installed.
    [INF] File "kea-dhcp-ddns@2022-07-27.yang" was installed.
    [INF] No datastore changes to apply.
    [INF] Connection 27 created.
    [INF] Module "kea-ctrl-agent" was installed.
    [INF] File "kea-ctrl-agent@2019-08-12.yang" was installed.
    [INF] No datastore changes to apply.
    [INF] Connection 29 created.
    [INF] Module "kea-dhcp4-server" was installed.
    [INF] File "kea-dhcp4-server@2022-11-30.yang" was installed.
    [INF] No datastore changes to apply.
    [INF] Connection 31 created.
    [INF] Module "kea-dhcp6-server" was installed.
    [INF] File "kea-dhcp6-server@2022-11-30.yang" was installed.
    [INF] No datastore changes to apply.

It is possible to confirm whether the modules are imported correctly.
The list of currently installed YANG modules should be similar to this:

.. code-block:: console

    $ sysrepoctl -l
    Sysrepo repository: /etc/sysrepo

    Module Name                | Revision   | Flags | Owner     | Startup Perms | Submodules | Features
    ---------------------------------------------------------------------------------------------------
    ietf-datastores            | 2018-02-14 | I     | user:user | 444           |            |
    ietf-dhcpv6-client         | 2018-09-04 | I     | user:user | 600           |            |
    ietf-dhcpv6-options        | 2018-09-04 | I     | user:user | 600           |            |
    ietf-dhcpv6-relay          | 2018-09-04 | I     | user:user | 600           |            |
    ietf-dhcpv6-server         | 2018-09-04 | I     | user:user | 600           |            |
    ietf-dhcpv6-types          | 2018-09-04 | I     | user:user | 600           |            |
    ietf-inet-types            | 2013-07-15 | I     | user:user | 444           |            |
    ietf-interfaces            | 2018-02-20 | I     | user:user | 600           |            |
    ietf-netconf               | 2013-09-29 | I     | user:user | 644           |            |
    ietf-netconf-acm           | 2018-02-14 | I     | user:user | 600           |            |
    ietf-netconf-notifications | 2012-02-06 | I     | user:user | 644           |            |
    ietf-netconf-with-defaults | 2011-06-01 | I     | user:user | 444           |            |
    ietf-origin                | 2018-02-14 | I     | user:user | 444           |            |
    ietf-yang-library          | 2019-01-04 | I     | user:user | 644           |            |
    ietf-yang-metadata         | 2016-08-05 | i     |           |               |            |
    ietf-yang-schema-mount     | 2019-01-14 | I     | user:user | 644           |            |
    ietf-yang-types            | 2013-07-15 | I     | user:user | 444           |            |
    kea-ctrl-agent             | 2019-08-12 | I     | user:user | 600           |            |
    kea-dhcp-ddns              | 2022-07-27 | I     | user:user | 600           |            |
    kea-dhcp-types             | 2022-11-30 | I     | user:user | 600           |            |
    kea-dhcp4-server           | 2022-11-30 | I     | user:user | 600           |            |
    kea-dhcp6-server           | 2022-11-30 | I     | user:user | 600           |            |
    kea-types                  | 2019-08-12 | I     | user:user | 600           |            |
    keatest-module             | 2022-11-30 | I     | user:user | 600           |            |
    sysrepo-monitoring         | 2022-04-08 | I     | user:user | 600           |            |
    sysrepo-plugind            | 2022-03-10 | I     | user:user | 644           |            |
    yang                       | 2022-06-16 | I     | user:user | 444           |            |

    Flags meaning: I - Installed/i - Imported; R - Replay support

To reinstall a module, if the revision YANG entry was bumped, simply installing
it will update it automatically. Otherwise, it must first be uninstalled:

.. code-block:: console

    $ sysrepoctl -u kea-dhcp4-server

If the module is used (i.e. imported) by other modules, it can be uninstalled
only after the dependent modules have first been uninstalled.
Installation and uninstallation must be done in dependency order and
reverse-dependency order accordingly.

.. _netconf-models:

Supported YANG Models
---------------------

The only currently supported models are ``kea-dhcp4-server`` and
``kea-dhcp6-server``. There is partial support for
``ietf-dhcpv6-server``, but the primary focus of testing has been on Kea DHCP
servers. Other models (``kea-dhcp-ddns`` and ``kea-ctrl-agent``)
are currently not supported.

.. _using-netconf:

Using the NETCONF Agent
-----------------------

The NETCONF agent follows this algorithm:

-  For each managed server, get the initial configuration from the
   server through the control socket.

-  Open a connection with the Sysrepo environment and establish two
   sessions with the startup and running datastores.

-  Check that the used (not-essential) and required (essential) modules are
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
is controlled by several configuration flags, which can be set in the
global scope or in a specific managed-server scope. If the latter,
the value defined in the managed-server scope takes precedence. These
flags are:

-  ``boot-update`` - controls the initial configuration phase; when
   ``true`` (the default), the initial configuration retrieved from the
   classic Kea server JSON configuration file is loaded first, and then
   the startup YANG model is loaded. This setting lets administrators
   define a control socket in the local JSON file and then download the
   configuration from YANG. When set to ``false``, this phase is skipped.

-  ``subscribe-changes`` - controls the module change
   subscription; when ``true`` (the default), a module change callback is
   subscribed, but when ``false`` the phase is skipped and running
   configuration updates are disabled. When set to ``true``, the running
   datastore is used to subscribe for changes.

-  ``validate-changes`` - controls how Kea monitors changes in
   the Sysrepo configuration. Sysrepo offers two stages where Kea can
   interact: validation and application. At the validation (or
   ``SR_EV_CHANGE`` event, in the Sysrepo naming convention) stage, Kea
   retrieves the newly committed configuration and verifies it. If the
   configuration is incorrect for any reason, the Kea servers reject it
   and the error is propagated back to the Sysrepo, which then returns
   an error. This step only takes place if ``validate-changes`` is set to
   ``true``. In the application (or ``SR_EV_UPDATE`` event in the Sysrepo naming
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

With module change subscriptions enabled, the ``kea-netconf`` daemon
monitors any configuration changes as they appear in the Sysrepo. Such
changes can be done using the ``sysrepocfg`` tool or remotely using any
NETCONF client. For details, please see the Sysrepo documentation or
:ref:`operation-example`.
Those tools can be used to modify YANG configurations in the running
datastore. Note that committed configurations are only updated in the
running datastore; to keep them between server reboots they must be
copied to the startup datastore.

When module changes are tracked (using ``subscribe-changes`` set to
``true``) and the running configuration has changed (e.g. using
``sysrepocfg`` or any NETCONF client), the callback validates the
modified configuration (if ``validate-changes`` was not set to ``false``)
and runs a second time to apply the new configuration. If the validation
fails, the callback is still called again but with an ``SR_EV_ABORT``
(vs. ``SR_EV_DONE``) event with rollback changes.

The returned code of the callback on an ``SR_EV_DONE`` event is ignored, as it is
too late to refuse a bad configuration.

There are four ways in which a modified YANG configuration might
be incorrect:

1. It could be non-compliant with the schema, e.g. an unknown entry, missing a
   mandatory entry, a value with a bad type, or not matching a constraint.

2. It could fail to be translated from YANG to JSON, e.g. an invalid user
   context.

3. It could fail Kea server sanity checks, e.g. an out-of-subnet-pool range
   or an unsupported database type.

4. The syntax may be correct and pass server sanity checks but the
   configuration could fail to run, e.g. the configuration specifies database
   credentials but the database refuses the connection.

The first case is handled by Sysrepo. The second and third cases are
handled by ``kea-netconf`` in the validation phase (if not disabled by
setting ``validate-changes`` to ``true``). The last case causes the
application phase to fail without a sensible report to Sysrepo.

The managed Kea servers and agents are described in the
``managed-servers`` section. Each sub-section begins with the service
name: ``dhcp4``, ``dhcp6``, ``d2`` (the DHCP-DDNS server does not
support the control-channel feature yet), and ``ca`` (the control
agent).

Each managed server entry may contain:

-  control flags - ``boot-update``, ``subscribe-changes``, and/or ``validate-changes``.

-  ``model`` - specifies the YANG model/module name. For each service,
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
   server control channel, which uses UNIX sockets; ``http`` uses
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

Hook libraries can be loaded by the NETCONF agent just as with other
servers or agents; however, currently no hook points are defined. The
``hooks-libraries`` list contains the list of hook libraries that
should be loaded by ``kea-netconf``, along with their configuration
information specified with ``parameters``.

Please consult :ref:`logging` for details on how to configure
logging. The name of the NETCONF agent's main logger is ``kea-netconf``, as
given in the example above.

.. _netconf-example:

A ``kea-netconf`` Configuration Example
---------------------------------------

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
                   "comment": "DHCPv4 server",
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

           // kea-netconf is able to load hook libraries that augment its operation.
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

``kea-netconf`` accepts the following command-line switches:

-  ``-c file`` - specifies the configuration file.

-  ``-d`` - specifies whether the agent logging should be switched to
   debug/verbose mode. In verbose mode, the logging severity and
   debuglevel specified in the configuration file are ignored and
   "debug" severity and the maximum debuglevel (99) are assumed. The
   flag is convenient for temporarily switching the server into maximum
   verbosity, e.g. when debugging.

-  ``-t file`` - specifies the configuration file to be tested.
   ``kea-netconf`` attempts to load it and conducts sanity checks;
   certain checks are possible only while running the actual server. The
   actual status is reported with exit code (0 = configuration appears valid,
   1 = error encountered). Kea prints out log messages to standard
   output and error to standard error when testing the configuration.

-  ``-v`` - displays the version of ``kea-netconf`` and exits.

-  ``-V`` - displays the extended version information for ``kea-netconf``
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
possible to rename interfaces; for instance, on Linux with an ens38
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
The following is an example control socket specification for the Kea
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

The current configuration of the server can be fetched via a control
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

.. note::

    kea-netconf fetches the entire configuration from any Sysrepo datastore in a
    single get-config NETCONF operation. It underwent an extensive overhaul
    from the approach prior to Kea 2.3.2 where a get-config operation was done
    for each leaf and leaf-list node. Because of the broad changes, kea-netconf
    is considered experimental.

.. _operation-example-errors:

Error Handling in NETCONF Operation Example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are four classes of issues with configurations applied via
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
server and fails to validate, as in this ``BAD-config.xml`` file:

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

.. _migrating-yang-data:

Migrating YANG Data from a prior Sysrepo version
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Shut down ``kea-netconf``. This makes sure that backups for both datastores
are done at the same configuration state and no change happens between exporting them.

2. Make data backups for all YANG modules, one XML for each datastore.

.. code-block:: console

    $ sysrepocfg --datastore running --export=save.xml --format=xml
    $ sysrepocfg --datastore startup --export=save.xml --format=xml

.. note::

    Sysrepo v0 does not support import/export of all YANG modules. This capability was added in
    Sysrepo v1. Users that are migrating from Sysrepo v0 will need to do per-module backups. This has
    the added benefit of isolating potential failures and preventing them from affecting all
    modules. The command is the same except it has the module name added to it at the end.

    .. code-block:: console

        $ sysrepocfg --datastore running --export=save.xml --format=xml kea-dhcp6-server
        $ sysrepocfg --datastore startup --export=save.xml --format=xml kea-dhcp6-server

3. Upgrade Sysrepo to the newer version and then:

.. code-block:: console

    $ sysrepocfg --datastore running --edit=save.xml
    $ sysrepocfg --datastore startup --edit=save.xml
