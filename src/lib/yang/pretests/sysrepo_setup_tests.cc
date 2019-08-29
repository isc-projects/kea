// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#define KEATEST_MODULE
#include <yang/yang_revisions.h>

#ifndef HAVE_PRE_0_7_6_SYSREPO
#include <sysrepo-cpp/Session.hpp>
#else
#include <sysrepo-cpp/Session.h>
#endif

#include <sstream>

using namespace std;
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif
using namespace isc::yang;

const string REPOSITORY = SYSREPO_REPO;

/// @brief Returns nicely formed error message if module is missing
///
/// @param name name of the YANG module to complain about
/// #param revision revision of the YANG module
/// @return a text explaining what the problem is and how to fix it
string missingModuleText(const string& name, const string& revision) {
    stringstream tmp;
    tmp << "ERROR: YANG module " << name << " is not installed." << endl
        << "The environment is not suitable for running unit-tests." << endl
        << "Please locate " << name << "@" << revision << ".yang, "
        << "change to its directory and issue the following command:"
        << endl << endl
        << "# sysrepoctl -i -s " << REPOSITORY << "/yang "
        << "-s . -g " << name << "@" << revision << ".yang" << endl
        << endl << endl;
    return (tmp.str());
}

/// @brief Returns nicely formed error message if module does not have
/// the expected revision.
///
/// @param name name of the YANG module to complain about
/// @param expected expected revision of the YANG module
/// @param got got (bad) revision of the YANG module
string badRevisionModuleText(const string& name, const string& expected,
                             const string& got) {
    stringstream tmp;
    tmp << "ERROR: YANG module " << name << " is not installed with the right "
        << "revision: expected " << expected << " but got " << got << endl
        << "Please remove the module " << name << " and re-install it: "
        << "Please locate " << name << "@" << expected << ".yang, " << endl
        << "change to its directory and issue the following commands:"
        << endl << endl
        << "# sysrepoctl -u -m " << name << endl
        << "# sysrepoctl -i -s " << REPOSITORY << "/yang "
        << "-s . -g " << name << "@" << expected << ".yang" << endl
        << endl << endl;
    return (tmp.str());
}

/// @brief Checks sysrepo setup:
///  - connection establishment
///  - session establishment
///  - test module
///  - type modules
///  - IETF module
///  - Kea modules.
///  - daemon required
int main() {
    S_Connection conn;
    try {
        conn.reset(new Connection("sysrepo setup check"));
    } catch (const sysrepo_exception& ex) {
        cerr << "ERROR: Can't connect to sysrepo: " << ex.what() << endl;
        cerr << "ERROR: Make sure the sysrepod daemon is running." << endl;
        exit(-1);
    }

    S_Session sess;
    try {
        sess.reset(new Session(conn, SR_DS_CANDIDATE));
    } catch (const sysrepo_exception& ex) {
        cerr << "ERROR: Can't establish a sysrepo session: "
             << ex.what() << endl;
        exit(-2);
    }

    S_Yang_Schemas schemas;
    try {
        schemas = sess->list_schemas();
    } catch (const sysrepo_exception& ex) {
        cerr << "ERROR: Can't list available schemas: " <<  ex.what() << endl;
        exit(-3);
    }

    map<string, bool> found;
    map<string, string> got;
    for (auto modrev : YANG_REVISIONS) {
        found[modrev.first] = false;
    }

    for (size_t i = 0; i < schemas->schema_cnt(); ++i) {
        string module = schemas->schema(i)->module_name();
        if (YANG_REVISIONS.count(module)) {
            found[module] = true;
            if (!schemas->schema(i)->revision() ||
                !schemas->schema(i)->revision()->revision()) {
                got[module] = "none";
            } else {
                string rev = schemas->schema(i)->revision()->revision();
                got[module] = rev;
            }
        }
    }

    int exit_code = 0;

    for (auto modfnd : found) {
        string rev = YANG_REVISIONS.at(modfnd.first);
        if (!modfnd.second) {
            if (exit_code > -4) {
                exit_code = -4;
            }
            --exit_code;
            cerr << missingModuleText(modfnd.first, rev);
        } else if (rev != got[modfnd.first]) {
            if (exit_code > -40) {
                exit_code += -40;
            } else {
                exit_code += -10;
            }
            cerr << badRevisionModuleText(modfnd.first, rev, got[modfnd.first]);
        }
    }

    try {
        sess.reset();
        conn.reset(new Connection("sysrepo setup check",
                                  SR_CONN_DAEMON_REQUIRED));
    } catch (const sysrepo_exception& ex) {
        cerr <<"ERROR: Can't connect to sysrepo daemon: " <<ex.what() << endl
             << endl
             << "Sysrepo daemon is required or actions will be local to "
             << "the local library instance." << endl;
        cerr << "Please make sure the sysrepod daemon is running." << endl;
        cerr << "The following command should do the trick:" << endl;
        cerr << endl;
        cerr << "$ sudo sysrepod" << endl;
        cerr << endl;

        exit_code -= 100;
    }

    exit(exit_code);
}
