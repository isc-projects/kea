;; This is the source of a zone stored in test.sqlite3.  It's provided
;; for reference purposes only.
example.com.         1000  IN  SOA a.dns.example.com. mail.example.com. 1 1 1 1 1
example.com.         1000  IN  NS  a.dns.example.com.
example.com.         1000  IN  NS  b.dns.example.com.
example.com.         1000  IN  NS  c.dns.example.com.
a.dns.example.com.   1000  IN  A    1.1.1.1
b.dns.example.com.   1000  IN  A    3.3.3.3
b.dns.example.com.   1000  IN  AAAA 4:4::4:4
b.dns.example.com.   1000  IN  AAAA 5:5::5:5
