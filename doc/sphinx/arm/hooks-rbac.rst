.. _hooks-RBAC:

``rbac``: Role-Based Access Control
===================================

.. _hooks-RBAC-overview:

Role-Based Access Control (RBAC) Overview
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Before the processing of commands in received HTTP requests, the ``rbac`` hook
takes specific parameters, e.g. the common name part of the client
certificate subject name, to assign a role to the request.
The configuration associated with this role is used to accept or reject
the command. After processing, the response can be rewritten, e.g.
parts can be removed.

Here is a summary of the steps in processing a request:
 - The HTTP library records some information to be used later, e.g.
   the remote address.
 - When TLS is required but the request was not protected by TLS,
   the request is rejected by sending an "unauthorized" response.
 - The command is extracted from the request.
 - A role is assigned using recorded information in the request.
 - The role is used to accept (pass through) or reject (send
   a forbidden response) the command.

Here is a summary of the steps in processing a response:
 - The information attached to the request is retrieved during the
   request processing (when the request was accepted).
 - Request filters are applied to the response.

.. _hooks-RBAC-config:

Role-Based Access Control Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Role Assignment
---------------

Role assignment is governed by the configured role-assignment method.

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
------------------

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
   | response-filters | the filters to apply to responses                  |
   +------------------+----------------------------------------------------+

.. note::

   The role assignment can fail, for instance with ``cert-subject`` when
   the client certificate was not required, or it has no subject common
   name and instead a DNS alternative subject name. In this case the role
   assignment returns the empty role and the ``default-role`` entry is used.

   The role assignment can return an unexpected value e.g. with an
   unregistered role name or a typing error. In this case the ``unknown-role``
   entry is used.

   Both ``default-role`` and ``unknown-role`` default to reject all commands.

API Commands
------------

All commands of the REST API are described in files in the source directory
``src/share/api``, or in installed Kea
in ``.../share/kea/api``. The ``rbac`` hook reads these files to take the name,
the access right (i.e. ``read`` or ``write``), and the hook name.

.. table:: Extra command-definition parameters

   +--------+---------------------------------------------------------+
   | Name   | Description                                             |
   +--------+---------------------------------------------------------+
   | name   | (mandatory) the command name                            |
   +--------+---------------------------------------------------------+
   | access | (mandatory) the access right i.e. ``read`` or ``write`` |
   +--------+---------------------------------------------------------+
   | hook   | (optional) the hook name (empty or not-present for      |
   |        | commands of servers or agents)                          |
   +--------+---------------------------------------------------------+

.. note::

   These command description files are security-sensitive, e.g. with
   too-permissive access rights a local attacker may modify them and
   defeat the RBAC goal.

Access Control Lists
--------------------

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
   | READ  | matches commands with the read-access right  |
   +-------+----------------------------------------------+
   | WRITE | matches commands with the write-access right |
   +-------+----------------------------------------------+

Map access list specifications use a list type in the name of the single entry
and parameter in the value.

.. table:: Access list types

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
----------------

.. table:: Predefined response filters

   +---------------+---------------------------------------+
   | Name          | Description                           |
   +---------------+---------------------------------------+
   | list-commands | Removes not-allowed commands from the |
   |               | list-commands response                |
   +---------------+---------------------------------------+

Global Parameters
-----------------

The global parameters are:

-  ``assign-role-method``: the name of the method
   which is used for role assignment. This parameter is mandatory.

-  ``api-files``: the path of the directory where
   the API files describing commands can be found. This parameter is mandatory.

-  ``require-tls``: the specification of whether received requests on HTTP (vs HTTPS) are
   rejected. It defaults to ``false`` when the role-assignment method is not
   based on certificates.

-  ``commands``: the list of extra command configurations.

-  ``access-control-lists``: the named access control list definitions
   (each definition is a single entry map; the name of the entry is
   the name of the access list, and the value is the specification).

-  ``roles``: the role configurations.

-  ``default-role``: the configuration of the default role (used
   when "" is assigned).

-  ``unknown-role``: the configuration of the unknown role
   (used when the not-empty assigned role has no configuration).

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

This is the pseudo-code of the accept/reject decision algorithm which returns
``true`` (accept) or ``false`` (reject).

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

Extensive Example
~~~~~~~~~~~~~~~~~

Here is an extensive example for a role accepting all read commands, with
the exception of ``config-get``, e.g. for hiding passwords. For any remote
user who is not recognized as "user1", all commands should be rejected.

The first option is to put the allowed commands in the "accept-commands"
list and to reject anything else:

.. code-block:: javascript

   ...
   "roles": [
   {
       "name": "user1",
       "accept-commands":
       {
           "and": [
               "READ",
               { "not":
                   { "commands": [ "config-get" ] }
               }
           ]
       },
       "reject-commands": "ALL",
       // This is the default but as the config relies on it
       // it is explicitly set.
       "list-match-first": "accept"
    },
    ...
    ],
    ...

A common alternative is to not set the "reject-commands" list, i.e. leave
it empty and rely on "other-commands" to reject anything else.

.. code-block:: javascript

   ...
   "roles": [
   {
       "name": "user2",
       "accept-commands":
       {
           "and": [
               "READ",
               { "not":
                   { "commands": [ "config-get" ] }
               }
           ]
       },
       // This is the default but as the config relies on it
       // it is explicitly set.
       "other-commands": "reject"
    },
    ...
    ],
    ...

It is also possible to do the opposite, i.e. to set only the "reject-commands" list:

.. code-block:: javascript

   ...
   "roles": [
   {
       "name": "user3",
       "reject-commands":
       {
           "or": [
               "WRITE",
               { "commands": [ "config-get" ] }
           ]
       },
       "other-commands": "accept"
    },
    ...
    ],
    ...

Or use both lists with the exception in the "reject-commands" list,
which must be checked first as "config-get" has the read-access right.

.. code-block:: javascript

   ...
   "roles": [
   {
       "name": "user4",
       "accept-commands": "READ",
       "reject-commands": { "commands": [ "config-get" ] },
       "list-match-first": "reject"
    },
    ...
    ],
    ...

To check any configuration, it is a good idea to use the "list-commands"
response filter, which shows errors such as missing (rejected) commands
and extra (accepted) commands.
