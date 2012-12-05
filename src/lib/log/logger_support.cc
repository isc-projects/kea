// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
// PERFORMANCE OF THIS SOFTWARE

#include <string>
#include <log/logger_support.h>
#include <log/logger_manager.h>

using namespace std;

namespace {

// Flag to hold logging initialization state.
bool logging_init_state = false;

} // Anonymous namespace

namespace isc {
namespace log {

// Return initialization state.
bool
isLoggingInitialized() {
    return (logging_init_state);
}

// Set initialization state.  (Note: as logging can be initialized via a direct
// call to LoggerManager::init(), this function is called from there, not from
// the initialization functions in this file.
void
setLoggingInitialized(bool state) {
    logging_init_state = state;
}

// Logger Run-Time Initialization.

void
initLogger(const string& root, isc::log::Severity severity, int dbglevel,
           const char* file, bool buffer) {
    LoggerManager::init(root, severity, dbglevel, file, buffer);
}

} // namespace log
} // namespace isc
