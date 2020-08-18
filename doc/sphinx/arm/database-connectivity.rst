.. _database-connectivity:

*********************
Database Connectivity
*********************
Kea servers (kea-dhcp4 and kea-dhcp6) can be configured to use a variety of 
database back ends for leases, hosts and configuration.  All of them may be 
configured to support automatic recovery when connectivity is lost (see 
``max-reconnect-tries`` and ``reconnect-wait-time``).

It is important to understand how and when automatic recovery comes into play.  
Automatic recovery, when configured, only operates after a successful start up 
or reconfiguration during which connectivity to all back ends has been 
successfully established.

During server start up the inability to connect to any of the configured back
ends is always considered fatal.  A fatal error will be logged and the server
will exit.  This is done based on the idea that configuration should be valid
at start up. Exiting to the operating system allows nanny scripts to detect
the problem.

During dynamic reconfiguration, all back ends are disconnected and then
reconnected using the new configuration.  If connectivity to any of the
back ends cannot be established, the server will log a fatal error but remain
up. It will be able to process commands but will not serve clients. This 
allows the configuration to be corrected via command, if required.

During normal operations, if connectivity to any of the back ends is lost and 
automatic recovery for that back end is enabled, the server will disconnect 
from all back ends, and then attempt to reconnect them.  During the recovery
process the server will cease serving clients but continue to respond to 
commands.  If connectivity to all back ends is restored the server will 
return to normal operations.  If connectivity cannot be restored after
``max-reconnect-tries``,  the server will issue a fatal error and exit.
