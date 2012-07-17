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
#include <iostream>
#include <map>
#include "memfile_ubench.h"

using namespace std;


class memfile_LeaseMgr {
public:
typedef std::map<uint32_t /* addr */, Lease4Ptr /* lease info */> IPv4Hash;
typedef std::map<uint32_t, Lease4Ptr>::iterator leaseIt;
    memfile_LeaseMgr(const std::string& filename);
    ~memfile_LeaseMgr();
    bool addLease(Lease4Ptr lease);
    Lease4Ptr getLease(uint32_t addr);
    Lease4Ptr updateLease(uint32_t addr, uint32_t new_cltt);
    bool deleteLease(uint32_t addr);

protected:

    void writeLease(Lease4Ptr lease);

    std::string Filename_;
    std::ofstream File_;
    IPv4Hash ip4Hash_;
};

memfile_LeaseMgr::memfile_LeaseMgr(const std::string& filename)
    : File_(filename.c_str(), ios::trunc), Filename_(filename) {
    if (!File_.is_open()) {
        throw "Failed to create file " + filename;
    }

}

memfile_LeaseMgr::~memfile_LeaseMgr() {
    File_.close();
}

void memfile_LeaseMgr::writeLease(Lease4Ptr lease) {
    File_ << "lease " << lease->addr << " {" << endl << "  hw-addr ";
    for (std::vector<uint8_t>::const_iterator it = lease->hwaddr.begin();
         it != lease->hwaddr.end(); ++it) {
        File_ << *it;
    }
    File_ << ";" << endl << "  client-id ";
    for (std::vector<uint8_t>::const_iterator it = lease->client_id.begin();
         it != lease->client_id.end(); ++it) {
        File_ << *it;
    }
    File_ << ";" << endl << "  valid-lifetime " << lease->valid_lft << endl;
    File_ << "  recycle-time " << lease->recycle_time << endl;
    File_ << "  cltt " << lease->cltt << endl;
    File_ << "  pool-id " << lease->pool_id << endl;
    File_ << "  fixed " << lease->fixed << endl;
    File_ << "  hostname " << lease->hostname << endl;
    File_ << "  fqdn_fwd " << lease->fqdn_fwd << endl;
    File_ << "  fqdn_rev " << lease->fqdn_rev << endl;
    File_ << "}" << endl;
}

bool memfile_LeaseMgr::addLease(Lease4Ptr lease) {
    if (ip4Hash_.find(lease->addr) != ip4Hash_.end()) {
        // there is such an address already in the hash
        return false;
    }
    ip4Hash_.insert(pair<uint32_t, Lease4Ptr>(lease->addr, lease));
    lease->hostname = "add";
    writeLease(lease);
    return (true);
}

Lease4Ptr memfile_LeaseMgr::getLease(uint32_t addr) {
    leaseIt x = ip4Hash_.find(addr);
    if (x != ip4Hash_.end())
        return x->second; // found

    // not found
    return Lease4Ptr();
}

Lease4Ptr memfile_LeaseMgr::updateLease(uint32_t addr, uint32_t new_cltt) {
    leaseIt x = ip4Hash_.find(addr);
    if (x != ip4Hash_.end()) {
        x->second->cltt = new_cltt;
        x->second->hostname = "update";
        writeLease(x->second);
        return x->second;
    }
    return Lease4Ptr();
}

bool memfile_LeaseMgr::deleteLease(uint32_t addr) {
    leaseIt x = ip4Hash_.find(addr);
    if (x != ip4Hash_.end()) {
        x->second->hostname = "delete";
        writeLease(x->second);
        ip4Hash_.erase(x);
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
    try {
        LeaseMgr_ = new memfile_LeaseMgr(Filename_);

    } catch (const std::string& e) {
        failure(e.c_str());
    }
}

void memfile_uBenchmark::disconnect() {
    delete LeaseMgr_;
    LeaseMgr_ = NULL;
}

void memfile_uBenchmark::createLease4Test() {
    if (!LeaseMgr_) {
        throw "No LeaseMgr instantiated.";
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

        if (!LeaseMgr_->addLease(lease)) {
            failure("addLease() failed");
        } else {
            printf(".");
        };

        addr++;
    }
    printf("\n");
}

void memfile_uBenchmark::searchLease4Test() {
    if (!LeaseMgr_) {
        throw "No LeaseMgr instantiated.";
    }

    // this formula should roughly find something a lease in 90% cases
    float hitRatio = 0.5;

    printf("RETRIEVE: ");

    for (uint32_t i = 0; i < Num_; i++) {

        uint32_t x = BASE_ADDR4 + random() % int(Num_ / hitRatio);

        Lease4Ptr lease = LeaseMgr_->getLease(x);
        if (lease) {
            printf(".");
        } else {
            printf("X");
        }
    }

    printf("\n");
}

void memfile_uBenchmark::updateLease4Test() {
    if (!LeaseMgr_) {
        throw "No LeaseMgr instantiated.";
    }

    printf("UPDATE:   ");

    time_t cltt = time(NULL);

    for (uint32_t i = 0; i < Num_; i++) {

        uint32_t x = BASE_ADDR4 + random() % Num_;

        Lease4Ptr lease = LeaseMgr_->updateLease(x, cltt);
        if (!lease) {
            stringstream tmp;
            tmp << "UPDATE failed for lease " << hex << x << dec;
            failure(tmp.str().c_str());
        }
        printf(".");
    }

    printf("\n");
}

void memfile_uBenchmark::deleteLease4Test() {
    if (!LeaseMgr_) {
        throw "No LeaseMgr instantiated.";
    }

    printf("DELETE:   ");
    char * errorMsg = NULL;

    for (uint32_t i = 0; i < Num_; i++) {

        uint32_t x = BASE_ADDR4 + i;

        if (!LeaseMgr_->deleteLease(x)) {
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
    uint32_t num = 10000;

    memfile_uBenchmark bench(filename, num);

    int result = bench.run();

    return (result);
}
