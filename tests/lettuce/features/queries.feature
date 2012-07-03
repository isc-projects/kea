Feature: Querying feature
    This feature is a collection of non-specific querying tests;
    for instance whether multiple queries in a row return consistent
    answers.

    Scenario: Repeated queries
        Given I have bind10 running with configuration example.org.inmem.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module Stats should not be running
        And bind10 module StatsHttpd should not be running

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

        # Repeat of the above
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

        # And now query something completely different
        A query for nosuchname.example.org should have rcode NXDOMAIN
        The last query response should have flags qr aa rd
        The last query response should have ancount 0
        The last query response should have nscount 1
        The last query response should have adcount 0
        The authority section of the last query response should be
        """
        example.org.            3600    IN      SOA     ns1.example.org. admin.example.org. 1234 3600 1800 2419200 7200
        """

    Scenario: ANY query
        Given I have bind10 running with configuration example.org.inmem.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module Stats should not be running
        And bind10 module StatsHttpd should not be running

        A query for example.org type ANY should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have ancount 4
        The last query response should have nscount 0
        The last query response should have adcount 3
        The answer section of the last query response should be
        """
        example.org.            3600    IN      NS      ns1.example.org.
        example.org.            3600    IN      NS      ns2.example.org.
        example.org.            3600    IN      SOA     ns1.example.org. admin.example.org. 1234 3600 1800 2419200 7200
        example.org.            3600    IN      MX      10 mail.example.org.
        """
        The additional section of the last query response should be
        """
        ns1.example.org.        3600    IN      A       192.0.2.3
        ns2.example.org.        3600    IN      A       192.0.2.4
        mail.example.org.       3600    IN      A       192.0.2.10
        """

    Scenario: Delegation query for unsigned child zone
        Given I have bind10 running with configuration example.org.inmem.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED
        A dnssec query for www.sub.example.org type AAAA should have rcode NOERROR
        The last query response should have flags qr rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 1
        The last query response should have adcount 2
        The authority section of the last query response should be
        """
        sub.example.org.	3600	IN	NS	ns.sub.example.org.
        """
        The additional section of the last query response should be
        """
        ns.sub.example.org.	3600	IN	A	192.0.2.101
        """

    Scenario: SSHFP query
        # We are testing one more RR type for a normal successful case
        Given I have bind10 running with configuration example.org.inmem.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module Stats should not be running
        And bind10 module StatsHttpd should not be running

        A query for example.org type SSHFP should have rcode NOERROR
        The last query response should have ancount 0
        A query for shell.example.org type SSHFP should have rcode NOERROR
        The last query response should have ancount 1
        The answer section of the last query response should be
        """
        shell.example.org.      3600    IN      SSHFP   2 1 123456789abcdef67890123456789abcdef67890
        """
