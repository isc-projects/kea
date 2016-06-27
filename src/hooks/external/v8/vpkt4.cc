// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <libplatform/libplatform.h>
#include <v8.h>

#include <hooks/external/v8/voption.h>
#include <hooks/external/v8/vpkt4.h>

#include <iostream>

using namespace std;
using namespace v8;
using namespace isc::dhcp;
using namespace isc::v8;

// Contructor
v8_pkt4::v8_pkt4() {}

namespace { // anonymous namespace

// finalize (how to call it?)
void
pkt4_finalize(Local<Object> obj) {
    // This is a critical code to avoid memory leaks
    cout << "pkt4_finalize called\n";
    Local<External> field = Local<External>::Cast(obj->GetInternalField(0));
    v8_pkt4* const self = static_cast<v8_pkt4*>(field->Value());
    self->object.reset();
    delete self;
}

// toString
void
pkt4_tostring(const FunctionCallbackInfo<Value>& info) {
    HandleScope handle_scope(info.GetIsolate());

    Local<External> field =
        Local<External>::Cast(info.Holder()->GetInternalField(0));
    v8_pkt4* const self = static_cast<v8_pkt4*>(field->Value());
    info.GetReturnValue().Set(
        String::NewFromUtf8(info.GetIsolate(),
                            self->object->toText().c_str(),
                            NewStringType::kNormal).ToLocalChecked());
}

} // end of anonymous namespace

namespace isc {
namespace v8 {

Global<ObjectTemplate> pkt4_template;

void init_pkt4_template(Isolate* isolate) {
    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);

    // Get an object template
    Local<ObjectTemplate> templ = ObjectTemplate::New(isolate);

    // Get one field
    templ->SetInternalFieldCount(1);

    // Set Methods
    Local<Function> tostring;
    if (!Function::New(isolate->GetCurrentContext(),
                       pkt4_tostring).ToLocal(&tostring)) {
        cerr << "can't create pkt4_tostring\n";
    }
    templ->Set(isolate, "toString", tostring);

    // Store it
    pkt4_template.Reset(isolate, templ);
}

} // end of namespace v8
} // end of namespace isc
