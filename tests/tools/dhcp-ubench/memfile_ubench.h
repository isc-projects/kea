// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <fstream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "benchmark.h"

struct Lease4 {
    uint32_t addr;
    std::vector<uint8_t> hwaddr;
    std::vector<uint8_t> client_id;
    uint32_t valid_lft;
    uint32_t recycle_time;
    time_t cltt;
    uint32_t pool_id;
    bool fixed;
    std::string hostname;
    bool fqdn_fwd;
    bool fqdn_rev;
    std::string options;
    std::string comments;
};

typedef boost::shared_ptr<Lease4> Lease4Ptr;

class memfile_LeaseMgr;

class memfile_uBenchmark: public uBenchmark {
public:
    memfile_uBenchmark(const std::string& filename,
                       uint32_t num_iterations);

    virtual void printInfo();
    virtual void connect();
    virtual void disconnect();
    virtual void createLease4Test();
    virtual void searchLease4Test();
    virtual void updateLease4Test();
    virtual void deleteLease4Test();

protected:
    void failure(const char* operation);

    memfile_LeaseMgr * LeaseMgr_;

    std::string Filename_;
};
