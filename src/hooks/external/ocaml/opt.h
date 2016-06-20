// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OCAML_OPT_H
#define OCAML_OPT_H 1

#include <dhcp/option.h>

namespace isc {
namespace ocaml {

// Ocaml option class
class oc_opt {
  oc_opt();

public:
    isc::dhcp::OptionPtr object;
};

extern "C" CAMLprim value opt_factory(value u, value typ, value bytes);
extern "C" CAMLprim value opt_toText(value opt);
extern "C" CAMLprim value opt_getUniverse(value opt);
extern "C" CAMLprim value opt_toBinary(value opt);
extern "C" CAMLprim value opt_getType(value opt);
extern "C" CAMLprim value opt_len(value opt);
extern "C" CAMLprim value opt_getHeaderLen(value opt);
extern "C" CAMLprim value opt_getData(value opt);
extern "C" CAMLprim value opt_addOption(value opt, value sub);
extern "C" CAMLprim value opt_getOption(value opt, value typ);
extern "C" CAMLprim value opt_delOption(value opt, value typ);
extern "C" CAMLprim value opt_setData(value opt, value bytes);
extern "C" CAMLprim value opt_setEncapsulatedSpace(value opt, value name);
extern "C" CAMLprim value opt_getEncapsulatedSpace(value opt);

CAMLextern struct custom_operations* opt_ops;

} // end of namespace ocaml
} // end of namespace isc

#endif // OCAML_OPT_H
