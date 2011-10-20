Feature: SQLite3 backend
    In order to support SQLite3
    As administrators
    We test serving an sqlite3 backend

    Scenario: New database
        Given I have no database
        When I start bind10 with configuration no_db_file.config
        Then wait for bind10 auth to start
        Then stop process bind10
        I should see a database file

    Scenario: example.org queries
        # This scenario performs a number of queries and inspects the results
        # This is not only to test, but also to show the different options
        # we have to inspect the data

        # This is a compound statement that starts and waits for the
        # started message
        Given I have bind10 running with configuration example.org.config

        # A simple query that is not examined further
        A query for www.example.com should have rcode REFUSED

        # A query where we look at some of the result properties
        A query for www.example.org should have rcode NOERROR
        The last query should have qdcount 1
        The last query should have ancount 1
        The last query should have nscount 3
        The last query should have adcount 0
        The SOA serial for example.org should be 1234

        # Another query where we look at some of the result properties
        A query for doesnotexist.example.org should have rcode NXDOMAIN
        The last query should have qdcount 1
        The last query should have ancount 0
        The last query should have nscount 1
        The last query should have adcount 0
        The last query should have flags qr aa rd

        A query for www.example.org type TXT should have rcode NOERROR
        The last query should have ancount 0

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
        Then wait for bind10 auth to start
        Wait for bind10 stderr message CMDCTL_STARTED
        A query for www.example.org should have rcode NOERROR
        Wait for bind10 stderr message AUTH_SEND_NORMAL_RESPONSE
        Then set bind10 configuration Auth/database_file to data/empty_db.sqlite3
        And wait for bind10 stderr message DATASRC_SQLITE_OPEN
        A query for www.example.org should have rcode REFUSED
        Wait for bind10 stderr message AUTH_SEND_NORMAL_RESPONSE
        Then set bind10 configuration Auth/database_file to data/example.org.sqlite3
        And wait for bind10 stderr message DATASRC_SQLITE_OPEN
        A query for www.example.org should have rcode NOERROR

    Scenario: two bind10 instances
        # This is more a test of the test system, start 2 bind10's
        When I start bind10 with configuration example.org.config as bind10_one
        And I start bind10 with configuration example2.org.config with cmdctl port 47804 as bind10_two

        Then wait for bind10 auth of bind10_one to start
        Then wait for bind10 auth of bind10_two to start
        A query for www.example.org to 127.0.0.1:47806 should have rcode NOERROR
        A query for www.example.org to 127.0.0.1:47807 should have rcode NOERROR

        Then set bind10 configuration Auth/database_file to data/empty_db.sqlite3
        And wait for bind10_one stderr message DATASRC_SQLITE_OPEN

        A query for www.example.org to 127.0.0.1:47806 should have rcode REFUSED
        A query for www.example.org to 127.0.0.1:47807 should have rcode NOERROR
