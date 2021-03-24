.. _database-connectivity:

*********************
Database Connectivity
*********************
Kea servers (kea-dhcp4 and kea-dhcp6) can be configured to use a variety of
database backends for leases, hosts, and configuration. All of them may be
configured to support automatic recovery when connectivity is lost (see
``max-reconnect-tries``, ``reconnect-wait-time``and
``disable-service-on-db-loss``).

It is important to understand how and when automatic recovery comes into play.
Automatic recovery, when configured, only operates after a successful startup
or reconfiguration during which connectivity to all backends has been
successfully established.

During server startup, the inability to connect to any of the configured
backends is always considered fatal. A fatal error is logged and the server
exits, based on the idea that the configuration should be valid
at startup. Exiting to the operating system allows nanny scripts to detect
the problem.

During dynamic reconfiguration, all backends are disconnected and then
reconnected using the new configuration. If connectivity to any of the
backends cannot be established, the server logs a fatal error but remains
up. It is able to process commands but does not serve clients. This
allows the configuration to be corrected via command, if required.

During normal operations, if connectivity to any of the backends is lost and
automatic recovery for that backend is enabled, the server disconnects from the
respective backend and then attempts to reconnect. During the recovery process,
the server ceases to serve clients according to the
``disable-service-on-db-loss`` configured option, and continues to respond to
commands. If connectivity to all backends is restored, the server returns to
normal operations. If connectivity cannot be restored after
``max-reconnect-tries``, the server issues a fatal error and exits.
