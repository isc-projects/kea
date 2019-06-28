// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <database/server_selector.h>
#include <exceptions/exceptions.h>

using namespace isc::data;

namespace isc {
namespace db {

ServerSelector
ServerSelector::MULTIPLE(const std::set<std::string>& server_tags) {
    if (server_tags.empty()) {
        isc_throw(InvalidOperation, "ServerSelector: expecting at least one"
                  " server tag");
    }

    std::set<ServerTag> tags;

    // Create a set of tags from strings.
    for (auto tag : server_tags) {
        tags.insert(ServerTag(tag));
    }

    ServerSelector selector(tags);
    return (selector);
}

ServerSelector::ServerSelector(const Type& type)
    : type_(type), tags_() {
    if (type_ == Type::ALL) {
        tags_.insert(ServerTag());
    }
}

ServerSelector::ServerSelector(const ServerTag& server_tag)
    : type_(server_tag.amAll() ? Type::ALL : Type::SUBSET), tags_({server_tag}) {
}

ServerSelector::ServerSelector(const std::set<ServerTag>& server_tags)
    : type_(Type::SUBSET), tags_(server_tags) {
}

} // end of namespace isc::db
} // end of namespace isc
