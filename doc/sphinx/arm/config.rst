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
configuration file is specified upon startup using the -c parameter.

.. _json-format:

JSON Syntax
-----------

Configuration files for the DHCPv4, DHCPv6, DDNS, Control Agent, and
NETCONF modules are defined in an extended JSON format. Basic JSON is
defined in `RFC 7159 <https://tools.ietf.org/html/rfc7159>`__ and `ECMA
404 <https://www.ecma-international.org/publications/standards/Ecma-404.htm>`__.
In particular, the only boolean values allowed are true or false (all
lowercase). The capitalized versions (True or False) are not accepted.

Kea components use an extended JSON with additional features allowed:

-  shell comments: any text after the hash (#) character is ignored.

-  C comments: any text after the double slashes (//) character is
   ignored.

-  Multiline comments: any text between /\* and \*/ is ignored. This
   commenting can span multiple lines.

-  File inclusion: JSON files can include other JSON files by using a
   statement of the form \<?include "file.json"?\>.

The configuration file consists of a single object (often colloquially
called a map) started with a curly bracket. It comprises one or more of
the "Dhcp4", "Dhcp6", "DhcpDdns", "Control-agent", and "Netconf" objects.
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

 .. note::

   The "Logging" element is removed in Kea 1.6.0 and its contents (the
   "loggers" object) moved inside the configuration objects (maps) for the
   respective Kea modules. For example: the "Dhcp4" map contains the
   "loggers" object specifying logging configuration for the DHCPv4
   server. Backward compatibility is maintained until at least Kea 1.7.0
   release; it will be possible to specify the "Logging" object at the top
   configuration level and "loggers" objects at the module configuration
   level. Ultimately, support for the top-level "Logging" object will be
   removed.

   The specification of several supported elements (e.g. "Dhcp4",
   "Dhcp6") in a single configuration file can be confusing and works
   badly with the commands that fetch and write new configurations.
   Support for it will be removed in a future release of Kea, after
   which each component will require its own configuration file.

To avoid repetition of mostly similar structures, examples in the rest
of this guide will showcase only the subset of parameters appropriate
for a given context. For example, when discussing the IPv6 subnets
configuration in DHCPv6, only subnet6 parameters will be mentioned. It
is implied that the remaining elements (the global map that holds Dhcp6
and Logging) are present, but they are omitted for clarity. Usually,
locations where extra parameters may appear are denoted by an ellipsis
(...).

.. _user-context:

Comments and User Context
-------------------------

You can specify shell, C or C++ style comments in the JSON configuration file if
you use the file locally. This is convenient and works in simple cases where
your configuration is kept statically using local file. However, since comments
are not part of JSON syntax, most JSON tools will detect them as
errors. Another problem with them is once Kea loads its configuration, the
shell, C and C++ style comments are ignored. If you use commands such as
`config-get` or `config-write`, those comments will be lost. An example of such
comments has been presented in the previous section.

Historically, to address the problem Kea code allowed to put `comment` strings
as valid JSON entities. This had the benefit of being retained through various
operations (such as `config-get`) or allowed processing by JSON tools. An
example JSON comment looks like this:

::

   "Dhcp4": {
       "subnet4": [{
           "subnet": "192.0.2.0/24",
           "pools": [{ "pool": "192.0.2.10 - 192.0.2.20" }],
           "comment": "second floor"
       }]
   }

However, users complained that the comment is only a single line and it's not
possible to add any other information in more structured form. One specific
example was a request to add floor levels and building numbers to subnets. This
was one of the reasons why the concept of user context has been introduced. It
allows adding arbitrary JSON structure to most Kea configuration structures. It
has a number of benefits compared to earlier approaches. First, it is fully
compatible with JSON tools and Kea commands. Second, it allows storing simple
comment strings if you want to, but it can store much more complex data, such as
multiple lines (as string array), extra typed data (such as floor numbers being
actual numbers) and more. Third, the data is exposed to hooks, so it's possible
to develop third party hooks that take advantage of that extra information. An
example user context would look like this:

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

In a sense the user context mechanism has superseeded the JSON comment
capabilities. ISC would like to encourage people to use user-context in favor of
the older mechanisms and we hope to deprecate JSON comments one day in the
future. To promote this way of storing comments, Kea code is able to understand
JSON comments, but converts them to user context on the fly. For the time being,
the comments entries in user-context are converted back to JSON comments to keep
backward compatibility, but that conversion is expected to go away soon.

The is one side effect, however. If your configuration uses the old JSON
comment, the `config-get` command will return a slightly modified
configuration. Don't be surprised if you call `config-set` followed by a
`config-get` and receive a slightly different structure. If this bothers you,
the best way to avoid this problem is simply abandon JSON comments and start
using user-context.

For a discussion about user context used in hooks, see :ref:`user-context-hooks`.


Simplified Notation
-------------------

It is sometimes convenient to refer to a specific element in the
configuration hierarchy. Each hierarchy level is separated by a slash.
If there is an array, a specific instance within that array is
referenced by a number in square brackets (with numbering starting at
zero). For example, in the above configuration the valid-lifetime in the
Dhcp4 component can be referred to as Dhcp4/valid-lifetime and the pool
in the first subnet defined in the DHCPv4 configuration as
Dhcp4/subnet4[0]/pool.


.. include:: config-backend.rst
