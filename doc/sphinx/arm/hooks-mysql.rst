.. ischooklib:: libdhcp_mysql.so
.. _hooks-mysql:

``libdhcp_mysql.so``: Database Backend for MySQL
================================================

This hook library implements MySQL database storage for:
 - Lease Backend
 - Host Backend
 - Configuration Backend

.. _mysql-configuration-backend:

MySQL Configuration Backend
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This hook library works in conjunction with :ischooklib:`libdhcp_cb_cmds.so` to
implement the API to create, read, update, and delete (CRUD) the configuration
in a MySQL database. Please see :ref:`hooks-cb-cmds` for more details.

