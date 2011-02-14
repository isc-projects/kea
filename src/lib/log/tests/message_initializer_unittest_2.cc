// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id: base64_unittest.cc 2549 2010-07-20 19:09:37Z jinmei $

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

// Statically initialize the global dictionary with those messages.
// Three sets are used to check that the declaration of separate
// initializer objects really does combine the messages.
MessageInitializer init_message_initializer_unittest_3(values3);
