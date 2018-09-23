// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <sysrepo-cpp/Session.h>

using namespace std;

const string TEST_MODULE = "keatest-module";
const string IETF_MODULE = "ietf-dhcpv6-server";
const string KEA_DHCP4_MODULE = "kea-dhcp4-server";
const string KEA_DHCP6_MODULE = "kea-dhcp6-server";
const string KEA_CTRL_AGENT_MODULE = "kea-ctrl-agent";
const string KEA_D2_MODULE = "kea-dhcp-ddns";

/// @brief Checks sysrepo setup:
///  - connection establishment
///  - daemon required
///  - session establishment
///  - test module
///  - IETF module
///  - Kea modules.
int main() {
    S_Connection conn;
    try {
        conn.reset(new Connection("sysrepo setup check"));
    } catch (const sysrepo_exception& ex) {
        cerr << "Can't connect to sysrepo: " << ex.what() << endl;
        exit(-1);
    }
    try {
        conn.reset(new Connection("sysrepo setup check",
                                  SR_CONN_DAEMON_REQUIRED));
    } catch (const sysrepo_exception& ex) {
        cerr <<"Can't require sysrepo daemon: " <<ex.what() << endl
             << endl
             << "Sysrepo daemon is required or actions will be local to "
             << "the local library instance" << endl;
        exit(-2);
    }
    S_Session sess;
    try {
        sess.reset(new Session(conn, SR_DS_CANDIDATE));
    } catch (const sysrepo_exception& ex) {
        cerr << "Can't establish a sysrepo session: " << ex.what() << endl;
        exit(-3);
    }
    S_Yang_Schemas schemas;
    try {
        schemas = sess->list_schemas();
    } catch (const sysrepo_exception& ex) {
        cerr << "Can't list available schemas: " <<  ex.what() << endl;
    }
    bool found_test = false;
    bool found_ietf = false;
    bool found_kea4 = false;
    bool found_kea6 = false;
    bool found_keaca = false;
    bool found_kea2 = false;
    for (size_t i = 0; i < schemas->schema_cnt(); ++i) {
        string module = schemas->schema(i)->module_name();
        size_t rev = module.find("@");
        if (rev != string::npos) {
            module = module.substr(0, rev);
        }
        if (module == TEST_MODULE) {
            found_test = true;
        } else if (module == IETF_MODULE) {
            found_ietf = true;
        } else if (module == KEA_DHCP4_MODULE) {
            found_kea4 = true;
        } else if (module == KEA_DHCP6_MODULE) {
            found_kea6 = true;
        } else if (module == KEA_CTRL_AGENT_MODULE) {
            found_keaca = true;
        } else if (module == KEA_D2_MODULE) {
            found_kea2 = true;
        }
    }

    if (!found_test) {
        cerr << "Module used in unit-tests " << TEST_MODULE
             << " is not installed. The environment is not suitable for "
             << "running unit-tests. Please locate " << TEST_MODULE
             << ".yang and issue the following command:" << endl
             << "sysrepoctl --i -g " << TEST_MODULE << ".yang" << endl;
        exit(-4);
    }

    if (!found_ietf) {
        cerr << "Please install " << IETF_MODULE << " module" << endl;
        exit(-5);
    }

    if (!found_kea4) {
        cerr <<"Please install " << KEA_DHCP4_MODULE << " module" << endl;
        exit(-6);
    }

    if (!found_kea6) {
        cerr <<"Please install " << KEA_DHCP6_MODULE << " module" << endl;
        exit(-7);
    }

    if (!found_keaca) {
        cerr <<"Please install " << KEA_CTRL_AGENT_MODULE << " module" << endl;
        exit(-8);
    }

    if (!found_kea2) {
        cerr <<"Please install " << KEA_D2_MODULE<< " module" << endl;
        exit(-9);
    }

    exit(0);
}
