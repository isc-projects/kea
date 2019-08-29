.. _cb-cmds-library:

cb_cmds: Configuration Backend Commands
=======================================

This section describes the ``cb_cmds`` hooks library, which is used to
manage Kea servers' configurations in the Configuration Backends. This
library must be used in conjunction with the available CB hooks libraries
implementing the common APIs to create, read, update, and delete (CRUD)
the configuration information in the respective databases. For example:
the ``mysql_cb`` hooks library, released in Kea 1.6.0, implements this
API for MySQL. In order to manage the configuration information in the
MySQL database, both the ``mysql_cb`` and ``cb_cmds`` libraries must be
loaded by the server used for the configuration management.

The ``cb_cmds`` library is only available to ISC customers with a paid
support contract.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or
   ``kea-dhcp6`` process.

Commands Structure
~~~~~~~~~~~~~~~~~~

There are 5 types of commands supported by this library:

-  ``del`` - delete the selected object from the database, e.g.
   ``remote-global-parameter4-del``.

-  ``get`` - fetch the selected object from the database, e.g.
   ``remote-subnet4-get``.

-  ``get-all`` - fetch all objects of the particular type from the
   database, e.g. ``remote-option-def4-get-all``.

-  ``list`` - list all objects of the particular type in the database,
   e.g. ``remote-network4-list``; this class of commands returns brief
   information about each object comparing to the output of ``get-all``.

-  ``set`` - creates or replaces an object of the given type in the
   database, e.g. ``remote-option4-global-set``.

All types of commands accept an optional ``remote`` map which selects the
database instance to which the command refers. For example:

::

   {
       "command": "remote-subnet4-list",
       "arguments": {
           "remote": {
               "type": "mysql",
               "host": "192.0.2.33",
               "port": 3302
           }
       }
   }

selects the MySQL database, running on host 192.0.2.33 and port 3302, to
fetch the list of subnets from. All parameters in the ``remote`` argument are
optional. The ``port`` parameter can be only specified in conjunction
with the ``host``. If no options in the ``remote`` parameter are to
be specified, the parameter should be omitted. In this case, the server
will use the first backend listed in the ``config-control`` map within
the configuration of the server receiving the command.

.. note::

   As of the Kea 1.6.0 release, it is possible to configure the Kea server
   to use only one configuration backend. Strictly speaking, it is
   possible to point the Kea server to at most one MySQL database using the
   ``config-control`` parameter. That's why, in this release, the
   ``remote`` parameter may be omitted in the commands and the
   cb_cmds hooks library will use the sole backend by default.

.. _cb-cmds-dhcp:

Control Commands for DHCP Servers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section describes and gives some examples of the control commands
implemented by the ``cb_cmds`` hooks library, to manage the
configuration information of the DHCPv4 and DHCPv6 servers. Many of the
commands are almost identical between DHCPv4 and DHCPv6; they only
differ by the command name. Other commands differ slightly by the
structure of the inserted data; for example, the structure of the IPv4 subnet
information is different than that of the IPv6 subnet.
Nevertheless, they still share the structure of their command arguments
and thus it makes sense to describe them together.

In the following sections, various commands are described and some usage
examples are provided. In the sections jointly describing the DHCPv4 and
DHCPv6 variants of the particular command, we sometimes use the following
notation: the ``remote-subnet[46]-set`` is the wildcard name for the
two commands: ``remote-subnet4-set`` and ``remote-subnet6-set``.

In addition, whenever the text in the subsequent sections refers to a
DHCP command or DHCP parameter, it refers to both DHCPv4 and DHCPv6
variants. The text specific to the particular server type refers to them
as: DHCPv4 command, DHCPv4 parameter, DHCPv6 command, DHCPv6 parameter,
etc.

.. _cb-cmds-metadata:

Metadata
~~~~~~~~

The typical response to the ``get`` or ``list`` command includes a list
of returned objects (e.g. subnets), and each such object contains the
``metadata`` map with some database-specific information describing this
object. In other words, the metadata contains any information about the
fetched object which may be useful for the administrator, but which is not
part of the object specification from the DHCP server standpoint. In the
Kea 1.6.0 release, the metadata is limited to the ``server-tag``, which
describes the association of the object with a particular server or
all servers.

The following is the example response to the ``remote-network4-list``
command, which includes the metadata:

::

   {
       "result": 0,
       "text": "1 IPv4 shared network(s) found.",
       "arguments": {
           "shared-networks": [
               {
                   "name": "level3",
                   "metadata": {
                       "server-tags": [ "all" ]
                   }
               }
           ],
           "count": 1
       }
   }


Client implementations must not assume that the metadata contains only
the ``server-tags`` parameter. In future releases, this map will be
extended with additional information, e.g. object modification time, log
message created during the last modification, etc.

.. _command-remote-server4-del:
.. _command-remote-server6-del:

remote-server4-del, remote-server6-del commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to delete the information about a selected DHCP server from
the configuration database. The server is identified by a unique case
insensitive server tag.  For example:

::

    {
        "command": "remote-server4-del",
        "arguments": {
            "servers": [
                {
                    "server-tag": "server1"
                }
            ],
            "remote": {
                "type": "mysql"
            }
        }
    }

As a result of this command, the user defined server called `server1` is removed
from the database. All associations of the configuration information with this
server are automatically removed from the database. The non-shareable
configuration information, such as: global parameters, option definitions and
global options associated with the server are removed from the database. The
shareable configuration information, i.e. the configuration elements which may
be associated with more than one server, is preserved. In particular, the
subnets and shared networks associated with the deleted servers are
preserved. If any of the shareable configuration elements was associated only
with the deleted server, this object becomes unassigned (orphaned).  For
example: if a subnet has been created and associated with the `server1` using
the `remote-subnet4-set` command and the server1 is subsequently deleted, the
subnet remains in the database but none of the servers can use this subnet. The
subnet can be updated using the `remote-subnet4-set` and associated with some
other server or with all servers using the special server tag "all". Such subnet
can be also deleted from the database using the `remote-subnet4-del-by-id` or
`remote-subnet4-del-by-prefix`, if it is no longer needed.

The following is the successful response to the `remote-server4-del` command:

::

    {
        "result": 0,
        "text": "1 DHCPv4 server(s) deleted."
        "arguments": {
            "count": 1
        }
    }


.. note::

   The `remote-server4-del` and `remote-server6-del` commands must be used with
   care, because an accidental deletion of the server causes some parts of the
   existing configurations to be lost permanently from the database. This
   operation is not reversible. Re-creation of the accidentally deleted server
   does not revert the lost configuration for that server and such configuration
   must be re-created manually by the user.

.. _command-remote-server4-get:
.. _command-remote-server6-get:

remote-server4-get, remote-server6-get commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to fetch the information about the selected DHCP server
from the configuration database.  For example:

::

    {
        "command": "remote-server6-get"
        "arguments": {
            "servers": [
                {
                    "server-tag": "server1"
                }
            ],
            "remote": {
                "type": "mysql"
            }
        }
    }


This command fetches the information about the DHCPv6 server identified by the
server tag `server1`. The server tag is case insensitive.  A successful response
returns basic information about the server, such as server tag and the user's
description of the server:

::

    {
        "result": 0,
        "text": "DHCP server server1 found.",
        "arguments": {
            "servers": [
                {
                    "server-tag": "server1",
                    "description": "A DHCPv6 server located on the first floor."
                }
            ],
            "count": 1
        }
    }

.. _command-remote-server4-get-all:
.. _command-remote-server6-get-all:

remote-server4-get-all, remote-server6-get-all commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to fetch all user defined DHCPv4 or DHCPv6 servers from the
database. The command structure is very simple:

::

    {
        "command": "remote-server4-get-all"
        "arguments": {
            "remote": {
                "type": "mysql"
            }
        }
    }

The response includes basic information about each server, such as its server
tag and description:

::

    {
        "result": 0,
        "text": "DHCPv4 servers found.",
        "arguments": {
            "servers": [
                {
                    "server-tag": "server1",
                    "description": "A DHCP server located on the first floor."
                },
                {
                    "server-tag": "server2",
                    "description": "An old DHCP server to be soon replaced."
                }
            ],
           "count": 2
        }
    }

.. _command-remote-server4-set:
.. _command-remote-server6-set:

remote-server4-set, remote-server6-set commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to create or replace an information about a DHCP server in
the database. The information about the server must be created when there is a
need to differentiate the configurations used by various Kea instances
connecting to the same database. Various configuration elements, e.g. global
parameters, subnets etc. may be explicitly associated with the selected servers
(using server tags as identifiers), allowing only these servers to use the
respective configuration elements. Using the particular server tag to make such
associations is only possible when the server information has been stored in the
database via the `remote-server4-set` or `remote-server6-set` commands. The
following command creates a new (or updates an existing) DHCPv6 server in the
database:

::

    {
        "command": "remote-server6-set"
        "arguments": {
            "servers": [
                {
                    "server-tag": "server1",
                    "description": "A DHCP server on the ground floor."
                }
            ],
            "remote": {
                "type": "mysql"
            }
        }
    }

The server tag must be unique accross all servers in the database. When the
server information under the given server tag already exists, it is replaced
with the new information. The specified server tag is case insensitive. The
maximum length of the server tag is 256 characters. The following keywords are
reserved and must not be used as server tags: "all" and "any".

The following is the example response to the above command:

::

    {
        "result": 0,
        "text": "DHCPv6 server successfully set.",
        "arguments": {
            "servers": [
                {
                    "server-tag": "server1",
                    "description": "A DHCP server on the ground floor."
                }
            ]
        }
    }


.. _command-remote-global-parameter4-del:

.. _command-remote-global-parameter6-del:

The remote-global-parameter4-del, remote-global-parameter6-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete a global DHCP parameter from the
configuration database. When the parameter is deleted from the database,
the server will use the value specified in the configuration file for
this parameter, or a default value if the parameter is not specified in
the configuration file.

The following command attempts to delete the DHCPv4 ``renew-timer``
parameter common for all servers from the database:

::

   {
       "command": "remote-global-parameter4-del",
       "arguments": {
           "parameters": [ "renew-timer" ],
           "remote": {
               "type": "mysql"
            },
           "server-tags": [ "all" ]
       }
   }

If the server specific parameter is to be deleted, the
`server-tags` list must contain the tag of the appropriate
server. There must be exactly one server tag specified in this list.


.. _command-remote-global-parameter4-get:

.. _command-remote-global-parameter6-get:

The remote-global-parameter4-get, remote-global-parameter6-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch a scalar global DHCP parameter from the
configuration database.

The following command attempts to fetch the ``boot-file-name``
parameter for the "server1":

::

   {
       "command": "remote-global-parameter4-get",
       "arguments": {
           "parameters": [ "boot-file-name" ],
            "remote": {
                "type": "mysql"
            },
            "server-tags": [ "server1" ]
       }
   }


The returned value has one of the four scalar types: string, integer,
real, or boolean. Non-scalar global configuration parameters, such as map
or list, are not returned by this command.

In the case of the example above, the string value is returned, e.g.:

::

   {
       "result": 0,
       "text": "1 DHCPv4 global parameter found.",
       "arguments": {
           "parameters": {
               "boot-file-name": "/dev/null",
               "metadata": {
                   "server-tags": [ "all" ]
               }
           },
           "count": 1
       }
   }


Note that the response above indicates that the returned parameter is associated
with "all" servers rather than "server1" used in the command. This indicates
that there is no server1 specific value in the database. Therefore, the value
shared by all servers is returned. If there was the server1 specific value
in the database this value would be returned instead.

The example response for the integer value is:

::

   {
       "result": 0,
       "text": "1 DHCPv4 global parameter found.",
       "arguments": {
           "parameters": {
               "renew-timer": 2000,
               "metadata": {
                   "server-tags": [ "server1" ]
               }
           },
           "count": 1
       }
   }


The real value:

::

   {
       "result": 0,
       "text": "1 DHCPv4 global parameter found.",
       "arguments": {
           "parameters": {
               "t1-percent": 0.85,
               "metadata": {
                   "server-tags": [ "all" ]
               }
           },
           "count": 1
       }
   }


Finally, the boolean value:

::

   {
       "result": 0,
       "text": "1 DHCPv4 global parameter found.",
       "arguments": {
           "parameters": {
               "match-client-id": true,
               "metadata": {
                   "server-tags": [ "server2" ]
               }
           },
           "count": 1
       }
   }


.. _command-remote-global-parameter4-get-all:

.. _command-remote-global-parameter6-get-all:

The remote-global-parameter4-get-all, remote-global-parameter6-get-all Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch all global DHCP parameters from the database
for the specified server. The following example demonstrates how to fetch all
global parameters to be used by the server "server1":

::

    {
        "command": "remote-global-parameter4-get-all",
        "arguments": {
            "remote": {
                "type": "mysql"
            },
            "server-tags": [ "server1" ]
        }
    }

The example response may look as follows:

::

    {
        "result": 0,
        "text": "DHCPv4 global parameters found.",
        "arguments": {
            "parameters": [
                {
                    "boot-file-name": "/dev/null",
                    "metadata": {
                        "server-tags": [ "server1" ]
                    }
                },
                {
                    "match-client-id": true,
                    "metadata": {
                        "server-tags": [ "all" ]
                    }
                }
            ],
            "count": 2
        }
    }


The example response contains two parameters, one string parameter and one
boolean parameter. The metadata returned for each parameter indicates
if this parameter is specific to the "server1" or all servers. Since the
`match-client-id` value is associated with "all" servers
it indicates that there is no server1 specific setting for this parameter.
Each parameter always has exactly one server tag associated with it, because
the global parameters are non-shareable configuration elements.

.. note::

   If the server tag is set to "all" in the command, the response will
   contain only the global parameters associated with the logical server
   "all". When the server tag points to the specific server (as in the
   example above), the returned list combines parameters associated with
   this server and all servers, but the former take precedence.

.. _command-remote-global-parameter4-set:

.. _command-remote-global-parameter6-set:

The remote-global-parameter4-set, remote-global-parameter6-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to create scalar global DHCP parameters in the
database. If any of the parameters already exists, its value is replaced
as a result of this command. It is possible to set multiple parameters
within a single command, each having one of the four types: string,
integer, real, or boolean. For example:

::

   {
       "command": "remote-global-parameter4-set"
       "arguments": {
           "parameters": {
               "boot-file-name": "/dev/null",
               "renew-timer": 2000,
               "t1-percent": 0.85,
               "match-client-id": true
           },
           "remote": {
               "type": "mysql"
           },
           "server-tags": [ "server1" ]
       }
   }


An error is returned if any of the parameters is not supported by the DHCP
server or its type does not match. Care should be taken when multiple parameters
are specified in a single command, because it is possible that only some of the
parameters are stored successfully and some fail. If an error occurs when
processing this command, it is recommended to use
``remote-global-parameter[46]-get-all`` to check which of the parameters have
been stored/updated successfully and which have failed.

The `server-tags` list is mandatory and it must contain a single server tag or
the keyword "all". In the example above, all specified parameters are associated
with the "server1" server.

.. _command-remote-network4-del:

.. _command-remote-network6-del:

The remote-network4-del, remote-network6-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete an IPv4 or IPv6 shared network from
the database. The optional parameter ``subnets-action`` determines
whether the subnets belonging to the deleted shared network should also
be deleted or preserved. The ``subnets-action`` parameter defaults to ``keep``,
which preserves the subnets. If it is set to ``delete``, the subnets are
deleted along with the shared network.

The following command:

::

   {
       "command": "remote-network6-del",
       "arguments": {
           "shared-networks": [
               {
                   "name": "level3"
               }
           ],
           "subnets-action": "keep",
           "remote": {
               "type": "mysql"
           }
       }
   }


deletes the "level3" IPv6 shared network. The subnets are preserved, but
they are disassociated from the deleted shared network and become
global. This behavior corresponds to the behavior of the
``network[46]-del`` commands with respect to the ``subnets-action`` parameter.

Note that the `server-tags` parameter must not be used for this command.

.. _command-remote-network4-get:

.. _command-remote-network6-get:

The remote-network4-get, remote-network6-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to retrieve information about an IPv4 or
IPv6 shared network. The optional parameter ``subnets-include`` denotes
whether the subnets belonging to the shared network should also be
returned. This parameter defaults to ``no``, in which case the subnets
are not returned. If this parameter is set to ``full``, the subnets are
returned together with the shared network.

The following command fetches the "level3" IPv6 shared network along
with the full information about the subnets belonging to it:

::

   {
       "command": "remote-network6-get",
       "arguments": {
           "shared-networks": [
               {
                   "name": "level3"
               }
           ],
           "subnets-include": "full",
           "remote": {
               "type": "mysql"
           }
       }
   }

Note that the `server-tags` parameter must not be used for this command.

.. _command-remote-network4-list:

.. _command-remote-network6-list:

The remote-network4-list, remote-network6-list Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to list all IPv4 or IPv6 shared networks for a server.

The following command retrieves all shared networks to be used by the
"server1" and "server2":

::

    {
        "command": "remote-network4-list"
        "arguments": {
            "remote": {
                "type": "mysql"
            },
            "server-tags": [ "server1", "server2" ]
        }
    }

The `server-tags` parameter is mandatory and it contains one or more server
tags. It may contain the keyword "all" to fetch the shared networks associated
with all servers. When the `server-tags` list contains the
`null` value the returned response contains a list of unassigned shared
networks, i.e. the networks which are associated with no servers. For example:

::

    {
        "command": "remote-network4-list"
        "arguments": {
            "remote": {
                "type": "mysql"
            },
            "server-tags": [ null ]
        }
    }

The example response to this command when non-null server tags are specified
looks similar to this:

::

    {
        "result": 0,
        "text": "3 IPv4 shared network(s) found.",
        "arguments": {
            "shared-networks": [
                {
                    "name": "ground floor",
                    "metadata": {
                        "server-tags": [ "all" ]
                    }
                },
                {
                    "name": "floor2",
                    "metadata": {
                        "server-tags": [ "server1" ]
                    }
                },
                {
                    "name": "floor3",
                    "metadata": {
                        "server-tags": [ "server2" ]
                    }
                }
            ],
            "count": 3
        }
    }

The returned information about each shared network merely contains the shared
network name and the metadata. In order to fetch the detailed information about
the selected shared network, use the `remote-network[46]-get` command.

The example response above contains three shared networks. One of the
shared networks is associated will all servers, so it is included in
the list of shared networks to be used by the "server1" and "server2".
The remaining two shared networks are returned because one of them
is associated with the "server1" and another one is associated with
the "server2".


When listing unassigned shared networks, the response will look similar
to this:

::

    {
        "result": 0,
        "text": "1 IPv4 shared network(s) found.",
        "arguments": {
            "shared-networks": [
                {
                    "name": "fancy",
                    "metadata": {
                        "server-tags": [ null ]
                    }
                }
            ],
            "count": 1
        }
    }

The `null` value in the metadata indicates that the
returned shared network is unassigned.

.. _command-remote-network4-set:

.. _command-remote-network6-set:

The remote-network4-set, remote-network6-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands create a new or replace an existing IPv4 or IPv6 shared
network in the database. The structure of the shared network information
is the same as in the Kea configuration file (see
:ref:`shared-network4` and :ref:`shared-network6` for details),
except that specifying subnets along with the shared
network information is not allowed. Including the ``subnet4`` or ``subnet6`` parameter
within the shared network information will result in an error.

These commands are intended to be used for managing the shared
network-specific information and DHCP options. In order to associate and
disassociate the subnets with the shared networks, the
``remote-subnet[46]-set`` commands should be used.

The following command adds the IPv6 shared network "level3" to the
database:

::

   {
       "command": "remote-network6-set",
       "arguments": {
           "shared-networks": [
               {
                   "name": "level3",
                   "interface": "eth0",
                   "option-data": [ {
                       "name": "sntp-servers",
                       "data": "2001:db8:1::1"
                   } ],
               }
           ],
           "remote": {
               "type": "mysql"
           },
           "server-tags": [ "all" ]
       }
   }


This command includes the ``interface`` parameter, which sets the shared
network-level interface name. Any remaining shared network-level parameters,
which are not specified with the command, will be marked as
"unspecified" in the database. The DHCP server will use the global
values for unspecified parameters or, if the global values are not
specified, the default values will be used.

The `server-tags` list is mandatory for this command and it must include one or
more server tags. As a result the shared network is associated with all listed
servers. The shared network may be associated with all servers connecting to the
database when the keyword "all" is included.

.. note::

   As with other "set" commands, this command replaces all the
   information about the given shared network in the database, if the
   shared network already exists. Therefore, when sending this command,
   make sure to always include all parameters that must be specified for
   the updated shared-network instance. Any unspecified parameter will
   be marked unspecified in the database, even if its value was present
   prior to sending the command.

.. _command-remote-option-def4-del:

.. _command-remote-option-def6-del:

The remote-option-def4-del, remote-option-def6-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete a DHCP option definition from the
database. The option definition is identified by an option code and
option space. For example:

::

   {
       "command": "remote-option-def6-del",
       "arguments": {
           "option-defs": [
               {
                   "code": 1,
                   "space": "isc"
               }
           ],
           "remote": {
               "type": "mysql"
           },
           "server-tags": [ "server1" ]
       }
   }


deletes the definition of the option associated with the "server1", having the
code of 1 and belonging to the option space "isc". The default option spaces are
"dhcp4" and "dhcp6" for the DHCPv4 and DHCPv6 top level options respectively. If
there is no such option explicitly associated with the server1, no option is
deleted. In order to delete an option belonging to "all" servers, the keyword
"all" must be used as server tag. The `server-tags` list must contain exactly
one tag. It must not include the `null` value.

.. _command-remote-option-def4-get:

.. _command-remote-option-def6-get:

The remote-option-def4-get, remote-option-def6-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch a specified DHCP option definition from
the database. The option definition is identified by the option code and
option space. The default option spaces are "dhcp4" and "dhcp6" for the
DHCPv4 and DHCPv6 top-level options, respectively.

The following command retrieves a DHCPv4 option definition associated with all
servers, having the code of 1 and belonging to the option space "isc":

::

   {
       "command": "remote-option-def4-get"
       "arguments": {
           "option-defs": [
               {
                   "code": 1,
                   "space": "isc"
               }
           ],
           "remote": {
               "type": "mysql"
           },
           "server-tags": [ "all" ]
       }
   }

The `server-tags` list must include exactly one server tag or the keyword
"all". It must not contain the `null` value.

.. _command-remote-option-def4-get-all:

.. _command-remote-option-def6-get-all:

The remote-option-def4-get-all, remote-option-def6-get-all Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch all DHCP option definitions from the database
for the particular server or all servers. For example:

::

    {
        "command": "remote-option-def6-get-all"
        "arguments": {
            "remote": {
                "type": "mysql"
            },
            "server-tags": [ "all" ]
        }
    }


This command attempts to fetch all DHCPv6 option definitions associated
with "all" servers. The `server-tags` list is mandatory for
this command and it must include exactly one server tag or the keyword "all".
It must not include the `null` value.</para>

The following is the example response to this command:

::

    {
        "result": 0,
        "text": "1 DHCPv6 option definition(s) found.",
        "arguments": {
            "option-defs": [
                {
                    "name": "bar",
                    "code": 1012,
                    "space": "dhcp6",
                    "type": "record",
                    "array": true,
                    "record-types": "ipv6-address, uint16",
                    "encapsulate": "",
                    "metadata": {
                        "server-tags": [ "all" ]
                    }
                }
            ],
            "count": 1
        }
    }

The response contains an option definition associated with all servers as
indicated by the metadata.

.. _command-remote-option-def4-set:

.. _command-remote-option-def6-set:

The remote-option-def4-set, remote-option-def6-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands create a new DHCP option definition or replace an
existing option definition in the database. The structure of the option
definition information is the same as in the Kea configuration file (see
:ref:`dhcp4-custom-options` and :ref:`dhcp6-custom-options`).
The following command creates the DHCPv4 option definition in the
top-level "dhcp4" option space and associates it with the "server1":

::

   {
       "command": "remote-option-def4-set",
       "arguments": {
           "option-defs": [
               {
                   "name": "foo",
                   "code": 222,
                   "type": "uint32",
                   "array": false,
                   "record-types": "",
                   "space": "dhcp4",
                   "encapsulate": ""
               }
           ],
           "remote": {
               "type": "mysql"
           },
           "server-tags": [ "server1" ]
       }
   }

The `server-tags` list must include exactly one
server tag or the keyword "all". It must not contain the
`null` value.</para>

.. _command-remote-option4-global-del:

.. _command-remote-option6-global-del:

The remote-option4-global-del, remote-option6-global-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete a global DHCP option from the
database. The option is identified by an option code and option space.
For example:

::

   {
       "command": "remote-option4-global-del",
       "arguments": {
           "options": [
               {
                   "code": 5
                   "space": "dhcp4"
               }
           ],
           "remote": {
               "type": "mysql"
           },
           "server-tags": [ "server1" ]
       }
   }

The "dhcp4" is the top-level option space where the standard DHCPv4 options
belong. The `server-tags` is mandatory and it must include a
single option tag or the keyword "all". If the explicit server tag is specified
then this command attempts to delete a global option associated with this
server. If there is no such option associated with the given server, no option
is deleted. In order to delete the option associated with all servers, the
keyword "all" must be specified.

.. _command-remote-option4-global-get:

.. _command-remote-option6-global-get:

The remote-option4-global-get, remote-option6-global-get Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch a global DHCP option from the database.
The option is identified by the code and option space. The top-level
option spaces where DHCP standard options belong are called "dhcp4" and
"dhcp6" for the DHCPv4 and DHCPv6 servers, respectively.

The following command retrieves the IPv6 "DNS Servers" (code 23) option
associated with all servers:

::

   {
       "command": remote-option6-global-get",
       "arguments": {
           "options": [
               {
                   "code": 23,
                   "space": "dhcp6"
               }
           ],
           "remote": {
               "type": "mysql"
           },
           "server-tags": [ "all" ]
       }
   }

The `server-tags` is mandatory and it must include exactly one
server tag or the keyword "all". It must not contain the `null`
value.

.. _command-remote-option4-global-get-all:

.. _command-remote-option6-global-get-all:

The remote-option4-global-get-all, remote-option6-global-get-all Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to fetch all global DHCP options from the configuration
database for the particular server or for all servers. The following command
fetches all global DHCPv4 options for the "server1":

::

    {
        "command": "remote-option6-global-get-all",
        "arguments": {
            "remote": {
                "type": "mysql"
            },
            "server-tags": [ "server1" ]
        }
    }

The `server-tags` list is mandatory for this command and
it must contain exactly one server tag or a keyword "all". It must not contain
the `null` value. The following is the example response to this
command with a single option being associated with the "server1" returned:

::

    {
        "result": 0,
        "text": "DHCPv4 options found.",
        "arguments": {
            "options": [
                {
                    "name": "domain-name-servers",
                    "code": 6,
                    "space": "dhcp4",
                    "csv-format": false,
                    "data": "192.0.2.3",
                    "metadata": {
                        "server-tags": [ "server1" ]
                    }
                }
            ],
            "count": 1
        }
    }


.. _command-remote-option4-global-set:

.. _command-remote-option6-global-set:

The remote-option4-global-set, remote-option6-global-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands create a new global DHCP option or replace an existing
option in the database. The structure of the option information is the
same as in the Kea configuration file (see :ref:`dhcp4-std-options`
and :ref:`dhcp6-std-options`). For example:

::

   {
       "command": "remote-option6-global-set",
       "arguments": {
           "options": [
               {
                   "name": "dns-servers",
                   "data": "2001:db8:1::1"
               }
           ],
           "remote": {
               "type": "mysql"
           },
           "server-tags": [ "server1" ]
       }
   }

The `server-tags` list is mandatory for this command
and it must include exactly one server tag or the keyword "all". It must
not include the `null` value. The command above associates
the option with the "server1" server.

Note that specifying an option name instead of the option code only
works reliably for the standard DHCP options. When specifying a value
for the user-defined DHCP option, the option code should be specified
instead of the name. For example:

::

   {
       "command": "remote-option6-global-set",
       "arguments": {
           "options": [
               {
                   "code": 1,
                   "space": "isc",
                   "data": "2001:db8:1::1"
               }
           ],
           "server-tags": [ "server1" ]
       }
   }

.. _command-remote-option4-network-del:

.. _command-remote-option6-network-del:

The remote-option4-network-del, remote-option6-network-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete a shared network specific DHCP
option from the database. The option is identified by an option code
and option space and these two parameters are passed within the
`options` list. Another list, `shared-networks`, contains a map
with the name of the shared network from which the option is to
be deleted. If the option is not explicitly specified for this
shared network, no option is deleted. In particular, the given
option may be present for a subnet belonging to the shared network.
Such option instance is not affected by this command as this
command merely deletes shared network level option. In order to
delete subnet level option the `remote-option[46]-subnet-del`
command must be used instead.

The following command attempts to delete an option having the
option code 5 in the top-level option space from the shared
network "fancy".

::

   {
       "command": "remote-option4-network-del",
       "arguments": {
           "shared-networks": [
               {
                   "name": "fancy"
               }
           ],
           "options": [
               {
                   "code": 5,
                   "space": "dhcp4"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The "dhcp4" is the top-level option space where the standard DHCPv4 options
belong. The `server-tags` parameter must not be specified for this command.

.. _command-remote-option4-network-set:

.. _command-remote-option6-network-set:

The remote-option4-network-set, remote-option6-network-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands create a new shared network specific DHCP option or replace
an existing option in the database. The structure of the option information
is the same as in the Kea configuration file (see :ref:`dhcp4-std-options`
and :ref:`dhcp6-std-options`). The option information is carried in the
`options` list. Another list, `shared-networks`, contains a map with the
name of the shared network for which the option is to be set. If such option
already exists for the shared network, it is replaced with the new instance.

::

   {
       "command": "remote-option6-network-set",
       "arguments": {
           "shared-networks": [
               {
                   "name": "fancy"
               }
           ],
           "options": [
               {
                   "name": "dns-servers",
                   "data": "2001:db8:1::1"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The `sever-tags` parameter must not be specified for this command.

Specifying an option name instead of the option code only works reliably
for the standard DHCP options. When specifying a value for the user-defined
DHCP option, the option code should be specified instead of the name.

.. _command-remote-option6-pd-pool-del:

The remote-option6-pd-pool-del Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command is used to delete a prefix delegation pool specific DHCPv6
option from the database. The option is identified by an option code
and option space and these two parameters are passed within the
`options` list. Another list, `pd-pools`, contains a map with the
prefix delegation pool prefix and length identifying the pool. If the
option is not explicitly specified for this pool, no option is deleted.
In particular, the given option may exist for a subnet containing
the specified pool. Such option instance is not affected by this
command as this command merely deletes a prefix delegation pool level
option. In order to delete subnet level option the
`remote-option6-subnet-del` command must be used instead.

::

   {
       "command": "remote-option6-pd-pool-del",
       "arguments": {
           "pd-pools": [
               {
                   "prefix": "3000::",
                   "prefix-len": 64
               }
           ],
           "options": [
               {
                   "code": 23,
                   "space": "dhcp6"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The "dhcp6" is the top-level option space where the standard DHCPv6 options
belong. The `server-tags` parameter must not be specified for this command.


.. _command-remote-option6-pd-pool-set:

The remote-option6-pd-pool-set Command
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This command creates a new prefix delefation pool specific DHCPv6 option or
replaces an existing option in the database. The structure of the option
information is the same as in the Kea configuration file (see :ref:`dhcp4-std-options`
and :ref:`dhcp6-std-options`). The option information is carried in the
`options` list. Another list, `pd-pools`, contains a map with the prefix
delegation pool prefix and the prefix length identifying the pool. If such
option already exists for the prefix delegation pool, it is replaced with
the new instance.

For example:

::

   {
       "command": "remote-option6-pd-pool-set",
       "arguments": {
           "pd-pools": [
               {
                   "prefix": "3001:1::",
                   "length": 64
               }
           ],
           "options": [
               {
                   "name": "dns-servers",
                   "data": "2001:db8:1::1"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The `sever-tags` parameter must not be specified for this command.

Specifying an option name instead of the option code only works reliably
for the standard DHCP options. When specifying a value for the user-defined
DHCP option, the option code should be specified instead of the name.


.. _command-remote-option4-pool-del:

.. _command-remote-option6-pool-del:

The remote-option4-pool-del, remote-option6-pool-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete an address pool specific DHCP
option from the database. The option is identified by an option code
and option space and these two parameters are passed within the
`options` list. Another list, `pools`, contains a map with the
IP address range or prefix identifying the pool. If the option
is not explicitly specified for this pool, no option is deleted.
In particular, the given option may exist for a subnet containing
the specified pool. Such option instance is not affected by this
command as this command merely deletes a pool level option. In
order to delete subnet level option the `remote-option[46]-subnet-del`
command must be used instead.

The following command attempts to delete an option having the
option code 5 in the top-level option space from an IPv4 address
pool:

::

   {
       "command": "remote-option4-pool-del",
       "arguments": {
           "pools": [
               {
                   "pool": "192.0.2.10 - 192.0.2.100"
               }
           ],
           "options": [
               {
                   "code": 5,
                   "space": "dhcp4"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The "dhcp4" is the top-level option space where the standard DHCPv4 options
belong. The `server-tags` parameter must not be specified for this command.


.. _command-remote-option4-pool-set:

.. _command-remote-option6-pool-set:

The remote-option4-pool-set, remote-option6-pool-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands create a new address pool specific DHCP option or replace
an existing option in the database. The structure of the option information
is the same as in the Kea configuration file (see :ref:`dhcp4-std-options`
and :ref:`dhcp6-std-options`). The option information is carried in the
`options` list. Another list, `pools`, contains a map with the IP address
range or prefix identifying the pool. If such option already exists for the
pool, it is replaced with the new instance.

For example:

::

   {
       "command": "remote-option4-pool-set",
       "arguments": {
           "pools": [
               {
                   "pool": "192.0.2.10 - 192.0.2.100"
               }
           ],
           "options": [
               {
                   "name": "domain-name-servers",
                   "data": "10.0.0.1"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The `sever-tags` parameter must not be specified for this command.

Specifying an option name instead of the option code only works reliably
for the standard DHCP options. When specifying a value for the user-defined
DHCP option, the option code should be specified instead of the name.

.. _command-remote-option4-subnet-del:

.. _command-remote-option6-subnet-del:

The remote-option4-subnet-del, remote-option6-subnet-del Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to delete a subnet specific DHCP option
from the database. The option is identified by an option code
and option space and these two parameters are passed within the
`options` list. Another list, `subnets`, contains a map with the
identifier of the subnet from which the option is to be deleted.
If the option is not explicitly specified for this subnet, no
option is deleted.

The following command attempts to delete an option having the
option code 5 in the top-level option space from the subnet
having an identifer of 123.

::

   {
       "command": "remote-option4-subnet-del",
       "arguments": {
           "subnets": [
               {
                   "id": 123
               }
           ],
           "options": [
               {
                   "code": 5,
                   "space": "dhcp4"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The "dhcp4" is the top-level option space where the standard DHCPv4 options
belong. The `server-tags` parameter must not be specified for this command.

.. _command-remote-option4-subnet-set:

.. _command-remote-option6-subnet-set:

The remote-option4-subnet-set, remote-option6-subnet-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands create a new subnet specific DHCP option or replace an existing
option in the database. The structure of the option information is the same as
in the Kea configuration file (see :ref:`dhcp4-std-options`
and :ref:`dhcp6-std-options`). The option information is carried in the
`options` list. Another list, `subnets`, contains a map with the identifier of
the subnet for which the option is to be set. If such option already exists
for the subnet, it is replaced with the new instance.

::

   {
       "command": "remote-option6-subnet-set",
       "arguments": {
           "subnets": [
               {
                   "id": 123
               }
           ],
           "options": [
               {
                   "name": "dns-servers",
                   "data": "2001:db8:1::1"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The `sever-tags` parameter must not be specified for this command.

Specifying an option name instead of the option code only works reliably
for the standard DHCP options. When specifying a value for the user-defined
DHCP option, the option code should be specified instead of the name.

.. _command-remote-subnet4-del-by-id:

.. _command-remote-subnet6-del-by-id:

The remote-subnet4-del-by-id, remote-subnet6-del-by-id Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the first variant of the commands used to delete an IPv4 or IPv6
subnet from the database. It uses the subnet ID to identify the subnet. For
example, to delete the IPv4 subnet with an ID of 5:

::

   {
       "command": "remote-subnet4-del-by-id",
       "arguments": {
           "subnets": [
               {
                   "id": 5
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The `server-tags` parameter must not be used with this command.

.. _command-remote-subnet4-del-by-prefix:

.. _command-remote-subnet6-del-by-prefix:

The remote-subnet4-del-by-prefix, remote-subnet6-del-by-prefix Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the second variant of the commands used to delete an IPv4 or
IPv6 subnet from the database. It uses the subnet prefix to identify the
subnet. For example:

::

   {
       "command": "remote-subnet6-del-by-prefix",
       "arguments": {
           "subnets": [
               {
                   "subnet": "2001:db8:1::/64"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The `server-tags` parameter must not be used with this command.

.. _command-remote-subnet4-get-by-id:

.. _command-remote-subnet6-get-by-id:

The remote-subnet4-get-by-id, remote-subnet6-get-by-id Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the first variant of the commands used to fetch an IPv4 or IPv6
subnet from the database. It uses a subnet ID to identify the subnet.
For example:

::

   {
       "command": "remote-subnet4-get-by-id",
       "arguments": {
           "subnets": [
               {
                   "id": 5
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The `server-tags` parameter must not be used with this command.

.. _command-remote-subnet4-get-by-prefix:

.. _command-remote-subnet6-get-by-prefix:

The remote-subnet4-get-by-prefix, remote-subnet6-get-by-prefix Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the second variant of the commands used to fetch an IPv4 or IPv6
subnet from the database. It uses a subnet prefix to identify the
subnet. For example:

::

   {
       "command": "remote-subnet6-get-by-prefix",
       "arguments": {
           "subnets": [
               {
                   "subnet": "2001:db8:1::/64"
               }
           ],
           "remote": {
               "type": "mysql"
           }
       }
   }

The `server-tags` parameter must not be used with this command.

.. _command-remote-subnet4-list:

.. _command-remote-subnet6-list:

The remote-subnet4-list, remote-subnet6-list Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to list all IPv4 or IPv6 subnets from the database for
selected servers or all servers. The following command retrieves all servers to
be used by the "server1" and "server2":

::

    {
        "command": "remote-subnet4-list"
        "arguments": {
            "remote": {
                "type": "mysql"
            },
            "server-tags": [ "server1", "server2" ]
        }
    }

The `server-tags` parameter is mandatory and it contains one or
more server tags. It may contain the keyword "all" to fetchg the subnets
associated with all servers. When the `server-tags` list
contains the `null` value the returned response contains a list
of unassigned subnets, i.e. the subnets which are associated with no servers.
For example:

::

    {
        "command": "remote-subnet4-list"
        "arguments": {
            "remote": {
                "type": "mysql"
            },
            "server-tags": [ null ]
        }
    }

The example response to this command when non-null server tags are specified
looks similar to this:

::

    {
        "result": 0,
        "text": "2 IPv4 subnet(s) found.",
        "arguments": {
            "subnets": [
                {
                    "id": 1,
                    "subnet": "192.0.2.0/24",
                    "shared-network-name": null,
                    "metadata": {
                        "server-tags": [ "server1", "server2" ]
                    }
                },
                {
                    "id": 2,
                    "subnet": "192.0.3.0/24",
                    "shared-network-name": null,
                    "metadata": {
                        "server-tags": [ "all" ]
                    }
                }
            ],
            "count": 2
        }
    }

The returned information about each subnet is limited to subnet identifier,
prefix and associated shared network name. In order to retrieve full
information about the selected subnet use the
`remote-subnet[46]-get-by-id` or
`remote-subnet[46]-get-by-prefix`.

The example response above contains two subnets. One of the subnets is
associated with both servers: "server1" and "server2". The second subnet is
associated with all servers, thus it is also present in the configuration for
the "server1" and "server2".

When listing unassigned subnets, the response will look similar to this:

::

    {
        "result": 0,
        "text": "1 IPv4 subnet(s) found.",
        "arguments": {
            "subnets": [
                {
                    "id": 3,
                    "subnet": "192.0.4.0/24",
                    "shared-network-name": null,
                    "metadata": {
                        "server-tags": [ null ]
                    }
                }
            ],
            "count": 1
        }
    }

The `null` value in the metadata indicates that the
returned subnet is unassigned.

.. _command-remote-subnet4-set:

.. _command-remote-subnet6-set:

The remote-subnet4-set, remote-subnet6-set Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These commands are used to create a new IPv4 or IPv6 subnet or replace
an existing subnet in the database. Setting the subnet also associates
or disassociates the subnet with a shared network.

The structure of the subnet information is similar to the structure used
in the configuration file (see :ref:`dhcp4-configuration` and
:ref:`dhcp6-configuration`). The subnet information conveyed in the
``remote-subnet[46]-set`` command must include the additional parameter
``shared-network-name``, which denotes whether the subnet belongs to a
shared network.

Consider the following example:

::

   {
       "command": "remote-subnet4-set",
       "arguments": {
           "subnets": [
               {
                   "id": 5,
                   "subnet": "192.0.2.0/24",
                   "shared-network-name": "level3",
                   "pools": [ { "pool": "192.0.2.100-192.0.2.200" } ],
                   "option-data": [ {
                       "name": "routers",
                       "data": "192.0.2.1"
                   } ]
               }
           ],
           "remote": {
               "type": "mysql"
           },
           "server-tags": [ "all" ]
       }
   }


It creates the subnet and associates it with the "level3" shared
network. The "level3" shared network must be created with the ``remote-network4-set``
command prior to creating the subnet.

If the created subnet must be global - that is, not associated with any shared
network - the ``shared-network-name`` must be explicitly set to
``null``:

::

   {
       "command": "remote-subnet4-set",
       "arguments": {
           "subnets": [
               {
                   "id": 5,
                   "subnet": "192.0.2.0/24",
                   "shared-network-name": null,
                   "pools": [ { "pool": "192.0.2.100-192.0.2.200" } ],
                   "option-data": [ {
                       "name": "routers",
                       "data": "192.0.2.1"
                   } ]
              }
           ],
           "server-tags": [ "all" ]
       }
   }


The subnet created in the previous example is replaced with the new
subnet having the same parameters, but it becomes global.

The ``shared-network-name`` parameter is mandatory for the
``remote-subnet4-set`` command. The `server-tags` list is mandatory and it must
include one or more server tags. As a result, the subnet is associated with all
of the listed servers. It may also be associated with "all" servers connecting
to the database when the keyword "all" is used as the server tag.</para>

.. note::

   As with other "set" commands, this command replaces all the
   information about the particular subnet in the database, if the
   subnet information is already present. Therefore, when sending this
   command, make sure to always include all parameters that must be
   specified for the updated subnet instance. Any unspecified parameter
   will be marked as unspecified in the database, even if its value was
   present prior to sending the command.
