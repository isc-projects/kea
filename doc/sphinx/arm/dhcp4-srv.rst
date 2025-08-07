.. _dhcp4:

*****************
The DHCPv4 Server
*****************

.. _dhcp4-start-stop:

Starting and Stopping the DHCPv4 Server
=======================================

It is recommended that the Kea DHCPv4 server be started and stopped
using :iscman:`keactrl` (described in :ref:`keactrl`); however, it is also
possible to run the server directly via the :iscman:`kea-dhcp4` command, which accepts
the following command-line switches:

-  ``-c file`` - specifies the configuration file. This is the only
   mandatory switch.

-  ``-d`` - specifies whether the server logging should be switched to
   debug/verbose mode. In verbose mode, the logging severity and debuglevel
   specified in the configuration file are ignored; "debug" severity
   and the maximum debuglevel (99) are assumed. The flag is convenient
   for temporarily switching the server into maximum verbosity, e.g.
   when debugging.

-  ``-p server-port`` - specifies the local UDP port on which the server
   listens. This is only useful during testing, as a DHCPv4 server
   listening on ports other than the standard ones is not able to
   handle regular DHCPv4 queries.

-  ``-P client-port`` - specifies the remote UDP port to which the
   server sends all responses. This is only useful during testing,
   as a DHCPv4 server sending responses to ports other than the standard
   ones is not able to handle regular DHCPv4 queries.

-  ``-t file`` - specifies a configuration file to be tested. :iscman:`kea-dhcp4`
   loads it, checks it, and exits. During the test, log messages are
   printed to standard output and error messages to standard error. The
   result of the test is reported through the exit code (0 =
   configuration looks OK, 1 = error encountered). The check is not
   comprehensive; certain checks are possible only when running the
   server.

-  ``-T file`` - specifies a configuration file to be tested. :iscman:`kea-dhcp4`
   loads it, checks it, and exits. It performs extra checks beyond what ``-t``
   offers, such as establishing database connections (for the lease backend,
   host reservations backend, configuration backend, and forensic logging
   backend), loading hook libraries, parsing hook-library configurations, etc.
   It does not open UNIX or TCP/UDP sockets, nor does it open or rotate
   files, as any of these actions could interfere with a running process on the
   same machine.

-  ``-v`` - displays the Kea version and exits.

-  ``-V`` - displays the Kea extended version with additional parameters
   and exits. The listing includes the versions of the libraries
   dynamically linked to Kea.

-  ``-W`` - displays the Kea configuration report and exits. The report
   is a copy of the ``config.report`` file produced by ``meson setup``;
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

-  ``-X`` - As of Kea 3.0, disables security restrictions. The server will
   still check for violations but will emit warning logs when they are found
   rather than fail with an error. Please see
   :ref:`sec-kea-runtime-security-policy-checking` for details.

On startup, the server detects available network interfaces and
attempts to open UDP sockets on all interfaces listed in the
configuration file. Since the DHCPv4 server opens privileged ports, it
requires root access; this daemon must be run as root.

During startup, the server attempts to create a PID file of the
form: ``[pidfile_dir]/[conf name].kea-dhcp4.pid`` where:

- ``pidfile_dir`` - is ``[prefix]/[localstatedir]/run/kea`` where
  ``prefix`` and ``localstatedir`` are the values passed into meson setup using
  ``--prefix`` and ``--localstatedir`` which default to ``/usr/local`` and
  ``var`` respectively. So the whole ``pidfile_dir`` defaults to
  ``/usr/local/var``. Note that this value may be overridden at runtime by
  setting the environment variable  ``KEA_PIDFILE_DIR`` intended primarily for
  testing purposes.

- ``conf name``: The configuration file name used to start the server,
  minus all preceding paths and the file extension. For example, given
  a pathname of ``/usr/local/etc/kea/myconf.txt``, the portion used would
  be ``myconf``.

If the file already exists and contains the PID of a live process, the
server issues a ``DHCP4_ALREADY_RUNNING`` log message and exits. It is
possible, though unlikely, that the file is a remnant of a system crash
and the process to which the PID belongs is unrelated to Kea. In such a
case, it would be necessary to manually delete the PID file.

The server can be stopped using the ``kill`` command. When running in a
console, the server can also be shut down by pressing Ctrl-c. Kea detects
the key combination and shuts down gracefully.

The reconfiguration of each Kea server is triggered by the SIGHUP signal.
When a server receives the SIGHUP signal it rereads its configuration file and,
if the new configuration is valid, uses the new configuration.
If the new configuration proves to be invalid, the server retains its
current configuration; however, in some cases a fatal error message is logged
indicating that the server is no longer providing any service: a working
configuration must be loaded as soon as possible.

.. _dhcp4-configuration:

DHCPv4 Server Configuration
===========================

Introduction
------------

This section explains how to configure the Kea DHCPv4 server using a
configuration file.

Before DHCPv4 is started, its configuration file must
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
               "id": 1,
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
above, this object is called ``Dhcp4``.

The ``Dhcp4`` configuration starts with the ``"Dhcp4": {`` line and ends
with the corresponding closing brace (in the above example, the brace
after the last comment). Everything defined between those lines is
considered to be the ``Dhcp4`` configuration.

In general, the order in which those parameters appear does not
matter, but there are two caveats. The first one is that the
configuration file must be well-formed JSON, meaning that the
parameters for any given scope must be separated by a comma, and there
must not be a comma after the last parameter. When reordering a
configuration file, moving a parameter to or from the
last position in a given scope may also require moving the comma. The
second caveat is that it is uncommon — although legal JSON — to repeat
the same parameter multiple times. If that happens, the last occurrence
of a given parameter in a given scope is used, while all previous
instances are ignored. This is unlikely to cause any confusion as there
are no real-life reasons to keep multiple copies of the same parameter
in the configuration file.

The first few DHCPv4 configuration elements
define some global parameters. ``valid-lifetime`` defines how long the
addresses (leases) given out by the server are valid; the default
is for a client to be allowed to use a given address for 4000
seconds. (Note that integer numbers are specified as is, without any
quotes around them.) ``renew-timer`` and ``rebind-timer`` are values
(also in seconds) that define the T1 and T2 timers that govern when the
client begins the renewal and rebind processes.

.. note::

   The lease valid lifetime is expressed as a triplet with minimum, default, and
   maximum values using configuration entries
   ``min-valid-lifetime``, ``valid-lifetime``, and ``max-valid-lifetime``.
   Since Kea 1.9.5, these values may be specified in client classes. The procedure
   the server uses to select which lifetime value to use is as follows:

   If the client query is a BOOTP query, the server always uses the
   infinite lease time (e.g. 0xffffffff). Otherwise, the server must
   determine which configured triplet to use by first searching all
   classes assigned to the query, and then the subnet selected for
   the query.

   Classes are searched in the order they were assigned to the query; the
   server uses the triplet from the first class that specifies it.
   If no classes specify the triplet, the server uses the triplet
   specified by the subnet selected for the client. If the subnet does not
   explicitly specify it, the server next looks at the subnet's
   shared-network (if one exists), then for a global specification, and
   finally the global default.

   If the client requested a lifetime value via DHCP option 51, then the
   lifetime value used is the requested value bounded by the configured
   triplet. In other words, if the requested lifetime is less than the
   configured minimum, the configured minimum is used; if it is more
   than the configured maximum, the configured maximum is used. If
   the client did not provide a requested value, the lifetime value used
   is the triplet default value.

.. note::

   Both ``renew-timer`` and ``rebind-timer``
   are optional. The server only sends ``rebind-timer`` to the client,
   via DHCPv4 option code 59, if it is less than ``valid-lifetime``; and it
   only sends ``renew-timer``, via DHCPv4 option code 58, if it is less
   than ``rebind-timer`` (or ``valid-lifetime`` if ``rebind-timer`` was not
   specified). In their absence, the client should select values for T1
   and T2 timers according to `RFC 2131 <https://tools.ietf.org/html/rfc2131>`_.
   See section :ref:`dhcp4-t1-t2-times`
   for more details on generating T1 and T2.

The ``interfaces-config`` map specifies the network interfaces on which the
server should listen to DHCP messages. The ``interfaces`` parameter specifies
a list of network interfaces on which the server should listen. Lists are
opened and closed with square brackets, with elements separated by commas. To
listen on two interfaces, the ``interfaces-config`` element should look like
this:

::

   {
   "interfaces-config": {
       "interfaces": [ "eth0", "eth1" ]
   },
   ...
   }

The next lines define the lease database, the place where the
server stores its lease information. This particular example tells the
server to use memfile, which is the simplest and fastest database
backend. It uses an in-memory database and stores leases on disk in a
CSV (comma-separated values) file. This is a very simple configuration example;
usually the lease database configuration is more extensive and contains
additional parameters. Note that ``lease-database`` is an object and opens up a
new scope, using an opening brace. Its parameters (just one in this example:
``type``) follow. If there were more than one, they would be separated
by commas. This scope is closed with a closing brace. As more parameters
for the ``Dhcp4`` definition follow, a trailing comma is present.

Finally, we need to define a list of IPv4 subnets. This is the most
important DHCPv4 configuration structure, as the server uses that
information to process clients' requests. It defines all subnets from
which the server is expected to receive DHCP requests. The subnets are
specified with the ``subnet4`` parameter. It is a list, so it starts and
ends with square brackets. Each subnet definition in the list has
several attributes associated with it, so it is a structure and is
opened and closed with braces. At a minimum, a subnet definition must
have at least two parameters: ``subnet``, which defines the whole
subnet; and ``pools``, which is a list of dynamically allocated pools
that are governed by the DHCP server.

The example contains a single subnet. If more than one were defined,
additional elements in the ``subnet4`` parameter would be specified and
separated by commas. For example, to define three subnets, the following
syntax would be used:

::

   {
   "subnet4": [
       {
           "id": 1,
           "pools": [ { "pool":  "192.0.2.1 - 192.0.2.200" } ],
           "subnet": "192.0.2.0/24"
       },
       {
           "id": 2,
           "pools": [ { "pool": "192.0.3.100 - 192.0.3.200" } ],
           "subnet": "192.0.3.0/24"
       },
       {
           "id": 3,
           "pools": [ { "pool": "192.0.4.1 - 192.0.4.254" } ],
           "subnet": "192.0.4.0/24"
       }
   ],
   ...
   }

Note that indentation is optional and is used for aesthetic purposes
only. In some cases it may be preferable to use more compact notation.

After all the parameters have been specified, there are two contexts open:
``global`` and ``Dhcp4``; thus, two closing curly brackets must be used to close
them.

Lease Storage
-------------

All leases issued by the server are stored in the lease database.
There are three database backends available: memfile
(the default), MySQL, PostgreSQL.

Memfile - Basic Storage for Leases
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The server is able to store lease data in different repositories. Larger
deployments may elect to store leases in a database;
:ref:`database-configuration4` describes this option. In
typical smaller deployments, though, the server stores lease
information in a CSV file rather than a database. As well as requiring
less administration, an advantage of using a file for storage is that it
eliminates a dependency on third-party database software.

The configuration of the memfile backend is controlled through
the ``Dhcp4``/``lease-database`` parameters. The ``type`` parameter is mandatory
and specifies which storage for leases the server should use, through
the ``"memfile"`` value. The following list gives additional optional parameters
that can be used to configure the memfile backend.

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

-  ``name``: specifies the lease file in which new leases and lease updates
   are recorded. The default value for this parameter is
   ``"[kea-install-dir]/var/lib/kea/kea-leases4.csv"``.

.. note::

    As of Kea 2.7.9, lease files may only be loaded from the data directory
    determined during compilation: ``"[kea-install-dir]/var/lib/kea"``. This
    path may be overridden at startup by setting the environment variable
    ``KEA_DHCP_DATA_DIR`` to the desired path.  If a path other than
    this value is used in ``name``, Kea will emit an error and refuse to start
    or, if already running, log an unrecoverable error.  For ease of use in
    specifying a custom file name simply omit the path component from ``name``.

-  ``lfc-interval``: specifies the interval, in seconds, at which the
   server will perform a lease file cleanup (LFC). This removes
   redundant (historical) information from the lease file and
   effectively reduces the lease file size. The cleanup process is
   described in more detail later in this section. The default
   value of the ``lfc-interval`` is ``3600``. A value of ``0`` disables the LFC.

-  ``max-row-errors``: specifies the number of row errors before the server
   stops attempting to load a lease file. When the server loads a lease file, it is processed
   row by row, each row containing a single lease. If a row is flawed and
   cannot be processed correctly the server logs it, discards the row,
   and goes on to the next row. This parameter can be used to set a limit on
   the number of such discards that can occur, after which the server
   abandons the effort and exits. The default value of ``0`` disables the limit
   and allows the server to process the entire file, regardless of how many
   rows are discarded.

An example configuration of the memfile backend is presented below:

::

   "Dhcp4": {
       "lease-database": {
           "type": "memfile",
           "persist": true,
           "name": "kea-leases4.csv",
           "lfc-interval": 1800,
           "max-row-errors": 100
       }
   }

This configuration selects ``kea-leases4.csv`` as the storage
for lease information and enables persistence (writing lease updates to
this file). It also configures the backend to perform a periodic cleanup
of the lease file every 1800 seconds (30 minutes) and sets the maximum number of
row errors to 100.

Why Is Lease File Cleanup Necessary?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is important to know how the lease file contents are organized to
understand why the periodic lease file cleanup is needed. Every time the
server updates a lease or creates a new lease for a client, the new
lease information must be recorded in the lease file. For performance
reasons, the server does not update the existing client's lease in the
file, as this would potentially require rewriting the entire file.
Instead, it simply appends the new lease information to the end of the
file; the previous lease entries for the client are not removed. When
the server loads leases from the lease file, e.g. at server startup,
it assumes that the latest lease entry for the client is the valid one.
Previous entries are discarded, meaning that the server can
reconstruct accurate information about the leases even though there
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
previous cleanup was still in progress, but it implies that the actual
cleanups will be triggered more rarely than the configured interval. Moreover,
triggering a new cleanup adds overhead to the server, which is not
able to respond to new requests for a short period of time when the new
cleanup process is spawned. Therefore, it is recommended that the
``lfc-interval`` value be selected in a way that allows the LFC
to complete the cleanup before a new cleanup is triggered.

Lease file cleanup is performed by a separate process (in the
background) to avoid a performance impact on the server process. To
avoid conflicts between two processes using the same lease
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

.. note::

   Kea requires the database timezone to match the system timezone.
   For more details, see :ref:`mysql-database-create` and
   :ref:`pgsql-database-create`.

Lease database configuration is controlled through the
``Dhcp4``/``lease-database`` parameters. The database type must be set to
``memfile``, ``mysql`` or ``postgresql``, e.g.:

::

   "Dhcp4": { "lease-database": { "type": "mysql", ... }, ... }

Next, the name of the database to hold the leases must be set; this is
the name used when the database was created (see
:ref:`mysql-database-create` or :ref:`pgsql-database-create`).

For MySQL or PostgreSQL:

::

   "Dhcp4": { "lease-database": { "name": "database-name" , ... }, ... }

If the database is located on a different system from the DHCPv4 server,
the database host name must also be specified:

::

   "Dhcp4": { "lease-database": { "host": "remote-host-name", ... }, ... }

Normally, the database is on the same machine as the DHCPv4 server.
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

The maximum number of times the server automatically attempts to
reconnect to the lease database after connectivity has been lost may be
specified:

::

   "Dhcp4": { "lease-database": { "max-reconnect-tries" : number-of-tries, ... }, ... }

If the server is unable to reconnect to the database after making the
maximum number of attempts, the server will exit. A value of 0 (the
default) disables automatic recovery and the server will exit
immediately upon detecting a loss of connectivity (MySQL and PostgreSQL
only).

The number of milliseconds the server waits between attempts to
reconnect to the lease database after connectivity has been lost may
also be specified:

::

   "Dhcp4": { "lease-database": { "reconnect-wait-time" : number-of-milliseconds, ... }, ... }

The default value for MySQL and PostgreSQL is 0, which disables automatic
recovery and causes the server to exit immediately upon detecting the
loss of connectivity.

::

   "Dhcp4": { "lease-database": { "on-fail" : "stop-retry-exit", ... }, ... }

The possible values are:

-  ``stop-retry-exit`` - disables the DHCP service while trying to automatically
   recover lost connections, and shuts down the server on failure after exhausting
   ``max-reconnect-tries``. This is the default value for the lease backend,
   the host backend, and the configuration backend.

-  ``serve-retry-exit`` - continues the DHCP service while trying to
   automatically recover lost connections, and shuts down the server on failure
   after exhausting ``max-reconnect-tries``.

-  ``serve-retry-continue`` - continues the DHCP service and does not shut down
   the server even if the recovery fails. This is the default value for forensic
   logging.

.. note::

   Automatic reconnection to database backends is configured individually per
   backend; this allows users to tailor the recovery parameters to each backend
   they use. We suggest that users enable it either for all backends or none,
   so behavior is consistent.

   Losing connectivity to a backend for which reconnection is disabled results
   (if configured) in the server shutting itself down. This includes cases when
   the lease database backend and the hosts database backend are connected to
   the same database instance.

   It is highly recommended not to change the ``stop-retry-exit`` default
   setting for the lease manager, as it is critical for the connection to be
   active while processing DHCP traffic. Change this only if the server is used
   exclusively as a configuration tool.

::

   "Dhcp4": { "lease-database": { "retry-on-startup" : true, ... }, ... }

During server startup, the inability to connect to any of the configured
backends is considered fatal only if ``retry-on-startup`` is set to ``false``
(the default). A fatal error is logged and the server exits, based on the idea
that the configuration should be valid at startup. Exiting to the operating
system allows nanny scripts to detect the problem.
If ``retry-on-startup`` is set to ``true``, the server starts reconnection
attempts even at server startup or on reconfigure events, and honors the
action specified in the ``on-fail`` parameter.

The host parameter is used by the MySQL and PostgreSQL backends.

Finally, the credentials of the account under which the server will
access the database should be set:

::

   "Dhcp4": {
       "lease-database": {
           "user": "user-name",
           "password": "1234",
           ...
       },
       ...
   }

If there is no password to the account, set the password to the empty
string ``""``. (This is the default.)

.. _tuning-database-timeouts4:

Tuning Database Timeouts
~~~~~~~~~~~~~~~~~~~~~~~~

In rare cases, reading or writing to the database may hang. This can be
caused by a temporary network issue, or by misconfiguration of the proxy
server switching the connection between different database instances.
These situations are rare, but users have reported
that Kea sometimes hangs while performing database IO operations.
Setting appropriate timeout values can mitigate such issues.

MySQL exposes two distinct connection options to configure the read and
write timeouts. Kea's corresponding ``read-timeout`` and  ``write-timeout``
configuration parameters specify the timeouts in seconds. For example:

::

   "Dhcp4": { "lease-database": { "read-timeout" : 10, "write-timeout": 20, ... }, ... }


Setting these parameters to 0 is equivalent to not specifying them, and
causes the Kea server to establish a connection to the database with the
MySQL defaults. In this case, Kea waits indefinitely for the completion of
the read and write operations.

MySQL versions earlier than 5.6 do not support setting timeouts for
read and write operations. Moreover, the ``read-timeout`` and ``write-timeout``
parameters can only be specified for the MySQL backend; setting them for
any other backend database type causes a configuration error.

To set a timeout in seconds for PostgreSQL, use the ``tcp-user-timeout``
parameter. For example:

::

   "Dhcp4": { "lease-database": { "tcp-user-timeout" : 10, ... }, ... }


Specifying this parameter for other backend types causes a configuration
error.

.. note::

    The timeouts described here are only effective for TCP connections.
    Please note that the MySQL client library used by the Kea servers
    typically connects to the database via a UNIX domain socket when the
    ``host`` parameter is ``localhost``, but establishes a TCP connection
    for ``127.0.0.1``.

Since Kea.2.7.4, the libdhcp_mysql.so hook library must be loaded in order to
store leases in the MySQL Lease Database Backend.
Specify the lease backend hook library location:

::

   "Dhcp4": { "hooks-libraries": [
       {
           // the MySQL lease backend hook library required for lease storage.
           "library": "/opt/lib/kea/hooks/libdhcp_mysql.so"
       }, ... ], ... }

Since Kea.2.7.4, the libdhcp_pgsql.so hook library must be loaded in order to
store leases in the PostgreSQL Lease Database Backend.
Specify the lease backend hook library location.

::

   "Dhcp4": { "hooks-libraries": [
       {
           // the PostgreSQL lease backend hook library required for lease storage.
           "library": "/opt/lib/kea/hooks/libdhcp_pgsql.so"
       }, ... ], ... }


.. _hosts4-storage:

Hosts Storage
-------------

Kea is also able to store information about host reservations in the
database. The hosts database configuration uses the same syntax as the
lease database. In fact, the Kea server opens independent connections for
each purpose, be it lease or hosts information, which gives
the most flexibility. Kea can keep leases and host reservations
separately, but can also point to the same database. Currently the
supported hosts database types are MySQL and PostgreSQL.

The following configuration can be used to configure a
connection to MySQL:

::

   "Dhcp4": {
       "hosts-database": {
           "type": "mysql",
           "name": "kea",
           "user": "kea",
           "password": "1234",
           "host": "localhost",
           "port": 3306
       }
   }

Depending on the database configuration, many of the
parameters may be optional.

Please note that usage of hosts storage is optional. A user can define
all host reservations in the configuration file, and that is the
recommended way if the number of reservations is small. However, when
the number of reservations grows, it is more convenient to use host
storage. Please note that both storage methods (the configuration file and
one of the supported databases) can be used together. If hosts are
defined in both places, the definitions from the configuration file are
checked first and external storage is checked later, if necessary.

Host information can be placed in multiple stores. Operations
are performed on the stores in the order they are defined in the
configuration file, although this leads to a restriction in ordering
in the case of a host reservation addition; read-only stores must be
configured after a (required) read-write store, or the addition will
fail.

.. note::

   Kea requires the database timezone to match the system timezone.
   For more details, see :ref:`mysql-database-create` and
   :ref:`pgsql-database-create`.

.. _hosts-databases-configuration4:

DHCPv4 Hosts Database Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hosts database configuration is controlled through the
``Dhcp4``/``hosts-database`` parameters. If enabled, the type of database must
be set to ``mysql`` or ``postgresql``.

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

Normally, the database is on the same machine as the DHCPv4 server.
In this case, set the value to the empty string:

::

   "Dhcp4": { "hosts-database": { "host" : "", ... }, ... }

Should the database use a port different than the default, it may be
specified as well:

::

   "Dhcp4": { "hosts-database": { "port" : 12345, ... }, ... }

The maximum number of times the server automatically attempts to
reconnect to the host database after connectivity has been lost may be
specified:

::

   "Dhcp4": { "hosts-database": { "max-reconnect-tries" : number-of-tries, ... }, ... }

If the server is unable to reconnect to the database after making the
maximum number of attempts, the server will exit. A value of 0 (the
default) disables automatic recovery and the server will exit
immediately upon detecting a loss of connectivity (MySQL and PostgreSQL
only).

The number of milliseconds the server waits between attempts to
reconnect to the host database after connectivity has been lost may also
be specified:

::

   "Dhcp4": { "hosts-database": { "reconnect-wait-time" : number-of-milliseconds, ... }, ... }

The default value for MySQL and PostgreSQL is 0, which disables automatic
recovery and causes the server to exit immediately upon detecting the
loss of connectivity.

::

   "Dhcp4": { "hosts-database": { "on-fail" : "stop-retry-exit", ... }, ... }

The possible values are:

-  ``stop-retry-exit`` - disables the DHCP service while trying to automatically
   recover lost connections. Shuts down the server on failure after exhausting
   ``max-reconnect-tries``. This is the default value for MySQL and PostgreSQL.

-  ``serve-retry-exit`` - continues the DHCP service while trying to automatically
   recover lost connections. Shuts down the server on failure after exhausting
   ``max-reconnect-tries``.

-  ``serve-retry-continue`` - continues the DHCP service and does not shut down the
   server even if the recovery fails.

.. note::

   Automatic reconnection to database backends is configured individually per
   backend. This allows users to tailor the recovery parameters to each backend
   they use. We suggest that users enable it either for all backends or none,
   so behavior is consistent.

   Losing connectivity to a backend for which reconnection is disabled results
   (if configured) in the server shutting itself down. This includes cases when
   the lease database backend and the hosts database backend are connected to
   the same database instance.

::

   "Dhcp4": { "hosts-database": { "retry-on-startup" : true, ... }, ... }

During server startup, the inability to connect to any of the configured
backends is considered fatal only if ``retry-on-startup`` is set to ``false``
(the default). A fatal error is logged and the server exits, based on the idea
that the configuration should be valid at startup. Exiting to the operating
system allows nanny scripts to detect the problem.
If ``retry-on-startup`` is set to ``true``, the server starts reconnection
attempts even at server startup or on reconfigure events, and honors the
action specified in the ``on-fail`` parameter.

Finally, the credentials of the account under which the server will
access the database should be set:

::

   "Dhcp4": {
       "hosts-database": {
           "user": "user-name",
           "password": "1234",
           ...
       },
       ...
   }

If there is no password to the account, set the password to the empty
string ``""``. (This is the default.)

The multiple-storage extension uses a similar syntax; a configuration is
placed into a ``hosts-databases`` list instead of into a ``hosts-database``
entry, as in:

::

   "Dhcp4": { "hosts-databases": [ { "type": "mysql", ... }, ... ], ... }

If the same host is configured both in-file and in-database, Kea does not issue a warning,
as it would if both were specified in the same data source.
Instead, the host configured in-file has priority over the one configured
in-database.

.. _read-only-database-configuration4:

Using Read-Only Databases for Host Reservations With DHCPv4
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In some deployments, the user whose name is specified in the
database backend configuration may not have write privileges to the
database. This is often required by the policy within a given network to
secure the data from being unintentionally modified. In many cases
administrators have deployed inventory databases, which contain
substantially more information about the hosts than just the static
reservations assigned to them. The inventory database can be used to
create a view of a Kea hosts database and such a view is often
read-only.

Kea host-database backends operate with an implicit configuration to
both read from and write to the database. If the user does not
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

   The ``readonly`` parameter is only supported for MySQL and
   PostgreSQL databases.

Since Kea.2.7.4, the libdhcp_mysql.so hook library must be loaded in order to
store host reservations in the MySQL Host Database Backend.
Specify the lease backend hook library location:

::

   "Dhcp4": { "hooks-libraries": [
       {
           // the MySQL host backend hook library required for host storage.
           "library": "/opt/lib/kea/hooks/libdhcp_mysql.so"
       }, ... ], ... }

Since Kea.2.7.4, the libdhcp_pgsql.so hook library must be loaded in order to
store host reservations in the PostgreSQL Host Database Backend.
Specify the lease backend hook library location.

::

   "Dhcp4": { "hooks-libraries": [
       {
           // the PostgreSQL host backend hook library required for host storage.
           "library": "/opt/lib/kea/hooks/libdhcp_pgsql.so"
       }, ... ], ... }


Tuning Database Timeouts for Hosts Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

See :ref:`tuning-database-timeouts4`.

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
       },
       ...
   }

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


It is possible to use an interface wildcard (*) concurrently
with explicit interface names:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3", "*" ]
       },
       ...
   }

This format should only be used when it is
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

Kea supports responding to directly connected clients which do not have
an address configured. This requires the server to inject the hardware
address of the destination into the data-link layer of the packet
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
from the relay agents, the Kea server should be configured to use UDP
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


The ``dhcp-socket-type`` parameter specifies that the IP/UDP sockets will be
opened on all interfaces on which the server listens, i.e. "eth1" and
"eth3" in this example. If ``dhcp-socket-type`` is set to ``raw``, it
configures the server to use raw sockets instead. If the
``dhcp-socket-type`` value is not specified, the default value ``raw``
is used.

Using UDP sockets automatically disables the reception of broadcast
packets from directly connected clients. This effectively means that UDP
sockets can be used for relayed traffic only. When using raw sockets,
both the traffic from the directly connected clients and the relayed
traffic are handled.

Caution should be taken when configuring the server
to open multiple raw sockets on the interface with several IPv4
addresses assigned. If the directly connected client sends the message
to the broadcast address, all sockets on this link will receive this
message and multiple responses will be sent to the client. Therefore,
the configuration with multiple IPv4 addresses assigned to the interface
should not be used when the directly connected clients are operating on
that link. To use a single address on such an interface, the
"interface-name/address" notation should be used.

.. note::

   Specifying the value ``raw`` as the socket type does not guarantee
   that raw sockets will be used! The use of raw sockets to handle
   traffic from the directly connected clients is currently
   supported on Linux and BSD systems only. If raw sockets are not
   supported on the particular OS in use, the server issues a warning and
   fall back to using IP/UDP sockets.

In a typical environment, the DHCP server is expected to send back a
response on the same network interface on which the query was received.
This is the default behavior. However, in some deployments it is desired
that the outbound (response) packets be sent as regular traffic and
the outbound interface be determined by the routing tables. This
kind of asymmetric traffic is uncommon, but valid. Kea supports a
parameter called ``outbound-interface`` that controls this behavior. It
supports two values: the first one, ``same-as-inbound``, tells Kea to
send back the response on the same interface where the query packet was
received. This is the default behavior. The second parameter, ``use-routing``,
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


Note that interfaces are not re-detected during :isccmd:`config-test`.

Usually loopback interfaces (e.g. the ``lo`` or ``lo0`` interface) are not
configured, but if a loopback interface is explicitly configured and
IP/UDP sockets are specified, the loopback interface is accepted.

For example, this setup can be used to run Kea in a FreeBSD jail having only a
loopback interface, to service a relayed DHCP request:

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "lo0" ],
           "dhcp-socket-type": "udp"
       },
       ...
   }

Kea binds the service sockets for each interface on startup. If another
process is already using a port, then Kea logs the message and suppresses an
error. DHCP service runs, but it is unavailable on some interfaces.

The "service-sockets-require-all" option makes Kea require all sockets to
be successfully bound. If any opening fails, Kea interrupts the
initialization and exits with a non-zero status. (Default is false).

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3" ],
           "service-sockets-require-all": true
       },
       ...
   }

Sometimes, immediate interruption isn't a good choice. The port can be
unavailable only temporary. In this case, retrying the opening may resolve
the problem. Kea provides two options to specify the retrying:
``service-sockets-max-retries`` and ``service-sockets-retry-wait-time``.

The first defines a maximal number of retries that Kea makes to open a socket.
The zero value (default) means that the Kea doesn't retry the process.

The second defines a wait time (in milliseconds) between attempts. The default
value is 5000 (5 seconds).

::

   "Dhcp4": {
       "interfaces-config": {
           "interfaces": [ "eth1", "eth3" ],
           "service-sockets-max-retries": 5,
           "service-sockets-retry-wait-time": 5000
       },
       ...
   }

If "service-sockets-max-retries" is non-zero and "service-sockets-require-all"
is false, then Kea retries the opening (if needed) but does not fail if any
socket is still not opened.

.. _dhcpinform-unicast-issues:

Issues With Unicast Responses to DHCPINFORM
-------------------------------------------

The use of UDP sockets has certain benefits in deployments where the
server receives only relayed traffic; these benefits are mentioned in
:ref:`dhcp4-interface-configuration`. From the
administrator's perspective it is often desirable to configure the
system's firewall to filter out unwanted traffic, and the use of UDP
sockets facilitates this. However, the administrator must also be aware
of the implications related to filtering certain types of traffic, as it
may impair the DHCP server's operation.

In this section we focus on the case when the server receives the
DHCPINFORM message from the client via a relay. According to `RFC
2131 <https://tools.ietf.org/html/rfc2131>`__, the server should unicast
the DHCPACK response to the address carried in the ``ciaddr`` field. When
the UDP socket is in use, the DHCP server relies on the low-level
functions of an operating system to build the data link, IP, and UDP
layers of the outgoing message. Typically, the OS first uses ARP to
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

Note that the issue described in this section is not observed when
raw sockets are in use, because, in this case, the DHCP server builds
all the layers of the outgoing message on its own and does not use ARP.
Instead, it inserts the value carried in the ``chaddr`` field of the
DHCPINFORM message into the link layer.

Server administrators willing to support DHCPINFORM messages via relays
should not block ARP traffic in their networks, or should use raw sockets
instead of UDP sockets.

.. _ipv4-subnet-id:

IPv4 Subnet Identifier
----------------------

The subnet identifier (subnet ID) is a unique number associated with a particular
subnet. In principle, it is used to associate clients' leases with their
respective subnets. The server configuration must contain unique and stable
identifiers for all subnets.

.. note::

   Subnet IDs must be greater than zero and less than 4294967295.

The following configuration assigns the specified subnet identifier
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

.. _ipv4-subnet-prefix:

IPv4 Subnet Prefix
------------------

The subnet prefix is the second way to identify a subnet. Kea can
accept non-canonical subnet addresses; for instance,
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

This works even if there is another subnet with the "192.0.2.0/24" prefix;
only the textual form of subnets are compared to avoid duplicates.

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
administrator of that network decides that addresses from the range
192.0.2.10 to 192.0.2.20 are going to be managed by the DHCPv4 server.
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
previous example, further assume that 192.0.2.64/26 should also be
managed by the server. It could be written as 192.0.2.64 to 192.0.2.127,
or it can be expressed more simply as 192.0.2.64/26. Both
formats are supported by ``Dhcp4`` and can be mixed in the pool list. For
example, the following pools could be defined:

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

The server may be configured to serve more than one subnet. To add a
second subnet, use a command similar to the following:

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
can use a given pool, it is also able to allocate the first
(typically a network address) and the last (typically a broadcast
address) address from that pool. In the aforementioned example of pool
192.0.3.0/24, both the 192.0.3.0 and 192.0.3.255 addresses may be
assigned as well. This may be invalid in some network configurations. To
avoid this, use the ``min-max`` notation.

In a subnet whose prefix length is less than 24, users may wish to exclude all
addresses ending in .0 and .255 from being dynamically allocated. For
instance, in the subnet 10.0.0.0/8, an administrator may wish to exclude 10.x.y.0
and 10.x.y.255 for all
values of x and y, even though only 10.0.0.0 and 10.255.255.255 must be
excluded according to RFC standards. The ``exclude-first-last-24`` configuration
compatibility flag (:ref:`dhcp4-compatibility`) does this
automatically, rather than requiring explicit configuration of many pools or
reservations for fake hosts. When ``true``, it applies only to subnets of
prefix length 24 or smaller, i.e. larger address space; the default is ``false``.

In this case, "exclude" means to skip these addresses in the free address pickup
routine of the allocation engine; if a client explicitly requests or
has a host reservation for an address in .0 or .255, it will get it.

.. note::

    Here are some liberties and limits to the values that subnets and pools can
    take in unusual Kea configurations:

    +-------------------------------------------------------------+---------+--------------------------------------------------------------------------------------+
    | Kea configuration case                                      | Allowed | Comment                                                                              |
    +=============================================================+=========+======================================================================================+
    | Overlapping subnets                                         | Yes     | Administrator should consider how clients are matched to these subnets.              |
    +-------------------------------------------------------------+---------+--------------------------------------------------------------------------------------+
    | Overlapping pools in one subnet                             | No      | Startup error: DHCP4_PARSER_FAIL                                                     |
    +-------------------------------------------------------------+---------+--------------------------------------------------------------------------------------+
    | Overlapping address pools in different subnets              | Yes     | Specifying the same address pool in different subnets can be used as an equivalent   |
    |                                                             |         | of the global address pool. In that case, the server can assign addresses from the   |
    |                                                             |         | same range regardless of the client's subnet. If an address from such a pool is      |
    |                                                             |         | assigned to a client in one subnet, the same address will be renewed for this        |
    |                                                             |         | client if it moves to another subnet. Another client in a different subnet will      |
    |                                                             |         | not be assigned an address already assigned to the client in any of the subnets.     |
    +-------------------------------------------------------------+---------+--------------------------------------------------------------------------------------+
    | Pools not matching the subnet prefix                        | No      | Startup error: DHCP4_PARSER_FAIL                                                     |
    +-------------------------------------------------------------+---------+--------------------------------------------------------------------------------------+

.. _dhcp4-t1-t2-times:

Sending T1 (Option 58) and T2 (Option 59)
-----------------------------------------

According to `RFC 2131 <https://tools.ietf.org/html/rfc2131>`__,
servers should send values for T1 and T2 that are 50% and 87.5% of the
lease lifetime, respectively. By default, :iscman:`kea-dhcp4` does not send
either value; it can be configured to send values that are either specified
explicitly or that are calculated as percentages of the lease time. The
server's behavior is governed by a combination of configuration
parameters, two of which have already been mentioned.
To send specific, fixed values use the following two parameters:

-  ``renew-timer`` - specifies the value of T1 in seconds.

-  ``rebind-timer`` - specifies the value of T2 in seconds.

The server only sends T2 if it is less than the valid lease time. T1
is only sent if T2 is being sent and T1 is less than T2; or T2
is not being sent and T1 is less than the valid lease time.

Calculating the values is controlled by the following three parameters.

-  ``calculate-tee-times`` - when true, T1 and T2 are calculated as
   percentages of the valid lease time. It defaults to false.

-  ``t1-percent`` - the percentage of the valid lease time to use for
   T1. It is expressed as a real number between 0.0 and 1.0 and must be
   less than ``t2-percent``. The default value is 0.50, per RFC 2131.

-  ``t2-percent`` - the percentage of the valid lease time to use for
   T2. It is expressed as a real number between 0.0 and 1.0 and must be
   greater than ``t1-percent``. The default value is .875, per RFC 2131.

.. note::

   In the event that both explicit values are specified and
   ``calculate-tee-times`` is true, the server will use the explicit values.
   Administrators with a setup where some subnets or shared-networks
   use explicit values and some use calculated values must
   not define the explicit values at any level higher than where they
   will be used. Inheriting them from too high a scope, such as
   global, will cause them to have explicit values at every level underneath
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


Note that either ``name`` or ``code`` is required; there is no need to
specify both. ``space`` has a default value of ``dhcp4``, so this can be skipped
as well if a regular (not encapsulated) DHCPv4 option is defined.
Finally, ``csv-format`` defaults to ``true``, so it too can be skipped, unless
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


Defined options are added to the response when the client requests them,
with a few exceptions which are always added. To enforce the addition of
a particular option, set the ``always-send`` flag to ``true`` as in:

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


In the example above, the ``domain-name-servers`` option respects the global
``always-send`` flag and is always added to responses, but for subnet
``192.0.3.0/24``, the value is taken from the subnet-level option data
specification.

Contrary to ``always-send``, if the ``never-send`` flag is set to
``true`` for a particular option, the server does not add it to the response.
The effect is the same as if the client removed the option code in the
Parameter Request List option (or its equivalent for vendor options):

::

   "Dhcp4": {
       "option-data": [
           {
              "name": "domain-name-servers",
              "data": "192.0.2.1, 192.0.2.2"
           },
           ...
       ],
       "subnet4": [
           {
              "subnet": "192.0.3.0/24",
              "option-data": [
                  {
                      "name": "domain-name-servers",
                      "never-send": true
                  },
                  ...
              ],
              ...
           },
           ...
       ],
       ...
   }

In the example above, the ``domain-name-servers`` option is never added to
responses on subnet ``192.0.3.0/24``. ``never-send`` has precedence over
``always-send``, so if both are ``true`` the option is not added.

.. note::

    The ``always-send`` and ``never-send`` flags are sticky, meaning
    they do not follow the usual configuration inheritance rules.
    Instead, if they are enabled at least once along the configuration
    inheritance chain, they are applied - even if they are
    disabled in other places which would normally receive a higher priority.
    For instance, if one of the flags is enabled in the global scope,
    but disabled at the subnet level, it is enabled,
    disregarding the subnet-level setting.

.. note::

   The ``never-send`` flag is less powerful than :ischooklib:`libdhcp_flex_option.so`;
   for instance, it has no effect on options managed by the server itself.
   Both ``always-send`` and ``never-send`` have no effect on options
   which cannot be requested, for instance from a custom space.

.. note::

    Beginning with Kea 2.7.4, option inclusion can also be controlled through
    option class-tagging, see :ref:`option-class-tagging`

The ``name`` parameter specifies the option name. For a list of
currently supported names, see :ref:`dhcp4-std-options-list`
below. The ``code`` parameter specifies the option code, which must
match one of the values from that list. The next line specifies the
option space, which must always be set to ``dhcp4`` as these are standard
DHCPv4 options. For other option spaces, including custom option spaces,
see :ref:`dhcp4-option-spaces`. The next line specifies the format in
which the data will be entered; use of CSV (comma-separated values) is
recommended. The sixth line gives the actual value to be sent to
clients. The data parameter is specified as normal text, with values separated by
commas if more than one value is allowed.

Options can also be configured as hexadecimal values. If ``csv-format``
is set to ``false``, option data must be specified as a hexadecimal string.
The following commands configure the ``domain-name-servers`` option for all
subnets with the following addresses: 192.0.3.1 and 192.0.3.2. Note that
``csv-format`` is set to ``false``.

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
   spaces (":" or " "). While each octet may contain one or two digits,
   we strongly recommend always using two digits. Valid examples are
   "ab:cd:ef" and "ab cd ef".

-  ``String of digits`` - a continuous string of hexadecimal digits with
   or without a "0x" prefix. Valid examples are "0xabcdef" and "abcdef".

Care should be taken to use proper encoding when using hexadecimal
format; Kea's ability to validate data correctness in hexadecimal is
limited.

It is also possible to specify data for binary options as
a single-quoted text string within double quotes as shown (note that
``csv-format`` must be set to ``false``):

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

Most of the parameters in the ``option-data`` structure are optional and
can be omitted in some circumstances, as discussed in :ref:`dhcp4-option-data-defaults`.

It is possible to specify or override options on a per-subnet basis. If
clients connected to most subnets are expected to get the same
values of a given option, administrators should use global options. On the other
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
values override subnet-specific and global option values; it
is not possible to prioritize assignment of pool-specific
options via the order of pool declarations in the server
configuration.

The following configuration snippet demonstrates how to specify the DNS
servers option, which is assigned to a client only if the client
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

Options can also be specified in class or host-reservation scope. The
current Kea options precedence order is (from most important to least): host
reservation, pool, subnet, shared network, class, global.

When a data field is a string and that string contains the comma (``,``;
U+002C) character, the comma must be escaped with two backslashes (``\\,``;
U+005C). This double escape is required because both the routine
splitting of CSV data into fields and JSON use the same escape character; a
single escape (``\,``) would make the JSON invalid. For example, the string
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
value is allowed. For example, the option ``time-servers``
allows the specification of more than one IPv4 address, enabling clients
to obtain the addresses of multiple NTP servers.

:ref:`dhcp4-custom-options` describes the
configuration syntax to create custom option definitions (formats).
Creation of custom definitions for standard options is generally not
permitted, even if the definition being created matches the actual
option format defined in the RFCs. However, there is an exception to this rule
for standard options for which Kea currently does not provide a
definition. To use such options, a server administrator must
create a definition as described in
:ref:`dhcp4-custom-options` in the ``dhcp4`` option space. This
definition should match the option format described in the relevant RFC,
but the configuration mechanism allows any option format as there is
currently no way to validate it.

The currently supported standard DHCPv4 options are listed in
the table below. "Name" and "Code" are the
values that should be used as a name/code in the option-data structures.
"Type" designates the format of the data; the meanings of the various
types are given in :ref:`dhcp-types`.

.. _dhcp4-std-options-list:

.. table:: List of standard DHCPv4 options configurable by an administrator

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
   | nds-servers                            | 85   | ipv4-address              | true        | false       |
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
   | v6-only-preferred                      | 108  | uint32                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | netinfo-server-address                 | 112  | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | netinfo-server-tag                     | 113  | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-captive-portal                      | 114  | string                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | auto-config                            | 116  | uint8                     | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | name-service-search                    | 117  | uint16                    | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | domain-search                          | 119  | fqdn                      | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | classless-static-route                 | 121  | internal                  | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | cablelabs-client-conf                  | 122  | empty                     | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | vivco-suboptions                       | 124  | record (uint32, binary)   | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | vivso-suboptions                       | 125  | uint32                    | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | pana-agent                             | 136  | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-lost                                | 137  | fqdn                      | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | capwap-ac-v4                           | 138  | ipv4-address              | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | sip-ua-cs-domains                      | 141  | fqdn                      | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-sztp-redirect                       | 143  | tuple                     | true        | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | rdnss-selection                        | 146  | record (uint8,            | true        | false       |
   |                                        |      | ipv4-address,             |             |             |
   |                                        |      | ipv4-address, fqdn)       |             |             |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-portparams                          | 159  | record (uint8, psid)      | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-dnr                                 | 162  | record (uint16, uint16,   | false       | false       |
   |                                        |      | uint8, fqdn, binary)      |             |             |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | option-6rd                             | 212  | record (uint8, uint8,     | true        | false       |
   |                                        |      | ipv6-address,             |             |             |
   |                                        |      | ipv4-address)             |             |             |
   +----------------------------------------+------+---------------------------+-------------+-------------+
   | v4-access-domain                       | 213  | fqdn                      | false       | false       |
   +----------------------------------------+------+---------------------------+-------------+-------------+

.. note::

  The ``default-url`` option was replaced with ``v4-captive-portal`` in Kea 2.1.2, as introduced by
  `RFC 8910 <https://tools.ietf.org/html/rfc8910>`_. The new option has exactly the same format as the
  old one. The general perception is that ``default-url`` was seldom used. Migrating users should
  replace ``default-url`` with ``v4-captive-portal`` in their configurations.

Kea also supports other options than those listed above; the following options
are returned by the Kea engine itself and in general should not be configured
manually.

.. table:: List of standard DHCPv4 options managed by Kea on its own and not directly configurable by an administrator

   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | Name                           | Code  | Type                                  | Description                                                       |
   +================================+=======+=======================================+===================================================================+
   | subnet-mask                    | 1     | ipv4-address                          | calculated automatically, based on subnet definition.             |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | host-name                      | 12    | string                                | sent by client, generally governed by the DNS configuration.      |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | dhcp-requested-address         | 50    | ipv4-address                          | may be sent by the client and the server should not set it.       |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | dhcp-lease-time                | 51    | uint32                                | set automatically based on the ``valid-lifetime`` parameter.      |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | dhcp-message-type              | 53    | string                                | sent by clients and servers. Set by the Kea engine depending on   |
   |                                |       |                                       | the situation and should never be configured explicitly.          |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | dhcp-parameter-request-list    | 55    | uint8 array                           | sent by clients and should never be sent by the server.           |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | dhcp-renewal-time              | 58    | uint32                                | governed by ``renew-timer`` parameter.                            |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | dhcp-rebinding-time            | 59    | uint32                                | governed by ``rebind-timer`` parameter.                           |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | dhcp-client-identifier         | 61    | binary                                | sent by client, echoed back with the value sent by the client.    |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | fqdn                           | 81    | record (uint8, uint8, uint8, fqdn)    | part of the DDNS and D2 configuration.                            |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | dhcp-agent-options             | 82    | empty                                 | sent by the relay agent. This is an empty container option; see   |
   |                                |       |                                       | RAI option detail later in this section.                          |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | authenticate                   | 90    | binary                                | sent by client, Kea does not yet validate it.                     |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | client-last-transaction-time   | 91    | uint32                                | sent by client, server does not set it.                           |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | associated-ip                  | 92    | ipv4-address array                    | sent by client, server responds with list of addresses.           |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | subnet-selection               | 118   | ipv4-address                          | if present in client's messages, will be used in the subnet       |
   |                                |       |                                       | selection process.                                                |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | status-code                    | 151   | record (uint8, string)                | set by server in bulk leasequery responses.                       |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | base-time                      | 152   | uint32                                | set by server in bulk leasequery responses.                       |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | start-time-of-state            | 153   | uint32                                | set by server in bulk leasequery responses.                       |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | query-start-time               | 154   | uint32                                | set by requestor during bulk leasequery.                          |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | query-end-time                 | 155   | uint32                                | set by requestor during bulk leasequery.                          |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | dhcp-state                     | 156   | uint8                                 | set by server in bulk leasequery responses.                       |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+
   | data-source                    | 157   | uint8                                 | set by server in bulk leasequery responses.                       |
   +--------------------------------+-------+---------------------------------------+-------------------------------------------------------------------+

The following table lists all option types used in the previous two tables with a description of
what values are accepted for them.

.. _dhcp-types:

.. table:: List of standard DHCP option types

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
   |                 | silently discards any                                 |
   |                 | terminating/trailing nulls from                       |
   |                 | the end of "string" options when                      |
   |                 | unpacking received packets. This                      |
   |                 | is in keeping with `RFC 2132,                         |
   |                 | Section                                               |
   |                 | 2 <https://tools.ietf.org/html/rfc2132#section-2>`__. |
   +-----------------+-------------------------------------------------------+
   | tuple           | A length field encoded as an 8-bit                    |
   |                 | or 16-bit unsigned integer followed by                |
   |                 | a string of this length. Typically, for DHCPv4,       |
   |                 | the length is 8-bit, and for DHCPv6, it is 16-bit.    |
   |                 | However, there are exceptions to that rule.           |
   |                 | E.g. for the DHCPv4 SZTP Redirect Option,             |
   |                 | bootstrap-server-list is encoded as a list of         |
   |                 | tuples where the URI-length in each tuple is          |
   |                 | a 16-bit unsigned integer.                            |
   +-----------------+-------------------------------------------------------+
   | uint8           | An 8-bit unsigned integer with                        |
   |                 | allowed values 0 to 255.                              |
   +-----------------+-------------------------------------------------------+
   | uint16          | A 16-bit unsigned integer with                        |
   |                 | allowed values 0 to 65535.                            |
   +-----------------+-------------------------------------------------------+
   | uint32          | A 32-bit unsigned integer with                        |
   |                 | allowed values 0 to 4294967295.                       |
   +-----------------+-------------------------------------------------------+
   | int8            | An 8-bit signed integer with allowed                  |
   |                 | values -128 to 127.                                   |
   +-----------------+-------------------------------------------------------+
   | int16           | A 16-bit signed integer with                          |
   |                 | allowed values -32768 to 32767.                       |
   +-----------------+-------------------------------------------------------+
   | int32           | A 32-bit signed integer with                          |
   |                 | allowed values -2147483648 to                         |
   |                 | 2147483647.                                           |
   +-----------------+-------------------------------------------------------+

Kea also supports the Relay Agent Information (RAI, defined in
`RFC 3046 <https://tools.ietf.org/html/rfc3046>`_) option, sometimes referred to as the relay option, agent
option, or simply option 82. The option itself is just a container and does not convey any information
on its own. The following table contains a list of RAI sub-options that Kea can understand. The RAI
and its sub-options are inserted by the relay agent and received by Kea; there is no need for Kea
to be configured with those options. Kea's classification and flexible ID features in host reservations can be
used to process those and other options not listed in the table below.

.. table:: List of RAI sub-options that Kea can understand

   +--------------------+------+----------------------------------------------------------------------+
   | Name               | Code | Comment                                                              |
   +====================+======+======================================================================+
   | circuit-id         | 1    | Used when host-reservation-identifiers is set to `circuit-id`.       |
   +--------------------+------+----------------------------------------------------------------------+
   | remote-id          | 2    | Can be used with flex-id to identify hosts.                          |
   +--------------------+------+----------------------------------------------------------------------+
   | link-selection     | 5    | If present, used to select the appropriate subnet.                   |
   +--------------------+------+----------------------------------------------------------------------+
   | subscriber-id      | 6    | Can be used with flex-id to identify hosts.                          |
   +--------------------+------+----------------------------------------------------------------------+
   | server-id-override | 11   | If sent by the relay, Kea accepts it as the `server-id`.             |
   +--------------------+------+----------------------------------------------------------------------+
   | relay-id           | 12   | Identifies the relay                                                 |
   +--------------------+------+----------------------------------------------------------------------+
   | relay-port         | 19   | If sent by the relay, Kea sends back its responses to this port.     |
   +--------------------+------+----------------------------------------------------------------------+

All other RAI sub-options (including those not listed here) can be used in client classification to
classify incoming packets to specific classes, and/or by :ischooklib:`libdhcp_flex_id.so` to
construct a unique device identifier. For more information about expressions used in client
classification and flexible identifiers, see :ref:`classify`. The RAI sub-options can be
referenced using ``relay4[option-code].hex``; for example, to classify packets based on the
``remote-id`` (sub-option code 2), one would use ``relay4[2].hex``. An example client class that
includes all packets with a specific ``remote-id`` value would look as follows:

::

    "Dhcp4": {
        "client-classes": [
            {
                "name": "remote-id-1020304",
                "test": "relay4[2].hex == 0x01020304",
                ...
            }
        ],
        ...
    }

Classes may be used to segregate traffic into a relatively small number of groups, which then
can be used to select specific subnets, pools and extra options, and more. If per-host behavior
is necessary, using host reservations with flexible identifiers is strongly recommended.

.. _cablelabs-client-conf-suboptions:

CableLabs Client Conf Suboptions
--------------------------------

CableLabs client conf option ("cablelabs-client-conf" code 122) is a
container of suboptions in the "cablelabs-client-conf" space listed in
the table below.

.. table:: List of CableLabs Client Conf sub-options that Kea can understand

   +------------------------+------+-----------------------------+
   | Name                   | Code | Format                      |
   +========================+======+=============================+
   | tsp-primary-server     | 1    | IPv4 address                |
   +------------------------+------+-----------------------------+
   | tsp-secondary-server   | 2    | IPv4 address                |
   +------------------------+------+-----------------------------+
   | tsp-as-parameters      | 4    | record of 3 uint32's        |
   +------------------------+------+-----------------------------+
   | tsp-ap-parameters      | 5    | record of 3 uint32's        |
   +------------------------+------+-----------------------------+
   | tsp-realm              | 6    | Fully Qualified Domain Name |
   +------------------------+------+-----------------------------+
   | tsp-use-tgt            | 7    | boolean                     |
   +------------------------+------+-----------------------------+
   | tsp-provisioning-timer | 8    | uint8                       |
   +------------------------+------+-----------------------------+
   | tsp-sct                | 9    | uint16                      |
   +------------------------+------+-----------------------------+
   | kdc-server             | 10   | array of IPv4 addresses     |
   +------------------------+------+-----------------------------+

These suboptions are defined in
`RFC 3495 <https://tools.ietf.org/html/rfc3495>`_ including its errata
which clarifies the realm format,
`RFC 3594 <https://tools.ietf.org/html/rfc3594>`_ and
`RFC 3634 <https://tools.ietf.org/html/rfc3634>`_.

.. note::

  The suboption 3 carries the TSP provisioning server address as an
  either IPv4 address or a FQDN. This can't be defined in Kea so no
  standard suboption is defined for the code 3 leaving the choice to
  configure its content as a binary value, or if it is used only as an
  IPv4 address or a FQDN to define it as a record of an ``uint8`` (set
  to 0) and ``ipv4-address``, or a record of an ``uint8`` (set to 1)
  and a ``fqdn``, allowing the use of CSV formatted data.

.. _dhcp4-custom-options:

Custom DHCPv4 Options
---------------------

Kea supports custom (non-standard) DHCPv4 options. Let's say that we want
to define a new DHCPv4 option called ``foo``, which will have code 222
and will convey a single, unsigned, 32-bit integer value.
Such an option can be defined by putting the following entry in the configuration file:

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
           },
           ...
       ],
       ...
   }

The ``false`` value of the ``array`` parameter determines that the
option does NOT comprise an array of ``uint32`` values but is, instead, a
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
are optional. The ``array`` parameter's default value is ``false``. The
``record-types`` and ``encapsulate`` parameters' default values are blank
(``""``). The default ``space`` is ``dhcp4``.

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
           },
           ...
       ],
       ...
   }

New options can take more complex forms than the simple use of primitives
(uint8, string, ipv4-address, etc.); it is possible to define an option
comprising a number of existing primitives.

For example, say we want to define a new option that will consist of
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
           },
           ...
       ],
       ...
   }

The ``type`` parameter is set to ``"record"`` to indicate that the option
contains multiple values of different types. These types are given as a
comma-separated list in the ``record-types`` field and should be ones
from those listed in :ref:`dhcp-types`.

The option's values are set in an ``option-data`` statement as follows:

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

The ``csv-format`` parameter is set to ``true`` to indicate that the ``data``
field comprises a comma-separated list of values. The values in ``data`` must
correspond to the types set in the ``record-types`` field of the option
definition.

When ``array`` is set to ``true`` and ``type`` is set to ``"record"``, the
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
           },
           ...
       ],
       ...
   }

The new option content is one IPv4 address followed by one or more 16-bit
unsigned integers.

.. note::

   In general, boolean values are specified as ``true`` or ``false``,
   without quotes. Some specific boolean parameters may also accept
   ``"true"``, ``"false"``, ``0``, ``1``, ``"0"``, and ``"1"``.

.. note::

   Numbers can be specified in decimal or hexadecimal format. The
   hexadecimal format can be either plain (e.g. abcd) or prefixed with
   0x (e.g. 0xabcd).

.. _dhcp4-private-opts:

DHCPv4 Private Options
----------------------

Options with a code between 224 and 254 are reserved for private use.
They can be defined at the global scope or at the client-class local
scope; this allows option definitions to be used depending on context,
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
           },
           ...
       ],
       ...
   }

As the Vendor-Specific Information (VSI) option (code 43) has a vendor-specific
format, i.e. can carry either raw binary value or sub-options, this
mechanism is also available for this option.

In the following example taken from a real configuration, two vendor
classes use option 43 for different and incompatible purposes:

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
               "test": "option[vendor-class-identifier].text == 'APC'",
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
               "test": "option[vendor-class-identifier].text == 'PXE'",
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

.. note::

   This last-resort definition for the Vendor-Specific Information
   option (code 43) is not compatible with a raw binary value. When
   there are known cases where a raw binary value will be used, a
   client class must be defined with both a classification expression
   matching these cases and an option definition for the VSI option with
   a binary type and no encapsulation.

.. note::

   By default, in the Vendor-Specific Information option (code 43),
   sub-option code 0 and 255 mean PAD and END respectively, according to
   `RFC 2132 <https://tools.ietf.org/html/rfc2132>`_. In other words, the
   sub-option code values of 0 and 255 are reserved. Kea does, however,
   allow users to define sub-option codes from 0 to 255. If
   sub-options with codes 0 and/or 255 are defined, bytes with that value are
   no longer treated as a PAD or an END, but as the sub-option code
   when parsing a VSI option in an incoming query.

   Option 43 input processing (also called unpacking) is deferred so that it
   happens after classification. This means clients cannot be classified
   using option 43 sub-options. The definition used to unpack option 43
   is determined as follows:

   - If defined at the global scope, this definition is used.
   - If defined at client class scope and the packet belongs to this
     class, the client class definition is used.
   - If not defined at global scope nor in a client class to which the
     packet belongs, the built-in last resort definition is used. This
     definition only says the sub-option space is
     ``"vendor-encapsulated-options-space"``.

   The output definition selection is a bit simpler:

   - If the packet belongs to a client class which defines the option
     43, use this definition.
   - If defined at the global scope, use this definition.
   - Otherwise, use the built-in last-resort definition.

   Since they use a specific/per vendor option space, sub-options
   are defined at the global scope.

.. note::

   Option definitions in client classes are allowed only for this
   limited option set (codes 43 and from 224 to 254), and only for
   DHCPv4.

.. _dhcp4-vendor-opts:

DHCPv4 Vendor-Specific Options
------------------------------

Currently there are two option spaces defined for :iscman:`kea-dhcp4`:
``dhcp4`` (for the top-level DHCPv4 options) and
``"vendor-encapsulated-options-space"``, which is empty by default but in
which options can be defined. Those options are carried in the
Vendor-Specific Information option (code 43). The following examples
show how to define an option ``foo`` with code 1 that
comprises an IPv4 address, an unsigned 16-bit integer, and a string. The
``foo`` option is conveyed in a Vendor-Specific Information option.

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

Note that the option space is set to ``"vendor-encapsulated-options-space"``.
Once the option format is defined, the next step is to define actual values
for that option:

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

In this example, we also include the Vendor-Specific Information option, which
conveys our sub-option ``foo``. This is required; otherwise, the option
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

Another popular option that is often somewhat imprecisely called the "vendor
option" is option 125. Its proper name is the "vendor-independent
vendor-specific information option" or "vivso". The idea behind vivso options
is that each vendor has its own unique set of options with their own custom
formats. The vendor is identified by a 32-bit unsigned integer called
``enterprise-number`` or ``vendor-id``.


The standard spaces defined in Kea and their options are:

- ``vendor-4491``: Cable Television Laboratories, Inc. for DOCSIS3 options:

+-------------+--------------+------------------------------------------------------------------------+
| option code | option name  | option description                                                     |
+=============+==============+========================================================================+
| 1           | oro          | ORO (or Option Request Option), used by clients to request a list of   |
|             |              | options they are interested in.                                        |
+-------------+--------------+------------------------------------------------------------------------+
| 2           | tftp-servers | a list of IPv4 addresses of TFTP servers to be used by the cable modem |
+-------------+--------------+------------------------------------------------------------------------+

In Kea, each vendor is represented by its own vendor space. Since there are
hundreds of vendors and they sometimes use different option definitions for
different hardware, it is impossible for Kea to support them all natively.
Fortunately, it is easy to define support for new vendor options. As an
example, the Genexis home gateway device requires the vivso 125 option to be
sent with a sub-option 2 that contains a string with the TFTP server URL. To
support such a device, three steps are needed: first, establish option
definitions that explain how the option is supposed to be formed; second,
define option values; and third, tell Kea when to send those
specific options, via client classification.

An example snippet of a configuration could look similar to the
following:

::

   "Dhcp4": {
       // First, we need to define that the sub-option 2 in vivso option for
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
           }
       ],

       "client-classes": [
           {
               // We now need to tell Kea how to recognize when to use vendor space 25167.
               // Usually we can use a simple expression, such as checking if the device
               // sent a vivso option with specific vendor-id, e.g. "vendor[4491].exists".
               // Unfortunately, Genexis is a bit unusual in this aspect, because it
               // doesn't send vivso. In this case we need to look into the vendor class
               // (option code 60) and see if there's a specific string that identifies
               // the device. Alternatively, one can make use of the automated `VENDOR_CLASS_`
               // client class and replace "name" and "test" with `"name": "VENDOR_CLASS_HMC1000"`
               // and no test expression.
               "name": "cpe_genexis",
               "test": "substring(option[60].hex,0,7) == 'HMC1000'",

               // Once the device is recognized, we want to send two options:
               // the vivso option with vendor-id set to 25167, and a sub-option 2.
               "option-data": [
                   {
                       "name": "vivso-suboptions",
                       "data": "25167"
                   },

                   // The sub-option 2 value is defined as any other option. However,
                   // we want to send this sub-option 2, even when the client didn't
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
           }
       ]
   }

By default, Kea sends back only those options that are requested by a client,
unless there are protocol rules that tell the DHCP server to always send an
option. This approach works nicely in most cases and avoids problems with
clients refusing responses with options they do not understand. However, the
situation with vendor options is more complex, as they are not requested the
same way as other options, are not well-documented in official RFCs, or vary by
vendor.

Some vendors (such as DOCSIS, identified by vendor option 4491) have a mechanism
to request specific vendor options and Kea is able to honor those (sub-option 1).
Unfortunately, for many other vendors, such as Genexis (25167, discussed above),
Kea does not have such a mechanism, so it cannot send any sub-options on its own.
To solve this issue, we devised the concept of persistent options. Kea can be
told to always send options, even if the client did not request them. This can
be achieved by adding ``"always-send": true`` to the option data entry. Note
that in this particular case an option is defined in vendor space 25167. With
``always-send`` enabled, the option is sent every time there is a need to deal
with vendor space 25167.

This is also how :iscman:`kea-dhcp4` can be configured to send multiple vendor options
from different vendors, along with each of their specific vendor IDs.
If these options need to be sent by the server regardless of whether the client
specified any enterprise number, ``"always-send": true`` must be configured
for the suboptions that will be included in the ``vivso-suboptions`` option (code 125).

::

   "Dhcp4": {
       "option-data": [
           # Typically DHCPv4 clients will send a Parameter Request List option (code 55) for
           # vivso-suboptions (code 125), and that is enough for Kea to understand that it needs to
           # send the option. These options still need to be defined in the configuration, one per
           # each vendor, but they don't need "always-send" enabled in that case. For misbehaving
           # clients that do not explicitly request it, one may alternatively set "always-send"
           # to true for them as well. This is referring to the following two entries in option-data.
           {
               "name": "vivso-suboptions",
               "space": "dhcp4",
               "data": "2234"
           },
           {
               "name": "vivso-suboptions",
               "space": "dhcp4",
               "data": "3561"
           },
           {
               "always-send": true,
               "data": "tagged",
               "name": "tag",
               "space": "vendor-2234"
           },
           {
               "always-send": true,
               "data": "https://example.com:1234/path",
               "name": "url",
               "space": "vendor-3561"
           }
       ],
       "option-def": [
           {
               "code": 22,
               "name": "tag",
               "space": "vendor-2234",
               "type": "string"
           },
           {
               "code": 11,
               "name": "url",
               "space": "vendor-3561",
               "type": "string"
           }
       ]
   }

Another possibility is to redefine the option; see :ref:`dhcp4-private-opts`.

Kea comes with several example configuration files. Some of them showcase
how to configure options 60 and 43. See ``doc/examples/kea4/vendor-specific.json``
and ``doc/examples/kea4/vivso.json`` in the Kea sources.

.. note::

   :iscman:`kea-dhcp4` is able to recognize multiple Vendor Class Identifier
   options (code 60) with different vendor IDs in the client requests, and to
   send multiple vivso options (code 125) in the responses, one for each vendor.

   :iscman:`kea-dhcp4` honors DOCSIS sub-option 1 (ORO) and adds only requested options
   if this sub-option is present in the client request.

   Currently only one vendor is supported for the ``vivco-suboptions``
   (code 124) option. Specifying multiple enterprise numbers within a single
   option instance or multiple options with different enterprise numbers is not
   supported.

.. _dhcp4-option-spaces:

Nested DHCPv4 Options (Custom Option Spaces)
--------------------------------------------

It is sometimes useful to define a completely new option space, such as
when a user creates a new option in the standard option space
(``dhcp4``) and wants this option to convey sub-options. Since they are in
a separate space, sub-option codes have a separate numbering scheme
and may overlap with the codes of standard options.

Note that the creation of a new option space is not required when
defining sub-options for a standard option, because one is created by
default if the standard option is meant to convey any sub-options (see
:ref:`dhcp4-vendor-opts`).

If we want a DHCPv4 option called ``container`` with code 222,
that conveys two sub-options with codes 1 and 2, we first need to
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
(in this case, ``"isc"``).

The next step is to define a regular DHCPv4 option with the desired code
and specify that it should include options from the new option space:

::

   "Dhcp4": {
       "option-def": [
           {
               "name": "container",
               "code": 222,
               "space": "dhcp4",
               "type": "empty",
               "array": false,
               "record-types": "",
               "encapsulate": "isc"
           },
           ...
       ],
       ...
   }

The name of the option space in which the sub-options are defined is set
in the ``encapsulate`` field. The ``type`` field is set to ``"empty"``, to
indicate that this option does not carry any data other than
sub-options.

Finally, we can set values for the new options:

.. code-block:: json

   {
     "Dhcp4": {
       "option-data": [
           {
               "name": "subopt1",
               "code": 1,
               "space": "isc",
               "data": "192.0.2.3"
           },
           {
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
       ]
     }
   }

It is possible to create an option which carries some data in
addition to the sub-options defined in the encapsulated option space.
For example, if the ``container`` option from the previous example were
required to carry a uint16 value as well as the sub-options, the
``type`` value would have to be set to ``"uint16"`` in the option
definition. (Such an option would then have the following data
structure: DHCP header, uint16 value, sub-options.) The value specified
with the ``data`` parameter — which should be a valid integer enclosed
in quotes, e.g. ``"123"`` — would then be assigned to the ``uint16`` field in
the ``container`` option.

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
   identify an option; this parameter may be left unspecified if the
   ``name`` parameter is specified. However, this also requires that the
   particular option have a definition (either as a standard option or
   an administrator-created definition for the option using an
   ``option-def`` structure), as the option definition associates an
   option with a particular name. It is possible to configure an option
   for which there is no definition (unspecified option format).
   Configuration of such options requires the use of the option code.

-  ``space`` - if the option space is unspecified it defaults to
   ``dhcp4``, which is an option space holding standard DHCPv4 options.

-  ``data`` - if the option data is unspecified it defaults to an empty
   value. The empty value is mostly used for the options which have no
   payload (boolean options), but it is legal to specify empty values
   for some options which carry variable-length data and for which the
   specification allows a length of 0. For such options, the data
   parameter may be omitted in the configuration.

-  ``csv-format`` - if this value is not specified, the server
   assumes that the option data is specified as a list of comma-separated
   values to be assigned to individual fields of the DHCP option.

.. _dhcp4-support-for-long-options:

Support for Long Options
------------------------

The :iscman:`kea-dhcp4` server partially supports long options (RFC 3396).
Since Kea 2.1.6, the server accepts configuring long options and sub-options
(longer than 255 bytes). The options and sub-options are stored internally
in their unwrapped form and they can be processed as usual using the parser
language. On send, the server splits long options and sub-options into multiple
options and sub-options, using the respective option code.

::

   {
   "option-def": [
       {
           "array": false,
           "code": 240,
           "encapsulate": "",
           "name": "my-option",
           "space": "dhcp4",
           "type": "string"
       }
   ],
   "subnet4": [
       {
           "id": 1,
           "subnet": "192.0.2.0/24",
           "reservations": [
               {
                   "hw-address": "aa:bb:cc:dd:ee:ff",
                   "option-data": [
                       {
                           "always-send": false,
                           "code": 240,
                           "name": "my-option",
                           "csv-format": true,
                           "data": "data \
                                    -00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809 \
                                    -00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809 \
                                    -00010203040506070809-00010203040506070809-00010203040506070809-00010203040506070809 \
                                    -data",
                           "space": "dhcp4"
                       }
                   ]
               }
           ]
       }
   ],
   ...
   }

.. note::

   In the example above, the data has been wrapped into several lines for clarity,
   but Kea does not support wrapping in the configuration file.

This example illustrates configuring a custom long option (exceeding 255 octets)
in a reservation. When sending a response, the server splits this option
into two options, each with the code 240.

.. note::

   Currently the server does not support storing long options in databases,
   either via host reservations or the configuration backend.

The server is also able to receive packets with split options (options using
the same option code) and to fuse the data chunks into one option. This is
also supported for sub-options if each sub-option data chunk also contains the
sub-option code and sub-option length.

.. _dhcp4-support-for-v6-only-preferred-option:

Support for IPv6-Only Preferred Option
--------------------------------------

The ``v6-only-preferred`` (code 108) option is handled in a specific
way described in `RFC 8925 <https://tools.ietf.org/html/rfc8925>`_
by :iscman:`kea-dhcp4` when it is configured in a subnet or a
shared network: when the client requests the option (i.e. puts
the 108 code in the DHCP parameter request list option) and
the subnet or shared network is selected the 0.0.0.0 address
is offered and the option returned in the response.

.. _dhcp4-stateless-configuration:

Stateless Configuration of DHCPv4 Clients
-----------------------------------------

The DHCPv4 server supports stateless client configuration, whereby
the client has an IP address configured (e.g. using manual
configuration) and only contacts the server to obtain other
configuration parameters, such as addresses of DNS servers. To
obtain the stateless configuration parameters, the client sends the
DHCPINFORM message to the server with the ``ciaddr`` set to the address
that the client is currently using. The server unicasts the DHCPACK
message to the client that includes the stateless configuration
("yiaddr" not set).

The server responds to the DHCPINFORM when the client is associated
with a subnet defined in the server's configuration. An example subnet
configuration looks like this:

::

   "Dhcp4": {
       "subnet4": [
           {
               "id": 1,
               "subnet": "192.0.2.0/24",
               "option-data": [
               {
                   "name": "domain-name-servers",
                   "code": 6,
                   "data": "192.0.2.200,192.0.2.201",
                   "csv-format": true,
                   "space": "dhcp4"
               }
               ]
           }
       ]
   }

This subnet specifies the single option which will be included in the
DHCPACK message to the client in response to DHCPINFORM. The
subnet definition does not require the address pool configuration if it
will be used solely for stateless configuration.

This server will associate the subnet with the client if one of the
following conditions is met:

-  The DHCPINFORM is relayed and the ``giaddr`` matches the configured
   subnet.

-  The DHCPINFORM is unicast from the client and the ``ciaddr`` matches the
   configured subnet.

-  The DHCPINFORM is unicast from the client and the ``ciaddr`` is not set,
   but the source address of the IP packet matches the configured
   subnet.

-  The DHCPINFORM is not relayed and the IP address on the interface on
   which the message is received matches the configured subnet.

.. _dhcp4-client-classifier:

Client Classification in DHCPv4
-------------------------------

The DHCPv4 server includes support for client classification. For a
deeper discussion of the classification process, see :ref:`classify`.

In certain cases it is useful to configure the server to differentiate
between DHCP client types and treat them accordingly. Client
classification can be used to modify the behavior of almost any part of
DHCP message processing. Kea currently offers client classification
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
devices behind the modem, which should get leases from subnet B. That
segregation is essential to prevent overly curious end-users from playing
with their cable modems. For details on how to set up class restrictions
on subnets, see :ref:`classification-subnets`.

When subnets belong to a shared network, the classification applies to
subnet selection but not to pools; that is, a pool in a subnet limited to a
particular class can still be used by clients which do not belong to the
class, if the pool they are expected to use is exhausted. The limit
on access based on class information is also available at the pool
level within a subnet: see :ref:`classification-pools`. This is
useful when segregating clients belonging to the same subnet into
different address ranges.

In a similar way, a pool can be constrained to serve only known clients,
i.e. clients which have a reservation, using the built-in ``KNOWN`` or
``UNKNOWN`` classes. Addresses can be assigned to registered clients
without giving a different address per reservation: for instance, when
there are not enough available addresses. The determination whether
there is a reservation for a given client is made after a subnet is
selected, so it is not possible to use ``KNOWN``/``UNKNOWN`` classes to select a
shared network or a subnet.

The process of classification is conducted in five steps. The first step
is to assess an incoming packet and assign it to zero or more classes.
The second step is to choose a subnet, possibly based on the class
information. When the incoming packet is in the special class ``DROP``,
it is dropped and a debug message logged.
The next step is to evaluate class expressions depending on
the built-in ``KNOWN``/``UNKNOWN`` classes after host reservation lookup,
using them for pool selection and assigning classes from host
reservations. The list of required classes is then built and each class
of the list has its expression evaluated; when it returns ``true``, the
packet is added as a member of the class. The last step is to assign
options, again possibly based on the class information. More complete
and detailed information is available in :ref:`classify`.

There are two main methods of classification. The first is automatic and
relies on examining the values in the vendor class options or the
existence of a host reservation. Information from these options is
extracted, and a class name is constructed from it and added to the
class list for the packet. The second method specifies an expression that is
evaluated for each packet. If the result is ``true``, the packet is a
member of the class.

.. note::

   The new ``early-global-reservations-lookup`` global parameter flag
   enables a lookup for global reservations before the subnet selection
   phase. This lookup is similar to the general lookup described above
   with two differences:

   - the lookup is limited to global host reservations

   - the ``UNKNOWN`` class is never set

.. note::

   Care should be taken with client classification, as it is easy for
   clients that do not meet class criteria to be denied all service.

Setting Fixed Fields in Classification
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is possible to specify that clients belonging to a particular class
should receive packets with specific values in certain fixed fields. In
particular, three fixed fields are supported: ``next-server`` (conveys
an IPv4 address, which is set in the ``siaddr`` field), ``server-hostname``
(conveys a server hostname, can be up to 64 bytes long, and is sent in
the ``sname`` field) and ``boot-file-name`` (conveys the configuration file,
can be up to 128 bytes long, and is sent using the ``file`` field).

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

If an incoming packet is matched to multiple classes, then the
value used for each field will come from the first class that
specifies the field, in the order the classes are assigned to the
packet.

.. note::

   The classes are ordered as specified in the configuration.

Using Vendor Class Information in Classification
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The server checks whether an incoming packet includes the vendor class
identifier option (60). If it does, the content of that option is
prepended with ``VENDOR_CLASS_``, and it is interpreted as a class. For
example, modern cable modems send this option with value
``docsis3.0``, so the packet belongs to the class
``VENDOR_CLASS_docsis3.0``.

.. note::

   Certain special actions for clients in ``VENDOR_CLASS_docsis3.0`` can be
   achieved by defining ``VENDOR_CLASS_docsis3.0`` and setting its
   ``next-server`` and ``boot-file-name`` values appropriately.

This example shows a configuration using an automatically generated
``VENDOR_CLASS_`` class. The administrator of the network has decided that
addresses from the range 192.0.2.10 to 192.0.2.20 are going to be managed by
the Dhcp4 server and only clients belonging to the DOCSIS 3.0 client
class are allowed to use that pool.

::

   "Dhcp4": {
       "subnet4": [
           {
               "id": 1,
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "client-classes": [ "VENDOR_CLASS_docsis3.0" ]
           }
       ],
       ...
   }

Defining and Using Custom Classes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following example shows how to configure a class using an expression
and a subnet using that class. This configuration defines the class
named ``Client_foo``. It is comprised of all clients whose client IDs
(option 61) start with the string ``foo``. Members of this class will be
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
               "id": 1,
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "client-classes": [ "Client_foo" ]
           },
           ...
       ],
       ...
   }

.. _dhcp4-additional-class:

Additional Classification
~~~~~~~~~~~~~~~~~~~~~~~~~

In some cases it is useful to limit the scope of a class to a pool,
subnet, or shared network. There are two parameters which are used
to limit the scope of the class by instructing the server to evaluate test
expressions when required.

The ``evaluate-additional-classes``, which takes a list of class
names and is valid in pool, subnet, and shared network scope. Classes in
these lists are marked as additional and evaluated after selection of this
specific pool/subnet/shared network and before output-option processing.

The second one is the per-class ``only-in-additional-list`` flag, which is
``false`` by default. When it is set to ``true``, the test expression of
the class is not evaluated at the reception of the incoming packet but later,
and only if the class is present in an ``evaluate-additional-classes`` list.

In this example, a class is assigned to the incoming packet when the
specified subnet is used:

::

   "Dhcp4": {
       "client-classes": [
          {
              "name": "Client_foo",
              "test": "member('ALL')",
              "only-in-additional-list": true
          },
          ...
       ],
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "evaluate-additional-classes": [ "Client_foo" ],
               ...
           },
           ...
       ],
       ...
   }

Additional evaluation can be used to express complex dependencies like
subnet membership. It can also be used to reverse the
precedence; if ``option-data`` is set in a subnet, it takes precedence
over ``option-data`` in a class. If ``option-data`` is moved to a
required class and required in the subnet, a class evaluated earlier
may take precedence.

Additional evaluation is also available at shared network and pool levels.
The order in which additional classes are considered is: pool, subnet,
and shared network, i.e. in the same order from the way in which
``option-data`` is processed.

Since Kea version 2.7.4 additional classes configured without
a test expression are unconditionally added, i.e. they are considered
to always be evaluated to ``true``.

.. note::
   Because additional evaluation occurs after lease assignment, parameters
   that would otherwise impact lease life times (e.g. ``valid-lifetime``,
   ``offer-lifetime``) will have no effect when specified in a class that
   also sets ``only-in-additional-list`` true.

.. note::

   As of Kea version 2.7.4, ``only-if-required`` and ``require-client-classes``
   have been renamed to ``only-in-additional-list`` and ``evaluate-additional-classes``
   respectivley.  The original names will still be accepted as input to allow
   users to migrate but will eventually be rejected.

.. note::

   Vendor-Identifying Vendor Options are a special case: for all other
   options an option is identified by its code point, but ``vivco-suboptions``
   (124) and ``vivso-suboptions`` (125) are identified by the pair of
   code point and vendor identifier. This has no visible effect for
   ``vivso-suboptions``, whose value is the vendor identifier, but it
   is different for ``vivco-suboptions``, where the value is a record
   with the vendor identifier and a binary value. For instance, in:

::

   "Dhcp4": {
       "option-data": [
          {
              "name": "vivco-suboptions",
              "always-send": true,
              "data": "1234, 03666f6f"
          },
          {
              "name": "vivco-suboptions",
              "always-send": true,
              "data": "5678, 03626172"
          },
          ...
        ],
        ...
    }

The first ``option-data`` entry does not hide the second one, because the
vendor identifiers (1234 and 5678) are different: the responses will carry
two instances of the ``vivco-suboptions`` option, each for a different vendor.

.. _dhcp4-ddns-config:

DDNS for DHCPv4
---------------

As mentioned earlier, :iscman:`kea-dhcp4` can be configured to generate requests
to the DHCP-DDNS server, :iscman:`kea-dhcp-ddns`, (referred to herein as "D2") to
update DNS entries. These requests are known as NameChangeRequests or
NCRs. Each NCR contains the following information:

1. Whether it is a request to add (update) or remove DNS entries.

2. Whether the change requests forward DNS updates (A records), reverse
   DNS updates (PTR records), or both.

3. The Fully Qualified Domain Name (FQDN), lease address, and DHCID
   (information identifying the client associated with the FQDN).

DDNS-related parameters are split into two groups:

1. Connectivity Parameters

    These are parameters which specify where and how :iscman:`kea-dhcp4` connects to
    and communicates with D2. These parameters can only be specified
    within the top-level ``dhcp-ddns`` section in the :iscman:`kea-dhcp4`
    configuration. The connectivity parameters are listed below:

    -  ``enable-updates``
    -  ``server-ip``
    -  ``server-port``
    -  ``sender-ip``
    -  ``sender-port``
    -  ``max-queue-size``
    -  ``ncr-protocol``
    -  ``ncr-format``

2. Behavioral Parameters

    These parameters influence behavior such as how client host names and
    FQDN options are handled. They have been moved out of the ``dhcp-ddns``
    section so that they may be specified at the global, shared-network,
    subnet, and/or pool levels. Furthermore, they are inherited downward
    from global to shared-network to subnet to pool. In other words, if a
    parameter is not specified at a given level, the value for that level
    comes from the level above it. The behavioral parameters are as follows:

    -  ``ddns-send-updates``
    -  ``ddns-override-no-update``
    -  ``ddns-override-client-update``
    -  ``ddns-replace-client-name``
    -  ``ddns-generated-prefix``
    -  ``ddns-qualifying-suffix``
    -  ``ddns-update-on-renew``
    -  ``ddns-conflict-resolution-mode``
    -  ``ddns-ttl``
    -  ``ddns-ttl-percent``
    -  ``ddns-ttl-min``
    -  ``ddns-ttl-max``
    -  ``hostname-char-set``
    -  ``hostname-char-replacement``

.. note::

    Kea 2.7.6 added support for these parameters to the pool level.

.. note::

    Behavioral parameters that affect the FQDN are in effect even
    if both ``enable-updates`` and ``ddns-send-updates`` are ``false``,
    to support environments in which clients are responsible
    for their own DNS updates. This applies to ``ddns-replace-client-name``,
    ``ddns-generated-prefix``, ``ddns-qualifying-suffix``, ``hostname-char-set``,
    and ``hostname-char-replacement``.

The default configuration and values would appear as follows:

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
        "ddns-update-on-renew": false,
        "ddns-conflict-resolution-mode": "check-with-dhcid",
        "hostname-char-set": "",
        "hostname-char-replacement": "",
        ...
   }

There are two parameters which determine whether :iscman:`kea-dhcp4`
can generate DDNS requests to D2: the existing ``dhcp-ddns:enable-updates``
parameter, which now only controls whether :iscman:`kea-dhcp4` connects to D2;
and the new behavioral parameter, ``ddns-send-updates``, which determines
whether DDNS updates are enabled at a given level (i.e. global, shared-network,
or subnet). The following table shows how the two parameters function
together:

.. table:: Enabling and disabling DDNS updates

   +-----------------+--------------------+-------------------------------------+
   | dhcp-ddns:      | Global             | Outcome                             |
   | enable-updates  | ddns-send-updates  |                                     |
   +=================+====================+=====================================+
   | false (default) | false              | no updates at any scope             |
   +-----------------+--------------------+-------------------------------------+
   | false           | true (default)     | no updates at any scope             |
   +-----------------+--------------------+-------------------------------------+
   | true            | false              | updates only at scopes with         |
   |                 |                    | a local value of ``true`` for       |
   |                 |                    | ``ddns-enable-updates``             |
   +-----------------+--------------------+-------------------------------------+
   | true            | true               | updates at all scopes except those  |
   |                 |                    | with a local value of ``false``     |
   |                 |                    | for ``ddns-enable-updates``         |
   +-----------------+--------------------+-------------------------------------+

Kea 1.9.1 added two new parameters; the first is ``ddns-update-on-renew``.
Normally, when leases are renewed, the server only updates DNS if the DNS
information for the lease (e.g. FQDN, DNS update direction flags) has changed.
Setting ``ddns-update-on-renew`` to ``true`` instructs the server to always update
the DNS information when a lease is renewed, even if its DNS information has not
changed. This allows Kea to "self-heal" if it was previously unable
to add DNS entries or they were somehow lost by the DNS server.

.. note::

    Setting ``ddns-update-on-renew`` to ``true`` may impact performance, especially
    for servers with numerous clients that renew often.

The second parameter added in Kea 1.9.1 is ``ddns-use-conflict-resolution``.  This
boolean parameter was passed through to D2 and enabled or disabled conflict resolution
as described in `RFC 4703 <https://tools.ietf.org/html/rfc4703>`__.  Beginning with
Kea 2.5.0, it is deprecated and replaced by ``ddns-conflict-resolution-mode``, which
offers four modes of conflict resolution-related behavior:

    - ``check-with-dhcid`` - This mode, the default, instructs D2 to carry out RFC
      4703-compliant conflict resolution.  Existing DNS entries may only be
      overwritten if they have a DHCID record and it matches the client's DHCID.
      This is equivalent to ``ddns-use-conflict-resolution``: ``true``;

    - ``no-check-with-dhcid`` - Existing DNS entries may be overwritten by any
      client, whether those entries include a DHCID record or not. The new entries
      will include a DHCID record for the client to whom they belong.
      This is equivalent to ``ddns-use-conflict-resolution``: ``false``;

    - ``check-exists-with-dhcid`` - Existing DNS entries may only be overwritten
      if they have a DHCID record. The DHCID record need not match the client's DHCID.
      This mode provides a way to protect static DNS entries (those that do not have
      a DHCID record) while allowing dynamic entries (those that do have a DHCID
      record) to be overwritten by any client. This behavior was not supported
      prior to Kea 2.4.0.

    - ``no-check-without-dhcid`` - Existing DNS entries may be overwritten by
      any client; new entries will not include DHCID records. This behavior was
      not supported prior to Kea 2.4.0.

.. note::

    For backward compatibility, ``ddns-use-conflict-resolution`` is still accepted in
    JSON configuration.  The server replaces the value internally with
    ``ddns-conflict-resolution-mode`` and an appropriate value:
    ``check-with-dhcid`` for ``true`` and ``no-check-with-dhcid`` for ``false``.

.. note::

    Setting ``ddns-conflict-resolution-mode`` to any value other than
    ``check-with-dhcid`` disables the overwrite safeguards
    that the rules of conflict resolution (from
    `RFC 4703 <https://tools.ietf.org/html/rfc4703>`__) are intended to
    prevent. This means that existing entries for an FQDN or an
    IP address made for Client-A can be deleted or replaced by entries
    for Client-B. Furthermore, there are two scenarios by which entries
    for multiple clients for the same key (e.g. FQDN or IP) can be created.

    1. Client-B uses the same FQDN as Client-A but a different IP address.
    In this case, the forward DNS entries (A and DHCID RRs) for
    Client-A will be deleted as they match the FQDN, and new entries for
    Client-B will be added. The reverse DNS entries (PTR and DHCID RRs)
    for Client-A, however, will not be deleted as they belong to a different
    IP address, while new entries for Client-B will still be added.

    2. Client-B uses the same IP address as Client-A but a different FQDN.
    In this case, the reverse DNS entries (PTR and DHCID RRs) for Client-A
    will be deleted as they match the IP address, and new entries for
    Client-B will be added. The forward DNS entries (A and DHCID RRs)
    for Client-A, however, will not be deleted, as they belong to a different
    FQDN, while new entries for Client-B will still be added.

    Disabling conflict resolution should be done only after careful review of
    specific use cases. The best way to avoid unwanted DNS entries is to
    always ensure that lease changes are processed through Kea, whether they are
    released, expire, or are deleted via the :isccmd:`lease4-del` command, prior to
    reassigning either FQDNs or IP addresses. Doing so causes :iscman:`kea-dhcp4`
    to generate DNS removal requests to D2.

The DNS entries Kea creates contain a value for TTL (time to live).
By default, the :iscman:`kea-dhcp4` server calculates that value based on
`RFC 4702, Section 5 <https://tools.ietf.org/html/rfc4702#section-5>`__,
which suggests that the TTL value be 1/3 of the lease's lifetime, with
a minimum value of 10 minutes.  There are four optional parameters which
may be used to influence the TTL calculation:


    - ``ddns-ttl`` - If specified and greater than 0 use it as the value of TTL
      unconditionally.  It is specified in seconds. By default it is unspecified.

    - ``ddns-ttl-percent`` - If specified and greater than zero use it as the
      percentage of the lease life time otherwise use 1/3 (per RFC 4702) of the
      lease life time. It is specified as a decimal percentage (e.g. 0.75, 0.50)
      and is unspecified by default.

    - ``ddns-ttl-min`` - If specified and greater than 0 use it the minimum
      otherwise use a minimum of 600 seconds (per RFC 4702). If the calculated TTL
      is less than the minimum return the minimum.  It is specified in seconds. By
      default it is unspecified.

    - ``ddns-ttl-max`` - If specified and greater than zero limit the calculated TTL
      to its value. It is specified in seconds. By default it is unspecified.

.. note::

    A value of zero for any of the TTL parameters can be used to suppress (i.e. "unspecify")
    the value of that parameter inherited from a higher scope.

.. _dhcpv4-d2-io-config:

DHCP-DDNS Server Connectivity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For NCRs to reach the D2 server, :iscman:`kea-dhcp4` must be able to communicate
with it. :iscman:`kea-dhcp4` uses the following configuration parameters to
control this communication:

-  ``enable-updates`` - Enables connectivity to :iscman:`kea-dhcp-ddns` such that DDNS
   updates can be constructed and sent.
   It must be ``true`` for NCRs to be generated and sent to D2.
   It defaults to ``false``.

-  ``server-ip`` - This is the IP address on which D2 listens for requests. The
   default is the local loopback interface at address 127.0.0.1.
   Either an IPv4 or IPv6 address may be specified.

-  ``server-port`` - This is the port on which D2 listens for requests. The default
   value is ``53001``.

-  ``sender-ip`` - This is the IP address which :iscman:`kea-dhcp4` uses to send requests to
   D2. The default value is blank, which instructs :iscman:`kea-dhcp4` to select a
   suitable address.

-  ``sender-port`` - This is the port which :iscman:`kea-dhcp4` uses to send requests to D2.
   The default value of ``0`` instructs :iscman:`kea-dhcp4` to select a suitable port.

-  ``max-queue-size`` - This is the maximum number of requests allowed to queue
   while waiting to be sent to D2. This value guards against requests
   accumulating uncontrollably if they are being generated faster than
   they can be delivered. If the number of requests queued for
   transmission reaches this value, DDNS updating is turned off
   until the queue backlog has been sufficiently reduced. The intent is
   to allow the :iscman:`kea-dhcp4` server to continue lease operations without
   running the risk that its memory usage grows without limit. The
   default value is ``1024``.

-  ``ncr-protocol`` - This specifies the socket protocol to use when sending requests to
   D2. Currently only UDP is supported.

-  ``ncr-format`` - This specifies the packet format to use when sending requests to D2.
   Currently only JSON format is supported.

By default, :iscman:`kea-dhcp-ddns` is assumed to be running on the same machine
as :iscman:`kea-dhcp4`, and all of the default values mentioned above should be
sufficient. If, however, D2 has been configured to listen on a different
address or port, these values must be altered accordingly. For example, if
D2 has been configured to listen on 192.168.1.10 port 900, the following
configuration is required:

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

When Does the :iscman:`kea-dhcp4` Server Generate a DDNS Request?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :iscman:`kea-dhcp4` server follows the behavior prescribed for DHCP servers in
`RFC 4702 <https://tools.ietf.org/html/rfc4702>`__. It is important to keep
in mind that :iscman:`kea-dhcp4` makes the initial decision of when and what to
update and forwards that information to D2 in the form of NCRs. Carrying
out the actual DNS updates and dealing with such things as conflict
resolution are within the purview of D2 itself
(see :ref:`dhcp-ddns-server`). This section describes when :iscman:`kea-dhcp4`
generates NCRs and the configuration parameters that can be used to
influence this decision. It assumes that both the connectivity parameter
``enable-updates`` and the behavioral parameter ``ddns-send-updates``,
are ``true``.

In general, :iscman:`kea-dhcp4` generates DDNS update requests when:

1. A new lease is granted in response to a DHCPREQUEST;

2. An existing lease is renewed but the FQDN associated with it has
   changed; or

3. An existing lease is released in response to a DHCPRELEASE.

In the second case, lease renewal, two DDNS requests are issued: one
request to remove entries for the previous FQDN, and a second request to
add entries for the new FQDN. In the third case, a lease release - a
single DDNS request - to remove its entries is made.

As for the first case, the decisions involved when granting a new lease are
more complex. When a new lease is granted, :iscman:`kea-dhcp4` generates a
DDNS update request if the DHCPREQUEST contains either the FQDN option
(code 81) or the Host Name option (code 12). If both are present, the
server uses the FQDN option.
By default, :iscman:`kea-dhcp4` respects the FQDN N and S flags
specified by the client as shown in the following table:

.. table:: Default FQDN flag behavior

   +------------+-----------------+-----------------+-------------+
   | Client     | Client Intent   | Server Response | Server      |
   | Flags:N-S  |                 |                 | Flags:N-S-O |
   +============+=================+=================+=============+
   | 0-0        | Client wants to | Server          | 1-0-0       |
   |            | do forward      | generates       |             |
   |            | updates, server | reverse-only    |             |
   |            | should do       | request         |             |
   |            | reverse updates |                 |             |
   +------------+-----------------+-----------------+-------------+
   | 0-1        | Server should   | Server          | 0-1-0       |
   |            | do both forward | generates       |             |
   |            | and reverse     | request to      |             |
   |            | updates         | update both     |             |
   |            |                 | directions      |             |
   +------------+-----------------+-----------------+-------------+
   | 1-0        | Client wants no | Server does not | 1-0-0       |
   |            | updates done    | generate a      |             |
   |            |                 | request         |             |
   +------------+-----------------+-----------------+-------------+

The first row in the table above represents "client delegation." Here
the DHCP client states that it intends to do the forward DNS updates and
the server should do the reverse updates. By default, :iscman:`kea-dhcp4`
honors the client's wishes and generates a DDNS request to the D2 server
to update only reverse DNS data. The parameter
``ddns-override-client-update`` can be used to instruct the server to
override client delegation requests. When this parameter is ``true``,
:iscman:`kea-dhcp4` disregards requests for client delegation and generates a
DDNS request to update both forward and reverse DNS data. In this case,
the N-S-O flags in the server's response to the client will be 0-1-1
respectively.

(Note that the flag combination N=1, S=1 is prohibited according to `RFC
4702 <https://tools.ietf.org/html/rfc4702>`__. If such a combination is
received from the client, the packet is dropped by :iscman:`kea-dhcp4`.)

To override client delegation, set the following values in the
configuration file:

::

    "Dhcp4": {
        "ddns-override-client-update": true,
        ...
    }

The third row in the table above describes the case in which the client
requests that no DNS updates be done. The parameter
``ddns-override-no-update`` can be used to instruct the server to disregard
the client's wishes. When this parameter is ``true``, :iscman:`kea-dhcp4`
generates DDNS update requests to :iscman:`kea-dhcp-ddns` even if the client
requests that no updates be done. The N-S-O flags in the server's response to
the client will be 0-1-1.

To override client delegation, issue the following commands:

::

    "Dhcp4": {
        "ddns-override-no-update": true,
        ...
    }

The :iscman:`kea-dhcp4` server always generates DDNS update requests if the
client request only contains the Host Name option. In addition, it includes
an FQDN option in the response to the client with the FQDN N-S-O flags
set to 0-1-0, respectively. The domain name portion of the FQDN option
is the name submitted to D2 in the DDNS update request.

.. _dhcpv4-fqdn-name-generation:

:iscman:`kea-dhcp4` Name Generation for DDNS Update Requests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each NameChangeRequest must of course include the fully qualified domain
name whose DNS entries are to be affected. :iscman:`kea-dhcp4` can be configured
to supply a portion or all of that name, based on what it receives
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

.. note::

   In early versions of Kea, this parameter was a boolean and permitted only
   values of ``true`` and ``false``. Boolean values have been deprecated
   and are no longer accepted. Administrators currently using booleans
   must replace them with the desired mode name. A value of ``true``
   maps to ``when-present``, while ``false`` maps to ``never``.

For example, to instruct :iscman:`kea-dhcp4` to always generate the FQDN for a
client, set the parameter ``ddns-replace-client-name`` to ``always`` as
follows:

::

    "Dhcp4": {
        "ddns-replace-client-name": "always",
        ...
    }

The prefix used in the generation of an FQDN is specified by the
``ddns-generated-prefix`` parameter. The default value is "myhost". To alter
its value, simply set it to the desired string:

::

    "Dhcp4": {
        "ddns-generated-prefix": "another.host",
        ...
    }

The suffix used when generating an FQDN, or when qualifying a partial
name, is specified by the ``ddns-qualifying-suffix`` parameter. It is
strongly recommended that the user supply a value for the qualifying
suffix when DDNS updates are enabled. For obvious reasons, we cannot
supply a meaningful default.

::

    "Dhcp4": {
        "ddns-qualifying-suffix": "foo.example.org",
        ...
    }

When qualifying a partial name, :iscman:`kea-dhcp4` constructs the name in the
format:

``[candidate-name].[ddns-qualifying-suffix].``

where ``candidate-name`` is the partial name supplied in the DHCPREQUEST.
For example, if the FQDN domain name value is "some-computer" and the
``ddns-qualifying-suffix`` is "example.com", the generated FQDN is:

``some-computer.example.com.``

When generating the entire name, :iscman:`kea-dhcp4` constructs the name in
the format:

``[ddns-generated-prefix]-[address-text].[ddns-qualifying-suffix].``

where ``address-text`` is simply the lease IP address converted to a
hyphenated string. For example, if the lease address is 172.16.1.10, the
qualifying suffix is "example.com", and the default value is used for
``ddns-generated-prefix``, the generated FQDN is:

``myhost-172-16-1-10.example.com.``

.. note::

    When the client sends the host name option, ``kea-dhcp4`` never adds
    a dot to the host name in the returned option. It will only end with
    a dot if the client sent it already qualified and ending with a dot.
    When the client sends the FQDN option, the FQDN returned in the response
    will always end with a dot.

.. _dhcp4-host-name-sanitization:

Sanitizing Client Host Name and FQDN Names
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Some DHCP clients may provide values in the Host Name
option (option code 12) or FQDN option (option code 81) that contain undesirable
characters. It is possible to configure :iscman:`kea-dhcp4` to sanitize these
values. The most typical use case is ensuring that only characters that
are permitted by RFC 1035 be included: A-Z, a-z, 0-9, and "-". This may be
accomplished with the following two parameters:

-  ``hostname-char-set`` - a regular expression describing the invalid
   character set. This can be any valid, regular expression using POSIX
   extended expression syntax. Embedded nulls (0x00) are always
   considered an invalid character to be replaced (or omitted).
   The default is ``"[^A-Za-z0-9.-]"``. This matches any character that is not
   a letter, digit, dot, hyphen, or null.

-  ``hostname-char-replacement`` - a string of zero or more characters
   with which to replace each invalid character in the host name. An empty
   string causes invalid characters to be OMITTED rather than replaced.
   The default is ``""``.

The following configuration replaces anything other than a letter,
digit, dot, or hyphen with the letter "x":
::

    "Dhcp4": {
        "hostname-char-set": "[^A-Za-z0-9.-]",
        "hostname-char-replacement": "x",
        ...
    }

Thus, a client-supplied value of "myhost-$[123.org" would become
"myhost-xx123.org". Sanitizing is performed only on the portion of the
name supplied by the client, and it is performed before applying a
qualifying suffix (if one is defined and needed).

.. note::

   Name sanitizing is meant to catch the more common cases of invalid
   characters through a relatively simple character-replacement scheme.
   It is difficult to devise a scheme that works well in all cases, for
   both Host Name and FQDN options.
   Administrators who find they have clients with odd corner cases of
   character combinations that cannot be readily handled with this
   mechanism should consider writing a hook that can carry out
   sufficiently complex logic to address their needs.

   If clients include domain names in the Host Name option and the administrator
   wants these preserved, they need to make sure that the dot, ".",
   is considered a valid character by the ``hostname-char-set`` expression,
   such as this: ``"[^A-Za-z0-9.-]"``. This does not affect dots in FQDN
   Option values.
   When scrubbing FQDNs, dots are treated as delimiters and used to separate
   the option value into individual domain labels that are scrubbed and
   then re-assembled.

   If clients are sending values that differ only by characters
   considered as invalid by the ``hostname-char-set``, be aware that
   scrubbing them will yield identical values. In such cases, DDNS
   conflict rules will permit only one of them to register the name.

   Finally, given the latitude clients have in the values they send, it
   is virtually impossible to guarantee that a combination of these two
   parameters will always yield a name that is valid for use in DNS. For
   example, using an empty value for ``hostname-char-replacement`` could
   yield an empty domain label within a name, if that label consists
   only of invalid characters.

.. note::

   It is possible to specify ``hostname-char-set``
   and/or ``hostname-char-replacement`` at the global scope.

   The Kea hook library :ischooklib:`libdhcp_ddns_tuning.so` provides the ability
   for both :iscman:`kea-dhcp4` and :iscman:`kea-dhcp6` to generate host names
   procedurally based on an expression, to skip DDNS updates on a per-client basis,
   or to fine-tune various DNS update aspects. Please refer to the :ref:`hooks-ddns-tuning`
   documentation for the configuration options.

.. _dhcp4-next-server:

Next Server (``siaddr``)
------------------------

In some cases, clients want to obtain configuration from a TFTP server.
Although there is a dedicated option for it, some devices may use the
``siaddr`` field in the DHCPv4 packet for that purpose. That specific field
can be configured using the ``next-server`` directive. It is possible to
define it in the global scope or for a given subnet only. If both are
defined, the subnet value takes precedence. The value in the subnet can be
set to "0.0.0.0", which means that ``next-server`` should not be sent. It
can also be set to an empty string, which is equivalent to it
not being defined at all; that is, it uses the global value.

The ``server-hostname`` (which conveys a server hostname, can be up to
64 bytes long, and is in the ``sname`` field) and
``boot-file-name`` (which conveys the configuration file, can be up to
128 bytes long, and is sent using the ``file`` field) directives are
handled the same way as ``next-server``.

::

   "Dhcp4": {
       "next-server": "192.0.2.123",
       "boot-file-name": "/dev/null",
       "subnet4": [
           {
               "next-server": "192.0.2.234",
               "server-hostname": "some-name.example.org",
               "boot-file-name": "bootfile.efi",
               ...
           }
       ],
       ...
   }

.. _dhcp4-echo-client-id:

Echoing Client-ID (RFC 6842)
----------------------------

The original DHCPv4 specification (`RFC
2131 <https://tools.ietf.org/html/rfc2131>`__) states that the DHCPv4
server must not send back client-id options when responding to clients.
However, in some cases that results in confused clients that do not have a MAC
address or client-id; see `RFC
6842 <https://tools.ietf.org/html/rfc6842>`__ for details. That behavior
changed with the publication of `RFC
6842 <https://tools.ietf.org/html/rfc6842>`__, which updated `RFC
2131 <https://tools.ietf.org/html/rfc2131>`__. That update states that
the server must send the client-id if the client sent it, and that is Kea's
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

-  When the client tries to renew or release the existing lease, the
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
   correlation and better administer the network.  Beginning with
   release 2.1.2, Kea supports DHCPv6 DUIDs embedded within DHCPv4
   Client Identifier options as described in
   `RFC 4361 <https://tools.ietf.org/html/rfc4361>`__.

DHCPv4 uses two distinct identifiers which are placed by the client in
the queries sent to the server and copied by the server to its responses
to the client: ``chaddr`` and ``client-identifier``. The former was
introduced as a part of the BOOTP specification and it is also used by
DHCP to carry the hardware address of the interface used to send the
query to the server (MAC address for the Ethernet). The latter is
carried in the client-identifier option, introduced in `RFC
2132 <https://tools.ietf.org/html/rfc2132>`__.

`RFC 2131 <https://tools.ietf.org/html/rfc2131>`__ indicates that the
server may use both of these identifiers to identify the client but the
client identifier, if present, takes precedence over ``chaddr``. One of
the reasons for this is that the client identifier is independent from the
hardware used by the client to communicate with the server. For example,
if the client obtained the lease using one network card and then the
network card is moved to another host, the server will wrongly identify
this host as the one which obtained the lease. Moreover, `RFC
4361 <https://tools.ietf.org/html/rfc4361>`__ gives the recommendation
to use a DUID (see `RFC 8415 <https://tools.ietf.org/html/rfc8415>`__,
the DHCPv6 specification) carried as a client identifier when dual-stack
networks are in use to provide consistent identification information for
the client, regardless of the type of protocol it is using. Kea adheres to
these specifications, and the client identifier by default takes
precedence over the value carried in the ``chaddr`` field when the server
searches, creates, updates, or removes the client's lease.

When the server receives a DHCPDISCOVER or DHCPREQUEST message from the
client, it tries to find out if the client already has a lease in the
database; if it does, the server hands out that lease rather than allocates a new one.
Each lease in the lease database is associated with the client
identifier and/or ``chaddr``. The server first uses the client
identifier (if present) to search for the lease; if one is found, the
server treats this lease as belonging to the client, even if the
current ``chaddr`` and the ``chaddr`` associated with the lease do not
match. This facilitates the scenario when the network card on the client
system has been replaced and thus the new MAC address appears in the
messages sent by the DHCP client. If the server fails to find the lease
using the client identifier, it performs another lookup using the
``chaddr``. If this lookup returns no result, the client is considered to
not have a lease and a new lease is created.

A common problem reported by network operators is that poor client
implementations do not use stable client identifiers, instead generating
a new client identifier each time the client connects to the network.
Another well-known case is when the client changes its client
identifier during the multi-stage boot process (PXE). In such cases,
the MAC address of the client's interface remains stable, and using the
``chaddr`` field to identify the client guarantees that the particular
system is considered to be the same client, even though its client
identifier changes.

To address this problem, Kea includes a configuration option which
enables client identification using ``chaddr`` only. This instructs the
server to ignore the client identifier during lease lookups and allocations
for a particular subnet. Consider the following simplified server configuration:

.. code-block:: json

   {
     "Dhcp4": {
       "match-client-id": true,
       "subnet4": [
       {
           "id": 1,
           "subnet": "192.0.10.0/24",
           "pools": [ { "pool": "192.0.2.23-192.0.2.87" } ],
           "match-client-id": false
       },
       {
           "id": 1,
           "subnet": "10.0.0.0/8",
           "pools": [ { "pool": "10.0.0.23-10.0.2.99" } ]
       }
       ]
     }
   }

The ``match-client-id`` parameter is a boolean value which controls this
behavior. The default value of ``true`` indicates that the server will use
the client identifier for lease lookups and ``chaddr`` if the first lookup
returns no results. ``false`` means that the server will only use
the ``chaddr`` to search for the client's lease. Whether the DHCID for DNS
updates is generated from the client identifier or ``chaddr`` is
controlled through the same parameter.

The ``match-client-id`` parameter may appear both in the global
configuration scope and/or under any subnet declaration. In the example
shown above, the effective value of the ``match-client-id`` will be
``false`` for the subnet 192.0.10.0/24, because the subnet-specific
setting of the parameter overrides the global value of the parameter.
The effective value of the ``match-client-id`` for the subnet 10.0.0.0/8
will be set to ``true``, because the subnet declaration lacks this
parameter and the global setting is by default used for this subnet. In
fact, the global entry for this parameter could be omitted in this case,
because ``true`` is the default value.

It is important to understand what happens when the client obtains its
lease for one setting of the ``match-client-id`` and then renews it when
the setting has been changed. First, consider the case when the client
obtains the lease and the ``match-client-id`` is set to ``true``. The
server stores the lease information, including the client identifier
(if supplied) and ``chaddr``, in the lease database. When the setting is
changed and the client renews the lease, the server will determine that
it should use the ``chaddr`` to search for the existing lease. If the
client has not changed its MAC address, the server should successfully
find the existing lease. The client identifier associated with the
returned lease will be ignored and the client will be allowed to use this lease.
When the lease is renewed only the ``chaddr`` will be recorded for this lease,
according to the new server setting.

In the second case, the client has the lease with only a ``chaddr`` value
recorded. When the ``match-client-id`` setting is changed to ``true``,
the server will first try to use the client identifier to find the
existing client's lease. This will return no results because the client
identifier was not recorded for this lease. The server will then use
the ``chaddr`` and the lease will be found. If the lease appears to have
no client identifier recorded, the server will assume that this lease
belongs to the client and that it was created with the previous setting
of the ``match-client-id``. However, if the lease contains a client
identifier which is different from the client identifier used by the
client, the lease will be assumed to belong to another client and a
new lease will be allocated.

For a more visual representation of how Kea recognizes the same client,
please refer to :ref:`uml-recognizing-same-client`.

.. _dhcp4-authoritative:

Authoritative DHCPv4 Server Behavior
------------------------------------

The original DHCPv4 specification (`RFC
2131 <https://tools.ietf.org/html/rfc2131>`__) states that if a client
requests an address in the INIT-REBOOT state of which the server has no
knowledge, the server must remain silent, except if the server knows
that the client has requested an IP address from the wrong network. By
default, Kea follows the behavior of the ISC ``dhcpd`` daemon instead of the
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

   The DHCPv4-over-DHCPv6 details of the inter-process communication may change;
   for instance, the support of port relay (RFC 8357) introduced an incompatible
   change.
   Both the DHCPv4 and DHCPv6 sides should be running the same version of Kea.

The ``dhcp4o6-port`` global parameter specifies the first of the two
consecutive ports of the UDP sockets used for the communication between
the DHCPv6 and DHCPv4 servers. The DHCPv4 server is bound to ::1 on
``port`` + 1 and connected to ::1 on ``port``.

With DHCPv4-over-DHCPv6, the DHCPv4 server does not have access to
several of the identifiers it would normally use to select a subnet. To
address this issue, three new configuration entries are available; the
presence of any of these allows the subnet to be used with
DHCPv4-over-DHCPv6. These entries are:

-  ``4o6-subnet``: takes a prefix (i.e., an IPv6 address followed by a
   slash and a prefix length) which is matched against the source
   address.

-  ``4o6-interface-id``: takes a relay interface ID option value.

-  ``4o6-interface``: takes an interface name which is matched against
   the incoming interface name.

ISC tested the following configuration:

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

       "subnet4": [
       {
           "id": 1,
           "subnet": "10.10.10.0/24",
           "4o6-interface": "eno33554984",
           "4o6-subnet": "2001:db8:1:1::/64",
           "pools": [ { "pool": "10.10.10.100 - 10.10.10.199" } ]
       }
       ],

       "dhcp4o6-port": 786,

       "loggers": [
       {
           "name": "kea-dhcp4",
           "output-options": [
           {
               "output": "kea-dhcp4.log"
           }
           ],
           "severity": "DEBUG",
           "debuglevel": 0
       }
       ]
   }

   }

.. _sanity-checks4:

Sanity Checks in DHCPv4
-----------------------

An important aspect of a well-running DHCP system is an assurance that
the data remains consistent; however, in some cases it may be convenient
to tolerate certain inconsistent data. For example, a network
administrator who temporarily removes a subnet from a configuration
would not want all the leases associated with it to disappear from the
lease database. Kea has a mechanism to implement sanity checks for situations
like this.

Kea supports a configuration scope called ``sanity-checks``.
A parameter, called ``lease-checks``,
governs the verification carried out when a new lease is loaded from a
lease file. This mechanism permits Kea to attempt to correct inconsistent data.

Every subnet has a ``subnet-id`` value; this is how Kea internally
identifies subnets. Each lease has a ``subnet-id`` parameter as well, which
identifies the subnet it belongs to. However, if the configuration has
changed, it is possible that a lease could exist with a ``subnet-id`` but
without any subnet that matches it. Also, it is possible that the
subnet's configuration has changed and the ``subnet-id`` now belongs to a
subnet that does not match the lease.

Kea's corrective algorithm first
checks to see if there is a subnet with the ``subnet-id`` specified by the
lease. If there is, it verifies whether the lease belongs to that
subnet. If not, depending on the ``lease-checks`` setting, the lease is
discarded, a warning is displayed, or a new subnet is selected for the
lease that matches it topologically.

There are five levels which are supported:

-  ``none`` - do no special checks; accept the lease as is.

-  ``warn`` - if problems are detected display a warning, but
   accept the lease data anyway. This is the default value.

-  ``fix`` - if a data inconsistency is discovered, try to
   correct it. If the correction is not successful, insert the incorrect data
   anyway.

-  ``fix-del`` - if a data inconsistency is discovered, try to
   correct it. If the correction is not successful, reject the lease.
   This setting ensures the data's correctness, but some
   incorrect data may be lost. Use with care.

-  ``del`` - if any inconsistency is
   detected, reject the lease. This is the strictest mode; use with care.

This feature is currently implemented for the memfile backend. The
sanity check applies to the lease database in memory, not to the lease file,
i.e. inconsistent leases stay in the lease file.

An example configuration that sets this parameter looks as follows:

::

   "Dhcp4": {
       "sanity-checks": {
           "lease-checks": "fix-del"
       },
       ...
   }

.. _dhcp4-store-extended-info:

Storing Extended Lease Information
----------------------------------

To support such features as DHCP Leasequery
(`RFC 4388 <https://tools.ietf.org/html/rfc4388>`__) and
stash agent options (:ref:`stash-agent-options`),
additional information must be stored with each lease. Because the amount
of information for each lease has ramifications in terms of
performance and system resource consumption, storage of this additional
information is configurable through the ``store-extended-info`` parameter.
It defaults to ``false`` and may be set at the global, shared-network, and
subnet levels.

::

   "Dhcp4": {
       "store-extended-info": true,
       ...
   }

When set to ``true``, information relevant to the DHCPREQUEST asking for the lease is
added into the lease's user context as a map element labeled "ISC".
When the DHCPREQUEST received contains the option
(DHCP Option 82), the map contains the ``relay-agent-info`` map
with the content option (DHCP Option 82) in the ``sub-options`` entry and,
when present, the ``remote-id`` and ``relay-id`` options.
Since DHCPREQUESTs sent as renewals are not likely to contain this
information, the values taken from the last DHCPREQUEST that did contain it are
retained on the lease. The lease's user context looks something like this:

::

  { "ISC": { "relay-agent-info": { "sub-options": "0x0104AABBCCDD" } } }

Or with remote and relay sub-options:

::

   {
       "ISC": {
           "relay-agent-info": {
               "sub-options": "0x02030102030C03AABBCC",
               "remote-id": "03010203",
               "relay-id": "AABBCC"
           }
       }
   }

.. note::

    It is possible that other hook libraries are already using ``user-context``.
    Enabling ``store-extended-info`` should not interfere with any other ``user-context``
    content, as long as it does not also use an element labeled "ISC". In other
    words, ``user-context`` is intended to be a flexible container serving multiple
    purposes. As long as no other purpose also writes an "ISC" element to
    ``user-context`` there should not be a conflict.

Extended lease information is also subject to configurable sanity checking.
The parameter in the ``sanity-checks`` scope is named ``extended-info-checks``
and supports these levels:

-  ``none`` - do no check nor upgrade. This level should be used only when
   extended info is not used at all or when no badly formatted extended
   info, including using the old format, is expected.

-  ``fix`` - fix some common inconsistencies and upgrade extended info
   using the old format to the new one. It is the default level and is
   convenient when the Leasequery hook library is not loaded.

-  ``strict`` - fix all inconsistencies which have an impact on the (Bulk)
   Leasequery hook library.

-  ``pedantic`` - enforce full conformance to the format produced by the
   Kea code; for instance, no extra entries are allowed with the exception
   of ``comment``.

.. note::

   This feature is currently implemented only for the memfile
   backend. The sanity check applies to the lease database in memory,
   not to the lease file, i.e. inconsistent leases stay in the lease
   file.

.. _stash-agent-options:

Stash Agent Options
-------------------

This global parameter was added in version 2.5.8 to mirror a feature that was
previously available in ISC DHCP. When the ``stash-agent-options`` parameter
is ``true``, the server records the relay agent information options sent
during the client's initial DHCPREQUEST message (when the client was in the
SELECTING state) and behaves as if those options are included in all
subsequent DHCPREQUEST messages sent in the RENEWING state. This works around
a problem with relay agent information options, which do not usually appear
in DHCPREQUEST messages sent by the client in the RENEWING state; such messages are
unicast directly to the server and are not sent through a relay agent.

The default is ``false``.

.. _dhcp4-multi-threading-settings:

Multi-Threading Settings
------------------------

The Kea server can be configured to process packets in parallel using multiple
threads. These settings can be found under the ``multi-threading`` structure and are
represented by:

-  ``enable-multi-threading`` - use multiple threads to process packets in
   parallel. The default is ``true``.

-  ``thread-pool-size`` - specify the number of threads to process packets in
   parallel. It may be set to ``0`` (auto-detect), or any positive number that
   explicitly sets the thread count. The default is ``0``.

-  ``packet-queue-size`` - specify the size of the queue used by the thread
   pool to process packets. It may be set to ``0`` (unlimited), or any positive
   number that explicitly sets the queue size. The default is ``64``.

An example configuration that sets these parameters looks as follows:

::

   "Dhcp4": {
       "multi-threading": {
          "enable-multi-threading": true,
          "thread-pool-size": 4,
          "packet-queue-size": 16
       },
       ...
   }

Multi-Threading Settings With Different Database Backends
---------------------------------------------------------

The Kea DHCPv4 server is benchmarked by ISC to determine which settings
give the best performance. Although this section describes our results, they are merely
recommendations and are very dependent on the particular hardware used
for benchmarking. We strongly advise that administrators run their own performance benchmarks.

A full report of performance results for the latest stable Kea version can be found
`here <https://reports.kea.isc.org/>`_.
This includes hardware and benchmark scenario descriptions, as well as
current results.

After enabling multi-threading, the number of threads is set by the ``thread-pool-size``
parameter. Results from our experiments show that the best settings for
:iscman:`kea-dhcp4` are:

-  ``thread-pool-size``: 4 when using ``memfile`` for storing leases.

-  ``thread-pool-size``: 12 or more when using ``mysql`` for storing leases.

-  ``thread-pool-size``: 8 when using ``postgresql``.

Another very important parameter is ``packet-queue-size``; in our benchmarks we
used it as a multiplier of ``thread-pool-size``. The actual setting strongly depends
on ``thread-pool-size``.

We saw the best results in our benchmarks with the following settings:

-  ``packet-queue-size``: 7 * ``thread-pool-size`` when using ``memfile`` for
   storing leases; in our case it was 7 * 4 = 28. This means that at any given
   time, up to 28 packets could be queued.

-  ``packet-queue-size``: 66 * ``thread-pool-size`` when using ``mysql`` for
   storing leases; in our case it was 66 * 12 = 792. This means that up to
   792 packets could be queued.

-  ``packet-queue-size``: 11 * ``thread-pool-size`` when using ``postgresql`` for
   storing leases; in our case it was 11 * 8 = 88.

IPv6-Only Preferred Networks
----------------------------

`RFC 8925 <https://tools.ietf.org/html/rfc8925>`_, recently published by the IETF,
specifies a DHCPv4 option to indicate that a host supports an IPv6-only mode and is willing to
forgo obtaining an IPv4 address if the network provides IPv6 connectivity. The general idea is that
a network administrator can enable this option to signal to compatible dual-stack devices that
IPv6 connectivity is available and they can shut down their IPv4 stack. The new option
``v6-only-preferred`` content is a 32-bit unsigned integer and specifies for how long the device
should disable its stack. The value is expressed in seconds.

The RFC mentions the ``V6ONLY_WAIT`` timer. This is implemented in Kea by setting the value of
the ``v6-only-preferred`` option. This follows the usual practice of setting options; the
option value can be specified on the pool, subnet, shared network, or global levels, or even
via host reservations.

There is no special processing involved; it follows the standard Kea option processing
regime. The option is not sent back unless the client explicitly requests it. For example, to
enable the option for the whole subnet, the following configuration can be used:

::

    {
    "subnet4": [
        {
            "id": 1,
            "pools": [ { "pool":  "192.0.2.1 - 192.0.2.200" } ],
            "subnet": "192.0.2.0/24",
            "option-data": [
                {
                    // This will make the v6-only capable devices to disable their
                    // v4 stack for half an hour and then try again
                    "name": "v6-only-preferred",
                    "data": "1800"
                }
            ]
        }
    ],
    ...
    }

Lease Caching
-------------

Clients that attempt multiple renewals in a short period can cause the server to update
and write to the database frequently, resulting in a performance impact
on the server. The cache parameters instruct the DHCP server to avoid
updating leases too frequently, thus avoiding this behavior. Instead,
the server assigns the same lease (i.e. reuses it) with no
modifications except for CLTT (Client Last Transmission Time), which
does not require disk operations.

The two parameters are the ``cache-threshold`` double and the
``cache-max-age`` integer. These parameters can be configured
at the global, shared-network, and subnet levels. The subnet level has
precedence over the shared-network level, while the global level is used
as a last resort. For example:

::

    {
    "subnet4": [
        {
            "pools": [ { "pool":  "192.0.2.1 - 192.0.2.200" } ],
            "subnet": "192.0.2.0/24",
            "cache-threshold": .25,
            "cache-max-age": 600,
            "valid-lifetime": 2000,
            ...
        }
    ],
    ...
    }

.. note::

   Beginning with Kea 2.7.8, the default value for ``cache-threshold`` is
   0.25 while ``cache-max-age`` is left unspecified.  This means that lease
   caching is enabled by default.  It may be disabled at the desired scope
   either by setting ``cache-threshold`` to 0.0 or setting ``cache-max-age``
   to 0.

When an already-assigned lease can fulfill a client query:

  - any important change, e.g. for DDNS parameter, hostname, or
    valid lifetime reduction, makes the lease not reusable.

  - lease age, i.e. the difference between the creation or last modification
    time and the current time, is computed (elapsed duration).

  - if ``cache-max-age`` is explicitly configured, it is compared with the lease age;
    leases that are too old are not reusable. This means that the value 0
    for ``cache-max-age`` disables the lease cache feature.

  - if ``cache-threshold`` is explicitly configured and is between 0.0 and 1.0,
    it expresses the percentage of the lease valid lifetime which is
    allowed for the lease age. Values below and including 0.0 and
    values greater than 1.0 disable the lease cache feature.

In our example, a lease with a valid lifetime of 2000 seconds can be
reused if it was committed less than 500 seconds ago. With a lifetime
of 3000 seconds, a maximum age of 600 seconds applies.

In outbound client responses (e.g. DHCPACK messages), the
``dhcp-lease-time`` option is set to the reusable valid lifetime,
i.e. the expiration date does not change. Other options based on the
valid lifetime e.g. ``dhcp-renewal-time`` and ``dhcp-rebinding-time``,
also depend on the reusable lifetime.

Temporary Allocation on DHCPDISCOVER
------------------------------------

By default, :iscman:`kea-dhcp4` does not allocate or store a lease when offering an address
to a client in response to a DHCPDISCOVER. In general, :iscman:`kea-dhcp4` can fulfill client
demands faster by deferring lease allocation and storage until it receives DHCPREQUESTs
for them. The ``offer-lifetime`` parameter in :iscman:`kea-dhcp4`
(when not zero) instructs the server to allocate and persist a lease when generating a
DHCPOFFER. In addition:

- The persisted lease's lifetime is equal to ``offer-lifetime`` (in seconds).

- The lifetime sent to the client in the DHCPOFFER via option 51 is still based
  on ``valid-lifetime``. This avoids issues with clients that may reject offers whose
  lifetimes they perceive as too short.

- DDNS updates are not performed. As with the default behavior, those updates occur on DHCPREQUEST.

- Updates are not sent to HA peers.

- Assigned lease statistics are incremented.

- Expiration processing and reclamation behave just as they do for leases allocated
  during DHCPREQUEST processing.

- Lease caching, if enabled, is honored.

- In sites running multiple instances of :iscman:`kea-dhcp4` against a single, shared lease store, races
  for given address values are lost during DHCPDISCOVER processing rather than during DHCPREQUEST
  processing. Servers that lose the race for the address simply do not respond to the client,
  rather than NAK them. The client in turn simply retries its DHCPDISCOVER. This should reduce
  the amount of traffic such conflicts incur.

- Clients repeating DHCPDISCOVERs are offered the same address each time.

An example subnet configuration is shown below:

::

    {
    "subnet4": [
        {
            "pools": [ { "pool":  "192.0.2.1 - 192.0.2.200" } ],
            "subnet": "192.0.2.0/24",
            "offer-lifetime": 60,
            "valid-lifetime": 2000,
            ...
        }
    ],
    ...
    }

Here ``offer-lifetime`` has been configured to be 60 seconds, with a ``valid-lifetime``
of 2000 seconds. This instructs :iscman:`kea-dhcp4` to persist leases for 60 seconds when
sending them back in DHCPOFFERs, and then extend them to 2000 seconds when clients
DHCPREQUEST them.

The value, which defaults to 0, is supported at the global, shared-network, subnet,
and class levels. Choosing an appropriate value for ``offer-lifetime`` is extremely
site-dependent, but a value between 60 and 120 seconds is a reasonable starting
point.

.. _dnr4-options:

DNR (Discovery of Network-designated Resolvers) Options for DHCPv4
------------------------------------------------------------------

The Discovery of Network-designated Resolvers, or DNR option, was
introduced in `RFC 9463 <https://tools.ietf.org/html/rfc9463>`__ as
a way to communicate location of DNS resolvers available over means other than
the classic DNS over UDP over port 53. As of spring 2024, the supported technologies
are DoT (DNS-over-TLS), DoH (DNS-over-HTTPS), and DoQ (DNS-over-QUIC), but the option was
designed to be extensible to accommodate other protocols in the future.

The DHCPv4 option and its corresponding DHCPv6 options are almost exactly the same,
with the exception of cardinality: only one DHCPv4 option is allowed, while multiple
options are allowed for DHCPv6. To be able to convey multiple entries, the DHCPv4 DNR is an
array that allows multiple DNS instances. Each instance is logically equal to one
DHCPv6 option; the only difference is that it uses IPv4 rather than IPv6 addresses.
DNR DHCPv4 options allow more than one DNR instance to be configured, and the DNR
instances are separated with the "pipe" (``0x7C``) character.

For a detailed example of how to configure the DNR option, see :ref:`dnr6-options`.

For each DNR instance, comma-delimited fields must be provided in the following order:

- Service Priority (mandatory),
- ADN FQDN (mandatory),
- IP address(es) (optional; if more than one, they must be separated by spaces)
- SvcParams as a set of key=value pairs (optional; if more than one - they must be separated by spaces)
  To provide more than one ``alpn-id``, separate them with double backslash-escaped commas
  as in the example below).

Example usage:

::

      {
        "name": "v4-dnr",
        // 2 DNR Instances:
        // - Service priority 2, ADN, resolver IPv4 address and Service Parameters
        // - Service priority 3, ADN - this is ADN-only mode as per RFC 9463 3.1.6
        "data": "2, resolver.example., 10.0.5.6, alpn=dot\\,doq port=8530 | 3, fooexp.resolver.example."
      }


.. note::

   If "comma" or "pipe" characters are used as text rather than as field delimiters, they must be escaped with
   double backslashes (``\\,`` or ``\\|``). Escaped commas must be used when configuring more than one ``ALPN``
   protocol, to separate them. The "pipe" (``0x7C``) character can be used in the ``dohpath`` service parameter,
   as it is allowed in a URI.

Examples for DNR DHCPv4 options are provided in the Kea sources, in
`all-options.json` in the `doc/examples/kea4` directory.


.. _host-reservation-v4:

Host Reservations in DHCPv4
===========================

There are many cases where it is useful to provide a configuration on a
per-host basis. The most obvious one is to reserve a specific, static
address for exclusive use by a given client (host); the returning client
receives the same address from the server every time, and other
clients generally do not receive that address. Host
reservations are also convenient when a host has
specific requirements, e.g. a printer that needs additional DHCP
options. Yet another possible use case is to define unique names for
hosts.

There may be cases when a new reservation has been made for a
client for an address currently in use by another client. We call this
situation a "conflict."
These conflicts get resolved automatically over time, as described in
subsequent sections. Once a conflict is resolved, the correct client will
receive the reserved configuration when it renews.

Host reservations are defined as parameters for each subnet. Each host
must have its own unique identifier, such as the hardware/MAC
address. There is an optional ``reservations`` array in the ``subnet4``
structure; each element in that array is a structure that holds
information about reservations for a single host. In particular, the
structure has an identifier that uniquely identifies a host. In
the DHCPv4 context, the identifier is usually a hardware or MAC address.
In most cases an IP address will be specified. It is also possible to
specify a hostname, host-specific options, or fields carried within the
DHCPv4 message such as ``siaddr``, ``sname``, or ``file``.

.. note::

   The reserved address must be within the subnet.

The following example shows how to reserve addresses for specific hosts
in a subnet:

::

   {
   "subnet4": [
       {
           "id": 1,
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
   ],
   ...
   }

The first entry reserves the 192.0.2.202 address for the client that
uses a MAC address of 1a:1b:1c:1d:1e:1f. The second entry reserves the
address 192.0.2.100 and the hostname of "alice-laptop" for the client
using a DUID 0a:0b:0c:0d:0e:0f. (If DNS updates are planned,
it is strongly recommended that the hostnames be unique.) The
third example reserves address 192.0.3.203 for a client whose request
would be relayed by a relay agent that inserts a ``circuit-id`` option with
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

In a typical Kea scenario there is an IPv4 subnet defined, e.g.
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
belong to any specific subnet. Kea still matches inbound client
packets to a subnet as before, but when the subnet's reservation mode is
set to "global", Kea looks for host reservations only among the
global reservations defined. Typically, such reservations would be used
to reserve hostnames for clients which may move from one subnet to
another.

.. note::

   Global reservations, while useful in certain circumstances, have aspects
   that must be given due consideration when using them. Please see
   :ref:`reservation4-conflict` for more details.

.. note::

   Since Kea 1.9.1, reservation mode has been replaced by three
   boolean flags, ``reservations-global``, ``reservations-in-subnet``,
   and ``reservations-out-of-pool``, which allow the configuration of
   host reservations both globally and in a subnet. In such cases a subnet
   host reservation has preference over a global reservation
   when both exist for the same client.

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
requests an address, the server cannot immediately assign the reserved
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
lease, though, as there's a small chance that the DHCPNAK will not be delivered if
the network is lossy. If that happens, the client will not receive any
responses, so it will retransmit its DHCPREQUEST packet. Once the
DHCPNAK is received by Host A, it will revert to server discovery and
will eventually get a different address. Besides allocating a new lease,
the server will also remove the old one. As a result, address 192.0.2.10
will become free.

When Host B tries to renew its temporarily assigned
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

This mechanism allows the server to fully recover from a case
where reservations conflict with existing leases; however, this procedure
takes roughly as long as the value set for ``renew-timer``. The
best way to avoid such a recovery is not to define new reservations that
conflict with existing leases. Another recommendation is to use
out-of-pool reservations; if the reserved address does not belong to a
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
returns this hostname to the client in the Client FQDN or Hostname
option. The server responds with the Client FQDN option only if the
client has included the Client FQDN option in its message to the server. The
server responds with the Hostname option if the client included
the Hostname option in its message to the server, or if the client
requested the Hostname option using the Parameter Request List option.
The server returns the Hostname option even if it is not configured
to perform DNS updates. The reserved hostname always takes precedence
over the hostname supplied by the client or the autogenerated (from the
IPv4 address) hostname.

The server qualifies the reserved hostname with the value of the
``ddns-qualifying-suffix`` parameter. For example, the following subnet
configuration:

.. code-block:: json

       {
           "subnet4": [
           {
               "id": 1,
               "subnet": "10.0.0.0/24",
               "pools": [ { "pool": "10.0.0.10-10.0.0.100" } ],
               "ddns-qualifying-suffix": "example.isc.org.",
               "reservations": [
                  {
                    "hw-address": "aa:bb:cc:dd:ee:ff",
                    "hostname": "alice-laptop"
                  }
               ]
           }
           ],
           "dhcp-ddns": {
               "enable-updates": true
           }
       }

will result in the "alice-laptop.example.isc.org." hostname being assigned to
the client using the MAC address "aa:bb:cc:dd:ee:ff". If the
``ddns-qualifying-suffix`` is not specified, the default (empty) value will
be used, and in this case the value specified as a ``hostname`` will be
treated as a fully qualified name. Thus, by leaving the
``ddns-qualifying-suffix`` empty it is possible to qualify hostnames for
different clients with different domain names:

.. code-block:: json

       {
           "subnet4": [
           {
               "id": 1,
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
           }
           ],
           "dhcp-ddns": {
               "enable-updates": true
           }
       }

The above example results in the assignment of the
"alice-laptop.isc.org." hostname to the client using the MAC
address "aa:bb:cc:dd:ee:ff", and the hostname  "mark-desktop.example.org."
to the client using the MAC address "12:34:56:78:99:AA".

.. _reservation4-options:

Including Specific DHCPv4 Options in Reservations
-------------------------------------------------

Kea offers the ability to specify options on a per-host basis. These
options follow the same rules as any other options. These can be
standard options (see :ref:`dhcp4-std-options`),
custom options (see :ref:`dhcp4-custom-options`),
or vendor-specific options (see :ref:`dhcp4-vendor-opts`). The following
example demonstrates how standard options can be defined:

::

   {
       "subnet4": [
       {
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
               }
               ]
           }
           ],
           ...
       }
       ],
       ...
   }

Vendor-specific options can be reserved in a similar manner:

::

   {
       "subnet4": [
       {
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
               }
               ]
           }
           ],
           ...
       }
       ],
       ...
   }

Options defined at the host level have the highest priority. In other words,
if there are options defined with the same type on the global, subnet,
class, and host levels, the host-specific values are used.

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
       "subnet4": [
       {
           "reservations": [
           {
               "hw-address": "aa:bb:cc:dd:ee:ff",
               "next-server": "10.1.1.2",
               "server-hostname": "server-hostname.example.org",
               "boot-file-name": "/usr/local/share/kea/bootfile.efi"
           }
           ],
           ...
       }
       ],
       ...
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
options that this client sends to the server. Host reservation
mechanisms also allow for the static assignment of classes to clients.
The definitions of these classes are placed in the Kea configuration file or
a database. The following configuration snippet shows how to specify that
a client belongs to the classes ``reserved-class1`` and ``reserved-class2``. Those
classes are associated with specific options sent to the clients which belong
to them.

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
       "subnet4": [
       {
           "id": 1,
           "subnet": "10.0.0.0/24",
           "pools": [ { "pool": "10.0.0.10-10.0.0.100" } ],
           "reservations": [
           {
               "hw-address": "aa:bb:cc:dd:ee:ff",

               "client-classes": [ "reserved-class1", "reserved-class2" ]

           }
           ]
       }
       ]
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
                "only-in-additional-list": true
            }
        ]
    }

The ``only-in-additional-list`` parameter is needed here to force evaluation
of the class after the lease has been allocated, and thus the reserved
class has been also assigned.

.. note::

   The classes specified in non-global host reservations
   are assigned to the processed packet after all classes with the
   ``only-in-additional-list`` parameter set to ``false`` have been evaluated.
   This means that these classes must not depend on the
   statically assigned classes from the host reservations. If
   such a dependency is needed, the ``only-in-additional-list`` parameter must
   be set to ``true`` for the dependent classes. Such classes are
   evaluated after the static classes have been assigned to the packet.
   This, however, imposes additional configuration overhead, because
   all classes marked as ``only-in-additional-list`` must be listed in the
   ``evaluate-additional-classes`` list for every subnet where they are used.

.. note::

   Client classes specified within the Kea configuration file may
   depend on the classes specified within the global host reservations.
   In such a case the ``only-in-additional-list`` parameter is not needed.
   Refer to :ref:`pool-selection-with-class-reservations4` and
   :ref:`subnet-selection-with-class-reservations4`
   for specific use cases.

.. _reservations4-mysql-pgsql:

Storing Host Reservations in MySQL or PostgreSQL
------------------------------------------------

Kea can store host reservations in MySQL or PostgreSQL.
See :ref:`hosts4-storage` for information on how to
configure Kea to use reservations stored in MySQL or PostgreSQL.
Kea provides a dedicated hook for managing reservations in a
database; section :ref:`hooks-host-cmds` provides detailed information.
The `Kea wiki
<https://gitlab.isc.org/isc-projects/kea/wikis/designs/commands#23-host-reservations-hr-management>`__
provides some examples of how to conduct common host reservation
operations.

.. note::

   In Kea, the maximum length of an option specified per-host-reservation is
   arbitrarily set to 4096 bytes.

.. _reservations4-tuning:

Fine-Tuning DHCPv4 Host Reservation
-----------------------------------

The host reservation capability introduces additional restrictions for
the allocation engine (the component of Kea that selects an address for
a client) during lease selection and renewal. In particular, three major
checks are necessary. First, when selecting a new lease, it is not
sufficient for a candidate lease to simply not be in use by another DHCP
client; it also must not be reserved for another client. Similarly, when
renewing a lease, an additional check must be performed to see whether
the address being renewed is reserved for another client. Finally, when
a host renews an address, the server must check whether there is a
reservation for this host, which would mean the existing (dynamically allocated)
address should be revoked and the reserved one be used instead.

Some of those checks may be unnecessary in certain deployments, and not
performing them may improve performance. The Kea server provides the
``reservations-global``, ``reservations-in-subnet`` and
``reservations-out-of-pool`` configuration parameters to select the types of
reservations allowed for a particular subnet. Each reservation type has
different constraints for the checks to be performed by the server when
allocating or renewing a lease for the client.

Configuration flags are:

-  ``reservations-in-subnet`` - when set to ``true``, it enables in-pool host
   reservation types. This setting is the default value, and is the safest and
   most flexible. However, as all checks are conducted, it is also the slowest.
   It does not check against global reservations. This flag defaults to ``true``.

-  ``reservations-out-of-pool`` - when set to ``true``, it allows only out-of-pool
   host reservations. In this case the server assumes that all host reservations
   are for addresses that do not belong to the dynamic pool. Therefore, it can
   skip the reservation checks when dealing with in-pool addresses, thus
   improving performance. Do not use this mode if any reservations use in-pool
   addresses. Caution is advised when using this setting; Kea does not
   sanity-check the reservations against ``reservations-out-of-pool`` and
   misconfiguration may cause problems. This flag defaults to ``false``.

-  ``reservations-global`` - allows global host reservations. With this setting
   in place, the server searches for reservations for a client among the defined
   global reservations. If an address is specified, the server skips the
   reservation checks carried out in other modes, thus improving performance.
   Caution is advised when using this setting; Kea does not sanity-check the
   reservations when ``reservations-global`` is set to ``true``, and
   misconfiguration may cause problems. This flag defaults to ``false``.

Note: setting all flags to ``false`` disables host reservation support.
   As there are no reservations, the server skips all checks. Any reservations
   defined are completely ignored. As checks are skipped, the server may operate
   faster in this mode.

Since Kea 1.9.1 the ``reservations-global``, ``reservations-in-subnet`` and
``reservations-out-of-pool`` flags are suported.

The ``reservations-global``, ``reservations-in-subnet`` and
``reservations-out-of-pool`` parameters can be specified at:

- global level: ``.Dhcp4["reservations-global"]`` (lowest priority: gets overridden
  by all others)

- subnet level: ``.Dhcp4.subnet4[]["reservations-in-subnet"]`` (low priority)

- shared-network level: ``.Dhcp4["shared-networks"][]["reservations-out-of-pool"]``
  (high priority)

- shared-network subnet-level:
  ``.Dhcp4["shared-networks"][].subnet4[]["reservations-out-of-pool"]`` (highest
  priority: overrides all others)

To decide which flags to use, the following decision diagram may be useful:

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
    | used to reserve addresses? |
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
            |              |      addresses       |   |
            |              |  aren't part of the  |   |
            |              |   pools configured   |   |
            |              |  in the respective   |   |
            |              |       subnet?        |   |
            |              +-+------------------+-+   |
            |                |                  |     |
            |             yes|                no|     |
            |                |                  |     V
            +----------------+                  +--> "in-subnet"

An example configuration that disables reservations looks as follows:

.. code-block:: json

    {
      "Dhcp4": {
        "subnet4": [
          {
            "id": 1,
            "pools": [
              {
                "pool": "192.0.2.10-192.0.2.100"
              }
            ],
            "reservations-global": false,
            "reservations-in-subnet": false,
            "subnet": "192.0.2.0/24"
          }
        ]
      }
    }

An example configuration using global reservations is shown below:

.. code-block:: json

    {
      "Dhcp4": {
        "reservations-global": true,
        "reservations": [
          {
            "hostname": "host-one",
            "hw-address": "01:bb:cc:dd:ee:ff"
          },
          {
            "hostname": "host-two",
            "hw-address": "02:bb:cc:dd:ee:ff"
          }
        ],
        "subnet4": [
          {
            "id": 1,
            "pools": [
              {
                "pool": "192.0.2.10-192.0.2.100"
              }
            ],
            "subnet": "192.0.2.0/24"
          }
        ]
      }
    }

The meaning of the reservation flags are:

- ``reservations-global``: fetch global reservations.

- ``reservations-in-subnet``: fetch subnet reservations. For a shared network
  this includes all subnet members of the shared network.

- ``reservations-out-of-pool``: this makes sense only when the
  ``reservations-in-subnet`` flag is ``true``. When ``reservations-out-of-pool``
  is ``true``, the server assumes that all host reservations are for addresses
  that do not belong to the dynamic pool. Therefore, it can skip the reservation
  checks when dealing with in-pool addresses, thus improving performance.
  The server will not assign reserved addresses that are inside the dynamic
  pools to the respective clients. This also means that the addresses matching
  the respective reservations from inside the dynamic pools (if any) can be
  dynamically assigned to any client.

The ``disabled`` configuration corresponds to:

.. code-block:: json

    {
      "Dhcp4": {
        "reservations-global": false,
        "reservations-in-subnet": false
      }
    }

The ``global``configuration using ``reservations-global`` corresponds to:

.. code-block:: json

    {
      "Dhcp4": {
        "reservations-global": true,
        "reservations-in-subnet": false
      }
    }

The ``out-of-pool`` configuration using ``reservations-out-of-pool`` corresponds to:

.. code-block:: json

    {
      "Dhcp4": {
        "reservations-global": false,
        "reservations-in-subnet": true,
        "reservations-out-of-pool": true
      }
    }

And the ``in-subnet`` configuration using ``reservations-in-subnet`` corresponds to:

.. code-block:: json

    {
      "Dhcp4": {
        "reservations-global": false,
        "reservations-in-subnet": true,
        "reservations-out-of-pool": false
      }
    }

To activate both ``global`` and ``in-subnet``, the following combination can be used:

.. code-block:: json

    {
      "Dhcp4": {
        "reservations-global": true,
        "reservations-in-subnet": true,
        "reservations-out-of-pool": false
      }
    }

To activate both ``global`` and ``out-of-pool``, the following combination can
be used:

.. code-block:: json

    {
      "Dhcp4": {
        "reservations-global": true,
        "reservations-in-subnet": true,
        "reservations-out-of-pool": true
      }
    }

Enabling ``out-of-pool`` and disabling ``in-subnet`` at the same time
is not recommended because ``out-of-pool`` applies to host reservations in a
subnet, which are fetched only when the ``in-subnet`` flag is ``true``.

The parameter can be specified at the global, subnet, and shared-network
levels.

An example configuration that disables reservations looks as follows:

.. code-block:: json

    {
      "Dhcp4": {
        "subnet4": [
          {
            "reservations-global": false,
            "reservations-in-subnet": false,
            "subnet": "192.0.2.0/24",
            "id": 1
          }
        ]
      }
    }

An example configuration using global reservations is shown below:

.. code-block:: json

    {
      "Dhcp4": {
        "reservations": [
          {
            "hostname": "host-one",
            "hw-address": "01:bb:cc:dd:ee:ff"
          },
          {
            "hostname": "host-two",
            "hw-address": "02:bb:cc:dd:ee:ff"
          }
        ],
        "reservations-global": true,
        "reservations-in-subnet": false,
        "subnet4": [
          {
            "pools": [
              {
                "pool": "192.0.2.10-192.0.2.100"
              }
            ],
            "subnet": "192.0.2.0/24",
            "id": 1
          }
        ]
      }
    }

For more details regarding global reservations, see :ref:`global-reservations4`.

Another aspect of host reservations is the different types of
identifiers. Kea currently supports four types of identifiers:
``hw-address``, ``duid``, ``client-id``, and ``circuit-id``. This is beneficial from a
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
identifier types as a parameter. Kea checks only those identifier
types enumerated in ``host-reservation-identifiers``. From a performance
perspective, the number of identifier types should be kept to a minimum,
ideally one. If the deployment uses several reservation types, please
enumerate them from most- to least-frequently used, as this increases
the chances of Kea finding the reservation using the fewest queries. An
example of a ``host-reservation-identifiers`` configuration looks as follows:

::

   {
   "host-reservation-identifiers": [ "circuit-id", "hw-address", "duid", "client-id" ],
   "subnet4": [
       {
           "subnet": "192.0.2.0/24",
           ...
       }
   ],
   ...
   }

If not specified, the default value is:

::

   "host-reservation-identifiers": [ "hw-address", "duid", "circuit-id", "client-id" ]

.. note::

   As soon as a host reservation is found, the search is stopped;
   when a client has two host reservations using different enabled
   identifier types, the first is always returned and the second
   ignored. In other words, this is usually a configuration error.
   In those rare cases when having two reservations for the same host makes sense,
   the one to be used can be specified by ordering the list of
   identifier types in ``host-reservation-identifiers``.

.. _global-reservations4:

Global Reservations in DHCPv4
-----------------------------

In some deployments, such as mobile networks, clients can roam within the network
and certain parameters must be specified regardless of the client's
current location. To meet such a need, Kea offers a global reservation
mechanism. The idea behind it is that regular host
reservations are tied to specific subnets, by using a specific
subnet ID. Kea can specify a global reservation that can be used in
every subnet that has global reservations enabled.

This feature can be used to assign certain parameters, such as hostname
or other dedicated, host-specific options. It can also be used to assign
addresses.

An address assigned via global host reservation must be feasible for the
subnet the server selects for the client. In other words, the address must
lie within the subnet; otherwise, it is ignored and the server will
attempt to dynamically allocate an address. If the selected subnet
belongs to a shared network, the server checks for feasibility against
the subnet's siblings, selecting the first in-range subnet. If no such
subnet exists, the server falls back to dynamically allocating the address.

.. note::

    Prior to release 2.3.5, the server did not perform feasibility checks on
    globally reserved addresses, which allowed the server to be configured to
    hand out nonsensical leases for arbitrary address values. Later versions
    of Kea perform these checks.

To use global host reservations, a configuration similar to the
following can be used:

::

   "Dhcp4": {
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
          # If used outside of a matching subnet, such as 192.0.1.0/24,
          # it will result in a broken configuration being handed
          # to the client.
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
       "subnet4": [
       {
           "id": 1,
           "subnet": "10.0.0.0/24",
           # Specify if the server should look up global reservations.
           "reservations-global": true,
           # Specify if the server should look up in-subnet reservations.
           "reservations-in-subnet": false,
           # Specify if the server can assume that all reserved addresses
           # are out-of-pool. It can be ignored because "reservations-in-subnet"
           # is false.
           # "reservations-out-of-pool": false,
           "pools": [ { "pool": "10.0.0.10-10.0.0.100" } ]
       }
       ]
   }

When using database backends, the global host reservations are
distinguished from regular reservations by using a ``subnet-id`` value of
0.

.. _pool-selection-with-class-reservations4:

Pool Selection with Client Class Reservations
---------------------------------------------

Client classes can be specified in the Kea configuration file and/or via
host reservations. The classes specified in the Kea configuration file are
evaluated immediately after receiving the DHCP packet and therefore can be
used to influence subnet selection using the ``client-classes`` parameter
specified in the subnet scope. The classes specified within the host
reservations are fetched and assigned to the packet after the server has
already selected a subnet for the client. This means that the client
class specified within a host reservation cannot be used to influence
subnet assignment for this client, unless the subnet belongs to a
shared network. If the subnet belongs to a shared network, the server may
dynamically change the subnet assignment while trying to allocate a lease.
If the subnet does not belong to a shared network, the subnet
is not changed once selected.

If the subnet does not belong to a shared network, it is possible to
use host reservation-based client classification to select a pool
within the subnet as follows:

.. code-block:: json

    {
        "Dhcp4": {
            "client-classes": [
                {
                    "name": "reserved_class"
                },
                {
                    "name": "unreserved_class",
                    "test": "not member('reserved_class')"
                }
            ],
            "subnet4": [
                {
                    "id": 1,
                    "subnet": "192.0.2.0/24",
                    "reservations": [
                        {
                            "hw-address": "aa:bb:cc:dd:ee:fe",
                            "client-classes": [ "unreserved_class" ]
                        }
                    ],
                    "pools": [
                        {
                            "pool": "192.0.2.10 - 192.0.2.20",
                            "client-classes": [ "unreserved_class" ]
                        },
                        {
                            "pool": "192.0.2.30 - 192.0.2.40",
                            "client-classes": [ "reserved_class" ]
                        },
                        {
                            "pool": "192.0.2.50 - 192.0.2.60"
                        }
                    ]
                }
            ]
        }
    }

``reserved_class`` is declared without the ``test`` parameter because
it may only be assigned to a client via the host reservation mechanism. The
second class, ``unreserved_class``, is assigned to clients which do not
belong to ``reserved_class``.

The first pool in the subnet is used for clients not having such a reservation.
The second pool is only used for clients having a reservation for ``reserved_class``.
The third pool is an unrestricted pool for any clients, comprising of both
``reserved_class`` clients and ``unreserved_class``.

The configuration snippet includes one host reservation which causes the client
with the MAC address ``aa:bb:cc:dd:ee:fe`` to be assigned to ``reserved_class``.
Thus, this client will be given an IP address from the second address pool.

Reservations defined on a subnet that belongs to a shared network are not
visible to an otherwise matching client, so they cannot be used to select pools,
nor subnets for that matter.

.. _subnet-selection-with-class-reservations4:

Subnet Selection with Client Class Reservations
-----------------------------------------------

There is one specific use case when subnet selection may be influenced by
client classes specified within host reservations: when the
client belongs to a shared network. In such a case it is possible to use
classification to select a subnet within this shared network. Consider the
following example:

.. code-block:: json

    {
        "Dhcp4": {
            "client-classes": [
                {
                    "name": "reserved_class"
                },
                {
                    "name": "unreserved_class",
                    "test": "not member('reserved_class')"
                }
            ],
            "reservations": [
                {
                    "hw-address": "aa:bb:cc:dd:ee:fe",
                    "client-classes": [ "reserved_class" ]
                }
            ],
            "reservations-global": true,
            "reservations-in-subnet": false,
            "shared-networks": [
                {
                    "name": "net",
                    "subnet4": [
                        {
                            "id": 1,
                            "subnet": "192.0.2.0/24",
                            "pools": [
                                {
                                    "pool": "192.0.2.10-192.0.2.20",
                                    "client-classes": [ "unreserved_class" ]
                                },
                                {
                                    "pool": "192.0.2.30-192.0.2.40",
                                    "client-classes": [ "unreserved_class" ]
                                }
                            ]
                        },
                        {
                            "id": 2,
                            "subnet": "192.0.3.0/24",
                            "pools": [
                                {
                                    "pool": "192.0.3.10-192.0.3.20",
                                    "client-classes": [ "reserved_class" ]
                                },
                                {
                                    "pool": "192.0.3.30-192.0.3.40",
                                    "client-classes": [ "reserved_class" ]
                                }
                            ]
                        },
                        {
                            "id": 3,
                            "subnet": "192.0.4.0/24",
                            "pools": [
                                {
                                    "pool": "192.0.4.10-192.0.4.20"
                                },
                                {
                                    "pool": "192.0.4.30-192.0.4.40"
                                }
                            ]
                        }
                    ]
                }
            ]
        }
    }

This is similar to the example described in
:ref:`pool-selection-with-class-reservations4`. This time, however, there
are three subnets, of which the first two have a pool associated with a different
class each.

The clients that do not have a reservation for ``reserved_class``
are assigned an address from the first subnet and when that is filled from
the third subnet. Clients with a reservation for ``reserved_class`` are assigned
an address from the second subnet and when that is filled from the third subnet.

The subnets must belong to the same shared network.

For a subnet to be restricted to a certain class, or skipped, all of the pools
inside that subnet must be guarded by ``reserved_class`` or ``unreserved_class``
respectively.

In addition, the reservation for the client class must be specified at the
global scope (global reservation) and ``reservations-global`` must be
set to ``true``.

In the example above, the ``client-classes`` configuration parameter could also
be specified at the subnet level rather than the pool level, and would yield the
same effect.

If the subnets were defined outside shared networks, and ``client-classes`` were
specified at the subnet level, then ``early-global-reservations-lookup`` would
also need to be enabled in order for subnet selection to work.

.. _multiple-reservations-same-ip4:

Multiple Reservations for the Same IP
-------------------------------------

Host reservations were designed to preclude the creation of multiple
reservations for the same IP address within a particular subnet, to avoid
having two different clients compete for the same address.
When using the default settings, the server returns a configuration error
when it finds two or more reservations for the same IP address within
a subnet in the Kea configuration file. :ischooklib:`libdhcp_host_cmds.so`
returns an error in response to the :isccmd:`reservation-add` command
when it detects that the reservation exists in the database for the IP
address for which the new reservation is being added.

In some deployments a single host can select one of several network
interfaces to communicate with the DHCP server, and the server must assign
the same IP address to the host regardless of the interface used. Since
each interface is assigned a different MAC address, it implies that
several host reservations must be created to associate all of the MAC
addresses present on this host with IP addresses. Using different
IP addresses for each interface is impractical and is considered a waste
of the IPv4 address space, especially since the host typically uses only one
interface for communication with the server, hence only one IP address
is in use.

This causes a need to create multiple host reservations for a single
IP address within a subnet; this is supported since the Kea 1.9.1
release as an optional mode of operation, enabled with the
``ip-reservations-unique`` global parameter.

``ip-reservations-unique`` is a boolean parameter that defaults to
``true``, which forbids the specification of more than one reservation
for the same IP address within a given subnet. Setting this parameter to
``false`` allows such reservations to be created both in the Kea configuration
file and in the host database backend, via :ischooklib:`libdhcp_host_cmds.so`.

Setting ``ip-reservations-unique`` to ``false`` when using memfile, MySQL, or PostgreSQL is supported.
This setting is not supported when using Host Cache (see :ref:`hooks-host-cache`) or the RADIUS backend
(see :ref:`hooks-radius`). These reservation backends do not support multiple reservations for the
same IP; if either of these hooks is loaded and ``ip-reservations-unique`` is set to ``false``, then a
configuration error is emitted and the server fails to start.

.. note::

   When ``ip-reservations-unique`` is set to ``true`` (the default value),
   the server ensures that IP reservations are unique for a subnet within
   a single host backend and/or Kea configuration file. It does not
   guarantee that the reservations are unique across multiple backends.
   On server startup, only IP reservations defined in the Kea configuration
   file are checked for uniqueness.

The following is an example configuration with two reservations for
the same IP address but different MAC addresses:

::

   "Dhcp4": {
       "ip-reservations-unique": false,
       "subnet4": [
           {
               "id": 1,
               "subnet": "192.0.2.0/24",
               "reservations": [
                   {
                       "hw-address": "1a:1b:1c:1d:1e:1f",
                       "ip-address": "192.0.2.11"
                   },
                   {
                       "hw-address": "2a:2b:2c:2d:2e:2f",
                       "ip-address": "192.0.2.11"
                   }
               ]
           }
       ]
   }

It is possible to control the ``ip-reservations-unique`` parameter via the
:ref:`dhcp4-cb`. If the new setting of this parameter conflicts with
the currently used backends (i.e. backends do not support the new setting),
the new setting is ignored and a warning log message is generated.
The backends continue to use the default setting, expecting that
IP reservations are unique within each subnet. To allow the
creation of non-unique IP reservations, the administrator must remove
the backends which lack support for them from the configuration file.

Administrators must be careful when they have been using multiple
reservations for the same IP address and later decide to return to
the default mode in which this is no longer allowed. They
must make sure that at most one reservation for a given IP address
exists within a subnet, prior to switching back to the default mode.
If such duplicates are left in the configuration file, the server
reports a configuration error. Leaving such reservations in the host
databases does not cause configuration errors but may lead to lease
allocation errors during the server's operation, when it unexpectedly
finds multiple reservations for the same IP address.

.. note::

   Currently, the Kea server does not verify whether multiple reservations for
   the same IP address exist in MySQL and/or PostgreSQL host databases when
   ``ip-reservations-unique`` is updated from ``false`` to ``true``. This may
   cause issues with lease allocations. The administrator must ensure that there
   is at most one reservation for each IP address within each subnet, prior to
   the configuration update.

The ``reservations-lookup-first`` is a boolean parameter which controls whether
host reservations lookup should be performed before lease lookup. This parameter
has effect only when multi-threading is disabled. When multi-threading is
enabled, host reservations lookup is always performed first to avoid lease-lookup
resource locking. The ``reservations-lookup-first`` parameter defaults to ``false``
when multi-threading is disabled.

.. _host_reservations_as_basic_access_control4:

Host Reservations as Basic Access Control
-----------------------------------------

It is possible to define a host reservation that
contains just an identifier, without any address, options, or values. In some
deployments this is useful, as the hosts that have a reservation belong to
the KNOWN class while others do not. This can be used as a basic access control
mechanism.

The following example demonstrates this concept. It indicates a single IPv4 subnet
and all clients will get an address from it. However, only known clients (those that
have reservations) will get their default router configured. Empty reservations,
i.e. reservations that only have the identification criterion, can be
useful as a way of making the clients known.

::

    "Dhcp4": {
        "client-classes": [
            {
                "name": "KNOWN",
                "option-data": [
                    {
                        "name": "routers",
                        "data": "192.0.2.250"
                    }
                ]
            }
        ],
        "reservations": [
            // Clients on this list will be added to the KNOWN class.
            { "hw-address": "aa:bb:cc:dd:ee:fe" },
            { "hw-address": "11:22:33:44:55:66" }
        ],
        "reservations-in-subnet": true,

        "subnet4": [
            {
                "id": 1,
                "subnet": "192.0.2.0/24",
                "pools": [
                    {
                        "pool": "192.0.2.1-192.0.2.200"
                    }
                ]
            }
        ]
    }

This concept can be extended further. A good real-life scenario might be a
situation where some customers of an ISP have not paid their bills. A new class can be
defined to use an alternative default router that, instead of relaying traffic,
redirects those customers to a captive portal urging them to bring their accounts up to date.

::

    "Dhcp4": {
        "client-classes": [
            {
                "name": "blocked",
                "option-data": [
                    {
                        "name": "routers",
                        "data": "192.0.2.251"
                    }
                ]
            }
        ],
        "reservations": [
            // Clients on this list will be added to the KNOWN class. Some
            // will also be added to the blocked class.
            { "hw-address": "aa:bb:cc:dd:ee:fe",
              "client-classes": [ "blocked" ] },
            { "hw-address": "11:22:33:44:55:66" }
        ],
        "reservations-in-subnet": true,

        "subnet4": [
            {
                "id": 1,
                "subnet": "192.0.2.0/24",
                "pools": [
                    {
                        "pool": "192.0.2.1-192.0.2.200"
                    }
                ],
                "option-data": [
                    {
                        "name": "routers",
                        "data": "192.0.2.250"
                    }
                ]
            }
        ]
    }

.. _shared-network4:

Shared Networks in DHCPv4
=========================

DHCP servers use subnet information in two ways. It is used to
both determine the point of attachment, i.e. where the client is
connected to the network, and to
group information pertaining to a specific location in the network.
Sometimes it is useful to have more than one
logical IP subnet deployed on the same physical link.
Understanding that two or more subnets are used on the same link requires
additional logic in the DHCP server. This capability is called "shared
networks" in Kea, and sometimes also
"shared subnets"; in Microsoft's nomenclature it is called "multinet."

There are many cases where the shared networks feature is useful; here we
explain just a handful of the most common ones. The first and by far
most common use case is an existing IPv4 network that has grown and is
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
(e.g., due to address-pool exhaustion), it uses another subnet from
the same shared network and tries to allocate an address from this subnet.
The server typically allocates all
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

To define a shared network, an additional configuration scope is
introduced:

::

   {
   "Dhcp4": {
       "shared-networks": [
           {
               # Name of the shared network. It may be an arbitrary string
               # and it must be unique among all shared networks.
               "name": "my-secret-lair-level-1",

               # The subnet selector can be specified at the shared-network level.
               # Subnets from this shared network will be selected for directly
               # connected clients sending requests to the server's "eth0" interface.
               "interface": "eth0",

               # This starts a list of subnets in this shared network.
               # There are two subnets in this example.
               "subnet4": [
                   {
                       "id": 1,
                       "subnet": "10.0.0.0/8",
                       "pools": [ { "pool":  "10.0.0.1 - 10.0.0.99" } ]
                   },
                   {
                       "id": 2,
                       "subnet": "192.0.2.0/24",
                       "pools": [ { "pool":  "192.0.2.100 - 192.0.2.199" } ]
                   }
               ]
           }
       ],
       # end of shared-networks

       # It is likely that in the network there will be a mix of regular,
       # "plain" subnets and shared networks. It is perfectly valid to mix
       # them in the same configuration file.
       #
       # This is a regular subnet. It is not part of any shared network.
       "subnet4": [
           {
               "id": 3,
               "subnet": "192.0.3.0/24",
               "pools": [ { "pool":  "192.0.3.1 - 192.0.3.200" } ],
               "interface": "eth1"
           }
       ]
   }
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
To avoid unnecessary performance degradation, shared subnets should
only be defined when required by the deployment.

Shared networks provide the ability to specify many parameters in the
shared network scope that apply to all subnets within it. If
necessary, it is possible to specify a parameter in the shared-network scope and
then override its value in the subnet scope. For example:

::

   {
   "shared-networks": [
       {
           "name": "lab-network3",

           "interface": "eth0",

           # This applies to all subnets in this shared network, unless
           # values are overridden on subnet scope.
           "valid-lifetime": 600,

           # This option is made available to all subnets in this shared
           # network.
           "option-data": [
           {
               "name": "log-servers",
               "data": "1.2.3.4"
           }
           ],

           "subnet4": [
               {
                   "id": 1,
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
                    "id": 2,
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
       }
       ],
       ...
   }

In this example, there is a ``log-servers`` option defined that is available
to clients in both subnets in this shared network. Also, the valid
lifetime is set to 10 minutes (600s). However, the first subnet
overrides some of the values (the valid lifetime is 20 minutes, there is a different IP
address for ``log-servers``), but also adds its own option (the router address).
Assuming a client asking for router and ``log-servers`` options is assigned
a lease from this subnet, it will get a lease for 20 minutes and a
``log-servers`` and routers value of 10.0.0.254. If the same client is
assigned to the second subnet, it will get a 10-minute lease, a
``log-servers`` value of 1.2.3.4, and routers set to 192.0.2.1.

Local and Relayed Traffic in Shared Networks
--------------------------------------------

It is possible to specify an interface name at the shared-network level,
to tell the server that this specific shared network is reachable
directly (not via relays) using the local network interface. As all
subnets in a shared network are expected to be used on the same physical
link, it is a configuration error to attempt to define a shared network
using subnets that are reachable over different interfaces. In other
words, all subnets within the shared network must have the same value
for the ``interface`` parameter. The following configuration is an
example of what **NOT** to do:

::

   {
   "shared-networks": [
       {
           "name": "office-floor-2",
           "subnet4": [
               {
                   "id": 1,
                   "subnet": "10.0.0.0/8",
                   "pools": [ { "pool":  "10.0.0.1 - 10.0.0.99" } ],
                   "interface": "eth0"
               },
               {
                    "id": 2,
                    "subnet": "192.0.2.0/24",
                    "pools": [ { "pool":  "192.0.2.100 - 192.0.2.199" } ],

                    # Specifying the different interface name is a configuration
                    # error. This value should rather be "eth0" or the interface
                    # name in the other subnet should be "eth1".
                    "interface": "eth1"
               }
           ]
       }
   ],
   ...
   }

To minimize the chance of configuration errors, it is often more convenient
to simply specify the interface name once, at the shared-network level, as
shown in the example below.

::

   {
   "shared-networks": [
       {
           "name": "office-floor-2",

           # This tells Kea that the whole shared network is reachable over a
           # local interface. This applies to all subnets in this network.
           "interface": "eth0",

           "subnet4": [
               {
                   "id": 1,
                   "subnet": "10.0.0.0/8",
                   "pools": [ { "pool":  "10.0.0.1 - 10.0.0.99" } ]
               },
               {
                    "id": 2,
                    "subnet": "192.0.2.0/24",
                    "pools": [ { "pool":  "192.0.2.100 - 192.0.2.199" } ]
               }
           ]
       }
   ],
   ...
   }


With relayed traffic, subnets are typically selected using
the relay agents' addresses. If the subnets are used independently (not
grouped within a shared network), a different relay
address can be specified for each of these subnets. When multiple subnets belong to a
shared network they must be selected via the same relay address and,
similarly to the case of the local traffic described above, it is a
configuration error to specify different relay addresses for the respective
subnets in the shared network. The following configuration is another example
of what **NOT** to do:

::

   {
   "shared-networks": [
       {
           "name": "kakapo",
           "subnet4": [
               {
                   "id": 1,
                   "subnet": "192.0.2.0/26",
                   "relay": {
                       "ip-addresses": [ "192.1.1.1" ]
                   },
                   "pools": [ { "pool": "192.0.2.63 - 192.0.2.63" } ]
               },
               {
                   "id": 2,
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
   ],
   ...
   }

Again, it is better to specify the relay address at the shared-network
level; this value will be inherited by all subnets belonging to the
shared network.

::

   {
   "shared-networks": [
       {
           "name": "kakapo",
           "relay": {
               # This relay address is inherited by both subnets.
               "ip-addresses": [ "192.1.1.1" ]
           },
           "subnet4": [
               {
                   "id": 1,
                   "subnet": "192.0.2.0/26",
                   "pools": [ { "pool": "192.0.2.63 - 192.0.2.63" } ]
               },
               {
                   "id": 2,
                   "subnet": "10.0.0.0/24",
                   "pools": [ { "pool": "10.0.0.16 - 10.0.0.16" } ]
               }
           ]
       }
   ],
   ...
   }

Even though it is technically possible to configure two (or more) subnets
within the shared network to use different relay addresses, this will almost
always lead to a different behavior than what the user expects. In this
case, the Kea server will initially select one of the subnets by matching
the relay address in the client's packet with the subnet's configuration.
However, it MAY end up using the other subnet (even though it does not match
the relay address) if the client already has a lease in this subnet or has a
host reservation in this subnet, or simply if the initially selected subnet has no
more addresses available. Therefore, it is strongly recommended to always
specify subnet selectors (interface or relay address) at the shared-network
level if the subnets belong to a shared network, as it is rarely useful to
specify them at the subnet level and may lead to the configuration errors
described above.

Client Classification in Shared Networks
----------------------------------------

Sometimes it is desirable to segregate clients into specific subnets
based on certain properties. This mechanism is called client
classification and is described in :ref:`classify`.

Client classification can be applied to subnets belonging to shared networks in
the same way as it is used for subnets specified outside of shared
networks. It is important to understand how the server selects subnets
for clients when client classification is in use, to ensure that the
appropriate subnet is selected for a given client type.

If a subnet is associated with one or more classes, only the clients belonging
to at least one of these classes may use this subnet. If there are no classes
specified for a subnet, any client connected to a given shared network can use
this subnet. A common mistake is to assume that a subnet that includes a client
class is preferred over subnets without client classes.

The ``client-classes`` parameter may be specified at the shared network, subnet,
and/or pool scopes. If specified for a shared network, clients must belong to at
least one of the classes specified for that network to be considered for subnets
within that network. If specified for a subnet, clients must belong to at least
one of the classes specified for that subnet to be considered for any of that
subnet's pools or host reservations. If specified for a pool, clients must
belong to at least one of the classes specified for that pool to be given a lease from that pool.

.. note:

    As of Kea 2.7.5, ``client-class`` (a single class name) has been replaced
    with ``client-classes`` (a list of one or more class names) and is now
    deprecated. It will still be accepted as input for a time to allow users
    to migrate but will eventually be unsupported.

Consider the following example:

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
                       "id": 1,
                       "subnet": "192.0.2.0/26",
                       "pools": [ { "pool": "192.0.2.1 - 192.0.2.63" } ]
                   },
                   {
                       "id": 2,
                       "subnet": "10.0.0.0/24",
                       "pools": [ { "pool": "10.0.0.2 - 10.0.0.250" } ],
                       "client-classes": [ "b-devices" ]
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
rather than as a way to express subnet preference. For example, if the
client does not belong to the "b-devices" class, it may only use the
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
                       "id": 1,
                       "subnet": "192.0.2.0/26",
                       "pools": [ { "pool": "192.0.2.1 - 192.0.2.63" } ],
                       "client-classes": [ "a-devices" ]
                   },
                   {
                       "id": 2,
                       "subnet": "10.0.0.0/24",
                       "pools": [ { "pool": "10.0.0.2 - 10.0.0.250" } ],
                       "client-classes": [ "b-devices" ]
                   }
               ]
           }
       ]
   }

In this example each class has its own restriction. Only clients that
belong to class "a-devices" are able to use subnet 192.0.2.0/26 and
only clients belonging to "b-devices" are able to use subnet
10.0.0.0/24. Care should be taken not to define too-restrictive
classification rules, as clients that are unable to use any subnets will
be refused service. However, this may be a desired outcome if one wishes
to provide service only to clients with known properties (e.g. only VoIP
phones allowed on a given link).

It is possible to achieve an effect similar to the one
presented in this section without the use of shared networks. If the
subnets are placed in the global subnets scope, rather than in the
shared network, the server will still use classification rules to pick
the right subnet for a given class of devices. The major benefit of
placing subnets within the shared network is that common parameters for
the logically grouped subnets can be specified once in the
shared-network scope, e.g. the ``interface`` or ``relay`` parameter. All subnets
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
whether there is a reservation for a given client in its initially
selected subnet, Kea looks through all subnets in a shared network for a
reservation. This is one of the reasons why defining a shared network
may impact performance. If there is a reservation for a client in any
subnet, that particular subnet is selected for the client. Although
it is technically not an error, it is considered bad practice to define
reservations for the same host in multiple subnets belonging to the same
shared network.

While not strictly mandatory, it is strongly recommended to use explicit
"id" values for subnets if database storage will be used for host
reservations. If an ID is not specified, the values for it are
auto-generated, i.e. Kea assigns increasing integer values starting from
1. Thus, the auto-generated IDs are not stable across configuration
changes.

.. _dhcp4-serverid:

Server Identifier in DHCPv4
===========================

The DHCPv4 protocol uses a "server identifier" to allow clients to
discriminate between several servers present on the same link; this
value is an IPv4 address of the server. The server chooses the IPv4
address of the interface on which the message from the client (or relay)
has been received. A single server instance uses multiple server
identifiers if it is receiving queries on multiple interfaces.

It is possible to override the default server identifier values by specifying
the ``dhcp-server-identifier`` option. This option configuration is only
supported at the subnet, shared network, client class, and global levels. It
must not be specified at the host-reservation level.
When configuring the ``dhcp-server-identifier`` option at client-class level, the
class must not set the ``only-in-additional-list`` flag, because this class would not
be evaluated before the server determines if the received DHCP message should
be accepted for processing. Such classes are evaluated after subnet selection.
See :ref:`dhcp4-additional-class` for details.

The following example demonstrates how to override the server identifier
for a subnet:

::

   {
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
   ],
   ...
   }

.. _dhcp4-subnet-selection:

How the DHCPv4 Server Selects a Subnet for the Client
=====================================================

The DHCPv4 server differentiates among directly connected clients,
clients trying to renew leases, and clients sending their messages
through relays. For directly connected clients, the server checks
the configuration for the interface on which the message has been
received and, if the server configuration does not match any configured
subnet, the message is discarded.

An optional interface parameter is available within a subnet definition to
designate that a given subnet is local, i.e. reachable directly over the
specified interface. For example, a server that is intended to serve a local
subnet over eth0 may be configured as follows:

::

   "Dhcp4": {
       "subnet4": [
           {
               "id": 1,
               "subnet": "192.0.2.0/24",
               "pools": [
                    {
                        "pool": "192.0.2.100 - 192.0.2.199"
                    }
                ],
               "interface": "eth0"
           }
       ],
       ...
   }

Assuming that the server's interface is configured with the IPv4 address
192.0.2.3, the server only processes messages received through this
interface from a directly connected client if there is a subnet
configured to which this IPv4 address belongs, such as 192.0.2.0/24. The
server uses this subnet to assign an IPv4 address for the client.

The rule above does not apply when the client unicasts its message, i.e.
is trying to renew its lease; such a message is accepted through any
interface. The renewing client sets ``ciaddr`` to the currently used IPv4
address, and the server uses this address to select the subnet for the
client (in particular, to extend the lease using this address).

If the message is relayed it is accepted through any interface. The
``giaddr`` set by the relay agent is used to select the subnet for the
client.

It is also possible to specify a relay IPv4 address for a given subnet.
It can be used to match incoming packets into a subnet in uncommon
configurations, e.g. shared networks. See :ref:`dhcp4-relay-override` for details.

.. note::

   The subnet selection mechanism described in this section is based on
   the assumption that client classification is not used. The
   classification mechanism alters the way in which a subnet is selected
   for the client, depending on the classes to which the client belongs.

.. note::

   When the selected subnet is a member of a shared network, the
   whole shared network is selected.

.. _dhcp4-relay-override:

Using a Specific Relay Agent for a Subnet
-----------------------------------------

A relay must have an interface connected to the link on which the
clients are being configured. Typically the relay has an IPv4 address
configured on that interface, which belongs to the subnet from which the
server assigns addresses. Normally, the server is able to use the
IPv4 address inserted by the relay (in the ``giaddr`` field of the DHCPv4
packet) to select the appropriate subnet.

However, that is not always the case. In certain uncommon — but valid —
deployments, the relay address may not match the subnet. This usually
means that there is more than one subnet allocated for a given link. The
two most common examples of this are long-lasting network
renumbering (where both old and new address spaces are still being used)
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

.. code-block:: json

   {
     "Dhcp4": {
       "subnet4": [
           {
               "id": 1,
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "relay": {
                   "ip-addresses": [ "10.0.0.1" ]
               }
           }
       ]
     }
   }

If ``relay`` is specified, the ``ip-addresses`` parameter within it is
mandatory. The ``ip-addresses`` parameter supports specifying a list of addresses.

.. _dhcp4-srv-example-client-class-relay:

Segregating IPv4 Clients in a Cable Network
-------------------------------------------

In certain cases, it is useful to mix relay address information
(introduced in :ref:`dhcp4-relay-override`) with client classification (explained
in :ref:`classify`). One specific example is in a cable network,
where modems typically get addresses from a different subnet than all
the devices connected behind them.

Let us assume that there is one Cable Modem Termination System (CMTS)
with one CM MAC (a physical link that modems are connected to). We want
the modems to get addresses from the 10.1.1.0/24 subnet, while
everything connected behind the modems should get addresses from the
192.0.2.0/24 subnet. The CMTS that acts as a relay uses address
10.1.1.1. The following configuration can serve that situation:

::

   "Dhcp4": {
       "subnet4": [
           {
               "id": 1,
               "subnet": "10.1.1.0/24",
               "pools": [ { "pool": "10.1.1.2 - 10.1.1.20" } ],
               "client-classes": [ "docsis3.0" ],
               "relay": {
                   "ip-addresses": [ "10.1.1.1" ]
               }
           },
           {
               "id": 2,
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
However, for various reasons such as misconfiguration or a faulty
client implementation that retains its address beyond the valid
lifetime, there may be devices connected that use those addresses
without the server's approval or knowledge.

Such an unwelcome event can be detected by legitimate clients (using ARP
or ICMP Echo Request mechanisms) and reported to the DHCPv4 server using
a DHCPDECLINE message. The server does a sanity check (to see whether
the client declining an address really was supposed to use it) and then
conducts a clean-up operation. Any DNS entries related to that
address are removed, the event is logged, and hooks are
triggered. After that is complete, the address is marked as
declined (which indicates that it is used by an unknown entity and thus
not available for assignment) and a probation time is set on it.
Unless otherwise configured, the probation period lasts 24 hours; after
that time, the server will recover the lease (i.e. put it back into
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
       "subnet4": [
           {
               ...
           },
           ...
       ],
       ...
   }

The parameter is expressed in seconds, so the example above
instructs the server to recycle declined leases after one hour.

There are several statistics and hook points associated with the decline
handling procedure. The ``lease4_decline`` hook point is triggered after the
incoming DHCPDECLINE message has been sanitized and the server is about
to decline the lease. The ``declined-addresses`` statistic is increased
after the hook returns (both the global and subnet-specific variants). (See
:ref:`dhcp4-stats` and :ref:`hooks-libraries`
for more details on DHCPv4 statistics and Kea hook points.)

Once the probation time elapses, the declined lease is recovered using
the standard expired-lease reclamation procedure, with several
additional steps. In particular, both ``declined-addresses`` statistics
(global and subnet-specific) are decreased. At the same time,
``reclaimed-declined-addresses`` statistics (again in two variants, global
and subnet-specific) are increased.

A note about statistics: The Kea server does not decrease the
``assigned-addresses`` statistics when a DHCPDECLINE is received and
processed successfully. While technically a declined address is no
longer assigned, the primary usage of the ``assigned-addresses`` statistic
is to monitor pool utilization. Most people would forget to include
``declined-addresses`` in the calculation, and would simply use
``assigned-addresses``/``total-addresses``. This would cause a bias towards
under-representing pool utilization. As this has a potential to cause serious
confusion, ISC decided not to decrease ``assigned-addresses`` immediately after
receiving DHCPDECLINE, but to do it later when Kea recovers the address
back to the available pool.

.. _dhcp4-stats:

Statistics in the DHCPv4 Server
===============================

The DHCPv4 server supports the following statistics:

.. tabularcolumns:: |p{0.2\linewidth}|p{0.1\linewidth}|p{0.7\linewidth}|

.. table:: DHCPv4 statistics
   :class: longtable
   :widths: 20 10 70


   +----------------------------------------------------+----------------+------------------------------------+
   | Statistic                                          | Data Type      | Description                        |
   +====================================================+================+====================================+
   | pkt4-received                                      | integer        | Number of DHCPv4 packets received. |
   |                                                    |                | This includes all packets: valid,  |
   |                                                    |                | bogus, corrupted, rejected, etc.   |
   |                                                    |                | This statistic is expected to grow |
   |                                                    |                | rapidly.                           |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-discover-received                             | integer        | Number of DHCPDISCOVER packets     |
   |                                                    |                | received. This statistic is        |
   |                                                    |                | expected to grow; its increase     |
   |                                                    |                | means that clients that just       |
   |                                                    |                | booted started their configuration |
   |                                                    |                | process and their initial packets  |
   |                                                    |                | reached the Kea server.            |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-offer-received                                | integer        | Number of DHCPOFFER packets        |
   |                                                    |                | received. This statistic is        |
   |                                                    |                | expected to remain zero at all     |
   |                                                    |                | times, as DHCPOFFER packets are    |
   |                                                    |                | sent by the server and the server  |
   |                                                    |                | is never expected to receive them. |
   |                                                    |                | A non-zero value indicates an      |
   |                                                    |                | error. One likely cause would be a |
   |                                                    |                | misbehaving relay agent that       |
   |                                                    |                | incorrectly forwards DHCPOFFER     |
   |                                                    |                | messages towards the server,       |
   |                                                    |                | rather than back to the clients.   |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-request-received                              | integer        | Number of DHCPREQUEST packets      |
   |                                                    |                | received. This statistic is        |
   |                                                    |                | expected to grow. Its increase     |
   |                                                    |                | means that clients that just       |
   |                                                    |                | booted received the server's       |
   |                                                    |                | response (DHCPOFFER) and accepted  |
   |                                                    |                | it, and are now requesting an      |
   |                                                    |                | address (DHCPREQUEST).             |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-ack-received                                  | integer        | Number of DHCPACK packets          |
   |                                                    |                | received. This statistic is        |
   |                                                    |                | expected to remain zero at all     |
   |                                                    |                | times, as DHCPACK packets are sent |
   |                                                    |                | by the server and the server is    |
   |                                                    |                | never expected to receive them. A  |
   |                                                    |                | non-zero value indicates an error. |
   |                                                    |                | One likely cause would be a        |
   |                                                    |                | misbehaving relay agent that       |
   |                                                    |                | incorrectly forwards DHCPACK       |
   |                                                    |                | messages towards the server,       |
   |                                                    |                | rather than back to the clients.   |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-nak-received                                  | integer        | Number of DHCPNAK packets          |
   |                                                    |                | received. This statistic is        |
   |                                                    |                | expected to remain zero at all     |
   |                                                    |                | times, as DHCPNAK packets are sent |
   |                                                    |                | by the server and the server is    |
   |                                                    |                | never expected to receive them. A  |
   |                                                    |                | non-zero value indicates an error. |
   |                                                    |                | One likely cause would be a        |
   |                                                    |                | misbehaving relay agent that       |
   |                                                    |                | incorrectly forwards DHCPNAK       |
   |                                                    |                | messages towards the server,       |
   |                                                    |                | rather than back to the clients.   |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-release-received                              | integer        | Number of DHCPRELEASE packets      |
   |                                                    |                | received. This statistic is        |
   |                                                    |                | expected to grow. Its increase     |
   |                                                    |                | means that clients that had an     |
   |                                                    |                | address are shutting down or       |
   |                                                    |                | ceasing to use their addresses.    |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-decline-received                              | integer        | Number of DHCPDECLINE packets      |
   |                                                    |                | received. This statistic is        |
   |                                                    |                | expected to remain close to zero.  |
   |                                                    |                | Its increase means that a client   |
   |                                                    |                | leased an address, but discovered  |
   |                                                    |                | that the address is currently      |
   |                                                    |                | used by an unknown device          |
   |                                                    |                | elsewhere in the network.          |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-inform-received                               | integer        | Number of DHCPINFORM packets       |
   |                                                    |                | received. This statistic is        |
   |                                                    |                | expected to grow. Its increase     |
   |                                                    |                | means that there are clients       |
   |                                                    |                | that either do not need an address |
   |                                                    |                | or already have an address and are |
   |                                                    |                | interested only in getting         |
   |                                                    |                | additional configuration           |
   |                                                    |                | parameters.                        |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-unknown-received                              | integer        | Number of packets received of an   |
   |                                                    |                | unknown type. A non-zero value of  |
   |                                                    |                | this statistic indicates that the  |
   |                                                    |                | server received a packet that it   |
   |                                                    |                | was not able to recognize, either  |
   |                                                    |                | with an unsupported type or        |
   |                                                    |                | possibly malformed (without a      |
   |                                                    |                | message-type option).              |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-sent                                          | integer        | Number of DHCPv4 packets sent.     |
   |                                                    |                | This statistic is expected to grow |
   |                                                    |                | every time the server transmits a  |
   |                                                    |                | packet. In general, it should      |
   |                                                    |                | roughly match ``pkt4-received``, as|
   |                                                    |                | most incoming packets cause the    |
   |                                                    |                | server to respond. There are       |
   |                                                    |                | exceptions (e.g. DHCPRELEASE), so  |
   |                                                    |                | do not worry if it is less than    |
   |                                                    |                | pkt4-received.                     |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-offer-sent                                    | integer        | Number of DHCPOFFER packets sent.  |
   |                                                    |                | This statistic is expected to grow |
   |                                                    |                | in most cases after a DHCPDISCOVER |
   |                                                    |                | is processed. There are certain    |
   |                                                    |                | uncommon but valid cases where     |
   |                                                    |                | incoming DHCPDISCOVER packets are  |
   |                                                    |                | dropped, but in general this       |
   |                                                    |                | statistic is expected to be close  |
   |                                                    |                | to ``pkt4-discover-received``.     |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-ack-sent                                      | integer        | Number of DHCPACK packets sent.    |
   |                                                    |                | This statistic is expected to grow |
   |                                                    |                | in most cases after a DHCPREQUEST  |
   |                                                    |                | is processed; there are certain    |
   |                                                    |                | cases where DHCPNAK is sent        |
   |                                                    |                | instead. In general, the sum of    |
   |                                                    |                | ``pkt4-ack-sent`` and              |
   |                                                    |                | ``pkt4-nak-sent`` should be close  |
   |                                                    |                | to ``pkt4-request-received``.      |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-nak-sent                                      | integer        | Number of DHCPNAK packets sent.    |
   |                                                    |                | This statistic is expected to grow |
   |                                                    |                | when the server chooses not to     |
   |                                                    |                | honor the address requested by a   |
   |                                                    |                | client. In general, the sum of     |
   |                                                    |                | ``pkt4-ack-sent`` and              |
   |                                                    |                | ``pkt4-nak-sent`` should be close  |
   |                                                    |                | to ``pkt4-request-received``.      |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-parse-failed                                  | integer        | Number of incoming packets that    |
   |                                                    |                | could not be parsed. A non-zero    |
   |                                                    |                | value of this statistic indicates  |
   |                                                    |                | that the server received a         |
   |                                                    |                | malformed or truncated packet.     |
   |                                                    |                | This may indicate problems in the  |
   |                                                    |                | network, faulty clients, or a bug  |
   |                                                    |                | in the server.                     |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-receive-drop                                  | integer        | Number of incoming packets that    |
   |                                                    |                | were dropped. The exact reason for |
   |                                                    |                | dropping packets is logged, but    |
   |                                                    |                | the most common reasons may be that|
   |                                                    |                | an unacceptable packet type was    |
   |                                                    |                | received, direct responses are     |
   |                                                    |                | forbidden, or the server ID sent   |
   |                                                    |                | by the client does not match the   |
   |                                                    |                | server's server ID.                |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].total-addresses                         | integer        | Total number of addresses          |
   |                                                    |                | available for DHCPv4 management    |
   |                                                    |                | for a given subnet; in other       |
   |                                                    |                | words, this is the count of all    |
   |                                                    |                | addresses in all configured pools. |
   |                                                    |                | This statistic changes only during |
   |                                                    |                | configuration updates. It does not |
   |                                                    |                | take into account any addresses    |
   |                                                    |                | that may be reserved due to host   |
   |                                                    |                | reservation. The *id* is the       |
   |                                                    |                | the subnet ID of a given subnet.   |
   |                                                    |                | This statistic is exposed for each |
   |                                                    |                | subnet separately, and is reset    |
   |                                                    |                | during a reconfiguration event.    |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].pool[pid].total-addresses               | integer        | Total number of addresses          |
   |                                                    |                | available for DHCPv4 management    |
   |                                                    |                | for a given subnet pool; in other  |
   |                                                    |                | words, this is the count of all    |
   |                                                    |                | addresses in configured subnet     |
   |                                                    |                | pool. This statistic changes only  |
   |                                                    |                | during configuration updates. It   |
   |                                                    |                | does not take into account any     |
   |                                                    |                | addresses that may be reserved due |
   |                                                    |                | to host reservation. The *id* is   |
   |                                                    |                | the subnet ID of a given subnet.   |
   |                                                    |                | The *pid* is the pool ID of a      |
   |                                                    |                | given pool. This statistic is      |
   |                                                    |                | exposed for each subnet pool       |
   |                                                    |                | separately, and is reset during a  |
   |                                                    |                | reconfiguration event.             |
   +----------------------------------------------------+----------------+------------------------------------+
   | cumulative-assigned-addresses                      | integer        | Cumulative number of addresses     |
   |                                                    |                | that have been assigned since      |
   |                                                    |                | server startup. It is incremented  |
   |                                                    |                | each time an address is assigned   |
   |                                                    |                | and is not reset when the server   |
   |                                                    |                | is reconfigured.                   |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].cumulative-assigned-addresses           | integer        | Cumulative number of assigned      |
   |                                                    |                | addresses in a given subnet. It    |
   |                                                    |                | increases every time a new lease   |
   |                                                    |                | is allocated (as a result of       |
   |                                                    |                | receiving a DHCPREQUEST message)   |
   |                                                    |                | and never decreases. The *id* is   |
   |                                                    |                | the subnet ID of the subnet. This  |
   |                                                    |                | statistic is exposed for each      |
   |                                                    |                | subnet separately, and is reset    |
   |                                                    |                | during a reconfiguration event.    |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].pool[pid].cumulative-assigned-addresses | integer        | Cumulative number of assigned      |
   |                                                    |                | addresses in a given subnet pool.  |
   |                                                    |                | It increases every time a new      |
   |                                                    |                | lease is allocated (as a result of |
   |                                                    |                | receiving a DHCPREQUEST message)   |
   |                                                    |                | and never decreases. The *id* is   |
   |                                                    |                | the subnet ID of the subnet. The   |
   |                                                    |                | *pid* is the pool ID of the pool.  |
   |                                                    |                | This statistic is exposed for each |
   |                                                    |                | subnet pool separately, and is     |
   |                                                    |                | reset during a reconfiguration     |
   |                                                    |                | event.                             |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].assigned-addresses                      | integer        | Number of assigned addresses in a  |
   |                                                    |                | given subnet. It increases every   |
   |                                                    |                | time a new lease is allocated (as  |
   |                                                    |                | a result of receiving a            |
   |                                                    |                | DHCPREQUEST message) and decreases |
   |                                                    |                | every time a lease is released (a  |
   |                                                    |                | DHCPRELEASE message is received)   |
   |                                                    |                | or expires. The *id* is the        |
   |                                                    |                | subnet ID of the subnet. This      |
   |                                                    |                | statistic is exposed for each      |
   |                                                    |                | subnet separately, and is reset    |
   |                                                    |                | during a reconfiguration event.    |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].pool[pid].assigned-addresses            | integer        | Number of assigned addresses in a  |
   |                                                    |                | given subnet pool. It increases    |
   |                                                    |                | every time a new lease is          |
   |                                                    |                | allocated (as a result of          |
   |                                                    |                | receiving a DHCPREQUEST message)   |
   |                                                    |                | and decreases every time a lease   |
   |                                                    |                | is released (a DHCPRELEASE message |
   |                                                    |                | is received) or expires. The *id*  |
   |                                                    |                | is the subnet ID of the subnet.    |
   |                                                    |                | The *pid* is the pool ID of the    |
   |                                                    |                | pool. This statistic is exposed    |
   |                                                    |                | for each subnet pool separately,   |
   |                                                    |                | and is reset during a              |
   |                                                    |                | reconfiguration event.             |
   +----------------------------------------------------+----------------+------------------------------------+
   | reclaimed-leases                                   | integer        | Number of expired leases that have |
   |                                                    |                | been reclaimed since server        |
   |                                                    |                | startup. It is incremented each    |
   |                                                    |                | time an expired lease is reclaimed |
   |                                                    |                | and never decreases. It can be     |
   |                                                    |                | used as a long-term indicator of   |
   |                                                    |                | how many actual leases have been   |
   |                                                    |                | reclaimed. This is a global        |
   |                                                    |                | statistic that covers all subnets. |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].reclaimed-leases                        | integer        | Number of expired leases           |
   |                                                    |                | associated with a given subnet     |
   |                                                    |                | that have been reclaimed since     |
   |                                                    |                | server startup. It is incremented  |
   |                                                    |                | each time an expired lease is      |
   |                                                    |                | reclaimed. The *id* is the         |
   |                                                    |                | subnet ID of a given subnet. This  |
   |                                                    |                | statistic is exposed for each      |
   |                                                    |                | subnet separately.                 |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].pool[pid].reclaimed-leases              | integer        | Number of expired leases           |
   |                                                    |                | associated with a given subnet     |
   |                                                    |                | pool that have been reclaimed      |
   |                                                    |                | since server startup. It is        |
   |                                                    |                | incremented each time an expired   |
   |                                                    |                | lease is reclaimed. The *id* is    |
   |                                                    |                | the subnet ID of a given subnet.   |
   |                                                    |                | The *pid* is the pool ID of the    |
   |                                                    |                | pool. This statistic is exposed    |
   |                                                    |                | for each subnet pool separately.   |
   +----------------------------------------------------+----------------+------------------------------------+
   | declined-addresses                                 | integer        | Number of IPv4 addresses that are  |
   |                                                    |                | currently declined; a count of the |
   |                                                    |                | number of leases currently         |
   |                                                    |                | unavailable. Once a lease is       |
   |                                                    |                | recovered, this statistic is       |
   |                                                    |                | decreased; ideally, this statistic |
   |                                                    |                | should be zero. If this statistic  |
   |                                                    |                | is non-zero or increasing, a       |
   |                                                    |                | network administrator should       |
   |                                                    |                | investigate whether there is a     |
   |                                                    |                | misbehaving device in the network. |
   |                                                    |                | This is a global statistic that    |
   |                                                    |                | covers all subnets.                |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].declined-addresses                      | integer        | Number of IPv4 addresses that are  |
   |                                                    |                | currently declined in a given      |
   |                                                    |                | subnet; a count of the number of   |
   |                                                    |                | leases currently unavailable. Once |
   |                                                    |                | a lease is recovered, this         |
   |                                                    |                | statistic is decreased; ideally,   |
   |                                                    |                | this statistic should be zero. If  |
   |                                                    |                | this statistic is non-zero or      |
   |                                                    |                | increasing, a network              |
   |                                                    |                | administrator should investigate   |
   |                                                    |                | whether there is a misbehaving     |
   |                                                    |                | device in the network. The *id* is |
   |                                                    |                | the subnet ID of a given subnet.   |
   |                                                    |                | This statistic is exposed for each |
   |                                                    |                | subnet separately.                 |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].pool[pid].declined-addresses            | integer        | Number of IPv4 addresses that are  |
   |                                                    |                | currently declined in a given      |
   |                                                    |                | subnet pool; a count of the number |
   |                                                    |                | of leases currently unavailable.   |
   |                                                    |                | Once a lease is recovered, this    |
   |                                                    |                | statistic is decreased; ideally,   |
   |                                                    |                | this statistic should be zero. If  |
   |                                                    |                | this statistic is non-zero or      |
   |                                                    |                | increasing, a network              |
   |                                                    |                | administrator should investigate   |
   |                                                    |                | whether there is a misbehaving     |
   |                                                    |                | device in the network. The *id* is |
   |                                                    |                | the subnet ID of a given subnet.   |
   |                                                    |                | The *pid* is the pool ID of the    |
   |                                                    |                | pool. This statistic is exposed    |
   |                                                    |                | for each subnet pool separately.   |
   +----------------------------------------------------+----------------+------------------------------------+
   | reclaimed-declined-addresses                       | integer        | Number of IPv4 addresses that were |
   |                                                    |                | declined, but have now been        |
   |                                                    |                | recovered. Unlike                  |
   |                                                    |                | ``declined-addresses``, this       |
   |                                                    |                | statistic never decreases. It can  |
   |                                                    |                | be used as a long-term indicator of|
   |                                                    |                | how many actual valid declines were|
   |                                                    |                | processed and recovered from. This |
   |                                                    |                | is a global statistic that covers  |
   |                                                    |                | all subnets.                       |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].reclaimed-declined-addresses            | integer        | Number of IPv4 addresses that were |
   |                                                    |                | declined, but have now been        |
   |                                                    |                | recovered. Unlike                  |
   |                                                    |                | ``declined-addresses``, this       |
   |                                                    |                | statistic never decreases. It can  |
   |                                                    |                | be used as a long-term indicator of|
   |                                                    |                | how many actual valid declines were|
   |                                                    |                | processed and recovered from. The  |
   |                                                    |                | *id* is the subnet ID of a given   |
   |                                                    |                | subnet. This statistic is exposed  |
   |                                                    |                | for each subnet separately.        |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].pool[pid].reclaimed-declined-addresses  | integer        | Number of IPv4 addresses that were |
   |                                                    |                | declined, but have now been        |
   |                                                    |                | recovered. Unlike                  |
   |                                                    |                | ``declined-addresses``, this       |
   |                                                    |                | statistic never decreases. It can  |
   |                                                    |                | be used as a long-term indicator of|
   |                                                    |                | how many actual valid declines were|
   |                                                    |                | processed and recovered from. The  |
   |                                                    |                | *id* is the subnet ID of a given   |
   |                                                    |                | subnet. The *pid* is the pool ID   |
   |                                                    |                | of the pool. This statistic is     |
   |                                                    |                | exposed for each subnet pool       |
   |                                                    |                | separately.                        |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-lease-query-received                          | integer        | Number of IPv4 DHCPLEASEQUERY      |
   |                                                    |                | packets received. (Only exists if  |
   |                                                    |                | the Leasequery hook library is     |
   |                                                    |                | loaded.)                           |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-lease-query-response-unknown-sent             | integer        | Number of IPv4 DHCPLEASEUNKNOWN    |
   |                                                    |                | responses sent. (Only exists if    |
   |                                                    |                | the Leasequery hook library is     |
   |                                                    |                | loaded.)                           |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-lease-query-response-unassigned-sent          | integer        | Number of IPv4 DHCPLEASEUNASSIGNED |
   |                                                    |                | responses sent. (Only exists if    |
   |                                                    |                | the Leasequery hook library is     |
   |                                                    |                | loaded.)                           |
   +----------------------------------------------------+----------------+------------------------------------+
   | pkt4-lease-query-response-active-sent              | integer        | Number of IPv4 DHCPLEASEACTIVE     |
   |                                                    |                | responses sent. (Only exists if    |
   |                                                    |                | the Leasequery hook library is     |
   |                                                    |                | loaded.)                           |
   +----------------------------------------------------+----------------+------------------------------------+
   | v4-allocation-fail                                 | integer        | Number of total address allocation |
   |                                                    |                | failures for a particular client.  |
   |                                                    |                | This consists of the number of     |
   |                                                    |                | lease allocation attempts that the |
   |                                                    |                | server made before giving up, if it|
   |                                                    |                | was unable to use any of the       |
   |                                                    |                | address pools. This is a global    |
   |                                                    |                | statistic that covers all subnets. |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].v4-allocation-fail                      | integer        | Number of total address allocation |
   |                                                    |                | failures for a particular client.  |
   |                                                    |                | This consists of the number of     |
   |                                                    |                | lease allocation attempts that the |
   |                                                    |                | server made before giving up, if it|
   |                                                    |                | was unable to use any of the       |
   |                                                    |                | address pools. The *id* is the     |
   |                                                    |                | subnet ID of a given subnet. This  |
   |                                                    |                | statistic is exposed for each      |
   |                                                    |                | subnet separately.                 |
   +----------------------------------------------------+----------------+------------------------------------+
   | v4-allocation-fail-shared-network                  | integer        | Number of address allocation       |
   |                                                    |                | failures for a particular client   |
   |                                                    |                | connected to a shared network.     |
   |                                                    |                | This is a global statistic that    |
   |                                                    |                | covers all subnets.                |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].v4-allocation-fail-shared-network       | integer        | Number of address allocation       |
   |                                                    |                | failures for a particular client   |
   |                                                    |                | connected to a shared network.     |
   |                                                    |                | The *id* is the subnet ID of a     |
   |                                                    |                | given subnet. This statistic is    |
   |                                                    |                | exposed for each subnet            |
   |                                                    |                | separately.                        |
   +----------------------------------------------------+----------------+------------------------------------+
   | v4-allocation-fail-subnet                          | integer        | Number of address allocation       |
   |                                                    |                | failures for a particular client   |
   |                                                    |                | connected to a subnet that does    |
   |                                                    |                | not belong to a shared network.    |
   |                                                    |                | This is a global statistic that    |
   |                                                    |                | covers all subnets.                |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].v4-allocation-fail-subnet               | integer        | Number of address allocation       |
   |                                                    |                | failures for a particular client   |
   |                                                    |                | connected to a subnet that does    |
   |                                                    |                | not belong to a shared network.    |
   |                                                    |                | The *id* is the subnet ID of a     |
   |                                                    |                | given subnet. This statistic is    |
   |                                                    |                | exposed for each subnet            |
   |                                                    |                | separately.                        |
   +----------------------------------------------------+----------------+------------------------------------+
   | v4-allocation-fail-no-pools                        | integer        | Number of address allocation       |
   |                                                    |                | failures because the server could  |
   |                                                    |                | not use any configured pools for   |
   |                                                    |                | a particular client. It is also    |
   |                                                    |                | possible that all of the subnets   |
   |                                                    |                | from which the server attempted to |
   |                                                    |                | assign an address lack address     |
   |                                                    |                | pools. In this case, it should be  |
   |                                                    |                | considered misconfiguration if an  |
   |                                                    |                | operator expects that some clients |
   |                                                    |                | should be assigned dynamic         |
   |                                                    |                | addresses. This is a global        |
   |                                                    |                | statistic that covers all subnets. |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].v4-allocation-fail-no-pools             | integer        | Number of address allocation       |
   |                                                    |                | failures because the server could  |
   |                                                    |                | not use any configured pools for   |
   |                                                    |                | a particular client. It is also    |
   |                                                    |                | possible that all of the subnets   |
   |                                                    |                | from which the server attempted to |
   |                                                    |                | assign an address lack address     |
   |                                                    |                | pools. In this case, it should be  |
   |                                                    |                | considered misconfiguration if an  |
   |                                                    |                | operator expects that some clients |
   |                                                    |                | should be assigned dynamic         |
   |                                                    |                | addresses. The *id* is the         |
   |                                                    |                | subnet ID of a given subnet. This  |
   |                                                    |                | statistic is exposed for each      |
   |                                                    |                | subnet separately.                 |
   +----------------------------------------------------+----------------+------------------------------------+
   | v4-allocation-fail-classes                         | integer        | Number of address allocation       |
   |                                                    |                | failures when the client's packet  |
   |                                                    |                | belongs to one or more classes.    |
   |                                                    |                | There may be several reasons why a |
   |                                                    |                | lease was not assigned: for        |
   |                                                    |                | example, if all pools              |
   |                                                    |                | require packets to belong to       |
   |                                                    |                | certain classes and an incoming    |
   |                                                    |                | packet does not belong to any.     |
   |                                                    |                | Another case where this            |
   |                                                    |                | information may be useful is to    |
   |                                                    |                | indicate that the pool reserved    |
   |                                                    |                | for a given class has run out of   |
   |                                                    |                | addresses. This is a global        |
   |                                                    |                | statistic that covers all subnets. |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].v4-allocation-fail-classes              | integer        | Number of address allocation       |
   |                                                    |                | failures when the client's packet  |
   |                                                    |                | belongs to one or more classes.    |
   |                                                    |                | There may be several reasons why a |
   |                                                    |                | lease was not assigned: for        |
   |                                                    |                | example, if all pools              |
   |                                                    |                | require packets to belong to       |
   |                                                    |                | certain classes and an incoming    |
   |                                                    |                | packet does not belong to any.     |
   |                                                    |                | Another case where this            |
   |                                                    |                | information may be useful is to    |
   |                                                    |                | indicate that the pool reserved    |
   |                                                    |                | for a given class has run out of   |
   |                                                    |                | addresses. The *id* is the         |
   |                                                    |                | subnet ID of a given subnet. This  |
   |                                                    |                | statistic is exposed for each      |
   |                                                    |                | subnet separately.                 |
   +----------------------------------------------------+----------------+------------------------------------+
   | v4-lease-reuses                                    | integer        | Number of times an IPv4 lease had  |
   |                                                    |                | its CLTT increased in memory and   |
   |                                                    |                | its expiration time left unchanged |
   |                                                    |                | in persistent storage, as part of  |
   |                                                    |                | the lease caching feature. This is |
   |                                                    |                | referred to as a lease reuse.      |
   |                                                    |                | This statistic is global.          |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].v4-lease-reuses                         | integer        | Number of times an IPv4 lease had  |
   |                                                    |                | its CLTT increased in memory and   |
   |                                                    |                | its expiration time left unchanged |
   |                                                    |                | in persistent storage, as part of  |
   |                                                    |                | the lease caching feature. This is |
   |                                                    |                | referred to as a lease reuse.      |
   |                                                    |                | This statistic is on a per-subnet  |
   |                                                    |                | basis. The *id* is the subnet ID   |
   |                                                    |                | of a given subnet.                 |
   +----------------------------------------------------+----------------+------------------------------------+
   | v4-reservation-conflicts                           | integer        | Number of host reservation         |
   |                                                    |                | allocation conflicts which have    |
   |                                                    |                | occurred across every subnet. When |
   |                                                    |                | a client sends a DHCP Discover and |
   |                                                    |                | is matched to a host reservation   |
   |                                                    |                | which is already leased to another |
   |                                                    |                | client, this counter is increased  |
   |                                                    |                | by 1.                              |
   +----------------------------------------------------+----------------+------------------------------------+
   | subnet[id].v4-reservation-conflicts                | integer        | Number of host reservation         |
   |                                                    |                | allocation conflicts which have    |
   |                                                    |                | occurred in a specific subnet.     |
   |                                                    |                | When a client sends a DHCP         |
   |                                                    |                | Discover and is matched to a host  |
   |                                                    |                | reservation which is already       |
   |                                                    |                | leased to another client, this     |
   |                                                    |                | counter is increased by 1.         |
   +----------------------------------------------------+----------------+------------------------------------+

.. note::

   The pool ID can be configured on each pool by explicitly setting the ``pool-id``
   parameter in the pool parameter map. If not configured, ``pool-id`` defaults to 0.
   The statistics related to pool ID 0 refer to all the statistics of all the pools
   that have an unconfigured ``pool-id``.
   The pool ID does not need to be unique within the subnet or across subnets.
   The statistics regarding a specific pool ID within a subnet are combined with the
   other statistics of all other pools with the same pool ID in the respective subnet.

.. note::

   This section describes DHCPv4-specific statistics. For a general
   overview and usage of statistics, see :ref:`stats`.

The DHCPv4 server provides two global parameters to control the default sample
limits of statistics:

- ``statistic-default-sample-count`` - determines the default maximum
  number of samples to be kept. The special value of 0
  indicates that a default maximum age should be used.

- ``statistic-default-sample-age`` - determines the default maximum
  age, in seconds, of samples to be kept.

For instance, to reduce the statistic-keeping overhead, set
the default maximum sample count to 1 so only one sample is kept:

::

   "Dhcp4": {
       "statistic-default-sample-count": 1,
       "subnet4": [
           {
               ...
           },
           ...
       ],
       ...
   }

Statistics can be retrieved periodically to gain more insight into Kea operations. One tool that
leverages that capability is ISC Stork. See :ref:`stork` for details.


.. _dhcp4-ctrl-channels:

Management API for the DHCPv4 Server
====================================

The management API allows the issuing of specific management commands,
such as statistics retrieval, reconfiguration, or shutdown. For more
details, see :ref:`ctrl-channel`. By default there are no sockets
open; to instruct Kea to open a socket, the following entry in the
configuration file can be used:

::

   "Dhcp4": {
       "control-sockets": [
           {
               "socket-type": "unix",
               "socket-name": "/path/to/the/unix/socket"
           }
       ],

       "subnet4": [
           {
               ...
           },
           ...
       ],
       ...
   }

.. note:

   For backward compatibility the ``control-socket`` keyword is still
   recognized by Kea version newer than 2.7.2: a ``control-socket`` entry
   is put into a ``control-sockets`` list by the configuration parser.

.. _dhcp4-unix-ctrl-channel:

UNIX Control Socket
-------------------

Until Kea server 2.7.2 the only supported communication channel type was
the UNIX stream socket with ``socket-type`` set to ``unix`` and
``socket-name`` to the file path of the UNIX/LOCAL socket.

The length of the path specified by the ``socket-name`` parameter is
restricted by the maximum length for the UNIX socket name on the administrator's
operating system, i.e. the size of the ``sun_path`` field in the
``sockaddr_un`` structure, decreased by 1. This value varies on
different operating systems, between 91 and 107 characters. Typical
values are 107 on Linux and 103 on FreeBSD.

Kea supports only one ``unix`` control socket in the "control-sockets" list.

.. note::

    As of Kea 2.7.9, control sockets may only reside in the directory
    determined during compilation as ``"[kea-install-dir]/var/run/kea"``,
    which must also have ``0750`` access rights. This path may be overridden
    at startup by setting the environment variable ``KEA_CONTROL_SOCKET_DIR``
    to the desired path.  If a path other than this value is used in
    ``socket-name``, Kea will emit an error and refuse to start or, if already
    running, log an unrecoverable error.  For ease of use in simply omit the
    path component from ``socket-name``.

Communication over the control channel is conducted using JSON
structures. See the
`Control Channel section in the Kea Developer's Guide
<https://reports.kea.isc.org/dev_guide/d2/d96/ctrlSocket.html>`__
for more details.

The DHCPv4 server supports the following operational commands:

- :isccmd:`build-report`
- :isccmd:`config-get`
- :isccmd:`config-hash-get`
- :isccmd:`config-reload`
- :isccmd:`config-set`
- :isccmd:`config-test`
- :isccmd:`config-write`
- :isccmd:`dhcp-disable`
- :isccmd:`dhcp-enable`
- :isccmd:`leases-reclaim`
- :isccmd:`list-commands`
- :isccmd:`shutdown`
- :isccmd:`status-get`
- :isccmd:`version-get`

as described in :ref:`commands-common`. In addition, it supports the
following statistics-related commands:

- :isccmd:`statistic-get`
- :isccmd:`statistic-reset`
- :isccmd:`statistic-remove`
- :isccmd:`statistic-get`-all
- :isccmd:`statistic-reset`-all
- :isccmd:`statistic-remove`-all
- :isccmd:`statistic-sample-age-set`
- :isccmd:`statistic-sample-age-set`-all
- :isccmd:`statistic-sample-count-set`
- :isccmd:`statistic-sample-count-set`-all

as described in :ref:`command-stats`.

.. _dhcp4-http-ctrl-channel:

HTTP/HTTPS Control Socket
-------------------------

The ``socket-type`` must be ``http`` or ``https`` (when the type is ``https``
TLS is required). The ``socket-address`` (default ``127.0.0.1``) and
``socket-port`` (default 8000) specify an IP address and port to which
the HTTP service will be bound.

Since Kea 2.7.5 the ``http-headers`` parameter specifies a list of
extra HTTP headers to add to HTTP responses.

The ``trust-anchor``, ``cert-file``, ``key-file``, and ``cert-required``
parameters specify the TLS setup for HTTP, i.e. HTTPS. If these parameters
are not specified, HTTP is used. The TLS/HTTPS support in Kea is
described in :ref:`tls`.

Basic HTTP authentication protects
against unauthorized uses of the control agent by local users. For
protection against remote attackers, HTTPS and reverse proxy of
:ref:`agent-secure-connection` provide stronger security.

The authentication is described in the ``authentication`` block
with the mandatory ``type`` parameter, which selects the authentication.
Currently only the basic HTTP authentication (type basic) is supported.

The ``realm`` authentication parameter (default ``kea-dhcpv4-server``
is used for error messages when the basic HTTP authentication is required
but the client is not authorized.

When the ``clients`` authentication list is configured and not empty,
basic HTTP authentication is required. Each element of the list
specifies a user ID and a password. The user ID is mandatory, must
not be empty, and must not contain the colon (:) character. The
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

Since Kea-2.7.6 Kea supports multiple HTTP/HTTPS connections.
Both IPv4 and IPv6 addresses can be used.
The server will issue an error when changing the socket type from HTTP to HTTPS
or from HTTPS to HTTP using the same address and port. This action is not
allowed as it might introduce a security issue accidentally caused by a user
mistake.
A different address or port must be specified when using the "config-set"
command to switch from HTTP to HTTPS or from HTTPS to HTTP. The same applies
when modyfying the configuration file and then running "config-reload" command.

When files are used, they are read when the configuration is loaded,
to detect configuration errors as soon as possible.

::

   "Dhcp4": {
       "control-sockets": [
           {
               "socket-type": "https",
               "socket-address": "10.20.30.40",
               "socket-port": 8004,
               "http-headers": [
                   {
                       "name": "Strict-Transport-Security",
                       "value": "max-age=31536000"
                    }
               ],
               "trust-anchor": "/path/to/the/ca-cert.pem",
               "cert-file": "/path/to/the/agent-cert.pem",
               "key-file": "/path/to/the/agent-key.pem",
               "cert-required": true,
               "authentication": {
                   "type": "basic",
                   "realm": "kea-dhcpv4-server",
                   "clients": [
                   {
                       "user": "admin",
                       "password": "1234"
                   } ]
               }
           },
           {
               "socket-type": "http",
               "socket-address": "2010:30:40::50",
               "socket-port": 8004
           }
       ],

       "subnet4": [
           {
               ...
           },
           ...
       ],
       ...
   }

.. _dhcp4-user-contexts:

User Contexts in IPv4
=====================

Kea allows the loading of hook libraries that can sometimes benefit from
additional parameters. If such a parameter is specific to the whole
library, it is typically defined as a parameter for the hook library.
However, sometimes there is a need to specify parameters that are
different for each pool.

See :ref:`user-context` for additional background regarding the
user-context idea. See :ref:`user-context-hooks` for a discussion from the
hooks perspective.

User contexts can be specified at global scope; at the shared-network, subnet,
pool, client-class, option-data, or definition level; and via host
reservation. One other useful feature is the ability to store comments or
descriptions.

Let's consider an imaginary case of devices that have colored LED lights.
Depending on their location, they should glow red, blue, or green. It
would be easy to write a hook library that would send specific values,
maybe as a vendor option. However, the server has to have some way to
specify that value for each pool. This need is addressed by user
contexts. In essence, any user data can be specified in the user context
as long as it is a valid JSON map. For example, the aforementioned case
of LED devices could be configured in the following way:

::

   "Dhcp4": {
       "subnet4": [
           {
           "id": 1,
           "subnet": "192.0.2.0/24",
           "pools": [
           {
               "pool": "192.0.2.10 - 192.0.2.20",
               # This is pool specific user context
               "user-context": { "color": "red" }
           }
           ],

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
       }
       ]
   }

Kea does not interpret or use the user-context information; it simply
stores it and makes it available to the hook libraries. It is up to each
hook library to extract that information and use it. The parser
translates a ``comment`` entry into a user context with the entry, which
allows a comment to be attached inside the configuration itself.


.. _dhcp4-std:

Supported DHCP Standards
========================

The following standards are currently supported in Kea:

-  *BOOTP Vendor Information Extensions*, `RFC 1497
   <https://tools.ietf.org/html/rfc1497>`__: This requires the open source
   BOOTP hook to be loaded. See :ref:`hooks-bootp` for details.

-  *Dynamic Host Configuration Protocol*, `RFC 1531
   <https://tools.ietf.org/html/rfc1531>`__: This RFC is obsolete and
   was replaced by RFC 1541, which in turn was replaced by RFC 2131.
   Kea supports all three RFCs.

-  *Clarifications and Extensions for the Bootstrap Protocol*, `RFC 1532
   <https://tools.ietf.org/html/rfc1532>`__: This RFC has an editorial
   error and was quickly superseeded by RFC 1542. Kea supports them both.

-  *DHCP Options and BOOTP Vendor Extensions*, `RFC 1533
   <https://tools.ietf.org/html/rfc1533>`__: This RFC is obsolete and
   was replaced by RFC 2132. Nevertheless, Kea supports the options
   defined in it.

-  *Dynamic Host Configuration Protocol*, `RFC 1541
   <https://tools.ietf.org/html/rfc1541>`__: This RFC is obsolete and
   was replaced by RFC 2131. Kea supports both.

-  *Clarifications and Extensions for the Bootstrap Protocol*, `RFC 1542
   <https://tools.ietf.org/html/rfc1542>`__: This RFC is supported.

-  *Dynamic Host Configuration Protocol*, `RFC 2131
   <https://tools.ietf.org/html/rfc2131>`__: Supported messages are
   DHCPDISCOVER (1), DHCPOFFER (2), DHCPREQUEST (3), DHCPRELEASE (7),
   DHCPINFORM (8), DHCPACK (5), and DHCPNAK(6).

-  *DHCP Options and BOOTP Vendor Extensions*, `RFC 2132
   <https://tools.ietf.org/html/rfc2132>`__: Supported options are PAD (0),
   END(255), Message Type(53), DHCP Server Identifier (54), Domain Name (15),
   DNS Servers (6), IP Address Lease Time (51), Subnet Mask (1), and Routers (3).

-  *DHCP Options for Novell Directory Services*, `RFC 2241
   <https://tools.ietf.org/html/rfc2241>`__: All three options are supported.

-  *Management of IP numbers by peg-dhcp*,
   `RFC 2322 <https://tools.ietf.org/html/rfc2322>`__: This RFC is supported,
   although additional hardware is required for full deployment.

-  *DHCP Option for The Open Group's User Authentication Protocol*,
   `RFC 2485 <https://tools.ietf.org/html/rfc2485>`__: The option is supported.

-  *DHCP Option to Disable Stateless Auto-Configuration in IPv4 Clients*,
   `RFC 2563 <https://tools.ietf.org/html/rfc2563>`__: The option is supported.

-  *DHCP Options for Service Location Protocol*, `RFC 2610
   <https://tools.ietf.org/html/rfc2610>`__: Both options are supported.

-  *The Name Service Search Option for DHCP*, `RFC 2937
   <https://tools.ietf.org/html/rfc2937>`__: The option is supported.

-  *The User Class Option for DHCP*, `RFC 3004 <https://tools.ietf.org/html/rfc3004>`__:
   The user class is supported and can be used in any expression. The option's
   structure is not parsed and has to be referenced using hex.

-  *The IPv4 Subnet Selection Option for DHCP*, `RFC 3011
   <https://tools.ietf.org/html/rfc3011>`__: The subnet-selection option is
   supported; if received in a packet, it is used in the subnet-selection
   process.

-  *DHCP Relay Agent Information Option*, `RFC 3046
   <https://tools.ietf.org/html/rfc3046>`__: Relay Agent Information,
   Circuit ID, and Remote ID options are supported.

-  *The DOCSIS (Data-Over-Cable Service Interface Specifications) Device Class
   DHCP (Dynamic Host Configuration Protocol) Relay Agent Information Sub-option*,
   `RFC 3256 <https://tools.ietf.org/html/rfc3256>`__: The DOCSIS sub-option
   is supported and can be used in any expression.

-  *Encoding Long Options in the Dynamic Host Configuration Protocol (DHCPv4)*,
   `RFC 3396 <https://tools.ietf.org/html/rfc3396>`__: The Kea server can both
   receive and send long options. The long options can be configured and Kea
   will send them as separate instances if the payload length is longer than
   255 octets.

-  *Dynamic Host Configuration Protocol (DHCP) Domain Search Option*, `RFC 3397
   <https://tools.ietf.org/html/rfc3397>`__: The option is supported.

-  *The Classless Static Route Option for Dynamic Host Configuration Protocol
   (DHCP) version 4*, `RFC 3442 <https://tools.ietf.org/html/rfc3442>`__:
   The option is supported.

-  *Dynamic Host Configuration Protocol (DHCP) Option for CableLabs Client
   Configuration*, `RFC 3495 <https://tools.ietf.org/html/rfc3495>`__:
   The option and its suboptions 1, 2, 4, 5, 6, 7 and 8 are supported.
   See :ref:`cablelabs-client-conf-suboptions` for details.

-  *Link Selection sub-option for the Relay Agent Option*, `RFC 3527
   <https://tools.ietf.org/html/rfc3527>`__: The link selection sub-option
   is supported.

-  *PacketCable Security Ticket Control Sub-Option for the DHCP CableLabs
   Client Configuration (CCC) Option*, `RFC 3594
   <https://tools.ietf.org/html/rfc3594>`__: The Security Ticket Control
   sub-option is supported.

-  *Key Distribution Center (KDC) Server Address Sub-option for the
   Dynamic Host Configuration Protocol (DHCP) CableLabs Client
   Configuration (CCC) Option*, `RFC 3634
   <https://tools.ietf.org/html/rfc3634>`__: The Key Distribution Center
   IP Address sub-option is supported.

-  *Unused Dynamic Host Configuration Protocol (DHCP) Option Codes*, `RFC 3679
   <https://tools.ietf.org/html/rfc3679>`__: Kea does not support any of the
   old options that were obsoleted by this RFC.

-  *Vendor-Identifying Vendor Options for Dynamic Host Configuration
   Protocol version 4*, `RFC 3925
   <https://tools.ietf.org/html/rfc3925>`__: The Vendor-Identifying Vendor Class
   and Vendor-Identifying Vendor-Specific Information options are supported.

-  *Reclassifying Dynamic Host Configuration Protocol version 4 (DHCPv4) Options*,
   `RFC 3942 <https://tools.ietf.org/html/rfc3942>`__: Kea supports options with
   codes greater than 127.

-  *Subscriber-ID Suboption for the DHCP Relay Agent Option*, `RFC 3993
   <https://tools.ietf.org/html/rfc3993>`__: The Subscriber-ID option is
   supported.

-  *Dynamic Host Configuration Protocol (DHCP) Options for Broadcast and Multicast
   Control Servers*, `RFC 4280 <https://tools.ietf.org/html/rfc4280>`__:
   The DHCPv4 options are supported.

-  *Node-specific Client Identifiers for Dynamic Host Configuration Protocol
   Version Four (DHCPv4)*, `RFC 4361 <https://datatracker.ietf.org/doc/html/rfc4361>`__:
   The DUID in DHCPv4 is supported.

-  *Dynamic Host Configuration Protocol (DHCP) Leasequery*, `RFC 4388
   <https://datatracker.ietf.org/doc/html/rfc4388>`__: The server functionality
   is supported. This requires leasequery hook. See :ref:`hooks-lease-query` for details.

-  *Dynamic Host Configuration Protocol (DHCP) Options for the Intel Preboot
   eXecution Environment (PXE)*, `RFC 4578
   <https://datatracker.ietf.org/doc/html/rfc4578>`__: All three options defined
   are supported.

-  *A DNS Resource Record (RR) for Encoding Dynamic Host Configuration Protocol
   (DHCP) Information (DHCID RR)*, `RFC 4701 <https://tools.ietf.org/html/rfc4701>`__:
   The DHCPv4 server supports DHCID records. The DHCP-DDNS server must be running
   to add, update, and/or delete DHCID records.

-  *The Dynamic Host Configuration Protocol (DHCP) Client Fully
   Qualified Domain Name (FQDN) Option*, `RFC 4702
   <https://tools.ietf.org/html/rfc4702>`__: The Kea server is able to handle
   the Client FQDN option. Also, it is able to use the :iscman:`kea-dhcp-ddns`
   component to initiate appropriate DNS Update operations.

-  *Resolution of Fully Qualified Domain Name (FQDN) Conflicts among Dynamic
   Host Configuration Protocol (DHCP) Clients*, `RFC 4703
   <https://tools.ietf.org/html/rfc4703>`__: The DHCPv6 server uses a DHCP-DDNS
   server to resolve conflicts.

-  *Timezone Options for DHCP*: `RFC 4833 <https://tools.ietf.org/html/rfc4833>`__:
   Both DHCPv4 options are supported.

-  *The Dynamic Host Configuration Protocol Version 4 (DHCPv4) Relay Agent Flags
   Suboption*: `RFC 5010 <https://tools.ietf.org/html/rfc5010>`__: The Relay Agent
   Flags sub-option is understood by Kea and can be used in an expression.

-  *Server Identifier Override sub-option for the Relay Agent Option*, `RFC 5107
   <https://tools.ietf.org/html/rfc5107>`__: The server identifier override
   sub-option is supported. The implementation is not complete according to the
   RFC, because the server does not store the RAI, but the functionality handles
   expected use cases.

-  *DHCP Options for Protocol for Carrying Authentication for Network Access
   (PANA) Authentication Agents*: `RFC 5192 <https://tools.ietf.org/html/rfc5192>`__:
   The PANA option is supported.

-  *Discovering Location-to-Service Translation (LoST) Servers Using the
   Dynamic Host Configuration Protocol (DHCP)*: `RFC 5223
   <https://tools.ietf.org/html/rfc5223>`__: The LOST option is supported.

-  *Control And Provisioning of Wireless Access Points (CAPWAP) Access Controller
   DHCP Option*: `RFC 5417 <https://tools.ietf.org/html/rfc5417>`__: The CAPWAP
   for IPv4 option is supported.

-  *DHCPv4 Lease Query by Relay Agent Remote ID*, `RFC 6148
   <https://tools.ietf.org/html/rfc6148>`__: The leasequery by remote-id is
   supported. This requires leasequery hook. See :ref:`hooks-lease-query` for details.

-  *Client Identifier Option in DHCP Server Replies*, `RFC 6842
   <https://tools.ietf.org/html/rfc6842>`__: The server by default sends back
   the ``client-id`` option. That capability can be disabled. See
   :ref:`dhcp4-echo-client-id` for details.

-  *The DHCPv4 Relay Agent Identifier Sub-Option*, `RFC 6925
   <https://tools.ietf.org/html/rfc6925>`__: The relay-id option is supported and
   can be used in all features that are using expressions (client classification,
   flex-id reservations, etc.).

-  *DHCPv4 Bulk Leasequery*, `RFC 6926 <https://tools.ietf.org/html/rfc6926>`__: The
   server functionality (TCP connections, new query types, multiple responses, etc.)
   is supported. This requires leasequery hook. See :ref:`hooks-lease-query` for details.

-  *Generalized UDP Source Port for the DHCP Relay Agent Option*, `RFC 8357
   <https://tools.ietf.org/html/rfc8357>`__: The Kea server handles the Relay
   Agent Information Source Port sub-option in a received message, remembers the
   UDP port, and sends back a reply to the same relay agent using this UDP port.

-  *Captive-Portal Identification in DHCP and Router Advertisements (RAs)*, `RFC
   8910 <https://tools.ietf.org/html/rfc8910>`__: The Kea server can configure
   both v4 and v6 versions of the captive portal options.

-  *IPv6-Only Preferred Option for DHCPv4*, `RFC 8925
   <https://tools.ietf.org/html/rfc8925>`__: The Kea server is able to designate
   its pools and subnets as IPv6-Only Preferred and send back the
   ``v6-only-preferred`` option to clients that requested it.

-  *DHCP and Router Advertisement Options for the Discovery of Network-designated
   Resolvers (DNR)*, `RFC 9463 <https://tools.ietf.org/html/rfc9463>`__. The Kea server
   supports the DNR option.

Known RFC Violations
--------------------

In principle, Kea aspires to be a reference implementation and aims to implement 100% of the RFC standards.
However, in some cases there are practical aspects that prevent Kea from completely adhering to the text of all RFC documents.

- `RFC 2131 <https://tools.ietf.org/html/rfc2131>`__, page 30, says that if the incoming DHCPREQUEST packet has no
  "requested IP address" option and ``ciaddr`` is not set, the server is supposed to respond with NAK. However,
  broken clients exist that will always send a DHCPREQUEST without those options indicated. In that event, Kea accepts the DHCPREQUEST,
  assigns an address, and responds with an ACK.

- `RFC 2131 <https://tools.ietf.org/html/rfc2131>`__, table 5, says that messages
  of type DHCPDECLINE or DHCPRELEASE must have the server identifier set and
  should be dropped if that option is missing. However, ISC DHCP does not enforce this, presumably as a compatibility
  effort for broken clients, and the Kea team decided to follow suit.

.. _dhcp4-limit:

DHCPv4 Server Limitations
=========================

These are the current known limitations of the Kea DHCPv4 server software. Most of
them are reflections of the current stage of development and should be
treated as “not yet implemented,” rather than as actual limitations.
However, some of them are implications of the design choices made. Those
are clearly marked as such.

-  On the Linux and BSD system families, DHCP messages are sent and
   received over raw sockets (using LPF and BPF) and all packet
   headers (including data link layer, IP, and UDP headers) are created
   and parsed by Kea, rather than by the system kernel. Currently, Kea
   can only parse the data-link layer headers with a format adhering to
   the IEEE 802.3 (Ethernet) standard, and assumes this data-link-layer header
   format for all interfaces. Thus, Kea does not work on interfaces
   which use different data-link-layer header formats, with the exception of
   LPF being able to handle InfiniBand framing, thus enabling Kea to serve
   these kind of interfaces on Linux.

.. _dhcp4-srv-examples:

Kea DHCPv4 Server Examples
==========================

A collection of simple-to-use examples for the DHCPv4 component of Kea
is available with the source files, located in the ``doc/examples/kea4``
directory.

.. _dhcp4-cb:

Configuration Backend in DHCPv4
===============================

In the :ref:`config-backend` section we have described the Configuration
Backend (CB) feature, its applicability, and its limitations. This section focuses
on the usage of the CB with the Kea DHCPv4 server. It lists the supported
parameters, describes limitations, and gives examples of DHCPv4
server configurations to take advantage of the CB. Please also refer to
the corresponding section :ref:`dhcp6-cb` for DHCPv6-specific usage of
the CB.

.. _dhcp4-cb-parameters:

Supported Parameters
--------------------

The ultimate goal for the CB is to serve as a central configuration
repository for one or multiple Kea servers connected to a database.
In currently supported Kea versions, only a subset of
the DHCPv4 server parameters can be configured in the database. All other
parameters must be specified in the JSON configuration file, if
required.

All supported parameters can be configured via :ischooklib:`libdhcp_cb_cmds.so`.
The general rule is that
scalar global parameters are set using
:isccmd:`remote-global-parameter4-set`; shared-network-specific parameters
are set using :isccmd:`remote-network4-set`; and subnet-level and pool-level
parameters are set using :isccmd:`remote-subnet4-set`. Whenever
there is an exception to this general rule, it is highlighted in the
table. Non-scalar global parameters have dedicated commands; for example,
the global DHCPv4 options (``option-data``) are modified using
:isccmd:`remote-option4-global-set`. Client classes, together with class-specific
option definitions and DHCPv4 options, are configured using the
:isccmd:`remote-class4-set` command.

The :ref:`cb-sharing` section explains the concept of shareable
and non-shareable configuration elements and the limitations for
sharing them between multiple servers. In the DHCP configuration (both DHCPv4
and DHCPv6), the shareable configuration elements are subnets and shared
networks. Thus, they can be explicitly associated with multiple server tags.
The global parameters, option definitions, and global options are non-shareable
and can be associated with only one server tag. This rule does not apply
to the configuration elements associated with ``all`` servers. Any configuration
element associated with ``all`` servers (using the ``all`` keyword as a server tag) is
used by all servers connecting to the configuration database.

The following table lists DHCPv4-specific parameters supported by the
configuration backend, with an indication of the level of the hierarchy
at which it is currently supported.

.. table:: List of DHCPv4 parameters supported by the configuration backend

   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | Parameter                   | Global                     | Client       | Shared      | Subnet      | Pool        |
   |                             |                            | Class        | Network     |             |             |
   +=============================+============================+==============+=============+=============+=============+
   | 4o6-interface               | n/a                        | n/a          | n/a         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | 4o6-interface-id            | n/a                        | n/a          | n/a         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | 4o6-subnet                  | n/a                        | n/a          | n/a         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | allocator                   | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | boot-file-name              | yes                        | yes          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | cache-max-age               | yes                        | n/a          | no          | no          | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | cache-threshold             | yes                        | n/a          | no          | no          | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | calculate-tee-times         | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | client-class                | n/a                        | n/a          | yes         | yes         | yes         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | ddns-send-update            | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | ddns-override-no-update     | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | ddns-override-client-update | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | ddns-replace-client-name    | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | ddns-generated-prefix       | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | ddns-qualifying-suffix      | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | decline-probation-period    | yes                        | n/a          | n/a         | n/a         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | dhcp4o6-port                | yes                        | n/a          | n/a         | n/a         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | echo-client-id              | yes                        | n/a          | n/a         | n/a         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | hostname-char-set           | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | hostname-char-replacement   | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | interface                   | n/a                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | match-client-id             | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | min-valid-lifetime          | yes                        | yes          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | max-valid-lifetime          | yes                        | yes          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | next-server                 | yes                        | yes          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | option-data                 | yes (via                   | yes          | yes         | yes         | yes         |
   |                             | remote-option4-global-set) |              |             |             |             |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | option-def                  | yes (via                   | yes          | n/a         | n/a         | n/a         |
   |                             | remote-option-def4-set)    |              |             |             |             |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | rebind-timer                | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | renew-timer                 | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | server-hostname             | yes                        | yes          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | valid-lifetime              | yes                        | yes          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | relay                       | n/a                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | require-client-classes      | no                         | n/a          | yes         | yes         | yes         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | evaluate-additional-classes | no                         | n/a          | yes         | yes         | yes         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | reservations-global         | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | reservations-in-subnet      | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | reservations-out-of-pool    | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | t1-percent                  | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+
   | t2-percent                  | yes                        | n/a          | yes         | yes         | n/a         |
   +-----------------------------+----------------------------+--------------+-------------+-------------+-------------+

-  ``yes`` - indicates that the parameter is supported at the given
   level of the hierarchy and can be configured via the configuration backend.

-  ``no`` - indicates that a parameter is supported at the given level
   of the hierarchy but cannot be configured via the configuration backend.

-  ``n/a`` -  indicates that a given parameter is not applicable
   at the particular level of the hierarchy or that the
   server does not support the parameter at that level.

Some scalar parameters contained by top-level global maps are supported by the configuration backend.

.. table:: List of DHCPv4 map parameters supported by the configuration backend

   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | Parameter name (flat naming format)                              | Global map                   | Parameter name                   |
   +==================================================================+==============================+==================================+
   | compatibility.ignore-dhcp-server-identifier                      | compatibility                | ignore-dhcp-server-identifier    |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | compatibility.ignore-rai-link-selection                          | compatibility                | ignore-rai-link-selection        |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | compatibility.lenient-option-parsing                             | compatibility                | lenient-option-parsing           |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | compatibility.exclude-first-last-24                              | compatibility                | exclude-first-last-24            |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-ddns.enable-updates                                         | dhcp-ddns                    | enable-updates                   |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-ddns.max-queue-size                                         | dhcp-ddns                    | max-queue-size                   |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-ddns.ncr-format                                             | dhcp-ddns                    | ncr-format                       |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-ddns.ncr-protocol                                           | dhcp-ddns                    | ncr-protocol                     |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-ddns.sender-ip                                              | dhcp-ddns                    | sender-ip                        |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-ddns.sender-port                                            | dhcp-ddns                    | sender-port                      |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-ddns.server-ip                                              | dhcp-ddns                    | server-ip                        |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-ddns.server-port                                            | dhcp-ddns                    | server-port                      |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | expired-leases-processing.flush-reclaimed-timer-wait-time        | expired-leases-processing    | flush-reclaimed-timer-wait-time  |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | expired-leases-processing.hold-reclaimed-time                    | expired-leases-processing    | hold-reclaimed-time              |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | expired-leases-processing.max-reclaim-leases                     | expired-leases-processing    | max-reclaim-leases               |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | expired-leases-processing.max-reclaim-time                       | expired-leases-processing    | max-reclaim-time                 |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | expired-leases-processing.reclaim-timer-wait-time                | expired-leases-processing    | reclaim-timer-wait-time          |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | expired-leases-processing.unwarned-reclaim-cycles                | expired-leases-processing    | unwarned-reclaim-cycles          |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | multi-threading.enable-multi-threading                           | multi-threading              | enable-multi-threading           |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | multi-threading.thread-pool-size                                 | multi-threading              | thread-pool-size                 |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | multi-threading.packet-queue-size                                | multi-threading              | packet-queue-size                |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | sanity-checks.lease-checks                                       | sanity-checks                | lease-checks                     |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | sanity-checks.extended-info-checks                               | sanity-checks                | extended-info-checks             |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-queue-control.enable-queue                                  | dhcp-queue-control           | enable-queue                     |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-queue-control.queue-type                                    | dhcp-queue-control           | queue-type                       |
   +------------------------------------------------------------------+------------------------------+----------------------------------+
   | dhcp-queue-control.capacity                                      | dhcp-queue-control           | capacity                         |
   +------------------------------------------------------------------+------------------------------+----------------------------------+

Some global list parameters containing only scalar types are supported by the configuration backend.

.. table:: List of DHCPv4 list parameters supported by the configuration backend

   +------------------------------------------------------------------+
   | Parameter name                | List container parameter type    |
   +==================================================================+
   | host-reservation-identifiers  | string                           |
   +------------------------------------------------------------------+

.. _dhcp4-cb-json:

Enabling the Configuration Backend
----------------------------------

Consider the following configuration snippet, which uses a MySQL configuration
database:

.. code-block:: json

   {
       "Dhcp4": {
           "server-tag": "my DHCPv4 server",
           "config-control": {
               "config-databases": [
                   {
                       "type": "mysql",
                       "name": "kea",
                       "user": "kea",
                       "password": "1234",
                       "host": "192.0.2.1",
                       "port": 3302
                   }
               ],
               "config-fetch-wait-time": 20
           },
           "hooks-libraries": [
               {
                   "library": "/usr/local/lib/kea/hooks/libdhcp_mysql.so"
               },
               {
                   "library": "/usr/local/lib/kea/hooks/libdhcp_cb_cmds.so"
               }
           ]
       }
   }

The following snippet illustrates the use of a PostgreSQL database:

.. code-block:: json

   {
       "Dhcp4": {
           "server-tag": "my DHCPv4 server",
           "config-control": {
               "config-databases": [
                   {
                       "type": "postgresql",
                       "name": "kea",
                       "user": "kea",
                       "password": "1234",
                       "host": "192.0.2.1",
                       "port": 3302
                   }
               ],
               "config-fetch-wait-time": 20
           },
           "hooks-libraries": [
               {
                   "library": "/usr/local/lib/kea/hooks/libdhcp_pgsql.so"
               },
               {
                   "library": "/usr/local/lib/kea/hooks/libdhcp_cb_cmds.so"
               }
           ]
       }
   }

The ``config-control`` map contains two parameters. ``config-databases``
is a list that contains one element, which includes the database type, its location,
and the credentials to be used to connect to this database. (Note that
the parameters specified here correspond to the database specification
for the lease database backend and hosts database backend.) Currently
only one database connection can be specified on the
``config-databases`` list. The server connects to this database
during startup or reconfiguration, and fetches the configuration
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
   configuration file with overlapping IDs and/or prefixes with the
   subnets from the database will be superseded by those from the
   database.

Once the Kea server is configured, it starts periodically polling
the database for configuration changes. The polling frequency is
controlled by the ``config-fetch-wait-time`` parameter, expressed
in seconds; it is the period between the time when the server
completed its last poll (and possibly the local configuration update) and
the time when it will begin polling again. In the example above, this period
is set to 20 seconds. This means that after adding a new configuration
into the database (e.g. adding a new subnet), it will take up to 20 seconds
(plus the time needed to fetch and apply the new configuration) before
the server starts using this subnet. The lower the
``config-fetch-wait-time`` value, the shorter the time for the server to
react to incremental configuration updates in the database. On the
other hand, polling the database too frequently may impact the DHCP
server's performance, because the server needs to make at least one query
to the database to discover any pending configuration updates. The
default value of ``config-fetch-wait-time`` is 30 seconds.

The :isccmd:`config-backend-pull` command can be used to force the server to
immediately poll any configuration changes from the database and avoid
waiting for the next fetch cycle.

In the configuration examples above, two hook libraries are loaded. The first
is a library which implements the configuration backend for a specific database
type: :ischooklib:`libdhcp_mysql.so` provides support for MySQL and
:ischooklib:`libdhcp_pgsql.so` provides support for PostgreSQL. The library
loaded must match the database ``type`` specified within the ``config-control``
parameter; otherwise an error is logged when the server attempts to load its
configuration, and the load fails.

The second hook library, :ischooklib:`libdhcp_cb_cmds.so`, is optional. It should
be loaded when the Kea server instance is to be used to manage the
configuration in the database. See the :ref:`hooks-cb-cmds` section for
details.

.. _dhcp4-compatibility:

Kea DHCPv4 Compatibility Configuration Parameters
=================================================

ISC's intention is for Kea to follow the RFC documents to promote better standards
compliance. However, many buggy DHCP implementations already exist that cannot be
easily fixed or upgraded. Therefore, Kea provides an easy-to-use compatibility
mode for broken or non-compliant clients. For that purpose, the compatibility option must be
enabled to permit uncommon practices:

.. code-block:: json

    {
      "Dhcp4": {
        "compatibility": {
        }
      }
    }


Lenient Option Parsing
----------------------

By default, tuple fields defined in custom options are parsed as a set of
length-value pairs.

With ``"lenient-option-parsing": true``, if a length ever exceeded the rest of
the option's buffer, previous versions of Kea returned a log message ``unable to
parse the opaque data tuple, the buffer length is x, but the tuple length is y``
with ``x < y``; this no longer occurs. Instead, the value is considered to be the rest of the buffer,
or in terms of the log message above, the tuple length ``y`` becomes ``x``.

.. code-block:: json

    {
      "Dhcp4": {
        "compatibility": {
          "lenient-option-parsing": true
        }
      }
    }

Starting with Kea version 2.5.8, this parsing is extended to silently ignore
FQDN (81) options with some invalid domain names.

Ignore DHCP Server Identifier
-----------------------------

With ``"ignore-dhcp-server-identifier": true``, the server does not check the
address in the DHCP Server Identifier option, i.e. whether a query is sent
to this server or another one (and in the second case dropping the query).

.. code-block:: json

    {
      "Dhcp4": {
        "compatibility": {
          "ignore-dhcp-server-identifier": true
        }
      }
    }


Ignore RAI Link Selection
-------------------------

With ``"ignore-rai-link-selection": true``, Relay Agent Information Link
Selection sub-option data is not used for subnet selection. In this case,
normal logic drives the subnet selection, instead of attempting to use the subnet specified
by the sub-option. This option is not RFC-compliant and is set to ``false`` by
default. Setting this option to ``true`` can help with subnet selection in
certain scenarios; for example, when DHCP relays do not allow the administrator to
specify which sub-options are included in the Relay Agent Information option,
and include incorrect Link Selection information.

.. code-block:: json

    {
      "Dhcp4": {
        "compatibility": {
          "ignore-rai-link-selection": true
        }
      }
    }

Exclude First Last Addresses in /24 Subnets or Larger
-----------------------------------------------------

The ``exclude-first-last-24`` compatibility flag is described in
:ref:`dhcp4-address-config` (when true .0 and .255 addresses are excluded
from subnets with prefix length less than or equal to 24).

.. _dhcp4_allocation_strategies:

Address Allocation Strategies in DHCPv4
=======================================

A DHCP server follows a complicated algorithm to select an IPv4 address for a client.
It prefers assigning specific addresses requested by the client and the addresses for
which the client has reservations.

If the client requests no particular address and
has no reservations, or other clients are already using any requested addresses, the server must
find another available address within the configured pools. A server function called
an "allocator" is responsible in Kea for finding an available address in such a case.

The Kea DHCPv4 server provides configuration parameters to select different allocators
at the global, shared-network, and subnet levels.
Consider the following example:

.. code-block:: json

    {
        "Dhcp4": {
            "allocator": "random",
            "subnet4": [
                {
                    "id": 1,
                    "subnet": "10.0.0.0/8",
                    "allocator": "iterative"
                },
                {
                    "id": 2,
                    "subnet": "192.0.2.0/24"
                }
            ]
        }
    }

This allocator overrides the default iterative allocation strategy at the global level and
selects the random allocation instead. The random allocation will be used
for the subnet with ID 2, while the iterative allocation will be used for the subnet
with ID 1.

The following sections describe the supported allocators and their
recommended uses.

Allocators Comparison
---------------------

In the table below, we briefly compare the supported allocators, all of which
are described in detail in later sections.

.. table:: Comparison of the lease allocators supported by Kea DHCPv4

   +------------------+-----------------------------+------------------------------+-----------------------+------------------------------+----------------+
   | Allocator        | Low Utilization Performance | High Utilization Performance | Lease Randomization   | Startup/Configuration        | Memory Usage   |
   +==================+=============================+==============================+=======================+==============================+================+
   | Iterative        | very high                   | low                          | no                    | very fast                    | low            |
   +------------------+-----------------------------+------------------------------+-----------------------+------------------------------+----------------+
   | Random           | high                        | low                          | yes                   | very fast                    | high (varying) |
   +------------------+-----------------------------+------------------------------+-----------------------+------------------------------+----------------+
   | Free Lease Queue | high                        | high                         | yes                   | slow (depends on pool sizes) | high (varying) |
   +------------------+-----------------------------+------------------------------+-----------------------+------------------------------+----------------+


Iterative Allocator
-------------------
This is the default allocator used by the Kea DHCPv4 server. It remembers the
last offered address and offers this address, increased by one, to the next client.
For example, it may offer addresses in this order: ``192.0.2.10``, ``192.0.2.11``,
``192.0.2.12``, and so on. The time to find and offer the next address is very
short; thus, this is the most performant allocator when pool utilization
is low and there is a high probability that the next address is available.

The iterative allocation underperforms when multiple DHCP servers share a lease
database or are connected to a cluster. The servers tend to offer and allocate
the same blocks of addresses to different clients independently, which causes many
allocation conflicts between the servers and retransmissions by clients. A random
allocation addresses this issue by dispersing the allocation order.

Random Allocator
----------------

The random allocator uses a uniform randomization function to select offered
addresses from subnet pools. It is suitable in deployments where multiple servers
are connected to a shared
database or a database cluster. By dispersing the offered addresses, the servers
minimize the risk of allocating the same address to two different clients at
the same or nearly the same time. In addition, it improves the server's resilience against
attacks based on allocation predictability.

The random allocator is, however, slightly slower than the iterative allocator.
Moreover, it increases the server's memory consumption because it must remember
randomized addresses to avoid offering them repeatedly. Memory consumption grows
with the number of offered addresses; in other words, larger pools and more
clients increase memory consumption by random allocation.

The following configuration snippet shows how to select the random allocator
for a subnet:

.. code-block:: json

    {
        "Dhcp4": {
            "allocator": "random",
            "subnet4": [
                {
                    "id": 1,
                    "subnet": "10.0.0.0/8",
                    "allocator": "random"
                }
            ]
        }
    }

Free Lease Queue Allocator
--------------------------

This is a sophisticated allocator whose use should be considered in subnets
with highly utilized address pools. In such cases, it can take a considerable
amount of time for the iterative or random allocator to find an available
address, because they must repeatedly check whether there is a valid lease for
an address they will offer. The number of checks can be as high as the number
of addresses in the subnet when the subnet pools are exhausted, which can have a
direct negative impact on the DHCP response time for each request.

The Free Lease Queue (FLQ) allocator tracks lease allocations and de-allocations
and maintains a running list of available addresses for each address pool.
It allows an available lease to be selected within a constant time, regardless of
the subnet pools' utilization. The allocator continuously updates the list of
free leases by removing any allocated leases and adding released or
reclaimed ones.

The following configuration snippet shows how to select the FLQ allocator
for a subnet:

.. code-block:: json

    {
        "Dhcp4": {
            "subnet4": [
                {
                    "id": 1,
                    "subnet": "192.0.2.0/24",
                    "allocator": "flq"
                }
            ]
        }
    }


There are several considerations that the administrator should take into account
before using this allocator. The FLQ allocator can heavily impact the server's
startup and reconfiguration time, because the allocator has to populate the
list of free leases for each subnet where it is used. These delays can be
observed both during the configuration reload and when the subnets are
created using :ischooklib:`libdhcp_subnet_cmds.so`. This allocator increases
memory consumption to hold the list of free leases, proportional
to the total size of the address pools for which the FLQ allocator is used.
Finally, lease reclamation must be enabled with a low value of the
``reclaim-timer-wait-time`` parameter, to ensure that the server frequently
collects expired leases and makes them available for allocation via the
free lease queue; expired leases are not considered free by
the allocator until they are reclaimed by the server. See
:ref:`lease-reclamation` for more details about the lease reclamation process.

We recommend that the FLQ allocator be selected
only after careful consideration. For example, using it for a subnet with a
``/8`` pool may delay the server's startup by 15 seconds or more. On the
other hand, the startup delay and the memory consumption increase should
be acceptable for subnets with a ``/16`` pool or smaller. We also recommend
specifying another allocator type in the global configuration settings
and overriding this selection at the subnet or shared-network level, to use
the FLQ allocator only for selected subnets. That way, when a new subnet is
added without an allocator specification, the global setting is used, thus
avoiding unnecessary impact on the server's startup time.

.. warning::

   The FLQ allocator is not suitable for use with a shared lease database
   (i.e., when multiple Kea servers store leases in the same database).
   The servers are unaware of the expired leases reclaimed by the
   sibling servers and never return them to their local free lease queues.
   As a result, the servers will not be able to offer some of the available
   leases to the clients. Only a server reclaiming a particular lease will
   be able to offer it.
