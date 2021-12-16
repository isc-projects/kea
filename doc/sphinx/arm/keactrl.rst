.. _keactrl:

*****************************
Managing Kea with ``keactrl``
*****************************

.. _keactrl-overview:

Overview
========

``keactrl`` is a shell script which controls the startup, shutdown, and
reconfiguration of the Kea servers (``kea-dhcp4``, ``kea-dhcp6``,
``kea-dhcp-ddns``, ``kea-ctrl-agent``, and ``kea-netconf``). It also
provides the means for checking the current status of the servers and
determining the configuration files in use.

``keactrl`` is available only when Kea is built from sources. When installing
Kea using native packages, the native ``systemd`` scripts are provided. See
:ref:`systemd` Section for details.

.. _keactrl-usage:

Command Line Options
====================

``keactrl`` is run as follows:

.. code-block:: console

   # keactrl <command> [-c keactrl-config-file] [-s server[,server,...]]

``<command>`` is one of the commands described in :ref:`keactrl-commands`.

The optional ``-c keactrl-config-file`` switch allows specification of
an alternate ``keactrl`` configuration file. (``--ctrl-config`` is a
synonym for ``-c``.) In the absence of ``-c``, ``keactrl`` uses the
default configuration file ``[kea-install-dir]/etc/kea/keactrl.conf``.

The optional ``-s server[,server,...]`` switch selects the servers to
which the command is issued. (``--server`` is a synonym for ``-s``.) If
absent, the command is sent to all servers enabled in the ``keactrl``
configuration file. If multiple servers are specified, they should be
separated by commas with no intervening spaces.

.. _keactrl-config-file:

The ``keactrl`` Configuration File
==================================

Depending on the administrator's requirements, it may not be
necessary to run all of the available servers.
The ``keactrl`` configuration file sets which servers are enabled and
which are disabled. The default configuration file is
``[kea-install-dir]/etc/kea/keactrl.conf``, but this can be overridden
on a per-command basis using the ``-c`` switch.

The contents of ``keactrl.conf`` are:

.. code-block:: bash

   # This is a configuration file for keactrl script which controls
   # the startup, shutdown, reconfiguration and gathering the status
   # of the Kea processes.

   # prefix holds the location where the Kea is installed.
   prefix=@prefix@

   # Location of Kea configuration file.
   kea_dhcp4_config_file=@sysconfdir@/@PACKAGE@/kea-dhcp4.conf
   kea_dhcp6_config_file=@sysconfdir@/@PACKAGE@/kea-dhcp6.conf
   kea_dhcp_ddns_config_file=@sysconfdir@/@PACKAGE@/kea-dhcp-ddns.conf
   kea_ctrl_agent_config_file=@sysconfdir@/@PACKAGE@/kea-ctrl-agent.conf
   kea_netconf_config_file=@sysconfdir@/@PACKAGE@/kea-netconf.conf

   # Location of Kea binaries.
   exec_prefix=@exec_prefix@
   dhcp4_srv=@sbindir@/kea-dhcp4
   dhcp6_srv=@sbindir@/kea-dhcp6
   dhcp_ddns_srv=@sbindir@/kea-dhcp-ddns
   ctrl_agent_srv=@sbindir@/kea-ctrl-agent
   netconf_srv=@sbindir@/kea-netconf

   # Start DHCPv4 server?
   dhcp4=yes

   # Start DHCPv6 server?
   dhcp6=yes

   # Start DHCP DDNS server?
   dhcp_ddns=no

   # Start Control Agent?
   ctrl_agent=yes

   # Start Netconf?
   netconf=no

   # Be verbose?
   kea_verbose=no

.. note::

   In the example above, strings of the form @something@ are replaced by
   the appropriate values when Kea is installed.

Setting the ``dhcp4``, ``dhcp6``, ``dhcp_ddns``, ``ctrl_agent``, and ``netconf``
parameters set to "yes" configures ``keactrl`` to manage (start,
reconfigure) all servers, i.e. ``kea-dhcp4``, ``kea-dhcp6``,
``kea-dhcp-ddns``, ``kea-ctrl-agent``, and ``kea-netconf``. When any of
these parameters is set to "no", ``keactrl`` ignores the
corresponding server when starting or reconfiguring Kea. Some daemons
(dhcp_ddns and netconf) are disabled by default.

By default, Kea servers managed by ``keactrl`` are located in
``[kea-install-dir]/sbin``. This should work for most installations. If
the default location needs to be altered, the paths
specified with the ``dhcp4_srv``, ``dhcp6_srv``, ``dhcp_ddns_srv``,
``ctrl_agent_srv``, and ``netconf_srv`` parameters should be modified.

The ``kea_verbose`` parameter specifies the verbosity of the servers
being started. When ``kea_verbose`` is set to "yes," the logging level of
the server is set to DEBUG. Modification of the logging severity in a
configuration file, as described in :ref:`logging`, will have no
effect as long as ``kea_verbose`` is set to "yes." Setting it to
"no" causes the server to use the logging levels specified in the
Kea configuration file. If no logging configuration is specified, the
default settings are used.

.. note::

   The verbosity for the server is set when it is started. Once started,
   the verbosity can only be changed by stopping the server and starting
   it again with the new value of the ``kea_verbose`` parameter.

.. _keactrl-commands:

Commands
========

The following commands are supported by ``keactrl``:

-  ``start`` - starts the selected servers.

-  ``stop`` - stops all running servers.

-  ``reload`` - triggers reconfiguration of the selected servers by
   sending the SIGHUP signal to them.

-  ``status`` - returns the status of the servers (active or inactive)
   and the names of the configuration files in use.

-  ``version`` - prints out the version of the ``keactrl`` tool itself,
   together with the versions of the Kea daemons.

Typical output from ``keactrl`` when starting the servers looks similar
to the following:

.. code-block:: console

   $ keactrl start
   INFO/keactrl: Starting kea-dhcp4 -c /usr/local/etc/kea/kea-dhcp4.conf -d
   INFO/keactrl: Starting kea-dhcp6 -c /usr/local/etc/kea/kea-dhcp6.conf -d
   INFO/keactrl: Starting kea-dhcp-ddns -c /usr/local/etc/kea/kea-dhcp-ddns.conf -d
   INFO/keactrl: Starting kea-ctrl-agent -c /usr/local/etc/kea/kea-ctrl-agent.conf -d
   INFO/keactrl: Starting kea-netconf -c /usr/local/etc/kea/kea-netconf.conf -d

Kea's servers create PID files upon startup. These files are used by
``keactrl`` to determine whether a given server is running. If one or more
servers are running when the start command is issued, the output
looks similar to the following:

.. code-block:: console

   $ keactrl start
   INFO/keactrl: kea-dhcp4 appears to be running, see: PID 10918, PID file: /usr/local/var/run/kea/kea.kea-dhcp4.pid.
   INFO/keactrl: kea-dhcp6 appears to be running, see: PID 10924, PID file: /usr/local/var/run/kea/kea.kea-dhcp6.pid.
   INFO/keactrl: kea-dhcp-ddns appears to be running, see: PID 10930, PID file: /usr/local/var/run/kea/kea.kea-dhcp-ddns.pid.
   INFO/keactrl: kea-ctrl-agent appears to be running, see: PID 10931, PID file: /usr/local/var/run/kea/kea.kea-ctrl-agent.pid.
   INFO/keactrl: kea-netconf appears to be running, see: PID 10123, PID file: /usr/local/var/run/kea/kea.kea-netconf.pid.

During normal shutdowns, these PID files are deleted; they may, however,
be left over as remnants following a system crash. It is possible,
though highly unlikely, that upon system restart the PIDs they contain
may actually refer to processes unrelated to Kea. This condition will
cause ``keactrl`` to decide that the servers are running, when in fact they
are not. In such a case the PID files listed in the ``keactrl`` output
must be manually deleted.

The following command stops all servers:

.. code-block:: console

   $ keactrl stop
   INFO/keactrl: Stopping kea-dhcp4...
   INFO/keactrl: Stopping kea-dhcp6...
   INFO/keactrl: Stopping kea-dhcp-ddns...
   INFO/keactrl: Stopping kea-ctrl-agent...
   INFO/keactrl: Stopping kea-netconf...

Note that the ``stop`` command attempts to stop all servers
regardless of whether they are "enabled" in ``keactrl.conf``. If any
of the servers are not running, an informational message is displayed as
in the ``stop`` command output below.

.. code-block:: console

   $ keactrl stop
   INFO/keactrl: kea-dhcp4 isn't running.
   INFO/keactrl: kea-dhcp6 isn't running.
   INFO/keactrl: kea-dhcp-ddns isn't running.
   INFO/keactrl: kea-ctrl-agent isn't running.
   INFO/keactrl: kea-netconf isn't running.

As already mentioned, the reconfiguration of each Kea server is
triggered by the SIGHUP signal. The ``reload`` command sends the SIGHUP
signal to any servers that are enabled in the ``keactrl`` configuration
file and that are currently running. When a server receives the SIGHUP signal
it rereads its configuration file and, if the new configuration is
valid, uses the new configuration. A reload is executed as follows:

.. code-block:: console

   $ keactrl reload
   INFO/keactrl: Reloading kea-dhcp4...
   INFO/keactrl: Reloading kea-dhcp6...
   INFO/keactrl: Reloading kea-dhcp-ddns...
   INFO/keactrl: Reloading kea-ctrl-agent...

If any of the servers are not running, an informational message is
displayed as in the ``reload`` command output below.
``kea-netconf`` does not support the SIGHUP signal. If its
configuration has changed, please stop and restart it for the change to
take effect.

.. code-block:: console

   $ keactrl stop
   INFO/keactrl: kea-dhcp4 isn't running.
   INFO/keactrl: kea-dhcp6 isn't running.
   INFO/keactrl: kea-dhcp-ddns isn't running.
   INFO/keactrl: kea-ctrl-agent isn't running.
   INFO/keactrl: kea-netconf isn't running.

.. note::

   NETCONF is an optional feature that is disabled by default and can be
   enabled during compilation. If Kea was compiled without NETCONF
   support, ``keactrl`` does not provide
   information about it. The NETCONF entries are still present in
   the ``keactrl.conf`` file, but NETCONF status is not shown and other
   commands ignore it.

.. note::

   Currently ``keactrl`` does not report configuration failures when the
   server is started or reconfigured. To check if the server's
   configuration succeeded, the Kea log must be examined for errors. By
   default, the log is written to the `syslog` file.

Sometimes it is useful to check which servers are running. The
``status`` command reports this, with typical output that looks like:

.. code-block:: console

   $ keactrl status
   DHCPv4 server: active
   DHCPv6 server: inactive
   DHCP DDNS: active
   Control Agent: active
   Netconf agent: inactive
   Kea configuration file: /usr/local/etc/kea/kea.conf
   Kea DHCPv4 configuration file: /usr/local/etc/kea/kea-dhcp4.conf
   Kea DHCPv6 configuration file: /usr/local/etc/kea/kea-dhcp6.conf
   Kea DHCP DDNS configuration file: /usr/local/etc/kea/kea-dhcp-ddns.conf
   Kea Control Agent configuration file: /usr/local/etc/kea/kea-ctrl-agent.conf
   Kea Netconf configuration file: /usr/local/etc/kea/kea-netconf.conf
   keactrl configuration file: /usr/local/etc/kea/keactrl.conf

``keactrl status`` offers basic reporting capabilities. For more extensive insight
into Kea's health and status, consider deploying Stork. For details, see :ref:`stork`.

.. _keactrl-overriding-servers:

Overriding the Server Selection
===============================

The optional ``-s`` switch allows the selection of the server(s) to which
the ``keactrl`` command is issued. For example, the following instructs
``keactrl`` to stop the ``kea-dhcp4`` and ``kea-dhcp6`` servers and
leave the ``kea-dhcp-ddns`` and ``kea-ctrl-agent`` running:

.. code-block:: console

   $ keactrl stop -s dhcp4,dhcp6

Similarly, the following starts only the ``kea-dhcp4`` and
``kea-dhcp-ddns`` servers, but not ``kea-dhcp6`` or ``kea-ctrl-agent``.

.. code-block:: console

   $ keactrl start -s dhcp4,dhcp_ddns

Note that the behavior of the ``-s`` switch with the ``start`` and
``reload`` commands is different from its behavior with the ``stop``
command. On ``start`` and ``reload``, ``keactrl`` checks whether the
servers given as parameters to the ``-s`` switch are enabled in the
``keactrl`` configuration file; if not, the server is ignored. For
``stop``, however, this check is not made; the command is applied to all
listed servers, regardless of whether they have been enabled in the
file.

The following keywords can be used with the ``-s`` command-line option:

-  ``dhcp4`` for ``kea-dhcp4``.

-  ``dhcp6`` for ``kea-dhcp6``.

-  ``dhcp_ddns`` for ``kea-dhcp-ddns``.

-  ``ctrl_agent`` for ``kea-ctrl-agent``.

-  ``netconf`` for ``kea-netconf``.

-  ``all`` for all servers (default).

.. _systemd:

Native Packages and ``systemd``
===============================

``keactrl`` is a script that was developed to assist in managing Kea processes.
However, all modern operating systems have their own process-management scripts,
such as ``systemd``. In general, these native scripts should be used,
as they have several advantages. ``systemd`` scripts handle processes in a uniform
way, so Kea is handled in a similar fashion to HTTP or a mail
server. Second and more importantly, ``systemd`` allows dependencies to be defined
between services. For example, it is easy to specify that the Kea server should not start
until the network interfaces are operational. Using native scripts also has other benefits, such as
the ability to enable or disable services using commands, and the ability to temporarily start a disabled
service.

Thus, it is recommended to use ``systemctl`` commands if they are available. Native
Kea packages do not provide ``keactrl``; ``systemctl`` service definitions are
provided instead. Consult the system documentation for details.

Briefly, here are example commands to check status, start, stop, and restart various Kea daemons:

.. code-block:: console

   # systemctl status isc-kea-ctrl-agent
   # systemctl start isc-kea-dhcp4-server
   # systemctl stop isc-kea-dhcp6-server
   # systemctl restart isc-kea-dhcp-ddns-server

Note that the service names may be slightly different between Linux distributions; in general,
we have followed the naming conventions in third-party packages. In particular,
some systems may not have the `isc-` prefix.
