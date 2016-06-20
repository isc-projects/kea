// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OCAML_PKT4_H
#define OCAML_PKT4_H 1

#include <dhcp/pkt4.h>

namespace isc {
namespace ocaml {

// Ocaml DHCPv4 packet class
class oc_pkt4 {
  oc_pkt4();

public:
    isc::dhcp::Pkt4Ptr object;
};

extern "C" CAMLprim value pkt4_toText(value pkt);
extern "C" CAMLprim value pkt4_addOption(value pkt, value opt);
extern "C" CAMLprim value pkt4_delOption(value pkt, value typ);
extern "C" CAMLprim value pkt4_len(value pkt);
extern "C" CAMLprim value pkt4_getType(value pkt);
extern "C" CAMLprim value pkt4_setType(value pkt, value typ);
extern "C" CAMLprim value pkt4_setTransid(value pkt, value tid);
extern "C" CAMLprim value pkt4_getTransid(value pkt);
extern "C" CAMLprim value pkt4_inClass(value pkt, value cclass);
extern "C" CAMLprim value pkt4_addClass(value pkt, value cclass);
extern "C" CAMLprim value pkt4_getOption(value pkt, value typ);
extern "C" CAMLprim value pkt4_setIndex(value pkt, value idx);
extern "C" CAMLprim value pkt4_getIndex(value pkt);
extern "C" CAMLprim value pkt4_getIface(value pkt);
extern "C" CAMLprim value pkt4_setIface(value pkt, value ifn);

CAMLextern struct custom_operations* pkt4_ops;

} // end of namespace ocaml
} // end of namespace isc

#endif // OCAML_PKT4_H
