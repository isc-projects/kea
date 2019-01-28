// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/stamped_element.h>

namespace isc {
namespace data {

StampedElement::StampedElement()
    : timestamp_(boost::posix_time::microsec_clock::local_time()) {
}

void
StampedElement::updateModificationTime() {
    setModificationTime(boost::posix_time::microsec_clock::local_time());
}

} // end of namespace isc::data
} // end of namespace isc
