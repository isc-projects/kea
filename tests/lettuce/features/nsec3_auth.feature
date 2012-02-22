Feature: NSEC3 Authoritative service
    This feature tests NSEC3 as defined in RFC5155, using the example
    zone from appendix A and testing responses appendix B.
    Additional tests can be added as well
    
    Scenario: B.1. Name Error
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A query for a.c.x.w.example. should have rcode NXDOMAIN
