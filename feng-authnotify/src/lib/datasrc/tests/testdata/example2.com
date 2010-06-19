;; This is an incomplete zone file, but should be okay for testing purposes.
example2.com.		3600	IN SOA	master.example2.com. admin.example2.com. (
					1234       ; serial
					3600       ; refresh (1 hour)
					1800       ; retry (30 minutes)
					2419200    ; expire (4 weeks)
					7200       ; minimum (2 hours)
					)
