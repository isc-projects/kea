Feature: Xfrin 
    Tests for Xfrin, specific for BIND 10 behaviour.
    
    Scenario: Retransfer command
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

    A query for www.example.org should have rcode REFUSED
    Wait for bind10 stderr message CMDCTL_STARTED
    When I send bind10 the command Xfrin retransfer example.org IN ::1 47807
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    A query for www.example.org should have rcode NOERROR
