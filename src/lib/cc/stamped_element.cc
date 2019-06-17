// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/stamped_element.h>

namespace isc {
namespace data {

StampedElement::StampedElement()
    : BaseStampedElement(), server_tags_() {
}

bool
StampedElement::hasServerTag(const ServerTag& server_tag) const {
    for (auto tag : server_tags_) {
        if (tag.get() == server_tag.get()) {
            return (true);
        }
    }
    return (false);
}

bool
StampedElement::hasAllServerTag() const {
    return (hasServerTag(ServerTag(ServerTag::ALL)));
}


ElementPtr
StampedElement::getMetadata() const {
    ElementPtr metadata = Element::createMap();
    ElementPtr tags = Element::createList();

    for (auto server_tag : server_tags_) {
        tags->add(Element::create(server_tag.get()));
    }

    metadata->set("server-tags", tags);
    return (metadata);
}

} // end of namespace isc::data
} // end of namespace isc
