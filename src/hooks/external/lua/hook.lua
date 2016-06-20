-- Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
--
-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at http://mozilla.org/MPL/2.0/.

-- Support for Kea hook in lua

print("hook.lua is loading")

-- require kea

NEXT_STEP_CONTINUE = 0
NEXT_STEP_SKIP = 1
NEXT_STEP_DROP = 2

-- pkt4_receive hook point
--
-- parameter: inout Pkt4Ptr query4 
-- return: next step

function pkt4_receive(query4)
    print("pkt4_receive: handler is called with", tostring(query4))
    return NEXT_STEP_CONTINUE
end

print("hook.lua loaded")
