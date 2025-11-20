// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/fd_event_handler_factory.h>

#include <gtest/gtest.h>
#include <sys/select.h>

using namespace isc;
using namespace isc::util;

namespace {

// This test verifies if the constructors are working as expected
// and process passed parameters.
TEST(FDEventHandlerFactory, factory) {
    FDEventHandlerPtr handler = FDEventHandlerFactory::factoryFDEventHandler();
    if (handler->type() == FDEventHandler::TYPE_SELECT) {
        EXPECT_THROW(handler->add(FD_SETSIZE), BadValue);
        EXPECT_THROW(handler->readReady(FD_SETSIZE), BadValue);
        EXPECT_THROW(handler->hasError(FD_SETSIZE), BadValue);
    } else {
        EXPECT_NO_THROW(handler->add(FD_SETSIZE));
    }
}

} // end of anonymous namespace
