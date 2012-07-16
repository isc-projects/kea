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

#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include "memfile_ubench.h"
#include <boost/shared_ptr.hpp>

using namespace std;


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

std::map<uint32_t /* addr */, Lease4Ptr /* lease info */> ip4Hash;
typedef std::map<uint32_t, Lease4Ptr>::iterator leaseIt;

bool addLease(Lease4Ptr lease) {
    if (ip4Hash.find(lease->addr) != ip4Hash.end()) {
        // there is such an address already in the hash
        return false;
    }
    ip4Hash.insert(pair<uint32_t, Lease4Ptr>(lease->addr, lease));
    return (true);
}

Lease4Ptr getLease(uint32_t addr) {
    leaseIt x = ip4Hash.find(addr);
    if (x != ip4Hash.end())
        return x->second; // found
    
    // not found
    return Lease4Ptr();
}

bool updateLease(uint32_t addr, uint32_t new_cltt) {
    leaseIt x = ip4Hash.find(addr);
    if (x != ip4Hash.end()) {
        x->second->cltt = new_cltt;
        return true;
    }
    return false;
}

bool deleteLease(uint32_t addr) {
    leaseIt x = ip4Hash.find(addr);
    if (x != ip4Hash.end()) {
        ip4Hash.erase(x);
        return true;
    } 
    return false;
}

memfile_uBenchmark::memfile_uBenchmark(const string& filename,
                                   uint32_t num_iterations)
    :uBenchmark(num_iterations), Filename_(filename) {

}

void memfile_uBenchmark::failure(const char* operation) {
    throw string(operation);
}

void memfile_uBenchmark::connect() {
    File_.open(Filename_.c_str());
    if (!File_.is_open()) {
        failure("Failed to create output file");
    }
}

void memfile_uBenchmark::disconnect() {
    File_.close();
}

void memfile_uBenchmark::createLease4Test() {
    if (!File_.is_open()) {
        throw "Lease file not open for writing.";
    }

    uint32_t addr = BASE_ADDR4; // Let's start with 1.0.0.0 address
    char hwaddr_tmp[20];
    uint8_t hwaddr_len = 20; // not a real field
    char client_id_tmp[128];
    uint8_t client_id_len = 128;
    uint32_t valid_lft = 1000;  // we can use the same value for all leases
    uint32_t recycle_time = 0;  // not supported in any foresable future,
                                // so keep this as 0
    time_t cltt = time(NULL); // timestamp
    uint32_t pool_id = 0; // let's use pools 0-99
    bool fixed = false;   //
    string hostname("foo");      // will generate it dynamically
    bool fqdn_fwd = true; // let's pretend to do AAAA update
    bool fqdn_rev = true; // let's pretend to do PTR update

    printf("CREATE:   ");

    for (uint8_t i = 0; i < 20; i++) {
        hwaddr_tmp[i] = 65 + i;
    }
    vector<uint8_t> hwaddr(hwaddr_tmp, hwaddr_tmp+19);

    for (uint8_t i = 0; i < 128; i++) {
        client_id_tmp[i] = 33 + i;
    }
    vector<uint8_t> client_id(client_id_tmp, client_id_tmp+19);

    for (uint32_t i = 0; i < Num_; i++) {

        cltt++;

        Lease4Ptr lease = boost::shared_ptr<Lease4>(new Lease4());
        lease->addr = addr;
        lease->hwaddr = hwaddr;
        lease->client_id = client_id;
        lease->valid_lft = valid_lft;
        lease->recycle_time = 0;
        lease->cltt = cltt;
        lease->pool_id = 0;
        lease->fixed = false;
        lease->hostname = "foo";
        lease->fqdn_fwd = true;
        lease->fqdn_rev = true;

        if (!addLease(lease)) {
            failure("addLease() failed");
        } else {
            printf(".");
        };

        addr++;
    }
    printf("\n");
}

void memfile_uBenchmark::searchLease4Test() {
    if (!File_.is_open()) {
        throw "Lease file not open for writing.";
    }

    // this formula should roughly find something a lease in 90% cases
    float hitRatio = 0.5;

    printf("RETRIEVE: ");

    for (uint32_t i = 0; i < Num_; i++) {

        uint32_t x = BASE_ADDR4 + random() % int(Num_ / hitRatio);

        Lease4Ptr lease = getLease(x);
        if (lease) {
            printf(".");
        } else {
            printf("X");
        }
    }

    printf("\n");
}

void memfile_uBenchmark::updateLease4Test() {
    if (!File_.is_open()) {
        throw "Lease file not open for writing.";
    }

    printf("UPDATE:   ");

    time_t cltt = time(NULL);

    for (uint32_t i = 0; i < Num_; i++) {

        uint32_t x = BASE_ADDR4 + random() % Num_;

        if (!updateLease(x, cltt)) {
            stringstream tmp;
            tmp << "UPDATE failed for lease " << hex << x << dec;
            failure(tmp.str().c_str());
        }
        printf(".");
    }

    printf("\n");
}

void memfile_uBenchmark::deleteLease4Test() {
    if (!File_.is_open()) {
        throw "Lease file not open for writing.";
    }

    printf("DELETE:   ");
    char * errorMsg = NULL;

    for (uint32_t i = 0; i < Num_; i++) {

        uint32_t x = BASE_ADDR4 + i;

        if (!deleteLease(x)) {
            stringstream tmp;
            tmp << "UPDATE failed for lease " << hex << x << dec;
            failure(tmp.str().c_str());
        }
        printf(".");
    }

    printf("\n");
}

void memfile_uBenchmark::printInfo() {
    cout << "Using memory db + write-only file." << endl;
}


int main(int argc, const char * argv[]) {

    const char * filename = "dhcpd.leases";
    uint32_t num = 1000000;

    memfile_uBenchmark bench(filename, num);

    int result = bench.run();

    return (result);
}
