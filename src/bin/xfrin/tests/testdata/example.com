;; This is a simplest form of zone file for 'example.com', which is the
;; source of the corresponding sqlite3 DB file.  This file is provided
;; for reference purposes only; it's not actually used anywhere.

example.com.		3600	IN SOA	master.example.com. admin.example.com. (
					1230       ; serial
					3600       ; refresh (1 hour)
					1800       ; retry (30 minutes)
					2419200    ; expire (4 weeks)
					7200       ; minimum (2 hours)
					)
			3600	NS	dns01.example.com.
			3600	NS	dns02.example.com.
			3600	NS	dns03.example.com.
dns01.example.com.	3600	IN A	192.0.2.1
dns02.example.com.	3600	IN A	192.0.2.2
dns03.example.com.	3600	IN A	192.0.2.3
