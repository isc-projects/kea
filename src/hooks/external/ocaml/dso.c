// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/callback.h>

#include <hooks/hooks.h>

#include <hooks/external/ocaml/opt.h>
#include <hooks/external/ocaml/pkt4.h>

#include <iostream>

using namespace std;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::ocaml;

namespace {
    // Pkt4 receive handler
    value* pkt4_rcv_hndl;
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
    // Start ocaml
    char* argv[2];
    argv[0] = &progname[0];
    argv[1] = NULL;
    caml_startup(argv);
    
    // Initialize types
    caml_register_custom_operations(opt_ops);
    caml_register_custom_operations(pkt4_ops);

    // Get pkt4_rcv_hndl address
    pkt4_rcv_hndl = caml_named_value("pkt4_receive");
    if (pkt4_rcv_hndl) {
        cout << "got pkt4_receive\n";
    }

    return (0);
}

// unload
int unload() {
    return (0);
}

// pkt4_receive hook
int pkt4_receive(CalloutHandle& handle) {
    CAMLparam0();
    CAMLlocal2(query, result);

    if (!pkt4_rcv_hndl) {
        cerr << "pkt4_receive ocaml hook not available\n";
        CAMLdrop;
        return (0);
    }
    cout << "pkt4_receive enter\n";

    Pkt4Ptr query4;
    handle.getArgument("query4", query4);
    if (!query4) {
        cerr << "pkt4_receive: null query4\n";
        CAMLdrop;
        return (0);
    }

    query = caml_alloc_custom(pkt4_ops, sizeof(oc_pkt4), 0, 1);
    if (!query) {
        cerr << "caml_alloc_custom failed\n";
        CAMLdrop;
        return (0);
    }
    (static_cast<oc_pkt4*>(Data_custom_val(query)))->object = query4;

    result = caml_callback_exn(*pkt4_rcv_hndl, query);
    if (Is_exception_result(result)) {
        cerr << "pkt4_receive raised an exception\n";
        CAMLdrop;
        return (0);
    }
    if (!Is_long(result)) {
        cerr << "pkt4_receive did not return an integer\n";
        CAMLdrop;
        return (0);
    }
    CAMLdrop;
    return (Int_val(result));
}

}
