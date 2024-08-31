.. _database-connectivity:

*********************
Database Connectivity
*********************

The Kea servers (:iscman:`kea-dhcp4` and :iscman:`kea-dhcp6`) can be configured to use a variety of
database backends for leases, hosts, and configuration. They can be
configured to support automatic recovery when connectivity is lost, via
the ``on-fail`` and ``retry-on-startup`` parameters.
(The ``reconnect-wait-time`` and ``max-reconnect-tries`` parameters are
described in :ref:`database-configuration4` and :ref:`database-configuration6`.)

It is important to understand how and when automatic recovery comes into play.
Automatic recovery, when configured, only operates after a successful startup
or reconfiguration during which connectivity to all backends has been
successfully established.

During server startup, the inability to connect to any of the configured
backends is considered fatal only if ``retry-on-startup`` is set to ``false``
(the default). A fatal error is logged and the server exits, based on the idea
that the configuration should be valid at startup. Exiting to the operating
system allows nanny scripts to detect the problem.
If ``retry-on-startup`` is set to ``true``, the server will start reconnection
attempts even at server startup or on reconfigure events, and will honor the
action specified in the ``on-fail`` parameter.

During dynamic reconfiguration, all backends are disconnected and then
reconnected using the new configuration. If connectivity to any of the
backends cannot be established, the server logs a fatal error but remains
up. It is able to process commands but does not serve clients. This
allows the configuration to be corrected via the :isccmd:`config-set` or
``remote-*`` commands, if required.

During normal operations, if connectivity to any of the backends is lost and
automatic recovery for that backend is enabled, the server disconnects from the
respective backend and then attempts to reconnect. During the recovery process,
the server ceases to serve clients according to the ``on-fail`` configured
option but continues to respond to commands.

The ``on-fail`` parameter configures the actions the server should take when a
connection is lost. It can have one of the following values:

-  ``stop-retry-exit`` - indicates that the server should stop the service
   while it tries to recover the connection, and exit if recovery is not
   successful after ``max-reconnect-tries``.

-  ``serve-retry-exit`` - indicates that the server should not stop the
   service while it tries to recover the connection, and exit if recovery is not
   successful after ``max-reconnect-tries``.

-  ``serve-retry-continue`` - indicates that the server should not stop the
   service while it tries to recover the connection, and not exit if recovery is
   not successful after ``max-reconnect-tries``.

If connectivity to all backends is restored, the server returns to normal
operations. If the connection cannot be restored and the server is configured
to exit, it issues a fatal error before shutdown.

For Kea DHCP servers to work with database backends, the database schema must be
created and must match the version of the Kea
server. If the version check fails and the database backend is not configured
as read-only, Kea attempts to initialize the schema.

.. note::

    Kea does not automatically attempt to upgrade an existing schema; doing so
    might deprive users of the opportunity to take precautions, such as
    backing up the database or temporarily shutting off running
    Kea servers that are currently operating on the database.

The connection to the database server can optionally be protected by TLS.
Corresponding database configuration parameters for Kea servers are:

-  The ``trust-anchor`` specifies the Certification Authority file name or
   directory path.

-  The ``cert-file`` specifies the client certificate file name.

-  The ``key-file`` specifies the private key file name.

-  The ``cipher-list`` specifies the list of TLS ciphers (the syntax of
   the content of this parameter is described in the OpenSSL ciphers
   manual).

These parameters are similar to the parameters of the secure connections
with the agent but are interpreted by different backends using database
configurations too.

Currently the support for each database is:

-  MySQL supports the whole set, additional configuration must be done
   in the MySQL local setup, for instance certificate revocation list,
   choice of a specific TLS version, mutual authentication, etc.
   When a TLS connection was required but the actual connection is in
   clear text an error log is emitted.

-  PostgreSQL only uses the configuration to enable the SSL/TLS support
   in the client library (libpq). Anything else must be done in the
   PostgreSQL local configuration.
