Feature: Basic Authoritative DNS server
    This feature set is for testing the execution of the b10-auth
    component using its default datasource configurations. This
    will start it and perform queries against it.

    Scenario: Query builtin bind zone
        Given I have bind10 running with configuration auth/auth_basic.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message AUTH_SERVER_STARTED

        bind10 module Auth should be running
        And bind10 module Resolver should not be running

        A query for example.com should have rcode REFUSED
        A query for version.bind type TXT class CH should have rcode NOERROR
        A query for authors.bind type TXT class CH should have rcode NOERROR

        # TODO: to be compatible with BIND 9
        # A query for nonexistent.bind type TXT class CH should have rcode REFUSED
