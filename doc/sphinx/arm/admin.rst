.. _admin:

***************************
Kea Database Administration
***************************

.. _kea-database-version:

Databases and Schema Versions
=============================

Kea may be configured to use a database as storage for leases or as a
source of servers' configurations and host reservations (i.e. static
assignments of addresses, prefixes, options, etc.). As Kea is
updated, new database schemas are introduced to facilitate new
features and correct discovered issues with the existing schemas.

Each version of Kea expects a particular schema structure and checks for this by
examining the version of the database it is using. Separate version numbers are
maintained for the schemas, independent of the version of Kea itself. It is
possible that the schema version will stay the same through several Kea
revisions; similarly, it is possible that the version of the schema may go up
several revisions during a single Kea version upgrade. Versions for each backend
type are also independent, so an increment in the MySQL backend version does not
imply an increment in that of PostgreSQL.

Schema versions are specified in a major.minor format. For the most recent
versions, the minor version is always zero and only the major version is
incremented.

Historically, the minor version used to be incremented when backward-compatible
changes were introduced to the schema: for example - when a new index is added.
This was opposed to incrementing the major version which implied an incompatible
schema change: for example - changing the type of an existing column. If Kea
attempts to run on a schema that is too old, as indicated by a mismatched schema
version, it will fail; administrative action is required to upgrade the schema.

.. _kea-admin:

The ``kea-admin`` Tool
======================

To manage the databases, Kea provides the ``kea-admin`` tool. It can
initialize a new backend, check its version number, perform a backend
upgrade, and dump lease data to a text file.

``kea-admin`` takes two mandatory parameters: ``command`` and
``backend``. Additional, non-mandatory options may be specified. The
currently supported commands are:

-  ``db-init`` — initializes a new database schema. This is useful
   during a new Kea installation. The database is initialized to the
   latest version supported by the version of the software being
   installed.

-  ``db-version`` — reports the database backend version number. This
   is not necessarily equal to the Kea version number, as each backend
   has its own versioning scheme.

-  ``db-upgrade`` — conducts a database schema upgrade. This is
   useful when upgrading Kea.

-  ``lease-dump`` — dumps the contents of the lease database (for MySQL or
   PostgreSQL backends) to a CSV (comma-separated values) text file.

   The first line of the file contains the column names. This can be used
   as a way to switch from a database backend to a memfile backend.
   Alternatively, it can be used as a diagnostic tool, so it provides a portable
   form of the lease data.

-  ``lease-upload`` — uploads leases from a CSV (comma-separated values) text
   file to a MySQL or a PostgreSQL lease database. The CSV file needs to be in
   memfile format.

``backend`` specifies the type of backend database. The currently
supported types are:

-  ``memfile`` — lease information is stored on disk in a text file.

-  ``mysql`` — information is stored in a MySQL relational database.

-  ``pgsql`` — information is stored in a PostgreSQL relational
   database.

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
backend is essential for the success of the deployment.

.. table:: List of available backends

   +---------------+----------------+----------------+---------------+
   | Feature       | Memfile        | MySQL          | PostgreSQL    |
   |               |                |                |               |
   +===============+================+================+===============+
   | Status        | Stable         | Stable         | Stable        |
   |               |                |                |               |
   +---------------+----------------+----------------+---------------+
   | Data format   | CSV file       | SQL RMDB       | SQL RMDB      |
   |               |                |                |               |
   |               |                |                |               |
   +---------------+----------------+----------------+---------------+
   | Leases        | yes            | yes            | yes           |
   +---------------+----------------+----------------+---------------+
   | Host          | no             | yes            | yes           |
   | reservations  |                |                |               |
   |               |                |                |               |
   +---------------+----------------+----------------+---------------+
   | Options       | no             | yes            | yes           |
   | defined on    |                |                |               |
   | per host      |                |                |               |
   | basis         |                |                |               |
   +---------------+----------------+----------------+---------------+
   | Configuration | no             | yes            | yes           |
   | backend       |                |                |               |
   |               |                |                |               |
   +---------------+----------------+----------------+---------------+

Memfile
-------

The memfile backend is able to store lease information, but cannot
store host reservation details; these must be stored in the
configuration file. (There are no plans to add a host reservations
storage capability to this backend.)

No special initialization steps are necessary for the memfile backend.
During the first run, both ``kea-dhcp4`` and ``kea-dhcp6`` create
an empty lease file if one is not present. Necessary disk-write
permission is required.

.. _memfile-upgrade:

Upgrading Memfile Lease Files From an Earlier Version of Kea
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are no special steps required to upgrade memfile lease files
between versions of Kea. During startup, the
servers check the schema version of the lease files against their
own. If there is a mismatch, the servers automatically launch the
LFC process to convert the files to the server's schema version. While
this mechanism is primarily meant to ease the process of upgrading to
newer versions of Kea, it can also be used for downgrading should the
need arise. When upgrading, any values not present in the original lease
files are assigned appropriate default values. When downgrading, any
data present in the files but not in the server's schema are
dropped. To convert the files manually prior to starting the
servers, run the lease file cleanup (LFC) process. See :ref:`kea-lfc` for more information.

.. _mysql-database:

MySQL
-----

MySQL is able to store leases, host reservations, options defined on a
per-host basis, and a subset of the server configuration parameters
(serving as a configuration backend).

.. _mysql-database-engine:

MySQL 5.7 vs MySQL 8 vs MariaDB 10 and 11
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In our Kea performance testing MySQL 8 shows 60-90% drop in speed
in comparison with older MySQL 5.7.
Due to the upcoming MySQL 5.7 EOL, we recommend using MariaDB instead of MySQL 8.

MySQL 5.7, MySQL 8, MariaDB 10, MariaDB 11 are fully compatible,
interchangeble and tested with Kea.

.. _mysql-database-create:

First-Time Creation of the MySQL Database
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Before preparing any Kea-specific database and tables, the MySQL database
must be configured to use the system timezone. It is recommended to use UTC
as the timezone for both the system and the MySQL database.

To check the system timezone:

   .. code-block:: console

      date +%Z

To check the MySQL timezone:

   .. code-block:: mysql

      mysql> SELECT @@system_time_zone;
      mysql> SELECT @@global.time_zone;
      mysql> SELECT @@session.time_zone;

To configure the MySQL timezone for a specific server, please refer to the
installed version documentation.

Usually the setting is configured in the [mysqld] section in ``/etc/mysql/my.cnf``,
``/etc/mysql/mysql.cnf``, ``/etc/mysql/mysqld.cnf``, or
``/etc/mysql/mysql.conf.d/mysqld.cnf``.

   .. code-block:: ini

      [mysqld]
      # using default-time-zone
      default-time-zone='+00:00'

      # or using timezone
      timezone='UTC'

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

   (``database_name`` is the name chosen for the database.)

3. Create the user under which Kea will access the database (and give it
   a password), then grant it access to the database tables:

   .. code-block:: mysql

      mysql> CREATE USER 'user-name'@'localhost' IDENTIFIED BY 'password';
      mysql> GRANT ALL ON database-name.* TO 'user-name'@'localhost';

   (``user-name`` and ``password`` are the user ID and password used to
   allow Kea access to the MySQL instance. All apostrophes in the
   command lines above are required.)

4. Create the database.

    Exit the MySQL client

    .. code-block:: mysql

      mysql> quit
      Bye

    Then use the  ``kea-admin`` tool to create the database.

    .. code-block:: console

        $ kea-admin db-init mysql -u database-user -p database-password -n database-name

    While it is possible to create the database from within the MySQL client, we recommend
    using the ``kea-admin`` tool as it performs some necessary validations to ensure Kea can
    access the database at runtime. Among those checks is verification that the schema does not contain
    any pre-existing tables; any pre-existing tables must be removed
    manually. An additional check examines the user's ability to create functions and
    triggers. The following error indicates that the user does not have the necessary
    permissions to create functions or triggers:

    .. code-block:: console

        ERROR 1419 (HY000) at line 1: You do not have the SUPER privilege and binary logging is
        enabled (you *might* want to use the less safe log_bin_trust_function_creators variable)
        ERROR/kea-admin: mysql_can_create cannot trigger, check user permissions, mysql status = 1
        mysql: [Warning] Using a password on the command line interface can be insecure.
        ERROR/kea-admin: Create failed, the user, keatest, has insufficient privileges.

    The simplest way around this is to set the global MySQL variable,
    ``log_bin_trust_function_creators``, to 1 via the MySQL client.
    Note this must be done as a user with SUPER privileges:

    .. code-block:: mysql

        mysql> set @@global.log_bin_trust_function_creators = 1;
        Query OK, 0 rows affected (0.00 sec)

    To create the database with MySQL directly, follow these steps:

    .. code-block:: mysql

      mysql> CONNECT database-name;
      mysql> SOURCE path-to-kea/share/kea/scripts/mysql/dhcpdb_create.mysql

   (where ``path-to-kea`` is the location where Kea is installed.)

    The database may also be dropped manually as follows:

    .. code-block:: mysql

      mysql> CONNECT database-name;
      mysql> SOURCE path-to-kea/share/kea/scripts/mysql/dhcpdb_drop.mysql

   (where ``path-to-kea`` is the location where Kea is installed.)

.. warning::

    Dropping the database results in the unrecoverable loss of any data it contains.


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
all data must be removed manually. (This process is a manual operation
on purpose, to avoid accidentally irretrievable mistakes by ``kea-admin``.)

.. _mysql-upgrade:

Upgrading a MySQL Database From an Earlier Version of Kea
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sometimes a new Kea version uses a newer database schema, so the
existing database needs to be upgraded. This can be done using the
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
earlier version.

To perform an upgrade, issue the following command:

.. code-block:: console

   $ kea-admin db-upgrade mysql -u database-user -p database-password -n database-name

.. note::

    To search host reservations by hostname, it is critical that the collation of
    the hostname column in the host table be case-insensitive. Fortunately, that
    is the default in MySQL, but it can be verified via this command:

    .. code-block:: mysql

      mysql> SELECT COLLATION('');
      +-----------------+
      | COLLATION('')   |
      +-----------------+
      | utf8_general_ci |
      +-----------------+

    According to mysql's naming convention, when the name ends in ``_ci``,
    the collation is case-insensitive.

.. _mysql-performance:

Improved Performance With MySQL
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Changing the MySQL internal value ``innodb_flush_log_at_trx_commit`` from the default value
of 1 to 2 can result in a huge gain in Kea performance. In some deployments, the
gain was over 1000% (10 times faster when set to 2, compared to the default value of 1).
It can be set per-session for testing:

.. code-block:: mysql

    mysql> SET GLOBAL innodb_flush_log_at_trx_commit=2;
    mysql> SHOW SESSION VARIABLES LIKE 'innodb_flush_log%';

or permanently in ``/etc/mysql/my.cnf``:

.. code-block:: ini

    [mysqld]
    innodb_flush_log_at_trx_commit=2

Be aware that changing this value can cause problems during data recovery
after a crash, so we recommend checking the `MySQL documentation
<https://dev.mysql.com/doc/refman/8.0/en/innodb-parameters.html#sysvar_innodb_flush_log_at_trx_commit>`__.
With the default value of 1, MySQL writes changes to disk after every INSERT or UPDATE query
(in Kea terms, every time a client gets a new lease or renews an existing lease). When
``innodb_flush_log_at_trx_commit`` is set to 2, MySQL writes the changes at intervals
no longer than 1 second. Batching writes gives a substantial performance boost. The trade-off,
however, is that in the worst-case scenario, all changes in the last second before crash
could be lost. Given the fact that Kea is stable software and crashes very rarely,
most deployments find it a beneficial trade-off.

.. _pgsql-database:

PostgreSQL
----------

PostgreSQL can store leases, host reservations, and options
defined on a per-host basis.

.. _pgsql-database-create:

First-Time Creation of the PostgreSQL Database
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Before preparing any Kea-specific database and tables, the PostgreSQL database
must be configured to use the system timezone. It is recommended to use UTC
as the timezone for both the system and the PostgreSQL database.

To check the system timezone:

   .. code-block:: console

      date +%Z

To check the PostgreSQL timezone:

   .. code-block:: psql

      postgres=# show timezone;
      postgres=# SELECT * FROM pg_timezone_names WHERE name = current_setting('TIMEZONE');

To configure the PostgreSQL timezone for a specific server, please refer to the
installed version documentation.

Usually the setting is configured in the ``postgresql.conf`` with the varying
version path ``/etc/postgresql/<version>/main/postgresql.conf``, but on some systems
the files may be located in ``/var/lib/pgsql/data``.

   .. code-block:: ini

      timezone = 'UTC'

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

   (``database-name`` is the name chosen for the database.)

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
   following command. PostgreSQL will prompt the administrator to enter the
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

   (``path-to-kea`` is the location where Kea is installed.)

   If instead an error is encountered, such as:

   ::

      psql: FATAL:  no pg_hba.conf entry for host "[local]", user "user-name", database "database-name", SSL off

   ... the PostgreSQL configuration will need to be altered. Kea uses
   password authentication when connecting to the database and must have
   the appropriate entries added to PostgreSQL's pg_hba.conf file. This
   file is normally located in the primary data directory for the
   PostgreSQL server. The precise path may vary depending on the
   operating system and version, but the default location for PostgreSQL is
   ``/etc/postgresql/*/main/postgresql.conf``. However, on some systems
   (notably CentOS 8), the file may reside in ``/var/lib/pgsql/data``.

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
   may be necessary to restart PostgreSQL for the changes to
   take effect.

Initialize the PostgreSQL Database Using ``kea-admin``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If the tables were not created manually, do so now by
running the ``kea-admin`` tool:

.. code-block:: console

   $ kea-admin db-init pgsql -u database-user -p database-password -n database-name

Do not do this if the tables were already created manually. ``kea-admin``
implements rudimentary checks; it will refuse to initialize a database
that contains any existing tables. To start from scratch,
all data must be removed manually. (This process is a manual operation
on purpose, to avoid accidentally irretrievable mistakes by ``kea-admin``.)

.. _pgsql-upgrade:

Upgrading a PostgreSQL Database From an Earlier Version of Kea
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

.. _pgsl-ssl:

PostgreSQL without OpenSSL support
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Usually the PostgreSQL database client library is built with the OpenSSL
support but Kea can be configured to handle the case where it is not
supported:

.. code-block:: console

   $ ./configure [other-options] --disable-pgsql-ssl

.. _pgsql-performance:

Improved Performance With PostgreSQL
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Changing the PostgreSQL internal value ``synchronous_commit`` from the default value
of ON to OFF can result in gain in Kea performance. On slow systems, the gain can be over 1000%.
It can be set per-session for testing:

.. code-block:: psql

    postgres=# SET synchronous_commit = OFF;

or permanently by command (preferred method):

.. code-block:: psql

    postgres=# ALTER SYSTEM SET synchronous_commit=OFF;

or permanently in ``/etc/postgresql/[version]/main/postgresql.conf``:

.. code-block:: ini

    synchronous_commit = off

Be aware that changing this value can cause problems during data recovery
after a crash, so we recommend checking the `PostgreSQL documentation
<https://www.postgresql.org/docs/current/wal-async-commit.html>`__.
With the default value of ON, PostgreSQL writes changes to disk after every INSERT or UPDATE query
(in Kea terms, every time a client gets a new lease or renews an existing lease). When
``synchronous_commit`` is set to OFF, PostgreSQL writes the changes with some delay.
Batching writes gives a substantial performance boost. The trade-off,
however, is that in the worst-case scenario, all changes in the last moment before crash
could be lost. Given the fact that Kea is stable software and crashes very rarely,
most deployments find it a beneficial trade-off.

Using Read-Only Databases With Host Reservations
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

The lease expiration time in Kea is stored in the SQL database for each lease
as a timestamp value. Kea developers have observed that the MySQL database
does not accept timestamps beyond 2147483647 seconds (the maximum signed
32-bit number) from the beginning of the UNIX epoch (00:00:00 on 1
January 1970). Some versions of PostgreSQL do accept greater values, but
the value is altered when it is read back. For this reason, the lease
database backends put a restriction on the maximum timestamp to be
stored in the database, which is equal to the maximum signed 32-bit
number. This effectively means that the current Kea version cannot store
leases whose expiration time is later than 2147483647 seconds since the
beginning of the epoch (around the year 2038). This will be fixed when
database support for longer timestamps is available.
