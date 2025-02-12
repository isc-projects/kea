// Copyright (C) 2020-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_QUERY_IMPL_FACTORY_H
#define LEASE_QUERY_IMPL_FACTORY_H

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <lease_query_impl4.h>
#include <lease_query_impl6.h>

namespace isc {
namespace lease_query {

class LeaseQueryImplFactory {
public:

    /// @brief Creates the LeaseQueryImpl singleton
    /// @param family protocol family to support (AF_INET or AF_INET6)
    /// @param config config parameters to use
    static void createImpl(uint16_t family, isc::data::ConstElementPtr config);

    /// @brief Destroy the LeaseQueryImpl singleton
    static void destroyImpl();

    /// @brief Fetch the LeaseQueryImpl singleton
    /// @return a reference to the singleton
    /// @throw Unexpected if no instance exists.
    static const LeaseQueryImpl& getImpl();

    /// @brief Fetch the LeaseQueryImpl singleton
    /// @return a reference to the singleton
    /// @throw Unexpected if no instance exists.
    static LeaseQueryImpl& getMutableImpl();

private:

    /// @brief LeaseQueryImpl singleton.
    static LeaseQueryImplPtr impl_;
};

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // LEASE_QUERY_IMPL_FACTORY_H
