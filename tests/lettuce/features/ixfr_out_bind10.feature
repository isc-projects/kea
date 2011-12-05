Feature: IXFR out
    Tests for IXFR-out, specific for BIND 10 behaviour.
    These are (part of) the tests as described on
    http://bind10.isc.org/wiki/IxfrSystemTests

    # A lot of these tests test specific UDP behaviour.
    #
    # Since we do not support that at this time, these are commented out
    # Once we implement it, we can uncomment them. The tests themselves
    # should already work.
    #
    # Some of the tests (scenario 1 tests 3 and 4, and scenario 2 tests 1 and
    # 2 may still not work if we replicate BIND 9's behaviour; it always
    # responds to UDP IXFR requests with just the SOA, and it does not do
    # AXFR-style IXFR if the number of changes exceeds the size of the zone)
    #
    # So in effect, there is only one test that is currently active (scenario
    # 1 test 7)

    Scenario: Test Set 1
        Given I have bind10 running with configuration ixfr-out/testset1-config.db
        The SOA serial for example.com should be 22

        # These tests use a zone with just a few records, the first serial
        # is 2, and it is incremented in steps of 2, up to serial 22.
        # Each updates either deletes or adds the www.example.com A record.
        
        #
        # Test 1
        #
        #When I do an IXFR transfer of example.com 123 over udp
        #The transfer result should have 1 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 2
        #
        #When I do an IXFR transfer of example.com 123 over udp
        #The transfer result should have 1 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 3
        #
        #When I do an IXFR transfer of example.com 20 over udp
        #The transfer result should have 5 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 20 28800 7200 604800 18000
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #www.example.com. 3600 IN A 192.0.2.1
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 4
        #
        #When I do an IXFR transfer of example.com 18 over udp
        #The transfer result should have 8 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 18 28800 7200 604800 18000
        #www.example.com. 3600 IN A 192.0.2.1
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 20 28800 7200 604800 18000
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 20 28800 7200 604800 18000
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #www.example.com. 3600 IN A 192.0.2.1
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 5
        #
        #When I do an IXFR transfer of example.com 2 over udp
        #The transfer result should have 1 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 6
        #
        #When I do an IXFR transfer of example.com 5 over udp
        #The transfer result should have 1 RRs
        #The full result of the last transfer should be
        #"""
        #example.com. 3600 IN SOA ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 7
        #
        When I do an IXFR transfer of example.com 14 over tcp
        The transfer result should have 14 RRs
        The full result of the last transfer should be
        """
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 14 28800 7200 604800 18000
        www.example.com.        3600    IN      A       192.0.2.1
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 16 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 16 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 18 28800 7200 604800 18000
        www.example.com.        3600    IN      A       192.0.2.1
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 18 28800 7200 604800 18000
        www.example.com.        3600    IN      A       192.0.2.1
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 20 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 20 28800 7200 604800 18000
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        www.example.com.        3600    IN      A       192.0.2.1
        example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        """

    Scenario: Test Set 2
        Given I have bind10 running with configuration ixfr-out/testset1-config.db
        The SOA serial for example.com should be 22

        #
        # Test 1
        #
        #When I do an IXFR transfer of example.com 19 over udp
        #The transfer result should have 5 RRs
        #The full result of the last transfer should be
        #"""
        #example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #example.com.            3600    IN      NS      ns.example.com.
        #ns.example.com.         3600    IN      A       192.0.2.1
        #www.example.com.        3600    IN      A       192.0.2.1
        #example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 2
        #
        #When I do an IXFR transfer of example.com 6 over udp
        #The transfer result should have 5 RRs
        #The full result of the last transfer should be
        #"""
        #example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #example.com.            3600    IN      NS      ns.example.com.
        #ns.example.com.         3600    IN      A       192.0.2.1
        #www.example.com.        3600    IN      A       192.0.2.1
        #example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #"""

        #
        # Test 3
        #
        #When I do an IXFR transfer of example.com 19 over udp
        #The transfer result should have 1 RRs
        #The full result of the last transfer should be
        #"""
        #example.com.            3600    IN      SOA     ns.example.com. admin.example.com. 22 28800 7200 604800 18000
        #"""
