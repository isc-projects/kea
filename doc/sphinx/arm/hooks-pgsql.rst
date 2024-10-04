.. ischooklib:: libdhcp_pgsql.so
.. _hooks-pgsql:

``libdhcp_pgsql.so``: Database Backend for PostgreSQL
=====================================================

This hook library implements PostgreSQL database storage for:
 - Lease Backend
 - Host Backend
 - Configuration Backend

This hook library works in conjunction with :ischooklib:`libdhcp_cb_cmds.so` to
implement the API to create, read, update, and delete (CRUD) the configuration
in a PostgreSQL database. Please see :ref:`hooks-cb-cmds` for more details.

.. note::

    :ischooklib:`libdhcp_pgsql.so` is part of the open source code and is
    available to every Kea user. However, this hook library only works with
    :ischooklib:`libdhcp_cb_cmds.so`, which allows easy configuration
    management with the use of API commands. :ischooklib:`libdhcp_cb_cmds.so`
    is available only to ISC customers with a paid support contract; for more
    information on subscription options, please complete the form at
    https://www.isc.org/contact.
