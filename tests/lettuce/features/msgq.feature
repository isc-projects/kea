Feature: Message queue tests
    Tests for the message queue daemon.

    Scenario: logging
        # We check the message queue logs.
        Given I have bind10 running with configuration default.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message MSGQ_START
        And wait for bind10 stderr message MSGQ_LISTENER_STARTED
        And wait for bind10 stderr message MSGQ_CFGMGR_SUBSCRIBED
        And wait for bind10 stderr message CMDCTL_STARTED

        # Check it handles configuration. The configuration is invalid,
        # but it should get there anyway and we abuse it.
        # TODO: Once it has any kind of real command or configuration
        # value, use that instead.
        Then set bind10 configuration Msgq to {"nonsense": 1}
        And wait for bind10 stderr message MSGQ_CONFIG_DATA
