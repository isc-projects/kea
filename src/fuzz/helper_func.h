// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <cc/data.h>

static const std::string JSON_CONFIG4 = R"CONFIG(
    {
        "Dhcp4":{
            "interfaces-config": {
                "interfaces": [ "eth0" ]
            },
            "lease-database": {
                "type": "memfile",
                "lfc-interval": 3600,
                "name": "/tmp/kea-leases4.csv"
            },
            "valid-lifetime": 4000,
            "subnet4": [{
                "pools": [ { "pool":  "192.0.2.1 - 192.0.2.200" } ],
                "id": 1,
                "subnet": "192.0.2.0/24",
                "interface": "eth0"
            }],
            "loggers": [{
                "name": "kea-dhcp4",
                "output-options": [{
                    "output": "stdout"
                }],
                "severity": "INFO"
            }]
        }
    })CONFIG";

static const std::string JSON_CONFIG6 = R"CONFIG(
    {
        "Dhcp6": {
            "interfaces-config": {
                "interfaces": [ "eth0" ]
            },
            "option-data": [{
                "name": "dns-servers",
                "data": "2001:db8::1, 2001:db8::2"
            }],
            "lease-database": {
                "type": "memfile",
                "lfc-interval": 3600,
                "name": "/tmp/kea-leases6.csv"
            }
        }
    })CONFIG";

static const std::string LEASE4 = R"LEASE(
address,hwaddr,client_id,valid_lifetime,expire,subnet_id,fqdn_fwd,fqdn_rev,hostname,state,user_context,pool_id
192.0.2.10,32:30,33:30,40,1642000000,50,1,1,one.example.com,0,,0
192.0.2.11,,31:32:33,40,1643210000,50,1,1,,1,{  },0
192.0.2.12,32:32,,40,1643212345,50,1,1,three&#x2cexample&#x2ccom,2,{ "a": 1&#x2c "b": "c" },0
192.0.2.13,aa:bb:cc:dd:ee:01,01:23:45:67:89:ab,86400,1767225600,1,1,1,host1.example.test,0,{  },0
)LEASE";

static const std::string LEASE6 = R"LEASE(
address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,state,user_context,hwtype,hwaddr_source,pool_id
::10,32:30:33,30,1642000000,40,50,1,60,128,1,1,one.example.com,38:30,0,,90,16,0
::11,32:31:33,30,1643210000,40,50,1,60,128,1,1,,38:30,1,{  },90,1,0
::12,32:32:33,30,1643212345,40,50,1,60,128,1,1,three&#x2cexample&#x2ccom,38:30,2,{ "a": 1&#x2c "b": "c" },90,4,0
2001:db8::100,00:01:00:01:12:34:56:78:aa:bb:cc:dd,86400,1767225600,1,43200,0,1,128,1,1,host1v6.example.test,aa:bb:cc:dd:ee:01,0,{  },1,1,0
)LEASE";

static const std::string USER = R"USER({ "type" : "HW_ADDR", "id" : "01AC00F03344", "opt1" : "true" }
{ "type" : "HW_ADDR", "id" : "01:AC:00:F0:33:45", "opt1" : "true" }
{ "type" : "DUID", "id" : "225060de0a0b", "opt1" : "true" }
{ "type" : "DUID", "id" : "22:50:60:de:0a:0c", "opt1" : "true" })USER";

namespace fuzz {
    std::string writeTempConfig(bool isV4);
    std::string writeTempLease(bool isV4);
    std::string writeTempUserFile();
    std::string writeTempFile(const std::string& payload, const char* suffix = "json", const std::string& explicit_path = "");
    void deleteTempFile(std::string file_path);
    isc::data::ElementPtr parseJSON(const std::string& s);
}
