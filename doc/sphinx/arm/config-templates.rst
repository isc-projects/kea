.. _config-templates:

Configuration Templates
=======================

The following sections include configuration templates for
certain deployment types. The example configuration files are also available in the Kea sources,
in the ``doc/examples`` directory.

.. include:: template-power-user-home.md

Some tweaking of these templates may be required to match specific system needs: at a
minimum, the lines highlighted in yellow must be adjusted to match the actual deployment.

Server1's Control Agent configuration file:

.. literalinclude:: template-power-user-home-ca-1.conf
   :language: javascript
   :emphasize-lines: 9, 12
   :linenos:

Server1's DHCPv4 configuration file:

.. literalinclude:: template-power-user-home-dhcp4-1.conf
   :language: javascript
   :emphasize-lines: 25,76,81,121,133,147,151,154-158,166-180,190-199
   :linenos:

Server2's Control Agent configuration file:

.. literalinclude:: template-power-user-home-ca-2.conf
   :language: javascript
   :emphasize-lines: 9, 12
   :linenos:

Server2's DHCPv4 configuration file:

.. literalinclude:: template-power-user-home-dhcp4-2.conf
   :language: javascript
   :emphasize-lines: 25,76,81,121,133,147,151,154-158,166-180,190-199
   :linenos:
