// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <lease_query_impl_factory.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::lease_query;

LeaseQueryImplPtr LeaseQueryImplFactory::impl_(0);

void
LeaseQueryImplFactory::createImpl(uint16_t family, ConstElementPtr config) {
    if (family == AF_INET) {
        impl_.reset(new LeaseQueryImpl4(config));
    } else {
        impl_.reset(new LeaseQueryImpl6(config));
    }
}

void
LeaseQueryImplFactory::destroyImpl() {
    impl_.reset();
}

const LeaseQueryImpl&
LeaseQueryImplFactory::getImpl() {
    if (!impl_) {
        isc_throw(Unexpected, "LeaseQueryImpl does not exist");
    }

    return (*impl_);
}

LeaseQueryImpl&
LeaseQueryImplFactory::getMutableImpl() {
    if (!impl_) {
        isc_throw(Unexpected, "LeaseQueryImpl does not exist");
    }

    return (*impl_);
}
