.. ischooklib:: libdhcp_pgsql_cb.so
.. _hooks-cb-pgsql:

``libdhcp_pgsql_cb.so``: Configuration Backend for PostgreSQL
=============================================================

This hook library works in conjunction with :ischooklib:`libdhcp_cb_cmds.so` to
implement the API to create, read, update, and delete (CRUD) the
configuration in a PostgreSQL database. Please see :ref:`hooks-cb-cmds`
for more details.

.. note::

    :ischooklib:`libdhcp_pgsql_cb.so` is part of the open source code and is
    available to every Kea user. However, this hook library only works
    with :ischooklib:`libdhcp_cb_cmds.so`, which allows easy configuration
    management with the use of API commands. :ischooklib:`libdhcp_cb_cmds.so`
    is available only to ISC customers with a paid support contract; for more information
    on subscription options, please complete the form at https://www.isc.org/contact.
