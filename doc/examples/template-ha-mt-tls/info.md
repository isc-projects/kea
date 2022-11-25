Template: Secure High Availability Kea DHCP with multi-threading
----------------------------------------------------------------

Below are some templates to assist in configuring a secure Kea DHCP server with
multi-threading. These templates make the following assumptions:

- the administrator wants to set up High Availability with multi-threading.
- the machines running Kea with multi-threading have at least 4 CPUs.
- the connection to the peer is secured using TLS.

The logical setup consists of two hosts, each running a Kea DHCPv4 server and a Control Agent (CA).
In the multi-threading setup, the CA is not required, as the server is using it's
own dedicated HTTP listener to communicate with the peer. However it can still
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

The CA on host-1 and CA on host-2 both listen on port 8001, and the server dedicated HTTP
listener uses port 8000. The DHCP servers communicate with each other via the dedicated HTTP
listener, which forward only the lease updates commands to the peer server.

Deployment Considerations
~~~~~~~~~~~~~~~~~~~~~~~~~

The setup is not expected to scale automatically. This example uses 4 threads for
processing DHCP traffic, 4 threads for listening and handling HA peer HTTP requests
and 4 threads for sending lease updates to the HA peer. The thread queue used to
store incoming DHCP requests is set to 64, but specific values for better
performance must be determined on the deployment setup by doing proper testing
and benchmarks.

The assumption is that there are two hosts that are running the Kea setup:

- 192.168.1.2 - primary HA server (active, handles all the traffic)

- 192.168.1.3 - secondary HA server (passive, ready to take over if the primary fails)

The network is 192.168.1.0/24. It is assumed that 192.168.1.1 is the default router.

The whole subnet is split into dynamic pools:

- 192.168.1.100 - 192.168.1.199 - this is the dynamic pool. When new devices appear in the network,
  they are assigned dynamic addresses from this pool.

To deploy this setup, follow the steps provided in the power user home setup with the following distinctions:

1. Install CA only if the administrator is planning to manage Kea using RESTful API.
   Otherwise, the High Availability Kea server with multi-threading does not require CA to run.

2. Alter the following to match the local setup:

   - the paths to ``trust-anchor``, ``cert-file``, ``key-file`` must be set to the
     respective values corresponding to the deployment machine.

   - the addressing, if using something other than 192.168.1.0/24. Make sure the CA port
     configuration (``http-host`` and ``http-port`` in ``kea-ca.conf``) is different than the DHCPv4 server
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

The proposed configuration is somewhat basic, but functional. Once it is set up and running, administrators
may wish to consider the following changes:

- if using a database, configuring TLS for the database backend (either for lease, host, configuration backend or forensic logging)
  is also possible. See :ref:`database-connectivity` for more information.
