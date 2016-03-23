// Copyright (C) 2014-2016 Internet Systems Consortium, Inc. ("ISC")
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
#include <sstream>
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

std::string
ClientClasses::toText(const std::string& separator) const {
    std::stringstream s;
    for (const_iterator class_it = begin(); class_it != end(); ++class_it) {
        if (class_it != begin()) {
            s << separator;
        }
        s << *class_it;
    }
    return (s.str());
}
    
} // end of namespace isc::dhcp
} // end of namespace isc

