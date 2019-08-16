.. _class-cmds-library:

class_cmds: Class Commands
==========================

This section describes the Class Commands hooks library, which exposes
several control commands for manipulating client classes (part of the
Kea DHCP servers' configurations) without the need to restart those
servers. Using these commands it is possible to add, update, delete, and
list client classes configured for a given server.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or
   ``kea-dhcp6`` process.

The Class Commands hooks library is currently available only to ISC
customers with a paid support contract.

.. _command-class-add:

The class-add Command
~~~~~~~~~~~~~~~~~~~~~

The ``class-add`` command adds a new client class to the DHCP server
configuration. This class is appended at the end of the list of classes
used by the server and may depend on any of the already-configured
client classes.

The following example demonstrates how to add a new client class to the
DHCPv4 server configuration:

::

   {
       "command": "class-add",
       "arguments": {
           "client-classes": [
               {
                   "name": "ipxe_efi_x64",
                   "test": "option[93].hex == 0x0009",
                   "next-server": "192.0.2.254",
                   "server-hostname": "hal9000",
                   "boot-file-name": "/dev/null"
               }
           ]
       }
   }

Note that the ``client-classes`` parameter is a JSON list, but it allows
only a single client class to be present.

Here is the response to the ``class-add`` command in our example:

::

   {
       "result": 0,
       "text": "Class 'ipxe_efi_x64' added."
   }

.. _command-class-update:

The class-update Command
~~~~~~~~~~~~~~~~~~~~~~~~

The ``class-update`` command updates an existing client class in the
DHCP server configuration. If the client class with the given name
does not exist, the server returns the result code of 3, which means that
the server configuration is not modified and the client class does not
exist. The ``class-add`` command must be used instead to create the new
client class.

The ``class-update`` command has the same argument structure as the
``class-add`` command:

::

   {
       "command": "class-update",
       "arguments": {
           "client-classes": [
               {
                   "name": "ipxe_efi_x64",
                   "test": "option[93].hex == 0x0017",
                   "next-server": "0.0.0.0",
                   "server-hostname": "xfce",
                   "boot-file-name": "/dev/null"
               }
           ]
       }
   }

Here is the response for our example:

::

   {
       "result": 0,
       "text": "Class 'ipxe_efi_x64' updated."
   }

Any parameter of the client class can be modified with this command,
except ``name``. There is currently no way to rename the class, because
the class name is used as a key for searching the class to be updated.
To achieve a similar effect to renaming the class, an existing class can
be removed with the ``class-del`` command and then added again with a
different name using ``class-add``. Note, however, that the class with
the new name will be added at the end of the list of configured classes.

.. _command-class-del:

The class-del Command
~~~~~~~~~~~~~~~~~~~~~


The ``class-del`` command is used to remove a particular class from the server
configuration. The class to be removed is identified by name. The class
is not removed if there are other classes depending on it; to remove
such a class, the dependent classes must be removed first.

The following is a sample command removing the ``ipxe_efi_x64`` class:

::

   {
       "command": "class-del",
       "arguments": {
           {
               "name": "ipxe_efi_x64"
           }
       }
   }

Here is the response to the ``class-del`` command in our example, when
the specified client class has been found:

::

   {
       "result": 0,
       "text": "Class 'ipxe_efi_x64' deleted."
   }

If the class does not exist, the result of 3 is returned.

.. _command-class-list:

The class-list Command
~~~~~~~~~~~~~~~~~~~~~~


``class-list`` is used to retrieve a list of all client classes. This
command includes no arguments:

::

   {
       "command": "class-list"
   }

Here is the response of the server in our example, including the list of
client classes:

::

   {
       "result": 0,
       "text": "2 classes found",
       "arguments": {
           "client-classes": [
               {
                   "name": "ipxe_efi_x64"
               },
               {
                   "name": "pxeclient"
               }
           ]
       }
   }

Note that the returned list does not contain full class definitions, but
merely class names. To retrieve full class information, the
``class-get`` command should be used.

.. _command-class-get:

The class-get Command
~~~~~~~~~~~~~~~~~~~~~


``class-get`` is used to retrieve detailed information about a specified
class. The command structure is very simple:

::

   {
       "command": "class-get",
       "arguments": {
           "name": "pxeclient"
       }
   }

If the class with the specified name does not exist, the status code of
3 is returned. If the specified client class exists, the class details
are returned in the following format:

::

   {
       "result": 0,
       "text": "Class 'pxeclient' definition returned",
       "arguments": {
           "client-classes": [
               {
                   "name": "pxeclient",
                   "only-if-required": true,
                   "test": "option[vendor-class-identifier].text == 'PXEClient'",
                   "option-def": [
                       {
                           "name": "configfile",
                           "code": 209,
                           "type": "string"
                       }
                   ],
                   "option-data": [ ],
                   "next-server": "0.0.0.0",
                   "server-hostname": "xfce",
                   "boot-file-name": "/dev/null"
               }
           ]
       }
   }

Note that the example above is DHCPv4-specific; the last three
parameters are only returned by the DHCPv4 server and are never returned
by the DHCPv6 server. Also, some of the parameters provided in this
example may not be returned if they are not specified for the class.
Specifically, ``only-if-required``, ``test``, and ``option-def`` are not
returned if they are not specified for the class.
