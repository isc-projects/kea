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
   :emphasize-lines: 25, 79, 84, 124, 136, 151, 155, 158-162, 170-184, 194-203
   :linenos:

Server2's Control Agent configuration file:

.. literalinclude:: template-power-user-home-ca-2.conf
   :language: javascript
   :emphasize-lines: 9, 12
   :linenos:

Server2's DHCPv4 configuration file:

.. literalinclude:: template-power-user-home-dhcp4-2.conf
   :language: javascript
   :emphasize-lines: 25, 79, 84, 124, 136, 151, 155, 158-162, 170-184, 194-203
   :linenos:

.. include:: template-ha-mt-tls.md

Some tweaking of these templates may be required to match specific system needs: at a
minimum, the lines highlighted in yellow must be adjusted to match the actual deployment.

Server1's Control Agent configuration file:

.. literalinclude:: template-ha-mt-tls-ca-1.conf
   :language: javascript
   :emphasize-lines: 10, 14, 18, 21, 24, 36
   :linenos:

Server1's DHCPv4 configuration file:

.. literalinclude:: template-ha-mt-tls-dhcp4-1.conf
   :language: javascript
   :emphasize-lines: 25, 38-54, 98, 103, 139-152, 161, 163, 165, 167, 181, 183, 185, 187, 204, 208, 211-215
   :linenos:

Server2's Control Agent configuration file:

.. literalinclude:: template-ha-mt-tls-ca-2.conf
   :language: javascript
   :emphasize-lines: 10, 14, 18, 21, 24, 36
   :linenos:

Server2's DHCPv4 configuration file:

.. literalinclude:: template-ha-mt-tls-dhcp4-2.conf
   :language: javascript
   :emphasize-lines: 25, 38-54, 98, 103, 139-152, 161, 163, 165, 167, 181, 183, 185, 187, 204, 208, 211-215
   :linenos:
