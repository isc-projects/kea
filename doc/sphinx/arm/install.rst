.. _installation:

************
Installation
************

Packages
========

Some operating systems or software package vendors may provide
ready-to-use, pre-built software packages for Kea. Installing a
pre-built package means you do not need to install the software required
only to build Kea and do not need to *make* the software.

.. _install-hierarchy:

Installation Hierarchy
======================

The following is the directory layout of the complete Kea installation.
(All directory paths are relative to the installation directory):

-  ``etc/kea/`` — configuration files.

-  ``include/`` — C++ development header files.

-  ``lib/`` — libraries.

-  ``lib/kea/hooks`` — additional hooks libraries.

-  ``sbin/`` — server software and commands used by the system
   administrator.

-  ``share/kea/`` — configuration specifications and examples.

-  ``share/doc/kea/`` — this guide, other supplementary documentation,
   and examples.

-  ``share/man/`` — manual pages (online documentation).

-  ``var/lib/kea/`` — server identification, and lease databases
   files.

-  ``var/log/`` - log files.

-  ``var/run/kea`` - pid and logger lock files.

.. _build-requirements:

Build Requirements
=====================

In addition to the run-time requirements (listed in
:ref:`required-software`), building Kea from source code requires
various development include headers and program development tools.

.. note::

   Some operating systems have split their distribution packages into a
   run-time and a development package. You will need to install the
   development package versions, which include header files and
   libraries, to build Kea from the source code.

Building from source code requires the following software installed on
the system:

-  Boost C++ libraries (https://www.boost.org/). The oldest Boost version
   used for testing is 1.57 (although it may also work with older
   versions). The Boost system library must also be installed.
   Installing a header-only version of Boost is no longer recommended.

-  OpenSSL (at least version 1.0.1) or Botan (at least version 2).
   Note that OpenSSL version 1.0.2 or 1.1.0 or later is strongly recommended.

-  log4cplus (at least version 1.0.3) development include headers.

-  A C++ compiler (with C++11 support) and standard development headers.
   The Kea build has been checked with GCC g++ 4.8.5 and some later versions,
   and Clang 800.0.38 and some later versions.

-  The development tools automake, libtool, and pkg-config.

-  The MySQL client and the client development libraries, when using the
   --with-mysql configuration flag to build the Kea MySQL database
   backend. In this case, an instance of the MySQL server running
   locally or on a machine reachable over a network is required. Note
   that running the unit tests requires a local MySQL server.

-  The PostgreSQL client and the client development libraries, when
   using the --with-pgsql configuration flag to build the Kea PostgreSQL
   database backend. In this case an instance of the PostgreSQL server
   running locally or on some other machine, reachable over the network
   from the machine running Kea, is required. Note that running the unit
   tests requires a local PostgreSQL server.

-  The cpp-driver from DataStax is needed when using the --with-cql
   configuration flag to build Kea with the Cassandra database backend.
   In this case, an instance of the Cassandra server running locally or
   on some other machine, reachable over the network from the machine
   running Kea, is required. Note that running the unit tests requires a
   local Cassandra server.

-  The FreeRADIUS client library is required to connect to a RADIUS
   server. (This is specified using the --with-freeradius configuration
   switch.)

-  Sysrepo (version 0.7.6 or later) and libyang (version 0.16-r2 or
   later) are needed to connect to a Sysrepo database. (This is
   specified using the --with-sysrepo switch when running "configure".)

-  googletest (version 1.8 or later) is required when using the --with-gtest
   configuration option to build the unit tests.

-  The documentation generation tools `Sphinx <https://www.sphinx-doc.org/>`_,
   texlive with its extensions and Doxygen, if using the --enable-generate-docs
   configuration option to create the documentation. Particularly,
   in case of Fedora: python3-sphinx, texlive and texlive-collection-latexextra;
   in case of Ubuntu: python3-sphinx, python3-sphinx-rtd-theme and texlive???

Visit ISC's Knowledgebase at https://kb.isc.org/docs/installing-kea for
system-specific installation tips.

.. _install:

Installation from Source
========================

Although Kea may be available in pre-compiled, ready-to-use packages
from operating system vendors, it is open source software written in
C++. As such, it is freely available in source code form from ISC as a
downloadable tar file. The source code can also be obtained from the Kea
Gitlab repository at https://gitlab.isc.org/isc-projects/kea. This
section describes how to build Kea from the source code.

Download Tar File
-----------------

The Kea release tarballs may be downloaded from:
http://ftp.isc.org/isc/kea/ (using FTP or HTTP).

Retrieve from Git
-----------------

Downloading this "bleeding edge" code is recommended only for developers
or advanced users. Using development code in a production environment is
not recommended.

.. note::

   When building from source code retrieved via git, additional software
   will be required: automake (v1.11 or later), libtoolize, and autoconf
   (v2.69 or later). These may need to be installed.

The latest development code is available on GitLab (see
https://gitlab.isc.org/isc-projects/kea). The Kea source is public and
development is done in the “master” branch.

The code can be checked out from
``https://gitlab.isc.org/isc-projects/kea.git``:

.. code-block:: console

   $ git clone https://gitlab.isc.org/isc-projects/kea.git

The code checked out from the git repository does not include the
generated configure script, the Makefile.in files, nor their related build
files. They can be created by running ``autoreconf`` with the
``--install`` switch. This will run ``autoconf``, ``aclocal``,
``libtoolize``, ``autoheader``, ``automake``, and related commands.

Write access to the Kea repository is only granted to ISC staff. If you
are a developer planning to contribute to Kea, please check our
`Contributor's
Guide <https://gitlab.isc.org/isc-projects/kea/blob/master/contributors-guide.md>`__.
The `Kea Developer's
Guide <https://jenkins.isc.org/job/Kea_doc/doxygen/>`__ contains more
information about the process, as well as describes the requirements for
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

--prefix
   Define the installation location (the default is ``/usr/local``).

--with-mysql
   Build Kea with code to allow it to store leases and host reservations
   in a MySQL database.

--with-pgsql
   Build Kea with code to allow it to store leases and host reservations
   in a PostgreSQL database.

--with-cql
   Build Kea with code to allow it to store leases and host reservations
   in a Cassandra (CQL) database.

--with-log4cplus
   Define the path to find the Log4cplus headers and libraries. Normally
   this is not necessary.

--with-boost-include
   Define the path to find the Boost headers. Normally this is not
   necessary.

--with-botan-config
   Specify the path to the botan-config script to build with Botan for
   cryptographic functions. It is preferable to use OpenSSL (see below).

--with-openssl
   Replace Botan by the OpenSSL the cryptographic library. By default
   ``configure`` searches for a valid Botan installation. If one is not
   found, it searches for OpenSSL. Normally this is not necessary.

--enable-shell
   Build the optional ``kea-shell`` tool (more in :ref:`kea-shell`).
   The default is to not build it.

--with-site-packages
   Only useful when ``kea-shell`` is enabled. It causes the kea-shell
   python packages to be installed in specified directory. This is
   mostly useful for Debian related distros. While most systems store
   python packages in ${prefix}/usr/lib/pythonX/site-packages, Debian
   introduced separate directory for packages installed from DEB. Such
   python packages are expected to be installed in
   /usr/lib/python3/dist-packages.

--enable-perfdhcp
   Build the optional ``perfdhcp`` DHCP benchmarking tool. The default
   is to not build it.

.. note::

   The ``--runstatedir`` in the installation directories is particular.
   There are three cases:

   - You use autoconf 2.70 or greater which supports this, but this autoconf
     version has not been released yet.

   - You use autoconf 2.69 patched to add support of this. In this case and the
     previous simply use when needed the``--runstatedir`` configure parameter.

   - There is no support (the configure parameter is not recognized and configure
     directly raises an error). For autoconf 2.69 the ``runstatedir`` environment
     variable is supported so simply remove the ``--`` before ``runstatedir``
     in the configure script call, e.g.: ``./configure runstatedir=/opt/run ...``

..

.. note::

   For instructions concerning the installation and configuration of
   database backends for Kea, see :ref:`dhcp-install-configure`.

There are also many additional options that are typically not necessary for
regular users. However, they may be useful for package maintainers,
developers, or people who want to extend Kea code or send patches:

--with-gtest, --with-gtest-source
   Enable the building of the C++ Unit Tests using the Google Test
   framework. This option specifies the path to the gtest source. (If
   the framework is not installed on your system, it can be downloaded
   from https://github.com/google/googletest.)

--enable-generate-docs
   Enable the rebuilding Kea documentation. ISC publishes Kea
   documentation for each release; however, in some cases you may want
   to rebuild it. For example, if you want to change something in the
   docs, or want to generate new ones from git sources that are not
   released yet.

--enable-generate-parser
   Many Kea components have parsers implemented using flex (.ll files)
   and bison (.yy files). Kea sources have C++/h files generated out
   from them. By default Kea does not use flex or bison to avoid
   requiring installation of unnecessary dependencies for users.
   However, if you change anything in the parses (such as adding a new
   parameter), you will need to use flex and bison to regenerate
   parsers. This option lets you do that.

--enable-generate-messages
   Enable the regeneration of messages files from their messages source
   files, e.g. regenerate xxx_messages.h and xxx_messages.cc from
   xxx_messages.mes using the Kea message compiler. By default Kea is
   built using these .h and .cc files from the distribution. However, if
   you change anything in a .mes file (such as adding a new message), you
   will need to build and use the Kea message compiler. This option lets
   you do that.

--with-benchmark, --with-benchmark-source
   Enable the building of the database backend benchmarks using the
   Google Benchmark framework. This option specifies the path to the
   gtest source. (If the framework is not installed on your system, it
   can be downloaded from https://github.com/google/benchmark.)
   This support is experimental.

For example, the following command configures Kea to find the Boost
headers in /usr/pkg/include, specifies that PostgreSQL support should be
enabled, and sets the installation location to /opt/kea:

.. code-block:: console

   $ ./configure \
         --with-boost-include=/usr/pkg/include \
         --with-pgsql=/usr/local/bin/pg_config \
         --prefix=/opt/kea

If you have any problems with building Kea using the header-only Boost
code, or you'd like to use the Boost system library (assumed for the
sake of this example to be located in /usr/pkg/lib):

.. code-block:: console

   $ ./configure \
         --with-boost-libs=-lboost_system \
         --with-boost-lib-dir=/usr/pkg/lib

If ``configure`` fails, it may be due to missing or old dependencies.

If ``configure`` succeeds, it displays a report with the parameters used
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
prefix/lib if configured with --prefix) in ``/etc/ld.so.conf`` (or the
relevant linker cache configuration file for your OS):

.. code-block:: console

   $ ldconfig

..

.. note::

   If you do not run ``ldconfig`` where it is required, you may see
   errors like the following:

   ::

       program: error while loading shared libraries: libkea-something.so.1:
       cannot open shared object file: No such file or directory


.. _dhcp-install-configure:

DHCP Database Installation and Configuration
============================================

Kea stores its leases in a lease database. The software has been written
in a way that makes it possible to choose which database product should
be used to store the lease information. Kea supports four
database backends: MySQL, PostgreSQL, Cassandra, and memfile. To limit
external dependencies, MySQL, PostgreSQL, and Cassandra support are
disabled by default and only memfile is available. Support for the
optional external database backend must be explicitly included when Kea
is built. This section covers the building of Kea with one of the
optional backends and the creation of the lease database.

.. note::

   When unit tests are built with Kea (i.e. the --with-gtest configuration
   option is specified), the databases must be manually pre-configured
   for the unit tests to run. The details of this configuration can be
   found in the `Kea Developer's
   Guide <https://jenkins.isc.org/job/Kea_doc/doxygen/>`__.

Building with MySQL Support
---------------------------

Install MySQL according to the instructions for your system. The client
development libraries must be installed.

Build and install Kea as described in :ref:`installation`,
with the following modification. To enable the MySQL database code, at
the "configure" step (see :ref:`configure`),
the --with-mysql switch should be specified:

.. code-block:: console

   $ ./configure [other-options] --with-mysql

If MySQL was not installed in the default location, the location of the
MySQL configuration program "mysql_config" should be included with the
switch, i.e.

.. code-block:: console

   $ ./configure [other-options] --with-mysql=path-to-mysql_config

See :ref:`mysql-database-create` for details regarding MySQL
database configuration.

Building with PostgreSQL support
--------------------------------

Install PostgreSQL according to the instructions for your system. The
client development libraries must be installed. Client development
libraries are often packaged as "libpq".

Build and install Kea as described in :ref:`installation`,
with the following modification. To enable the PostgreSQL database code,
at the "configure" step (see :ref:`configure`), the --with-pgsql switch should be specified:

.. code-block:: console

   $ ./configure [other-options] --with-pgsql

If PostgreSQL was not installed in the default location, the location of
the PostgreSQL configuration program "pg_config" should be included with
the switch, i.e.

.. code-block:: console

   $ ./configure [other-options] --with-pgsql=path-to-pg_config

See :ref:`pgsql-database-create` for details regarding PostgreSQL
database configuration.

Building with CQL (Cassandra) Support
-------------------------------------

Install Cassandra according to the instructions for your system. The
Cassandra project website contains useful pointers:
https://cassandra.apache.org.

If you have a cpp-driver package available as binary or as source,
simply install or build and install the package. Then build and install
Kea as described in :ref:`installation`. To enable the
Cassandra (CQL) database code, at the "configure" step (see :ref:`configure`), enter:

.. code-block:: console

   $ ./configure [other-options] --with-cql=path-to-pkg-config

Note if ``pkg-config`` is at its standard location (and thus in the
shell path) you do not need to supply its path. If it does not work
(e.g. no pkg-config, package not available in pkg-config with the
cassandra name), you can still use the ``cql_config`` script in tools/
as described below.

Download and compile cpp-driver from DataStax. For details regarding
dependencies for building cpp-driver, see the project homepage
https://github.com/datastax/cpp-driver. In June 2016, the following
commands were used:

.. code-block:: console

   $ git clone https://github.com/datastax/cpp-driver
   $ cd cpp-driver
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make

As of January 2019, cpp-driver does not include cql_config script. Work
is in progress to contribute such a script to the cpp-driver project
but, until that is complete, intermediate steps need to be conducted. A
cql_config script is present in the tools/ directory of the Kea sources.
Before using it, please create a cql_config_defines.sh file in the same
directory (there is an example available in cql_config_define.sh.sample;
you may copy it over to cql_config_defines.sh and edit the path
specified in it) and change the environment variable CPP_DRIVER_PATH to
point to the directory where the cpp-driver sources are located. Make
sure that appropriate access rights are set on this file. It should be
executable by the system user building Kea.

Build and install Kea as described in :ref:`installation`,
with the following modification. To enable the Cassandra (CQL) database
code, at the "configure" step (see :ref:`configure`), enter:

.. code-block:: console

   $ ./configure [other-options] --with-cql=path-to-cql_config



.. include:: hammer.rst

Running Kea from non-root account on Linux
==========================================

Both Kea DHCPv4 and DHCPv6 servers perform operations that in general require root access
privileges. In particular, DHCPv4 opens raw sockets and both DHCPv4 and DHCPv6 open UDP sockets on
privileged ports. However, with some extra system configuration, it is possible to run Kea from
non-root accounts.

First, a regular user account must be created:

.. code-block:: console

   useradd admin

Then, change the binaries ownership and group to new user. Note your path may be different. Please
refer to the ``--prefix`` parameter passed to the configure script.:

.. code-block:: console

   chown -R admin /opt/kea
   chgrp -R admin /opt/kea
   chown -R admin /var/log/kea-dhcp4.log
   chgrp -R admin /var/log/kea-dhcp4.log
   chown -R admin /var/log/kea-dhcp6.log
   chgrp -R admin /var/log/kea-dhcp6.log

Assuming you are using systemd, you also should modify its service file
(e.g. /etc/systemd/system/kea-dhcp6.service):

.. code-block:: console

   User=admin
   Group=admin

The most important step is to set capabilities of the binaries. Refer to `man capabilities` to get
more information.

.. code-block:: console

   setcap 'cap_net_bind_service=+ep' /opt/kea/sbin/kea-dhcp4
   setcap 'cap_net_raw=+ep' /opt/kea/sbin/kea-dhcp4
   setcap 'cap_net_bind_service=+ep' /opt/kea/sbin/kea-dhcp6

After this step is complete, the admin user should be able to run Kea. Note that DHCPv4 server by
default opens raw sockets. If your network is only using relayed traffic, you can instruct Kea to
use regular UDP sockets (refer to ``dhcp-socket-type`` parameter in the
:ref:`dhcp4-interface-configuration` section) and the ``cap_net_raw`` capability can be skipped.

.. note::

   An alternative approach to avoiding running Kea with root privileges assumes instructing Kea to
   use non-privileged (greater than 1024) posts and redirecting traffic. This, however, will work
   only for relayed traffic. This approach in general is considered experimental and not tested
   enough for deployment in production environment. Use with caution!


To use this approach, configure the server to listen on other non privileged port (eg: 1547
and 1548) by running the process with ``-p`` option in ``/etc/systemd/system/kea-dhcp4.service``:

.. code-block:: console

   ExecStart=/opt/kea/sbin/kea-dhcp4 -d -c /etc/kea/kea-dhcp4.conf -p 2067

and ``/etc/systemd/system/kea-dhcp4.service``:

.. code-block:: console

   ExecStart=/opt/kea/sbin/kea-dhcp6 -d -c /etc/kea/kea-dhcp6.conf -p 1547

and then configure port redirection with iptables and ip6tables for new ports (eg: 1547
and 1548). Make sure you replace ens4 with your specific interface name.

.. code-block:: console

   iptables -t nat -A PREROUTING -i ens4 -p udp --dport 67 -j REDIRECT --to-port 2067
   iptables -t nat -A PREROUTING -i ens4 -p udp --dport 2068 -j REDIRECT --to-port 68
   ip6tables -t nat -A PREROUTING -i ens4 -p udp --dport 547 -j REDIRECT --to-port 1547
   ip6tables -t nat -A PREROUTING -i ens4 -p udp --dport 1548 -j REDIRECT --to-port 548
