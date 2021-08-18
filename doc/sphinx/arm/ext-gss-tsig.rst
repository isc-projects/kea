.. _gss-tsig:

****************
GSS-TSIG Support
****************

.. _gss-tsig-overview:

GSS-TSIG Overview
=================

Kea provides in a premium hook the support of GSS-TSIG to protect DNS
updates sent by the Kea DHCP-DDNS (aka D2) server.

GSS-TSIG uses a GSS-API for Kerberos 5 with SPENO library such as
the MIT Kerberos 5 or the Heimdal libraries.

.. note:

    This is a work in progress.

.. _gss-tsig-install:

Installing GSS-TSIG
===================

This is a page explaining how to install Kea with GSS-TSIG support.

This procedure was tested on Ubuntu 20.10 and 21.04:

1.  Get the kea sources, this will do the trick extracting to ``kea/``
    directory:

.. code-block:: console

    $ git clone https://gitlab.isc.org/isc-projects/kea.git

2.  Get the premium sources - go to
    https://gitlab.isc.org/isc-external/kea-gss-tsig and click download
    or clone from there, using either https or git. Using git requires
    setting up SSH keys which you can do on your own in your
    `gitlab preferences <https://gitlab.isc.org/-/profile/keys>`__.
    Extract to ``kea/premium/`` directory.

3. Run autoreconf:

.. code-block:: console

    autoreconf -i

4. Make sure ``./configure --help`` shows the ``--with-gssapi`` option.

5. Install either MIT (``libkrb5-dev``) or Heimdal (``heimdal-dev``) library,
   for instance:

.. code-block:: console

    sudo apt install libkrb5-dev

6. Run configure with the ``--with-gssapi`` option:

.. code-block:: console

    ./configure --with-gssapi

.. note:

    It is ``--with-gssapi`` (without dash between gss and api) to keep
    consistency with BIND 9 option.

The ``--with-gssapi`` requires ``krb5-config`` tool to be present. This
tool is provided by both MIT Kerberos 5 and Heimdal, on some systems
where both Kerberos 5 and Heimdal are installed it is a symbolic link
to one of them. If it's not in your standard location, you may specify
it with ``--with-gssapi=/path/to/krb5-config``. Since this is an early
prototype, it is strongly recommended to use default installation
locations as provided by packages.

The ``./configure`` script should complete with a successful GSS-API
detection, similar to this:

::

    GSS-API support:
      GSSAPI_CFLAGS:         -isystem /usr/include/mit-krb5
      GSSAPI_LIBS:           -L/usr/lib/x86_64-linux-gnu/mit-krb5 -Wl,-Bsymbolic-functions -Wl,-z,relro -lgssapi_krb5 -lkrb5 -lk5crypto -lcom_err

7.  Compile as usual ``make -jX`` where X is the number of CPU cores
    available.

8.  After compilation, the gss_tsig hook is available in the
    ``premium/src/hooks/d2/gss_tsig`` directory.
    It can be loaded by the D2.

The gss_tsig was developed using the MIT Kerberos 5 implementation but
Heimdal is supported too. Note that Heimdal is picky about security
sensitive file permissions but emits an unclear error message. Anyway
it is a good idea to keep these files as plain, with one link and and
no access for the group or other users.

The krb5-config script should provide an ``--all`` option which
identifies the implementation: in any report about the GSS-TSIG report
please add the result of the ``--all`` option of the krb5-config used
to configure Kea.

.. _gss-tsig-using:

Using GSS-TSIG
==============

To be done.
