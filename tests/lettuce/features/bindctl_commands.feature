Feature: control with bindctl
    Assorted tests using bindctl for the administration of BIND 10.

    Scenario: Removing modules
    # This test runs the original example configuration, which has
    # a number of modules. It then removes all non-essential modules,
    # and checks whether they do disappear from the list of running
    # modules (note that it 'misuses' the help command for this,
    # there is a Boss command 'show_processes' but it's output is
    # currently less standardized than 'help')
    Given I have bind10 running with configuration bindctl_commands.config
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    And wait for bind10 stderr message ZONEMGR_STARTED
    And wait for bind10 stderr message AUTH_SERVER_STARTED
    And wait for bind10 stderr message XFRIN_STARTED
    And wait for bind10 stderr message XFROUT_STARTED
    And wait for bind10 stderr message STATS_STARTING
    And wait for bind10 stderr message STATHTTPD_STARTED

    Then remove bind10 configuration Boss/components/NOSUCHMODULE
    last bindctl output should contain Error

    bind10 module Xfrout should be running
    bind10 module Stats should be running
    bind10 module Zonemgr should be running
    bind10 module Xfrin should be running
    bind10 module Auth should be running
    bind10 module StatsHttpd should be running
    bind10 module Resolver should not be running

    Then remove bind10 configuration Boss/components value b10-xfrout
    And wait for new bind10 stderr message BIND10_PROCESS_ENDED
    last bindctl output should not contain Error

    # assuming it won't error for further modules (if it does, the final
    # 'should not be running' tests would fail anyway)
    Then remove bind10 configuration Boss/components value b10-stats-httpd
    And wait for new bind10 stderr message BIND10_PROCESS_ENDED
    last bindctl output should not contain Error

    Then remove bind10 configuration Boss/components value b10-stats
    And wait for new bind10 stderr message BIND10_PROCESS_ENDED
    last bindctl output should not contain Error

    Then remove bind10 configuration Boss/components value b10-zonemgr
    And wait for new bind10 stderr message BIND10_PROCESS_ENDED
    last bindctl output should not contain Error

    Then remove bind10 configuration Boss/components value b10-xfrin
    And wait for new bind10 stderr message BIND10_PROCESS_ENDED
    last bindctl output should not contain Error

    Then remove bind10 configuration Boss/components value b10-auth
    And wait for new bind10 stderr message BIND10_PROCESS_ENDED
    last bindctl output should not contain Error

    # After these ^^^ have been stopped...
    bind10 module Xfrout should not be running
    bind10 module Zonemgr should not be running
    bind10 module Xfrin should not be running
    bind10 module Auth should not be running
    bind10 module StatsHttpd should not be running
    bind10 module Stats should not be running
    bind10 module Resolver should not be running

    Scenario: Executing scripts
    # This test tests the 'execute' command, which reads and executes
    # bindctl commands from a file
    Given I have bind10 running with configuration bindctl_commands.config
    And wait for bind10 stderr message BIND10_STARTED_CC
    And wait for bind10 stderr message CMDCTL_STARTED
    When I send bind10 the command execute file data/commands/empty
    last bindctl output should not contain Error
