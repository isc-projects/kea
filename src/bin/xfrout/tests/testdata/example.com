;; This is the source of a zone stored in test.sqlite3.  It's provided
;; for reference purposes only.
example.com.         3600  IN  SOA a.dns.example.com. mail.example.com. 1 1 1 1 1
example.com.         3600  IN  NS  a.dns.example.com.
a.dns.example.com.   3600  IN  A    192.0.2.1
a.dns.example.com.   7200  IN  A    192.0.2.2
