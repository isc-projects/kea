// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Async callout library
///
/// This is source of a test library for testing a "parking" feature, i.e.
/// the callouts can schedule asynchronous operation and indicate that the
/// packet should be parked until the asynchronous operation completes and
/// the hooks library indicates that packet processing should be resumed.

#include <config.h>
#include <hooks/hooks.h>
#include <hooks/parking_lots.h>
#include <log/logger.h>
#include <log/macros.h>
#include <log/message_initializer.h>
#include <algorithm>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

using namespace isc::hooks;
using namespace isc::log;
using namespace std;

namespace {

/// @brief Logger used by the library.
isc::log::Logger logger("acl");

/// @brief Log messages.
const char* log_messages[] = {
    "ACL_LOAD_START", "async callout load %1",
    "ACL_LOAD_END", "async callout load end",
    "ACL_LOAD_END", "duplicate of async callout load end",
    NULL
};

/// @brief Initializer for log messages.
const MessageInitializer message_initializer(log_messages);

/// @brief Simple callback which unparks parked object.
///
/// @param parking_lot parking lot where the object is parked.
/// @param parked_object parked object.
void unpark(ParkingLotHandlePtr parking_lot, const std::string& parked_object) {
    parking_lot->unpark(parked_object);
}

} //  end of anonymous namespace

extern "C" {

/// @brief Callout scheduling object parking and providing function to unpark
///        it.
///
/// This callout is crafted to test the following scenario. The callout returns
/// status "park" to indicate that the packet should be parked. The callout
/// performs asynchronous operation and indicates that the packet should be
/// unparked when this operation completes. Unparking the packet triggers a
/// function associated with the parked packet, e.g. a function which continues
/// processing of this packet.
///
/// This test callout "parks" a string object instead of a packet. It assumes
/// that there might be multiple callouts installed on this hook point, which
/// all trigger asynchronous operation. The object must be unparked when the
/// last asynchronous operation completes. Therefore, it calls the @c reference
/// function on the parking lot object to increase the reference count. The
/// object remains parked as long as the reference counter is greater than
/// 0.
///
/// The callout returns 1 or more pointers to the functions which should be
/// called by the unit tests to simulate completion of the asynchronous tasks.
/// When the test calls those functions, @c unpark function is called, which
/// decreases reference count on the parked object, or actually unparks the
/// object when the reference count reaches 0.
///
/// @param handle Reference to callout handle used to set/get arguments.
int
hookpt_one(CalloutHandle& handle) {
    // Using a string as "parked" object.
    std::string parked_object;
    handle.getArgument("parked_object", parked_object);

    // Retrieve the parking lot handle for this hook point. It allows for
    // increasing a reference count on the parked object and also for
    // scheduling packet unparking.
    ParkingLotHandlePtr parking_lot = handle.getParkingLotHandlePtr();

    // Increase the reference count to indicate that this callout needs the
    // object to remain parked until the asynchronous operation completes.
    // Otherwise, other callouts could potentially call unpark and cause the
    // packet processing to continue before the asynchronous operation
    // completes.
    parking_lot->reference(parked_object);

    // Create pointer to the function that the test should call to simulate
    // completion of the asynchronous operation scheduled by this callout.
    std::function<void()> unpark_trigger_func =
        std::bind(unpark, parking_lot, parked_object);

    // Every callout (if multiple callouts installed on this hook point) should
    // return the function pointer under unique name. The base name is
    // "unpark_trigger" and the callouts append consecutive numbers to this
    // base name, e.g. "unpark_trigger1", "unpark_trigger2" etc.

    std::string fun_name;
    std::vector<std::string> args = handle.getArgumentNames();
    unsigned i = 1;
    do {
        std::ostringstream candidate_name;
        candidate_name << "unpark_trigger" << i;
        if (std::find(args.begin(), args.end(), candidate_name.str()) ==
            args.end()) {
            fun_name = candidate_name.str();

        } else {
            ++i;
        }
    } while (fun_name.empty());

    handle.setArgument(fun_name, unpark_trigger_func);

    handle.setStatus(CalloutHandle::NEXT_STEP_PARK);

    return (0);
}

// Framework functions.

int
version() {
    return (KEA_HOOKS_VERSION);
}

// load() initializes the user library if the main image was statically linked.
int
load(isc::hooks::LibraryHandle&) {
#ifdef USE_STATIC_LINK
    hooksStaticLinkInit();
#endif
    LOG_INFO(logger, "ACL_LOAD_START").arg("argument");
    LOG_INFO(logger, "ACL_LOAD_END");
    return (0);
}

}

