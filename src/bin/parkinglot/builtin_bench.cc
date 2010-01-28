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

// $Id$

#include <sys/time.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include <dns/cpp/buffer.h>
#include <dns/cpp/messagerenderer.h>
#include <dns/cpp/name.h>
#include <dns/cpp/rdata.h>
#include <dns/cpp/rrclass.h>
#include <dns/cpp/rrtype.h>
#include <dns/cpp/rrttl.h>
#include <dns/cpp/rrset.h>

#include "builtin.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

static const int ITERATION = 100000;

namespace {
Name authors_name("authors.bind");

inline double
tv_sub(const struct timeval& t1, const struct timeval& t2)
{
    struct timeval result;

    result.tv_sec = t1.tv_sec - t2.tv_sec;
    result.tv_usec = t1.tv_usec - t2.tv_usec;
    if (result.tv_usec < 0) {
        result.tv_usec += 1000000;
        result.tv_sec--;
    }

    return (result.tv_sec + result.tv_usec / 1000000.0);
}

void
buildAuthors(vector<string>& authors)
{
    authors.push_back("Han Feng");
    authors.push_back("Kazunori Fujiwara");
    authors.push_back("Michael Graff");
    authors.push_back("Evan Hunt");
    authors.push_back("Jelte Jansen");
    authors.push_back("Jin Jian");
    authors.push_back("JINMEI Tatuya");
    authors.push_back("Naoki Kambe");
    authors.push_back("Shane Kerr"); 
    authors.push_back("Zhang Likun");
    authors.push_back("Jeremy C. Reed");
}

struct RdataInserterFromText
{
    RdataInserterFromText(RRsetPtr rrset) : rrset_(rrset) {}
    void operator()(const string& author)
    {
        rrset_->addRdata(generic::TXT(author));
    }
    RRsetPtr rrset_;
};

inline RRsetPtr
getNormalRRset(const vector<string>& authors)
{
    RRsetPtr rrset = RRsetPtr(new RRset(authors_name,  RRClass::CH(),
                                        RRType::TXT(), RRTTL(0)));
    for_each(authors.begin(), authors.end(), RdataInserterFromText(rrset));

    return (rrset);
}

struct RdataInserterFromWire
{
    RdataInserterFromWire(RRsetPtr rrset) : rrset_(rrset) {}
    void operator()(const OutputBuffer& buffer)
    {
        InputBuffer b(buffer.getData(), buffer.getLength());
        rrset_->addRdata(RdataPtr(new generic::TXT(b, buffer.getLength())));
    }
    RRsetPtr rrset_;
};

inline RRsetPtr
getNormalRRset(const vector<OutputBuffer>& buffers)
{
    RRsetPtr rrset = RRsetPtr(new RRset(authors_name,  RRClass::CH(),
                                        RRType::TXT(), RRTTL(0)));
    for_each(buffers.begin(), buffers.end(), RdataInserterFromWire(rrset));

    return (rrset);
}

inline OutputBuffer
txtToWire(const string& txt)
{
    OutputBuffer buffer(0);
    generic::TXT(txt).toWire(buffer);
    return (buffer);
}

struct WireDataInserter
{
    WireDataInserter(vector<OutputBuffer>& buffers) : buffers_(buffers)
    {}
    void operator()(const string& author)
    {
        OutputBuffer buffer(0);
        generic::TXT(author).toWire(buffer);
        buffers_.push_back(buffer);
    }
    vector<OutputBuffer>& buffers_;
};

void
showResult(const struct timeval& tv_begin, const struct timeval& tv_end,
           int iteration, const char* description)
{
    double diff = tv_sub(tv_end, tv_begin);
    cout << description << " " << iteration << " times in "
         << fixed << diff << "sec ("
         << static_cast<int>(iteration / diff) << "qps)" << endl;
}
}

int
main(int argc, char* argv[])
{
    int iteration = ITERATION;
    if (argc > 1) {
        istringstream(argv[1]) >> dec >> iteration;
    }

    vector<string> authors;
    buildAuthors(authors);

    struct timeval tv_begin, tv_end;
    OutputBuffer buffer(512);
    MessageRenderer renderer(buffer);

    //
    // Benchmark for rendering an optimized pre-format RRset
    //
    gettimeofday(&tv_begin, NULL);
    for (int i = 0; i < iteration; ++i) {
        renderer.clear();
        renderer.skip(12);
        renderer.writeName(authors_name);
        RRsetPtr rrset_optimized = getBuiltinAuthors().getAnswer();
        rrset_optimized->toWire(renderer);
    }
    gettimeofday(&tv_end, NULL);
    showResult(tv_begin, tv_end, iteration, "Rendered optimized RRset");

    vector<unsigned char> data(buffer.getLength());
    memcpy(&data[0], buffer.getData(), buffer.getLength());

    //
    // Benchmark for rendering a general purpose RRset of the same content
    //
    RRsetPtr rrset_normal = getNormalRRset(authors);
    gettimeofday(&tv_begin, NULL);
    for (int i = 0; i < iteration; ++i) {
        renderer.clear();
        renderer.skip(12);
        renderer.writeName(authors_name);
        rrset_normal->toWire(renderer);
    }
    gettimeofday(&tv_end, NULL);
    showResult(tv_begin, tv_end, iteration, "Rendered normal RRset");

    // Confirm the two sets of output are identical.
    if (data.size() != buffer.getLength() ||
        memcmp(&data[0], buffer.getData(), buffer.getLength())) {
        cerr << "Rendered data mismatch" << endl;
        return (1);
    }

    //
    // Benchmark for rendering a general purpose RRset of the same content,
    // create RRset from text every time
    //
    gettimeofday(&tv_begin, NULL);
    for (int i = 0; i < iteration; ++i) {
        renderer.clear();
        renderer.skip(12);
        renderer.writeName(authors_name);
        getNormalRRset(authors)->toWire(renderer);
    }
    gettimeofday(&tv_end, NULL);
    showResult(tv_begin, tv_end, iteration,
               "Rendered normal RRset with fromText");

    // Confirm the two sets of output are identical.
    if (data.size() != buffer.getLength() ||
        memcmp(&data[0], buffer.getData(), buffer.getLength())) {
        cerr << "Rendered data mismatch" << endl;
        return (1);
    }

    //
    // Benchmark for rendering a general purpose RRset of the same content,
    // create RRset from wire data every time
    //
    vector<OutputBuffer> buffers;
    for_each(authors.begin(), authors.end(), WireDataInserter(buffers));
    gettimeofday(&tv_begin, NULL);
    for (int i = 0; i < iteration; ++i) {
        renderer.clear();
        renderer.skip(12);
        renderer.writeName(authors_name);
        getNormalRRset(buffers)->toWire(renderer);
    }
    gettimeofday(&tv_end, NULL);
    showResult(tv_begin, tv_end, iteration,
               "Rendered normal RRset with fromWire");

    // Confirm the two sets of output are identical.
    if (data.size() != buffer.getLength() ||
        memcmp(&data[0], buffer.getData(), buffer.getLength())) {
        cerr << "Rendered data mismatch" << endl;
        return (1);
    }

    return (0);
}
