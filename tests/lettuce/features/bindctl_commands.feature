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

    Scenario: Executing scripts from files
        # This test tests the 'execute' command, which reads and executes
        # bindctl commands from a file
        Given I have bind10 running with configuration bindctl/bindctl.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED

        # first a few bad commands
        When I send bind10 the command execute
        last bindctl output should contain Error
        When I send bind10 the command execute file
        last bindctl output should contain Error
        When I send bind10 the command execute file data/commands/nosuchfile
        last bindctl output should contain Error

        # empty list should be no-op
        When I send bind10 the command execute file data/commands/empty
        last bindctl output should not contain Error

        # some tests of directives like !echo and !verbose
        When I send bind10 the command execute file data/commands/directives
        last bindctl output should not contain Error
        last bindctl output should not contain commentexample1
        last bindctl output should contain echoexample2
        last bindctl output should contain verbosecommentexample3
        last bindctl output should not contain commentexample4
        last bindctl output should contain echoexample5
        last bindctl output should contain echoexample6
        last bindctl output should contain verbosecommentexample7
        last bindctl output should not contain commentexample8

        # bad_command contains a bad command, at which point execution should stop
        When I send bind10 the command execute file data/commands/bad_command
        last bindctl output should contain shouldshow
        last bindctl output should contain Error
        last bindctl output should not contain shouldnotshow
        # This would fail if the entire list was passed, or the configuration
        # was committed
        send bind10 the command config show Boss/components
        last bindctl output should not contain b10-auth

        # nested_command contains another execute script
        When I send bind10 the command execute file data/commands/nested
        last bindctl output should contain shouldshow
        last bindctl output should not contain Error

        # show commands from a file
        When I send bind10 the command execute file data/commands/bad_command show
        last bindctl output should not contain Error
        last bindctl output should contain shouldshow
        last bindctl output should contain shouldnotshow

    Scenario: Executing builting script init_authoritative_server
        Given I have bind10 running with configuration bindctl/bindctl.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED

        When I send bind10 the command execute init_authoritative_server show
        # just test some parts of the output
        last bindctl output should contain /Boss/components/b10-auth/special
        last bindctl output should contain /Boss/components/b10-zonemgr/kind
        last bindctl output should contain Please

        # nothing should have been changed
        When I send bind10 the command config diff
        last bindctl output should contain {}

        # ok now make sure modules aren't running, execute it, and make
        # sure modules are running
        bind10 module Auth should not be running
        bind10 module Xfrout should not be running
        bind10 module Xfrin should not be running
        bind10 module Zonemgr should not be running

        When I send bind10 the following commands:
        """
        execute init_authoritative_server
        config commit
        """
        And wait for bind10 stderr message AUTH_SERVER_STARTED
        And wait for bind10 stderr message ZONEMGR_STARTED
        And wait for bind10 stderr message XFRIN_STARTED
        And wait for bind10 stderr message XFROUT_STARTED

        last bindctl output should not contain Error
        bind10 module Auth should be running
        bind10 module Xfrout should be running
        bind10 module Xfrin should be running
        bind10 module Zonemgr should be running
