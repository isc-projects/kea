.. _quickstart:

***********
Quick Start
***********

This section describes the basic steps needed to get Kea up and running.
For further details, full customizations, and troubleshooting, see the
respective chapters in the Kea Administrator Reference Manual (ARM).

.. _quick-start:

Quick Start Guide for DHCPv4 and DHCPv6 Services
================================================

1.  Install required run-time and build dependencies. See
    :ref:`build-requirements` for details.

2.  Download the Kea source tarball from the :ref:`ISC.org downloads
    page <https://www.isc.org/download/>` or the :ref:`ISC FTP
    server <ftp://ftp.isc.org/isc/kea/>`.

3.  Extract the tarball. For example:

    ::

       $ tar xvzf kea-KEAVERSION.tar.gz

4.  Go into the source directory and run the configure script:

    ::

       $ cd kea-KEAVERSION
       $ ./configure [your extra parameters]

5.  Build it:

    ::

       $ make

6.  Install it (by default it will be placed in ``/usr/local/``, so it
    is likely that you will need root privileges for this step):

    ::

       # make install

7.  Edit the Kea configuration files which by default are installed in
    the ``[kea-install-dir]/etc/kea/`` directory. These are:
    ``kea-dhcp4.conf``, ``kea-dhcp6.conf``, ``kea-dhcp-ddns.conf`` and
    ``kea-ctrl-agent.conf``, for DHCPv4 server, DHCPv6 server, D2, and
    Control Agent, respectively.

8.  In order to start the DHCPv4 server in the background, run the
    following command (as root):

    ::

       # keactrl start -s dhcp4

    Or run the following command to start the DHCPv6 server instead:

    ::

       # keactrl start -s dhcp6

    Note that it is also possible to start all servers simultaneously:

    ::

       $ keactrl start

9.  Verify that the Kea server(s) is/are running:

    ::

       # keactrl status

    A server status of "inactive" may indicate a configuration error.
    Please check the log file (by default named
    ``[kea-install-dir]/var/kea/kea-dhcp4.log``,
    ``[kea-install-dir]/var/kea/kea-dhcp6.log``,
    ``[kea-install-dir]/var/kea/kea-ddns.log`` or
    ``[kea-install-dir]/var/kea/kea-ctrl-agent.log``) for the details of
    the error.

10. If the server has been started successfully, test that it is
    responding to DHCP queries and that the client receives a
    configuration from the server; for example, use the :ref:`ISC DHCP
    client <https://www.isc.org/download/>`.

11. Stop running the server(s):

    ::

       # keactrl stop

For instructions specific to your system, please read the
:ref:`system-specific notes <https://kb.isc.org/docs/installing-kea>`,
available in the :ref:`Kea section of ISC's
Knowledgebase <https://kb.isc.org/docs>`.

The details of ``keactrl`` script usage can be found in
:ref:`keactrl`.

.. _quick-start-direct-run:

Running the Kea Servers Directly
================================

The Kea servers can be started directly, without the need to use
``keactrl``. To start the DHCPv4 server run the following command:

::

   # kea-dhcp4 -c /path/to/your/kea4/config/file.json

Similarly, to start the DHCPv6 server run the following command:

::

   # kea-dhcp6 -c /path/to/your/kea6/config/file.json
