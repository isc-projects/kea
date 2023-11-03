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

2.  Download the Kea source tarball from
    `the ISC.org downloads page <https://www.isc.org/download/>`__ or
    `the ISC downloads site <https://downloads.isc.org/isc/kea/>`__ or
    `the ISC Cloudsmith page <https://cloudsmith.io/~isc/packages/?q=format%3Araw>`__.

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

1. Go to `Kea on cloudsmith.io <https://cloudsmith.io/~isc/repos/>`__.

2. Choose the Cloudsmith repository e.g. |cloudsmith_repo| for Kea |version|.

3. Click on the arrow besides the ``Set Me Up`` button and select your OS flavor
   out of: ``Alpine``, ``Debian``, ``RedHat``.

4. Follow the instructions written there.

.. note::
  For example, the Debian setup instructions for Kea 2.4 can be found here:
  https://cloudsmith.io/~isc/repos/kea-2-4/setup/#formats-deb

  The dropdown near the top of the page offers instructions for
  other operating systems.

5. Kea is split into various packages. The entire list is available on the
   Cloudsmith repository page under ``Packages``, or it can be retrieved
   using ``apk``/``apt``/``dnf``.

.. list-table::
    :stub-columns: 1
    :widths: 10 90

    * - Debian/Ubuntu

      - .. code-block:: console

            $ apt search isc-kea

        .. note::
            ``isc-kea-dhcp4-server`` and ``isc-kea-dhcp6-server`` are empty
            transitional packages. The working server packages are
            ``isc-kea-dhcp4`` and ``isc-kea-dhcp6``.

    * - Fedora/RedHat

      - .. code-block:: console

            $ dnf search 'isc-kea*'

    * - Alpine

      - .. code-block:: console

            $ apk search isc-kea

6. Install the metapackage containing all the tools, libraries, servers,
   documentation, and open source hooks:

.. list-table::
    :stub-columns: 1
    :widths: 10 90

    * - Debian/Ubuntu

      - .. code-block:: console

            $ sudo apt install isc-kea

    * - Fedora/RedHat

      - .. code-block:: console

            $ sudo dnf install isc-kea

    * - Alpine

      - .. code-block:: console

            # apk add isc-kea

or specific packages:

.. list-table::
    :stub-columns: 1
    :widths: 10 90

    * - Debian/Ubuntu

      - .. code-block:: console

            $ sudo apt install isc-kea-dhcp6

    * - Fedora/RedHat

      - .. code-block:: console

            $ sudo dnf install isc-kea-dhcp6

    * - Alpine

      - .. code-block:: console

            $ apk add isc-kea-dhcp6

or every single Kea-related package, including development headers, debug
symbols, and premium hooks (if available):

.. list-table::
    :stub-columns: 1
    :widths: 10 90

    * - Debian/Ubuntu

      - .. code-block:: console

            $ sudo apt install 'isc-kea*'

    * - Fedora/RedHat

      - .. code-block:: console

            $ sudo dnf install 'isc-kea*'

    * - Alpine

      - Installing packages via globbing (``*``) is not available for Alpine,
        but it can be simulated with the following command:

        .. code-block:: console

            # apk search isc-kea | sed 's/-[0-9].*//g' | xargs apk add

or all packages with a specified version number:

.. list-table::
    :stub-columns: 1
    :widths: 10 90

    * - Debian/Ubuntu

      - .. code-block:: console

            $ sudo apt install 'isc-kea*=2.4.0-isc20230921141113'

    * - Fedora/RedHat

      - .. code-block:: console

            $ sudo dnf install 'isc-kea*2.4.0-isc20230921141113*'

    * - Alpine

      - Installing packages via globbing (``*``) is not available for Alpine,
        but it can be simulated with the following command:

        .. code-block:: console

            # apk search isc-kea | sed 's/-[0-9].*//g' | grep r20230921141113 | xargs apk add

8. All installed packages should be now available directly.

    You can start a server up manually:

    .. code-block:: console

        # kea-dhcp6 -c /etc/kea/kea-dhcp6.conf

   or using systemd:

    .. code-block:: console

        # systemctl restart kea-dhcp6

   or using OpenRC on Alpine:

    .. code-block:: console

        # service kea-dhcp6 restart

.. note::
  :iscman:`keactrl` is not available in packages, as similar functionality is provided
  by the native systemctl scripts.

9. On Debian/Ubuntu systems, the service is enabled at boot time automatically
   when the package is installed. On Fedora/RHEL and Alpine, the service is not
   enabled automatically, so, if desired, it must be enabled manually.

    With systemd on Fedora/RedHat:

    .. code-block:: console

        # systemctl enable kea-dhcp6

    With OpenRC on Alpine:

    .. code-block:: console

        # rc-update add kea-dhcp6


.. _quick-start-docker:

Quick Start Guide Using Docker Containers
=========================================

1. Go to `ISC docker repository on cloudsmith.io <https://cloudsmith.io/~isc/repos/docker/packages/>`__.

2. Create an ipvlan network attached to the client-facing host interface and
   assigned to the subnet that is served by Kea.

.. code-block:: console

    $ docker network create --driver ipvlan --ipv6 --subnet 2001:db8::/64 --opt parent=eth0 ipvlan0

3. Pick the desired image and pull it locally.

.. code-block:: console

    $ docker pull docker.cloudsmith.io/isc/docker/kea-dhcp6


4. Create a container out of the image. Mount the configuration volume and the
   data volume if needed.

.. code-block:: console

    $ docker create \
        --name kea-dhcp6 \
        --network ipvlan0 \
        --volume /local/kea/config:/etc/kea \
        --volume /local/kea/data:/var/lib/kea \
        docker.cloudsmith.io/isc/docker/kea-dhcp6

5. Start the docker container.

.. code-block:: console

    $ docker start kea-dhcp6

6. To stop the docker container, run:

.. code-block:: console

    $ docker stop kea-dhcp6

.. note::

    Refer to the `kea-docker readme <https://gitlab.isc.org/isc-projects/kea-docker#user-content-docker-files-for-building-kea-containers>`__ for more complex scenarios.


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

The details of :iscman:`keactrl` script usage can be found in :ref:`keactrl`.

Once Kea services are up and running, consider deploying a dashboard solution
to monitor running services. For more details, see :ref:`stork`.

.. _quick-start-direct-run:

Running the Kea Servers Directly
================================

The Kea servers can be started directly, without the need to use
:iscman:`keactrl` or ``systemctl``. To start the DHCPv4 server run the following command:

.. code-block:: console

   # kea-dhcp4 -c /path/to/your/kea4/config/file.json

Similarly, to start the DHCPv6 server, run the following command:

.. code-block:: console

   # kea-dhcp6 -c /path/to/your/kea6/config/file.json
