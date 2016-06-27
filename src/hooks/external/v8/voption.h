// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_V8_H
#define OPTION_V8_H 1

#include <dhcp/option.h>

namespace isc {
namespace v8 {

// Ocaml option class
class v8_option {
public:
    v8_option();

    isc::dhcp::OptionPtr object;
};

::v8::Local< ::v8::Object> make_option(::v8::Isolate* isolate,
                                       isc::dhcp::OptionPtr opt);

void init_option(::v8::Isolate* isolate);

} // end of namespace v8
} // end of namespace isc

#endif // OPTION_V8_H
