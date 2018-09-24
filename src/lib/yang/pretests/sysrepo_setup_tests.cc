// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <sysrepo-cpp/Session.h>
#include <sstream>

using namespace std;

const string TEST_MODULE = "keatest-module";
const string IETF_MODULE = "ietf-dhcpv6-server";
const string KEA_DHCP4_MODULE = "kea-dhcp4-server";
const string KEA_DHCP6_MODULE = "kea-dhcp6-server";
const string KEA_CTRL_AGENT_MODULE = "kea-ctrl-agent";
const string KEA_D2_MODULE = "kea-dhcp-ddns";

/// @brief Returns nicely formed error message if module is missing
///
/// @param name name of the YANG module to complain about
/// @return a text explaining what the problem is and how to fix it
string missingModuleText(const string& name) {
    stringstream tmp;
    tmp << "ERROR: YANG model " << name << " is not installed." << endl
        << "The environment is not suitable for running unit-tests." << endl
        << "Please locate " << name << ".yang and issue the following command:" << endl
        << endl
        << "# sysrepoctl -i -g " << name << ".yang" << endl
        << endl
        << "If sysrepoctl complains about missing data model, you may need to specify " << endl
        << "the default Sysrepo schema directory with -s PATH. You can check it with:" << endl
        << endl
        << "$ sysrepoctl -l" << endl
        << endl;
    return (tmp.str());
}

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
        cerr << "ERROR: Can't connect to sysrepo: " << ex.what() << endl;
        exit(-1);
    }
    try {
        conn.reset(new Connection("sysrepo setup check",
                                  SR_CONN_DAEMON_REQUIRED));
    } catch (const sysrepo_exception& ex) {
        cerr <<"ERROR: Can't connect to sysrepo daemon: " <<ex.what() << endl
             << endl
             << "Sysrepo daemon is required or actions will be local to "
             << "the local library instance." << endl;
        exit(-2);
    }
    S_Session sess;
    try {
        sess.reset(new Session(conn, SR_DS_CANDIDATE));
    } catch (const sysrepo_exception& ex) {
        cerr << "ERROR: Can't establish a sysrepo session: " << ex.what() << endl;
        exit(-3);
    }
    S_Yang_Schemas schemas;
    try {
        schemas = sess->list_schemas();
    } catch (const sysrepo_exception& ex) {
        cerr << "ERROR: Can't list available schemas: " <<  ex.what() << endl;
        exit(-4);
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


    int exit_code = 0;

    if (!found_test) {
        cerr << missingModuleText(TEST_MODULE);
        exit_code = -5;
    }

    if (!found_ietf) {
        cerr << missingModuleText(IETF_MODULE);
        exit_code = -6;
    }

    if (!found_kea4) {
        cerr << missingModuleText(KEA_DHCP4_MODULE);
        exit_code = -7;
    }

    if (!found_kea6) {
        cerr << missingModuleText(KEA_DHCP6_MODULE);
        exit_code = -8;
    }

    if (!found_keaca) {
        cerr << missingModuleText(KEA_CTRL_AGENT_MODULE);
        exit_code = -9;
    }

    if (!found_kea2) {
        cerr << missingModuleText(KEA_D2_MODULE);
        exit_code = -10;
    }

    exit(exit_code);
}
