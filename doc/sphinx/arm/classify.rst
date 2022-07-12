.. _classify:

*********************
Client Classification
*********************

Client Classification Overview
==============================

In certain cases it is useful to differentiate among different types
of clients and treat them accordingly. Common reasons include:

-  The clients represent different pieces of topology, e.g. a cable
   modem is not the same as the clients behind that modem.

-  The clients have different behavior, e.g. a smartphone behaves
   differently from a laptop.

-  The clients require different values for some options, e.g. a
   docsis3.0 cable modem requires different settings from a docsis2.0
   cable modem.

To make management easier, different clients can be grouped into a
client class to receive common options.

An incoming packet can be associated with a client class in several
ways:

-  Implicitly, using a vendor class option or another built-in condition.

-  Using an expression which evaluates to ``true``.

-  Using static host reservations, a shared network, a subnet, etc.

-  Using a hook.

Client classification can be used to change the behavior of almost any
part of the DHCP message processing. There are currently six
mechanisms that take advantage of client classification: dropping
queries, subnet selection, pool selection, definition of DHCPv4
private (codes 224-254) and code 43 options, assignment of different
options, and, for DHCPv4 cable modems, the setting of specific options
for use with the TFTP server address and the boot file field.

.. _classify-classification-steps:

Classification Steps
--------------------

The classification process is conducted in several steps:

1.  The ``ALL`` class is associated with the incoming packet.

2.  Vendor class options are processed.

3.  Classes with matching expressions and not marked for later evaluation ("on
    request" or depending on the ``KNOWN``/``UNKNOWN`` built-in classes)
    are processed in the order they are defined in the
    configuration; the boolean expression is evaluated and, if it
    returns ``true`` (a match), the incoming packet is associated with the
    class.

4.  If a private or code 43 DHCPv4 option is received, it is decoded
    following its client-class or global (or, for option 43,
    last-resort) definition.

5.  When the incoming packet belongs to the special class ``DROP``, it is
    dropped and an informational message is logged with the packet
    information.

.. note::

    The ``pkt4_receive`` and ``pkt6_receive`` callouts are called here.

6.  When the ``early-global-reservations-lookup`` global parameter is
    configured to true global reservations are looked for and the 8, 9
    and 10 steps are partially performed: the lookup is limited to
    global reservations, if one is found the ``KNOWN`` class is set
    but if none is found the ``UNKNOWN`` class is **not** set.

7.  A subnet is chosen, possibly based on the class information when
    some subnets are reserved. More precisely: when choosing a subnet,
    the server iterates over all of the subnets that are feasible given
    the information found in the packet (client address, relay address,
    etc.). It uses the first subnet it finds that either has no
    class associated with it, or has a class which matches one of the
    packet's classes.

.. note::

    The ``subnet4_select`` and ``subnet6_select`` callouts are called here.

8.  The server looks for host reservations. If an identifier from the
    incoming packet matches a host reservation in the subnet or shared
    network, the packet is associated with the ``KNOWN`` class and all
    classes of the host reservation. If a reservation is not found, the
    packet is assigned to the ``UNKNOWN`` class.

9.  Classes with matching expressions - directly, or indirectly using the
    ``KNOWN``/``UNKNOWN`` built-in classes and not marked for later evaluation ("on
    request") - are processed in the order they are defined
    in the configuration; the boolean expression is evaluated and, if it
    returns ``true`` (a match), the incoming packet is associated with the
    class. After a subnet is selected, the server determines whether
    there is a reservation for a given client. Therefore, it is not
    possible to use the ``UNKNOWN`` class to select a shared network or
    a subnet. For the ``KNOWN`` class only global reservations only
    global reservations are used and the ``early-global-reservations-lookup``
    parameter must be configured to true

10. When the incoming packet belongs to the special class ``DROP``, it is
    dropped and an informational message is logged with the packet
    information. Since Kea version 1.9.8, it is permissible to make the ``DROP``
    class dependent on the ``KNOWN``/``UNKNOWN`` classes.

11. If needed, addresses and prefixes from pools are assigned, possibly
    based on the class information when some pools are reserved for
    class members.

.. note::

    The ``lease4_select``, ``lease4_renew``, ``lease6_select``, ``lease6_renew``, and ``lease6_rebind``
    callouts are called here.

12. Classes marked as "required" are evaluated in the order in which
    they are listed: first the shared network, then the subnet, and
    finally the pools that assigned resources belong to.

13. Options are assigned, again possibly based on the class information
    in the order that classes were associated with the incoming packet.
    For DHCPv4 private and code 43 options, this includes option
    definitions specified within classes.

.. note::

   Client classes in Kea follow the order in which they are specified in
   the configuration (vs. alphabetical order). Required classes follow
   the order in which they are required.

When determining which options to include in the response, the server
examines the union of options from all of the assigned classes. If two
or more classes include the same option, the value from the first class
examined is used; classes are examined in the order they were
associated, so ``ALL`` is always the first class and matching required
classes are last.

As an example, imagine that an incoming packet matches two classes.
Class ``foo`` defines values for an NTP server (option 42 in DHCPv4) and
an SMTP server (option 69 in DHCPv4), while class ``bar`` defines values
for an NTP server and a POP3 server (option 70 in DHCPv4). The server
examines the three options - NTP, SMTP, and POP3 - and returns any that
the client requested. As the NTP server was defined twice, the server
chooses only one of the values for the reply; the class from which the
value is obtained is determined as explained in the previous paragraph.

.. note::

   Care should be taken with client classification, as it is easy for
   clients that do not meet any class criteria to be denied service
   altogether.

.. _classification-using-vendor:

Built-in Client Classes
=======================

Some classes are built-in, so they do not need to be defined.
Vendor class information is the primary example: the server checks whether an
incoming DHCPv4 packet includes the vendor class identifier option (60)
or an incoming DHCPv6 packet includes the vendor class option (16). If
it does, the content of that option is prepended with ``VENDOR_CLASS_``
and the result is interpreted as a class. For example, modern cable
modems send this option with value ``docsis3.0``, so the packet belongs to
class ``VENDOR_CLASS_docsis3.0``.

The ``HA_`` prefix is used by the High Availability hook library to
designate certain servers to process DHCP packets as a result of load
balancing. The class name is constructed by prepending the ``HA_`` prefix
to the name of the server which should process the DHCP packet. This
server uses an appropriate pool or subnet to allocate IP addresses
(and/or prefixes), based on the assigned client classes. The details can
be found in :ref:`hooks-high-availability`.

The ``BOOTP`` class is used by the BOOTP hook library to classify and
respond to inbound BOOTP queries.

The ``SKIP_DDNS`` class is used by the DDNS-tuning hook library to suppress
DDNS updates on a per client basis.

Other examples are the ``ALL`` class, to which all incoming packets belong,
and the ``KNOWN`` class, assigned when host reservations exist for a
particular client. By convention, the names of built-in classes begin with all
capital letters.

Currently recognized built-in class names are ``ALL``, ``KNOWN`` and ``UNKNOWN``,
and the prefixes ``VENDOR_CLASS_``, ``HA_``, ``AFTER_``, ``EXTERNAL_``,
``SKIP_DDNS``. Although the ``AFTER_`` prefix is a provision for an
as-yet-unwritten hook, the ``EXTERNAL_`` prefix can be freely used; built-in
classes are implicitly defined so they never raise warnings if they do not
appear in the configuration.

.. _classification-using-expressions:

Using Expressions in Classification
===================================

The expression portion of a classification definition contains operators
and values. All values are currently strings; operators take a string or
strings and return another string. When all the operations have
completed, the result should be a value of ``true`` or ``false``. The packet
belongs to the class (and the class name is added to the list of
classes) if the result is ``true``. Expressions are written in standard
format and can be nested.

Expressions are pre-processed during the parsing of the configuration
file and converted to an internal representation. This allows certain
types of errors to be caught and logged during parsing. Examples of
these errors include an incorrect number or type of argument to an
operator. The evaluation code also checks for this class of error and
generally throws an exception, though this should not occur in a
normally functioning system.

Other issues, such as the starting position of a substring being
outside of the substring or an option not existing in the packet, result
in the operator returning an empty string.

Dependencies between classes are also checked. For instance, forward
dependencies are rejected when the configuration is parsed; an
expression can only depend on already-defined classes (including built-in
classes) which are evaluated in a previous or the same evaluation phase.
This does not apply to the ``KNOWN`` or ``UNKNOWN`` classes.

.. table:: List of classification values

   +-----------------------+-------------------------------+-----------------------+
   | Name                  | Example expression            | Example value         |
   +=======================+===============================+=======================+
   | String literal        | 'example'                     | 'example'             |
   +-----------------------+-------------------------------+-----------------------+
   | Hexadecimal string    | 0x5a7d                        | 'Z}'                  |
   | literal               |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | IP address literal    | 10.0.0.1                      | 0x0a000001            |
   +-----------------------+-------------------------------+-----------------------+
   | Integer literal       | 123                           | '123'                 |
   +-----------------------+-------------------------------+-----------------------+
   | Binary content of the | option[123].hex               | '(content of the      |
   | option                |                               | option)'              |
   +-----------------------+-------------------------------+-----------------------+
   | Option existence      | option[123].exists            | 'true'                |
   +-----------------------+-------------------------------+-----------------------+
   | Binary content of the | option[12].option[34].hex     | '(content of the      |
   | sub-option            |                               | sub-option)'          |
   +-----------------------+-------------------------------+-----------------------+
   | Sub-Option existence  | option[12].option[34].exists  | 'true'                |
   +-----------------------+-------------------------------+-----------------------+
   | Client class          | member('foobar')              | 'true'                |
   | membership            |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Known client          | known                         | member('KNOWN')       |
   +-----------------------+-------------------------------+-----------------------+
   | Unknown client        | unknown                       | not member('KNOWN')   |
   +-----------------------+-------------------------------+-----------------------+
   | DHCPv4 relay agent    | relay4[123].hex               | '(content of the RAI  |
   | sub-option            |                               | sub-option)'          |
   +-----------------------+-------------------------------+-----------------------+
   | DHCPv6 Relay Options  | relay6[nest].option[code].hex | (value of the option) |
   +-----------------------+-------------------------------+-----------------------+
   | DHCPv6 Relay Peer     | relay6[nest].peeraddr         | 2001:DB8::1           |
   | Address               |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | DHCPv6 Relay Link     | relay6[nest].linkaddr         | 2001:DB8::1           |
   | Address               |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Interface name of     | pkt.iface                     | eth0                  |
   | packet                |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Source address of     | pkt.src                       | 10.1.2.3              |
   | packet                |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Destination address   | pkt.dst                       | 10.1.2.3              |
   | of packet             |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Length of packet      | pkt.len                       | 513                   |
   +-----------------------+-------------------------------+-----------------------+
   | Hardware address in   | pkt4.mac                      | 0x010203040506        |
   | DHCPv4 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Hardware length in    | pkt4.hlen                     | 6                     |
   | DHCPv4 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Hardware type in      | pkt4.htype                    | 6                     |
   | DHCPv4 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | ciaddr field in       | pkt4.ciaddr                   | 192.0.2.1             |
   | DHCPv4 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | giaddr field in       | pkt4.giaddr                   | 192.0.2.1             |
   | DHCPv4 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | yiaddr field in       | pkt4.yiaddr                   | 192.0.2.1             |
   | DHCPv4 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | siaddr field in       | pkt4.siaddr                   | 192.0.2.1             |
   | DHCPv4 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Message type in       | pkt4.msgtype                  | 1                     |
   | DHCPv4 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Transaction ID (xid)  | pkt4.transid                  | 12345                 |
   | in DHCPv4 packet      |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Message type in       | pkt6.msgtype                  | 1                     |
   | DHCPv6 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Transaction ID in     | pkt6.transid                  | 12345                 |
   | DHCPv6 packet         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Vendor option         | vendor[*].exists              | true                  |
   | existence (any        |                               |                       |
   | vendor)               |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Vendor option         | vendor[4491].exists           | true                  |
   | existence (specific   |                               |                       |
   | vendor)               |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Enterprise-id from    | vendor.enterprise             | 4491                  |
   | vendor option         |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Vendor sub-option     | vendor[4491].option[1].exists | true                  |
   | existence             |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Vendor sub-option     | vendor[4491].option[1].hex    | docsis3.0             |
   | content               |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Vendor class option   | vendor-class[*].exist         | true                  |
   | existence (any        | s                             |                       |
   | vendor)               |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Vendor class option   | vendor-class[4491].exists     | true                  |
   | existence (specific   |                               |                       |
   | vendor)               |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Enterprise-id from    | vendor-class.enterprise       | 4491                  |
   | vendor class option   |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | First data chunk from | vendor-class[4491].data       | docsis3.0             |
   | vendor class option   |                               |                       |
   +-----------------------+-------------------------------+-----------------------+
   | Specific data chunk   | vendor-class[4491].data[3]    | docsis3.0             |
   | from vendor class     |                               |                       |
   | option                |                               |                       |
   +-----------------------+-------------------------------+-----------------------+

Notes:

-  Hexadecimal strings are converted into a string as expected. The
   starting "0X" or "0x" is removed, and if the string is an odd number
   of characters a "0" is prepended to it.

-  IP addresses are converted into strings of length 4 or 16. IPv4,
   IPv6, and IPv4-embedded IPv6 (e.g. IPv4-mapped IPv6) addresses are
   supported.

-  Integers in an expression are converted to 32-bit unsigned integers
   and are represented as four-byte strings; for example, 123 is
   represented as 0x0000007b. All expressions that return numeric values
   use 32-bit unsigned integers, even if the field in the packet is
   smaller. In general, it is easier to use decimal notation to
   represent integers, but it is also possible to use hexadecimal
   notation. When writing an integer in hexadecimal, care should be
   taken to make sure the value is represented as 32 bits, e.g. use
   0x00000001 instead of 0x1 or 0x01. Also, make sure the value is
   specified in network order, e.g. 1 is represented as 0x00000001.

-  ``option[code].hex`` extracts the value of the option with the code
   ``code`` from the incoming packet. If the packet does not contain the
   option, it returns an empty string. The string is presented as a byte
   string of the option payload, without the type code or length fields.

-  ``option[code].exists`` checks whether an option with the code ``code``
   is present in the incoming packet. It can be used with empty options.

-  ``member('foobar')`` checks whether the packet belongs to the client
   class ``foobar``. To avoid dependency loops, the configuration file
   parser verifies whether client classes were already defined or are
   built-in, i.e., beginning with ``VENDOR_CLASS_``, ``AFTER_`` (for the
   to-come "after" hook) and ``EXTERNAL_`` or equal to ``ALL``, ``KNOWN``,
   ``UNKNOWN``, etc.

   ``known`` and ``unknown`` are shorthand for ``member('KNOWN')`` and ``not
   member('KNOWN')``. Note that the evaluation of any expression using
   the ``KNOWN`` class (directly or indirectly) is deferred after the host
   reservation lookup (i.e. when the ``KNOWN`` or ``UNKNOWN`` partition is
   determined).

-  ``relay4[code].hex`` attempts to extract the value of the sub-option
   ``code`` from the option inserted as the DHCPv4 Relay Agent Information
   (82) option. If the packet does not contain a RAI option, or the RAI
   option does not contain the requested sub-option, the expression
   returns an empty string. The string is presented as a byte string of
   the option payload without the type code or length fields. This
   expression is allowed in DHCPv4 only.

-  ``relay4`` shares the same representation types as ``option``; for
   instance, ``relay4[code].exists`` is supported.

-  ``relay6[nest]`` allows access to the encapsulations used by any DHCPv6
   relays that forwarded the packet. The ``nest`` level specifies the
   relay from which to extract the information, with a value of 0
   indicating the relay closest to the DHCPv6 server. Negative values
   allow relays to be specified counting from the DHCPv6 client, with -1 indicating
   the relay closest to the client. If the requested
   encapsulation does not exist, an empty string ``""`` is returned. This
   expression is allowed in DHCPv6 only.

-  ``relay6[nest].option[code]`` shares the same representation types as
   ``option``; for instance, ``relay6[nest].option[code].exists`` is
   supported.

-  Expressions starting with ``pkt4`` can be used only in DHCPv4. They
   allow access to DHCPv4 message fields.

-  ``pkt6`` refers to information from the client request. To access any
   information from an intermediate relay, use ``relay6``. ``pkt6.msgtype``
   and ``pkt6.transid`` output a 4-byte binary string for the message type
   or transaction ID. For example, the message type ``SOLICIT`` is
   ``0x00000001`` or simply 1, as in ``pkt6.msgtype == 1``.

-  "Vendor option" means the Vendor-Identifying Vendor-Specific Information
   option in DHCPv4 (code 125; see `Section 4 of RFC
   3925 <https://tools.ietf.org/html/rfc3925#section-4>`__) and the
   Vendor-Specific Information Option in DHCPv6 (code 17, defined in
   `Section 21.17 of RFC
   8415 <https://tools.ietf.org/html/rfc8415#section-21.17>`__). "Vendor
   class option" means the Vendor-Identifying Vendor Class Option in DHCPv4
   (code 124; see `Section 3 of RFC
   3925 <https://tools.ietf.org/html/rfc3925#section-3>`__) in DHCPv4 and
   the Class Option in DHCPv6 (code 16; see `Section 21.16 of RFC
   8415 <https://tools.ietf.org/html/rfc8415#section-21.16>`__). Vendor
   options may have sub-options that are referenced by their codes.
   Vendor class options do not have sub-options, but rather data chunks,
   which are referenced by index value. Index 0 means the first data
   chunk, index 1 is for the second data chunk (if present), etc.

-  In the vendor and vendor-class constructs an asterisk (*) or 0 can be
   used to specify a wildcard ``enterprise-id`` value, i.e. it will match
   any ``enterprise-id`` value.

-  Vendor Class Identifier (option 60 in DHCPv4) can be accessed using the
   option[60] expression.

-  `RFC 3925 <https://tools.ietf.org/html/rfc3925>`__ and `RFC
   8415 <https://tools.ietf.org/html/rfc8415>`__ allow for multiple
   instances of vendor options to appear in a single message. The client
   classification code currently examines the first instance if more
   than one appear. For the ``vendor.enterprise`` and ``vendor-class.enterprise``
   expressions, the value from the first instance is returned. Please
   submit a feature request on the
   `Kea GitLab site <https://gitlab.isc.org/isc-projects/kea>`__ to request
   support for multiple instances.

.. table:: List of classification expressions

   +-----------------------+-------------------------+-----------------------+
   | Name                  | Example                 | Description           |
   +=======================+=========================+=======================+
   | Equal                 | 'foo' == 'bar'          | Compare the two       |
   |                       |                         | values and return     |
   |                       |                         | `true` or `false`     |
   +-----------------------+-------------------------+-----------------------+
   | Not                   | not ('foo' == 'bar')    | Logical negation      |
   +-----------------------+-------------------------+-----------------------+
   | And                   | ('foo' == 'bar') and    | Logical and           |
   |                       | ('bar' == 'foo')        |                       |
   +-----------------------+-------------------------+-----------------------+
   | Or                    | ('foo' == 'bar') or     | Logical or            |
   |                       | ('bar' == 'foo')        |                       |
   +-----------------------+-------------------------+-----------------------+
   | Substring             | substring('foobar',0,3) | Return the requested  |
   |                       |                         | substring             |
   +-----------------------+-------------------------+-----------------------+
   | Concat                | concat('foo','bar')     | Return the            |
   |                       |                         | concatenation of the  |
   |                       |                         | strings               |
   +-----------------------+-------------------------+-----------------------+
   | Concat (operator +)   | 'foo' + 'bar'           | Return the            |
   |                       |                         | concatenation of the  |
   |                       |                         | strings               |
   +-----------------------+-------------------------+-----------------------+
   | Ifelse                | ifelse('foo' ==         | Return the branch     |
   |                       | 'bar','us','them')      | value according to    |
   |                       |                         | the condition         |
   +-----------------------+-------------------------+-----------------------+
   | Hexstring             | hexstring('foo', '-')   | Converts the value to |
   |                       |                         | a hexadecimal string, |
   |                       |                         | e.g. 0a:1b:2c:3e      |
   +-----------------------+-------------------------+-----------------------+
   | Split                 | split('foo.bar', '.', 2)| Return the second     |
   |                       |                         | field, splitting on   |
   |                       |                         | dots.                 |
   +-----------------------+-------------------------+-----------------------+

.. table:: List of conversion-to-text expressions

   +-----------------------+---------------------------+------------------------+
   | Name                  | Example                   | Description            |
   +=======================+===========================+========================+
   | AddressToText         | addrtotext (192.10.0.1)   | Represent the 4 bytes  |
   |                       | addrtotext (2003:db8::)   | of an IPv4 address or  |
   |                       |                           | the 16 bytes of an     |
   |                       |                           | IPv6 address in human  |
   |                       |                           | readable format        |
   +-----------------------+---------------------------+------------------------+
   | Int8ToText            | int8totext (-1)           | Represents the 8-bit   |
   |                       |                           | signed integer in text |
   |                       |                           | format                 |
   +-----------------------+---------------------------+------------------------+
   | Int16ToText           | int16totext (-1)          | Represents the 16-bit  |
   |                       |                           | signed integer in text |
   |                       |                           | format                 |
   +-----------------------+---------------------------+------------------------+
   | Int32ToText           | int32totext (-1)          | Represents the 32-bit  |
   |                       |                           | signed integer in text |
   |                       |                           | format                 |
   +-----------------------+---------------------------+------------------------+
   | UInt8ToText           | uint8totext (255)         | Represents the 8-bit   |
   |                       |                           | unsigned integer in    |
   |                       |                           | text format            |
   +-----------------------+---------------------------+------------------------+
   | UInt16ToText          | uint16totext (65535)      | Represents the 16-bit  |
   |                       |                           | unsigned integer in    |
   |                       |                           | text format            |
   +-----------------------+---------------------------+------------------------+
   | UInt32ToText          | uint32totext (4294967295) | Represents the 32-bit  |
   |                       |                           | unsigned integer in    |
   |                       |                           | text format            |
   +-----------------------+---------------------------+------------------------+

Notes:

The conversion operators can be used to transform data from binary to the text
representation. The only requirement is that the input data type length matches
an expected value.

The ``AddressToText`` token expects 4 bytes for IPv4 addresses or 16 bytes for IPv6
addresses. The ``Int8ToText`` and ``UInt8ToText`` tokens expect 1 byte, the ``Int16ToText`` and
``UInt16ToText`` tokens expect 2 bytes, and ``Int32ToText`` and ``UInt32ToText`` expect 4 bytes.
For all conversion tokens, if the data length is 0, the result string is empty.

Logical Operators
-----------------

The Not, And, and Or logical operators are the common operators. Not has
the highest precedence and Or the lowest. And and Or are (left)
associative. Parentheses around a logical expression can be used to
enforce a specific grouping; for instance, in "A and (B or C)". Without
parentheses, "A and B or C" means "(A and B) or C".

Substring
---------

The substring operator ``substring(value, start, length)`` accepts both
positive and negative values for the starting position and the length.
For ``start``, a value of 0 is the first byte in the string while -1 is
the last byte. If the starting point is outside of the original string
an empty string is returned. ``length`` is the number of bytes to extract.
A negative number means to count towards the beginning of the string but
does not include the byte pointed to by ``start``. The special value ``all``
means to return all bytes from start to the end of the string. If the length
is longer than the remaining portion of the string, then the entire
remaining portion is returned. Some examples may be helpful:
::

           substring('foobar', 0, 6) == 'foobar'
           substring('foobar', 3, 3) == 'bar'
           substring('foobar', 3, all) == 'bar'
           substring('foobar', 1, 4) == 'ooba'
           substring('foobar', -5, 4) == 'ooba'
           substring('foobar', -1, -3) == 'oba'
           substring('foobar', 4, -2) == 'ob'
           substring('foobar', 10, 2) == ''


Concat
------

The concat function ``concat(string1, string2)`` returns the concatenation
of its two arguments. For instance:
::

           concat('foo', 'bar') == 'foobar'

For user convenience, Kea version 1.9.8 added an associative operator
version of the concat function. For instance:
::

           'abc' + 'def' + 'ghi' + 'jkl' + '...'

is the same as:
::

           concat(concat(concat(concat('abc', 'def'), 'ghi'), 'jkl'), '...')

or:
::

           concat('abc', concat('def', concat('ghi', concat('jkl', '...'))))

or:
::

           'abcdefghijkl...'

Split
---------

The Split operator ``split(value, delimiters, field-number)`` accepts a list
of characters to use as delimiters and a positive field number of the
desired field when the value is split into fields separated by the delimiters.
Adjacent delimiters are not compressed out, rather they result in an empty
string for that field number. If value is an empty string, the result will be an
empty string. If the delimiters list is empty, the result will be the original
value. If the field-number is less than one or larger than the number of
fields, the result will be an empty string. Some examples follow:
::

           split ('one.two..four', '.', 1) == 'one'
           split ('one.two..four', '.', 2) == 'two'
           split ('one.two..four', '.', 3) == ''
           split ('one.two..four', '.', 4) == 'four'
           split ('one.two..four', '.', 5) == ''

Ifelse
------

The ifelse function ``ifelse(cond, iftrue, ifelse)`` returns the ``iftrue``
or ``ifelse`` branch value following the boolean condition ``cond``. For
instance:
::

            ifelse(option[230].exists, option[230].hex, 'none')


Hexstring
---------

The hexstring function ``hexstring(binary, separator)`` returns the binary
value as its hexadecimal string representation: pairs of hexadecimal
digits separated by the separator, e.g ``':'``, ``'-'``, ``''`` (empty separator).
::

             hexstring(pkt4.mac, ':')


.. note::

   The expression for each class is executed on each packet received. If
   the expressions are overly complex, the time taken to execute them
   may impact the performance of the server. Administrators who need complex or
   time-consuming expressions should consider writing a
   :ref:`hook <hooks-libraries>` to perform the necessary work.

.. _classification-configuring:

Configuring Classes
===================

A class contains five items: a name, a test expression, option data,
an option definition, and an ``only-if-required`` flag. The name must exist and
must be unique among all classes. The test expression, option data and
definition, and ``only-if-required`` flag are optional.

The test expression is a string containing the logical expression used
to determine membership in the class. The entire expression is in double
quotes (").

The option data is a list which defines any options that should be
assigned to members of this class.

The option definition is for DHCPv4 option 43
(:ref:`dhcp4-vendor-opts`) and DHCPv4 private options
(:ref:`dhcp4-private-opts`).

Usually the test expression is evaluated before subnet selection, but in
some cases it is useful to evaluate it later when the subnet,
shared network, or pools are known but output-option processing has not yet
been done. The ``only-if-required`` flag, which is ``false`` by default, allows the
evaluation of the test expression only when it is required, i.e. in a
``require-client-classes`` list of the selected subnet, shared network, or
pool.

The ``require-client-classes`` list, which is valid for shared-network,
subnet, and pool scope, specifies the classes which are evaluated in the
second pass before output-option processing. The list is built in the
reversed precedence order of option data, i.e. an option data item in a
subnet takes precedence over one in a shared network, but required class in
a subnet is added after one in a shared network. The mechanism is
related to the ``only-if-required`` flag but it is not mandatory that the
flag be set to ``true``.

In the following example, the class named "Client_foo" is defined. It is
comprised of all clients whose client IDs (option 61) start with the
string "foo". Members of this class will be given 192.0.2.1 and
192.0.2.2 as their domain name servers.

::

   "Dhcp4": {
       "client-classes": [
           {
               "name": "Client_foo",
               "test": "substring(option[61].hex,0,3) == 'foo'",
               "option-data": [
                   {
                       "name": "domain-name-servers",
                       "code": 6,
                       "space": "dhcp4",
                       "csv-format": true,
                       "data": "192.0.2.1, 192.0.2.2"
                   }
               ]
           },
           ...
       ],
       ...
   }

The next example shows a client class being defined for use by the DHCPv6
server. In it the class named "Client_enterprise" is defined. It is
comprised of all clients whose client identifiers start with the given
hex string (which would indicate a DUID based on an enterprise ID of
0xAABBCCDD). Members of this class will be given 2001:db8:0::1 and
2001:db8:2::1 as their domain name servers.

::

   "Dhcp6": {
       "client-classes": [
           {
               "name": "Client_enterprise",
               "test": "substring(option[1].hex,0,6) == 0x0002AABBCCDD",
               "option-data": [
                   {
                       "name": "dns-servers",
                       "code": 23,
                       "space": "dhcp6",
                       "csv-format": true,
                       "data": "2001:db8:0::1, 2001:db8:2::1"
                   }
               ]
           },
           ...
       ],
       ...
   }

.. _classification-using-host-reservations:

Using Static Host Reservations in Classification
================================================

Classes can be statically assigned to the clients using techniques
described in :ref:`reservation4-client-classes` and
:ref:`reservation6-client-classes`.

Subnet host reservations are searched after subnet selection.
Global host reservations are searched at the same time by default but
the ``early-global-reservations-lookup`` allows to change this behavior
into searching them before the subnet selection.

Pool selection is performed after all host reservations lookups.

.. _classification-subnets:

Configuring Subnets With Class Information
==========================================

In certain cases it is beneficial to restrict access to certain subnets
only to clients that belong to a given class, using the ``client-class``
keyword when defining the subnet.

Let's assume that the server is connected to a network segment that uses
the 192.0.2.0/24 prefix. The administrator of that network has decided
that addresses from the range 192.0.2.10 to 192.0.2.20 will be
managed by the DHCP4 server. Only clients belonging to client class
"Client_foo" are allowed to use this subnet. Such a configuration can be
achieved in the following way:

::

   "Dhcp4": {
       "client-classes": [
           {
               "name": "Client_foo",
               "test": "substring(option[61].hex,0,3) == 'foo'",
               "option-data": [
                   {
                       "name": "domain-name-servers",
                       "code": 6,
                       "space": "dhcp4",
                       "csv-format": true,
                       "data": "192.0.2.1, 192.0.2.2"
                   }
               ]
           },
           ...
       ],
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [ { "pool": "192.0.2.10 - 192.0.2.20" } ],
               "client-class": "Client_foo"
           },
           ...
       ],,
       ...
   }

The following example shows how to restrict access to a DHCPv6 subnet. This
configuration restricts use of the addresses in the range 2001:db8:1::1 to
2001:db8:1::FFFF to members of the "Client_enterprise" class.

::

   "Dhcp6": {
       "client-classes": [
           {
               "name": "Client_enterprise",
               "test": "substring(option[1].hex,0,6) == 0x0002AABBCCDD",
               "option-data": [
                   {
                       "name": "dns-servers",
                       "code": 23,
                       "space": "dhcp6",
                       "csv-format": true,
                       "data": "2001:db8:0::1, 2001:db8:2::1"
                   }
               ]
           },
           ...
       ],
       "subnet6": [
           {
               "subnet": "2001:db8:1::/64",
               "pools": [ { "pool": "2001:db8:1::-2001:db8:1::ffff" } ],
               "client-class": "Client_enterprise"
           }
       ],
       ...
   }

.. _classification-pools:

Configuring Pools With Class Information
========================================

Similar to subnets, in certain cases access to certain address or prefix
pools must be restricted to only clients that belong to a given class,
using the ``client-class`` when defining the pool.

Let's assume that the server is connected to a network segment that uses
the 192.0.2.0/24 prefix. The administrator of that network has decided
that addresses from the range 192.0.2.10 to 192.0.2.20 are going to be
managed by the DHCP4 server. Only clients belonging to client class
"Client_foo" are allowed to use this pool. Such a configuration can be
achieved in the following way:

::

   "Dhcp4": {
       "client-classes": [
           {
               "name": "Client_foo",
               "test": "substring(option[61].hex,0,3) == 'foo'",
               "option-data": [
                   {
                       "name": "domain-name-servers",
                       "code": 6,
                       "space": "dhcp4",
                       "csv-format": true,
                       "data": "192.0.2.1, 192.0.2.2"
                   }
               ]
           },
           ...
       ],
       "subnet4": [
           {
               "subnet": "192.0.2.0/24",
               "pools": [
                   {
                       "pool": "192.0.2.10 - 192.0.2.20",
                       "client-class": "Client_foo"
                   }
               ]
           },
           ...
       ],,

   }

The following example shows how to restrict access to an address pool. This
configuration restricts use of the addresses in the range 2001:db8:1::1 to
2001:db8:1::FFFF to members of the "Client_enterprise" class.

::

   "Dhcp6": {
       "client-classes": [
           {
               "name": "Client_enterprise_",
               "test": "substring(option[1].hex,0,6) == 0x0002AABBCCDD",
               "option-data": [
                   {
                       "name": "dns-servers",
                       "code": 23,
                       "space": "dhcp6",
                       "csv-format": true,
                       "data": "2001:db8:0::1, 2001:db8:2::1"
                   }
               ]
           },
           ...
       ],
       "subnet6": [
           {
               "subnet": "2001:db8:1::/64",

               "pools": [
                   {
                       "pool": "2001:db8:1::-2001:db8:1::ffff",
                       "client-class": "Client_foo"
                   }
               ]
           },
           ...
       ],
       ...
   }

Using Classes
=============

Currently classes can be used for two functions: they can supply options
to members of the class, and they can be used to choose a subnet from
which an address will be assigned to a class member.

When options are defined as part of the class definition
they override any global options that may be defined, and
in turn will be overridden by any options defined for an
individual subnet.

Classes and Hooks
=================

Hooks may be used to classify packets. This may be useful if the
expression would be complex or time-consuming to write, and could be
better or more easily written as code. Once the hook has added the proper class name
to the packet, the rest of the classification system will work as expected
in choosing a subnet and selecting options. For a description of hooks,
see :ref:`hooks-libraries`; for information on configuring classes,
see :ref:`classification-configuring` and :ref:`classification-subnets`.

Debugging Expressions
=====================

While constructing classification expressions, administrators may find
it useful to enable logging; see :ref:`logging` for a more complete
description of the logging facility.

To enable the debug statements in the classification system,
the severity must be set to ``DEBUG`` and the debug level to at least 55.
The specific loggers are ``kea-dhcp4.eval`` and ``kea-dhcp6.eval``.

To understand the logging statements, it is essential to understand a bit about
how expressions are evaluated; for a more complete description, refer to
[the design document](https://gitlab.isc.org/isc-projects/kea/-/wikis/designs/client-classification-design).
In brief, there are two structures used during the evaluation of an
expression: a list of tokens which represent the expressions, and a value
stack which represents the values being manipulated.

The list of tokens is created when the configuration file is processed,
with most expressions and values being converted to a token. The list is
organized in reverse Polish notation. During execution, the list is
traversed in order; as each token is executed, it is able to pop
values from the top of the stack and eventually push its result on the
top of the stack. Imagine the following expression:

::

          "test": "substring(option[61].hex,0,3) == 'foo'",


This will result in the following tokens:

::

          option, number (0), number (3), substring, text ('foo'), equals


In this example, the first three tokens will simply push values onto the
stack. The substring token will then remove those three values and
compute a result that it places on the stack. The text option also
places a value on the stack, and finally the equals token removes the two
tokens on the stack and places its result on the stack.

When debug logging is enabled, each time a token is evaluated it
emits a log message indicating the values of any objects that were popped
off of the value stack, and any objects that were pushed onto the value
stack.

The values are displayed as either text, if the command is known to
use text values, or hexadecimal, if the command either uses binary values
or can manipulate either text or binary values. For expressions that pop
multiple values off the stack, the values are displayed in the order
they were popped. For most expressions this will not matter, but for the
concat expression the values are displayed in reverse order from their
written order in the expression.

Let us assume that the following test has been entered into the
configuration. This example skips most of the configuration to
concentrate on the test.

::

          "test": "substring(option[61].hex,0,3) == 'foo'",


The logging might then resemble this:

::

      2016-05-19 13:35:04.163 DEBUG [kea.eval/44478] EVAL_DEBUG_OPTION Pushing option 61 with value 0x666F6F626172
      2016-05-19 13:35:04.164 DEBUG [kea.eval/44478] EVAL_DEBUG_STRING Pushing text string '0'
      2016-05-19 13:35:04.165 DEBUG [kea.eval/44478] EVAL_DEBUG_STRING Pushing text string '3'
      2016-05-19 13:35:04.166 DEBUG [kea.eval/44478] EVAL_DEBUG_SUBSTRING Popping length 3, start 0, string 0x666F6F626172 pushing result 0x666F6F
      2016-05-19 13:35:04.167 DEBUG [kea.eval/44478] EVAL_DEBUG_STRING Pushing text string 'foo'
      2016-05-19 13:35:04.168 DEBUG [kea.eval/44478] EVAL_DEBUG_EQUAL Popping 0x666F6F and 0x666F6F pushing result 'true'

.. note::

   The debug logging may be quite verbose if there are multiple
   expressions to evaluate; it is intended as an aid in helping
   create and debug expressions. Administrators should plan to disable debug
   logging when expressions are working correctly. Users may also
   wish to include only one set of expressions at a time in the
   configuration file while debugging them, to limit the log
   statements. For example, when adding a new set of expressions, an administrator
   might find it more convenient to create a configuration file that
   only includes the new expressions until they are working
   correctly, and then add the new set to the main configuration file.
