// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrtype.h>
#include <dns/rrclass.h>
#include <dns/question.h>

#include <bench/benchmark_util.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;

namespace isc {
namespace bench {
void
loadQueryData(const char* const input_file, BenchQueries& queries,
              const RRClass& qclass, const bool strict)
{
    ifstream ifs;

    ifs.open(input_file, ios_base::in);
    if ((ifs.rdstate() & istream::failbit) != 0) {
        isc_throw(BenchMarkError, "failed to load query data file: " +
                  string(input_file));
    }
    loadQueryData(ifs, queries, qclass, strict);
    ifs.close();
}

void
loadQueryData(istream& input, BenchQueries& queries, const RRClass& qclass,
              const bool strict)
{
    string line;
    unsigned int linenum = 0;
    Message query_message(Message::RENDER);
    OutputBuffer buffer(128); // this should be sufficiently large
    MessageRenderer renderer(buffer);
    while (getline(input, line), !input.eof()) {
        ++linenum;
        if (input.bad() || input.fail()) {
            isc_throw(BenchMarkError,
                      "Unexpected line in query data file around line " <<
                      linenum);
        }
        if (line.empty() || line[0] == '#') {
            continue;           // skip comment and blank lines
        }

        istringstream iss(line);
        string qname_string, qtype_string;
        iss >> qname_string >> qtype_string;
        if (iss.bad() || iss.fail()) {
            if (strict) {
                isc_throw(BenchMarkError,
                          "load query: unexpected input around line " <<
                          linenum);
            }
            continue;
        }

        // We expect broken lines of data, which will be ignored with a
        // warning message.
        try {
            query_message.clear(Message::RENDER);
            query_message.setQid(0);
            query_message.setOpcode(Opcode::QUERY());
            query_message.setRcode(Rcode::NOERROR());
            query_message.addQuestion(Question(Name(qname_string), qclass,
                                               RRType(qtype_string)));

            renderer.clear();
            query_message.toWire(renderer);
            vector<unsigned char> query_data(
                static_cast<const unsigned char*>(buffer.getData()),
                static_cast<const unsigned char*>(buffer.getData()) +
                buffer.getLength());
            queries.push_back(query_data);
        } catch (const Exception&) {
            if (strict) {
                isc_throw(BenchMarkError,
                          "failed to parse/create query around line " <<
                          linenum);
            }
            continue;
        }
    }
}
}
}
