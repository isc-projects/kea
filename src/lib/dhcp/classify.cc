// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/classify.h>
#include <util/strutil.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <vector>

namespace isc {
namespace dhcp {

ClientClasses::ClientClasses(const std::string& class_names)
    : std::set<ClientClass>() {
    std::vector<std::string> split_text;
    boost::split(split_text, class_names, boost::is_any_of(","),
                 boost::algorithm::token_compress_off);
    for (size_t i = 0; i < split_text.size(); ++i) {
        std::string trimmed = util::str::trim(split_text[i]);
        // Ignore empty class names.
        if (!trimmed.empty()) {
            insert(ClientClass(trimmed));
        }
    }
}
    
} // end of namespace isc::dhcp
} // end of namespace isc

