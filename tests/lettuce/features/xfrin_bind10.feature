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



    Scenario: Transfer with TSIG
    # Similar setup to the test above, but this time, we add TSIG configuration

    # In order to check that the tests don't give false positives because config
    # happens to be right (like no TSIG on either side), we take an existing
    # non-TSIG config, add TSIG on the master side, see it fail, add TSIG
    # on the slave side, then check again.

    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 47804 as master
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED

    And I have bind10 running with configuration xfrin/retransfer_slave.conf
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message XFRIN_STARTED

    # Set slave config for 'automatic' xfrin
    When I set bind10 configuration Xfrin/zones to [{"master_port": 47806, "name": "example.org", "master_addr": "::1"}]

    # Make sure it is fully open
    When I send bind10 the command Xfrin retransfer example.org
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    And wait for new bind10 stderr message ZONEMGR_RECEIVE_XFRIN_SUCCESS

    # First to master, a transfer should then fail
    When I send bind10 the following commands with cmdctl port 47804:
    """
    config add tsig_keys/keys "example.key.:c2VjcmV0"
    config set Xfrout/zone_config[0]/transfer_acl [{"action": "ACCEPT", "from": "::1", "key": "example.key."}]
    config commit
    """

    # Transfer should fail
    When I send bind10 the command Xfrin retransfer example.org
    Then wait for new bind10 stderr message XFRIN_XFR_TRANSFER_PROTOCOL_ERROR not XFRIN_TRANSFER_SUCCESS
    # Set client to use TSIG as well
    When I send bind10 the following commands:
    """
    config add tsig_keys/keys "example.key.:c2VjcmV0"
    config set Xfrin/zones[0]/tsig_key  "example.key.:c2VjcmV0"
    config commit
    """

    # Transwer should succeed now
    When I send bind10 the command Xfrin retransfer example.org
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
