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

#include <hooks/external/ocaml/opt.h>

#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace isc::dhcp;
using namespace isc::ocaml;

namespace { // anonymous namespace

// finalize
void finalize(value opt) {
    // This is a critical code to avoid memory leaks
    cerr << "kea option finalize called\n";
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    self->object.reset();
}

// dummy deserialize
uintnat deserialize(void*) {
    // Should never be called
    caml_failwith("attempt to deserialize a kea option");
}

// option operations
struct custom_operations* init_opt_ops() {
    static struct custom_operations ops;
    static string id = "kea-opt";
    ops.identifier = &id[0];
    ops.finalize = finalize;
    ops.compare = custom_compare_default;
    ops.hash = custom_hash_default;
    ops.serialize = custom_serialize_default;
    // Define deserialize to be allowed to register
    ops.deserialize = deserialize;
    ops.compare_ext = custom_compare_ext_default;

    return (&ops);
}

}

namespace isc {
namespace ocaml {

struct custom_operations* opt_ops = init_opt_ops();

extern "C" CAMLprim value opt_factory(value u, value typ, value bytes) {
    CAMLparam3(u, typ, bytes);
    CAMLlocal1(result);
    Option::Universe universe;
    ostringstream oss;
    switch (Int_val(u)) {
    case 4:
        universe = Option::V4;
        if (Int_val(typ) > 255) {
            oss << "out of range type for DHCPv4: " << Int_val(typ);
            caml_invalid_argument(oss.str().c_str());
        }
        break;
    case 6:
        universe = Option::V6;
        break;
    default:
        oss << "universe must be 4 or 6 (not " << Int_val(u) << ")";
        caml_invalid_argument(oss.str().c_str());
    }
    uint16_t type = static_cast<uint16_t>(Int_val(typ));
    OptionBuffer data;
    data.resize(static_cast<size_t>(caml_string_length(bytes)));
    if (!data.empty()) {
        memmove(&data[0], String_val(bytes), data.size());
    }
    result = caml_alloc_custom(opt_ops, sizeof(oc_opt), 0, 1);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(result));
    self->object.reset(new Option(universe, type, data));
    CAMLreturn (result);
}

extern "C" CAMLprim value opt_toText(value opt) {
    CAMLparam1(opt);
    CAMLlocal1(result);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    result = caml_copy_string(self->object->toText().c_str());
    CAMLreturn (result);
}

extern "C" CAMLprim value opt_getUniverse(value opt) {
    CAMLparam1(opt);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    int ret = 0;
    switch (self->object->getUniverse()) {
    case Option::V4:
        ret = 4;
        break;
    case Option::V6:
        ret = 6;
        break;
    default: {
        string msg = "getUniverse";
        caml_raise_sys_error(caml_copy_string(msg.c_str()));
    }
    }
    CAMLreturn (Val_int(ret));
}

extern "C" CAMLprim value opt_toBinary(value opt) {
    CAMLparam1(opt);
    CAMLlocal1(result);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    vector<uint8_t> bin = self->object->toBinary(true);
    result = caml_alloc_string(static_cast<mlsize_t>(bin.size()));
    if (!bin.empty()) {
        memmove(String_val(result), &bin[0], bin.size());
    }
    CAMLreturn (result);
}

extern "C" CAMLprim value opt_getType(value opt) {
    CAMLparam1(opt);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    CAMLreturn (Val_int(self->object->getType()));
}

extern "C" CAMLprim value opt_len(value opt) {
    CAMLparam1(opt);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    CAMLreturn (Val_int(self->object->len()));
}

extern "C" CAMLprim value opt_getHeaderLen(value opt) {
    CAMLparam1(opt);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    CAMLreturn (Val_int(self->object->getHeaderLen()));
}

extern "C" CAMLprim value opt_getData(value opt) {
    CAMLparam1(opt);
    CAMLlocal1(result);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    vector<uint8_t> data = self->object->getData();
    result = caml_alloc_string(static_cast<mlsize_t>(data.size()));
    if (!data.empty()) {
        memmove(String_val(result), &data[0], data.size());
    }
    CAMLreturn (result);
}

extern "C" CAMLprim value opt_addOption(value opt, value sub) {
    CAMLparam2(opt, sub);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    oc_opt* const other = static_cast<oc_opt*>(Data_custom_val(sub));
    self->object->addOption(other->object);
    CAMLreturn (Val_unit);
}

extern "C" CAMLprim value opt_getOption(value opt, value typ) {
    CAMLparam2(opt, typ);
    CAMLlocal2(option, result);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    uint16_t type = static_cast<uint16_t>(Long_val(typ));
    OptionPtr sub = self->object->getOption(type);
    if (sub) {
        option = caml_alloc_custom(opt_ops, sizeof(oc_opt), 0, 1);
        (static_cast<oc_opt*>(Data_custom_val(option)))->object = sub;
        result = caml_alloc(1, 0);
        Store_field(result, 0, option);
    } else {
        result = Val_int(0);
    }
    CAMLreturn (result);
}

// TODO getOptions

extern "C" CAMLprim value opt_delOption(value opt, value typ) {
    CAMLparam2(opt, typ);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    uint16_t type = static_cast<uint16_t>(Long_val(typ));
    bool ret = self->object->delOption(type);
    CAMLreturn (Val_int(ret ? 1 : 0));
}

extern "C" CAMLprim value opt_setData(value opt, value bytes) {
    CAMLparam2(opt, bytes);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    vector<uint8_t> data;
    data.resize(static_cast<size_t>(caml_string_length(bytes)));
    if (!data.empty()) {
        memmove(&data[0], String_val(bytes), data.size());
    }
    self->object->setData(data.begin(), data.end());
    CAMLreturn (Val_unit);
}

extern "C" CAMLprim value opt_setEncapsulatedSpace(value opt, value name) {
    CAMLparam2(opt, name);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    string space(String_val(name));
    self->object->setEncapsulatedSpace(space);
    CAMLreturn (Val_unit);
}

extern "C" CAMLprim value opt_getEncapsulatedSpace(value opt) {
    CAMLparam1(opt);
    CAMLlocal1(result);
    oc_opt* const self = static_cast<oc_opt*>(Data_custom_val(opt));
    string space = self->object->getEncapsulatedSpace();
    result = caml_copy_string(space.c_str());
    CAMLreturn (result);
}

} // end of namespace ocaml
} // end of namespace isc
