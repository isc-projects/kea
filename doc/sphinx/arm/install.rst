.. _installation:

************
Installation
************

Packages
========

ISC publishes native RPM, deb, and APK packages, as well as tarballs
with the source code. The packages are available in
`ISC's Cloudsmith repositories <https://cloudsmith.io/~isc/repos>`_.
The native packages can be downloaded
and installed using the system available in a specific distribution (such
as dpkg or rpm). The Kea repository can also be added to the system,
making it easier to install updates. For details, please
go to https://cloudsmith.io/~isc/repos, choose the desired Kea version,
and then click the "Set Me Up" button. For detailed
instructions, please refer to this `Knowledgebase article <https://kb.isc.org/docs/isc-kea-packages>`_.

ISC maintains two types of repositories: stable and development.
The stable repositories contain a single stable release (e.g.,
kea-2-4 or kea-2-6) along with all its maintenance updates.
Separate repositories were introduced to minimize the risk of
unintentionally upgrading from one stable release to another.

The development repository, kea-dev, includes current and
future development releases, which ISC does not recommend
for production use. Packages in the kea-dev repository are
subject to cleanup, and older versions may be removed.

Installation From Cloudsmith Packages
-------------------------------------
ISC provides Kea packages for Alpine, Debian, Fedora, RHEL, and Ubuntu.
The recommended method for installing Kea on any of these systems is to
install the ``isc-kea`` metapackage from the Cloudsmith repository.
This metapackage is included on all supported distros and
installs all of the services offered by the Kea software suite.

Specific Kea components
can be installed individually, with any of the following packages:

- ``isc-kea-dhcp4`` — Kea DHCPv4 server package

- ``isc-kea-dhcp6`` — Kea DHCPv6 server package

- ``isc-kea-dhcp-ddns`` — Kea DHCP DDNS server

- ``isc-kea-ctrl-agent`` — Kea Control Agent for remote configuration

- ``isc-kea-admin`` — Kea database administration tools

- ``isc-kea-hooks`` — Kea open source DHCP hooks

Kea premium hook packages are not included in the ``isc-kea-hooks`` package.
For ISC customers with access to the premium hooks, those packages have the
``isc-kea-premium-`` prefix. Users wishing to purchase the premium hooks
can find them on ISC's website, at https://www.isc.org/shop/.

Once installed, the services can be managed through the distribution's
service manager. The services are named: :iscman:`kea-dhcp4`, :iscman:`kea-dhcp6`,
:iscman:`kea-dhcp-ddns`, and :iscman:`kea-ctrl-agent`.

.. note::
   The real service names on Debian and Ubuntu use slightly different
   package names, to maintain compatibility with some older scripts. A
   systemd service alias is used to allow users to refer to them with shorter
   names. Calling ``systemctl enable`` on these services requires
   the real service names, which are: ``isc-kea-dhcp4-server``,
   ``isc-kea-dhcp6-server``, ``isc-kea-dhcp-ddns-server``, and
   ``isc-kea-ctrl-agent``.

Caveats When Upgrading Kea Packages
-----------------------------------

To upgrade to a current version of Kea from version 2.3.2 or earlier on Debian
and Ubuntu systems, run ``apt dist-upgrade`` instead of the usual ``apt upgrade``.
Once this upgrade has been completed, it is possible to upgrade to later versions
normally using  ``apt upgrade`` on Debian and Ubuntu systems.

Users may notice differences in the packages distributed in Kea versions prior to
2.3.2 and those distributed with 2.3.2 and later. As a result of an overhaul of our
package design with that release, some packages were renamed or removed.
To ensure that upgrades go as smoothly as possible, pay attention to
which packages are being removed and installed by the upgrade transaction,
and ensure that all required packages are reinstalled.

Specifically, there is a possibility for the following packages to be removed
during the upgrade, depending on which packages were originally installed:

- ``isc-kea-dhcp4``

- ``isc-kea-dhcp6``

- ``isc-kea-dhcp-ddns``

- ``isc-kea-hooks``

To install the entire Kea software suite, simply run
``apt install isc-kea`` after upgrading, which
will install all of the relevant subpackages that make up Kea.

This upgrade path issue does not apply to RPM and Alpine systems.

Customers with ISC support contracts who experience difficulties with upgrading
are invited to open a ticket in their support queue. Other users
are encouraged to describe their situation on the `kea-users mailing list <https://lists.isc.org/mailman/listinfo/kea-users>`_
for best-effort support from other list members.

.. _install-hierarchy:

Installation Hierarchy
======================

The following is the directory layout of the complete Kea installation.
(All directory paths are relative to the installation directory.)

-  ``etc/kea/`` — configuration files.

-  ``include/`` — C++ development header files.

-  ``lib/`` — libraries.

-  ``lib/kea/hooks`` — additional hook libraries.

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

In addition to the runtime requirements (listed in
:ref:`required-software`), building Kea from source code requires
various development include headers and program development tools.

.. note::

   Some operating systems have split their distribution packages into a
   runtime and a development package. The
   development package versions, which include header files and
   libraries, must be installed to build Kea from the source code.

Building from source code requires the following software installed on
the system:

-  Boost C++ libraries (https://www.boost.org/). The oldest Boost version
   used for testing is 1.67 (although Kea may also work with older
   versions e.g. 1.66). The Boost system library must also be installed.
   Installing a header-only version of Boost is not recommended.

-  OpenSSL (at least version 1.0.2) or Botan (at least version 2).
   OpenSSL version 1.1.1 or later is strongly recommended.

-  log4cplus (at least version 1.0.3) development include headers.

-  A C++ compiler (with C++14 support) and standard development headers.

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

-  Sysrepo v1.4.140 and libyang v1.0.240, needed to connect to a Sysrepo
   datastore. Earlier versions are no longer supported. When compiling from
   sources, the configure switches that can be used are ``--with-libyang`` and
   ``--with-sysrepo`` without any parameters. If these dependencies were
   installed in custom paths, point the switches to them.

-  The MIT Kerberos 5 or Heimdal libraries are needed by Kea DDNS server to sign
   and verify DNS updates using GSS-TSIG. The configuration switch which enables
   this functionality is ``--with-gssapi``, without any parameters. If these
   dependencies were installed in custom paths, point the switch to them.

-  googletest (version 1.8 or later) is required when using the ``--with-gtest``
   configuration option to build the unit tests.

-  The documentation generation tools `Sphinx <https://www.sphinx-doc.org/>`_,
   texlive with its extensions, and Doxygen, if using the
   ``--enable-generate-docs`` configuration option to create the documentation.
   Specifically, with Fedora, ``python3-sphinx``, ``python3-sphinx_rtd_theme``,
   ``texlive``, and ``texlive-collection-latexextra`` are necessary.
   With Ubuntu, ``python3-sphinx``, ``python3-sphinx-rtd-theme``,
   ``texlive``, and ``texlive-latex-extra`` are needed.
   If LaTeX packages are missing, Kea skips PDF generation and produces only
   HTML documents.

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

Verify The Tar File Signature
-----------------------------

The tar file with the source code is distributed together with its
GPG signature. The signature is a file with the same name as the tar
file appended by the ``.asc`` extension. You can find the signature
file on our download page, FTP, or CloudSmith.

The signature is created using the ISC code-signing key. The current
set of ISC code-signing keys is available from the ISC website at
https://www.isc.org/pgpkey (the `Current Set of ISC Code-Signing Keys
<https://www.isc.org/docs/isc-keyblock.asc>`_ link).

The signature can be verified using the GnuPGP ``gpg`` tool. The
following commands import the code-signing keys
(``isc-keyblock.asc``) and verify the signature:

.. code-block:: console

   $ gpg --import isc-keyblock.asc
   $ gpg --verify kea-X.Y.Z.tar.gz.asc kea-X.Y.Z.tar.gz

The verification allows users to confirm that the tar file has not
been tampered with and that it was created by ISC.

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
files. Those can be created by running ``autoreconf`` with the
``--install`` switch, which will run ``autoconf``, ``aclocal``,
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
   Build the optional :iscman:`kea-shell` tool (see :ref:`kea-shell`).
   The default is to not build it.

 - ``--with-site-packages``
   Install the kea-shell Python packages in the specified directory; this 
   is only useful when :iscman:`kea-shell` is enabled, and is
   mostly helpful for Debian-related distributions. While most systems store
   Python packages in ``${prefix}/usr/lib/pythonX/site-packages``, Debian
   introduced a separate directory for packages installed from DEB. Such
   Python packages are expected to be installed in
   ``/usr/lib/python3/dist-packages``.

 - ``--enable-perfdhcp``
   Build the optional :iscman:`perfdhcp` DHCP benchmarking tool. The default
   is to not build it.

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
and is also embedded into the executable binaries, e.g. :iscman:`kea-dhcp4`.

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
Raspbian: see this `Kea Cross-Compiling Example
<https://reports.kea.isc.org/dev_guide/de/d9a/crossCompile.html>`__.

.. _dhcp-install-configure:

DHCP Database Installation and Configuration
============================================

Kea stores its leases in a lease database. The software has been written
in a way that makes it possible to choose which database product should
be used to store the lease information. Kea supports three
database backends: MySQL, PostgreSQL, and memfile. To limit external
dependencies, MySQL and PostgreSQL support are disabled by default and only
memfile is available. Support for the optional external database backend must
be explicitly included when Kea is built.
This section covers the building of Kea with one of the optional backends and
the creation of the lease database.

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

The most important step is to set the capabilities of the binaries. Refer to the operating system man page
for `capabilities` for more information.

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
deprecate features before removing them, to signal
to current users to plan a migration. New users should not rely on deprecated features.

Sysrepo 0.x or 1.x
------------------

Kea 2.3.2 introduced support for Sysrepo 2.x. Unfortunately,
Sysrepo continues to undergo major changes that are backward-incompatible,
and current Kea versions do not support Sysrepo earlier than versions 2.x.
