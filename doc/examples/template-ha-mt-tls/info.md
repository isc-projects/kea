Template: Secure High Availability Kea DHCP with Multi-Threading
----------------------------------------------------------------

Below are some templates to assist in configuring a secure Kea DHCP server with
multi-threading. These templates make the following assumptions:

- The administrator wants to set up High Availability (HA) with multi-threading.
- The machines running Kea with multi-threading have at least four CPU cores.
- The connection to the peer is secured using TLS.

The logical setup consists of two hosts, each running a Kea DHCPv4 server and a Control Agent (CA).
In the multi-threading setup, the CA is not required, as the server is using its
own dedicated HTTP listener to communicate with the peer. However, the CA can still
be used to handle user commands.

.. code-block:: none

   +-host-1-+       +-host-2-+
   |        |       |        |
   |   CA   |       |   CA   |    ===== - HTTPS connection
   |   #    |       |   #    |
   |   #    |       |   #    |    ##### - UNIX socket
   |   #    |       |   #    |
   | DHCPv4 ========= DHCPv4 |
   |        |       |        |
   +--------+       +--------+

The CAs on host-1 and host-2 both listen on port 8001, and the server's dedicated HTTP
listener uses port 8000. The DHCP servers communicate with each other via the dedicated HTTP
listener, which forwards only the lease-update commands to the peer server.

Deployment Considerations
~~~~~~~~~~~~~~~~~~~~~~~~~

The setup is not expected to scale automatically. This example uses four threads for
processing DHCP traffic, four threads for listening and handling HA peer HTTP requests,
and four threads for sending lease updates to the HA peer. The thread queue used to
store incoming DHCP requests is set to 64, but proper testing and benchmarks are required
to determine the appropriate values for best performance on the deployment setup.

In this example, there are two hosts running Kea:

- 192.168.1.2 - primary HA server (active, handles all the traffic)

- 192.168.1.3 - secondary HA server (passive, ready to take over if the primary fails)

The network is 192.168.1.0/24. It is assumed that 192.168.1.1 is the default router.

The whole subnet is split into dynamic pools:

- 192.168.1.100 - 192.168.1.199 - this is the dynamic pool. When new devices appear in the network,
  they are assigned dynamic addresses from this pool.

To deploy this setup, follow the steps provided in the power user home setup with the following distinctions:

1. Install the CA only if the administrator is planning to manage Kea using the RESTful API.
   Otherwise, the CA is not required for the High Availability Kea server with multi-threading.

2. Alter the following to match the local setup:

   - The paths to ``trust-anchor``, ``cert-file``, and ``key-file`` must be set to the
     respective values corresponding to the deployment machine.

   - The addressing must be updated, if using something other than 192.168.1.0/24. Make sure the CA port
     configuration (``http-host`` and ``http-port`` in ``kea-ca.conf``) is different from the DHCPv4 server
     configuration (``url`` in ``hook-libraries/parameters/high-availability/peers`` in ``kea-dhcp4.conf``).
     The CA is used to handle only management commands, as the HA module sends lease updates using
     the dedicated HTTP listener to the peer.

3. Verify the communication between the HA peers by checking the Kea logs.

4. Verify that communication between the hosts works in the opposite direction as well
   (host-2 can connect to host-1), by repeating step 3 from host-2 using host-1's IP address and port.

5. Install the CA and DHCPv4 on host-2, as in steps 1 and 2. The config file for the
   standby server is very similar to the one on the primary server, other than the definition of
   the ``this-server-name`` field (and possibly the interface names).

Possible Extensions
~~~~~~~~~~~~~~~~~~~

This sample configuration is basic but functional. Once it is set up and running, administrators
may wish to consider the following changes:

- If using a database, it is also possible to configure TLS for the database backend (for
  lease, host, configuration backend, or forensic logging). See :ref:`database-connectivity`
  for more information.
