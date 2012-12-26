Feature: Querying feature
    This feature is a collection of non-specific querying tests;
    for instance whether multiple queries in a row return consistent
    answers.

    Scenario: Repeated queries
        Given I have bind10 running with configuration example.org.inmem.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED
        And wait for bind10 stderr message STATS_STARTING

        bind10 module Auth should be running
        And bind10 module Stats should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module StatsHttpd should not be running

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_

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

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_ except for the following items
          | item_name     | item_value |
          | request.v4    |          1 |
          | request.udp   |          1 |
          | opcode.query  |          1 |
          | responses     |          1 |
          | qrysuccess    |          1 |
          | qryauthans    |          1 |
          | rcode.noerror |          1 |


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

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_ except for the following items
          | item_name     | item_value |
          | request.v4    |          2 |
          | request.udp   |          2 |
          | opcode.query  |          2 |
          | responses     |          2 |
          | qrysuccess    |          2 |
          | qryauthans    |          2 |
          | rcode.noerror |          2 |

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

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_ except for the following items
          | item_name      | item_value |
          | request.v4     |          3 |
          | request.udp    |          3 |
          | opcode.query   |          3 |
          | responses      |          3 |
          | qrysuccess     |          2 |
          | qryauthans     |          3 |
          | rcode.noerror  |          2 |
          | rcode.nxdomain |          1 |

    Scenario: ANY query
        Given I have bind10 running with configuration example.org.inmem.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Stats should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module StatsHttpd should not be running

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_

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

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_ except for the following items
          | item_name     | item_value |
          | request.v4    |          1 |
          | request.udp   |          1 |
          | opcode.query  |          1 |
          | responses     |          1 |
          | qrysuccess    |          1 |
          | qryauthans    |          1 |
          | rcode.noerror |          1 |

    Scenario: Delegation query for unsigned child zone
        Given I have bind10 running with configuration example.org.inmem.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_

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

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_ except for the following items
          | item_name         | item_value |
          | request.v4        |          1 |
          | request.udp       |          1 |
          | request.edns0     |          1 |
          | request.dnssec_ok |          1 |
          | opcode.query      |          1 |
          | responses         |          1 |
          | response.edns0    |          1 |
          | qrynoauthans      |          1 |
          | qryreferral       |          1 |
          | rcode.noerror     |          1 |

    Scenario: SSHFP query
        # We are testing one more RR type for a normal successful case
        Given I have bind10 running with configuration example.org.inmem.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Stats should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module StatsHttpd should not be running

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_

        A query for example.org type SSHFP should have rcode NOERROR
        The last query response should have ancount 0

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_ except for the following items
          | item_name     | item_value |
          | request.v4    |          1 |
          | request.udp   |          1 |
          | opcode.query  |          1 |
          | responses     |          1 |
          | qryauthans    |          1 |
          | qrynxrrset    |          1 |
          | rcode.noerror |          1 |

        A query for shell.example.org type SSHFP should have rcode NOERROR
        The last query response should have ancount 1
        The answer section of the last query response should be
        """
        shell.example.org.      3600    IN      SSHFP   2 1 123456789abcdef67890123456789abcdef67890
        """

        When I wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
        And wait for new bind10 stderr message AUTH_RECEIVED_COMMAND
        Then I query statistics zones of bind10 module Auth
        And last bindctl output should not contain "error"
        The statistics counters are 0 in category .Auth.zones._SERVER_ except for the following items
          | item_name     | item_value |
          | request.v4    |          2 |
          | request.udp   |          2 |
          | opcode.query  |          2 |
          | responses     |          2 |
          | qrysuccess    |          1 |
          | qryauthans    |          2 |
          | qrynxrrset    |          1 |
          | rcode.noerror |          2 |
