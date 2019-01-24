-- Copyright (C) 2016-2018 Internet Systems Consortium.
--
-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at http://mozilla.org/MPL/2.0/.

-- This is the soft wipe script for CQL (Cassandra). This capability may be
-- used when running Cassandra unit-tests.
--
-- In some deployments (e.g. in case of Tomek's dev system) Cassandra tests take
-- a very long time to execute. This was traced back to slow table/indexes
-- creation/deletion. With full wipe and recreation of all structures, it
-- took over 60 seconds for each test to execute. To avoid this problem, a
-- feature called soft-wipe has been implemented. If enabled, it does not
-- remove the structures, just the data from essential tables. To enable
-- it set KEA_TEST_CASSANDRA_WIPE environment variable to 'soft'. Make sure
-- that the database schema is set up properly before running in soft-wipe
-- mode.

TRUNCATE TABLE lease4;
TRUNCATE TABLE lease6;
TRUNCATE TABLE lease6_types;
TRUNCATE TABLE lease_hwaddr_source;
TRUNCATE TABLE lease_state;
TRUNCATE TABLE host_reservations;
TRUNCATE TABLE logs;
