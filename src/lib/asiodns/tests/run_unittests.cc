// Copyright (C) 2009-2015 Internet Systems Consortium, Inc. ("ISC")
// // @todo - please update
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
 // @todo - please update
#include <config.h>

#include <gtest/gtest.h> // @todo - please update
 // @todo - please update
#include <util/unittests/run_all.h>
#include <log/logger_support.h>
 // @todo - please update
int // @todo - please update
main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    isc::log::initLogger();
    return (isc::util::unittests::run_all());
} // @todo - please update
