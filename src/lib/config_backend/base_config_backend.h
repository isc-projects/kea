// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_CONFIG_BACKEND_H
#define BASE_CONFIG_BACKEND_H

#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace cb {

class BaseConfigBackend {
public:


    virtual ~BaseConfigBackend() {
    }

    virtual std::string getType() const = 0;

    virtual std::string getHost() const = 0;

    virtual uint16_t getPort() const = 0;
};

typedef boost::shared_ptr<BaseConfigBackend> BaseConfigBackendPtr;

} // end of namespace isc::cb
} // end of namespace isc

#endif // BASE_CONFIG_BACKEND_H
