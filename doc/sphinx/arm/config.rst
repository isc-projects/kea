.. _kea-config:

*****************
Kea Configuration
*****************

Kea uses JSON structures to represent server configurations. The
following sections describe how the configuration structures are
organized.

.. _json:

JSON Configuration
==================

JSON is the notation used throughout the Kea project. The most obvious
usage is for the configuration file, but JSON is also used for sending
commands over the Management API (see :ref:`ctrl-channel`) and for
communicating between DHCP servers and the DDNS update daemon.

Typical usage assumes that the servers are started from the command
line, either directly or using a script, e.g. ``keactrl``. The
configuration file is specified upon startup using the ``-c`` parameter.

.. _json-format:

JSON Syntax
-----------

Configuration files for the DHCPv4, DHCPv6, DDNS, Control Agent, and
NETCONF modules are defined in an extended JSON format. Basic JSON is
defined in `RFC 7159 <https://tools.ietf.org/html/rfc7159>`__ and `ECMA
404 <https://www.ecma-international.org/publications/standards/Ecma-404.htm>`__.
In particular, the only boolean values allowed are true or false (all
lowercase). The capitalized versions (True or False) are not accepted.

Even though the JSON standard (ECMA 404) does not require JSON objects
(i.e. name/value maps) to have unique entries, Kea implements them
using a C++ STL map with unique entries. Therefore, if there are multiple
values for the same name in an object/map, the last value overwrites previous values.
Since Kea 1.9.0, configuration file parsers raise a syntax error in such cases.

Kea components use extended JSON with additional features allowed:

-  Shell comments: any text after the hash (#) character is ignored.

-  C comments: any text after the double slashes (//) character is
   ignored.

-  Multiline comments: any text between /\* and \*/ is ignored. This
   comment can span multiple lines.

-  File inclusion: JSON files can include other JSON files by using a
   statement of the form \<?include "file.json"?\>.

-  Extra commas: to remove the inconvenience of errors caused by leftover commas
   after making changes to configuration. While parsing, a warning is printed
   with the location of the comma to give the user the ability to correct a
   potential mistake.

.. warning::

   These features are meant to be used in a JSON configuration file.
   Their usage in any other way may result in errors.

The configuration file consists of a single object (often colloquially
called a map) started with a curly bracket. It comprises only one of
the "Dhcp4", "Dhcp6", "DhcpDdns", "Control-agent", or "Netconf" objects.
It is possible to define additional elements but they will be ignored.

A very simple configuration for DHCPv4 could look like this:

::

   # The whole configuration starts here.
   {
       # DHCPv4 specific configuration starts here.
       "Dhcp4": {
           "interfaces-config": {
               "interfaces": [ "eth0" ],
               "dhcp-socket-type": "raw"
           },
           "valid-lifetime": 4000,
           "renew-timer": 1000,
           "rebind-timer": 2000,
           "subnet4": [{
              "pools": [ { "pool": "192.0.2.1-192.0.2.200" } ],
              "subnet": "192.0.2.0/24"
           }],

          # Now loggers are inside the DHCPv4 object.
          "loggers": [{
               "name": "*",
               "severity": "DEBUG"
           }]
       }

   # The whole configuration structure ends here.
   }

More examples are available in the installed ``share/doc/kea/examples``
directory.

To avoid repetition of mostly similar structures, examples in the rest
of this guide will showcase only the subset of parameters appropriate
for a given context. For example, when discussing the IPv6 subnets
configuration in DHCPv6, only subnet6 parameters will be mentioned. It
is implied that the remaining elements (the global map that holds Dhcp6)
are present, but they are omitted for clarity. Usually,
locations where extra parameters may appear are denoted by an ellipsis
(...).

.. _user-context:

Comments and User Context
-------------------------

Shell, C, or C++ style comments are all permitted in the JSON configuration file if
the file is used locally. This is convenient and works in simple cases where
the configuration is kept statically using a local file. However, since comments
are not part of JSON syntax, most JSON tools detect them as
errors. Another problem with them is that once Kea loads its configuration, the
shell, C, and C++ style comments are ignored. If commands such as
``config-get`` or ``config-write`` are used, those comments are lost. An example of such
comments was presented in the previous section.

Historically, to address the problem, Kea code allowed the use of `comment` strings
as valid JSON entities. This had the benefit of being retained through various
operations (such as ``config-get``), or allowing processing by JSON tools. An
example JSON comment looks like this:

::

   "Dhcp4": {
       "subnet4": [{
           "subnet": "192.0.2.0/24",
           "pools": [{ "pool": "192.0.2.10 - 192.0.2.20" }],
           "comment": "second floor"
       }]
   }

However, the facts that the comment could only be a single line, and that it was not
possible to add any other information in a more structured form, were frustrating. One specific
example was a request to add floor levels and building numbers to subnets. This
was one of the reasons why the concept of user context was introduced. It
allows adding an arbitrary JSON structure to most Kea configuration structures.

This has a number of benefits compared to earlier approaches. First, it is fully
compatible with JSON tools and Kea commands. Second, it allows storing simple
comment strings, but it can also store much more complex data, such as
multiple lines (as a string array), extra typed data (such as floor numbers being
actual numbers), and more. Third, the data is exposed to hooks, so it is possible
to develop third-party hooks that take advantage of that extra information. An
example user context looks like this:

::

   "Dhcp4": {
       "subnet4": [{
           "subnet": "192.0.2.0/24",
           "pools": [{ "pool": "192.0.2.10 - 192.0.2.20" }],
           "user-context": {
               "comment": "second floor",
               "floor": 2
           }
       }]
   }

User contexts can store an arbitrary data file as long as it has valid JSON
syntax and its top-level element is a map (i.e. the data must be enclosed in
curly brackets). However, some hook libraries may expect specific formatting;
please consult the specific hook library documentation for details.

In a sense the user-context mechanism has superseded the JSON comment
capabilities; ISC encourages administrators to use user-context instead of
the older mechanisms. To promote this way of storing comments, Kea compared
converts JSON comments to user-context on the fly.

However, if the configuration uses the old JSON
comment, the ``config-get`` command returns a slightly modified
configuration. It is not uncommon for a call for ``config-set`` followed by a
``config-get`` to receive a slightly different structure.
The best way to avoid this problem is simply to abandon JSON comments and
use user-context.

Kea supports user contexts at the following levels: global scope,
interfaces configuration, shared networks,
subnets, client classes, option data and definitions, host
reservations, control socket, DHCP-DDNS, loggers, leases, and server ID. These
are supported in both DHCPv4 and DHCPv6, with the exception of server ID,
which is DHCPv6 only.

User context can be added and edited in structures supported by commands.

We encourage Kea users to utilize these functions to store information
used by other systems and custom hooks.

For example, the `subnet4-update` command can be used to add user context data
to an existing subnet.

::

   "subnet4": [ {
      "id": 1,
      "subnet": "10.20.30.0/24",
      "user-context": {
         "building": "Main"
         "floor": 1
         }
    } ]

The same can be done with many other commands like lease6-add etc.

Kea also uses user context to store non-standard data.
Currently, only :ref:`dhcp4-store-extended-info` uses this feature.

When enabled, it adds the ISC key in `user-context` to differentiate automatically
added content.

Example of relay information stored in a lease:

::

   {
   "arguments": {
      "client-id": "42:42:42:42:42:42:42:42",
      "cltt": 12345678,
      "fqdn-fwd": false,
      "fqdn-rev": true,
      "hostname": "myhost.example.com.",
      "hw-address": "08:08:08:08:08:08",
      "ip-address": "192.0.2.1",
      "state": 0,
      "subnet-id": 44,
      "valid-lft": 3600
      "user-context": {
         "ISC": {
         "relays": [
         {
               "hop": 2,
               "link": "2001:db8::1",
               "peer": "2001:db8::2"
         },
         {
               "hop": 1,
               "link": "2001:db8::3",
               "options": "0x00C800080102030405060708",
               "peer": "2001:db8::4"
         }]
         }
      }
   }


User context can store configuration for multiple hooks and comments at once.

For a discussion about user context used in hooks, see :ref:`user-context-hooks`.


Simplified Notation
-------------------

It is sometimes convenient to refer to a specific element in the
configuration hierarchy. Each hierarchy level is separated by a slash.
If there is an array, a specific instance within that array is
referenced by a number in square brackets (with numbering starting at
zero). For example, in the above configuration the valid-lifetime in the
Dhcp4 component can be referred to as Dhcp4/valid-lifetime, and the pool
in the first subnet defined in the DHCPv4 configuration as
Dhcp4/subnet4[0]/pool.


.. include:: config-backend.rst


Configuration Files Inclusion
-----------------------------

The parser provides the ability to include files. The syntax was chosen
to look similar to how Apache includes PHP scripts in HTML code. This particular
syntax was chosen to emphasize that the include directive is an additional
feature and not a part of JSON syntax.

The inclusion is implemented as a stack of files. You can use the include directive
in nested includes. Up to ten nesting levels are supported. This arbitrarily chosen
limit is protection against recursive inclusions.

The include directive has the form:

::

   <?include "[PATH]"?>

The *[PATH]* pattern should be replaced with an absolute path or a path relative to
the current working directory at the time the Kea process was launched.

To include one file from another, use the following syntax:

.. code-block:: javascript

   {
      "Dhcp6": {
         "interfaces-config": {
            "interfaces": [ "*" ]},
         "preferred-lifetime": 3000,
         "rebind-timer": 2000,
         "renew-timer": 1000,
         <?include "subnets.json"?>
         "valid-lifetime": 4000
      }
   }

where the content of "subnets.json" may be:

::

   "subnet4": [
      {
         "id": 123,
         "subnet": "192.0.2.0/24"
      },
      {
         "id": 234,
         "subnet": "192.0.3.0/24"
      },
      {
         "id": 345,
         "subnet": "10.0.0.0/8"
      }
   ],
