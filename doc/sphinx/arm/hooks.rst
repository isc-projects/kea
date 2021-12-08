.. _hooks-libraries:

***************
Hooks Libraries
***************

.. _hooks-libraries-introduction:

Introduction
============

Kea is both flexible and customizable, via the use of "hooks." This feature
lets Kea load one or more
dynamically linked libraries (known as "hooks libraries") and, at
various points in its processing ("hook points"), call functions in
them. Those functions perform whatever custom processing is required.

The hooks concept allows the core Kea code to remain reasonably small
by moving features to external libraries that some, but not all, users
find useful. Those with no need for specific functions can simply choose not
to load the libraries.

Hooks libraries are loaded by individual Kea processes, not by Kea as a
whole. This means, among other things, that it is possible to associate one set
of libraries with the DHCP4 server and a different set with the DHCP6
server.

Another point to note is that it is possible for a process to load
multiple libraries. When processing reaches a hook point, Kea calls the
hooks library functions attached to it. If multiple libraries have
attached a function to a given hook point, Kea calls all of them, in the
order in which the libraries are specified in the configuration file.
The order may be important; consult the documentation of the libraries
for specifics.

When a Kea process unloads a library, it expects the ``dlclose`` function
removes all library symbols and removes the library code from address space
on the last reference. This behavior is not required by the POSIX standard
and at least the musl library used by default by Alpine Linux implements
the ``dlclose`` function as a no operation. On such systems a library
is loaded forever in a process, for instance it is not possible to
replace a library binary by another version using configuration change
or reload: the process must be stopped and relaunched.

The next section describes how to configure hooks libraries. Users who are
interested in writing their own hooks library can find information
in the `Hooks Developer's Guide section of the Kea Developer's
Guide <https://reports.kea.isc.org/dev_guide/df/d46/hooksdgDevelopersGuide.html>`__.

Note that some libraries are available under different licenses.

Please also note that some libraries may require additional dependencies and/or
compilation switches to be enabled, e.g. the RADIUS library introduced in
Kea 1.4 requires the FreeRadius-client library to be present. If
--with-freeradius option is not specified, the RADIUS library will not
be built.

Installing Hook Packages
========================

.. note::

   For more details about installing the Kea Premium Hooks package, please read
   `this Knowledge Base article <https://kb.isc.org/docs/aa-01587>`__.

Some hook packages are included in the base Kea sources. There is no
need to do anything special to compile or install them, as they are covered
by the usual building and installation procedures. Please
refer to :ref:`installation` for a general overview of the installation process.

ISC provides several additional premium hooks in the form of packages, which
follow a similar installation procedure but with several additional steps.
For our users' convenience, the premium hooks installation procedure is described in this section.

1. Download the package; detailed instructions are provided separately on how
to get it. The package will be a file with a name similar to
kea-premium-|release|.tar.gz. (The name may vary depending on the package
purchased.)

2. Administrators who still have the sources for the corresponding version of the
open-source Kea package still on their system from the initial Kea installation
should skip this step. Otherwise, extract the Kea source from the original
tarball that was downloaded. For example, with a download of Kea |release|.,
there should be a tarball called kea-|release|.tar.gz on the system.
Unpack this tarball:

.. parsed-literal::

   $ tar -zxvf kea-|release|.tar.gz

This will unpack the tarball into the kea-|release| subdirectory of
the current working directory.

3. Unpack the Kea premium tarball into the directory into which Kea was
unpacked. Once Kea |release| has been unpacked into a kea-|release|
subdirectory and the Kea premium tarball is in the current directory, the following
steps will unpack the premium tarball into the correct location:

.. parsed-literal::

     $ cd kea-|release|
     $ tar -xvf ../kea-premium-|release|.tar.gz

Note that unpacking the Kea premium package will put the files into a
directory named "premium". Regardless of the name of the package, the
directory will always be called "premium", although its contents will vary
depending on the premium package.

4. Run ``autoreconf`` tools. This step is necessary to update Kea's build
script to include the additional directory. If this tool is not already
available on the system, install the ``automake`` and ``autoconf``
tools. To generate the configure script, please use:

::

     $ autoreconf -i

5. Rerun configure, using the same configure options that were used when
originally building Kea. It is possible to verify that configure has detected the
premium package by inspecting the summary printed when it exits. The
first section of the output should look something like this:

.. parsed-literal::

   Package:
     Name:             kea
     Version:          |release|
     Extended version: |release| (tarball)
     OS Family:        Linux
     Using GNU sed:    yes
     Premium package:  yes
     Included Hooks:   forensic_log flex_id host_cmds subnet_cmds radius host_cache class_cmds cb_cmds lease_query

The last line indicates which specific hooks were detected. Note that
some hooks may require their own dedicated switches, e.g. the RADIUS hook
requires extra switches for FreeRADIUS. Please consult later sections of
this chapter for details.

6. Rebuild Kea.

::

     $ make

If the machine has multiple CPU cores, an interesting option to consider
here is using the argument -j X, where X is the number of available cores.

7. Install Kea sources along with the hooks:

::

   $ sudo make install

Note that as part of the installation procedure, the install script will
eventually venture into the premium/ directory and will install additional
hook libraries and associated files.

The installation location of the hooks libraries depends on whether the
--prefix parameter was specified in the configure script. If not,
the default location will be /usr/local/lib/kea/hooks. The proper installation
of the libraries can be verified with this command:

::

   $ ls -l /usr/local/lib/kea/hooks/*.so
   /usr/local/lib/kea/hooks/libdhcp_class_cmds.so
   /usr/local/lib/kea/hooks/libdhcp_flex_id.so
   /usr/local/lib/kea/hooks/libdhcp_flex_option.so
   /usr/local/lib/kea/hooks/libdhcp_host_cmds.so
   /usr/local/lib/kea/hooks/libdhcp_lease_cmds.so
   /usr/local/lib/kea/hooks/libdhcp_legal_log.so
   /usr/local/lib/kea/hooks/libdhcp_subnet_cmds.so

The exact list returned will depend on the packages installed. If the
directory was specified via --prefix, the hooks libraries will be located in
{prefix directory}/lib/kea/hooks.

Configuring Hooks Libraries
===========================

The hooks libraries for a given process are configured using the
``hooks-libraries`` keyword in the configuration for that process. (Note
that the word "hooks" is plural.) The value of the keyword is an array
of map structures, with each structure corresponding to a hooks library. For
example, to set up two hooks libraries for the DHCPv4 server, the
configuration would be:

::

   "Dhcp4": {
       :
       "hooks-libraries": [
           {
               "library": "/opt/charging.so"
           },
           {
               "library": "/opt/local/notification.so",
               "parameters": {
                   "mail": "spam@example.com",
                   "floor": 13,
                   "debug": false,
                   "users": [ "alice", "bob", "charlie" ],
                   "languages": {
                       "french": "bonjour",
                       "klingon": "yl'el"
                   }
               }
           }
       ]
       :
   }

..

.. note::

   This syntax is effective as of Kea 1.1.0, to facilitate the
   specification of library-specific parameters. Libraries should allow a
   parameter entry for comments, as is the case with many configuration
   scopes.

..

.. note::

   In all versions of Kea since 1.1.0, libraries
   are reloaded even if their lists have not changed,
   because the parameters specified for the library (or the files those
   parameters point to) may have changed.

Libraries may have additional parameters that are not mandatory, in the
sense that there may be libraries that do not require them. However, for a
specific library there is often a specific requirement to specify a certain
set of parameters. Please consult the documentation for each individual library for
details. In the example above, the first library has no parameters. The
second library has five parameters: specifying mail (string parameter),
floor (integer parameter), debug (boolean parameter), lists
(list of strings), and maps (containing strings). Nested parameters can
be used if the library supports it. This topic is explained in detail in
the `Hooks Developer's Guide section of the Kea Developer's Guide
<https://reports.kea.isc.org/dev_guide/df/d46/hooksdgDevelopersGuide.html>`__.

Notes:

-  The full path to each library should be given.

-  As noted above, the order in which the hooks are called may be important;
   consult the documentation for each library for specifics.

-  An empty list has the same effect as omitting the ``hooks-libraries``
   configuration element altogether.

   .. note::

      There is one case where this is not true: if Kea is running with a
      configuration that contains a ``hooks-libraries`` item, and that
      item is removed and the configuration reloaded, the removal will
      be ignored and the libraries remain loaded. As a workaround,
      instead of removing the ``hooks-libraries`` item, change it to an
      empty list. This will be fixed in a future version of Kea.

At the present time, only the kea-dhcp4 and kea-dhcp6 processes support
hooks libraries.

Available Hooks Libraries
=========================

As described above, the hooks functionality provides a way to customize
a Kea server without modifying the core code. ISC has chosen to take
advantage of this feature to provide functions that may only be useful
to a subset of Kea users. To this end, ISC has created some hooks
libraries, discussed in the following sections.

.. note::

   Some of these libraries are available with the base code, while
   others will be shared with organizations supporting development of
   Kea. Users who would like to get access to those premium
   libraries should consider purchasing a support contract from ISC. This
   includes professional support, advance security notifications, input
   into ISC's roadmap planning, and many other benefits, while helping
   make Kea sustainable in the long term.

The following table provides a list of libraries currently available
from ISC. It is important to pay attention to which libraries may be
loaded by which Kea processes. It is a common mistake to configure the
``kea-ctrl-agent`` process to load libraries that should, in fact, be
loaded by the ``kea-dhcp4`` or ``kea-dhcp6`` processes. If a library
from ISC does not work as expected, please make sure that it has been
loaded by the correct process per the table below.

.. warning::

   While the Kea Control Agent includes the "hooks" functionality, (i.e.
   hooks libraries can be loaded by this process), none of ISC's current
   hooks libraries should be loaded by the Control Agent.

.. tabularcolumns:: |p{0.1\linewidth}|p{0.1\linewidth}|p{0.8\linewidth}|

.. table:: List of Available Hooks Libraries
   :class: longtable
   :widths: 10 10 80

   +-----------------+---------------+------------------------------------------------------------+
   | Name            | Availability  | Description                                                |
   +=================+===============+============================================================+
   | User Check      | Kea sources   |Reads known users list from a file. Unknown users will be   |
   |                 | (since 0.8)   |assigned a lease from the last subnet defined in the        |
   |                 |               |configuration file, e.g. to redirect them to a captive      |
   |                 |               |portal. This demonstrates how an external source of         |
   |                 |               |information can be used to influence the Kea allocation     |
   |                 |               |engine. This hook is part of the Kea source code and is     |
   |                 |               |available in the src/hooks/dhcp/user_chk directory.         |
   +-----------------+---------------+------------------------------------------------------------+
   | Forensic        | Support       |This library provides hooks that record a detailed log of   |
   | Logging         | customers     |lease assignments and renewals into a set of log files. In  |
   |                 | (since 1.1)   |many legal jurisdictions companies, especially ISPs, must   |
   |                 |               |record information about the addresses they have leased to  |
   |                 |               |DHCP clients. This library is designed to help with that    |
   |                 |               |requirement. If the information that it records is          |
   |                 |               |sufficient it may be used directly. If your jurisdiction    |
   |                 |               |requires that you save a different set of information, you  |
   |                 |               |may use it as a template or example and create your own     |
   |                 |               |custom logging hooks. In Kea 1.9.8 additional parameters    |
   |                 |               |have been added to give users more flexibility regarding    |
   |                 |               |what information should be logged.                          |
   +-----------------+---------------+------------------------------------------------------------+
   | Flexible        | Support       |Kea software provides a way to handle host reservations that|
   | Identifier      | customers     |include addresses, prefixes, options, client classes and    |
   |                 | (since 1.2)   |other features. The reservation can be based on hardware    |
   |                 |               |address, DUID, circuit-id or client-id in DHCPv4 and using  |
   |                 |               |hardware address or DUID in DHCPv6. However, there are      |
   |                 |               |sometimes scenarios where the reservation is more complex,  |
   |                 |               |e.g. uses other options that mentioned above, uses part of  |
   |                 |               |specific options or perhaps even a combination of several   |
   |                 |               |options and fields to uniquely identify a client. Those     |
   |                 |               |scenarios are addressed by the Flexible Identifiers hook    |
   |                 |               |application. It allows defining an expression, similar to   |
   |                 |               |the one used in client classification,                      |
   |                 |               |e.g. substring(relay6[0].option[37],0,6). Each incoming     |
   |                 |               |packet is evaluated against that expression and its value is|
   |                 |               |then searched in the reservations database.                 |
   +-----------------+---------------+------------------------------------------------------------+
   | Flexible        | Kea sources   |This library provides hooks that compute option values      |
   | Option          | (since 1.7.1) |instead of static configured values. An expression is       |
   |                 |               |evaluated on the query packet. Defined add, supersede and   |
   |                 |               |remove actions are applied on the response packet before    |
   |                 |               |it is sent using the evaluation result.                     |
   +-----------------+---------------+------------------------------------------------------------+
   | Host Commands   | Support       |Kea provides a way to store host reservations in a          |
   |                 | customers     |database. In many larger deployments it is useful to be able|
   |                 | (since 1.2)   |to manage that information while the server is running. This|
   |                 |               |library provides management commands for adding, querying   |
   |                 |               |and deleting host reservations in a safe way without        |
   |                 |               |restarting the server.  In particular, it validates the     |
   |                 |               |parameters, so an attempt to insert incorrect data, e.g. add|
   |                 |               |a host with conflicting identifier in the same subnet will  |
   |                 |               |be rejected. Those commands are exposed via command channel |
   |                 |               |(JSON over unix sockets) and Control Agent (JSON over       |
   |                 |               |RESTful interface). Additional commands and capabilities    |
   |                 |               |related to host reservations will be added in the future.   |
   +-----------------+---------------+------------------------------------------------------------+
   | Subnet Commands | Support       |In deployments in which subnet configuration needs to be    |
   |                 | customers     |frequently updated, it is a hard requirement that such      |
   |                 | (since 1.3)   |updates be performed without the need for a full DHCP server|
   |                 |               |reconfiguration or restart. This hooks library allows for   |
   |                 |               |incremental changes to the subnet configuration such as:    |
   |                 |               |adding a subnet, removing a subnet. It also allows for      |
   |                 |               |listing all available subnets and fetching detailed         |
   |                 |               |information about a selected subnet. The commands exposed by|
   |                 |               |this library do not affect other subnets or configuration   |
   |                 |               |parameters currently used by the server.                    |
   +-----------------+---------------+------------------------------------------------------------+
   | Lease Commands  | Kea sources   |The lease commands hook library offers a number of new      |
   |                 | (since 1.3)   |commands used to manage leases. Kea provides a way to store |
   |                 |               |lease information in various backends: memfile, MySQL,      |
   |                 |               |PostgreSQL and Cassandra. This library provides a unified   |
   |                 |               |interface that can manipulate leases in an unified, safe    |
   |                 |               |way. In particular, it allows: manipulate leases in memfile |
   |                 |               |while Kea is running, sanity check changes, check lease     |
   |                 |               |existence and remove all leases belonging to specific       |
   |                 |               |subnet. It can also catch more obscure errors, like adding a|
   |                 |               |lease with subnet-id that does not exist in the             |
   |                 |               |configuration or configuring a lease to use an address that |
   |                 |               |is outside of the subnet to which it is supposed to belong. |
   |                 |               |It provides a way to manage user contexts associated with   |
   |                 |               |leases.                                                     |
   +-----------------+---------------+------------------------------------------------------------+
   | High            | Kea sources   |Minimizing a risk of DHCP service unavailability is achieved|
   | Availability    | (since 1.4)   |by setting up a pair of the DHCP servers in a network.  Two |
   |                 |               |modes of operation are supported. The first one is called   |
   |                 |               |load balancing and is sometimes referred to as              |
   |                 |               |active-active. Each server can handle selected groups of    |
   |                 |               |clients in this network or all clients, if it detects that  |
   |                 |               |its partner has become unavailable. It is also possible to  |
   |                 |               |designate one server to serve all DHCP clients, and leave   |
   |                 |               |another server as "standby". This mode is called hot standby|
   |                 |               |and is sometimes referred to as active-passive. This        |
   |                 |               |server will activate its DHCP function when it detects that |
   |                 |               |its partner is not available.  Such cooperation between the |
   |                 |               |DHCP servers requires that these servers constantly         |
   |                 |               |communicate with each other to send updates about allocated |
   |                 |               |leases and to periodically test whether their partners are  |
   |                 |               |still operational. The hook library also provides an ability|
   |                 |               |to send lease updates to external backup servers, making it |
   |                 |               |much easier to have a replacement that is almost up to      |
   |                 |               |date. The "libdhcp_ha" library provides such functionality  |
   |                 |               |for Kea DHCP servers.                                       |
   +-----------------+---------------+------------------------------------------------------------+
   | Statistics      | Kea sources   |The Statistics Commands library provides additional         |
   | Commands        | (since 1.4)   |commands for retrieving accurate DHCP lease statistics for  |
   |                 |               |Kea DHCP servers that share the same lease database. This   |
   |                 |               |setup is common in deployments where DHCP service redundancy|
   |                 |               |is required and a shared lease database is used to avoid    |
   |                 |               |lease data replication between the DHCP servers. A feature  |
   |                 |               |was introduced in Kea 1.4.0 that allows tracking lease      |
   |                 |               |allocations within the lease database, thus making the      |
   |                 |               |statistics accessible to all connected DHCP servers. The    |
   |                 |               |Statistics Commands hooks library utilizes this feature and |
   |                 |               |returns lease statistics for all subnets respectively.      |
   +-----------------+---------------+------------------------------------------------------------+
   | RADIUS          | Support       |The RADIUS Hook library allows Kea to interact with the     |
   |                 | customers     |RADIUS servers using access and accounting mechanisms. The  |
   |                 | (since 1.4)   |access mechanism may be used for access control, assigning  |
   |                 |               |specific IPv4 or IPv6 addresses reserved by RADIUS,         |
   |                 |               |dynamically assigning addresses from designated pools chosen|
   |                 |               |by RADIUS or rejecting the client's messages altogether. The|
   |                 |               |accounting mechanism allows a RADIUS server to keep track of|
   |                 |               |device activity over time.                                  |
   +-----------------+---------------+------------------------------------------------------------+
   | Host Cache      | Support       |Some of the database backends, such as RADIUS, are          |
   |                 | customers     |considered slow and may take a long time to respond. Since  |
   |                 | (since 1.4)   |Kea in general is synchronous, the backend performance      |
   |                 |               |directly affects the DHCP performance. To minimize the      |
   |                 |               |impact and improve performance, the Host Cache library      |
   |                 |               |provides a way to cache responses from other hosts. This    |
   |                 |               |includes negative caching, i.e. the ability to remember that|
   |                 |               |there is no client information in the database.             |
   +-----------------+---------------+------------------------------------------------------------+
   | Class Commands  | Support       |This Class Cmds hooks library allows for adding, updating,  |
   |                 | customers     |deleting and fetching configured DHCP client classes without|
   |                 | (since 1.5)   |the need to restart the DHCP server.                        |
   +-----------------+---------------+------------------------------------------------------------+
   | MySQL           | Kea sources   |The MySQL CB hooks library is an implementation of the Kea  |
   | Configuration   | (since 1.6)   |Configuration Backend for MySQL. It uses a MySQL database as|
   | Backend         |               |a repository for the Kea configuration information. The Kea |
   |                 |               |servers use this library to fetch their configurations.     |
   +-----------------+---------------+------------------------------------------------------------+
   | Configuration   | Support       |The Configuration Backend Commands (CB Commands) hooks      |
   | Backend         | customers     |library implements a collection of commands to manage the   |
   | Commands        | (since 1.6)   |configuration information of the Kea servers in the         |
   |                 |               |database. This library may only be used in conjunction with |
   |                 |               |one of the supported configuration backend implementations. |
   +-----------------+---------------+------------------------------------------------------------+
   | BOOTP           | Kea sources   |The BOOTP hooks library adds BOOTP support, as defined in   |
   |                 | (since 1.7.3) |RFC 1497. It recognizes received BOOTP requests:            |
   |                 |               |they are translated into DHCPREQUEST packets, put into the  |
   |                 |               |BOOTP client class and get infinite lifetime leases.        |
   +-----------------+---------------+------------------------------------------------------------+
   | Leasequery      | Support       |The Leasequery hooks library adds support for DHCPv4        |
   |                 | customers     |Leasequery as described in RFC 4388; and for DHCPv6         |
   |                 | (DHCPv4 since |Leasequery as described in RFC 5007.                        |
   |                 | 1.7.8, DHCPv6 |                                                            |
   |                 | since 1.7.9)  |                                                            |
   +-----------------+---------------+------------------------------------------------------------+
   | Run Script      | Kea sources   |The Run Script hooks library adds support to run external   |
   |                 | (since 1.9.5) |scripts for specific packet processing hook points. There   |
   |                 |               |are several exported environment variables available for    |
   |                 |               |the script.                                                 |
   +-----------------+---------------+------------------------------------------------------------+
   | GSS-TSIG        | ISC support   |This hook library adds support to the Kea D2 server         |
   |                 | customers     |(kea-dhcp-ddns) for using GSS-TSIG to sign DNS updates.     |
   |                 | (since 2.0.1) |                                                            |
   +-----------------+---------------+------------------------------------------------------------+

ISC hopes to see more hooks libraries become available as time
progresses, developed both internally and externally. Since this list
may evolve dynamically, it is maintained on a wiki page, available
at this link:
https://gitlab.isc.org/isc-projects/kea/wikis/Hooks-available.
Developers or others who are aware of any hooks libraries not listed there
are asked to please send a note to the kea-users or kea-dev mailing lists for
updating.

The libraries developed by ISC are described in detail in the following
sections.

user_chk: Checking User Access
==============================

The user_chk library is the first hooks library published by ISC. It
serves several purposes:

-  To assign "new" or "unregistered" users to a restricted subnet, while
   "known" or "registered" users are assigned to unrestricted subnets.

-  To allow DHCP response options or vendor option values to be
   customized based on user identity.

-  To provide a real-time record of user registration activity, which
   can be sampled by an external consumer.

-  To serve as a demonstration of various capabilities possible using
   the hooks interface.

Once loaded, the library allows the separation of incoming requests into known
and unknown clients. For known clients, packets are processed
as usual, although it is possible to override the sending of certain options
on a per-host basis. Clients that are not on the known
hosts list will be treated as unknown and will be assigned to the last
subnet defined in the configuration file.

As an example of a use case, this behavior may be implemented to put unknown users
into a separate subnet that leads to a "walled garden," where they can
only access a registration portal. Once they fill in necessary data,
their details are added to the known clients file and they get a proper
address after their device is restarted.

.. note::

   This library was developed several years before the host reservation
   mechanism became available. Host reservation is much
   more powerful and flexible, but the user_chk capability
   to consult an external source of information about clients and alter
   Kea's behavior remains useful and of educational value.

The library reads the /tmp/user_chk_registry.txt file while being loaded
and each time an incoming packet is processed. Each line of the file is expected to
contain a self-contained JSON snippet which must have the
following two entries:

-  ``type`` - whose value is "HW_ADDR" for IPv4 users or "DUID" for IPv6
   users.

-  ``id`` - whose value is either the hardware address or the DUID from
   the request formatted as a string of hex digits, with or without ":"
   delimiters.

and may have zero or more of the following entries:

-  ``bootfile`` - whose value is the pathname of the desired file.

-  ``tftp_server`` - whose value is the hostname or IP address of the
   desired server.

A sample user registry file is shown below:

::

   { "type" : "HW_ADDR", "id" : "0c:0e:0a:01:ff:04", "bootfile" : "/tmp/v4bootfile" }
   { "type" : "HW_ADDR", "id" : "0c:0e:0a:01:ff:06", "tftp_server" : "tftp.v4.example.com" }
   { "type" : "DUID", "id" : "00:01:00:01:19:ef:e6:3b:00:0c:01:02:03:04", "bootfile" : "/tmp/v6bootfile" }
   { "type" : "DUID", "id" : "00:01:00:01:19:ef:e6:3b:00:0c:01:02:03:06", "tftp_server" : "tftp.v6.example.com" }

As with any other hooks libraries provided by ISC, internals of the
user_chk code are well-documented. Users may refer to the `user_chk
library section of the Kea Developer's Guide
<https://reports.kea.isc.org/dev_guide/d8/db2/libdhcp_user_chk.html>`__
for information on how the code works internally. That, together with the
`Hooks Framework section of the Kea Developer's Guide
<https://reports.kea.isc.org/dev_guide/index.html#hooksFramework>`__ should give users
some pointers on how to extend this library and perhaps even write one
from scratch.

legal_log: Forensic Logging Hooks
=================================

This section describes the forensic log hooks library. This library provides
hooks that record a detailed log of assignments, renewals, releases and other
lease events into a set of log files.

Currently this library is only available to ISC customers with a paid support
contract.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or ``kea-dhcp6``
   process.

In many legal jurisdictions, companies, especially ISPs, must record
information about the addresses they have leased to DHCP clients. This
library is designed to help with that requirement. If the information
that it records is sufficient, it may be used directly.

If a jurisdiction requires that a different set of information be saved, users
may use the custom formatting capability to extract information from the inbound
request packet, or from the outbound response packet. Use with caution as this
might affect server performance.  The custom format can not be used for control
channel commands.

Alternatively, this library may be used as a template or an example for the
user's own custom logging hook. The logging is done as a set of hooks to allow
it to be customized to any particular need. Modifying a hooks library is easier
and safer than updating the core code. In addition by using the hooks features,
those users who do not need to log this information can leave it out and avoid
any performance penalties.

Log File Naming
~~~~~~~~~~~~~~~

The names for the log files have the following form:

Legal file names, if using ``day``, ``month`` or ``year`` as time unit:

::

   path/base-name.CCYYMMDD.txt

where ``CC`` represents century, ``YY`` represents current year,
``MM`` represents current month and ``DD`` represents current day.

Legal file names, if using ``second`` as time unit:

::

   path/base-name.TXXXXXXXXXXXXXXXXXXXX.txt

where ``XXXXXXXXXXXXXXXXXXXX`` represents time in seconds since epoch.

When using ``second`` as the time unit, the file will be rotated when
the ``count`` number of seconds pass. In contrast, when using ``day``, ``month``
or ``year`` as time unit, the file will be rotated whenever the ``count`` th day,
month or year starts respectively.

The ``"path"`` and ``"base-name"`` are supplied in the configuration as
described below; see :ref:`forensic-log-configuration`.

.. note::

   When running Kea servers for both DHCPv4 and DHCPv6, the log names
   must be distinct. See the examples in :ref:`forensic-log-configuration`.

.. _forensic-log-configuration:

Configuring the Forensic Log Hooks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To use this functionality, the hook library must be included in the
configuration of the desired DHCP server modules. The legal_log library
is able to save logs to a text file or to a database (created using
``kea-admin`` see :ref:`mysql-database-create`, :ref:`pgsql-database-create`).
The library is installed alongside the Kea libraries in
``[kea-install-dir]/var/lib/kea`` where ``kea-install-dir`` is determined
by the "--prefix" option of the configure script. It defaults to
``/usr/local``. Assuming the default value, configuring kea-dhcp4 to load
the legal_log library could be done with the following kea-dhcp4 configuration:

.. code-block:: json

    {
        "Dhcp4": {
            "hooks-libraries": [
                {
                    "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
                    "parameters": {
                        "path": "/var/lib/kea/log",
                        "base-name": "kea-forensic4"
                    }
                }
            ]
        }
    }

For kea-dhcp6, the configuration is:

.. code-block:: json

    {
        "Dhcp6": {
            "hooks-libraries": [
                {
                    "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
                    "parameters": {
                        "path": "/var/lib/kea/log",
                        "base-name": "kea-forensic6"
                    }
                }
            ]
        }
    }

The hook library parameters for the text file configuration are:

-  ``path`` - the directory in which the forensic file(s) will be written.
   The default value is ``[prefix]/var/lib/kea``. The directory must exist.

-  ``base-name`` - an arbitrary value which is used in conjunction with the
   current system date to form the current forensic file name. It
   defaults to ``kea-legal``.

-  ``time-unit`` - configures the time unit used to rotate the log file. Valid
   values are ``second``, ``day``, ``month`` or ``year``. It defaults to
   ``day``.

-  ``count`` - configures the number of time units that need to pass until the
   log file is rotated. It can be any positive number, or 0 which disables log
   rotate. It defaults to 1.

If log rotate is disabled, a new file will be created when the library is
loaded and the new file name is different that any previous file name.

Additional actions can be performed just before closing the old file and after
opening the new file. These actions must point to an external executable or
script and are configured by setting:

-  ``prerotate`` - external executable or script called with the name of the
   file that will be closed. Kea will not wait for the process to finish.

-  ``postrotate`` - external executable or script called with the name of the
   file that had been opened. Kea will not wait for the process to finish.

Custom formatting can be enabled for logging information that can be extracted
either from the client's request packet or from the server's response packet.
Use with caution as this might affect server performance.
The custom format can not be used for control channel commands.
Two parameters can be used towards this goal, either together or separately:

-  ``request-parser-format`` - evaluated parsed expression used to extract and
   log data from the incoming packet

-  ``response-parser-format`` - evaluated parsed expression used to extract and
   log data from the server response packet

See :ref:`classification-using-expressions` for a list of expressions.
If any of ``request-parser-format`` or ``response-parser-format`` is
configured, the default logging format is not used. If both of them are
configured, the resulting log message is constructed by concatenating the
data extracted from the request and the data extracted from the response.

Some data might be available in the request or in the response only and some
data might differ in the request packet from the one in the response packet.

The lease client context can only be printed using the default format, as this
information is not directly stored in the request packet or in the response
packet.

Additional parameters for the database connection can be specified, e.g:

.. code-block:: json

    {
      "Dhcp6": {
        "hooks-libraries": [
          {
            "library": "/usr/local/lib/kea/hooks/libdhcp_legal_log.so",
            "parameters": {
              "name": "database-name",
              "password": "passwd",
              "type": "mysql",
              "user": "user-name"
            }
          }
        ]
      }
    }

For more specific information about database related parameters please refer to
:ref:`database-configuration6` and :ref:`database-configuration4`.

If it is desired to restrict forensic logging to certain subnets, the
"legal-logging" boolean parameter can be specified within a user context
of these subnets. For example:

.. code-block:: json

    {
        "Dhcp4": {
            "subnet4": [
                {
                    "subnet": "192.0.2.0/24",
                    "pools": [
                        {
                            "pool": "192.0.2.1 - 192.0.2.200"
                        }
                    ],
                    "user-context": {
                        "legal-logging": false
                    }
                }
            ]
        }
    }

This configuration disables legal logging for the subnet "192.0.2.0/24". If the
"legal-logging" parameter is not specified, it defaults to 'true', which
enables legal logging for the subnet.

The following example demonstrates how to selectively disable legal
logging for an IPv6 subnet:

.. code-block:: json

    {
        "Dhcp6": {
            "subnet6": [
                {
                    "subnet": "2001:db8:1::/64",
                    "pools": [
                        {
                            "pool": "2001:db8:1::1-2001:db8:1::ffff"
                        }
                    ],
                    "user-context": {
                        "legal-logging": false
                    }
                }
            ]
        }
    }


See :ref:`dhcp4-user-contexts` and :ref:`dhcp6-user-contexts` to
learn more about user contexts in Kea configuration.

DHCPv4 Log Entries
~~~~~~~~~~~~~~~~~~

For DHCPv4, the library creates entries based on DHCPREQUEST, DHCPDECLINE,
DHCPRELEASE messages et.al. and their responses. The resulting packets and
leases are taken into account, intercepted through the following hook points:
* pkt4_receive
* leases4_committed
* pkt4_send
* lease4_release
* lease4_decline

An entry is a single string with no embedded end-of-line markers and a
prepended timestamp, and has the following sections:

::

   timestamp address duration device-id {client-info} {relay-info} {user-context}

Where:

-  timestamp - the current date and time the log entry was written in
   "%Y-%m-%d %H:%M:%S %Z" strftime format ("%Z" is the time zone name).

-  address - the leased IPv4 address given out and whether it was
   assigned, renewed or released.

-  duration - the lease lifetime expressed in days (if present), hours,
   minutes, and seconds. A lease lifetime of 0xFFFFFFFF will be denoted
   with the text "infinite duration". This information is not given
   when the lease is released.

-  device-id - the client's hardware address shown as numerical type and
   hex digit string.

-  client-info - the DHCP client id option (61) if present, shown as a
   hex string. When its content is printable it is displayed.

-  relay-info - for relayed packets the giaddr and the RAI circuit-id,
   remote-id, and subscriber-id options (option 82 sub options: 1, 2 and 6)
   if present. The circuit id and remote id are presented as hex
   strings. When their content is printable it is displayed.

-  user-context - the optional user context associated with the lease.

For instance (line breaks added for readability; they will not be
present in the log file):

::

   2018-01-06 01:02:03 CET Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:
   hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33,
   identified by circuit-id: 68:6f:77:64:79 (howdy) and remote-id: 87:f6:79:77:ef

or for a release:

::

   2018-01-06 01:02:03 CET Address: 192.2.1.100 has been released from a device with hardware address:
   hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33,
   identified by circuit-id: 68:6f:77:64:79 (howdy) and remote-id: 87:f6:79:77:ef

In addition to logging lease activity driven by DHCPv4 client traffic,
the hooks library also logs entries for the following lease management control
channel commands: lease4-add, lease4-update, and lease4-del. These cannot have
custom formatting. Each entry is a single string with no embedded end-of-line
markers, and it will typically have the following form:

``lease4-add:``

::

   *timestamp* Administrator added a lease of address: *address* to a device with hardware address: *device-id*

Depending on the arguments of the add command, it may also include the
client-id and duration.

Example:

::

   2018-01-06 01:02:03 CET Administrator added a lease of address: 192.0.2.202 to a device with hardware address:
   1a:1b:1c:1d:1e:1f for 1 days 0 hrs 0 mins 0 secs

``lease4-update:``

::

   *timestamp* Administrator updated information on the lease of address: *address* to a device with hardware address: *device-id*

Depending on the arguments of the update command, it may also include
the client-id and lease duration.

Example:

::

   2018-01-06 01:02:03 CET Administrator updated information on the lease of address: 192.0.2.202 to a device
   with hardware address: 1a:1b:1c:1d:1e:1f, client-id: 1234567890

``lease4-del:`` deletes have two forms, one by address and one by
identifier and identifier type:

::

   *timestamp* Administrator deleted the lease for address: *address*

or

::

   *timestamp* Administrator deleted a lease for a device identified by: *identifier-type* of *identifier*

Currently only a type of @b hw-address (hardware address) is supported.

Examples:

::

   2018-01-06 01:02:03 CET Administrator deleted the lease for address: 192.0.2.202

   2018-01-06 01:02:12 CET Administrator deleted a lease for a device identified by: hw-address of 1a:1b:1c:1d:1e:1f

The ``request-parser-format`` and ``response-parser-format`` can be used to
extract and log data from the incoming packet and server response packet
respectively. The configured value is an evaluated parsed expression returning a
string. A list of tokens is described in the server classification process.
Use with caution as this might affect server performance.
If any of them is configured, the default logging format is not used.
If both of them are configured, the resulting log message is constructed by
concatenating the logged data extracted from the request and the logged data
extracted from the response.

Some data might be available in the request or in the response only and some
data might differ in the incoming packet from the one in the response packet.

Examples:

.. code-block:: json

    {
        "request-parser-format": "ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7, 'Address: ' + ifelse(option[50].exists, addrtotext(option[50].hex), addrtotext(pkt4.ciaddr)) + ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') + ifelse(option[61].exists, ', client-id: ' + hexstring(option[61].hex, ':'), '') + ifelse(pkt4.giaddr == 0.0.0.0, '', ' connected via relay at address: ' + addrtotext(pkt4.giaddr) + ifelse(option[82].option[1].exists, ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'), '') + ifelse(option[82].option[2].exists, ', remote-id: ' + hexstring(option[82].option[2].hex, ':'), '') + ifelse(option[82].option[6].exists, ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'), '')), '')",
        "response-parser-format": "ifelse(pkt4.msgtype == 5, 'Address: ' + addrtotext(pkt4.yiaddr) + ' has been assigned for ' + uint32totext(option[51].hex) + ' seconds to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') + ifelse(option[61].exists, ', client-id: ' + hexstring(option[61].hex, ':'), '') + ifelse(pkt4.giaddr == 0.0.0.0, '', ' connected via relay at address: ' + addrtotext(pkt4.giaddr) + ifelse(option[82].option[1].exists, ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'), '') + ifelse(option[82].option[2].exists, ', remote-id: ' + hexstring(option[82].option[2].hex, ':'), '') + ifelse(option[82].option[6].exists, ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'), '')), '')"
    }

.. raw:: html

    <details><summary>Expand here!</summary>
    <pre>{
        "request-parser-format":
            "ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7,
                'Address: ' +
                ifelse(option[50].exists,
                    addrtotext(option[50].hex),
                    addrtotext(pkt4.ciaddr)) +
                ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
                ifelse(option[61].exists,
                    ', client-id: ' + hexstring(option[61].hex, ':'),
                    '') +
                ifelse(pkt4.giaddr == 0.0.0.0,
                    '',
                    ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                    ifelse(option[82].option[1].exists,
                        ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                        '') +
                    ifelse(option[82].option[2].exists,
                        ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                        '') +
                    ifelse(option[82].option[6].exists,
                        ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                        '')),
                '')",
        "response-parser-format":
            "ifelse(pkt4.msgtype == 5,
                'Address: ' + addrtotext(pkt4.yiaddr) + ' has been assigned for ' + uint32totext(option[51].hex) + ' seconds to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
                ifelse(option[61].exists,
                    ', client-id: ' + hexstring(option[61].hex, ':'),
                    '') +
                ifelse(pkt4.giaddr == 0.0.0.0,
                    '',
                    ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                    ifelse(option[82].option[1].exists,
                        ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                        '') +
                    ifelse(option[82].option[2].exists,
                        ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                        '') +
                    ifelse(option[82].option[6].exists,
                        ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                        '')),
                '')"
    }</pre>
    </details><br>


This will log the following data on request and renew:

::

   Address: 192.2.1.100 has been assigned for 6735 seconds to a device with hardware address: hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33, circuit-id: 68:6f:77:64:79, remote-id: 87:f6:79:77:ef, subscriber-id: 1a:2b:3c:4d:5e:6f


This will log the following data on release and decline:

::

   Address: 192.2.1.100 has been released from a device with hardware address: hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33, circuit-id: 68:6f:77:64:79, remote-id: 87:f6:79:77:ef, subscriber-id: 1a:2b:3c:4d:5e:6f


Similar result can be obtained if configuring ``request-parser-format`` only.

Examples:


.. code-block:: json

    {
        "request-parser-format": "ifelse(pkt4.msgtype == 3, 'Address: ' + ifelse(option[50].exists, addrtotext(option[50].hex), addrtotext(pkt4.ciaddr)) + ' has been assigned' + ifelse(option[51].exists, ' for ' + uint32totext(option[51].hex) + ' seconds', '') + ' to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') + ifelse(option[61].exists, ', client-id: ' + hexstring(option[61].hex, ':'), '') + ifelse(pkt4.giaddr == 0.0.0.0, '', ' connected via relay at address: ' + addrtotext(pkt4.giaddr) + ifelse(option[82].option[1].exists, ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'), '') + ifelse(option[82].option[2].exists, ', remote-id: ' + hexstring(option[82].option[2].hex, ':'), '') + ifelse(option[82].option[6].exists, ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'), '')), ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7, 'Address: ' + ifelse(option[50].exists, addrtotext(option[50].hex), addrtotext(pkt4.ciaddr)) + ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') + ifelse(option[61].exists, ', client-id: ' + hexstring(option[61].hex, ':'), '') + ifelse(pkt4.giaddr == 0.0.0.0, '', ' connected via relay at address: ' + addrtotext(pkt4.giaddr) + ifelse(option[82].option[1].exists, ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'), '') + ifelse(option[82].option[2].exists, ', remote-id: ' + hexstring(option[82].option[2].hex, ':'), '') + ifelse(option[82].option[6].exists, ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'), '')), ''))"
    }

.. raw:: html

    <details><summary>Expand here!</summary>
    <pre>{
        "request-parser-format":
            "ifelse(pkt4.msgtype == 3,
                'Address: ' +
                ifelse(option[50].exists,
                    addrtotext(option[50].hex),
                    addrtotext(pkt4.ciaddr)) +
                ' has been assigned' +
                ifelse(option[51].exists,
                    ' for ' + uint32totext(option[51].hex) + ' seconds',
                    '') +
                ' to a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
                ifelse(option[61].exists,
                    ', client-id: ' + hexstring(option[61].hex, ':'),
                    '') +
                ifelse(pkt4.giaddr == 0.0.0.0,
                    '',
                    ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                    ifelse(option[82].option[1].exists,
                        ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                        '') +
                    ifelse(option[82].option[2].exists,
                        ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                        '') +
                    ifelse(option[82].option[6].exists,
                        ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                        '')),
                ifelse(pkt4.msgtype == 4 or pkt4.msgtype == 7,
                    'Address: ' +
                    ifelse(option[50].exists,
                        addrtotext(option[50].hex),
                        addrtotext(pkt4.ciaddr)) +
                    ' has been released from a device with hardware address: hwtype=' + substring(hexstring(pkt4.htype, ''), 7, 1) + ' ' + hexstring(pkt4.mac, ':') +
                    ifelse(option[61].exists,
                        ', client-id: ' + hexstring(option[61].hex, ':'),
                        '') +
                    ifelse(pkt4.giaddr == 0.0.0.0,
                        '',
                        ' connected via relay at address: ' + addrtotext(pkt4.giaddr) +
                        ifelse(option[82].option[1].exists,
                            ', circuit-id: ' + hexstring(option[82].option[1].hex, ':'),
                            '') +
                        ifelse(option[82].option[2].exists,
                            ', remote-id: ' + hexstring(option[82].option[2].hex, ':'),
                            '') +
                        ifelse(option[82].option[6].exists,
                            ', subscriber-id: ' + hexstring(option[82].option[6].hex, ':'),
                            '')),
                    ''))"
    }</pre>
    </details><br>


DHCPv6 Log Entries
~~~~~~~~~~~~~~~~~~

For DHCPv6, the library creates entries based on REQUEST, RENEW, RELEASE,
DECLINE messages et.al. and their responses. The resulting packets and leases
are taken into account, intercepted through the following hook points:
* pkt6_receive
* leases6_committed
* pkt6_send
* lease6_release
* lease6_decline

An entry is a single string with no embedded end-of-line markers and a
prepended timestamp, and has the following sections:

::

   timestamp address duration device-id {relay-info}* {user-context}

Where:

-  timestamp - the current date and time the log entry was written in
   "%Y-%m-%d %H:%M:%S %Z" strftime format ("%Z" is the time zone name).

-  address - the leased IPv6 address or prefix given out and whether it
   was assigned, renewed or released.

-  duration - the lease lifetime expressed in days (if present), hours,
   minutes, and seconds. A lease lifetime of 0xFFFFFFFF will be denoted
   with the text "infinite duration". This information is not given
   when the lease is released.

-  device-id - the client's DUID and hardware address (if present).

-  relay-info - for relayed packets the content of relay agent messages,
   remote-id (code 37), subscriber-id (code 38), and interface-id (code 18)
   options, if present. Note that interface-id option, if present,
   identifies the whole interface the relay agent received the message
   on. This typically translates to a single link in the network, but
   it depends on the specific network topology. Nevertheless, this is
   useful information to better scope down the location of the device,
   so it is recorded, if present.

-  user-context - the optional user context associated with the lease.

For instance (line breaks added for readability; they will not be
present in the log file):

::

   2018-01-06 01:02:03 PST Address:2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs
   to a device with DUID: 17:34:e2:ff:09:92:54 and hardware address: hwtype=1 08:00:2b:02:3f:4e
   (from Raw Socket) connected via relay at address: fe80::abcd for client on link address: 3001::1,
   hop count: 1, identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f and subscriber-id: 1a:2b:3c:4d:5e:6f

or for a release:

::

   2018-01-06 01:02:03 PST Address:2001:db8:1:: has been released
   from a device with DUID: 17:34:e2:ff:09:92:54 and hardware address: hwtype=1 08:00:2b:02:3f:4e
   (from Raw Socket) connected via relay at address: fe80::abcd for client on link address: 3001::1,
   hop count: 1, identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f and subscriber-id: 1a:2b:3c:4d:5e:6f

In addition to logging lease activity driven by DHCPv6 client traffic,
the hooks library also logs entries for the following lease management control channel
commands: lease6-add, lease6-update, and lease6-del. Each entry is a
single string with no embedded end-of-line markers, and it will
typically have the following form:

``lease6-add:``

::

   *timestamp* Administrator added a lease of address: *address* to a device with DUID: *DUID*

Depending on the arguments of the add command, it may also include the
hardware address and duration.

Example:

::

   2018-01-06 01:02:03 PST Administrator added a lease of address: 2001:db8::3 to a device with DUID:
   1a:1b:1c:1d:1e:1f:20:21:22:23:24 for 1 days 0 hrs 0 mins 0 secs

``lease6-update:``

::

   *timestamp* Administrator updated information on the lease of address: *address* to a device with DUID: *DUID*

Depending on the arguments of the update command, it may also include
the hardware address and lease duration.

Example:

::

   2018-01-06 01:02:03 PST Administrator updated information on the lease of address: 2001:db8::3 to a device with
   DUID: 1a:1b:1c:1d:1e:1f:20:21:22:23:24, hardware address: 1a:1b:1c:1d:1e:1f

``lease6-del:`` deletes have two forms, one by address and one by
identifier and identifier type:

::

   *timestamp* Administrator deleted the lease for address: *address*

or

::

   *timestamp* Administrator deleted a lease for a device identified by: *identifier-type* of *identifier*

Currently only a type of DUID is supported.

Examples:

::

   2018-01-06 01:02:03 PST Administrator deleted the lease for address: 2001:db8::3

   2018-01-06 01:02:11 PST Administrator deleted a lease for a device identified by: duid of 1a:1b:1c:1d:1e:1f:20:21:22:23:24

The ``request-parser-format`` and ``response-parser-format`` can be used to
extract and log data from the incoming packet and server response packet
respectively. The configured value is an evaluated parsed expression returning a
string. A list of tokens is described in the server classification process.
Use with caution as this might affect server performance.
If any of them is configured, the default logging format is not used.
If both of them are configured, the resulting log message is constructed by
concatenating the logged data extracted from the request and the logged data
extracted from the response.

Some data might be available in the request or in the response only and some
data might differ in the incoming packet from the one in the response packet.

Examples:


.. code-block:: json

    {
        "request-parser-format": "ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9, ifelse(option[3].option[5].exists, 'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), '') + ifelse(option[25].option[26].exists, 'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), ''), '')",
        "response-parser-format": "ifelse(pkt6.msgtype == 7, ifelse(option[3].option[5].exists, 'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), '') + ifelse(option[25].option[26].exists, 'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), ''), '')"
    }

.. raw:: html

    <details><summary>Expand here!</summary>
    <pre>{
        "request-parser-format":
            "ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9,
                ifelse(option[3].option[5].exists,
                    'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    '') +
                ifelse(option[25].option[26].exists,
                    'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    ''),
                '')",
        "response-parser-format":
            "ifelse(pkt6.msgtype == 7,
                ifelse(option[3].option[5].exists,
                    'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    '') +
                ifelse(option[25].option[26].exists,
                    'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    ''),
                '')"
    }</pre>
    </details><br>


This will log the following data on request, renew and rebind for NA:

::

   Address: 2001:db8:1:: has been assigned for 713 seconds to a device with DUID: 17:34:e2:ff:09:92:54 connected via relay at address: fe80::abcd for client on link address: 3001::1, remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f, subscriber-id: 1a:2b:3c:4d:5e:6f, connected at location interface-id: 72:65:6c:61:79:31:3a:65:74:68:30


This will log the following data on request, renew and rebind for PD:

::

   Prefix: 2001:db8:1::/64 has been assigned for 713 seconds to a device with DUID: 17:34:e2:ff:09:92:54 connected via relay at address: fe80::abcd for client on link address: 3001::1, remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f, subscriber-id: 1a:2b:3c:4d:5e:6f, connected at location interface-id: 72:65:6c:61:79:31:3a:65:74:68:30


This will log the following data on release and decline for NA:

::

   Address: 2001:db8:1:: has been released from a device with DUID: 17:34:e2:ff:09:92:54 connected via relay at address: fe80::abcd for client on link address: 3001::1, remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f, subscriber-id: 1a:2b:3c:4d:5e:6f, connected at location interface-id: 72:65:6c:61:79:31:3a:65:74:68:30


This will log the following data on release and decline for PD:

::

   Prefix: 2001:db8:1::/64 has been released from a device with DUID: 17:34:e2:ff:09:92:54 connected via relay at address: fe80::abcd for client on link address: 3001::1, remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f, subscriber-id: 1a:2b:3c:4d:5e:6f, connected at location interface-id: 72:65:6c:61:79:31:3a:65:74:68:30


Similar result can be obtained if configuring ``request-parser-format`` only.

Examples:


.. code-block:: json

    {
        "request-parser-format": "ifelse(pkt6.msgtype == 3 or pkt6.msgtype == 5 or pkt6.msgtype == 6, ifelse(option[3].option[5].exists, 'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), '') + ifelse(option[25].option[26].exists, 'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), ''), ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9, ifelse(option[3].option[5].exists, 'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), '') + ifelse(option[25].option[26].exists, 'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') + ifelse(relay6[0].peeraddr == '', '', ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) + ifelse(relay6[0].option[37].exists, ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'), '') + ifelse(relay6[0].option[38].exists, ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'), '') + ifelse(relay6[0].option[18].exists, ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'), '')), ''), ''))"
    }

.. raw:: html

    <details><summary>Expand here!</summary>
    <pre>{
        "request-parser-format":
            "ifelse(pkt6.msgtype == 3 or pkt6.msgtype == 5 or pkt6.msgtype == 6,
                ifelse(option[3].option[5].exists,
                    'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been assigned for ' + uint32totext(substring(option[3].option[5].hex, 20, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    '') +
                ifelse(option[25].option[26].exists,
                    'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been assigned for ' + uint32totext(substring(option[25].option[26].hex, 4, 4)) + ' seconds to a device with DUID: ' + hexstring(option[1].hex, ':') +
                    ifelse(relay6[0].peeraddr == '',
                        '',
                        ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                        ifelse(relay6[0].option[37].exists,
                            ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[38].exists,
                            ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                            '') +
                        ifelse(relay6[0].option[18].exists,
                            ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                            '')),
                    ''),
                ifelse(pkt6.msgtype == 8 or pkt6.msgtype == 9,
                    ifelse(option[3].option[5].exists,
                        'Address: ' + addrtotext(substring(option[3].option[5].hex, 0, 16)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                        ifelse(relay6[0].peeraddr == '',
                            '',
                            ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                            ifelse(relay6[0].option[37].exists,
                                ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                                '') +
                            ifelse(relay6[0].option[38].exists,
                                ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                                '') +
                            ifelse(relay6[0].option[18].exists,
                                ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                                '')),
                        '') +
                    ifelse(option[25].option[26].exists,
                        'Prefix: ' + addrtotext(substring(option[25].option[26].hex, 9, 16)) + '/' + uint8totext(substring(option[25].option[26].hex, 8, 1)) + ' has been released from a device with DUID: ' + hexstring(option[1].hex, ':') +
                        ifelse(relay6[0].peeraddr == '',
                            '',
                            ' connected via relay at address: ' + addrtotext(relay6[0].peeraddr) + ' for client on link address: ' + addrtotext(relay6[0].linkaddr) +
                            ifelse(relay6[0].option[37].exists,
                                ', remote-id: ' + hexstring(relay6[0].option[37].hex, ':'),
                                '') +
                            ifelse(relay6[0].option[38].exists,
                                ', subscriber-id: ' + hexstring(relay6[0].option[38].hex, ':'),
                                '') +
                            ifelse(relay6[0].option[18].exists,
                                ', connected at location interface-id: ' + hexstring(relay6[0].option[18].hex, ':'),
                                '')),
                        ''),
                    ''))"
    }</pre>
    </details><br>

.. _forensic-log-database:

Database Backend
~~~~~~~~~~~~~~~~

Log entries can be inserted into a database when Kea is configured with
database backend support. A table named "logs" is used that includes a timestamp
(timeuuid for Cassandra) generated by the database software, and a
text log with the same format as files without the timestamp.

Please refer to :ref:`mysql-database` for information on using a MySQL database; to
:ref:`pgsql-database` for PostgreSQL database information; or to :ref:`cql-database`
for information on using a Cassandra (CQL) database. The logs table is part of the Kea database schemas.

Configuration parameters are extended by standard lease database
parameters as defined in :ref:`database-configuration4`. The "type"
parameter should be "mysql", "postgresql", "cql", or "logfile". When
it is absent or set to "logfile", files are used.

This database feature is experimental and will be likely improved, for
instance to add an address/prefix index (currently the only index is
the timestamp). No specific tools are provided to operate the database,
but standard tools may be used, for example, to dump the logs table
from a CQL database:

::

   $ echo 'SELECT dateOf(timeuuid), log FROM logs;' | cqlsh -k database-name

    system.dateof(timeuuid)         | log
   ---------------------------------+---------------------------------------
    2018-01-06 01:02:03.227000+0000 | Address: 192.2.1.100 has been renewed ...
    ...
   (12 rows)

Like all the other database-centric features, forensic logging supports database
connection recovery which can be enabled by setting the ``on-fail`` parameter.
If not specified, the ``on-fail`` parameter defaults to ``serve-retry-continue``
as opposed to the case of lease manager, host manager and config backend where
it defaults to ``stop-retry-exit``. In this case, the server will continue
serving clients and it will not shut down even if the recovery mechanism fails.
If the ``on-fail`` is set to ``serve-retry-exit``, the server will shut down if
the connection to the database backend is not restored according to the
``max-reconnect-tries`` and ``reconnect-wait-time`` parameters, but it will
continue serving clients while this mechanism is activated.

.. _flex-id:

flex_id: Flexible Identifiers for Host Reservations
===================================================

This section describes a hook application dedicated to generating flexible
identifiers for host reservations. The Kea software provides a way to handle
host reservations that include addresses, prefixes, options, client
classes, and other features. The reservation can be based on hardware
address, DUID, circuit-id, or client-id in DHCPv4 and on hardware
address or DUID in DHCPv6. However, there are sometimes scenarios where
the reservation is more complex; it may use options other than those mentioned
above, use parts of specific options, or perhaps even use a combination of
several options and fields to uniquely identify a client. Those
scenarios are addressed by the Flexible Identifiers hook application.

Currently this library is only available to ISC customers with a paid support
contract.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or ``kea-dhcp6``
   process.

The library allows the definition of an expression, using notation initially
used only for client classification. (See
:ref:`classification-using-expressions` for a detailed description of
the syntax available.) One notable difference is that for client
classification, the expression currently has to evaluate to either true
or false, while the flexible identifier expression is expected to
evaluate to a string that will be used as an identifier. It is a valid case
for the expression to evaluate to an empty string (e.g. in cases where a
client does not send specific options). This expression is then
evaluated for each incoming packet, and this evaluation generates an
identifier that is used to identify the client. In particular, there may
be host reservations that are tied to specific values of the flexible
identifier.

The library can be loaded in a similar way as other hook libraries. It
takes a mandatory parameter ``identifier-expression`` and optional boolean
parameter ``replace-client-id``:

::

   "Dhcp6": {
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_flex_id.so",
               "parameters": {
                   "identifier-expression": "expression",
                   "replace-client-id": false
               }
           },
           ...
       ]
   }

The flexible identifier library supports both DHCPv4 and DHCPv6.

Let's consider a case of an IPv6 network that has an
independent interface for each of its connected customers. Customers are
able to plug in whatever device they want, so any type of identifier
(e.g. a client-id) is unreliable. Therefore, the operator may decide to
use an option inserted by a relay agent to differentiate between
clients. In this particular deployment, the operator has verified that the
interface-id is unique for each customer-facing interface, so it
is suitable for usage as a reservation. However, only the first six bytes of
the interface-id are interesting, because remaining bytes are either
randomly changed or not unique between devices. Therefore, the customer
decided to use the first six bytes of the interface-id option inserted by the
relay agent. After adding ``flex-id``, the ``host-reservation-identifiers`` goal
can be achieved by using the following configuration:

::

   "Dhcp6": {
       "subnet6": [{ ..., # subnet definition starts here
       "reservations": [
           "flex-id": "'port1234'", # value of the first 8 bytes of the interface-id
           "ip-addresses": [ "2001:db8::1" ]
       ],
       }], # end of subnet definitions
       "host-reservation-identifiers": ["duid", "flex-id"], # add "flex-id" to reservation identifiers
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_flex_id.so",
               "parameters": {
                   "identifier-expression": "substring(relay6[0].option[18].hex,0,8)"
               }
           },
           ...
       ]
   }

.. note::

  Care should be taken when adjusting the expression. If the expression
  changes, then all the ``flex-id`` values may change, possibly rendering
  all reservations based on ``flex-id`` unusable until they are manually updated.
  It is strongly recommended that administrators start with the expression and a
  handful of reservations, and then adjust the expression as needed. Once
  the expression is confirmed to do what is desired of it, host reservations
  can be deployed on a broader scale.

``flex-id`` values in host reservations can be specified in two ways. First,
they can be expressed as a hex string, e.g. bar string can be represented
as 626174. Alternatively, it can be expressed as a quoted value (using
double and single quotes), e.g. "'bar'". The former is more convenient
for printable characters, while hex string values are more convenient
for non-printable characters and do not require the use of the
``hexstring`` operator.

::

   "Dhcp6": {
       "subnet6": [{ ..., # subnet definition starts here
       "reservations": [
           "flex-id": "01:02:03:04:05:06", # value of the first 8 bytes of the interface-id
           "ip-addresses": [ "2001:db8::1" ]
       ],
       }], # end of subnet definitions
       "host-reservation-identifiers": ["duid", "flex-id"], # add "flex-id" to reservation identifiers
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_flex_id.so",
               "parameters": {
                   "identifier-expression": "vendor[4491].option[1026].hex"
               }
           },
           ...
       ]
   }

When ``replace-client-id`` is set to "false" (which is the default setting),
the flex-id hook library uses the evaluated flexible identifier solely for
identifying host reservations, i.e. searching for reservations within a
database. This is the functional equivalent of other identifiers, similar
to hardware address or circuit-id. However, this mode of operation
implies that if a client device is replaced, it may cause a
conflict between an existing lease (allocated to the old device) and the
new lease being allocated to the new device. The conflict arises
because the same flexible identifier is computed for the replaced device,
so the server will try to allocate the same lease. The mismatch between
client identifiers sent by the new device and the old device causes the server
to refuse this new allocation until the old lease expires. A
manifestation of this problem is dependent on the specific expression used
as the flexible identifier and is likely to appear if only options
and other parameters are used that identify where the device is connected
(e.g. circuit-id), rather than the device identification itself (e.g.
MAC address).

The flex-id library offers a way to overcome the problem with lease
conflicts by dynamically replacing the client identifier (or DUID in DHCPv6)
with a value derived from the flexible identifier. The server
processes the client's query as if the flexible identifier were sent in the
client identifier (or DUID) option. This guarantees that a returning
client (for which the same flexible identifier is evaluated) will be
assigned the same lease despite the client identifier and/or MAC address
change.

The following is a stub configuration that enables this behavior:

::

   "Dhcp4": {
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_flex_id.so",
               "parameters": {
                   "identifier-expression": "expression",
                   "replace-client-id": true
               }
           },
           ...
       ]
   }

In the DHCPv4 case, the value derived from the flexible identifier is
formed by prepending one byte with a value of zero to the flexible identifier.
In the DHCPv6 case, it is formed by prepending two zero bytes before the
flexible identifier.

Note that for this mechanism to take effect, the DHCPv4 server must be
configured to respect the client identifier option value during lease
allocation, i.e. ``match-client-id`` must be set to "true". See
:ref:`dhcp4-match-client-id` for details. No additional settings are
required for DHCPv6.

If the ``replace-client-id`` option is set to "true", the value of the
``echo-client-id`` parameter (which governs whether to send back a
client-id option) is ignored.

The :ref:`lease-cmds` section describes commands used to retrieve,
update, and delete leases using various identifiers, such as "hw-address" and
"client-id". The lease_cmds library does not natively support querying
for leases by flexible identifier. However, when ``replace-client-id`` is
set to "true", it makes it possible to query for leases using a value
derived from the flexible identifier. In the DHCPv4 case, the query will
look similar to this:

::

   {
       "command": "lease4-get",
       "arguments": {
           "identifier-type": "client-id",
           "identifier": "00:54:64:45:66",
           "subnet-id": 44
       }
   }

where the hexadecimal value of "54:64:45:66" is a flexible identifier
computed for the client.

In the DHCPv6 case, the corresponding query will look similar to this:

::

   {
       "command": "lease6-get",
       "arguments": {
           "identifier-type": "duid",
           "identifier": "00:00:54:64:45:66",
           "subnet-id": 10
       }
   }

.. _flex-option:

flex_option Flexible Option for Option value settings
=====================================================

This library allows you to define an action to take, for a given option,
based upon on the result of an expression.  These actions are carried
out during the final stages of constructing a query response packet,
just before it is sent to the client. The three actions currently
supported are ``add``, ``supersede``, and ``remove``.

The syntax used for the action expressions is the same syntax used
for client classification and the Flex Identifier hook library
(See either :ref:`classification-using-expressions` or :ref:`flex-id`
for detailed description of the syntax).

The ``add`` and ``supersede`` actions use an expression returning a
string, doing nothing when it evaluates to the empty string. The
``remove`` application uses an expression returning true or false,
doing nothing on false. When it is necessary to set an option to the
empty value this mechanism does not work but a client class can be
used instead.

The ``add`` action adds an option only when the option does not already
exist and the expression does not evaluate to the empty string.
The ``supersede`` action does the same but it overwrites the option value
if it already exists. The ``remove`` action removes the option from
the response packet if it already exists and the expression evaluates to
true.

The option to which an action applies may be specified by either its
numeric code or its name.. At least the code or the name must be
specified. The option space is the DHCPv4 or DHCPv6 spaces depending
on the server where the hook library is loaded. Other spaces as vendor
spaces could be supported in a further version.

The library is available since Kea 1.7.1 and can be loaded in a
similar way as other hook libraries by the ``kea-dhcp4`` or `kea-dhcp6``
process.. It takes a mandatory ``options`` parameter holding a list of
per option parameter maps with code, name, add, supersede and remove
actions. Action entries take a string value representing an
expression.

::

    "Dhcp4": {
        "hooks-libraries": [
            {   "library": "/usr/local/lib/libdhcp_flex_option.so",
                "parameters": {
                    "options": [
                            {
                            "code": 67,
                            "add":
  "ifelse(option[host-name].exists,concat(option[host-name].text,'.boot'),'')"
                        }
                    ]
                }
            },
            ...
        ]
    }

If (and only if) the query includes a host-name option (code 12),
a boot-file-name option (code 67) is added to the response with the host
name followed by .boot for content.

The flexible option library supports both DHCPv4 and DHCPv6.

Since Kea 1.9.0, the add and supersede actions take an optional csv-format
boolean parameter. If not specified or configured to false, the option data is
set using the raw value of the evaluated expression. When it is configured
to true, this value is parsed using the option definition from the option data
specified in the configuration file. This eases option setting for options
using complex record formats or fully qualified domain names.

For instance if the expression evaluation returns "example.com" and
the option is defined with the fqdn type the domain name will be
encoded into DNS binary format.


.. _host-cmds:

host_cmds: Host Commands
========================

This section describes a hook application that offers a number of new
commands used to query and manipulate host reservations. Kea provides a
way to store host reservations in a database. In many larger deployments
it is useful to be able to manage that information while the server is
running. This library provides management commands for adding, querying,
and deleting host reservations in a safe way without restarting the
server. In particular, it validates the parameters, so an attempt to
insert incorrect data - such as adding a host with a conflicting identifier in the
same subnet - will be rejected. Those commands are exposed via the command
channel (JSON over UNIX sockets) and the Control Agent (JSON over a RESTful
interface). Additional commands and capabilities related to host
reservations will be added in the future.

Currently this library is only available to ISC customers with a paid support
contract.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or ``kea-dhcp6``
   process.

Currently, six commands are supported: reservation-add (which adds a new
host reservation), reservation-get (which returns an existing reservation
if specified criteria are matched), reservation-get-all (which returns
all reservations in a specified subnet), reservation-get-page (a variant
of reservation-get-all which returns all reservations in a specified
subnet by pages and since Kea version 1.9.0 all reservations),
reservation-get-by-hostname (which returns all reservations
with a specified hostname and optionally in a subnet) since Kea version
1.7.1, reservation-get-by-id (which returns all reservations with a
specified identifier) since Kea version 1.9.0,
and reservation-del (which attempts to delete a
reservation matching specified criteria). To use commands that change
the reservation information (currently these are reservation-add and
reservation-del, but this rule applies to other commands that may be
implemented in the future), the hosts database must be specified and it must not operate
in read-only mode (see
the hosts-databases descriptions in :ref:`hosts-databases-configuration4`
and :ref:`hosts-databases-configuration6`). If the hosts-databases are not specified or are
running in read-only mode, the host_cmds library will load, but any
attempts to use reservation-add or reservation-del will fail.

Additional host reservation commands are planned in future releases of Kea. For a
description of envisaged commands, see the `Control API
Requirements <https://gitlab.isc.org/isc-projects/kea/wikis/designs/commands>`__
document.

All commands use JSON syntax. They can be issued either using the
control channel (see :ref:`ctrl-channel`) or via the Control Agent (see
:ref:`kea-ctrl-agent`).

The library can be loaded similarly to other hook libraries. It
does not take any parameters, and it supports both DHCPv4 and DHCPv6
servers.

::

   "Dhcp6": {
       "hooks-libraries": [
           {
               "library": "/path/libdhcp_host_cmds.so"
           }
           ...
       ]
   }

The subnet-id Parameter
~~~~~~~~~~~~~~~~~~~~~~~

Prior to diving into the individual commands, it is worth discussing the
parameter, ``subnet-id``. Currently this parameter is mandatory for all of the
commands supplied by this library with the exception of
reservation-get-by-hostname where it is optional, and since Kea 1.9.0
reservation-get-page where it is optional and reservation-get-by-id
where it is forbidden.
In previous versions of Kea, reservations had
to belong to a specific subnet; as of Kea 1.5.0, reservations may
be specified globally. In other words, they are not specific to any
subnet. When reservations are supplied via the configuration file, the
ID of the containing subnet (or lack thereof) is implicit in the
configuration structure. However, when managing reservations using
host commands, it is necessary to explicitly identify the scope to which
the reservation belongs. This is done via the ``subnet-id`` parameter.
For global reservations, use a value of zero (0). For reservations
scoped to a specific subnet, use that subnet's ID.

On the other hand when the subnet id is not specified in the command
parameters it is added to each host in responses. If the subnet id
has the unused special value this means the host entry belongs only
to the other IP version (i.e. IPv6 in DHCPv4 server or IPv4 in DHCPv6
server) and this entry is ignored.

.. _command-reservation-add:

The reservation-add Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-add`` allows for the insertion of a new host. It takes a
set of arguments that vary depending on the nature of the host
reservation. Any parameters allowed in the configuration file that
pertain to host reservation are permitted here. For details regarding
IPv4 reservations, see :ref:`host-reservation-v4`; for IPv6 reservations, see
:ref:`host-reservation-v6`. The ``subnet-id`` is mandatory. Use a
value of zero (0) to add a global reservation, or the id of the subnet
to which the reservation should be added. An example command can be as
simple as:

.. code-block:: json

   {
       "command": "reservation-add",
       "arguments": {
           "reservation": {
               "subnet-id": 1,
               "hw-address": "1a:1b:1c:1d:1e:1f",
               "ip-address": "192.0.2.202"
           }
       }
   }

but it can also take many more parameters, for example:

.. code-block:: json

   {
       "command": "reservation-add",
       "arguments": {
           "reservation": {
               "subnet-id": 1,
               "client-id": "01:0a:0b:0c:0d:0e:0f",
               "ip-address": "192.0.2.205",
               "next-server": "192.0.2.1",
               "server-hostname": "hal9000",
               "boot-file-name": "/dev/null",
               "option-data": [
                   {
                       "name": "domain-name-servers",
                       "data": "10.1.1.202,10.1.1.203"
                   }
               ],
               "client-classes": [ "special_snowflake", "office" ]
           }
       }
   }

Here is an example of a complex IPv6 reservation:

.. code-block:: json

   {
       "command": "reservation-add",
       "arguments": {
           "reservation": {
               "subnet-id": 1,
               "duid": "01:02:03:04:05:06:07:08:09:0A",
               "ip-addresses": [ "2001:db8:1:cafe::1" ],
               "prefixes": [ "2001:db8:2:abcd::/64" ],
               "hostname": "foo.example.com",
               "option-data": [
                   {
                       "name": "vendor-opts",
                       "data": "4491"
                   },
                   {
                       "name": "tftp-servers",
                       "space": "vendor-4491",
                       "data": "3000:1::234"
                   }
               ]
           }
       }
   }

The command returns a status that indicates either a success (result 0)
or a failure (result 1). A failed command always includes a text parameter
that explains the cause of the failure. Example results:

::

   { "result": 0, "text": "Host added." }

Example failure:

::

   { "result": 1, "text": "Mandatory 'subnet-id' parameter missing." }

As ``reservation-add`` is expected to store the host, the hosts-databases
parameter must be specified in the configuration and databases must not
run in read-only mode. In future versions of Kea, it will be possible to
modify the reservations read from a configuration file. Interested parties are
encouraged to contact ISC for more information on developing this functionality.

.. _command-reservation-get:

The reservation-get Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get`` can be used to query the host database and retrieve
existing reservations. There are two types of parameters this command
supports: (subnet-id, address) or (subnet-id, identifier-type,
identifier). The first type of query is used when the address (either
IPv4 or IPv6) is known, but the details of the reservation are not. One
common use case of this type of query is to find out whether a given
address is reserved. The second query uses identifiers. For
maximum flexibility, Kea stores the host identifying information as a
pair of values: the type and the actual identifier. Currently supported
identifiers are "hw-address", "duid", "circuit-id", "client-id", and
"flex-id", but additional types may be added in the future. If any new
identifier types are defined in the future, the reservation-get command will
support them automatically. The ``subnet-id`` is mandatory. Use a value
of zero (0) to fetch a global reservation, or the id of the subnet to
which the reservation belongs.

An example command for getting a host reservation by a (subnet-id,
address) pair looks as follows:

::

   {
       "command": "reservation-get",
       "arguments": {
           "subnet-id": 1,
           "ip-address": "192.0.2.202"
       }
   }

An example query by (subnet-id, identifier-type, identifier) looks as
follows:

::

   {
       "command": "reservation-get",
       "arguments": {
           "subnet-id": 4,
           "identifier-type": "hw-address",
           "identifier": "01:02:03:04:05:06"
       }
   }

``reservation-get`` typically returns the result 0 when the query was
conducted properly. In particular, 0 is returned when the host was not
found. If the query was successful, a number of host parameters will be
returned. An example of a query that did not find the host looks as
follows:

::

   { "result": 0, "text": "Host not found." }

An example result returned when the host was found looks like this:

::

   {
     "arguments": {
       "boot-file-name": "bootfile.efi",
       "client-classes": [

       ],
       "hostname": "somehost.example.org",
       "hw-address": "01:02:03:04:05:06",
       "ip-address": "192.0.2.100",
       "next-server": "192.0.0.2",
       "option-data": [

       ],
       "server-hostname": "server-hostname.example.org"
     },
     "result": 0,
     "text": "Host found."
   }

An example result returned when the query was malformed might look like this:

::

   { "result": 1, "text": "No 'ip-address' provided and 'identifier-type'
                           is either missing or not a string." }

.. _command-reservation-get-all:

The reservation-get-all Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-all`` can be used to query the host database and
retrieve all reservations in a specified subnet. This command uses
parameters providing the mandatory subnet-id. Global host reservations
can be retrieved by using a subnet-id value of zero (0).

For instance, retrieving host reservations for the subnet 1:

::

   {
       "command": "reservation-get-all",
       "arguments": {
           "subnet-id": 1
        }
   }

returns some IPv4 hosts:

::

   {
       "arguments": {
           "hosts": [
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "somehost.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.100",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               },
               ...
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "otherhost.example.org",
                   "hw-address": "01:02:03:04:05:ff",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               }
           ]
       },
       "result": 0,
       "text": "72 IPv4 host(s) found."
   }

The response returned by ``reservation-get-all`` can be very long. The
DHCP server does not handle DHCP traffic when preparing a response to
reservation-get-all, so if there are many reservations in a subnet, this
may be disruptive. Use with caution. For larger deployments, please
consider using ``reservation-get-page`` instead (see
:ref:`command-reservation-get-page`).

For a reference, see :ref:`command-reservation-get-all`.

.. _command-reservation-get-page:

The reservation-get-page command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-page`` can be used to query the host database and
retrieve all reservations in a specified subnet by pages. This command
uses parameters providing the mandatory subnet-id. Use a value of zero
(0) to fetch global reservations. The second mandatory parameter is the
page size limit. Optional source-index and from host id, both defaulting
to 0, are used to chain page queries.
Since Kea version 1.9.0 the subnet id parameter is optional.

The usage of from and source-index parameters requires additional
explanation. For the first call, those parameters should not be specified
(or specified as zeros). For any follow-up calls, they should be set to
the values returned in previous calls in a next map holding from and
source-index values. Subsequent calls should be issued until all
reservations are returned. The end is reached once the returned list is
empty, the count is 0, no next map is present, and result status 3 (empty) is
returned.

.. note::

   The from and source-index parameters are reflecting the internal state of
   the search. There is no need to understand what they represent; it is
   simply a value that is supposed to be copied from one response to the
   next query. However, for those who are curious, the from field represents a
   64-bit representation of the host identifier used by a host backend. The
   source-index is an internal representation of multiple host
   backends: 0 is used to represent hosts defined in a configuration
   file, and 1 represents the first database backend. In some uncommon cases
   there may be more than one database backend configured, so
   potentially there may be a 2. In any case, Kea will iterate over all
   backends configured.

For instance, retrieving host reservations for the subnet 1 and
requesting the first page can be done by:

::

   {
       "command": "reservation-get-page",
       "arguments": {
           "subnet-id": 1,
           "limit": 10
        }
   }

Since this is the first call, source-index and from should not be
specified. They will default to their zero default values.

Some hosts are returned with information to get the next page:

::

   {
       "arguments": {
           "count": 72,
           "hosts": [
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "somehost.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.100",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               },
               ...
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "otherhost.example.org",
                   "hw-address": "01:02:03:04:05:ff",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               }
           ],
           "next": {
               "from": 1234567,
               "source-index": 1
           }
       },
       "result": 0,
       "text": "72 IPv4 host(s) found."
   }

Note that the "from" and "source-index" fields were specified in the response in
the next map. Those two must be copied to the next command, so Kea
continues from the place where the last command finished. To get the
next page the following command can be sent:

::

   {
       "command": "reservation-get-page",
       "arguments": {
           "subnet-id": 1,
           "source-index": 1,
           "from": 1234567,
           "limit": 10
        }
   }

The response will contain a list of hosts with updated source-index
and from fields. Continue calling the command until the last
page is received. Its response will look like this:

::

   {
       "arguments": {
           "count": 0,
           "hosts": [ ],
       },
       "result": 3,
       "0 IPv4 host(s) found."
   }

This command is more complex than ``reservation-get-all``, but lets
users retrieve larger host reservations lists in smaller chunks. For
small deployments with few reservations, it is easier to use
``reservation-get-all`` (see :ref:`command-reservation-get-all`).

.. note::

   Currently ``reservation-get-page`` is not supported by the Cassandra
   host backend.

.. _command-reservation-get-by-hostname:

The reservation-get-by-hostname Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-by-hostname`` can be used to query the host database and
retrieve all reservations with a specified hostname and optionally in
a specified subnet. This command uses parameters providing the mandatory
hostname and the optional subnet-id. Global host reservations
can be retrieved by using a subnet-id value of zero (0).
Hostname matching is case-insensitive. This command is available since
Kea version 1.7.1.

For instance, retrieving host reservations for "foobar" in the subnet 1:

::

   {
       "command": "reservation-get-by-hostname",
       "arguments": {
           "hostname": "foobar.example.org",
           "subnet-id": 1
        }
   }

returns some IPv4 hosts:

::

   {
       "arguments": {
           "hosts": [
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "foobar.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.100",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               },
               ...
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "foobar.example.org",
                   "hw-address": "01:02:03:04:05:ff",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org"
               }
           ]
       },
       "result": 0,
       "text": "5 IPv4 host(s) found."
   }

The response returned by ``reservation-get-by-hostname`` can be long
in particular when responses are not limited to a subnet.

For a reference, see :ref:`command-reservation-get-by-hostname`.

.. note::

   When the host backend is MySQL this commands relies on the fact
   the hostname column in the hosts table uses a case-insensitive
   collation as explained in the :ref:`mysql-database` section of
   :ref:`admin`.

.. _command-reservation-get-by-id:

The reservation-get-by-id Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-by-id`` can be used to query the host database and
retrieve all reservations with a specified identifier (identifier-type
and identifier parameters) independently of subnets. The syntax for
parameters is the same as for ref:`command-reservation-get`.
The subnet-id parameter is forbidden to avoid confusion.
This command is available since Kea version 1.9.0.

For instance, retrieving host reservations for the 01:02:03:04:05:06 MAC
address:

::

   {
       "command": "reservation-get-by-id",
       "arguments": {
           "identifier-type": "hw-address",
           "identifier": "01:02:03:04:05:06"
        }
    }

returns some IPv4 hosts:

::

   {
       "arguments": {
           "hosts": [
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "foo.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.100",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org",
                   "subnet-id": 123
               },
               ...
               {
                   "boot-file-name": "bootfile.efi",
                   "client-classes": [ ],
                   "hostname": "bar.example.org",
                   "hw-address": "01:02:03:04:05:06",
                   "ip-address": "192.0.2.200",
                   "next-server": "192.0.0.2",
                   "option-data": [ ],
                   "server-hostname": "server-hostname.example.org",
                   "subnet-id": 345
               }
           ]
       },
       "result": 0,
       "text": "5 IPv4 host(s) found."
   }

The response returned by ``reservation-get-by-id`` can be long
in particular when responses are not limited to a subnet.

For a reference, see :ref:`command-reservation-get-by-id`.

.. _command-reservation-del:

The reservation-del Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-del`` can be used to delete a reservation from the host
database. There are two types of parameters this command supports:
(subnet-id, address) or (subnet-id, identifier-type, identifier). The
first type of query is used when the address (either IPv4 or IPv6) is
known, but the details of the reservation are not. One common use case of
this type of query is to remove a reservation (e.g. a specific
address should no longer be reserved). The second query uses identifiers.
For maximum flexibility, Kea stores the host identifying information as
a pair of values: the type and the actual identifier. Currently supported
identifiers are "hw-address", "duid", "circuit-id", "client-id", and
"flex-id", but additional types may be added in the future. If any new
identifier types are defined in the future, the reservation-get command will
support them automatically. The ``subnet-id`` is mandatory. Use a value
of zero (0) to delete a global reservation, or the id of the subnet from
which the reservation should be deleted.

An example command for deleting a host reservation by (subnet-id,
address) pair looks as follows:

::

   {
       "command": "reservation-del",
       "arguments": {
           "subnet-id": 1,
           "ip-address": "192.0.2.202"
       }
   }

An example deletion by (subnet-id, identifier-type, identifier) looks as
follows:

::

   {
       "command": "reservation-del",
       "arguments":
           "subnet-id": 4,
           "identifier-type": "hw-address",
           "identifier": "01:02:03:04:05:06"
       }
   }

``reservation-del`` returns a result 0 when the host deletion was
successful or 1 if it was not. Descriptive text is provided in the event of
an error. Example results look as follows:

::

   {
       "result": 1,
       "text": "Host not deleted (not found)."
   }

::

   {
       "result": 0,
       "text": "Host deleted."
   }

::

   {
       "result": 1,
       "text": "Unable to delete a host because there is no hosts-database
                configured."
   }



.. include:: hooks-lease-cmds.rst


.. _subnet-cmds:

subnet_cmds: Subnet Commands
============================

This section describes a hook application that offers some new
commands used to query and manipulate subnet and shared network
configurations in Kea. This application is very useful in deployments
with a large number of subnets being managed by the DHCP servers,
when those subnets are frequently updated. The commands offer a lightweight
approach for manipulating subnets without a need to fully reconfigure
the server and without affecting existing servers' configurations. An
ability to manage shared networks (listing, retrieving details, adding
new ones, removing existing ones, and adding subnets to and removing them from
shared networks) is also provided.

Currently this library is only available to ISC customers with a paid support
contract.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or ``kea-dhcp6``
   process.

The following commands are currently supported:

-  ``subnet4-list/subnet6-list`` - lists all configured subnets.

-  ``subnet4-get/subnet6-get`` - retrieves detailed information about a
   specified subnet.

-  ``subnet4-add/subnet6-add`` - adds a new subnet into the server's
   configuration.

-  ``subnet4-update/subnet6-update`` - updates a subnet in the server's
   configuration.

-  ``subnet4-del/subnet6-del`` - removes a subnet from the server's
   configuration.

-  ``network4-list/network6-list`` - lists all configured shared networks.

-  ``network4-get/network6-get`` - retrieves detailed information about a
   specified shared network.

-  ``network4-add/network6-add`` - adds a new shared network to the
   server's configuration.

-  ``network4-del/network6-del`` - removes a shared network from the
   server's configuration.

-  ``network4-subnet-add/network6-subnet-add`` - adds an existing subnet to
   an existing shared network.

-  ``network4-subnet-del/network6-subnet-del`` - removes a subnet from
   an existing shared network and demotes it to a plain subnet.

.. _command-subnet4-list:

The subnet4-list Command
~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to list all currently configured subnets. Each
subnet is returned with a subnet identifier and
subnet prefix. To retrieve
detailed information about the subnet, use the ``subnet4-get`` command.

This command has the simple structure:

::

   {
       "command": "subnet4-list"
   }

The list of subnets is returned in the following format:

::

   {
       "result": 0,
       "text": "2 IPv4 subnets found",
       "arguments": {
       "subnets": [
           {
               "id": 10,
               "subnet": "10.0.0.0/8"
           },
           {
               "id": 100,
               "subnet": "192.0.2.0/24"
           }
       ]
   }

If no IPv4 subnets are found, an error code is returned along with the
error description.

.. _command-subnet6-list:

The subnet6-list Command
~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to list all currently configured subnets. Each
subnet is returned with a subnet identifier and
subnet prefix. To retrieve
detailed information about the subnet, use the ``subnet6-get`` command.

This command has the simple structure:

::

   {
       "command": "subnet6-list"
   }

The list of subnets is returned in the following format:

::

   {
       "result": 0,
       "text": "2 IPv6 subnets found",
       "arguments": {
       "subnets": [
           {
               "id": 11,
               "subnet": "2001:db8:1::/64"
           },
           {
               "id": 233,
               "subnet": "3000::/16"
           }
       ]
   }

If no IPv6 subnets are found, an error code is returned along with the
error description.

.. _command-subnet4-get:

The subnet4-get Command
~~~~~~~~~~~~~~~~~~~~~~~

This command is used to retrieve detailed information about the
specified subnet. This command usually follows ``subnet4-list``,
which is used to discover available subnets with their respective subnet
identifiers and prefixes. Any of those parameters can be then used in
``subnet4-get`` to fetch subnet information:

::

   {
       "command": "subnet4-get",
       "arguments": {
           "id": 10
       }
   }

or

::

   {
       "command": "subnet4-get",
       "arguments": {
           "subnet": "10.0.0.0/8"
       }
   }

If the subnet exists the response will be similar to this:

::

   {
       "result": 0,
       "text": "Info about IPv4 subnet 10.0.0.0/8 (id 10) returned",
       "arguments": {
           "subnets": [
               {
                   "subnet": "10.0.0.0/8",
                   "id": 1,
                   "option-data": [
                       ....
                   ]
                   ...
               }
           ]
       }
   }

.. _command-subnet6-get:

The subnet6-get Command
~~~~~~~~~~~~~~~~~~~~~~~

This command is used to retrieve detailed information about the
specified subnet. This command usually follows ``subnet6-list``,
which is used to discover available subnets with their respective subnet
identifiers and prefixes. Any of those parameters can be then used in
``subnet6-get`` to fetch subnet information:

::

   {
       "command": "subnet6-get",
       "arguments": {
           "id": 11
       }
   }

or

::

   {
       "command": "subnet6-get",
       "arguments": {
           "subnet": "2001:db8:1::/64"
       }
   }

If the subnet exists the response will be similar to this:

::

   {
       "result": 0,
       "text": "Info about IPv6 subnet 2001:db8:1::/64 (id 11) returned",
       "arguments": {
           "subnets": [
               {
                   "subnet": "2001:db8:1::/64",
                   "id": 1,
                   "option-data": [
                       ...
                   ]
                   ....
               }
           ]
       }
   }

.. _command-subnet4-add:

The subnet4-add Command
~~~~~~~~~~~~~~~~~~~~~~~

This command is used to create and add a new subnet to the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier must be specified and must be unique among all subnets. If
the identifier or a subnet prefix is not unique, an error is reported and
the subnet is not added.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations must not be specified within
``subnet4-add``. The commands described in :ref:`host-cmds` should be used to
add, remove, and modify static reservations.

::

   {
       "command": "subnet4-add",
       "arguments": {
           "subnet4": [ {
               "id": 123,
               "subnet": "10.20.30.0/24",
               ...
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv4 subnet added",
       "arguments": {
           "subnet4": [
               {
                   "id": 123,
                   "subnet": "10.20.30.0/24"
               }
           ]
       }
   }

.. _command-subnet6-add:

The subnet6-add Command
~~~~~~~~~~~~~~~~~~~~~~~

This command is used to create and add a new subnet to the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier must be specified and must be unique among all subnets. If
the identifier or a subnet prefix is not unique, an error is reported and
the subnet is not added.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations must not be specified within
``subnet6-add``. The commands described in :ref:`host-cmds` should be used
to add, remove, and modify static reservations.

::

   {
       "command": "subnet6-add",
       "arguments": {
           "subnet6": [ {
               "id": 234,
               "subnet": "2001:db8:1::/64",
               ...
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv6 subnet added",
       "arguments": {
           "subnet6": [
               {
                   "id": 234,
                   "subnet": "2001:db8:1::/64"
               }
           ]
       }
   }

It is recommended, but not mandatory, to specify the subnet ID. If not
specified, Kea will try to assign the next subnet-id value. This
automatic ID value generator is simple; it returns a previously
automatically assigned value, increased by 1. This works well, unless
a subnet is manually created with a value bigger than one previously used. For
example, if subnet4-add is called five times, each without an ID, Kea will
assign IDs 1, 2, 3, 4, and 5 and it will work just fine. However, if
subnet4-add is called five times, with the first subnet having the
subnet-id of value 3 and the remaining ones having no subnet-id, the operation will
fail. The first command (with the explicit value) will use subnet-id 3; the
second command will create a subnet with id of 1; the third will use a
value of 2; and finally the fourth will have the subnet-id value
auto-generated as 3. However, since there is already a subnet with that
ID, the process will fail.

The general recommendation is either never use explicit values, so
the auto-generated values will always work; or always use explicit
values, so the auto-generation is never used. The two
approaches can be mixed only if the administrator understands how internal
automatic subnet-id generation works in Kea.

.. note::

   Subnet IDs must be greater than zero and less than 4294967295.

.. _command-subnet4-update:

The subnet4-update Command
~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to update a subnet in the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier is used to identify the subnet to replace; it must be
specified and must be unique among all subnets. The subnet prefix should
not be updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations must not be specified within
``subnet4-update``. The commands described in :ref:`host-cmds` should be used
to update, remove, and modify static reservations.

::

   {
       "command": "subnet4-update",
       "arguments": {
           "subnet4": [ {
               "id": 123,
               "subnet": "10.20.30.0/24",
               ...
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv4 subnet updated",
       "arguments": {
           "subnet4": [
               {
                   "id": 123,
                   "subnet": "10.20.30.0/24"
               }
           ]
       }
   }

.. _command-subnet6-update:

The subnet6-update Command
~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to update a subnet in the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier is used to identify the subnet to replace; it must be
specified and must be unique among all subnets. The subnet prefix should
not be updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file, with the exception
that static host reservations must not be specified within
``subnet6-update``. The commands described in :ref:`host-cmds` should be used
to update, remove, and modify static reservations.

::

   {
       "command": "subnet6-update",
       "arguments": {
           "subnet6": [ {
               "id": 234,
               "subnet": "2001:db8:1::/64",
               ...
           } ]
       }
   }

The response to this command has the following structure:

::

   {
       "result": 0,
       "text": "IPv6 subnet updated",
       "arguments": {
           "subnet6": [
               {
                   "id": 234,
                   "subnet": "2001:db8:1::/64"
               }
           ]
       }
   }

.. _command-subnet4-del:

The subnet4-del Command
~~~~~~~~~~~~~~~~~~~~~~~

This command is used to remove a subnet from the server's configuration.
This command has no effect on other configured subnets, but removing a
subnet has certain implications which the server's administrator should
be aware of.

In most cases the server has assigned some leases to the clients
belonging to the subnet. The server may also be configured with static
host reservations which are associated with this subnet. The current
implementation of the ``subnet4-del`` command removes neither the leases nor
the host reservations associated with a subnet. This is the safest approach
because the server does not lose track of leases assigned to the clients
from this subnet. However, removal of the subnet may still cause
configuration errors and conflicts. For example: after removal of the
subnet, the server administrator may update a new subnet with the ID
used previously for the removed subnet. This means that the existing
leases and static reservations will be in conflict with this new subnet.
Thus, we recommend that this command be used with extreme caution.

This command can also be used to completely delete an IPv4 subnet that
is part of a shared network. To simply remove the subnet
from a shared network and keep the subnet configuration, use the
``network4-subnet-del`` command instead.

The command has the following structure:

::

   {
       "command": "subnet4-del",
       "arguments": {
           "id": 123
       }
   }

The example successful response may look like this:

::

   {
       "result": 0,
       "text": "IPv4 subnet 192.0.2.0/24 (id 123) deleted",
       "arguments": {
           "subnets": [
               {
                   "id": 123,
                   "subnet": "192.0.2.0/24"
               }
           ]
       }
   }

.. _command-subnet6-del:

The subnet6-del Command
~~~~~~~~~~~~~~~~~~~~~~~

This command is used to remove a subnet from the server's configuration.
This command has no effect on other configured subnets, but removing a
subnet has certain implications which the server's administrator should
be aware of.

In most cases the server has assigned some leases to the clients
belonging to the subnet. The server may also be configured with static
host reservations which are associated with this subnet. The current
implementation of the ``subnet6-del`` command removes neither the leases nor
the host reservations associated with a subnet. This is the safest approach
because the server does not lose track of leases assigned to the clients
from this subnet. However, removal of the subnet may still cause
configuration errors and conflicts. For example: after removal of the
subnet, the server administrator may add a new subnet with the ID used
previously for the removed subnet. This means that the existing leases
and static reservations will be in conflict with this new subnet. Thus,
we recommend that this command be used with extreme caution.

This command can also be used to completely delete an IPv6 subnet that
is part of a shared network. To simply remove the subnet
from a shared network and keep the subnet configuration, use the
``network6-subnet-del`` command instead.

The command has the following structure:

::

   {
       "command": "subnet6-del",
       "arguments": {
           "id": 234
       }
   }

The example successful response may look like this:

::

   {
       "result": 0,
       "text": "IPv6 subnet 2001:db8:1::/64 (id 234) deleted",
       "subnets": [
           {
               "id": 234,
               "subnet": "2001:db8:1::/64"
           }
       ]
   }

.. _command-network4-list:

.. _command-network6-list:

The network4-list, network6-list Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to retrieve the full list of currently configured
shared networks. The list contains only very basic information about
each shared network. If more details are needed, please use
``network4-get`` or ``network6-get`` to retrieve all information
available. This command does not require any parameters and its
invocation is very simple:

::

   {
       "command": "network4-list"
   }

An example response for ``network4-list`` looks as follows:

::

   {
       "arguments": {
           "shared-networks": [
               { "name": "floor1" },
               { "name": "office" }
           ]
       },
       "result": 0,
       "text": "2 IPv4 network(s) found"
   }

``network6-list`` follows exactly the same syntax for both the query and
the response.

.. _command-network4-get:

.. _command-network6-get:

The network4-get, network6-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to retrieve detailed information about shared
networks, including subnets that are currently part of a given network.
Both commands take one mandatory parameter, ``name``, which specifies the
name of the shared network. An example command to retrieve details about
an IPv4 shared network with the name "floor13" looks as follows:

::

   {
       "command": "network4-get",
       "arguments": {
           "name": "floor13"
       }
   }

An example response could look as follows:

::

   {
       "result": 0,
       "text": "Info about IPv4 shared network 'floor13' returned",
       "arguments": {
           "shared-networks": [
           {
               "match-client-id": true,
               "name": "floor13",
               "option-data": [ ],
               "rebind-timer": 90,
               "relay": {
                   "ip-address": "0.0.0.0"
               },
               "renew-timer": 60,
               # "reservation-mode": "all",
               # It is replaced by the "reservations-global"
               # "reservations-in-subnet" and "reservations-out-of-pool"
               # parameters.
               # Specify if the server should lookup global reservations.
               "reservations-global": false,
               # Specify if the server should lookup in-subnet reservations.
               "reservations-in-subnet": true,
               # Specify if the server can assume that all reserved addresses
               # are out-of-pool.
               "reservations-out-of-pool": false,
               "subnet4": [
                   {
                       "subnet": "192.0.2.0/24",
                       "id": 5,
                       # many other subnet-specific details here
                   },
                   {
                       "id": 6,
                       "subnet": "192.0.3.0/31",
                       # many other subnet-specific details here
                   }
               ],
               "valid-lifetime": 120
           }
           ]
       }
   }

Note that the actual response contains many additional fields that are
omitted here for clarity. The response format is exactly the same as
used in ``config-get``, just limited to returning the shared network's
information.

.. _command-network4-add:

.. _command-network6-add:

The network4-add, network6-add Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to add a new shared network, which must
have a unique name. This command requires one parameter,
``shared-networks``, which is a list and should contain exactly one
entry that defines the network. The only mandatory element for a network
is its name. Although it does not make operational sense, it is possible
to add an empty shared network that does not have any subnets in it.
That is allowed for testing purposes, but having empty networks (or with
only one subnet) is discouraged in production environments. For details
regarding syntax, see :ref:`shared-network4` and
:ref:`shared-network6`.

.. note::

   As opposed to parameter inheritance during the processing of a full new
   configuration, this command does not fully handle parameter inheritance.
   Any missing parameters will be filled with default values, rather
   than inherited from the global scope.

An example that showcases how to add a new IPv4 shared network looks as
follows:

::

   {
       "command": "network4-add",
       "arguments": {
           "shared-networks": [ {
               "name": "floor13",
               "subnet4": [
               {
                   "id": 100,
                   "pools": [ { "pool": "192.0.2.2-192.0.2.99" } ],
                   "subnet": "192.0.2.0/24",
                   "option-data": [
                       {
                           "name": "routers",
                           "data": "192.0.2.1"
                       }
                   ]
               },
               {
                   "id": 101,
                   "pools": [ { "pool": "192.0.3.2-192.0.3.99" } ],
                   "subnet": "192.0.3.0/24",
                   "option-data": [
                       {
                           "name": "routers",
                           "data": "192.0.3.1"
                       }
                   ]
               } ]
           } ]
       }
   }

Assuming there was no shared network with a name "floor13" and no subnets
with IDs 100 and 101 previously configured, the command will be
successful and will return the following response:

::

   {
       "arguments": {
           "shared-networks": [ { "name": "floor13" } ]
       },
       "result": 0,
       "text": "A new IPv4 shared network 'floor13' added"
   }

The ``network6-add`` command uses the same syntax for both the query and the
response. However, there are some parameters that are IPv4-only (e.g.
match-client-id) and some that are IPv6-only (e.g. interface-id). The same
applies to subnets within the network.

.. _command-network4-del:

.. _command-network6-del:

The network4-del, network6-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete existing shared networks. Both
commands take exactly one parameter, ``name``, that specifies the name of
the network to be removed. An example invocation of the ``network4-del``
command looks as follows:

::

   {
       "command": "network4-del",
       "arguments": {
           "name": "floor13"
       }
   }

Assuming there was such a network configured, the response will look
similar to the following:

::

   {
       "arguments": {
           "shared-networks": [
               {
                   "name": "floor13"
               }
           ]
       },
       "result": 0,
       "text": "IPv4 shared network 'floor13' deleted"
   }

The ``network6-del`` command uses exactly the same syntax for both the
command and the response.

If there are any subnets belonging to the shared network being deleted,
they will be demoted to a plain subnet. There is an optional parameter
called ``subnets-action`` that, if specified, takes one of two possible
values: ``keep`` (which is the default) and ``delete``. It controls
whether the subnets are demoted to plain subnets or removed. An example
usage in the ``network6-del`` command that deletes the shared network and all
subnets in it could look as follows:

::

   {
       "command": "network4-del",
       "arguments": {
           "name": "floor13",
           "subnets-action": "delete"
       }
   }

Alternatively, to completely remove the subnets, it is possible to use the
``subnet4-del`` or ``subnet6-del`` commands.

.. _command-network4-subnet-add:

.. _command-network6-subnet-add:

The network4-subnet-add, network6-subnet-add Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to add existing subnets to existing shared
networks. There are several ways to add a new shared network. The system
administrator can add the whole shared network at once, either by
editing a configuration file or by calling the ``network4-add`` or
``network6-add`` command with the desired subnets in it. This approach
works better for completely new shared subnets. However, there may be
cases when an existing subnet is running out of addresses and needs to
be extended with additional address space; in other words, another subnet
needs to be added on top of it. For this scenario, a system administrator
can use ``network4-add`` or ``network6-add``, and then add an existing
subnet to this newly created shared network using
``network4-subnet-add`` or ``network6-subnet-add``.

The ``network4-subnet-add`` and ``network6-subnet-add`` commands take
two parameters: ``id``, which is an integer and specifies the subnet-id of
an existing subnet to be added to a shared network; and ``name``, which
specifies the name of the shared network to which the subnet will be added. The
subnet must not belong to any existing network; to
reassign a subnet from one shared network to another, please use the
``network4-subnet-del`` or ``network6-subnet-del`` commands first.

An example invocation of the ``network4-subnet-add`` command looks as
follows:

::

   {
       "command": "network4-subnet-add",
       "arguments": {
           "name": "floor13",
           "id": 5
       }
   }

Assuming there is a network named "floor13", and there is a subnet with
subnet-id 5 that is not a part of existing network, the command will
return a response similar to the following:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now part of shared network 'floor13'"
   }

The ``network6-subnet-add`` command uses exactly the same syntax for
both the command and the response.

.. note::

   As opposed to parameter inheritance during the processing of a full new
   configuration or when adding a new shared network with new subnets,
   this command does not fully handle parameter inheritance.
   Any missing parameters will be filled with default values, rather
   than inherited from the global scope or from the shared network.

.. _command-network4-subnet-del:

.. _command-network6-subnet-del:

The network4-subnet-del, network6-subnet-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to remove a subnet that is part of an existing
shared network and demote it to a plain, stand-alone subnet.
To remove a subnet completely, use the ``subnet4-del`` or ``subnet6-del``
commands instead. The ``network4-subnet-del`` and
``network6-subnet-del`` commands take two parameters: ``id``, which is
an integer and specifies the subnet-id of an existing subnet to be removed from
a shared network; and ``name``, which specifies the name of the shared
network from which the subnet will be removed.

An example invocation of the ``network4-subnet-del`` command looks as
follows:

::

    {
       "command": "network4-subnet-del",
       "arguments": {
           "name": "floor13",
           "id": 5
       }
    }

Assuming there was a subnet with subnet-id equal to 5, that was part of a
shared network named "floor13", the response would look similar to the
following:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now removed from shared network 'floor13'"
   }

The ``network6-subnet-del`` command uses exactly the same syntax for
both the command and the response.


.. include:: hooks-bootp.rst
.. include:: hooks-class-cmds.rst
.. include:: hooks-cb-cmds.rst
.. include:: hooks-ha.rst
.. include:: hooks-stat-cmds.rst
.. include:: hooks-radius.rst
.. include:: hooks-host-cache.rst
.. include:: hooks-lease-query.rst
.. include:: hooks-run-script.rst


.. _user-context-hooks:

User Contexts in Hooks
======================

Hooks libraries can have their own configuration parameters, which is
convenient if the parameter applies to the whole library. However,
sometimes it is very useful to extend certain configuration entities
with additional configuration data. This is where the concept
of user contexts comes in. A system administrator can define an arbitrary set of
data and attach it to Kea structures, as long as the data are specified
as a JSON map. In particular, it is possible to define fields that are
integers, strings, boolean, lists, or maps. It is possible to define
nested structures of arbitrary complexity. Kea does not use that data on
its own; it simply stores it and makes it available for the hooks libraries.

Another use case for user contexts may be storing comments and other
information that will be retained by Kea. Regular comments are discarded
when the configuration is loaded, but user contexts are retained. This is
useful if administrators want their comments to survive config-set or config-get
operations, for example.

If user context is supported in a given context, the parser translates
"comment" entries into user context with a "comment" entry. The pretty
print of a configuration did the opposite operation and put "comment"
entries at the beginning of maps, but this was withdrawn in 1.7.9.

As of Kea 1.3, the structures that allow user contexts are pools of all
types (addresses and prefixes) and subnets. Kea 1.4 extended user
context support to the global scope, interfaces configuration, shared networks,
subnets, client classes, option data and definitions, host
reservations, control socket, dhcp ddns, loggers and server ID. These
are supported in both DHCPv4 and DHCPv6, with the exception of server ID
which is DHCPv6 only.
