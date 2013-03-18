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
    # Test1 for Xfrout statistics
    #
    check initial statistics for Xfrout
    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | min_value | max_value |
      | open      |         0 |         1 |

    #
    # Test2 for Xfrin statistics
    #
    check initial statistics for Xfrin
    When I send bind10 with cmdctl port 47804 the command Xfrout notify example.org IN
    Then wait for new master stderr message XFROUT_NOTIFY_COMMAND
    Then wait for new bind10 stderr message AUTH_RECEIVED_NOTIFY
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_NOTIFY
    Then wait for new bind10 stderr message XFRIN_XFR_TRANSFER_STARTED
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_XFRIN_SUCCESS
    Then wait 5 times for new master stderr message NOTIFY_OUT_SENDING_NOTIFY
    Then wait for new master stderr message NOTIFY_OUT_RETRY_EXCEEDED

    A query for www.example.org to [::1]:47806 should have rcode NOERROR

    #
    # Test3 for Xfrout statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    wait for new master stderr message STATS_SEND_STATISTICS_REQUEST
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones except for the following items
      | item_name                | item_value |
      | _SERVER_.notifyoutv6     |          5 |
      | _SERVER_.xfrreqdone      |          1 |
      | example.org..notifyoutv6 |          5 |
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
    wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
    wait for new bind10 stderr message XFRIN_RECEIVED_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrin with cmdctl
    The statistics counters are 0 in category .Xfrin.zones except for the following items
      | item_name                         | item_value | min_value |
      | _SERVER_.soaoutv6                 |          1 |           |
      | _SERVER_.axfrreqv6                |          1 |           |
      | _SERVER_.xfrsuccess               |          1 |           |
      | _SERVER_.latest_axfr_duration     |            |       0.0 |
      | example.org..soaoutv6             |          1 |           |
      | example.org..axfrreqv6            |          1 |           |
      | example.org..xfrsuccess           |          1 |           |
      | example.org..latest_axfr_duration |            |       0.0 |

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
    check initial statistics for Xfrout
    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | min_value | max_value |
      | open      |         0 |         1 |

    #
    # Test2 for Xfrin statistics
    #
    check initial statistics for Xfrin
    When I send bind10 with cmdctl port 47804 the command Xfrout notify example.org IN
    Then wait for new master stderr message XFROUT_NOTIFY_COMMAND
    Then wait for new bind10 stderr message AUTH_RECEIVED_NOTIFY
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_NOTIFY
    Then wait for new bind10 stderr message XFRIN_XFR_TRANSFER_STARTED
    Then wait for new bind10 stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_XFRIN_SUCCESS
    Then wait 5 times for new master stderr message NOTIFY_OUT_SENDING_NOTIFY
    Then wait for new master stderr message NOTIFY_OUT_RETRY_EXCEEDED

    A query for www.example.org to 127.0.0.1:47806 should have rcode NOERROR

    #
    # Test3 for Xfrout statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    wait for new master stderr message STATS_SEND_STATISTICS_REQUEST
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones except for the following items
      | item_name                | item_value |
      | _SERVER_.notifyoutv4     |          5 |
      | _SERVER_.xfrreqdone      |          1 |
      | example.org..notifyoutv4 |          5 |
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
    wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
    wait for new bind10 stderr message XFRIN_RECEIVED_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrin with cmdctl
    The statistics counters are 0 in category .Xfrin.zones except for the following items
      | item_name                         | item_value | min_value |
      | _SERVER_.soaoutv4                 |          1 |           |
      | _SERVER_.axfrreqv4                |          1 |           |
      | _SERVER_.xfrsuccess               |          1 |           |
      | _SERVER_.latest_axfr_duration     |            |       0.0 |
      | example.org..soaoutv4             |          1 |           |
      | example.org..axfrreqv4            |          1 |           |
      | example.org..xfrsuccess           |          1 |           |
      | example.org..latest_axfr_duration |            |       0.0 |

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
    check initial statistics for Xfrout
    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | min_value | max_value |
      | open      |         0 |         1 |

    #
    # Test2 for Xfrin statistics
    #
    check initial statistics for Xfrin
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
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_NOTIFY
    Then wait for new bind10 stderr message XFRIN_XFR_TRANSFER_STARTED
    Then wait for new bind10 stderr message XFRIN_XFR_TRANSFER_PROTOCOL_VIOLATION not XFRIN_XFR_TRANSFER_STARTED
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_XFRIN_FAILED not ZONEMGR_RECEIVE_XFRIN_SUCCESS
    Then wait 5 times for new master stderr message NOTIFY_OUT_SENDING_NOTIFY
    Then wait for new master stderr message NOTIFY_OUT_RETRY_EXCEEDED

    A query for www.example.org to [::1]:47806 should have rcode NXDOMAIN

    #
    # Test3 for Xfrout statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    wait for new master stderr message STATS_SEND_STATISTICS_REQUEST
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones except for the following items
      | item_name                | item_value | min_value |
      | _SERVER_.notifyoutv6     |          5 |           |
      | _SERVER_.xfrrej          |            |         1 |
      | example.org..notifyoutv6 |          5 |           |
      | example.org..xfrrej      |            |         1 |

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
    wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
    wait for new bind10 stderr message XFRIN_RECEIVED_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrin with cmdctl
    The statistics counters are 0 in category .Xfrin.zones except for the following items
      | item_name              | min_value | max_value |
      | _SERVER_.soaoutv6      |         1 |         3 |
      | _SERVER_.axfrreqv6     |         1 |         3 |
      | _SERVER_.xfrfail       |         1 |         3 |
      | example.org..soaoutv6  |         1 |         3 |
      | example.org..axfrreqv6 |         1 |         3 |
      | example.org..xfrfail   |         1 |         3 |

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
    check initial statistics for Xfrout
    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | min_value | max_value |
      | open      |         0 |         1 |

    #
    # Test2 for Xfrin statistics
    #
    check initial statistics for Xfrin
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
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_NOTIFY
    Then wait for new bind10 stderr message XFRIN_XFR_TRANSFER_STARTED
    Then wait for new bind10 stderr message XFRIN_XFR_TRANSFER_PROTOCOL_VIOLATION not XFRIN_XFR_TRANSFER_STARTED
    Then wait for new bind10 stderr message ZONEMGR_RECEIVE_XFRIN_FAILED not ZONEMGR_RECEIVE_XFRIN_SUCCESS
    Then wait 5 times for new master stderr message NOTIFY_OUT_SENDING_NOTIFY
    Then wait for new master stderr message NOTIFY_OUT_RETRY_EXCEEDED

    A query for www.example.org to 127.0.0.1:47806 should have rcode NXDOMAIN

    #
    # Test3 for Xfrout statistics
    #
    # check statistics change
    #

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    wait for new master stderr message STATS_SEND_STATISTICS_REQUEST
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones except for the following items
      | item_name                | item_value | min_value |
      | _SERVER_.notifyoutv4     |          5 |           |
      | _SERVER_.xfrrej          |            |         1 |
      | example.org..notifyoutv4 |          5 |           |
      | example.org..xfrrej      |            |         1 |

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
    wait for new bind10 stderr message STATS_SEND_STATISTICS_REQUEST
    wait for new bind10 stderr message XFRIN_RECEIVED_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrin with cmdctl
    The statistics counters are 0 in category .Xfrin.zones except for the following items
      | item_name              | min_value | max_value |
      | _SERVER_.soaoutv4      |         1 |         3 |
      | _SERVER_.axfrreqv4     |         1 |         3 |
      | _SERVER_.xfrfail       |         1 |         3 |
      | example.org..soaoutv4  |         1 |         3 |
      | example.org..axfrreqv4 |         1 |         3 |
      | example.org..xfrfail   |         1 |         3 |

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

    # wait until the last stats requesting is finished
    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    wait for new master stderr message STATS_SEND_STATISTICS_REQUEST
    wait for new master stderr message XFROUT_RECEIVED_GETSTATS_COMMAND
    last bindctl output should not contain "error"

    When I query statistics zones of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.zones except for the following items
      | item_name                | min_value | max_value |
      | _SERVER_.notifyoutv6     |         1 |	       5 |
      | example.org..notifyoutv6 |         1 |	       5 |

    When I query statistics socket of bind10 module Xfrout with cmdctl port 47804
    The statistics counters are 0 in category .Xfrout.socket.unixdomain except for the following items
      | item_name | item_value |
      | open      |          1 |
