$ORIGIN sql1.example.com.
$TTL 3600
@	SOA master.example.com. admin.example.com. 678 3600 1800 2419200 7200
	NS dns01.example.com.
	NS dns02.example.com.
	NS dns03.example.com.
www	3600 IN A 192.168.2.2
