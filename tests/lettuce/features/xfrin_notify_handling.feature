Feature: Xfrin incoming notify handling
    Tests for Xfrin incoming notify handling.

    Scenario: Handle incoming notify
    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 47804 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED
    And wait for master stderr message STATS_STARTING

    And I have bind10 running with configuration xfrin/retransfer_slave_notify.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    A query for www.example.org to [::1]:47806 should have rcode NXDOMAIN

    #
    # Test for statistics
    #
    # check for initial statistics
    #
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    last bindctl output should not contain "error"
    last bindctl output should not contain "example.org."
    Then the statistics counter notifyoutv4 for the zone _SERVER_ should be 0
    Then the statistics counter notifyoutv6 for the zone _SERVER_ should be 0
    Then the statistics counter xfrrej for the zone _SERVER_ should be 0
    Then the statistics counter xfrreqdone for the zone _SERVER_ should be 0

    When I query statistics ixfr_running of bind10 module Xfrout with cmdctl port 47804
    Then the statistics counter ixfr_running should be 0

    When I query statistics axfr_running of bind10 module Xfrout with cmdctl port 47804
    Then the statistics counter axfr_running should be 0

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    Then the statistics counter open should be between 0 and 1
    Then the statistics counter openfail should be 0
    Then the statistics counter close should be 0
    Then the statistics counter bindfail should be 0
    Then the statistics counter acceptfail should be 0
    Then the statistics counter accept should be 0
    Then the statistics counter senderr should be 0
    Then the statistics counter recverr should be 0

    When I send bind10 with cmdctl port 47804 the command Xfrout notify example.org IN
    Then wait for new master stderr message XFROUT_NOTIFY_COMMAND
    Then wait for new bind10 stderr message AUTH_RECEIVED_NOTIFY
    # From this point we can't reliably 'wait for new' because the ordering
    # of logs from different processes is unpredictable.  But these
    # should be okay in this case.
    Then wait for bind10 stderr message ZONEMGR_RECEIVE_NOTIFY
    Then wait for bind10 stderr message XFRIN_XFR_TRANSFER_STARTED
    Then wait for bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    Then wait for bind10 stderr message ZONEMGR_RECEIVE_XFRIN_SUCCESS
    Then wait for master stderr message NOTIFY_OUT_REPLY_RECEIVED

    A query for www.example.org to [::1]:47806 should have rcode NOERROR
    # Make sure handling statistics command handling checked below is
    # after this query
    And wait for bind10 stderr message AUTH_SEND_NORMAL_RESPONSE

    #
    # Test for statistics
    #
    # check for statistics change
    #

    # wait until the last stats requesting is finished
    # note that this does not 100% guarantee the stats updated Xfrout
    # statistics.  But there doesn't seem to be a better log message that
    # suggests this event.
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    last bindctl output should not contain "error"
    Then the statistics counter notifyoutv4 for the zone _SERVER_ should be 0
    Then the statistics counter notifyoutv4 for the zone example.org. should be 0
    Then the statistics counter notifyoutv6 for the zone _SERVER_ should be 1
    Then the statistics counter notifyoutv6 for the zone example.org. should be 1
    Then the statistics counter xfrrej for the zone _SERVER_ should be 0
    Then the statistics counter xfrrej for the zone example.org. should be 0
    Then the statistics counter xfrreqdone for the zone _SERVER_ should be 1
    Then the statistics counter xfrreqdone for the zone example.org. should be 1

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    Then the statistics counter open should be 1
    Then the statistics counter openfail should be 0
    Then the statistics counter close should be 0
    Then the statistics counter bindfail should be 0
    Then the statistics counter acceptfail should be 0
    Then the statistics counter accept should be 1
    Then the statistics counter senderr should be 0
    Then the statistics counter recverr should be 0

    #
    # Test for Xfr request rejected
    #
    Scenario: Handle incoming notify (XFR request rejected)
    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 47804 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED
    And wait for master stderr message STATS_STARTING

    And I have bind10 running with configuration xfrin/retransfer_slave_notify.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    A query for www.example.org to [::1]:47806 should have rcode NXDOMAIN

    #
    # Test1 for statistics
    #
    # check for initial statistics
    #
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    last bindctl output should not contain "error"
    last bindctl output should not contain "example.org."
    Then the statistics counter notifyoutv4 for the zone _SERVER_ should be 0
    Then the statistics counter notifyoutv6 for the zone _SERVER_ should be 0
    Then the statistics counter xfrrej for the zone _SERVER_ should be 0
    Then the statistics counter xfrreqdone for the zone _SERVER_ should be 0

    When I query statistics ixfr_running of bind10 module Xfrout with cmdctl port 47804
    Then the statistics counter ixfr_running should be 0

    When I query statistics axfr_running of bind10 module Xfrout with cmdctl port 47804
    Then the statistics counter axfr_running should be 0

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    Then the statistics counter open should be between 0 and 1
    Then the statistics counter openfail should be 0
    Then the statistics counter close should be 0
    Then the statistics counter bindfail should be 0
    Then the statistics counter acceptfail should be 0
    Then the statistics counter accept should be 0
    Then the statistics counter senderr should be 0
    Then the statistics counter recverr should be 0

    #
    # set transfer_acl rejection
    # Local xfr requests from Xfrin module would be rejected here.
    #
    When I send bind10 the following commands with cmdctl port 47804
    """
    config set Xfrout/zone_config[0]/transfer_acl [{"action":  "REJECT", "from": "::1"}]
    config commit
    """
    last bindctl output should not contain Error

    When I send bind10 with cmdctl port 47804 the command Xfrout notify example.org IN
    Then wait for new master stderr message XFROUT_NOTIFY_COMMAND
    Then wait for new bind10 stderr message AUTH_RECEIVED_NOTIFY
    # can't use 'wait for new' below.
    Then wait for bind10 stderr message ZONEMGR_RECEIVE_NOTIFY
    Then wait for bind10 stderr message XFRIN_XFR_TRANSFER_STARTED
    Then wait for bind10 stderr message XFRIN_XFR_TRANSFER_PROTOCOL_VIOLATION not XFRIN_TRANSFER_SUCCESS
    Then wait for bind10 stderr message ZONEMGR_RECEIVE_XFRIN_FAILED not ZONEMGR_RECEIVE_XFRIN_SUCCESS
    Then wait for master stderr message NOTIFY_OUT_REPLY_RECEIVED

    A query for www.example.org to [::1]:47806 should have rcode NXDOMAIN

    #
    # Test2 for statistics
    #
    # check for statistics change
    #

    # wait until stats request at least after NOTIFY_OUT_REPLY_RECEIVED
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    last bindctl output should not contain "error"
    Then the statistics counter notifyoutv4 for the zone _SERVER_ should be 0
    Then the statistics counter notifyoutv4 for the zone example.org. should be 0
    Then the statistics counter notifyoutv6 for the zone _SERVER_ should be 1
    Then the statistics counter notifyoutv6 for the zone example.org. should be 1
    # The counts of rejection would be between 1 and 2. They are not
    # fixed. It would depend on timing or the platform.
    Then the statistics counter xfrrej for the zone _SERVER_ should be greater than 0
    Then the statistics counter xfrrej for the zone example.org. should be greater than 0
    Then the statistics counter xfrreqdone for the zone _SERVER_ should be 0
    Then the statistics counter xfrreqdone for the zone example.org. should be 0

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    Then the statistics counter open should be 1
    Then the statistics counter openfail should be 0
    Then the statistics counter close should be 0
    Then the statistics counter bindfail should be 0
    Then the statistics counter acceptfail should be 0
    Then the statistics counter accept should be 1
    Then the statistics counter senderr should be 0
    Then the statistics counter recverr should be 0

    #
    # Test for unreachable slave
    #
    Scenario: Handle incoming notify (unreachable slave)
    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 47804 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED
    And wait for master stderr message STATS_STARTING

    When I send bind10 with cmdctl port 47804 the command Xfrout notify example.org IN
    Then wait for new master stderr message XFROUT_NOTIFY_COMMAND
    Then wait for new master stderr message NOTIFY_OUT_SENDING_NOTIFY
    Then wait for new master stderr message NOTIFY_OUT_TIMEOUT

    #
    # Test1 for Xfrout statistics
    #
    # check statistics change
    #

    # wait until stats request at least after NOTIFY_OUT_TIMEOUT
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    last bindctl output should not contain "error"
    Then the statistics counter notifyoutv4 for the zone _SERVER_ should be 0
    Then the statistics counter notifyoutv4 for the zone example.org. should be 0
    Then the statistics counter notifyoutv6 for the zone _SERVER_ should be greater than 0
    Then the statistics counter notifyoutv6 for the zone example.org. should be greater than 0
    Then the statistics counter xfrrej for the zone _SERVER_ should be 0
    Then the statistics counter xfrrej for the zone example.org. should be 0
    Then the statistics counter xfrreqdone for the zone _SERVER_ should be 0
    Then the statistics counter xfrreqdone for the zone example.org. should be 0

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    Then the statistics counter open should be 1
    Then the statistics counter openfail should be 0
    Then the statistics counter close should be 0
    Then the statistics counter bindfail should be 0
    Then the statistics counter acceptfail should be 0
    Then the statistics counter accept should be 0
    Then the statistics counter senderr should be 0
    Then the statistics counter recverr should be 0

    #
    # Test for NOTIFY that would result in NOTAUTH
    #
    Scenario: Handle incoming notify that does match authoritative zones
    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 47804 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED
    And wait for master stderr message STATS_STARTING

    And I have bind10 running with configuration xfrin/retransfer_slave_notify.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    #
    # replace master's data source with unmatched zone for slave's zone.
    # we restart Xfrout to make it sure.
    #
    When I send bind10 the following commands with cmdctl port 47804
    """
    config set data_sources/classes/IN[0]/params/database_file data/ixfr-out/zones.sqlite3
    config set Auth/database_file data/ixfr-out/zones.sqlite3
    config set Xfrout/zone_config[0]/origin example.com
    config commit
    Xfrout shutdown
    """
    last bindctl output should not contain "error"
    And wait for new master stderr message XFROUT_STARTED

    A query for www.example.com to [::1]:47806 should have rcode REFUSED

    When I send bind10 with cmdctl port 47804 the command Xfrout notify example.com IN
    Then wait for new master stderr message XFROUT_NOTIFY_COMMAND
    Then wait for new bind10 stderr message AUTH_RECEIVED_NOTIFY_NOTAUTH
    Then wait for new master stderr message NOTIFY_OUT_REPLY_RECEIVED

    A query for www.example.com to [::1]:47806 should have rcode REFUSED

    #
    # Test for NOTIFY that's not in the secondaries list
    #
    Scenario: Handle incoming notify that is not in the secondaries list
    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 47804 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED
    And wait for master stderr message STATS_STARTING

    And I have bind10 running with configuration xfrin/retransfer_slave_notify.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    #
    # Empty slave's secondaries list, and restart zonemgr to make it sure
    #
    When I send bind10 the following commands with cmdctl
    """
    config remove Zonemgr/secondary_zones[0]
    config commit
    Zonemgr shutdown
    """
    last bindctl output should not contain "error"
    And wait for new bind10 stderr message ZONEMGR_STARTED

    A query for www.example.org to [::1]:47806 should have rcode NXDOMAIN

    When I send bind10 with cmdctl port 47804 the command Xfrout notify example.org IN
    Then wait for new master stderr message XFROUT_NOTIFY_COMMAND
    Then wait for new bind10 stderr message AUTH_RECEIVED_NOTIFY
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_NOTIFY
    Then wait for new bind10 stderr message ZONEMGR_ZONE_NOTIFY_NOT_SECONDARY
    Then wait for new master stderr message NOTIFY_OUT_REPLY_RECEIVED

    A query for www.example.org to [::1]:47806 should have rcode NXDOMAIN

    #
    # Test for NOTIFY when zonemgr is not running
    #
    Scenario: Handle incoming notify while zonemgr is not running
    Given I have bind10 running with configuration xfrin/retransfer_master.conf with cmdctl port 47804 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED
    And wait for master stderr message STATS_STARTING

    And I have bind10 running with configuration xfrin/retransfer_slave_notify.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    # remove zonemgr from the system.  a subsequent notify is ignored, but
    # an error message shouldn't be logged at auth.
    When I send bind10 the following commands with cmdctl
    """
    config remove Init/components b10-zonemgr
    config commit
    """
    last bindctl output should not contain "error"
    And wait for new bind10 stderr message BIND10_PROCESS_ENDED

    A query for www.example.org to [::1]:47806 should have rcode NXDOMAIN

    When I send bind10 with cmdctl port 47804 the command Xfrout notify example.org IN
    Then wait for master stderr message XFROUT_NOTIFY_COMMAND
    Then wait for new bind10 stderr message AUTH_RECEIVED_NOTIFY
    Then wait for new bind10 stderr message AUTH_ZONEMGR_NOTEXIST not AUTH_ZONEMGR_ERROR
    Then wait for master stderr message NOTIFY_OUT_TIMEOUT not NOTIFY_OUT_REPLY_RECEIVED

    A query for www.example.org to [::1]:47806 should have rcode NXDOMAIN
