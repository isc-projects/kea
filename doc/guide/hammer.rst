.. _hammer:

Hammer Building Tool
====================

An optionl building tool called Hammer was introduced with Kea 1.6.0. It
is a Python 3 script that lets users automate tasks related to building
Kea, such as setting up virtual machines, installing Kea dependencies,
compiling Kea with various options, running unit-tests and more. This
tool was created primarily for internal QA purposes at ISC and it is not
included in the Kea distribution. However, it is available in the Kea
git repository. This tool was developed primarily for internal purpose
and ISC cannot guarantee its proper operation. If you decide to use it,
please do so with care.

   **Note**

   Use of this tool is completely optional. Everything it does can be
   done manually.

The first time user is strongly encouraged to look at Hammer's built in
help:

::

   ./hammer.py --help

It will list available parameters.

Hammer is able to set up various operating systems running eiter in LXC
or in VirtualBox. To list of supported systems, use
``supported-systems`` command:

::

   $./hammer.py supported-systems
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
       

It is also possible to run build locally, in current system (if the OS
is supported).

At first it is required to install Hammer dependencies which is Vagrant
and either VirtualBox or LXC. To make life easier Hammer can install
Vagrant and required Vagrant plugins using the command:

::

   ./hammer.py ensure-hammer-deps

VirtualBox and LXC need to be installed manually.

Basic functionality provided by Hammer is preparing building environment
and performing actual build and running unit tests locally, in current
system. This can be achieved by running the command:

::

   ./hammer.py build -p local

The scope of the process can be defined using --with (-w) and --without
(-x) options. By default the build command will build Kea with
documentation, install it locally and run unit tests.

To exclude installation and generating docs do:

::

   ./hammer.py build -p local -x install docs

The basic scope can be extended by: mysql, pgsql, cql, native-pkg,
radius, shell, forge.

   **Note**

   For build Kea locally installing Hammer dependencies like Vagrant is
   not needed.

Hammer can be told to set up a new virtual machine with specified
operating system and not running the build:

::

   ./hammer.py prepare-system -p virtualbox -s freebsd -r 12.0

This way we can prepare a system for our own use. To get to such system
using SSH invoke:

::

   ./hammer.py ssh -p virtualbox -s freebsd -r 12.0

It is possible to speed up subsequent Hammer builds. To achieve this
Hammer employs `ccache <https://ccache.samba.org/>`__. During
compilation ccache stores object to shared folder. In subsequent runs
instead doing actuall compilation ccache just returns stored earlier
objects. Cache with objects for reuse needs to be stored outside of VM
or LXC. To indicate such folder Hammer requires providing --ccache-dir
parameter. In indicated folder there are stored objects for each target
operating system separatelly.

::

         ./hammer.py build -p lxc -s ubuntu -r 18.04 --ccache-dir ~/kea-ccache
       

..

   **Note**

   For now ccache is only supported for LXC provider in Hammer. Support
   for VirtualBox will be added later.

For more information check:

::

   ./hammer.py --help
