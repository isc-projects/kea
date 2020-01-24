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
to apply such a change; running an older backend version is possible.
(Although, in the example given, running without the new index may
introduce a performance penalty.) On the other hand, the
major number is increased when an incompatible change is introduced; for
example, an extra column is added to a table. If Kea is run on a
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

-  ``db-init`` — Initializes a new database schema. This is useful
   during a new Kea installation. The database is initialized to the
   latest version supported by the version of the software being
   installed.

-  ``db-version`` — Reports the database backend version number. This
   is not necessarily equal to the Kea version number as each backend
   has its own versioning scheme.

-  ``db-upgrade`` — Conducts a database schema upgrade. This is
   useful when upgrading Kea.

-  ``lease-dump`` — Dumps the contents of the lease database (for MySQL,
   PostgreSQL, or CQL backends) to a CSV (comma-separated values) text
   file. The first line of the file contains the column names. This is
   meant to be used as a diagnostic tool, so it provides a portable,
   human-readable form of the lease data.

.. note::

  In previous versions of Kea earlier than 1.6.0 `db-init`, `db-version` and
  `db-upgrade` commands were named `lease-init`, `lease-version` and
  `lease-upgrade`.

``backend`` specifies the type of backend database. The currently
supported types are:

-  ``memfile`` — Lease information is stored on disk in a text file.

-  ``mysql`` — Information is stored in a MySQL relational database.

-  ``pgsql`` — Information is stored in a PostgreSQL relational
   database.

-  ``cql`` — Information is stored in an Apache Cassandra database.

Additional parameters may be needed, depending on the setup and
specific operation: username, password, and database name or the
directory where specific files are located. See the appropriate manual
page for details (``man 8 kea-admin``).

.. _supported-databases:

Supported Backends
==================

The following table presents the capabilities of available backends.
Please refer to the specific sections dedicated to each backend to
better understand their capabilities and limitations. Choosing the right
backend may be essential for the success of the deployment.

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

Memfile
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
dropped. To convert the files manually prior to starting the
servers, run the LFC process. See :ref:`kea-lfc` for more information.

.. _mysql-database:

MySQL
-----

MySQL is able to store leases, host reservations, options defined on a
per-host basis, and a subset of the server configuration parameters
(serving as a configuration backend). This section can be safely ignored
if the data will be stored in other backends.

.. _mysql-database-create:

First-Time Creation of the MySQL Database
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When setting up the MySQL database for the first time, the
database area must be created within MySQL, and the MySQL user ID under
which Kea will access the database must be set up. This needs to be done manually,
rather than via ``kea-admin``.

To create the database:

1. Log into MySQL as "root":

   .. code-block:: console

      $ mysql -u root -p
      Enter password:
      mysql>

2. Create the MySQL database:

   .. code-block:: mysql

      mysql> CREATE DATABASE database_name;

   (database_name is the name chosen for the database.)

3. Create the user under which Kea will access the database (and give it
   a password), then grant it access to the database tables:

   .. code-block:: mysql

      mysql> CREATE USER 'user-name'@'localhost' IDENTIFIED BY 'password';
      mysql> GRANT ALL ON database-name.* TO 'user-name'@'localhost';

   (user-name and password are the user ID and password being used to
   allow Kea access to the MySQL instance. All apostrophes in the
   command lines above are required.)

4. Create the database.

    You'll need to exit mysql client

    .. code-block:: mysql

      mysql> quit
      Bye

    and then use the  ``kea-admin`` tool to create the database.

    .. code-block:: console

        $ kea-admin db-init mysql -u database-user -p database-password -n database-name

    While it is possible to create the database from within mysql client, we recommend you
    use the kea-admin tool as it performs some necessary validations to ensure Kea can
    access the database at runtime.  Among those checks is that the schema does not contain
    any pre-existing tables.  If there are any pre-existing tables they must be removed
    manaully.  An additional check examines the user's ability to create functions and
    triggers.  If you encounter the following error:

    .. code-block:: console

        ERROR 1419 (HY000) at line 1: You do not have the SUPER privilege and binary logging is
        enabled (you *might* want to use the less safe log_bin_trust_function_creators variable)
        ERROR/kea-admin: mysql_can_create cannot trigger, check user permissions, mysql status = 1
        mysql: [Warning] Using a password on the command line interface can be insecure.
        ERROR/kea-admin: Create failed, the user, keatest, has insufficient privileges.

    Then user does not have the necessary permissions to create functions or triggers.
    The simplest way around this is to set the global MySQL variable, log_bin_trust_function_creators to 1
    via mysql client. Note you must do this as a user with SUPER privileges:

    .. code-block:: mysql

        mysql> set @@global.log_bin_trust_function_creators = 1;
        Query OK, 0 rows affected (0.00 sec)

    If you choose to create the database with mysql directly, you may do as as follows:

    .. code-block:: mysql

      mysql> CONNECT database-name;
      mysql> SOURCE path-to-kea/share/kea/scripts/mysql/dhcpdb_create.mysql

   (path-to-kea is the location where Kea is installed.)

    The database may also be dropped manually as follows:

    .. code-block:: mysql

      mysql> CONNECT database-name;
      mysql> SOURCE path-to-kea/share/kea/scripts/mysql/dhcpdb_drop.mysql

   (path-to-kea is the location where Kea is installed.)

.. warning::
    Dropping the database will result in the unrecoverable loss of any data it contains.


5. Exit MySQL:

   .. code-block:: mysql

      mysql> quit
      Bye

If the tables were not created in Step 4, run the ``kea-admin`` tool
to create them now:

.. code-block:: console

   $ kea-admin db-init mysql -u database-user -p database-password -n database-name

Do not do this if the tables were created in Step 4. ``kea-admin``
implements rudimentary checks; it will refuse to initialize a database
that contains any existing tables. To start from scratch,
all must be removed data manually. (This process is a manual operation
on purpose, to avoid possibly irretrievable mistakes by ``kea-admin``.)

.. _mysql-upgrade:

Upgrading a MySQL Database from an Earlier Version of Kea
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sometimes a new Kea version may use a newer database schema, so the
existing database will need to be upgraded. This can be done using the
``kea-admin db-upgrade`` command.

To check the current version of the database, use the following command:

.. code-block:: console

   $ kea-admin db-version mysql -u database-user -p database-password -n database-name

(See :ref:`kea-database-version`
for a discussion about versioning.) If the version does not match the
minimum required for the new version of Kea (as described in the release
notes), the database needs to be upgraded.

Before upgrading, please make sure that the database is backed up. The
upgrade process does not discard any data, but depending on the nature
of the changes, it may be impossible to subsequently downgrade to an
earlier version. To perform an upgrade, issue the following command:

.. code-block:: console

   $ kea-admin db-upgrade mysql -u database-user -p database-password -n database-name

.. note::

    To search host reservations by hostname it is critical the collation of
    the hostname column in the host table to be case-insensitive. Fortunately
    the default collation in MySQL is case-insensitive. You can verify this
    on your MySQL installation by:

    .. code-block:: mysql

      mysql> SELECT COLLATION('');
      +-----------------+
      | COLLATION('')   |
      +-----------------+
      | utf8_general_ci |
      +-----------------+

    According to the naming of collations when the name finishes by ``_ci``
    the collation is case-insensitive.

.. _mysql-performance:

Simple MySQL tweak to gain performance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Changing MySQL internal value ``innodb_flush_log_at_trx_commit`` from default value
``1`` to ``2`` can result with huge gain in Kea performance. It can be set per session for testing:

.. code-block:: mysql

    mysql> SET GLOBAL innodb_flush_log_at_trx_commit=2;
    mysql> SHOW SESSION VARIABLES LIKE 'innodb_flush_log%';

or permanently in ``/etc/mysql/my.cnf``:

.. code-block:: mysql

    [mysqld]
    innodb_flush_log_at_trx_commit=2

Be aware that changing this value can result with problems during data recovery
after crash, we strongly recommend to check `MySQL documentation <https://dev.mysql.com/doc/refman/8.0/en/innodb-parameters.html#sysvar_innodb_flush_log_at_trx_commit>`__.

.. _pgsql-database:

PostgreSQL
----------

PostgreSQL is able to store leases, host reservations, and options
defined on a per-host basis. This step can be safely ignored if
other database backends will be used.

.. _pgsql-database-create:

First-Time Creation of the PostgreSQL Database
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The first task is to create both the database and the user under
which the servers will access it. A number of steps are required:

1. Log into PostgreSQL as "root":

   .. code-block:: console

      $ sudo -u postgres psql postgres
      Enter password:
      postgres=#

2. Create the database:

   .. code-block:: psql

      postgres=# CREATE DATABASE database-name;
      CREATE DATABASE
      postgres=#

   (database-name is the name chosen for the database.)

3. Create the user under which Kea will access the database (and give it
   a password), then grant it access to the database:

   .. code-block:: psql

      postgres=# CREATE USER user-name WITH PASSWORD 'password';
      CREATE ROLE
      postgres=# GRANT ALL PRIVILEGES ON DATABASE database-name TO user-name;
      GRANT
      postgres=#

4. Exit PostgreSQL:

   .. code-block:: psql

      postgres=# \q
      Bye
      $

5. At this point, create the database tables either
   using the ``kea-admin`` tool, as explained in the next section
   (recommended), or manually. To create the tables manually, enter the
   following command. Note that PostgreSQL will prompt the administrator to enter the
   new user's password that was specified in Step 3. When the command
   completes, Kea will return to the shell prompt. The
   output should be similar to the following:

   .. code-block:: console

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

   (path-to-kea is the location where Kea is installed.)

   If instead an error is encountered, such as:

   ::

      psql: FATAL:  no pg_hba.conf entry for host "[local]", user "user-name", database "database-name", SSL off

   ... the PostgreSQL configuration will need to be altered. Kea uses
   password authentication when connecting to the database and must have
   the appropriate entries added to PostgreSQL's pg_hba.conf file. This
   file is normally located in the primary data directory for the
   PostgreSQL server. The precise path may vary depending on the
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
   security. Please consult the PostgreSQL user manual before making
   these changes, as they may expose other databases that are running. It
   may be necessary to restart PostgreSQL in order for the changes to
   take effect.

Initialize the PostgreSQL Database Using kea-admin
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If the tables were not created manually, do so now by
running the ``kea-admin`` tool:

.. code-block:: console

   $ kea-admin db-init pgsql -u database-user -p database-password -n database-name

Do not do this if the tables were already created manually. ``kea-admin``
implements rudimentary checks; it will refuse to initialize a database
that contains any existing tables. To start from scratch,
all data must be removed manually. (This process is a manual operation
on purpose, to avoid possibly irretrievable mistakes by ``kea-admin``.)

.. _pgsql-upgrade:

Upgrading a PostgreSQL Database from an Earlier Version of Kea
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The PostgreSQL database schema can be upgraded using the same tool and
commands as described in :ref:`mysql-upgrade`, with the exception that the "pgsql"
database backend type must be used in the commands.

Use the following command to check the current schema version:

.. code-block:: console

   $ kea-admin db-version pgsql -u database-user -p database-password -n database-name

Use the following command to perform an upgrade:

.. code-block:: console

   $ kea-admin db-upgrade pgsql -u database-user -p database-password -n database-name

.. _cql-database:

Cassandra
---------

Cassandra (sometimes for historical reasons referred to in documentation
and commands as CQL) is the newest backend added to Kea; initial
development was contributed by Deutsche Telekom. The Cassandra backend
is able to store leases, host reservations, and options defined on a
per-host basis.

Cassandra must be properly set up if Kea is to store information
in it. This section can be safely ignored if the
data will be stored in other backends.

.. _cql-database-create:

First-Time Creation of the Cassandra Database
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When setting up the Cassandra database for the first time,
the keyspace area within it must be created. This needs to be done
manually; it cannot be performed by ``kea-admin``.

To create the database:

1. Export CQLSH_HOST environment variable:

   .. code-block:: console

      $ export CQLSH_HOST=localhost

2. Log into CQL:

   .. code-block:: console

      $ cqlsh
      cql>

3. Create the CQL keyspace:

   ::

      cql> CREATE KEYSPACE keyspace-name WITH replication = {'class' : 'SimpleStrategy','replication_factor' : 1};

   (keyspace-name is the name chosen for the keyspace.)

4. At this point, the database tables can be created.
   (It is also possible to exit Cassandra and create the tables using
   the ``kea-admin`` tool, as explained below.) To do this:

   ::

      cqslh -k keyspace-name -f path-to-kea/share/kea/scripts/cql/dhcpdb_create.cql

   (path-to-kea is the location where Kea is installed.)

If the tables were not created in Step 4, do so now by
running the ``kea-admin`` tool:

.. code-block:: console

   $ kea-admin db-init cql -n database-name

Do not do this if the tables were created in Step 4. ``kea-admin``
implements rudimentary checks; it will refuse to initialize a database
that contains any existing tables. To start from scratch,
all data must be removed manually. (This process is a manual operation
on purpose, to avoid possibly irretrievable mistakes by ``kea-admin``.)

.. _cql-upgrade:

Upgrading a Cassandra Database from an Earlier Version of Kea
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sometimes a new Kea version may use a newer database schema, so the
existing database will need to be upgraded. This can be done using the
``kea-admin db-upgrade`` command.

To check the current version of the database, use the following command:

.. code-block:: console

   $ kea-admin db-version cql -n database-name

(See :ref:`kea-database-version`
for a discussion about versioning.) If the version does not match the
minimum required for the new version of Kea (as described in the release
notes), the database needs to be upgraded.

Before upgrading, please make sure that the database is backed up. The
upgrade process does not discard any data, but depending on the nature
of the changes, it may be impossible to subsequently downgrade to an
earlier version. To perform an upgrade, issue the following command:

.. code-block:: console

   $ kea-admin db-upgrade cql -n database-name

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
32-bit number) from the beginning of the UNIX epoch (00:00:00 on 1
January 1970). Some versions of PostgreSQL do accept greater values, but
the value is altered when it is read back. For this reason, the lease
database backends put a restriction on the maximum timestamp to be
stored in the database, which is equal to the maximum signed 32-bit
number. This effectively means that the current Kea version cannot store
leases whose expiration time is later than 2147483647 seconds since the
beginning of the epoch (around year 2038). This will be fixed when the
database support for longer timestamps is available.
