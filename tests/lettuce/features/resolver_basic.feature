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
        And wait for new bind10 stderr message RESOLVER_STARTED
        # This answer is currently hardcoded (as part of the fake priming)
        A query for l.root-servers.net. should have rcode NOERROR
