Feature: DDNS System
    A number of BIND10-specific DDNS tests, that do not fall under the
    'compliance' category; specific ACL checks, module checks, etc.

    Scenario: Module tests
        # The given config has b10-ddns disabled
        Given I have bind10 running with configuration ddns/noddns.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        # Sanity check
        bind10 module DDNS should not be running

        # Test 1
        When I use DDNS to set the SOA serial to 1235
        # Note: test spec says refused here, system returns NOTIMP
        The DDNS response should be NOTIMP
        And the SOA serial for example.org should be 1234

        # Test 2
        When I configure bind10 to run DDNS
        And wait for new bind10 stderr message DDNS_STARTED
        bind10 module DDNS should be running

        # Test 3
        When I use DDNS to set the SOA serial to 1236
        The DDNS response should be REFUSED
        And the SOA serial for example.org should be 1234

        # Test 4
        When I send bind10 the following commands
        """
        config add DDNS/zones
        config set DDNS/zones[0]/origin example.org
        config add DDNS/zones[0]/update_acl {"action": "ACCEPT", "from": "127.0.0.1"}
        config commit
        """

        # Test 5
        When I use DDNS to set the SOA serial to 1237
        # also check if Auth server reloaded
        And wait for new bind10 stderr message AUTH_DATASRC_CLIENTS_BUILDER_LOAD_ZONE
        The DDNS response should be SUCCESS
        And the SOA serial for example.org should be 1237

        # Test 6
        When I send bind10 the command DDNS shutdown
        And wait for new bind10 stderr message DDNS_STOPPED

        # Test 7
        # BoB should restart it
        And wait for new bind10 stderr message DDNS_STARTED

        # Test 8
        When I use DDNS to set the SOA serial to 1238
        And wait for new bind10 stderr message AUTH_DATASRC_CLIENTS_BUILDER_LOAD_ZONE
        The DDNS response should be SUCCESS
        And the SOA serial for example.org should be 1238

        When I use DDNS to set the SOA serial to 1239
        And wait for new bind10 stderr message AUTH_DATASRC_CLIENTS_BUILDER_LOAD_ZONE
        The DDNS response should be SUCCESS
        And the SOA serial for example.org should be 1239

        # Test 9
        When I send bind10 the command Auth shutdown
        And wait for new bind10 stderr message AUTH_SHUTDOWN
        # BoB should restart it automatically
        And wait for new bind10 stderr message AUTH_SERVER_STARTED

        # Test 10
        When I use DDNS to set the SOA serial to 1240
        And wait for new bind10 stderr message AUTH_DATASRC_CLIENTS_BUILDER_LOAD_ZONE
        The DDNS response should be SUCCESS
        And the SOA serial for example.org should be 1240

        # Test 11
        When I configure BIND10 to stop running DDNS
        And wait for new bind10 stderr message DDNS_STOPPED

        bind10 module DDNS should not be running

        # Test 12
        When I use DDNS to set the SOA serial to 1241
        # should this be REFUSED again?
        The DDNS response should be NOTIMP
        And the SOA serial for example.org should be 1240

    Scenario: ACL
        Given I have bind10 running with configuration ddns/ddns.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message AUTH_SERVER_STARTED
        And wait for bind10 stderr message DDNS_STARTED

        # Sanity check
        A query for new1.example.org should have rcode NXDOMAIN
        A query for new2.example.org should have rcode NXDOMAIN
        A query for new3.example.org should have rcode NXDOMAIN
        The SOA serial for example.org should be 1234

        # Test 1
        When I use DDNS to add a record new1.example.org. 3600 IN A 192.0.2.1
        The DDNS response should be SUCCESS
        A query for new1.example.org should have rcode NOERROR
        The SOA serial for example.org should be 1235

        # Test 2
        When I set DDNS ACL 0 for 127.0.0.1 to REJECT
        Then use DDNS to add a record new2.example.org. 3600 IN A 192.0.2.2
        The DDNS response should be REFUSED
        A query for new2.example.org should have rcode NXDOMAIN
        The SOA serial for example.org should be 1235

        # Test 3
        When I set DDNS ACL 0 for 127.0.0.1 to ACCEPT
        Then use DDNS to add a record new3.example.org. 3600 IN A 192.0.2.3
        The DDNS response should be SUCCESS
        A query for new3.example.org should have rcode NOERROR
        The SOA serial for example.org should be 1236

    #Scenario: DDNS and Xfrout
    ## Unfortunately, Xfrout can only notify to inzone slaves, and hence only
    ## to port 53, which we do not want to use for Lettuce tests (for various
    ## reasons). So for now this test is only an outline, the configs
    ## themselves have not been set up yet
    #    When I start bind10 with configuration ddns/primary.config as primary
    #    And wait for primary stderr message AUTH_SERVER_STARTED
    #    And wait for primary stderr message XFROUT_STARTED
    #    And wait for primary stderr message DDNS_STARTED

    #    And I start bind10 with configuration example2.org.config with cmdctl port 47804 as secondary
    #    And wait for secondary stderr message AUTH_SERVER_STARTED
    #    And wait for secondary stderr message XFRIN_STARTED

    #    # Sanity check
    #    The SOA serial for example.org should be 1234
    #    The SOA serial for example.org at 127.0.0.1:47807 should be 1234

    #    When I use DDNS to set the SOA serial to 1235
    #    The DDNS response should be SUCCESS

    #    The SOA serial for example.org should be 1235
    #    The SOA serial for example.org at 127.0.0.1:47807 should be 1235
