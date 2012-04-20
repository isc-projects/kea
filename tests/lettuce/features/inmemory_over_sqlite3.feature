Feature: In-memory zone using SQLite3 backend
    This feature tests the authoritative server configured with an in-memory
    data source that uses the SQLite3 data source as the backend, and tests
    scenarios that update the zone via incoming zone transfers.

    Scenario: Load and response
        Given I have bind10 running with configuration inmemory_over_sqlite3/secondary.conf
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED
        A query for www.example.org should have rcode NOERROR
        The SOA serial for example.org should be 1234
