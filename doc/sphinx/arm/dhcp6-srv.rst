.. _dhcp6:

*****************
The DHCPv6 Server
*****************

.. _dhcp6-start-stop:

Starting and Stopping the DHCPv6 Server
=======================================

It is recommended that the Kea DHCPv6 server be started and stopped
using ``keactrl`` (described in :ref:`keactrl`); however, it is also
possible to run the server directly. It accepts the following
command-line switches:

-  ``-c file`` - specifies the configuration file. This is the only
   mandatory switch.

-  ``-d`` - specifies whether the server logging should be switched to
   debug/verbose mode. In verbose mode, the logging severity and debuglevel
   specified in the configuration file are ignored; "debug" severity
   and the maximum debuglevel (99) are assumed. The flag is convenient
   for temporarily switching the server into maximum verbosity, e.g.
   when debugging.

-  ``-p server-port`` - specifies the local UDP port on which the server
   will listen. This is only useful during testing, as a DHCPv6 server
   listening on ports other than the standard ones will not be able to
   handle regular DHCPv6 queries.

-  ``-P client-port`` - specifies the remote UDP port to which the
   server will send all responses. This is only useful during testing,
   as a DHCPv6 server sending responses to ports other than the standard
   ones will not be able to handle regular DHCPv6 queries.

-  ``-t file`` - specifies a configuration file to be tested. Kea-dhcp6
   will load it, check it, and exit. During the test, log messages are
   printed to standard output and error messages to standard error. The
   result of the test is reported through the exit code (0 =
   configuration looks ok, 1 = error encountered). The check is not
   comprehensive; certain checks are possible only when running the
   server.

-  ``-v`` - displays the Kea version and exits.

-  ``-V`` - displays the Kea extended version with additional parameters
   and exits. The listing includes the versions of the libraries
   dynamically linked to Kea.

-  ``-W`` - displays the Kea configuration report and exits. The report
   is a copy of the ``config.report`` file produced by ``./configure``;
   it is embedded in the executable binary.

On startup, the server will detect available network interfaces and will
attempt to open UDP sockets on all interfaces mentioned in the
configuration file. Since the DHCPv6 server opens privileged ports, it
requires root access. This daemon must be run as root.

During startup, the server will attempt to create a PID file of the
form: [**runstatedir**]/kea/[**conf name**].kea-dhcp6.pid where:

-  ``runstatedir``: The value as passed into the build configure
   script; it defaults to "/usr/local/var/run". Note that this value may be
   overridden at runtime by setting the environment variable
   ``KEA_PIDFILE_DIR``, although this is intended primarily for testing
   purposes.

-  ``conf name``: The configuration file name used to start the server,
   minus all preceding paths and the file extension. For example, given
   a pathname of "/usr/local/etc/kea/myconf.txt", the portion used would
   be "myconf".

If the file already exists and contains the PID of a live process, the
server will issue a DHCP6_ALREADY_RUNNING log message and exit. It is
possible, though unlikely, that the file is a remnant of a system crash
and the process to which the PID belongs is unrelated to Kea. In such a
case it would be necessary to manually delete the PID file.

The server can be stopped using the ``kill`` command. When running in a
console, the server can also be shut down by pressing ctrl-c. It detects
the key combination and shuts down gracefully.

.. _dhcp6-configuration:

DHCPv6 Server Configuration
===========================

Introduction
------------

This section explains how to configure the DHCPv6 server using a
configuration file. Before DHCPv6 is started, its configuration file must
be created. The basic configuration is as follows:

::

   {
   # DHCPv6 configuration starts on the next line
   "Dhcp6": {

   # First we set up global values
       "valid-lifetime": 4000,
       "renew-timer": 1000,
       "rebind-timer": 2000,
       "preferred-lifetime": 3000,

   # Next we set up the interfaces to be used by the server.
       "interfaces-config": {
           "interfaces": [ "eth0" ]
       },

   # And we specify the type of lease database
       "lease-database": {
           "type": "memfile",
           "persist": true,
           "name": "/var/lib/kea/dhcp6.leases"
       },

   # Finally, we list the subnets from which we will be leasing addresses.
       "subnet6": [
           {
               "subnet": "2001:db8:1::/64",
               "pools": [
                    {
                        "pool": "2001:db8:1::1-2001:db8:1::ffff"
                    }
                ]
           }
       ]
   # DHCPv6 configuration ends with the next line
   }

   }

The following paragraphs provide a brief overview of the parameters in
the above example, along with their format. Subsequent sections of this
chapter go into much greater detail for these and other parameters.

The lines starting with a hash (#) are comments and are ignored by the
server; they do not impact its operation in any way.

The configuration starts in the first line with the initial opening
curly bracket (or brace). Each configuration must contain an object
specifying the configuration of the Kea module using it. In the example
above this object is called ``Dhcp6``.

.. note::

   In the current Kea release it is possible to specify configurations
   of multiple modules within a single configuration file, but this is
   not recommended and support for it was removed in 1.7.10 release,
   including the ``Logging`` object: its previous content, the list
   of loggers, must now be inside the ``Dhcp6`` object.

The Dhcp6 configuration starts with the ``"Dhcp6": {`` line and ends
with the corresponding closing brace (in the above example, the brace
after the last comment). Everything defined between those lines is
considered to be the Dhcp6 configuration.

In general, the order in which those parameters appear does not
matter, but there are two caveats. The first one is to remember that the
configuration file must be well-formed JSON. That means that the
parameters for any given scope must be separated by a comma, and there
must not be a comma after the last parameter. When reordering a
configuration file, keep in mind that moving a parameter to or from the
last position in a given scope may also require moving the comma. The
second caveat is that it is uncommon — although legal JSON — to repeat
the same parameter multiple times. If that happens, the last occurrence
of a given parameter in a given scope is used, while all previous
instances are ignored. This is unlikely to cause any confusion as there
are no real-life reasons to keep multiple copies of the same parameter
in the configuration file.

The first few DHCPv6 configuration elements
define some global parameters. ``valid-lifetime`` defines how long the
addresses (leases) given out by the server are valid. If nothing
changes, a client that got an address is allowed to use it for 4000
seconds. (Note that integer numbers are specified as is, without any
quotes around them.) The address will become deprecated in 3000 seconds,
i.e. clients are allowed to keep old connections, but can't use this
address for creating new connections. ``renew-timer`` and
``rebind-timer`` are values (also in seconds) that define T1 and T2 timers that govern
when the client will begin the renewal and rebind procedures.

The ``interfaces-config`` map specifies the server configuration
concerning the network interfaces on which the server should listen to
the DHCP messages. The ``interfaces`` parameter specifies a list of
network interfaces on which the server should listen. Lists are opened
and closed with square brackets, with elements separated by commas. To
listen on two interfaces, the ``interfaces-config`` should look like
this:

::

   "interfaces-config": {
       "interfaces": [ "eth0", "eth1" ]
   },

The next couple of lines define the lease database, the place where the
server stores its lease information. This particular example tells the
server to use ``memfile``, which is the simplest (and fastest) database
backend. It uses an in-memory database and stores leases on disk in a
CSV (comma-separated values) file. This is a very simple configuration; usually the lease
database configuration is more extensive and contains additional
parameters. Note that ``lease-database`` is an object and opens up a new
scope, using an opening brace. Its parameters (just one in this example:
``type``) follow. If there were more than one, they would be separated
by commas. This scope is closed with a closing brace. As more parameters
for the Dhcp6 definition follow, a trailing comma is present.

Finally, we need to define a list of IPv6 subnets. This is the most
important DHCPv6 configuration structure, as the server uses that
information to process clients' requests. It defines all subnets from
which the server is expected to receive DHCP requests. The subnets are
specified with the ``subnet6`` parameter. It is a list, so it starts and
ends with square brackets. Each subnet definition in the list has
several attributes associated with it, so it is a structure and is
opened and closed with braces. At a minimum, a subnet definition has to
have at least two parameters: ``subnet`` (which defines the whole
subnet) and ``pools`` (which is a list of dynamically allocated pools
that are governed by the DHCP server).

The example contains a single subnet. If more than one were defined,
additional elements in the ``subnet6`` parameter would be specified and
separated by commas. For example, to define two subnets, the following
syntax would be used:

::

   "subnet6": [
       {
           "pools": [ { "pool": "2001:db8:1::/112" } ],
           "subnet": "2001:db8:1::/64"
       },
       {
           "pools": [ { "pool": "2001:db8:2::1-2001:db8:2::ffff" } ],
           "subnet": "2001:db8:2::/64"
       }
   ]

Note that indentation is optional and is used for aesthetic purposes
only. In some cases it may be preferable to use more compact notation.

After all the parameters are specified, we have two contexts open: global
and Dhcp6; thus, we need two closing curly brackets to close them.

Lease Storage
-------------

All leases issued by the server are stored in the lease database.
Currently there are four database backends available: memfile (which is
the default backend), MySQL, PostgreSQL, and Cassandra.

Memfile - Basic Storage for Leases
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The server is able to store lease data in different repositories. Larger
deployments may elect to store leases in a database.
:ref:`database-configuration6` describes this option. In
typical smaller deployments, though, the server will store lease
information in a CSV file rather than a database. As well as requiring
less administration, an advantage of using a file for storage is that it
eliminates a dependency on third-party database software.

The configuration of the file backend (memfile) is controlled through
the Dhcp6/lease-database parameters. The ``type`` parameter is mandatory
and it specifies which storage for leases the server should use. The
value of ``"memfile"`` indicates that the file should be used as the
storage. The following list gives additional optional parameters that
can be used to configure the memfile backend.

-  ``persist``: controls whether the new leases and updates to existing
   leases are written to the file. It is strongly recommended that the
   value of this parameter be set to ``true`` at all times during the
   server's normal operation. Not writing leases to disk means that if a
   server is restarted (e.g. after a power failure), it will not know
   which addresses have been assigned. As a result, it may assign new clients
   addresses that are already in use. The value of
   ``false`` is mostly useful for performance-testing purposes. The
   default value of the ``persist`` parameter is ``true``, which enables
   writing lease updates to the lease file.

-  ``name``: specifies an absolute location of the lease file in which
   new leases and lease updates will be recorded. The default value for
   this parameter is ``"[kea-install-dir]/var/lib/kea/kea-leases6.csv"``.

-  ``lfc-interval``: specifies the interval, in seconds, at which the
   server will perform a lease file cleanup (LFC). This removes
   redundant (historical) information from the lease file and
   effectively reduces the lease file size. The cleanup process is
   described in more detail later in this section. The
   default value of the ``lfc-interval`` is ``3600``. A value of 0
   disables the LFC.

-  ``max-row-errors``: when the server loads a lease file, it is processed
   row by row, each row containing a single lease. If a row is flawed and
   cannot be processed correctly the server will log it, discard the row,
   and go on to the next row. This parameter can be used to set a limit on
   the number of such discards that may occur after which the server will
   abandon the effort and exit.  The default value of 0 disables the limit
   and allows the server to process the entire file, regardless of how many
   rows are discarded.

An example configuration of the memfile backend is presented below:

::

   "Dhcp6": {
       "lease-database": {
           "type": "memfile",
           "persist": true,
           "name": "/tmp/kea-leases6.csv",
           "lfc-interval": 1800,
           "max-row-errors": 100
       }
   }

This configuration selects the ``/tmp/kea-leases6.csv`` as the storage
for lease information and enables persistence (writing lease updates to
this file). It also configures the backend to perform a periodic cleanup
of the lease file every 30 minutes and sets the maximum number of row
errors to 100.


It is important to know how the lease file contents are organized to
understand why the periodic lease file cleanup is needed. Every time the
server updates a lease or creates a new lease for the client, the new
lease information must be recorded in the lease file. For performance
reasons, the server does not update the existing client's lease in the
file, as this would potentially require rewriting the entire file.
Instead, it simply appends the new lease information to the end of the
file; the previous lease entries for the client are not removed. When
the server loads leases from the lease file, e.g. at the server startup,
it assumes that the latest lease entry for the client is the valid one.
The previous entries are discarded, meaning that the server can
re-construct the accurate information about the leases even though there
may be many lease entries for each client. However, storing many entries
for each client results in a bloated lease file and impairs the
performance of the server's startup and reconfiguration, as it needs to
process a larger number of lease entries.

Lease file cleanup (LFC) removes all previous entries for each client
and leaves only the latest ones. The interval at which the cleanup is
performed is configurable, and it should be selected according to the
frequency of lease renewals initiated by the clients. The more frequent
the renewals, the smaller the value of ``lfc-interval`` should be. Note,
however, that the LFC takes time and thus it is possible (although
unlikely) that, if the ``lfc-interval`` is too short, a new cleanup may
be started while the previous one is still running. The server would
recover from this by skipping the new cleanup when it detected that the
previous cleanup was still in progress. But it implies that the actual
cleanups will be triggered more rarely than configured. Moreover,
triggering a new cleanup adds overhead to the server, which will not be
able to respond to new requests for a short period of time when the new
cleanup process is spawned. Therefore, it is recommended that the
``lfc-interval`` value be selected in a way that allows the LFC
to complete the cleanup before a new cleanup is triggered.

Lease file cleanup is performed by a separate process (in the
background) to avoid a performance impact on the server process. To
avoid conflicts between two processes both using the same lease
files, the LFC process starts with Kea opening a new lease file; the
actual LFC process operates on the lease file that is no longer used by
the server. There are also other files created as a side effect of the
lease file cleanup. The detailed description of the LFC process is located later
in this Kea Administrator's Reference Manual: :ref:`kea-lfc`.

.. _database-configuration6:

Lease Database Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::

   Lease database access information must be configured for the DHCPv6
   server, even if it has already been configured for the DHCPv4 server.
   The servers store their information independently, so each server can
   use a separate database or both servers can use the same database.

.. note::

   Kea requires the database timezone to match the system timezone.
   For more details, see :ref:`mysql-database-create` and
   :ref:`pgsql-database-create`.

Lease database configuration is controlled through the
Dhcp6/lease-database parameters. The database type must be set to
"memfile", "mysql", "postgresql", or "cql", e.g.:

::

   "Dhcp6": { "lease-database": { "type": "mysql", ... }, ... }

Next, the name of the database to hold the leases must be set; this is
the name used when the database was created (see
:ref:`mysql-database-create`, :ref:`pgsql-database-create`, or
:ref:`cql-database-create`).

::

   "Dhcp6": { "lease-database": { "name": "database-name" , ... }, ... }

For Cassandra:

::

   "Dhcp6": { "lease-database": { "keyspace": "database-name" , ... }, ... }

If the database is located on a different system from the DHCPv6 server,
the database host name must also be specified:

::

   "Dhcp6": { "lease-database": { "host": "remote-host-name", ... }, ... }

(It should be noted that this configuration may have a severe impact on server performance.)

For Cassandra, multiple contact points can be provided:

::

   "Dhcp6": { "lease-database": { "contact-points": "remote-host-name[, ...]" , ... }, ... }

Normally, the database will be on the same machine as the DHCPv6 server.
In this case, set the value to the empty string:

::

   "Dhcp6": { "lease-database": { "host" : "", ... }, ... }

For Cassandra:

::

   "Dhcp6": { "lease-database": { "contact-points": "", ... }, ... }

Should the database use a port other than the default, it may be
specified as well:

::

   "Dhcp6": { "lease-database": { "port" : 12345, ... }, ... }

Should the database be located on a different system, the administrator may need to
specify a longer interval for the connection timeout:

::

   "Dhcp6": { "lease-database": { "connect-timeout" : timeout-in-seconds, ... }, ... }

The default value of five seconds should be more than adequate for local
connections. If a timeout is given, though, it should be an integer
greater than zero.

The maximum number of times the server will automatically attempt to
reconnect to the lease database after connectivity has been lost may be
specified:

::

   "Dhcp6": { "lease-database": { "max-reconnect-tries" : number-of-tries, ... }, ... }

If the server is unable to reconnect to the database after making the
maximum number of attempts, the server will exit. A value of zero (the
default) disables automatic recovery and the server will exit
immediately upon detecting a loss of connectivity (MySQL and PostgreSQL
only).

The number of milliseconds the server will wait between attempts to
reconnect to the lease database after connectivity has been lost may
also be specified:

::

   "Dhcp6": { "lease-database": { "reconnect-wait-time" : number-of-milliseconds, ... }, ... }

The default value for MySQL and PostgreSQL is 0, which disables automatic
recovery and causes the server to exit immediately upon detecting the
loss of connectivity. The default value for Cassandra is 2000 ms.

::

   "Dhcp6": { "lease-database": { "on-fail" : "stop-retry-exit", ... }, ... }

The possible values are:

-  ``stop-retry-exit`` disables the DHCP service while trying to automatically
   recover lost connections. Shuts down the server on failure after exhausting
   ``max-reconnect-tries``. This is the default value for MySQL and PostgreSQL.

-  ``serve-retry-exit`` DHCP service continues while trying to automatically
   recover lost connections. Shuts down the server on failure after exhausting
   ``max-reconnect-tries``.

-  ``serve-retry-continue`` DHCP service continues and does not shut down the
   server even if the recovery fails.

.. note::

   Automatic reconnection to database backends is configured individually per
   backend. This allows users to tailor the recovery parameters to each backend
   they use. We do suggest that users enable it either for all backends or none,
   so behavior is consistent.
   Losing connectivity to a backend for which reconnect is disabled will result
   (if configured) in the server shutting itself down. This includes cases when
   the lease database backend and the hosts database backend are connected to
   the same database instance.
   It is highly recommended to not change the ``stop-retry-exit`` default
   setting for the lease manager as it is critical for the connection to be
   active while processing DHCP traffic. Change this only if the server is used
   exclusively as a configuration tool.

..

.. note::

   Note that the host parameter is used by the MySQL and PostgreSQL backends.
   Cassandra has a concept of contact points that can be used to
   contact the cluster, instead of a single IP or hostname. It takes a
   list of comma-separated IP addresses, which may be specified as:
   ::

      "Dhcp6": { "lease-database": { "contact-points" : "192.0.2.1,192.0.2.2", ... }, ... }

Finally, the credentials of the account under which the server will
access the database should be set:

::

   "Dhcp6": { "lease-database": { "user": "user-name",
                                  "password": "password",
                                 ... },
              ... }

If there is no password to the account, set the password to the empty
string "". (This is also the default.)

.. _cassandra-database-configuration6:

Cassandra-Specific Parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The parameters are the same for both DHCPv4 and DHCPv6. See
:ref:`cassandra-database-configuration4` for details.

.. _hosts6-storage:

Hosts Storage
-------------

Kea is also able to store information about host reservations in the
database. The hosts database configuration uses the same syntax as the
lease database. In fact, a Kea server opens independent connections for
each purpose, be it lease or hosts information. This arrangement gives
the most flexibility. Kea can keep leases and host reservations
separately, but can also point to the same database. Currently the
supported hosts database types are MySQL, PostgreSQL, and Cassandra.

For example, the following configuration can be used to configure a
connection to MySQL:

::

   "Dhcp6": {
       "hosts-database": {
           "type": "mysql",
           "name": "kea",
           "user": "kea",
           "password": "secret123",
           "host": "localhost",
           "port": 3306
       }
   }

Note that depending on the database configuration, many of the
parameters may be optional.

Please note that usage of hosts storage is optional. A user can define
all host reservations in the configuration file, and that is the
recommended way if the number of reservations is small. However, when
the number of reservations grows, it is more convenient to use host
storage. Please note that both storage methods (configuration file and
one of the supported databases) can be used together. If hosts are
defined in both places, the definitions from the configuration file are
checked first and external storage is checked later, if necessary.

In fact, host information can be placed in multiple stores. Operations
are performed on the stores in the order they are defined in the
configuration file, although this leads to a restriction in ordering in
the case of a host reservation addition; read-only stores must be
configured after a (required) read-write store, or the addition will
fail.

.. note::

   Kea requires the database timezone to match the system timezone.
   For more details, see :ref:`mysql-database-create` and
   :ref:`pgsql-database-create`.

.. _hosts-databases-configuration6:

DHCPv6 Hosts Database Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hosts database configuration is controlled through the
Dhcp6/hosts-database parameters. If enabled, the type of database must
be set to "mysql" or "postgresql".

::

   "Dhcp6": { "hosts-database": { "type": "mysql", ... }, ... }

Next, the name of the database to hold the reservations must be set;
this is the name used when the lease database was created (see
:ref:`supported-databases` for instructions on how to set up the
desired database type):

::

   "Dhcp6": { "hosts-database": { "name": "database-name" , ... }, ... }

If the database is located on a different system than the DHCPv6 server,
the database host name must also be specified:

::

   "Dhcp6": { "hosts-database": { "host": remote-host-name, ... }, ... }

(Again, it should be noted that this configuration may have a severe impact on server performance.)

Normally, the database will be on the same machine as the DHCPv6 server.
In this case, set the value to the empty string:

::

   "Dhcp6": { "hosts-database": { "host" : "", ... }, ... }

::

   "Dhcp6": { "hosts-database": { "port" : 12345, ... }, ... }

The maximum number of times the server will automatically attempt to
reconnect to the host database after connectivity has been lost may be
specified:

::

   "Dhcp6": { "hosts-database": { "max-reconnect-tries" : number-of-tries, ... }, ... }

If the server is unable to reconnect to the database after making the
maximum number of attempts, the server will exit. A value of zero (the
default) disables automatic recovery and the server will exit
immediately upon detecting a loss of connectivity (MySQL and PostgreSQL
only). For Cassandra, Kea uses a Cassandra interface that connects to
all nodes in a cluster at the same time. Any connectivity issues should
be handled by internal Cassandra mechanisms.

The number of milliseconds the server will wait between attempts to
reconnect to the host database after connectivity has been lost may also
be specified:

::

   "Dhcp6": { "hosts-database": { "reconnect-wait-time" : number-of-milliseconds, ... }, ... }

The default value for MySQL and PostgreSQL is 0, which disables automatic
recovery and causes the server to exit immediately upon detecting the
loss of connectivity. The default value for Cassandra is 2000 ms.

::

   "Dhcp6": { "hosts-database": { "on-fail" : "stop-retry-exit", ... }, ... }

The possible values are:

-  ``stop-retry-exit`` disables the DHCP service while trying to automatically
   recover lost connections. Shuts down the server on failure after exhausting
   ``max-reconnect-tries``. This is the default value for MySQL and PostgreSQL.

-  ``serve-retry-exit`` DHCP service continues while trying to automatically
   recover lost connections. Shuts down the server on failure after exhausting
   ``max-reconnect-tries``.

-  ``serve-retry-continue`` DHCP service continues and does not shut down the
   server even if the recovery fails.

.. note::

   Automatic reconnection to database backends is configured individually per
   backend. This allows users to tailor the recovery parameters to each backend
   they use. We do suggest that users enable it either for all backends or none,
   so behavior is consistent.
   Losing connectivity to a backend for which reconnect is disabled will result
   (if configured) in the server shutting itself down. This includes cases when
   the lease database backend and the hosts database backend are connected to
   the same database instance.

Finally, the credentials of the account under which the server will
access the database should be set:

::

   "Dhcp6": { "hosts-database": { "user": "user-name",
                                  "password": "password",
                                 ... },
              ... }

If there is no password to the account, set the password to the empty
string "". (This is also the default.)

The multiple storage extension uses a similar syntax; a configuration is
placed into a "hosts-databases" list instead of into a "hosts-database"
entry, as in:

::

   "Dhcp6": { "hosts-databases": [ { "type": "mysql", ... }, ... ], ... }

For additional Cassandra-specific parameters, see
:ref:`cassandra-database-configuration4`.

If the same host is configured both in-file and in-database, Kea does not issue a warning,
as it would if both were specified in the same data source.
Instead, the host configured in-file has priority over the one configured
in-database.

.. _read-only-database-configuration6:

Using Read-Only Databases for Host Reservations with DHCPv6
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In some deployments the database user whose name is specified in the
database backend configuration may not have write privileges to the
database. This is often required by the policy within a given network to
secure the data from being unintentionally modified. In many cases
administrators have deployed inventory databases, which contain
substantially more information about the hosts than just the static
reservations assigned to them. The inventory database can be used to
create a view of a Kea hosts database and such a view is often
read-only.

Kea host database backends operate with an implicit configuration to
both read from and write to the database. If the database user does not
have write access to the host database, the backend will fail to start
and the server will refuse to start (or reconfigure). However, if access
to a read-only host database is required for retrieving reservations
for clients and/or assigning specific addresses and options, it is
possible to explicitly configure Kea to start in "read-only" mode. This
is controlled by the ``readonly`` boolean parameter as follows:

::

   "Dhcp6": { "hosts-database": { "readonly": true, ... }, ... }

Setting this parameter to ``false`` configures the database backend to
operate in "read-write" mode, which is also the default configuration if
the parameter is not specified.

.. note::

   The ``readonly`` parameter is currently only supported for MySQL and
   PostgreSQL databases.

.. _dhcp6-interface-configuration:

Interface Configuration
-----------------------

The DHCPv6 server must be configured to listen on specific network
interfaces. The simplest network interface configuration tells the
server to listen on all available interfaces:

::

   "Dhcp6": {
       "interfaces-config": {
           "interfaces": [ "*" ]
       }
       ...
   }

The asterisk plays the role of a wildcard and means "listen on all
interfaces." However, it is usually a good idea to explicitly specify
interface names:

::

   "Dhcp6": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3" ]
       },
       ...
   }


It is possible to use a wildcard interface name (asterisk) concurrently
with explicit interface names:

::

   "Dhcp6": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3", "*" ]
       },
       ...
   }


It is anticipated that this form of usage will only be used when it is
desired to temporarily override a list of interface names and listen on
all interfaces.

As with the DHCPv4 server, binding to specific addresses and disabling
re-detection of interfaces are supported. But ``dhcp-socket-type`` is
not supported, because DHCPv6 uses UDP/IPv6 sockets only. The following example
shows how to disable the interface detection:

::

   "Dhcp6": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3" ],
           "re-detect": false
       },
       ...
   }


The loopback interfaces (i.e. the "lo" or "lo0" interface) are not
configured by default, unless explicitly mentioned in the
configuration. Note that Kea requires a link-local address (which does
not exist on all systems) or a specified unicast address, as in:

::

   "Dhcp6": {
       "interfaces-config": {
           "interfaces": [ "enp0s2/2001:db8::1234:abcd" ]
       },
       ...
   }


.. _ipv6-subnet-id:

IPv6 Subnet Identifier
----------------------

The subnet identifier is a unique number associated with a particular
subnet. In principle, it is used to associate clients' leases with their
respective subnets. When a subnet identifier is not specified for a
subnet being configured, it will be automatically assigned by the
configuration mechanism. The identifiers are assigned from 1 and are
monotonically increased for each subsequent subnet: 1, 2, 3 ....

If there are multiple subnets configured with auto-generated identifiers
and one of them is removed, the subnet identifiers may be renumbered.
For example: if there are four subnets and the third is removed, the
last subnet will be assigned the identifier that the third subnet had
before removal. As a result, the leases stored in the lease database for
subnet 3 are now associated with subnet 4, something that may have
unexpected consequences. The only remedy for this issue at present is to
manually specify a unique identifier for each subnet.

.. note::

   Subnet IDs must be greater than zero and less than 4294967295.

The following configuration will assign the specified subnet identifier
to a newly configured subnet:

::

   "Dhcp6": {
       "subnet6": [
           {
               "subnet": "2001:db8:1::/64",
               "id": 1024,
               ...
           }
       ]
   }

This identifier will not change for this subnet unless the "id"
parameter is removed or set to 0. The value of 0 forces auto-generation
of the subnet identifier.

.. _ipv6-subnet-prefix:

IPv6 Subnet Prefix
------------------

The subnet prefix is the second way to identify a subnet. It does not
need to have the address part to match the prefix length, for instance
this configuration is accepted:

::

   "Dhcp6": {
      "subnet6": [
          {
               "subnet": "2001:db8:1::1/64",
               ...
          }
       ]
   }

Even there is another subnet with the "2001:db8:1::/64" prefix:
only the textual form of subnets are compared to avoid duplicates.

.. note::

   Abuse of this feature can lead to incorrect subnet selection
   (see :ref:`dhcp6-config-subnets`).

.. _dhcp6-unicast:

Unicast Traffic Support
-----------------------

When the DHCPv6 server starts, by default it listens to the DHCP traffic
sent to multicast address ff02::1:2 on each interface that it is
configured to listen on (see :ref:`dhcp6-interface-configuration`). In some cases it is
useful to configure a server to handle incoming traffic sent to global
unicast addresses as well; the most common reason for this is to have
relays send their traffic to the server directly. To configure the
server to listen on a specific unicast address, add a slash after the interface name,
followed by the global unicast
address on which the server should listen. The server will listen to this
address in addition to normal link-local binding and listening on the
ff02::1:2 address. The sample configuration below shows how to listen on
2001:db8::1 (a global address) configured on the eth1 interface.

::

   "Dhcp6": {
       "interfaces-config": {
           "interfaces": [ "eth1/2001:db8::1" ]
       },
       ...
       "option-data": [
           {
               "name": "unicast",
               "data": "2001:db8::1"
           } ],
       ...
   }


This configuration will cause the server to listen on eth1 on the
link-local address, the multicast group (ff02::1:2), and 2001:db8::1.

Usually unicast support is associated with a server unicast option which
allows clients to send unicast messages to the server. The example above
includes a server unicast option specification which will cause the
client to send messages to the specified unicast address.

It is possible to mix interface names, wildcards, and interface
names/addresses in the list of interfaces. It is not possible, however,
to specify more than one unicast address on a given interface.

Care should be taken to specify proper unicast addresses. The server
will attempt to bind to the addresses specified without any additional
checks. This approach was selected on purpose, to allow the software to
communicate over uncommon addresses if so desired.

.. _dhcp6-address-config:

Configuration of IPv6 Address Pools
-----------------------------------

The main role of a DHCPv6 server is address assignment. For this, the
server must be configured with at least one subnet and one pool of
dynamic addresses to be managed. For example, assume that the server is
connected to a network segment that uses the 2001:db8:1::/64 prefix. The
administrator of that network decides that addresses from range
2001:db8:1::1 to 2001:db8:1::ffff are going to be managed by the Dhcp6
server. Such a configuration can be achieved in the following way:

::

   "Dhcp6": {
       "subnet6": [
          {
              "subnet": "2001:db8:1::/64",
              "pools": [
                  {
                      "pool": "2001:db8:1::1-2001:db8:1::ffff"
                  }
              ],
              ...
          }
       ]
   }

Note that ``subnet`` is defined as a simple string, but the ``pools``
parameter is actually a list of pools; for this reason, the pool
definition is enclosed in square brackets, even though only one range of
addresses is specified.

Each ``pool`` is a structure that contains the parameters that describe
a single pool. Currently there is only one parameter, ``pool``, which
gives the range of addresses in the pool.

It is possible to define more than one pool in a subnet; continuing the
previous example, further assume that 2001:db8:1:0:5::/80 should also be
managed by the server. It could be written as 2001:db8:1:0:5:: to
2001:db8:1::5:ffff:ffff:ffff, but typing so many 'f's is cumbersome. It
can be expressed more simply as 2001:db8:1:0:5::/80. Both formats are
supported by Dhcp6 and can be mixed in the pool list. For example, one
could define the following pools:

::

   "Dhcp6": {
       "subnet6": [
       {
           "subnet": "2001:db8:1::/64",
           "pools": [
               { "pool": "2001:db8:1::1-2001:db8:1::ffff" },
               { "pool": "2001:db8:1:05::/80" }
           ],
           ...
       }
       ]
   }

White space in pool definitions is ignored, so spaces before and after
the hyphen are optional. They can be used to improve readability.

The number of pools is not limited, but for performance reasons it is
recommended to use as few as possible.

The server may be configured to serve more than one subnet. To add a
second subnet, use a command similar to the following:

::

   "Dhcp6": {
       "subnet6": [
       {
           "subnet": "2001:db8:1::/64",
           "pools": [
               { "pool": "2001:db8:1::1-2001:db8:1::ffff" }
           ]
       },
       {
           "subnet": "2001:db8:2::/64",
           "pools": [
               { "pool": "2001:db8:2::/64" }
           ]
       },

           ...
       ]
   }

In this example, we allow the server to dynamically assign all addresses
available in the whole subnet. Although rather wasteful, it is certainly
a valid configuration to dedicate the whole /64 subnet for that purpose.
Note that the Kea server does not preallocate the leases, so there is no
danger in using gigantic address pools.

When configuring a DHCPv6 server using prefix/length notation, please
pay attention to the boundary values. When specifying that the server
can use a given pool, it will also be able to allocate the first
(typically a network address) address from that pool. For example, for
pool 2001:db8:2::/64, the 2001:db8:2:: address may be assigned as well.
To avoid this, use the "min-max" notation.

.. _dhcp6-prefix-config:

Subnet and Prefix Delegation Pools
----------------------------------

Subnets may also be configured to delegate prefixes, as defined in `RFC
8415 <https://tools.ietf.org/html/rfc8415>`__, section 6.3. A subnet may
have one or more prefix delegation pools. Each pool has a prefixed
address, which is specified as a prefix (``prefix``) and a prefix length
(``prefix-len``), as well as a delegated prefix length
(``delegated-len``). The delegated length must not be shorter than (that
is, it must be numerically greater than or equal to) the prefix length.
If both the delegated and prefix lengths are equal, the server will be
able to delegate only one prefix. The delegated prefix does not have to
match the subnet prefix.

Below is a sample subnet configuration which enables prefix delegation
for the subnet:

::

   "Dhcp6": {
       "subnet6": [
           {
               "subnet": "2001:d8b:1::/64",
               "pd-pools": [
                   {
                       "prefix": "3000:1::",
                       "prefix-len": 64,
                       "delegated-len": 96
                   }
               ]
           }
       ],
       ...
   }

.. _pd-exclude-option:

Prefix Exclude Option
---------------------

For each delegated prefix, the delegating router may choose to exclude a
single prefix out of the delegated prefix as specified in `RFC
6603 <https://tools.ietf.org/html/rfc6603>`__. The requesting router must
not assign the excluded prefix to any of its downstream interfaces, and
it is intended to be used on a link through which the delegating router
exchanges DHCPv6 messages with the requesting router. The configuration
example below demonstrates how to specify an excluded prefix within a
prefix pool definition. The excluded prefix
"2001:db8:1:8000:cafe:80::/72" will be sent to a requesting router which
includes the Prefix Exclude option in the Option Request option (ORO),
and which is delegated a prefix from this pool.

::

   "Dhcp6": {
       "subnet6": [
           {
               "subnet": "2001:db8:1::/48",
               "pd-pools": [
                   {
                       "prefix": "2001:db8:1:8000::",
                       "prefix-len": 48,
                       "delegated-len": 64,
                       "excluded-prefix": "2001:db8:1:8000:cafe:80::",
                       "excluded-prefix-len": 72
                   }
               ]
           }
       ]
   }

.. _dhcp6-std-options:

Standard DHCPv6 Options
-----------------------

One of the major features of the DHCPv6 server is the ability to provide
configuration options to clients. Although there are several options
that require special behavior, most options are sent by the server only
if the client explicitly requests them. The following example shows how
to configure the addresses of DNS servers, one of the most frequently used options.
Options specified in this way are considered global and apply to all configured subnets.

::

   "Dhcp6": {
       "option-data": [
           {
              "name": "dns-servers",
              "code": 23,
              "space": "dhcp6",
              "csv-format": true,
              "data": "2001:db8::cafe, 2001:db8::babe"
           },
           ...
       ]
   }

The ``option-data`` line creates a new entry in the option-data table.
This table contains information on all global options that the server is
supposed to configure in all subnets. The ``name`` line specifies the
option name. (For a complete list of currently supported names, see
:ref:`dhcp6-std-options-list`.) The next line specifies the
option code, which must match one of the values from that list. The line
beginning with ``space`` specifies the option space, which must always
be set to "dhcp6" as these are standard DHCPv6 options. For other name
spaces, including custom option spaces, see :ref:`dhcp6-option-spaces`. The following line
specifies the format in which the data will be entered; use of CSV
(comma-separated values) is recommended. Finally, the ``data`` line
gives the actual value to be sent to clients. The data parameter is specified as
normal text, with values separated by commas if more than one value is
allowed.

Options can also be configured as hexadecimal values. If "csv-format" is
set to false, the option data must be specified as a hexadecimal string.
The following commands configure the DNS-SERVERS option for all subnets
with the following addresses: 2001:db8:1::cafe and 2001:db8:1::babe.

::

   "Dhcp6": {
       "option-data": [
           {
              "name": "dns-servers",
              "code": 23,
              "space": "dhcp6",
              "csv-format": false,
              "data": "20 01 0D B8 00 01 00 00 00 00 00 00 00 00 CA FE
                       20 01 0D B8 00 01 00 00 00 00 00 00 00 00 BA BE"
           },
           ...
       ]
   }


..

.. note::

   The value for the setting of the "data" element is split across two
   lines in this example for clarity; when entering the command, the
   whole string should be entered on the same line.

Kea supports the following formats when specifying hexadecimal data:

-  ``Delimited octets`` - one or more octets separated by either colons or
   spaces (':' or ' '). While each octet may contain one or two digits,
   we strongly recommend always using two digits. Valid examples are
   "ab:cd:ef" and "ab cd ef".

-  ``String of digits`` - a continuous string of hexadecimal digits with
   or without a "0x" prefix. Valid examples are "0xabcdef" and "abcdef".

Care should be taken to use proper encoding when using hexadecimal
format; Kea's ability to validate data correctness in hexadecimal is
limited.

As of Kea 1.6.0, it is also possible to specify data for binary options as
a single-quoted text string within double quotes as shown (note that
``csv-format`` must be set to false):

::

   "Dhcp6": {
       "option-data": [
           {
               "name": "subscriber-id",
               "code": 38,
               "space": "dhcp6",
               "csv-format": false,
               "data": "'convert this text to binary'"
           },
           ...
       ],
       ...
   }

Most of the parameters in the "option-data" structure are optional and
can be omitted in some circumstances, as discussed in :ref:`dhcp6-option-data-defaults`.
Only one of name or code
is required; it is not necessary to specify both. Space has a default value
of "dhcp6", so this can be skipped as well if a regular (not
encapsulated) DHCPv6 option is defined. Finally, csv-format defaults to "true", so it
too can be skipped, unless the option value is specified as
hexstring. Therefore, the above example can be simplified to:

::

   "Dhcp6": {
       "option-data": [
           {
              "name": "dns-servers",
              "data": "2001:db8::cafe, 2001:db8::babe"
           },
           ...
       ]
   }


Defined options are added to the response when the client requests them,
as well as any options required by a protocol. An administrator can also
specify that an option is always sent, even if a client did not
specifically request it. To enforce the addition of a particular option,
set the "always-send" flag to true as in:

::

   "Dhcp6": {
       "option-data": [
           {
              "name": "dns-servers",
              "data": "2001:db8::cafe, 2001:db8::babe",
              "always-send": true
           },
           ...
       ]
   }


The effect is the same as if the client added the option code in the
Option Request option (or its equivalent for vendor options), as in:

::

   "Dhcp6": {
       "option-data": [
           {
              "name": "dns-servers",
              "data": "2001:db8::cafe, 2001:db8::babe",
              "always-send": true
           },
           ...
       ],
       "subnet6": [
           {
              "subnet": "2001:db8:1::/64",
              "option-data": [
                  {
                      "name": "dns-servers",
                      "data": "2001:db8:1::cafe, 2001:db8:1::babe"
                  },
                  ...
              ],
              ...
           },
           ...
       ],
       ...
   }


The DNS servers option is always added to responses (the always-send is
"sticky"), but the value is the subnet one when the client is localized
in the subnet.

It is possible to override options on a per-subnet basis. If clients
connected to most subnets are expected to get the same values of
a given option, administrators should use global options; it is possible to override
specific values for a small number of subnets. On the other hand, if
different values are used in each subnet, it does not make sense to specify
global option values; rather, only subnet-specific ones should be set.

The following commands override the global DNS servers option for a
particular subnet, setting a single DNS server with address
2001:db8:1::3.

::

   "Dhcp6": {
       "subnet6": [
           {
               "option-data": [
                   {
                       "name": "dns-servers",
                       "code": 23,
                       "space": "dhcp6",
                       "csv-format": true,
                       "data": "2001:db8:1::3"
                   },
                   ...
               ],
               ...
           },
           ...
       ],
       ...
   }

In some cases it is useful to associate some options with an address or
prefix pool from which a client is assigned a lease. Pool-specific
option values override subnet-specific and global option values. If the
client is assigned multiple leases from different pools, the server will
assign options from all pools from which the leases have been obtained.
However, if the particular option is specified in multiple pools from
which the client obtains the leases, only one instance of this option
will be handed out to the client. The server's administrator must not
try to prioritize assignment of pool-specific options by trying to order
pools declarations in the server configuration.

The following configuration snippet demonstrates how to specify the DNS
servers option, which will be assigned to a client only if the client
obtains an address from the given pool:

::

   "Dhcp6": {
       "subnet6": [
           {
               "pools": [
                   {
                       "pool": "2001:db8:1::100-2001:db8:1::300",
                       "option-data": [
                           {
                               "name": "dns-servers",
                               "data": "2001:db8:1::10"
                           }
                       ]
                   }
               ]
           },
           ...
       ],
       ...
   }

Options can also be specified in class or host reservation scope. The
current Kea options precedence order is (from most important): host
reservation, pool, subnet, shared network, class, global.

The currently supported standard DHCPv6 options are listed in
:ref:`dhcp6-std-options-list`. "Name" and "Code" are the
values that should be used as a name/code in the option-data structures.
"Type" designates the format of the data; the meanings of the various
types are given in :ref:`dhcp-types`.

When a data field is a string and that string contains the comma (,;
U+002C) character, the comma must be escaped with two backslashes (\;
U+005C). This double escape is required because both the routine
splitting CSV data into fields and JSON use the same escape character; a
single escape (\,) would make the JSON invalid. For example, the string
"EST5EDT4,M3.2.0/02:00,M11.1.0/02:00" must be represented as:

::

   "Dhcp6": {
       "subnet6": [
           {
               "pools": [
                   {
                       "option-data": [
                           {
                               "name": "new-posix-timezone",
                               "data": "EST5EDT4\\,M3.2.0/02:00\\,M11.1.0/02:00"
                           }
                       ]
                   },
                   ...
               ],
               ...
           },
           ...
       ],
       ...
   }

Some options are designated as arrays, which means that more than one
value is allowed in such an option. For example, the option dns-servers
allows the specification of more than one IPv6 address, enabling clients
to obtain the addresses of multiple DNS servers.

:ref:`dhcp6-custom-options` describes the
configuration syntax to create custom option definitions (formats).
Creation of custom definitions for standard options is generally not
permitted, even if the definition being created matches the actual
option format defined in the RFCs. There is an exception to this rule
for standard options for which Kea currently does not provide a
definition. In order to use such options, a server administrator must
create a definition as described in :ref:`dhcp6-custom-options` in the 'dhcp6' option space. This
definition should match the option format described in the relevant RFC,
but the configuration mechanism will allow any option format as it
currently has no means to validate it.

.. _dhcp6-std-options-list:

.. table:: List of Standard DHCPv6 Options configurable by an administrator

   +--------------------------+-----------------+-----------------+-----------------+
   | Name                     | Code            | Type            | Array?          |
   +==========================+=================+=================+=================+
   | preference               | 7               | uint8           | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | unicast                  | 12              | ipv6-address    | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | sip-server-dns           | 21              | fqdn            | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | sip-server-addr          | 22              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | dns-servers              | 23              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | domain-search            | 24              | fqdn            | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | nis-servers              | 27              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | nisp-servers             | 28              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | nis-domain-name          | 29              | fqdn            | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | nisp-domain-name         | 30              | fqdn            | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | sntp-servers             | 31              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | information-refresh-time | 32              | uint32          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | bcmcs-server-dns         | 33              | fqdn            | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | bcmcs-server-addr        | 34              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | geoconf-civic            | 36              | record (uint8,  | false           |
   |                          |                 | uint16, binary) |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | remote-id                | 37              | record (uint32, | false           |
   |                          |                 | binary)         |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | subscriber-id            | 38              | binary          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | client-fqdn              | 39              | record (uint8,  | false           |
   |                          |                 | fqdn)           |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | pana-agent               | 40              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | new-posix-timezone       | 41              | string          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | new-tzdb-timezone        | 42              | string          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | ero                      | 43              | uint16          | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | lq-query (1)             | 44              | record (uint8,  | false           |
   |                          |                 | ipv6-address)   |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | client-data (1)          | 45              | empty           | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | clt-time (1)             | 46              | uint32          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | lq-relay-data (1)        | 47              | record          | false           |
   |                          |                 | (ipv6-address,  |                 |
   |                          |                 | binary)         |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | lq-client-link (1)       | 48              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | v6-lost                  | 51              | fqdn            | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | capwap-ac-v6             | 52              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | relay-id                 | 53              | binary          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | v6-access-domain         | 57              | fqdn            | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | sip-ua-cs-list           | 58              | fqdn            | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | bootfile-url             | 59              | string          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | bootfile-param           | 60              | tuple           | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | client-arch-type         | 61              | uint16          | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | nii                      | 62              | record (uint8,  | false           |
   |                          |                 | uint8, uint8)   |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | aftr-name                | 64              | fqdn            | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | erp-local-domain-name    | 65              | fqdn            | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | rsoo                     | 66              | empty           | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | pd-exclude               | 67              | binary          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | rdnss-selection          | 74              | record          | true            |
   |                          |                 | (ipv6-address,  |                 |
   |                          |                 | uint8, fqdn)    |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | client-linklayer-addr    | 79              | binary          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | link-address             | 80              | ipv6-address    | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | solmax-rt                | 82              | uint32          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | inf-max-rt               | 83              | uint32          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | dhcp4o6-server-addr      | 88              | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+
   | s46-rule                 | 89              | record (uint8,  | false           |
   |                          |                 | uint8, uint8,   |                 |
   |                          |                 | ipv4-address,   |                 |
   |                          |                 | ipv6-prefix)    |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | s46-br                   | 90              | ipv6-address    | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | s46-dmr                  | 91              | ipv6-prefix     | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | s46-v4v6bind             | 92              | record          | false           |
   |                          |                 | (ipv4-address,  |                 |
   |                          |                 | ipv6-prefix)    |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | s46-portparams           | 93              | record(uint8,   | false           |
   |                          |                 | psid)           |                 |
   +--------------------------+-----------------+-----------------+-----------------+
   | s46-cont-mape            | 94              | empty           | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | s46-cont-mapt            | 95              | empty           | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | s46-cont-lw              | 96              | empty           | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | v6-captive-portal        | 103             | string          | false           |
   +--------------------------+-----------------+-----------------+-----------------+
   | ipv6-address-andsf       | 143             | ipv6-address    | true            |
   +--------------------------+-----------------+-----------------+-----------------+

Options marked with (1) have option definitions, but the logic behind
them is not implemented. That means that, technically, Kea knows how to
parse them in incoming messages or how to send them if configured to do
so, but not what to do with them. Since the related RFCs require certain
processing, the support for those options is non-functional. However, it
may be useful in some limited lab testing; hence the definition formats
are listed here.

Kea supports more options than the listed above. The following list is mostly useful for readers who
want to understand whether Kea is able to support certain options. The following options are
returned by the Kea engine itself and in general should not be configured manually.

.. table:: List of standard DHCPv6 options managed by Kea on its own and not directly configurable by an administrator

   +--------------+------+------------------------------------------------------------------------+
   | Name         | Code | Description                                                            |
   +==============+======+========================================================================+
   | client-id    | 1    | sent by the client and Kea uses it to distinguish between clients.     |
   +--------------+------+------------------------------------------------------------------------+
   | server-id    | 2    | sent by clients to request action from a specific server and by the    |
   |              |      | server to identify itself. See :ref:`dhcp6-serverid` for details.      |
   +--------------+------+------------------------------------------------------------------------+
   | ia-na        | 3    | a container option that conveys IPv6 addresses (``iaddr`` options). Kea|
   |              |      | receives and sends those options using its allocation engine.          |
   +--------------+------+------------------------------------------------------------------------+
   | ia-ta        | 4    | conveys temporary addresses. Deprecated feature, not supported.        |
   +--------------+------+------------------------------------------------------------------------+
   | iaaddr       | 5    | conveys addresses with lifetimes in ``ia-na`` and ``ia-ta`` options.   |
   +--------------+------+------------------------------------------------------------------------+
   | oro          | 6    | ORO (or Option Request Option) is used by the clients to request a list|
   |              |      | of options they are interested in. Kea supports it and will send the   |
   |              |      | requested options back if configured with required options.            |
   +--------------+------+------------------------------------------------------------------------+
   | elapsed-time | 8    | sent by the clients to identify how long they're trying to obtain a    |
   |              |      | configuration. Kea uses high values sent by clients as an indicator    |
   |              |      | that something is wrong and this is one of the aspects used in HA to   |
   |              |      | determine if the partner is healthy or not.                            |
   +--------------+------+------------------------------------------------------------------------+
   | relay-msg    | 9    | used by relays to encapsulate the original client message. Kea uses it |
   |              |      | when sending back relayed responses to the relay agent.                |
   +--------------+------+------------------------------------------------------------------------+
   | auth         | 10   | used to pass authentication information between clients and server. The|
   |              |      | support for this option is very limited.                               |
   +--------------+------+------------------------------------------------------------------------+
   | status-code  | 13   | an option that the server can attach in case of various failures, such |
   |              |      | as running out of addresses or not being configured to assign prefixes.|
   +--------------+------+------------------------------------------------------------------------+
   | rapid-commit | 14   | used to signal client's willingness to support ``rapid-commit`` and    |
   |              |      | server's acceptance for this configuration. See                        |
   |              |      | :ref:`dhcp6-rapid-commit` for details.                                 |
   +--------------+------+------------------------------------------------------------------------+
   | user-class   | 15   | sent by the client to self-identify what kind of device type it is. Kea|
   |              |      | can use this for client classification.                                |
   +--------------+------+------------------------------------------------------------------------+
   | vendor-class | 16   | similar to ``user-class``, but it is vendor specific.                  |
   +--------------+------+------------------------------------------------------------------------+
   | vendor-opts  | 17   | a vendor specific container that is used by both the client and the    |
   |              |      | server to exchange vendor specific options. The logic behind those     |
   |              |      | options vary between vendors. The vendor options are explained in      |
   |              |      | :ref:`dhcp6-vendor-opts`.                                              |
   +--------------+------+------------------------------------------------------------------------+
   | interface-id | 18   | may be inserted by the relay agent to identify the interface that the  |
   |              |      | original client message was received on. Kea may be told to use this   |
   |              |      | information to select specific subnets. Also, if specified, Kea will   |
   |              |      | echo this option back, so the relay will know which interface to use to|
   |              |      | reach the client.                                                      |
   +--------------+------+------------------------------------------------------------------------+
   | ia-pd        | 25   | a container for conveying PDs (Prefix Delegation) that are being       |
   |              |      | delegated to clients. See :ref:`dhcp6-prefix-config` for details.      |
   +--------------+------+------------------------------------------------------------------------+
   | iaprefix     | 26   | conveys IPv6 prefix in ``ia-pd`` option. See :ref:`dhcp6-prefix-config`|
   |              |      | for details.                                                           |
   +--------------+------+------------------------------------------------------------------------+

.. _s46-options:

Common Softwire46 Options
-------------------------

Softwire46 options are involved in IPv4 over IPv6 provisioning by means
of tunneling or translation as specified in `RFC
7598 <https://tools.ietf.org/html/rfc7598>`__. The following sections
provide configuration examples of these options.

.. _s46-containers:

Softwire46 Container Options
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Softwire46 (S46) container options group rules and optional port parameters for a
specified domain. There are three container options specified in the
"dhcp6" (top-level) option space: the MAP-E Container option, the MAP-T
Container option, and the S46 Lightweight 4over6 Container option. These
options only contain the encapsulated options specified below; they do not
include any data fields.

To configure the server to send a specific container option along with
all encapsulated options, the container option must be included in the
server configuration as shown below:

::

   "Dhcp6": {
       ...
       "option-data": [
           {
               "name": "s46-cont-mape"
           } ],
       ...
   }

This configuration will cause the server to include the MAP-E Container
option to the client. Use "s46-cont-mapt" or "s46-cont-lw" for the MAP-T
Container and S46 Lightweight 4over6 Container options, respectively.

All remaining Softwire options described below are included in one of
the container options. Thus, they must be included in appropriate
option spaces by selecting a "space" name, which specifies in which
option they are supposed to be included.

S46 Rule Option
~~~~~~~~~~~~~~~

The S46 Rule option is used for conveying the Basic Mapping Rule (BMR)
and Forwarding Mapping Rule (FMR).

::

   {
       "space": "s46-cont-mape-options",
       "name": "s46-rule",
       "data": "128, 0, 24, 192.0.2.0, 2001:db8:1::/64"
   }

Another possible "space" value is "s46-cont-mapt-options".

The S46 Rule option conveys a number of parameters:

-  ``flags`` - an unsigned 8-bit integer, with currently only the
   most-significant bit specified. It denotes whether the rule can be
   used for forwarding (128) or not (0).

-  ``ea-len`` - an 8-bit-long Embedded Address length. Allowed values
   range from 0 to 48.

-  ``IPv4 prefix length`` - 8 bits long; expresses the prefix length of
   the Rule IPv4 prefix specified in the ipv4-prefix field. Allowed
   values range from 0 to 32.

-  ``IPv4 prefix`` - a fixed-length 32-bit field that specifies the IPv4
   prefix for the S46 rule. The bits in the prefix after
   a specific number of bits (defined in prefix4-len) are reserved, and MUST
   be initialized to zero by the sender and ignored by the receiver.

-  ``IPv6 prefix`` - in prefix/length notation that specifies the IPv6
   domain prefix for the S46 rule. The field is padded on the right with
   zero bits up to the nearest octet boundary, when prefix6-len is not
   evenly divisible by 8.

S46 BR Option
~~~~~~~~~~~~~

The S46 BR option is used to convey the IPv6 address of the Border
Relay. This option is mandatory in the MAP-E Container option and is not
permitted in the MAP-T and S46 Lightweight 4over6 Container options.

::

   {
       "space": "s46-cont-mape-options",
       "name": "s46-br",
       "data": "2001:db8:cafe::1",
   }

Another possible "space" value is "s46-cont-lw-options".

S46 DMR Option
~~~~~~~~~~~~~~

The S46 DMR option is used to convey values for the Default Mapping Rule
(DMR). This option is mandatory in the MAP-T container option and is not
permitted in the MAP-E and S46 Lightweight 4over6 Container options.

::

   {
       "space": "s46-cont-mapt-options",
       "name": "s46-dmr",
       "data": "2001:db8:cafe::/64",
   }

This option must not be included in other containers.

S46 IPv4/IPv6 Address Binding Option
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The S46 IPv4/IPv6 Address Binding option may be used to specify the full
or shared IPv4 address of the Customer Edge (CE). The IPv6 prefix field
is used by the CE to identify the correct prefix to use for the tunnel
source.

::

   {
       "space": "s46-cont-lw",
       "name": "s46-v4v6bind",
       "data": "192.0.2.3, 2001:db8:1:cafe::/64"
   }

This option must not be included in other containers.

S46 Port Parameters
~~~~~~~~~~~~~~~~~~~

The S46 Port Parameters option specifies optional port-set information
that MAY be provided to CEs.

::

   {
       "space": "s46-rule-options",
       "name": "s46-portparams",
       "data": "2, 3/4",
   }

Another possible "space" value is "s46-v4v6bind", to include this option
in the S46 IPv4/IPv6 Address Binding option.

Note that the second value in the example above specifies the PSID and
PSID-length fields in the format of PSID/PSID length. This is equivalent
to the values of PSID-len=4 and PSID=12288 conveyed in the S46 Port
Parameters option.

.. _dhcp6-custom-options:

Custom DHCPv6 Options
---------------------

Kea supports custom (non-standard) DHCPv6 options.
Assume that we want to define a new DHCPv6 option called "foo" which
will have code 100 and which will convey a single, unsigned, 32-bit
integer value. We can define such an option by putting the following entry
in the configuration file:

::

   "Dhcp6": {
       "option-def": [
           {
               "name": "foo",
               "code": 100,
               "type": "uint32",
               "array": false,
               "record-types": "",
               "space": "dhcp6",
               "encapsulate": ""
           }, ...
       ],
       ...
   }

The ``false`` value of the ``array`` parameter determines that the option
does NOT comprise an array of "uint32" values but is, instead, a single
value. Two other parameters have been left blank: ``record-types`` and
``encapsulate``. The former specifies the comma-separated list of option
data fields, if the option comprises a record of data fields. The
``record-types`` value should be non-empty if ``type`` is set to
"record"; otherwise it must be left blank. The latter parameter
specifies the name of the option space being encapsulated by the
particular option. If the particular option does not encapsulate any
option space, the parameter should be left blank. Note that the ``option-def``
configuration statement only defines the format of the new option and does
not set its value(s).

The ``name``, ``code``, and ``type`` parameters are required; all
others are optional. The ``array`` default value is ``false``. The
``record-types`` and ``encapsulate`` default values are blank (i.e. "").
The default ``space`` is "dhcp6".

Once the new option format is defined, its value is set in the same way
as for a standard option. For example, the following commands set a
global value that applies to all subnets.

::

   "Dhcp6": {
       "option-data": [
           {
               "name": "foo",
               "code": 100,
               "space": "dhcp6",
               "csv-format": true,
               "data": "12345"
           }, ...
       ],
       ...
   }

New options can take more complex forms than simple use of primitives
(uint8, string, ipv6-address, etc.); it is possible to define an option
comprising a number of existing primitives.

For example, assume we want to define a new option that will consist of
an IPv6 address, followed by an unsigned 16-bit integer, followed by a
boolean value, followed by a text string. Such an option could be
defined in the following way:

::

   "Dhcp6": {
       "option-def": [
           {
               "name": "bar",
               "code": 101,
               "space": "dhcp6",
               "type": "record",
               "array": false,
               "record-types": "ipv6-address, uint16, boolean, string",
               "encapsulate": ""
           }, ...
       ],
       ...
   }

The ``type`` is set to "record" to indicate that the option contains
multiple values of different types. These types are given as a
comma-separated list in the ``record-types`` field and should be ones
from those listed in :ref:`dhcp-types`.

The values of the options are set in an ``option-data`` statement as
follows:

::

   "Dhcp6": {
       "option-data": [
           {
               "name": "bar",
               "space": "dhcp6",
               "code": 101,
               "csv-format": true,
               "data": "2001:db8:1::10, 123, false, Hello World"
           }
       ],
       ...
   }

``csv-format`` is set to ``true`` to indicate that the ``data`` field
comprises a comma-separated list of values. The values in ``data``
must correspond to the types set in the ``record-types`` field of the
option definition.

When ``array`` is set to ``true`` and ``type`` is set to "record", the
last field is an array, i.e. it can contain more than one value, as in:

::

   "Dhcp6": {
       "option-def": [
           {
               "name": "bar",
               "code": 101,
               "space": "dhcp6",
               "type": "record",
               "array": true,
               "record-types": "ipv6-address, uint16",
               "encapsulate": ""
           }, ...
       ],
       ...
   }

The new option content is one IPv6 address followed by one or more 16-bit
unsigned integers.

.. note::

   In general, boolean values are specified as ``true`` or ``false``,
   without quotes. Some specific boolean parameters may accept also
   ``"true"``, ``"false"``, ``0``, ``1``, ``"0"``, and ``"1"``.

.. _dhcp6-vendor-opts:

DHCPv6 Vendor-Specific Options
------------------------------

Vendor options in DHCPv6 are carried in the Vendor-Specific
Information option (code 17). The following examples show how to
define an option "foo" with code 1 that consists of an IPv6 address,
an unsigned 16-bit integer, and a string.  The "foo" option is
conveyed in a Vendor-Specific Information option, which comprises a
single uint32 value that is set to "12345". The sub-option "foo"
follows the data field holding this value.

The first step is to define the format of the option:

::

   "Dhcp6": {
       "option-def": [
           {
               "name": "foo",
               "code": 1,
               "space": "vendor-12345",
               "type": "record",
               "array": false,
               "record-types": "ipv6-address, uint16, string",
               "encapsulate": ""
           }
       ],
       ...
   }

(Note that the option space is set to ``vendor-12345``.) Once the
option format is defined, the next step is to define actual values for
that option:

::

   "Dhcp6": {
       "option-data": [
           {
               "name": "foo",
               "space": "vendor-12345",
               "data": "2001:db8:1::10, 123, Hello World"
           },
           ...
       ],
       ...
   }

We should also define a value (enterprise-number) for the
Vendor-Specific Information option, that conveys our option "foo".

::

   "Dhcp6": {
       "option-data": [
           ...,
           {
               "name": "vendor-opts",
               "data": "12345"
           }
       ],
       ...
   }

Alternatively, the option can be specified using its code.

::

   "Dhcp6": {
       "option-data": [
           ...,
           {
               "code": 17,
               "data": "12345"
           }
       ],
       ...
   }

A common configuration is to set the always-send flag to true so the
vendor option is sent even when the client did not specify it in the query.

.. note::

   Currently only a single instance of the vendor-class (code 16) and
   a single instance of the vendor-opts (code 17) options can be
   specified.  Specifying multiple options with different enterprise
   numbers is currently not supported by Kea.

.. _dhcp6-option-spaces:

Nested DHCPv6 Options (Custom Option Spaces)
--------------------------------------------

It is sometimes useful to define completely new option spaces, such as
when a user creates a new option to convey sub-options that
use a separate numbering scheme, for example sub-options with codes 1
and 2. Those option codes conflict with standard DHCPv6 options, so a
separate option space must be defined.

Note that the creation of a new option space is not required when
defining sub-options for a standard option, because one is created by
default if the standard option is meant to convey any sub-options (see
:ref:`dhcp6-vendor-opts`).

Assume that we want to have a DHCPv6 option called "container" with code
102 that conveys two sub-options with codes 1 and 2. First we need to
define the new sub-options:

::

   "Dhcp6": {
       "option-def": [
           {
               "name": "subopt1",
               "code": 1,
               "space": "isc",
               "type": "ipv6-address",
               "record-types": "",
               "array": false,
               "encapsulate": ""
           },
           {
               "name": "subopt2",
               "code": 2,
               "space": "isc",
               "type": "string",
               "record-types": "",
               "array": false
               "encapsulate": ""
           }
       ],
       ...
   }

Note that we have defined the options to belong to a new option space
(in this case, "isc").

The next step is to define a regular DHCPv6 option with the desired code
and specify that it should include options from the new option space:

::

   "Dhcp6": {
       "option-def": [
           ...,
           {
               "name": "container",
               "code": 102,
               "space": "dhcp6",
               "type": "empty",
               "array": false,
               "record-types": "",
               "encapsulate": "isc"
           }
       ],
       ...
   }

The name of the option space in which the sub-options are defined is set
in the ``encapsulate`` field. The ``type`` field is set to ``empty``,
which limits this option to only carrying data in sub-options.

Finally, we can set values for the new options:

::

   "Dhcp6": {
       "option-data": [
           {
               "name": "subopt1",
               "code": 1,
               "space": "isc",
               "data": "2001:db8::abcd"
           },
           }
               "name": "subopt2",
               "code": 2,
               "space": "isc",
               "data": "Hello world"
           },
           {
               "name": "container",
               "code": 102,
               "space": "dhcp6"
           }
       ],
       ...
   }

Note that it is possible to create an option which carries some data in
addition to the sub-options defined in the encapsulated option space.
For example, if the "container" option from the previous example were
required to carry a uint16 value as well as the sub-options, the
``type`` value would have to be set to "uint16" in the option
definition. (Such an option would then have the following data
structure: DHCP header, uint16 value, sub-options.) The value specified
with the ``data`` parameter — which should be a valid integer enclosed
in quotes, e.g. "123" — would then be assigned to the uint16 field in
the "container" option.

.. _dhcp6-option-data-defaults:

Unspecified Parameters for DHCPv6 Option Configuration
------------------------------------------------------

In many cases it is not required to specify all parameters for an option
configuration, and the default values can be used. However, it is
important to understand the implications of not specifying some of them,
as it may result in configuration errors. The list below explains the
behavior of the server when a particular parameter is not explicitly
specified:

-  ``name`` - the server requires either an option name or an option code to
   identify an option. If this parameter is unspecified, the option code
   must be specified.

-  ``code`` - the server requires either an option name or an option code to
   identify an option. This parameter may be left unspecified if the
   ``name`` parameter is specified. However, this also requires that the
   particular option has a definition (either as a standard option or
   an administrator-created definition for the option using an
   'option-def' structure), as the option definition associates an
   option with a particular name. It is possible to configure an option
   for which there is no definition (unspecified option format).
   Configuration of such options requires the use of the option code.

-  ``space`` - if the option space is unspecified it will default to
   'dhcp6', which is an option space holding standard DHCPv6 options.

-  ``data`` - if the option data is unspecified it defaults to an empty
   value. The empty value is mostly used for the options which have no
   payload (boolean options), but it is legal to specify empty values
   for some options which carry variable-length data and for which the
   specification allows a length of 0. For such options, the data
   parameter may be omitted in the configuration.

-  ``csv-format`` - if this value is not specified, the server will
   assume that the option data is specified as a list of comma-separated
   values to be assigned to individual fields of the DHCP option.

.. _dhcp6-t1-t2-times:

Controlling the Values Sent for T1 and T2 Times
-----------------------------------------------

According to RFC 8415, section 21.4, the recommended T1 and T2 values
are 50% and 80% of the preferred
lease time, respectively. Kea can be configured to send values that are
specified explicitly or that are calculated as percentages of the
preferred lease time. The server's behavior is governed by a combination
of configuration parameters, two of which have already been mentioned.

Beginning with Kea 1.6.0 lease preferred and valid lifetime are extended from
single values to triplets with minimum, default and maximum values using:


- ``min-preferred-lifetime`` - specifies the minimum preferred lifetime (optional).

- ``preferred-lifetime`` - specifies the default preferred lifetime.

- ``max-preferred-lifetime`` - specifies the maximum preferred lifetime (optional).

- ``min-valid-lifetime`` - specifies the minimum valid lifetime (optional).

- ``valid-lifetime`` - specifies the default valid lifetime.

- ``max-valid-lifetime`` - specifies the maximum valid lifetime (optional).

As of Kea 1.9.11, these values may be specified within client classes.

When the client does not specify lifetimes the default is used. When
it specifies a lifetime using IAADDR or IAPREFIX sub option with
non-zero values, these values are used when they are between configured
minimum (lower values are round up) and maximum (larger values are
rounded down) bounds.

To send specific, fixed values use the following two parameters:

-  ``renew-timer`` - specifies the value of T1 in seconds.

-  ``rebind-timer`` - specifies the value of T2 in seconds.

Any value greater than or equal to zero may be specified for T2. When
specifying T1 it must be less than T2. This flexibility is allowed to
support a use case where administrators want to suppress client renewals and
rebinds by deferring them beyond the lifespan of the lease. This should
cause the lease to expire, rather than get renewed by clients. If T1 is
specified as larger than T2, T1 will be set to zero in the outbound IA.

In the great majority of cases the values should follow this rule: T1 < T2 <
preferred lifetime < valid lifetime. Alternatively, both T1 and T2
values can be configured to 0, which is a signal to DHCPv6 clients that
they may renew at their own discretion. However, there are known broken
client implementations in use that will start renewing immediately.
Administrators who plan to use T1=T2=0 values should test first and make sure
their clients behave rationally.

In some rare cases there may be a need to disable a client's ability to
renew addresses. This is undesired from a protocol perspective and should
be avoided if possible. However, if necessary, administrators can
configure the T1 and T2 values to be equal or greater to the valid
lifetime. Be advised that this will cause clients to occasionally
lose their addresses, which is generally perceived as poor service.
However, there may be some rare business cases when this is desired
(e.g. when it is desirable to intentionally break long-lasting connections).

Calculation of the values is controlled by the following three parameters:

-  ``calculate-tee-times`` - when true, T1 and T2 will be calculated as
   percentages of the valid lease time. It defaults to true.

-  ``t1-percent`` - the percentage of the valid lease time to use for
   T1. It is expressed as a real number between 0.0 and 1.0 and must be
   less than t2-percent. The default value is 0.5 per RFC 8415.

-  ``t2-percent`` - the percentage of the valid lease time to use for
   T2. It is expressed as a real number between 0.0 and 1.0 and must be
   greater than t1-percent. The default value is 0.8 per RFC 8415.

..

.. note::

   In the event that both explicit values are specified and
   calculate-tee-times is true, the server will use the explicit values.
   Administrators with a setup where some subnets or share-networks
   will use explicit values and some will use calculated values must
   not define the explicit values at any level higher than where they
   will be used. Inheriting them from too high a scope, such as
   global, will cause them to have values at every level underneath
   (shared-networks and subnets), effectively disabling calculated
   values.

.. _dhcp6-config-subnets:

IPv6 Subnet Selection
---------------------

The DHCPv6 server may receive requests from local (connected to the same
subnet as the server) and remote (connected via relays) clients. As the
server may have many subnet configurations defined, it must select an
appropriate subnet for a given request.

In IPv4, the server can determine which of the configured subnets are
local, as there is a reasonable expectation that the server will have a
(global) IPv4 address configured on the interface. That assumption is not
true in IPv6; the DHCPv6 server must be able to operate while only using
link-local addresses. Therefore, an optional ``interface`` parameter is
available within a subnet definition to designate that a given subnet is
local, i.e. reachable directly over the specified interface. For
example, a server that is intended to serve a local subnet over eth0
may be configured as follows:

::

   "Dhcp6": {
       "subnet6": [
           {
               "subnet": "2001:db8:beef::/48",
               "pools": [
                    {
                        "pool": "2001:db8:beef::/48"
                    }
                ],
               "interface": "eth0"
           }
       ],
       ...
   }

.. _dhcp6-rapid-commit:

Rapid Commit
------------

The Rapid Commit option, described in `RFC
8415 <https://tools.ietf.org/html/rfc8415>`__, is supported by the Kea
DHCPv6 server. However, support is disabled by default. It can be
enabled on a per-subnet basis using the ``rapid-commit`` parameter as
shown below:

::

   "Dhcp6": {
       "subnet6": [
           {
               "subnet": "2001:db8:beef::/48",
               "rapid-commit": true,
               "pools": [
                    {
                        "pool": "2001:db8:beef::1-2001:db8:beef::10"
                    }
                ],
           }
       ],
       ...
   }

This setting only affects the subnet for which ``rapid-commit`` is
set to ``true``. For clients connected to other subnets, the server will
ignore the Rapid Commit option sent by the client and will follow the
4-way exchange procedure, i.e. respond with an Advertise for a Solicit
containing a Rapid Commit option.

.. _dhcp6-relays:

DHCPv6 Relays
-------------

A DHCPv6 server with multiple subnets defined must select the
appropriate subnet when it receives a request from a client. For clients
connected via relays, two mechanisms are used:

The first uses the linkaddr field in the RELAY_FORW message. The name of
this field is somewhat misleading in that it does not contain a
link-layer address; instead, it holds an address (typically a global
address) that is used to identify a link. The DHCPv6 server checks to
see whether the address belongs to a defined subnet and, if it does,
that subnet is selected for the client's request.

The second mechanism is based on interface-id options. While forwarding
a client's message, relays may insert an interface-id option into the
message that identifies the interface on the relay that received the
message. (Some relays allow configuration of that parameter, but it is
sometimes hard-coded and may range from the very simple (e.g. "vlan100")
to the very cryptic; one example seen on real hardware was
"ISAM144|299|ipv6|nt:vp:1:110"). The server can use this information to
select the appropriate subnet. The information is also returned to the
relay, which then knows the interface to use to transmit the response to
the client. For this to work successfully, the relay interface IDs must
be unique within the network and the server configuration must match
those values.

When configuring the DHCPv6 server, it should be noted that two
similarly named parameters can be configured for a subnet:

-  ``interface`` defines which local network interface can be used to
   access a given subnet.

-  ``interface-id`` specifies the content of the interface-id option
   used by relays to identify the interface on the relay to which the
   response packet is sent.

The two are mutually exclusive; a subnet cannot be reachable both
locally (direct traffic) and via relays (remote traffic). Specifying
both is a configuration error and the DHCPv6 server will refuse such a
configuration.

The following example configuration shows how to specify an interface-id
with a value of "vlan123":

::

   "Dhcp6": {
       "subnet6": [
           {
               "subnet": "2001:db8:beef::/48",
               "pools": [
                    {
                        "pool": "2001:db8:beef::/48"
                    }
                ],
               "interface-id": "vlan123"
           }
       ],
       ...
   }

.. _dhcp6-rsoo:

Relay-Supplied Options
----------------------

`RFC 6422 <https://tools.ietf.org/html/rfc6422>`__ defines a mechanism
called Relay-Supplied DHCP Options. In certain cases relay agents are
the only entities that may have specific information, and they can
insert options when relaying messages from the client to the server. The
server will then do certain checks and copy those options to the
response sent to the client.

There are certain conditions that must be met for the option to be
included. First, the server must not provide the option itself; in other
words, if both relay and server provide an option, the server always
takes precedence. Second, the option must be RSOO-enabled. (RSOO is the
"Relay Supplied Options option.") IANA maintains a list of RSOO-enabled
options
`here <https://www.iana.org/assignments/dhcpv6-parameters/dhcpv6-parameters.xhtml#options-relay-supplied>`__.
However, there may be cases when system administrators want to echo
other options. Kea can be instructed to treat other options as
RSOO-enabled. For example, to mark options 110, 120, and 130 as
RSOO-enabled, the following syntax should be used:

::

   "Dhcp6": {
       "relay-supplied-options": [ "110", "120", "130" ],
       ...
   }

As of February 2019, only option 65 is RSOO-enabled by IANA. This option
will always be treated as such, so there is no need to explicitly mark
it. Also, when enabling standard options, it is possible to use their
names rather than their option code, e.g. use ``dns-servers`` instead of
``23``. See ref:`dhcp6-std-options-list` for the names. In
certain cases this may also work for custom options, but due to the
nature of the parser code this may be unreliable and should be avoided.

.. _dhcp6-client-classifier:

Client Classification in DHCPv6
-------------------------------

The DHCPv6 server includes support for client classification. For a
deeper discussion of the classification process see :ref:`classify`.

In certain cases it is useful to configure the server to differentiate
between DHCP client types and treat them accordingly. Client
classification can be used to modify the behavior of almost any part of
the DHCP message processing. Kea currently offers
three mechanisms that take advantage of client classification in DHCPv6:
subnet selection, address pool selection, and DHCP options assignment.

Kea can be instructed to limit access to given subnets based on class
information. This is particularly useful for cases where two types of
devices share the same link and are expected to be served from two
different subnets. The primary use case for such a scenario is cable
networks, where there are two classes of devices: the cable modem
itself, which should be handed a lease from subnet A; and all other
devices behind the modem, which should get a lease from subnet B. That
segregation is essential to prevent overly curious users from playing
with their cable modems. For details on how to set up class restrictions
on subnets, see :ref:`classification-subnets`.

When subnets belong to a shared network, the classification applies to
subnet selection but not to pools; that is, a pool in a subnet limited to a
particular class can still be used by clients which do not belong to the
class, if the pool they are expected to use is exhausted. So the limit
on access based on class information is also available at the
address/prefix pool level; see :ref:`classification-pools`, within a
subnet. This is useful when segregating clients belonging to the same
subnet into different address ranges.

In a similar way, a pool can be constrained to serve only known clients,
i.e. clients which have a reservation, using the built-in "KNOWN" or
"UNKNOWN" classes. Addresses can be assigned to registered clients
without giving a different address per reservation, for instance when
there are not enough available addresses. The determination whether
there is a reservation for a given client is made after a subnet is
selected, so it is not possible to use "KNOWN"/"UNKNOWN" classes to select a
shared network or a subnet.

The process of classification is conducted in five steps. The first step
is to assess an incoming packet and assign it to zero or more classes.
The second step is to choose a subnet, possibly based on the class
information. When the incoming packet is in the special class, "DROP,
it is dropped and a debug message logged.
The next step is to evaluate class expressions depending on the built-in
"KNOWN"/"UNKNOWN" classes after host reservation lookup, using them for
pool/pd-pool selection and assigning classes from host reservations. The
list of required classes is then built and each class of the list has
its expression evaluated; when it returns "true" the packet is added as
a member of the class. The last step is to assign options, again possibly
based on the class information. More complete and detailed information
is available in :ref:`classify`.

There are two main methods of classification. The first is automatic and
relies on examining the values in the vendor class options or the
existence of a host reservation. Information from these options is
extracted, and a class name is constructed from it and added to the
class list for the packet. The second specifies an expression that is
evaluated for each packet. If the result is "true", the packet is a
member of the class.

.. note::

   Care should be taken with client classification, as it is easy for
   clients that do not meet class criteria to be denied all service.

Defining and Using Custom Classes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following example shows how to configure a class using an expression
and a subnet using that class. This configuration defines the class
named "Client_enterprise". It is comprised of all clients whose client
identifiers start with the given hex string (which would indicate a DUID
based on an enterprise id of 0xAABBCCDD). Members of this class will be given an address
from 2001:db8:1::0 to 2001:db8:1::FFFF and the addresses of their DNS
servers set to 2001:db8:0::1 and 2001:db8:2::1.

::

   "Dhcp6": {
       "client-classes": [
           {
               "name": "Client_enterprise",
               "test": "substring(option[1].hex,0,6) == 0x0002AABBCCDD",
               "option-data": [
                   {
                       "name": "dns-servers",
                       "code": 23,
                       "space": "dhcp6",
                       "csv-format": true,
                       "data": "2001:db8:0::1, 2001:db8:2::1"
                   }
               ]
           },
           ...
       ],
       "subnet6": [
           {
               "subnet": "2001:db8:1::/64",
               "pools": [ { "pool": "2001:db8:1::-2001:db8:1::ffff" } ],
               "client-class": "Client_enterprise"
           }
       ],
       ...
   }

This example shows a configuration using an automatically generated
"VENDOR_CLASS\_" class. The administrator of the network has decided that
addresses in the range 2001:db8:1::1 to 2001:db8:1::ffff are to be
managed by the DHCP6 server and that only clients belonging to the
eRouter1.0 client class are allowed to use that pool.

::

   "Dhcp6": {
       "subnet6": [
           {
               "subnet": "2001:db8:1::/64",
               "pools": [
                    {
                        "pool": "2001:db8:1::-2001:db8:1::ffff"
                    }
                ],
               "client-class": "VENDOR_CLASS_eRouter1.0"
           }
       ],
       ...
   }

.. _dhcp6-required-class:

Required Classification
~~~~~~~~~~~~~~~~~~~~~~~

In some cases it is useful to limit the scope of a class to a
shared network, subnet, or pool. There are two parameters which are used
to limit the scope of the class by instructing the server to evaluate
test expressions when required.

The first one is the per-class ``only-if-required`` flag, which is false
by default. When it is set to ``true``, the test expression of the class
is not evaluated at the reception of the incoming packet but later, and
only if the class evaluation is required.

The second is ``require-client-classes``, which takes a list of class
names and is valid in shared-network, subnet, and pool scope. Classes in
these lists are marked as required and evaluated after selection of this
specific shared-network/subnet/pool and before output option processing.

In this example, a class is assigned to the incoming packet when the
specified subnet is used:

::

   "Dhcp6": {
       "client-classes": [
          {
              "name": "Client_foo",
              "test": "member('ALL')",
              "only-if-required": true
          },
          ...
       ],
       "subnet6": [
           {
               "subnet": "2001:db8:1::/64"
               "pools": [
                    {
                        "pool": "2001:db8:1::-2001:db8:1::ffff"
                    }
                ],
               "require-client-classes": [ "Client_foo" ],
               ...
           },
           ...
       ],
       ...
   }

Required evaluation can be used to express complex dependencies like
subnet membership. It can also be used to reverse the
precedence; if an option-data is set in a subnet, it takes precedence
over an option-data in a class. If the option-data is moved to a
required class and required in the subnet, a class evaluated earlier
may take precedence.

Required evaluation is also available at shared-network and pool/pd-pool
levels. The order in which required classes are considered is:
shared-network, subnet, and (pd-)pool, i.e. in the opposite order in which
option-data is processed.

.. _dhcp6-ddns-config:

DDNS for DHCPv6
---------------

As mentioned earlier, kea-dhcp6 can be configured to generate requests
to the DHCP-DDNS server (referred to here as "D2") to update DNS
entries. These requests are known as Name Change Requests or NCRs. Each
NCR contains the following information:

1. Whether it is a request to add (update) or remove DNS entries

2. Whether the change requests forward DNS updates (AAAA records),
   reverse DNS updates (PTR records), or both

3. The Fully Qualified Domain Name (FQDN), lease address, and DHCID
   (information identifying the client associated with the FQDN)

Prior to Kea 1.7.1, all parameters for controlling DDNS were within the
global ``dhcp-ddns`` section of the kea-dhcp6.  Beginning with Kea 1.7.1
DDNS related parameters were split into two groups:

1. Connectivity Parameters

    These are parameters which specify where and how kea-dhcp6 connects to
    and communicates with D2.  These parameters can only be specified
    within the top-level ``dhcp-ddns`` section in the kea-dhcp6
    configuration.  The connectivity parameters are listed below:

    -  ``enable-updates``
    -  ``server-ip``
    -  ``server-port``
    -  ``sender-ip``
    -  ``sender-port``
    -  ``max-queue-size``
    -  ``ncr-protocol``
    -  ``ncr-format"``

2. Behavioral Parameters

    These parameters influence behavior such as how client host names and
    FQDN options are handled.  They have been moved out of the ``dhcp-ddns``
    section so that they may be specified at the global, shared-network,
    and/or subnet levels.  Furthermore, they are inherited downward from global to
    shared-network to subnet.  In other words, if a parameter is not specified at
    a given level, the value for that level comes from the level above it.
    The behavioral parameter as follows:

    -  ``ddns-send-updates``
    -  ``ddns-override-no-update``
    -  ``ddns-override-client-update``
    -  ``ddns-replace-client-name"``
    -  ``ddns-generated-prefix``
    -  ``ddns-qualifying-suffix``
    -  ``ddns-update-on-renew``
    -  ``ddns-use-conflict-resolution``
    -  ``hostname-char-set``
    -  ``hostname-char-replacement``

.. note::

    For backward compatibility, configuration parsing will still recognize
    the original behavioral parameters specified in ``dhcp-ddns``.  It will
    do so by translating the parameter into its global equivalent.  If a
    parameter is specified both globally and in ``dhcp-ddns``, the latter
    value will be ignored.  In either case, a log will be emitted explaining
    what has occurred.  Specifying these values within ``dhcp-ddns`` is
    deprecated and support for it will be removed at some future date.

The default configuration and values would appear as follows:

::

   "Dhcp6": {
        "dhcp-ddns": {
           // Connectivity parameters
           "enable-updates": false,
            "server-ip": "127.0.0.1",
            "server-port":53001,
            "sender-ip":"",
            "sender-port":0,
            "max-queue-size":1024,
            "ncr-protocol":"UDP",
            "ncr-format":"JSON"
        },

        // Behavioral parameters (global)
        "ddns-send-updates": true,
        "ddns-override-no-update": false,
        "ddns-override-client-update": false,
        "ddns-replace-client-name": "never",
        "ddns-generated-prefix": "myhost",
        "ddns-qualifying-suffix": "",
        "ddns-update-on-renew": false,
        "ddns-use-conflict-resolution": true,
        "hostname-char-set": "",
        "hostname-char-replacement": ""
        ...
   }

As of Kea 1.7.1, there are two parameters which determine if kea-dhcp6
can generate DDNS requests to D2: the existing ``dhcp-ddns:enable-updates``
parameter, which now only controls whether kea-dhcp6 connects to D2;
and the new behavioral parameter, ``ddns-send-updates``, which determines
whether DDNS updates are enabled at a given level (i.e. global, shared-network,
or subnet). The following table shows how the two parameters function
together:

.. table:: Enabling and Disabling DDNS Updates

   +-----------------+--------------------+-------------------------------+
   | dhcp-ddns:      | Global             | Outcome                       |
   | enable-updates  | ddns-send-updates  |                               |
   +=================+====================+===============================+
   | false (default) | false              | no updates at any scope       |
   +-----------------+--------------------+-------------------------------+
   | false           | true (default)     | no updates at any scope       |
   +-----------------+--------------------+-------------------------------+
   | true            | false              | updates only at scopes with   |
   |                 |                    | a local value of true for     |
   |                 |                    | ddns-enable-updates           |
   +-----------------+--------------------+-------------------------------+
   | true            | true               | updates at all scopes except  |
   |                 |                    | those with a local value of   |
   |                 |                    | false for ddns-enable-updates |
   +-----------------+--------------------+-------------------------------+

Kea 1.9.1 adds two new parameters. The first new parameter is ``ddns-update-on-renew``.
Normally, when leases are renewed the server only updates DNS if the DNS
information for the lease (e.g. FQDN, DNS update direction flags) has changed.
Setting ``ddns-update-on-renew`` to true instructs the server to always update
the DNS information when a lease is renewed even if its DNS information has not
changed. This allows Kea to "self-heal" if it was previously unable
to add DNS entries or they were somehow lost by the DNS server.

.. note::

    Setting ``ddns-update-on-renew`` to true may impact performance, especially
    for servers with numerous clients who renew often.

The second parameter added in Kea 1.9.1 is ``ddns-use-conflict-resolution``.
The value of this parameter is passed by kea-dhcp6 to D2 with each DNS update
request.  When true, (the default value), D2 will employ conflict resolution,
as described in `RFC 4703 <https://tools.ietf.org/html/rfc4703>`__, when
attempting to fulfill the update request.  When false, D2 will simply attempt
to update the DNS entries per the request, regardless of whether or not they
conflict with existing entries owned by other DHCP6 clients.

.. note::

    Setting ``ddns-use-conflict-resolution`` to false disables the overwrite
    safeguards that the rules of conflict resolution (
    `RFC 4703 <https://tools.ietf.org/html/rfc4703>`__) are intended to
    prevent.  This means that existing entries for a FQDN or an
    IP address made for Client-A can be deleted or replaced by entries
    for Client-B.  Furthermore, there are two scenarios by which entries
    for multiple clients for the same key (e.g. FQDN or IP) can be created.

    1. Client-B uses the same FQDN as Client-A but a different IP address.
    In this case the forward DNS entries (AAAA, and DHCID RRs) for
    Client-A will be deleted as they match the FQDN and new entries for
    Client-B will be added.  The reverse DNS entries (PTR and DHCID RRs)
    for Client-A, however, will not be deleted as they belong to a different
    IP address while new entries for Client-B will still be added.

    2. Client-B uses the same IP address as Client-A but a different FQDN.
    In this case the reverse DNS entries (PTR and DHCID RRs) for Client-A
    will be deleted as they match the IP address and new entries for
    Client-B will be added.  The forward DNS entries (AAAA and DHCID RRs)
    for Client-A, however, will not be deleted as they belong to a different
    FQDN while new entries for Client-B will still be added.

    Disabling conflict resolution should be done only after careful review of
    specific use cases. The best way to avoid unwanted DNS entries is to
    always ensure lease changes are processed through Kea, whether they are
    released, expire, or are deleted via the lease-del6 command, prior to
    reassigning either FQDNs or IP addresses. Doing so causes kea-dhcp6
    to generate DNS removal requests to D2.

.. note::

    The DNS entries Kea creates contain a value for TTL (time to live).  As of
    Kea 1.9.3, kea-dhcp6 calculates that value based on
    `RFC 4702, Section 5 <https://tools.ietf.org/html/rfc4702#section-5>`__
    which suggests that the TTL value be 1/3 of the lease's lifetime with
    a minimum value of 10 minutes.  Prior to this the server set the TTL value
    equal to the lease's valid lifetime.  Future releases may add one or
    more parameters to customize this value.

.. _dhcpv6-d2-io-config:

DHCP-DDNS Server Connectivity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For NCRs to reach the D2 server, kea-dhcp6 must be able to communicate
with it. kea-dhcp6 uses the following configuration parameters to
control this communication:

-  ``enable-updates`` - As of Kea 1.7.1, this parameter only enables
   connectivity to kea-dhcp-ddns such that DDNS updates can be constructed
   and sent.  It must be true for NCRs to be generated and sent to D2.
   It defaults to false.

-  ``server-ip`` - IP address on which D2 listens for requests. The
   default is the local loopback interface at address 127.0.0.1.
   Either an IPv4 or IPv6 address may be specified.

-  ``server-port`` - port on which D2 listens for requests. The default
   value is 53001.

-  ``sender-ip`` - the IP address which kea-dhcp6 uses to send requests to
   D2. The default value is blank, which instructs kea-dhcp6 to select a
   suitable address.

-  ``sender-port`` - the port which kea-dhcp6 uses to send requests to D2.
   The default value of 0 instructs kea-dhcp6 to select a suitable port.

-  ``max-queue-size`` - the maximum number of requests allowed to queue
   waiting to be sent to D2. This value guards against requests
   accumulating uncontrollably if they are being generated faster than
   they can be delivered. If the number of requests queued for
   transmission reaches this value, DDNS updating will be turned off
   until the queue backlog has been sufficiently reduced. The intent is
   to allow the kea-dhcp6 server to continue lease operations without running the
   risk that its memory usage grows without limit. The default value is
   1024.

-  ``ncr-protocol`` - the socket protocol to use when sending requests to
   D2. Currently only UDP is supported.

-  ``ncr-format`` - the packet format to use when sending requests to D2.
   Currently only JSON format is supported.

By default, kea-dhcp-ddns is assumed to be running on the same machine
as kea-dhcp6, and all of the default values mentioned above should be
sufficient. If, however, D2 has been configured to listen on a different
address or port, these values must be altered accordingly. For example, if
D2 has been configured to listen on 2001:db8::5 port 900, the following
configuration is required:

::

   "Dhcp6": {
       "dhcp-ddns": {
           "server-ip": "2001:db8::5",
           "server-port": 900,
           ...
       },
       ...
   }

.. _dhcpv6-d2-rules-config:

When Does the kea-dhcp6 Server Generate a DDNS Request?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

kea-dhcp6 follows the behavior prescribed for DHCP servers in `RFC
4704 <https://tools.ietf.org/html/rfc4704>`__. It is important to keep in
mind that kea-dhcp6 makes the initial decision of when and what to
update and forwards that information to D2 in the form of NCRs. Carrying
out the actual DNS updates and dealing with such things as conflict
resolution are within the purview of D2 itself
(see :ref:`dhcp-ddns-server`). This section describes when kea-dhcp6
will generate NCRs and the configuration parameters that can be used to
influence this decision. It assumes that the ``enable-updates``
parameter is true.

.. note::

   Currently the interface between kea-dhcp6 and D2 only supports
   requests which update DNS entries for a single IP address. If a lease
   grants more than one address, kea-dhcp6 will create the DDNS update
   request for only the first of these addresses.

In general, kea-dhcp6 will generate DDNS update requests when:

1. A new lease is granted in response to a DHCPREQUEST;

2. An existing lease is renewed but the FQDN associated with it has
   changed; or

3. An existing lease is released in response to a DHCPRELEASE.

In the second case, lease renewal, two DDNS requests will be issued: one
request to remove entries for the previous FQDN, and a second request to
add entries for the new FQDN. In the last case, a lease release, a
single DDNS request to remove its entries will be made.

As for the first case, the decisions involved when granting a new lease are
more complex. When a new lease is granted, kea-dhcp6 will generate a
DDNS update request only if the DHCPREQUEST contains the FQDN option
(code 39). By default, kea-dhcp6 will respect the FQDN N and S flags
specified by the client as shown in the following table:

.. table:: Default FQDN Flag Behavior

   +-----------------+-----------------+-----------------+-----------------+
   | Client          | Client Intent   | Server Response | Server          |
   | Flags:N-S       |                 |                 | Flags:N-S-O     |
   +=================+=================+=================+=================+
   | 0-0             | Client wants to | Server          | 1-0-0           |
   |                 | do forward      | generates       |                 |
   |                 | updates, server | reverse-only    |                 |
   |                 | should do       | request         |                 |
   |                 | reverse updates |                 |                 |
   +-----------------+-----------------+-----------------+-----------------+
   | 0-1             | Server should   | Server          | 0-1-0           |
   |                 | do both forward | generates       |                 |
   |                 | and reverse     | request to      |                 |
   |                 | updates         | update both     |                 |
   |                 |                 | directions      |                 |
   +-----------------+-----------------+-----------------+-----------------+
   | 1-0             | Client wants no | Server does not | 1-0-0           |
   |                 | updates done    | generate a      |                 |
   |                 |                 | request         |                 |
   +-----------------+-----------------+-----------------+-----------------+

The first row in the table above represents "client delegation." Here
the DHCP client states that it intends to do the forward DNS updates and
the server should do the reverse updates. By default, kea-dhcp6 will
honor the client's wishes and generate a DDNS request to D2 to update
only reverse DNS data. The parameter ``ddns-override-client-update`` can be
used to instruct the server to override client delegation requests. When
this parameter is "true", kea-dhcp6 will disregard requests for client
delegation and generate a DDNS request to update both forward and
reverse DNS data. In this case, the N-S-O flags in the server's response
to the client will be 0-1-1 respectively.

(Note that the flag combination N=1, S=1 is prohibited according to `RFC
4702 <https://tools.ietf.org/html/rfc4702>`__. If such a combination is
received from the client, the packet will be dropped by kea-dhcp6.)

To override client delegation, set the following values in the
configuration file:

::

    "Dhcp6": {
        ...
        "ddns-override-client-update": true,
        ...
    }

The third row in the table above describes the case in which the client
requests that no DNS updates be done. The parameter,
``ddns-override-no-update``, can be used to instruct the server to disregard
the client's wishes. When this parameter is true, kea-dhcp6 will
generate DDNS update requests to kea-dhcp-ddns even if the client
requests that no updates be done. The N-S-O flags in the server's response to
the client will be 0-1-1.

To override client delegation, issue the following commands:

::

    "Dhcp6": {
        ...
        "ddns-override-no-update": true,
        ...
    }

.. _dhcpv6-fqdn-name-generation:

kea-dhcp6 Name Generation for DDNS Update Requests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each Name Change Request must of course include the fully qualified
domain name whose DNS entries are to be affected. kea-dhcp6 can be
configured to supply a portion or all of that name, based upon what it
receives from the client in the DHCPREQUEST.

The default rules for constructing the FQDN that will be used for DNS
entries are:

1. If the DHCPREQUEST contains the client FQDN option, take the
   candidate name from there.

2. If the candidate name is a partial (i.e. unqualified) name, then add
   a configurable suffix to the name and use the result as the FQDN.

3. If the candidate name provided is empty, generate an FQDN using a
   configurable prefix and suffix.

4. If the client provides neither option, then take no DNS action.

These rules can be amended by setting the ``ddns-replace-client-name``
parameter, which provides the following modes of behavior:

-  ``never`` - use the name the client sent. If the client sent no name,
   do not generate one. This is the default mode.

-  ``always`` - replace the name the client sent. If the client sent no
   name, generate one for the client.

-  ``when-present`` - replace the name the client sent. If the client
   sent no name, do not generate one.

-  ``when-not-present`` - use the name the client sent. If the client
   sent no name, generate one for the client.

..

.. note::

   Note that in early versions of Kea, this parameter was a boolean and
   permitted only values of ``true`` and ``false``.
   Boolean values have been deprecated and are no longer accepted.
   Administrators currently using booleans must replace them with the
   desired mode name. A value of ``true`` maps to ``"when-present"``, while
   ``false`` maps to ``"never"``.

For example, to instruct kea-dhcp6 to always generate the FQDN for a
client, set the parameter ``ddns-replace-client-name`` to ``always`` as
follows:

::

    "Dhcp6": {
        ...
        "ddns-replace-client-name": "always",
        ...
    }

The prefix used in the generation of an FQDN is specified by the
``ddns-generated-prefix`` parameter. The default value is "myhost". To alter
its value, simply set it to the desired string:

::

    "Dhcp6": {
        ...
        "ddns-generated-prefix": "another.host",
        ...
    }

The suffix used when generating an FQDN, or when qualifying a partial
name, is specified by the ``ddns-qualifying-suffix`` parameter. This
parameter has no default value; thus, it is mandatory when DDNS updates
are enabled. To set its value simply set it to the desired string:

::

    "Dhcp6": {
        ...
        "ddns-qualifying-suffix": "foo.example.org",
        ...
    }

When qualifying a partial name, kea-dhcp6 constructs the name in the
format:

[**candidate-name**].[**ddns-qualifying-suffix**].

where **candidate-name** is the partial name supplied in the DHCPREQUEST.
For example, if the FQDN domain name value is "some-computer" and the
``ddns-qualifying-suffix`` "example.com", the generated FQDN is:

**some-computer.example.com.**

When generating the entire name, kea-dhcp6 will construct the name in
the format:

[**ddns-generated-prefix**]-[**address-text**].[**ddns-qualifying-suffix**].

where **address-text** is simply the lease IP address converted to a
hyphenated string. For example, if the lease address is 3001:1::70E, the
qualifying suffix "example.com", and the default value is used for
``ddns-generated-prefix``, the generated FQDN is:

**myhost-3001-1--70E.example.com.**

.. _dhcp6-host-name-sanitization:

Sanitizing Client FQDN Names
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Some DHCP clients may provide values in the name
component of the FQDN option (option code 39) that contain undesirable
characters. It is possible to configure kea-dhcp6 to sanitize these
values. The most typical use case is ensuring that only characters that
are permitted by RFC 1035 be included: A-Z, a-z, 0-9, and '-'. This may be
accomplished with the following two parameters:

-  ``hostname-char-set`` - a regular expression describing the invalid
   character set. This can be any valid, regular expression using POSIX
   extended expression syntax.  Embedded nulls (0x00) are always
   considered an invalid character to be replaced (or omitted).

-  ``hostname-char-replacement`` - a string of zero or more characters
   with which to replace each invalid character in the host name. An empty
   string causes invalid characters to be OMITTED rather than replaced.

.. note::

    Starting with Kea 1.7.5, the default values are as follows:

    - "hostname-char-set": "[^A-Za-z0-9.-]",
    - "hostname-char-replacement": ""

    This enables sanitizing and omits any character that is not
    a letter, digit, hyphen, dot, or null.

The following configuration replaces anything other than a letter,
digit, hyphen, or dot with the letter 'x':
::

    "Dhcp6": {
        ...
        "hostname-char-set": "[^A-Za-z0-9.-]",
        "hostname-char-replacement": "x",
        ...
    }

Thus, a client-supplied value of "myhost-$[123.org" would become
"myhost-xx123.org". Sanitizing is performed only on the portion of the
name supplied by the client, and it is performed before applying a
qualifying suffix (if one is defined and needed).

.. note::

   The following are some considerations to keep in mind:
   Name sanitizing is meant to catch the more common cases of invalid
   characters through a relatively simple character-replacement scheme.
   It is difficult to devise a scheme that works well in all cases.
   Administrators who find they have clients with odd corner cases of
   character combinations that cannot be readily handled with this
   mechanism should consider writing a hook that can carry out
   sufficiently complex logic to address their needs.

   Do not include dots in the hostname-char-set expression. When
   scrubbing FQDNs, dots are treated as delimiters and used to separate
   the option value into individual domain labels that are scrubbed and
   then re-assembled.

   If clients are sending values that differ only by characters
   considered as invalid by the hostname-char-set, be aware that
   scrubbing them will yield identical values. In such cases, DDNS
   conflict rules will permit only one of them to register the name.

   Finally, given the latitude clients have in the values they send, it
   is virtually impossible to guarantee that a combination of these two
   parameters will always yield a name that is valid for use in DNS. For
   example, using an empty value for hostname-char-replacement could
   yield an empty domain label within a name, if that label consists
   only of invalid characters.

.. note::

   Since the 1.6.0 Kea release, it is possible to specify hostname-char-set
   and/or hostname-char-replacement at the global scope. This allows
   sanitizing of host names without requiring a dhcp-ddns entry. When
   a hostname-char parameter is defined at the global scope and
   in a dhcp-ddns entry, the second (local) value is used.

.. _dhcp6-dhcp4o6-config:

DHCPv4-over-DHCPv6: DHCPv6 Side
-------------------------------

The support of DHCPv4-over-DHCPv6 transport is described in `RFC
7341 <https://tools.ietf.org/html/rfc7341>`__ and is implemented using
cooperating DHCPv4 and DHCPv6 servers. This section is about the
configuration of the DHCPv6 side (the DHCPv4 side is described in
:ref:`dhcp4-dhcp4o6-config`).

.. note::

   DHCPv4-over-DHCPv6 support is experimental and the details of the
   inter-process communication may change; both the DHCPv4 and DHCPv6
   sides should be running the same version of Kea. For instance, the
   support of port relay (RFC 8357) introduced an incompatible change.

There is only one specific parameter for the DHCPv6 side:
``dhcp4o6-port``, which specifies the first of the two consecutive ports
of the UDP sockets used for the communication between the DHCPv6 and
DHCPv4 servers. The DHCPv6 server is bound to ::1 on ``port`` and
connected to ::1 on ``port`` + 1.

Two other configuration entries are generally required: unicast traffic
support (see :ref:`dhcp6-unicast`) and DHCP 4o6
server address option (name "dhcp4o6-server-addr", code 88).

The following configuration was used during some tests:

::

   {

   # DHCPv6 conf
   "Dhcp6": {

       "interfaces-config": {
           "interfaces": [ "eno33554984/2001:db8:1:1::1" ]
       },

       "lease-database": {
           "type": "memfile",
           "name": "leases6"
       },

       "preferred-lifetime": 3000,
       "valid-lifetime": 4000,
       "renew-timer": 1000,
       "rebind-timer": 2000,

       "subnet6": [ {
           "subnet": "2001:db8:1:1::/64",
           "interface": "eno33554984",
           "pools": [ { "pool": "2001:db8:1:1::1:0/112" } ]
       } ],

       "dhcp4o6-port": 6767,

       "option-data": [ {
           "name": "dhcp4o6-server-addr",
           "code": 88,
           "space": "dhcp6",
           "csv-format": true,
           "data": "2001:db8:1:1::1"
       } ],


       "loggers": [ {
           "name": "kea-dhcp6",
           "output_options": [ {
               "output": "/tmp/kea-dhcp6.log"
           } ],
           "severity": "DEBUG",
           "debuglevel": 0
       } ]
   }

   }

..

.. note::

   Relayed DHCPv4-QUERY DHCPv6 messages are not supported.

.. _sanity-checks6:

Sanity Checks in DHCPv6
-----------------------

An important aspect of a well-running DHCP system is an assurance that
the data remain consistent. However, in some cases it may be convenient
to tolerate certain inconsistent data. For example, a network
administrator that temporarily removed a subnet from a configuration
would not want all the leases associated with it to disappear from the lease
database. Kea has a mechanism to control sanity checks for situations
such as this.

Kea supports a configuration scope called ``sanity-checks``. It
currently allows only a single parameter, called ``lease-checks``, which
governs the verification carried out when a new lease is loaded from a
lease file. This mechanism permits Kea to attempt to correct
inconsistent data.

Every subnet has a subnet-id value; this is how Kea internally
identifies subnets. Each lease has a subnet-id parameter as well, which
identifies which subnet it belongs to. However, if the configuration has
changed, it is possible that a lease could exist with a subnet-id, but
without any subnet that matches it. Also, it may be possible that the
subnet's configuration has changed and the subnet-id now belongs to a
subnet that does not match the lease. Kea's corrective algorithm first
checks to see if there is a subnet with the subnet-id specified by the
lease. If there is, it verifies whether the lease belongs to that
subnet. If not, depending on the lease-checks setting, the lease is
discarded, a warning is displayed, or a new subnet is selected for the
lease that matches it topologically.

Since delegated prefixes do not have to belong to a subnet in which
they are offered, there is no way to implement such a mechanism for IPv6
prefixes. As such, the mechanism works for IPv6 addresses only.

There are five levels which are supported:

-  ``none`` - do no special checks; accept the lease as is.

-  ``warn`` - if problems are detected display a warning, but
   accept the lease data anyway. This is the default value.

-  ``fix`` - if a data inconsistency is discovered, try to
   correct it. If the correction is not successful, the incorrect data
   will be inserted anyway.

-  ``fix-del`` - if a data inconsistency is discovered, try to
   correct it. If the correction is not successful, reject the lease.
   This setting ensures the data's correctness, but some
   incorrect data may be lost. Use with care.

-  ``del`` - this is the strictest mode. If any inconsistency is
   detected, reject the lease. Use with care.

This feature is currently implemented for the memfile backend. Note the
sanity check applies to the lease database in memory, not to the lease file,
i.e. inconsistent leases will stay in the lease file.

An example configuration that sets this parameter looks as follows:

::

   "Dhcp6": {
       "sanity-checks": {
           "lease-checks": "fix-del"
       },
       ...
   }

.. _store-extended-info-v6:

Storing Extended Lease Information
----------------------------------
In order to support such features as DHCPv6 Reconfigure
(`RFC 3315 <https://tools.ietf.org/html/rfc3315>`__) and LeaseQuery
(`RFC 5007 <https://tools.ietf.org/html/rfc5007>`__) it is necessary to
store additional information with each lease.  Because the amount
of information stored for each lease has ramifications in terms of
performance and system resource consumption, storing this additional
information is configurable through the "store-extended-info" parameter.
It defaults to false and may be set at the global, shared-network, and
subnet levels.

::

   "Dhcp6": {
       "store-extended-info": true,
       ...
   }

When enabled, information relevant to the DHCPv6 query (e.g. REQUEST, RENEW,
or REBIND) asking for the lease is added into the lease's user-context as a
map element labeled "ISC".  Currently the information contained in the map
will be a list of relays, one for each relay message layer that encloses the
client query. Other values may be added at a future date. The lease's
user-context for a two-hop query might look something like this (shown
pretty-printed for clarity):

::

    {
        "ISC": {
            "relays": [
            {
                "hop": 2,
                "link": "2001:db8::1",
                "peer": "2001:db8::2"
            },
            {
                "hop": 1,
                "link": "2001:db8::3",
                "options": "0x00C800080102030405060708",
                "peer": "2001:db8::4"
            }]
        }
    }


.. note::
    This feature is intended to be used in conjunction with an upcoming
    LeaseQuery hook library and at this time there is other use for this
    information within Kea.

.. note::
    It is possible that other hook libraries are already using
    user-context. Enabling store-extended-info should not interfere with
    any other user-context content, as long as it does not also use an element
    labeled "ISC". In other words, user-context is intended to be a flexible
    container serving multiple purposes. As long as no other purpose also
    writes an "ISC" element to user-context there should not be a conflict.

.. _dhcp6-multi-threading-settings:

Multi-Threading Settings
------------------------

The Kea server can be configured to process packets in parallel using multiple
threads. These settings can be found under ``multi-threading`` structure and are
represented by:

-  ``enable-multi-threading`` - use multiple threads to process packets in
   parallel (default false).

-  ``thread-pool-size`` - specify the number of threads to process packets in
   parallel.  Supported values are: 0 (auto detect), any positive number sets
   thread count explicitly (default 0).

-  ``packet-queue-size`` - specify the size of the queue used by the thread
   pool to process packets.  Supported values are: 0 (unlimited), any positive
   number sets queue size explicitly (default 64).

An example configuration that sets these parameter looks as follows:

::

   "Dhcp6": {
       "multi-threading": {
          "enable-multi-threading": true,
          "thread-pool-size": 4,
          "packet-queue-size": 16
       }
       ...
   }

Multi-Threading Settings in Different Backends
----------------------------------------------

Both kea-dhcp4 and kea-dhcp6 are tested internally to determine which settings
give the best performance. Although this section describes our results, they are merely
recommendations and are very dependent on the particular hardware that was used
for testing. We strongly advise that administrators run their own performance tests.

A full report of performance results for the latest stable Kea can be found
`here <https://reports.kea.isc.org/>`_.
This includes hardware and test scenario descriptions, as well as
current results.

After enabling multi-threading, the number of threads is set by ``thread-pool-size``
parameter, and results from our tests show that best configurations for
kea-dhcp6 are:

-  ``thread-pool-size``: 4 when using ``memfile`` for storing leases.

-  ``thread-pool-size``: 12 or more when using ``mysql`` for storing leases.

-  ``thread-pool-size``: 6 when using ``postgresql``.

Another very important parameter is ``packet-queue-size`` and in our tests we
used it as multiplier of ``thread-pool-size``. So actual setting strongly depends
on ``thread-pool-size``.

Our tests reported best results when:

-  ``packet-queue-size``: 150 * ``thread-pool-size`` when using ``memfile`` for
   storing leases. In our case it's 150 * 4 = 600. This means that at any given
   time, up to 600 packets could be queued.

-  ``packet-queue-size``: 200 * ``thread-pool-size`` when using ``mysql`` for
   storing leases. In our case it's 200 * 12 = 2400. This means that up to
   2400 packets could be queued.

-  ``packet-queue-size``: 11 * ``thread-pool-size`` when using ``postgresql`` for
   storing leases. In our case it's 11 * 6 = 66.


Lease Caching
-------------

Clients that attempt renewal frequently can cause the server to update
and write to the database frequently resulting in a performance impact
on the server. The cache parameters instruct the DHCP server to avoid
updating leases too frequently thus avoiding this behavior. Instead
the server assigns the same lease (i.e. reuses it) with no
modifications except for CLTT (Client Last Transmission Time) which
does not require disk operations.

The two parameters are the ``cache-threshold`` double and the
``cache-max-age`` integer and have no default, i.e. the lease caching
feature must be explicitly enabled. These parameters can be configured
at the global, shared network and subnet levels. The subnet level has
the precedence on the shared network level, the global level is used
as last resort. For example:

::

    "subnet6": [
        {
            "subnet": "2001:db8:1:1::/64",
            "pools": [ { "pool": "2001:db8:1:1::1:0/112" } ],
            "cache-threshold": .25,
            "cache-max-age": 600,
            "valid-lifetime": 2000,
            ...
        }
    ],

When an already assigned lease can fulfill a client query:

  - any important change e.g. for DDNS parameter, hostname, or
    preferred or valid lifetime reduction makes the lease not reusable

  - lease age i.e. the difference between the creation or last modification
    time and the current time is computed (elapsed duration)

  - if ``cache-max-age`` is explicitly configured, it is compared with the age
    and leases that are too old are not reusable (this means that the value 0
    for ``cache-max-age`` disables the lease cache feature)

  - if ``cache-threshold`` is explicitly configured and is between 0.0 and 1.0,
    it expresses the percentage of the lease valid lifetime which is
    allowed for the lease age. Values below and including 0.0 and
    values greater than 1.0 disable the lease cache feature.

In the example a lease with a valid lifetime of 2000 seconds can be
reused if it was committed less than 500 seconds ago. With a lifetime
of 3000 seconds the maximum age of 600 seconds applies.

In outbound client responses (e.g. DHCPV6_REPLY messages) used
preferred and valid lifetimes are the reusable values i.e. the
expiration dates do not change.

.. _host-reservation-v6:

Host Reservation in DHCPv6
==========================

There are many cases where it is useful to provide a configuration on a
per-host basis. The most obvious one is to reserve a specific, static
IPv6 address or/and prefix for exclusive use by a given client (host);
the returning client will receive the same address or/and prefix every time,
and other clients will never get that address. Another situation when host
reservations are applicable is when a host has specific requirements,
e.g. a printer that needs additional DHCP options or a cable modem that
needs specific parameters. Yet another possible use case is to define
unique names for hosts.

Note that there may be cases when a new reservation has been made for a
client for an address or prefix currently in use by another client. We
call this situation a "conflict." These conflicts get resolved
automatically over time as described in subsequent sections. Once the
conflict is resolved, the correct client will receive the reserved
configuration when it renews.

Host reservations are defined as parameters for each subnet. Each host
must be identified by either DUID or its hardware/MAC address; see
:ref:`mac-in-dhcpv6` for details. There
is an optional ``reservations`` array in the ``subnet6`` structure; each
element in that array is a structure that holds information about a
single host. In particular, the structure has an identifier that
uniquely identifies a host. In the DHCPv6 context, the identifier is
usually a DUID, but it can also be a hardware or MAC address. One or more
addresses or prefixes may also be specified, and it is possible to
specify a hostname and DHCPv6 options for a given host.

.. note::

   Kea requires that reserved addresses must be within the subnet.
   Kea 1.7.10 is the last release that does not enforce this.
   This does not apply to reserved prefixes.

The following example shows how to reserve addresses and prefixes for
specific hosts:

::

   "subnet6": [
       {
           "subnet": "2001:db8:1::/48",
           "pools": [ { "pool": "2001:db8:1::/80" } ],
           "pd-pools": [
               {
                   "prefix": "2001:db8:1:8000::",
                   "prefix-len": 48,
                   "delegated-len": 64
               }
           ],
           "reservations": [
               {
                   "duid": "01:02:03:04:05:0A:0B:0C:0D:0E",
                   "ip-addresses": [ "2001:db8:1::100" ]
               },
               {
                   "hw-address": "00:01:02:03:04:05",
                   "ip-addresses": [ "2001:db8:1::101", "2001:db8:1::102" ]
               },
               {
                   "duid": "01:02:03:04:05:06:07:08:09:0A",
                   "ip-addresses": [ "2001:db8:1::103" ],
                   "prefixes": [ "2001:db8:2:abcd::/64" ],
                   "hostname": "foo.example.com"
               }
           ]
       }
   ]

This example includes reservations for three different clients. The
first reservation is for the address 2001:db8:1::100 for a client using
DUID 01:02:03:04:05:0A:0B:0C:0D:0E. The second reservation is for two
addresses, 2001:db8:1::101 and 2001:db8:1::102, for a client using MAC
address 00:01:02:03:04:05. Lastly, address 2001:db8:1::103 and prefix
2001:db8:2:abcd::/64 are reserved for a client using DUID
01:02:03:04:05:06:07:08:09:0A. The last reservation also assigns a
hostname to this client.

Note that DHCPv6 allows a single client to lease multiple addresses and
multiple prefixes at the same time. Therefore ``ip-addresses`` and
``prefixes`` are plural and are actually arrays. When the client sends
multiple IA options (IA_NA or IA_PD), each reserved address or prefix is
assigned to an individual IA of the appropriate type. If the number of
IAs of a specific type is lower than the number of reservations of that
type, the number of reserved addresses or prefixes assigned to the
client is equal to the number of IA_NAs or IA_PDs sent by the client;
that is, some reserved addresses or prefixes are not assigned. However,
they still remain reserved for this client and the server will not
assign them to any other client. If the number of IAs of a specific type
sent by the client is greater than the number of reserved addresses or
prefixes, the server will try to assign all reserved addresses or
prefixes to the individual IAs and dynamically allocate addresses or
prefixes to the remaining IAs. If the server cannot assign a reserved
address or prefix because it is in use, the server will select the next
reserved address or prefix and try to assign it to the client. If the
server subsequently finds that there are no more reservations that can
be assigned to the client at that moment, the server will try to assign
leases dynamically.

Making a reservation for a mobile host that may visit multiple subnets
requires a separate host definition in each subnet that host is expected to
visit. It is not possible to define multiple host definitions with the
same hardware address in a single subnet. Multiple host definitions with
the same hardware address are valid if each is in a different subnet.
The reservation for a given host should include only one identifier,
either DUID or hardware address; defining both for the same host is
considered a configuration error.

Adding host reservations incurs a performance penalty. In principle,
when a server that does not support host reservation responds to a
query, it needs to check whether there is a lease for a given address
being considered for allocation or renewal. The server that does
support host reservation has to perform additional checks: not only
whether the address is currently used (i.e., if there is a lease for
it), but also whether the address could be used by someone else (i.e.,
if there is a reservation for it). That additional check incurs extra
overhead.

.. _reservation6-types:

Address/Prefix Reservation Types
--------------------------------

In a typical scenario there is an IPv6 subnet defined, with a certain
part of it dedicated for dynamic address allocation by the DHCPv6
server. There may be an additional address space defined for prefix
delegation. Those dynamic parts are referred to as dynamic pools,
address and prefix pools, or simply pools. In principle, a host
reservation can reserve any address or prefix that belongs to the
subnet. The reservations that specify addresses that belong to
configured pools are called "in-pool reservations." In contrast, those
that do not belong to dynamic pools are called "out-of-pool
reservations." There is no formal difference in the reservation syntax
and both reservation types are handled uniformly.

Kea supports global host reservations. These are reservations that are
specified at the global level within the configuration and that do not
belong to any specific subnet. Kea will still match inbound client
packets to a subnet as before, but when the subnet's reservation mode is
set to ``"global"``, Kea will look for host reservations only among the
global reservations defined. Typically, such reservations would be used
to reserve hostnames for clients which may move from one subnet to
another.

.. note::

   Global reservations, while useful in certain circumstances, have aspects
   that must be given due consideration when using them. Please see
   :ref:`reservation6-conflict` for more details.

.. note::

   Beginning with Kea 1.9.1 reservation mode was replaced by three
   boolean flags ``"reservations-global"``, ``"reservations-in-subnet"``
   and ``"reservations-out-of-pool"`` which allows the configuration of
   host reservations both globally and in a subnet. In such cases a subnet
   host reservation has preference over a global reservation
   when both exist for the same client.

.. _reservation6-conflict:

Conflicts in DHCPv6 Reservations
--------------------------------

As reservations and lease information are stored separately, conflicts
may arise. Consider the following series of events: the server has
configured the dynamic pool of addresses from the range of 2001:db8::10
to 2001:db8::20. Host A requests an address and gets 2001:db8::10. Now
the system administrator decides to reserve address 2001:db8::10 for
Host B. In general, reserving an address that is currently assigned to
someone else is not recommended, but there are valid use cases where
such an operation is warranted.

The server now has a conflict to resolve. If Host B boots up and
requests an address, the server is not able to assign the reserved
address 2001:db8::10. A naive approach would to be immediately remove
the lease for Host A and create a new one for Host B. That would not
solve the problem, though, because as soon as Host B gets the address,
it will detect that the address is already in use (by Host
A) and will send a DHCPDECLINE message. Therefore, in this situation,
the server has to temporarily assign a different address from the
dynamic pool (not matching what has been reserved) to Host B.

When Host A renews its address, the server will discover that the
address being renewed is now reserved for someone else - Host B.
The server will remove the lease for 2001:db8::10, select a
new address, and create a new lease for it. It will send two addresses
in its response: the old address, with lifetime set to 0 to explicitly
indicate that it is no longer valid; and the new address, with a
non-zero lifetime. When Host B tries to renew its temporarily assigned address,
the server will detect that the existing lease does not match the
reservation, so it will release the current address Host B has and will
create a new lease matching the reservation. As before, the server will
send two addresses: the temporarily assigned one with zeroed lifetimes,
and the new one that matches the reservation with proper lifetimes set.

This recovery will succeed, even if other hosts attempt to get the
reserved address. If Host C requests the address 2001:db8::10 after the
reservation is made, the server will propose a different address.

This recovery mechanism allows the server to fully recover from a case
where reservations conflict with existing leases; however, this procedure
will take roughly as long as the value set for renew-timer. The
best way to avoid such recovery is not to define new reservations that
conflict with existing leases. Another recommendation is to use
out-of-pool reservations. If the reserved address does not belong to a
pool, there is no way that other clients can get it.

.. note::

   The conflict-resolution mechanism does not work for global
   reservations. Although the global address reservations feature may be useful
   in certain settings, it is generally recommended not to use
   global reservations for addresses. Administrators who do choose
   to use global reservations must manually ensure that the reserved
   addresses are not in dynamic pools.

.. _reservation6-hostname:

Reserving a Hostname
--------------------

When the reservation for a client includes the ``hostname``, the server
will assign this hostname to the client and send it back in the Client
FQDN, if the client sent the FQDN option to the server. The reserved
hostname always takes precedence over the hostname supplied by the
client (via the FQDN option) or the autogenerated (from the IPv6
address) hostname.

The server qualifies the reserved hostname with the value of the
``ddns-qualifying-suffix`` parameter. For example, the following subnet
configuration:

::

   "subnet6": [
       {
           "subnet": "2001:db8:1::/48",
           "pools": [ { "pool": "2001:db8:1::/80" } ],
           "ddns-qualifying-suffix": "example.isc.org.",
           "reservations": [
               {
                   "duid": "01:02:03:04:05:0A:0B:0C:0D:0E",
                   "ip-addresses": [ "2001:db8:1::100" ]
                   "hostname": "alice-laptop"
               }
           ]
       }
   ],
   "dhcp-ddns": {
       "enable-updates": true
   }

will result in assigning the "alice-laptop.example.isc.org." hostname to
the client using the DUID "01:02:03:04:05:0A:0B:0C:0D:0E". If the
``ddns-qualifying-suffix`` is not specified, the default (empty) value will
be used, and in this case the value specified as a ``hostname`` will be
treated as a fully qualified name. Thus, by leaving the
``ddns-qualifying-suffix`` empty it is possible to qualify hostnames for
different clients with different domain names:

::

   "subnet6": [
       {
           "subnet": "2001:db8:1::/48",
           "pools": [ { "pool": "2001:db8:1::/80" } ],
           "reservations": [
               {
                   "duid": "01:02:03:04:05:0A:0B:0C:0D:0E",
                   "ip-addresses": [ "2001:db8:1::100" ]
                   "hostname": "mark-desktop.example.org."
               }
           ]
       }
   ],
   "dhcp-ddns": {
       "enable-updates": true,
   }

The above example results in the assignment of the
"mark-desktop.example.org." hostname to the client using the DUID
"01:02:03:04:05:0A:0B:0C:0D:0E".

.. _reservation6-options:

Including Specific DHCPv6 Options in Reservations
-------------------------------------------------

Kea offers the ability to specify options on a per-host basis. These
options follow the same rules as any other options. These can be
standard options (see :ref:`dhcp6-std-options`),
custom options (see :ref:`dhcp6-custom-options`),
or vendor-specific options (see :ref:`dhcp6-vendor-opts`). The following
example demonstrates how standard options can be defined.

::

   "reservations": [
   {
      "duid": "01:02:03:05:06:07:08",
      "ip-addresses": [ "2001:db8:1::2" ],
       "option-data": [
       {
           "option-data": [ {
               "name": "dns-servers",
               "data": "3000:1::234"
           },
           {
               "name": "nis-servers",
               "data": "3000:1::234"
           }
       } ]
   } ]

Vendor-specific options can be reserved in a similar manner:

::

   "reservations": [
   {
       "duid": "aa:bb:cc:dd:ee:ff",
       "ip-addresses": [ "2001:db8::1" ],
       "option-data": [
       {
           "name": "vendor-opts",
           "data": 4491
       },
       {
           "name": "tftp-servers",
           "space": "vendor-4491",
           "data": "3000:1::234"
       } ]
   } ]

Options defined at host level have the highest priority. In other words,
if there are options defined with the same type on global, subnet,
class, and host levels, the host-specific values will be used.

.. _reservation6-client-classes:

Reserving Client Classes in DHCPv6
----------------------------------

:ref:`classification-using-expressions` explains how to configure
the server to assign classes to a client, based on the content of the
options that this client sends to the server. Host reservations
mechanisms also allow for the static assignment of classes to clients.
The definitions of these classes are placed in the Kea configuration or
a database. The following configuration snippet shows how to specify that
a client belongs to classes ``reserved-class1`` and ``reserved-class2``. Those
classes are associated with specific options sent to the clients which belong
to them.

::

   {
       "client-classes": [
       {
          "name": "reserved-class1",
          "option-data": [
          {
              "name": "dns-servers",
              "data": "2001:db8:1::50"
          }
          ]
       },
       {
          "name": "reserved-class2",
          "option-data": [
          {
              "name": "nis-servers",
              "data": "2001:db8:1::100"
          }
          ]
       }
       ],
       "subnet6": [
       {   "pools": [ { "pool": "2001:db8:1::/64" } ],
           "subnet": "2001:db8:1::/48",
           "reservations": [
           {
               "duid": "01:02:03:04:05:06:07:08",

               "client-classes": [ "reserved-class1", "reserved-class2" ]

           }
           ]
       } ]
    }

In some cases the host reservations can be used in conjunction with client
classes specified within the Kea configuration. In particular, when a
host reservation exists for a client within a given subnet, the "KNOWN"
built-in class is assigned to the client. Conversely, when there is no
static assignment for the client, the "UNKNOWN" class is assigned to the
client. Class expressions within the Kea configuration file can
refer to "KNOWN" or "UNKNOWN" classes using the "member" operator.
For example:

::

    {
        "client-classes": [
            {
                "name": "dependent-class",
                "test": "member('KNOWN')",
                "only-if-required": true
            }
        ]
    }

Note that the ``only-if-required`` parameter is needed here to force
evaluation of the class after the lease has been allocated and thus the
reserved class has been also assigned.

.. note::
   Be aware that the classes specified in non-global host reservations
   are assigned to the processed packet after all classes with the
   ``only-if-required`` parameter set to ``false`` have been evaluated.
   This has an implication that these classes must not depend on the
   statically assigned classes from the host reservations. If there
   is a need to create such dependency, the ``only-if-required`` must
   be set to ``true`` for the dependent classes. Such classes are
   evaluated after the static classes have been assigned to the packet.
   This, however, imposes additional configuration overhead, because
   all classes marked as ``only-if-required`` must be listed in the
   ``require-client-classes`` list for every subnet where they are used.

.. note::
   Client classes specified within the Kea configuration file may
   depend on the classes specified within the global host reservations.
   In such a case the ``only-if-required`` parameter is not needed.
   Refer to the :ref:`pool-selection-with-class-reservations6` and
   :ref:`subnet-selection-with-class-reservations6`
   for the specific use cases.

.. _reservations6-mysql-pgsql-cql:

Storing Host Reservations in MySQL, PostgreSQL, or Cassandra
------------------------------------------------------------

It is possible to store host reservations in MySQL, PostgreSQL, or
Cassandra. See :ref:`hosts6-storage` for information on
how to configure Kea to use reservations stored in MySQL, PostgreSQL, or
Cassandra. Kea provides a dedicated hook for managing reservations in a
database; section :ref:`host-cmds` provides detailed information.
The `Kea wiki
<https://gitlab.isc.org/isc-projects/kea/wikis/designs/commands#23-host-reservations-hr-management>`__
provides some examples of how to conduct common host reservations
operations.

.. note::

   In Kea, the maximum length of an option specified per-host is
   arbitrarily set to 4096 bytes.

.. _reservations6-tuning:

Fine-Tuning DHCPv6 Host Reservation
-----------------------------------

The host reservation capability introduces additional restrictions for
the allocation engine (the component of Kea that selects an address for
a client) during lease selection and renewal. In particular, three major
checks are necessary. First, when selecting a new lease, it is not
sufficient for a candidate lease to simply not be in use by another DHCP
client; it also must not be reserved for another client. Second, when
renewing a lease, an additional check must be performed to see whether
the address being renewed is reserved for another client. Finally, when
a host renews an address or a prefix, the server must check whether
there is a reservation for this host, so the existing (dynamically
allocated) address should be revoked and the reserved one be used
instead.

Some of those checks may be unnecessary in certain deployments and not
performing them may improve performance. The Kea server provides the
``reservation-mode`` configuration parameter to select the types of
reservations allowed for a particular subnet. Each reservation type has
different constraints for the checks to be performed by the server when
allocating or renewing a lease for the client. Allowed values are:

-  ``all`` - enables both in-pool and out-of-pool host reservation
   types. This setting is the default value, and is the safest and most
   flexible. However, as all checks are conducted, it is also the slowest.
   It does not check against global reservations.

-  ``out-of-pool`` - allows only out-of-pool host reservations. With
   this setting in place, the server may assume that all host
   reservations are for addresses that do not belong to the dynamic
   pool. Therefore, it can skip the reservation checks when dealing with
   in-pool addresses, thus improving performance. Do not use this mode
   if any reservations use in-pool addresses. Caution is advised
   when using this setting; Kea does not sanity-check the reservations
   against ``reservation-mode`` and misconfiguration may cause problems.

-  ``global`` - allows only global host reservations. With this setting
   in place, the server searches for reservations for a client only
   among the defined global reservations. If an address is specified,
   the server skips the reservation checks carried out when dealing in
   other modes, thus improving performance. Caution is advised when
   using this setting; Kea does not sanity-check the reservations when
   ``global`` and misconfiguration may cause problems.

-  ``disabled`` - host reservation support is disabled. As there are no
   reservations, the server will skip all checks. Any reservations
   defined will be completely ignored. As the checks are skipped, the
   server may operate faster in this mode.

Since Kea 1.9.1, the ``reservation-mode`` is replaced by the
``reservations-global``, ``reservations-in-subnet`` and
``reservations-out-of-pool`` flags.
The flags can be activated independently and can produce various combinations,
some of them being unsupported by the deprecated ``reservation-mode``.

The ``reservation-mode`` parameter can be specified at:

- global level: ``.Dhcp6["reservation-mode"]`` (lowest priority: gets overridden
  by all others)

- subnet level: ``.Dhcp6.subnet6[]["reservation-mode"]`` (low priority)

- shared-network level: ``.Dhcp6["shared-networks"][]["reservation-mode"]``
  (high priority)

- shared-network subnet-level:
  ``.Dhcp6["shared-networks"][].subnet6[]["reservation-mode"]`` (highest
  priority: overrides all others)

To decide which ``"reservation-mode"`` to choose, the
following decision diagram may be useful:

::

                                  O
                                  |
                                  v
    +-----------------------------+------------------------------+
    |         Is per-host configuration needed, such as          |
    |                reserving specific addresses,               |
    |               assigning specific options or                |
    | assigning packets to specific classes on per-device basis? |
    +-+-----------------+----------------------------------------+
      |                 |
    no|              yes|
      |                 |   +--------------------------------------+
      |                 |   |         For all given hosts,         |
      +--> "disabled"   +-->+      can the reserved resources      |
                            |  be used in all configured subnets?  |
                            +--------+---------------------------+-+
                                     |                           |
    +----------------------------+   |no                         |yes
    |             Is             |   |                           |
    |  at least one reservation  +<--+               "global" <--+
    | used to reserve addresses  |
    |        or prefixes?        |
    +-+------------------------+-+
      |                        |
    no|                     yes|   +---------------------------+
      |                        |   | Is high leases-per-second |
      +--> "out-of-pool"       +-->+ performance or efficient  |
            ^                      |      resource usage       |
            |                      |  (CPU ticks, RAM usage,   |
            |                      |   database roundtrips)    |
            |                      | important to your setup?  |
            |                      +-+----------------+--------+
            |                        |                |
            |                     yes|              no|
            |                        |                |
            |          +-------------+                |
            |          |                              |
            |          |   +----------------------+   |
            |          |   | Can it be guaranteed |   |
            |          +-->+  that the reserved   |   |
            |              |  addresses/prefixes  |   |
            |              |  aren't part of the  |   |
            |              |   pools configured   |   |
            |              |  in the respective   |   |
            |              |       subnet?        |   |
            |              +-+------------------+-+   |
            |                |                  |     |
            |             yes|                no|     |
            |                |                  |     V
            +----------------+                  +--> "all"

An example configuration that disables reservations looks as follows:

.. code-block:: json

    {
      "Dhcp6": {
        "subnet6": [
          {
            "pools": [
              {
                "pool": "2001:db8:1::-2001:db8:1::100"
              }
            ],
            "reservation-mode": "disabled",
            "subnet": "2001:db8:1::/64"
          }
        ]
      }
    }

An example configuration using global reservations is shown below:

.. code-block:: json

    {
      "Dhcp6": {
        "reservation-mode": "global",
        "reservations": [
          {
            "duid": "00:03:00:01:11:22:33:44:55:66",
            "hostname": "host-one"
          },
          {
            "duid": "00:03:00:01:99:88:77:66:55:44",
            "hostname": "host-two"
          }
        ],
        "subnet6": [
          {
            "pools": [
              {
                "pool": "2001:db8:1::-2001:db8:1::100"
              }
            ],
            "subnet": "2001:db8:1::/64"
          }
        ]
      }
    }

The meaning of the reservation flags are:

- ``reservations-global``: fetch global reservations.

- ``reservations-in-subnet``: fetch subnet reservations. For a shared network
  this includes all subnet members of the shared network.

- ``reservations-out-of-pool``: this makes sense only when the
  ``reservations-in-subnet`` flag is true. When ``reservations-out-of-pool``
  is true the server may assume that all host reservations are for addresses
  that do not belong to the dynamic pool. Therefore, it can skip the reservation
  checks when dealing with in-pool addresses, thus improving performance.
  Also the server will not assign reserved addresses that are inside the dynamic
  pools to the respective clients. This also means that the addresses matching
  the respective reservations from inside the dynamic pools (if any) can be
  dynamically assigned to any client.

The ``reservation-mode`` will be deprecated in a future Kea version.

The correspondence of old values are:

``disabled``:

.. code-block:: json

    {
      "Dhcp6": {
        "reservations-global": false,
        "reservations-in-subnet": false
      }
    }

``global``:

.. code-block:: json

    {
      "Dhcp6": {
        "reservations-global": true,
        "reservations-in-subnet": false
      }
    }

``out-of-pool``:

.. code-block:: json

    {
      "Dhcp6": {
        "reservations-global": false,
        "reservations-in-subnet": true,
        "reservations-out-of-pool": true
      }
    }

``all``:

.. code-block:: json

    {
      "Dhcp6": {
        "reservations-global": false,
        "reservations-in-subnet": true,
        "reservations-out-of-pool": false
      }
    }

To activate both ``global`` and ``all``, the following combination can be used:

.. code-block:: json

    {
      "Dhcp6": {
        "reservations-global": true,
        "reservations-in-subnet": true,
        "reservations-out-of-pool": false
      }
    }

To activate both ``global`` and ``out-of-pool``, the following combination can
be used:

.. code-block:: json

    {
      "Dhcp6": {
        "reservations-global": true,
        "reservations-in-subnet": true,
        "reservations-out-of-pool": true
      }
    }

Note that enabling ``out-of-pool`` and disabling ``in-subnet`` at the same time
is not recommended because ``out-of-pool`` is about host reservations in a
subnet which are fetched only when the ``in-subnet`` flag is true.

The parameter can be specified at global, subnet, and shared-network
levels.

An example configuration that disables reservations looks as follows:

.. code-block:: json

    {
      "Dhcp6": {
        "subnet6": [
          {
            "reservations-global": false,
            "reservations-in-subnet": false,
            "subnet": "2001:db8:1::/64"
          }
        ]
      }
    }

An example configuration using global reservations is shown below:

.. code-block:: json

    {
      "Dhcp6": {
        "reservations": [
          {
            "duid": "00:03:00:01:11:22:33:44:55:66",
            "hostname": "host-one"
          },
          {
            "duid": "00:03:00:01:99:88:77:66:55:44",
            "hostname": "host-two"
          }
        ],
        "reservations-global": true,
        "reservations-in-subnet": false,
        "subnet6": [
          {
            "pools": [
              {
                "pool": "2001:db8:1::-2001:db8:1::100"
              }
            ],
            "subnet": "2001:db8:1::/64"
          }
        ]
      }
    }

For more details regarding global reservations, see :ref:`global-reservations6`.

Another aspect of host reservations is the different types of
identifiers. Kea currently supports two types of identifiers in DHCPv6:
hardware address and DUID. This is beneficial from a usability
perspective; however, there is one drawback. For each incoming packet
Kea has to extract each identifier type and then query the database
to see if there is a reservation by this particular identifier. If
nothing is found, the next identifier is extracted and the next query is
issued. This process continues until either a reservation is found or
all identifier types have been checked. Over time, with an increasing
number of supported identifier types, Kea would become slower and
slower.

To address this problem, a parameter called
``host-reservation-identifiers`` is available. It takes a list of
identifier types as a parameter. Kea will check only those identifier
types enumerated in host-reservation-identifiers. From a performance
perspective, the number of identifier types should be kept to a minimum,
ideally one. If the deployment uses several reservation types, please
enumerate them from most- to least-frequently used, as this increases
the chances of Kea finding the reservation using the fewest queries. An
example of host reservation identifiers looks as follows:

::

   "host-reservation-identifiers": [ "duid", "hw-address" ],
   "subnet6": [
       {
           "subnet": "2001:db8:1::/64",
           ...
       }
   ]

If not specified, the default value is:

::

   "host-reservation-identifiers": [ "hw-address", "duid" ]

.. _global-reservations6:

Global Reservations in DHCPv6
-----------------------------

In some deployments, such as mobile, clients can roam within the network
and certain parameters must be specified regardless of the client's
current location. To facilitate such a need, a global reservation
mechanism has been implemented. The idea behind it is that regular host
reservations are tied to specific subnets, by using a specific
subnet-id. Kea can specify a global reservation that can be used in
every subnet that has global reservations enabled.

This feature can be used to assign certain parameters, such as hostname
or other dedicated, host-specific options. It can also be used to assign
addresses or prefixes. However, global reservations that assign either
of these bypass the whole topology determination provided by DHCP logic
implemented in Kea. It is very easy to misuse this feature and get a
configuration that is inconsistent. To give a specific example, imagine
a global reservation for an address 2001:db8:1111::1 and two subnets
2001:db8:1111::/48 and 2001:db8:ffff::/48. If global reservations are
used in both subnets and a device matching global host reservations
visits part of the network that is covered by 2001:db8:ffff::/48, it
will get an IP address 2001:db8:ffff::1, which will be outside of the
prefix announced by its local router using Router Advertisements. Such a
configuration is unusable or, at the very least, riddled with
issues, such as downlink traffic not reaching the device.

To use global host reservations, a configuration similar to the
following can be used:

::

   "Dhcp6:" {
       # This specifies global reservations.
       # They will apply to all subnets that
       # have global reservations enabled.

       "reservations": [
       {
          "hw-address": "aa:bb:cc:dd:ee:ff",
          "hostname": "hw-host-dynamic"
       },
       {
          "hw-address": "01:02:03:04:05:06",
          "hostname": "hw-host-fixed",

          # Use of IP addresses in global reservations is risky.
          # If used outside of matching subnet, such as 3001::/64,
          # it will result in a broken configuration being handed
          # to the client.
          "ip-address": "2001:db8:ff::77"
       },
       {
          "duid": "01:02:03:04:05",
          "hostname": "duid-host"
       }
       ],
       "valid-lifetime": 600,
       "subnet4": [ {
           "subnet": "2001:db8:1::/64",
           # It is replaced by the "reservations-global"
           # "reservations-in-subnet" and "reservations-out-of-pool"
           # parameters.
           # "reservation-mode": "global",
           # Specify if the server should lookup global reservations.
           "reservations-global": true,
           # Specify if the server should lookup in-subnet reservations.
           "reservations-in-subnet": false,
           # Specify if the server can assume that all reserved addresses
           # are out-of-pool. It can be ignored because "reservations-in-subnet"
           # is false.
           # "reservations-out-of-pool": false,
           "pools": [ { "pool": "2001:db8:1::-2001:db8:1::100" } ]
       } ]
   }

When using database backends, the global host reservations are
distinguished from regular reservations by using subnet-id value of
zero.

.. _pool-selection-with-class-reservations6:

Pool Selection with Client Class Reservations
---------------------------------------------

Client classes can be specified both in the Kea configuration file and/or
host reservations. The classes specified in the Kea configuration file are
evaluated immediately after receiving the DHCP packet and therefore can be
used to influence subnet selection using the ``client-class`` parameter
specified in the subnet scope. The classes specified within the host
reservations are fetched and assigned to the packet after the server has
already selected a subnet for the client. This means that the client
class specified within a host reservation cannot be used to influence
subnet assignment for this client, unless the subnet belongs to a
shared network. If the subnet belongs to a shared network, the server may
dynamically change the subnet assignment while trying to allocate a lease.
If the subnet does not belong to a shared network, once selected, the subnet
is not changed.

If the subnet does not belong to a shared network, it is possible to
use host reservation based client classification to select an address pool
within the subnet as follows:

::

    "Dhcp6": {
        "client-classes": [
            {
                "name": "reserved_class"
            },
            {
                "name": "unreserved_class",
                "test": "not member('reserved_class')"
            }
        ],
        "subnet6": [
            {
                "subnet": "2001:db8:1::/64",
                "reservations": [{"
                    "hw-address": "aa:bb:cc:dd:ee:fe",
                    "client-classes": [ "reserved_class" ]
                 }],
                "pools": [
                    {
                        "pool": "2001:db8:1::10-2001:db8:1::20",
                        "client-class": "reserved_class"
                    },
                    {
                        "pool": "2001:db8:1::30-2001:db8:1::40",
                        "client-class": "unreserved_class"
                    }
                ]
            }
        ]
    }

The ``reserved_class`` is declared without the ``test`` parameter because
it may be only assigned to the client via host reservation mechanism. The
second class, ``unreserved_class``, is assigned to the clients which do not
belong to the ``reserved_class``.  The first pool within the subnet is only
used for the clients having a reservation for the ``reserved_class``. The
second pool is used for the clients not having such reservation. The
configuration snippet includes one host reservation which causes the client
having the MAC address of aa:bb:cc:dd:ee:fe to be assigned to the
``reserved_class``. Thus, this client will be given an IP address from the
first address pool.

.. _subnet-selection-with-class-reservations6:

Subnet Selection with Client Class Reservations
-----------------------------------------------

There is one specific use case when subnet selection may be influenced by
client classes specified within host reservations. This is the case when the
client belongs to a shared network. In such a case it is possible to use
classification to select a subnet within this shared network. Consider the
following example:

::

    "Dhcp6": {
        "client-classes": [
            {
                "name": "reserved_class"
            },
            {
                "name: "unreserved_class",
                "test": "not member('reserved_class')"
            }
        ],
        "reservations": [{"
            "hw-address": "aa:bb:cc:dd:ee:fe",
            "client-classes": [ "reserved_class" ]
        }],
        # It is replaced by the "reservations-global"
        # "reservations-in-subnet" and "reservations-out-of-pool" parameters.
        # Specify if the server should lookup global reservations.
        "reservations-global": true,
        # Specify if the server should lookup in-subnet reservations.
        "reservations-in-subnet": false,
        # Specify if the server can assume that all reserved addresses
        # are out-of-pool. It can be ignored because "reservations-in-subnet"
        # is false, but if specified, it is inherited by "shared-networks"
        # and "subnet6" levels.
        # "reservations-out-of-pool": false,
        "shared-networks": [{
            "subnet6": [
                {
                    "subnet": "2001:db8:1::/64",
                    "pools": [
                        {
                            "pool": "2001:db8:1::10-2001:db8:1::20",
                            "client-class": "reserved_class"
                        }
                    ]
                },
                {
                    "subnet": "2001:db8:2::/64",
                    "pools": [
                        {
                            "pool": "2001:db8:2::10-2001:db8:2::20",
                            "client-class": "unreserved_class"
                        }
                    ]
                }
            ]
        }]
    }

This is similar to the example described in the
:ref:`pool-selection-with-class-reservations6`. This time, however, there
are two subnets, each of them having a pool associated with a different
class. The clients which don't have a reservation for the ``reserved_class``
will be assigned an address from the subnet 2001:db8:2::/64. Clients having
a reservation for the ``reserved_class`` will be assigned an address from
the subnet 2001:db8:1::/64. The subnets must belong to the same shared network.
In addition, the reservation for the client class must be specified at the
global scope (global reservation) and the ``reservations-global`` must be
set to true.

In the example above the ``client-class`` could also be specified at the
subnet level rather than pool level yielding the same effect.

.. _multiple-reservations-same-ip6:

Multiple Reservations for the Same IP
-------------------------------------

Host Reservations were designed to preclude creation of multiple
reservations for the same IP address or delegated prefix within a
particular subnet to avoid the situation when two different clients
compete for the same lease. When using the default settings, the server
returns a configuration error when it finds two or more reservations for
the same lease within a subnet in the Kea configuration file. The
:ref:`host-cmds` hooks library returns an error in response to the
``reservation-add`` command when it detects that the reservation exists
in the database for the lease for which the new reservation is being added.

Similar to DHCPv4 (see :ref:`multiple-reservations-same-ip4`), the DHCPv6
server can also be configured to allow creating multiple reservations
for the same IPv6 address and/or delegated prefix in a given subnet. This
is supported beginning with Kea release 1.9.1 as an optional mode of operation
enabled with the ``ip-reservations-unique`` global parameter.

The ``ip-reservations-unique`` is a boolean parameter, which defaults to
``true``, which forbids the specification of more than one reservation
for the same lease in a given subnet. Setting this parameter to ``false``
allows for creating such reservations both in the Kea configuration
file and in the host database backends via ``host-cmds`` hooks library.

This setting is currently supported by the most popular host database
backends, i.e. MySQL and PostgreSQL. It is not supported for Cassandra,
Host Cache (see :ref:`hooks-host-cache`) or Radius backend
(see :ref:`hooks-radius`). An attempt to set ``ip-reservations-unique``
to ``false`` when any of these three backends is in use yields a
configuration error.

.. note::

   When ``ip-reservations-unique`` is set to ``true`` (the default value)
   the server ensures that IP reservations are unique for a subnet within
   a single host backend and/or Kea configuration file. It does not
   guarantee that the reservations are unique across multiple backends.


The following is the example configuration with two reservations for
the same IPv6 address and for different MAC addresses:

::

   "Dhcp6": {
       "ip-reservations-unique": false,
       "subnet6": [
           {
               "subnet": "2001:db8:1::/64",
               "reservations": [
                   {
                       "hw-address": "1a:1b:1c:1d:1e:1f",
                       "ip-address": "2001:db8:1::11"
                   },
                   {
                       "hw-address": "2a:2b:2c:2d:2e:2f",
                       "ip-address": "2001:db8:1::11"
                   }
               ]
           }
       ]
   }

It is possible to control the ``ip-reservations-unique`` via the
:ref:`dhcp6-cb`. If the new setting of this parameter conflicts with
the currently used backends (backends do not support the new setting),
the new setting is ignored and the warning log message is output.
The backends continue to use the default setting, i.e. expecting that
IP reservations are unique within each subnet. To allow the
creation of non-unique IP reservations, the administrator must remove
the backends which lack support for them from the configuration file.

Administrators must be careful when they have been using multiple
reservations for the same IP address and/or delegated prefix and later
decide to return to the default mode in which this is no longer allowed.
The administrators must make sure that at most one reservation for
the given IP address or delegated prefix exists within a subnet prior
to switching back to the default mode. If such duplicates are left in
the configuration file, the server reports a configuration error.
Leaving such reservations in the host databases does not cause
configuration errors but may lead to lease allocation errors during
the server operation, when it unexpectedly finds multiple reservations
for the same IP address or delegated prefix.

.. note::

   Currently the server does not verify whether multiple reservations for
   the same IP address and/or delegated prefix exist in the host
   databases (MySQL and/or PostgreSQL) when ``ip-reservations-unique``
   is updated from ``true`` to ``false``. This may cause issues with
   lease allocations. The administrator must ensure that there is at
   most one reservation for each IP address and/or delegated prefix
   within each subnet prior to this configuration update.


.. _shared-network6:

Shared Networks in DHCPv6
=========================

DHCP servers use subnet information in two ways. First, it is used to
determine the point of attachment, or where the client is
connected to the network. Second, the subnet information is used to
group information pertaining to a specific location in the network. This
approach works well in general, but there are scenarios where the
boundaries are blurred. Sometimes it is useful to have more than one
logical IP subnet being deployed on the same physical link.
Understanding that two or more subnets are used on the same link requires
additional logic in the DHCP server. This capability is called "shared
networks" in the Kea and ISC DHCP projects. (It is sometimes also
called "shared subnets"; in Microsoft's nomenclature it is called
"multinet.")

There are many use cases where the feature is useful; the most common
example in IPv4 is when the server is running out of available
addresses in a subnet. This is less common in IPv6, but shared networks
are still useful in IPv6. One of the use cases is an exhaustion of IPv6-
delegated prefixes within a subnet; another is an
experiment with an addressing scheme. With the advent of IPv6 deployment
and a vast address space, many organizations split the address space
into subnets, deploy it, and then after a while discover that they want
to split it differently. In the transition period, they want both old
and new addressing to be available; thus the need for more than one
subnet on the same physical link.

Finally, the case of cable networks is directly applicable in IPv6.
There are two types of devices in cable networks: cable modems and the
end-user devices behind them. It is a common practice to use different
subnets for cable modems to prevent users from tinkering with them. In
this case, the distinction is based on the type of device, rather than
on address-space exhaustion.

A client connected to a shared network may be assigned a lease (address
or prefix) from any of the pools defined within the subnets belonging to
the shared network. Internally, the server selects one of the subnets
belonging to a shared network and tries to allocate a lease from this
subnet. If the server is unable to allocate a lease from the selected
subnet (e.g., due to pool exhaustion), it will use another subnet from
the same shared network and will try to allocate a lease from this subnet,
etc. Therefore, the server will typically allocate all leases
available in a given subnet before it starts allocating leases from
other subnets belonging to the same shared network. However, in certain
situations the client can be allocated a lease from the other subnets
before the pools in the first subnet get exhausted; this sometimes occurs
when the client provides a hint that belongs to another subnet, or the client has
reservations in a subnet other than the default.

.. note::

   Deployments should not assume that Kea waits until it has allocated
   all the addresses from the first subnet in a shared network before
   allocating addresses from other subnets.

In order to define a shared network an additional configuration scope is
introduced:

::

   "Dhcp6": {
       "shared-networks": [{
           # Name of the shared network. It may be an arbitrary string
           # and it must be unique among all shared networks.
           "name": "ipv6-lab-1",

           # The subnet selector can be specified on the shared network
           # level. Subnets from this shared network will be selected
           # for clients communicating via relay agent having
           # the specified IP address.
           "relay": {
               "ip-addresses": [ "2001:db8:2:34::1" ]
           },

           # This starts a list of subnets in this shared network.
           # There are two subnets in this example.
           "subnet6": [{
               "subnet": "2001:db8::/48",
               "pools": [{ "pool":  "2001:db8::1 - 2001:db8::ffff" }]
           }, {
               "subnet": "3ffe:ffe::/64",
               "pools": [{ "pool":  "3ffe:ffe::/64" }]
           }]
       }], # end of shared-networks

       # It is likely that in the network there will be a mix of regular,
       # "plain" subnets and shared networks. It is perfectly valid
       # to mix them in the same configuration file.
       #
       # This is a regular subnet. It is not part of any shared-network.
       "subnet6": [{
           "subnet": "2001:db9::/48",
           "pools": [{ "pool":  "2001:db9::/64" }],
           "relay": {
               "ip-addresses": [ "2001:db8:1:2::1" ]
           }
       }]
   } # end of Dhcp6

As demonstrated in the example, it is possible to mix shared and regular
("plain") subnets. Each shared network must have a unique name. This is
similar to the ID for subnets, but gives administrators more
flexibility. It is used for logging, but also internally for
identifying shared networks.

In principle it makes sense to define only shared networks that consist
of two or more subnets. However, for testing purposes, an empty subnet
or a network with just a single subnet is allowed. This
is not a recommended practice in production networks, as the shared
network logic requires additional processing and thus lowers the
server's performance. To avoid unnecessary performance degradation, the
shared subnets should only be defined when required by the deployment.

Shared networks provide an ability to specify many parameters in the
shared network scope that apply to all subnets within it. If
necessary, it is possible to specify a parameter in the shared network scope and
then override its value in the subnet scope. For example:

::

   "shared-networks": [
       {
           "name": "lab-network3",
           "relay": {
                "ip-addresses": [ "2001:db8:2:34::1" ]
           },

           # This applies to all subnets in this shared network, unless
           # values are overridden on subnet scope.
           "valid-lifetime": 600,

           # This option is made available to all subnets in this shared
           # network.
           "option-data": [ {
               "name": "dns-servers",
               "data": "2001:db8::8888"
           } ],

           "subnet6": [
               {
                   "subnet": "2001:db8:1::/48",
                   "pools": [ { "pool":  "2001:db8:1::1 - 2001:db8:1::ffff" } ],

                   # This particular subnet uses different values.
                   "valid-lifetime": 1200,
                   "option-data": [
                   {
                       "name": "dns-servers",
                       "data": "2001:db8::1:2"
                   },
                   {
                       "name": "unicast",
                       "data": "2001:abcd::1"
                   } ]
               },
               {
                    "subnet": "2001:db8:2::/48",
                    "pools": [ { "pool":  "2001:db8:2::1 - 2001:db8:2::ffff" } ],

                    # This subnet does not specify its own valid-lifetime value,
                    # so it is inherited from shared network scope.
                    "option-data": [
                    {
                        "name": "dns-servers",
                        "data": "2001:db8:cafe::1"
                    } ]
               }
           ],
       } ]

In this example, there is a dns-servers option defined that is available
to clients in both subnets in this shared network. Also, the valid
lifetime is set to 10 minutes (600s). However, the first subnet
overrides some of the values (valid lifetime is 20 minutes, different IP
address for dns-servers), but also adds its own option (unicast
address). Assuming a client asking for a server unicast and dns-servers
options is assigned a lease from this subnet, it will get a lease for 20
minutes and dns-servers, and be allowed to use server unicast at address
2001:abcd::1. If the same client is assigned to the second subnet, it
will get a 10-minute lease, a dns-servers value of 2001:db8:cafe::1, and
no server unicast.

Some parameters must be the same in all subnets in the same shared
network. This restriction applies to the ``interface`` and
``rapid-commit`` settings. The most convenient way is to define them on
the shared network scope, but they can be specified for each subnet.
However, care should be taken for each subnet to have the same value.

.. note::

    There is an inherent ambiguity when using clients that send multiple IA
    options in a single request and shared-networks whose subnets have
    different values for options and configuration parameters.  The server
    sequentially processes IA options in the order that they occur in the
    client's query.  If the leases requested in the IA options end up being
    fulfilled from different subnets then which parameters and options should
    apply?  Currently, the code will use the values from the last subnet of
    the last IA option fulfilled.

    We view this largely as a site configuration issue.  A shared-network
    generally means the same physical link, so services configured by options
    from subnet A should be as easily reachable from subnet B and vice versa.
    There are a number of ways to avoid this situation:

    - Use the same values for options and parameters for subnets within the shared-network.
    - Use subnet selectors or client class guards that ensure that for a single client's query, the same subnet will be used for all IA options in that query.
    - Avoid using shared-networks with clients that send multiple IA options per query


Local and Relayed Traffic in Shared Networks
--------------------------------------------

It is possible to specify an interface name at the shared network level
to tell the server that this specific shared network is reachable
directly (not via relays) using the local network interface. As all
subnets in a shared network are expected to be used on the same physical
link, it is a configuration error to attempt to define a shared network
using subnets that are reachable over different interfaces. In other
words, all subnets within the shared network must have the same value
of the "interface" parameter. The following configuration is wrong.

::

   "shared-networks": [
       {
           "name": "office-floor-2",
           "subnet6": [
               {
                   "subnet": "2001:db8::/64",
                   "pools": [ { "pool":  "2001:db8::1 - 2001:db8::ffff" } ],
                   "interface": "eth0"
               },
               {
                    "subnet": "3ffe:abcd::/64",
                    "pools": [ { "pool":  "3ffe:abcd::1 - 3ffe:abcd::ffff" } ],

                    # Specifying the different interface name is a configuration
                    # error. This value should rather be "eth0" or the interface
                    # name in the other subnet should be "eth1".
                    # "interface": "eth1"
               }
           ],
       } ]

To minimize the chance of the configuration errors, it is often more convenient
to simply specify the interface name once, at the shared network level, like
shown in the example below.

::

   "shared-networks": [
       {
           "name": "office-floor-2",

           # This tells Kea that the whole shared network is reachable over a
           # local interface. This applies to all subnets in this network.
           "interface": "eth0",

           "subnet6": [
               {
                   "subnet": "2001:db8::/64",
                   "pools": [ { "pool":  "2001:db8::1 - 2001:db8::ffff" } ],
               },
               {
                    "subnet": "3ffe:abcd::/64",
                    "pools": [ { "pool":  "3ffe:abcd::1 - 3ffe:abcd::ffff" } ]
               }
           ],
       } ]


In case of the relayed traffic, the subnets are typically selected using
the relay agents' addresses. If the subnets are used independently (not
grouped within a shared network) it is allowed to specify different relay
addresses for each of these subnets. When multiple subnets belong to a
shared network they must be selected via the same relay address and,
similarly to the case of the local traffic described above, it is a
configuration error to specify different relay addresses for the respective
subnets in the shared network. The following configuration is wrong.

::

   "shared-networks": [
       {
           "name": "kakapo",
           "subnet6": [
               {
                   "subnet": "2001:db8::/64",
                   "relay": {
                       "ip-addresses": [ "2001:db8::1234" ]
                   },
                   "pools": [ { "pool":  "2001:db8::1 - 2001:db8::ffff" } ]
               },
               {
                   "subnet": "3ffe:abcd::/64",
                   "pools": [ { "pool":  "3ffe:abcd::1 - 3ffe:abcd::ffff" } ],
                   "relay": {
                       # Specifying a different relay address for this
                       # subnet is a configuration error. In this case
                       # it should be 2001:db8::1234 or the relay address
                       # in the previous subnet should be 3ffe:abcd::cafe.
                       "ip-addresses": [ "3ffe:abcd::cafe" ]
                   }
               }
           ]
       }
   ]

Again, it is better to specify the relay address at the shared network
level and this value will be inherited by all subnets belonging to the
shared network.

::

   "shared-networks": [
       {
           "name": "kakapo",
           "relay": {
               # This relay address is inherited by both subnets.
               "ip-addresses": [ "2001:db8::1234" ]
           },
           "subnet6": [
               {
                   "subnet": "2001:db8::/64",
                   "pools": [ { "pool":  "2001:db8::1 - 2001:db8::ffff" } ]
               },
               {
                    "subnet": "3ffe:abcd::/64",
                    "pools": [ { "pool":  "3ffe:abcd::1 - 3ffe:abcd::ffff" } ]
               }
           ]
       }
   ]

Even though it is technically possible to configure two (or more) subnets
within the shared network to use different relay addresses, this will almost
always lead to a different behavior than what the user would expect. In this
case, the Kea server will initially select one of the subnets by matching
the relay address in the client's packet with the subnet's configuration.
However, it MAY end up using the other subnet (even though it does not match
the relay address) if the client already has a lease in this subnet, has a
host reservation in this subnet or simply the initially selected subnet has no
more addresses available. Therefore, it is strongly recommended to always
specify subnet selectors (interface or a relay address) at shared network
level if the subnets belong to a shared network, as it is rarely useful to
specify them at the subnet level and it may lead to the configuration errors
described above.

Client Classification in Shared Networks
----------------------------------------

Sometimes it is desirable to segregate clients into specific subnets
based on certain properties. This mechanism is called client
classification and is described in :ref:`classify`. Client
classification can be applied to subnets belonging to shared networks in
the same way as it is used for subnets specified outside of shared
networks. It is important to understand how the server selects subnets
for clients when client classification is in use, to ensure that the
desired subnet is selected for a given client type.

If a subnet is associated with a class, only the clients belonging to
this class can use this subnet. If there are no classes specified for a
subnet, any client connected to a given shared network can use this
subnet. A common mistake is to assume that the subnet including a client
class is preferred over subnets without client classes. Consider the
following example:

::

   {
       "client-classes": [
           {
               "name": "b-devices",
               "test": "option[1234].hex == 0x0002"
           }
       ],
       "shared-networks": [
           {
               "name": "galah",
               "relay": {
                   "ip-address": [ "2001:db8:2:34::1" ]
               },
               "subnet6": [
                   {
                       "subnet": "2001:db8:1::/64",
                       "pools": [ { "pool": "2001:db8:1::20 - 2001:db8:1::ff" } ],
                   },
                   {
                       "subnet": "2001:db8:3::/64",
                       "pools": [ { "pool": "2001:db8:3::20 - 2001:db8:3::ff" } ],
                       "client-class": "b-devices"
                   }
               ]
           }
       ]
   }

If the client belongs to the "b-devices" class (because it includes
option 1234 with a value of 0x0002), that does not guarantee that the
subnet 2001:db8:3::/64 will be used (or preferred) for this client. The
server can use either of the two subnets, because the subnet
2001:db8:1::/64 is also allowed for this client. The client
classification used in this case should be perceived as a way to
restrict access to certain subnets, rather than a way to express subnet
preference. For example, if the client does not belong to the "b-devices"
class it may only use the subnet 2001:db8:1::/64 and will never use the
subnet 2001:db8:3::/64.

A typical use case for client classification is in a cable network,
where cable modems should use one subnet and other devices should use
another subnet within the same shared network. In this case it is
necessary to apply classification on all subnets. The following example
defines two classes of devices, and the subnet selection is made based
on option 1234 values.

::

   {
       "client-classes": [
           {

               "name": "a-devices",
               "test": "option[1234].hex == 0x0001"
           },
           {
               "name": "b-devices",
               "test": "option[1234].hex == 0x0002"
           }
       ],
       "shared-networks": [
           {
               "name": "galah",
               "relay": {
                   "ip-addresses":  [ "2001:db8:2:34::1" ]
               },
               "subnet6": [
                   {
                       "subnet": "2001:db8:1::/64",
                       "pools": [ { "pool": "2001:db8:1::20 - 2001:db8:1::ff" } ],
                       "client-class": "a-devices"
                   },
                   {
                       "subnet": "2001:db8:3::/64",
                       "pools": [ { "pool": "2001:db8:3::20 - 2001:db8:3::ff" } ],
                       "client-class": "b-devices"
                   }
               ]
           }
       ]
   }

In this example each class has its own restriction. Only clients that
belong to class "a-devices" will be able to use subnet 2001:db8:1::/64
and only clients belonging to "b-devices" will be able to use subnet
2001:db8:3::/64. Care should be taken not to define too-restrictive
classification rules, as clients that are unable to use any subnets will
be refused service. However, this may be a desired outcome if one wishes
to provide service only to clients with known properties (e.g. only VoIP
phones allowed on a given link).

Note that it is possible to achieve an effect similar to the one
presented in this section without the use of shared networks. If the
subnets are placed in the global subnets scope, rather than in the
shared network, the server will still use classification rules to pick
the right subnet for a given class of devices. The major benefit of
placing subnets within the shared network is that common parameters for
the logically grouped subnets can be specified once, in the shared
network scope, e.g. the "interface" or "relay" parameter. All subnets
belonging to this shared network will inherit those parameters.

Host Reservations in Shared Networks
------------------------------------

Subnets that are part of a shared network allow host reservations,
similar to regular subnets:

::

   {
       "shared-networks": [
       {
           "name": "frog",
           "relay": {
               "ip-addresses": [ "2001:db8:2:34::1" ]
           },
           "subnet6": [
               {
                   "subnet": "2001:db8:1::/64",
                   "id": 100,
                   "pools": [ { "2001:db8:1::1 - 2001:db8:1::64" } ],
                   "reservations": [
                   {
                       "duid": "00:03:00:01:11:22:33:44:55:66",
                       "ip-addresses": [ "2001:db8:1::28" ]
                   }
                   ]
               },
               {
                   "subnet": "2001:db8:3::/64",
                   "id": 101,
                   "pools": [ { "pool": "2001:db8:3::1 - 2001:db8:3::64" } ],
                   "reservations": [
                       {
                           "duid": "00:03:00:01:aa:bb:cc:dd:ee:ff",
                           "ip-addresses": [ "2001:db8:2::28" ]
                       }
                   ]
               }
           ]
       }
       ]
   }


It is worth noting that Kea conducts additional checks when processing a
packet if shared networks are defined. First, instead of simply checking
whether there's a reservation for a given client in its initially
selected subnet, Kea looks through all subnets in a shared network for a
reservation. This is one of the reasons why defining a shared network
may impact performance. If there is a reservation for a client in any
subnet, that particular subnet will be picked for the client. Although
it is technically not an error, it is considered a bad practice to define
reservations for the same host in multiple subnets belonging to the same
shared network.

While not strictly mandatory, it is strongly recommended to use explicit
"id" values for subnets if database storage will be used for host
reservations. If an ID is not specified, the values for it are
auto generated, i.e. it assigns increasing integer values starting from
1. Thus, the auto generated IDs are not stable across configuration
changes.

.. _dhcp6-serverid:

Server Identifier in DHCPv6
===========================

The DHCPv6 protocol uses a "server identifier" (also known as a DUID) to
allow clients to discriminate between several servers present on the
same link. `RFC 8415 <https://tools.ietf.org/html/rfc8415>`__ currently
defines four DUID types: DUID-LLT, DUID-EN, DUID-LL, and DUID-UUID.

The Kea DHCPv6 server generates a server identifier once, upon the first
startup, and stores it in a file. This identifier is not modified across
restarts of the server and so is a stable identifier.

Kea follows the recommendation from `RFC
8415 <https://tools.ietf.org/html/rfc8415>`__ to use DUID-LLT as the
default server identifier. However, ISC has received reports that some
deployments require different DUID types, and there is a need to
administratively select both the DUID type and/or its contents.

The server identifier can be configured using parameters within the
``server-id`` map element in the global scope of the Kea configuration
file. The following example demonstrates how to select DUID-EN as a
server identifier:

::

   "Dhcp6": {
       "server-id": {
           "type": "EN"
       },
       ...
   }

Currently supported values for the ``type`` parameter are: "LLT", "EN", and
"LL", for DUID-LLT, DUID-EN, and DUID-LL respectively.

When a new DUID type is selected, the server generates its value and
replaces any existing DUID in the file. The server then uses the new
server identifier in all future interactions with the clients.

.. note::

   If the new server identifier is created after some clients have
   obtained their leases, the clients using the old identifier are not
   able to renew the leases; the server will ignore messages containing
   the old server identifier. Clients will continue sending Renew until
   they transition to the rebinding state. In this state, they will
   start sending Rebind messages to the multicast address without a
   server identifier. The server will respond to the Rebind messages
   with a new server identifier, and the clients will associate the new
   server identifier with their leases. Although the clients will be
   able to keep their leases and will eventually learn the new server
   identifier, this will be at the cost of an increased number of
   renewals and multicast traffic due to a need to rebind. Therefore, it
   is recommended that modification of the server identifier type and
   value be avoided if the server has already assigned leases and these
   leases are still valid.

There are cases when an administrator needs to explicitly specify a DUID
value rather than allow the server to generate it. The following example
demonstrates how to explicitly set all components of a DUID-LLT.

::

   "Dhcp6": {
       "server-id": {
           "type": "LLT",
           "htype": 8,
           "identifier": "A65DC7410F05",
           "time": 2518920166
       },
       ...
   }

where:

-  ``htype`` is a 16-bit unsigned value specifying hardware type,

-  ``identifier`` is a link-layer address, specified as a string of
   hexadecimal digits, and

-  ``time`` is a 32-bit unsigned time value.

The hexadecimal representation of the DUID generated as a result of the
configuration specified above is:

::

    00:01:00:08:96:23:AB:E6:A6:5D:C7:41:0F:05
   |type |htype|   time    |   identifier    |

A special value of 0 for "htype" and "time" is allowed, which indicates
that the server should use ANY value for these components. If the server
already uses a DUID-LLT, it will use the values from this DUID; if the
server uses a DUID of a different type or doesn't yet use any DUID, it
will generate these values. Similarly, if the "identifier" is assigned
an empty string, the value of the identifier will be generated. Omitting
any of these parameters is equivalent to setting them to those special
values.

For example, the following configuration:

::

   "Dhcp6": {
       "server-id": {
           "type": "LLT",
           "htype": 0,
           "identifier": "",
           "time": 2518920166
       },
       ...
   }

indicates that the server should use ANY link-layer address and hardware
type. If the server is already using DUID-LLT, it will use the
link-layer address and hardware type from the existing DUID. If the
server is not yet using any DUID, it will use the link-layer address and
hardware type from one of the available network interfaces. The server
will use an explicit value of time; if it is different than a time value
present in the currently used DUID, that value will be replaced,
effectively modifying the current server identifier.

The following example demonstrates an explicit configuration of a
DUID-EN:

::

   "Dhcp6": {
       "server-id": {
           "type": "EN",
           "enterprise-id": 2495,
           "identifier": "87ABEF7A5BB545"
       },
       ...
   }

where:

-  ``enterprise-id`` is a 32-bit unsigned value holding an enterprise
   number, and

-  ``identifier`` is a variable- length identifier within DUID-EN.

The hexadecimal representation of the DUID-EN created according to the
configuration above is:

::

    00:02:00:00:09:BF:87:AB:EF:7A:5B:B5:45
   |type |  ent-id   |     identifier     |

As in the case of the DUID-LLT, special values can be used for the
configuration of the DUID-EN. If the ``enterprise-id`` is 0, the server
will use a value from the existing DUID-EN. If the server is not using
any DUID or the existing DUID has a different type, the ISC enterprise
id will be used. When an empty string is entered for ``identifier``, the
identifier from the existing DUID-EN will be used. If the server is not
using any DUID-EN, a new 6-byte-long identifier will be generated.

DUID-LL is configured in the same way as DUID-LLT except that the
``time`` parameter has no effect for DUID-LL, because this DUID type
only comprises a hardware type and link-layer address. The following
example demonstrates how to configure DUID-LL:

::

   "Dhcp6": {
       "server-id": {
           "type": "LL",
           "htype": 8,
           "identifier": "A65DC7410F05"
       },
       ...
   }

which will result in the following server identifier:

::

    00:03:00:08:A6:5D:C7:41:0F:05
   |type |htype|   identifier    |

The server stores the generated server identifier in the following
location: [kea-install-dir]/var/lib/kea/kea-dhcp6-serverid.

In some uncommon deployments where no stable storage is available, the
server should be configured not to try to store the server identifier.
This choice is controlled by the value of the ``persist`` boolean
parameter:

::

   "Dhcp6": {
       "server-id": {
           "type": "EN",
           "enterprise-id": 2495,
           "identifier": "87ABEF7A5BB545",
           "persist": false
       },
       ...
   }

The default value of the "persist" parameter is ``true``, which
configures the server to store the server identifier on a disk.

In the example above, the server is configured not to store the
generated server identifier on a disk. But if the server identifier is
not modified in the configuration, the same value will be used after
server restart, because the entire server identifier is explicitly
specified in the configuration.

.. _data-directory:

DHCPv6 Data Directory
=====================

The Kea DHCPv6 server puts the server identifier file and the default
memory lease file into its data directory. By default this directory is
``prefix/var/lib/kea`` but this location can be changed using the
``data-directory`` global parameter as in:

::

   "Dhcp6": {
       "data-directory": "/var/tmp/kea-server6",
       ...
   }

.. _stateless-dhcp6:

Stateless DHCPv6 (Information-Request Message)
==============================================

Typically DHCPv6 is used to assign both addresses and options. These
assignments (leases) have a state that changes over time, hence their
description as stateful. DHCPv6 also supports a stateless mode, where clients
request configuration options only. This mode is considered lightweight
from the server perspective, as it does not require any state tracking,
and carries the stateless name.

The Kea server supports stateless mode. Clients can send
Information-Request messages and the server sends back answers with the
requested options, providing the options are available in the server
configuration. The server attempts to use per-subnet options first; if
that fails for any reason, it then tries to provide options
defined in the global scope.

Stateless and stateful mode can be used together. No special
configuration directives are required to handle this; simply use the
configuration for stateful clients and the stateless clients will get
only the options they requested.

This usage of global options allows for an interesting case. It is
possible to run a server that provides only options and no addresses or
prefixes. If the options have the same value in each subnet, the
configuration can define required options in the global scope and skip
subnet definitions altogether. Here's a simple example of such a
configuration:

::

   "Dhcp6": {
       "interfaces-config": {
           "interfaces": [ "ethX" ]
       },
       "option-data": [ {
           "name": "dns-servers",
           "data": "2001:db8::1, 2001:db8::2"
       } ],
       "lease-database": {
           "type": "memfile"
       }
    }

This very simple configuration provides DNS server information to
all clients in the network, regardless of their location. Note the
specification of the memfile lease database; this is needed as Kea
requires a lease database to be specified even if it is not used.

.. _dhcp6-rfc7550:

Support for RFC 7550 (now part of RFC 8415)
===========================================

`RFC 7550 <https://tools.ietf.org/html/rfc7550>`__ introduced some
changes to the previous DHCPv6 specifications, `RFC
3315 <https://tools.ietf.org/html/rfc3315>`__ and `RFC
3633 <https://tools.ietf.org/html/rfc3633>`__, to resolve a few issues
with the coexistence of multiple stateful options in the messages sent
between clients and servers. Those changes were later included in
the most recent DHCPv6 protocol specification, `RFC
8415 <https://tools.ietf.org/html/rfc8415>`__, which obsoleted `RFC
7550 <https://tools.ietf.org/html/rfc7550>`__. Kea supports `RFC
8415 <https://tools.ietf.org/html/rfc8415>`__ along with these protocol
changes, which are briefly described below.

When a client, such as a requesting router, requests an allocation of
both addresses and prefixes during the 4-way (SARR) exchange with the
server, and the server is not configured to allocate any prefixes but it
can allocate some addresses, it will respond with the IA_NA(s)
containing allocated addresses and the IA_PD(s) containing the
NoPrefixAvail status code. According to the updated specifications, if
the client can operate without prefixes it should accept allocated
addresses and transition to the "bound" state. When the client
subsequently sends Renew/Rebind messages to the server, according to the
T1 and T2 times, to extend the lifetimes of the allocated addresses, and
if the client is still interested in obtaining prefixes from the server,
it may also include an IA_PD in the Renew/Rebind to request allocation
of the prefixes. If the server still cannot allocate the prefixes, it
will respond with the IA_PD(s) containing the NoPrefixAvail status code.
However, if the server can allocate the prefixes it will allocate and
send them in the IA_PD(s) to the client. A similar situation occurs when
the server is unable to allocate addresses for the client but can
delegate prefixes. The client may request allocation of the addresses
while renewing the delegated prefixes. Allocating leases for other IA
types while renewing existing leases is by default supported by the Kea
DHCPv6 server, and the server provides no configuration mechanisms to
disable this behavior.

The following are the other behaviors first introduced in `RFC
7550 <https://tools.ietf.org/html/rfc7550>`__ (now part of `RFC
8415 <https://tools.ietf.org/html/rfc8415>`__) and supported by the Kea
DHCPv6 server:

-  Set T1/T2 timers to the same value for all stateful (IA_NA and IA_PD)
   options to facilitate renewal of all of a client's leases at the same
   time (in a single message exchange).

-  Place NoAddrsAvail and NoPrefixAvail status codes in the IA_NA and
   IA_PD options in the Advertise message, rather than as the top-level
   options.

.. _dhcp6-relay-override:

Using a Specific Relay Agent for a Subnet
=========================================

The DHCPv6 server follows the same principles as the DHCPv4 server to
select a subnet for the client, with noticeable differences mainly for
relays.

.. note::

   Starting with Kea 1.7.9, the order used to find a subnet which matches
   required conditions to be selected is the ascending subnet identifier
   order. When the selected subnet is a member of a shared network the
   whole shared network is selected.

The relay must have an interface connected to the link on which the
clients are being configured. Typically the relay has a global IPv6
address configured on that interface, which belongs to the subnet from
which the server will assign addresses. Normally, the server is able to
use the IPv6 address inserted by the relay (in the link-addr field in
RELAY-FORW message) to select the appropriate subnet.

However, that is not always the case. The relay address may not match
the subnet in certain deployments. This usually means that there is more
than one subnet allocated for a given link. The two most common examples
where this is the case are long-lasting network renumbering (where both the
old and new address spaces are still being used) and a cable network. In a
cable network, both cable modems and the devices behind them are
physically connected to the same link, yet they use distinct addressing.
In such a case, the DHCPv6 server needs additional information (like the
value of the interface-id option or the IPv6 address inserted in the
link-addr field in the RELAY-FORW message) to properly select an
appropriate subnet.

The following example assumes that there is a subnet 2001:db8:1::/64
that is accessible via a relay that uses 3000::1 as its IPv6 address.
The server is able to select this subnet for any incoming packets that
come from a relay that has an address in the 2001:db8:1::/64 subnet. It also
selects that subnet for a relay with address 3000::1.

::

   "Dhcp6": {
       "subnet6": [
           {
               "subnet": "2001:db8:1::/64",
               "pools": [
                    {
                        "pool": "2001:db8:1::1-2001:db8:1::ffff"
                    }
               ],
               "relay": {
                   "ip-addresses": [ "3000::1" ]
               }
           }
       ]
   }

If "relay" is specified, the "ip-addresses" parameter within it is
mandatory.

.. note::

   The current version of Kea uses the "ip-addresses" parameter, which
   supports specifying a list of addresses.

.. _dhcp6-client-class-relay:

Segregating IPv6 Clients in a Cable Network
===========================================

In certain cases, it is useful to mix relay address information
(introduced in :ref:`dhcp6-relay-override`), with client classification, explained
in :ref:`classify`. One specific example is in a cable network,
where modems typically get addresses from a different subnet than all
the devices connected behind them.

Let us assume that there is one CMTS (Cable Modem Termination System)
with one CM MAC (a physical link that modems are connected to). We want
the modems to get addresses from the 3000::/64 subnet, while everything
connected behind the modems should get addresses from another subnet
(2001:db8:1::/64). The CMTS that acts as a relay uses address 3000::1.
The following configuration can serve that configuration:

::

   "Dhcp6": {
       "subnet6": [
           {
               "subnet": "3000::/64",
               "pools": [
                   { "pool": "3000::2 - 3000::ffff" }
               ],
               "client-class": "VENDOR_CLASS_docsis3.0",
               "relay": {
                   "ip-addresses": [ "3000::1" ]
               }
           },
           {
               "subnet": "2001:db8:1::/64",
               "pools": [
                    {
                        "pool": "2001:db8:1::1-2001:db8:1::ffff"
                    }
               ],
               "relay": {
                   "ip-addresses": [ "3000::1" ]
               }
           }
       ]
   }

.. _mac-in-dhcpv6:

MAC/Hardware Addresses in DHCPv6
================================

MAC/hardware addresses are available in DHCPv4 messages from the
clients, and administrators frequently use that information to perform
certain tasks like per-host configuration and address reservation for
specific MAC addresses. Unfortunately, the DHCPv6 protocol does not
provide any completely reliable way to retrieve that information. To
mitigate that issue, a number of mechanisms have been implemented in
Kea. Each of these mechanisms works in certain cases, but may fail in
others. Whether the mechanism works in a particular deployment is
somewhat dependent on the network topology and the technologies used.

Kea allows specification of which of the supported methods should be
used and in what order. This configuration may be considered a fine
tuning of the DHCP deployment. In a typical deployment the default value
of ``"any"`` is sufficient and there is no need to select specific
methods. Changing the value of this parameter is most useful in
cases when an administrator wants to disable certain methods; for
example, if the administrator trusts the network infrastructure more
than the information provided by the clients themselves, they may prefer
information provided by the relays over that provided by clients.

The configuration is controlled by the ``mac-sources`` parameter as
follows:

::

   "Dhcp6": {
       "mac-sources": [ "method1", "method2", "method3", ... ],

       "subnet6": [ ... ],

       ...
   }

When not specified, a special value of "any" is used, which instructs
the server to attempt to try all the methods in sequence and use the
value returned by the first one that succeeds. If specified, it must
have at least one value.

Supported methods are:

-  ``any`` - not an actual method, just a keyword that instructs Kea to
   try all other methods and use the first one that succeeds. This is
   the default operation if no ``mac-sources`` are defined.

-  ``raw`` - in principle, a DHCPv6 server could use raw sockets to
   receive incoming traffic and extract MAC/hardware address
   information. This is currently not implemented for DHCPv6 and this
   value has no effect.

-  ``duid`` - DHCPv6 uses DUID identifiers instead of MAC addresses.
   There are currently four DUID types defined, and two of them
   (DUID-LLT, which is the default, and DUID-LL) convey MAC address
   information. Although `RFC 8415 <https://tools.ietf.org/html/rfc8415>`__
   forbids it, it is possible to
   parse those DUIDs and extract necessary information from them. This
   method is not completely reliable, as clients may use other DUID
   types, namely DUID-EN or DUID-UUID.

-  ``ipv6-link-local`` - another possible acquisition method comes from
   the source IPv6 address. In typical usage, clients are sending their
   packets from IPv6 link-local addresses. There is a good chance that
   those addresses are based on EUI-64, which contains a MAC address.
   This method is not completely reliable, as clients may use other
   link-local address types. In particular, privacy extensions, defined
   in `RFC 4941 <https://tools.ietf.org/html/rfc4941>`__, do not use MAC
   addresses. Also note that successful extraction requires that the
   address's u-bit must be set to 1 and its g-bit set to 0, indicating
   that it is an interface identifier as per `RFC 2373, section
   2.5.1 <https://tools.ietf.org/html/rfc2373#section-2.5.1>`__.

-  ``client-link-addr-option`` - one extension defined to alleviate
   missing MAC issues is the client link-layer address option, defined
   in `RFC 6939 <https://tools.ietf.org/html/rfc6939>`__. This is an
   option that is inserted by a relay and contains information about a
   client's MAC address. This method requires a relay agent that
   supports the option and is configured to insert it. This method is
   useless for directly connected clients. This parameter can also be
   specified as ``rfc6939``, which is an alias for
   ``client-link-addr-option``.

-  ``remote-id`` - `RFC 4649 <https://tools.ietf.org/html/rfc4649>`__
   defines a remote-id option that is inserted by a relay agent.
   Depending on the relay agent configuration, the inserted option may
   convey the client's MAC address information. This parameter can also
   be specified as ``rfc4649``, which is an alias for ``remote-id``.

-  ``subscriber-id`` - Another option that is somewhat similar to the
   previous one is subscriber-id, defined in `RFC
   4580 <https://tools.ietf.org/html/rfc4580>`__. It, too, is inserted by
   a relay agent that is configured to insert it. This parameter can
   also be specified as ``rfc4580``, which is an alias for
   ``subscriber-id``. This method is currently not implemented.

-  ``docsis-cmts`` - Yet another possible source of MAC address
   information are the DOCSIS options inserted by a CMTS that acts as a
   DHCPv6 relay agent in cable networks. This method attempts to extract
   MAC address information from sub-option 1026 (cm mac) of the
   vendor-specific option with vendor-id=4491. This vendor option is
   extracted from the relay-forward message, not the original client's
   message.

-  ``docsis-modem`` - The final possible source of MAC address
   information are the DOCSIS options inserted by the cable modem
   itself. This method attempts to extract MAC address information from
   sub-option 36 (device id) of the vendor-specific option with
   vendor-id=4491. This vendor option is extracted from the original
   client's message, not from any relay options.

Empty mac-sources are not allowed. Administrators who do not want to specify it
should either simply omit the mac-sources definition or specify it with the
"any" value, which is the default.

.. _dhcp6-decline:

Duplicate Addresses (DECLINE Support)
=====================================

The DHCPv6 server is configured with a certain pool of addresses that it
is expected to hand out to DHCPv6 clients. It is assumed that the server
is authoritative and has complete jurisdiction over those addresses.
However, for various reasons, such as misconfiguration or a faulty
client implementation that retains its address beyond the valid
lifetime, there may be devices connected that use those addresses
without the server's approval or knowledge.

Such an unwelcome event can be detected by legitimate clients (using
Duplicate Address Detection) and reported to the DHCPv6 server using a
DHCPDECLINE message. The server will do a sanity check (to see whether
the client declining an address really was supposed to use it), and then
will conduct a clean-up operation and confirm it by sending back a REPLY
message. Any DNS entries related to that address will be removed, the
fact will be logged, and hooks will be triggered. After that is
complete, the address will be marked as declined (which indicates that
it is used by an unknown entity and thus not available for assignment)
and a probation time will be set on it. Unless otherwise configured, the
probation period lasts 24 hours; after that period, the server will
recover the lease (i.e. put it back into the available state) and the
address will be available for assignment again. It should be noted that
if the underlying issue of a misconfigured device is not resolved, the
duplicate-address scenario will repeat. If reconfigured correctly, this
mechanism provides an opportunity to recover from such an event
automatically, without any system administrator intervention.

To configure the decline probation period to a value other than the
default, the following syntax can be used:

::

     "Dhcp6": {
       "decline-probation-period": 3600,
       "subnet6": [ ... ],
       ...
   }

The parameter is expressed in seconds, so the example above will
instruct the server to recycle declined leases after one hour.

There are several statistics and hook points associated with the decline
handling procedure. The lease6_decline hook is triggered after the
incoming DHCPDECLINE message has been sanitized and the server is about
to decline the lease. The declined-addresses statistic is increased
after the hook returns (both global and subnet-specific variants). (See
:ref:`dhcp6-stats` and :ref:`hooks-libraries`
for more details on DHCPv6 statistics and Kea hook points.)

Once the probation time elapses, the declined lease is recovered using
the standard expired-lease reclamation procedure, with several
additional steps. In particular, both declined-addresses statistics
(global and subnet-specific) are decreased. At the same time,
reclaimed-declined-addresses statistics (again in two variants, global
and subnet-specific) are increased.

A note about statistics: The server does not decrease the
assigned-nas statistics when a DHCPDECLINE message is received and
processed successfully. While technically a declined address is no
longer assigned, the primary usage of the assigned-nas statistic
is to monitor pool utilization. Most people would forget to include
declined-addresses in the calculation, and simply use
assigned-nas/total-nas. This would cause a bias towards
under-representing pool utilization. As this has a potential for major
issues, ISC decided not to decrease assigned-nas immediately after
receiving DHCPDECLINE, but to do it later when Kea recovers the address
back to the available pool.

.. _dhcp6-stats:

Statistics in the DHCPv6 Server
===============================

The DHCPv6 server supports the following statistics:

.. tabularcolumns:: |p{0.2\linewidth}|p{0.1\linewidth}|p{0.7\linewidth}|

.. table:: DHCPv6 Statistics
   :class: longtable
   :widths: 20 10 70


   +-----------------------------------------+-----------------------+------------------------+
   | Statistic                               | Data Type             | Description            |
   +=========================================+=======================+========================+
   | pkt6-received                           | integer               | Number of DHCPv6       |
   |                                         |                       | packets received.      |
   |                                         |                       | This includes all      |
   |                                         |                       | packets: valid,        |
   |                                         |                       | bogus, corrupted,      |
   |                                         |                       | rejected, etc. This    |
   |                                         |                       | statistic is expected  |
   |                                         |                       | to grow rapidly.       |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-receive-drop                       | integer               | Number of incoming     |
   |                                         |                       | packets that were      |
   |                                         |                       | dropped. The exact     |
   |                                         |                       | reason for dropping    |
   |                                         |                       | packets is logged,     |
   |                                         |                       | but the most common    |
   |                                         |                       | reasons may be: an     |
   |                                         |                       | unacceptable or not    |
   |                                         |                       | supported packet type  |
   |                                         |                       | is received, direct    |
   |                                         |                       | responses are          |
   |                                         |                       | forbidden, the         |
   |                                         |                       | server-id sent by the  |
   |                                         |                       | client does not match  |
   |                                         |                       | the server's           |
   |                                         |                       | server-id, or the      |
   |                                         |                       | packet is malformed.   |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-parse-failed                       | integer               | Number of incoming     |
   |                                         |                       | packets that could     |
   |                                         |                       | not be parsed. A       |
   |                                         |                       | non-zero value of      |
   |                                         |                       | this statistic         |
   |                                         |                       | indicates that the     |
   |                                         |                       | server received a      |
   |                                         |                       | malformed or           |
   |                                         |                       | truncated packet.      |
   |                                         |                       | This may indicate      |
   |                                         |                       | problems in the        |
   |                                         |                       | network, faulty        |
   |                                         |                       | clients, faulty relay  |
   |                                         |                       | agents, or a bug in    |
   |                                         |                       | the server.            |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-solicit-received                   | integer               | Number of SOLICIT      |
   |                                         |                       | packets received.      |
   |                                         |                       | This statistic is      |
   |                                         |                       | expected to grow; its  |
   |                                         |                       | increase means that    |
   |                                         |                       | clients that just      |
   |                                         |                       | booted started their   |
   |                                         |                       | configuration process  |
   |                                         |                       | and their initial      |
   |                                         |                       | packets reached the    |
   |                                         |                       | Kea server.            |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-advertise-received                 | integer               | Number of ADVERTISE    |
   |                                         |                       | packets received.      |
   |                                         |                       | Advertise packets are  |
   |                                         |                       | sent by the server     |
   |                                         |                       | and the server is      |
   |                                         |                       | never expected to      |
   |                                         |                       | receive them. A        |
   |                                         |                       | non-zero value of      |
   |                                         |                       | this statistic         |
   |                                         |                       | indicates an error     |
   |                                         |                       | occurring in the       |
   |                                         |                       | network. One likely    |
   |                                         |                       | cause would be a       |
   |                                         |                       | misbehaving relay      |
   |                                         |                       | agent that             |
   |                                         |                       | incorrectly forwards   |
   |                                         |                       | ADVERTISE messages     |
   |                                         |                       | towards the server,    |
   |                                         |                       | rather than back to    |
   |                                         |                       | the clients.           |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-request-received                   | integer               | Number of DHCPREQUEST  |
   |                                         |                       | packets received.      |
   |                                         |                       | This statistic is      |
   |                                         |                       | expected to grow. Its  |
   |                                         |                       | increase means that    |
   |                                         |                       | clients that just      |
   |                                         |                       | booted received the    |
   |                                         |                       | server's response      |
   |                                         |                       | (DHCPADVERTISE) and    |
   |                                         |                       | accepted it, and are   |
   |                                         |                       | now requesting an      |
   |                                         |                       | address                |
   |                                         |                       | (DHCPREQUEST).         |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-reply-received                     | integer               | Number of REPLY        |
   |                                         |                       | packets received.      |
   |                                         |                       | This statistic is      |
   |                                         |                       | expected to remain     |
   |                                         |                       | zero at all times, as  |
   |                                         |                       | REPLY packets are      |
   |                                         |                       | sent by the server     |
   |                                         |                       | and the server is      |
   |                                         |                       | never expected to      |
   |                                         |                       | receive them. A        |
   |                                         |                       | non-zero value         |
   |                                         |                       | indicates an error.    |
   |                                         |                       | One likely cause       |
   |                                         |                       | would be a             |
   |                                         |                       | misbehaving relay      |
   |                                         |                       | agent that             |
   |                                         |                       | incorrectly forwards   |
   |                                         |                       | REPLY messages         |
   |                                         |                       | towards the server,    |
   |                                         |                       | rather than back to    |
   |                                         |                       | the clients.           |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-renew-received                     | integer               | Number of RENEW        |
   |                                         |                       | packets received.      |
   |                                         |                       | This statistic is      |
   |                                         |                       | expected to grow; its  |
   |                                         |                       | increase means that    |
   |                                         |                       | clients received       |
   |                                         |                       | their addresses and    |
   |                                         |                       | prefixes and are       |
   |                                         |                       | trying to renew them.  |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-rebind-received                    | integer               | Number of REBIND       |
   |                                         |                       | packets received. A    |
   |                                         |                       | non-zero value         |
   |                                         |                       | indicates that         |
   |                                         |                       | clients did not        |
   |                                         |                       | receive responses to   |
   |                                         |                       | their RENEW messages   |
   |                                         |                       | (through the regular   |
   |                                         |                       | lease-renewal          |
   |                                         |                       | mechanism) and are     |
   |                                         |                       | attempting to find     |
   |                                         |                       | any server that is     |
   |                                         |                       | able to take over      |
   |                                         |                       | their leases. It may   |
   |                                         |                       | mean that some         |
   |                                         |                       | servers' REPLY         |
   |                                         |                       | messages never         |
   |                                         |                       | reached the clients.   |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-release-received                   | integer               | Number of RELEASE      |
   |                                         |                       | packets received.      |
   |                                         |                       | This statistic is      |
   |                                         |                       | expected to grow when  |
   |                                         |                       | a device is being      |
   |                                         |                       | shut down in the       |
   |                                         |                       | network; it indicates  |
   |                                         |                       | that the address or    |
   |                                         |                       | prefix assigned is     |
   |                                         |                       | reported as no longer  |
   |                                         |                       | needed. Note that      |
   |                                         |                       | many devices,          |
   |                                         |                       | especially wireless,   |
   |                                         |                       | do not send RELEASE    |
   |                                         |                       | packets either         |
   |                                         |                       | because of design      |
   |                                         |                       | choice or due to the   |
   |                                         |                       | client moving out of   |
   |                                         |                       | range.                 |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-decline-received                   | integer               | Number of DECLINE      |
   |                                         |                       | packets received.      |
   |                                         |                       | This statistic is      |
   |                                         |                       | expected to remain     |
   |                                         |                       | close to zero. Its     |
   |                                         |                       | increase means that a  |
   |                                         |                       | client leased an       |
   |                                         |                       | address, but           |
   |                                         |                       | discovered that the    |
   |                                         |                       | address is currently   |
   |                                         |                       | used by an unknown     |
   |                                         |                       | device in the          |
   |                                         |                       | network. If this       |
   |                                         |                       | statistic is growing,  |
   |                                         |                       | it may indicate a      |
   |                                         |                       | misconfigured server   |
   |                                         |                       | or devices that have   |
   |                                         |                       | statically assigned    |
   |                                         |                       | conflicting            |
   |                                         |                       | addresses.             |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-infrequest-received                | integer               | Number of              |
   |                                         |                       | INFORMATION-REQUEST    |
   |                                         |                       | packets received.      |
   |                                         |                       | This statistic is      |
   |                                         |                       | expected to grow if    |
   |                                         |                       | there are devices      |
   |                                         |                       | that are using         |
   |                                         |                       | stateless DHCPv6.      |
   |                                         |                       | INFORMATION-REQUEST    |
   |                                         |                       | messages are used by   |
   |                                         |                       | clients that request   |
   |                                         |                       | stateless              |
   |                                         |                       | configuration, i.e.    |
   |                                         |                       | options and            |
   |                                         |                       | parameters other than  |
   |                                         |                       | addresses or           |
   |                                         |                       | prefixes.              |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-dhcpv4-query-received              | integer               | Number of              |
   |                                         |                       | DHCPv4-QUERY packets   |
   |                                         |                       | received. This         |
   |                                         |                       | statistic is expected  |
   |                                         |                       | to grow if there are   |
   |                                         |                       | devices that are       |
   |                                         |                       | using                  |
   |                                         |                       | DHCPv4-over-DHCPv6.    |
   |                                         |                       | DHCPv4-QUERY messages  |
   |                                         |                       | are used by DHCPv4     |
   |                                         |                       | clients on an          |
   |                                         |                       | IPv6-only line which   |
   |                                         |                       | encapsulates the       |
   |                                         |                       | requests over DHCPv6.  |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-dhcpv4-response-received           | integer               | Number of              |
   |                                         |                       | DHCPv4-RESPONSE        |
   |                                         |                       | packets received.      |
   |                                         |                       | This statistic is      |
   |                                         |                       | expected to remain     |
   |                                         |                       | zero at all times, as  |
   |                                         |                       | DHCPv4-RESPONSE        |
   |                                         |                       | packets are sent by    |
   |                                         |                       | the server and the     |
   |                                         |                       | server is never        |
   |                                         |                       | expected to receive    |
   |                                         |                       | them. A non-zero       |
   |                                         |                       | value indicates an     |
   |                                         |                       | error. One likely      |
   |                                         |                       | cause would be a       |
   |                                         |                       | misbehaving relay      |
   |                                         |                       | agent that             |
   |                                         |                       | incorrectly forwards   |
   |                                         |                       | DHCPv4-RESPONSE        |
   |                                         |                       | message towards the    |
   |                                         |                       | server rather than     |
   |                                         |                       | back to the clients.   |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-unknown-received                   | integer               | Number of packets      |
   |                                         |                       | received of an         |
   |                                         |                       | unknown type. A        |
   |                                         |                       | non-zero value of      |
   |                                         |                       | this statistic         |
   |                                         |                       | indicates that the     |
   |                                         |                       | server received a      |
   |                                         |                       | packet that it wasn't  |
   |                                         |                       | able to recognize;     |
   |                                         |                       | either it had an       |
   |                                         |                       | unsupported type or    |
   |                                         |                       | was possibly           |
   |                                         |                       | malformed.             |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-sent                               | integer               | Number of DHCPv6       |
   |                                         |                       | packets sent. This     |
   |                                         |                       | statistic is expected  |
   |                                         |                       | to grow every time     |
   |                                         |                       | the server transmits   |
   |                                         |                       | a packet. In general,  |
   |                                         |                       | it should roughly      |
   |                                         |                       | match pkt6-received,   |
   |                                         |                       | as most incoming       |
   |                                         |                       | packets cause the      |
   |                                         |                       | server to respond.     |
   |                                         |                       | There are exceptions   |
   |                                         |                       | (e.g. server           |
   |                                         |                       | receiving a REQUEST    |
   |                                         |                       | with server-id         |
   |                                         |                       | matching another       |
   |                                         |                       | server), so do not     |
   |                                         |                       | worry if it is less    |
   |                                         |                       | than pkt6-received.    |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-advertise-sent                     | integer               | Number of ADVERTISE    |
   |                                         |                       | packets sent. This     |
   |                                         |                       | statistic is expected  |
   |                                         |                       | to grow in most cases  |
   |                                         |                       | after a SOLICIT is     |
   |                                         |                       | processed. There are   |
   |                                         |                       | certain uncommon, but  |
   |                                         |                       | valid, cases where     |
   |                                         |                       | incoming SOLICIT       |
   |                                         |                       | packets are dropped,   |
   |                                         |                       | but in general this    |
   |                                         |                       | statistic is expected  |
   |                                         |                       | to be close to         |
   |                                         |                       | pkt6-solicit-received. |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-reply-sent                         | integer               | Number of REPLY        |
   |                                         |                       | packets sent. This     |
   |                                         |                       | statistic is expected  |
   |                                         |                       | to grow in most cases  |
   |                                         |                       | after a SOLICIT (with  |
   |                                         |                       | rapid-commit),         |
   |                                         |                       | REQUEST, RENEW,        |
   |                                         |                       | REBIND, RELEASE,       |
   |                                         |                       | DECLINE, or            |
   |                                         |                       | INFORMATION-REQUEST    |
   |                                         |                       | is processed. There    |
   |                                         |                       | are certain cases      |
   |                                         |                       | where there is no      |
   |                                         |                       | response.              |
   +-----------------------------------------+-----------------------+------------------------+
   | pkt6-dhcpv4-response-sent               | integer               | Number of              |
   |                                         |                       | DHCPv4-RESPONSE        |
   |                                         |                       | packets sent. This     |
   |                                         |                       | statistic is expected  |
   |                                         |                       | to grow in most cases  |
   |                                         |                       | after a DHCPv4-QUERY   |
   |                                         |                       | is processed. There    |
   |                                         |                       | are certain cases      |
   |                                         |                       | where there is no      |
   |                                         |                       | response.              |
   +-----------------------------------------+-----------------------+------------------------+
   | subnet[id].total-nas                    | integer               | Total number of NA     |
   |                                         |                       | addresses available    |
   |                                         |                       | for DHCPv6 management  |
   |                                         |                       | for a given subnet;    |
   |                                         |                       | in other words, this   |
   |                                         |                       | is the sum of all      |
   |                                         |                       | addresses in all       |
   |                                         |                       | configured pools.      |
   |                                         |                       | This statistic         |
   |                                         |                       | changes only during    |
   |                                         |                       | configuration          |
   |                                         |                       | changes. Note that it  |
   |                                         |                       | does not take into     |
   |                                         |                       | account any addresses  |
   |                                         |                       | that may be reserved   |
   |                                         |                       | due to host            |
   |                                         |                       | reservation. The *id*  |
   |                                         |                       | is the subnet-id of a  |
   |                                         |                       | given subnet. This     |
   |                                         |                       | statistic is exposed   |
   |                                         |                       | for each subnet        |
   |                                         |                       | separately, and is     |
   |                                         |                       | reset during a         |
   |                                         |                       | reconfiguration        |
   |                                         |                       | event.                 |
   +-----------------------------------------+-----------------------+------------------------+
   | cumulative-assigned-nas                 | integer               | Cumulative number of   |
   |                                         |                       | NA addresses that      |
   |                                         |                       | have been assigned     |
   |                                         |                       | since server startup.  |
   |                                         |                       | It is incremented      |
   |                                         |                       | each time a NA address |
   |                                         |                       | is assigned and is not |
   |                                         |                       | reset when the server  |
   |                                         |                       | is reconfigured.       |
   +-----------------------------------------+-----------------------+------------------------+
   | subnet[id].cumulative-assigned-nas      | integer               | Cumulative number of   |
   |                                         |                       | NA addresses in a      |
   |                                         |                       | given subnet that      |
   |                                         |                       | were assigned. It      |
   |                                         |                       | increases every time   |
   |                                         |                       | a new lease is         |
   |                                         |                       | allocated (as a        |
   |                                         |                       | result of receiving a  |
   |                                         |                       | REQUEST message) and   |
   |                                         |                       | is never decreased.    |
   |                                         |                       | The *id* is the        |
   |                                         |                       | subnet-id of a given   |
   |                                         |                       | subnet. This           |
   |                                         |                       | statistic is exposed   |
   |                                         |                       | for each subnet        |
   |                                         |                       | separately, and is     |
   |                                         |                       | reset during a         |
   |                                         |                       | reconfiguration        |
   |                                         |                       | event.                 |
   +-----------------------------------------+-----------------------+------------------------+
   | subnet[id].assigned-nas                 | integer               | Number of NA           |
   |                                         |                       | addresses in a given   |
   |                                         |                       | subnet that are        |
   |                                         |                       | assigned. It           |
   |                                         |                       | increases every time   |
   |                                         |                       | a new lease is         |
   |                                         |                       | allocated (as a        |
   |                                         |                       | result of receiving a  |
   |                                         |                       | REQUEST message) and   |
   |                                         |                       | is decreased every     |
   |                                         |                       | time a lease is        |
   |                                         |                       | released (a RELEASE    |
   |                                         |                       | message is received)   |
   |                                         |                       | or expires. The *id*   |
   |                                         |                       | is the subnet-id of a  |
   |                                         |                       | given subnet. This     |
   |                                         |                       | statistic is exposed   |
   |                                         |                       | for each subnet        |
   |                                         |                       | separately, and is     |
   |                                         |                       | reset during a         |
   |                                         |                       | reconfiguration        |
   |                                         |                       | event.                 |
   +-----------------------------------------+-----------------------+------------------------+
   | subnet[id].total-pds                    | integer               | Total number of PD     |
   |                                         |                       | prefixes available     |
   |                                         |                       | for DHCPv6 management  |
   |                                         |                       | for a given subnet;    |
   |                                         |                       | in other words, this   |
   |                                         |                       | is the sum of all      |
   |                                         |                       | prefixes in all        |
   |                                         |                       | configured pools.      |
   |                                         |                       | This statistic         |
   |                                         |                       | changes only during    |
   |                                         |                       | configuration          |
   |                                         |                       | changes. Note it does  |
   |                                         |                       | not take into account  |
   |                                         |                       | any prefixes that may  |
   |                                         |                       | be reserved due to     |
   |                                         |                       | host reservation. The  |
   |                                         |                       | *id* is the subnet-id  |
   |                                         |                       | of a given subnet.     |
   |                                         |                       | This statistic is      |
   |                                         |                       | exposed for each       |
   |                                         |                       | subnet separately,     |
   |                                         |                       | and is reset during a  |
   |                                         |                       | reconfiguration        |
   |                                         |                       | event.                 |
   +-----------------------------------------+-----------------------+------------------------+
   | cumulative-assigned-pds                 | integer               | Cumulative number of   |
   |                                         |                       | PD prefixes that       |
   |                                         |                       | have been assigned     |
   |                                         |                       | since server startup.  |
   |                                         |                       | It is incremented      |
   |                                         |                       | each time a PD prefix  |
   |                                         |                       | is assigned and is not |
   |                                         |                       | reset when the server  |
   |                                         |                       | is reconfigured.       |
   +-----------------------------------------+-----------------------+------------------------+
   | subnet[id].cumulative-assigned-pds      | integer               | Cumulative number of   |
   |                                         |                       | PD prefixes in a       |
   |                                         |                       | given subnet that      |
   |                                         |                       | were assigned. It      |
   |                                         |                       | increases every time   |
   |                                         |                       | a new lease is         |
   |                                         |                       | allocated (as a        |
   |                                         |                       | result of receiving a  |
   |                                         |                       | REQUEST message) and   |
   |                                         |                       | is never decreased.    |
   |                                         |                       | The *id* is the        |
   |                                         |                       | subnet-id of a given   |
   |                                         |                       | subnet. This           |
   |                                         |                       | statistic is exposed   |
   |                                         |                       | for each subnet        |
   |                                         |                       | separately, and is     |
   |                                         |                       | reset during a         |
   |                                         |                       | reconfiguration        |
   |                                         |                       | event.                 |
   +-----------------------------------------+-----------------------+------------------------+
   | subnet[id].assigned-pds                 | integer               | Number of PD prefixes  |
   |                                         |                       | in a given subnet      |
   |                                         |                       | that are assigned. It  |
   |                                         |                       | increases every time   |
   |                                         |                       | a new lease is         |
   |                                         |                       | allocated (as a        |
   |                                         |                       | result of receiving a  |
   |                                         |                       | REQUEST message) and   |
   |                                         |                       | is decreased every     |
   |                                         |                       | time a lease is        |
   |                                         |                       | released (a RELEASE    |
   |                                         |                       | message is received)   |
   |                                         |                       | or expires. The *id*   |
   |                                         |                       | is the subnet-id of a  |
   |                                         |                       | given subnet. This     |
   |                                         |                       | statistic is exposed   |
   |                                         |                       | for each subnet        |
   |                                         |                       | separately, and is     |
   |                                         |                       | reset during a         |
   |                                         |                       | reconfiguration        |
   |                                         |                       | event.                 |
   +-----------------------------------------+-----------------------+------------------------+
   | reclaimed-leases                        | integer               | Number of expired      |
   |                                         |                       | leases that have been  |
   |                                         |                       | reclaimed since        |
   |                                         |                       | server startup. It is  |
   |                                         |                       | incremented each time  |
   |                                         |                       | an expired lease is    |
   |                                         |                       | reclaimed (counting    |
   |                                         |                       | both NA and PD         |
   |                                         |                       | reclamations).         |
   |                                         |                       | This statistic never   |
   |                                         |                       | decreases. It can be   |
   |                                         |                       | used as a long-term    |
   |                                         |                       | indicator of how many  |
   |                                         |                       | actual leases have been|
   |                                         |                       | reclaimed.             |
   |                                         |                       | This is a global       |
   |                                         |                       | statistic that covers  |
   |                                         |                       | all subnets.           |
   +-----------------------------------------+-----------------------+------------------------+
   | subnet[id].reclaimed-leases             | integer               | Number of expired      |
   |                                         |                       | leases associated      |
   |                                         |                       | with a given subnet    |
   |                                         |                       | (*"id"* is the         |
   |                                         |                       | subnet-id) that have   |
   |                                         |                       | been reclaimed since   |
   |                                         |                       | server startup. It is  |
   |                                         |                       | incremented each time  |
   |                                         |                       | an expired lease is    |
   |                                         |                       | reclaimed (counting    |
   |                                         |                       | both NA and PD         |
   |                                         |                       | reclamations).         |
   |                                         |                       | The *id* is the        |
   |                                         |                       | subnet-id of a         |
   |                                         |                       | given subnet. This     |
   |                                         |                       | statistic is exposed   |
   |                                         |                       | for each subnet        |
   |                                         |                       | separately.            |
   +-----------------------------------------+-----------------------+------------------------+
   | declined-addresses                      | integer               | Number of IPv6         |
   |                                         |                       | addresses that are     |
   |                                         |                       | currently declined; a  |
   |                                         |                       | count of the number    |
   |                                         |                       | of leases currently    |
   |                                         |                       | unavailable. Once a    |
   |                                         |                       | lease is recovered,    |
   |                                         |                       | this statistic will    |
   |                                         |                       | be decreased;          |
   |                                         |                       | ideally, this          |
   |                                         |                       | statistic should be    |
   |                                         |                       | zero. If this          |
   |                                         |                       | statistic is non-zero  |
   |                                         |                       | or increasing, a       |
   |                                         |                       | network administrator  |
   |                                         |                       | should investigate     |
   |                                         |                       | whether there is a     |
   |                                         |                       | misbehaving device in  |
   |                                         |                       | the network. This is   |
   |                                         |                       | a global statistic     |
   |                                         |                       | that covers all        |
   |                                         |                       | subnets.               |
   +-----------------------------------------+-----------------------+------------------------+
   | subnet[id].declined-addresses           | integer               | Number of IPv6         |
   |                                         |                       | addresses that are     |
   |                                         |                       | currently declined in  |
   |                                         |                       | a given subnet; a      |
   |                                         |                       | count of the number    |
   |                                         |                       | of leases currently    |
   |                                         |                       | unavailable. Once a    |
   |                                         |                       | lease is recovered,    |
   |                                         |                       | this statistic will    |
   |                                         |                       | be decreased;          |
   |                                         |                       | ideally, this          |
   |                                         |                       | statistic should be    |
   |                                         |                       | zero. If this          |
   |                                         |                       | statistic is non-zero  |
   |                                         |                       | or increasing, a       |
   |                                         |                       | network administrator  |
   |                                         |                       | should investigate     |
   |                                         |                       | whether there is a     |
   |                                         |                       | misbehaving device in  |
   |                                         |                       | the network. The *id*  |
   |                                         |                       | is the subnet-id of a  |
   |                                         |                       | given subnet. This     |
   |                                         |                       | statistic is exposed   |
   |                                         |                       | for each subnet        |
   |                                         |                       | separately.            |
   +-----------------------------------------+-----------------------+------------------------+
   | reclaimed-declined-addresses            | integer               | Number of IPv6         |
   |                                         |                       | addresses that were    |
   |                                         |                       | declined, but have     |
   |                                         |                       | now been recovered.    |
   |                                         |                       | Unlike                 |
   |                                         |                       | declined-addresses,    |
   |                                         |                       | this statistic never   |
   |                                         |                       | decreases. It can be   |
   |                                         |                       | used as a long-term    |
   |                                         |                       | indicator of how many  |
   |                                         |                       | actual valid Declines  |
   |                                         |                       | were processed and     |
   |                                         |                       | recovered from. This   |
   |                                         |                       | is a global statistic  |
   |                                         |                       | that covers all        |
   |                                         |                       | subnets.               |
   +-----------------------------------------+-----------------------+------------------------+
   | subnet[id].reclaimed-declined-addresses | integer               | Number of IPv6         |
   |                                         |                       | addresses that were    |
   |                                         |                       | declined, but have     |
   |                                         |                       | now been recovered.    |
   |                                         |                       | Unlike                 |
   |                                         |                       | declined-addresses,    |
   |                                         |                       | this statistic never   |
   |                                         |                       | decreases. It can be   |
   |                                         |                       | used as a long-term    |
   |                                         |                       | indicator of how many  |
   |                                         |                       | actual valid Declines  |
   |                                         |                       | were processed and     |
   |                                         |                       | recovered from. The    |
   |                                         |                       | *id* is the subnet-id  |
   |                                         |                       | of a given subnet.     |
   |                                         |                       | This statistic is      |
   |                                         |                       | exposed for each       |
   |                                         |                       | subnet separately.     |
   +-----------------------------------------+-----------------------+------------------------+

.. note::

   This section describes DHCPv6-specific statistics. For a general
   overview and usage of statistics, see :ref:`stats`.

Beginning with Kea 1.7.7, the DHCPv6 server provides two global
parameters to control statistics default sample limits:

- ``statistic-default-sample-count`` - determines the default maximum
  number of samples which are kept. The special value of zero
  indicates that a default maximum age should be used.

- ``statistic-default-sample-age`` - determines the default maximum
  age in seconds of samples which are kept.

For instance, to reduce the statistic-keeping overhead, set
the default maximum sample count to 1 so that only one sample is kept:

::

     "Dhcp6": {
       "statistic-default-sample-count": 1,
       "subnet6": [ ... ],
       ...
   }

Statistics can be retrieved periodically to gain more insight into Kea operations. One tool that
leverages that capability is ISC Stork. See :ref:`stork` for details.


.. _dhcp6-ctrl-channel:

Management API for the DHCPv6 Server
====================================

The management API allows the issuing of specific management commands,
such as statistics retrieval, reconfiguration, or shutdown. For more
details, see :ref:`ctrl-channel`. Currently, the only supported
communication channel type is UNIX stream socket. By default there are
no sockets open; to instruct Kea to open a socket, the following entry
in the configuration file can be used:

::

   "Dhcp6": {
       "control-socket": {
           "socket-type": "unix",
           "socket-name": "/path/to/the/unix/socket"
       },

       "subnet6": [
           ...
       ],
       ...
   }

The length of the path specified by the ``socket-name`` parameter is
restricted by the maximum length for the UNIX socket name on the administrator's
operating system, i.e. the size of the ``sun_path`` field in the
``sockaddr_un`` structure, decreased by 1. This value varies on
different operating systems between 91 and 107 characters. Typical
values are 107 on Linux and 103 on FreeBSD.

Communication over the control channel is conducted using JSON
structures. See the
`Control Channel section in the Kea Developer's Guide
<https://reports.kea.isc.org/dev_guide/d2/d96/ctrlSocket.html>`__
for more details.

The DHCPv6 server supports the following operational commands:

-  build-report
-  config-get
-  config-reload
-  config-set
-  config-test
-  config-write
-  dhcp-disable
-  dhcp-enable
-  leases-reclaim
-  list-commands
-  shutdown
-  status-get
-  version-get

as described in :ref:`commands-common`. In addition, it supports the
following statistics-related commands:

-  statistic-get
-  statistic-reset
-  statistic-remove
-  statistic-get-all
-  statistic-reset-all
-  statistic-remove-all
-  statistic-sample-age-set
-  statistic-sample-age-set-all
-  statistic-sample-count-set
-  statistic-sample-count-set-all

as described in :ref:`command-stats`.

.. _dhcp6-user-contexts:

User Contexts in IPv6
=====================

Kea allows loading hook libraries that can sometimes benefit from
additional parameters. If such a parameter is specific to the whole
library, it is typically defined as a parameter for the hook library.
However, sometimes there is a need to specify parameters that are
different for each pool.

See :ref:`user-context` for additional background regarding the user
context idea. See :ref:`user-context-hooks` for a discussion from the
hooks perspective.

User contexts can be specified at global scope, shared network, subnet,
pool, client class, option data, or definition level, and via host
reservation. One other useful feature is the ability to store comments or
descriptions.

Let's consider a lightweight 4over6 deployment as an example. It is an
IPv6 transition technology that allows mapping IPv6 prefixes into full
or partial IPv4 addresses. In the DHCP context, these are specific
parameters that are supposed to be delivered to clients in the form of
additional options. Values of these options are correlated to delegated
prefixes, so it is reasonable to keep these parameters together with the
PD pool. On the other hand, lightweight 4over6 is not a commonly used
feature, so it is not a part of the base Kea code. The solution to this
problem is to specify a user context. For each PD pool that is expected to be
used for lightweight 4over6, a user context with extra parameters is
defined. Those extra parameters will be used by a hook library
and loaded only when dynamic calculation of the lightweight 4over6
option is actually needed. An example configuration looks as follows:

::

   "Dhcp6": {
       "subnet6": [ {
           "pd-pools": [
           {
               "prefix":  "2001:db8::",
               "prefix-len": 56,
               "delegated-len": 64,

               # This is a pool specific context.
               "user-context": {
                   "threshold-percent": 85,
                   "v4-network": "192.168.0.0/16",
                   "v4-overflow": "10.0.0.0/16",
                   "lw4over6-sharing-ratio": 64,
                   "lw4over6-v4-pool": "192.0.2.0/24",
                   "lw4over6-sysports-exclude": true,
                   "lw4over6-bind-prefix-len": 56
               }
           } ],
           "subnet": "2001:db8::/32",

           # This is a subnet-specific context. Any type of
           # information can be entered here as long as it is valid JSON.
           "user-context": {
               "comment": "Those v4-v6 migration technologies are tricky.",
               "experimental": true,
               "billing-department": 42,
               "contact-points": [ "Alice", "Bob" ]
           }
       } ]
   }

Kea does not interpret or use the user context information; it simply
stores it and makes it available to the hook libraries. It is up to each
hook library to extract that information and use it. The parser
translates a "comment" entry into a user context with the entry, which
allows a comment to be attached inside the configuration itself.

.. _dhcp6-std:

Supported DHCPv6 Standards
==========================

The following standards are currently supported:

-  *Dynamic Host Configuration Protocol for IPv6*, `RFC
   3315 <https://tools.ietf.org/html/rfc3315>`__: Supported messages are
   SOLICIT, ADVERTISE, REQUEST, RELEASE, RENEW, REBIND,
   INFORMATION-REQUEST, CONFIRM, DECLINE and REPLY. The only not
   supported message is RECONFIGURE.

-  *Dynamic Host Configuration Protocol (DHCPv6) Options for
   Session Initiation Protocol (SIP) Servers*, `RFC 3319
   <https://tools.ietf.org/html/rfc3319>`__: All defined options are supported.

-  *IPv6 Prefix Options for Dynamic Host Configuration Protocol (DHCP)
   version 6*, `RFC 3633 <https://tools.ietf.org/html/rfc3633>`__:
   Supported options are IA_PD and IA_PREFIX. Also supported is the
   status code NoPrefixAvail.

-  *DNS Configuration options for Dynamic Host Configuration Protocol for IPv6
   (DHCPv6)*, `RFC 3646 <https://tools.ietf.org/html/rfc3646>`__: All defined
   options are supported.

-  *Stateless Dynamic Host Configuration Protocol (DHCP) Service for IPv6*, `RFC
   3736 <https://tools.ietf.org/html/rfc3736>`__: The server operation in
   stateless mode is supported. Kea is currently server only, so the client side
   is not implemented.

-  *Information Refresh Time Option for Dynamic Host Configuration Protocol for
   IPv6 (DHCPv6)*, `RFC 4242 <https://tools.ietf.org/html/rfc4242>`__: The
   sole defined option (information-refresh-time) is supported.

-  *The Dynamic Host Configuration Protocol for IPv6 (DHCPv6) Relay
   Agent Remote-ID Option*, `RFC
   4649 <https://tools.ietf.org/html/rfc4649>`__: REMOTE-ID option is
   supported.

-  *Resolution of Fully Qualified Domain Name (FQDN) Conflicts among Dynamic Host
   Configuration Protocol (DHCP) Clients*, `RFC 4703
   <https://tools.ietf.org/html/rfc4703>`__: The DHCPv6 server uses DHCP-DDNS
   server to resolve conflicts.

-  *The Dynamic Host Configuration Protocol for IPv6 (DHCPv6) Client
   Fully Qualified Domain Name (FQDN) Option*, `RFC
   4704 <https://tools.ietf.org/html/rfc4704>`__: Supported option is
   CLIENT_FQDN.

-  *Dynamic Host Configuration Protocol for IPv6 (DHCPv6) Option for
   Dual-Stack Lite*, `RFC 6334 <https://tools.ietf.org/html/rfc6334>`__:
   the AFTR-Name DHCPv6 Option is supported.

-  *Relay-Supplied DHCP Options*, `RFC
   6422 <https://tools.ietf.org/html/rfc6422>`__: Full functionality is
   supported: OPTION_RSOO, ability of the server to echo back the
   options, checks whether an option is RSOO-enabled, ability to mark
   additional options as RSOO-enabled.

-  *Prefix Exclude Option for DHCPv6-based Prefix Delegation*, `RFC
   6603 <https://tools.ietf.org/html/rfc6603>`__: Prefix Exclude option
   is supported.

-  *Client Link-Layer Address Option in DHCPv6*, `RFC
   6939 <https://tools.ietf.org/html/rfc6939>`__: Supported option is
   client link-layer address option.

-  *Issues and Recommendations with Multiple Stateful DHCPv6 Options*,
   `RFC 7550 <https://tools.ietf.org/html/rfc7550>`__: All
   recommendations related to the DHCPv6 server operation are supported.

-  *DHCPv6 Options for Configuration of Softwire Address and Port-Mapped
   Clients*, `RFC 7598 <https://tools.ietf.org/html/rfc7598>`__: All
   options indicated in this specification are supported by the DHCPv6
   server.

-  *Generalized UDP Source Port for DHCP Relay*, `RFC 8357
   <https://tools.ietf.org/html/rfc8357>`__: The Kea server is able
   to handle Relay Source Port option in a received Relay-Forward
   message, remembers the UDP port and sends back Relay-Reply with a
   copy of the option to the relay agent using this UDP port.

-  *Dynamic Host Configuration Protocol for IPv6 (DHCPv6)*, `RFC 8415
   <https://tools.ietf.org/html/rfc8415>`__: New DHCPv6 protocol specification
   which obsoletes RFC 3315, RFC 3633, RFC 3736, RFC 4242, RFC 7083, RFC 7283,
   and RFC 7550. All features, with the exception of Reconfigure mechanism and
   the now deprecated temporary addresses (IA_TA) mechanism, are supported.

.. _dhcp6-limit:

DHCPv6 Server Limitations
=========================

These are the current limitations of the DHCPv6 server software. Most of
them are reflections of the current stage of development and should be
treated as “not implemented yet”, rather than actual limitations.

-  The server will allocate, renew, or rebind a maximum of one lease for
   a particular IA option (IA_NA or IA_PD) sent by a client. `RFC
   8415 <https://tools.ietf.org/html/rfc8415>`__ allows for multiple
   addresses or prefixes to be allocated for a single IA.

-  Temporary addresses are not supported. There is no intention to ever
   implement this feature, as it is deprecated in RFC8415.

-  Client reconfiguration (RECONFIGURE) is not yet supported.

.. _dhcp6-srv-examples:

Kea DHCPv6 Server Examples
==========================

A collection of simple-to-use examples for the DHCPv6 component of Kea
is available with the source files, located in the doc/examples/kea6
directory.

.. _dhcp6-cb:

Configuration Backend in DHCPv6
===============================

In the :ref:`config-backend` section we have described the Configuration
Backend feature, its applicability, and its limitations. This section focuses
on the usage of the CB with the DHCPv6 server. It lists the supported
parameters, describes limitations, and gives examples of the DHCPv6
server configuration to take advantage of the CB. Please also refer to
the sibling section :ref:`dhcp4-cb` for the DHCPv4-specific usage of
the CB.

.. _dhcp6-cb-parameters:

Supported Parameters
--------------------

The ultimate goal for the CB is to serve as a central configuration
repository for one or multiple Kea servers connected to the database. In
the future, it will be possible to store most of the server's
configuration in the database and reduce the configuration file to a bare
minimum; the only mandatory parameter will be the
``config-control``, which includes the necessary information to connect
to the database. In the present release, however, only a subset of
the DHCPv4 server parameters can be stored in the database. All other
parameters must be specified in the JSON configuration file, if
required.

The following table lists DHCPv6 specific parameters supported by the
Configuration Backend, with an indication on which level of the hierarchy
it is currently supported. The "n/a" marks cases when a
given parameter is not applicable at the particular level of the
hierarchy or in cases when the server does not support the parameter
at this level of the hierarchy. "no" is used when a parameter is
supported at the given level of the hierarchy but is not
configurable via the Configuration Backend.

All supported parameters can be configured via ``cb_cmds`` hooks library
described in the :ref:`cb-cmds-library` section. The general rule is that
the scalar global parameters are set using the
``remote-global-parameter6-set``; the shared network-specific parameters
are set using ``remote-network6-set``; and the subnet- and pool-level
parameters are set using ``remote-subnet6-set``. Whenever
there is an exception to this general rule, it is highlighted in the
table. The non-scalar global parameters have dedicated commands; for example,
the global DHCPv6 options (``option-data``) are modified using
``remote-option6-global-set``. Client classes together with class specific
option definitions and DHCPv6 options are configured using the
``remote-class6-set`` command.

.. table:: List of DHCPv6 Parameters Supported by the Configuration Backend

   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | Parameter                   | Global                     | Client    | Shared    | Subnet    | Pool      | Prefix     |
   |                             |                            | Class     | Network   |           |           | Delegation |
   |                             |                            |           |           |           |           | Pool       |
   +=============================+============================+===========+===========+===========+===========+============+
   | cache-max-age               | yes                        | n/a       | todo      | todo      | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | cache-threshold             | yes                        | n/a       | todo      | todo      | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | calculate-tee-times         | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | client-class                | n/a                        | n/a       | yes       | yes       | yes       | yes        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | ddns-send-update            | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | ddns-override-no-update     | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | ddns-override-client-update | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | ddns-replace-client-name    | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | ddns-generated-prefix       | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | ddns-qualifying-suffix      | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | decline-probation-period    | yes                        | n/a       | n/a       | n/a       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | delegated-len               | n/a                        | n/a       | n/a       | n/a       | n/a       | yes        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | dhcp4o6-port                | yes                        | n/a       | n/a       | n/a       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | excluded-prefix             | n/a                        | n/a       | n/a       | n/a       | n/a       | yes        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | excluded-prefix-len         | n/a                        | n/a       | n/a       | n/a       | n/a       | yes        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | hostname-char-set           | no                         | n/a       | no        | no        | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | hostname-char-replacement   | no                         | n/a       | no        | no        | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | interface                   | n/a                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | interface-id                | n/a                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | max-preferred-lifetime      | yes                        | yes       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | max-valid-lifetime          | yes                        | yes       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | min-preferred-lifetime      | yes                        | yes       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | min-valid-lifetime          | yes                        | yes       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | option-data                 | yes (via                   | yes       | yes       | yes       | yes       | yes        |
   |                             | remote-option6-global-set) |           |           |           |           |            |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | option-def                  | yes (via                   | yes       | n/a       | n/a       | n/a       | n/a        |
   |                             | remote-option-def6-set)    |           |           |           |           |            |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | preferred-lifetime          | yes                        | yes       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | prefix                      | n/a                        | n/a       | n/a       | n/a       | n/a       | yes        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | prefix-len                  | n/a                        | n/a       | n/a       | n/a       | n/a       | yes        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | rapid-commit                | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | rebind-timer                | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | relay                       | n/a                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | renew-timer                 | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | require-client-classes      | n/a                        | n/a       | yes       | yes       | yes       | yes        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | reservation-mode            | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | reservations-global         | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | reservations-in-subnet      | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | reservations-out-of-pool    | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | t1-percent                  | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | t2-percent                  | yes                        | n/a       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+
   | valid-lifetime              | yes                        | yes       | yes       | yes       | n/a       | n/a        |
   +-----------------------------+----------------------------+-----------+-----------+-----------+-----------+------------+

.. _dhcp6-cb-json:

Enabling Configuration Backend
------------------------------

The following configuration snippet demonstrates how to enable the MySQL
Configuration Backend for the DHCPv6 server:

::

   {
       "Dhcp6": {
       "server-tag": "my DHCPv6 server",
           "config-control": {
               "config-databases": [
                   {
                       "type": "mysql",
                       "name": "kea",
                       "user": "kea",
                       "password": "kea",
                       "host": "2001:db8:1::1",
                       "port": 3302
                   }
               ],
               "config-fetch-wait-time": 20
           },
           "hooks-libraries": [
               {
                   "library": "/usr/local/lib/kea/hooks/libdhcp_mysql_cb.so"
               },
               {
                   "library": "/usr/local/lib/kea/hooks/libdhcp_cb_cmds.so"
               }
           ],
           ...
       }
   }

The configuration structure is almost identical to that of the DHCPv4 server
(see :ref:`dhcp4-cb-json` for the detailed description).

.. _dhcp6-compatibility:

Kea DHCPv6 Compatibility Configuration Parameters
=================================================

By default, Kea aims to follow the RFC documents to promote better standards
compliance. However, there are buggy implementations out there that cannot be
easily fixed or upgraded. Therefore Kea provides an easy to use compatibility
mode for broken or non-compliant clients. In that purpose, flags have to be
enabled in order to enable uncommon practices:

.. code-block:: json

    {
      "Dhcp6": {
        "compatibility": {
        }
      }
    }


Lenient Option Parsing
----------------------

By default, DHCPv6 option 16's vendor-class-data field is parsed as a set of
length-value pairs. Same for tuple fields defined in custom options.

With ``lenient-option-parsing: "true"``, if a length ever exceeds the rest of
the option's buffer, Kea no longer complains with the log message ``unable to
parse the opaque data tuple, the buffer length is x, but the tuple length is y``
with ``x < y``. Instead, the value is considered to be the rest of the buffer,
or in terms of the log message above, the tuple length ``y`` becomes ``x``.

Enabling this flag is expected to improve compatibility with devices such as RAD
MiNID.

.. code-block:: json

    {
      "Dhcp6": {
        "compatibility": {
          "lenient-option-parsing": true
        }
      }
    }
