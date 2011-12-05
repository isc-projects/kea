Feature: IXFR out
    Tests for IXFR-out, specific for BIND 10 behaviour.
    These are (part of) the tests as described on
    http://bind10.isc.org/wiki/IxfrSystemTests

    Scenario: Test Set 1
        Given I have bind10 running with configuration ixfr-out/testset1-config.db
        The SOA serial for example.com should be 22
        
        # A lot of these tests test specific UDP behaviour.
        # Since we do not support that at this time, these are commented out
        # Once we implement it, we can uncomment them. The tests themselves
        # should already work

        #
        # Test 1
        #
        # UDP support isn't added yet, so this would fail
        #When I do an IXFR transfer of example.com 123 over udp
        #The transfer result should have 1 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 2
        #
        #When I do an IXFR transfer of example.com 123 over udp
        #The transfer result should have 1 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 3
        #
        #When I do an IXFR transfer of example.com 20 over udp
        When I do an IXFR transfer of example.com 20 over tcp
        The transfer result should have 5 RRs
        The full result of the last transfer should be
        """
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 20 28800 7200 604800 18000
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        www.example.com. 3600 IN A 192.0.2.1
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        """

        #
        # Test 4
        #
        When I do an IXFR transfer of example.com 18 over tcp
        The transfer result should have 8 RRs
        The full result of the last transfer should be
        """
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 18 28800 7200 604800 18000
        www.example.com. 3600 IN A 192.0.2.1
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 20 28800 7200 604800 18000
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 20 28800 7200 604800 18000
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        www.example.com. 3600 IN A 192.0.2.1
        example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        """

        #
        # Test 5
        #
        #When I do an IXFR transfer of example.com 2 over udp
        #The transfer result should have 1 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 6
        #
        #When I do an IXFR transfer of example.com 5 over udp
        #The transfer result should have 1 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 7
        #
        When I do an IXFR transfer of example.com 14 over tcp
        The transfer result should have 14 RRs
        The full result of the last transfer should be
        """
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 14 28800 7200 604800 18000
        www.example.com.        3600    IN      A       192.0.2.1
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 16 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 16 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 18 28800 7200 604800 18000
        www.example.com.        3600    IN      A       192.0.2.1
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 18 28800 7200 604800 18000
        www.example.com.        3600    IN      A       192.0.2.1
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 20 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 20 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        www.example.com.        3600    IN      A       192.0.2.1
        example.com.            3600    IN      SOA     ns.example.com. jelte.example.com. 22 28800 7200 604800 18000
        """
