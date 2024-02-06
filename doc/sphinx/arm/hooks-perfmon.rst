.. ischooklib:: libdhcp_perfmon.so
.. _hooks-perfmon:

``libdhcp_perfmon.so``: PerfMon
===============================

This hook library can be loaded by either kea-dhcp4 or kea-dhcp6 servers
to extend them with the ability to track and report performance related data.

.. note::

    This library is currently under development and not yet functional.

Overview
~~~~~~~~

The library, added in Kea 2.5.6, can be loaded by the :iscman:`kea-dhcp4` or
:iscman:`kea-dhcp6` daemon by adding it to the ``hooks-libraries`` element of
the server's configuration:

.. code-block:: javascript

    {
        "hooks-libraries": [
            {
                "library": "/usr/local/lib/libdhcp_perfmon.so",
                "parameters": {
                    ...
                }
            },
            ...
        ],
        ...
    }

Configuration
~~~~~~~~~~~~~

    TBD
