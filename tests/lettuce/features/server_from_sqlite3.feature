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
        When I start bind10 with configuration example.org.config
        Then wait for bind10 auth to start
        A query for www.example.org should have rcode NOERROR
        Then set bind10 configuration Auth/database_file to data/empty_db.sqlite3
        A query for www.example.org should have rcode REFUSED
        Then set bind10 configuration Auth/database_file to data/example.org.sqlite3
        A query for www.example.org should have rcode NOERROR
