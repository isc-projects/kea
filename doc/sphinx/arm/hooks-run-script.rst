.. _hooks-run-script:

Run Script Support
==================

This hook library adds support for calling an external script for specific
packet-processing hook points.

The library, which was added in Kea 1.9.5, can be loaded in a
similar way to other hook libraries by the ``kea-dhcp4`` and
``kea-dhcp6`` processes.

.. code-block:: json

    {
        "hooks-libraries": [
            {
                "library": "/usr/local/lib/libdhcp_run_script.so",
                "parameters": {
                    "name": "/full_path_to/script_name.sh",
                    "sync": false
                }
            }
        ]
    }

The parameters contain the ``name``, which indicates the full path to the external
script to be called on each hook point, and also the ``sync`` option, to be able
to wait synchronously for the script to finish execution.
If the ``sync`` parameter is ``false``, then the script will launch and Kea
will not wait for the execution to finish, causing all the OUT parameters of
the script (including the next step) to be ignored.

.. note::

   The script inherits all privileges from the server which calls it.

.. note::

   Currently, enabling synchronous calls to external scripts is not supported.

.. _hooks-run-script-hook-points:

This library has several hook-point functions implemented, which are
called at the specific packet-processing stage.

The dhcpv4 hook points:

::

   lease4_renew
   lease4_expire
   lease4_recover
   leases4_committed
   lease4_release
   lease4_decline


The dhcpv6 hook points:

::

   lease6_renew
   lease6_rebind
   lease6_expire
   lease6_recover
   leases6_committed
   lease6_release
   lease6_decline

Each hook point extracts the Kea internal data and exports it as string
environment variables. These parameters are shared with the target script
using the child process environment.
The only parameter passed to the call of the target script is the name of
the hook point.

An example of a script implementing all hook points is presented below:

::

   #!/bin/bash

   unknown_handle() {
       echo "Unhandled function call ${*}"
       exit 123
   }


   lease4_renew () {
       ...
   }

   lease4_expire () {
       ...
   }

   lease4_recover () {
       ...
   }

   leases4_committed () {
       ...
   }

   lease4_release () {
       ...
   }

   lease4_decline () {
       ...
   }

   lease6_renew () {
       ...
   }

   lease6_rebind () {
       ...
   }

   lease6_expire () {
       ...
   }

   lease6_recover () {
       ...
   }

   leases6_committed () {
       ...
   }

   lease6_release () {
       ...
   }

   lease6_decline () {
       ...
   }

   case "$1" in
       "lease4_renew")
           lease4_renew
           ;;
       "lease4_expire")
           lease4_expire
           ;;
       "lease4_recover")
           lease4_recover
           ;;
       "leases4_committed")
           leases4_committed
           ;;
       "lease4_release")
           lease4_release
           ;;
       "lease4_decline")
           lease4_decline
           ;;
       "lease6_renew")
           lease6_renew
           ;;
       "lease6_rebind")
           lease6_rebind
           ;;
       "lease6_expire")
           lease6_expire
           ;;
       "lease6_recover")
           lease6_recover
           ;;
       "leases6_committed")
           leases6_committed
           ;;
       "lease6_release")
           lease6_release
           ;;
       "lease6_decline")
           lease6_decline
           ;;
       *)
           unknown_handle "${@}"
           ;;
   esac


.. _hooks-run-script-exported-environment-variables:

Available parameters for each hook point are presented below.

DHCPv4:

``lease4_renew``

::

   QUERY4_TYPE
   QUERY4_TXID
   QUERY4_LOCAL_ADDR
   QUERY4_LOCAL_PORT
   QUERY4_REMOTE_ADDR
   QUERY4_REMOTE_PORT
   QUERY4_IFACE_INDEX
   QUERY4_IFACE_NAME
   QUERY4_HOPS
   QUERY4_SECS
   QUERY4_FLAGS
   QUERY4_CIADDR
   QUERY4_SIADDR
   QUERY4_YIADDR
   QUERY4_GIADDR
   QUERY4_RELAYED
   QUERY4_HWADDR
   QUERY4_HWADDR_TYPE
   QUERY4_LOCAL_HWADDR
   QUERY4_LOCAL_HWADDR_TYPE
   QUERY4_REMOTE_HWADDR
   QUERY4_REMOTE_HWADDR_TYPE
   QUERY4_OPTION_82
   QUERY4_OPTION_82_SUB_OPTION_1
   QUERY4_OPTION_82_SUB_OPTION_2
   SUBNET4_ID
   SUBNET4_NAME
   SUBNET4_PREFIX
   SUBNET4_PREFIX_LEN
   PKT4_CLIENT_ID
   PKT4_HWADDR
   PKT4_HWADDR_TYPE
   LEASE4_ADDRESS
   LEASE4_CLTT
   LEASE4_HOSTNAME
   LEASE4_HWADDR
   LEASE4_HWADDR_TYPE
   LEASE4_STATE
   LEASE4_SUBNET_ID
   LEASE4_VALID_LIFETIME
   LEASE4_CLIENT_ID

``lease4_expire``

::

   LEASE4_ADDRESS
   LEASE4_CLTT
   LEASE4_HOSTNAME
   LEASE4_HWADDR
   LEASE4_HWADDR_TYPE
   LEASE4_STATE
   LEASE4_SUBNET_ID
   LEASE4_VALID_LIFETIME
   LEASE4_CLIENT_ID
   REMOVE_LEASE

``lease4_recover``

::

   LEASE4_ADDRESS
   LEASE4_CLTT
   LEASE4_HOSTNAME
   LEASE4_HWADDR
   LEASE4_HWADDR_TYPE
   LEASE4_STATE
   LEASE4_SUBNET_ID
   LEASE4_VALID_LIFETIME
   LEASE4_CLIENT_ID

``leases4_committed``

::

   QUERY4_TYPE
   QUERY4_TXID
   QUERY4_LOCAL_ADDR
   QUERY4_LOCAL_PORT
   QUERY4_REMOTE_ADDR
   QUERY4_REMOTE_PORT
   QUERY4_IFACE_INDEX
   QUERY4_IFACE_NAME
   QUERY4_HOPS
   QUERY4_SECS
   QUERY4_FLAGS
   QUERY4_CIADDR
   QUERY4_SIADDR
   QUERY4_YIADDR
   QUERY4_GIADDR
   QUERY4_RELAYED
   QUERY4_HWADDR
   QUERY4_HWADDR_TYPE
   QUERY4_LOCAL_HWADDR
   QUERY4_LOCAL_HWADDR_TYPE
   QUERY4_REMOTE_HWADDR
   QUERY4_REMOTE_HWADDR_TYPE
   QUERY4_OPTION_82
   QUERY4_OPTION_82_SUB_OPTION_1
   QUERY4_OPTION_82_SUB_OPTION_2
   LEASES4_SIZE
   DELETED_LEASES4_SIZE

If ``LEASES4_SIZE`` or ``DELETED_LEASES4_SIZE`` is non-zero, then each lease
has its own unique identifier, as shown below. The first index starts
at 0.

::

   LEASES4_AT0_ADDRESS
   LEASES4_AT0_CLTT
   LEASES4_AT0_HOSTNAME
   LEASES4_AT0_HWADDR
   LEASES4_AT0_HWADDR_TYPE
   LEASES4_AT0_STATE
   LEASES4_AT0_SUBNET_ID
   LEASES4_AT0_VALID_LIFETIME
   LEASES4_AT0_CLIENT_ID
   DELETED_LEASES4_AT0_ADDRESS
   DELETED_LEASES4_AT0_CLTT
   DELETED_LEASES4_AT0_HOSTNAME
   DELETED_LEASES4_AT0_HWADDR
   DELETED_LEASES4_AT0_HWADDR_TYPE
   DELETED_LEASES4_AT0_STATE
   DELETED_LEASES4_AT0_SUBNET_ID
   DELETED_LEASES4_AT0_VALID_LIFETIME
   DELETED_LEASES4_AT0_CLIENT_ID

``lease4_release``

::

   QUERY4_TYPE
   QUERY4_TXID
   QUERY4_LOCAL_ADDR
   QUERY4_LOCAL_PORT
   QUERY4_REMOTE_ADDR
   QUERY4_REMOTE_PORT
   QUERY4_IFACE_INDEX
   QUERY4_IFACE_NAME
   QUERY4_HOPS
   QUERY4_SECS
   QUERY4_FLAGS
   QUERY4_CIADDR
   QUERY4_SIADDR
   QUERY4_YIADDR
   QUERY4_GIADDR
   QUERY4_RELAYED
   QUERY4_HWADDR
   QUERY4_HWADDR_TYPE
   QUERY4_LOCAL_HWADDR
   QUERY4_LOCAL_HWADDR_TYPE
   QUERY4_REMOTE_HWADDR
   QUERY4_REMOTE_HWADDR_TYPE
   QUERY4_OPTION_82
   QUERY4_OPTION_82_SUB_OPTION_1
   QUERY4_OPTION_82_SUB_OPTION_2
   LEASE4_ADDRESS
   LEASE4_CLTT
   LEASE4_HOSTNAME
   LEASE4_HWADDR
   LEASE4_HWADDR_TYPE
   LEASE4_STATE
   LEASE4_SUBNET_ID
   LEASE4_VALID_LIFETIME
   LEASE4_CLIENT_ID

``lease4_decline``

::

   QUERY4_TYPE
   QUERY4_TXID
   QUERY4_LOCAL_ADDR
   QUERY4_LOCAL_PORT
   QUERY4_REMOTE_ADDR
   QUERY4_REMOTE_PORT
   QUERY4_IFACE_INDEX
   QUERY4_IFACE_NAME
   QUERY4_HOPS
   QUERY4_SECS
   QUERY4_FLAGS
   QUERY4_CIADDR
   QUERY4_SIADDR
   QUERY4_YIADDR
   QUERY4_GIADDR
   QUERY4_RELAYED
   QUERY4_HWADDR
   QUERY4_HWADDR_TYPE
   QUERY4_LOCAL_HWADDR
   QUERY4_LOCAL_HWADDR_TYPE
   QUERY4_REMOTE_HWADDR
   QUERY4_REMOTE_HWADDR_TYPE
   QUERY4_OPTION_82
   QUERY4_OPTION_82_SUB_OPTION_1
   QUERY4_OPTION_82_SUB_OPTION_2
   LEASE4_ADDRESS
   LEASE4_CLTT
   LEASE4_HOSTNAME
   LEASE4_HWADDR
   LEASE4_HWADDR_TYPE
   LEASE4_STATE
   LEASE4_SUBNET_ID
   LEASE4_VALID_LIFETIME
   LEASE4_CLIENT_ID

DHCPv6:

``lease6_renew``

::

   QUERY6_TYPE
   QUERY6_TXID
   QUERY6_LOCAL_ADDR
   QUERY6_LOCAL_PORT
   QUERY6_REMOTE_ADDR
   QUERY6_REMOTE_PORT
   QUERY6_IFACE_INDEX
   QUERY6_IFACE_NAME
   QUERY6_REMOTE_HWADDR
   QUERY6_REMOTE_HWADDR_TYPE
   QUERY6_PROTO
   QUERY6_CLIENT_ID
   LEASE6_ADDRESS
   LEASE6_CLTT
   LEASE6_HOSTNAME
   LEASE6_HWADDR
   LEASE6_HWADDR_TYPE
   LEASE6_STATE
   LEASE6_SUBNET_ID
   LEASE6_VALID_LIFETIME
   LEASE6_DUID
   LEASE6_IAID
   LEASE6_PREFERRED_LIFETIME
   LEASE6_PREFIX_LEN
   LEASE6_TYPE
   PKT6_IA_IAID
   PKT6_IA_IA_TYPE
   PKT6_IA_IA_T1
   PKT6_IA_IA_T2

``lease6_rebind``

::

   QUERY6_TYPE
   QUERY6_TXID
   QUERY6_LOCAL_ADDR
   QUERY6_LOCAL_PORT
   QUERY6_REMOTE_ADDR
   QUERY6_REMOTE_PORT
   QUERY6_IFACE_INDEX
   QUERY6_IFACE_NAME
   QUERY6_REMOTE_HWADDR
   QUERY6_REMOTE_HWADDR_TYPE
   QUERY6_PROTO
   QUERY6_CLIENT_ID
   LEASE6_ADDRESS
   LEASE6_CLTT
   LEASE6_HOSTNAME
   LEASE6_HWADDR
   LEASE6_HWADDR_TYPE
   LEASE6_STATE
   LEASE6_SUBNET_ID
   LEASE6_VALID_LIFETIME
   LEASE6_DUID
   LEASE6_IAID
   LEASE6_PREFERRED_LIFETIME
   LEASE6_PREFIX_LEN
   LEASE6_TYPE
   PKT6_IA_IAID
   PKT6_IA_IA_TYPE
   PKT6_IA_IA_T1
   PKT6_IA_IA_T2

``lease6_expire``

::

   LEASE6_ADDRESS
   LEASE6_CLTT
   LEASE6_HOSTNAME
   LEASE6_HWADDR
   LEASE6_HWADDR_TYPE
   LEASE6_STATE
   LEASE6_SUBNET_ID
   LEASE6_VALID_LIFETIME
   LEASE6_DUID
   LEASE6_IAID
   LEASE6_PREFERRED_LIFETIME
   LEASE6_PREFIX_LEN
   LEASE6_TYPE
   REMOVE_LEASE

``lease6_recover``

::

   LEASE6_ADDRESS
   LEASE6_CLTT
   LEASE6_HOSTNAME
   LEASE6_HWADDR
   LEASE6_HWADDR_TYPE
   LEASE6_STATE
   LEASE6_SUBNET_ID
   LEASE6_VALID_LIFETIME
   LEASE6_DUID
   LEASE6_IAID
   LEASE6_PREFERRED_LIFETIME
   LEASE6_PREFIX_LEN
   LEASE6_TYPE

``leases6_committed``

::

   QUERY6_TYPE
   QUERY6_TXID
   QUERY6_LOCAL_ADDR
   QUERY6_LOCAL_PORT
   QUERY6_REMOTE_ADDR
   QUERY6_REMOTE_PORT
   QUERY6_IFACE_INDEX
   QUERY6_IFACE_NAME
   QUERY6_REMOTE_HWADDR
   QUERY6_REMOTE_HWADDR_TYPE
   QUERY6_PROTO
   QUERY6_CLIENT_ID
   LEASES6_SIZE
   DELETED_LEASES6_SIZE

If ``LEASES6_SIZE`` or ``DELETED_LEASES6_SIZE`` is non-zero, then each lease
has its own unique identifier, as shown below. The first index starts
at 0.

::

   LEASES6_AT0_ADDRESS
   LEASES6_AT0_CLTT
   LEASES6_AT0_HOSTNAME
   LEASES6_AT0_HWADDR
   LEASES6_AT0_HWADDR_TYPE
   LEASES6_AT0_STATE
   LEASES6_AT0_SUBNET_ID
   LEASES6_AT0_VALID_LIFETIME
   LEASES6_AT0_DUID
   LEASES6_AT0_IAID
   LEASES6_AT0_PREFERRED_LIFETIME
   LEASES6_AT0_PREFIX_LEN
   LEASES6_AT0_TYPE
   DELETED_LEASES6_AT0_ADDRESS
   DELETED_LEASES6_AT0_CLTT
   DELETED_LEASES6_AT0_HOSTNAME
   DELETED_LEASES6_AT0_HWADDR
   DELETED_LEASES6_AT0_HWADDR_TYPE
   DELETED_LEASES6_AT0_STATE
   DELETED_LEASES6_AT0_SUBNET_ID
   DELETED_LEASES6_AT0_VALID_LIFETIME
   DELETED_LEASES6_AT0_DUID
   DELETED_LEASES6_AT0_IAID
   DELETED_LEASES6_AT0_PREFERRED_LIFETIME
   DELETED_LEASES6_AT0_PREFIX_LEN
   DELETED_LEASES6_AT0_TYPE

``lease6_release``

::

   QUERY6_TYPE
   QUERY6_TXID
   QUERY6_LOCAL_ADDR
   QUERY6_LOCAL_PORT
   QUERY6_REMOTE_ADDR
   QUERY6_REMOTE_PORT
   QUERY6_IFACE_INDEX
   QUERY6_IFACE_NAME
   QUERY6_REMOTE_HWADDR
   QUERY6_REMOTE_HWADDR_TYPE
   QUERY6_PROTO
   QUERY6_CLIENT_ID
   LEASE6_ADDRESS
   LEASE6_CLTT
   LEASE6_HOSTNAME
   LEASE6_HWADDR
   LEASE6_HWADDR_TYPE
   LEASE6_STATE
   LEASE6_SUBNET_ID
   LEASE6_VALID_LIFETIME
   LEASE6_DUID
   LEASE6_IAID
   LEASE6_PREFERRED_LIFETIME
   LEASE6_PREFIX_LEN
   LEASE6_TYPE

``lease6_decline``

::

   QUERY6_TYPE
   QUERY6_TXID
   QUERY6_LOCAL_ADDR
   QUERY6_LOCAL_PORT
   QUERY6_REMOTE_ADDR
   QUERY6_REMOTE_PORT
   QUERY6_IFACE_INDEX
   QUERY6_IFACE_NAME
   QUERY6_REMOTE_HWADDR
   QUERY6_REMOTE_HWADDR_TYPE
   QUERY6_PROTO
   QUERY6_CLIENT_ID
   LEASE6_ADDRESS
   LEASE6_CLTT
   LEASE6_HOSTNAME
   LEASE6_HWADDR
   LEASE6_HWADDR_TYPE
   LEASE6_STATE
   LEASE6_SUBNET_ID
   LEASE6_VALID_LIFETIME
   LEASE6_DUID
   LEASE6_IAID
   LEASE6_PREFERRED_LIFETIME
   LEASE6_PREFIX_LEN
   LEASE6_TYPE
