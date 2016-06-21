-- Copyright (C) 2016 Internet Systems Consortium.

-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at http://mozilla.org/MPL/2.0/.

DROP TABLE IF EXISTS lease4 CASCADE;
DROP TABLE IF EXISTS lease6 CASCADE;
DROP TABLE IF EXISTS lease6_types CASCADE;
DROP TABLE IF EXISTS schema_version CASCADE;
DROP TABLE IF EXISTS lease_state CASCADE;
DROP TABLE IF EXISTS dhcp4_options CASCADE;
DROP TABLE IF EXISTS dhcp6_options CASCADE;
DROP TABLE IF EXISTS ipv6_reservations CASCADE;
DROP TABLE IF EXISTS lease_hwaddr_source CASCADE;
DROP TABLE IF EXISTS host_identifier_type CASCADE;
DROP TABLE IF EXISTS dhcp_option_scope CASCADE;
DROP TABLE IF EXISTS hosts CASCADE;
DROP FUNCTION IF EXISTS lease4DumpHeader();
DROP FUNCTION IF EXISTS lease4DumpData();
DROP FUNCTION IF EXISTS lease6DumpHeader();
DROP FUNCTION IF EXISTS lease6DumpData();
