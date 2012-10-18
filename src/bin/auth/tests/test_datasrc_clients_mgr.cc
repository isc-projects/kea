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
#include <auth/datasrc_config.h>

#include "test_datasrc_clients_mgr.h"

namespace isc {
namespace auth {
namespace datasrc_clientmgr_internal {

// Define static DataSrcClientsBuilder member variables.
bool FakeDataSrcClientsBuilder::started = false;
std::list<Command>* FakeDataSrcClientsBuilder::command_queue = NULL;
std::list<Command> FakeDataSrcClientsBuilder::command_queue_copy;
TestCondVar* FakeDataSrcClientsBuilder::cond = NULL;
TestCondVar FakeDataSrcClientsBuilder::cond_copy;
TestMutex* FakeDataSrcClientsBuilder::queue_mutex = NULL;
isc::datasrc::DataSrcClientListsPtr*
    FakeDataSrcClientsBuilder::clients_map = NULL;
TestMutex* FakeDataSrcClientsBuilder::map_mutex = NULL;
TestMutex FakeDataSrcClientsBuilder::queue_mutex_copy;
bool FakeDataSrcClientsBuilder::thread_waited = false;
FakeDataSrcClientsBuilder::ExceptionFromWait
FakeDataSrcClientsBuilder::thread_throw_on_wait =
    FakeDataSrcClientsBuilder::NOTHROW;

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
} // namespace datasrc_clientmgr_internal

template<>
void
TestDataSrcClientsMgr::cleanup() {
    using namespace datasrc_clientmgr_internal;
    // Make copy of some of the manager's member variables and reset the
    // corresponding pointers.  The currently pointed objects are in the
    // manager object, which are going to be invalidated.

    FakeDataSrcClientsBuilder::command_queue_copy = command_queue_;
    FakeDataSrcClientsBuilder::command_queue =
        &FakeDataSrcClientsBuilder::command_queue_copy;
    FakeDataSrcClientsBuilder::queue_mutex_copy = queue_mutex_;
    FakeDataSrcClientsBuilder::queue_mutex =
        &FakeDataSrcClientsBuilder::queue_mutex_copy;
    FakeDataSrcClientsBuilder::cond_copy = cond_;
    FakeDataSrcClientsBuilder::cond =
        &FakeDataSrcClientsBuilder::cond_copy;
}

} // namespace auth
} // namespace isc

// Local Variables:
// mode: c++
// End:
