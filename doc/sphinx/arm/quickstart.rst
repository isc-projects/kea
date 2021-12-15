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

3. Update system repositories. For example:

    .. code-block:: console

        $ apt-get update

4. Kea is split into various packages. The entire list is available on
   `cloudsmith.io <https://cloudsmith.io/~isc/repos/>`__  or using apt/yum/dnf.
   For example:

    .. code-block:: console

        $ apt-cache search isc-kea

5. Install specific packages:

    .. code-block:: console

        $ sudo apt-get install isc-kea-dhcp6-server

   or all packages:

    .. code-block:: console

        $ sudo apt-get install isc-kea*

   or all packages with a specified version number:

    .. code-block:: console

        $ sudo apt-get install isc-kea*=1.8.1-isc0000920201106154401

6. All installed packages should be now available directly; for example:

    .. code-block:: console

       # kea-dhcp6 -c /path/to/your/kea6/config/file.json

   or using systemd:

    .. code-block:: console

       # systemctl restart isc-kea-dhcp6-server

   ``keactrl`` is not available in packages as similar functionality is provided
   by the native systemctl scripts.

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
