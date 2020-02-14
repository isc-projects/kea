.. _dhcp4:

*****************
The DHCPv4 Server
*****************

.. _dhcp4-start-stop:

Starting and Stopping the DHCPv4 Server
=======================================

It is recommended that the Kea DHCPv4 server be started and stopped
using ``keactrl`` (described in :ref:`keactrl`); however, it is also
possible to run the server directly. It accepts the following
command-line switches:

-  ``-c file`` - specifies the configuration file. This is the only
   mandatory switch.

-  ``-d`` - specifies whether the server logging should be switched to
   debug/verbose mode. In verbose mode, the logging severity and
   debuglevel specified in the configuration file are ignored;
   "debug" severity and the maximum debuglevel (99) are assumed. The
   flag is convenient for temporarily switching the server into maximum
   verbosity, e.g. when debugging.

-  ``-p server-port`` - specifies the local UDP port on which the server
   will listen. This is only useful during testing, as a DHCPv4 server
   listening on ports other than the standard ones will not be able to
   handle regular DHCPv4 queries.

-  ``-P client-port`` - specifies the remote UDP port to which the
   server will send all responses. This is only useful during testing,
   as a DHCPv4 server sending responses to ports other than the standard
   ones will not be able to handle regular DHCPv4 queries.

-  ``-t file`` - specifies a configuration file to be tested. Kea-dhcp4
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
configuration file. Since the DHCPv4 server opens privileged ports, it
requires root access. This daemon must be run as root.

During startup, the server will attempt to create a PID file of the
form: [runstatedir]/kea/[conf name].kea-dhcp4.pid where:

-  ``runstatedir``: The value as passed into the build configure
   script; it defaults to "/usr/local/var/run". Note that this value may be
   overridden at runtime by setting the environment variable
   KEA_PIDFILE_DIR, although this is intended primarily for testing
   purposes.

-  ``conf name``: The configuration file name used to start the server,
   minus all preceding paths and the file extension. For example, given
   a pathname of "/usr/local/etc/kea/myconf.txt", the portion used would
   be "myconf".

If the file already exists and contains the PID of a live process, the
server will issue a DHCP4_ALREADY_RUNNING log message and exit. It is
possible, though unlikely, that the file is a remnant of a system crash
and the process to which the PID belongs is unrelated to Kea. In such a
case it would be necessary to manually delete the PID file.

The server can be stopped using the ``kill`` command. When running in a
console, the server can also be shut down by pressing ctrl-c. It detects
the key combination and shuts down gracefully.

.. _dhcp4-configuration:

DHCPv4 Server Configuration
===========================

Introduction
------------

This section explains how to configure the DHCPv4 server using a
configuration file. Before DHCPv4 is started, its configuration file must
be created. The basic configuration is as follows:

::

   {
   # DHCPv4 configuration starts on the next line
   "Dhcp4": {

   # First we set up global values
       "valid-lifetime": 4000,
       "renew-timer": 1000,
       "rebind-timer": 2000,

   # Next we set up the interfaces to be used by the server.
       "interfaces-config": {
           "interfaces": [ "eth0" ]
       },

   # And we specify the type of lease database
       "lease-database": {
           "type": "memfile",
           "persist": true,
           "name": "/var/lib/kea/dhcp4.leases"
       },

   # Finally, we list the subnets from which we will be leasing addresses.
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [
                   {
                        "pool": "192.0.2.1 - 192.0.2.200"
                   }
               ]
           }
       ]
   # DHCPv4 configuration ends with the next line
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
above this object is called ``Dhcp4``.

.. note::

   In the current Kea release it is possible to specify configurations
   of multiple modules within a single configuration file, but this is
   not recommended and support for it will be removed in a future
   release. The only object, besides the one specifying module
   configuration, which can be (and usually was) included in the same file
   is ``Logging``. However, we don't include this object in the example
   above for clarity; its content, the list of loggers, should now be
   inside the ``Dhcp4`` object instead of the deprecated object.

The Dhcp4 configuration starts with the ``"Dhcp4": {`` line and ends
with the corresponding closing brace (in the above example, the brace
after the last comment). Everything defined between those lines is
considered to be the Dhcp4 configuration.

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

The first few DHCPv4 configuration elements
define some global parameters. ``valid-lifetime`` defines how long the
addresses (leases) given out by the server are valid. If nothing
changes, a client that got an address is allowed to use it for 4000
seconds. (Note that integer numbers are specified as is, without any
quotes around them.) ``renew-timer`` and ``rebind-timer`` are values
(also in seconds) that define T1 and T2 timers that govern when the
client will begin the renewal and rebind procedures.

.. note::

   Beginning with Kea 1.6.0 the lease valid lifetime is extended from a
   single value to a triplet with minimum, default and maximum values using
   ``min-valid-lifetime``, ``valid-lifetime`` and
   ``max-valid-lifetime``. When the client does not specify
   a lifetime the default value is used, when it specifies using a DHCP option
   code 51 this value is used if it is not less than the  minimum (in this case
   the minimum is returned) or greater than the maximum (in this case the
   maximum is used).

.. note::

   Both ``renew-timer`` and ``rebind-timer``
   are optional. The server will only send ``rebind-timer`` to the client,
   via DHCPv4 option code 59, if it is less than ``valid-lifetime``; and it
   will only send ``renew-timer``, via DHCPv4 option code 58, if it is less
   than ``rebind-timer`` (or ``valid-lifetime`` if ``rebind-timer`` was not
   specified). In their absence, the client should select values for T1
   and T2 timers according to `RFC 2131 <https://tools.ietf.org/html/rfc2131>`_.
   See section :ref:`dhcp4-t1-t2-times`
   for more details on generating T1 and T2.

The ``interfaces-config`` map specifies the server configuration
concerning the network interfaces on which the server should listen to
the DHCP messages. The ``interfaces`` parameter specifies a list of
network interfaces on which the server should listen. Lists are opened
and closed with square brackets, with elements separated by commas. To
listen on two interfaces, the ``interfaces-config`` command should look
like this:

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
for the Dhcp4 definition follow, a trailing comma is present.

Finally, we need to define a list of IPv4 subnets. This is the most
important DHCPv4 configuration structure, as the server uses that
information to process clients' requests. It defines all subnets from
which the server is expected to receive DHCP requests. The subnets are
specified with the ``subnet4`` parameter. It is a list, so it starts and
ends with square brackets. Each subnet definition in the list has
several attributes associated with it, so it is a structure and is
opened and closed with braces. At a minimum, a subnet definition has to
have at least two parameters: ``subnet`` (which defines the whole
subnet) and ``pools`` (which is a list of dynamically allocated pools
that are governed by the DHCP server).

The example contains a single subnet. If more than one were defined,
additional elements in the ``subnet4`` parameter would be specified and
separated by commas. For example, to define three subnets, the following
syntax would be used:

::

   "subnet4": [
       {
           "pools": [ { "pool":  "192.0.2.1 - 192.0.2.200" } ],
           "subnet": "192.0.2.0/24"
       },
       {
           "pools": [ { "pool": "192.0.3.100 - 192.0.3.200" } ],
           "subnet": "192.0.3.0/24"
       },
       {
           "pools": [ { "pool": "192.0.4.1 - 192.0.4.254" } ],
           "subnet": "192.0.4.0/24"
       }
   ]

Note that indentation is optional and is used for aesthetic purposes
only. In some cases it may be preferable to use more compact notation.

After all the parameters have been specified, we have two contexts open:
global and Dhcp4; thus, we need two closing curly brackets to close
them.

Lease Storage
-------------

All leases issued by the server are stored in the lease database.
Currently there are four database backends available: memfile (which is
the default backend), MySQL, PostgreSQL, and Cassandra.

Memfile - Basic Storage for Leases
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The server is able to store lease data in different repositories. Larger
deployments may elect to store leases in a database.
:ref:`database-configuration4` describes this option. In
typical smaller deployments, though, the server will store lease
information in a CSV file rather than a database. As well as requiring
less administration, an advantage of using a file for storage is that it
eliminates a dependency on third-party database software.

The configuration of the file backend (memfile) is controlled through
the Dhcp4/lease-database parameters. The ``type`` parameter is mandatory
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
   this parameter is ``"[kea-install-dir]/var/lib/kea/kea-leases4.csv"``.

-  ``lfc-interval``: specifies the interval, in seconds, at which the
   server will perform a lease file cleanup (LFC). This removes
   redundant (historical) information from the lease file and
   effectively reduces the lease file size. The cleanup process is
   described in more detail later in this section. The default
   value of the ``lfc-interval`` is ``3600``. A value of 0 disables the
   LFC.

-  ``max-row-errors``: when the server loads a lease file, it is processed
   row by row, each row contaning a single lease. If a row is flawed and
   cannot be processed correctly the server will log it, discard the row,
   and go on to the next row. This parameter can be used to set a limit on
   the number of such discards that may occur after which the server will
   abandon the effort and exit.  The default value of 0 disables the limit
   and allows the server to process the entire file, regardless of how many
   rows are discarded.

::

   "Dhcp4": {
       "lease-database": {
           "type": "memfile",
           "persist": true,
           "name": "/tmp/kea-leases4.csv",
           "lfc-interval": 1800,
           "max-row-errors": 100
       }
   }

This configuration selects the ``/tmp/kea-leases4.csv`` as the storage
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

.. _database-configuration4:

Lease Database Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::

   Lease database access information must be configured for the DHCPv4
   server, even if it has already been configured for the DHCPv6 server.
   The servers store their information independently, so each server can
   use a separate database or both servers can use the same database.

Lease database configuration is controlled through the
Dhcp4/lease-database parameters. The database type must be set to
"memfile", "mysql", "postgresql", or "cql", e.g.:

::

   "Dhcp4": { "lease-database": { "type": "mysql", ... }, ... }

Next, the name of the database to hold the leases must be set; this is
the name used when the database was created (see
:ref:`mysql-database-create`, :ref:`pgsql-database-create`, or
:ref:`cql-database-create`).

::

   "Dhcp4": { "lease-database": { "name": "database-name" , ... }, ... }

For Cassandra:

::

   "Dhcp4": { "lease-database": { "keyspace": "database-name" , ... }, ... }

If the database is located on a different system from the DHCPv4 server,
the database host name must also be specified:

::

   "Dhcp4": { "lease-database": { "host": "remote-host-name", ... }, ... }

(It should be noted that this configuration may have a severe impact on server performance.)

Normally, the database will be on the same machine as the DHCPv4 server.
In this case, set the value to the empty string:

::

   "Dhcp4": { "lease-database": { "host" : "", ... }, ... }

Should the database use a port other than the default, it may be
specified as well:

::

   "Dhcp4": { "lease-database": { "port" : 12345, ... }, ... }

Should the database be located on a different system, the administrator may need to
specify a longer interval for the connection timeout:

::

   "Dhcp4": { "lease-database": { "connect-timeout" : timeout-in-seconds, ... }, ... }

The default value of five seconds should be more than adequate for local
connections. If a timeout is given, though, it should be an integer
greater than zero.

The maximum number of times the server will automatically attempt to
reconnect to the lease database after connectivity has been lost may be
specified:

::

   "Dhcp4": { "lease-database": { "max-reconnect-tries" : number-of-tries, ... }, ... }

If the server is unable to reconnect to the database after making the
maximum number of attempts, the server will exit. A value of zero (the
default) disables automatic recovery and the server will exit
immediately upon detecting a loss of connectivity (MySQL and PostgreSQL
only). For Cassandra, Kea uses an interface that connects to
all nodes in a cluster at the same time. Any connectivity issues should
be handled by internal Cassandra mechanisms.

The number of milliseconds the server will wait between attempts to
reconnect to the lease database after connectivity has been lost may
also be specified:

::

   "Dhcp4": { "lease-database": { "reconnect-wait-time" : number-of-milliseconds, ... }, ... }

The default value for MySQL and PostgreSQL is 0, which disables automatic
recovery and causes the server to exit immediately upon detecting the
loss of connectivity. The default value for Cassandra is 2000 ms.

.. note::

   Automatic reconnection to database backends is configured
   individually per backend. This allows users to tailor the recovery
   parameters to each backend they use. We do suggest that users enable it
   either for all backends or none, so behavior is consistent.
   Losing connectivity to a backend for which reconnect is
   disabled will result in the server shutting itself down. This
   includes cases when the lease database backend and the hosts database
   backend are connected to the same database instance.

..

.. note::

   Note that the host parameter is used by the MySQL and PostgreSQL backends.
   Cassandra has a concept of contact points that can be used to
   contact the cluster, instead of a single IP or hostname. It takes a
   list of comma-separated IP addresses, which may be specified as:
   ::

      "Dhcp4": { "lease-database": { "contact-points" : "192.0.2.1,192.0.2.2", ... }, ... }

Finally, the credentials of the account under which the server will
access the database should be set:

::

   "Dhcp4": { "lease-database": { "user": "user-name",
                                  "password": "password",
                                 ... },
              ... }

If there is no password to the account, set the password to the empty
string "". (This is also the default.)

.. _cassandra-database-configuration4:

Cassandra-Specific Parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Cassandra backend is configured slightly differently. Cassandra has
a concept of contact points that can be used to contact the cluster,
instead of a single IP or hostname. It takes a list of comma-separated
IP addresses, which may be specified as:

::

   "Dhcp4": {
       "lease-database": {
           "type": "cql",
           "contact-points": "ip-address1, ip-address2 [,...]",
           ...
       },
       ...
   }

Cassandra also supports a number of optional parameters:

-  ``reconnect-wait-time`` - governs how long Kea waits before
   attempting to reconnect. Expressed in milliseconds. The default is
   2000 [ms].

-  ``connect-timeout`` - sets the timeout for connecting to a node.
   Expressed in milliseconds. The default is 5000 [ms].

-  ``request-timeout`` - sets the timeout for waiting for a response
   from a node. Expressed in milliseconds. The default is 12000 [ms].

-  ``tcp-keepalive`` - governs the TCP keep-alive mechanism. Expressed
   in seconds of delay. If the parameter is not present, the mechanism
   is disabled.

-  ``tcp-nodelay`` - enables/disables Nagle's algorithm on connections.
   The default is true.

-  ``consistency`` - configures consistency level. The default is
   "quorum". Supported values: any, one, two, three, quorum, all,
   local-quorum, each-quorum, serial, local-serial, local-one. See
   `Cassandra
   consistency <https://docs.datastax.com/en/cassandra/3.0/cassandra/dml/dmlConfigConsistency.html>`__
   for more details.

-  ``serial-consistency`` - configures serial consistency level which
   manages lightweight transaction isolation. The default is "serial".
   Supported values: any, one, two, three, quorum, all, local-quorum,
   each-quorum, serial, local-serial, local-one. See `Cassandra serial
   consistency <https://docs.datastax.com/en/cassandra/3.0/cassandra/dml/dmlConfigSerialConsistency.html>`__
   for more details.

For example, a complex Cassandra configuration with most parameters
specified could look as follows:

::

   "Dhcp4": {
     "lease-database": {
         "type": "cql",
         "keyspace": "keatest",
         "contact-points": "192.0.2.1, 192.0.2.2, 192.0.2.3",
         "port": 9042,
         "reconnect-wait-time": 2000,
         "connect-timeout": 5000,
         "request-timeout": 12000,
         "tcp-keepalive": 1,
         "tcp-nodelay": true
       },
       ...
   }

Similar parameters can be specified for the hosts database.

.. _hosts4-storage:

Hosts Storage
-------------

Kea is also able to store information about host reservations in the
database. The hosts database configuration uses the same syntax as the
lease database. In fact, a Kea server opens independent connections for
each purpose, be it lease or hosts information. This arrangement gives
the most flexibility. Kea can keep leases and host reservations
separately, but can also point to the same database. Currently the
supported hosts database types are MySQL, PostgreSQL, and Cassandra.

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
configuration file, although this leads to a restriction in ordering
in the case of a host reservation addition; read-only stores must be
configured after a (required) read-write store, or the addition will
fail.

.. _hosts-databases-configuration4:

DHCPv4 Hosts Database Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hosts database configuration is controlled through the
Dhcp4/hosts-database parameters. If enabled, the type of database must
be set to "mysql" or "postgresql".

::

   "Dhcp4": { "hosts-database": { "type": "mysql", ... }, ... }

Next, the name of the database to hold the reservations must be set;
this is the name used when the lease database was created (see
:ref:`supported-databases` for instructions on how to set up the
desired database type):

::

   "Dhcp4": { "hosts-database": { "name": "database-name" , ... }, ... }

If the database is located on a different system than the DHCPv4 server,
the database host name must also be specified:

::

   "Dhcp4": { "hosts-database": { "host": remote-host-name, ... }, ... }

(Again, it should be noted that this configuration may have a severe impact on server performance.)

Normally, the database will be on the same machine as the DHCPv4 server.
In this case, set the value to the empty string:

::

   "Dhcp4": { "hosts-database": { "host" : "", ... }, ... }

Should the database use a port different than the default, it may be
specified as well:

::

   "Dhcp4": { "hosts-database": { "port" : 12345, ... }, ... }

The maximum number of times the server will automatically attempt to
reconnect to the host database after connectivity has been lost may be
specified:

::

   "Dhcp4": { "hosts-database": { "max-reconnect-tries" : number-of-tries, ... }, ... }

If the server is unable to reconnect to the database after making the
maximum number of attempts, the server will exit. A value of zero (the
default) disables automatic recovery and the server will exit
immediately upon detecting a loss of connectivity (MySQL and PostgreSQL
only).

The number of milliseconds the server will wait between attempts to
reconnect to the host database after connectivity has been lost may also
be specified:

::

   "Dhcp4": { "hosts-database": { "reconnect-wait-time" : number-of-milliseconds, ... }, ... }

The default value for MySQL and PostgreSQL is 0, which disables automatic
recovery and causes the server to exit immediately upon detecting the
loss of connectivity. The default value for Cassandra is 2000 ms.

.. note::

   Automatic reconnection to database backends is configured
   individually per backend. This allows users to tailor the recovery
   parameters to each backend they use. We do suggest that users enable it
   either for all backends or none, so behavior is consistent.
   Losing connectivity to a backend for which reconnect is
   disabled will result in the server shutting itself down. This
   includes cases when the lease database backend and the hosts database
   backend are connected to the same database instance.

Finally, the credentials of the account under which the server will
access the database should be set:

::

   "Dhcp4": { "hosts-database": { "user": "user-name",
                                  "password": "password",
                                 ... },
              ... }

If there is no password to the account, set the password to the empty
string "". (This is also the default.)

The multiple storage extension uses a similar syntax; a configuration is
placed into a "hosts-databases" list instead of into a "hosts-database"
entry, as in:

::

   "Dhcp4": { "hosts-databases": [ { "type": "mysql", ... }, ... ], ... }

For additional Cassandra-specific parameters, see
:ref:`cassandra-database-configuration4`.

.. _read-only-database-configuration4:

Using Read-Only Databases for Host Reservations with DHCPv4
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

   "Dhcp4": { "hosts-database": { "readonly": true, ... }, ... }

Setting this parameter to ``false`` configures the database backend to
operate in "read-write" mode, which is also the default configuration if
the parameter is not specified.

.. note::

   The ``readonly`` parameter is currently only supported for MySQL and
   PostgreSQL databases.

.. _dhcp4-interface-configuration:

Interface Configuration
-----------------------

The DHCPv4 server must be configured to listen on specific network
interfaces. The simplest network interface configuration tells the
server to listen on all available interfaces:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "*" ]
       }
       ...
   },


The asterisk plays the role of a wildcard and means "listen on all
interfaces." However, it is usually a good idea to explicitly specify
interface names:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3" ]
       },
       ...
   }


It is possible to use a wildcard interface name (asterisk) concurrently
with explicit interface names:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3", "*" ]
       },
       ...
   }


It is anticipated that this form of usage will only be used when it is
desired to temporarily override a list of interface names and listen on
all interfaces.

Some deployments of DHCP servers require that the servers listen on
interfaces with multiple IPv4 addresses configured. In these situations,
the address to use can be selected by appending an IPv4 address to the
interface name in the following manner:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1/10.0.0.1", "eth3/192.0.2.3" ]
       },
       ...
   }


Should the server be required to listen on multiple IPv4 addresses
assigned to the same interface, multiple addresses can be specified for
an interface as in the example below:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1/10.0.0.1", "eth1/10.0.0.2" ]
       },
       ...
   }


Alternatively, if the server should listen on all addresses for the
particular interface, an interface name without any address should be
specified.

Kea supports responding to directly connected clients which don't have
an address configured. This requires the server to inject the hardware
address of the destination into the data link layer of the packet
being sent to the client. The DHCPv4 server uses raw sockets to
achieve this, and builds the entire IP/UDP stack for the outgoing
packets. The downside of raw socket use, however, is that incoming and
outgoing packets bypass the firewalls (e.g. iptables).

Handling traffic on multiple IPv4 addresses assigned to the same
interface can be a challenge, as raw sockets are bound to the
interface. When the DHCP server is configured to use the raw socket on
an interface to receive DHCP traffic, advanced packet filtering
techniques (e.g. the BPF) must be used to receive unicast traffic on
the desired addresses assigned to the interface. Whether clients use
the raw socket or the UDP socket depends on whether they are directly
connected (raw socket) or relayed (either raw or UDP socket).

Therefore, in deployments where the server does not need to provision
the directly connected clients and only receives the unicast packets
from the relay agents, the DHCP server should be configured to use UDP
sockets instead of raw sockets. The following configuration
demonstrates how this can be achieved:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3" ],
           "dhcp-socket-type": "udp"
       },
       ...
   }


The ``dhcp-socket-type`` specifies that the IP/UDP sockets will be
opened on all interfaces on which the server listens, i.e. "eth1" and
"eth3" in our case. If ``dhcp-socket-type`` is set to ``raw``, it
configures the server to use raw sockets instead. If the
``dhcp-socket-type`` value is not specified, the default value ``raw``
is used.

Using UDP sockets automatically disables the reception of broadcast
packets from directly connected clients. This effectively means that UDP
sockets can be used for relayed traffic only. When using raw sockets,
both the traffic from the directly connected clients and the relayed
traffic are handled. Caution should be taken when configuring the server
to open multiple raw sockets on the interface with several IPv4
addresses assigned. If the directly connected client sends the message
to the broadcast address, all sockets on this link will receive this
message and multiple responses will be sent to the client. Therefore,
the configuration with multiple IPv4 addresses assigned to the interface
should not be used when the directly connected clients are operating on
that link. To use a single address on such interface, the
"interface-name/address" notation should be used.

.. note::

   Specifying the value ``raw`` as the socket type doesn't guarantee
   that the raw sockets will be used! The use of raw sockets to handle
   the traffic from the directly connected clients is currently
   supported on Linux and BSD systems only. If the raw sockets are not
   supported on the particular OS in use, the server will issue a warning and
   fall back to using IP/UDP sockets.

In a typical environment, the DHCP server is expected to send back a
response on the same network interface on which the query was received.
This is the default behavior. However, in some deployments it is desired
that the outbound (response) packets will be sent as regular traffic and
the outbound interface will be determined by the routing tables. This
kind of asymmetric traffic is uncommon, but valid. Kea supports a
parameter called ``outbound-interface`` that controls this behavior. It
supports two values; the first one, ``same-as-inbound``, tells Kea to
send back the response on the same interface where the query packet was
received. This is the default behavior. The second one, ``use-routing``,
tells Kea to send regular UDP packets and let the kernel's routing table
determine the most appropriate interface. This only works when
``dhcp-socket-type`` is set to ``udp``. An example configuration looks
as follows:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3" ],
           "dhcp-socket-type": "udp",
           "outbound-interface": "use-routing"
       },
       ...
   }

Interfaces are re-detected at each reconfiguration. This behavior can be
disabled by setting the ``re-detect`` value to ``false``, for instance:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3" ],
           "re-detect": false
       },
       ...
   }


Note that interfaces are not re-detected during ``config-test``.

Usually loopback interfaces (e.g. the "lo" or "lo0" interface) may not
be configured, but if a loopback interface is explicitely configured and
IP/UDP sockets are specified, the loopback interface is accepted.

For example, it can be used to run Kea in a FreeBSD jail having only a
loopback interface, to service a relayed DHCP request:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "lo0" ],
           "dhcp-socket-type": "udp"
       },
       ...
   }

.. _dhcpinform-unicast-issues:

Issues with Unicast Responses to DHCPINFORM
-------------------------------------------

The use of UDP sockets has certain benefits in deployments where the
server receives only relayed traffic; these benefits are mentioned in
:ref:`dhcp4-interface-configuration`. From the
administrator's perspective it is often desirable to configure the
system's firewall to filter out unwanted traffic, and the use of UDP
sockets facilitates this. However, the administrator must also be aware
of the implications related to filtering certain types of traffic, as it
may impair the DHCP server's operation.

In this section we are focusing on the case when the server receives the
DHCPINFORM message from the client via a relay. According to `RFC
2131 <https://tools.ietf.org/html/rfc2131>`__, the server should unicast
the DHCPACK response to the address carried in the "ciaddr" field. When
the UDP socket is in use, the DHCP server relies on the low-level
functions of an operating system to build the data link, IP, and UDP
layers of the outgoing message. Typically, the OS will first use ARP to
obtain the client's link-layer address to be inserted into the frame's
header, if the address is not cached from a previous transaction that
the client had with the server. When the ARP exchange is successful, the
DHCP message can be unicast to the client, using the obtained address.

Some system administrators block ARP messages in their network, which
causes issues for the server when it responds to the DHCPINFORM
messages because the server is unable to send the DHCPACK if the
preceding ARP communication fails. Since the OS is entirely responsible
for the ARP communication and then sending the DHCP packet over the
wire, the DHCP server has no means to determine that the ARP exchange
failed and the DHCP response message was dropped. Thus, the server does
not log any error messages when the outgoing DHCP response is dropped.
At the same time, all hooks pertaining to the packet-sending operation
will be called, even though the message never reaches its destination.

Note that the issue described in this section is not observed when the
raw sockets are in use, because, in this case, the DHCP server builds
all the layers of the outgoing message on its own and does not use ARP.
Instead, it inserts the value carried in the "chaddr" field of the
DHCPINFORM message into the link layer.

Server administrators willing to support DHCPINFORM messages via relays
should not block ARP traffic in their networks or should use raw sockets
instead of UDP sockets.

.. _ipv4-subnet-id:

IPv4 Subnet Identifier
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

   "Dhcp4": {
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "id": 1024,
               ...
           }
       ]
   }

This identifier will not change for this subnet unless the "id"
parameter is removed or set to 0. The value of 0 forces auto-generation
of the subnet identifier.

.. _ipv4-subnet-prefix:

IPv4 Subnet Prefix
------------------

The subnet prefix is the second way to identify a subnet. It does not
need to have the address part to match the prefix length, for instance
this configuration is accepted:

::

   "Dhcp4": {
       "subnet4": [
           {
              "subnet": "192.0.2.1/24",
               ...
           }
       ]
   }

Even there is another subnet with the "192.0.2.0/24" prefix: only the
textual form of subnets are compared to avoid duplicates.

.. note::

    Abuse of this feature can lead to incorrect subnet selection
    (see :ref:`dhcp4-subnet-selection`).

.. _dhcp4-address-config:

Configuration of IPv4 Address Pools
-----------------------------------

The main role of a DHCPv4 server is address assignment. For this, the
server must be configured with at least one subnet and one pool of
dynamic addresses to be managed. For example, assume that the server is
connected to a network segment that uses the 192.0.2.0/24 prefix. The
administrator of that network decides that addresses from range
192.0.2.10 to 192.0.2.20 are going to be managed by the Dhcp4 server.
Such a configuration can be achieved in the following way:

::

   "Dhcp4": {
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [
                   { "pool": "192.0.2.10 - 192.0.2.20" }
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
previous example, further assume that 192.0.2.64/26 should be also be
managed by the server. It could be written as 192.0.2.64 to 192.0.2.127.
Alternatively, it can be expressed more simply as 192.0.2.64/26. Both
formats are supported by Dhcp4 and can be mixed in the pool list. For
example, one could define the following pools:

::

   "Dhcp4": {
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [
                   { "pool": "192.0.2.10-192.0.2.20" },
                   { "pool": "192.0.2.64/26" }
               ],
               ...
           }
       ],
       ...
   }

White space in pool definitions is ignored, so spaces before and after
the hyphen are optional. They can be used to improve readability.

The number of pools is not limited, but for performance reasons it is
recommended to use as few as possible.

The server may be configured to serve more than one subnet:

::

   "Dhcp4": {
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.1 - 192.0.2.200" } ],
               ...
           },
           {
               "subnet": "192.0.3.0/24",
               "pools": [ { "pool": "192.0.3.100 - 192.0.3.200" } ],
               ...
           },
           {
               "subnet": "192.0.4.0/24",
               "pools": [ { "pool": "192.0.4.1 - 192.0.4.254" } ],
               ...
           }
       ]
   }

When configuring a DHCPv4 server using prefix/length notation, please
pay attention to the boundary values. When specifying that the server
can use a given pool, it will also be able to allocate the first
(typically a network address) and the last (typically a broadcast
address) address from that pool. In the aforementioned example of pool
192.0.3.0/24, both the 192.0.3.0 and 192.0.3.255 addresses may be
assigned as well. This may be invalid in some network configurations. To
avoid this, use the "min-max" notation.

.. _dhcp4-t1-t2-times:

Sending T1 (Option 58) and T2 (Option 59)
-----------------------------------------

According to `RFC 2131 <https://tools.ietf.org/html/rfc2131>`__,
servers should send values for T1 and T2 that are 50% and 87.5% of the
lease lifetime, respectively. By default, kea-dhcp4 does not send
either value. It can be configured to send values that are specified
explicitly or that are calculated as percentages of the lease time. The
server's behavior is governed by a combination of configuration
parameters, two of which have already been mentioned.
To send specific, fixed values use the following two parameters:

-  ``renew-timer`` - specifies the value of T1 in seconds.

-  ``rebind-timer`` - specifies the value of T2 in seconds.

The server will only send T2 if it is less than the valid lease time. T1
will only be sent if: T2 is being sent and T1 is less than T2; or T2
is not being sent and T1 is less than the valid lease time.

Calculating the values is controlled by the following three parameters.

-  ``calculate-tee-times`` - when true, T1 and T2 will be calculated as
   percentages of the valid lease time. It defaults to false.

-  ``t1-percent`` - the percentage of the valid lease time to use for
   T1. It is expressed as a real number between 0.0 and 1.0 and must be
   less than t2-percent. The default value is 0.50 per RFC 2131.

-  ``t2-percent`` - the percentage of the valid lease time to use for
   T2. It is expressed as a real number between 0.0 and 1.0 and must be
   greater than t1-percent. The default value is .875 per RFC 2131.

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

.. _dhcp4-std-options:

Standard DHCPv4 Options
-----------------------

One of the major features of the DHCPv4 server is the ability to provide
configuration options to clients. Most of the options are sent by the
server only if the client explicitly requests them using the Parameter
Request List option. Those that do not require inclusion in the
Parameter Request List option are commonly used options, e.g. "Domain
Server", and options which require special behavior, e.g. "Client FQDN",
which is returned to the client if the client has included this option
in its message to the server.

:ref:`dhcp4-std-options-list` comprises the list of the
standard DHCPv4 options whose values can be configured using the
configuration structures described in this section. This table excludes
the options which require special processing and thus cannot be
configured with fixed values. The last column of the table
indicates which options can be sent by the server even when they are not
requested in the Parameter Request List option, and those which are sent
only when explicitly requested.

The following example shows how to configure the addresses of DNS
servers, which is one of the most frequently used options. Options
specified in this way are considered global and apply to all configured
subnets.

::

   "Dhcp4": {
       "option-data": [
           {
              "name": "domain-name-servers",
              "code": 6,
              "space": "dhcp4",
              "csv-format": true,
              "data": "192.0.2.1, 192.0.2.2"
           },
           ...
       ]
   }


Note that only one of name or code is required; there is no need to
specify both. Space has a default value of "dhcp4", so this can be skipped
as well if a regular (not encapsulated) DHCPv4 option is defined.
Finally, csv-format defaults to true, so it too can be skipped, unless
the option value is specified as a hexadecimal string. Therefore,
the above example can be simplified to:

::

   "Dhcp4": {
       "option-data": [
           {
              "name": "domain-name-servers",
              "data": "192.0.2.1, 192.0.2.2"
           },
           ...
       ]
   }


Defined options are added to the response when the client requests them
at a few exceptions, which are always added. To enforce the addition of
a particular option, set the always-send flag to true as in:

::

   "Dhcp4": {
       "option-data": [
           {
              "name": "domain-name-servers",
              "data": "192.0.2.1, 192.0.2.2",
              "always-send": true
           },
           ...
       ]
   }


The effect is the same as if the client added the option code in the
Parameter Request List option (or its equivalent for vendor options):

::

   "Dhcp4": {
       "option-data": [
           {
              "name": "domain-name-servers",
              "data": "192.0.2.1, 192.0.2.2",
              "always-send": true
           },
           ...
       ],
       "subnet4": [
           {
              "subnet": "192.0.3.0/24",
              "option-data": [
                  {
                      "name": "domain-name-servers",
                      "data": "192.0.3.1, 192.0.3.2"
                  },
                  ...
              ],
              ...
           },
           ...
       ],
       ...
   }


The Domain Name Servers option is always added to responses (the
always-send is "sticky"), but the value is the subnet one when the client
is localized in the subnet.

The ``name`` parameter specifies the option name. For a list of
currently supported names, see :ref:`dhcp4-std-options-list`
below. The ``code`` parameter specifies the option code, which must
match one of the values from that list. The next line specifies the
option space, which must always be set to "dhcp4" as these are standard
DHCPv4 options. For other option spaces, including custom option spaces,
see :ref:`dhcp4-option-spaces`. The next line specifies the format in
which the data will be entered; use of CSV (comma-separated values) is
recommended. The sixth line gives the actual value to be sent to
clients. The data parameter is specified as normal text, with values separated by
commas if more than one value is allowed.

Options can also be configured as hexadecimal values. If ``csv-format``
is set to false, option data must be specified as a hexadecimal string.
The following commands configure the domain-name-servers option for all
subnets with the following addresses: 192.0.3.1 and 192.0.3.2. Note that
``csv-format`` is set to false.

::

   "Dhcp4": {
       "option-data": [
           {
               "name": "domain-name-servers",
               "code": 6,
               "space": "dhcp4",
               "csv-format": false,
               "data": "C0 00 03 01 C0 00 03 02"
           },
           ...
       ],
       ...
   }

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

   "Dhcp4": {
       "option-data": [
           {
               "name": "user-class",
               "code": 77,
               "space": "dhcp4",
               "csv-format": false,
               "data": "'convert this text to binary'"
           },
           ...
       ],
       ...
   }

Most of the parameters in the "option-data" structure are optional and
can be omitted in some circumstances, as discussed in :ref:`dhcp4-option-data-defaults`.

It is possible to specify or override options on a per-subnet basis. If
clients connected to most subnets are expected to get the same
values of a given option, administrators should use global options; it is possible to
override specific values for a small number of subnets. On the other
hand, if different values are used in each subnet, it does not make sense
to specify global option values; rather, only
subnet-specific ones should be set.

The following commands override the global DNS servers option for a
particular subnet, setting a single DNS server with address 192.0.2.3:

::

   "Dhcp4": {
       "subnet4": [
           {
               "option-data": [
                   {
                       "name": "domain-name-servers",
                       "code": 6,
                       "space": "dhcp4",
                       "csv-format": true,
                       "data": "192.0.2.3"
                   },
                   ...
               ],
               ...
           },
           ...
       ],
       ...
   }

In some cases it is useful to associate some options with an address
pool from which a client is assigned a lease. Pool-specific option
values override subnet-specific and global option values. The server's
administrator must not try to prioritize assignment of pool-specific
options by trying to order pool declarations in the server
configuration.

The following configuration snippet demonstrates how to specify the DNS
servers option, which will be assigned to a client only if the client
obtains an address from the given pool:

::

   "Dhcp4": {
       "subnet4": [
           {
               "pools": [
                   {
                       "pool": "192.0.2.1 - 192.0.2.200",
                       "option-data": [
                           {
                               "name": "domain-name-servers",
                               "data": "192.0.2.3"
                            },
                            ...
                       ],
                       ...
                   },
                   ...
               ],
               ...
           },
           ...
       ],
       ...
   }

Options can also be specified in class or host reservation scope. The
current Kea options precedence order is (from most important): host
reservation, pool, subnet, shared network, class, global.

The currently supported standard DHCPv4 options are listed in
:ref:`dhcp4-std-options-list`. "Name" and "Code" are the
values that should be used as a name/code in the option-data structures.
"Type" designates the format of the data; the meanings of the various
types are given in :ref:`dhcp-types`.

When a data field is a string and that string contains the comma (,;
U+002C) character, the comma must be escaped with two backslashes (\;
U+005C). This double escape is required because both the routine
splitting CSV data into fields and JSON use the same escape character; a
single escape (\,) would make the JSON invalid. For example, the string
"foo,bar" must be represented as:

::

   "Dhcp4": {
       "subnet4": [
           {
               "pools": [
                   {
                       "option-data": [
                           {
                               "name": "boot-file-name",
                               "data": "foo\\,bar"
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
value is allowed in such an option. For example, the option time-servers
allows the specification of more than one IPv4 address, enabling clients
to obtain the addresses of multiple NTP servers.

:ref:`dhcp4-custom-options` describes the
configuration syntax to create custom option definitions (formats).
Creation of custom definitions for standard options is generally not
permitted, even if the definition being created matches the actual
option format defined in the RFCs. There is an exception to this rule
for standard options for which Kea currently does not provide a
definition. In order to use such options, a server administrator must
create a definition as described in
:ref:`dhcp4-custom-options` in the "dhcp4" option space. This
definition should match the option format described in the relevant RFC,
but the configuration mechanism will allow any option format as it
currently has no means to validate it.

.. _dhcp4-std-options-list:

.. table:: List of Standard DHCPv4 Options

   +----------------------------------------+------+---------------------------+-------------+-------------+
   | Name                                   | Code | Type                      | Array?      | Returned if |
   |                                        |      |                           |             | not         |
   |                                        |      |                           |             | requested?  |
   +========================================+======+===========================+=============+=============+
   | time-offset                            | 2    | int32                     | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | routers                                | 3    | ipv4-address              | true        | true        |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | time-servers                           | 4    | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | name-servers                           | 5    | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | domain-name-servers                    | 6    | ipv4-address              | true        | true        |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | log-servers                            | 7    | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | cookie-servers                         | 8    | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | lpr-servers                            | 9    | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | impress-servers                        | 10   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | resource-location-servers              | 11   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | boot-size                              | 13   | uint16                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | merit-dump                             | 14   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | domain-name                            | 15   | fqdn                      | false       | true        |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | swap-server                            | 16   | ipv4-address              | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | root-path                              | 17   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | extensions-path                        | 18   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | ip-forwarding                          | 19   | boolean                   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | non-local-source-routing               | 20   | boolean                   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | policy-filter                          | 21   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | max-dgram-reassembly                   | 22   | uint16                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | default-ip-ttl                         | 23   | uint8                     | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | path-mtu-aging-timeout                 | 24   | uint32                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | path-mtu-plateau-table                 | 25   | uint16                    | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | interface-mtu                          | 26   | uint16                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | all-subnets-local                      | 27   | boolean                   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | broadcast-address                      | 28   | ipv4-address              | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | perform-mask-discovery                 | 29   | boolean                   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | mask-supplier                          | 30   | boolean                   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | router-discovery                       | 31   | boolean                   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | router-solicitation-address            | 32   | ipv4-address              | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | static-routes                          | 33   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | trailer-encapsulation                  | 34   | boolean                   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | arp-cache-timeout                      | 35   | uint32                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | ieee802-3-encapsulation                | 36   | boolean                   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | default-tcp-ttl                        | 37   | uint8                     | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | tcp-keepalive-interval                 | 38   | uint32                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | tcp-keepalive-garbage                  | 39   | boolean                   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nis-domain                             | 40   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nis-servers                            | 41   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | ntp-servers                            | 42   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | vendor-encapsulated-options            | 43   | empty                     | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | netbios-name-servers                   | 44   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | netbios-dd-server                      | 45   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | netbios-node-type                      | 46   | uint8                     | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | netbios-scope                          | 47   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | font-servers                           | 48   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | x-display-manager                      | 49   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | dhcp-option-overload                   | 52   | uint8                     | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | dhcp-server-identifier                 | 54   | ipv4-address              | false       | true        |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | dhcp-message                           | 56   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | dhcp-max-message-size                  | 57   | uint16                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | vendor-class-identifier                | 60   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nwip-domain-name                       | 62   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nwip-suboptions                        | 63   | binary                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nisplus-domain-name                    | 64   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nisplus-servers                        | 65   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | tftp-server-name                       | 66   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | boot-file-name                         | 67   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | mobile-ip-home-agent                   | 68   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | smtp-server                            | 69   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | pop-server                             | 70   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nntp-server                            | 71   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | www-server                             | 72   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | finger-server                          | 73   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | irc-server                             | 74   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | streettalk-server                      | 75   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | streettalk-directory-assistance-server | 76   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | user-class                             | 77   | binary                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | slp-directory-agent                    | 78   | record (boolean,          | true        | false       |
   |                                        |      | ipv4-address)             |             |             |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | slp-service-scope                      | 79   | record (boolean, string)  | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nds-server                             | 85   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nds-tree-name                          | 86   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | nds-context                            | 87   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | bcms-controller-names                  | 88   | fqdn                      | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | bcms-controller-address                | 89   | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | client-system                          | 93   | uint16                    | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | client-ndi                             | 94   | record (uint8, uint8,     | false       | false       |
   |                                        |      | uint8)                    |             |             |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | uuid-guid                              | 97   | record (uint8, binary)    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | uap-servers                            | 98   | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | geoconf-civic                          | 99   | binary                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | pcode                                  | 100  | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | tcode                                  | 101  | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | netinfo-server-address                 | 112  | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | netinfo-server-tag                     | 113  | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | default-url                            | 114  | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | auto-config                            | 116  | uint8                     | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | name-service-search                    | 117  | uint16                    | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | subnet-selection                       | 118  | ipv4-address              | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | domain-search                          | 119  | fqdn                      | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | vivco-suboptions                       | 124  | binary                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | vivso-suboptions                       | 125  | binary                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | pana-agent                             | 136  | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-lost                                | 137  | fqdn                      | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | capwap-ac-v4                           | 138  | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | sip-ua-cs-domains                      | 141  | fqdn                      | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | rdnss-selection                        | 146  | record (uint8,            | true        | false       |
   |                                        |      | ipv4-address,             |             |             |
   |                                        |      | ipv4-address, fqdn)       |             |             |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-portparams                          | 159  | record (uint8, psid)      | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-captive-portal                      | 160  | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | option-6rd                             | 212  | record (uint8, uint8,     | true        | false       |
   |                                        |      | ipv6-address,             |             |             |
   |                                        |      | ipv4-address)             |             |             |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-access-domain                       | 213  | fqdn                      | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+

.. _dhcp-types:

.. table:: List of Standard DHCP Option Types

   +-----------------+-------------------------------------------------------+
   | Name            | Meaning                                               |
   +=================+=======================================================+
   | binary          | An arbitrary string of bytes, specified as a set      |
   |                 | of hexadecimal digits.                                |
   +-----------------+-------------------------------------------------------+
   | boolean         | A boolean value with allowed                          |
   |                 | values true or false.                                 |
   +-----------------+-------------------------------------------------------+
   | empty           | No value; data is carried in                          |
   |                 | sub-options.                                          |
   +-----------------+-------------------------------------------------------+
   | fqdn            | Fully qualified domain name (e.g.                     |
   |                 | www.example.com).                                     |
   +-----------------+-------------------------------------------------------+
   | ipv4-address    | IPv4 address in the usual                             |
   |                 | dotted-decimal notation (e.g.                         |
   |                 | 192.0.2.1).                                           |
   +-----------------+-------------------------------------------------------+
   | ipv6-address    | IPv6 address in the usual colon                       |
   |                 | notation (e.g. 2001:db8::1).                          |
   +-----------------+-------------------------------------------------------+
   | ipv6-prefix     | IPv6 prefix and prefix length                         |
   |                 | specified using CIDR notation,                        |
   |                 | e.g. 2001:db8:1::/64. This data                       |
   |                 | type is used to represent an                          |
   |                 | 8-bit field conveying a prefix                        |
   |                 | length and the variable length                        |
   |                 | prefix value.                                         |
   +-----------------+-------------------------------------------------------+
   | psid            | PSID and PSID length separated by                     |
   |                 | a slash, e.g. 3/4 specifies                           |
   |                 | PSID=3 and PSID length=4. In the                      |
   |                 | wire format it is represented by                      |
   |                 | an 8-bit field carrying PSID                          |
   |                 | length (in this case equal to 4)                      |
   |                 | and the 16-bits-long PSID value                       |
   |                 | field (in this case equal to                          |
   |                 | "0011000000000000b" using binary                      |
   |                 | notation). Allowed values for a                       |
   |                 | PSID length are 0 to 16. See `RFC                     |
   |                 | 7597 <https://tools.ietf.org/html/rfc7597>`__         |
   |                 | for details about the PSID wire                       |
   |                 | representation.                                       |
   +-----------------+-------------------------------------------------------+
   | record          | Structured data that may be                           |
   |                 | comprised of any types (except                        |
   |                 | "record" and "empty"). The array                      |
   |                 | flag applies to the last field                        |
   |                 | only.                                                 |
   +-----------------+-------------------------------------------------------+
   | string          | Any text. Please note that Kea                        |
   |                 | will silently discard any                             |
   |                 | terminating/trailing nulls from                       |
   |                 | the end of 'string' options when                      |
   |                 | unpacking received packets. This                      |
   |                 | is in keeping with `RFC 2132,                         |
   |                 | Section                                               |
   |                 | 2 <https://tools.ietf.org/html/rfc2132#section-2>`__. |
   +-----------------+-------------------------------------------------------+
   | tuple           | A length encoded as an 8- (16-                        |
   |                 | for DHCPv6) bit unsigned integer                      |
   |                 | followed by a string of this                          |
   |                 | length.                                               |
   +-----------------+-------------------------------------------------------+
   | uint8           | 8-bit unsigned integer with                           |
   |                 | allowed values 0 to 255.                              |
   +-----------------+-------------------------------------------------------+
   | uint16          | 16-bit unsigned integer with                          |
   |                 | allowed values 0 to 65535.                            |
   +-----------------+-------------------------------------------------------+
   | uint32          | 32-bit unsigned integer with                          |
   |                 | allowed values 0 to 4294967295.                       |
   +-----------------+-------------------------------------------------------+
   | int8            | 8-bit signed integer with allowed                     |
   |                 | values -128 to 127.                                   |
   +-----------------+-------------------------------------------------------+
   | int16           | 16-bit signed integer with                            |
   |                 | allowed values -32768 to 32767.                       |
   +-----------------+-------------------------------------------------------+
   | int32           | 32-bit signed integer with                            |
   |                 | allowed values -2147483648 to                         |
   |                 | 2147483647.                                           |
   +-----------------+-------------------------------------------------------+

.. _dhcp4-custom-options:

Custom DHCPv4 Options
---------------------

Kea supports custom (non-standard) DHCPv4 options. Assume that we want
to define a new DHCPv4 option called "foo" which will have code 222
and will convey a single, unsigned, 32-bit integer value. We can define
such an option by putting the following entry in the configuration file:

::

   "Dhcp4": {
       "option-def": [
           {
               "name": "foo",
               "code": 222,
               "type": "uint32",
               "array": false,
               "record-types": "",
               "space": "dhcp4",
               "encapsulate": ""
           }, ...
       ],
       ...
   }

The ``false`` value of the ``array`` parameter determines that the
option does NOT comprise an array of "uint32" values but is, instead, a
single value. Two other parameters have been left blank:
``record-types`` and ``encapsulate``. The former specifies the
comma-separated list of option data fields, if the option comprises a
record of data fields. The ``record-types`` value should be non-empty if
``type`` is set to "record"; otherwise it must be left blank. The latter
parameter specifies the name of the option space being encapsulated by
the particular option. If the particular option does not encapsulate any
option space, the parameter should be left blank. Note that the ``option-def``
configuration statement only defines the format of an option and does
not set its value(s).

The ``name``, ``code``, and ``type`` parameters are required; all others
are optional. The ``array`` default value is ``false``. The
``record-types`` and ``encapsulate`` default values are blank (i.e. "").
The default ``space`` is "dhcp4".

Once the new option format is defined, its value is set in the same way
as for a standard option. For example, the following commands set a
global value that applies to all subnets.

::

   "Dhcp4": {
       "option-data": [
           {
               "name": "foo",
               "code": 222,
               "space": "dhcp4",
               "csv-format": true,
               "data": "12345"
           }, ...
       ],
       ...
   }

New options can take more complex forms than simple use of primitives
(uint8, string, ipv4-address, etc.); it is possible to define an option
comprising a number of existing primitives.

For example, assume we want to define a new option that will consist of
an IPv4 address, followed by an unsigned 16-bit integer, followed by a
boolean value, followed by a text string. Such an option could be
defined in the following way:

::

   "Dhcp4": {
       "option-def": [
           {
               "name": "bar",
               "code": 223,
               "space": "dhcp4",
               "type": "record",
               "array": false,
               "record-types": "ipv4-address, uint16, boolean, string",
               "encapsulate": ""
           }, ...
       ],
       ...
   }

The ``type`` is set to "record" to indicate that the option contains
multiple values of different types. These types are given as a
comma-separated list in the ``record-types`` field and should be ones
from those listed in :ref:`dhcp-types`.

The values of the option are set in an ``option-data`` statement as follows:

::

   "Dhcp4": {
       "option-data": [
           {
               "name": "bar",
               "space": "dhcp4",
               "code": 223,
               "csv-format": true,
               "data": "192.0.2.100, 123, true, Hello World"
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

   "Dhcp4": {
       "option-def": [
           {
               "name": "bar",
               "code": 223,
               "space": "dhcp4",
               "type": "record",
               "array": true,
               "record-types": "ipv4-address, uint16",
               "encapsulate": ""
           }, ...
       ],
       ...
   }

The new option content is one IPv4 address followed by one or more 16-
bit unsigned integers.

.. note::

   In general, boolean values are specified as ``true`` or ``false``,
   without quotes. Some specific boolean parameters may also accept
   ``"true"``, ``"false"``, ``0``, ``1``, ``"0"``, and ``"1"``.

..

.. note::

   Numbers can be specified in decimal or hexadecimal format. The
   hexadecimal format can be either plain (e.g. abcd) or prefixed with
   0x (e.g. 0xabcd).

.. _dhcp4-private-opts:

DHCPv4 Private Options
----------------------

Options with a code between 224 and 254 are reserved for private use.
They can be defined at the global scope or at the client-class local
scope; this allows option definitions to be used depending on context
and option data to be set accordingly. For instance, to configure an old
PXEClient vendor:

::

   "Dhcp4": {
       "client-classes": [
           {
               "name": "pxeclient",
               "test": "option[vendor-class-identifier].text == 'PXEClient'",
               "option-def": [
                   {
                       "name": "configfile",
                       "code": 209,
                       "type": "string"
                   }
               ],
               ...
           }, ...
       ],
       ...
   }

As the Vendor-Specific Information option (code 43) has vendor-specific
format, i.e. can carry either raw binary value or sub-options, this
mechanism is available for this option too.

In the following example taken from a real configuration, two vendor
classes use the option 43 for different and incompatible purposes:

::

   "Dhcp4": {
       "option-def": [
           {
               "name": "cookie",
               "code": 1,
               "type": "string",
               "space": "APC"
           },
           {
               "name": "mtftp-ip",
               "code": 1,
               "type": "ipv4-address",
               "space": "PXE"
           },
           ...
       ],
       "client-classes": [
           {
               "name": "APC",
               "test": "(option[vendor-class-identifier].text == 'APC'",
               "option-def": [
                   {
                       "name": "vendor-encapsulated-options",
                       "type": "empty",
                       "encapsulate": "APC"
                   }
               ],
               "option-data": [
                   {
                       "name": "cookie",
                       "space": "APC",
                       "data": "1APC"
                   },
                   {
                       "name": "vendor-encapsulated-options"
                   },
                   ...
               ],
               ...
           },
           {
               "name": "PXE",
               "test": "(option[vendor-class-identifier].text == 'PXE'",
               "option-def": [
                   {
                       "name": "vendor-encapsulated-options",
                       "type": "empty",
                       "encapsulate": "PXE"
                   }
               ],
               "option-data": [
                   {
                       "name": "mtftp-ip",
                       "space": "PXE",
                       "data": "0.0.0.0"
                   },
                   {
                       "name": "vendor-encapsulated-options"
                   },
                   ...
               ],
               ...
           },
           ...
       ],
       ...
   }

The definition used to decode a VSI option is:

1. The local definition of a client class the incoming packet belongs
   to;

2. If none, the global definition;

3. If none, the last-resort definition described in the next section,
   :ref:`dhcp4-vendor-opts` (backward-compatible with previous Kea versions).

..

.. note::

   This last-resort definition for the Vendor-Specific Information
   option (code 43) is not compatible with a raw binary value. When
   there are known cases where a raw binary value will be used, a
   client class must be defined with both a classification expression
   matching these cases and an option definition for the VSI option with
   a binary type and no encapsulation.

.. note::

   By default, in the Vendor-Specific Information option (code 43)
   sub-option code 0 and 255 mean PAD and END respectively according to
   `RFC 2132 <https://tools.ietf.org/html/rfc2132>`_. In other words, the
   sub-option code values of 0 and 255 are reserved. Kea does, however,
   allow you to define sub-option codes from 0 to 255.  If you define
   sub-options with codes 0 and/or 255, bytes with that value will
   no longer be treated as a PAD or an END, but as the sub-option code
   when parsing a VSI option in an incoming query.

   Option 43 input processing (aka unpacking) is deferred so that it
   happens after classification.  This means you cannot classify clients
   using option 43 suboptions.  The definition used to unpack option 43
   is determined as follows:

   - If defined at the global scope this definition is used
   - If defined at client class scope and the packet belongs to this
     class the client class definition is used
   - If not defined at global scope nor in a client class to which the
     packet belongs, the built-in last resort definition is used. This
     definition only says the sub-option space is
     "vendor-encapsulated-options-space"

   The output definition selection  is a bit simpler:

   - If the packet belongs to a client class which defines the option
     43 use this definition
   - If defined at the global scope use this definition
   - Otherwise use the built-in last resot definition.

   Note as they use a specific/per vendor option space the sub-options
   are defined at the global scope.

.. note::

   Option definitions in client classes are allowed only for this
   limited option set (codes 43 and from 224 to 254), and only for
   DHCPv4.

.. _dhcp4-vendor-opts:

DHCPv4 Vendor-Specific Options
------------------------------

Currently there are two option spaces defined for the DHCPv4 daemon:
"dhcp4" (for the top-level DHCPv4 options) and
"vendor-encapsulated-options-space", which is empty by default but in
which options can be defined. Those options are carried in the
Vendor-Specific Information option (code 43). The following examples
show how to define an option "foo" with code 1 that
comprises an IPv4 address, an unsigned 16-bit integer, and a string. The
"foo" option is conveyed in a Vendor-Specific Information option.

The first step is to define the format of the option:

::

   "Dhcp4": {
       "option-def": [
           {
               "name": "foo",
               "code": 1,
               "space": "vendor-encapsulated-options-space",
               "type": "record",
               "array": false,
               "record-types": "ipv4-address, uint16, string",
               "encapsulate": ""
           }
       ],
       ...
   }

(Note that the option space is set to
``vendor-encapsulated-options-space``.) Once the option format is defined,
the next step is to define actual values for that option:

::

   "Dhcp4": {
       "option-data": [
           {
               "name": "foo",
               "space": "vendor-encapsulated-options-space",
               "code": 1,
               "csv-format": true,
               "data": "192.0.2.3, 123, Hello World"
           }
       ],
       ...
   }

We also include the Vendor-Specific Information option, the option that
conveys our suboption "foo". This is required; otherwise, the option
will not be included in messages sent to the client.

::

   "Dhcp4": {
       "option-data": [
           {
               "name": "vendor-encapsulated-options"
           }
       ],
       ...
   }

Alternatively, the option can be specified using its code.

::

   "Dhcp4": {
       "option-data": [
           {
               "code": 43
           }
       ],
       ...
   }

Another popular option that is often somewhat imprecisely called "vendor
option" is option 125. Its proper name is vendor-independent
vendor-specific information option or vivso. The idea behind those
options is that each vendor has its own unique set of options with their
own custom formats. The vendor is identified by a 32-bit unsigned integer
called enterprise-id or vendor-id. For example, vivso with vendor-id
4491 represents DOCSIS options, and they are often seen
when dealing with cable modems.

In Kea each vendor is represented by its own vendor space. Since there
are hundreds of vendors and sometimes they use different option
definitions for different hardware, it's impossible for Kea to support
them all out of the box. Fortunately, it's easy to define support for
new vendor options. Let's take an example of the Genexis home gateway. This
device requires sending the vivso 125 option with a suboption 2 that
contains a string with the TFTP server URL. To support such a device, three
steps are needed: first, we need to define option definitions that will
explain how the option is supposed to be formed. Second, we will need to
define option values. Third, we will need to tell Kea when to send those
specific options. This last step will be accomplished with client
classification.

An example snippet of a configuration could look similar to the
following:

::

   {
       // First, we need to define that the suboption 2 in vivso option for
       // vendor-id 25167 has a specific format (it's a plain string in this example).
       // After this definition, we can specify values for option tftp.
       "option-def": [
       {
           // We define a short name, so the option can be referenced by name.
           // The option has code 2 and resides within vendor space 25167.
           // Its data is a plain string.
           "name": "tftp",
           "code": 2,
           "space": "vendor-25167",
           "type": "string"
       } ],

       "client-classes": [
       {
           // We now need to tell Kea how to recognize when to use vendor space 25167.
           // Usually we can use a simple expression, such as checking if the device
           // sent a vivso option with specific vendor-id, e.g. "vendor[4491].exists".
           // Unfortunately, Genexis is a bit unusual in this aspect, because it
           // doesn't send vivso. In this case we need to look into the vendor class
           // (option code 60) and see if there's a specific string that identifies
           // the device.
           "name": "cpe_genexis",
           "test": "substring(option[60].hex,0,7) == 'HMC1000'",

           // Once the device is recognized, we want to send two options:
           // the vivso option with vendor-id set to 25167, and a suboption 2.
           "option-data": [
               {
                   "name": "vivso-suboptions",
                   "data": "25167",
                   "encapsulate": "vendor-25167"
               },

               // The suboption 2 value is defined as any other option. However,
               // we want to send this suboption 2, even when the client didn't
               // explicitly request it (often there is no way to do that for
               // vendor options). Therefore we use always-send to force Kea
               // to always send this option when 25167 vendor space is involved.
               {
                   "name": "tftp",
                   "space": "vendor-25167",
                   "data": "tftp://192.0.2.1/genexis/HMC1000.v1.3.0-R.img",
                   "always-send": true
               }
           ]
       } ]
   }

By default Kea sends back
only those options that are requested by a client, unless there are
protocol rules that tell the DHCP server to always send an option. This
approach works nicely for most cases and avoids problems with clients
refusing responses with options they don't understand. Unfortunately,
this is more complex when we consider vendor options. Some vendors (such
as docsis, identified by vendor option 4491) have a mechanism to
request specific vendor options and Kea is able to honor those.
Unfortunately, for many other vendors, such as Genexis (25167) as discussed
above, Kea does not have such a mechanism, so it can't send any
sub-options on its own. To solve this issue, we came up with the concept of
persistent options. Kea can be told to always send options, even if the
client did not request them. This can be achieved by adding
``"always-send": true`` to the option definition. Note that in this
particular case an option is defined in vendor space 25167. With the
"always-send" enabled, the option will be sent every time there is a
need to deal with vendor space 25167.

Another possibility is to redefine the option; see :ref:`dhcp4-private-opts`.

.. _dhcp4-option-spaces:

Nested DHCPv4 Options (Custom Option Spaces)
--------------------------------------------

It is sometimes useful to define a completely new option space, such as
when a user creates a new option in the standard option space
("dhcp4") and wants this option to convey sub-options. Since they are in
a separate space, sub-option codes will have a separate numbering scheme
and may overlap with the codes of standard options.

Note that the creation of a new option space is not required when
defining sub-options for a standard option, because one is created by
default if the standard option is meant to convey any sub-options (see
:ref:`dhcp4-vendor-opts`).

Assume that we want to have a DHCPv4 option called "container" with code
222 that conveys two sub-options with codes 1 and 2. First we need to
define the new sub-options:

::

   "Dhcp4": {
       "option-def": [
           {
               "name": "subopt1",
               "code": 1,
               "space": "isc",
               "type": "ipv4-address",
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
               "array": false,
               "encapsulate": ""
           }
       ],
       ...
   }

Note that we have defined the options to belong to a new option space
(in this case, "isc").

The next step is to define a regular DHCPv4 option with the desired code
and specify that it should include options from the new option space:

::

   "Dhcp4": {
       "option-def": [
           ...,
           {
               "name": "container",
               "code": 222,
               "space": "dhcp4",
               "type": "empty",
               "array": false,
               "record-types": "",
               "encapsulate": "isc"
           }
       ],
       ...
   }

The name of the option space in which the sub-options are defined is set
in the ``encapsulate`` field. The ``type`` field is set to ``empty``, to
indicate that this option does not carry any data other than
sub-options.

Finally, we can set values for the new options:

::

   "Dhcp4": {
       "option-data": [
           {
               "name": "subopt1",
               "code": 1,
               "space": "isc",
               "data": "192.0.2.3"
           },
           }
               "name": "subopt2",
               "code": 2,
               "space": "isc",
               "data": "Hello world"
           },
           {
               "name": "container",
               "code": 222,
               "space": "dhcp4"
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

.. _dhcp4-option-data-defaults:

Unspecified Parameters for DHCPv4 Option Configuration
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
   particular option have a definition (either as a standard option
   or an administrator-created definition for the option using an
   'option-def' structure), as the option definition associates an
   option with a particular name. It is possible to configure an option
   for which there is no definition (unspecified option format).
   Configuration of such options requires the use of the option code.

-  ``space`` - if the option space is unspecified it will default to
   'dhcp4', which is an option space holding standard DHCPv4
   options.

-  ``data`` - if the option data is unspecified it defaults to an empty
   value. The empty value is mostly used for the options which have no
   payload (boolean options), but it is legal to specify empty values
   for some options which carry variable-length data and for which the
   specification allows a length of 0. For such options, the
   data parameter may be omitted in the configuration.

-  ``csv-format`` - if this value is not specified, the server will
   assume that the option data is specified as a list of comma-separated
   values to be assigned to individual fields of the DHCP option.

.. _dhcp4-stateless-configuration:

Stateless Configuration of DHCPv4 Clients
-----------------------------------------

The DHCPv4 server supports the stateless client configuration whereby
the client has an IP address configured (e.g. using manual
configuration) and only contacts the server to obtain other
configuration parameters, such as addresses of DNS servers. In order to
obtain the stateless configuration parameters, the client sends the
DHCPINFORM message to the server with the "ciaddr" set to the address
that the client is currently using. The server unicasts the DHCPACK
message to the client that includes the stateless configuration
("yiaddr" not set).

The server will respond to the DHCPINFORM when the client is associated
with a subnet defined in the server's configuration. An example subnet
configuration will look like this:

::

   "Dhcp4": {
       "subnet4": [
           {
               "subnet": "192.0.2.0/24"
               "option-data": [ {
                   "name": "domain-name-servers",
                   "code": 6,
                   "data": "192.0.2.200,192.0.2.201",
                   "csv-format": true,
                   "space": "dhcp4"
               } ]
           }
       ]
   }

This subnet specifies the single option which will be included in the
DHCPACK message to the client in response to DHCPINFORM. Note that the
subnet definition does not require the address pool configuration if it
will be used solely for the stateless configuration.

This server will associate the subnet with the client if one of the
following conditions is met:

-  The DHCPINFORM is relayed and the giaddr matches the configured
   subnet.

-  The DHCPINFORM is unicast from the client and the ciaddr matches the
   configured subnet.

-  The DHCPINFORM is unicast from the client and the ciaddr is not set,
   but the source address of the IP packet matches the configured
   subnet.

-  The DHCPINFORM is not relayed and the IP address on the interface on
   which the message is received matches the configured subnet.

.. _dhcp4-client-classifier:

Client Classification in DHCPv4
-------------------------------

The DHCPv4 server includes support for client classification. For a
deeper discussion of the classification process see :ref:`classify`.

In certain cases it is useful to configure the server to differentiate
between DHCP client types and treat them accordingly. Client
classification can be used to modify the behavior of almost any part of
the DHCP message processing. Kea currently offers client classification
via private options and option 43 deferred unpacking; subnet selection;
pool selection; assignment of different options; and, for cable modems,
specific options for use with the TFTP server address and the boot file
field.

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
on access based on class information is also available at the pool
level; see :ref:`classification-pools`, within a subnet. This is
useful when segregating clients belonging to the same subnet into
different address ranges.

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
information. When the incoming packet is in the special class, "DROP",
it is dropped and an debug message logged.
The next step is to evaluate class expressions depending on
the built-in "KNOWN"/"UNKNOWN" classes after host reservation lookup,
using them for pool selection and assigning classes from host
reservations. The list of required classes is then built and each class
of the list has its expression evaluated; when it returns "true" the
packet is added as a member of the class. The last step is to assign
options, again possibly based on the class information. More complete
and detailed information is available in :ref:`classify`.

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

Setting Fixed Fields in Classification
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is possible to specify that clients belonging to a particular class
should receive packets with specific values in certain fixed fields. In
particular, three fixed fields are supported: ``next-server`` (conveys
an IPv4 address, which is set in the siaddr field), ``server-hostname``
(conveys a server hostname, can be up to 64 bytes long, and is sent in
the sname field) and ``boot-file-name`` (conveys the configuration file,
can be up to 128 bytes long, and is sent using the file field).

Obviously, there are many ways to assign clients to specific classes,
but for PXE clients the client architecture type option (code 93)
seems to be particularly suited to make the distinction. The following
example checks whether the client identifies itself as a PXE device with
architecture EFI x86-64, and sets several fields if it does. See
`Section 2.1 of RFC
4578 <https://tools.ietf.org/html/rfc4578#section-2.1>`__) or the
client documentation for specific values.

::

   "Dhcp4": {
       "client-classes": [
           {
               "name": "ipxe_efi_x64",
               "test": "option[93].hex == 0x0009",
               "next-server": "192.0.2.254",
               "server-hostname": "hal9000",
               "boot-file-name": "/dev/null"
           },
           ...
       ],
       ...
             }

If there are multiple classes defined and an incoming packet is matched
to multiple classes, the class that is evaluated first is used.

.. note::

   The classes are ordered as specified in the configuration.

Using Vendor Class Information in Classification
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The server checks whether an incoming packet includes the vendor class
identifier option (60). If it does, the content of that option is
prepended with "VENDOR_CLASS\_", and it is interpreted as a class. For
example, modern cable modems will send this option with value
"docsis3.0" and as a result the packet will belong to class
"VENDOR_CLASS_docsis3.0".

.. note::

   Certain special actions for clients in VENDOR_CLASS_docsis3.0 can be
   achieved by defining VENDOR_CLASS_docsis3.0 and setting its
   next-server and boot-file-name values appropriately.

This example shows a configuration using an automatically generated
"VENDOR_CLASS\_" class. The administrator of the network has decided that
addresses from range 192.0.2.10 to 192.0.2.20 are going to be managed by
the Dhcp4 server and only clients belonging to the docsis3.0 client
class are allowed to use that pool.

::

   "Dhcp4": {
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "client-class": "VENDOR_CLASS_docsis3.0"
           }
       ],
       ...
   }

Defining and Using Custom Classes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following example shows how to configure a class using an expression
and a subnet using that class. This configuration defines the class
named "Client_foo". It is comprised of all clients whose client ids
(option 61) start with the string "foo". Members of this class will be
given addresses from 192.0.2.10 to 192.0.2.20 and the addresses of their
DNS servers set to 192.0.2.1 and 192.0.2.2.

::

   "Dhcp4": {
       "client-classes": [
           {
               "name": "Client_foo",
               "test": "substring(option[61].hex,0,3) == 'foo'",
               "option-data": [
                   {
                       "name": "domain-name-servers",
                       "code": 6,
                       "space": "dhcp4",
                       "csv-format": true,
                       "data": "192.0.2.1, 192.0.2.2"
                   }
               ]
           },
           ...
       ],
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "client-class": "Client_foo"
           },
           ...
       ],
       ...
   }

.. _dhcp4-required-class:

Required Classification
~~~~~~~~~~~~~~~~~~~~~~~

In some cases it is useful to limit the scope of a class to a
shared network, subnet, or pool. There are two parameters which are used
to limit the scope of the class by instructing the server to evaluate test
expressions when required.

The first one is the per-class ``only-if-required`` flag, which is false
by default. When it is set to ``true``, the test expression of the class
is not evaluated at the reception of the incoming packet but later, and
only if the class evaluation is required.

The second is ``require-client-classes``, which takes a list of class
names and is valid in shared-network, subnet, and pool scope. Classes in
these lists are marked as required and evaluated after selection of this
specific shared network/subnet/pool and before output option processing.

In this example, a class is assigned to the incoming packet when the
specified subnet is used:

::

   "Dhcp4": {
       "client-classes": [
          {
              "name": "Client_foo",
              "test": "member('ALL')",
              "only-if-required": true
          },
          ...
       ],
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "require-client-classes": [ "Client_foo" ],
               ...
           },
           ...
       ],
       ...
   }

Required evaluation can be used to express complex dependencies like subnet membership. It can also be used to reverse the
precedence; if an option-data is set in a subnet, it takes precedence
over an option-data in a class. If the option-data is moved to a
required class and required in the subnet, a class evaluated earlier
may take precedence.

Required evaluation is also available at the shared-network and pool levels.
The order in which required classes are considered is: shared-network,
subnet, and pool, i.e. in the opposite order in which option-data is
processed.

.. _dhcp4-ddns-config:

DDNS for DHCPv4
---------------

As mentioned earlier, kea-dhcp4 can be configured to generate requests
to the DHCP-DDNS server, kea-dhcp-ddns, (referred to herein as "D2") to
update DNS entries. These requests are known as Name Change Requests or
NCRs. Each NCR contains the following information:

1. Whether it is a request to add (update) or remove DNS entries

2. Whether the change requests forward DNS updates (A records), reverse
   DNS updates (PTR records), or both

3. The Fully Qualified Domain Name (FQDN), lease address, and DHCID
   (information identifying the client associated with the FQDN)

Prior to Kea 1.7.1, all parameters for controlling DDNS were within the
global ``dhcp-ddns`` section of the kea-dhcp4.  Beginning with Kea 1.7.1
DDNS related parameters were split into two groups:

1. Connectivity Parameters
    These are parameters which specify where and how kea-dhcp4 connects to
    and communicates with D2.  These parameters can only be specified
    within the top-level ``dhcp-ddns`` section in the kea-dhcp4
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

The default configuration would appear as follows:

::

   "Dhcp4": {
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
        "hostname-char-set": "",
        "hostname-char-replacement": ""
        ...
   }

As of Kea 1.7.1, there are two parameters which determine if kea-dhcp4
can generate DDNS requests to D2.  The existing, ``dhcp-ddns:enable-updates``
parameter which now only controls whether kea-dhcp4 connects to D2.
And the new behavioral parameter, ``ddns-send-updates``, which determines
if DDNS updates are enabled at a given level (i.e global, shared-network,
or subnet).  The following table shows how the two parameters function
together:

.. table:: Enabling and Disabling DDNS Updates

   +-----------------+--------------------+-------------------------------+
   | dhcp-ddns:      | Global             | Outcome                       |
   | enable-updates  | ddns-send-udpates  |                               |
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

.. _dhcpv4-d2-io-config:

DHCP-DDNS Server Connectivity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For NCRs to reach the D2 server, kea-dhcp4 must be able to communicate
with it. kea-dhcp4 uses the following configuration parameters to
control this communication:

-  ``enable-updates`` - As of Kea 1.7.1, this parameter only enables
    connectivity to kea-dhcp-ddns such that DDNS updates can be constructed
    and sent.  It must be true for NCRs to be generated and sent to D2.
    It defaults to false.

-  ``server-ip`` - the IP address on which D2 listens for requests. The
   default is the local loopback interface at address 127.0.0.1.
   Either an IPv4 or IPv6 address may be specified.

-  ``server-port`` - the port on which D2 listens for requests. The default
   value is 53001.

-  ``sender-ip`` - the IP address which kea-dhcp4 uses to send requests to
   D2. The default value is blank, which instructs kea-dhcp4 to select a
   suitable address.

-  ``sender-port`` - the port which kea-dhcp4 uses to send requests to D2.
   The default value of 0 instructs kea-dhcp4 to select a suitable port.

-  ``max-queue-size`` - the maximum number of requests allowed to queue
   waiting to be sent to D2. This value guards against requests
   accumulating uncontrollably if they are being generated faster than
   they can be delivered. If the number of requests queued for
   transmission reaches this value, DDNS updating will be turned off
   until the queue backlog has been sufficiently reduced. The intent is
   to allow the kea-dhcp4 server to continue lease operations without
   running the risk that its memory usage grows without limit. The
   default value is 1024.

-  ``ncr-protocol`` - the socket protocol to use when sending requests to
   D2. Currently only UDP is supported.

-  ``ncr-format`` - the packet format to use when sending requests to D2.
   Currently only JSON format is supported.

By default, kea-dhcp-ddns is assumed to be running on the same machine
as kea-dhcp4, and all of the default values mentioned above should be
sufficient. If, however, D2 has been configured to listen on a different
address or port, these values must be altered accordingly. For example,
if D2 has been configured to listen on 192.168.1.10 port 900, the
following configuration is required:

::

   "Dhcp4": {
       "dhcp-ddns": {
           "server-ip": "192.168.1.10",
           "server-port": 900,
           ...
       },
       ...
   }

.. _dhcpv4-d2-rules-config:

When Does the kea-dhcp4 Server Generate a DDNS Request?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

kea-dhcp4 follows the behavior prescribed for DHCP servers in `RFC
4702 <https://tools.ietf.org/html/rfc4702>`__. It is important to keep in
mind that kea-dhcp4 makes the initial decision of when and what to
update and forwards that information to D2 in the form of NCRs. Carrying
out the actual DNS updates and dealing with such things as conflict
resolution are within the purview of D2 itself
(see :ref:`dhcp-ddns-server`). This section describes when kea-dhcp4
will generate NCRs and the configuration parameters that can be used to
influence this decision. It assumes that both the connectivity parameter,
``enable-updates`` and the behavioral parameter ``ddns-send-updates``,
are true.

In general, kea-dhcp4 will generate DDNS update requests when:

1. A new lease is granted in response to a DHCPREQUEST;

2. An existing lease is renewed but the FQDN associated with it has
   changed; or

3. An existing lease is released in response to a DHCPRELEASE.

In the second case, lease renewal, two DDNS requests will be issued: one
request to remove entries for the previous FQDN, and a second request to
add entries for the new FQDN. In the last case, a lease release, a
single DDNS request to remove its entries will be made.

As for the first case, the decisions involved when granting a new lease are
more complex. When a new lease is granted, kea-dhcp4 will generate a
DDNS update request if the DHCPREQUEST contains either the FQDN option
(code 81) or the Host Name option (code 12). If both are present, the
server will use the FQDN option. By default, kea-dhcp4 will respect the
FQDN N and S flags specified by the client as shown in the following
table:

.. table:: Default FQDN Flag Behavior

   +------------+---------------------+-----------------+-------------+
   | Client     | Client Intent       | Server Response | Server      |
   | Flags:N-S  |                     |                 | Flags:N-S-O |
   +============+=====================+=================+=============+
   | 0-0        | Client wants to     | Server          | 1-0-0       |
   |            | do forward          | generates       |             |
   |            | updates, server     | reverse-only    |             |
   |            | should do           | request         |             |
   |            | reverse updates     |                 |             |
   +------------+---------------------+-----------------+-------------+
   | 0-1        | Server should       | Server          | 0-1-0       |
   |            | do both forward     | generates       |             |
   |            | and reverse         | request to      |             |
   |            | updates             | update both     |             |
   |            |                     | directions      |             |
   +------------+---------------------+-----------------+-------------+
   | 1-0        | Client wants no     | Server does not | 1-0-0       |
   |            | updates done        | generate a      |             |
   |            |                     | request         |             |
   +------------+---------------------+-----------------+-------------+

The first row in the table above represents "client delegation." Here
the DHCP client states that it intends to do the forward DNS updates and
the server should do the reverse updates. By default, kea-dhcp4 will
honor the client's wishes and generate a DDNS request to the D2 server
to update only reverse DNS data. The parameter
``ddns-override-client-update`` can be used to instruct the server to
override client delegation requests. When this parameter is "true",
kea-dhcp4 will disregard requests for client delegation and generate a
DDNS request to update both forward and reverse DNS data. In this case,
the N-S-O flags in the server's response to the client will be 0-1-1
respectively.

(Note that the flag combination N=1, S=1 is prohibited according to `RFC
4702 <https://tools.ietf.org/html/rfc4702>`__. If such a combination is
received from the client, the packet will be dropped by kea-dhcp4.)

To override client delegation, set the following values in the
configuration file:

::

    "Dhcp4": {
        ...
        "ddns-override-client-update": true,
        ...
    }

The third row in the table above describes the case in which the client
requests that no DNS updates be done. The parameter,
``ddns-override-no-update``, can be used to instruct the server to disregard
the client's wishes. When this parameter is true, kea-dhcp4 will
generate DDNS update requests to kea-dhcp-ddns even if the client
requests that no updates be done. The N-S-O flags in the server's
response to the client will be 0-1-1.

To override client delegation, issue the following commands:

::

   "Dhcp4": {
       ...
       "ddns-override-no-update": true,
       ...
   }

kea-dhcp4 will always generate DDNS update requests if the client
request only contains the Host Name option. In addition, it will include
an FQDN option in the response to the client with the FQDN N-S-O flags
set to 0-1-0 respectively. The domain name portion of the FQDN option
will be the name submitted to D2 in the DDNS update request.

.. _dhcpv4-fqdn-name-generation:

kea-dhcp4 Name Generation for DDNS Update Requests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each Name Change Request must of course include the fully qualified domain
name whose DNS entries are to be affected. kea-dhcp4 can be configured
to supply a portion or all of that name, based upon what it receives
from the client in the DHCPREQUEST.

The default rules for constructing the FQDN that will be used for DNS
entries are:

1. If the DHCPREQUEST contains the client FQDN option, take the
   candidate name from there; otherwise, take it from the Host Name
   option.

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

   Note that in early versions of Kea, this parameter was a boolean and permitted only
   values of ``true`` and ``false``. Boolean values have been deprecated
   and are no longer accepted. Administrators currently using booleans
   must replace them with the desired mode name. A value of ``true``
   maps to ``"when-present"``, while ``false`` maps to ``"never"``.

For example, to instruct kea-dhcp4 to always generate the FQDN for a
client, set the parameter ``ddns-replace-client-name`` to ``always`` as
follows:

::

   "Dhcp4": {
        ...
        "ddns-replace-client-name": "always",
        ...
   }

The prefix used in the generation of an FQDN is specified by the
``generated-prefix`` parameter. The default value is "myhost". To alter
its value, simply set it to the desired string:

::

   "Dhcp4": {
       ...
        "ddns-generated-prefix": "another.host",
       ...
   }

The suffix used when generating an FQDN, or when qualifying a partial
name, is specified by the ``ddns-qualifying-suffix`` parameter.  It is
strongly recommended that you supply a value for qualifying prefix when
DDNS updates are enabled.  For obvious reasons, we cannot supply a
meaningful default.

::

    "Dhcp4": {
        ...
        "ddns-qualifying-suffix": "foo.example.org",
        ...
    }

When generating a name, kea-dhcp4 will construct the name in the format:

[**ddns-generated-prefix**]-[**address-text**].[**ddns-qualifying-suffix**].

where **address-text** is simply the lease IP address converted to a
hyphenated string. For example, if the lease address is 172.16.1.10, the
qualifying suffix "example.com", and the default value is used for
``ddns-generated-prefix``, the generated FQDN is:

**myhost-172-16-1-10.example.com.**

.. _dhcp4-host-name-sanitization:

Sanitizing Client Host Name and FQDN Names
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Some DHCP clients may provide values in the Host Name
option (option code 12) or FQDN option (option code 81) that contain
undesirable characters. It is possible to configure kea-dhcp4 to
sanitize these values. The most typical use case is ensuring that only
characters that are permitted by RFC 1035 be included: A-Z, a-z, 0-9,
and '-'. This may be accomplished with the following two parameters:

-  ``hostname-char-set`` - a regular expression describing the invalid
   character set. This can be any valid, regular expression using POSIX
   extended expression syntax.  Embedded nuls (0x00) will always be
   considered an invalid character to be replaced (or omitted).

-  ``hostname-char-replacement`` - a string of zero or more characters
   with which to replace each invalid character in the host name.  An empty
   string and will cause invalid characters to be OMITTED rather than replaced.

.. note::

    Starting with Kea 1.7.5, the default values are as follows:

    -   "hostname-char-set": "[^A-Za-z0-9.-]",
    -   "hostname-char-replacement": ""

    This enables sanitizing and will omit any character that is not
    a letter,digit, hyphen, dot or nul.

The following configuration will replace anything other than a letter,
digit, hyphen, or dot with the letter 'x':
::

   "Dhcp4": {
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
   It is difficult to devise a scheme that works well in all cases, for
   both Host Name and FQDN options. Administrators who find they have clients
   with odd corner cases of character combinations that cannot be
   readily handled with this mechanism should consider writing a
   hook that can carry out sufficiently complex logic to address their
   needs.

   If clients include domain names in the Host Name option and the administrator
   wants these preserved, they will need to make sure that the dot, '.',
   is considered a valid character by the hostname-char-set expression,
   such as this: "[^A-Za-z0-9.-]". This will not affect dots in FQDN
   Option values. When scrubbing FQDNs, dots are treated as delimiters
   and used to separate the option value into individual domain labels
   that are scrubbed and then re-assembled.

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

   Since the 1.6.0 Kea release it is possible to specify hostname-char-set
   and/or hostname-char-replacement at the global scope. This allows
   to sanitize host names without requiring a dhcp-ddns entry. When
   a hostname-char parameter is defined at the global scope and
   in a dhcp-ddns entry the second (local) value is used.

.. _dhcp4-next-server:

Next Server (siaddr)
--------------------

In some cases, clients want to obtain configuration from a TFTP server.
Although there is a dedicated option for it, some devices may use the
siaddr field in the DHCPv4 packet for that purpose. That specific field
can be configured using the ``next-server`` directive. It is possible to
define it in the global scope or for a given subnet only. If both are
defined, the subnet value takes precedence. The value in subnet can be
set to 0.0.0.0, which means that ``next-server`` should not be sent. It
may also be set to an empty string, which means the same as if it were
not defined at all; that is, use the global value.

The ``server-hostname`` (which conveys a server hostname, can be up to
64 bytes long, and will be sent in the sname field) and
``boot-file-name`` (which conveys the configuration file, can be up to
128 bytes long, and will be sent using the file field) directives are
handled the same way as ``next-server``.

::

   "Dhcp4": {
       "next-server": "192.0.2.123",
       "boot-file-name": "/dev/null",
       ...,
       "subnet4": [
           {
               "next-server": "192.0.2.234",
               "server-hostname": "some-name.example.org",
               "boot-file-name": "bootfile.efi",
               ...
           }
       ]
   }

.. _dhcp4-echo-client-id:

Echoing Client-ID (RFC 6842)
----------------------------

The original DHCPv4 specification (`RFC
2131 <https://tools.ietf.org/html/rfc2131>`__) states that the DHCPv4
server must not send back client-id options when responding to clients.
However, in some cases that result confused clients that did not have a MAC
address or client-id; see `RFC
6842 <https://tools.ietf.org/html/rfc6842>`__ for details. That behavior
changed with the publication of `RFC
6842 <https://tools.ietf.org/html/rfc6842>`__, which updated `RFC
2131 <https://tools.ietf.org/html/rfc2131>`__. That update states that
the server must send the client-id if the client sent it. That is Kea's
default behavior. However, in some cases older devices that do not
support `RFC 6842 <https://tools.ietf.org/html/rfc6842>`__ may refuse to
accept responses that include the client-id option. To enable backward
compatibility, an optional configuration parameter has been introduced.
To configure it, use the following configuration statement:

::

   "Dhcp4": {
       "echo-client-id": false,
       ...
   }

.. _dhcp4-match-client-id:

Using Client Identifier and Hardware Address
--------------------------------------------

The DHCP server must be able to identify the client from which it
receives the message and distinguish it from other clients. There are
many reasons why this identification is required; the most important
ones are:

-  When the client contacts the server to allocate a new lease, the
   server must store the client identification information in the lease
   database as a search key.

-  When the client is trying to renew or release the existing lease, the
   server must be able to find the existing lease entry in the database
   for this client, using the client identification information as a
   search key.

-  Some configurations use static reservations for the IP addresses and
   other configuration information. The server's administrator uses
   client identification information to create these static assignments.

-  In dual-stack networks there is often a need to correlate the lease
   information stored in DHCPv4 and DHCPv6 servers for a particular
   host. Using common identification information by the DHCPv4 and
   DHCPv6 clients allows the network administrator to achieve this
   correlation and better administer the network.

DHCPv4 uses two distinct identifiers which are placed by the client in
the queries sent to the server and copied by the server to its responses
to the client: "chaddr" and "client identifier". The former was
introduced as a part of the BOOTP specification and it is also used by
DHCP to carry the hardware address of the interface used to send the
query to the server (MAC address for the Ethernet). The latter is
carried in the Client-identifier option, introduced in `RFC
2132 <https://tools.ietf.org/html/rfc2132>`__.

`RFC 2131 <https://tools.ietf.org/html/rfc2131>`__ indicates that the
server may use both of these identifiers to identify the client but the
"client identifier", if present, takes precedence over "chaddr". One of
the reasons for this is that "client identifier" is independent from the
hardware used by the client to communicate with the server. For example,
if the client obtained the lease using one network card and then the
network card is moved to another host, the server will wrongly identify
this host as the one which obtained the lease. Moreover, `RFC
4361 <https://tools.ietf.org/html/rfc4361>`__ gives the recommendation
to use a DUID (see `RFC 8415 <https://tools.ietf.org/html/rfc8415>`__,
the DHCPv6 specification) carried as a "client identifier" when dual-stack
networks are in use to provide consistent identification information for
the client, regardless of the type of protocol it is using. Kea adheres to
these specifications, and the "client identifier" by default takes
precedence over the value carried in the "chaddr" field when the server
searches, creates, updates, or removes the client's lease.

When the server receives a DHCPDISCOVER or DHCPREQUEST message from the
client, it will try to find out if the client already has a lease in the
database; if it does, the server will hand out that lease rather than allocate a new one.
Each lease in the lease database is associated with the "client
identifier" and/or "chaddr". The server will first use the "client
identifier" (if present) to search for the lease. If the lease is found, the
server will treat this lease as belonging to the client even if the
current "chaddr" and the "chaddr" associated with the lease do not
match. This facilitates the scenario when the network card on the client
system has been replaced and thus the new MAC address appears in the
messages sent by the DHCP client. If the server fails to find the lease
using the "client identifier", it will perform another lookup using the
"chaddr". If this lookup returns no result, the client is considered as
not having a lease and a new lease will be created.

A common problem reported by network operators is that poor client
implementations do not use stable client identifiers, instead generating
a new "client identifier" each time the client connects to the network.
Another well-known case is when the client changes its "client
identifier" during the multi-stage boot process (PXE). In such cases,
the MAC address of the client's interface remains stable, and using the
"chaddr" field to identify the client guarantees that the particular
system is considered to be the same client, even though its "client
identifier" changes.

To address this problem, Kea includes a configuration option which
enables client identification using "chaddr" only. This instructs the
server to "ignore" the "client identifier" during lease lookups and allocations
for a particular subnet. Consider the following simplified server configuration:

::

   "Dhcp4": {
       ...
       "match-client-id": true,
       ...
       "subnet4": [
       {
           "subnet": "192.0.10.0/24",
           "pools": [ { "pool": "192.0.2.23-192.0.2.87" } ],
           "match-client-id": false
       },
       {
           "subnet": "10.0.0.0/8",
           "pools": [ { "pool": "10.0.0.23-10.0.2.99" } ],
       }
       ]
   }

The ``match-client-id`` is a boolean value which controls this behavior.
The default value of ``true`` indicates that the server will use the
"client identifier" for lease lookups and "chaddr" if the first lookup
returns no results. The ``false`` means that the server will only use
the "chaddr" to search for the client's lease. Whether the DHCID for DNS
updates is generated from the "client identifier" or "chaddr" is
controlled through the same parameter.

The ``match-client-id`` parameter may appear both in the global
configuration scope and/or under any subnet declaration. In the example
shown above, the effective value of the ``match-client-id`` will be
``false`` for the subnet 192.0.10.0/24, because the subnet-specific
setting of the parameter overrides the global value of the parameter.
The effective value of the ``match-client-id`` for the subnet 10.0.0.0/8
will be set to ``true`` because the subnet declaration lacks this
parameter and the global setting is by default used for this subnet. In
fact, the global entry for this parameter could be omitted in this case,
because ``true`` is the default value.

It is important to understand what happens when the client obtains its
lease for one setting of the ``match-client-id`` and then renews it when
the setting has been changed. First, consider the case when the client
obtains the lease and the ``match-client-id`` is set to ``true``. The
server will store the lease information, including "client identifier"
(if supplied) and "chaddr", in the lease database. When the setting is
changed and the client renews the lease, the server will determine that
it should use the "chaddr" to search for the existing lease. If the
client hasn't changed its MAC address, the server should successfully
find the existing lease. The "client identifier" associated with the
returned lease will be ignored and the client will be allowed to use this lease.
When the lease is renewed only the "chaddr" will be recorded for this lease,
according to the new server setting.

In the second case the client has the lease with only a "chaddr" value
recorded. When the ``match-client-id`` setting is changed to ``true``,
the server will first try to use the "client identifier" to find the
existing client's lease. This will return no results because the "client
identifier" was not recorded for this lease. The server will then use
the "chaddr" and the lease will be found. If the lease appears to have
no "client identifier" recorded, the server will assume that this lease
belongs to the client and that it was created with the previous setting
of the ``match-client-id``. However, if the lease contains a "client
identifier" which is different from the "client identifier" used by the
client, the lease will be assumed to belong to another client and the
new lease will be allocated.

.. _dhcp4-authoritative:

Authoritative DHCPv4 Server Behavior
------------------------------------

The original DHCPv4 specification (`RFC
2131 <https://tools.ietf.org/html/rfc2131>`__) states that if a client
requests an address in the INIT-REBOOT state, of which the server has no
knowledge, the server must remain silent, except if the server knows
that the client has requested an IP address from the wrong network. By
default, Kea follows the behavior of the ISC dhcpd daemon instead of the
specification and also remains silent if the client requests an IP
address from the wrong network, because configuration information about
a given network segment is not known to be correct. Kea only rejects a
client's DHCPREQUEST with a DHCPNAK message if it already has a lease
for the client with a different IP address. Administrators can
override this behavior through the boolean ``authoritative`` (``false``
by default) setting.

In authoritative mode, ``authoritative`` set to ``true``, Kea always
rejects INIT-REBOOT requests from unknown clients with DHCPNAK messages.
The ``authoritative`` setting can be specified in global,
shared-network, and subnet configuration scope and is automatically
inherited from the parent scope, if not specified. All subnets in a
shared-network must have the same ``authoritative`` setting.

.. _dhcp4-dhcp4o6-config:

DHCPv4-over-DHCPv6: DHCPv4 Side
-------------------------------

The support of DHCPv4-over-DHCPv6 transport is described in `RFC
7341 <https://tools.ietf.org/html/rfc7341>`__ and is implemented using
cooperating DHCPv4 and DHCPv6 servers. This section is about the
configuration of the DHCPv4 side (the DHCPv6 side is described in
:ref:`dhcp6-dhcp4o6-config`).

.. note::

   DHCPv4-over-DHCPv6 support is experimental and the details of the
   inter-process communication may change; both the DHCPv4 and DHCPv6
   sides should be running the same version of Kea. For instance, the
   support of port relay (RFC 8357) introduced an incompatible change.

The ``dhcp4o6-port`` global parameter specifies the first of the two
consecutive ports of the UDP sockets used for the communication between
the DHCPv6 and DHCPv4 servers. The DHCPv4 server is bound to ::1 on
``port`` + 1 and connected to ::1 on ``port``.

With DHCPv4-over-DHCPv6, the DHCPv4 server does not have access to
several of the identifiers it would normally use to select a subnet. To
address this issue, three new configuration entries have been added; the
presence of any of these allows the subnet to be used with
DHCPv4-over-DHCPv6. These entries are:

-  ``4o6-subnet``: takes a prefix (i.e., an IPv6 address followed by a
   slash and a prefix length) which is matched against the source
   address.

-  ``4o6-interface-id``: takes a relay interface ID option value.

-  ``4o6-interface``: takes an interface name which is matched against
   the incoming interface name.

The following configuration was used during some tests:

::

   {

   # DHCPv4 conf
   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eno33554984" ]
       },

       "lease-database": {
           "type": "memfile",
           "name": "leases4"
       },

       "valid-lifetime": 4000,

       "subnet4": [ {
           "subnet": "10.10.10.0/24",
           "4o6-interface": "eno33554984",
           "4o6-subnet": "2001:db8:1:1::/64",
           "pools": [ { "pool": "10.10.10.100 - 10.10.10.199" } ]
       } ],

       "dhcp4o6-port": 6767,

       "loggers": [ {
           "name": "kea-dhcp4",
           "output_options": [ {
               "output": "/tmp/kea-dhcp4.log"
           } ],
           "severity": "DEBUG",
           "debuglevel": 0
       } ]
   }

   }

.. _sanity-checks4:

Sanity Checks in DHCPv4
-----------------------

An important aspect of a well-running DHCP system is an assurance that
the data remain consistent. However, in some cases it may be convenient
to tolerate certain inconsistent data. For example, a network
administrator that temporarily removed a subnet from a configuration
would not want all the leases associated with it to disappear from the
lease database. Kea has a mechanism to control sanity checks such
as this.

Kea supports a configuration scope called ``sanity-checks``. It
currently allows only a single parameter, called ``lease-checks``, which
governs the verification carried out when a new lease is loaded from a
lease file. This mechanism permits Kea to attempt to correct inconsistent data.

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

There are five levels which are supported:

-  ``none`` - do no special checks; accept the lease as is.

-  ``warn`` - if problems are detected display a warning, but
   accept the lease data anyway. This is the default value. If
   not explicitly configured to some other value, this level will be
   used.

-  ``fix`` - if a data inconsistency is discovered, try to
   correct it. If the correction is not successful, the incorrect data
   will be inserted anyway.

-  ``fix-del`` - if a data inconsistency is discovered, try to
   correct it. If the correction is not successful, reject the lease.
   This setting ensures the data's correctness, but some
   incorrect data may be lost. Use with care.

-  ``del`` - this is the strictest mode. If any inconsistency is
   detected, reject the lease. Use with care.

This feature is currently implemented for the memfile backend.

An example configuration that sets this parameter looks as follows:

::

   "Dhcp4": {
       "sanity-checks": {
           "lease-checks": "fix-del"
       },
       ...
   }

.. _host-reservation-v4:

Host Reservation in DHCPv4
==========================

There are many cases where it is useful to provide a configuration on a
per-host basis. The most obvious one is to reserve a specific, static
address for exclusive use by a given client (host); the returning client
will receive the same address from the server every time, and other
clients will generally not receive that address. Another situation when
host reservations are applicable is when a host has
specific requirements, e.g. a printer that needs additional DHCP
options. Yet another possible use case is to define unique names for
hosts.

Note that there may be
cases when a new reservation has been made for a client for an address
currently in use by another client. We call this situation a "conflict."
These conflicts get resolved automatically over time as described in
subsequent sections. Once the conflict is resolved, the correct client will
receive the reserved configuration when it renews.

Host reservations are defined as parameters for each subnet. Each host
must have its own unique identifier, such as the hardware/MAC
address. There is an optional ``reservations`` array in the ``subnet4``
structure; each element in that array is a structure that holds
information about reservations for a single host. In particular, the
structure must have a unique host identifier. In
the DHCPv4 context, the identifier is usually a hardware or MAC address.
In most cases an IP address will be specified. It is also possible to
specify a hostname, host-specific options, or fields carried within the
DHCPv4 message such as siaddr, sname, or file.

The following example shows how to reserve addresses for specific hosts
in a subnet:

::

   "subnet4": [
       {
           "pools": [ { "pool":  "192.0.2.1 - 192.0.2.200" } ],
           "subnet": "192.0.2.0/24",
           "interface": "eth0",
           "reservations": [
               {
                   "hw-address": "1a:1b:1c:1d:1e:1f",
                   "ip-address": "192.0.2.202"
               },
               {
                   "duid": "0a:0b:0c:0d:0e:0f",
                   "ip-address": "192.0.2.100",
                   "hostname": "alice-laptop"
               },
               {
                   "circuit-id": "'charter950'",
                   "ip-address": "192.0.2.203"
               },
               {
                   "client-id": "01:11:22:33:44:55:66",
                   "ip-address": "192.0.2.204"
               }
           ]
       }
   ]

The first entry reserves the 192.0.2.202 address for the client that
uses a MAC address of 1a:1b:1c:1d:1e:1f. The second entry reserves the
address 192.0.2.100 and the hostname of alice-laptop for the client
using a DUID 0a:0b:0c:0d:0e:0f. (Note that if DNS updates are planned,
it is strongly recommended that the hostnames be unique.) The
third example reserves address 192.0.3.203 for a client whose request
would be relayed by a relay agent that inserts a circuit-id option with
the value "charter950". The fourth entry reserves address 192.0.2.204
for a client that uses a client identifier with value
01:11:22:33:44:55:66.

The above example is used for illustrational purposes only; in actual
deployments it is recommended to use as few types as possible
(preferably just one). See :ref:`reservations4-tuning` for a detailed discussion of this
point.

Making a reservation for a mobile host that may visit multiple subnets
requires a separate host definition in each subnet that host is expected to
visit. It is not possible to define multiple host definitions with the
same hardware address in a single subnet. Multiple host definitions with
the same hardware address are valid if each is in a different subnet.

Adding host reservations incurs a performance penalty. In principle, when
a server that does not support host reservation responds to a query, it
needs to check whether there is a lease for a given address being
considered for allocation or renewal. The server that does support host
reservation has to perform additional checks: not only whether the
address is currently used (i.e., if there is a lease for it), but also
whether the address could be used by someone else (i.e., if there is a
reservation for it). That additional check incurs extra overhead.

.. _reservation4-types:

Address Reservation Types
-------------------------

In a typical scenario there is an IPv4 subnet defined, e.g.
192.0.2.0/24, with a certain part of it dedicated for dynamic allocation
by the DHCPv4 server. That dynamic part is referred to as a dynamic pool
or simply a pool. In principle, a host reservation can reserve any
address that belongs to the subnet. The reservations that specify
addresses that belong to configured pools are called "in-pool
reservations." In contrast, those that do not belong to dynamic pools
are called "out-of-pool reservations." There is no formal difference in
the reservation syntax and both reservation types are handled uniformly.

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
   that must be given due consideration when using them, please see
   :ref:`reservation4-conflict` for more details.

.. _reservation4-conflict:

Conflicts in DHCPv4 Reservations
--------------------------------

As reservations and lease information are stored separately, conflicts
may arise. Consider the following series of events: the server has
configured the dynamic pool of addresses from the range of 192.0.2.10 to
192.0.2.20. Host A requests an address and gets 192.0.2.10. Now the
system administrator decides to reserve address 192.0.2.10 for Host B.
In general, reserving an address that is currently assigned to someone
else is not recommended, but there are valid use cases where such an
operation is warranted.

The server now has a conflict to resolve. If Host B boots up and
requests an address, the server is not able to assign the reserved
address 192.0.2.10. A naive approach would to be immediately remove the
existing lease for Host A and create a new one for Host B. That would
not solve the problem, though, because as soon as Host B gets the
address, it will detect that the address is already in use (by Host A) and
will send a DHCPDECLINE message. Therefore, in this situation, the
server has to temporarily assign a different address from the dynamic
pool (not matching what has been reserved) to Host B.

When Host A renews its address, the server will discover that the
address being renewed is now reserved for another host - Host B.
The server will inform Host A that it is no longer allowed to
use it by sending a DHCPNAK message. The server will not remove the
lease, though, as there's a small chance that the DHCPNAK may be lost if
the network is lossy. If that happens, the client will not receive any
responses, so it will retransmit its DHCPREQUEST packet. Once the
DHCPNAK is received by Host A, it will revert to server discovery and
will eventually get a different address. Besides allocating a new lease,
the server will also remove the old one. As a result, address 192.0.2.10
will become free. When Host B tries to renew its temporarily assigned
address, the server will detect that it has a valid lease, but will note
that there is a reservation for a different address. The server will
send DHCPNAK to inform Host B that its address is no longer usable, but
will keep its lease (again, the DHCPNAK may be lost, so the server will
keep it until the client returns for a new address). Host B will revert
to the server discovery phase and will eventually send a DHCPREQUEST
message. This time the server will find that there is a reservation for
that host and that the reserved address 192.0.2.10 is not used, so it
will be granted. It will also remove the lease for the temporarily
assigned address that Host B previously obtained.

This recovery will succeed, even if other hosts attempt to get the
reserved address. If Host C requests the address 192.0.2.10 after the
reservation is made, the server will either offer a different address
(when responding to DHCPDISCOVER) or send DHCPNAK (when responding to
DHCPREQUEST).

The recovery mechanism allows the server to fully recover from a case
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

.. _reservation4-hostname:

Reserving a Hostname
--------------------

When the reservation for a client includes the ``hostname``, the server
will return this hostname to the client in the Client FQDN or Hostname
option. The server responds with the Client FQDN option only if the
client has included the Client FQDN option in its message to the server. The
server will respond with the Hostname option if the client included
the Hostname option in its message to the server, or if the client
requested the Hostname option using the Parameter Request List option.
The server will return the Hostname option even if it is not configured
to perform DNS updates. The reserved hostname always takes precedence
over the hostname supplied by the client or the autogenerated (from the
IPv4 address) hostname.

The server qualifies the reserved hostname with the value of the
``ddns-qualifying-suffix`` parameter. For example, the following subnet
configuration:

::

       {
           "subnet4": [ {
               "subnet": "10.0.0.0/24",
               "pools": [ { "pool": "10.0.0.10-10.0.0.100" } ],
               "ddns-qualifying-suffix": "example.isc.org.",
               "reservations": [
                  {
                    "hw-address": "aa:bb:cc:dd:ee:ff",
                    "hostname": "alice-laptop"
                  }
               ]
            }],
           "dhcp-ddns": {
               "enable-updates": true,
           }
       }

will result in assigning the "alice-laptop.example.isc.org." hostname to
the client using the MAC address "aa:bb:cc:dd:ee:ff". If the
``ddns-qualifying-suffix`` is not specified, the default (empty) value will
be used, and in this case the value specified as a ``hostname`` will be
treated as a fully qualified name. Thus, by leaving the
``ddns-qualifying-suffix`` empty it is possible to qualify hostnames for
different clients with different domain names:

::

       {
           "subnet4": [ {
               "subnet": "10.0.0.0/24",
               "pools": [ { "pool": "10.0.0.10-10.0.0.100" } ],
               "reservations": [
                  {
                    "hw-address": "aa:bb:cc:dd:ee:ff",
                    "hostname": "alice-laptop.isc.org."
                  },
                  {
                    "hw-address": "12:34:56:78:99:AA",
                    "hostname": "mark-desktop.example.org."
                  }

               ]
            }],
           "dhcp-ddns": {
               "enable-updates": true,
           }
       }

.. _reservation4-options:

Including Specific DHCPv4 Options in Reservations
-------------------------------------------------

Kea offers the ability to specify options on a per-host basis. These
options follow the same rules as any other options. These can be
standard options (see :ref:`dhcp4-std-options`),
custom options (see :ref:`dhcp4-custom-options`),
or vendor-specific options (see :ref:`dhcp4-vendor-opts`). The following
example demonstrates how standard options can be defined.

::

   {
       "subnet4": [ {
           "reservations": [
           {
               "hw-address": "aa:bb:cc:dd:ee:ff",
               "ip-address": "192.0.2.1",
               "option-data": [
               {
                   "name": "cookie-servers",
                   "data": "10.1.1.202,10.1.1.203"
               },
               {
                   "name": "log-servers",
                   "data": "10.1.1.200,10.1.1.201"
               } ]
           } ]
       } ]
   }

Vendor-specific options can be reserved in a similar manner:

::

   {
       "subnet4": [ {
           "reservations": [
           {
               "hw-address": "aa:bb:cc:dd:ee:ff",
               "ip-address": "10.0.0.7",
               "option-data": [
               {
                   "name": "vivso-suboptions",
                   "data": "4491"
               },
               {
                   "name": "tftp-servers",
                   "space": "vendor-4491",
                   "data": "10.1.1.202,10.1.1.203"
               } ]
           } ]
       } ]
   }

Options defined at host level have the highest priority. In other words,
if there are options defined with the same type on global, subnet,
class, and host levels, the host-specific values will be used.

.. _reservation4-message-fields:

Reserving Next Server, Server Hostname, and Boot File Name
----------------------------------------------------------

BOOTP/DHCPv4 messages include "siaddr", "sname", and "file" fields. Even
though DHCPv4 includes corresponding options, such as option 66 and
option 67, some clients may not support these options. For this reason,
server administrators often use the "siaddr", "sname", and "file" fields
instead.

With Kea, it is possible to make static reservations for these DHCPv4
message fields:

::

   {
       "subnet4": [ {
           "reservations": [
           {
               "hw-address": "aa:bb:cc:dd:ee:ff",
               "next-server": "10.1.1.2",
               "server-hostname": "server-hostname.example.org",
               "boot-file-name": "/tmp/bootfile.efi"
           } ]
       } ]
   }

Note that those parameters can be specified in combination with other
parameters for a reservation, such as a reserved IPv4 address. These
parameters are optional; a subset of them can be specified, or all
of them can be omitted.

.. _reservation4-client-classes:

Reserving Client Classes in DHCPv4
----------------------------------

:ref:`classification-using-expressions` explains how to configure
the server to assign classes to a client, based on the content of the
options that this client sends to the server. Host reservations
mechanisms also allow for the static assignment of classes to clients.
The definitions of these classes are placed in the Kea configuration.
The following configuration snippet shows how to specify that a client
belongs to classes ``reserved-class1`` and ``reserved-class2``. Those
classes are associated with specific options that are sent to the clients
which belong to them.

::

   {
       "client-classes": [
       {
          "name": "reserved-class1",
          "option-data": [
          {
              "name": "routers",
              "data": "10.0.0.200"
          }
          ]
       },
       {
          "name": "reserved-class2",
          "option-data": [
          {
              "name": "domain-name-servers",
              "data": "10.0.0.201"
          }
          ]
       }
       ],
       "subnet4": [ {
           "subnet": "10.0.0.0/24",
           "pools": [ { "pool": "10.0.0.10-10.0.0.100" } ],
           "reservations": [
           {
               "hw-address": "aa:bb:cc:dd:ee:ff",

               "client-classes": [ "reserved-class1", "reserved-class2" ]

           }
           ]
       } ]
   }

Static class assignments, as shown above, can be used in conjunction
with classification, using expressions. The "KNOWN" or "UNKNOWN" built-in
class is added to the packet and any class depending on it (directly or
indirectly) and not only-if-required is evaluated.

.. note::

   To force the evaluation of a class expression after the
   host reservation lookup, for instance because of a dependency on
   "reserved-class1" from the previous example, add a
   "member('KNOWN')" statement in the expression.

.. note::
   Beware that the reserved classes are assigned to the processed
   packet after all classes with the ``only-if-required`` parameter
   set to ``false`` have been evaluated. This has an implication that
   these classes must not depend on the statically assigned classes
   from the host reservations. If there is a need to create such
   dependency, the ``only-if-required`` must be set to ``true`` for
   the dependent classes. Such classes are evaluated after the static
   classes have been assigned to the packet. This, however, imposes
   additional configuration overhead, because all classes marked as
   ``only-if-required`` must be listed in the ``require-client-classes``
   list for every subnet where they are used.

.. _reservations4-mysql-pgsql-cql:

Storing Host Reservations in MySQL, PostgreSQL, or Cassandra
------------------------------------------------------------

It is possible to store host reservations in MySQL, PostgreSQL, or
Cassandra. See :ref:`hosts6-storage` for information on how to
configure Kea to use reservations stored in MySQL, PostgreSQL, or
Cassandra. Kea provides a dedicated hook for managing reservations in a
database; section :ref:`host-cmds` provides detailed information.
The `Kea wiki
<https://gitlab.isc.org/isc-projects/kea/wikis/designs/commands#23-host-reservations-hr-management>`__
provides some examples of how to conduct common host reservation
operations.

.. note::

   In Kea, the maximum length of an option specified per-host is
   arbitrarily set to 4096 bytes.

.. _reservations4-tuning:

Fine-Tuning DHCPv4 Host Reservation
-----------------------------------

The host reservation capability introduces additional restrictions for
the allocation engine (the component of Kea that selects an address for
a client) during lease selection and renewal. In particular, three major
checks are necessary. First, when selecting a new lease, it is not
sufficient for a candidate lease to simply not be in use by another DHCP
client; it also must not be reserved for another client. Second, when
renewing a lease, an additional check must be performed to see whether
the address being renewed is reserved for another client. Finally, when
a host renews an address, the server must check whether there is a
reservation for this host, so the existing (dynamically allocated)
address should be revoked and the reserved one be used instead.

Some of those checks may be unnecessary in certain deployments, and not
performing them may improve performance. The Kea server provides the
``reservation-mode`` configuration parameter to select the types of
reservations allowed for a particular subnet. Each reservation type has
different constraints for the checks to be performed by the server when
allocating or renewing a lease for the client. Allowed values are:

-  ``all`` - enables both in-pool and out-of-pool host reservation
   types. This setting is the default value, and is the safest and
   most flexible. However, as all checks are conducted, it is also the slowest.
   It does not check against global reservations.

-  ``out-of-pool`` - allows only out-of- pool host reservations. With
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

The parameter can be specified at global, subnet, and shared-network
levels.

An example configuration that disables reservation looks as follows:

::

   "Dhcp4": {
       "subnet4": [
       {
           "subnet": "192.0.2.0/24",
           "reservation-mode": "disabled",
           ...
       }
       ]
   }

An example configuration using global reservations is shown below:

::

   "Dhcp4": {


       "reservation-mode": "global",
       "reservations": [
          {
           "hw-address": "01:bb:cc:dd:ee:ff",
           "hostname": "host-one"
          },
          {
           "hw-address": "02:bb:cc:dd:ee:ff",
           "hostname": "host-two"
          }
       ],

       "subnet4": [
       {
           "subnet": "192.0.2.0/24",
           ...
       }
       ]
   }

For more details regarding global reservations, see :ref:`global-reservations4`.

Another aspect of host reservations is the different types of
identifiers. Kea currently supports four types of identifiers:
hw-address, duid, client-id, and circuit-id. This is beneficial from a
usability perspective; however, there is one drawback. For each incoming
packet, Kea has to extract each identifier type and then query the
database to see if there is a reservation by this particular identifier.
If nothing is found, the next identifier is extracted and the next query
is issued. This process continues until either a reservation is found or
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

   "host-reservation-identifiers": [ "circuit-id", "hw-address", "duid", "client-id" ],
   "subnet4": [
       {
           "subnet": "192.0.2.0/24",
           ...
       }
   ]

If not specified, the default value is:

::

   "host-reservation-identifiers": [ "hw-address", "duid", "circuit-id", "client-id" ]

.. _global-reservations4:

Global Reservations in DHCPv4
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
addresses. However, global reservations that assign addresses bypass the
whole topology determination provided by DHCP logic implemented in Kea.
It is very easy to misuse this feature and get a configuration that is
inconsistent. To give a specific example, imagine a global reservation
for address 192.0.2.100 and two subnets 192.0.2.0/24 and 192.0.5.0/24.
If global reservations are used in both subnets and a device matching
global host reservations visits part of the network that is serviced by
192.0.5.0/24, it will get an IP address 192.0.2.100, a subnet 192.0.5.0
and a default router 192.0.5.1. Obviously, such a configuration is
unusable, as the client will not be able to reach its default gateway.

To use global host reservations, a configuration similar to the
following can be used:

::

   "Dhcp4:" {
       # This specifies global reservations. They will apply to all subnets that
       # have global reservations enabled.

       "reservations": [
       {
          "hw-address": "aa:bb:cc:dd:ee:ff",
          "hostname": "hw-host-dynamic"
       },
       {
          "hw-address": "01:02:03:04:05:06",
          "hostname": "hw-host-fixed",

          # Use of IP address in global reservation is risky. If used outside of
          # a matching subnet, such as 192.0.1.0/24, it will result in a broken
          # configuration being handed to the client.
          "ip-address": "192.0.1.77"
       },
       {
          "duid": "01:02:03:04:05",
          "hostname": "duid-host"
       },
       {
          "circuit-id": "'charter950'",
          "hostname": "circuit-id-host"
       },
       {
          "client-id": "01:11:22:33:44:55:66",
          "hostname": "client-id-host"
       }
       ],
       "valid-lifetime": 600,
       "subnet4": [ {
           "subnet": "10.0.0.0/24",
           "reservation-mode": "global",
           "pools": [ { "pool": "10.0.0.10-10.0.0.100" } ]
       } ]
   }

When using database backends, the global host reservations are
distinguished from regular reservations by using a subnet-id value of
zero.

.. _shared-network4:

Shared Networks in DHCPv4
=========================

DHCP servers use subnet information in two ways. First, it is used to
determine the point of attachment, or where the client is
connected to the network. Second, the subnet information is used to
group information pertaining to a specific location in the network. This
approach works well in general, but there are scenarios where the
boundaries are blurred. Sometimes it is useful to have more than one
logical IP subnet deployed on the same physical link.
Understanding that two or more subnets are used on the same link requires
additional logic in the DHCP server. This capability is called "shared
networks" in the Kea and ISC DHCP projects. (It is sometimes also called
"shared subnets"; in Microsoft's nomenclature it is called "multinet.")

There are many use cases where the feature is useful; this paragraph
explains just a handful of the most common ones. The first and by far
the most common use case is an existing network that has grown and is
running out of available address space. Rather than migrating all
devices to a new, larger subnet, it is easier to simply configure
additional subnets on top of the existing one. Sometimes, due to address
space fragmentation (e.g. only many disjointed /24s are available), this
is the only choice. Also, configuring additional subnets has the
advantage of not disrupting the operation of existing devices.

Another very frequent use case comes from cable networks. There are two
types of devices in cable networks: cable modems and the end-user
devices behind them. It is a common practice to use different subnets
for cable modems to prevent users from tinkering with them. In this
case, the distinction is based on the type of device, rather than
on address-space exhaustion.

A client connected to a shared network may be assigned an address from
any of the pools defined within the subnets belonging to the shared
network. Internally, the server selects one of the subnets belonging to
a shared network and tries to allocate an address from this subnet. If
the server is unable to allocate an address from the selected subnet
(e.g., due to address-pool exhaustion), it will use another subnet from
the same shared network and will try to allocate an address from this subnet,
etc. Therefore, the server will typically allocate all
addresses available in a given subnet before it starts allocating
addresses from other subnets belonging to the same shared network.
However, in certain situations the client can be allocated an address
from another subnet before the address pools in the first subnet get
exhausted; this sometimes occurs when the client provides a hint that belongs to another
subnet, or the client has reservations in a subnet other than the
default.

.. note::

   Deployments should not assume that Kea waits until it has allocated
   all the addresses from the first subnet in a shared network before
   allocating addresses from other subnets.

In order to define a shared network an additional configuration scope is
introduced:

::

   {
   "Dhcp4": {
       "shared-networks": [
           {
               # Name of the shared network. It may be an arbitrary string
               # and it must be unique among all shared networks.
               "name": "my-secret-lair-level-1",

               # The subnet selector can be specified at the shared network level.
               # Subnets from this shared network will be selected for directly
               # connected clients sending requests to server's "eth0" interface.
               "interface": "eth0",

               # This starts a list of subnets in this shared network.
               # There are two subnets in this example.
               "subnet4": [
                   {
                       "subnet": "10.0.0.0/8",
                       "pools": [ { "pool":  "10.0.0.1 - 10.0.0.99" } ],
                   },
                   {
                       "subnet": "192.0.2.0/24",
                       "pools": [ { "pool":  "192.0.2.100 - 192.0.2.199" } ]
                   }
               ],
           } ], # end of shared-networks

       # It is likely that in the network there will be a mix of regular,
       # "plain" subnets and shared networks. It is perfectly valid to mix
       # them in the same configuration file.
       #
       # This is a regular subnet. It is not part of any shared network.
       "subnet4": [
           {
               "subnet": "192.0.3.0/24",
               "pools": [ { "pool":  "192.0.3.1 - 192.0.3.200" } ],
               "interface": "eth1"
           }
       ]

   } # end of Dhcp4
   }

As demonstrated in the example, it is possible to mix shared and regular
("plain") subnets. Each shared network must have a unique name. This is
similar to the ID for subnets, but gives administrators more
flexibility. It is used for logging, but also internally for identifying
shared networks.

In principle it makes sense to define only shared networks that consist
of two or more subnets. However, for testing purposes, an empty subnet
or a network with just a single subnet is allowed. This is not a
recommended practice in production networks, as the shared network logic
requires additional processing and thus lowers the server's performance.
To avoid unnecessary performance degradation, the shared subnets should
only be defined when required by the deployment.

Shared networks provide an ability to specify many parameters in the
shared network scope that apply to all subnets within it. If
necessary, it is possible to specify a parameter in the shared network scope and
then override its value in the subnet scope. For example:

::

   "shared-networks": [
       {
           "name": "lab-network3",

           "interface": "eth0",

           # This applies to all subnets in this shared network, unless
           # values are overridden on subnet scope.
           "valid-lifetime": 600,

           # This option is made available to all subnets in this shared
           # network.
           "option-data": [ {
               "name": "log-servers",
               "data": "1.2.3.4"
           } ],

           "subnet4": [
               {
                   "subnet": "10.0.0.0/8",
                   "pools": [ { "pool":  "10.0.0.1 - 10.0.0.99" } ],

                   # This particular subnet uses different values.
                   "valid-lifetime": 1200,
                   "option-data": [
                   {
                       "name": "log-servers",
                       "data": "10.0.0.254"
                   },
                   {
                       "name": "routers",
                       "data": "10.0.0.254"
                   } ]
               },
               {
                    "subnet": "192.0.2.0/24",
                    "pools": [ { "pool":  "192.0.2.100 - 192.0.2.199" } ],

                    # This subnet does not specify its own valid-lifetime value,
                    # so it is inherited from shared network scope.
                    "option-data": [
                    {
                        "name": "routers",
                        "data": "192.0.2.1"
                    } ]
               }
           ]
       } ]

In this example, there is a log-servers option defined that is available
to clients in both subnets in this shared network. Also, the valid
lifetime is set to 10 minutes (600s). However, the first subnet
overrides some of the values (valid lifetime is 20 minutes, different IP
address for log-servers), but also adds its own option (router address).
Assuming a client asking for router and log servers options is assigned
a lease from this subnet, it will get a lease for 20 minutes and a
log-servers and routers value of 10.0.0.254. If the same client is
assigned to the second subnet, it will get a 10-minute lease, a
log-servers value of 1.2.3.4, and routers set to 192.0.2.1.

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
           "subnet4": [
               {
                   "subnet": "10.0.0.0/8",
                   "pools": [ { "pool":  "10.0.0.1 - 10.0.0.99" } ],
                   "interface": "eth0"
               },
               {
                    "subnet": "192.0.2.0/24",
                    "pools": [ { "pool":  "192.0.2.100 - 192.0.2.199" } ],

                    # Specifying the different interface name is a configuration
                    # error. This value should rather be "eth0" or the interface
                    # name in the other subnet should be "eth1".
                    "interface": "eth1"
               }
           ]
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

           "subnet4": [
               {
                   "subnet": "10.0.0.0/8",
                   "pools": [ { "pool":  "10.0.0.1 - 10.0.0.99" } ],
               },
               {
                    "subnet": "192.0.2.0/24",
                    "pools": [ { "pool":  "192.0.2.100 - 192.0.2.199" } ]
               }
           ]
       } ]


In case of the relayed traffic, the subnets are typically selected using
the relay agents' addresses. If the subnets are used independently (not
grouped within a shared network) it is allowed to specify different relay
address for each of these subnets. When multiple subnets belong to a
shared network they must be selected via the same relay address and,
similarly to the case of the local traffic described above, it is a
configuration error to specify different relay addresses for the respective
subnets in the shared network. The following configuration is wrong.

::

   "shared-networks": [
       {
           "name": "kakapo",
           "subnet4": [
               {
                   "subnet": "192.0.2.0/26",
                   "relay": {
                       "ip-addresses": [ "192.1.1.1" ]
                   },
                   "pools": [ { "pool": "192.0.2.63 - 192.0.2.63" } ]
               },
               {
                   "subnet": "10.0.0.0/24",
                   "relay": {
                       # Specifying a different relay address for this
                       # subnet is a configuration error. In this case
                       # it should be 192.1.1.1 or the relay address
                       # in the previous subnet should be 192.2.2.2.
                       "ip-addresses": [ "192.2.2.2" ]
                   },
                   "pools": [ { "pool": "10.0.0.16 - 10.0.0.16" } ]
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
               "ip-addresses": [ "192.1.1.1" ]
           },
           "subnet4": [
               {
                   "subnet": "192.0.2.0/26",
                   "pools": [ { "pool": "192.0.2.63 - 192.0.2.63" } ]
               },
               {
                   "subnet": "10.0.0.0/24",
                   "pools": [ { "pool": "10.0.0.16 - 10.0.0.16" } ]
               }
           ]
       }
   ]

Even though it is technically possible to configure two (or more) subnets
within the shared network to use different relay addresses, this will almost
always lead to a different behavior than what the user would expect. In this
case, the Kea server will initially select one of the subnets by matching
the relay address in the client's packet with the subnet's conifguration.
However, it MAY end up using the other subnet (even though it does not match
the relay address) if the client already has a lease in this subnet, has a
host reservation in this subnet or simply the initially selected subnet has no
more addresses available. Therefore, it is strongly recommended to always
specify subnet selectors (interface or a relay address) at shared network
level if the subnets belong to a shared network, as it is rarely useful to
specify them at the subnet level and it may lead to the configurtion errors
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
               "test": "option[93].hex == 0x0002"
           }
       ],
       "shared-networks": [
           {
               "name": "galah",
               "interface": "eth0",
               "subnet4": [
                   {
                       "subnet": "192.0.2.0/26",
                       "pools": [ { "pool": "192.0.2.1 - 192.0.2.63" } ],
                   },
                   {
                       "subnet": "10.0.0.0/24",
                       "pools": [ { "pool": "10.0.0.2 - 10.0.0.250" } ],
                       "client-class": "b-devices"
                   }
               ]
           }
       ]
   }

If the client belongs to the "b-devices" class (because it includes
option 93 with a value of 0x0002), that does not guarantee that the
subnet 10.0.0.0/24 will be used (or preferred) for this client. The
server can use either of the two subnets, because the subnet 192.0.2.0/26
is also allowed for this client. The client classification used in this
case should be perceived as a way to restrict access to certain subnets,
rather than a way to express subnet preference. For example, if the
client does not belong to the "b-devices" class it may only use the
subnet 192.0.2.0/26 and will never use the subnet 10.0.0.0/24.

A typical use case for client classification is in a cable network,
where cable modems should use one subnet and other devices should use
another subnet within the same shared network. In this case it is
necessary to apply classification on all subnets. The following example
defines two classes of devices, and the subnet selection is made based
on option 93 values.

::

   {
       "client-classes": [
           {

               "name": "a-devices",
               "test": "option[93].hex == 0x0001"
           },
           {
               "name": "b-devices",
               "test": "option[93].hex == 0x0002"
           }
       ],
       "shared-networks": [
           {
               "name": "galah",
               "interface": "eth0",
               "subnet4": [
                   {
                       "subnet": "192.0.2.0/26",
                       "pools": [ { "pool": "192.0.2.1 - 192.0.2.63" } ],
                       "client-class": "a-devices"
                   },
                   {
                       "subnet": "10.0.0.0/24",
                       "pools": [ { "pool": "10.0.0.2 - 10.0.0.250" } ],
                       "client-class": "b-devices"
                   }
               ]
           }
       ]
   }

In this example each class has its own restriction. Only clients that
belong to class "a-devices" will be able to use subnet 192.0.2.0/26 and
only clients belonging to "b-devices" will be able to use subnet
10.0.0.0/24. Care should be taken not to define too-restrictive
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
           "interface": "eth0",
           "subnet4": [
               {
                   "subnet": "192.0.2.0/26",
                   "id": 100,
                   "pools": [ { "pool": "192.0.2.1 - 192.0.2.63" } ],
                   "reservations": [
                       {
                           "hw-address": "aa:bb:cc:dd:ee:ff",
                           "ip-address": "192.0.2.28"
                       }
                   ]
               },
               {
                   "subnet": "10.0.0.0/24",
                   "id": 101,
                   "pools": [ { "pool": "10.0.0.1 - 10.0.0.254" } ],
                   "reservations": [
                       {
                           "hw-address": "11:22:33:44:55:66",
                           "ip-address": "10.0.0.29"
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
autogenerated, i.e. Kea assigns increasing integer values starting from
1. Thus, the autogenerated IDs are not stable across configuration
changes.

.. _dhcp4-serverid:

Server Identifier in DHCPv4
===========================

The DHCPv4 protocol uses a "server identifier" to allow clients to
discriminate between several servers present on the same link; this
value is an IPv4 address of the server. The server chooses the IPv4
address of the interface on which the message from the client (or relay)
has been received. A single server instance will use multiple server
identifiers if it is receiving queries on multiple interfaces.

It is possible to override the default server identifier values by
specifying the "dhcp-server-identifier" option. This option is only
supported at the global, shared network, and subnet levels; it must not
be specified on the client class or host reservation levels.

The following example demonstrates how to override the server identifier
for a subnet:

::

   "subnet4": [
       {
           "subnet": "192.0.2.0/24",
           "option-data": [
               {
                   "name": "dhcp-server-identifier",
                   "data": "10.2.5.76"
               }
           ],
           ...
       }
   ]

.. _dhcp4-subnet-selection:

How the DHCPv4 Server Selects a Subnet for the Client
=====================================================

The DHCPv4 server differentiates between directly connected clients,
clients trying to renew leases, and clients sending their messages
through relays. For directly connected clients, the server will check
the configuration for the interface on which the message has been
received and, if the server configuration doesn't match any configured
subnet, the message is discarded.

Assuming that the server's interface is configured with the IPv4 address
192.0.2.3, the server will only process messages received through this
interface from a directly connected client if there is a subnet
configured to which this IPv4 address belongs, such as 192.0.2.0/24. The
server will use this subnet to assign an IPv4 address for the client.

The rule above does not apply when the client unicasts its message, i.e.
is trying to renew its lease. Such a message is accepted through any
interface. The renewing client sets ciaddr to the currently used IPv4
address, and the server uses this address to select the subnet for the
client (in particular, to extend the lease using this address).

If the message is relayed it is accepted through any interface. The
giaddr set by the relay agent is used to select the subnet for the
client.

It is also possible to specify a relay IPv4 address for a given subnet.
It can be used to match incoming packets into a subnet in uncommon
configurations, e.g. shared networks. See :ref:`dhcp4-relay-override` for details.

.. note::

   The subnet selection mechanism described in this section is based on
   the assumption that client classification is not used. The
   classification mechanism alters the way in which a subnet is selected
   for the client, depending on the classes to which the client belongs.

.. _dhcp4-relay-override:

Using a Specific Relay Agent for a Subnet
-----------------------------------------

A relay must have an interface connected to the link on which the
clients are being configured. Typically the relay has an IPv4 address
configured on that interface, which belongs to the subnet from which the
server will assign addresses. Normally, the server is able to use the
IPv4 address inserted by the relay (in the giaddr field of the DHCPv4
packet) to select the appropriate subnet.

However, that is not always the case. In certain uncommon — but valid —
deployments, the relay address may not match the subnet. This usually
means that there is more than one subnet allocated for a given link. The
two most common examples where this is the case are long-lasting network
renumbering (where both old and new address space is still being used)
and a cable network. In a cable network, both cable modems and the
devices behind them are physically connected to the same link, yet they
use distinct addressing. In such a case, the DHCPv4 server needs
additional information (the IPv4 address of the relay) to properly
select an appropriate subnet.

The following example assumes that there is a subnet 192.0.2.0/24 that
is accessible via a relay that uses 10.0.0.1 as its IPv4 address. The
server is able to select this subnet for any incoming packets that come
from a relay that has an address in the 192.0.2.0/24 subnet. It also
selects that subnet for a relay with address 10.0.0.1.

::

   "Dhcp4": {
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "relay": {
                   "ip-addresses": [ "10.0.0.1" ]
               },
               ...
           }
       ],
       ...
   }

If "relay" is specified, the "ip-addresses" parameter within it is
mandatory.

.. note::

   The current version of Kea uses the "ip-addresses" parameter, which
   supports specifying a list of addresses.

.. _dhcp4-srv-example-client-class-relay:

Segregating IPv4 Clients in a Cable Network
-------------------------------------------

In certain cases, it is useful to mix relay address information
(introduced in :ref:`dhcp4-relay-override`), with client classification (explained
in :ref:`classify`). One specific example is in a cable network,
where modems typically get addresses from a different subnet than all
the devices connected behind them.

Let us assume that there is one CMTS (Cable Modem Termination System)
with one CM MAC (a physical link that modems are connected to). We want
the modems to get addresses from the 10.1.1.0/24 subnet, while
everything connected behind the modems should get addresses from another
subnet (192.0.2.0/24). The CMTS that acts as a relay uses address
10.1.1.1. The following configuration can serve that configuration:

::

   "Dhcp4": {
       "subnet4": [
           {
               "subnet": "10.1.1.0/24",
               "pools":  [ { "pool": "10.1.1.2 - 10.1.1.20" } ],
               "client-class" "docsis3.0",
               "relay": {
                   "ip-addresses": [ "10.1.1.1 ]"
               }
           },
           {
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "relay": {
                   "ip-addresses": [ "10.1.1.1" ]
               }
           }
       ],
       ...
   }

.. _dhcp4-decline:

Duplicate Addresses (DHCPDECLINE Support)
=========================================

The DHCPv4 server is configured with a certain pool of addresses that it
is expected to hand out to DHCPv4 clients. It is assumed that the server
is authoritative and has complete jurisdiction over those addresses.
However, for various reasons, such as misconfiguration or a faulty
client implementation that retains its address beyond the valid
lifetime, there may be devices connected that use those addresses
without the server's approval or knowledge.

Such an unwelcome event can be detected by legitimate clients (using ARP
or ICMP Echo Request mechanisms) and reported to the DHCPv4 server using
a DHCPDECLINE message. The server will do a sanity check (to see whether
the client declining an address really was supposed to use it), and then
will conduct a clean-up operation. Any DNS entries related to that
address will be removed, the fact will be logged, and hooks will be
triggered. After that is complete, the address will be marked as
declined (which indicates that it is used by an unknown entity and thus
not available for assignment) and a probation time will be set on it.
Unless otherwise configured, the probation period lasts 24 hours; after
that period, the server will recover the lease (i.e. put it back into
the available state) and the address will be available for assignment
again. It should be noted that if the underlying issue of a
misconfigured device is not resolved, the duplicate-address scenario
will repeat. If reconfigured correctly, this mechanism provides an
opportunity to recover from such an event automatically, without any
system administrator intervention.

To configure the decline probation period to a value other than the
default, the following syntax can be used:

::

     "Dhcp4": {
       "decline-probation-period": 3600,
       "subnet4": [ ... ],
       ...
   }

The parameter is expressed in seconds, so the example above will
instruct the server to recycle declined leases after one hour.

There are several statistics and hook points associated with the Decline
handling procedure. The lease4_decline hook is triggered after the
incoming DHCPDECLINE message has been sanitized and the server is about
to decline the lease. The declined-addresses statistic is increased
after the hook returns (both global and subnet-specific variants). (See
:ref:`dhcp4-stats` and :ref:`hooks-libraries` for more details on DHCPv4 statistics and Kea
hook points.)

Once the probation time elapses, the declined lease is recovered using
the standard expired-lease reclamation procedure, with several
additional steps. In particular, both declined-addresses statistics
(global and subnet-specific) are decreased. At the same time,
reclaimed-declined-addresses statistics (again in two variants, global
and subnet-specific) are increased.

A note about statistics: the server does not decrease the
assigned-addresses statistics when a DHCPDECLINE is received and
processed successfully. While technically a declined address is no
longer assigned, the primary usage of the assigned-addresses statistic
is to monitor pool utilization. Most people would forget to include
declined-addresses in the calculation, and simply use
assigned-addresses/total-addresses. This would cause a bias towards
under-representing pool utilization. As this has a potential for major
issues, ISC decided not to decrease assigned-addresses immediately after
receiving DHCPDECLINE, but to do it later when Kea recovers the address
back to the available pool.

.. _dhcp4-stats:

Statistics in the DHCPv4 Server
===============================

.. note::

   This section describes DHCPv4-specific statistics. For a general
   overview and usage of statistics, see :ref:`stats`.

The DHCPv4 server supports the following statistics:

.. tabularcolumns:: |p{0.2\linewidth}|p{0.1\linewidth}|p{0.7\linewidth}|

.. table:: DHCPv4 Statistics
   :class: longtable
   :widths: 20 10 70

   +--------------------------------+----------------+-----------------------------------+
   | Statistic                      | Data Type      | Description                       |
   +================================+================+===================================+
   | pkt4-received                  | integer        | Number of DHCPv4 packets          |
   |                                |                | received.  This includes all      |
   |                                |                | packets: valid, bogus,            |
   |                                |                | corrupted, rejected, etc. This    |
   |                                |                | statistic is expected to grow     |
   |                                |                | rapidly.                          |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-discover-received         | integer        | Number of                         |
   |                                |                | DHCPDISCOVER packets              |
   |                                |                | received. This                    |
   |                                |                | statistic is expected             |
   |                                |                | to grow; its increase             |
   |                                |                | means that clients                |
   |                                |                | that just booted                  |
   |                                |                | started their                     |
   |                                |                | configuration process             |
   |                                |                | and their initial                 |
   |                                |                | packets reached the               |
   |                                |                | Kea server.                       |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-offer-received            | integer        | Number of DHCPOFFER               |
   |                                |                | packets received.                 |
   |                                |                | This statistic is                 |
   |                                |                | expected to remain                |
   |                                |                | zero at all times, as             |
   |                                |                | DHCPOFFER packets are             |
   |                                |                | sent by the server                |
   |                                |                | and the server is                 |
   |                                |                | never expected to                 |
   |                                |                | receive them. A                   |
   |                                |                | non-zero value                    |
   |                                |                | indicates an error.               |
   |                                |                | One likely cause                  |
   |                                |                | would be a                        |
   |                                |                | misbehaving relay                 |
   |                                |                | agent that                        |
   |                                |                | incorrectly forwards              |
   |                                |                | DHCPOFFER messages                |
   |                                |                | towards the server,               |
   |                                |                | rather than back to               |
   |                                |                | the clients.                      |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-request-received          | integer        | Number of DHCPREQUEST             |
   |                                |                | packets received.                 |
   |                                |                | This statistic is                 |
   |                                |                | expected to grow. Its             |
   |                                |                | increase means that               |
   |                                |                | clients that just                 |
   |                                |                | booted received the               |
   |                                |                | server's response                 |
   |                                |                | (DHCPOFFER) and                   |
   |                                |                | accepted it, and are              |
   |                                |                | now requesting an                 |
   |                                |                | address                           |
   |                                |                | (DHCPREQUEST).                    |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-ack-received              | integer        | Number of DHCPACK                 |
   |                                |                | packets received.                 |
   |                                |                | This statistic is                 |
   |                                |                | expected to remain                |
   |                                |                | zero at all times, as             |
   |                                |                | DHCPACK packets are               |
   |                                |                | sent by the server                |
   |                                |                | and the server is                 |
   |                                |                | never expected to                 |
   |                                |                | receive them. A                   |
   |                                |                | non-zero value                    |
   |                                |                | indicates an error.               |
   |                                |                | One likely cause                  |
   |                                |                | would be a                        |
   |                                |                | misbehaving relay                 |
   |                                |                | agent that                        |
   |                                |                | incorrectly forwards              |
   |                                |                | DHCPACK messages                  |
   |                                |                | towards the server,               |
   |                                |                | rather than back to               |
   |                                |                | the clients.                      |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-nak-received              | integer        | Number of DHCPNAK                 |
   |                                |                | packets received.                 |
   |                                |                | This statistic is                 |
   |                                |                | expected to remain                |
   |                                |                | zero at all times, as             |
   |                                |                | DHCPNAK packets are               |
   |                                |                | sent by the server                |
   |                                |                | and the server is                 |
   |                                |                | never expected to                 |
   |                                |                | receive them. A                   |
   |                                |                | non-zero value                    |
   |                                |                | indicates an error.               |
   |                                |                | One likely cause                  |
   |                                |                | would be a                        |
   |                                |                | misbehaving relay                 |
   |                                |                | agent that                        |
   |                                |                | incorrectly forwards              |
   |                                |                | DHCPNAK messages                  |
   |                                |                | towards the server,               |
   |                                |                | rather than back to               |
   |                                |                | the clients.                      |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-release-received          | integer        | Number of DHCPRELEASE             |
   |                                |                | packets received.                 |
   |                                |                | This statistic is                 |
   |                                |                | expected to grow. Its             |
   |                                |                | increase means that               |
   |                                |                | clients that had an               |
   |                                |                | address are shutting              |
   |                                |                | down or ceasing to                |
   |                                |                | use their addresses.              |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-decline-received          | integer        | Number of DHCPDECLINE             |
   |                                |                | packets received.                 |
   |                                |                | This statistic is                 |
   |                                |                | expected to remain                |
   |                                |                | close to zero. Its                |
   |                                |                | increase means that a             |
   |                                |                | client leased an                  |
   |                                |                | address, but                      |
   |                                |                | discovered that the               |
   |                                |                | address is currently              |
   |                                |                | used by an unknown                |
   |                                |                | device in the                     |
   |                                |                | network.                          |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-inform-received           | integer        | Number of DHCPINFORM              |
   |                                |                | packets received.                 |
   |                                |                | This statistic is                 |
   |                                |                | expected to grow. Its             |
   |                                |                | increase means that               |
   |                                |                | there are clients                 |
   |                                |                | that either do not                |
   |                                |                | need an address or                |
   |                                |                | already have an                   |
   |                                |                | address and are                   |
   |                                |                | interested only in                |
   |                                |                | getting additional                |
   |                                |                | configuration                     |
   |                                |                | parameters.                       |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-unknown-received          | integer        | Number of packets                 |
   |                                |                | received of an                    |
   |                                |                | unknown type. A                   |
   |                                |                | non-zero value of                 |
   |                                |                | this statistic                    |
   |                                |                | indicates that the                |
   |                                |                | server received a                 |
   |                                |                | packet that it wasn't             |
   |                                |                | able to recognize,                |
   |                                |                | either with an                    |
   |                                |                | unsupported type or               |
   |                                |                | possibly malformed                |
   |                                |                | (without message type             |
   |                                |                | option).                          |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-sent                      | integer        | Number of DHCPv4                  |
   |                                |                | packets sent. This                |
   |                                |                | statistic is expected             |
   |                                |                | to grow every time                |
   |                                |                | the server transmits              |
   |                                |                | a packet. In general,             |
   |                                |                | it should roughly                 |
   |                                |                | match pkt4-received,              |
   |                                |                | as most incoming                  |
   |                                |                | packets cause the                 |
   |                                |                | server to respond.                |
   |                                |                | There are exceptions              |
   |                                |                | (e.g. DHCPRELEASE),               |
   |                                |                | so do not worry if it             |
   |                                |                | is less than                      |
   |                                |                | pkt4-received.                    |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-offer-sent                | integer        | Number of DHCPOFFER               |
   |                                |                | packets sent. This                |
   |                                |                | statistic is expected             |
   |                                |                | to grow in most cases             |
   |                                |                | after a DHCPDISCOVER              |
   |                                |                | is processed. There               |
   |                                |                | are certain uncommon,             |
   |                                |                | but valid, cases                  |
   |                                |                | where incoming                    |
   |                                |                | DHCPDISCOVER packets              |
   |                                |                | are dropped, but in               |
   |                                |                | general this                      |
   |                                |                | statistic is expected             |
   |                                |                | to be close to                    |
   |                                |                | pkt4-discover-received.           |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-ack-sent                  | integer        | Number of DHCPACK                 |
   |                                |                | packets sent. This                |
   |                                |                | statistic is expected             |
   |                                |                | to grow in most cases             |
   |                                |                | after a DHCPREQUEST               |
   |                                |                | is processed. There               |
   |                                |                | are certain cases                 |
   |                                |                | where DHCPNAK is sent             |
   |                                |                | instead. In general,              |
   |                                |                | the sum of                        |
   |                                |                | pkt4-ack-sent and                 |
   |                                |                | pkt4-nak-sent should              |
   |                                |                | be close to                       |
   |                                |                | pkt4-request-received.            |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-nak-sent                  | integer        | Number of DHCPNAK                 |
   |                                |                | packets sent. This                |
   |                                |                | statistic is expected             |
   |                                |                | to grow when the                  |
   |                                |                | server chooses not to             |
   |                                |                | honor the address                 |
   |                                |                | requested by a                    |
   |                                |                | client. In general,               |
   |                                |                | the sum of                        |
   |                                |                | pkt4-ack-sent and                 |
   |                                |                | pkt4-nak-sent should              |
   |                                |                | be close to                       |
   |                                |                | pkt4-request-received.            |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-parse-failed              | integer        | Number of incoming                |
   |                                |                | packets that could                |
   |                                |                | not be parsed. A                  |
   |                                |                | non-zero value of                 |
   |                                |                | this statistic                    |
   |                                |                | indicates that the                |
   |                                |                | server received a                 |
   |                                |                | malformed or                      |
   |                                |                | truncated packet.                 |
   |                                |                | This may indicate                 |
   |                                |                | problems in the                   |
   |                                |                | network, faulty                   |
   |                                |                | clients, or a bug in              |
   |                                |                | the server.                       |
   +--------------------------------+----------------+-----------------------------------+
   | pkt4-receive-drop              | integer        | Number of incoming                |
   |                                |                | packets that were                 |
   |                                |                | dropped. The exact                |
   |                                |                | reason for dropping               |
   |                                |                | packets is logged,                |
   |                                |                | but the most common               |
   |                                |                | reasons may be: an                |
   |                                |                | unacceptable packet               |
   |                                |                | type, direct                      |
   |                                |                | responses are                     |
   |                                |                | forbidden, or the                 |
   |                                |                | server-id sent by the             |
   |                                |                | client does not match             |
   |                                |                | the server's                      |
   |                                |                | server-id.                        |
   +--------------------------------+----------------+-----------------------------------+
   | subnet[id].total-addresses     | integer        | Total number of                   |
   |                                |                | addresses available               |
   |                                |                | for DHCPv4                        |
   |                                |                | management; in other              |
   |                                |                | words, this is the                |
   |                                |                | sum of all addresses              |
   |                                |                | in all configured                 |
   |                                |                | pools. This statistic             |
   |                                |                | changes only during               |
   |                                |                | configuration                     |
   |                                |                | changes. Note it does             |
   |                                |                | not take into account             |
   |                                |                | any addresses that                |
   |                                |                | may be reserved due               |
   |                                |                | to host reservation.              |
   |                                |                | The *id* is the                   |
   |                                |                | subnet-id of a given              |
   |                                |                | subnet. This                      |
   |                                |                | statistic is exposed              |
   |                                |                | for each subnet                   |
   |                                |                | separately, and is                |
   |                                |                | reset during a                    |
   |                                |                | reconfiguration                   |
   |                                |                | event.                            |
   +--------------------------------+----------------+-----------------------------------+
   | subnet[id].assigned-addresses  | integer        | Number of assigned                |
   |                                |                | addresses in a given              |
   |                                |                | subnet. It increases              |
   |                                |                | every time a new                  |
   |                                |                | lease is allocated                |
   |                                |                | (as a result of                   |
   |                                |                | receiving a                       |
   |                                |                | DHCPREQUEST message)              |
   |                                |                | and is decreased                  |
   |                                |                | every time a lease is             |
   |                                |                | released (a                       |
   |                                |                | DHCPRELEASE message               |
   |                                |                | is received) or                   |
   |                                |                | expires. The *id* is              |
   |                                |                | the subnet-id of the              |
   |                                |                | subnet. This                      |
   |                                |                | statistic is exposed              |
   |                                |                | for each subnet                   |
   |                                |                | separately, and is                |
   |                                |                | reset during a                    |
   |                                |                | reconfiguration                   |
   |                                |                | event.                            |
   +--------------------------------+----------------+-----------------------------------+
   | reclaimed-leases               | integer        | Number of expired                 |
   |                                |                | leases that have been             |
   |                                |                | reclaimed since                   |
   |                                |                | server startup. It is             |
   |                                |                | incremented each time             |
   |                                |                | an expired lease is               |
   |                                |                | reclaimed and is                  |
   |                                |                | reset when the server             |
   |                                |                | is reconfigured.                  |
   +--------------------------------+----------------+-----------------------------------+
   | subnet[id].reclaimed-leases    | integer        | Number of expired                 |
   |                                |                | leases associated                 |
   |                                |                | with a given subnet               |
   |                                |                | (*id* is the                      |
   |                                |                | subnet-id) that have              |
   |                                |                | been reclaimed since              |
   |                                |                | server startup. It is             |
   |                                |                | incremented each time             |
   |                                |                | an expired lease is               |
   |                                |                | reclaimed and is                  |
   |                                |                | reset when the server             |
   |                                |                | is reconfigured.                  |
   +--------------------------------+----------------+-----------------------------------+
   | declined-addresses             | integer        | Number of IPv4                    |
   |                                |                | addresses that are                |
   |                                |                | currently declined; a             |
   |                                |                | count of the number               |
   |                                |                | of leases currently               |
   |                                |                | unavailable. Once a               |
   |                                |                | lease is recovered,               |
   |                                |                | this statistic will               |
   |                                |                | be decreased;                     |
   |                                |                | ideally, this                     |
   |                                |                | statistic should be               |
   |                                |                | zero. If this                     |
   |                                |                | statistic is non-zero             |
   |                                |                | or increasing, a                  |
   |                                |                | network administrator             |
   |                                |                | should investigate                |
   |                                |                | whether there is a                |
   |                                |                | misbehaving device in             |
   |                                |                | the network. This is              |
   |                                |                | a global statistic                |
   |                                |                | that covers all                   |
   |                                |                | subnets.                          |
   +--------------------------------+----------------+-----------------------------------+
   | subnet[id].declined-addresses  | integer        | Number of IPv4                    |
   |                                |                | addresses that are                |
   |                                |                | currently declined in             |
   |                                |                | a given subnet; a                 |
   |                                |                | count of the number               |
   |                                |                | of leases currently               |
   |                                |                | unavailable. Once a               |
   |                                |                | lease is recovered,               |
   |                                |                | this statistic will               |
   |                                |                | be decreased;                     |
   |                                |                | ideally, this                     |
   |                                |                | statistic should be               |
   |                                |                | zero. If this                     |
   |                                |                | statistic is non-zero             |
   |                                |                | or increasing, a                  |
   |                                |                | network administrator             |
   |                                |                | should investigate                |
   |                                |                | whether there is a                |
   |                                |                | misbehaving device in             |
   |                                |                | the network. The *id*             |
   |                                |                | is the subnet-id of a             |
   |                                |                | given subnet. This                |
   |                                |                | statistic is exposed              |
   |                                |                | for each subnet                   |
   |                                |                | separately.                       |
   +--------------------------------+----------------+-----------------------------------+
   | reclaimed-declined-addresses   | integer        | Number of IPv4                    |
   |                                |                | addresses that were               |
   |                                |                | declined, but have                |
   |                                |                | now been recovered.               |
   |                                |                | Unlike                            |
   |                                |                | declined-addresses,               |
   |                                |                | this statistic never              |
   |                                |                | decreases. It can be              |
   |                                |                | used as a long-term               |
   |                                |                | indicator of how many             |
   |                                |                | actual valid Declines             |
   |                                |                | were processed and                |
   |                                |                | recovered from. This              |
   |                                |                | is a global statistic             |
   |                                |                | that covers all                   |
   |                                |                | subnets.                          |
   +--------------------------------+----------------+-----------------------------------+
   | subnet[id].reclaimed           | integer        | Number of IPv4                    |
   |  -declined-addresses           |                | addresses that were               |
   |                                |                | declined, but have                |
   |                                |                | now been recovered.               |
   |                                |                | Unlike                            |
   |                                |                | declined-addresses,               |
   |                                |                | this statistic never              |
   |                                |                | decreases. It can be              |
   |                                |                | used as a long-term               |
   |                                |                | indicator of how many             |
   |                                |                | actual valid Declines             |
   |                                |                | were processed and                |
   |                                |                | recovered from. The               |
   |                                |                | *id* is the subnet-id             |
   |                                |                | of a given subnet.                |
   |                                |                | This statistic is                 |
   |                                |                | exposed for each                  |
   |                                |                | subnet separately.                |
   +--------------------------------+----------------+-----------------------------------+

.. _dhcp4-ctrl-channel:

Management API for the DHCPv4 Server
====================================

The management API allows the issuing of specific management commands,
such as statistics retrieval, reconfiguration, or shutdown. For more
details, see :ref:`ctrl-channel`. Currently, the only supported
communication channel type is UNIX stream socket. By default there are
no sockets open; to instruct Kea to open a socket, the following entry
in the configuration file can be used:

::

   "Dhcp4": {
       "control-socket": {
           "socket-type": "unix",
           "socket-name": "/path/to/the/unix/socket"
       },

       "subnet4": [
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
<https://jenkins.isc.org/job/Kea_doc/doxygen/d2/d96/ctrlSocket.html>`__
for more details.

The DHCPv4 server supports the following operational commands:

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

.. _dhcp4-user-contexts:

User Contexts in IPv4
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

Let's consider an imaginary case of devices that have colored LED lights.
Depending on their location, they should glow red, blue, or green. It
would be easy to write a hook library that would send specific values as
maybe a vendor option. However, the server has to have some way to
specify that value for each pool. This need is addressed by user
contexts. In essence, any user data can be specified in the user context
as long as it is a valid JSON map. For example, the aforementioned case
of LED devices could be configured in the following way:

::

   "Dhcp4": {
       "subnet4": [{
           "subnet": "192.0.2.0/24",
           "pools": [{
               "pool": "192.0.2.10 - 192.0.2.20",
               # This is pool specific user context
               "user-context": { "color": "red" }
           }],

           # This is a subnet-specific user context. Any type
           # of information can be entered here as long as it is valid JSON.
           "user-context": {
               "comment": "network on the second floor",
               "last-modified": "2017-09-04 13:32",
               "description": "you can put anything you like here",
               "phones": [ "x1234", "x2345" ],
               "devices-registered": 42,
               "billing": false
           }
       }],
   }

Kea does not interpret or use the user context information; it simply stores it and makes it
available to the hook libraries. It is up to each hook library to
extract that information and use it. The parser translates a "comment"
entry into a user context with the entry, which allows a comment to be
attached inside the configuration itself.

.. _dhcp4-std:

Supported DHCP Standards
========================

The following standards are currently supported:

-  *BOOTP Vendor Information Extensions*, `RFC
   1497 <https://tools.ietf.org/html/rfc1497>`__: This requires the open
   source BOOTP hook to be loaded.

-  *Dynamic Host Configuration Protocol*, `RFC
   2131 <https://tools.ietf.org/html/rfc2131>`__: Supported messages are
   DHCPDISCOVER (1), DHCPOFFER (2), DHCPREQUEST (3), DHCPRELEASE (7),
   DHCPINFORM (8), DHCPACK (5), and DHCPNAK(6).

-  *DHCP Options and BOOTP Vendor Extensions*, `RFC
   2132 <https://tools.ietf.org/html/rfc2132>`__: Supported options are:
   PAD (0), END(255), Message Type(53), DHCP Server Identifier (54),
   Domain Name (15), DNS Servers (6), IP Address Lease Time (51), Subnet
   mask (1), and Routers (3).

-  *DHCP Relay Agent Information Option*, `RFC
   3046 <https://tools.ietf.org/html/rfc3046>`__: Relay Agent Information
   option is supported.

-  *Vendor-Identifying Vendor Options for Dynamic Host Configuration
   Protocol version 4*, `RFC
   3925 <https://tools.ietf.org/html/rfc3925>`__: Vendor-Identifying
   Vendor Class and Vendor-Identifying Vendor-Specific Information
   options are supported.

-  *The Dynamic Host Configuration Protocol (DHCP) Client Fully
   Qualified Domain Name (FQDN) Option*, `RFC 4702
   <https://tools.ietf.org/html/rfc4702>`__: The Kea server is able to
   handle the Client FQDN option. Also, it is able to use
   kea-dhcp-ddns component do initiate appropriate DNS Update
   operations.

-  *Resolution of Fully Qualified Domain Name (FQDN) Conflicts among Dynamic Host
   Configuration Protocol (DHCP) Clients*, `RFC 4703
   <https://tools.ietf.org/html/rfc4703>`__: The DHCPv6 server uses DHCP-DDNS
   server to resolve conflicts.

-  *Client Identifier Option in DHCP Server Replies*, `RFC
   6842 <https://tools.ietf.org/html/rfc6842>`__: Server by default sends
   back client-id option. That capability may be disabled. See :ref:`dhcp4-echo-client-id` for details.

-  *Generalized UDP Source Port for DHCP Relay*, `RFC 8357
   <https://tools.ietf.org/html/rfc8357>`__: The Kea server is able
   to handle Relay Agent Information Source Port suboption in a received
   message, remembers the UDP port  and sends back reply to the same relay
   agent using this UDP port.

.. _dhcp4-limit:

DHCPv4 Server Limitations
=========================

These are the current limitations of the DHCPv4 server software. Most of
them are reflections of the current stage of development and should be
treated as “not implemented yet,” rather than as actual limitations.
However, some of them are implications of the design choices made. Those
are clearly marked as such.

-  BOOTP (`RFC 951 <https://tools.ietf.org/html/rfc951>`__) is not
   supported. This is a design choice; historic BOOTP support is not planned.

-  BOOTP with vendor information extensions
   (`RFC 1497 <https://tools.ietf.org/html/rfc1497>`__) is supported
   by the BOOTP hooks library; see :ref:`hooks-bootp` for details.

-  On Linux and BSD system families the DHCP messages are sent and
   received over the raw sockets (using LPF and BPF) and all packet
   headers (including data link layer, IP, and UDP headers) are created
   and parsed by Kea, rather than by the system kernel. Currently, Kea
   can only parse the data link layer headers with a format adhering to
   the IEEE 802.3 standard and assumes this data link layer header
   format for all interfaces. Thus, Kea will fail to work on interfaces
   which use different data link layer header formats (e.g. Infiniband).

-  The DHCPv4 server does not verify that an assigned address is unused.
   According to `RFC 2131 <https://tools.ietf.org/html/rfc2131>`__, the
   allocating server should verify that an address is not used by
   sending an ICMP echo request.

.. _dhcp4-srv-examples:

Kea DHCPv4 Server Examples
==========================

A collection of simple-to-use examples for the DHCPv4 component of Kea
is available with the source files, located in the doc/examples/kea4
directory.

.. _dhcp4-cb:

Configuration Backend in DHCPv4
===============================

In the :ref:`config-backend` section we have described the Configuration
Backend feature, its applicability, and its limitations. This section focuses
on the usage of the CB with the DHCPv4 server. It lists the supported
parameters, describes limitations, and gives examples of the DHCPv4
server configuration to take advantage of the CB. Please also refer to
the sibling section :ref:`dhcp6-cb` for the DHCPv6-specific usage of
the CB.

.. _dhcp4-cb-parameters:

Supported Parameters
--------------------

The ultimate goal for the CB is to serve as a central configuration
repository for one or multiple Kea servers connected to the database. In
the future it will be possible to store most of the server's
configuration in the database and reduce the configuration file to a bare
minimum; the only mandatory parameter will be
``config-control``, which includes the necessary information to connect
to the database. In the Kea 1.6.0 release, however, only a subset of
the DHCPv4 server parameters can be stored in the database. All other
parameters must be specified in the JSON configuration file, if
required.

The following table lists DHCPv4 specific parameters supported by the
Configuration Backend, with an indication on which level of the hierarchy
it is currently supported. "n/a" is used in cases when a
given parameter is not applicable on a particular level of the
hierarchy, or in cases when the parameter is not supported by the server
at this level of the hierarchy. "no" is used when the parameter is
supported by the server on the given level of the hierarchy, but is not
configurable via the Configuration Backend.

All supported parameters can be configured via the ``cb_cmds`` hooks library
described in the :ref:`cb-cmds-library` section. The general rule is that
the scalar global parameters are set using
``remote-global-parameter4-set``; the shared network-specific parameters
are set using ``remote-network4-set``; and the subnet- and pool-level
parameters are set using ``remote-subnet4-set``. Whenever
there is an exception to this general rule, it is highlighted in the
table. The non-scalar global parameters have dedicated commands; for example,
the global DHCPv4 options (``option-data``) are modified using
``remote-option4-global-set``.

The :ref:`cb-sharing` explains the concept of shareable
and non-shareable configuration elements and the limitations for
sharing them between multiple servers. In the DHCP configuration (both DHCPv4
and DHCPv6) the shareable configuration elements are: subnets and shared
networks. Thus, they can be explicitly associated with multiple server tags.
The global parameters, option definitions and global options are non-shareable
and they can be associated with only one server tag. This rule does not apply
to the configuration elements associated with "all" servers. Any configuration
element associated with "all" servers (using "all" keyword as a server tag) is
used by all servers connecting to the configuration database.

.. table:: List of DHCPv4 Parameters Supported by the Configuration Backend

   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | Parameter                   | Global                     | Shared      | Subnet      | Pool        |
   |                             |                            | Network     |             |             |
   +=============================+============================+=============+=============+=============+
   | 4o6-interface               | n/a                        | n/a         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | 4o6-interface-id            | n/a                        | n/a         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | 4o6-subnet                  | n/a                        | n/a         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | boot-file-name              | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | calculate-tee-times         | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | client-class                | n/a                        | yes         | yes         | yes         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | ddns-send-update            | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | ddns-override-no-update     | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | ddns-override-client-update | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | ddns-replace-client-name    | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | ddns-generated-prefix       | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | ddns-qualifying-suffix      | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | decline-probation-period    | yes                        | n/a         | n/a         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | dhcp4o6-port                | yes                        | n/a         | n/a         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | echo-client-id              | yes                        | n/a         | n/a         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | hostname-char-set           | no                         | no          | no          | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | hostname-char-replacement   | no                         | no          | no          | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | interface                   | n/a                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | match-client-id             | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | next-server                 | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | option-data                 | yes (via                   | yes         | yes         | yes         |
   |                             | remote-option4-global-set) |             |             |             |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | option-def                  | yes (via                   | n/a         | n/a         | n/a         |
   |                             | remote-option-def4-set)    |             |             |             |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | rebind-timer                | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | renew-timer                 | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | server-hostname             | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | valid-lifetime              | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | relay                       | n/a                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | require-client-classes      | no                         | yes         | yes         | yes         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | reservation-mode            | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | t1-percent                  | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+
   | t2-percent                  | yes                        | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+-------------+-------------+-------------+

.. _dhcp4-cb-json:

Enabling Configuration Backend
------------------------------

Consider the following configuration snippet:

::

   "Dhcp4": {
       "server-tag": "my DHCPv4 server",
       "config-control": {
           "config-databases": [{
               "type": "mysql",
               "name": "kea",
               "user": "kea",
               "password": "kea",
               "host": "192.0.2.1",
               "port": 3302
           }],
           "config-fetch-wait-time": 20
       },
       "hooks-libraries": [{
           "library": "/usr/local/lib/kea/hooks/libdhcp_mysql_cb.so"
       }, {
           "library": "/usr/local/lib/kea/hooks/libdhcp_cb_cmds.so"
       }],
   }

The ``config-control`` command contains two parameters. ``config-databases``
is a list which contains one element comprising database type, location,
and the credentials to be used to connect to this database. (Note that
the parameters specified here correspond to the database specification
for the lease database backend and hosts database backend.) Currently
only one database connection can be specified on the
``config-databases`` list. The server will connect to this database
during the startup or reconfiguration, and will fetch the configuration
available for this server from the database. This configuration is
merged into the configuration read from the configuration file.

.. note::

   Whenever there is a conflict between the parameters specified in the
   configuration file and the database, the parameters from the database
   take precedence. We strongly recommend avoiding the duplication of
   parameters in the file and the database, but this recommendation is
   not enforced by the Kea servers. In particular, if the subnets'
   configuration is sourced from the database, we recommend that all
   subnets be specified in the database and that no subnets be specified in
   the configuration file. It is possible to specify the subnets in both
   places, but the subnets in the
   configuration file with overlapping ids and/or prefixes with the
   subnets from the database will be superseded by those from the
   database.

Once the Kea server is configured, it starts periodically polling for
the configuration changes in the database. The frequency of polling is
controlled by the ``config-fetch-wait-time`` parameter, expressed
in seconds; it is the period between the time when the server
completed last polling (and possibly the local configuration update) and
the time when it will begin polling again. In the example above, this period
is set to 20 seconds. This means that after adding a new configuration
into the database (e.g. adding new subnet), it will take up to 20 seconds
(plus the time needed to fetch and apply the new configuration) before
the server starts using this subnet. The lower the
``config-fetch-wait-time`` value, the shorter the time for the server to
react to the incremental configuration updates in the database. On the
other hand, polling the database too frequently may impact the DHCP
server's performance, because the server needs to make at least one query
to the database to discover the pending configuration updates. The
default value of the ``config-fetch-wait-time`` is 30 seconds.

The ``config-backend-pull`` command can be used to force the server to
immediately poll the configuration changes from the database and avoid
waiting for the next fetch cycle. The command was added in 1.7.1 Kea
release for DHCPv4 and DHCPv6 servers.

Finally, in the configuration example above, two hooks libraries are
loaded. The first, ``libdhcp_mysql_cb.so``, is the implementation of
the Configuration Backend for MySQL. It must be always present when the
server uses MySQL as the configuration repository. Failing to load this
library will result in an error during the server configuration if the
"mysql" database is selected with the ``config-control`` parameter.

The second hooks library, ``libdhcp_cb_cmds.so``, is optional. It should
be loaded when the Kea server instance is to be used for managing the
configuration in the database. See the :ref:`cb-cmds-library` section for
details. Note that this hooks library is only available to ISC
customers with a support contract.
