// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <libplatform/libplatform.h>
#include <v8.h>

#include <hooks/external/v8/voption.h>

#include <iostream>

using namespace std;
using namespace v8;
using namespace isc::dhcp;
using namespace isc::v8;

// Contructor
v8_option::v8_option() {}

namespace { // anonymous namespace

// finalize (how to call it?)
void
option_finalize(const WeakCallbackData<Object, v8_option>& data) {
    // This is a critical code to avoid memory leaks
    cout << "option_finalize called\n";
    Local<External> field =
        Local<External>::Cast(data.GetValue()->GetInternalField(0));
    delete static_cast<v8_option*>(field->Value());
}

// toString
void
option_tostring(const FunctionCallbackInfo<Value>& info) {
    HandleScope handle_scope(info.GetIsolate());

    Local<External> field =
        Local<External>::Cast(info.Holder()->GetInternalField(0));
    v8_option* const self = static_cast<v8_option*>(field->Value());
    info.GetReturnValue().Set(
        String::NewFromUtf8(info.GetIsolate(),
                            self->object->toText().c_str(),
                            NewStringType::kNormal).ToLocalChecked());
}

} // end of anonymous namespace

namespace isc {
namespace v8 {

Global<ObjectTemplate> option_template;

Local<Object> make_option(Isolate* isolate, OptionPtr opt) {
    // Create a stack-allocated handle scope.
    EscapableHandleScope handle_scope(isolate);

    // Catch errors
    TryCatch try_catch(isolate);

    // Generate a new instance from the template
    Local<ObjectTemplate> templ =
        Local<ObjectTemplate>::New(isolate, option_template);
    Local<Object> result;
    if (!templ->NewInstance(isolate->GetCurrentContext()).ToLocal(&result)) {
        String::Utf8Value error(try_catch.Exception());
        cerr << "NewInstance failed: " << *error << "\n";
        return (handle_scope.Escape(result));
    }

    // Set the C++ part
    v8_option* ccpobj(new v8_option());
    ccpobj->object = opt;
    Local<External> ptr = External::New(isolate, ccpobj);
    result->SetInternalField(0, ptr);

    // Show the new value to the garbage collector
    Persistent<Object> gcref(isolate, result);
    gcref.SetWeak<v8_option>(ccpobj, option_finalize);

    return (handle_scope.Escape(result));
}

void init_option(Isolate* isolate) {
    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);

    // Get an object template
    Local<ObjectTemplate> templ = ObjectTemplate::New(isolate);

    // Get one field
    templ->SetInternalFieldCount(1);

    // Set Methods
    Local<Function> tostring;
    if (!Function::New(isolate->GetCurrentContext(),
                       option_tostring).ToLocal(&tostring)) {
        cerr << "can't create pkt4_tostring\n";
    }
    templ->Set(isolate, "toString", tostring);

    // Store it
    option_template.Reset(isolate, templ);
}

} // end of namespace v8
} // end of namespace isc
