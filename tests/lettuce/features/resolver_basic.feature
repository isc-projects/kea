Feature: Basic Resolver
    This feature set is just testing the execution of the b10-resolver
    module. It sees whether it starts up, takes configuration, and
    answers queries.

    Scenario: Listen for and answer query
        # This scenario starts a server that runs a real resolver.
        # In order not to send out queries into the wild, we only
        # query for something known to be hardcoded at this moment.
        # NOTE: once real priming has been implemented, this test needs
        # to be revised (as it would then leak, which is probably true
        # for any resolver system test)
        When I start bind10 with configuration resolver/resolver_basic.config
        And wait for bind10 stderr message BIND10_STARTED_CC
        And wait for bind10 stderr message CMDCTL_STARTED
        And wait for bind10 stderr message RESOLVER_STARTED

        bind10 module Resolver should be running
        And bind10 module Auth should not be running
        And bind10 module Xfrout should not be running
        And bind10 module Zonemgr should not be running
        And bind10 module Xfrin should not be running
        And bind10 module Stats should not be running
        And bind10 module StatsHttpd should not be running

        # The ACL is set to reject any queries
        A query for l.root-servers.net. should have rcode REFUSED

        # Test whether acl ACCEPT works
        When I set bind10 configuration Resolver/query_acl[0] to {"action": "ACCEPT", "from": "127.0.0.1"}
        # This address is currently hardcoded, so shouldn't cause outside traffic
        A query for l.root-servers.net. should have rcode NOERROR

        # Check whether setting the ACL to reject again works
        When I set bind10 configuration Resolver/query_acl[0] to {"action": "REJECT", "from": "127.0.0.1"}
        A query for l.root-servers.net. should have rcode REFUSED
