$TTL 3600
@    SOA ns.example.com. admin.example.com. 1234 3600 1800 2419200 7200
        	NS ns.example.com.
ns.example.com.	A 192.0.2.1

;; bogus RDATA for CNAME RR, but the loadzone tool accepts it.  looking up this
;; record will trigger an exception.
broken.example.com. CNAME 0123456789012345678901234567890123456789012345678901234567890123456789.example.com.
