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
pkt4_finalize(const WeakCallbackData<Object, v8_pkt4>& data) {
    // This is a critical code to avoid memory leaks
    cout << "pkt4_finalize called\n";
    Local<External> field =
        Local<External>::Cast(data.GetValue()->GetInternalField(0));
    delete static_cast<v8_pkt4*>(field->Value());
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

Local<Object> make_pkt4(Isolate* isolate, Pkt4Ptr pkt) {
    // Create a stack-allocated handle scope.
    EscapableHandleScope handle_scope(isolate);

    // Catch errors
    TryCatch try_catch(isolate);

    // Generate a new instance from the template
    Local<ObjectTemplate> templ =
        Local<ObjectTemplate>::New(isolate, pkt4_template);
    Local<Object> result;
    if (!templ->NewInstance(isolate->GetCurrentContext()).ToLocal(&result)) {
        String::Utf8Value error(try_catch.Exception());
        cerr << "NewInstance failed: " << *error << "\n";
        return (handle_scope.Escape(result));
    }

    // Set the C++ part
    v8_pkt4* ccpobj(new v8_pkt4());
    ccpobj->object = pkt;
    Local<External> ptr = External::New(isolate, ccpobj);
    result->SetInternalField(0, ptr);

    // Show the new value to the garbage collector
    Persistent<Object> gcref(isolate, result);
    gcref.SetWeak<v8_pkt4>(ccpobj, pkt4_finalize);

    return (handle_scope.Escape(result));
}

void init_pkt4(Isolate* isolate) {
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
