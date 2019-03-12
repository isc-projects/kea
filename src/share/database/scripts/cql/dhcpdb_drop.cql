-- Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
-- Copyright (C) 2015-2017 Deutsche Telekom AG.

-- Author: Razvan Becheriu <razvan.becheriu@qualitance.com>

-- Licensed under the Apache License, Version 2.0 (the "License");
-- you may not use this file except in compliance with the License.
-- You may obtain a copy of the License at

--           http://www.apache.org/licenses/LICENSE-2.0

-- Unless required by applicable law or agreed to in writing, software
-- distributed under the License is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
-- See the License for the specific language governing permissions and
-- limitations under the License.

DROP TABLE IF EXISTS lease4;
DROP TABLE IF EXISTS lease6;
DROP TABLE IF EXISTS lease6_types;
DROP TABLE IF EXISTS lease_hwaddr_source;
DROP TABLE IF EXISTS lease_state;
DROP TABLE IF EXISTS schema_version;
DROP TABLE IF EXISTS hosts;
DROP TABLE IF EXISTS dhcp4_options;
DROP TABLE IF EXISTS dhcp6_options;
DROP TABLE IF EXISTS host_identifier_type;
DROP TABLE IF EXISTS dhcp_option_scope;
DROP TABLE IF EXISTS logs;

DROP INDEX IF EXISTS lease4index1;
DROP INDEX IF EXISTS lease4index2;
DROP INDEX IF EXISTS lease4index3;
DROP INDEX IF EXISTS lease4index4;
DROP INDEX IF EXISTS lease4index5;

DROP INDEX IF EXISTS lease6index1;
DROP INDEX IF EXISTS lease6index2;
DROP INDEX IF EXISTS lease6index3;
DROP INDEX IF EXISTS lease6index4;
DROP INDEX IF EXISTS lease6index5;
DROP INDEX IF EXISTS lease6index6;

DROP INDEX IF EXISTS hostsindex1;
DROP INDEX IF EXISTS hostsindex2;
DROP INDEX IF EXISTS hostsindex3;
DROP INDEX IF EXISTS hostsindex4;
DROP INDEX IF EXISTS hostsindex5;
DROP INDEX IF EXISTS hostsindex6;
DROP INDEX IF EXISTS hostsindex7;

DROP INDEX IF EXISTS logsindex;
