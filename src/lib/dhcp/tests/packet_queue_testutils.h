// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKET_QUEUE_TESTUTILS_H
#define PACKET_QUEUE_TESTUTILS_H

#include <config.h>

#include <dhcp/packet_queue.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

namespace isc {
namespace dhcp {
namespace test {

template<typename PacketQueuePtrType>
void checkInfo(PacketQueuePtrType queue, const std::string& exp_json) {
    ASSERT_TRUE(queue) << "packet queue ptr is null";
    // Fetch the queue info and verify it has all the expected values.
    data::ElementPtr info;
    ASSERT_NO_THROW(info  = queue->getInfo());
    ASSERT_TRUE(info);
    data::ElementPtr exp_elems;
    ASSERT_NO_THROW(exp_elems = data::Element::fromJSON(exp_json)) <<
        " exp_elems is invalid JSON : " << exp_json << " test is broken";
    EXPECT_TRUE(exp_elems->equals(*info));
}

#define CHECK_QUEUE_INFO(queue, stream) \
    { \
        std::ostringstream oss__; \
        oss__ << stream; \
        checkInfo(queue, oss__.str().c_str());\
    }


template<typename PacketQueuePtrType>
void checkIntStat(PacketQueuePtrType queue, const std::string& name, size_t exp_value) {
    ASSERT_TRUE(queue) << "packet queue ptr is null";
    data::ElementPtr info;
    ASSERT_NO_THROW(info  = queue->getInfo());
    ASSERT_TRUE(info);

    data::ConstElementPtr elem;
    ASSERT_NO_THROW(elem = info->get(name)) << "stat: " << name << " not in info" << std::endl;
    ASSERT_TRUE(elem);

    int64_t value = 0;
    ASSERT_NO_THROW(value = elem->intValue());
    EXPECT_EQ(exp_value, value) << "stat: " << name << " is wrong" << std::endl;;
}

extern data::ElementPtr makeQueueConfig(const std::string& queue_type, size_t capacity, bool enable_queue=true);

}  // namespace test
}  // namespace dhcp
}  // namespace isc

#endif // PACKET_QUEUE_TESTUTILS_H
