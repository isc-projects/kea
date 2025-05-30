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
kea-2-6 or kea-3-0) along with all its maintenance updates.
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

The Kea subscriber hook packages are not included in the ``isc-kea-hooks`` package.
For ISC customers with access to the subscriber hooks, those packages have the
``isc-kea-subscriber-`` prefix. For users interested in purchasing professional
support services from ISC and getting access to the subscriber hooks, please
fill out our contact form at https://www.isc.org/contact.

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

-  ``var/log/kea/`` - log files.

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
   ``-D mysql=enabled`` configuration flag to build the Kea MySQL database
   backend. In this case, an instance of the MySQL server running locally
   or on a machine reachable over a network is required. Note that running
   the unit tests requires a local MySQL server.

-  The PostgreSQL client and the client development libraries, when using the
   ``-D postgresql=enabled`` configuration flag to build the Kea PostgreSQL database
   backend. In this case an instance of the PostgreSQL server running locally
   or on a machine reachable over a network is required. Note that running
   the unit tests requires a local PostgreSQL server.

-  Sysrepo v1.4.140 and libyang v1.0.240, needed to connect to a Sysrepo
   datastore. Earlier versions are no longer supported. When compiling from
   sources, the configure switch that can be used is ``-D netconf=enabled``.
   If these dependencies were installed in custom paths, point PKG_CONFIG_PATH
   to them.

-  The MIT Kerberos 5 or Heimdal libraries are needed by Kea DDNS server to
   sign and verify DNS updates using GSS-TSIG. The configuration switch which
   enables this functionality is ``-D krb5=enabled``. If this dependency is installed
   in a custom path, point PKG_CONFIG_PATH to the .pc file or PATH to the
   krb5-config tool.

-  googletest (version 1.8 or later) is required when using the ``-D tests=enabled``
   configuration option to build the unit tests.

-  The documentation generation tools `Sphinx <https://www.sphinx-doc.org/>`_,
   texlive with its extensions, and Doxygen, to create the documentation.
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
   $ gpg --verify kea-X.Y.Z.tar.xz.asc kea-X.Y.Z.tar.xz

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

The code checked out from the git repository does not include the build files.
They can be created by running ``meson setup build``.

Write access to the Kea repository is only granted to ISC staff.
Developers planning to contribute to Kea should check our
`Contributor's
Guide <https://gitlab.isc.org/isc-projects/kea/blob/master/contributors-guide.md>`__.
The `Kea Developer's
Guide <https://reports.kea.isc.org/dev_guide/>`__ contains more
information about the process, and describes the requirements for
contributed code to be accepted by ISC.

.. _setup:

Set Up the Build
----------------

Kea uses Meson to discover build environment details. To generate the ninja
file using the defaults, simply run:

.. code-block:: console

   $ meson setup build

Run ``meson configure`` to view the different build options.
Some commonly used options are:

 - ``--prefix``
   Define the installation location (the default is ``/usr/local``).

 - ``-D mysql=enabled``
   Build Kea with code to allow it to store leases and host reservations
   in a MySQL database.

 - ``-D postgresql=enabled``
   Build Kea with code to allow it to store leases and host reservations
   in a PostgreSQL database.

 - ``-D krb5=enabled``
   Build Kea with Kerberos5 with GSS-API support required by
   :ischooklib:`libddns_gss_tsig.so`.

 - ``-D netconf=enabled``
   Build Kea with libyang and sysrepo support required by
   :iscman:`kea-netconf`.

 - ``-D crypto=botan``
   Specify the name of the Botan pkg-config library e.g. ``botan-2``
   to build with Botan for cryptographic functions. It is preferable
   to use OpenSSL (see below).

 - ``--D crypto=openssl``
   Use the OpenSSL cryptographic library instead of Botan. By default
   Meson searches for a valid Botan installation; if one is not
   found, Kea searches for OpenSSL. Normally this is not necessary.

.. note::

   For instructions concerning the installation and configuration of
   database backends for Kea, see :ref:`dhcp-install-configure`.

If ``meson setup build`` fails, it may be due to missing or old dependencies.

When ``meson setup build`` succeeds, it displays a report with the parameters
used to build the code. This report is saved into the file
``build/config.report`` and is also embedded into the executable binaries, e.g.
:iscman:`kea-dhcp6`.

Build
-----

After the setup step is complete, build the executables from the C++
code and prepare the Python scripts by running the command:

.. code-block:: console

   $ meson compile -C build

Install
-------

To install the Kea executables, support files, and documentation, issue
the command:

.. code-block:: console

   $ meson install -C build

.. note::

   The install step may require superuser privileges.

It should not be required, but if shared libraries are not found at runtime,
you can run ``ldconfig`` as root with ``/usr/local/lib`` (or with
``${prefix}/lib`` if set up with ``--prefix``) in ``/etc/ld.so.conf`` (or
the relevant linker cache configuration file for the OS):

.. code-block:: console

   $ ldconfig

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

   When unit tests are built with Kea (i.e. the ``-D tests=enabled`` configuration
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
setup step (see :ref:`setup`), the ``-D mysql=enabled`` switch should be specified:

.. code-block:: console

   $ meson setup build -D mysql=enabled

If MySQL was not installed in the default location, the location can be
selected by setting ``PKG_CONFIG_PATH=/path/to/mariadb.pc:${PKG_CONFIG_PATH}``
or ``PATH=/path/to/mariadb-config:${PATH}`` prior to ``meson setup``.

.. code-block:: console

   $ PKG_CONFIG_PATH=/opt/mariadb/lib/pkgconfig PATH=/opt/mariadb/bin meson setup build -D mysql=enabled

See :ref:`mysql-database-create` for details regarding MySQL
database configuration.

Building with PostgreSQL Support
--------------------------------

Install PostgreSQL according to the instructions for the system. The
client development libraries must be installed. Client development
libraries are often packaged as ``libpq``.

Build and install Kea as described in :ref:`installation`,
with the following modification. To enable the PostgreSQL database code, at the
setup step (see :ref:`setup`), the ``-D postgresql=enabled`` switch should be specified.

If PostgreSQL was not installed in the default location, the location can be
selected by setting ``PKG_CONFIG_PATH=/path/to/libpq.pc:${PKG_CONFIG_PATH}``
or ``PATH=/path/to/pg_config:${PATH}`` prior to ``meson setup``.

.. code-block:: console

   $ PKG_CONFIG_PATH=/opt/postgresql/lib/pkgconfig PATH=/opt/postgresql/bin meson setup build -D postgresql=enabled

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
parameter passed to ``meson setup``:

.. code-block:: console

   chown -R admin /opt/kea
   chgrp -R admin /opt/kea
   chown -R admin /var/log/kea/kea-dhcp4.log
   chgrp -R admin /var/log/kea/kea-dhcp4.log
   chown -R admin /var/log/kea/kea-dhcp6.log
   chgrp -R admin /var/log/kea/kea-dhcp6.log

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
