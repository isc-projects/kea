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
   :emphasize-lines: 25, 76, 81, 121, 133, 148, 152, 155-159, 167-181, 191-200
   :linenos:

Server2's Control Agent configuration file:

.. literalinclude:: template-power-user-home-ca-2.conf
   :language: javascript
   :emphasize-lines: 9, 12
   :linenos:

Server2's DHCPv4 configuration file:

.. literalinclude:: template-power-user-home-dhcp4-2.conf
   :language: javascript
   :emphasize-lines: 25, 76, 81, 121, 133, 148, 152, 155-159, 167-181, 191-200
   :linenos:

.. include:: template-ha-mt-tls.md

Some tweaking of these templates may be required to match specific system needs: at a
minimum, the lines highlighted in yellow must be adjusted to match the actual deployment.

Server1's Control Agent configuration file:

.. literalinclude:: template-ha-mt-tls-ca-1.conf
   :language: javascript
   :emphasize-lines: 10, 14, 17, 20, 23, 32
   :linenos:

Server1's DHCPv4 configuration file:

.. literalinclude:: template-ha-mt-tls-dhcp4-1.conf
   :language: javascript
   :emphasize-lines: 25, 38-54, 95, 100, 133-142, 151, 153, 155, 157, 169, 171, 173, 175, 190, 194, 197-201
   :linenos:

Server2's Control Agent configuration file:

.. literalinclude:: template-ha-mt-tls-ca-2.conf
   :language: javascript
   :emphasize-lines: 10, 14, 17, 20, 23, 32
   :linenos:

Server2's DHCPv4 configuration file:

.. literalinclude:: template-ha-mt-tls-dhcp4-2.conf
   :language: javascript
   :emphasize-lines: 25, 38-54, 95, 100, 133-142, 151, 153, 155, 157, 169, 171, 173, 175, 190, 194, 197-201
   :linenos:
