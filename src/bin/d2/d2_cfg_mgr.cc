// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <d2/d2_log.h>
#include <d2/d2_cfg_mgr.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;

namespace isc {
namespace d2 {

// *********************** D2CfgContext  *************************

D2CfgContext::D2CfgContext() {
    // @TODO - initialize D2 specific storage
}

D2CfgContext::D2CfgContext(const D2CfgContext& rhs) : DCfgContextBase(rhs)
    /* @TODO copy D2 specific storage  */ {
}

D2CfgContext::~D2CfgContext() {
}

// *********************** D2CfgMgr  *************************

D2CfgMgr::D2CfgMgr() : DCfgMgrBase(DCfgContextBasePtr(new D2CfgContext())) {
}

D2CfgMgr::~D2CfgMgr() {
}

isc::dhcp::ParserPtr
D2CfgMgr::createConfigParser(const std::string& element_id) {
    // @TODO This is only enough implementation for integration.
    // This will expand to support the top level D2 elements.
    // For now we will simply return a debug parser for everything.
    return (isc::dhcp::ParserPtr(new isc::dhcp::DebugParser(element_id)));
}

}; // end of isc::dhcp namespace
}; // end of isc namespace

