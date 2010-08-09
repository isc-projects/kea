$ORIGIN sql2.example.com.
$TTL 3600
@	SOA master.example.com. admin.example.com. 678 3600 1800 2419200 7200
	NS dns01.example.com.
	NS dns02.example.com.
	NS dns03.example.com.
a	3600 IN A 192.168.2.1
b	3600 IN A 192.168.2.2
c	3600 IN A 192.168.2.3
d	3600 IN A 192.168.2.4
www	3600 IN A 192.168.2.5
e.f.g.h.i 3600 IN A 192.168.2.6
