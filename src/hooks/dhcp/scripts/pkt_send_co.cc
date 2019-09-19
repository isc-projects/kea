// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file pkt_send_co.cc Defines the pkt4_send and pkt6_send callout functions.

#include <config.h>
#include <asiolink/io_address.h>
#include <hooks/hooks.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/dhcp6.h>
#include <scripts_cfg.h>
#include <scripts.h>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace hooks::scripts;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief  This callout is called at the "pkt6_send" hook.
///
/// This function generates environment variables based on the Pkt6 content.
/// It then calls the external script.
///
/// @return 0 upon success, non-zero otherwise.
int pkt6_send(CalloutHandle& handle) {


    try {
        Pkt6Ptr query;
        handle.getArgument("query6", query);

        Pkt6Ptr response;
        handle.getArgument("response6", response);

        Variables vars;

        if (!query || !response) {
            // Something is very wrong.
            return (1);
        }

        stringstream tmp;
        tmp << "ACTION=" << Pkt6::getName(query->getType());
        vars.push_back(tmp.str());

        auto ia_list = response->getOptions(D6O_IA_NA);
        int addr_cnt = 1;
        for (auto ia : ia_list) {
            auto opts = ia.second->getOptions();

            for (auto opt : opts) {
                if (opt.second->getType() != D6O_IAADDR) {
                    continue;
                }

                Option6IAAddrPtr addr = boost::dynamic_pointer_cast<Option6IAAddr>(opt.second);
                if (!addr) {
                    // something is wrong. But let's ignore it and move forward.
                    continue;
                }

                tmp.str("");
                tmp << "ADDRESS" << (addr_cnt) << "=" << addr->getAddress();
                vars.push_back(tmp.str());


                tmp.str("");
                tmp << "ADDRESS" << (addr_cnt) << "_PREFERRED=" << addr->getPreferred();
                vars.push_back(tmp.str());

                tmp.str("");
                tmp << "ADDRESS" << (addr_cnt++) << "_VALID=" << addr->getValid();
                vars.push_back(tmp.str());
            }
        }

        auto pd_list = response->getOptions(D6O_IA_PD);
        int prefix_cnt = 1;

        for (auto pd: pd_list) {
            auto opts = pd.second->getOptions();

            for (auto opt : opts) {
                if (opt.second->getType() != D6O_IAPREFIX) {
                    continue;
                }

                Option6IAPrefixPtr prefix = boost::dynamic_pointer_cast<Option6IAPrefix>(opt.second);
                if (!prefix) {
                    // something is wrong. But let's ignore it and move forward.
                    continue;
                }

                stringstream tmp;
                tmp << "PREFIX" << (prefix_cnt) << "=" << prefix->getAddress() << "/"
                    << prefix->getLength();
                vars.push_back(tmp.str());

                tmp.str("");
                tmp << "PREFIX" << (prefix_cnt) << "_PREFERRED=" << prefix->getPreferred();
                vars.push_back(tmp.str());

                tmp.str("");
                tmp << "PREFIX" << (prefix_cnt++) << "_VALID=" << prefix->getValid();
                vars.push_back(tmp.str());
            }

        }

        // Ok, all variables are set, call the scripts!
        callScript(vars);

    } catch (const std::exception& ex) {
        std::cout << "DHCP Scripts Hook : pkt6_send unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }


    return (0);
}

} // extern C
