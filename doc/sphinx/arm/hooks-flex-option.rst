.. ischooklib:: libdhcp_flex_option.so
.. _hooks-flex-option:

``libdhcp_flex_option.so``: Flexible Option Actions for Option Value Settings
=============================================================================

This library allows administrators to define an action to take, for a given
option, based upon on the result of an expression. These actions are carried
out during the final stages of constructing a query response packet, just
before it is sent to the client. The three actions currently supported are
``add``, ``supersede``, and ``remove``.

.. note::

    :ischooklib:`libdhcp_flex_option.so` is part of the open source code and is
    available to every Kea user.

The syntax used for the action expressions is the same syntax used
for client classification and the Flexible Identifier hook library;
see either :ref:`classification-using-expressions` or :ref:`hooks-flex-id`
for a detailed description of the syntax.

The ``add`` and ``supersede`` actions use an expression returning a
string, and do nothing if the string is empty. The
``remove`` application uses an expression returning ``true`` or ``false``,
and does nothing on ``false``. When it is necessary to set an option to the
empty value this mechanism does not work, but a client class can be
used instead.

The ``add`` action adds an option only when the option does not already
exist and the expression does not evaluate to the empty string.
The ``supersede`` action is similar, but it overwrites the option value
if it already exists. The ``remove`` action removes the option from
the response packet if it already exists and the expression evaluates to
true.

The option to which an action applies may be specified by either its
numeric code or its name; either the code or the name must be
specified. The option space is DHCPv4 or DHCPv6, depending
on the server where the hook library is loaded.

:ischooklib:`libdhcp_flex_option.so` can be loaded
by either the :iscman:`kea-dhcp4` or :iscman:`kea-dhcp6`
process. It takes a mandatory ``options`` parameter with a list of
per-option parameter maps, with ``code``, ``name``, ``add``, ``supersede``, and
``remove`` actions. Action entries take a string value representing an
expression.

.. code-block:: json

 {
    "Dhcp4": {
        "hooks-libraries": [
            {
                "library": "/usr/local/lib/libdhcp_flex_option.so",
                "parameters": {
                    "options": [
                        {
                            "code": 67,
                            "add": "ifelse(option[host-name].exists,concat(option[host-name].text,'.boot'),'')"
                        }
                    ]
                }
            }
        ]
    }
 }

If (and only if) the **query** includes a ``host-name`` option (code 12), a
``boot-file-name`` option (code 67) is added to the response with the host name
followed by ``.boot`` for content.

A commonly discussed use case is modifying the DHCPv4 subnet mask option
(code 1). The following example demonstrates that capability, as all ingress
packets identified by the gateway address 192.168.0.1 are met with a /32 subnet
mask in the response:

.. code-block:: json

    {
        "Dhcp4": {
            "hooks-libraries": [
                {
                    "library": "/usr/local/lib/libdhcp_flex_option.so",
                    "parameters": {
                        "options": [
                            {
                                "code": 1,
                                "supersede": "ifelse(pkt4.giaddr==192.168.0.1, '255.255.255.255', '')"
                            }
                        ]
                    }
                }
            ]
        }
    }

The Flexible Option library supports both DHCPv4 and DHCPv6.

The ``add`` and ``supersede`` actions take an optional
``csv-format`` boolean parameter. If not specified or set to ``false``, the
option data is set using the raw value of the evaluated expression. When it is
configured to ``true``, this value is parsed using the option definition from
the option data specified in the configuration file. This eases option setting
for options using complex record formats or fully qualified domain names.

For instance, if the expression evaluation returns "example.com" and
the option is defined with the ``fqdn`` type, the domain name is
encoded into DNS binary format.

Since Kea 2.1.4, the ``client-class`` parameter specifies a class guard,
and takes a client-class name. If not empty, the client's packet needs to
belong to tne specified class for this entry to be used.

It is also possible to have multiple entries for the same option,
but each entry must have exactly one action. If the option is not defined
in ``dhcp4`` for DHCPv4 or ``dhcp6`` for DHCPv6, the location of
the option definition can be specified using its name, with the new
``space`` parameter.

Since Kea 2.1.4, sub-options are supported with a new entry, ``sub-options``,
which replaces the action in the configuration of the container option,
i.e. the option where sub-options are located.

The ``sub-options`` parameter takes a list of sub-option entries, each
containing:

- ``code`` - specifies the sub-option code; either the ``code`` or ``name``
  must be specified. If both are given, they must match or the configuration
  is rejected at load time.

- ``name`` - specifies the sub-option name; either the ``code`` or ``name``
  must be specified. If both are given, they must match or the configuration
  is rejected at load time.

- ``space`` - specifies the space where the sub-option can be defined. This
  parameter is optional, because it can be found in the container option
  definition. The configuration is rejected if no valid space name is
  available at load time. Note that vendor spaces are supported for the
  DHCPv4 ``vivso-suboptions`` and for the DHCPv6 ``vendor-opts``, both
  pre-defined (e.g. DoCSIS vendor id 4491) or custom.

- ``add`` - (action) adds a sub-option only if it does not already exist
  and the expression does not evaluate to the empty string.

- ``supersede`` - (action) adds or overwrites a sub-option if the expression
  does not evaluate to the empty string.

- ``remove`` - (action) removes a sub-option if it already exists and the
  expression evaluates to true.

- ``container-add`` - a boolean value that specifies whether the container option
  should be created, if it does not exist in the ``add`` and ``supersede``
  action. If not specified, it defaults to ``true``.

- ``container-remove`` - a boolean value that specifies whether the container option
  should be deleted, if it remains empty after the removal of a sub-option by
  the ``remove`` action. If not specified, it defaults to ``true``.

- ``csv-format`` - a boolean value that specifies whether the raw value of the
  evaluated expression is used (false, default) or parsed using the sub-option
  definition (true).

- ``client-class`` - specifies whether the sub-option entry must be skipped when
  the **query** does not belong to the specified client class. Note that the similar
  parameter in the container option entry applies to the whole ``sub-options``
  list.

For instance, this configuration adds a string sub-option in the DHCPv4
``vendor-encapsulated-options`` (code 43) option. This option
encapsulates the ``vendor-encapsulated-options`` space.

.. code-block:: json

 {
    "Dhcp4": {
        "hooks-libraries": [
            {
                "library": "/usr/local/lib/libdhcp_flex_option.so",
                "parameters": {
                    "options": [
                        {
                            "code": 43,
                            "sub-options": [
                                {
                                   "code": 1,
                                   "add": "'foobar'"
                                }
                            ]
                        }
                    ]
                }
            }
        ]
    }
 }
