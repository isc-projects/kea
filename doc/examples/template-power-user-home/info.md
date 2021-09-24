Template: Home network of a power user
--------------------------------------

This directory contains template configurations for home network of a power user. It may also be
appropriate for a small office. It makes the following assumptions:

- you want to use a single /24 class of IPv4 addresses
- you want High Availability, so there are 2 DHCP servers
- you have a handful of devices, and some of them (e.g. a printer or NAS) require
  static addresses or extra options
- you do not want to be bothered with database management
- the setup is optimized for minimal-to-zero maintenance
- performance is not an issue. You do not expect to see 100s of queries per second
- you do not use IPv6
- you do not want to update your DNS

The logical set-up consists of two hosts, each running Kea DHCPv4 server and a Control Agent (CA).
The server connects with the CA using UNIX sockets. Each DHCPv4+CA acts as one partner of the HA
pair.

.. code-block:: none

  ```
   +-host-1-+       +-host-2-+
   |        |       |        |
   |   CA <===\   /===> CA   |    ===== - HTTP connection
   |   #    |  \ /  |   #    |
   |   #    |   X   |   #    |    ##### - UNIX socket
   |   #    |  / \      #    |
   | DHCPv4 ==/   \== DHCPv4 |
   |        |       |        |
   +--------+       +--------+
  ```

The CA at host 1 and CA at host 2 will both listen on port 8000. The DHCP servers will communicate
with each other via CAs which forward control commands to the DHCP servers over the UNIX domain
sockets.

Deployment Considerations
~~~~~~~~~~~~~~~~~~~~~~~~~

The setup is not expected to be very performant. Most modest hardware will do. There are successful
deployments on Raspberry Pi platforms. If you are running a VM, 2GB ram with one CPU core should
be enough. If you don't have any preference, Ubuntu LTS is a choice that is easy to set up and is
low maintenance. However, any Linux or FreeBSD is fine. Less popular systems, such as OpenBSD or
NetBSD should also work in principle, but they are not regularly tested.

The assumption is that there are 2 hosts that will be running the Kea setup:

- 192.168.1.2 - primary HA server (active, will handle all the traffic)

- 192.168.1.3 - secondary HA server (passive, ready to take over in case the primary fails)

The network is 192.168.1.0/24. It is assumed that 192.168.1.1 is your default router.

The whole subnet is split into dynamic and static pools:

- 192.168.1.100 - 192.168.1.199 - this is the dynamic pool. When new devices appear in your network,
  they will be assigned dynamic addresses from this pool.
- The reservations are done outside of this dynamic range (depending on your addressing preference,
  either 192.168.1.1-192.168.1.99 or 192.168.1.200-192.168.1.254).

To deploy this setup, you need to conduct the following steps:

1. Install CA and DHCPv4 on host1, copy the config files to the typical locations. It's typically
   ``/etc/kea`` on Linux and ``/usr/local/etc/kea`` on FreeBSD. The files are typically called
   ``kea-ctrl-agent.conf`` and ``kea-dhcp4.conf``. Please consult your start-up scripts.

2. At the very least alter the following to match your setup:

   - the interface name which Kea should listen on (``interfaces`` in ``interfaces-config``)

   - the interface name which is used to access the subnet (``interface`` in ``subnet4``)

   - your addressing, if you use something different than 192.168.1.0/24. Make sure the CA port
     configuration (``http-host`` and ``http-port`` in kea-ca.conf) matches your DHCPv4 server
     configuration (``url`` in ``hook-libraries/parameters/high-availability/peers`` in kea-dhcp4.conf).

   - tweak your router option to match your actual network

   - tweak your DNS option to match your actual network

   - the path to the hook libraries. This is very OS specific parameter. The library names are in
     general the same everywhere, but the path varies. See Section 16.2 of the Kea ARM for details.

3. If using a firewall, make sure server1 can reach server2. A nice way to ensure that is to
   try to retrieve server2's config from server1:

   ``curl -X POST -H "Content-Type: application/json" -d '{ "command": "config-get", "service": [ "dhcp4" ] }'  http://192.168.1.3:8000/``

   You should get a DHCPv4 running configuration in return in a JSON format.

4. Make sure the opposite direction (server2 can connect to server1) works too. Simply repeat
   step 3 from the server2 and user server's 1 IP address and port.

5. Install CA and DHCPv4 on host2, similar to steps 1 and 2. Note the config file for the
   standby server is very similar, except the definition of ``this-server-name`` field
   (and possibly inteface names). In many cases you can simply copy over the file
   and just tweak it a little bit.

Possible extensions
~~~~~~~~~~~~~~~~~~~

The proposed configuration is somewhat basic, but functional. Once your setup is up and running, you
may want to consider the following changes:

- if you have your own DNS server, you may configure DNS Updates. This requires running a D2 server
  (``kea-dhcp-ddns``), which is a nickname for DHCP-DDNS update server. See Section 13 of the Kea ARM
  for details.

- if you want to run Stateful DHCP for IPv6, you will need to run ``kea-dhcp6`` server. Its configuration
  is very similar to ``kea-dhcp4``, but there are some notable differences: the default gateway is not
  configured via DHCPv6 protocol, but via Router Advertisements sent by your router. Also, there is
  a concept of Prefix Delegation, which was non-existent in the DHCPv4. See Section 9 of the Kea ARM
  for details.

- if you want to expand your network, adding MySQL or PostgreSQL database is a popular direction for
  growing networks. You can choose to store leases, host reservations and even most of the configuration
  in a database. See Section 4 of the Kea ARM and ``lease-database``, ``hosts-database``, and
  ``config-control`` parameters in Section 8 of the Kea ARM.

- if you want to get more insight into how your DHCP server operates, you may use REST API to query
  for a lot of run-time statistics or even change your configuration during run-time. You may also
  consider deploying Stork, which is a young, but fast growing dashboard for Kea. See Section 22
  of the Kea ARM for pointers.

- you should probably also read Section 23 of the Kea ARM that discusses various trade offs between
  convenience and security.
