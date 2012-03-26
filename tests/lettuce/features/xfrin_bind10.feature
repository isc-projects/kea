Feature: Xfrin 
    Tests for Xfrin, specific for BIND 10 behaviour.
    
    Scenario: Retransfer command
    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 47804 as master
    And I have bind10 running with configuration xfrin/retransfer_slave.conf
    A query for www.example.org should have rcode REFUSED
    Wait for bind10 stderr message CMDCTL_STARTED
    When I send bind10 the command Xfrin retransfer example.org IN ::1 47807
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    A query for www.example.org should have rcode NOERROR
