$TTL 3600
@    SOA master.example.com. admin.example.com. 1234 3600 1800 2419200 7200
        	NS dns01.example.com.
        	NS dns02.example.com.
		NS dns03.example.com.
                MX 10 mail.example.com.
                MX 20 mail.subzone.example.com.
www		A 192.168.1.1
mail            A 192.168.10.10
foo		CNAME cnametest.flame.org.
cname-int	CNAME www.example.com.
cname-ext	CNAME www.sql1.example.com.
dns01           A 192.168.2.1
dns02           A 192.168.2.2
dns03           A 192.168.2.3
insec           NS ns1.insec.example.com.
insec           NS ns2.insec.example.com.
ns1.insec  	A 192.168.4.1
ns2.insec  	A 192.168.4.2
subzone		NS ns1.subzone.example.com.
subzone		NS ns2.subzone.example.com.
ns1.subzone	A 192.168.3.1
ns2.subzone	A 192.168.3.2
*.wild		A 192.168.3.2
*.wild2		CNAME www.example.com.
*.wild3		CNAME spork.example.com.
dname		DNAME sql1.example.com.

$ORIGIN sql1.example.com.
sql1.example.com.	NS dns01.example.com.
		        NS dns02.example.com.
		        NS dns03.example.com.

$ORIGIN sql2.example.com.
sql2.example.com.	NS dns01.example.com.
		        NS dns02.example.com.
		        NS dns03.example.com.
