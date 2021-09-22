.. _installation:

************
Installation
************

Packages
========

ISC publishes native RPM, deb, and APK packages, along with the tarballs
with the source code. The packages are available on
`Cloudsmith <https://cloudsmith.io/~isc/repos/>`_ at
https://cloudsmith.io/~isc/repos. The native packages can be downloaded
and installed using the system available in a specific distribution (such
as dpkg or rpm). The Kea repository can also be added to the system,
making it easier to install updates. For details, please
go to https://cloudsmith.io/~isc/repos, choose the repository of
interest, and then click the ``Set Me Up`` button for detailed
instructions.

.. _install-hierarchy:

Installation Hierarchy
======================

The following is the directory layout of the complete Kea installation.
(All directory paths are relative to the installation directory.)

-  ``etc/kea/`` — configuration files.

-  ``include/`` — C++ development header files.

-  ``lib/`` — libraries.

-  ``lib/kea/hooks`` — additional hooks libraries.

-  ``sbin/`` — server software and commands used by the system administrator.

-  ``share/doc/kea/`` — this guide, other supplementary documentation, and examples.

-  ``share/kea/`` — API command examples and database schema scripts.

-  ``share/man/`` — manual pages (online documentation).

-  ``var/lib/kea/`` — server identification and lease database files.

-  ``var/log/`` - log files.

-  ``var/run/kea`` - PID file and logger lock file.

.. _build-requirements:

Build Requirements
==================

In addition to the run-time requirements (listed in
:ref:`required-software`), building Kea from source code requires
various development include headers and program development tools.

.. note::

   Some operating systems have split their distribution packages into a
   run-time and a development package. The
   development package versions, which include header files and
   libraries, must be installed to build Kea from the source code.

Building from source code requires the following software installed on
the system:

-  Boost C++ libraries (https://www.boost.org/). The oldest Boost version
   used for testing is 1.57 (although Kea may also work with older
   versions). The Boost system library must also be installed.
   Installing a header-only version of Boost is not recommended.

-  OpenSSL (at least version 1.0.2) or Botan (at least version 2).
   OpenSSL version 1.1.1 or later is strongly recommended.

-  log4cplus (at least version 1.0.3) development include headers.

-  A C++ compiler (with C++11 support) and standard development headers.
   The Kea build has been checked with GCC g++ 4.8.5 and some later versions,
   and Clang 800.0.38 and some later versions.

-  The development tools automake, libtool, and pkg-config.

-  The MySQL client and the client development libraries, when using the
   ``--with-mysql`` configuration flag to build the Kea MySQL database
   backend. In this case, an instance of the MySQL server running locally
   or on a machine reachable over a network is required. Note that running
   the unit tests requires a local MySQL server.

-  The PostgreSQL client and the client development libraries, when using the
   ``--with-pgsql`` configuration flag to build the Kea PostgreSQL database
   backend. In this case an instance of the PostgreSQL server running locally
   or on a machine reachable over a network is required. Note that running
   the unit tests requires a local PostgreSQL server.

-  The cpp-driver from DataStax is needed when using the ``--with-cql``
   configuration flag to build Kea with the Cassandra database backend.
   In this case, an instance of the Cassandra server running locally
   or on a machine reachable over a network is required. Note that running
   the unit tests requires a local Cassandra server.

-  The FreeRADIUS client library is required to connect to a RADIUS server.
   This is specified using the ``--with-freeradius`` configuration switch.

-  Sysrepo v1.4.140 and libyang v1.0.240 are needed to connect to a Sysrepo
   datastore. Earlier versions are no longer supported. When compiling from
   sources, the configure switches that can be used are ``--with-libyang`` and
   ``--with-sysrepo`` without any parameters. If these dependencies were
   installed in custom paths, point the switches to them.

-  The MIT Kerberos 5 or Heimdal libraries are needed by Kea DDNS server to sign
   and verify DNS updates using GSS-TSIG. The configuration switch which enables
   this functionality is ``--with-gssapi`` without any parameters. If these
   dependencies were installed in custom paths, point the switch to them.

-  googletest (version 1.8 or later) is required when using the ``--with-gtest``
   configuration option to build the unit tests.

-  The documentation generation tools `Sphinx <https://www.sphinx-doc.org/>`_,
   texlive with its extensions, and Doxygen, if using the ``--enable-generate-docs``
   configuration option to create the documentation. Specifically,
   with Fedora, python3-sphinx, texlive, and texlive-collection-latexextra are necessary;
   with Ubuntu, python3-sphinx, python3-sphinx-rtd-theme, and texlive-binaries
   are needed. If LaTeX packages are missing, Kea skips PDF generation and produces
   only HTML documents.

Visit ISC's Knowledgebase at https://kb.isc.org/docs/installing-kea for
system-specific installation tips.

.. _install:

Installation From Source
========================

Although Kea may be available in pre-compiled, ready-to-use packages
from operating system vendors, it is open source software written in
C++. As such, it is freely available in source code form from ISC as a
downloadable tar file. The source code can also be obtained from the Kea
GitLab repository at https://gitlab.isc.org/isc-projects/kea. This
section describes how to build Kea from the source code.

Download Tar File
-----------------

The Kea release tarballs may be downloaded from:
https://downloads.isc.org/isc/kea/.

Retrieve From Git
-----------------

The latest development code is available on GitLab (see
https://gitlab.isc.org/isc-projects/kea). The Kea source is public and
development is done in the “master” branch.

Downloading this "bleeding edge" code is recommended only for developers
or advanced users. Using development code in a production environment is
not recommended.

.. note::

   When building from source code retrieved via git, additional software
   is required: automake (v1.11 or later), libtoolize, and autoconf
   (v2.69 or later). These may need to be installed.

The code can be checked out from
``https://gitlab.isc.org/isc-projects/kea.git``:

.. code-block:: console

   $ git clone https://gitlab.isc.org/isc-projects/kea.git

The code checked out from the git repository does not include the
generated configure script or the Makefile.in files, nor their related build
files. They can be created by running ``autoreconf`` with the
``--install`` switch. This will run ``autoconf``, ``aclocal``,
``libtoolize``, ``autoheader``, ``automake``, and related commands.

Write access to the Kea repository is only granted to ISC staff.
Developers planning to contribute to Kea should check our
`Contributor's
Guide <https://gitlab.isc.org/isc-projects/kea/blob/master/contributors-guide.md>`__.
The `Kea Developer's
Guide <https://reports.kea.isc.org/dev_guide/>`__ contains more
information about the process, and describes the requirements for
contributed code to be accepted by ISC.

.. _configure:

Configure Before the Build
--------------------------

Kea uses the GNU Build System to discover build environment details. To
generate the makefiles using the defaults, simply run:

.. code-block:: console

   $ ./configure

Run ``./configure`` with the ``--help`` switch to view the different
options. Some commonly used options are:

 - ``--prefix``
   Define the installation location (the default is ``/usr/local``).

 - ``--with-mysql``
   Build Kea with code to allow it to store leases and host reservations
   in a MySQL database.

 - ``--with-pgsql``
   Build Kea with code to allow it to store leases and host reservations
   in a PostgreSQL database.

 - ``--with-cql``
   Build Kea with code to allow it to store leases and host reservations
   in a Cassandra (CQL) database. Support for Cassandra is now deprecated.

 - ``--with-log4cplus``
   Define the path to find the Log4cplus headers and libraries. Normally
   this is not necessary.

 - ``--with-boost-include``
   Define the path to find the Boost headers. Normally this is not
   necessary.

 - ``--with-botan-config``
   Specify the path to the botan-config script to build with Botan for
   cryptographic functions. It is preferable to use OpenSSL (see below).

 - ``--with-openssl``
   Use the OpenSSL cryptographic library instead of Botan. By default
   ``configure`` searches for a valid Botan installation; if one is not
   found, Kea searches for OpenSSL. Normally this is not necessary.

 - ``--enable-shell``
   Build the optional ``kea-shell`` tool (more in :ref:`kea-shell`).
   The default is to not build it.

 - ``--with-site-packages``
   Only useful when ``kea-shell`` is enabled, this switch causes the kea-shell
   Python packages to be installed in the specified directory. This is
   mostly useful for Debian-related distributions. While most systems store
   Python packages in ``${prefix}/usr/lib/pythonX/site-packages``, Debian
   introduced a separate directory for packages installed from DEB. Such
   Python packages are expected to be installed in
   ``/usr/lib/python3/dist-packages``.

 - ``--enable-perfdhcp``
   Build the optional ``perfdhcp`` DHCP benchmarking tool. The default
   is to not build it.

 - ``--with-freeradius``
   Build the optional ``RADIUS`` hook. This option specifies the path to the
   patched version of the FreeRADIUS client. This feature is available in
   the subscriber-only version of Kea, and requires the subscription-only RADIUS hook.

 - ``--with-freeradius-dictionary``
   Specify a non-standard location for a FreeRADIUS dictionary file, which
   contains a list of supported RADIUS attributes. This feature is available in
   the subscriber-only version of Kea, and requires the subscription-only RADIUS hook.

If the RADIUS options are not available, ensure that the RADIUS hook sources are in
the ``premium`` directory and rerun ``autoreconf -i``.

.. note::

   For instructions concerning the installation and configuration of
   database backends for Kea, see :ref:`dhcp-install-configure`.

There are many options that are typically not necessary for
regular users. However, they may be useful for package maintainers,
developers, or people who want to extend Kea code or send patches:

 - ``--with-gtest``, ``--with-gtest-source``
   Enable the building of C++ unit tests using the Google Test
   framework. This option specifies the path to the gtest source. (If
   the framework is not installed on the system, it can be downloaded
   from https://github.com/google/googletest.)

 - ``--enable-generate-docs``
   Enable the rebuilding of Kea documentation. ISC publishes Kea
   documentation for each release; however, in some cases it may be
   desirable to rebuild it: for example, to change something in the
   docs, or to generate new ones from git sources that are not yet
   released.

 - ``--enable-generate-parser``
   Enable the generation of parsers using flex or bison. Kea sources include
   .cc and .h parser files, pre-generated for users' convenience. By
   default Kea does not use flex or bison, to avoid
   requiring installation of unnecessary dependencies for users.
   However, if anything in the parsers is changed (such as adding a new
   parameter), flex and bison are required to regenerate
   parsers. This option permits that.

 - ``--enable-generate-messages``
   Enable the regeneration of messages files from their messages source
   files, e.g. regenerate xxx_messages.h and xxx_messages.cc from
   xxx_messages.mes using the Kea message compiler. By default Kea is
   built using these .h and .cc files from the distribution. However, if
   anything in a .mes file is changed (such as adding a new message),
   the Kea message compiler needs to be built and used. This option
   permits that.

 - ``--with-benchmark``, ``--with-benchmark-source``
   Enable the building of the database backend benchmarks using the
   Google Benchmark framework. This option specifies the path to the
   gtest source. (If the framework is not installed on the system, it
   can be downloaded from https://github.com/google/benchmark.)
   This support is experimental.

As an example, the following command configures Kea to find the Boost
headers in /usr/pkg/include, specifies that PostgreSQL support should be
enabled, and sets the installation location to /opt/kea:

.. code-block:: console

   $ ./configure \
         --with-boost-include=/usr/pkg/include \
         --with-pgsql=/usr/local/bin/pg_config \
         --prefix=/opt/kea

Users who have any problems with building Kea using the header-only Boost
code, or who would like to use the Boost system library (assumed for the
sake of this example to be located in /usr/pkg/lib), should issue these
commands:

.. code-block:: console

   $ ./configure \
         --with-boost-libs=-lboost_system \
         --with-boost-lib-dir=/usr/pkg/lib

If ``configure`` fails, it may be due to missing or old dependencies.

When ``configure`` succeeds, it displays a report with the parameters used
to build the code. This report is saved into the file ``config.report``
and is also embedded into the executable binaries, e.g., ``kea-dhcp4``.

Build
-----

After the configure step is complete, build the executables from the C++
code and prepare the Python scripts by running the command:

.. code-block:: console

   $ make

Install
-------

To install the Kea executables, support files, and documentation, issue
the command:

.. code-block:: console

   $ make install

Do not use any form of parallel or job server options (such as GNU
make's ``-j`` option) when performing this step; doing so may cause
errors.

.. note::

   The install step may require superuser privileges.

If required, run ``ldconfig`` as root with ``/usr/local/lib`` (or with
prefix/lib if configured with ``--prefix``) in ``/etc/ld.so.conf`` (or the
relevant linker cache configuration file for the OS):

.. code-block:: console

   $ ldconfig

..

.. note::

   If ``ldconfig`` is not run where required, users may see
   errors like the following:

   ::

       program: error while loading shared libraries: libkea-something.so.1:
       cannot open shared object file: No such file or directory


Cross-Building
--------------

It is possible to cross-build Kea, i.e. to create binaries in a separate
system (the ``build`` system) from the one where Kea runs
(the ``host`` system).

It is outside of the scope of common administrator operations and requires
some developer skills, but the Developer Guide explains how to do that
using an x86_64 Linux system to build Kea for a Raspberry Pi box running
Raspbian: `Kea Cross-Compiling Example
<https://reports.kea.isc.org/dev_guide/de/d9a/crossCompile.html>`__.

.. _dhcp-install-configure:

DHCP Database Installation and Configuration
============================================

Kea stores its leases in a lease database. The software has been written
in a way that makes it possible to choose which database product should
be used to store the lease information. Kea supports four
database backends: MySQL, PostgreSQL, Cassandra[1], and memfile. To limit
external dependencies, MySQL, PostgreSQL, and Cassandra support are
disabled by default and only memfile is available. Support for the
optional external database backend must be explicitly included when Kea
is built. This section covers the building of Kea with one of the
optional backends and the creation of the lease database.

[1] As of Kea 1.9.9, support for Cassandra is deprecated.

.. note::

   When unit tests are built with Kea (i.e. the ``--with-gtest`` configuration
   option is specified), the databases must be manually pre-configured
   for the unit tests to run. The details of this configuration can be
   found in the `Kea Developer's
   Guide <https://reports.kea.isc.org/dev_guide/>`__.

Building with MySQL Support
---------------------------

Install MySQL according to the instructions for the system. The client
development libraries must be installed.

Build and install Kea as described in :ref:`installation`,
with the following modification. To enable the MySQL database code, at the
"configure" step (see :ref:`configure`), the ``--with-mysql`` switch should be
specified:

.. code-block:: console

   $ ./configure [other-options] --with-mysql

If MySQL was not installed in the default location, the location of the
MySQL configuration program "mysql_config" should be included with the
switch:

.. code-block:: console

   $ ./configure [other-options] --with-mysql=path-to-mysql_config

See :ref:`mysql-database-create` for details regarding MySQL
database configuration.

Building with PostgreSQL support
--------------------------------

Install PostgreSQL according to the instructions for the system. The
client development libraries must be installed. Client development
libraries are often packaged as "libpq".

Build and install Kea as described in :ref:`installation`,
with the following modification. To enable the PostgreSQL database code, at the
"configure" step (see :ref:`configure`), the ``--with-pgsql`` switch should be
specified:

.. code-block:: console

   $ ./configure [other-options] --with-pgsql

If PostgreSQL was not installed in the default location, the location of
the PostgreSQL configuration program "pg_config" should be included with
the switch:

.. code-block:: console

   $ ./configure [other-options] --with-pgsql=path-to-pg_config

See :ref:`pgsql-database-create` for details regarding PostgreSQL
database configuration.

Building with CQL (Cassandra) Support
-------------------------------------

As of Kea 1.9.9, support for Cassandra is deprecated. It is still
available in current versions, but the support will be removed in a future
version; new users are encouraged to choose an alternative.

Install Cassandra according to the instructions for the system. The
Cassandra project website contains useful pointers:
https://cassandra.apache.org.

If a cpp-driver package is available as binary or as source,
simply install or build and install the package. Then build and install
Kea as described in :ref:`installation`. To enable the
Cassandra (CQL) database code, at the "configure" step (see :ref:`configure`), enter:

.. code-block:: console

   $ ./configure [other-options] --with-cql=path-to-pkg-config

If ``pkg-config`` is at its standard location (and thus in the
shell path), the path does not need to be specified. If it does not work
(e.g. no pkg-config, package not available in pkg-config with the
cassandra name), the ``cql_config`` script in the tools/ directory
can still be used as described below.

Download and compile cpp-driver from DataStax. For details regarding
dependencies for building cpp-driver, see the project homepage
https://github.com/datastax/cpp-driver.

.. code-block:: console

   $ git clone https://github.com/datastax/cpp-driver.git
   $ cd cpp-driver
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make

Kea's cpp-driver does not include the cql_config script. A
cql_config script is present in the tools/ directory of the Kea sources.
Before using it, please create a cql_config_defines.sh file in the same
directory (there is an example available in cql_config_define.sh.sample;
copy it over to cql_config_defines.sh and edit the path
specified in it) and change the environment variable CPP_DRIVER_PATH to
point to the directory where the cpp-driver sources are located. Make
sure that appropriate access rights are set on this file; it should be
executable by the system user building Kea.

Build and install Kea as described in :ref:`installation`,
with the following modification. To enable the Cassandra (CQL) database
code, at the "configure" step (see :ref:`configure`), enter:

.. code-block:: console

   $ ./configure [other-options] --with-cql=path-to-cql_config



.. include:: hammer.rst

.. _non-root:

Running Kea From a Non-root Account on Linux
============================================

Both Kea DHCPv4 and DHCPv6 servers perform operations that in general require root access
privileges. In particular, DHCPv4 opens raw sockets and both DHCPv4 and DHCPv6 open UDP sockets on
privileged ports. However, with some extra system configuration, it is possible to run Kea from
non-root accounts.

First, a regular user account must be created:

.. code-block:: console

   useradd admin

Then, change the binaries' ownership and group to the new user. Note that
the specific path may be different. Please refer to the ``--prefix``
parameter passed to the configure script:

.. code-block:: console

   chown -R admin /opt/kea
   chgrp -R admin /opt/kea
   chown -R admin /var/log/kea-dhcp4.log
   chgrp -R admin /var/log/kea-dhcp4.log
   chown -R admin /var/log/kea-dhcp6.log
   chgrp -R admin /var/log/kea-dhcp6.log

If using systemd, modify its service file
(e.g. /etc/systemd/system/kea-dhcp6.service):

.. code-block:: console

   User=admin
   Group=admin

The most important step is to set the capabilities of the binaries. Refer to `man capabilities` to get
more information.

.. code-block:: console

   setcap 'cap_net_bind_service,cap_net_raw=+ep' /opt/kea/sbin/kea-dhcp4
   setcap 'cap_net_bind_service=+ep' /opt/kea/sbin/kea-dhcp6

If using systemd, also add this to the service file
(e.g. /etc/systemd/system/kea-dhcp6.service):

.. code-block:: console

   ExecStartPre=setcap 'cap_net_bind_service=+ep' /opt/kea/sbin/kea-dhcp6

After this step is complete, the admin user should be able to run Kea. Note that the DHCPv4 server by
default opens raw sockets. If the network is only using relayed traffic, Kea can be instructed to
use regular UDP sockets (refer to ``dhcp-socket-type`` parameter in the
:ref:`dhcp4-interface-configuration` section) and the ``cap_net_raw`` capability can be skipped.

.. note::

   It is possible to avoid running Kea with root privileges by instructing Kea to
   use non-privileged (greater than 1024) ports and redirecting traffic. This, however, only works
   for relayed traffic. This approach in general is considered experimental and has not been tested
   for deployment in production environments. Use with caution!

   To use this approach, configure the server to listen on other non-privileged ports (e.g. 1547
   and 1548) by running the process with the ``-p`` option in ``/etc/systemd/system/kea-dhcp4.service``:

.. code-block:: console

   ExecStart=/opt/kea/sbin/kea-dhcp4 -d -c /etc/kea/kea-dhcp4.conf -p 2067

and ``/etc/systemd/system/kea-dhcp4.service``:

.. code-block:: console

   ExecStart=/opt/kea/sbin/kea-dhcp6 -d -c /etc/kea/kea-dhcp6.conf -p 1547

Then configure port redirection with iptables and ip6tables for new ports (e.g. 1547
and 1548). Be sure to replace ``ens4`` with the specific interface name.

.. code-block:: console

   iptables -t nat -A PREROUTING -i ens4 -p udp --dport 67 -j REDIRECT --to-port 2067
   iptables -t nat -A PREROUTING -i ens4 -p udp --dport 2068 -j REDIRECT --to-port 68
   ip6tables -t nat -A PREROUTING -i ens4 -p udp --dport 547 -j REDIRECT --to-port 1547
   ip6tables -t nat -A PREROUTING -i ens4 -p udp --dport 1548 -j REDIRECT --to-port 548

.. _deprecated:

Deprecated Features
===================

This section lists significant features that have been or will be removed. We try to 
deprecate features before removing them to signal
to current users to plan a migration. New users should not rely on deprecated features.

Cassandra (CQL) Support
-----------------------

Cassandra is a non-relational NoSQL database. Kea added support for the CQL lease backend in
Kea 1.1.0-beta1 and the CQL host backend in 1.4.0-beta1. This feature never gained much
traction with users, particularly compared to the level of interest in and deployments of
the alternatives, MySQL and PostgreSQL.

The non-relational nature of Cassandra makes it exceedingly difficult to implement more complex
DHCP features, such as the configuration backend. Cassandra also introduces performance degradation,
is complicated to set up, and is an ongoing maintenance burden.

Cassandra support is deprecated as of Kea 1.9.9. The feature will
function as before in the Kea 2.0.x and 2.1.x series, but will print a warning. The
feature will be removed entirely in a future release.

Sysrepo 0.x
-----------

Kea versions 1.9.9 and earlier required Sysrepo 0.7.x to run, when optional support for NETCONF was
enabled. Kea versions 1.9.10 and later now require Sysrepo 1.4.x and the related libyang 1.x library to
run. The earlier Sysrepo versions are no longer supported. The latest Sysrepo 2.x version does not
provide C++ bindings, and as such, is not usable for Kea.
