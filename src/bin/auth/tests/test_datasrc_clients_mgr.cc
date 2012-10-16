// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include "test_datasrc_clients_mgr.h"

namespace isc {
namespace auth {
// Define static DataSrcClientsBuilder member variables.
bool FakeDataSrcClientsBuilder::started = false;
std::list<internal::Command>* FakeDataSrcClientsBuilder::command_queue = NULL;
internal::TestCondVar* FakeDataSrcClientsBuilder::cond = NULL;
internal::TestMutex* FakeDataSrcClientsBuilder::queue_mutex = NULL;
bool FakeDataSrcClientsBuilder::thread_waited = false;
bool FakeDataSrcClientsBuilder::thread_throw_on_wait = false;

namespace internal {
template<>
void
TestDataSrcClientsBuilder::doNoop() {
    ++queue_mutex_->noop_count;
    switch (queue_mutex_->throw_from_noop) {
    case TestMutex::NONE:
        break;                  // no throw
    case TestMutex::EXCLASS:
        isc_throw(Exception, "test exception");
    case TestMutex::INTEGER:
        throw 42;
    }
}
}
}
}

// Local Variables:
// mode: c++
// End:
