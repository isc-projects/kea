// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcp/queue_control.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;

namespace {

// Verifies QueueControl essentials
TEST(QueueControl, basics) {
    QueueControlPtr control1;
    QueueControlPtr control2;

    ASSERT_NO_THROW(control1.reset(new QueueControl()));
    EXPECT_EQ(0, control1->getCapacity());

    control1->setCapacity(100);
    EXPECT_EQ(100, control1->getCapacity());

    ASSERT_NO_THROW(control2.reset(new QueueControl()));
    control2->setCapacity(200);
    EXPECT_EQ(200, control2->getCapacity());

    EXPECT_FALSE(*control1 == *control2);
    EXPECT_TRUE(*control1 != *control2);

    control2->setCapacity(100);
    EXPECT_TRUE(*control1 == *control2);
    EXPECT_FALSE(*control1 != *control2);
}

// Verifies QueueControl::toElement
TEST(QueueControl, toElement) {
    QueueControlPtr control;
    ASSERT_NO_THROW(control.reset(new QueueControl()));
    control->setQueueType("qtype");
    control->setCapacity(100);

    data::ElementPtr exp_elements;
    std::string json = "{ \"capacity\": 100, \"queue-type\": \"qtype\" }";

    ASSERT_NO_THROW(exp_elements = data::Element::fromJSON(json))
                    << "invalid JSON, test is broken";

    data::ElementPtr elements;
    ASSERT_NO_THROW(elements = control->toElement());

    ASSERT_TRUE(elements);
    EXPECT_TRUE(elements->equals(*exp_elements));
}

}
