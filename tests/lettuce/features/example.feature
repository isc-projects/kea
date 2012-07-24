Feature: Example feature
    This is an example Feature set. Is is mainly intended to show
    our use of the lettuce tool and our own framework for it
    The first scenario is to show what a simple test would look like, and
    is intentionally uncommented.
    The later scenarios have comments to show what the test steps do and
    support

    Scenario: A simple example
        Given I have bind10 running with configuration example.org.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module Stats should not be running
        And bind10 module StatsHttpd should not be running

        A query for www.example.org should have rcode NOERROR
        A query for www.doesnotexist.org should have rcode REFUSED
        The SOA serial for example.org should be 1234

    Scenario: New database
        # This test checks whether a database file is automatically created
        # Underwater, we take advantage of our intialization routines so
        # that we are sure this file does not exist, see
        # features/terrain/terrain.py

        # Standard check to test (non-)existence of a file.
        # This file is actually automatically created.
        The file data/test_nonexistent_db.sqlite3 should not exist

        # In the first scenario, we used 'given I have bind10 running', which
        # is actually a compound step consisting of the following two
        # one to start the server
        When I start bind10 with configuration no_db_file.config

        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        # Now we use the first step again to see if the file has been created
        The file data/test_nonexistent_db.sqlite3 should exist

        bind10 module Auth should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module Stats should not be running
        And bind10 module StatsHttpd should not be running

        # This is a general step to stop a named process. By convention,
        # the default name for any process is the same as the one we
        # use in the start step (for bind 10, that is 'I start bind10 with')
        # See scenario 'Multiple instances' for more.
        Then stop process bind10

    Scenario: example.org queries
        # This scenario performs a number of queries and inspects the results
        # Simple queries have already been show, but after we have sent a query,
        # we can also do more extensive checks on the result.
        # See querying.py for more information on these steps.

        # note: lettuce can group similar checks by using tables, but we
        # intentionally do not make use of that here

        # This is a compound statement that starts and waits for the
        # started message
        Given I have bind10 running with configuration example.org.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module Stats should not be running
        And bind10 module StatsHttpd should not be running

        # Some simple queries that is not examined further
        A query for www.example.com should have rcode REFUSED
        A query for www.example.org should have rcode NOERROR

        # A query where we look at some of the result properties
        A query for www.example.org should have rcode NOERROR
        The last query response should have qdcount 1
        The last query response should have ancount 1
        The last query response should have nscount 3
        The last query response should have adcount 0
        # The answer section can be inspected in its entirety; in the future
        # we may add more granular inspection steps
        The answer section of the last query response should be
        """
        www.example.org.   3600    IN    A      192.0.2.1
        """

        A query for example.org type NS should have rcode NOERROR
        The answer section of the last query response should be
        """
        example.org. 3600 IN NS ns1.example.org.
        example.org. 3600 IN NS ns2.example.org.
        example.org. 3600 IN NS ns3.example.org.
        """

        # We have a specific step for checking SOA serial numbers
        The SOA serial for example.org should be 1234

        # Another query where we look at some of the result properties
        A query for doesnotexist.example.org should have rcode NXDOMAIN
        The last query response should have qdcount 1
        The last query response should have ancount 0
        The last query response should have nscount 1
        The last query response should have adcount 0
        # When checking flags, we must pass them exactly as they appear in
        # the output of dig.
        The last query response should have flags qr aa rd

        A query for www.example.org type TXT should have rcode NOERROR
        The last query response should have ancount 0

        # Some queries where we specify more details about what to send and
        # where
        A query for www.example.org class CH should have rcode REFUSED
        A query for www.example.org to 127.0.0.1 should have rcode NOERROR
        A query for www.example.org to 127.0.0.1:47806 should have rcode NOERROR
        A query for www.example.org type A class IN to 127.0.0.1:47806 should have rcode NOERROR

    Scenario: changing database
        # This scenario contains a lot of 'wait for' steps
        # If those are not present, the asynchronous nature of the application
        # can cause some of the things we send to be handled out of order;
        # for instance auth could still be serving the old zone when we send
        # the new query, or already respond from the new database.
        # Therefore we wait for specific log messages after each operation
        #
        # This scenario outlines every single step, and does not use
        # 'steps of steps' (e.g. Given I have bind10 running)
        # We can do that but as an example this is probably better to learn
        # the system

        When I start bind10 with configuration example.org.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Resolver should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module Stats should not be running
        And bind10 module StatsHttpd should not be running

        A query for www.example.org should have rcode NOERROR
        Wait for new bind10 stderr message AUTH_SEND_NORMAL_RESPONSE
        Then set bind10 configuration data_sources/classes/IN[0]/params to {"database_file": "data/empty_db.sqlite3"}
        And wait for new bind10 stderr message DATASRC_SQLITE_CONNOPEN
        A query for www.example.org should have rcode REFUSED
        Wait for new bind10 stderr message AUTH_SEND_NORMAL_RESPONSE
        Then set bind10 configuration data_sources/classes/IN[0]/params to {"database_file": "data/example.org.sqlite3"}
        And wait for new bind10 stderr message DATASRC_SQLITE_CONNOPEN
        A query for www.example.org should have rcode NOERROR

    Scenario: two bind10 instances
        # This is more a test of the test system, start 2 bind10's
        When I start bind10 with configuration example.org.config as bind10_one
        And wait for bind10_one stderr message BIND10_STARTED_CC
        And wait for bind10_one stderr message CMDCTL_STARTED
        And wait for bind10_one stderr message AUTH_SERVER_STARTED

        And I start bind10 with configuration example2.org.config with cmdctl port 47804 as bind10_two
        And wait for bind10_two stderr message BIND10_STARTED_CC
        And wait for bind10_two stderr message CMDCTL_STARTED
        And wait for bind10_two stderr message AUTH_SERVER_STARTED

        A query for www.example.org to 127.0.0.1:47806 should have rcode NOERROR
        A query for www.example.org to [::1]:47807 should have rcode NOERROR
        The SOA serial for example.org should be 1234
        The SOA serial for example.org at 127.0.0.1:47806 should be 1234
        The SOA serial for example.org at ::1:47807 should be 1234

        Then set bind10 configuration data_sources/classes/IN[0]/params to {"database_file": "data/empty_db.sqlite3"}
        And wait for bind10_one stderr message DATASRC_SQLITE_CONNOPEN

        A query for www.example.org to 127.0.0.1:47806 should have rcode REFUSED
        A query for www.example.org to [::1]:47807 should have rcode NOERROR
