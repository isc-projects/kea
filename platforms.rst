.. _platforms:

Supported Platforms
===================

In general, this version of Kea builds and runs on any POSIX-compliant
system with a C++ compiler (with C++11 support), the Botan cryptographic library,
the log4cplus logging library and the Boost system library.

The Kea build has been checked with GCC g++ 4.8.5 and some later versions,
and Clang 800.0.38 and some later versions.

ISC regularly tests Kea on many operating systems and architectures, but
lacks the resources to test all of them. Consequently, ISC is only able to
offer support on a "best-effort" basis for some.

Regularly Tested Platforms
--------------------------

Kea is officially supported on Alpine, CentOS, Fedora, Ubuntu, Debian,
and FreeBSD systems. Kea-|release| builds have been tested on:

* Alpine — 3.13, 3.14, 3.15, 3.16
* CentOS — 7
* Debian — 9, 10, 11
* Fedora — 34, 35, 36
* FreeBSD — 12, 13
* RHEL — 8, 9
* Ubuntu — 18.04, 20.04, 22.04

There are currently no plans to port Kea to Windows systems.

Best-Effort
-----------

The following are platforms on which Kea is known to build and run.
ISC makes every effort to fix bugs on these platforms, but may be unable to
do so quickly due to lack of hardware, less familiarity on the part of
engineering staff, and other constraints.

* FreeBSD — 11
* macOS — 10.15, 11, 12

Community-Maintained
--------------------

These systems may not all have the required dependencies for building Kea
easily available, although it is possible in many cases to compile
those directly from source. The community and interested parties may wish
to help with maintenance, and we welcome patch contributions, although we
cannot guarantee that we will accept them. All contributions are
assessed against the risk of adverse effect on officially supported
platforms.

These include platforms past their respective EOL dates, such as:

* Alpine — 3.10 (1 May 2021), 3.11, 3.12
* CentOS — 6 (30 November 2020), 8 (31 December 2021)
* Debian — 8 (30 June 2020)
* Fedora — 31, 32, 33
* FreeBSD — 10 (31 October 2018)
* macOS — 10.13, 10.14
* Ubuntu — 14.04, 18.10, 19.04, 19.10, 21.04

Unsupported Platforms
---------------------

These are platforms on which versions of Kea since 1.7 are known *not* to build or run:

* Windows (all versions)
* Windows Server (all versions)
* Any platform with OpenSSL 1.0.1 or earlier, which does not also have Botan as an alternative
* Any platform with log4cplus version 1.0.2 or earlier.

.. _required-software:

Required Software at Runtime
============================

Kea uses various extra software packages which may not be
provided in the default installation of some operating systems, nor in
the standard package collections. This required software may need to
be installed separately. (For the build requirements, also see :ref:`build-requirements`.)

-  Kea supports two cryptographic libraries: Botan and OpenSSL. Only one
   of them is required to be installed during compilation. Kea uses the
   Botan library for C++ (https://botan.randombit.net/), version 2.0 or
   later; support for Botan versions earlier than 2.0 was
   removed as of Kea 1.7.0. As an alternative to Botan, Kea can
   use the OpenSSL cryptographic library (https://www.openssl.org/),
   version 1.0.2 or later.

-  Kea uses the log4cplus C++ logging library
   (https://sourceforge.net/p/log4cplus/wiki/Home/). It requires log4cplus version
   1.0.3 or later.

-  Kea requires the Boost system library (https://www.boost.org/).
   Building with the header-only version of Boost is no longer
   recommended.

Some optional features of Kea have additional dependencies.

-  To store lease information in a MySQL database, Kea requires
   MySQL headers and libraries. This is an optional dependency;
   Kea can be built without MySQL support.

-  To store lease information in a PostgreSQL database, Kea
   requires PostgreSQL headers and libraries. This is an optional
   dependency; Kea can be built without PostgreSQL support.

-  Integration with RADIUS is provided in Kea via the hook library
   available to ISC's paid support customers. Use of this library requires
   the FreeRADIUS-client library to be present on the system where Kea
   is running. This is an optional dependency; Kea can be built
   without RADIUS support.

-  Kea provides a NETCONF interface with the ``kea-netconf`` agent. This Kea module
   requires Sysrepo software when used. Building Kea with NETCONF support
   requires many dependencies to be installed, which are described in more
   detail in :ref:`netconf-install`. This is an optional dependency; Kea can be
   built without NETCONF support.

-  To sign and verify DNS updates the Kea DDNS server may use GSS-TSIG, which requires
   MIT Kerberos 5 or Heimdal libraries. The dependencies required to be
   installed are described in more detail in :ref:`gss-tsig-install`. This is an
   optional dependency; Kea can be built without GSS-TSIG support.
