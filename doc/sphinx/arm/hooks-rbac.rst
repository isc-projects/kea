.. _hooks-RBAC:

Role Based Access Control
=========================

.. _hooks-RBAC-overview:

Role Based Access Control Overview
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Before the processing of commands in received HTTP requests, the hook
takes some parameters e.g. the common name part of the client
certificate subject name to assign a role to the request.
The configuration associated to this role is used to accept or reject
the command. After the processing the response can be rewritten e.g.
removing parts.

Summary of the request processing:
 - the HTTP library records some information to be used later, e.g.
   the remote address.
 - when TLS is required but the request was not protected by TLS,
   reject the request by sending an unauthorized response.
 - extract the command from the request.
 - assign a role using recorded information in the request.
 - use the role to accept (i.e. pass through) or reject (i.e. send
   a forbidden response) the command.

Summary of response processing:
 - retrieve some information attached to the request during the
   request processing (when the request was accepted).
 - applies request filters to the response.

.. _hooks-RBAC-config:

Role Based Access Control Configuration
---------------------------------------

Role Assignment
~~~~~~~~~~~~~~~

The role assignment is governed by the configured role assignment method.

.. table:: Role assignment methods

   +----------------------+---------------------------------------------------------+
   | Name                 | Description                                             |
   +----------------------+---------------------------------------------------------+
   | remote-address       | remote/client IP address                                |
   +----------------------+---------------------------------------------------------+
   | cert-subject         | common name part of the client certificate subject name |
   +----------------------+---------------------------------------------------------+
   | cert-issuer          | common name part of the client certificate issuer name  |
   +----------------------+---------------------------------------------------------+
   | basic-authentication | user ID of basic HTTP authentication                    |
   +----------------------+---------------------------------------------------------+
   | custom-value         | for extension                                           |
   +----------------------+---------------------------------------------------------+

Role Configuration
~~~~~~~~~~~~~~~~~~

If the role assignment returns the empty role the configuration of the
``default`` role is used: by default the request is rejected.
If the role assignment returns a not empty role without a configuration,
the configuration of the ``unknown`` role is used.

.. table:: Role configuration parameters

   +------------------+----------------------------------------------------+
   | Name             | Description                                        |
   +------------------+----------------------------------------------------+
   | name             | the role name (at the exception of the default     |
   |                  | and unknown roles)                                 |
   +------------------+----------------------------------------------------+
   | accept-commands  | the accept access list                             |
   +------------------+----------------------------------------------------+
   | reject-commands  | the reject access list                             |
   +------------------+----------------------------------------------------+
   | other-commands   | specifies what to do for commands not matching     |
   |                  | accept and reject lists (default reject)           |
   +------------------+----------------------------------------------------+
   | list-match-first | specifies what to do for commands matching both    |
   |                  | accept and reject list by giving the list to check |
   |                  | and apply first (default accept)                   |
   +------------------+----------------------------------------------------+
   | response-filters | filters to apply to responses                      |
   +------------------+----------------------------------------------------+

API Commands
~~~~~~~~~~~~

All commands of the REST API are described in files in a directory
which can be found in sources in ``src/share/api`` or in installed Kea
in ``.../share/kea/api``. The hook reads these files to take the name,
access right (i.e. ``read`` or ``write``) and the hook name.

.. table:: Extra commands definition parameters

   +--------+---------------------------------------------------------+
   | Name   | Description                                             |
   +--------+---------------------------------------------------------+
   | name   | (mandatory) the command name                            |
   +--------+---------------------------------------------------------+
   | access | (mandatory) the access right i.e. ``read`` or ``write`` |
   +--------+---------------------------------------------------------+
   | hook   | (optional) the hook name (empty or not present for      |
   |        | commands of servers or agents)                          |
   +--------+---------------------------------------------------------+

.. note::

   These command description files are security sensitive e.g. with
   too permissive access rights a local attacker may modify them and
   defeat the RBAC goal.

Access control lists
~~~~~~~~~~~~~~~~~~~~

Access control lists can be specified using a name (string) or a
single entry map.

.. table:: Predefined named access list

   +-------+----------------------------------------------+
   | Name  | Description                                  |
   +-------+----------------------------------------------+
   | ALL   | matches everything                           |
   +-------+----------------------------------------------+
   | NONE  | matches nothing                              |
   +-------+----------------------------------------------+
   | READ  | matches commands with the read access right  |
   +-------+----------------------------------------------+
   | WRITE | matches commands with the write access right |
   +-------+----------------------------------------------+

Map access list specifications use a kind in the name of the single entry
and parameter in the value.

.. table:: Access list kinds

   +---------+-----------------+--------------------------------------+
   | Name    | Description     | Parameter                            |
   +---------+-----------------+--------------------------------------+
   | not     | logical not     | access list                          |
   +---------+-----------------+--------------------------------------+
   | and     | logical and     | list of access lists                 |
   +---------+-----------------+--------------------------------------+
   | or      | logical or      | list of access lists                 |
   +---------+-----------------+--------------------------------------+
   | command | explicit list   | list of command names                |
   +---------+-----------------+--------------------------------------+
   | access  | by access right | access right (``read`` or ``write``) |
   +---------+-----------------+--------------------------------------+
   | hook    | by hook         | hook name (can be empty)             |
   +---------+-----------------+--------------------------------------+

Response Filters
~~~~~~~~~~~~~~~~

.. table:: Predefined response filters

   +---------------+---------------------------------------+
   | Name          | Description                           |
   +---------------+---------------------------------------+
   | list-commands | Removes not allowed commands from the |
   |               | list-commands response                |
   +---------------+---------------------------------------+


Global Parameters
~~~~~~~~~~~~~~~~~

Global parameters are:

-  ``assign-role-method``: (mandatory) the name of the method
   which is used for role assignment.

-  ``api-files``: (mandatory) the path of the directory where
   the API files describing commands can be found.

-  ``require-tls``: specifies if received requests on HTTP vs HTTPS are
   rejected. Default to false when the role assignment method is not
   based on certificates.

-  ``commands``: the list of extra command configurations.

-  ``access-control-lists``: named access control list definitions
   (each definition is a single entry map: the name of the entry is
   the name of the access list, the value is the specification).

-  ``roles``: role configurations.

-  ``default-role``: the configuration of the default role (used
   when "" is assigned).

-  ``unknown-role``: takes the configuration of the unknown role
   (used when the not empty assigned role has no configuration).

Sample Configuration
~~~~~~~~~~~~~~~~~~~~

A sample configuration is available in ``doc/examples/agent/rbac.json``
in the Kea source and is copied below.

.. code-block:: javascript
   :linenos:
   :emphasize-lines: 31-85

    {
    "Control-agent": {
        // We need to specify where the agent should listen to incoming HTTP
        // queries.
        "http-host": "127.0.0.1",

        // If enabling HA and multi-threading, the 8000 port is used by the HA
        // hook library http listener. When using HA hook library with
        // multi-threading to function, make sure the port used by dedicated
        // listener is different (e.g. 8001) than the one used by CA. Note
        // the commands should still be sent via CA. The dedicated listener
        // is specifically for HA updates only.
        "http-port": 8000,

        // TLS trust anchor (Certificate Authority). This is a file name or
        // (for OpenSSL only) a directory path.
        "trust-anchor": "my-ca",

        // TLS server certificate file name.
        "cert-file": "my-cert",

        // TLS server private key file name.
        "key-file": "my-key",

        // TLS require client certificates flag. Default is true and means
        // require client certificates. False means they are optional.
        "cert-required": true,

        // Add hooks here.
        "hooks-libraries": [
        {
            "library": "/opt/lib/libca_rbac.so",
            "parameters": {
                // This section configures the RBAC hook library.
                // Mandatory parameters.
                "assign-role-method": "cert-subject",
                "api-files": "/opt/share/kea/api",
                // Optional parameters.
                "require-tls": true,
                "commands": [
                {
                    "name": "my-command",
                    "access": "read",
                    "hook": "my-hook"
                } ],
                "access-control-lists": [
                {
                    "my-none": { "not": "ALL" }
                },{
                    "another-none": { "and": [ "ALL", "NONE" ] }
                },{
                    "my-read": { "access": "read" }
                } ],
                "roles": [
                {
                    "name": "kea-client",
                    "accept-commands":
                    {
                        "commands": [ "list-commands", "status-get" ]
                    },
                    "reject-commands": "NONE",
                    "other-commands": "reject",
                    "list-match-first": "accept",
                    "response-filters": [ "list-commands" ]
                },{
                    "name": "admin",
                    "accept-commands": "ALL",
                    "reject-commands":
                    {
                        "hook": "cb_cmds"
                    },
                    "list-match-first": "reject"
                } ],
                "default-role":
                {
                    "accept-commands": "NONE",
                    "reject-commands": "ALL"
                },
                "unknown-role":
                {
                    "accept-commands": "READ",
                    "reject-commands": "WRITE"
                }
            }
        } ]

        // Additional parameters, such as logging and others
        // omitted for clarity.

    }
    }

Accept/Reject Algorithm
~~~~~~~~~~~~~~~~~~~~~~~

Here is the pseudo-code of the accept/reject decision algorithm which returns
true i.e. accept or false i.e. reject.

.. code-block:: c

   bool match(command) {
       if (list-match-first == accept) {
           if (accept_list && accept_list->match(command)) {
               return (true);
           }
           if (reject_list && reject_list->match(command)) {
               return (false);
           }
       } else {
           if (reject_list && reject_list->match(command)) {
               return (false);
           }
           if (accept_list && accept_list->match(command)) {
               return (true);
           }
       }
       if (others == reject) {
          return (false);
       } else {
          return (true);
       }
   }

