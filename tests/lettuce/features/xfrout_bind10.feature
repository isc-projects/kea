Feature: Xfrout
    Tests for Xfrout, specific for BIND 10 behaviour.

    Scenario: normal transfer with a moderate number of RRs

    Load 100 records for zone example.org to DB file data/xfrout.sqlite3

    Given I have bind10 running with configuration xfrout_master.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFROUT_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    # The transferred zone should have the generated 100 RRs plush one
    # trailing SOA.
    When I do a customized AXFR transfer of example.org
    Then transfer result should have 101 rrs

    # Similar to the previous one, but using a much larger zone, and with
    # a small delay at the client side.  It should still succeed.
    # The specific delay (5 seconds) was chosen for an environment that
    # revealed a bug which is now fixed to reproduce the issue; shorter delays
    # didn't trigger the problem.  Depending on the OS implementation, machine
    # speed, etc, the same delay may be too long or too short, but in any case
    # the test should succeed now.
    Scenario: transfer a large zone

    Load 50000 records for zone example.org to DB file data/xfrout.sqlite3

    Given I have bind10 running with configuration xfrout_master.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFROUT_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    When I do a customized AXFR transfer of example.org from [::1]:56176 with pause of 5 seconds
    Then transfer result should have 50001 rrs
