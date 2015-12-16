// Copyright (C) 2009-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

#include <gtest/gtest.h>

#include <dns/rcode.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/tests/unittest_util.h>

using namespace std;
using namespace isc::dns;

using isc::UnitTestUtil;

namespace {
class UnitTestUtilConfig {
private:
    // This is a singleton object and cannot be constructed explicitly.
    UnitTestUtilConfig() {}
    UnitTestUtilConfig(const UnitTestUtilConfig& source);
    ~UnitTestUtilConfig() {}
public:
    /// Return a singleton unit test configuration object.  On first invocation
    /// one will be constructed.
    static UnitTestUtilConfig& getConfig();

    /// A list of paths to wire data files.
    /// \c UnitTestUtil::readWireData() (first version)
    /// will search the directories in this list for the specified data file.
    std::vector<string> data_paths_;
};

UnitTestUtilConfig&
UnitTestUtilConfig::getConfig() {
    static UnitTestUtilConfig config;
    return (config);
}
}

void
UnitTestUtil::readWireData(const char* datafile, vector<unsigned char>& data) {
    ifstream ifs;

    const UnitTestUtilConfig& config = UnitTestUtilConfig::getConfig();
    vector<string>::const_iterator it = config.data_paths_.begin();
    for (; it != config.data_paths_.end(); ++it) {
        string data_path = *it;
        if (data_path.empty() || *data_path.rbegin() != '/') {
            data_path.push_back('/');
        }
        ifs.open((data_path + datafile).c_str(), ios_base::in);
        if ((ifs.rdstate() & istream::failbit) == 0) {
            break;
        }
    }

    if (it == config.data_paths_.end()) {
        throw runtime_error("failed to open data file in data paths: " +
                            string(datafile));
    }

    data.clear();

    string s;
    while (getline(ifs, s), !ifs.eof()) {
        if (ifs.bad() || ifs.fail()) {
            throw runtime_error("unexpected data line");
        }
        if (s.empty() || s[0] == '#') {
            continue;
        }

        readWireData(s, data);
    }
}

void
UnitTestUtil::addDataPath(const string& directory) {
    UnitTestUtilConfig::getConfig().data_paths_.push_back(directory);
}

void
UnitTestUtil::readWireData(const string& datastr,
                           vector<unsigned char>& data)
{
    istringstream iss(datastr);

    do {
        string bytes;
        iss >> bytes;
        if (iss.bad() || iss.fail() || (bytes.size() % 2) != 0) {
            ostringstream err_oss;
            err_oss << "unexpected input or I/O error in reading " <<
                datastr;
            throw runtime_error(err_oss.str());
        }

        for (string::size_type pos = 0; pos < bytes.size(); pos += 2) {
            istringstream iss_byte(bytes.substr(pos, 2));
            unsigned int ch;

            iss_byte >> hex >> ch;
            if (iss_byte.rdstate() != istream::eofbit) {
                ostringstream err_oss;
                err_oss << "invalid byte representation: " << iss_byte.str();
                throw runtime_error(err_oss.str());
            }
            data.push_back(static_cast<unsigned char>(ch));
        }
    } while (!iss.eof());
}

::testing::AssertionResult
UnitTestUtil::matchName(const char*, const char*,
                        const isc::dns::Name& name1,
                        const isc::dns::Name& name2)
{
    ::testing::Message msg;

    NameComparisonResult cmpresult = name1.compare(name2);
    if (cmpresult.getOrder() != 0 ||
        cmpresult.getRelation() != NameComparisonResult::EQUAL) {
        msg << "Two names are expected to be equal but not:\n"
            << "  One: " << name1 << "\n"
            << "Other: " << name2 << "\n";
        return (::testing::AssertionFailure(msg));
    }
    return (::testing::AssertionSuccess());
}

void
UnitTestUtil::createRequestMessage(Message& message,
                                   const Opcode& opcode,
                                   const uint16_t qid,
                                   const Name& name,
                                   const RRClass& rrclass,
                                   const RRType& rrtype)
{
    message.clear(Message::RENDER);
    message.setOpcode(opcode);
    message.setRcode(Rcode::NOERROR());
    message.setQid(qid);
    message.addQuestion(Question(name, rrclass, rrtype));
}

void
UnitTestUtil::createDNSSECRequestMessage(Message& message,
                                         const Opcode& opcode,
                                         const uint16_t qid,
                                         const Name& name,
                                         const RRClass& rrclass,
                                         const RRType& rrtype)
{
    message.clear(Message::RENDER);
    message.setOpcode(opcode);
    message.setRcode(Rcode::NOERROR());
    message.setQid(qid);
    message.addQuestion(Question(name, rrclass, rrtype));
    EDNSPtr edns(new EDNS());
    edns->setUDPSize(4096);
    edns->setDNSSECAwareness(true);
    message.setEDNS(edns);
}
