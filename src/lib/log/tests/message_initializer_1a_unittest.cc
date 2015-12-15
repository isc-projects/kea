// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// The sole purpose of this file is to provide a set of message definitions
// in a separate compilation unit from the one in which their presence is
// checked.  This tests that merely declaring the MessageInitializer object
// is enough to include the definitions in the global dictionary.

#include <log/message_initializer.h>

using namespace isc::log;

// Declare a set of messages to go into the global dictionary.

namespace {

const char* values3[] = {
    "GLOBAL5", "global message five",
    "GLOBAL6", "global message six",
    NULL
};

}

// Register the messages for loading into the global dictionary
const MessageInitializer init_message_initializer_unittest_3(values3);
