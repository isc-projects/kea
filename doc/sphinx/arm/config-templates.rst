.. _config-templates:

Configuration Templates
=======================

The following sections include configuration templates that are proposed configuration for
certain deployment types. The example configuration files are also available in the Kea sources
in the `doc/examples` directory.

.. include:: template-power-user-home.md

At the very least, the lines marked in yellow must be adjusted to match the actual deployment.

Server1's Control Agent configuration file:

.. literalinclude:: template-power-user-home-ca-1.conf
   :language: javascript
   :emphasize-lines: 8
   :linenos:

Server1's DHCPv4 configuration file:

.. literalinclude:: template-power-user-home-dhcp4-1.conf
   :language: javascript
   :emphasize-lines: 25,120,132,146,150,153-157,165-179,189-198
   :linenos:

Server2's Control Agent configuration file:

.. literalinclude:: template-power-user-home-ca-2.conf
   :language: javascript
   :emphasize-lines: 8
   :linenos:

Server2's DHCPv4 configuration file:

.. literalinclude:: template-power-user-home-dhcp4-2.conf
   :language: javascript
   :emphasize-lines: 25,120,132,146,150,153-157,165-179,189-198
   :linenos:
