// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.



#include <config.h>
#include <netconf/translator.h>

namespace isc {
namespace netconf {

Translator::Translator(const std::string& xpath)
    :xpath_(xpath), netconf_data_(0) {

};

std::string Translator::getXPath() {
    return (xpath_);
}

isc::data::ElementPtr Translator::getJSON() {
    return (json_);
}

};
};
