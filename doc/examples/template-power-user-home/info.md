
Kea Configuration Template: Home network of a power user
========================================================

This directory contains template configurations for home network of a power user.
It may also be appropriate for a small office. It makes the following assumptions:

- you want to use a single /24 class of IPv4 addresses
- you want High Availability, so there are 2 DHCP servers
- you have a handful of devices, and some of them (e.g. a printer or NAS) require
  static addresses or extra options
- you do not want to be bothered with database management
- the setup is optimized for minimal-to-zero maintenance
- performance is not an issue. You do not expect to see 100s of queries per second
- you do not use IPv6
- you do not want to update your DNS

The logical set-up consists of two hosts, each running Kea DHCPv4 server and a Control
Agent (CA). The server connects with the CA using UNIX sockets. Each DHCPv4+CA acts
as one partner of the HA pair.

```mermaid
CA-1 ====== CA-2

subgraph host1
CA-1 ------ DHCPv4-1

subgraph host2
CA-2 ------ DHCPv4-2
```

Deployment Considerations
-------------------------
