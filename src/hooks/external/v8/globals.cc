// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <libplatform/libplatform.h>
#include <v8.h>

#include <hooks/external/v8/globals.h>

#include <iostream>

using namespace std;
using namespace v8;
using namespace isc::v8;

namespace { // anonymous namespace

// Convert a C++ string to a v8 String
Local<String> StringToObject(Isolate* isolate, const string& cpps) {
    EscapableHandleScope handle_scope(isolate);

    Local<String> v8s =
        String::NewFromUtf8(isolate, cpps.c_str(),
                            NewStringType::kNormal).ToLocalChecked();
    return (handle_scope.Escape(v8s));
}

// Convert a v8 String to a C++ UTF8 string
string ObjectToString(Local<String> value) {
    int len = value->Utf8Length();
    char* str = new char[len + 1];
    value->WriteUtf8(str);
    string result(str);
    delete [] str;
    return (result);
}

// Print
void Print(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    for (int i = 0; i < args.Length(); ++i) {
        HandleScope handle_scope(isolate);

        if (i != 0) {
            cout << " ";
        }

        // toString() can raise errors
        TryCatch try_catch(isolate);

        Local<Value> arg = args[i];
        Local<String> str;

        // Defer symbols
        if (arg->IsSymbol()) {
            arg = Local<Symbol>::Cast(arg)->Name();
        }

        // Get v8 string
        if (!arg->ToString(isolate->GetCurrentContext()).ToLocal(&str)) {
            try_catch.ReThrow();
            return;
        }

        cout << ObjectToString(str);
    }
    cout << "\n";
}

} // end of anonymous namespace

namespace isc {
namespace v8 {

void init_globals(Isolate* isolate, Local<ObjectTemplate> global) {
    global->Set(StringToObject(isolate, "print"),
                FunctionTemplate::New(isolate, Print));
}

} // end of namespace v8
} // end of namespace isc
