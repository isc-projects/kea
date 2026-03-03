// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// This file should contain only empty LLVMFuzzer.* functions for harnesses contributed externally that did not define
// them to begin with.

#include <config.h>
#include <fuzz.h>

int
LLVMFuzzerInitialize() {
    return 0;
}

int
LLVMFuzzerTearDown() {
    return 0;
}
