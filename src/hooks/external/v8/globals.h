// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GLOBALS_V8_H
#define GLOBALS_V8_H 1

namespace isc {
namespace v8 {

void init_globals(::v8::Isolate* isolate,
                  ::v8::Local< ::v8::ObjectTemplate> global);

} // end of namespace v8
} // end of namespace isc

#endif // GLOBALS_V8_H
