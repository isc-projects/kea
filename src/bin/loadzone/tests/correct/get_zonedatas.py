from isc.datasrc import sqlite3_ds
import sys
ZONE_FILE = sys.argv[1]
zonename_set = ["include.", "ttl1.", "ttl2.", "mix1.", "mix2.", "ttlext.", "example.com.", "comment.example.com."]
for zone_name in zonename_set:
    for rr_data in sqlite3_ds.get_zone_datas(zone_name, ZONE_FILE):
        data_len = len(rr_data[2])
        sys.stdout.write(rr_data[2] + '\t\t' + str(rr_data[4]) + '\tIN\t' + rr_data[5] + '\t' + rr_data[7] + '\n')
