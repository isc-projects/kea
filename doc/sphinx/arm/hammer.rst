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

Hammer is able to set up various operating systems running either in LXC
or in VirtualBox. For a list of supported systems, use the
``supported-systems`` command:

.. code-block:: console

   $ ./hammer.py supported-systems
   fedora:
     - 27: lxc, virtualbox
     - 28: lxc, virtualbox
     - 29: lxc, virtualbox
   centos:
     - 7: lxc, virtualbox
   rhel:
     - 8: virtualbox
   ubuntu:
     - 16.04: lxc, virtualbox
     - 18.04: lxc, virtualbox
     - 18.10: lxc, virtualbox
   debian:
     - 8: lxc, virtualbox
     - 9: lxc, virtualbox
   freebsd:
     - 11.2: virtualbox
     - 12.0: virtualbox

It is also possible to run the build locally, in the current system (if the OS
is supported).

First, the Hammer dependencies must be installed: Vagrant
and either VirtualBox or LXC. Hammer can install
Vagrant and the required Vagrant plugins using the command:

.. code-block:: console

   $ ./hammer.py ensure-hammer-deps

VirtualBox and LXC must be installed manually.

The basic functions provided by Hammer are to prepare the build environment
and perform the actual build, and to run the unit tests locally in the current
system. This can be achieved by running the command:

.. code-block:: console

   $ ./hammer.py build -p local

The scope of the process can be defined using the ``--with`` (``-w``) and ``--without``
(``-x``) options. By default, the ``build`` command builds Kea with
documentation, installs it locally, and runs unit tests.

To exclude the installation and generation of docs, type:

.. code-block:: console

   $ ./hammer.py build -p local -x install docs

The basic scope can be extended by mysql, pgsql, cql, native-pkg,
radius, shell, and forge.

.. note::

   If building Kea locally, Hammer dependencies like Vagrant are
   not needed.

Hammer can be told to set up a new virtual machine with a specified
operating system, without the build:

.. code-block:: console

   $ ./hammer.py prepare-system -p virtualbox -s freebsd -r 12.0

This way, a system can be prepared for our own use. To get to such a system
using SSH, invoke:

.. code-block:: console

   $ ./hammer.py ssh -p virtualbox -s freebsd -r 12.0

It is possible to speed up subsequent Hammer builds via
`ccache <https://ccache.samba.org/>`__. During
compilation, ccache stores objects in a shared folder. In subsequent runs,
instead of doing an actual compilation, ccache returns the stored earlier
objects. The cache with these objects for reuse must be stored outside of VM
or LXC. To indicate the folder, the ``--ccache-dir``
parameter for Hammer must be included. In the indicated folder, there are separate stored objects for each target
operating system.

.. code-block:: console

   $ ./hammer.py build -p lxc -s ubuntu -r 18.04 --ccache-dir ~/kea-ccache

.. note::

   ccache is currently only supported for LXC in Hammer; support
   for VirtualBox may be added later.

For more information check:

.. code-block:: console

   $ ./hammer.py --help
