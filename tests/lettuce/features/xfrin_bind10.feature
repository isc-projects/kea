Feature: Xfrin
    Tests for Xfrin, specific for BIND 10 behaviour.

    Scenario: Retransfer command
    # Standard check to test (non-)existence of a file.
    # This file is actually automatically created.
    The file data/test_nonexistent_db.sqlite3 should not exist

    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 56174 as master
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

    # Now we use the first step again to see if the file has been created.
    # The DB currently doesn't know anything about the zone, so we install
    # an empty zone for xfrin.
    The file data/test_nonexistent_db.sqlite3 should exist
    A query for www.example.org to [::1]:56176 should have rcode REFUSED
    Then make empty zone example.org in DB file data/test_nonexistent_db.sqlite3

    When I send bind10 the command Xfrin retransfer example.org IN ::1 56177
    # The data we receive contain a NS RRset that refers to three names in the
    # example.org. zone. All these three are nonexistent in the data, producing
    # 3 separate warning messages in the log.
    And wait for new bind10 stderr message XFRIN_ZONE_WARN
    And wait for new bind10 stderr message XFRIN_ZONE_WARN
    And wait for new bind10 stderr message XFRIN_ZONE_WARN
    # But after complaining, the zone data should be accepted.
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    # there's no guarantee this is logged before XFRIN_TRANSFER_SUCCESS, so
    # we can't reliably use 'wait for new'.  In this case this should be the
    # only occurrence of this message, so this should be okay.
    Then wait for bind10 stderr message ZONEMGR_RECEIVE_XFRIN_SUCCESS
    A query for www.example.org to [::1]:56176 should have rcode NOERROR

    # The transferred zone should have 11 non-NSEC3 RRs and 1 NSEC3 RR.
    # The following check will get these by AXFR, so the total # of RRs
    # should be 13, counting the duplicated SOA.
    # At this point we can confirm both in and out of AXFR for a zone
    # containing an NSEC3 RR.
    # We don't have to specify the address/port here; the defaults will work.
    When I do an AXFR transfer of example.org
    Then transfer result should have 13 rrs

    # Now try to offer another update. However, the validation of
    # data should fail. The old version shoud still be available.
    When I send bind10 the following commands with cmdctl port 56174:
    """
    config set data_sources/classes/IN[0]/params/database_file data/example.org-nons.sqlite3
    config set Auth/database_file data/example.org-nons.sqlite3
    config commit
    """
    Then I send bind10 the command Xfrin retransfer example.org IN ::1 56177
    And wait for new bind10 stderr message XFRIN_ZONE_INVALID
    And wait for new bind10 stderr message XFRIN_INVALID_ZONE_DATA
    # We can't use 'wait for new' here; see above.
    Then wait for bind10 stderr message ZONEMGR_RECEIVE_XFRIN_FAILED
    A query for example.org type NS to [::1]:56176 should have rcode NOERROR
    And transfer result should have 13 rrs

    Scenario: Transfer with TSIG
    # Similar setup to the test above, but this time, we add TSIG configuration

    # In order to check that the tests don't give false positives because config
    # happens to be right (like no TSIG on either side), we take an existing
    # non-TSIG config, add TSIG on the master side, see it fail, add TSIG
    # on the slave side, then check again.

    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 56174 as master
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED

    And I have bind10 running with configuration xfrin/retransfer_slave.conf
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message XFRIN_STARTED

    # For xfrin make the data source aware of the zone (with empty data)
    Then make empty zone example.org in DB file data/test_nonexistent_db.sqlite3

    # Set slave config for 'automatic' xfrin
    When I set bind10 configuration Xfrin/zones to [{"master_port": 56176, "name": "example.org", "master_addr": "::1"}]

    # Make sure it is fully open
    When I send bind10 the command Xfrin retransfer example.org
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    # this can't be 'wait for new'; see above.
    And wait for bind10 stderr message ZONEMGR_RECEIVE_XFRIN_SUCCESS

    # First to master, a transfer should then fail
    When I send bind10 the following commands with cmdctl port 56174:
    """
    config add tsig_keys/keys "example.key.:c2VjcmV0"
    config set Xfrout/zone_config[0]/transfer_acl [{"action": "ACCEPT", "from": "::1", "key": "example.key."}]
    config commit
    """

    # Transfer should fail
    When I send bind10 the command Xfrin retransfer example.org
    Then wait for new bind10 stderr message XFRIN_XFR_TRANSFER_PROTOCOL_VIOLATION not XFRIN_TRANSFER_SUCCESS
    # Set client to use TSIG as well
    When I send bind10 the following commands:
    """
    config add tsig_keys/keys "example.key.:c2VjcmV0"
    config set Xfrin/zones[0]/tsig_key  "example.key."
    config commit
    """

    # Transwer should succeed now
    When I send bind10 the command Xfrin retransfer example.org
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE

    Scenario: Validation fails
    # In this test, the source data of the XFR is invalid (missing NS record
    # at the origin). We check it is rejected after the transfer.
    #
    # We use abuse the fact that we do not check data when we read it from
    # the sqlite3 database (unless we load into in-memory, which we don't
    # do here).
    The file data/test_nonexistent_db.sqlite3 should not exist

    Given I have bind10 running with configuration xfrin/retransfer_master_nons.conf with cmdctl port 56174 as master
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

    # Now we use the first step again to see if the file has been created,
    # then install empty zone data
    The file data/test_nonexistent_db.sqlite3 should exist
    A query for www.example.org to [::1]:56176 should have rcode REFUSED
    Then make empty zone example.org in DB file data/test_nonexistent_db.sqlite3

    When I send bind10 the command Xfrin retransfer example.org IN ::1 56177
    # It should complain once about invalid data, then again that the whole
    # zone is invalid and then reject it.
    And wait for new bind10 stderr message XFRIN_ZONE_INVALID
    And wait for new bind10 stderr message XFRIN_INVALID_ZONE_DATA
    # This can't be 'wait for new'
    Then wait for bind10 stderr message ZONEMGR_RECEIVE_XFRIN_FAILED
    # The zone still doesn't exist as it is rejected.
    # FIXME: This step fails. Probably an empty zone is created in the data
    # source :-|. This should be REFUSED, not SERVFAIL.
    A query for www.example.org to [::1]:56176 should have rcode SERVFAIL

    # TODO:
    # * IXFR - generate an sqlite db that contains the journal. Check it was
    #   IXFR by logs.
    # * IXFR->AXFR fallback if IXFR is not available (even rejected or
    #   something, not just the differences missing).
    # * Retransfer with short refresh time (without notify).
    Scenario: With differences
    # We transfer from one bind10 to other, just like in the Retransfer command
    # scenario. Just this time, the master contains the differences table
    # and the slave has a previous version of the zone, so we use the IXFR.

    Given I have bind10 running with configuration xfrin/retransfer_master_diffs.conf with cmdctl port 56174 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED

    And I have bind10 running with configuration xfrin/retransfer_slave_diffs.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    A query for example. type SOA to [::1]:56176 should have rcode NOERROR
    The answer section of the last query response should be
    """
    example.    3600    IN      SOA     ns1.example. hostmaster.example. 94 3600 900 7200 300
    """

    # To invoke IXFR we need to use refresh command
    When I send bind10 the command Xfrin refresh example. IN ::1 56177
    Then wait for new bind10 stderr message XFRIN_GOT_INCREMENTAL_RESP
    Then wait for new bind10 stderr message XFRIN_IXFR_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    # This can't be 'wait for new'
    Then wait for bind10 stderr message ZONEMGR_RECEIVE_XFRIN_SUCCESS

    A query for example. type SOA to [::1]:56176 should have rcode NOERROR
    The answer section of the last query response should be
    """
    example.    3600    IN      SOA     ns1.example. hostmaster.example. 100 3600 900 7200 300
    """
