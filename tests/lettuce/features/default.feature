Feature: default bind10 config
    Tests for the default configuration of bind10.

    Scenario: Check that only the default components are running
    Given I have bind10 running with configuration default.config
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message STATS_STARTING

    # These should be running
    bind10 module Boss should be running
    And bind10 module Logging should be running
    And bind10 module Stats should be running

    # These should not be running
    bind10 module Resolver should not be running
    And bind10 module Xfrout should not be running
    And bind10 module Zonemgr should not be running
    And bind10 module Xfrin should not be running
    And bind10 module Auth should not be running
    And bind10 module StatsHttpd should not be running
