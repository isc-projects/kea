// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/data.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/callout_handle_store.h>
#include <hooks/hooks_manager.h>
#include <log/logger_support.h>

#include <boost/foreach.hpp>

#include <iostream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;

// config fragment for hooks-libraries
const string config =
    "{ \"hooks-libraries\": ["
    " { \"library\": \"kea.so\", "
    "   \"parameters\": "
    "   { \"program\": \"kea\", "
    "     \"script\": \"hook\" }"
    " }] }";

// main routine
int main() {
    // must be first
    int hi_pkt4_receive = HooksManager::registerHook("pkt4_receive");
    cout << "pkt4_receive is hook#" << hi_pkt4_receive << "\n";

    initLogger();

    // check if there is a library already loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    if (!hooks_libraries.empty()) {
        cerr << "hooks_libraries is not empty\n";
    }

    // parse config into json
    ElementPtr json = Element::fromJSON(config);
    if (!json) {
        cerr << "fatal: fromJSON failed\n";
        exit(-1);
    }
    cout << "config parsed\n";

    // call the hooks-libraries parser
    boost::shared_ptr<HooksLibrariesParser> parser;
    try {
        const map<string, ConstElementPtr>& cmap = json->mapValue();
        if (cmap.empty()) {
            cerr << "fatal: config map is empty\n";
            exit(-1);
        }
        if (cmap.size() > 1) {
            cerr << "config map has more than one element\n";
        }
        if (cmap.count("hooks-libraries") == 0) {
            cerr << "fatal: no \"hooks-libraries\" in config\n";
            exit(-1);
        }
        const ConstElementPtr& hl_value = cmap.find("hooks-libraries")->second;
        if (!hl_value) {
            cerr << "fatal: empty \"hooks-libraries\" value\n";
            exit(-1);
        }
        parser.reset(new HooksLibrariesParser("hooks-libraries"));
        parser->build(hl_value);
        parser->commit();
        cout << "config committed\n";
    } catch (const Exception& ex) {
        cerr << "fatal: config parsing failed: " << ex.what() << "\n";
        exit(-1);
    }
    
    // check if the library was loaded
    HookLibsCollection libraries;
    bool changed = false;
    parser->getLibraries(libraries, changed);
    if (!changed) {
        cerr << "commit didn't change libraries\n";
    }
    if (libraries.empty()) {
        cerr << "fatal: no libraries\n";
        exit(-1);
    }
    if (libraries.size() > 1) {
        cerr << "more than one library\n";
    }
    cout << "library is \"" + libraries[0].first + "\"\n";
    if (libraries[0].first != "kea.so") {
        cerr << "fatal: library is not \"kea.so\"\n";
        exit(-1);
    }
    ConstElementPtr params = libraries[0].second;
    if (!params) {
        cerr << "no parameters\n";
    } else {
        cout << "got " << params->size() << " parameters\n";
    }

    // note we can't know this way if it was successfully loaded

    // get the callout
    if (!HooksManager::calloutsPresent(hi_pkt4_receive)) {
        cerr << "fatal: no callout present for pkt4_receive\n";
        exit(-1);
    }

    // from pkt4_unittests.cc
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 0x12345678));
    const uint8_t macAddr[] = {0, 1, 2, 3, 4, 5};
    vector<uint8_t> vectorMacAddr(macAddr, macAddr + sizeof(macAddr));
    pkt->setHWAddr(6, 6, vectorMacAddr);
    pkt->setHops(13);
    // Transaction-id is already set.
    pkt->setSecs(42);
    pkt->setFlags(BOOTP_BROADCAST);
    pkt->setCiaddr(IOAddress("192.0.2.1"));
    pkt->setYiaddr(IOAddress("1.2.3.4"));
    pkt->setSiaddr(IOAddress("192.0.2.255"));
    pkt->setGiaddr(IOAddress("255.255.255.255"));
    // Chaddr already set with setHWAddr().

    // from dhcp4_srv.cc
    CalloutHandlePtr co_handle = getCalloutHandle(pkt);
    co_handle->deleteAllArguments();
    co_handle->setArgument("query4", pkt);
    cout << "calling pkt4_receive callout\n";
    HooksManager::callCallouts(hi_pkt4_receive, *co_handle);
    cout << "pkt4_receive callout status " << co_handle->getStatus() << "\n";
    co_handle->getArgument("query4", pkt);

    // TODO...

    exit(0);
}
