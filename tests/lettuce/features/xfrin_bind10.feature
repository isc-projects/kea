Feature: Xfrin 
    Tests for Xfrin, specific for BIND 10 behaviour.
    
    Scenario: Retransfer command
    # Standard check to test (non-)existence of a file.
    # This file is actually automatically created.
    The file data/test_nonexistent_db.sqlite3 should not exist

    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 47804 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED

    And I have bind10 running with configuration xfrin/retransfer_slave.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    # Now we use the first step again to see if the file has been created
    The file data/test_nonexistent_db.sqlite3 should exist

    A query for www.example.org to [::1]:47806 should have rcode REFUSED
    When I send bind10 the command Xfrin retransfer example.org IN ::1 47807
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_XFRIN_SUCCESS
    A query for www.example.org to [::1]:47806 should have rcode NOERROR

    # The transferred zone should have 11 non-NSEC3 RRs and 1 NSEC3 RR.
    # The following check will get these by AXFR, so the total # of RRs
    # should be 13, counting the duplicated SOA.
    # At this point we can confirm both in and out of AXFR for a zone
    # containing an NSEC3 RR.
    # We don't have to specify the address/port here; the defaults will work.
    When I do an AXFR transfer of example.org
    Then transfer result should have 13 rrs
