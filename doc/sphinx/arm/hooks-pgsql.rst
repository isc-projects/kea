.. ischooklib:: libdhcp_pgsql.so
.. _hooks-pgsql:

``libdhcp_pgsql.so``: Database Backend for PostgreSQL
=====================================================

This hook library implements PostgreSQL database storage for:
 - Lease Backend
 - Host Backend
 - Configuration Backend

.. _pgsql-configuration-backend:

PostgreSQL Configuration Backend
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This hook library works in conjunction with :ischooklib:`libdhcp_cb_cmds.so` to
implement the API to create, read, update, and delete (CRUD) the configuration
in a PostgreSQL database. Please see :ref:`hooks-cb-cmds` for more details.

