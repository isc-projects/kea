Template: Home Network of a Power User
--------------------------------------

Below are some templates to assist in configuring the home network of a power user; they may also be
appropriate for a small office. These templates make the following assumptions:

- The administrator wants to use a single /24 class of IPv4 addresses.
- High Availability (HA) is desired, so there are two DHCP servers.
- There are a handful of devices, and some of them (e.g. a printer or NAS) require
  static addresses or extra options.
- The administrator does not want to be bothered with database management.
- The setup is optimized for minimal to zero maintenance.
- Performance is not an issue; hundreds of queries per second are not expected.
- IPv6 is not used.
- DNS updates will not be performed by Kea.

The logical setup consists of two hosts, each running a Kea DHCPv4 server and a Control Agent (CA).
The server connects with the CA using UNIX sockets. Each DHCPv4+CA acts as one partner of the HA
pair.

.. code-block:: none

   +-host-1-+       +-host-2-+
   |        |       |        |
   |   CA <===\   /===> CA   |    ===== - HTTP connection
   |   #    |  \ /  |   #    |
   |   #    |   X   |   #    |    ##### - UNIX socket
   |   #    |  / \      #    |
   | DHCPv4 ==/   \== DHCPv4 |
   |        |       |        |
   +--------+       +--------+

The CAs on host-1 and host-2 both listen on port 8000. The DHCP servers communicate
with each other via the CAs, which forward control commands to the DHCP servers over the UNIX domain
sockets.

Deployment Considerations
~~~~~~~~~~~~~~~~~~~~~~~~~

This setup is not expected to be very performant. Most modest hardware will do; Kea has been successfully
deployed on Raspberry Pi platforms, for example. If it is running on a VM, 2GB of RAM with one CPU core should
be sufficient. Ubuntu LTS is a choice that is easy to set up and is
low maintenance; however, any Linux or FreeBSD operating system is fine. Less popular systems, such as OpenBSD or
NetBSD, should also work in principle, but they are not regularly tested.

In this example, there are two hosts running Kea:

- 192.168.1.2 - primary HA server (active, handles all the traffic)

- 192.168.1.3 - secondary HA server (passive, ready to take over if the primary fails)

The network is 192.168.1.0/24. It is assumed that 192.168.1.1 is the default router.

The whole subnet is split into dynamic and static pools:

- 192.168.1.100 - 192.168.1.199 - this is the dynamic pool. When new devices appear in the network,
  they are assigned dynamic addresses from this pool.
- The reservations are done outside of this dynamic range (depending on the addressing preference,
  either 192.168.1.1-192.168.1.99 or 192.168.1.200-192.168.1.254).

To deploy this setup, perform the following steps:

1. Install the CA and the DHCPv4 server on host-1, and copy the configuration files to their typical locations.
   They are usually in ``/etc/kea`` on Linux and ``/usr/local/etc/kea`` on FreeBSD, and the files are typically called
   ``kea-ctrl-agent.conf`` and ``kea-dhcp4.conf``. Please consult the startup scripts for any specific system.

2. Alter the following to match the local setup:

   - The interface name that Kea should listen on (``interfaces`` in ``interfaces-config``).

   - The interface name that is used to access the subnet (``interface`` in ``subnet4``).

   - The addressing, if using something other than 192.168.1.0/24. Make sure the CA port
     configuration (``http-host`` and ``http-port`` in ``kea-ca.conf``) matches the DHCPv4 server
     configuration (``url`` in ``hook-libraries/parameters/high-availability/peers`` in ``kea-dhcp4.conf``).

   - The router option, to match the actual network.

   - The DNS option, to match the actual network.

   - The path to the hook libraries. This is a very OS-specific parameter; the library names are
     generally the same everywhere, but the path varies. See :ref:`hooks-libraries-introduction` for details.

3. If using a firewall, make sure host-1 can reach host-2. An easy way to ensure that is to
   try to retrieve host-2's config from host-1:

   ``curl -X POST -H "Content-Type: application/json" -d '{ "command": "config-get", "service": [ "dhcp4" ] }'  http://192.168.1.3:8000/``

   The DHCPv4 running configuration should be returned, in JSON format.

4. Verify that communication between the hosts works in the opposite direction as well
   (host-2 can connect to host-1), by repeating step 3 from host-2 using host-1's IP address and port.

5. Install the CA and the DHCPv4 server on host-2, as in steps 1 and 2. The config file for the
   standby server is very similar to the one on the primary server, other than the definition of
   the ``this-server-name`` field (and possibly the interface names).

Possible Extensions
~~~~~~~~~~~~~~~~~~~

This sample configuration is basic but functional. Once it is set up and running, administrators
may wish to consider the following changes:

- If there is a local DNS server, DNS updates can be configured via Kea. This requires running a DHCP-DDNS update server
  (``kea-dhcp-ddns``). See :ref:`dhcp-ddns-overview` for details.

- To run Stateful DHCP for IPv6, a ``kea-dhcp6`` server is necessary. Its configuration
  is very similar to ``kea-dhcp4``, but there are some notable differences: the default gateway is not
  configured via the DHCPv6 protocol, but via router advertisements sent by the local router. Also, the
  DHCPv6 concept of prefix delegation does not exist in DHCPv4. See :ref:`dhcp6`
  for details.

- To expand the local network, adding a MySQL or PostgreSQL database is a popular solution.
  Users can choose to store leases, host reservations, and even most of the configuration
  in a database. See :ref:`admin` and the ``lease-database``, ``hosts-database``, and
  ``config-control`` parameters in :ref:`dhcp4`.

- To provide more insight into how the DHCP server operates, Kea's RESTful API can query
  for many runtime statistics or even change the configuration during runtime. Users may also
  consider deploying Stork, which is a rapidly developing dashboard for Kea. See :ref:`stork`
  for more information.

- All Kea users should read :ref:`security`: to learn about various trade-offs between
  convenience and security in Kea.
