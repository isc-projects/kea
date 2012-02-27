Feature: NSEC3 Authoritative service
    This feature tests NSEC3 as defined in RFC5155, using the example
    zone from appendix A and testing the example responses from appendix B.
    Additional tests can be added as well.

    # Response section data is taken directly from RFC5155
    # It has been modified slightly; it has been 'flattened' (i.e. converted
    # to 1-line RRs with TTL and class data), and whitespace has been added
    # in the places where dig adds them too.
    # Any other changes from the specific example data are added as inline
    # comments.

    Scenario: B.1. Name Error
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for a.c.x.w.example. should have rcode NXDOMAIN
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 8
        The last query response should have adcount 1
        The authority section of the last query response should be
        """
        example.	3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
        example.	3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example.	3600	IN	NSEC3	1 1 12 aabbccdd  2t7b4g4vsa5smi47k61mv5bv1a22bojr NS SOA MX RRSIG DNSKEY NSEC3PARAM 
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. OSgWSm26B+cS+dDL8b5QrWr/dEWhtCsKlwKLIBHYH6blRxK9rC0bMJPw Q4mLIuw85H2EY762BOCXJZMnpuwhpA==
        b4um86eghhds6nea196smvmlo4ors995.example.	3600	IN	NSEC3	1 1 12 aabbccdd  gjeqe526plbf1g8mklp59enfd789njgi MX RRSIG 
        b4um86eghhds6nea196smvmlo4ors995.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. ZkPG3M32lmoHM6pa3D6gZFGB/rhL//Bs3Omh5u4m/CUiwtblEVOaAKKZ d7S959OeiX43aLX3pOv0TSTyiTxIZg==
        35mthgpgcu1qg68fab165klnsnk3dpvl.example.	3600	IN	NSEC3	1 1 12 aabbccdd  b4um86eghhds6nea196smvmlo4ors995 NS DS RRSIG 
        35mthgpgcu1qg68fab165klnsnk3dpvl.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. g6jPUUpduAJKRljUsN8gB4UagAX0NxY9shwQAynzo8EUWH+z6hEIBlUT PGj15eZll6VhQqgZXtAIR3chwgW+SA==
        """

    Scenario: B.2. No Data Error
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for ns1.example. type MX should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 4
        The last query response should have adcount 1
        The authority section of the last query response should be
        """
        example.	3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
        example.	3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
        2t7b4g4vsa5smi47k61mv5bv1a22bojr.example.	3600	IN	NSEC3	1 1 12 aabbccdd  2vptu5timamqttgl4luu9kg21e0aor3s A RRSIG 
        2t7b4g4vsa5smi47k61mv5bv1a22bojr.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. OmBvJ1Vgg1hCKMXHFiNeIYHK9XVW0iLDLwJN4TFoNxZuP03gAXEI634Y wOc4YBNITrj413iqNI6mRk/r1dOSUw==
        """

    Scenario: B2.1. No Data Error, Empty Non-Terminal
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for y.w.example. should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 4
        The last query response should have adcount 1
        The authority section of the last query response should be
        """
        example.	3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
        example.	3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
        ji6neoaepv8b5o6k4ev33abha8ht9fgc.example.	3600	IN	NSEC3	1 1 12 aabbccdd  k8udemvp1j2f7eg6jebps17vp3n8i58h
        ji6neoaepv8b5o6k4ev33abha8ht9fgc.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. gPkFp1s2QDQ6wQzcg1uSebZ61W33rUBDcTj72F3kQ490fEdp7k1BUIfb cZtPbX3YCpE+sIt0MpzVSKfTwx4uYA==
        """

    Scenario: B.3. Referral to an Opt-Out Unsigned Zone
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for mc.c.example. type MX should have rcode NOERROR
        The last query response should have flags qr rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 6
        The last query response should have adcount 3
        The authority section of the last query response should be
        """
        c.example.	3600	IN	NS	ns1.c.example.
        c.example.	3600	IN	NS	ns2.c.example.
        35mthgpgcu1qg68fab165klnsnk3dpvl.example.	3600	IN	NSEC3	1 1 12 aabbccdd  b4um86eghhds6nea196smvmlo4ors995 NS DS RRSIG 
        35mthgpgcu1qg68fab165klnsnk3dpvl.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. g6jPUUpduAJKRljUsN8gB4UagAX0NxY9shwQAynzo8EUWH+z6hEIBlUT PGj15eZll6VhQqgZXtAIR3chwgW+SA==
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example.	3600	IN	NSEC3	1 1 12 aabbccdd  2t7b4g4vsa5smi47k61mv5bv1a22bojr NS SOA MX RRSIG DNSKEY NSEC3PARAM 
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. OSgWSm26B+cS+dDL8b5QrWr/dEWhtCsKlwKLIBHYH6blRxK9rC0bMJPw Q4mLIuw85H2EY762BOCXJZMnpuwhpA==
        """
        The additional section of the last query response should be
        """
        ns1.c.example. 3600 IN A       192.0.2.7
        ns2.c.example. 3600 IN A       192.0.2.8
        """

    Scenario: B.4. Wildcard Expansion
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for a.z.w.example. type MX should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 2
        The last query response should have nscount 5
        The last query response should have adcount 9
        The answer section of the last query response should be
        """
        a.z.w.example.	3600	IN	MX	1 ai.example.
        a.z.w.example.	3600	IN	RRSIG	MX 7 2 3600 20150420235959 20051021000000 40430 example. CikebjQwGQPwijVcxgcZcSJKtfynugtlBiKb9FcBTrmOoyQ4InoWVudh CWsh/URX3lc4WRUMivEBP6+4KS3ldA==
        """
        The authority section of the last query response should be
        """
        example.	3600	IN	NS	ns1.example.
        example.	3600	IN	NS	ns2.example.
        example.	3600	IN	RRSIG	NS 7 1 3600 20150420235959 20051021000000 40430 example. PVOgtMK1HHeSTau+HwDWC8Ts+6C8qtqd4pQJqOtdEVgg+MA+ai4fWDEh u3qHJyLcQ9tbD2vvCnMXjtz6SyObxA==
        q04jkcevqvmu85r014c7dkba38o0ji5r.example.	3600	IN	NSEC3	1 1 12 aabbccdd  r53bq7cc2uvmubfu5ocmm6pers9tk9en A RRSIG 
        q04jkcevqvmu85r014c7dkba38o0ji5r.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. hV5I89b+4FHJDATp09g4bbN0R1F845CaXpL3ZxlMKimoPAyqletMlEWw LfFia7sdpSzn+ZlNNlkxWcLsIlMmUg==
        """
        # This is slightly different from the example in RFC5155; there are
        # more RRs in the additional section.
        The additional section of the last query response should be
        """
        ai.example.		3600	IN	A	192.0.2.9
        ai.example.		3600	IN	AAAA	2001:db8::f00:baa9
        ns1.example.		3600	IN	A	192.0.2.1
        ns2.example.		3600	IN	A	192.0.2.2
        ai.example.		3600	IN	RRSIG	A 7 2 3600 20150420235959 20051021000000 40430 example. hVe+wKYMlObTRPhX0NL67GxeZfdxqr/QeR6FtfdAj5+FgYxyzPEjIzvK Wy00hWIl6wD3Vws+rznEn8sQ64UdqA==
        ai.example.		3600	IN	RRSIG	AAAA 7 2 3600 20150420235959 20051021000000 40430 example. LcdxKaCB5bGZwPDg+3JJ4O02zoMBrjxqlf6WuaHQZZfTUpb9Nf2nxFGe 2XRPfR5tpJT6GdRGcHueLuXkMjBArQ==
        ns1.example.		3600	IN	RRSIG	A 7 2 3600 20150420235959 20051021000000 40430 example. bu6kx73n6XEunoVGuRfAgY7EF/AJqHy7hj0jkiqJjB0dOrx3wuz9SaBe GfqWIdn/uta3SavN4FRvZR9SCFHF5Q==
        ns2.example.		3600	IN	RRSIG	A 7 2 3600 20150420235959 20051021000000 40430 example. ktQ3TqE0CfRfki0Rb/Ip5BM0VnxelbuejCC4zpLbFKA/7eD7UNAwxMgx JPtbdST+syjYSJaj4IHfeX6n8vfoGA==
        """

    Scenario: B.5. Wildcard No Data Error
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for a.z.w.example. type AAAA should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 8
        The last query response should have adcount 1
        The authority section of the last query response should be
        """
        example.	3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
        example.	3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
        k8udemvp1j2f7eg6jebps17vp3n8i58h.example.	3600	IN	NSEC3	1 1 12 aabbccdd  kohar7mbb8dc2ce8a9qvl8hon4k53uhi
        k8udemvp1j2f7eg6jebps17vp3n8i58h.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. FtXGbvF0+wf8iWkyo73enAuVx03klN+pILBKS6qCcftVtfH4yVzsEZqu J27NHR7ruxJWDNMtOtx7w9WfcIg62A==
        q04jkcevqvmu85r014c7dkba38o0ji5r.example.	3600	IN	NSEC3	1 1 12 aabbccdd  r53bq7cc2uvmubfu5ocmm6pers9tk9en A RRSIG 
        q04jkcevqvmu85r014c7dkba38o0ji5r.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. hV5I89b+4FHJDATp09g4bbN0R1F845CaXpL3ZxlMKimoPAyqletMlEWw LfFia7sdpSzn+ZlNNlkxWcLsIlMmUg==
        r53bq7cc2uvmubfu5ocmm6pers9tk9en.example.	3600	IN	NSEC3	1 1 12 aabbccdd  t644ebqk9bibcna874givr6joj62mlhv MX RRSIG 
        r53bq7cc2uvmubfu5ocmm6pers9tk9en.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. aupviViruXs4bDg9rCbezzBMf9h1ZlDvbW/CZFKulIGXXLj8B/fsDJar XVDA9bnUoRhEbKp+HF1FWKW7RIJdtQ==
        """

    Scenario: B.6. DS Child Zone No Data Error
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for example. type DS should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 4
        The last query response should have adcount 1
        The authority section of the last query response should be
        """
        example.	3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
        example.	3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example.	3600	IN	NSEC3	1 1 12 aabbccdd  2t7b4g4vsa5smi47k61mv5bv1a22bojr NS SOA MX RRSIG DNSKEY NSEC3PARAM 
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. OSgWSm26B+cS+dDL8b5QrWr/dEWhtCsKlwKLIBHYH6blRxK9rC0bMJPw Q4mLIuw85H2EY762BOCXJZMnpuwhpA==
        """

    #
    # Below are additional tests, not explicitely stated in RFC5155
    #

    # THIS TEST CURRENTLY FAILS: An NSEC3 record is added twice
    # See ticket #1688
    #Scenario: 7.2.2 other; Name Error where one NSEC3 covers multiple parts of proof (closest encloser)
    #    Given I have bind10 running with configuration nsec3/nsec3_auth.config
    #    A dnssec query for b.x.w.example. should have rcode NXDOMAIN
    #    The last query response should have flags qr aa rd
    #    The last query response should have edns_flags do
    #    The last query response should have ancount 0
    #    The last query response should have nscount 6
    #    The last query response should have adcount 1
    #    The authority section of the last query response should be
    #    """
    #    example.	3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
    #    example.	3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
    #    b4um86eghhds6nea196smvmlo4ors995.example.	3600	IN	NSEC3	1 1 12 aabbccdd  gjeqe526plbf1g8mklp59enfd789njgi MX RRSIG 
    #    b4um86eghhds6nea196smvmlo4ors995.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. ZkPG3M32lmoHM6pa3D6gZFGB/rhL//Bs3Omh5u4m/CUiwtblEVOaAKKZ d7S959OeiX43aLX3pOv0TSTyiTxIZg==
    #    35mthgpgcu1qg68fab165klnsnk3dpvl.example.	3600	IN	NSEC3	1 1 12 aabbccdd  b4um86eghhds6nea196smvmlo4ors995 NS DS RRSIG 
    #    35mthgpgcu1qg68fab165klnsnk3dpvl.example.	3600	IN	RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. g6jPUUpduAJKRljUsN8gB4UagAX0NxY9shwQAynzo8EUWH+z6hEIBlUT PGj15eZll6VhQqgZXtAIR3chwgW+SA==
    #    """

    # THIS TEST CURRENTLY FAILS: An NSEC3 record is added twice
    # See ticket #1688
    #Scenario: 7.2.2 other; Name Error where one NSEC3 covers multiple parts of proof (wildcard)
    #    Given I have bind10 running with configuration nsec3/nsec3_auth.config
    #    A dnssec query for a.w.example. should have rcode NXDOMAIN
    #    The last query response should have flags qr aa rd
    #    The last query response should have edns_flags do
    #    The last query response should have ancount 0
    #    The last query response should have nscount 6
    #    The last query response should have adcount 1
    #    The authority section of the last query response should be
    #    """
    #    example.		3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
    #    example.		3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
    #    k8udemvp1j2f7eg6jebps17vp3n8i58h.example. 3600 IN NSEC3	1 1 12 AABBCCDD KOHAR7MBB8DC2CE8A9QVL8HON4K53UHI
    #    k8udemvp1j2f7eg6jebps17vp3n8i58h.example. 3600 IN RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. FtXGbvF0+wf8iWkyo73enAuVx03klN+pILBKS6qCcftVtfH4yVzsEZqu J27NHR7ruxJWDNMtOtx7w9WfcIg62A==
    #    r53bq7cc2uvmubfu5ocmm6pers9tk9en.example. 3600 IN NSEC3	1 1 12 AABBCCDD T644EBQK9BIBCNA874GIVR6JOJ62MLHV MX RRSIG
    #    r53bq7cc2uvmubfu5ocmm6pers9tk9en.example. 3600 IN RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. aupviViruXs4bDg9rCbezzBMf9h1ZlDvbW/CZFKulIGXXLj8B/fsDJar XVDA9bnUoRhEbKp+HF1FWKW7RIJdtQ==
    #    """

    Scenario: Wildcard other: Wildcard name itself
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for *.w.example. type MX should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 2
        The last query response should have nscount 3
        The last query response should have adcount 9
        The answer section of the last query response should be
        """
        *.w.example.		3600	IN	MX	1 ai.example.
        *.w.example.		3600	IN	RRSIG	MX 7 2 3600 20150420235959 20051021000000 40430 example. CikebjQwGQPwijVcxgcZcSJKtfynugtlBiKb9FcBTrmOoyQ4InoWVudh CWsh/URX3lc4WRUMivEBP6+4KS3ldA==
        """
        The authority section of the last query response should be
        """
        example.		3600	IN	NS	ns1.example.
        example.		3600	IN	NS	ns2.example.
        example.		3600	IN	RRSIG	NS 7 1 3600 20150420235959 20051021000000 40430 example. PVOgtMK1HHeSTau+HwDWC8Ts+6C8qtqd4pQJqOtdEVgg+MA+ai4fWDEh u3qHJyLcQ9tbD2vvCnMXjtz6SyObxA==
        """
        The additional section of the last query response should be
        """
        ai.example.		3600	IN	A	192.0.2.9
        ai.example.		3600	IN	AAAA	2001:db8::f00:baa9
        ns1.example.		3600	IN	A	192.0.2.1
        ns2.example.		3600	IN	A	192.0.2.2
        ai.example.		3600	IN	RRSIG	A 7 2 3600 20150420235959 20051021000000 40430 example. hVe+wKYMlObTRPhX0NL67GxeZfdxqr/QeR6FtfdAj5+FgYxyzPEjIzvK Wy00hWIl6wD3Vws+rznEn8sQ64UdqA==
        ai.example.		3600	IN	RRSIG	AAAA 7 2 3600 20150420235959 20051021000000 40430 example. LcdxKaCB5bGZwPDg+3JJ4O02zoMBrjxqlf6WuaHQZZfTUpb9Nf2nxFGe 2XRPfR5tpJT6GdRGcHueLuXkMjBArQ==
        ns1.example.		3600	IN	RRSIG	A 7 2 3600 20150420235959 20051021000000 40430 example. bu6kx73n6XEunoVGuRfAgY7EF/AJqHy7hj0jkiqJjB0dOrx3wuz9SaBe GfqWIdn/uta3SavN4FRvZR9SCFHF5Q==
        ns2.example.		3600	IN	RRSIG	A 7 2 3600 20150420235959 20051021000000 40430 example. ktQ3TqE0CfRfki0Rb/Ip5BM0VnxelbuejCC4zpLbFKA/7eD7UNAwxMgx JPtbdST+syjYSJaj4IHfeX6n8vfoGA==
        """

    Scenario: Wildcard other: Wildcard name itself nodata
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for *.w.example. type A should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 4
        The last query response should have adcount 1
        The authority section of the last query response should be
        """
        example.		3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
        example.		3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
        r53bq7cc2uvmubfu5ocmm6pers9tk9en.example. 3600 IN NSEC3	1 1 12 AABBCCDD T644EBQK9BIBCNA874GIVR6JOJ62MLHV MX RRSIG
        r53bq7cc2uvmubfu5ocmm6pers9tk9en.example. 3600 IN RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. aupviViruXs4bDg9rCbezzBMf9h1ZlDvbW/CZFKulIGXXLj8B/fsDJar XVDA9bnUoRhEbKp+HF1FWKW7RIJdtQ==
        """

    Scenario: Direct query for NSEC3 record
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for 0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example. type NSEC3 should have rcode NXDOMAIN
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 8
        The last query response should have adcount 1
        The authority section of the last query response should be
        """
        example.		3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
        example.		3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example. 3600 IN NSEC3	1 1 12 AABBCCDD 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR NS SOA MX RRSIG DNSKEY NSEC3PARAM
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example. 3600 IN RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. OSgWSm26B+cS+dDL8b5QrWr/dEWhtCsKlwKLIBHYH6blRxK9rC0bMJPw Q4mLIuw85H2EY762BOCXJZMnpuwhpA==
        q04jkcevqvmu85r014c7dkba38o0ji5r.example. 3600 IN NSEC3	1 1 12 AABBCCDD R53BQ7CC2UVMUBFU5OCMM6PERS9TK9EN A RRSIG
        q04jkcevqvmu85r014c7dkba38o0ji5r.example. 3600 IN RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. hV5I89b+4FHJDATp09g4bbN0R1F845CaXpL3ZxlMKimoPAyqletMlEWw LfFia7sdpSzn+ZlNNlkxWcLsIlMmUg==
        gjeqe526plbf1g8mklp59enfd789njgi.example. 3600 IN NSEC3	1 1 12 AABBCCDD JI6NEOAEPV8B5O6K4EV33ABHA8HT9FGC A HINFO AAAA RRSIG
        gjeqe526plbf1g8mklp59enfd789njgi.example. 3600 IN RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. IVnezTJ9iqblFF97vPSmfXZ5Zozngx3KX3byLTZC4QBH2dFWhf6scrGF ZB980AfCxoD9qbbKDy+rdGIeRSVNyw==
        """

    Scenario: No data, type DS, in-zone
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for ai.example. type DS should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 4
        The last query response should have adcount 1
        The authority section of the last query response should be
        """
        example.		3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
        example.		3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
        gjeqe526plbf1g8mklp59enfd789njgi.example. 3600 IN NSEC3	1 1 12 AABBCCDD JI6NEOAEPV8B5O6K4EV33ABHA8HT9FGC A HINFO AAAA RRSIG
        gjeqe526plbf1g8mklp59enfd789njgi.example. 3600 IN RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. IVnezTJ9iqblFF97vPSmfXZ5Zozngx3KX3byLTZC4QBH2dFWhf6scrGF ZB980AfCxoD9qbbKDy+rdGIeRSVNyw==
        """

    Scenario: No data, type DS, optout delegation
        Given I have bind10 running with configuration nsec3/nsec3_auth.config
        A dnssec query for c.example. type DS should have rcode NOERROR
        The last query response should have flags qr aa rd
        The last query response should have edns_flags do
        The last query response should have ancount 0
        The last query response should have nscount 6
        The last query response should have adcount 1
        The authority section of the last query response should be
        """
        example.		3600	IN	SOA	ns1.example. bugs.x.w.example. 1 3600 300 3600000 3600
        example.		3600	IN	RRSIG	SOA 7 1 3600 20150420235959 20051021000000 40430 example. Hu25UIyNPmvPIVBrldN+9Mlp9Zql39qaUd8iq4ZLlYWfUUbbAS41pG+6 8z81q1xhkYAcEyHdVI2LmKusbZsT0Q==
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example. 3600 IN NSEC3	1 1 12 AABBCCDD 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR NS SOA MX RRSIG DNSKEY NSEC3PARAM
        0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example. 3600 IN RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. OSgWSm26B+cS+dDL8b5QrWr/dEWhtCsKlwKLIBHYH6blRxK9rC0bMJPw Q4mLIuw85H2EY762BOCXJZMnpuwhpA==
        35mthgpgcu1qg68fab165klnsnk3dpvl.example. 3600 IN NSEC3	1 1 12 AABBCCDD B4UM86EGHHDS6NEA196SMVMLO4ORS995 NS DS RRSIG
        35mthgpgcu1qg68fab165klnsnk3dpvl.example. 3600 IN RRSIG	NSEC3 7 2 3600 20150420235959 20051021000000 40430 example. g6jPUUpduAJKRljUsN8gB4UagAX0NxY9shwQAynzo8EUWH+z6hEIBlUT PGj15eZll6VhQqgZXtAIR3chwgW+SA==
        """
