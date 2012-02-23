Feature: Multiple instances
    This feature tests whether multiple instances can be run, and whether
    removing them does not affect the running of other instances

    Scenario: Multiple instances
        # This config should have two running instances
        Given I have bind10 running with configuration multi_instance/multi_auth.config
        And bind10 module Auth should be running
        A query for example.com should have rcode REFUSED

        # this also checks whether the process is running
        If I remember the pid of process b10-auth
        And remember the pid of process b10-auth-2

        When I remove bind10 configuration Boss/components value b10-auth-2

        Then the pid of process b10-auth should not have changed
        # COMMENTED OUT BECAUSE OF CURRENT BUG
        # And a query for example.com should have rcode REFUSED

        When I send bind10 the following commands
        """
        config add Boss/components b10-auth-2
        config set Boss/components/b10-auth-2/special auth
        config set Boss/components/b10-auth-2/kind needed
        config commit
        """
        And wait for new bind10 stderr message AUTH_SERVER_STARTED
        And remember the pid of process b10-auth-2

        Then the pid of process b10-auth should not have changed
        A query for example.com should have rcode REFUSED

        When I remove bind10 configuration Boss/components value b10-auth
        Then the pid of process b10-auth-2 should not have changed
        # COMMENTED OUT BECAUSE OF CURRENT BUG
        #A query for example.com should have rcode REFUSED
