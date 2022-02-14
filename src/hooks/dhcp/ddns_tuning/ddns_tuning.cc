// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ddns_tuning.h>
#include <ddns_tuning_log.h>
#include <util/strutil.h>
#include <cc/simple_parser.h>
#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>
#include <eval/eval_context.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace isc::log;
using namespace isc::util;
using namespace std;

namespace isc {
namespace ddns_tuning {

DdnsTuningImpl::DdnsTuningImpl() {
}

DdnsTuningImpl::~DdnsTuningImpl() {
}

void DdnsTuningImpl::configure(isc::data::ConstElementPtr params) {
    if (!params) {
        isc_throw(BadValue, "missing parameters");
    }
    ConstElementPtr hostname = params->get("hostname-expr");
    if (!hostname) {
        isc_throw(BadValue, "hostname-expr parameter missing");
    }
    if (hostname->getType() != Element::string) {
        isc_throw(BadValue, "'hostname-expr' must e a string");
    }

    /// @todo: Parse expression
    setText(hostname->str());

}


} // end of namespace ddns_tuning
} // end of namespace isc
