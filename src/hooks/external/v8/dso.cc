// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <libplatform/libplatform.h>
#include <v8.h>

#include <exceptions/exceptions.h>
#include <hooks/hooks.h>

#include <hooks/external/v8/globals.h>
#include <hooks/external/v8/voption.h>
#include <hooks/external/v8/vpkt4.h>

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
using namespace v8;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::v8;

namespace {
    // Platform
    Platform* platform_ = NULL;

    // Isolate
    Isolate* isolate_ = NULL;

    // Pkt4 receive handler
    Global<Function> pkt4_rcv_hndl;

    // Allocator
    class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
    public:
        virtual void* Allocate(size_t length) {
            void* data = AllocateUninitialized(length);
            return data == NULL ? data : memset(data, 0, length);
        }

        virtual void* AllocateUninitialized(size_t length) {
            return malloc(length);
        }

        virtual void Free(void* data, size_t) {
            free(data);
        }
    };

    // Fatal Error Handler
    void fatal_error_handler(const char* location, const char* message) {
        ostringstream oss;
        oss << "V8 crashed because " << message << " at " << location;
        isc_throw(isc::Unexpected, oss.str().c_str());
    }
};

extern "C" {

// Framework functions

// version
int version() {
    return (KEA_HOOKS_VERSION);
}

// load
int load(LibraryHandle& handle) {
    // Set the program name (default "kea")
    ConstElementPtr program = handle.getParameter("program");
    string progname = "kea";
    if (program && program->getType() == Element::string) {
        progname = program->stringValue();
    } else {
        cout << "no \"program\" parameter: using \"kea\"\n";
    }

    // Get the script module name (default "hook.js")
    ConstElementPtr script_param = handle.getParameter("script");
    string script_name = "hook.js";
    if (script_param && script_param->getType() == Element::string) {
        script_name = script_param->stringValue();
    } else {
        cout << "no \"script\" parameter: using \"hook.js\"\n";
    }

    // Read the script
    int fd = open(script_name.c_str(), O_RDONLY);
    if (fd < 0) {
        cerr << "open(" << script_name << ") failed: "
             << strerror(errno) << "\n";
        return (1);
    }
    struct stat st;
    if (fstat(fd, &st) < 0) {
        cerr << "stat(" << script_name << ") failed: "
             << strerror(errno) << "\n";
        close(fd);
        return (2);
    }
    size_t sz = static_cast<size_t>(st.st_size);
    char* content = new char[static_cast<size_t>(st.st_size)];
    if (read(fd, content, sz) < 0) {
        cerr << "read(" << script_name << ") failed: "
             << strerror(errno) << "\n";
        close(fd);
        return (3);
    }
    close(fd);

    // Initialize the v8 interpreter
#if (V8_MAJOR_VERSION < 5) || \
    ((V8_MAJOR_VERSION == 5) && (V8_MINOR_VERSION < 3))
    V8::InitializeICU();
#else
    V8::InitializeICUDefaultLocation(progname.c_str());
#endif
    V8::InitializeExternalStartupData(progname.c_str());
    platform_ = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform_);
    V8::Initialize();
    ArrayBufferAllocator array_buffer_allocator;
    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = &array_buffer_allocator;
    isolate_ = Isolate::New(create_params);
    isolate_->SetFatalErrorHandler(&fatal_error_handler);

    // Open a scope for the script
    Isolate::Scope isolate_scope(isolate_);

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate_);

    // Catch errors
    TryCatch try_catch(isolate_);

    // For global objects
    Local<ObjectTemplate> globals = ObjectTemplate::New(isolate_);
    init_globals(isolate_, globals);

    // Create a new context
    Local<Context> context = Context::New(isolate_, NULL, globals);

    // Enter the context for compiling and running the script
    Context::Scope context_scope(context);

    // Initialize option and pkt4
    init_option(isolate_);
    init_pkt4(isolate_);

    // Import script file content
    Local<String> source =
        String::NewFromUtf8(isolate_, content,
                            NewStringType::kNormal).ToLocalChecked();

    // Compile the script
    Local<Script> script;
    if (!Script::Compile(context, source).ToLocal(&script)) {
        String::Utf8Value error(try_catch.Exception());
        cerr << "Compile(" << script_name << ") failed: "
             << *error << "\n";
        return (4);
    }

    // Run the script to get the result.
    Local<Value> result;
    if (!script->Run(context).ToLocal(&result)) {
        String::Utf8Value error(try_catch.Exception());
        cerr << "Run(" << script_name << ") failed: " << *error << "\n";
        return (5);
    }

    // Get the pkt4_receive function
    Local<String> pkt4_rcv_name =
        String::NewFromUtf8(isolate_, "pkt4_receive",
                            NewStringType::kNormal).ToLocalChecked();
    Local<Object> global = context->Global();
    Local<Value> pkt4_rcv_val;
    if (!global->Get(context, pkt4_rcv_name).ToLocal(&pkt4_rcv_val)) {
        String::Utf8Value error(try_catch.Exception());
        cerr << "global->Get(pkt4_receive) failed: " << *error << "\n";
        return (6);
    }
    if (!pkt4_rcv_val->IsFunction()) {
        cerr << "\"pkt4_receive\" is not a function\n";
        return (7);
    }
    Local<Function> pkt4_rcv_fun = Local<Function>::Cast(pkt4_rcv_val);
    pkt4_rcv_hndl.Reset(isolate_, pkt4_rcv_fun);

    return (0);
}

// unload
int unload() {
    // Clear pkt4_receive handler
    pkt4_rcv_hndl.Reset();

    // Destroy v8 interpreter
    if (platform_) {
        if (isolate_) {
            isolate_->Dispose();
        }
        isolate_ = NULL;
        V8::Dispose();
        V8::ShutdownPlatform();
        delete platform_;
    }
    platform_ = NULL;

    return (0);
}

// pkt4_receive hook
int pkt4_receive(CalloutHandle& handle) {
    if (pkt4_rcv_hndl.IsEmpty()) {
        return (0);
    }
    cout << "pkt4_receive: enter\n";

    Pkt4Ptr query4;
    handle.getArgument("query4", query4);
    if (!query4) {
        cerr << "pkt4_receive: null query4\n";
        return (0);
    }

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate_);

    // Catch errors
    TryCatch try_catch(isolate_);

    // Get a new context
    Local<Context> context = Context::New(isolate_);

    // Enter the context for running the handler
    Context::Scope context_scope(context);

    // Create pkt4 object
    Local<Object> query = make_pkt4(isolate_, query4);
    if (query.IsEmpty()) {
        cerr << "empty v8 query\n";
        return (0);
    }

    // Call the handler
    const int argc = 1;
    Local<Value> argv[argc] = { query };
    Local<Function> handler = Local<Function>::New(isolate_, pkt4_rcv_hndl);
    Local<Value> result;
    if (!handler->Call(context, context->Global(),
                       argc, argv).ToLocal(&result)) {
        String::Utf8Value error(try_catch.Exception());
        cerr << "pkt4_receive handler failed: " << *error << "\n";
        return (0);
    }
    if (!result->IsInt32()) {
        cerr << "pkt4_receive handler didn't return an int32\n";
        return (0);
    }

    int32_t ret = 0xbadbad;
    ret = result->Int32Value(context).FromJust();
    if (ret == 0xbadbad) {
        String::Utf8Value error(try_catch.Exception());
        cerr << "ToInt32 failed: " << *error << "\n";
        return (0);
    }

    cout << "pkt4_receive: return " << ret << "\n";
    return (static_cast<int>(ret));
}

}
