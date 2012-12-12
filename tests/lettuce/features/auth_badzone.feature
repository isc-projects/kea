Feature: Authoritative DNS server with a bad zone
    This feature set is for testing the execution of the b10-auth
    component when one zone is broken, whereas others are fine. In this
    case, b10-auth should not reject the data source, but reject the bad
    zone only and serve the good zones anyway.

    Scenario: Bad zone
        Given I have bind10 running with configuration auth/auth_badzone.config

        # loading example.com, example.net and example.info zones fail.
        # Note: wait for these messages right away as otherwise they
        # will be logged and we cannot use the 'new' keyword to wait for
        # 3 different log messages. *There could still be a race here if
        # auth starts very quickly.*
        And wait for new bind10 stderr message DATASRC_LOAD_FROM_FILE_ERROR
        And wait for new bind10 stderr message DATASRC_LOAD_FROM_FILE_ERROR
        And wait for new bind10 stderr message DATASRC_LOAD_FROM_FILE_ERROR

        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Resolver should not be running

        A query for www.example.org should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have ancount 1
        The last query response should have nscount 2
        The last query response should have adcount 2

        The answer section of the last query response should be
        """
        www.example.org.        3600    IN      A       192.0.2.1
        """
        The authority section of the last query response should be
        """
        example.org.            3600    IN      NS      ns1.example.org.
        example.org.            3600    IN      NS      ns2.example.org.
        """
        The additional section of the last query response should be
        """
        ns1.example.org.        3600    IN      A       192.0.2.3
        ns2.example.org.        3600    IN      A       192.0.2.4
        """

        A query for www.example.com should have rcode REFUSED
        A query for www.example.net should have rcode REFUSED
        A query for www.example.info should have rcode REFUSED
