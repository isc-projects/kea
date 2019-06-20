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
Netconf modules are defined in an extended JSON format. Basic JSON is
defined in :ref:`RFC 7159 <http://tools.ietf.org/html/rfc7159>` and :ref:`ECMA
404 <http://www.ecma-international.org/publications/standards/Ecma-404.htm>`.
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

   **Note**

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
