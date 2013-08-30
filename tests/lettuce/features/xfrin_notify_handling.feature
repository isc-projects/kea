Feature: Xfrin incoming notify handling
    Tests for Xfrin incoming notify handling. They also test
    statistics counters incremented, which are related to notifying
    and transferring by Xfrout and receiveing by Xfrin. Some cases are
    considered: Transferring is done via IPv4 or IPv6 transport. A
    transfer request from Xfrin is rejected by Xfrout. The master
    server or slave server is unreachable.

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
    # Test1 for Xfrout statistics
    #
    check initial statistics not containing example.org for Xfrout with cmdctl port 47804 except for the following items
      | item_name                | min_value | max_value |
      | socket.unixdomain.open   |         0 |         1 |
    # Note: .Xfrout.socket.unixdomain.open can be either expected to
    # be 0 or 1 here.  The reason is: if b10-xfrout has started up and is
    # ready for a request from b10-stats, then b10-stats does request
    # to b10-xfrout and the value results in 1. Otherwise if
    # b10-xfrout is starting and isn't yet ready, then b10-stats
    # doesn't request to b10-xfrout and the value still remains to be the
    # default value(0).

    #
    # Test2 for Xfrin statistics
    #
    check initial statistics not containing example.org for Xfrin

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
    # Test3 for Xfrout statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    # note that this does not 100% guarantee the stats updated Xfrout
    # statistics.  But there doesn't seem to be a better log message that
    # suggests this event.
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones.IN except for the following items
      | item_name                | item_value |
      | _SERVER_.notifyoutv6     |          1 |
      | _SERVER_.xfrreqdone      |          1 |
      | example.org..notifyoutv6 |          1 |
      | example.org..xfrreqdone  |          1 |

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | item_value |
      | open      |          1 |
      | accept    |          1 |

    #
    # Test4 for Xfrin statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrin with cmdctl
    wait for new bind10 stderr message XFRIN_RECEIVED_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrin with cmdctl
    The statistics counters are 0 in category .Xfrin.zones.IN except for the following items
      | item_name                       | item_value | min_value |
      | _SERVER_.soaoutv6               |          1 |           |
      | _SERVER_.axfrreqv6              |          1 |           |
      | _SERVER_.xfrsuccess             |          1 |           |
      | _SERVER_.last_axfr_duration     |            |       0.0 |
      | example.org..soaoutv6           |          1 |           |
      | example.org..axfrreqv6          |          1 |           |
      | example.org..xfrsuccess         |          1 |           |
      | example.org..last_axfr_duration |            |       0.0 |

    #
    # Test for handling incoming notify only in IPv4
    #
    Scenario: Handle incoming notify (IPv4)
    Given I have bind10 running with configuration xfrin/retransfer_master_v4.conf with cmdctl port 47804 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED
    And wait for master stderr message STATS_STARTING

    And I have bind10 running with configuration xfrin/retransfer_slave_notify_v4.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    A query for www.example.org to 127.0.0.1:47806 should have rcode NXDOMAIN

    #
    # Test1 for Xfrout statistics
    #
    check initial statistics not containing example.org for Xfrout with cmdctl port 47804 except for the following items
      | item_name                | min_value | max_value |
      | socket.unixdomain.open   |         0 |         1 |
    # Note: See above about .Xfrout.socket.unixdomain.open.

    #
    # Test2 for Xfrin statistics
    #
    check initial statistics not containing example.org for Xfrin

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

    A query for www.example.org to 127.0.0.1:47806 should have rcode NOERROR
    # Make sure handling statistics command handling checked below is
    # after this query
    And wait for bind10 stderr message AUTH_SEND_NORMAL_RESPONSE

    #
    # Test3 for Xfrout statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    # note that this does not 100% guarantee the stats updated Xfrout
    # statistics.  But there doesn't seem to be a better log message that
    # suggests this event.
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones.IN except for the following items
      | item_name                | item_value |
      | _SERVER_.notifyoutv4     |          1 |
      | _SERVER_.xfrreqdone      |          1 |
      | example.org..notifyoutv4 |          1 |
      | example.org..xfrreqdone  |          1 |

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | item_value |
      | open      |          1 |
      | accept    |          1 |

    #
    # Test4 for Xfrin statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrin with cmdctl
    wait for new bind10 stderr message XFRIN_RECEIVED_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrin with cmdctl
    The statistics counters are 0 in category .Xfrin.zones.IN except for the following items
      | item_name                       | item_value | min_value |
      | _SERVER_.soaoutv4               |          1 |           |
      | _SERVER_.axfrreqv4              |          1 |           |
      | _SERVER_.xfrsuccess             |          1 |           |
      | _SERVER_.last_axfr_duration     |            |       0.0 |
      | example.org..soaoutv4           |          1 |           |
      | example.org..axfrreqv4          |          1 |           |
      | example.org..xfrsuccess         |          1 |           |
      | example.org..last_axfr_duration |            |       0.0 |

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
    # Test1 for Xfrout statistics
    #
    check initial statistics not containing example.org for Xfrout with cmdctl port 47804 except for the following items
      | item_name                | min_value | max_value |
      | socket.unixdomain.open   |         0 |         1 |
    # Note: See above about .Xfrout.socket.unixdomain.open.

    #
    # Test2 for Xfrin statistics
    #
    check initial statistics not containing example.org for Xfrin

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
    # Test3 for Xfrout statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones.IN except for the following items
      | item_name                | item_value | min_value | max_value |
      | _SERVER_.notifyoutv6     |          1 |           |           |
      | _SERVER_.xfrrej          |            |         1 |         3 |
      | example.org..notifyoutv6 |          1 |           |           |
      | example.org..xfrrej      |            |         1 |         3 |
    # Note: The above rejection counters might sometimes be increased
    # up to 3. See this for details
    # http://git.bind10.isc.org/~tester/builder/BIND10-lettuce/20120918210000-MacOS/logs/lettuce.out

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | item_value |
      | open      |          1 |
      | accept    |          1 |

    #
    # Test4 for Xfrin statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrin with cmdctl
    wait for new bind10 stderr message XFRIN_RECEIVED_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrin with cmdctl
    The statistics counters are 0 in category .Xfrin.zones.IN except for the following items
      | item_name              | item_value |
      | _SERVER_.soaoutv6      |          1 |
      | _SERVER_.axfrreqv6     |          1 |
      | _SERVER_.xfrfail       |          1 |
      | example.org..soaoutv6  |          1 |
      | example.org..axfrreqv6 |          1 |
      | example.org..xfrfail   |          1 |

    #
    # Test for Xfr request rejected in IPv4
    #
    Scenario: Handle incoming notify (XFR request rejected in IPv4)
    Given I have bind10 running with configuration xfrin/retransfer_master_v4.conf with cmdctl port 47804 as master
    And wait for master stderr message BIND10_STARTED_CC
    And wait for master stderr message CMDCTL_STARTED
    And wait for master stderr message AUTH_SERVER_STARTED
    And wait for master stderr message XFROUT_STARTED
    And wait for master stderr message ZONEMGR_STARTED
    And wait for master stderr message STATS_STARTING

    And I have bind10 running with configuration xfrin/retransfer_slave_notify_v4.conf
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED

    A query for www.example.org to 127.0.0.1:47806 should have rcode NXDOMAIN

    #
    # Test1 for Xfrout statistics
    #
    check initial statistics not containing example.org for Xfrout with cmdctl port 47804 except for the following items
      | item_name                | min_value | max_value |
      | socket.unixdomain.open   |         0 |         1 |
    # Note: See above about .Xfrout.socket.unixdomain.open.

    #
    # Test2 for Xfrin statistics
    #
    check initial statistics not containing example.org for Xfrin

    #
    # set transfer_acl rejection
    # Local xfr requests from Xfrin module would be rejected here.
    #
    When I send bind10 the following commands with cmdctl port 47804
    """
    config set Xfrout/zone_config[0]/transfer_acl [{"action":  "REJECT", "from": "127.0.0.1"}]
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

    A query for www.example.org to 127.0.0.1:47806 should have rcode NXDOMAIN

    #
    # Test3 for Xfrout statistics
    #
    # check statistics change
    #

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    # wait until stats request at least after NOTIFY_OUT_REPLY_RECEIVED
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones.IN except for the following items
      | item_name                | item_value | min_value | max_value |
      | _SERVER_.notifyoutv4     |          1 |           |           |
      | _SERVER_.xfrrej          |            |         1 |         3 |
      | example.org..notifyoutv4 |          1 |           |           |
      | example.org..xfrrej      |            |         1 |         3 |
    # Note: The above rejection counters might sometimes be increased
    # up to 3. See this for details
    # http://git.bind10.isc.org/~tester/builder/BIND10-lettuce/20120918210000-MacOS/logs/lettuce.out

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | item_value |
      | open      |          1 |
      | accept    |          1 |

    #
    # Test4 for Xfrin statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrin with cmdctl
    wait for new bind10 stderr message XFRIN_RECEIVED_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrin with cmdctl
    The statistics counters are 0 in category .Xfrin.zones.IN except for the following items
      | item_name              | item_value |
      | _SERVER_.soaoutv4      |          1 |
      | _SERVER_.axfrreqv4     |          1 |
      | _SERVER_.xfrfail       |          1 |
      | example.org..soaoutv4  |          1 |
      | example.org..axfrreqv4 |          1 |
      | example.org..xfrfail   |          1 |

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

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    # wait until stats request at least after NOTIFY_OUT_TIMEOUT
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones.IN except for the following items
      | item_name                | min_value | max_value |
      | _SERVER_.notifyoutv6     |         1 |         5 |
      | example.org..notifyoutv6 |         1 |         5 |

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | item_value |
      | open      |          1 |

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
