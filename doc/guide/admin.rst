.. _admin:

***************************
Kea Database Administration
***************************

.. _kea-database-version:

Databases and Database Version Numbers
======================================

Kea may be configured to use a database as a storage for leases or as a
source of servers' configurations and host reservations (i.e. static
assignments of addresses, prefixes, options, etc.). Kea
updates introduce changes to the database schemas to faciliate new
features and correct discovered issues with the existing schemas.

A given version of Kea expects a particular structure in the backend and
checks for this by examining the version of the database it is using.
Separate version numbers are maintained for backends, independent of the
version of Kea itself. It is possible that the backend version will stay
the same through several Kea revisions; similarly, it is possible that
the version of the backend may go up several revisions during a Kea
upgrade. Versions for each backend are independent, so an increment in
the MySQL backend version does not imply an increment in that of
PostgreSQL.

Backend versions are specified in a major.minor format. The minor number
is increased when there are backwards-compatible changes introduced; for
example, the addition of a new index. It is desirable but not mandatory
to apply such a change; you can run an older backend version if you want
to. (Although, in the example given, running without the new index may
introduce a performance penalty.) On the other hand, the
major number is increased when an incompatible change is introduced; for
example, an extra column is added to a table. If you try to run Kea on a
backend that is too old (as signified by a mismatched backend major
version number), Kea will refuse to run; administrative action will be
required to upgrade the backend.

.. _kea-admin:

The kea-admin Tool
==================

To manage the databases, Kea provides the ``kea-admin`` tool. It is able
to initialize a new backend, check its version number, perform a backend
upgrade, and dump lease data to a text file.

``kea-admin`` takes two mandatory parameters: ``command`` and
``backend``. Additional, non-mandatory options may be specified. The
currently supported commands are:

-  ``lease-init`` — Initializes a new database schema. This is useful
   during a new Kea installation. The database is initialized to the
   latest version supported by the version of the software being
   installed.

-  ``lease-version`` — Reports the database backend version number. This
   is not necessarily equal to the Kea version number as each backend
   has its own versioning scheme.

-  ``lease-upgrade`` — Conducts a database schema upgrade. This is
   useful when upgrading Kea.

-  ``lease-dump`` — Dumps the contents of the lease database (for MySQL,
   PostgreSQL, or CQL backends) to a CSV (comma-separated values) text
   file. The first line of the file contains the column names. This is
   meant to be used as a diagnostic tool, so it provides a portable,
   human-readable form of the lease data.

``backend`` specifies the type of backend database. The currently
supported types are:

-  ``memfile`` — Lease information is stored on disk in a text file.

-  ``mysql`` — Information is stored in a MySQL relational database.

-  ``pgsql`` — Information is stored in a PostgreSQL relational
   database.

-  ``cql`` — Information is stored in an Apache Cassandra database.

Additional parameters may be needed, depending on your setup and
specific operation: username, password, and database name or the
directory where specific files are located. See the appropriate manual
page for details (``man 8 kea-admin``).

.. _supported-databases:

Supported Backends
==================

The following table presents the capabilities of available backends.
Please refer to the specific sections dedicated to each backend to
better understand their capabilities and limitations. Choosing the right
backend may be essential for the success of your deployment.

.. table:: List of available backends

   +---------------+----------------+----------------+---------------+--------------+
   | Feature       | Memfile        | MySQL          | PostgreSQL    | CQL          |
   |               |                |                |               | (Cassandra)  |
   +===============+================+================+===============+==============+
   | Status        | Stable         | Stable         | Stable        | Experimental |
   |               |                |                |               |              |
   +---------------+----------------+----------------+---------------+--------------+
   | Data format   | CSV file       | SQL RMDB       | SQL RMDB      | NoSQL        |
   |               |                |                |               | database     |
   |               |                |                |               | (Cassandra)  |
   +---------------+----------------+----------------+---------------+--------------+
   | Leases        | yes            | yes            | yes           | yes          |
   +---------------+----------------+----------------+---------------+--------------+
   | Host          | no             | yes            | yes           | yes          |
   | Reservations  |                |                |               |              |
   |               |                |                |               |              |
   +---------------+----------------+----------------+---------------+--------------+
   | Options       | no             | yes            | yes           | yes          |
   | defined on    |                |                |               |              |
   | per host      |                |                |               |              |
   | basis         |                |                |               |              |
   +---------------+----------------+----------------+---------------+--------------+
   | Configuration | no             | yes            | no            | no           |
   | Backend       |                |                |               |              |
   |               |                |                |               |              |
   +---------------+----------------+----------------+---------------+--------------+

memfile
-------

The memfile backend is able to store lease information, but cannot
store host reservation details; these must be stored in the
configuration file. (There are no plans to add a host reservations
storage capability to this backend.)

No special initialization steps are necessary for the memfile backend.
During the first run, both ``kea-dhcp4`` and ``kea-dhcp6`` will create
an empty lease file if one is not present. Necessary disk-write
permission is required.

.. _memfile-upgrade:

Upgrading Memfile Lease Files from an Earlier Version of Kea
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are no special steps required to upgrade memfile lease files from
an earlier version of Kea to a new version of Kea. During startup the
servers will check the schema version of the lease files against their
own. If there is a mismatch, the servers will automatically launch the
LFC process to convert the files to the server's schema version. While
this mechanism is primarily meant to ease the process of upgrading to
newer versions of Kea, it can also be used for downgrading should the
need arise. When upgrading, any values not present in the original lease
files will be assigned appropriate default values. When downgrading, any
data present in the files but not in the server's schema will be
dropped. If you wish to convert the files manually prior to starting the
servers, you may do so by running the LFC process yourself. See
:ref:`kea-lfc` for more information.

.. _mysql-database:

MySQL
-----

MySQL is able to store leases, host reservations, options defined on a
per-host basis, and a subset of the server configuration parameters
(serving as a configuration backend). This section can be safely ignored
if you choose to store the data in other backends.

.. _mysql-database-create:

First-Time Creation of the MySQL Database
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you are setting the MySQL database for the first time, you need to
create the database area within MySQL and set up the MySQL user ID under
which Kea will access the database. This needs to be done manually;
``kea-admin`` cannot do this for you.

To create the database:

1. Log into MySQL as "root":

   ::

      $ mysql -u root -p
      Enter password:
      mysql>

2. Create the MySQL database:

   ::

      mysql> CREATE DATABASE database-name;

   (database-name is the name you have chosen for the database.)

3. Create the user under which Kea will access the database (and give it
   a password), then grant it access to the database tables:

   ::

      mysql> CREATE USER 'user-name'@'localhost' IDENTIFIED BY 'password';
      mysql> GRANT ALL ON database-name.* TO 'user-name'@'localhost';

   (user-name and password are the user ID and password you are using to
   allow Kea access to the MySQL instance. All apostrophes in the
   command lines above are required.)

4. At this point, you may elect to create the database tables.
   (Alternatively, you can exit MySQL and create the tables using the
   ``kea-admin`` tool, as explained below.) To do this:

   ::

      mysql> CONNECT database-name;
      mysql> SOURCE path-to-kea/share/kea/scripts/mysql/dhcpdb_create.mysql

   (path-to-kea is the location where you installed Kea.)

5. Exit MySQL:

   ::

      mysql> quit
      Bye
      $

If you elected not to create the tables in Step 4, you can do so now by
running the ``kea-admin`` tool:

::

   $ kea-admin lease-init mysql -u database-user -p database-password -n database-name

Do not do this if you did create the tables in Step 4. ``kea-admin``
implements rudimentary checks; it will refuse to initialize a database
that contains any existing tables. If you want to start from scratch,
you must remove all data manually. (This process is a manual operation
on purpose, to avoid possibly irretrievable mistakes by ``kea-admin``.)

.. _mysql-upgrade:

Upgrading a MySQL Database from an Earlier Version of Kea
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sometimes a new Kea version may use a newer database schema, so the
existing database will need to be upgraded. This can be done using the
``kea-admin lease-upgrade`` command.

To check the current version of the database, use the following command:

::

   $ kea-admin lease-version mysql -u database-user -p database-password -n database-name

(See :ref:`kea-database-version`
for a discussion about versioning.) If the version does not match the
minimum required for the new version of Kea (as described in the release
notes), the database needs to be upgraded.

Before upgrading, please make sure that the database is backed up. The
upgrade process does not discard any data, but depending on the nature
of the changes, it may be impossible to subsequently downgrade to an
earlier version. To perform an upgrade, issue the following command:

::

   $ kea-admin lease-upgrade mysql -u database-user -p database-password -n database-name

.. _pgsql-database:

PostgreSQL
----------

PostgreSQL is able to store leases, host reservations, and options
defined on a per-host basis. This step can be safely ignored if you are
using other database backends.

.. _pgsql-database-create:

First-Time Creation of the PostgreSQL Database
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The first task is to create both the lease database and the user under
which the servers will access it. A number of steps are required:

1. Log into PostgreSQL as "root":

   ::

      $ sudo -u postgres psql postgres
      Enter password:
      postgres=#

2. Create the database:

   ::

      postgres=# CREATE DATABASE database-name;
      CREATE DATABASE
      postgres=#

   (database-name is the name you have chosen for the database.)

3. Create the user under which Kea will access the database (and give it
   a password), then grant it access to the database:

   ::

      postgres=# CREATE USER user-name WITH PASSWORD 'password';
      CREATE ROLE
      postgres=# GRANT ALL PRIVILEGES ON DATABASE database-name TO user-name;
      GRANT
      postgres=#

4. Exit PostgreSQL:

   ::

      postgres=# \q
      Bye
      $

5. At this point you are ready to create the database tables. This can
   be done using the ``kea-admin`` tool as explained in the next section
   (recommended), or manually. To create the tables manually, enter the
   following command. Note that PostgreSQL will prompt you to enter the
   new user's password you specified in Step 3. When the command
   completes, you will be returned to the shell prompt. You should see
   output similar to the following:

   ::

      $ psql -d database-name -U user-name -f path-to-kea/share/kea/scripts/pgsql/dhcpdb_create.pgsql
      Password for user user-name:
      CREATE TABLE
      CREATE INDEX
      CREATE INDEX
      CREATE TABLE
      CREATE INDEX
      CREATE TABLE
      START TRANSACTION
      INSERT 0 1
      INSERT 0 1
      INSERT 0 1
      COMMIT
      CREATE TABLE
      START TRANSACTION
      INSERT 0 1
      COMMIT
      $

   (path-to-kea is the location where you installed Kea.)

   If instead you encounter an error like:

   ::

      psql: FATAL:  no pg_hba.conf entry for host "[local]", user "user-name", database "database-name", SSL off

   ... you will need to alter the PostgreSQL configuration. Kea uses
   password authentication when connecting to the database and must have
   the appropriate entries added to PostgreSQL's pg_hba.conf file. This
   file is normally located in the primary data directory for your
   PostgreSQL server. The precise path may vary depending on your
   operating system and version, but the default location for PostgreSQL
   9.3 on Centos 6.5 is: ``/var/lib/pgsql/9.3/data/pg_hba.conf``.

   Assuming Kea is running on the same host as PostgreSQL, adding lines
   similar to the following should be sufficient to provide
   password-authenticated access to Kea's database:

   ::

      local   database-name    user-name                                 password
      host    database-name    user-name          127.0.0.1/32           password
      host    database-name    user-name          ::1/128                password

   These edits are primarily intended as a starting point, and are not a
   definitive reference on PostgreSQL administration or database
   security. Please consult your PostgreSQL user manual before making
   these changes, as they may expose other databases that you run. It
   may be necessary to restart PostgreSQL in order for the changes to
   take effect.

Initialize the PostgreSQL Database Using kea-admin
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you elected not to create the tables manually, you can do so now by
running the ``kea-admin`` tool:

::

   $ kea-admin lease-init pgsql -u database-user -p database-password -n database-name

Do not do this if you already created the tables manually. ``kea-admin``
implements rudimentary checks; it will refuse to initialize a database
that contains any existing tables. If you want to start from scratch,
you must remove all data manually. (This process is a manual operation
on purpose, to avoid possibly irretrievable mistakes by ``kea-admin``.)

.. _pgsql-upgrade:

Upgrading a PostgreSQL Database from an Earlier Version of Kea
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The PostgreSQL database schema can be upgraded using the same tool and
commands as described in :ref:`mysql-upgrade`, with the exception that the "pgsql"
database backend type must be used in the commands.

Use the following command to check the current schema version:

::

   $ kea-admin lease-version pgsql -u database-user -p database-password -n database-name

Use the following command to perform an upgrade:

::

   $ kea-admin lease-upgrade pgsql -u database-user -p database-password -n database-name

.. _cql-database:

Cassandra
---------

Cassandra (sometimes for historical reasons referred to in documentation
and commands as CQL) is the newest backend added to Kea; initial
development was contributed by Deutsche Telekom. The Cassandra backend
is able to store leases, host reservations, and options defined on a
per-host basis.

Cassandra must be properly set up if you want Kea to store information
in it. This section can be safely ignored if you choose to store the
data in other backends.

.. _cql-database-create:

First-Time Creation of the Cassandra Database
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you are setting up the Cassandra database for the first time, you
need to create the keyspace area within it. This needs to be done
manually; ``kea-admin`` cannot do this for you.

To create the database:

1. Export CQLSH_HOST environment variable:

   ::

      $ export CQLSH_HOST=localhost

2. Log into CQL:

   ::

      $ cqlsh
      cql>

3. Create the CQL keyspace:

   ::

      cql> CREATE KEYSPACE keyspace-name WITH replication = {'class' : 'SimpleStrategy','replication_factor' : 1};

   (keyspace-name is the name you have chosen for the keyspace)

4. At this point, you may elect to create the database tables.
   (Alternatively, you can exit Cassandra and create the tables using
   the ``kea-admin`` tool, as explained below.) To do this:

   ::

      cqslh -k keyspace-name -f path-to-kea/share/kea/scripts/cql/dhcpdb_create.cql

   (path-to-kea is the location where you installed Kea)

If you elected not to create the tables in Step 4, you can do so now by
running the ``kea-admin`` tool:

::

   $ kea-admin lease-init cql -n database-name

Do not do this if you did create the tables in Step 4. ``kea-admin``
implements rudimentary checks; it will refuse to initialize a database
that contains any existing tables. If you want to start from scratch,
you must remove all data manually. (This process is a manual operation
on purpose, to avoid possibly irretrievable mistakes by ``kea-admin``.)

.. _cql-upgrade:

Upgrading a Cassandra Database from an Earlier Version of Kea
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sometimes a new Kea version may use a newer database schema, so the
existing database will need to be upgraded. This can be done using the
``kea-admin lease-upgrade`` command.

To check the current version of the database, use the following command:

::

   $ kea-admin lease-version cql -n database-name

(See :ref:`kea-database-version`
for a discussion about versioning.) If the version does not match the
minimum required for the new version of Kea (as described in the release
notes), the database needs to be upgraded.

Before upgrading, please make sure that the database is backed up. The
upgrade process does not discard any data, but depending on the nature
of the changes, it may be impossible to subsequently downgrade to an
earlier version. To perform an upgrade, issue the following command:

::

   $ kea-admin lease-upgrade cql -n database-name

Using Read-Only Databases with Host Reservations
------------------------------------------------

If a read-only database is used for storing host reservations, Kea must
be explicitly configured to operate on the database in read-only mode.
Sections :ref:`read-only-database-configuration4` and
:ref:`read-only-database-configuration6` describe when such
a configuration may be required, and how to configure Kea to operate in
this way for both DHCPv4 and DHCPv6.

Limitations Related to the Use of SQL Databases
-----------------------------------------------

Year 2038 Issue
~~~~~~~~~~~~~~~

The lease expiration time is stored in the SQL database for each lease
as a timestamp value. Kea developers observed that the MySQL database
doesn't accept timestamps beyond 2147483647 seconds (the maximum signed
32-bit number) from the beginning of the Unix epoch (00:00:00 on 1
January 1970). Some versions of PostgreSQL do accept greater values, but
the value is altered when it is read back. For this reason, the lease
database backends put a restriction on the maximum timestamp to be
stored in the database, which is equal to the maximum signed 32-bit
number. This effectively means that the current Kea version cannot store
leases whose expiration time is later than 2147483647 seconds since the
beginning of the epoch (around year 2038). This will be fixed when the
database support for longer timestamps is available.
