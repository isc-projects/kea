Feature: default bind10 config
    Tests for the default configuration of bind10.

    Scenario: Check that only the default components are running
    Given I have bind10 running with configuration default.config

    bind10 module Boss should be running
    bind10 module Logging should be running
    bind10 module Stats should be running
    bind10 module StatsHttpd should be running
    bind10 module Resolver should not be running
    bind10 module Xfrout should not be running
    bind10 module Zonemgr should not be running
    bind10 module Xfrin should not be running
    bind10 module Auth should not be running
