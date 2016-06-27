// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT4_V8_H
#define PKT4_V8_H 1

#include <dhcp/pkt4.h>

namespace isc {
namespace v8 {

// Ocaml pkt4 class
class v8_pkt4 {
public:
    v8_pkt4();

    isc::dhcp::Pkt4Ptr object;
};

extern ::v8::Global< ::v8::ObjectTemplate> pkt4_template;

void init_pkt4_template(::v8::Isolate* isolate);

} // end of namespace v8
} // end of namespace isc

#endif // PKT4_V8_H
