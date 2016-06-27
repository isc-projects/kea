// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Support for kea hook in javascript v8

print("hook.js is loading");

const NEXT_STEP_CONTINUE = 0;
const NEXT_STEP_SKIP = 1;
const NEXT_STEP_DROP = 2;

function pkt4_receive(query4) {
    // pkt4_receive hook point.
    //
    // parameter: inout Pkt4Ptr query4
    // return: next step
    print("pkt4_receive: handler is called with", query4);
    return NEXT_STEP_CONTINUE;
};

print("hook.js loaded");
