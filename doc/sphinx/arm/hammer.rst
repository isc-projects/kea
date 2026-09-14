.. _hammer:

Hammer Building Tool
====================

Hammer is a Python 3 script that lets users automate tasks related to building
Kea, such as setting up virtual machines, installing Kea dependencies,
compiling Kea with various options, running unit-tests and more. This
tool was created primarily for internal QA purposes at ISC and it is not
included in the Kea distribution; however, it is available in the Kea
git repository. This tool was developed primarily for internal purposes
and ISC cannot guarantee its proper operation. Administrators who decide to use it
should do so with care.

.. note::

   Use of this tool is completely optional. Everything it does can be
   done manually.

The first-time user is strongly encouraged to look at Hammer's built-in
help:

.. code-block:: console

   $ ./hammer.py --help

It will list available parameters.

Hammer is able to set up various operating systems.
For a list of supported systems, use the ``supported-systems`` command:

.. code-block:: console

    $ ./hammer.py supported-systems
    alpine:
      - 3.21
      - 3.22
      - 3.23
      - 3.24
    debian:
      - 12
      - 13
    fedora:
      - 44
    freebsd:
      - 15
    rhel:
      - 8
      - 9
      - 10
    rocky:
      - 9
      - 10
    ubuntu:
      - 22.04
      - 24.04
      - 26.04

It is also possible to run the build locally, in the current system (if the OS
is supported).

The basic functions provided by Hammer are to prepare the build environment
and perform the actual build, and to run the unit tests locally in the current
system. This can be achieved by running the command:

.. code-block:: console

   $ ./hammer.py build

The scope of the process can be defined using the ``--with`` (``-w``) and ``--without``
(``-x``) options. By default, the ``build`` command builds Kea with
documentation, installs it locally, and runs unit tests.

To exclude the installation and generation of docs, type:

.. code-block:: console

   $ ./hammer.py build -x install docs

The basic scope can be extended by mysql, pgsql, native-pkg, shell, and forge.
Please refer to ``./hammer.py build --help`` for more details.

It is possible to speed up subsequent Hammer builds via
`ccache <https://ccache.samba.org/>`__. During
compilation, ccache stores objects in a shared folder. In subsequent runs,
instead of doing an actual compilation, ccache returns the stored earlier
objects. To indicate the folder, the ``--ccache-dir`` parameter for Hammer must be included.
In the indicated folder, there are separate stored objects for each target operating system.

.. code-block:: console

   $ ./hammer.py build --ccache-dir ~/kea-ccache

For more information check:

.. code-block:: console

   $ ./hammer.py --help
