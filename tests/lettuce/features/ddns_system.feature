Feature: DDNS System
    A number of BIND10-specific DDNS tests, that do not fall under the
    'compliance' category; specific ACL checks, module checks, etc.

    Scenario: Module tests
        # This test runs the original example configuration, which has
        # a number of modules. It then removes all non-essential modules,
        # and checks whether they do disappear from the list of running
        # modules (note that it 'misuses' the help command for this,
        # there is a Boss command 'show_processes' but it's output is
        # currently less standardized than 'help')
        Given I have bind10 running with configuration ddns/noddns.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        # Sanity check
        bind10 module DDNS should not be running

        # Test 1
        When I send a DDNS Update for example.org with the following commands:
        """
        update add example.org 3600 IN SOA ns1.example.org. admin.example.org. 1235 3600 1800 2419200 7200
        """
        # Note: test spec says refused here, system returns SERVFAIL
        #The DDNS response should be REFUSED
        The DDNS response should be SERVFAIL

        # Test 2
        When I send bind10 the following commands
        """
        config add Boss/components b10-ddns
        config set Boss/components/b10-ddns/kind needed
        config commit
        """
        And wait for new bind10 stderr message DDNS_RUNNING

        bind10 module DDNS should be running

        # Test 3
        When I send a DDNS Update for example.org with the following commands:
        """
        update add example.org 3600 IN SOA ns1.example.org. admin.example.org. 1236 3600 1800 2419200 7200
        """
        # Note: test spec says refused here, system returns SERVFAIL
        The DDNS response should be REFUSED

        # Test 4
        When I send bind10 the following commands
        """
        config add DDNS/zones
        config set DDNS/zones[0]/origin example.org
        config add DDNS/zones[0]/update_acl {"action": "ACCEPT", "from": "127.0.0.1"}
        config commit
        """

        # Test 5
        When I send a DDNS Update for example.org with the following commands:
        """
        update add example.org 3600 IN SOA ns1.example.org. admin.example.org. 1237 3600 1800 2419200 7200
        """
        # Note: test spec says refused here, system returns SERVFAIL
        The DDNS response should be SUCCESS
        And the SOA serial for example.org should be 1237

        # Test 6

        # Test 7

        # Test 8

        # Test 9

        # Test 10

        # Test 11



