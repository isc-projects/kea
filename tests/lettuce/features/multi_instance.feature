Feature: Multiple instances
    This feature tests whether multiple instances can be run, and whether
    removing them does not affect the running of other instances

    Scenario: Multiple instances of Auth
        # Standard check to test (non-)existence of a file
        # This file is actually automatically
        The file data/test_nonexistent_db.sqlite3 should not exist

        # This config should have two running instances
        Given I have bind10 running with configuration multi_instance/multi_auth.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED

        # This is a hack. We should actually check if b10-auth and
        # b10-auth-2 are started by name. But there's currently no way
        # for a component to find out its name and log it.
        And wait 2 times for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module Stats should not be running
        And bind10 module StatsHttpd should not be running

        # Now we use the first step again to see if the file has been created
        The file data/test_nonexistent_db.sqlite3 should exist

        A query for example.com should have rcode REFUSED

        # this also checks whether the process is running
        If I remember the pid of process b10-auth
        And remember the pid of process b10-auth-2

        When I remove bind10 configuration Boss/components value b10-auth-2
        And wait for new bind10 stderr message BIND10_PROCESS_ENDED

        Then the pid of process b10-auth should not have changed
        And a query for example.com should have rcode REFUSED

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
        And wait for new bind10 stderr message BIND10_PROCESS_ENDED
        Then the pid of process b10-auth-2 should not have changed
        A query for example.com should have rcode REFUSED
