.. _hooks-libraries:

***************
Hooks Libraries
***************

.. _hooks-libraries-introduction:

Introduction
============

Although Kea offers a lot of flexibility, there may be cases where its
behavior needs customization. To accommodate this possibility, Kea
includes the idea of "Hooks". This feature lets Kea load one or more
dynamically-linked libraries (known as "hooks libraries") and, at
various points in its processing ("hook points"), call functions in
them. Those functions perform whatever custom processing is required.

The hooks concept also allows keeping the core Kea code reasonably small
by moving features that some, but not all users find useful to external
libraries. People who don't need specific functionality simply don't
load the libraries.

Hooks libraries are loaded by individual Kea processes, not to Kea as a
whole. This means (for example) that it is possible to associate one set
of libraries with the DHCP4 server and a different set to the DHCP6
server.

Another point to note is that it is possible for a process to load
multiple libraries. When processing reaches a hook point, Kea calls the
hooks library functions attached to it. If multiple libraries have
attached a function to a given hook point, Kea calls all of them, in the
order in which the libraries are specified in the configuration file.
The order may be important: consult the documentation of the libraries
to see if this is the case.

The next section describes how to configure hooks libraries. If you are
interested in writing your own hooks library, information can be found
in the `Kea Developer's
Guide <https://jenkins.isc.org/job/Kea_doc/doxygen>`__.

Note that some libraries are available under different licenses.

Note that some libraries may require additional dependencies and/or
compilation switches to be enabled, e.g. Radius library introduced in
Kea 1.4 requires FreeRadius-client library to be present. If
--with-free-radius option is not specified, the Radius library will not
be built.

Installing Hook packages
========================

   **Note**

   The installation procedure has changed in 1.4.0. Kea 1.3.0 and
   earlier needed special switches passed to configure script to detect
   the hook libraries. Please see this KB article:
   https://kb.isc.org/article/AA-01587 .

Some hook packages are included in the base Kea sources. There is no
need to do anything special to compile or install them, they are covered
by the usual building and installation procedure. ISC also provides
several additional hooks in form of various packages. All of those
packages follow the same installation procedure that is similar to base
Kea, but has several additional steps. For your convenience, the whole
procedure is described here. Please refer to `??? <#installation>`__ for
general overview.

1. Download the package. You will receive detailed instructions how to
get it separately. This will be a file with a name similar to
kea-premium-KEAVERSION.tar.gz. Your name may differ depending on which
package you got.

2. If you have the sources for the corresponding version of the
open-source Kea package still on your system (from when you installed
Kea), skip this step. Otherwise extract the Kea source from the original
tarball you downloaded. For example, if you downloaded Kea KEAVERSION.,
you should have a tarball called kea-KEAVERSION.tar.gz on your system.
Unpack this tarball:

::

   $ tar zxvf kea-KEAVERSION.tar.gz

This will unpack the tarball into the kea-KEAVERSION subdirectory of
your current working directory.

3. Unpack the Kea premium tarball into the directory into which Kea was
unpacked. For example, assuming that you followed step 2 and that Kea
KEAVERSION has been unpacked into a kea-KEAVERSION subdirectory and that
the Kea premium tarball is in your current directory, the following
steps will unpack the premium tarball into the correct location:

::

     $ cd kea-KEAVERSION
     $ tar xvf ../kea-premium-KEAVERSION.tar.gz

Note that unpacking the Kea premium package will put the files into a
directory named premium. Regardless of the name of your package, the
directory will always be called premium, just its content may vary.

4. Run autoreconf tools. This step is necessary to update Kea's build
script to include additional directory. If this tool is not already
available on your system, you need to install automake and autoconf
tools. To generate configure script, please use:

::

     $ autoreconf -i

5. Rerun configure, using the same configure options as you used when
originally building Kea. You can check if configure has detected the
premium package by inspecting the summary printed when it exits. The
first section of the output should look something like:

::

   Package:
     Name:            kea
     Version:         KEAVERSION
     Extended version:KEAVERSION (tarball)
     OS Family:       Linux
     Using GNU sed:   yes
     Premium package: yes
     Included Hooks:  forensic_log flex_id host_cmds

The last line indicates which specific hooks were detected. Note that
some hooks may require its own dedicated switches, e.g. radius hook
requires extra switches for FreeRADIUS. Please consult later sections of
this chapter for details.

6. Rebuild Kea

::

     $ make

If your machine has multiple CPU cores, interesting option to consider
here is -j X, where X is the number of available cores.

7. Install Kea sources together with hooks:

::

   $ sudo make install

Note that as part of the installation procedure, the install script will
eventually venture into premium/ directory and will install additional
hook libraries and associated files.

The installation location of the hooks libraries depends whether you
specified --prefix parameter to the configure script. If you did not,
the default location will be /usr/local/lib/kea/hooks. You can verify
the libraries are installed properly with this command:

::

   $ ls -l /usr/local/lib/kea/hooks/*.so
   /usr/local/lib/kea/hooks/libdhcp_class_cmds.so
   /usr/local/lib/kea/hooks/libdhcp_flex_id.so
   /usr/local/lib/kea/hooks/libdhcp_host_cmds.so
   /usr/local/lib/kea/hooks/libdhcp_lease_cmds.so
   /usr/local/lib/kea/hooks/libdhcp_legal_log.so
   /usr/local/lib/kea/hooks/libdhcp_subnet_cmds.so

The exact list you see will depend on the packages you have. If you
specified directory via --prefix, the hooks libraries will be located in
{prefix directory}/lib/kea/hooks.

Configuring Hooks Libraries
===========================

The hooks libraries for a given process are configured using the
``hooks-libraries`` keyword in the configuration for that process. (Note
that the word "hooks" is plural). The value of the keyword is an array
of map structures, each structure corresponding to a hooks library. For
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

   **Note**

   This is a change to the syntax used in Kea 0.9.2 and earlier, where
   hooks-libraries was a list of strings, each string being the name of
   a library. The change was made in Kea 1.0 to facilitate the
   specification of library-specific parameters, a capability available
   in Kea 1.1.0 onwards. Libraries should allow a parameter entry where
   to put comments as it is done for many configuration scopes with
   comment and user context.

   **Note**

   The library reloading behavior has changed in Kea 1.1.0. Libraries
   are reloaded, even if their list hasn't changed. Kea does that,
   because the parameters specified for the library (or the files those
   parameters point to) may have changed.

Libraries may have additional parameters. Those are not mandatory in the
sense that there may be libraries that don't require them. However, for
specific library there is often specific requirement for specify certain
set of parameters. Please consult the documentation for your library for
details. In the example above, the first library has no parameters. The
second library has five parameters, specifying mail (string parameter),
floor (integer parameter), debug (boolean parameter) and even lists
(list of strings) and maps (containing strings). Nested parameters could
be used if the library supports it. This topic is explained in detail in
the Hooks Developer's Guide in the "Configuring Hooks Libraries"
section.

Notes:

-  The full path to each library should be given.

-  As noted above, order may be important - consult the documentation
   for each library.

-  An empty list has the same effect as omitting the ``hooks-libraries``
   configuration element all together.

      **Note**

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
to a subset of Kea users. To this end ISC has created some hooks
libraries; these discussed in the following sections.

   **Note**

   Some of these libraries will be available with the base code while
   others will be shared with organizations supporting development of
   Kea , possibly as a 'benefit' or 'thank you' for helping to sustain
   the larger Kea project. If you would like to get access to those
   libraries, please consider taking out a support contract: this
   includes professional support, advance security notifications, input
   into our roadmap planning, and many other benefits, while helping
   making Kea sustainable in the long term.

The following table provides a list of libraries currently available
from ISC. It is important to pay attention to which libraries may be
loaded by which Kea processes. It is a common mistake to configure the
``kea-ctrl-agent`` process to load libraries that should, in fact, be
loaded by the ``kea-dhcp4`` or ``kea-dhcp6`` processes. If a library
from ISC doesn't work as expected, please make sure that it has been
loaded by the correct process per the table below.

   **Warning**

   While the Kea Control Agent includes the "hooks" functionality, (i.e.
   hooks libraries can be loaded by this process), none of ISC's current
   hooks libraries should be loaded by the Control Agent.

.. table:: List of available hooks libraries

   +-----------------+-----------------+-----------------+-----------------+
   | Name            | Availability    | Since           | Load by process |
   +=================+=================+=================+=================+
   | user_chk        | Kea sources     | Kea 0.8         | kea-dhcp4,      |
   |                 |                 |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | Forensic        | Support         | Kea 1.1.0       | kea-dhcp4,      |
   | Logging         | customers       |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | Flexible        | Support         | Kea 1.2.0       | kea-dhcp4,      |
   | Identifier      | customers       |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | Host Commands   | Support         | Kea 1.2.0       | kea-dhcp4,      |
   |                 | customers       |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | Subnet Commands | Support         | Kea 1.3.0       | kea-dhcp4,      |
   |                 | customers       |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | Lease Commands  | Kea sources     | Kea 1.3.0       | kea-dhcp4,      |
   |                 |                 |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | High            | Kea sources     | Kea 1.4.0       | kea-dhcp4,      |
   | Availability    |                 |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | Statistics      | Kea sources     | Kea 1.4.0       | kea-dhcp4,      |
   | Commands        |                 |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | Radius          | Support         | Kea 1.4.0       | kea-dhcp4,      |
   |                 | customers       |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | Host Cache      | Support         | Kea 1.4.0       | kea-dhcp4,      |
   |                 | customers       |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | Class Commands  | Support         | Kea 1.5.0       | kea-dhcp4,      |
   |                 | customers       |                 | kea-dhcp6       |
   +-----------------+-----------------+-----------------+-----------------+
   | MySQL           | Kea sources     | Kea 1.6.0       | kea-dhcp4,      |
   | Configuration   |                 |                 | kea-dhcp6       |
   | Backend         |                 |                 |                 |
   +-----------------+-----------------+-----------------+-----------------+
   | Configuration   | Support         | Kea 1.6.0       | kea-dhcp4,      |
   | Backend         | customers       |                 | kea-dhcp6       |
   | Commands        |                 |                 |                 |
   +-----------------+-----------------+-----------------+-----------------+

ISC hopes to see more hooks libraries become available as time
progresses, both developed internally and externally. Since this list
may evolve dynamically, we decided to keep it on a wiki page, available
at this link:
https://gitlab.isc.org/isc-projects/kea/wikis/Hooks-available. If you
are a developer or are aware of any hooks libraries not listed there,
please send a note to the kea-users or kea-dev mailing lists and someone
will update it.

The libraries developed by ISC are described in detail in the following
sections.

user_chk: Checking User Access
------------------------------

The user_chk library is the first hooks library published by ISC. It
attempts to serve several purposes:

-  To assign "new" or "unregistered" users to a restricted subnet, while
   "known" or "registered" users are assigned to unrestricted subnets.

-  To allow DHCP response options or vendor option values to be
   customized based upon user identity.

-  To provide a real time record of the user registration activity which
   can be sampled by an external consumer.

-  To serve as a demonstration of various capabilities possible using
   the hooks interface.

Once loaded, the library allows segregating incoming requests into known
and unknown clients. For known clients, the packets are processed mostly
as usual, except it is possible to override certain options being sent.
That can be done on a per host basis. Clients that are not on the known
hosts list will be treated as unknown and will be assigned to the last
subnet defined in the configuration file.

As an example of use, this behavior may be used to put unknown users
into a separate subnet that leads to a walled garden, where they can
only access a registration portal. Once they fill in necessary data,
their details are added to the known clients file and they get a proper
address after their device is restarted.

   **Note**

   This library was developed several years before the host reservation
   mechanism has become available. Currently host reservation is much
   more powerful and flexible, but nevertheless the user_chk capability
   to consult and external source of information about clients and alter
   Kea's behavior is useful and remains of educational value.

The library reads the /tmp/user_chk_registry.txt file while being loaded
and each time an incoming packet is processed. The file is expected to
have each line contain a self-contained JSON snippet which must have the
following two entries:

-  ``type``, whose value is "HW_ADDR" for IPv4 users or "DUID" for IPv6
   users

-  ``id``, whose value is either the hardware address or the DUID from
   the request formatted as a string of hex digits, with or without ":"
   delimiters.

and may have the zero or more of the following entries:

-  ``bootfile`` whose value is the pathname of the desired file

-  ``tftp_server`` whose value is the hostname or IP address of the
   desired server

A sample user registry file is shown below:

::

   { "type" : "HW_ADDR", "id" : "0c:0e:0a:01:ff:04", "bootfile" : "/tmp/v4bootfile" }
   { "type" : "HW_ADDR", "id" : "0c:0e:0a:01:ff:06", "tftp_server" : "tftp.v4.example.com" }
   { "type" : "DUID", "id" : "00:01:00:01:19:ef:e6:3b:00:0c:01:02:03:04", "bootfile" : "/tmp/v6bootfile" }
   { "type" : "DUID", "id" : "00:01:00:01:19:ef:e6:3b:00:0c:01:02:03:06", "tftp_server" : "tftp.v6.example.com" }

As with any other hooks libraries provided by ISC, internals of the
user_chk code are well documented. You can take a look at the `Kea
Developer's Guide section dedicated to the user_chk
library <https://jenkins.isc.org/job/Kea_doc/doxygen/d8/db2/libdhcp_user_chk.html>`__
that discusses how the code works internally. That, together with our
general entries in `Hooks Framework
section <https://jenkins.isc.org/job/Kea_doc/doxygen>`__ should give you
some pointers how to extend this library and perhaps even write your own
from scratch.

legal_log: Forensic Logging Hooks
---------------------------------

This section describes the forensic log hooks library. This library
provides hooks that record a detailed log of lease assignments and
renewals into a set of log files. Currently this library is only
available to ISC customers with a support contract.

   **Note**

   This library may only be loaded by ``kea-dhcp4`` or ``kea-dhcp6``
   process.

In many legal jurisdictions companies, especially ISPs, must record
information about the addresses they have leased to DHCP clients. This
library is designed to help with that requirement. If the information
that it records is sufficient it may be used directly. If your
jurisdiction requires that you save a different set of information you
may use it as a template or example and create your own custom logging
hooks.

This logging is done as a set of hooks to allow it to be customized to
any particular need. Modifying a hooks library is easier and safer than
updating the core code. In addition by using the hooks features those
users who don't need to log this information can leave it out and avoid
any performance penalties.

Log File Naming
~~~~~~~~~~~~~~~

The names for the log files have the following form:

::

   path/base-name.CCYYMMDD.txt

The "path" and "base-name" are supplied in the configuration as
described below see `Configuring the Forensic Log
Hooks <#forensic-log-configuration>`__. The next part of the name is the
date the log file was started, with four digits for year, two digits for
month and two digits for day. The file is rotated on a daily basis.

   **Note**

   When running Kea servers for both DHCPv4 and DHCPv6 the log names
   must be distinct. See the examples in `Configuring the Forensic Log
   Hooks <#forensic-log-configuration>`__.

DHCPv4 Log Entries
~~~~~~~~~~~~~~~~~~

For DHCPv4 the library creates entries based on DHCPREQUEST messages and
corresponding DHCPv4 leases intercepted by lease4_select (for new
leases) and lease4_renew (for renewed leases) hooks.

An entry is a single string with no embedded end-of-line markers, a
prepended timestamp and has the following sections:

::

   timestamp address duration device-id {client-info} {relay-info} {user-context}

Where:

-  timestamp - the current date and time the log entry was written in
   "%Y-%m-%d %H:%M:%S %Z" strftime format ("%Z" is the time zone name).

-  address - the leased IPv4 address given out and whether it was
   assigned or renewed.

-  duration - the lease lifetime expressed in days (if present), hours,
   minutes and seconds. A lease lifetime of 0xFFFFFFFF will be denoted
   with the text "infinite duration".

-  device-id - the client's hardware address shown as numerical type and
   hex digit string.

-  client-info - the DHCP client id option (61) if present, shown as a
   hex string.

-  relay-info - for relayed packets the giaddr and the RAI circuit-id,
   remote-id and subscriber-id options (option 82 sub options: 1, 2 and
   6) if present. The circuit id and remote id are presented as hex
   strings

-  user-context - the optional user context associated to the lease.

For instance (line breaks added for readability, they would not be
present in the log file).

::

   2018-01-06 01:02:03 CET Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address:
   hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33,
   identified by circuit-id: 68:6f:77:64:79 and remote-id: 87:f6:79:77:ef

In addition to logging lease activity driven by DHCPv4 client traffic,
it also logs entries for the following lease management control channel
commands: lease4-add, lease4-update, and lease4-del. Each entry is a
single string with no embedded end-of-line markers and they will
typically have the following forms:

``lease4-add:``

::

   *timestamp* Administrator added a lease of address: *address* to a device with hardware address: *device-id*

Dependent on the arguments of the add command, it may also include the
client-id and duration.

Example:

::

   2018-01-06 01:02:03 CET Administrator added a lease of address: 192.0.2.202 to a device with hardware address:
   1a:1b:1c:1d:1e:1f for 1 days 0 hrs 0 mins 0 secs

``lease4-update:``

::

   *timestamp* Administrator updated information on the lease of address: *address* to a device with hardware address: *device-id*

Dependent on the arguments of the update command, it may also include
the client-id and lease duration.

Example:

::

   2018-01-06 01:02:03 CET Administrator updated information on the lease of address: 192.0.2.202 to a device
   with hardware address: 1a:1b:1c:1d:1e:1f, client-id: 1234567890

``lease4-del:`` Deletes have two forms, one by address and one by
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

DHCPv6 Log Entries
~~~~~~~~~~~~~~~~~~

For DHCPv6 the library creates entries based on lease management actions
intercepted by the lease6_select (for new leases), lease6_renew (for
renewed leases) and lease6_rebind (for rebound leases).

An entry is a single string with no embedded end-of-line markers, a
prepended timestamp and has the following sections:

::

   timestamp address duration device-id {relay-info}* {user-context}

Where:

-  timestamp - the current date and time the log entry was written in
   "%Y-%m-%d %H:%M:%S %Z" strftime format ("%Z" is the time zone name).

-  address - the leased IPv6 address or prefix given out and whether it
   was assigned or renewed.

-  duration - the lease lifetime expressed in days (if present), hours,
   minutes and seconds. A lease lifetime of 0xFFFFFFFF will be denoted
   with the text "infinite duration".

-  device-id - the client's DUID and hardware address (if present).

-  relay-info - for relayed packets the content of relay agent messages,
   remote-id (code 37), subscriber-id (code 38) and interface-id (code
   18) options if present. Note that interface-id option, if present,
   identifies the whole interface the relay agent received the message
   on. This typically translates to a single link in your network, but
   it depends on your specific network topology. Nevertheless, this is
   useful information to better scope down the location of the device,
   so it is being recorded, if present.

-  user-context - the optional user context associated to the lease.

For instance (line breaks added for readability, they would not be
present in the log file).

::

   2018-01-06 01:02:03 PST Address:2001:db8:1:: has been assigned for 0 hrs 11 mins 53 secs
   to a device with DUID: 17:34:e2:ff:09:92:54 and hardware address: hwtype=1 08:00:2b:02:3f:4e
   (from Raw Socket) connected via relay at address: fe80::abcd for client on link address: 3001::1,
   hop count: 1, identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f and subscriber-id: 1a:2b:3c:4d:5e:6f

In addition to logging lease activity driven by DHCPv6 client traffic,
it also logs entries for the following lease management control channel
commands: lease6-add, lease6-update, and lease6-del. Each entry is a
single string with no embedded end-of-line markers and they will
typically have the following forms:

``lease6-add:``

::

   *timestamp* Administrator added a lease of address: *address* to a device with DUID: *DUID*

Dependent on the arguments of the add command, it may also include the
hardware address and duration.

Example:

::

   2018-01-06 01:02:03 PST Administrator added a lease of address: 2001:db8::3 to a device with DUID:
   1a:1b:1c:1d:1e:1f:20:21:22:23:24 for 1 days 0 hrs 0 mins 0 secs

``lease6-update:``

::

   *timestamp* Administrator updated information on the lease of address: *address* to a device with DUID: *DUID*

Dependent on the arguments of the update command, it may also include
the hardware address and lease duration.

Example:

::

   2018-01-06 01:02:03 PST Administrator updated information on the lease of address: 2001:db8::3 to a device with
   DUID: 1a:1b:1c:1d:1e:1f:20:21:22:23:24, hardware address: 1a:1b:1c:1d:1e:1f

``lease6-del:`` Deletes have two forms, one by address and one by
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

.. _forensic-log-configuration:

Configuring the Forensic Log Hooks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To use this functionality the hook library must be included in the
configuration of the desired DHCP server modules. The legal_log library
is installed alongside the Kea libraries in ``[kea-install-dir]/lib``
where ``kea-install-dir`` is determined by the "--prefix" option of the
configure script. It defaults to ``/usr/local``. Assuming the default
value then, configuring kea-dhcp4 to load the legal_log library could be
done with the following Kea4 configuration:

::

   "Dhcp4": {
       "hooks-libraries": [
           {
               "library": "/usr/local/lib/libdhcp_legal_log.so",
               "parameters": {
                   "path": "/var/kea/var",
                   "base-name": "kea-forensic4"
               }
           },
           ...
       ]
   }

To configure it for kea-dhcp6, the commands are simply as shown below:

::

   "Dhcp6": {
       "hooks-libraries": [
           {
               "library": "/usr/local/lib/libdhcp_legal_log.so",
               "parameters": {
                   "path": "/var/kea/var",
                   "base-name": "kea-forensic6"
               }
           },
           ...
       ]
   }

Two Hook Library parameters are supported:

-  path - the directory in which the forensic file(s) will be written.
   The default value is ``[prefix]/kea/var``. The directory must exist.

-  base-name - an arbitrary value which is used in conjunction with the
   current system date to form the current forensic file name. It
   defaults to ``kea-legal``.

If it is desired to restrict forensic logging to certain subnets, the
"legal-logging" boolean parameter can be specified within a user context
of these subnets. For example:

::

   "Dhcpv4" {
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

disables legal logging for the subnet "192.0.2.0/24". If this parameter
is not specified, it defaults to 'true', which enables legal logging for
the subnet.

The following example demonstrates how to selectively disable legal
logging for an IPv6 subnet.

::

   "Dhcpv6": {
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

See `??? <#dhcp4-user-contexts>`__ and `??? <#dhcp6-user-contexts>`__ to
learn more about user contexts in Kea configuration.

.. _forensic-log-database:

Database backend
~~~~~~~~~~~~~~~~

Log entries can be inserted into a database when Kea is configured with
database backend support: a table named 'logs' is used with a timestamp
(timeuuid for Cassandra CQL) generated by the database software and a
text log with the same format than for files without the timestamp.

Please refer to `??? <#mysql-database>`__ for MySQL, to
`??? <#pgsql-database>`__ for PostgreSQL or to `??? <#cql-database>`__
for Cassandra CQL. The logs table is part of the Kea database schemas.

Configuration parameters are extended by standard lease database
parameters as defined in `??? <#database-configuration4>`__. The "type"
parameter should be "mysql", "postgresql", "cql" or be "logfile". When
it is absent or set to "logfile" files are used.

This database feature is experimental and will be likely improved, for
instance to add an address / prefix index (currently the only index is
the timestamp). No specific tools is provided to operate the database
but standard tools are applicable, for instance to dump the logs table
from a CQL database:

::

   $ echo 'SELECT dateOf(timeuuid), log FROM logs;' | cqlsh -k database-name

    system.dateof(timeuuid)         | log
   ---------------------------------+---------------------------------------
    2018-01-06 01:02:03.227000+0000 | Address: 192.2.1.100 has been renewed ...
    ...
   (12 rows)
   $

.. _flex-id:

flex_id: Flexible Identifiers for Host Reservations
---------------------------------------------------

This section describes a hook application dedicated to generate flexible
identifiers for host reservation. Kea software provides a way to handle
host reservations that include addresses, prefixes, options, client
classes and other features. The reservation can be based on hardware
address, DUID, circuit-id or client-id in DHCPv4 and using hardware
address or DUID in DHCPv6. However, there are sometimes scenarios where
the reservation is more complex, e.g. uses other options that mentioned
above, uses part of specific options or perhaps even a combination of
several options and fields to uniquely identify a client. Those
scenarios are addressed by the Flexible Identifiers hook application.

Currently this library is only available to ISC customers with a support
contract.

   **Note**

   This library may only be loaded by ``kea-dhcp4`` or ``kea-dhcp6``
   process.

The library allows for defining an expression, using notation initially
used for client classification only. See
`??? <#classification-using-expressions>`__ for detailed description of
the syntax available. One notable difference is that for client
classification the expression currently has to evaluate to either true
or false, while the flexible identifier expression is expected to
evaluate to a string that will be used as identifier. It is a valid case
for the expression to evaluate to empty string (e.g. in cases where a
client does not sent specific options). This expression is then
evaluated for each incoming packet. This evaluation generates an
identifier that is used to identify the client. In particular, there may
be host reservations that are tied to specific values of the flexible
identifier.

The library can be loaded in similar way as other hook libraries. It
takes a mandatory parameter identifier-expression and optional boolean
parameter replace-client-id:

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

EXAMPLE: Let's consider a case of an IPv6 network that has an
independent interface for each of the connected customers. Customers are
able to plug in whatever device they want, so any type of identifier
(e.g. a client-id) is unreliable. Therefore the operator may decide to
use an option inserted by a relay agent to differentiate between
clients. In this particular deployment, the operator verified that the
interface-id is unique for each customer facing interface. Therefore it
is suitable for usage as reservation. However, only the first 6 bytes of
the interface-id are interesting, because remaining bytes are either
randomly changed or not unique between devices. Therefore the customer
decided to use first 6 bytes of the interface-id option inserted by the
relay agent. After adding "flex-id" host-reservation-identifiers goal
can be achieved by using the following configuration:

::

   "Dhcp6": {
       "subnet6": [{ ..., // subnet definition starts here
       "reservations": [
           "flex-id": "'port1234'", // value of the first 8 bytes of the interface-id
           "ip-addresses": [ "2001:db8::1" ]
       ],
       }], // end of subnet definitions
       "host-reservation-identifiers": ["duid", "flex-id"], // add "flex-id" to reservation identifiers
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

NOTE: Care should be taken when adjusting the expression. If the
expression changes, then all the flex-id values may change, possibly
rendering all reservations based on flex-id unusable until they're
manually updated. Therefore it is strongly recommended to start with the
expression and a handful reservations, adjust the expression as needed
and only after it was confirmed the expression does exactly what is
expected out of it go forward with host reservations on any broader
scale.

flex-id values in host reservations can be specified in two ways. First,
they can be expressed as hex string, e.g. bar string can be represented
as 626174. Alternatively, it can be expressed as quoted value (using
double and single quotes), e.g. "'bar'". The former is more convenient
for printable characters, while hex string values are more convenient
for non-printable characters and does not require the use of the
``hexstring`` operator.

::

   "Dhcp6": {
       "subnet6": [{ ..., // subnet definition starts here
       "reservations": [
           "flex-id": "01:02:03:04:05:06", // value of the first 8 bytes of the interface-id
           "ip-addresses": [ "2001:db8::1" ]
       ],
       }], // end of subnet definitions
       "host-reservation-identifiers": ["duid", "flex-id"], // add "flex-id" to reservation identifiers
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

When "replace-client-id" is set to false (which is the default setting),
the flex-id hook library uses evaluated flexible identifier solely for
identifying host reservations, i.e. searching for reservations within a
database. This is a functional equivalent of other identifiers, similar
to hardware address or circuit-id. However, this mode of operation has
an implication that if a client device is replaced, it may cause a
conflict between an existing lease (allocated for old device) and the
new lease being allocated for the new device. The conflict arises
because the same flexible identifier is computed for the replaced device
and the server will try to allocate the same lease. The mismatch between
client identifiers sent by new device and old device causes the server
to refuse this new allocation until the old lease expires. A
manifestation of this problem is dependant on specific expression used
as flexible identifier and is likely to appear if you only use options
and other parameters that are identifying where the device is connected
(e.g. circuit-id), rather than the device identification itself (e.g.
MAC address).

The flex-id library offers a way to overcome the problem with lease
conflicts by dynamically replacing client identifier (or DUID in DHCPv6
case) with a value derived from flexible identifier. The server
processes the client's query as if flexible identifier was sent in the
client identifier (or DUID) option. This guarantees that returning
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
formed by prepending 1 byte with a value of zero to flexible identifier.
In the IPv6 case, it is formed by prepanding two zero bytes before the
flexible identifier.

Note that for this mechanism to take effect, the DHCPv4 server must be
configured to respect the client identifier option value during lease
allocation, i.e. "match-client-id" must be set to true. See
`??? <#dhcp4-match-client-id>`__ for details. No additional settings are
required for DHCPv6.

If "replace-client-id" option is set to true, the value of
"echo-client-id" parameter (that governs whether to send back a
client-id option or not) is ignored.

The `??? <#lease-cmds>`__ section describes commands used to retrieve,
update and delete leases using various identifiers, e.g. "hw-address",
"client-id". The lease_cmds library doesn't natively support querying
for leases by flexible identifier. However, when "replace-client-id" is
set to true, it makes it possible to query for leases using a value
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

where hexadecimal value of "54:64:45:66" is a flexible identifier
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

.. _host-cmds:

host_cmds: Host Commands
------------------------

This section describes a hook application that offers a number of new
commands used to query and manipulate host reservations. Kea provides a
way to store host reservations in a database. In many larger deployments
it is useful to be able to manage that information while the server is
running. This library provides management commands for adding, querying
and deleting host reservations in a safe way without restarting the
server. In particular, it validates the parameters, so an attempt to
insert incorrect data e.g. add a host with conflicting identifier in the
same subnet will be rejected. Those commands are exposed via command
channel (JSON over unix sockets) and Control Agent (JSON over RESTful
interface). Additional commands and capabilities related to host
reservations will be added in the future.

Currently this library is only available to ISC customers with a support
contract.

   **Note**

   This library may only be loaded by ``kea-dhcp4`` or ``kea-dhcp6``
   process.

Currently five commands are supported: reservation-add (which adds new
host reservation), reservation-get (which returns existing reservation
if specified criteria are matched), reservation-get-all (which returns
all reservations in a specified subnet), reservation-get-page (variant
of reservation-get-all which returns all reservations in a specified
subnet by pages) and reservation-del (which attempts to delete a
reservation matching specified criteria). To use commands that change
the reservation information (currently these are reservation-add and
reservation-del, but this rule applies to other commands that may be
implemented in the future), hosts database must be specified (see
hosts-databases description in `??? <#hosts-databases-configuration4>`__
and `??? <#hosts-databases-configuration6>`__) and it must not operate
in read-only mode. If the hosts-databases are not specified or are
running in read-only mode, the host_cmds library will load, but any
attempts to use reservation-add or reservation-del will fail.

Additional host reservation commands are planned in the future. For a
description of envisaged commands, see `Control API
Requirements <https://gitlab.isc.org/isc-projects/kea/wikis/designs/commands>`__
document.

All commands are using JSON syntax. They can be issued either using
control channel (see `??? <#ctrl-channel>`__) or via Control Agent (see
`??? <#kea-ctrl-agent>`__).

The library can be loaded in similar way as other hook libraries. It
does not take any parameters. It supports both DHCPv4 and DHCPv6
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

The subnet-id parameter
~~~~~~~~~~~~~~~~~~~~~~~

Prior to diving into the individual commands, it is worth discussing the
parameter, ``subnet-id``. Currently it is mandatory for all of the
commands supplied by this library. Prior to Kea 1.5.0, reservations had
to belong to specific subnet. Beginning with Kea 1.5.0, reservations may
now be specified globally. In other words, they are not specific to any
subnet. When reservations are supplied via the configuration file, the
ID of the containing subnet (or lack thereof) is implicit in the
configuration structure. However, when managing reservations using the
host commands, it is necessary to explicitly identify the scope to which
the reservation belongs. This is done via the ``subnet-id`` parameter.
For global reservations, use a value of zero (0). For reservations
scoped to a specific subnet, use that subnet's ID.

.. _command-reservation-add:

reservation-add command
~~~~~~~~~~~~~~~~~~~~~~~

``reservation-add`` allows for the insertion of a new host. It takes a
set of arguments that vary depending on the nature of the host
reservation. Any parameters allowed in the configuration file that
pertain to host reservation are permitted here. For details regarding
IPv4 reservations, see `??? <#host-reservation-v4>`__ and
`??? <#host-reservation-v6>`__. The ``subnet-id`` is manadatory. Use a
value of zero (0) to add a global reservation, or the id of the subnet
to which the reservation should be added. An example command can be as
simple as:

::

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

but can also take many more parameters, for example:

::

   {
       "command": "reservation-add",
       "arguments": {
           "reservation":
               {
                   "subnet-id":1,
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

Here is an example of complex IPv6 reservation:

::

   {
       "command": "reservation-add",
       "arguments": {
           "reservation":
               {
                   "subnet-id":1,
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
or a failure (result 1). Failed command always includes text parameter
that explains the cause of failure. Example results:

::

   { "result": 0, "text": "Host added." }

Example failure:

::

   { "result": 1, "text": "Mandatory 'subnet-id' parameter missing." }

As ``reservation-add`` is expected to store the host, hosts-databases
parameter must be specified in your configuration and databases must not
run in read-only mode. In the future versions it will be possible to
modify the reservations read from a configuration file. Please contact
ISC if you are interested in this functionality.

.. _command-reservation-get:

reservation-get command
~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get`` can be used to query the host database and retrieve
existing reservations. There are two types of parameters this command
supports: (subnet-id, address) or (subnet-id, identifier-type,
identifier). The first type of query is used when the address (either
IPv4 or IPv6) is known, but the details of the reservation aren't. One
common use case of this type of query is to find out whether a given
address is reserved or not. The second query uses identifiers. For
maximum flexibility, Kea stores the host identifying information as a
pair of values: type and the actual identifier. Currently supported
identifiers are "hw-address", "duid", "circuit-id", "client-id" and
"flex-id", but additional types may be added in the future. If any new
identifier types are defined in the future, reservation-get command will
support them automatically. The ``subnet-id`` is mandatory. Use a value
of zero (0) to fetch a global reservation, or the id of the subnet to
which the reservation belongs.

An example command for getting a host reservation by (subnet-id,
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

``reservation-get`` typically returns result 0 when the query was
conducted properly. In particular, 0 is returned when the host was not
found. If the query was successful a number of host parameters will be
returned. An example of a query that did not find the host looks as
follows:

::

   { "result": 0, "text": "Host not found." }

An example result returned when the host was found:

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

An example result returned when the query was malformed:

::

   { "result": 1, "text": "No 'ip-address' provided and 'identifier-type'
                           is either missing or not a string." }

.. _command-reservation-get-all:

reservation-get-all command
~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-all`` can be used to query the host database and
retrieve all reservations in a specified subnet. This command uses
parameters providing the mandatory subnet-id. Global host reservations
can be retrieved by using subnet-id value of zero (0).

For instance for retrieving host reservations for the subnet 1:

::

   {
       "command": "reservation-get-all",
       "arguments": {
           "subnet-id": 1
        }
   }

returns found some IPv4 hosts:

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
reservation-get-all. If there are many reservations in a subnet, this
may be disruptive. Use with caution. For larger deployments, please
consider using ``reservation-get-page`` instead (see
`reservation-get-page command <#command-reservation-get-page>`__).

For a reference, see `??? <#ref-reservation-get-all>`__.

.. _command-reservation-get-page:

reservation-get-page command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``reservation-get-page`` can be used to query the host database and
retrieve all reservations in a specified subnet by pages. This command
uses parameters providing the mandatory subnet-id. Use a value of zero
(0) to fetch global reservations. The second mandatory parameter is the
page size limit. Optional source-index and from host id, both defaulting
to 0, are uses to chain page queries.

The usage of from and source-index parameters requires additional
explanation. For the first call those parameters should not be specified
(or specified as zeros). For any follow up calls they should be set to
the values returned in previous calls in a next map holding from and
source-index values. The subsequent calls should be issued until all
reservations are returned. The end is reached once the returned list is
empty, count is 0, no next map is present and result status 3 (empty) is
returned.

   **Note**

   The from and source-index parameters are reflecting internal state of
   the search. There is no need to understand what they represent, it's
   simply a value that is supposed to be copied from one response to the
   next query. However, if you are curious, from field represents a 64
   bits representation of host identifier used by a host backend. The
   source-index represents internal representation of multiple host
   backends: 0 is used to represent hosts defined in a configuration
   file, 1 represents the first database backend. In some uncommon cases
   there may be more than one database backend configured, so
   potentially there may be 2. In any case, Kea will iterate over all
   backends configured.

For instance for retrieving host reservations for the subnet 1
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

Some hosts are returned with informations to get the next page:

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

Note that from and source-index fields were specified in the response in
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

. The response will contain a list of hosts with updated source-index
and from fields. Continue calling the command until you get the last
page. Its response will look like this:

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
users retrieve larger host reservations lists by smaller chunks. For
small deployments with few reservations, is it easier to use
``reservation-get-all`` (see `reservation-get-all
command <#command-reservation-get-all>`__.

For a reference, see `??? <#ref-reservation-get-page>`__.

   **Note**

   Currently ``reservation-get-page`` is not supported by the Cassandra
   host backend.

.. _command-reservation-del:

reservation-del command
~~~~~~~~~~~~~~~~~~~~~~~

``reservation-del`` can be used to delete a reservation from the host
database. There are two types of parameters this command supports:
(subnet-id, address) or (subnet-id, identifier-type, identifier). The
first type of query is used when the address (either IPv4 or IPv6) is
known, but the details of the reservation aren't. One common use case of
this type of query is to remove a reservation (e.g. you want a specific
address to no longer be reserved). The second query uses identifiers.
For maximum flexibility, Kea stores the host identifying information as
a pair of values: type and the actual identifier. Currently supported
identifiers are "hw-address", "duid", "circuit-id", "client-id" and
"flex-id", but additional types may be added in the future. If any new
identifier types are defined in the future, reservation-get command will
support them automatically. The ``subnet-id`` is manadatory. Use a value
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

``reservation-del`` returns result 0 when the host deletion was
successful or 1 if it was not. A descriptive text is provided in case of
error. Example results look as follows:

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
----------------------------

This section describes a hook application that offers a number of new
commands used to query and manipulate subnet and shared network
configurations in Kea. This application is very useful in deployments
with a large number of subnets being managed by the DHCP servers and
when the subnets are frequently updated. The commands offer lightweight
approach for manipulating subnets without a need to fully reconfigure
the server and without affecting existing servers' configurations. An
ability to manage shared networks (listing, retrieving details, adding
new ones, removing existing ones, adding subnets to and removing from
shared networks) is also provided.

Currently this library is only available to ISC customers with a support
contract.

   **Note**

   This library may only be loaded by ``kea-dhcp4`` or ``kea-dhcp6``
   process.

The following commands are currently supported:

-  ``subnet4-list/subnet6-list``: lists all configured subnets

-  ``subnet4-get/subnet6-get``: retrieves detailed information about a
   specified subnet

-  ``subnet4-add/subnet6-add``: adds new subnet into server's
   configuration

-  ``subnet4-update/subnet6-update``: updates subnet in server's
   configuration

-  ``subnet4-del/subnet6-del``: removes a subnet from the server's
   configuration

-  ``network4-list/network6-list``: lists all configured shared networks

-  ``network4-get/network6-get``: retrieves detailed information about
   specified shared network

-  ``network4-add/network6-add``: adds a new shared network to the
   server's configuration

-  ``network4-del/network6-del``: removes a shared network from the
   server's configuration

-  ``network4-subnet-add/network6-subnet-add``: adds existing subnet to
   existing shared network

-  ``network4-subnet-del/network6-subnet-del``: removes a subnet from
   existing shared network and demotes it to a plain subnet.

.. _command-subnet4-list:

subnet4-list command
~~~~~~~~~~~~~~~~~~~~

This command is used to list all currently configured subnets. The
subnets are returned in a brief form, i.e. a subnet identifier and
subnet prefix is included for each subnet. In order to retrieve the
detailed information about the subnet the ``subnet4-get`` should be
used.

This command has the simple structure:

::

   {
       "command": "subnet4-list"
   }

The list of subnets returned as a result of this command is returned in
the following format:

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

subnet6-list command
~~~~~~~~~~~~~~~~~~~~

This command is used to list all currently configured subnets. The
subnets are returned in a brief form, i.e. a subnet identifier and
subnet prefix is included for each subnet. In order to retrieve the
detailed information about the subnet the ``subnet6-get`` should be
used.

This command has the simple structure:

::

   {
       "command": "subnet6-list"
   }

The list of subnets returned as a result of this command is returned in
the following format:

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

subnet4-get command
~~~~~~~~~~~~~~~~~~~

This command is used to retrieve detailed information about the
specified subnet. This command usually follows the ``subnet4-list``,
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

subnet6-get command
~~~~~~~~~~~~~~~~~~~

This command is used to retrieve detailed information about the
specified subnet. This command usually follows the ``subnet6-list``,
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

subnet4-add
~~~~~~~~~~~

This command is used to create and add new subnet to the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier must be specified and must be unique among all subnets. If
the identifier or a subnet prefix is not unique an error is reported and
the subnet is not added.

The subnet information within this command has the same structure as the
subnet information in the server configuration file with the exception
that static host reservations must not be specified within
``subnet4-add``. The commands described in `host_cmds: Host
Commands <#host-cmds>`__ should be used to add, remove and modify static
reservations.

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

subnet6-add
~~~~~~~~~~~

This command is used to create and add new subnet to the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier must be specified and must be unique among all subnets. If
the identifier or a subnet prefix is not unique an error is reported and
the subnet is not added.

The subnet information within this command has the same structure as the
subnet information in the server configuration file with the exception
that static host reservations must not be specified within
``subnet6-add``. The commands described in `host_cmds: Host
Commands <#host-cmds>`__ should be used to add, remove and modify static
reservations.

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

It is recommended, but not mandatory to specify subnet id. If not
specified, Kea will try to assign the next subnet-id value. This
automatic ID value generator is simple. It returns a previously
automatically assigned value increased by 1. This works well, unless you
manually create a subnet with a value bigger than previously used. For
example, if you call subnet4-add five times, each without id, Kea will
assign IDs: 1,2,3,4 and 5 and it will work just fine. However, if you
try to call subnet4-add five times, with the first subnet having
subnet-id of value 3 and remaining ones having no subnet-id, it will
fail. The first command (with explicit value) will use subnet-id 3, the
second command will create a subnet with id of 1, the third will use
value of 2 and finally the fourth will have the subnet-id value
auto-generated as 3. However, since there is already a subnet with that
id, it will fail.

The general recommendation is to either: never use explicit values (so
the auto-generated values will always work) or always use explicit
values (so the auto-generation is never used). You can mix those two
approaches only if you understand how the internal automatic subnet-id
generation works.

   **Note**

   Subnet IDs must be greater than zero and less than 4294967295.

.. _command-subnet4-update:

subnet4-update
~~~~~~~~~~~~~~

This command is used to update a subnet in the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier is used to identify the subnet to replace, it must be
specified and must be unique among all subnets. The subnet prefix should
not be updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file with the exception
that static host reservations must not be specified within
``subnet4-update``. The commands described in `host_cmds: Host
Commands <#host-cmds>`__ should be used to update, remove and modify
static reservations.

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

subnet6-update
~~~~~~~~~~~~~~

This command is used to update a subnet in the existing server
configuration. This operation has no impact on other subnets. The subnet
identifier is used to identify the subnet to replace, it must be
specified and must be unique among all subnets. The subnet prefix should
not be updated.

The subnet information within this command has the same structure as the
subnet information in the server configuration file with the exception
that static host reservations must not be specified within
``subnet6-update``. The commands described in `host_cmds: Host
Commands <#host-cmds>`__ should be used to update, remove and modify
static reservations.

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

subnet4-del command
~~~~~~~~~~~~~~~~~~~

This command is used to remove a subnet from the server's configuration.
This command has no effect on other configured subnets but removing a
subnet has certain implications which the server's administrator should
be aware of.

In most cases the server has assigned some leases to the clients
belonging to the subnet. The server may also be configured with static
host reservations which are associated with this subnet. The current
implementation of the ``subnet4-del`` removes neither the leases nor
host reservations associated with a subnet. This is the safest approach
because the server doesn't loose track of leases assigned to the clients
from this subnet. However, removal of the subnet may still cause
configuration errors and conflicts. For example: after removal of the
subnet, the server administrator may update a new subnet with the ID
used previously for the removed subnet. This means that the existing
leases and static reservations will be in conflict with this new subnet.
Thus, we recommend that this command is used with extreme caution.

This command can also be used to completely delete an IPv4 subnet that
is part of a shared network. If you want to simply remove the subnet
from a shared network and keep the subnet configuration, use
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

subnet6-del command
~~~~~~~~~~~~~~~~~~~

This command is used to remove a subnet from the server's configuration.
This command has no effect on other configured subnets but removing a
subnet has certain implications which the server's administrator should
be aware of.

In most cases the server has assigned some leases to the clients
belonging to the subnet. The server may also be configured with static
host reservations which are associated with this subnet. The current
implementation of the ``subnet6-del`` removes neither the leases nor
host reservations associated with a subnet. This is the safest approach
because the server doesn't loose track of leases assigned to the clients
from this subnet. However, removal of the subnet may still cause
configuration errors and conflicts. For example: after removal of the
subnet, the server administrator may add a new subnet with the ID used
previously for the removed subnet. This means that the existing leases
and static reservations will be in conflict with this new subnet. Thus,
we recommend that this command is used with extreme caution.

This command can also be used to completely delete an IPv6 subnet that
is part of a shared network. If you want to simply remove the subnet
from a shared network and keep the subnet configuration, use
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

network4-list, network6-list commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to retrieve full list of currently configured
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

network4-get, network6-get commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to retrieve detailed information about shared
networks, including subnets currently being part of a given network.
Both commands take one mandatory parameter ``name``, which specify the
name of shared network. An example command to retrieve details about
IPv4 shared network with a name "floor13" looks as follows:

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
               "reservation-mode": "all",
               "subnet4": [
                   {
                       "subnet": "192.0.2.0/24",
                       "id": 5,
                       // many other subnet specific details here
                   },
                   {
                       "id": 6,
                       "subnet": "192.0.3.0/31",
                       // many other subnet specific details here
                   }
               ],
               "valid-lifetime": 120
           }
           ]
       }
   }

Note that actual response contains many additional fields that are
omitted here for clarity. The response format is exactly the same as
used in ``config-get``, just is limited to returning shared networks
information.

.. _command-network4-add:

network4-add, network6-add commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to add a new shared network. New network has to
have unique name. This command requires one parameter
``shared-networks``, which is a list and should contain exactly one
entry that defines the network. The only mandatory element for a network
is its name. Although it does not make operational sense, it is allowed
to add an empty shared network that does not have any subnets in it.
That is allowed for testing purposes, but having empty networks (or with
only one subnet) is discouraged in production environments. For details
regarding syntax, see `??? <#shared-network4>`__ and
`??? <#shared-network6>`__.

   **Note**

   As opposed to parameter inheritance during full new configuration
   processing, this command does not fully handle parameter inheritance
   and any missing parameters will be filled with default values, rather
   than inherited from global scope.

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

Assuming there was no shared network with a name floor13 and no subnets
with id 100 and 101 previously configured, the command will be
successful and will return the following response:

::

   {
       "arguments": {
           "shared-networks": [ { "name": "floor13" } ]
       },
       "result": 0,
       "text": "A new IPv4 shared network 'floor13' added"
   }

The ``network6-add`` uses the same syntax for both the query and the
response. However, there are some parameters that are IPv4-only (e.g.
match-client-id) and some are IPv6-only (e.g. interface-id). The same
applies to subnets within the network.

.. _command-network4-del:

network4-del, network6-del commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete existing shared networks. Both
commands take exactly one parameter 'name' that specifies the name of
the network to be removed. An example invocation of ``network4-del``
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
whether the subnets be demoted to plain subnets or removed. An example
usage in network6-del command that deletes the shared network and all
subnets in it could looks like as follows:

::

   {
       "command": "network4-del",
       "arguments": {
           "name": "floor13",
           "subnets-action": "delete"
       }
   }

Alternatively, if you want to completely remove the subnets, you may use
``subnet4-del`` or ``subnet6-del`` commands.

.. _command-network4-subnet-add:

network4-subnet-add, network6-subnet-add commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to add existing subnets to existing shared
networks. There are several ways to add new shared network. System
administrator can add the whole shared network at once, either by
editing a configuration file or by calling ``network4-add`` or
``network6-add`` commands with desired subnets in it. This approach
works better for completely new shared subnets. However, there may be
cases when an existing subnet is running out of addresses and needs to
be extended with additional address space. In other words another subnet
has to be added on top of it. For this scenario, a system administrator
can use ``network4-add`` or ``network6-add`` and then add existing
subnet to this newly created shared network using
``network4-subnet-add`` or ``network6-subnet-add``.

The ``network4-subnet-add`` and ``network6-subnet-add`` commands take
two parameters: ``id``, which is an integer and specifies subnet-id of
existing subnet to be added to a shared network; and ``name``, which
specifies name of the shared network the subnet will be added to. The
subnet must not belong to any existing network. In case you want to
reassign a subnet from one shared network to another, please use
``network4-subnet-del`` or ``network6-subnet-del`` commands first.

An example invocation of ``network4-subnet-add`` command looks as
follows:

::

   {
       "command": "network4-subnet-add",
       "arguments": {
           "name": "floor13",
           "id": 5
       }
   }

Assuming there is a network named 'floor13', there is a subnet with
subnet-id 5 and it is not a part of existing network, the command will
return a response similar to the following:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now part of shared network 'floor1'"
   }

The ``network6-subnet-add`` command uses exactly the same syntax for
both the command and the response.

   **Note**

   As opposed to parameter inheritance during full new configuration
   processing or when adding a new shared network with new subnets, this
   command does not fully handle parameter inheritance and any missing
   parameters will be filled with default values, rather than inherited
   from global scope or from the shared network.

.. _command-network4-subnet-del:

network4-subnet-del, network6-subnet-del commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to remove a subnet that is part of existing
shared network and demote it to a plain, stand-alone subnet. If you want
to remove a subnet completely, use ``subnet4-del`` or ``subnet6-del``
commands instead. The ``network4-subnet-del`` and
``network6-subnet-del`` commands take two parameters: ``id``, which is
an integer and specifies subnet-id of existing subnet to be removed from
a shared network; and ``name``, which specifies name of the shared
network the subnet will be removed from.

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

Assuming there was a subnet with subnet-id equal to 5 that was part of a
shared network named 'floor13', the response would look similar to the
following:

::

   {
       "result": 0,
       "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now removed from shared network 'floor13'"
   }

The ``network6-subnet-del`` command uses exactly the same syntax for
both the command and the response.


.. include:: hooks-class-cmds.rst
.. include:: hooks-cb-cmds.rst
.. include:: hooks-ha.rst
.. include:: hooks-stat-cmds.rst
.. include:: hooks-radius.rst
.. include:: hooks-host-cache.rst


.. _user-context:

User contexts
=============

Hook libraries can have their own configuration parameters. That is
convenient if the parameter applies to the whole library. However,
sometimes it is very useful if certain configuration entities are
extended with additional configuration data. This is where the concept
of user contexts comes in. A sysadmin can define an arbitrary set of
data and attach it to Kea structures, as long as the data is specified
as JSON map. In particular, it is possible to define fields that are
integers, strings, boolean, lists and maps. It is possible to define
nested structures of arbitrary complexity. Kea does not use that data on
its own, simply stores and makes it available for the hook libraries.

Another use case for user contexts may be storing comments and other
information that will be retained by Kea. Regular comments are discarded
when configuration is loaded, but user contexts are retained. This is
useful if you want your comments to survive config-set, config-get
operations for example.

If user context is supported in a given context, the parser translates
"comment" entries into user context with a "comment" entry. The pretty
print of a configuration does the opposite operation and puts "comment"
entries at the beginning of maps as it seems to be the common usage.

As of Kea 1.3, the structures that allow user contexts are pools of all
types (addresses and prefixes) and subnets. Kea 1.4 extended user
context support to the global scope, interfaces config, shared networks,
subnets, client classes, option datas and definitions, host
reservations, control socket, dhcp ddns, loggers and server id. These
are supported in both DHCPv4 and DHCPv6 at the exception of server id
which is DHCPv6 only.
