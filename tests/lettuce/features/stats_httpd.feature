Feature: b10-stats-httpd module
    Tests the stats httpd module

    Scenario: Check that the module logs and responds to requests
    Given I have bind10 running with configuration bindctl_commands.config
    And wait for bind10 stderr message STATHTTPD_STARTED

    When I request the URL http://127.0.0.1:47811/
    # Should result in redirect, so two query logs
    And wait for new bind10 stderr message localhost "GET / HTTP/1.0" 302 -
    And wait for new bind10 stderr message localhost "GET /bind10/statistics/xml/ HTTP/1.0" 200 -
    The last http response status code should be 200

    When I request the URL http://127.0.0.1:47811/no_such_url
    And wait for new bind10 stderr message localhost "GET /no_such_url HTTP/1.0" 404 -
    The last http response status code should be 404
