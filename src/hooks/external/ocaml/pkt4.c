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
#include <hooks/external/ocaml/pkt4.h>

#include <iostream>
#include <string>

using namespace std;
using namespace isc::dhcp;
using namespace isc::ocaml;

namespace { // anonymous namespace

// finalize
void finalize(value pkt) {
    // This is a critical code to avoid memory leaks
    cerr << "kea v4 packet finalize called\n";
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    self->object.reset();
}

// dummy deserialize
uintnat deserialize(void*) {
    // Should never be called
    caml_failwith("attempt to deserialize a kea v4 packet");
}

// v4 packet operations
struct custom_operations* init_pkt4_ops() {
    static struct custom_operations ops;
    static string id = "kea-pkt4";
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

struct custom_operations* pkt4_ops = init_pkt4_ops();

extern "C" CAMLprim value pkt4_toText(value pkt) {
    CAMLparam1(pkt);
    CAMLlocal1(result);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    result = caml_copy_string(self->object->toText().c_str());
    CAMLreturn (result);
}

extern "C" CAMLprim value pkt4_addOption(value pkt, value sub) {
    CAMLparam2(pkt, sub);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    oc_opt* const opt = static_cast<oc_opt*>(Data_custom_val(sub));
    self->object->addOption(opt->object);
    CAMLreturn (Val_unit);
}

extern "C" CAMLprim value pkt4_delOption(value pkt, value typ) {
    CAMLparam2(pkt, typ);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    uint16_t type = static_cast<uint16_t>(Long_val(typ));
    bool ret = self->object->delOption(type);
    CAMLreturn (Val_int(ret ? 1 : 0));
}

extern "C" CAMLprim value pkt4_len(value pkt) {
    CAMLparam1(pkt);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    CAMLreturn (Val_int(self->object->len()));
}

extern "C" CAMLprim value pkt4_getType(value pkt) {
    CAMLparam1(pkt);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    CAMLreturn (Val_int(self->object->getType()));
}

extern "C" CAMLprim value pkt4_setType(value pkt, value type) {
    CAMLparam1(pkt);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    self->object->setType(static_cast<uint8_t>(Int_val(type)));
    CAMLreturn (Val_unit);
}

extern "C" CAMLprim value pkt4_setTransid(value pkt, value tid) {
    CAMLparam1(pkt);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    self->object->setTransid(static_cast<uint8_t>(Int_val(tid)));
    CAMLreturn (Val_unit);
}

extern "C" CAMLprim value pkt4_getTransid(value pkt) {
    CAMLparam1(pkt);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    CAMLreturn (Val_int(self->object->getTransid()));
}

extern "C" CAMLprim value pkt4_inClass(value pkt, value cclass) {
    CAMLparam2(pkt, cclass);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    const ClientClass& client_class(String_val(cclass));
    bool ret = self->object->inClass(client_class);
    CAMLreturn (Val_int(ret ? 1 : 0));
}

extern "C" CAMLprim value pkt4_addClass(value pkt, value cclass) {
    CAMLparam2(pkt, cclass);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    const ClientClass& client_class(String_val(cclass));
    self->object->addClass(client_class);
    CAMLreturn (Val_unit);
}

// TODO getClasses

extern "C" CAMLprim value pkt4_getOption(value pkt, value typ) {
    CAMLparam2(pkt, typ);
    CAMLlocal2(opt, result);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    uint16_t type = static_cast<uint16_t>(Long_val(typ));
    OptionPtr sub = self->object->getOption(type);
    if (sub) {
        opt = caml_alloc_custom(opt_ops, sizeof(oc_opt), 0, 1);
        (static_cast<oc_opt*>(Data_custom_val(opt)))->object = sub;
        result = caml_alloc(1, 0);
        Store_field(result, 0, opt);
    } else {
        result = Val_int(0);
    }
    CAMLreturn (result);
}

// TODO getTimestamp

// TODO set/getLocal/RemoteAddr/Port

extern "C" CAMLprim value pkt4_setIndex(value pkt, value idx) {
    CAMLparam1(pkt);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    self->object->setIndex(static_cast<uint32_t>(Int_val(idx)));
    CAMLreturn (Val_unit);
}

extern "C" CAMLprim value pkt4_getIndex(value pkt) {
    CAMLparam1(pkt);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    CAMLreturn (Val_int(self->object->getIndex()));
}

extern "C" CAMLprim value pkt4_getIface(value pkt) {
    CAMLparam1(pkt);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    string iface = self->object->getIface();
    CAMLreturn (caml_copy_string(iface.c_str()));
}

extern "C" CAMLprim value pkt4_setIface(value pkt, value ifn) {
    CAMLparam1(pkt);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    self->object->setIface(string(String_val(ifn)));
    CAMLreturn (Val_unit);
}

// TODO many

extern "C" CAMLprim value pkt4_getHWAddr(value pkt) {
    CAMLparam1(pkt);
    CAMLlocal1(result);
    oc_pkt4* const self = static_cast<oc_pkt4*>(Data_custom_val(pkt));
    HWAddrPtr hwaddr = self->object->getHWAddr();
    vector<uint8_t> bin;
    if (hwaddr) {
        bin = hwaddr->hwaddr_;
    }
    result = caml_alloc_string(static_cast<mlsize_t>(bin.size()));
    if (!bin.empty()) {
        memmove(String_val(result), &bin[0], bin.size());
    }
    CAMLreturn (result);
}

} // end of namespace ocaml
} // end of namespace isc
