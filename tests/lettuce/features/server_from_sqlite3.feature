Feature: SQLite3 backend
    In order to support SQLite3
    As administrators
    We test serving an sqlite3 backend

    Scenario: New database
        Given I have no database
        When I start bind10 with configuration no_db_file.config
        Then wait for bind10 auth to start
        Then stop bind10
        I should see a database file

    Scenario: example.org queries
        When I start bind10 with configuration example.org.config
        Then wait for bind10 auth to start
        A query for www.example.com should have rcode REFUSED
        A query for www.example.org should have rcode NOERROR
        A query for doesnotexist.example.org should have rcode NXDOMAIN

    Scenario: changing database
        # This scenario contains a lot of 'wait for' steps
        # If those are not present, the asynchronous nature of the application
        # can cause some of the things we send to be handled out of order;
        # for instance auth could still be serving the old zone when we send
        # the new query, or already respond from the new database.
        # Therefore we wait for specific log messages after each operation
        When I start bind10 with configuration example.org.config
        Then wait for bind10 auth to start
        Wait for log message CMDCTL_STARTED
        A query for www.example.org should have rcode NOERROR
        Wait for log message AUTH_SEND_NORMAL_RESPONSE
        Then set bind10 configuration Auth/database_file to data/empty_db.sqlite3
        And wait for log message DATASRC_SQLITE_OPEN
        A query for www.example.org should have rcode REFUSED
        Wait for log message AUTH_SEND_NORMAL_RESPONSE
        Then set bind10 configuration Auth/database_file to data/example.org.sqlite3
        And wait for log message DATASRC_SQLITE_OPEN
        A query for www.example.org should have rcode NOERROR
