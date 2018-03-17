// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>

namespace isc {
namespace netconf {

/// @brief This represents a base class for all translators
///
/// Translator is an object that receives callback notification
/// from sysrepo (in YANG format) and converts it to appropriate
/// JSON that can be sent over control channel and understood by Kea
class Translator {
 public:
    // Constructor (requires xpath to install a callback)
    Translator(const std::string& xpath);

    virtual std::string getXPath();

    // This method will be called when the callback returns.
    // Need to figure out the type used.
    void setYangData(void* data);

    // This method translates Netconf data to JSON format
    // understood by Kea.
    void translate() = 0;

    // Once setYangData is called, 
    isc::data::ElementPtr getJSON();
 protected:

    std::string xpath_;

    void * netconf_data_;

    isc::data::ElementPtr json_;
};
 

};
};
