.. _quickstart:

***********
Quick Start
***********

This section describes the basic steps needed to get Kea up and running.
For further details, full customizations, and troubleshooting, see the
respective chapters elsewhere in this Kea Administrator Reference Manual (ARM).

.. _quick-start-tarball:

Quick Start Guide Using tarball
===============================

1.  Install required runtime and build dependencies. See
    :ref:`build-requirements` for details.

2.  Download the Kea source tarball from the `ISC.org downloads
    page <https://www.isc.org/download/>`__ or the `ISC downloads site
    <https://downloads.isc.org/isc/kea/>`__.

3.  Extract the tarball. For example:

    .. parsed-literal::

       $ tar -xvzf kea-|release|.tar.gz

4.  Go into the source directory and run the configure script:

    .. parsed-literal::

       $ cd kea-|release|
       $ ./configure [your extra parameters]

5.  Build it:

    .. code-block:: console

       $ make

6.  Install it (by default it will be placed in ``/usr/local/``, so
    root privileges are likely required for this step):

    .. code-block:: console

       $ make install

.. _quick-start-repo:

Quick Start Guide Using Native Packages
=======================================

ISC provides native Alpine, deb, and RPM packages, which make Kea installation
much easier. Unless specific compilation options are desired, it is usually
easier to install Kea using native packages.

1. Go to `Kea on cloudsmith.io <https://cloudsmith.io/~isc/repos/>`__,
   choose the Kea version, and enter the repository.

2. Use ``Set Me Up`` and follow instructions to add the repository
   to the local system.

.. note::
  For example, the Debian setup instructions for Kea 2.3 can be found here:
  https://cloudsmith.io/~isc/repos/kea-2-3/setup/#formats-deb

  You can use the dropdown near the top of the page to get instructions for
  another OS.

3. Update system repositories. For example on Debian/Ubuntu:

    .. code-block:: console

        $ sudo apt update

   On CentOS/Fedora:

    .. code-block:: console

        $ sudo yum update

   On Alpine:

    .. code-block:: console

        # apk update

4. Kea is split into various packages. The entire list is available on
   `cloudsmith.io <https://cloudsmith.io/~isc/repos/>`__  or using apt/yum/dnf.
   For example on Debian/Ubuntu:

    .. code-block:: console

        $ apt search isc-kea

   On CentOS/Fedora:

    .. code-block:: console

        $ yum search isc-kea

   On Alpine:

    .. code-block:: console

        $ apk search isc-kea

5. Install the metapackage containing all of the tools, services, and open
   source hooks:

    .. code-block:: console

        $ sudo apt install isc-kea

   or specific packages:

    .. code-block:: console

        $ sudo apt install isc-kea-dhcp6

   or every single Kea related package, including development headers, debug
   symbols, and premium hooks (if they are available to you):

    .. code-block:: console

        $ sudo apt install isc-kea*

   or all packages with a specified version number:

    .. code-block:: console

        $ sudo apt install isc-kea*=1.8.1-isc0000920201106154401

.. note::
  Not all package managers support installing packages with a glob (``*``),
  please refer to your package managers manual before attempting to do so.

  - On CentOS/Fedora systems, replace ``apt install`` with ``yum install``
  - On Alpine systems, replace ``apt install`` with ``apk add``

6. All installed packages should be now available directly; for example:

    .. code-block:: console

        # kea-dhcp6 -c /path/to/your/kea6/config/file.json

   or using systemd:

    .. code-block:: console

        # systemctl restart kea-dhcp6

   or using OpenRC on Alpine:

    .. code-block:: console

        # service kea-dhcp6 restart

.. note::
  ``keactrl`` is not available in packages as similar functionality is provided
  by the native systemctl scripts.

7. On CentOS, Fedora, and Alpine, you will need to enable the service at boot
   time if that is desirable. This is done automatically at package
   installation time on Debian and Ubuntu systems. For example, with systemd
   on CentOS/Fedora:

    .. code-block:: console

        # systemctl enable kea-dhcp6

   With OpenRC on Alpine:

    .. code-block:: console

        # rc-update add kea-dhcp6

.. _quick-start-services:

Quick Start Guide for DHCPv4 and DHCPv6 Services
================================================
1.  Edit the Kea configuration files, which by default are installed in
    the ``[kea-install-dir]/etc/kea/`` directory. These are:
    ``kea-dhcp4.conf``, ``kea-dhcp6.conf``, ``kea-dhcp-ddns.conf`` and
    ``kea-ctrl-agent.conf``, ``keactrl.conf`` for DHCPv4 server, DHCPv6 server,
    D2, Control Agent, and the keactrl script, respectively.

2.  To start the DHCPv4 server in the background, run the
    following command (as root):

    .. code-block:: console

       # keactrl start -s dhcp4

    Or run the following command to start the DHCPv6 server:

    .. code-block:: console

       # keactrl start -s dhcp6

    Note that it is also possible to start all servers simultaneously:

    .. code-block:: console

       # keactrl start

3.  Verify that the Kea server(s) is/are running:

    .. code-block:: console

       # keactrl status

    A server status of "inactive" may indicate a configuration error.
    Please check the log file (by default named
    ``[kea-install-dir]/var/log/kea-dhcp4.log``,
    ``[kea-install-dir]/var/log/kea-dhcp6.log``,
    ``[kea-install-dir]/var/log/kea-ddns.log``, or
    ``[kea-install-dir]/var/log/kea-ctrl-agent.log``) for the details of
    any errors.

4.  If the server has started successfully, test that it is
    responding to DHCP queries and that the client receives a
    configuration from the server; for example, use the `ISC DHCP
    client <https://www.isc.org/download/>`__.

5.  To stop running the server(s):

    .. code-block:: console

       # keactrl stop

For system-specific instructions, please read the
`system-specific notes <https://kb.isc.org/docs/installing-kea>`__,
available in the Kea section of `ISC's
Knowledgebase <https://kb.isc.org/docs>`__.

The details of ``keactrl`` script usage can be found in :ref:`keactrl`.

Once Kea services are up and running, consider deploying a dashboard solution
to monitor running services. For more details, see :ref:`stork`.

.. _quick-start-direct-run:

Running the Kea Servers Directly
================================

The Kea servers can be started directly, without the need to use
``keactrl`` or ``systemctl``. To start the DHCPv4 server run the following command:

.. code-block:: console

   # kea-dhcp4 -c /path/to/your/kea4/config/file.json

Similarly, to start the DHCPv6 server, run the following command:

.. code-block:: console

   # kea-dhcp6 -c /path/to/your/kea6/config/file.json
