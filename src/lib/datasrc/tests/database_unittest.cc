// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <datasrc/tests/database_unittest.h>
#include <datasrc/tests/faked_nsec3.h>

#include <dns/masterload.h>
#include <dns/name.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>
#include <dns/nsec3hash.h>
#include <exceptions/exceptions.h>

#include <datasrc/database.h>
#include <datasrc/zone.h>
#include <datasrc/zone_finder.h>
#include <datasrc/exceptions.h>
#include <datasrc/zone_iterator.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <map>
#include <string>
#include <vector>

using namespace isc::datasrc;
using namespace std;
// don't import the entire boost namespace.  It will unexpectedly hide uint32_t
// for some systems.
using boost::dynamic_pointer_cast;
using boost::lexical_cast;
using namespace isc::dns;
using namespace isc::testutils;
using namespace isc::datasrc::test;

namespace isc {
namespace datasrc {
namespace test {
/// Single journal entry in the mock database.
///
/// All the members there are public for simplicity, as it only stores data.
/// We use the implicit constructor and operator. The members can't be const
/// because of the assignment operator (used in the vectors).
struct JournalEntry {
    JournalEntry(int id, uint32_t serial,
                 DatabaseAccessor::DiffOperation operation,
                 const std::string (&data)[DatabaseAccessor::DIFF_PARAM_COUNT])
        : id_(id), serial_(serial), operation_(operation)
    {
        data_[DatabaseAccessor::DIFF_NAME] = data[DatabaseAccessor::DIFF_NAME];
        data_[DatabaseAccessor::DIFF_TYPE] = data[DatabaseAccessor::DIFF_TYPE];
        data_[DatabaseAccessor::DIFF_TTL] = data[DatabaseAccessor::DIFF_TTL];
        data_[DatabaseAccessor::DIFF_RDATA] =
            data[DatabaseAccessor::DIFF_RDATA];
    }
    JournalEntry(int id, uint32_t serial,
                 DatabaseAccessor::DiffOperation operation,
                 const std::string& name, const std::string& type,
                 const std::string& ttl, const std::string& rdata):
        id_(id), serial_(serial), operation_(operation)
    {
        data_[DatabaseAccessor::DIFF_NAME] = name;
        data_[DatabaseAccessor::DIFF_TYPE] = type;
        data_[DatabaseAccessor::DIFF_TTL] = ttl;
        data_[DatabaseAccessor::DIFF_RDATA] = rdata;
    }
    int id_;
    uint32_t serial_;
    DatabaseAccessor::DiffOperation operation_;
    std::string data_[DatabaseAccessor::DIFF_PARAM_COUNT];
    bool operator==(const JournalEntry& other) const {
        for (size_t i = 0; i < DatabaseAccessor::DIFF_PARAM_COUNT; ++ i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        // No need to check data here, checked above
        return (id_ == other.id_ && serial_ == other.serial_ &&
                operation_ == other.operation_);
    }
};
}
}
}

namespace {
// Imaginary zone IDs used in the mock accessor below.
const int READONLY_ZONE_ID = 42;
const int NEW_ZONE_ID = 420;
const int WRITABLE_ZONE_ID = 4200;

/*
 * An accessor with minimum implementation, keeping the original
 * "NotImplemented" methods.
 */
class NopAccessor : public DatabaseAccessor {
public:
    NopAccessor() : database_name_("mock_database") {
        zones_["example.org."] = READONLY_ZONE_ID;
        zones_["null.example.org."] = 13;
        zones_["empty.example.org."] = 0;
        zones_["bad.example.org."] = -1;
    }

    virtual std::pair<bool, int> getZone(const std::string& name) const {
        std::map<std::string, int>::const_iterator found = zones_.find(name);
        if (found != zones_.end()) {
            return (std::pair<bool, int>(true, found->second));
        } else {
            return (std::pair<bool, int>(false, 0));
        }
    }

    // A simple implementation of addZone.
    virtual int addZone(const std::string& zone_name) {
        if (zone_name == "example.com.") {
            zones_[zone_name] = NEW_ZONE_ID;
        }

        // for simplicity we assume zone_name is in zones_ at this point
        return (zones_[zone_name]);
    }

    // A simple implementation of deleteZone.
    virtual void deleteZone(int zone_id) {
        std::map<std::string, int>::iterator it = zones_.begin();
        std::map<std::string, int>::iterator end = zones_.end();
        while (it != end) {
            if (it->second == zone_id) {
                zones_.erase(it);
                return;
            }
            ++it;
        }
    }

    virtual boost::shared_ptr<DatabaseAccessor> clone() {
        // This accessor is stateless, so we can simply return a new instance.
        return (boost::shared_ptr<DatabaseAccessor>(new NopAccessor));
    }

    virtual std::pair<bool, int> startUpdateZone(const std::string&, bool) {
        // return dummy value.  unused anyway.
        return (pair<bool, int>(true, 0));
    }
    virtual void startTransaction() {}
    virtual void commit() {}
    virtual void rollback() {}
    virtual void addRecordToZone(const string (&)[ADD_COLUMN_COUNT]) {}
    virtual void addNSEC3RecordToZone(const string (&)[ADD_NSEC3_COLUMN_COUNT])
    {}
    virtual void deleteRecordInZone(const string (&)[DEL_PARAM_COUNT]) {}
    virtual void deleteNSEC3RecordInZone(const string
                                         (&)[DEL_NSEC3_PARAM_COUNT]) {}
    virtual void addRecordDiff(int, uint32_t, DiffOperation,
                               const std::string (&)[DIFF_PARAM_COUNT]) {}

    virtual const std::string& getDBName() const {
        return (database_name_);
    }

    virtual IteratorContextPtr getRecords(const std::string&, int, bool)
        const
    {
        isc_throw(isc::NotImplemented,
                  "This database datasource can't be iterated");
    }

    virtual IteratorContextPtr getNSEC3Records(const std::string&, int) const {
        isc_throw(isc::NotImplemented, "This test database datasource won't "
                  "give you any NSEC3. Ever. Ask someone else.");
    }

    virtual IteratorContextPtr getAllRecords(int) const {
        isc_throw(isc::NotImplemented,
                  "This database datasource can't be iterated");
    }

    virtual IteratorContextPtr getDiffs(int, uint32_t, uint32_t) const {
        isc_throw(isc::NotImplemented,
                  "This database datasource doesn't support diffs");
    }

    virtual std::string findPreviousName(int, const std::string&) const {
        isc_throw(isc::NotImplemented,
                  "This data source doesn't support DNSSEC");
    }

    virtual std::string findPreviousNSEC3Hash(int, const std::string&) const {
        isc_throw(isc::NotImplemented,
                  "This test database knows nothing about NSEC3 nor order");
    }

private:
    const std::string database_name_;
    std::map<std::string, int> zones_;
};

/*
 * A virtual database accessor that pretends it contains single zone --
 * example.org.
 *
 * It has the same getZone method as NopConnection, but it provides
 * implementation of the optional functionality.
 */
class MockAccessor : public NopAccessor {
    // Type of mock database "row"s.  This is a map whose keys are the
    // own names.  We internally sort them by the name comparison order.
    struct NameCompare : public binary_function<string, string, bool> {
        bool operator()(const string& n1, const string& n2) const {
            return (Name(n1).compare(Name(n2)).getOrder() < 0);
        }
    };
    typedef std::map<std::string,
                     std::vector< std::vector<std::string> >,
                     NameCompare > Domains;

public:
    MockAccessor() : rollbacked_(false), did_transaction_(false) {
        readonly_records_ = &readonly_records_master_;
        update_records_ = &update_records_master_;
        nsec3_namespace_ = &nsec3_namespace_master_;
        update_nsec3_namespace_ = &update_nsec3_namespace_master_;
        empty_records_ = &empty_records_master_;
        journal_entries_ = &journal_entries_master_;
        fillData();
    }

    virtual boost::shared_ptr<DatabaseAccessor> clone() {
        boost::shared_ptr<MockAccessor> cloned_accessor(new MockAccessor());
        cloned_accessor->readonly_records_ = &readonly_records_master_;
        cloned_accessor->update_records_ = &update_records_master_;
        cloned_accessor->nsec3_namespace_ = &nsec3_namespace_master_;
        cloned_accessor->update_nsec3_namespace_ =
            &update_nsec3_namespace_master_;
        cloned_accessor->empty_records_ = &empty_records_master_;
        cloned_accessor->journal_entries_ = &journal_entries_master_;
        latest_clone_ = cloned_accessor;
        return (cloned_accessor);
    }

    virtual void startTransaction() {
        // Currently we only use this transaction for simple read-only
        // operations.  So we just make a local copy of the data (we don't
        // care about what happens after commit() or rollback()).
        // Obviously as a consequence, if a test case tries to make multiple
        // transactions on a single mock accessor it will fail.

        // Check any attempt of multiple transactions
        if (did_transaction_) {
            isc_throw(DataSourceError, "MockAccessor::startTransaction() "
                      "called multiple times - likely a bug in the test");
        }

        readonly_records_copy_ = *readonly_records_;
        readonly_records_ = &readonly_records_copy_;
        did_transaction_ = true;
    }

    // If the test needs multiple calls to startTransaction() and knows it's
    // safe, it can use this method to disable the safeguard check in
    // startTransaction(); the test can also use this method by emulating a
    // lock conflict by setting is_allowed to false.
    void allowMoreTransaction(bool is_allowed) {
        did_transaction_ = !is_allowed;
    }

private:
    class DomainIterator : public IteratorContext {
    public:
        DomainIterator(const std::vector<std::vector<std::string> >& domain) :
            domain_(domain),
            position_(domain_.begin())
        {}
        virtual bool getNext(std::string (&columns)[COLUMN_COUNT]) {
            if (position_ == domain_.end()) {
                return (false);
            } else {
                for (size_t i(0); i < COLUMN_COUNT; ++ i) {
                    columns[i] = (*position_)[i];
                }
                ++ position_;
                return (true);
            }
        }
    private:
        const std::vector<std::vector<std::string> > domain_;
        std::vector<std::vector<std::string> >::const_iterator position_;
    };

    class MockNameIteratorContext : public IteratorContext {
    public:
        MockNameIteratorContext(const MockAccessor& mock_accessor, int zone_id,
                                const std::string& name, bool subdomains) :
            searched_name_(name), cur_record_(0)
        {
            // 'hardcoded' names to trigger exceptions
            // On these names some exceptions are thrown, to test the robustness
            // of the find() method.
            if (searched_name_ == "dsexception.example.org.") {
                isc_throw(DataSourceError, "datasource exception on search");
            } else if (searched_name_ == "iscexception.example.org.") {
                isc_throw(isc::Exception, "isc exception on search");
            } else if (searched_name_ == "basicexception.example.org.") {
                throw std::exception();
            }

            cur_record_ = 0;
            const Domains& cur_records = mock_accessor.getMockRecords(zone_id);
            if (cur_records.count(name) > 0) {
                    // we're not aiming for efficiency in this test, simply
                    // copy the relevant vector from records
                    cur_name = cur_records.find(name)->second;
            } else if (subdomains) {
                cur_name.clear();
                // Just walk everything and check if it is a subdomain.
                // If it is, just copy all data from there.
                for (Domains::const_iterator i = cur_records.begin();
                     i != cur_records.end(); ++i) {
                    const Name local(i->first);
                    if (local.compare(Name(name)).getRelation() ==
                        isc::dns::NameComparisonResult::SUBDOMAIN) {
                        cur_name.insert(cur_name.end(), i->second.begin(),
                                        i->second.end());
                    }
                }
            } else {
                cur_name.clear();
            }
        }

        virtual bool getNext(std::string (&columns)[COLUMN_COUNT]) {
            if (searched_name_ == "dsexception.getnext.example.org.") {
                isc_throw(DataSourceError, "datasource exception on getnextrecord");
            } else if (searched_name_ == "iscexception.getnext.example.org.") {
                isc_throw(isc::Exception, "isc exception on getnextrecord");
            } else if (searched_name_ ==
                       "basicexception.getnext.example.org.") {
                throw std::exception();
            }

            if (cur_record_ < cur_name.size()) {
                for (size_t i = 0; i < COLUMN_COUNT; ++i) {
                    columns[i] = cur_name[cur_record_][i];
                }
                cur_record_++;
                return (true);
            } else {
                return (false);
            }
        }

    private:
        const std::string searched_name_;
        size_t cur_record_;
        std::vector< std::vector<std::string> > cur_name;
    };

    class MockIteratorContext : public IteratorContext {
    private:
        int step;
        const Domains& domains_;
    public:
        MockIteratorContext(const Domains& domains) :
            step(0), domains_(domains)
        { }
        virtual bool getNext(string (&data)[COLUMN_COUNT]) {
            // A special case: if the given set of domains is already empty,
            // we always return false.
            if (domains_.empty()) {
                return (false);
            }

            // Return faked data for tests
            // This is the sequence of zone data in the order of appearance
            // in the returned sequence from this iterator.
            typedef const char* ColumnText[4];
            const ColumnText zone_data[] = {
                // A couple of basic RRs at the zone origin.
                {"example.org", "A", "3600", "192.0.2.1"},
                {"example.org", "SOA", "3600", "ns1.example.org. "
                 "admin.example.org. 1234 3600 1800 2419200 7200"},
                // RRsets sharing the same owner name with multiple RRs.
                {"x.example.org", "A", "300", "192.0.2.1"},
                {"x.example.org", "A", "300", "192.0.2.2"},
                {"x.example.org", "AAAA", "300", "2001:db8::1"},
                {"x.example.org", "AAAA", "300", "2001:db8::2"},
                // RRSIGs.  Covered types are different and these two should
                // be distinguished.
                {"x.example.org", "RRSIG", "300",
                 "A 5 3 3600 20000101000000 20000201000000 12345 "
                 "example.org. FAKEFAKEFAKE"},
                {"x.example.org", "RRSIG", "300",
                 "AAAA 5 3 3600 20000101000000 20000201000000 12345 "
                 "example.org. FAKEFAKEFAKEFAKE"},
                // Mixture of different TTLs.  Covering both cases of small
                // then large and large then small.  In either case the smaller
                // TTL should win.
                {"ttldiff.example.org", "A", "300", "192.0.2.1"},
                {"ttldiff.example.org", "A", "600", "192.0.2.2"},
                {"ttldiff2.example.org", "AAAA", "600", "2001:db8::1"},
                {"ttldiff2.example.org", "AAAA", "300", "2001:db8::2"}};
            const size_t num_rrs = sizeof(zone_data) / sizeof(zone_data[0]);
            if (step > num_rrs) {
                ADD_FAILURE() << "Request past the end of iterator context";
            } else if (step < num_rrs) {
                data[DatabaseAccessor::NAME_COLUMN] = zone_data[step][0];
                data[DatabaseAccessor::TYPE_COLUMN] = zone_data[step][1];
                data[DatabaseAccessor::TTL_COLUMN] = zone_data[step][2];
                data[DatabaseAccessor::RDATA_COLUMN] = zone_data[step][3];
                ++step;
                return (true);
            }
            return (false);
        }
    };
    class EmptyIteratorContext : public IteratorContext {
    public:
        virtual bool getNext(string(&)[COLUMN_COUNT]) {
            return (false);
        }
    };
    class BadIteratorContext : public IteratorContext {
    private:
        int step;
    public:
        BadIteratorContext() :
            step(0)
        { }
        virtual bool getNext(string (&data)[COLUMN_COUNT]) {
            switch (step ++) {
                case 0:
                    data[DatabaseAccessor::NAME_COLUMN] = "x.example.org";
                    data[DatabaseAccessor::TYPE_COLUMN] = "A";
                    data[DatabaseAccessor::TTL_COLUMN] = "300";
                    data[DatabaseAccessor::RDATA_COLUMN] = "192.0.2.1";
                    return (true);
                case 1:
                    data[DatabaseAccessor::NAME_COLUMN] = "x.example.org";
                    data[DatabaseAccessor::TYPE_COLUMN] = "A";
                    data[DatabaseAccessor::TTL_COLUMN] = "301";
                    data[DatabaseAccessor::RDATA_COLUMN] = "192.0.2.2";
                    return (true);
                default:
                    ADD_FAILURE() <<
                        "Request past the end of iterator context";
                case 2:
                    return (false);
            }
        }
    };
    class MockDiffIteratorContext : public IteratorContext {
        const vector<JournalEntry> diffs_;
        vector<JournalEntry>::const_iterator it_;
    public:
        MockDiffIteratorContext(const vector<JournalEntry>& diffs) :
            diffs_(diffs), it_(diffs_.begin())
        {}
        virtual bool getNext(string (&data)[COLUMN_COUNT]) {
            if (it_ == diffs_.end()) {
                return (false);
            }
            data[DatabaseAccessor::NAME_COLUMN] =
                (*it_).data_[DatabaseAccessor::DIFF_NAME];
            data[DatabaseAccessor::TYPE_COLUMN] =
                (*it_).data_[DatabaseAccessor::DIFF_TYPE];
            data[DatabaseAccessor::TTL_COLUMN] =
                (*it_).data_[DatabaseAccessor::DIFF_TTL];
            data[DatabaseAccessor::RDATA_COLUMN] =
                (*it_).data_[DatabaseAccessor::DIFF_RDATA];
            ++it_;
            return (true);
        }
    };
public:
    virtual IteratorContextPtr getAllRecords(int id) const {
        if (id == READONLY_ZONE_ID) {
            return (IteratorContextPtr(new MockIteratorContext(
                                           *readonly_records_)));
        } else if (id == 13) {
            return (IteratorContextPtr());
        } else if (id == 0) {
            return (IteratorContextPtr(new EmptyIteratorContext()));
        } else if (id == -1) {
            return (IteratorContextPtr(new BadIteratorContext()));
        } else {
            isc_throw(isc::Unexpected, "Unknown zone ID");
        }
    }

    virtual IteratorContextPtr getRecords(const std::string& name, int id,
                                          bool subdomains) const
    {
        if (id == READONLY_ZONE_ID || id == WRITABLE_ZONE_ID) {
            return (IteratorContextPtr(
                        new MockNameIteratorContext(*this, id, name,
                                                    subdomains)));
        } else {
            // This iterator is bogus, but for the cases tested below that's
            // sufficient.
            return (IteratorContextPtr(
                        new MockNameIteratorContext(*this, READONLY_ZONE_ID,
                                                    name, subdomains)));
        }
    }

    virtual IteratorContextPtr getNSEC3Records(const std::string& hash,
                                               int) const
    {
        Domains::const_iterator it(nsec3_namespace_->find(hash));
        if (it == nsec3_namespace_->end()) {
            return (IteratorContextPtr(new EmptyIteratorContext()));
        } else {
            return (IteratorContextPtr(new DomainIterator(it->second)));
        }
    }

    virtual pair<bool, int> startUpdateZone(const std::string& zone_name,
                                            bool replace)
    {
        const pair<bool, int> zone_info = getZone(zone_name);
        if (!zone_info.first) {
            return (pair<bool, int>(false, 0));
        }

        // Prepare the record set for update.  If replacing the existing one,
        // we use an empty set; otherwise we use a writable copy of the
        // original.
        if (replace) {
            update_records_->clear();
            update_nsec3_namespace_->clear();
        } else {
            *update_records_ = *readonly_records_;
            *update_nsec3_namespace_ = nsec3_namespace_master_;
        }

        if (zone_name == "bad.example.org.") {
            return (pair<bool, int>(true, -1));
        } else if (zone_name == "null.example.org.") {
            return (pair<bool, int>(true, 13));
        } else {
            return (pair<bool, int>(true, WRITABLE_ZONE_ID));
        }
    }
    virtual void commit() {
        *readonly_records_ = *update_records_;
        *nsec3_namespace_ = *update_nsec3_namespace_;
    }

    virtual void rollback() {
        // Special hook: if something with a name of "throw.example.org"
        // has been added, trigger an imaginary unexpected event with an
        // exception.
        if (update_records_->count("throw.example.org.") > 0) {
            isc_throw(DataSourceError, "unexpected failure in rollback");
        }

        rollbacked_ = true;
    }

private:
    // Common subroutine for addRecordToZone and addNSEC3RecordToZone.
    void addRecord(Domains& domains,
                   const string (&columns)[ADD_COLUMN_COUNT])
    {
        // Copy the current value to cur_name.  If it doesn't exist,
        // operator[] will create a new one.
        cur_name_ = domains[columns[ADD_NAME]];

        vector<string> record_columns;
        record_columns.push_back(columns[ADD_TYPE]);
        record_columns.push_back(columns[ADD_TTL]);
        record_columns.push_back(columns[ADD_SIGTYPE]);
        record_columns.push_back(columns[ADD_RDATA]);
        record_columns.push_back(columns[ADD_NAME]);

        // copy back the added entry
        cur_name_.push_back(record_columns);
        domains[columns[DatabaseAccessor::ADD_NAME]] = cur_name_;

        // remember this one so that test cases can check it.
        copy(columns, columns + DatabaseAccessor::ADD_COLUMN_COUNT,
             columns_lastadded_);
    }

public:
    virtual void addRecordToZone(const string (&columns)[ADD_COLUMN_COUNT]) {
        addRecord(*update_records_, columns);
    }

    virtual void addNSEC3RecordToZone(
        const string (&columns)[ADD_NSEC3_COLUMN_COUNT])
    {
        // Convert the NSEC3 parameters in the normal (non NSEC3) style so
        // we can share the merge code, and then update using addRecord().
        string normal_columns[ADD_COLUMN_COUNT];

        normal_columns[ADD_TYPE] = columns[ADD_NSEC3_TYPE];
        normal_columns[ADD_TTL] = columns[ADD_NSEC3_TTL];
        normal_columns[ADD_SIGTYPE] = "";
        normal_columns[ADD_RDATA] = columns[ADD_NSEC3_RDATA];
        normal_columns[ADD_NAME] = columns[ADD_NSEC3_HASH];

        addRecord(*update_nsec3_namespace_, normal_columns);
    }

private:
    // Helper predicate class used in deleteRecordInZone().
    struct deleteMatch {
        deleteMatch(const string& type, const string& rdata) :
            type_(type), rdata_(rdata)
        {}
        bool operator()(const vector<string>& row) const {
            return (row[0] == type_ && row[3] == rdata_);
        }
        const string& type_;
        const string& rdata_;
    };

    // Common subroutine for deleteRecordinZone and deleteNSEC3RecordInZone.
    template<size_t param_count>
    void deleteRecord(Domains& domains, const string (&params)[param_count]) {
        vector<vector<string> >& records =
            domains[params[DatabaseAccessor::DEL_NAME]];
        records.erase(remove_if(records.begin(), records.end(),
                                deleteMatch(
                                    params[DatabaseAccessor::DEL_TYPE],
                                    params[DatabaseAccessor::DEL_RDATA])),
                      records.end());
        if (records.empty()) {
            domains.erase(params[DatabaseAccessor::DEL_NAME]);
        }
    }

public:
    virtual void deleteRecordInZone(const string (&params)[DEL_PARAM_COUNT]) {
        deleteRecord(*update_records_, params);
    }

    virtual void deleteNSEC3RecordInZone(
        const string (&params)[DEL_NSEC3_PARAM_COUNT])
    {
        deleteRecord(*update_nsec3_namespace_, params);
    }

    //
    // Helper methods to keep track of some update related activities
    //
    bool isRollbacked() const {
        return (rollbacked_);
    }

    const string* getLastAdded() const {
        return (columns_lastadded_);
    }

    // This allows the test code to get the accessor used in an update context
    boost::shared_ptr<const MockAccessor> getLatestClone() const {
        return (latest_clone_);
    }

    virtual std::string findPreviousName(int id, const std::string& rname)
        const
    {
        if (id == -1) {
            isc_throw(isc::NotImplemented, "Test not implemented behaviour");
        } else if (id == READONLY_ZONE_ID) {
            // For some specific names we intentionally return broken or
            // unexpected result.
            if (rname == "org.example.badnsec2.") {
                return ("badnsec1.example.org.");
            } else if (rname == "org.example.brokenname.") {
                return ("brokenname...example.org.");
            } else if (rname == "org.example.notimplnsec." ||
                       rname == "org.example.wild.here.") {
                isc_throw(isc::NotImplemented, "Not implemented in this test");
            }

            // For the general case, we search for the first name N in the
            // domains that meets N >= reverse(rname) using lower_bound.
            // The "previous name" is the name of the previous entry of N.
            // Note that Domains are internally sorted by the Name comparison
            // order.  Due to the API requirement we are given a reversed
            // name (rname), so we need to reverse it again to convert it
            // to the original name.
            Domains::const_iterator it(readonly_records_->lower_bound(
                                           Name(rname).reverse().toText()));
            if (it == readonly_records_->begin()) {
                isc_throw(isc::Unexpected, "Unexpected name");
            }
            if (it == readonly_records_->end()) {
                return ((*readonly_records_->rbegin()).first);
            }
            return ((*(--it)).first);
        } else {
            isc_throw(isc::Unexpected, "Unknown zone ID");
        }
    }
    virtual std::string findPreviousNSEC3Hash(int,
                                              const std::string& hash) const
    {
        // TODO: Provide some broken data, but it is not known yet how broken
        // they'll have to be.
        Domains::const_iterator it(nsec3_namespace_->lower_bound(hash));
        // We got just after the one we want
        if (it == nsec3_namespace_->begin()) {
            // Hmm, we got something really small. So we wrap around.
            // This is one after the last, so after decreasing it we'll get
            // the biggest.
            it = nsec3_namespace_->end();
        }
        return ((--it)->first);
    }
    virtual void addRecordDiff(int id, uint32_t serial,
                               DiffOperation operation,
                               const std::string (&data)[DIFF_PARAM_COUNT])
    {
        if (id == 13) { // The null zone doesn't support journaling
            isc_throw(isc::NotImplemented, "Test not implemented behaviour");
        } else if (id == -1) { // Bad zone throws
            isc_throw(DataSourceError, "Test error");
        } else {
            journal_entries_->push_back(JournalEntry(id, serial, operation,
                                                     data));
        }
    }

    virtual IteratorContextPtr getDiffs(int id, uint32_t start,
                                        uint32_t end) const
    {
        vector<JournalEntry> selected_jnl;

        for (vector<JournalEntry>::const_iterator it =
                 journal_entries_->begin();
             it != journal_entries_->end(); ++it)
        {
            // For simplicity we assume this method is called for the
            // "readonly" zone possibly after making updates on the "writable"
            // copy and committing them.
            if (id != READONLY_ZONE_ID) {
                continue;
            }

            // Note: the following logic is not 100% accurate in terms of
            // serial number arithmetic; we prefer brevity for testing.
            // Skip until we see the starting serial.  Once we started
            // recording this condition is ignored (to support wrap-around
            // case).  Also, it ignores the RR type; it only checks the
            // versions.
            if ((*it).serial_ < start && selected_jnl.empty()) {
                continue;
            }
            if ((*it).serial_ > end) { // gone over the end serial. we're done.
                break;
            }
            selected_jnl.push_back(*it);
        }

        // Check if we've found the requested range.  If not, throw.
        if (selected_jnl.empty() || selected_jnl.front().serial_ != start ||
            selected_jnl.back().serial_ != end) {
            isc_throw(NoSuchSerial, "requested diff range is not found");
        }

        return (IteratorContextPtr(new MockDiffIteratorContext(selected_jnl)));
    }

    // Check the journal is as expected and clear the journal
    void checkJournal(const std::vector<JournalEntry> &expected) const {
        std::vector<JournalEntry> journal;
        // Clean the journal, but keep local copy to check
        journal.swap(*journal_entries_);
        ASSERT_EQ(expected.size(), journal.size());
        for (size_t i = 0; i < expected.size(); ++ i) {
            EXPECT_TRUE(expected[i] == journal[i]);
        }
    }

private:
    // The following member variables are storage and/or update work space
    // of the test zone.  The "master"s are the real objects that contain
    // the data, and they are shared among all accessors cloned from
    // an initially created one.  The "copy" data will be used for read-only
    // transaction.  The pointer members allow the sharing.
    // "readonly" is for normal lookups.  "update" is the workspace for
    // updates.  When update starts it will be initialized either as an
    // empty set (when replacing the entire zone) or as a copy of the
    // "readonly" one.  "empty" is a sentinel to produce negative results.
    Domains readonly_records_master_;
    Domains readonly_records_copy_;
    Domains* readonly_records_;
    Domains update_records_master_;
    Domains* update_records_;
    Domains nsec3_namespace_master_;
    Domains* nsec3_namespace_;
    Domains update_nsec3_namespace_master_;
    Domains* update_nsec3_namespace_;
    const Domains empty_records_master_;
    const Domains* empty_records_;

    // The journal data
    std::vector<JournalEntry> journal_entries_master_;
    std::vector<JournalEntry>* journal_entries_;

    // used as temporary storage after searchForRecord() and during
    // getNextRecord() calls, as well as during the building of the
    // fake data
    std::vector< std::vector<std::string> > cur_name_;

    // The columns that were most recently added via addRecordToZone()
    string columns_lastadded_[ADD_COLUMN_COUNT];

    // Whether rollback operation has been performed for the database.
    // Not useful except for purely testing purpose.
    bool rollbacked_;

    // Remember the mock accessor that was last cloned
    boost::shared_ptr<MockAccessor> latest_clone_;

    // Internal flag for duplicate check
    bool did_transaction_;

    const Domains& getMockRecords(int zone_id) const {
        if (zone_id == READONLY_ZONE_ID) {
            return (*readonly_records_);
        } else if (zone_id == WRITABLE_ZONE_ID) {
            return (*update_records_);
        }
        return (*empty_records_);
    }

    // Adds one record to the current name in the database
    // The actual data will not be added to 'records' until
    // addCurName() is called
    void addRecord(const std::string& type,
                   const std::string& ttl,
                   const std::string& sigtype,
                   const std::string& rdata) {
        std::vector<std::string> columns;
        columns.push_back(type);
        columns.push_back(ttl);
        columns.push_back(sigtype);
        columns.push_back(rdata);
        cur_name_.push_back(columns);
    }

    // Adds all records we just built with calls to addRecords
    // to the actual fake database. This will clear cur_name_,
    // so we can immediately start adding new records.
    void addCurName(const std::string& name) {
        ASSERT_EQ(0, readonly_records_->count(name));
        // Append the name to all of them
        for (std::vector<std::vector<std::string> >::iterator
             i = cur_name_.begin(); i != cur_name_.end(); ++ i) {
            i->push_back(name);
        }
        (*readonly_records_)[name] = cur_name_;
        cur_name_.clear();
    }

    // Works in a similar way to addCurName, but it is added to
    // the NSEC3 namespace. You don't provide the full name, only
    // the hash part.
    void addCurHash(const std::string& hash) {
        ASSERT_EQ(0, nsec3_namespace_->count(hash));
        // Append the name to all of them
        for (std::vector<std::vector<std::string> >::iterator
             i = cur_name_.begin(); i != cur_name_.end(); ++ i) {
            i->push_back(hash);
        }
        (*nsec3_namespace_)[hash] = cur_name_;
        cur_name_.clear();
    }

    // Fills the database with zone data.
    // This method constructs a number of resource records (with addRecord),
    // which will all be added for one domain name to the fake database
    // (with addCurName). So for instance the first set of calls create
    // data for the name 'www.example.org', which will consist of one A RRset
    // of one record, and one AAAA RRset of two records.
    // The order in which they are added is the order in which getNextRecord()
    // will return them (so we can test whether find() etc. support data that
    // might not come in 'normal' order)
    // It shall immediately fail if you try to add the same name twice.
    void fillData() {
        const char* prev_name = NULL;
        for (int i = 0; TEST_RECORDS[i][0] != NULL; ++i) {
            if (prev_name != NULL &&
                strcmp(prev_name, TEST_RECORDS[i][0]) != 0) {
                addCurName(prev_name);
            }
            prev_name = TEST_RECORDS[i][0];
            addRecord(TEST_RECORDS[i][1], TEST_RECORDS[i][2],
                      TEST_RECORDS[i][3], TEST_RECORDS[i][4]);
        }
        addCurName(prev_name);
        prev_name = NULL;
        for (int i = 0; TEST_NSEC3_RECORDS[i][0] != NULL; ++i) {
            if (prev_name != NULL &&
                strcmp(prev_name, TEST_NSEC3_RECORDS[i][0]) != 0) {
                addCurHash(prev_name);
            }
            prev_name = TEST_NSEC3_RECORDS[i][0];
            addRecord(TEST_NSEC3_RECORDS[i][1], TEST_NSEC3_RECORDS[i][2],
                      TEST_NSEC3_RECORDS[i][3], TEST_NSEC3_RECORDS[i][4]);
        }
        addCurHash(prev_name);
    }

public:
    // This adds the NSEC3PARAM into the apex, so we can perform some NSEC3
    // tests. Note that the NSEC3 namespace is available in other tests, but
    // it should not be accessed at that time.
    void enableNSEC3() {
        for (int i = 0; TEST_NSEC3PARAM_RECORDS[i][0] != NULL; ++i) {
            vector<string> param;
            param.push_back(TEST_NSEC3PARAM_RECORDS[i][1]); // RRtype
            param.push_back(TEST_NSEC3PARAM_RECORDS[i][2]); // TTL
            param.push_back("");                            // sigtype, unused
            param.push_back(TEST_NSEC3PARAM_RECORDS[i][4]); // RDATA
            param.push_back(TEST_NSEC3PARAM_RECORDS[i][0]); // owner name
            (*readonly_records_)[param.back()].push_back(param);
        }
    }
};
}

namespace isc {
namespace datasrc {
namespace test {

const char* const TEST_RECORDS[][5] = {
    // some plain data
    {"www.example.org.", "A", "3600", "", "192.0.2.1"},
    {"www.example.org.", "AAAA", "3600", "", "2001:db8::1"},
    {"www.example.org.", "AAAA", "3600", "", "2001:db8::2"},
    {"www.example.org.", "NSEC", "3600", "", "www2.example.org. A AAAA NSEC RRSIG"},
    {"www.example.org.", "RRSIG", "3600", "", "NSEC 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"www2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"www2.example.org.", "AAAA", "3600", "", "2001:db8::1"},
    {"www2.example.org.", "A", "3600", "", "192.0.2.2"},

    {"cname.example.org.", "CNAME", "3600", "", "www.example.org."},

    // some DNSSEC-'signed' data
    {"signed1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"signed1.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"signed1.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE"},
    {"signed1.example.org.", "AAAA", "3600", "", "2001:db8::1"},
    {"signed1.example.org.", "AAAA", "3600", "", "2001:db8::2"},
    {"signed1.example.org.", "RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"signedcname1.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"signedcname1.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // special case might fail; sig is for cname, which isn't there (should be ignored)
    // (ignoring of 'normal' other type is done above by www.)
    {"acnamesig1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"acnamesig1.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig1.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // let's pretend we have a database that is not careful
    // about the order in which it returns data
    {"signed2.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signed2.example.org.", "AAAA", "3600", "", "2001:db8::2"},
    {"signed2.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE"},
    {"signed2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"signed2.example.org.", "RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signed2.example.org.", "AAAA", "3600", "", "2001:db8::1"},

    {"signedcname2.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signedcname2.example.org.", "CNAME", "3600", "", "www.example.org."},

    {"acnamesig2.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"acnamesig2.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"acnamesig3.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig3.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig3.example.org.", "A", "3600", "", "192.0.2.1"},

    {"ttldiff1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"ttldiff1.example.org.", "A", "360", "", "192.0.2.2"},

    {"ttldiff2.example.org.", "A", "360", "", "192.0.2.1"},
    {"ttldiff2.example.org.", "A", "3600", "", "192.0.2.2"},

    // also add some intentionally bad data
    {"badcname1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"badcname1.example.org.", "CNAME", "3600", "", "www.example.org."},

    {"badcname2.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"badcname2.example.org.", "A", "3600", "", "192.0.2.1"},

    {"badcname3.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"badcname3.example.org.", "CNAME", "3600", "", "www.example2.org."},

    {"badrdata.example.org.", "A", "3600", "", "bad"},

    {"badtype.example.org.", "BAD_TYPE", "3600", "", "192.0.2.1"},

    {"badttl.example.org.", "A", "badttl", "", "192.0.2.1"},

    {"badsig.example.org.", "A", "badttl", "", "192.0.2.1"},
    {"badsig.example.org.", "RRSIG", "3600", "", "A 5 3 3600 somebaddata 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"badsigtype.example.org.", "A", "3600", "", "192.0.2.1"},
    {"badsigtype.example.org.", "RRSIG", "3600", "TXT", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // Data for testing delegation (with NS and DNAME)
    {"delegation.example.org.", "NS", "3600", "", "ns.example.com."},
    {"delegation.example.org.", "NS", "3600", "",
     "ns.delegation.example.org."},
    {"delegation.example.org.", "DS", "3600", "", "1 1 2 abcd"},
    {"delegation.example.org.", "RRSIG", "3600", "", "NS 5 3 3600 "
     "20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"delegation.example.org.", "RRSIG", "3600", "", "DS 5 3 3600 "
     "20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"ns.delegation.example.org.", "A", "3600", "", "192.0.2.1"},
    {"deep.below.delegation.example.org.", "A", "3600", "", "192.0.2.1"},

    {"dname.example.org.", "A", "3600", "", "192.0.2.1"},
    {"dname.example.org.", "DNAME", "3600", "", "dname.example.com."},
    {"dname.example.org.", "RRSIG", "3600", "",
     "DNAME 5 3 3600 20000101000000 20000201000000 12345 "
     "example.org. FAKEFAKEFAKE"},

    {"below.dname.example.org.", "A", "3600", "", "192.0.2.1"},

    // Insecure delegation (i.e., no DS at the delegation point)
    {"insecdelegation.example.org.", "NS", "3600", "", "ns.example.com."},
    {"insecdelegation.example.org.", "NSEC", "3600", "",
     "dummy.example.org. NS NSEC"},
    // and a DS under the zone cut. Such an RR shouldn't exist in a sane zone,
    // but it could by error or some malicious attempt.  It shouldn't confuse
    // the implementation)
    {"child.insecdelegation.example.org.", "DS", "3600", "", "DS 5 3 3600 "
     "20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // Delegation NS and other ordinary type of RR coexist at the same
    // name.  This is deviant (except for some special cases like the other
    // RR could be used for addressing the NS name), but as long as the
    // other records are hidden behind the delegation for normal queries
    // it's not necessarily harmful. (so "broken" may be too strong, but we
    // keep the name since it could be in a chain of sorted names for DNSSEC
    // processing and renaming them may have other bad effects for tests).
    {"brokenns1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"brokenns1.example.org.", "NS", "3600", "", "ns.example.com."},

    // Now double DNAME, to test failure mode
    {"baddname.example.org.", "DNAME", "3600", "", "dname1.example.com."},
    {"baddname.example.org.", "DNAME", "3600", "", "dname2.example.com."},

    // Put some data into apex (including NS) so we can check our NS
    // doesn't break anything
    {"example.org.", "SOA", "3600", "", "ns1.example.org. admin.example.org. "
     "1234 3600 1800 2419200 7200" },
    {"example.org.", "NS", "3600", "", "ns.example.com."},
    {"example.org.", "A", "3600", "", "192.0.2.1"},
    // Note that the RDATA text is "normalized", i.e., identical to what
    // Rdata::toText() would produce.  some tests rely on that behavior.
    {"example.org.", "NSEC", "3600", "",
     "acnamesig1.example.org. A NS RRSIG NSEC"},
    {"example.org.", "RRSIG", "3600", "", "SOA 5 3 3600 20000101000000 "
              "20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"example.org.", "RRSIG", "3600", "", "NSEC 5 3 3600 20000101000000 "
              "20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"example.org.", "RRSIG", "3600", "", "NS 5 3 3600 20000101000000 "
              "20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // This is because of empty domain test
    {"a.b.example.org.", "A", "3600", "", "192.0.2.1"},

    // Something for wildcards
    {"*.wild.example.org.", "A", "3600", "", "192.0.2.5"},
    {"*.wild.example.org.", "RRSIG", "3600", "A", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"*.wild.example.org.", "NSEC", "3600", "", "cancel.here.wild.example.org. A NSEC RRSIG"},
    {"*.wild.example.org.", "RRSIG", "3600", "", "NSEC 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"cancel.here.wild.example.org.", "AAAA", "3600", "", "2001:db8::5"},
    {"delegatedwild.example.org.", "NS", "3600", "", "ns.example.com."},
    {"*.delegatedwild.example.org.", "A", "3600", "", "192.0.2.5"},
    {"wild.*.foo.example.org.", "A", "3600", "", "192.0.2.5"},
    {"wild.*.foo.*.bar.example.org.", "A", "3600", "", "192.0.2.5"},
    {"wild.*.foo.*.bar.example.org.", "NSEC", "3600", "",
     "brokenns1.example.org. A NSEC"},
    {"bao.example.org.", "NSEC", "3600", "", "wild.*.foo.*.bar.example.org. NSEC"},
    {"*.cnamewild.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"*.dnamewild.example.org.", "DNAME", "3600", "", "dname.example.com."},
    {"*.nswild.example.org.", "NS", "3600", "", "ns.example.com."},
    // For NSEC empty non-terminal
    {"l.example.org.", "NSEC", "3600", "", "empty.nonterminal.example.org. NSEC"},
    {"empty.nonterminal.example.org.", "A", "3600", "", "192.0.2.1"},
    // Invalid rdata
    {"invalidrdata.example.org.", "A", "3600", "", "Bunch of nonsense"},
    {"invalidrdata2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"invalidrdata2.example.org.", "RRSIG", "3600", "", "Nonsense"},

    {NULL, NULL, NULL, NULL, NULL},
};

const char* TEST_NSEC3PARAM_RECORDS[][5] = {
    {"example.org.", "NSEC3PARAM", "3600", "", "1 0 12 aabbccdd"},
    {"example.org.", "RRSIG", "3600", "", "NSEC3PARAM 5 3 3600 20000101000000 "
     "20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {NULL, NULL, NULL, NULL, NULL}
};

const char* TEST_NSEC3_RECORDS[][5] = {
    {apex_hash, "NSEC3", "300", "", "1 1 12 AABBCCDD 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A RRSIG"},
    {apex_hash, "RRSIG", "300", "", "NSEC3 5 4 7200 20100410172647 20100311172647 63192 example.org. gNIVj4T8t51fEU6kOPpvK7HOGBFZGbalN5ZK mInyrww6UWZsUNdw07ge6/U6HfG+/s61RZ/L is2M6yUWHyXbNbj/QqwqgadG5dhxTArfuR02 xP600x0fWX8LXzW4yLMdKVxGbzYT+vvGz71o 8gHSY5vYTtothcZQa4BMKhmGQEk="},
    {ns1_hash, "NSEC3", "300", "", "1 1 12 AABBCCDD 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A RRSIG"},
    {ns1_hash, "RRSIG", "300", "", "NSEC3 5 4 7200 20100410172647 20100311172647 63192 example.org. gNIVj4T8t51fEU6kOPpvK7HOGBFZGbalN5ZK mInyrww6UWZsUNdw07ge6/U6HfG+/s61RZ/L is2M6yUWHyXbNbj/QqwqgadG5dhxTArfuR02 xP600x0fWX8LXzW4yLMdKVxGbzYT+vvGz71o 8gHSY5vYTtothcZQa4BMKhmGQEk="},
    {w_hash, "NSEC3", "300", "", "1 1 12 AABBCCDD 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A RRSIG"},
    {w_hash, "RRSIG", "300", "", "NSEC3 5 4 7200 20100410172647 20100311172647 63192 example.org. gNIVj4T8t51fEU6kOPpvK7HOGBFZGbalN5ZK mInyrww6UWZsUNdw07ge6/U6HfG+/s61RZ/L is2M6yUWHyXbNbj/QqwqgadG5dhxTArfuR02 xP600x0fWX8LXzW4yLMdKVxGbzYT+vvGz71o 8gHSY5vYTtothcZQa4BMKhmGQEk="},
    {zzz_hash, "NSEC3", "300", "", "1 1 12 AABBCCDD 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A RRSIG"},
    {zzz_hash, "RRSIG", "300", "", "NSEC3 5 4 7200 20100410172647 20100311172647 63192 example.org. gNIVj4T8t51fEU6kOPpvK7HOGBFZGbalN5ZK mInyrww6UWZsUNdw07ge6/U6HfG+/s61RZ/L is2M6yUWHyXbNbj/QqwqgadG5dhxTArfuR02 xP600x0fWX8LXzW4yLMdKVxGbzYT+vvGz71o 8gHSY5vYTtothcZQa4BMKhmGQEk="},
    {NULL, NULL, NULL, NULL, NULL}
};

DatabaseClientTest::DatabaseClientTest() :
    zname_("example.org"), qname_("www.example.org"),
    qclass_(dns::RRClass::IN()),
    qtype_(dns::RRType::A()),
    rrttl_(3600)
{
    // Test IN/A RDATA to be added in update tests.  Intentionally using
    // different data than the initial data configured in the MockAccessor.
    rrset_.reset(new RRset(qname_, qclass_, qtype_, rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(),
                                        rrset_->getClass(), "192.0.2.2"));
    soa_.reset(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
    soa_->addRdata(rdata::createRdata(soa_->getType(), soa_->getClass(),
                                      "ns1.example.org. admin.example.org. "
                                      "1234 3600 1800 2419200 7200"));

    // And its RRSIG.  Also different from the configured one.
    rrsigset_.reset(new RRset(qname_, qclass_, RRType::RRSIG(),
                              rrttl_));
    rrsigset_->addRdata(rdata::createRdata(rrsigset_->getType(),
                                           rrsigset_->getClass(),
                                           "A 5 3 0 20000101000000 "
                                           "20000201000000 0 example.org. "
                                           "FAKEFAKEFAKE"));
}

void
DatabaseClientTest::createClient(const DatabaseClientTestParam* test_param) {
    current_accessor_ = test_param->accessor_creator();
    is_mock_ = (dynamic_cast<MockAccessor*>(current_accessor_.get()) != NULL);
    client_.reset(new DatabaseClient(qclass_, current_accessor_));

    // set up the commonly used finder.
    const DataSourceClient::FindResult result(client_->findZone(zname_));
    assert(result.code == result::SUCCESS);
    finder_ = dynamic_pointer_cast<DatabaseClient::Finder>(
        result.zone_finder);
}

void
DatabaseClientTest::checkZoneFinder(const DataSourceClient::FindResult& zone) {
    ASSERT_NE(ZoneFinderPtr(), zone.zone_finder) << "No zone finder";
    boost::shared_ptr<DatabaseClient::Finder> finder(
        boost::dynamic_pointer_cast<DatabaseClient::Finder>(
            zone.zone_finder));
    ASSERT_NE(boost::shared_ptr<DatabaseClient::Finder>(), finder) <<
        "Wrong type of finder";
    if (is_mock_) {
        EXPECT_EQ(READONLY_ZONE_ID, finder->zone_id());
    }
    EXPECT_EQ(current_accessor_.get(), &finder->getAccessor());
}

boost::shared_ptr<DatabaseClient::Finder>
DatabaseClientTest::getFinder() {
    DataSourceClient::FindResult zone(client_->findZone(zname_));
    EXPECT_EQ(result::SUCCESS, zone.code);
    boost::shared_ptr<DatabaseClient::Finder> finder(
        boost::dynamic_pointer_cast<DatabaseClient::Finder>(
            zone.zone_finder));
    if (is_mock_) {
        EXPECT_EQ(READONLY_ZONE_ID, finder->zone_id());
    }

    return (finder);
}

bool
DatabaseClientTest::isRollbacked(bool expected) const {
    if (is_mock_) {
        const MockAccessor& mock_accessor =
            dynamic_cast<const MockAccessor&>(*update_accessor_);
        return (mock_accessor.isRollbacked());
    } else {
        return (expected);
    }
}

void
DatabaseClientTest::checkLastAdded(const char* const expected[]) const {
    if (is_mock_) {
        const MockAccessor* mock_accessor =
            dynamic_cast<const MockAccessor*>(current_accessor_.get());
        for (int i = 0; i < DatabaseAccessor::ADD_COLUMN_COUNT; ++i) {
            EXPECT_EQ(expected[i],
                      mock_accessor->getLatestClone()->getLastAdded()[i]);
        }
    }
}

void
DatabaseClientTest::setUpdateAccessor() {
    if (is_mock_) {
        const MockAccessor* mock_accessor =
            dynamic_cast<const MockAccessor*>(current_accessor_.get());
        update_accessor_ = mock_accessor->getLatestClone();
    }
}

void
DatabaseClientTest::checkJournal(const std::vector<JournalEntry>& expected) {
    if (is_mock_) {
        const MockAccessor* mock_accessor =
            dynamic_cast<const MockAccessor*>(current_accessor_.get());
        mock_accessor->checkJournal(expected);
    } else {
        // For other generic databases, retrieve the diff using the
        // reader class and compare the resulting sequence of RRset.
        // For simplicity we only consider the case where the expected
        // sequence is not empty.
        ASSERT_FALSE(expected.empty());
        const Name zone_name(expected.front().
                             data_[DatabaseAccessor::DIFF_NAME]);
        ZoneJournalReaderPtr jnl_reader =
            client_->getJournalReader(zone_name,
                                      expected.front().serial_,
                                      expected.back().serial_).second;
        ASSERT_TRUE(jnl_reader);
        ConstRRsetPtr rrset;
        std::vector<JournalEntry>::const_iterator it = expected.begin();
        for (rrset = jnl_reader->getNextDiff();
             rrset && it != expected.end();
             rrset = jnl_reader->getNextDiff(), ++it) {
            typedef DatabaseAccessor Accessor;
            RRsetPtr expected_rrset(
                new RRset(Name((*it).data_[Accessor::DIFF_NAME]),
                          qclass_,
                          RRType((*it).data_[Accessor::DIFF_TYPE]),
                          RRTTL((*it).data_[Accessor::DIFF_TTL])));
            expected_rrset->addRdata(
                rdata::createRdata(expected_rrset->getType(),
                                   expected_rrset->getClass(),
                                   (*it).data_[Accessor::DIFF_RDATA]));
            rrsetCheck(expected_rrset, rrset);
        }
        // We should have examined all entries of both expected and
        // actual data.
        EXPECT_TRUE(it == expected.end());
        ASSERT_FALSE(rrset);
    }
}

void
DatabaseClientTest::allowMoreTransaction(bool is_allowed) {
    if (is_mock_) {
        // Use a separate variable for MockAccessor&; some compilers
        // would be confused otherwise.
        MockAccessor& mock_accessor =
            dynamic_cast<MockAccessor&>(*current_accessor_);
        mock_accessor.allowMoreTransaction(is_allowed);
    }
}

void
loadTestDataGeneric(DatabaseAccessor& accessor) {
    accessor.startUpdateZone("example.org.", true);
    string columns[DatabaseAccessor::ADD_COLUMN_COUNT];
    for (int i = 0; TEST_RECORDS[i][0] != NULL; ++i) {
        columns[DatabaseAccessor::ADD_NAME] = TEST_RECORDS[i][0];
        columns[DatabaseAccessor::ADD_REV_NAME] =
            Name(columns[DatabaseAccessor::ADD_NAME]).reverse().toText();
        columns[DatabaseAccessor::ADD_TYPE] = TEST_RECORDS[i][1];
        columns[DatabaseAccessor::ADD_TTL] = TEST_RECORDS[i][2];
        columns[DatabaseAccessor::ADD_SIGTYPE] = TEST_RECORDS[i][3];
        columns[DatabaseAccessor::ADD_RDATA] = TEST_RECORDS[i][4];

        accessor.addRecordToZone(columns);
    }
    // We don't add NSEC3s until we are explicitly told we need them
    // in enableNSEC3(); these would break some non NSEC3 tests.
    accessor.commit();
}

void
enableNSEC3Generic(DatabaseAccessor& accessor) {
    accessor.startUpdateZone("example.org.", false);

    // Add NSECPARAM at the zone origin
    for (int i = 0; TEST_NSEC3PARAM_RECORDS[i][0] != NULL; ++i) {
        const string param_columns[DatabaseAccessor::ADD_COLUMN_COUNT] = {
            TEST_NSEC3PARAM_RECORDS[i][0], // name
            Name(param_columns[DatabaseAccessor::ADD_NAME]).reverse().toText(),
            // revname
            TEST_NSEC3PARAM_RECORDS[i][2],   // TTL
            TEST_NSEC3PARAM_RECORDS[i][1],   // RR type
            TEST_NSEC3PARAM_RECORDS[i][3],   // sigtype
            TEST_NSEC3PARAM_RECORDS[i][4] }; // RDATA
        accessor.addRecordToZone(param_columns);
    }

    // Add NSEC3s
    for (int i = 0; TEST_NSEC3_RECORDS[i][0] != NULL; ++i) {
        const string nsec3_columns[DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT] =
            {
                TEST_NSEC3_RECORDS[i][0], // Hash
                TEST_NSEC3_RECORDS[i][2], // TTL
                TEST_NSEC3_RECORDS[i][1], // RR type
                TEST_NSEC3_RECORDS[i][4]  // RDATA
            };
        accessor.addNSEC3RecordToZone(nsec3_columns);
    }

    accessor.commit();
}

} // namespace test
} // namespace datasrc
} // namespace isc

namespace {
// This tests the default getRecords behaviour, throwing NotImplemented
TEST(DatabaseConnectionTest, getRecords) {
    EXPECT_THROW(NopAccessor().getRecords(".", 1, false),
                 isc::NotImplemented);
}

// This tests the default getAllRecords behaviour, throwing NotImplemented
TEST(DatabaseConnectionTest, getAllRecords) {
    // The parameters don't matter
    EXPECT_THROW(NopAccessor().getAllRecords(1),
                 isc::NotImplemented);
}

// The following two lines instantiate test cases with concrete accessor
// classes to be tested.

boost::shared_ptr<DatabaseAccessor>
createMockAccessor() {
    return (boost::shared_ptr<DatabaseAccessor>(new MockAccessor()));
}

void
mockEnableNSEC3(DatabaseAccessor& accessor) {
    dynamic_cast<MockAccessor&>(accessor).enableNSEC3();
}

const DatabaseClientTestParam mock_param = { createMockAccessor,
                                             mockEnableNSEC3 };

INSTANTIATE_TEST_CASE_P(, DatabaseClientTest, ::testing::Values(&mock_param));

// This inherit the DatabaseClientTest cases except for the parameterized
// setup; it's intended to be used selected test cases that only work for mock
// data sources.
class MockDatabaseClientTest : public DatabaseClientTest {
protected:
    // Override SetUp() to avoid parameterized setup
    virtual void SetUp() {
        createClient(&mock_param);
    }
};

TEST_P(DatabaseClientTest, zoneNotFound) {
    EXPECT_EQ(result::NOTFOUND, client_->findZone(Name("example.com")).code);
}

TEST_P(DatabaseClientTest, exactZone) {
    const DataSourceClient::FindResult result =
        client_->findZone(Name("example.org"));
    EXPECT_EQ(result::SUCCESS, result.code);
    checkZoneFinder(result);
}

TEST_P(DatabaseClientTest, superZone) {
    const DataSourceClient::FindResult result =
        client_->findZone(Name("sub.example.org"));
    EXPECT_EQ(result::PARTIALMATCH, result.code);
    checkZoneFinder(result);
}

// This test doesn't depend on derived accessor class, so we use TEST().
TEST(GenericDatabaseClientTest, noAccessorException) {
    // We need a dummy variable here; some compiler would regard it a mere
    // declaration instead of an instantiation and make the test fail.
    EXPECT_THROW(DatabaseClient dummy(RRClass::IN(),
                                      boost::shared_ptr<DatabaseAccessor>()),
                 isc::InvalidParameter);
}

// If the zone doesn't exist, exception is thrown
TEST_P(DatabaseClientTest, noZoneIterator) {
    EXPECT_THROW(client_->getIterator(Name("example.com")), DataSourceError);
}

// If the zone doesn't exist and iteration is not implemented, it still throws
// the exception it doesn't exist
TEST(GenericDatabaseClientTest, noZoneNotImplementedIterator) {
    EXPECT_THROW(DatabaseClient(RRClass::IN(),
                                boost::shared_ptr<DatabaseAccessor>(
                                    new NopAccessor())).getIterator(
                                        Name("example.com")),
                 DataSourceError);
}

TEST(GenericDatabaseClientTest, notImplementedIterator) {
    EXPECT_THROW(DatabaseClient(RRClass::IN(),
                    boost::shared_ptr<DatabaseAccessor>(
                        new NopAccessor())).getIterator(Name("example.org")),
                 isc::NotImplemented);
}

// Pretend a bug in the connection and pass NULL as the context
// Should not crash, but gracefully throw.  Works for the mock accessor only.
TEST_F(MockDatabaseClientTest, nullIteratorContext) {
    EXPECT_THROW(client_->getIterator(Name("null.example.org")),
                 isc::Unexpected);
}

// It doesn't crash or anything if the zone is completely empty.
// Works for the mock accessor only.
TEST_F(MockDatabaseClientTest, emptyIterator) {
    ZoneIteratorPtr it(client_->getIterator(Name("empty.example.org")));
    EXPECT_EQ(ConstRRsetPtr(), it->getNextRRset());
    // This is past the end, it should throw
    EXPECT_THROW(it->getNextRRset(), isc::Unexpected);
}

// checks if the given rrset matches the
// given name, class, type and rdatas
void
checkRRset(isc::dns::ConstRRsetPtr rrset,
           const isc::dns::Name& name,
           const isc::dns::RRClass& rrclass,
           const isc::dns::RRType& rrtype,
           const isc::dns::RRTTL& rrttl,
           const std::vector<std::string>& rdatas) {
    isc::dns::RRsetPtr expected_rrset(
        new isc::dns::RRset(name, rrclass, rrtype, rrttl));
    for (unsigned int i = 0; i < rdatas.size(); ++i) {
        expected_rrset->addRdata(
            isc::dns::rdata::createRdata(rrtype, rrclass,
                                         rdatas[i]));
    }
    rrsetCheck(expected_rrset, rrset);
}

// Iterate through a zone, common case
TEST_P(DatabaseClientTest, iterator) {
    ZoneIteratorPtr it(client_->getIterator(Name("example.org")));
    ConstRRsetPtr rrset(it->getNextRRset());
    ASSERT_NE(ConstRRsetPtr(), rrset);

    // The first name should be the zone origin.
    EXPECT_EQ(zname_, rrset->getName());
}

// Supplemental structure used in the couple of tests below.  It represents
// parameters of an expected RRset containing up to two RDATAs.  If it contains
// only one RDATA, rdata2 is NULL.
struct ExpectedRRset {
    const char* const name;
    const RRType rrtype;
    const RRTTL rrttl;
    const char* const rdata1;
    const char* const rdata2;
};

// Common checker for the iterator tests below.  It extracts RRsets from the
// give iterator and compare them to the expected sequence.
void
checkIteratorSequence(ZoneIterator& it, ExpectedRRset expected_sequence[],
                      size_t num_rrsets)
{
    vector<string> expected_rdatas;
    for (size_t i = 0; i < num_rrsets; ++i) {
        const ConstRRsetPtr rrset = it.getNextRRset();
        ASSERT_TRUE(rrset);

        expected_rdatas.clear();
        expected_rdatas.push_back(expected_sequence[i].rdata1);
        if (expected_sequence[i].rdata2 != NULL) {
            expected_rdatas.push_back(expected_sequence[i].rdata2);
        }
        checkRRset(rrset, Name(expected_sequence[i].name), RRClass::IN(),
                   expected_sequence[i].rrtype, expected_sequence[i].rrttl,
                   expected_rdatas);
    }
    EXPECT_FALSE(it.getNextRRset());
}

TEST_F(MockDatabaseClientTest, iterator) {
    // This version of test creates an iterator that combines same types of
    // RRs into single RRsets.
    ExpectedRRset expected_sequence[] = {
        {"example.org", RRType::A(), rrttl_, "192.0.2.1", NULL},
        {"example.org", RRType::SOA(), rrttl_,
         "ns1.example.org. admin.example.org. 1234 3600 1800 2419200 7200",
         NULL},
        {"x.example.org", RRType::A(), RRTTL(300), "192.0.2.1", "192.0.2.2"},
        {"x.example.org", RRType::AAAA(), RRTTL(300),
         "2001:db8::1", "2001:db8::2"},
        {"x.example.org", RRType::RRSIG(), RRTTL(300),
         "A 5 3 3600 20000101000000 20000201000000 12345 example.org. "
         "FAKEFAKEFAKE", NULL},
        {"x.example.org", RRType::RRSIG(), RRTTL(300),
         "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. "
         "FAKEFAKEFAKEFAKE", NULL},
        {"ttldiff.example.org", RRType::A(), RRTTL(300),
         "192.0.2.1", "192.0.2.2"},
        {"ttldiff2.example.org", RRType::AAAA(), RRTTL(300),
         "2001:db8::1", "2001:db8::2"}
    };
    checkIteratorSequence(*client_->getIterator(Name("example.org")),
                          expected_sequence,
                          sizeof(expected_sequence) /
                          sizeof(expected_sequence[0]));
}

TEST_F(MockDatabaseClientTest, iteratorSeparateRRs) {
    // This version of test creates an iterator that separates all RRs as
    // individual RRsets.  In particular, it preserves the TTLs of an RRset
    // even if they are different.
    ExpectedRRset expected_sequence[] = {
        {"example.org", RRType::A(), rrttl_, "192.0.2.1", NULL},
        {"example.org", RRType::SOA(), rrttl_,
         "ns1.example.org. admin.example.org. 1234 3600 1800 2419200 7200",
         NULL},
        {"x.example.org", RRType::A(), RRTTL(300), "192.0.2.1", NULL},
        {"x.example.org", RRType::A(), RRTTL(300), "192.0.2.2", NULL},
        {"x.example.org", RRType::AAAA(), RRTTL(300), "2001:db8::1", NULL},
        {"x.example.org", RRType::AAAA(), RRTTL(300), "2001:db8::2", NULL},
        {"x.example.org", RRType::RRSIG(), RRTTL(300),
         "A 5 3 3600 20000101000000 20000201000000 12345 example.org. "
         "FAKEFAKEFAKE", NULL},
        {"x.example.org", RRType::RRSIG(), RRTTL(300),
         "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. "
         "FAKEFAKEFAKEFAKE", NULL},
        {"ttldiff.example.org", RRType::A(), RRTTL(300), "192.0.2.1", NULL},
        {"ttldiff.example.org", RRType::A(), RRTTL(600), "192.0.2.2", NULL},
        {"ttldiff2.example.org", RRType::AAAA(), RRTTL(600), "2001:db8::1",
         NULL},
        {"ttldiff2.example.org", RRType::AAAA(), RRTTL(300), "2001:db8::2",
         NULL}
    };
    checkIteratorSequence(*client_->getIterator(Name("example.org"), true),
                          expected_sequence,
                          sizeof(expected_sequence) /
                          sizeof(expected_sequence[0]));
}

// This has inconsistent TTL in the set (the rest, like nonsense in
// the data is handled in rdata itself).  Works for the mock accessor only.
TEST_F(MockDatabaseClientTest, badIterator) {
    // It should not throw, but get the lowest one of them
    ZoneIteratorPtr it(client_->getIterator(Name("bad.example.org")));
    EXPECT_EQ(it->getNextRRset()->getTTL(), isc::dns::RRTTL(300));
}

TEST_P(DatabaseClientTest, getSOAFromIterator) {
    vector<string> soa_data;
    soa_data.push_back("ns1.example.org. admin.example.org. "
                       "1234 3600 1800 2419200 7200");

    ZoneIteratorPtr it(client_->getIterator(zname_));
    ASSERT_TRUE(it);
    checkRRset(it->getSOA(), zname_, qclass_, RRType::SOA(), rrttl_, soa_data);

    // Iterate over the zone until we find an SOA.  Although there's a broken
    // RDATA that would trigger an exception in getNextRRset(), we should
    // reach the SOA as the sequence should be sorted and the SOA is at
    // the origin name (which has no bogus data).
    ConstRRsetPtr rrset;
    while ((rrset = it->getNextRRset()) != ConstRRsetPtr() &&
           rrset->getType() != RRType::SOA()) {
        ;
    }
    ASSERT_TRUE(rrset);
    // It should be identical to the result of getSOA().
    rrsetCheck(it->getSOA(), rrset);
}

TEST_P(DatabaseClientTest, noSOAFromIterator) {
    // First, empty the zone.
    updater_ = client_->getUpdater(zname_, true);
    updater_->commit();

    // Then getSOA() should return NULL.
    ZoneIteratorPtr it(client_->getIterator(zname_));
    ASSERT_TRUE(it);
    EXPECT_FALSE(it->getSOA());
}

TEST_P(DatabaseClientTest, iterateThenUpdate) {
    ZoneIteratorPtr it(client_->getIterator(zname_));
    ASSERT_TRUE(it);

    // Try to empty the zone after getting the iterator.  Depending on the
    // underlying data source, it may result in an exception due to the
    // transaction for the iterator.  In either case the integrity of the
    // iterator result should be reserved.
    try {
        updater_ = client_->getUpdater(zname_, true);
        updater_->commit();

        // Confirm at least it doesn't contain any SOA
        EXPECT_EQ(ZoneFinder::NXDOMAIN,
                  getFinder()->find(zname_, RRType::SOA())->code);
    } catch (const DataSourceError&) {}

    ConstRRsetPtr rrset;
    while ((rrset = it->getNextRRset()) != ConstRRsetPtr() &&
           rrset->getType() != RRType::SOA()) {
        ;
    }
    ASSERT_TRUE(rrset);
    // It should be identical to the result of getSOA().
    rrsetCheck(it->getSOA(), rrset);
}

TEST_P(DatabaseClientTest, updateThenIterateThenUpdate) {
    // First clear the zone.
    updater_ = client_->getUpdater(zname_, true);
    updater_->commit();

    // Then iterate over it.  It should immediately reach the end, at which
    // point the transaction should be committed.
    ZoneIteratorPtr it(client_->getIterator(zname_));
    ASSERT_TRUE(it);
    EXPECT_FALSE(it->getNextRRset());

    // So another update attempt should succeed, too.
    updater_ = client_->getUpdater(zname_, true);
    updater_->commit();
}

TEST_P(DatabaseClientTest, updateAfterDeleteIterator) {
    // Similar to the previous case, but we delete the iterator in the
    // middle of zone.  The transaction should be canceled (actually no
    // different from commit though) at that point.
    ZoneIteratorPtr it(client_->getIterator(zname_));
    ASSERT_TRUE(it);
    EXPECT_TRUE(it->getNextRRset());
    it.reset();

    // So another update attempt should succeed.
    updater_ = client_->getUpdater(zname_, true);
    updater_->commit();
}

void
findTestCommon(ZoneFinder& finder, const isc::dns::Name& name,
               const isc::dns::RRType& type,
               ConstZoneFinderContextPtr actual_result,
               const isc::dns::RRType& expected_type,
               const isc::dns::RRTTL expected_ttl,
               ZoneFinder::Result expected_result,
               const std::vector<string>& expected_rdatas,
               const std::vector<string>& expected_sig_rdatas,
               ZoneFinder::FindResultFlags expected_flags,
               const isc::dns::Name& expected_name,
               const ZoneFinder::FindOptions options)
{
    ASSERT_EQ(expected_result, actual_result->code) << name << " " << type;
    EXPECT_EQ((expected_flags & ZoneFinder::RESULT_WILDCARD) != 0,
              actual_result->isWildcard());
    EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0,
              actual_result->isNSECSigned());
    EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0,
              actual_result->isNSEC3Signed());
    if (!expected_rdatas.empty() && actual_result->rrset) {
        checkRRset(actual_result->rrset,
                   expected_name != Name::ROOT_NAME() ? expected_name :
                   name, finder.getClass(), expected_type, expected_ttl,
                   expected_rdatas);
        if ((options & ZoneFinder::FIND_DNSSEC) == ZoneFinder::FIND_DNSSEC) {
            if (!expected_sig_rdatas.empty() &&
                actual_result->rrset->getRRsig()) {
                checkRRset(actual_result->rrset->getRRsig(),
                           expected_name != Name::ROOT_NAME() ?
                           expected_name : name, finder.getClass(),
                           isc::dns::RRType::RRSIG(), expected_ttl,
                           expected_sig_rdatas);
            } else if (expected_sig_rdatas.empty()) {
                EXPECT_EQ(isc::dns::RRsetPtr(),
                          actual_result->rrset->getRRsig()) <<
                    "Unexpected RRSIG: " <<
                    actual_result->rrset->getRRsig()->toText();
            } else {
                ADD_FAILURE() << "Missing RRSIG";
            }
        } else if (actual_result->rrset->getRRsig()) {
            EXPECT_EQ(isc::dns::RRsetPtr(), actual_result->rrset->getRRsig())
                << "Unexpected RRSIG: "
                << actual_result->rrset->getRRsig()->toText();
        }
    } else if (expected_rdatas.empty()) {
        EXPECT_EQ(isc::dns::RRsetPtr(), actual_result->rrset) <<
            "Unexpected RRset: " << actual_result->rrset->toText();
    } else {
        ADD_FAILURE() << "Missing result";
    }
}

void
doFindTest(ZoneFinder& finder,
           const isc::dns::Name& name,
           const isc::dns::RRType& type,
           const isc::dns::RRType& expected_type,
           const isc::dns::RRTTL expected_ttl,
           ZoneFinder::Result expected_result,
           const std::vector<std::string>& expected_rdatas,
           const std::vector<std::string>& expected_sig_rdatas,
           ZoneFinder::FindResultFlags expected_flags =
           ZoneFinder::RESULT_DEFAULT,
           const isc::dns::Name& expected_name = isc::dns::Name::ROOT_NAME(),
           const ZoneFinder::FindOptions options = ZoneFinder::FIND_DEFAULT)
{
    SCOPED_TRACE("doFindTest " + name.toText() + " " + type.toText());
    ConstZoneFinderContextPtr result = finder.find(name, type, options);
    findTestCommon(finder, name, type, result, expected_type, expected_ttl,
                   expected_result, expected_rdatas, expected_sig_rdatas,
                   expected_flags, expected_name, options);
}

void
doFindAtOriginTest(ZoneFinder& finder,
                   const isc::dns::Name& origin,
                   const isc::dns::RRType& type,
                   const isc::dns::RRType& expected_type,
                   const isc::dns::RRTTL expected_ttl,
                   ZoneFinder::Result expected_result,
                   const std::vector<std::string>& expected_rdatas,
                   const std::vector<std::string>& expected_sig_rdatas,
                   bool use_minttl = false,
                   ZoneFinder::FindResultFlags expected_flags =
                   ZoneFinder::RESULT_DEFAULT,
                   const isc::dns::Name& expected_name =
                   isc::dns::Name::ROOT_NAME(),
                   const ZoneFinder::FindOptions options =
                   ZoneFinder::FIND_DEFAULT)
{
    SCOPED_TRACE("doFindOriginTest " + origin.toText() + " " + type.toText());
    ConstZoneFinderContextPtr result =
        finder.findAtOrigin(type, use_minttl, options);
    findTestCommon(finder, origin, type, result, expected_type, expected_ttl,
                   expected_result, expected_rdatas, expected_sig_rdatas,
                   expected_flags, expected_name, options);
}

void
doFindAllTestResult(ZoneFinder& finder, const isc::dns::Name& name,
                    ZoneFinder::Result expected_result,
                    const isc::dns::RRType expected_type,
                    std::vector<std::string> expected_rdata,
                    const isc::dns::Name& expected_name =
                    isc::dns::Name::ROOT_NAME(),
                    const ZoneFinder::FindOptions options =
                    ZoneFinder::FIND_DEFAULT,
                    ZoneFinder::FindResultFlags expected_flags =
                                          ZoneFinder::RESULT_DEFAULT)
{
    SCOPED_TRACE("All test for " + name.toText());
    std::vector<ConstRRsetPtr> target;
    ConstZoneFinderContextPtr result(finder.findAll(name, target, options));
    EXPECT_TRUE(target.empty());
    EXPECT_EQ(expected_result, result->code);
    EXPECT_EQ(expected_type, result->rrset->getType());
    if (expected_flags != ZoneFinder::RESULT_DEFAULT){
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_WILDCARD) != 0,
                  result->isWildcard());
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0,
                  result->isNSECSigned());
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0,
                  result->isNSEC3Signed());

    }
    RdataIteratorPtr it(result->rrset->getRdataIterator());
    std::vector<std::string> rdata;
    while (!it->isLast()) {
        rdata.push_back(it->getCurrent().toText());
        it->next();
    }
    std::sort(rdata.begin(), rdata.end());
    std::sort(expected_rdata.begin(), expected_rdata.end());
    ASSERT_EQ(expected_rdata.size(), rdata.size());
    for (size_t i(0); i < expected_rdata.size(); ++ i) {
        EXPECT_EQ(expected_rdata[i], rdata[i]);
    }
    EXPECT_TRUE(expected_rdata == rdata);
    EXPECT_EQ(expected_name == isc::dns::Name::ROOT_NAME() ? name :
              expected_name, result->rrset->getName());
}

// When asking for an RRset where RRs somehow have different TTLs, it should
// convert to the lowest one.
TEST_F(MockDatabaseClientTest, ttldiff) {
    ZoneIteratorPtr it(client_->getIterator(Name("example.org")));
    // Walk through the full iterator, we should see 1 rrset with name
    // ttldiff1.example.org., and two rdatas. Same for ttldiff2
    const Name name("ttldiff.example.org.");
    bool found = false;
    //bool found2 = false;
    ConstRRsetPtr rrset = it->getNextRRset();
    while (rrset != ConstRRsetPtr()) {
        if (rrset->getName() == name) {
            ASSERT_FALSE(found);
            ASSERT_EQ(2, rrset->getRdataCount());
            ASSERT_EQ(RRTTL(300), rrset->getTTL());
            found = true;
        }
        rrset = it->getNextRRset();
    }
    ASSERT_TRUE(found);
}

// Unless we ask for individual RRs in our iterator request. In that case
// every RR should go into its own 'rrset'
TEST_F(MockDatabaseClientTest, ttldiff_separate_rrs) {
    ZoneIteratorPtr it(client_->getIterator(Name("example.org"), true));

    // Walk through the full iterator, we should see 1 rrset with name
    // ttldiff1.example.org., and two rdatas. Same for ttldiff2
    const Name name("ttldiff.example.org.");
    int found1 = false;
    int found2 = false;
    ConstRRsetPtr rrset = it->getNextRRset();
    while (rrset != ConstRRsetPtr()) {
        if (rrset->getName() == name) {
            ASSERT_EQ(1, rrset->getRdataCount());
            // We should find 1 'rrset' with TTL 300 and one with TTL 600
            if (rrset->getTTL() == RRTTL(300)) {
                ASSERT_FALSE(found1);
                found1 = true;
            } else if (rrset->getTTL() == RRTTL(600)) {
                ASSERT_FALSE(found2);
                found2 = true;
            } else {
                FAIL() << "Found unexpected TTL: " <<
                          rrset->getTTL().toText();
            }
        }
        rrset = it->getNextRRset();
    }
    ASSERT_TRUE(found1);
    ASSERT_TRUE(found2);
}

TEST_P(DatabaseClientTest, find) {
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_rdatas_.push_back("192.0.2.2");
    doFindTest(*finder, isc::dns::Name("www2.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("2001:db8::1");
    expected_rdatas_.push_back("2001:db8::2");
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(),
               rrttl_, ZoneFinder::NXRRSET,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("www.example.org.");
    doFindTest(*finder, isc::dns::Name("cname.example.org."),
               qtype_, isc::dns::RRType::CNAME(), rrttl_,
               ZoneFinder::CNAME, expected_rdatas_,
               expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("www.example.org.");
    doFindTest(*finder, isc::dns::Name("cname.example.org."),
               isc::dns::RRType::CNAME(), isc::dns::RRType::CNAME(),
               rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("doesnotexist.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::NXDOMAIN,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 "
                                   "12346 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed1.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("2001:db8::1");
    expected_rdatas_.push_back("2001:db8::2");
    expected_sig_rdatas_.push_back("AAAA 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(), rrttl_,
               ZoneFinder::NXRRSET, expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("www.example.org.");
    expected_sig_rdatas_.push_back("CNAME 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signedcname1.example.org."),
               qtype_, isc::dns::RRType::CNAME(), rrttl_,
               ZoneFinder::CNAME, expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 "
                                   "12346 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed2.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("2001:db8::2");
    expected_rdatas_.push_back("2001:db8::1");
    expected_sig_rdatas_.push_back("AAAA 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(), rrttl_,
               ZoneFinder::NXRRSET, expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("www.example.org.");
    expected_sig_rdatas_.push_back("CNAME 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signedcname2.example.org."),
               qtype_, isc::dns::RRType::CNAME(), rrttl_,
               ZoneFinder::CNAME, expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("acnamesig1.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("acnamesig2.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("acnamesig3.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_rdatas_.push_back("192.0.2.2");
    doFindTest(*finder, isc::dns::Name("ttldiff1.example.org."),
               qtype_, qtype_, isc::dns::RRTTL(360),
               ZoneFinder::SUCCESS, expected_rdatas_, expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_rdatas_.push_back("192.0.2.2");
    doFindTest(*finder, isc::dns::Name("ttldiff2.example.org."),
               qtype_, qtype_, isc::dns::RRTTL(360),
               ZoneFinder::SUCCESS, expected_rdatas_, expected_sig_rdatas_);

    EXPECT_THROW(finder->find(isc::dns::Name("badcname1.example.org."),
                                              qtype_,
                                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badcname2.example.org."), qtype_,
                                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badcname3.example.org."), qtype_,
                                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badrdata.example.org."), qtype_,
                                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badtype.example.org."), qtype_,
                                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badttl.example.org."), qtype_,
                                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badsig.example.org."), qtype_,
                                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);

    // Trigger the hardcoded exceptions and see if find() has cleaned up
    if (is_mock_) {
        EXPECT_THROW(finder->find(Name("dsexception.example.org."), qtype_,
                                  ZoneFinder::FIND_DEFAULT),
                     DataSourceError);
        EXPECT_THROW(finder->find(Name("iscexception.example.org."), qtype_,
                                  ZoneFinder::FIND_DEFAULT),
                     isc::Exception);
        EXPECT_THROW(finder->find(Name("basicexception.example.org."), qtype_,
                                  ZoneFinder::FIND_DEFAULT),
                     std::exception);
        EXPECT_THROW(finder->find(Name("dsexception.getnext.example.org"),
                                  qtype_, ZoneFinder::FIND_DEFAULT),
                     DataSourceError);
        EXPECT_THROW(finder->find(Name("iscexception.getnext.example.org."),
                                  qtype_, ZoneFinder::FIND_DEFAULT),
                     isc::Exception);
        EXPECT_THROW(finder->find(Name("basicexception.getnext.example.org."),
                                  qtype_, ZoneFinder::FIND_DEFAULT),
                     std::exception);
    }

    // This RRSIG has the wrong sigtype field, which should be
    // an error if we decide to keep using that field
    // Right now the field is ignored, so it does not error
    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("badsigtype.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);
}

TEST_P(DatabaseClientTest, findAtOrigin) {
    ZoneFinderPtr finder(getFinder());

    // Specified type of RR exists, no DNSSEC
    expected_rdatas_.clear();
    expected_rdatas_.push_back("ns.example.com.");
    doFindAtOriginTest(*finder, zname_, RRType::NS(), RRType::NS(),
                       rrttl_, ZoneFinder::SUCCESS,
                       expected_rdatas_, expected_sig_rdatas_);

    // Specified type of RR exists, with DNSSEC
    expected_sig_rdatas_.push_back("NS 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE");
    doFindAtOriginTest(*finder, zname_, RRType::NS(), RRType::NS(),
                       rrttl_, ZoneFinder::SUCCESS,
                       expected_rdatas_, expected_sig_rdatas_,
                       false, ZoneFinder::RESULT_DEFAULT, zname_,
                       ZoneFinder::FIND_DNSSEC);

    // Specified type of RR doesn't exist, no DNSSEC
    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    doFindAtOriginTest(*finder, zname_, RRType::TXT(), qtype_,
                       rrttl_, ZoneFinder::NXRRSET,
                       expected_rdatas_, expected_sig_rdatas_);

    // Specified type of RR doesn't exist, with DNSSEC
    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("acnamesig1.example.org. A NS RRSIG NSEC");
    expected_sig_rdatas_.push_back("NSEC 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindAtOriginTest(*finder, zname_, RRType::TXT(), RRType::NSEC(),
                       rrttl_, ZoneFinder::NXRRSET,
                       expected_rdatas_, expected_sig_rdatas_,
                       false, ZoneFinder::RESULT_NSEC_SIGNED,
                       zname_, ZoneFinder::FIND_DNSSEC);

    // Specified type of RR doesn't exist, with DNSSEC, enabling NSEC3
    (GetParam()->enable_nsec3_fn)(*current_accessor_);
    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    doFindAtOriginTest(*finder, zname_, RRType::TXT(), RRType::TXT(),
                       rrttl_, ZoneFinder::NXRRSET,
                       expected_rdatas_, expected_sig_rdatas_,
                       false, ZoneFinder::RESULT_NSEC3_SIGNED,
                       zname_, ZoneFinder::FIND_DNSSEC);
}

TEST_P(DatabaseClientTest, findAtOriginWithMinTTL) {
    // First, replace the SOA of the test zone so that its RR TTL is larger
    // than MINTTL (the original data are used in many places, so replacing
    // them just for this doesn't make sense).
    RRsetPtr old_soa(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
    old_soa->addRdata(rdata::createRdata(RRType::SOA(), qclass_,
                                         "ns1.example.org. admin.example.org. "
                                         "1234 3600 1800 2419200 7200"));

    const string new_soa_rdata = "ns1.example.org. admin.example.org. "
        "1234 3600 1800 2419200 1200";
    RRsetPtr new_soa(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
    new_soa->addRdata(rdata::createRdata(RRType::SOA(), qclass_,
                                         new_soa_rdata));

    updater_ = client_->getUpdater(zname_, false);
    updater_->deleteRRset(*old_soa);
    updater_->addRRset(*new_soa);
    updater_->commit();

    ZoneFinderPtr finder = getFinder();

    // Specify the use of min TTL, then the resulting TTL should be derived
    // from the SOA MINTTL (which is smaller).
    expected_rdatas_.push_back(new_soa_rdata);
    doFindAtOriginTest(*finder, zname_, RRType::SOA(), RRType::SOA(),
                       RRTTL(1200), ZoneFinder::SUCCESS,
                       expected_rdatas_, expected_sig_rdatas_, true);

    // If DNSSEC is requested, TTL of the RRSIG should also be the min.
    expected_sig_rdatas_.push_back(
        "SOA 5 3 3600 20000101000000 "
        "20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindAtOriginTest(*finder, zname_, RRType::SOA(), RRType::SOA(),
                       RRTTL(1200), ZoneFinder::SUCCESS,
                       expected_rdatas_, expected_sig_rdatas_,
                       true, ZoneFinder::RESULT_DEFAULT, zname_,
                       ZoneFinder::FIND_DNSSEC);

    // Not really intended usage, but specify the use of min TTL for non SOA.
    // It should still work as specified.
    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("ns.example.com.");
    doFindAtOriginTest(*finder, zname_, RRType::NS(), RRType::NS(),
                       RRTTL(1200), ZoneFinder::SUCCESS,
                       expected_rdatas_, expected_sig_rdatas_, true);

    // If we don't request the use of min TTL, the original TTL will be used.
    expected_rdatas_.clear();
    expected_rdatas_.push_back(new_soa_rdata);
    doFindAtOriginTest(*finder, zname_, RRType::SOA(), RRType::SOA(),
                       rrttl_, ZoneFinder::SUCCESS,
                       expected_rdatas_, expected_sig_rdatas_);

    // If no RRset is returned, use_minttl doesn't matter (it shouldn't cause
    // disruption)
    expected_rdatas_.clear();
    doFindAtOriginTest(*finder, zname_, RRType::TXT(), qtype_,
                       rrttl_, ZoneFinder::NXRRSET,
                       expected_rdatas_, expected_sig_rdatas_, true);

    // If it results in NXRRSET with NSEC, and if we specify the use of min
    // TTL, the NSEC and RRSIG should have the min TTL (again, though, this
    // use case is not really the intended one)
    expected_rdatas_.push_back("acnamesig1.example.org. A NS RRSIG NSEC");
    expected_sig_rdatas_.push_back("NSEC 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindAtOriginTest(*finder, zname_, RRType::TXT(), RRType::NSEC(),
                       RRTTL(1200), ZoneFinder::NXRRSET,
                       expected_rdatas_, expected_sig_rdatas_,
                       true, ZoneFinder::RESULT_NSEC_SIGNED,
                       zname_, ZoneFinder::FIND_DNSSEC);
}

TEST_P(DatabaseClientTest, findAtOriginWithMinTTLBroken) {
    // Similar to the previous case, but we intentionally remove the SOA
    // (assuming the underlying data source doesn't complain about it).
    // This will cause exception in subsequent findAtOrigin() with use_minttl
    // being true.
    RRsetPtr old_soa(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
    old_soa->addRdata(rdata::createRdata(RRType::SOA(), qclass_,
                                         "ns1.example.org. admin.example.org. "
                                         "1234 3600 1800 2419200 7200"));
    updater_ = client_->getUpdater(zname_, false);
    updater_->deleteRRset(*old_soa);
    updater_->commit();

    EXPECT_THROW(getFinder()->findAtOrigin(RRType::NS(), true,
                                           ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
}

TEST_P(DatabaseClientTest, findOutOfZone) {
    // If the query name is out-of-zone it should result in an exception
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());
    vector<ConstRRsetPtr> target;

    // Superdomain
    EXPECT_THROW(finder->find(Name("org"), qtype_), OutOfZone);
    EXPECT_THROW(finder->findAll(Name("org"), target), OutOfZone);

    // sharing a common ancestor
    EXPECT_THROW(finder->find(Name("noexample.org"), qtype_), OutOfZone);
    EXPECT_THROW(finder->findAll(Name("noexample.org"), target), OutOfZone);

    // totally unrelated domain, smaller number of labels
    EXPECT_THROW(finder->find(Name("com"), qtype_), OutOfZone);
    EXPECT_THROW(finder->findAll(Name("com"), target), OutOfZone);

    // totally unrelated domain, same number of labels
    EXPECT_THROW(finder->find(Name("example.com"), qtype_), OutOfZone);
    EXPECT_THROW(finder->findAll(Name("example.com"), target), OutOfZone);

    // totally unrelated domain, larger number of labels
    EXPECT_THROW(finder->find(Name("more.example.com"), qtype_), OutOfZone);
    EXPECT_THROW(finder->findAll(Name("more.example.com"), target), OutOfZone);
}

TEST_P(DatabaseClientTest, findDelegation) {
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    // The apex should not be considered delegation point and we can access
    // data
    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    doFindTest(*finder, isc::dns::Name("example.org."),
               qtype_, qtype_,
               rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_);

    expected_rdatas_.clear();
    expected_rdatas_.push_back("ns.example.com.");
    expected_sig_rdatas_.push_back("NS 5 3 3600 20000101000000 20000201000000 "
                                  "12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("example.org."),
               isc::dns::RRType::NS(), isc::dns::RRType::NS(),
               rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_);

    // Check when we ask for something below delegation point, we get the NS
    // (Both when the RRset there exists and doesn't)
    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    expected_rdatas_.push_back("ns.example.com.");
    expected_rdatas_.push_back("ns.delegation.example.org.");
    expected_sig_rdatas_.push_back("NS 5 3 3600 20000101000000 20000201000000 "
                                  "12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("ns.delegation.example.org."),
               qtype_, isc::dns::RRType::NS(),
               rrttl_, ZoneFinder::DELEGATION, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("delegation.example.org."));
    doFindTest(*finder, isc::dns::Name("ns.delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::NS(),
               rrttl_, ZoneFinder::DELEGATION, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("delegation.example.org."));
    doFindTest(*finder, isc::dns::Name("deep.below.delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::NS(),
               rrttl_, ZoneFinder::DELEGATION, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("delegation.example.org."));

    // Even when we check directly at the delegation point, we should get
    // the NS
    doFindTest(*finder, isc::dns::Name("delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::NS(),
               rrttl_, ZoneFinder::DELEGATION, expected_rdatas_,
               expected_sig_rdatas_);

    // And when we ask directly for the NS, we should still get delegation
    doFindTest(*finder, isc::dns::Name("delegation.example.org."),
               isc::dns::RRType::NS(), isc::dns::RRType::NS(),
               rrttl_, ZoneFinder::DELEGATION, expected_rdatas_,
               expected_sig_rdatas_);

    // Now test delegation. If it is below the delegation point, we should get
    // the DNAME (the one with data under DNAME is invalid zone, but we test
    // the behaviour anyway just to make sure)
    expected_rdatas_.clear();
    expected_rdatas_.push_back("dname.example.com.");
    expected_sig_rdatas_.clear();
    expected_sig_rdatas_.push_back("DNAME 5 3 3600 20000101000000 "
                                  "20000201000000 12345 example.org. "
                                  "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("below.dname.example.org."),
               qtype_, isc::dns::RRType::DNAME(),
               rrttl_, ZoneFinder::DNAME, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("dname.example.org."));
    doFindTest(*finder, isc::dns::Name("below.dname.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::DNAME(),
               rrttl_, ZoneFinder::DNAME, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("dname.example.org."));
    // below.dname.example.org. has an A record
    doFindTest(*finder, isc::dns::Name("below.dname.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::DNAME(),
               rrttl_, ZoneFinder::DNAME, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("dname.example.org."));
    doFindTest(*finder, isc::dns::Name("really.deep.below.dname.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::DNAME(),
               rrttl_, ZoneFinder::DNAME, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("dname.example.org."));

    // Asking directly for DNAME should give SUCCESS
    doFindTest(*finder, isc::dns::Name("dname.example.org."),
               isc::dns::RRType::DNAME(), isc::dns::RRType::DNAME(),
               rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_);

    // But we don't delegate at DNAME point
    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("dname.example.org."),
               qtype_, qtype_,
               rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_);
    expected_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("dname.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               rrttl_, ZoneFinder::NXRRSET, expected_rdatas_,
               expected_sig_rdatas_);

    // This is broken dname, it contains two targets
    EXPECT_THROW(finder->find(isc::dns::Name("below.baddname.example.org."),
                              qtype_,
                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);

    // NS and other type coexist: deviant and not necessarily harmful.
    // It should normally just result in DELEGATION; if GLUE_OK is specified,
    // the other RR should be visible.
    expected_rdatas_.clear();
    expected_rdatas_.push_back("ns.example.com.");
    doFindTest(*finder, Name("brokenns1.example.org"), qtype_,
               RRType::NS(), rrttl_, ZoneFinder::DELEGATION,
               expected_rdatas_, empty_rdatas_,
               ZoneFinder::RESULT_DEFAULT);

    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    doFindTest(*finder, Name("brokenns1.example.org"), qtype_,
               qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, empty_rdatas_,
               ZoneFinder::RESULT_DEFAULT, Name("brokenns1.example.org"),
               ZoneFinder::FIND_GLUE_OK);
}

TEST_P(DatabaseClientTest, findDS) {
    // Type DS query is an exception to the general delegation case; the NS
    // should be ignored and it should be treated just like normal
    // authoritative data.

    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    // DS exists at the delegation point.  It should be returned with result
    // code of SUCCESS.
    expected_rdatas_.push_back("1 1 2 abcd"),
    expected_sig_rdatas_.push_back("DS 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, Name("delegation.example.org."),
               RRType::DS(), RRType::DS(), rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_,
               ZoneFinder::RESULT_DEFAULT);

    // DS doesn't exist at the delegation point.  The result should be
    // NXRRSET, and if DNSSEC is requested and the zone is NSEC-signed,
    // the corresponding NSEC should be returned (normally with its RRSIG,
    // but in this simplified test setup it's omitted in the test data).
    expected_rdatas_.clear();
    expected_rdatas_.push_back("dummy.example.org. NS NSEC");
    expected_sig_rdatas_.clear();
    doFindTest(*finder, Name("insecdelegation.example.org."),
               RRType::DS(), RRType::NSEC(), rrttl_, ZoneFinder::NXRRSET,
               expected_rdatas_, expected_sig_rdatas_,
               ZoneFinder::RESULT_NSEC_SIGNED,
               Name("insecdelegation.example.org."), ZoneFinder::FIND_DNSSEC);

    // Some insane case: DS under a zone cut.  It's included in the DB, but
    // shouldn't be visible via finder.
    expected_rdatas_.clear();
    expected_rdatas_.push_back("ns.example.com.");
    doFindTest(*finder, Name("child.insecdelegation.example.org"),
               RRType::DS(), RRType::NS(), rrttl_,
               ZoneFinder::DELEGATION, expected_rdatas_,
               empty_rdatas_, ZoneFinder::RESULT_DEFAULT,
               Name("insecdelegation.example.org."), ZoneFinder::FIND_DNSSEC);
}

TEST_P(DatabaseClientTest, emptyDomain) {
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    // This domain doesn't exist, but a subdomain of it does.
    // Therefore we should pretend the domain is there, but contains no RRsets
    doFindTest(*finder, isc::dns::Name("b.example.org."), qtype_,
               qtype_, rrttl_, ZoneFinder::NXRRSET,
               expected_rdatas_, expected_sig_rdatas_);
}

// Glue-OK mode. Just go through NS delegations down (but not through
// DNAME) and pretend it is not there.
TEST_P(DatabaseClientTest, glueOK) {
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("ns.delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               rrttl_, ZoneFinder::NXRRSET, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("ns.delegation.example.org."),
               ZoneFinder::FIND_GLUE_OK);
    doFindTest(*finder, isc::dns::Name("nothere.delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               rrttl_, ZoneFinder::NXDOMAIN, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("nothere.delegation.example.org."),
               ZoneFinder::FIND_GLUE_OK);
    expected_rdatas_.push_back("192.0.2.1");
    doFindTest(*finder, isc::dns::Name("ns.delegation.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("ns.delegation.example.org."),
               ZoneFinder::FIND_GLUE_OK);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("ns.example.com.");
    expected_rdatas_.push_back("ns.delegation.example.org.");
    expected_sig_rdatas_.clear();
    expected_sig_rdatas_.push_back("NS 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    // When we request the NS, it should be SUCCESS, not DELEGATION
    // (different in GLUE_OK)
    doFindTest(*finder, isc::dns::Name("delegation.example.org."),
               isc::dns::RRType::NS(), isc::dns::RRType::NS(),
               rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("delegation.example.org."),
               ZoneFinder::FIND_GLUE_OK);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("dname.example.com.");
    expected_sig_rdatas_.clear();
    expected_sig_rdatas_.push_back("DNAME 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("below.dname.example.org."),
               qtype_, isc::dns::RRType::DNAME(),
               rrttl_, ZoneFinder::DNAME, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("dname.example.org."), ZoneFinder::FIND_GLUE_OK);
    doFindTest(*finder, isc::dns::Name("below.dname.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::DNAME(), rrttl_,
               ZoneFinder::DNAME, expected_rdatas_, expected_sig_rdatas_,
               ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("dname.example.org."), ZoneFinder::FIND_GLUE_OK);
}

TEST_P(DatabaseClientTest, wildcard) {
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    // First, simple wildcard match
    // Check also that the RRSIG is added from the wildcard (not modified)
    expected_rdatas_.push_back("192.0.2.5");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("a.wild.example.org"),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_WILDCARD);
    doFindTest(*finder, isc::dns::Name("b.a.wild.example.org"),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_WILDCARD);
    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("a.wild.example.org"),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(), rrttl_,
               ZoneFinder::NXRRSET, expected_rdatas_, expected_sig_rdatas_,
               ZoneFinder::RESULT_WILDCARD);
    doFindTest(*finder, isc::dns::Name("b.a.wild.example.org"),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(), rrttl_,
               ZoneFinder::NXRRSET, expected_rdatas_, expected_sig_rdatas_,
               ZoneFinder::RESULT_WILDCARD);

    // Direct request for this wildcard
    expected_rdatas_.push_back("192.0.2.5");
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("*.wild.example.org"),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, expected_sig_rdatas_);
    expected_rdatas_.clear();
    expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("*.wild.example.org"),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(), rrttl_,
               ZoneFinder::NXRRSET, expected_rdatas_, expected_sig_rdatas_);
    // This is nonsense, but check it doesn't match by some stupid accident
    doFindTest(*finder, isc::dns::Name("a.*.wild.example.org"),
               qtype_, qtype_, rrttl_, ZoneFinder::NXDOMAIN,
               expected_rdatas_, expected_sig_rdatas_);
    // These should be canceled, since it is below a domain which exists
    doFindTest(*finder, isc::dns::Name("nothing.here.wild.example.org"),
               qtype_, qtype_, rrttl_, ZoneFinder::NXDOMAIN,
               expected_rdatas_, expected_sig_rdatas_);
    doFindTest(*finder, isc::dns::Name("cancel.here.wild.example.org"),
               qtype_, qtype_, rrttl_, ZoneFinder::NXRRSET,
               expected_rdatas_, expected_sig_rdatas_);
    doFindTest(*finder, isc::dns::Name("below.cancel.here.wild.example.org"),
               qtype_, qtype_, rrttl_, ZoneFinder::NXDOMAIN,
               expected_rdatas_, expected_sig_rdatas_);
    // And this should be just plain empty non-terminal domain, check
    // the wildcard doesn't hurt it
    doFindTest(*finder, isc::dns::Name("here.wild.example.org"),
               qtype_, qtype_, rrttl_, ZoneFinder::NXRRSET,
               expected_rdatas_, expected_sig_rdatas_);
    // Also make sure that the wildcard doesn't hurt the original data
    // below the wildcard
    expected_rdatas_.push_back("2001:db8::5");
    doFindTest(*finder, isc::dns::Name("cancel.here.wild.example.org"),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(), rrttl_,
               ZoneFinder::SUCCESS, expected_rdatas_, expected_sig_rdatas_);
    expected_rdatas_.clear();

    // How wildcard go together with delegation
    expected_rdatas_.push_back("ns.example.com.");
    doFindTest(*finder, isc::dns::Name("below.delegatedwild.example.org"),
               qtype_, isc::dns::RRType::NS(), rrttl_,
               ZoneFinder::DELEGATION, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("delegatedwild.example.org"));
    // FIXME: This doesn't look logically OK, GLUE_OK should make it
    // transparent, so the match should either work or be canceled, but return
    // NXDOMAIN
    doFindTest(*finder, isc::dns::Name("below.delegatedwild.example.org"),
               qtype_, isc::dns::RRType::NS(), rrttl_,
               ZoneFinder::DELEGATION, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               isc::dns::Name("delegatedwild.example.org"),
               ZoneFinder::FIND_GLUE_OK);

    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.5");
    // These are direct matches
    const char* positive_names[] = {
        "wild.*.foo.example.org.",
        "wild.*.foo.*.bar.example.org.",
        NULL
    };
    for (const char** name = positive_names; *name != NULL; ++ name) {
        doFindTest(*finder, isc::dns::Name(*name), qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_,
                   expected_sig_rdatas_);
    }

    // These are wildcard matches against empty nonterminal asterisk
    expected_rdatas_.clear();
    const char* negative_names[] = {
        "a.foo.example.org.",
        "wild.bar.foo.example.org.",
        "baz.foo.*.bar.example.org",
        "baz.foo.baz.bar.example.org",
        "*.foo.baz.bar.example.org",
        NULL
    };
    // Unless FIND_DNSSEC is specified, this is no different from other
    // NXRRSET case.
    for (const char** name = negative_names; *name != NULL; ++ name) {
        doFindTest(*finder, isc::dns::Name(*name), qtype_, qtype_, rrttl_,
                   ZoneFinder::NXRRSET, expected_rdatas_, expected_sig_rdatas_,
                   ZoneFinder::RESULT_WILDCARD);
    }

    // With FIND_DNSSEC, it should have NSEC_SIGNED flag.
    const char* negative_dnssec_names[] = {
        "a.bar.example.org.",
        "foo.baz.bar.example.org.",
        "a.foo.bar.example.org.",
        NULL
    };
    expected_rdatas_.clear();
    expected_rdatas_.push_back("wild.*.foo.*.bar.example.org. NSEC");
    expected_sig_rdatas_.clear();
    for (const char** name = negative_dnssec_names; *name != NULL; ++ name) {
        doFindTest(*finder, isc::dns::Name(*name), qtype_,
                   RRType::NSEC(), rrttl_, ZoneFinder::NXRRSET,
                   expected_rdatas_, expected_sig_rdatas_,
                   ZoneFinder::RESULT_WILDCARD | ZoneFinder::RESULT_NSEC_SIGNED,
                   Name("bao.example.org."), ZoneFinder::FIND_DNSSEC);
    }

    // CNAME on a wildcard.  Maybe not so common, but not disallowed.
    expected_rdatas_.clear();
    expected_rdatas_.push_back("www.example.org.");
    expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("a.cnamewild.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::CNAME(), rrttl_,
               ZoneFinder::CNAME, expected_rdatas_, expected_sig_rdatas_,
               ZoneFinder::RESULT_WILDCARD);

    // DNAME on a wildcard.  In our implementation we ignore DNAMEs on a
    // wildcard, but at a higher level we say the behavior is "unspecified".
    // rfc2672bis strongly discourages the mixture of DNAME and wildcard
    // (with SHOULD NOT).
    doFindTest(*finder, Name("a.dnamewild.example.org."),
               qtype_, qtype_, rrttl_, ZoneFinder::NXRRSET, empty_rdatas_,
               empty_rdatas_, ZoneFinder::RESULT_WILDCARD);

    // Some strange things in the wild node
    expected_rdatas_.clear();
    expected_rdatas_.push_back("ns.example.com.");
    doFindTest(*finder, isc::dns::Name("a.nswild.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::NS(), rrttl_,
               ZoneFinder::DELEGATION, expected_rdatas_, empty_rdatas_,
               ZoneFinder::RESULT_WILDCARD);
}

TEST_P(DatabaseClientTest, noWildcard) {
    // Tests with the NO_WILDCARD flag.

    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    // This would match *.wild.example.org, but with NO_WILDCARD should
    // result in NXDOMAIN.
    expected_rdatas_.push_back("cancel.here.wild.example.org. A NSEC RRSIG");
    expected_sig_rdatas_.push_back("NSEC 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("a.wild.example.org"),
               RRType::NSEC(), RRType::NSEC(), rrttl_,
               ZoneFinder::NXDOMAIN, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_NSEC_SIGNED,
               Name("*.wild.example.org."),
               ZoneFinder::FIND_DNSSEC | ZoneFinder::NO_WILDCARD);

    // Should be the same without FIND_DNSSEC (but in this case no RRsets
    // will be returned)
    doFindTest(*finder, isc::dns::Name("a.wild.example.org"),
               RRType::NSEC(), RRType::NSEC(), rrttl_, ZoneFinder::NXDOMAIN,
               empty_rdatas_, empty_rdatas_, ZoneFinder::RESULT_DEFAULT,
               Name::ROOT_NAME(), // name is dummy
               ZoneFinder::NO_WILDCARD);

    // Same for wildcard empty non terminal.
    expected_rdatas_.clear();
    expected_rdatas_.push_back("brokenns1.example.org. A NSEC");
    doFindTest(*finder, isc::dns::Name("a.bar.example.org"),
               RRType::NSEC(), RRType::NSEC(), rrttl_,
               ZoneFinder::NXDOMAIN, expected_rdatas_, empty_rdatas_,
               ZoneFinder::RESULT_NSEC_SIGNED,
               Name("wild.*.foo.*.bar.example.org"),
               ZoneFinder::FIND_DNSSEC | ZoneFinder::NO_WILDCARD);

    // Search for a wildcard name with NO_WILDCARD.  There should be no
    // difference.  This is, for example, necessary to provide non existence
    // of matching wildcard for isnx.nonterminal.example.org.
    expected_rdatas_.clear();
    expected_rdatas_.push_back("empty.nonterminal.example.org. NSEC");
    doFindTest(*finder, isc::dns::Name("*.nonterminal.example.org"),
               RRType::NSEC(), RRType::NSEC(), rrttl_,
               ZoneFinder::NXDOMAIN, expected_rdatas_, empty_rdatas_,
               ZoneFinder::RESULT_NSEC_SIGNED, Name("l.example.org"),
               ZoneFinder::FIND_DNSSEC | ZoneFinder::NO_WILDCARD);

    // On the other hand, if there's exact match for the wildcard name
    // it should be found regardless of NO_WILDCARD.
    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.5");
    expected_sig_rdatas_.clear();
    expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("*.wild.example.org"),
               qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_DEFAULT,
               Name("*.wild.example.org"), ZoneFinder::NO_WILDCARD);
}

TEST_P(DatabaseClientTest, NXRRSET_NSEC) {
    // The domain exists, but doesn't have this RRType
    // So we should get its NSEC
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    expected_rdatas_.push_back("www2.example.org. A AAAA NSEC RRSIG");
    expected_sig_rdatas_.push_back("NSEC 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::NSEC(),
               rrttl_, ZoneFinder::NXRRSET, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_NSEC_SIGNED,
               Name::ROOT_NAME(), ZoneFinder::FIND_DNSSEC);
}

TEST_P(DatabaseClientTest, wildcardNXRRSET_NSEC) {
    // The domain exists, but doesn't have this RRType
    // So we should get its NSEC
    //
    // The user will have to query us again to get the correct
    // answer (eg. prove there's not an exact match)
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    expected_rdatas_.push_back("cancel.here.wild.example.org. A NSEC RRSIG");
    expected_sig_rdatas_.push_back("NSEC 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    // Note that the NSEC name should NOT be synthesized.
    doFindTest(*finder, isc::dns::Name("a.wild.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::NSEC(), rrttl_,
               ZoneFinder::NXRRSET, expected_rdatas_, expected_sig_rdatas_,
               ZoneFinder::RESULT_WILDCARD | ZoneFinder::RESULT_NSEC_SIGNED,
               Name("*.wild.example.org"), ZoneFinder::FIND_DNSSEC);
}

// Subroutine for dnssecFlagCheck defined below.  It performs some simple
// checks regarding DNSSEC related result flags for findAll().
void
dnssecFlagCheckForAny(ZoneFinder& finder, const Name& name,
                      ZoneFinder::FindResultFlags sec_flag)
{
    std::vector<ConstRRsetPtr> target; // just for placeholder
    ConstZoneFinderContextPtr all_result =
        finder.findAll(name, target, ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ((sec_flag & ZoneFinder::RESULT_NSEC_SIGNED) != 0,
              all_result->isNSECSigned());
    EXPECT_EQ((sec_flag & ZoneFinder::RESULT_NSEC3_SIGNED) != 0,
              all_result->isNSEC3Signed());
}

// Common tests about DNSSEC related result flags.  Shared for the NSEC
// and NSEC3 cases.
void
dnssecFlagCheck(ZoneFinder& finder, ZoneFinder::FindResultFlags sec_flag) {
    std::vector<std::string> expected_rdatas;
    std::vector<std::string> expected_sig_rdatas;

    // Check NXDOMAIN case in NSEC signed zone, and RESULT_NSEC_SIGNED flag
    // should be returned to upper layer caller.
    if ((sec_flag & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        expected_rdatas.push_back("www2.example.org. A AAAA NSEC RRSIG");
        expected_sig_rdatas.push_back("NSEC 5 3 3600 20000101000000 "
                                      "20000201000000 12345 example.org. "
                                      "FAKEFAKEFAKE");
    }
    doFindTest(finder, Name("www1.example.org"), RRType::A(), RRType::NSEC(),
               RRTTL(3600), ZoneFinder::NXDOMAIN, expected_rdatas,
               expected_sig_rdatas, sec_flag, Name("www.example.org."),
               ZoneFinder::FIND_DNSSEC);
    dnssecFlagCheckForAny(finder, Name("www1.example.org"), sec_flag);

    // Check NXRRSET case in NSEC signed zone, and RESULT_NSEC_SIGNED flag
    // should be return.
    // No "findAll" test case for this because NXRRSET shouldn't happen for it.
    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    if ((sec_flag & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        expected_rdatas.push_back("www2.example.org. A AAAA NSEC RRSIG");
        expected_sig_rdatas.push_back("NSEC 5 3 3600 20000101000000 "
                                      "20000201000000 12345 example.org. "
                                      "FAKEFAKEFAKE");
    }
    doFindTest(finder, Name("www.example.org."), RRType::TXT(), RRType::NSEC(),
               RRTTL(3600), ZoneFinder::NXRRSET, expected_rdatas,
               expected_sig_rdatas, sec_flag, Name::ROOT_NAME(),
               ZoneFinder::FIND_DNSSEC);

    // Empty name, should result in NXRRSET (in this test setup the NSEC
    // doesn't have RRSIG).
    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    if ((sec_flag & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        expected_rdatas.push_back("empty.nonterminal.example.org. NSEC");
    }
    doFindTest(finder, Name("nonterminal.example.org."), RRType::A(),
               RRType::NSEC(), RRTTL(3600), ZoneFinder::NXRRSET,
               expected_rdatas,expected_sig_rdatas, sec_flag,
               Name("l.example.org."), ZoneFinder::FIND_DNSSEC);
    dnssecFlagCheckForAny(finder, Name("nonterminal.example.org"), sec_flag);

    // Wildcard match
    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.5");
    expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 "
                                  "20000201000000 12345 example.org. "
                                  "FAKEFAKEFAKE");
    doFindTest(finder, Name("b.a.wild.example.org"), RRType::A(),
               RRType::A(), RRTTL(3600), ZoneFinder::SUCCESS, expected_rdatas,
               expected_sig_rdatas, (ZoneFinder::RESULT_WILDCARD | sec_flag),
               Name("b.a.wild.example.org"), ZoneFinder::FIND_DNSSEC);
    dnssecFlagCheckForAny(finder, Name("b.a.wild.example.org"), sec_flag);

    // Wildcard + NXRRSET (no "findAll" test for this case)
    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    if ((sec_flag & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        expected_rdatas.push_back("cancel.here.wild.example.org. "
                                  "A NSEC RRSIG");
        expected_sig_rdatas.push_back("NSEC 5 3 3600 20000101000000 "
                                      "20000201000000 12345 example.org. "
                                      "FAKEFAKEFAKE");
    }
    doFindTest(finder, Name("b.a.wild.example.org"),
               RRType::TXT(), RRType::NSEC(), RRTTL(3600), ZoneFinder::NXRRSET,
               expected_rdatas, expected_sig_rdatas,
               (ZoneFinder::RESULT_WILDCARD | sec_flag),
               Name("*.wild.example.org"), ZoneFinder::FIND_DNSSEC);

    // Empty wildcard (this NSEC doesn't have RRSIG in our test data)
    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    if ((sec_flag & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        expected_rdatas.push_back("wild.*.foo.*.bar.example.org. NSEC");
    }
    doFindTest(finder, Name("foo.wild.bar.example.org"),
               RRType::TXT(), RRType::NSEC(), RRTTL(3600), ZoneFinder::NXRRSET,
               expected_rdatas, expected_sig_rdatas,
               (ZoneFinder::RESULT_WILDCARD | sec_flag),
               Name("bao.example.org"), ZoneFinder::FIND_DNSSEC);
    dnssecFlagCheckForAny(finder, Name("foo.wild.bar.example.org"), sec_flag);
}

TEST_P(DatabaseClientTest, dnssecResultFlags) {
    // ZoneFinder::find() for negative cases and wildcard cases should check
    // whether the zone is signed with NSEC or NSEC3.

    // In the default test setup, the zone should be considered NSEC-signed
    // (the apex node has an NSEC RR).
    {
        SCOPED_TRACE("NSEC only");
        dnssecFlagCheck(*getFinder(), ZoneFinder::RESULT_NSEC_SIGNED);
    }

    // Then add an NSEC3PARAM RRset at the apex (it may look weird if the
    // zone only has NSEC3PARM RRset (but no NSEC3s), but it is okay for the
    // purpose of this test).  The zone should now be considered NSEC3-signed.
    // Note that the apex NSEC still exists; NSEC3 should override NSEC.
    updater_ = client_->getUpdater(zname_, false);
    rrset_.reset(new RRset(zname_, qclass_, RRType::NSEC3PARAM(), rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "1 0 12 aabbccdd"));
    updater_->addRRset(*rrset_);
    {
        SCOPED_TRACE("NSEC and NSEC3");
        dnssecFlagCheck(updater_->getFinder(), ZoneFinder::RESULT_NSEC3_SIGNED);
    }

    // Next, delete the apex NSEC.  Since NSEC3PARAM remains, the zone should
    // still be considered NSEC3-signed.
    RRsetPtr nsec_rrset(new RRset(zname_, qclass_, RRType::NSEC(), rrttl_));
    nsec_rrset->addRdata(rdata::createRdata(RRType::NSEC(), qclass_,
                                            "acnamesig1.example.org. NS A "
                                            "NSEC RRSIG"));
    updater_->deleteRRset(*nsec_rrset);
    {
        SCOPED_TRACE("NSEC3 only");
        dnssecFlagCheck(updater_->getFinder(), ZoneFinder::RESULT_NSEC3_SIGNED);
    }

    // Finally, delete the NSEC3PARAM we just added above.  The zone should
    // then be considered unsigned.
    updater_->deleteRRset(*rrset_);
    {
        SCOPED_TRACE("unsigned");
        dnssecFlagCheck(updater_->getFinder(), ZoneFinder::RESULT_DEFAULT);
    }
}

TEST_P(DatabaseClientTest, NXDOMAIN_NSEC) {
    // The domain doesn't exist, so we must get the right NSEC
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());
    expected_rdatas_.push_back("www2.example.org. A AAAA NSEC RRSIG");
    expected_sig_rdatas_.push_back("NSEC 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("www1.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::NSEC(),
               rrttl_, ZoneFinder::NXDOMAIN, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_NSEC_SIGNED,
               Name("www.example.org."), ZoneFinder::FIND_DNSSEC);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("acnamesig1.example.org. NS A NSEC RRSIG");
    // This tests it works correctly in apex (there was a bug, where a check
    // for NS-alone was there and it would throw).
    doFindTest(*finder, isc::dns::Name("aa.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::NSEC(),
               rrttl_, ZoneFinder::NXDOMAIN, expected_rdatas_,
               expected_sig_rdatas_, ZoneFinder::RESULT_NSEC_SIGNED,
               Name("example.org."), ZoneFinder::FIND_DNSSEC);

    // Check that if the DB doesn't support it, the exception from there
    // is not propagated and it only does not include the NSEC
    if (!is_mock_) {
        return; // We don't make the real DB to throw
    }
    // In this case the accessor doesn't support findPreviousName(), but the
    // zone apex has NSEC, and the zone itself is considered NSEC-signed.
    doFindTest(*finder, Name("notimplnsec.example.org."),
               RRType::TXT(), RRType::NSEC(), rrttl_, ZoneFinder::NXDOMAIN,
               empty_rdatas_, empty_rdatas_, ZoneFinder::RESULT_NSEC_SIGNED,
               Name::ROOT_NAME(), ZoneFinder::FIND_DNSSEC);
}

TEST_P(DatabaseClientTest, emptyNonterminalNSEC) {
    // Same as NXDOMAIN_NSEC, but with empty non-terminal
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    expected_rdatas_.push_back("empty.nonterminal.example.org. NSEC");
    doFindTest(*finder, isc::dns::Name("nonterminal.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::NSEC(), rrttl_,
               ZoneFinder::NXRRSET, expected_rdatas_, expected_sig_rdatas_,
               ZoneFinder::RESULT_NSEC_SIGNED, Name("l.example.org."),
               ZoneFinder::FIND_DNSSEC);

    // Check that if the DB doesn't support it, the exception from there
    // is not propagated and it only does not include the NSEC
    if (!is_mock_) {
        return; // We don't make the real DB to throw
    }
    // See the corresponding case of NXDOMAIN_NSEC.
    doFindTest(*finder, Name("here.wild.example.org."),
               RRType::TXT(), RRType::NSEC(), rrttl_, ZoneFinder::NXRRSET,
               empty_rdatas_, empty_rdatas_, ZoneFinder::RESULT_NSEC_SIGNED,
               Name::ROOT_NAME(), ZoneFinder::FIND_DNSSEC);
}

TEST_P(DatabaseClientTest, anyFromFind) {
    // Find will reject answering an ANY query
    EXPECT_THROW(getFinder()->find(isc::dns::Name("www2.example.org."),
                                   RRType::ANY()), isc::Unexpected);
}

TEST_P(DatabaseClientTest, findRRSIGsWithoutDNSSEC) {
    // Trying to find RRSIG records directly should work even if
    // FIND_DNSSEC flag is not specified.

    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());
    ConstZoneFinderContextPtr result =
        finder->find(isc::dns::Name("signed1.example.org."), RRType::RRSIG());

    EXPECT_EQ(ZoneFinder::SUCCESS, result->code);

    std::vector<std::string> expected_rdata;
    expected_rdata.push_back(TEST_RECORDS[10][4]);
    expected_rdata.push_back(TEST_RECORDS[11][4]);
    expected_rdata.push_back(TEST_RECORDS[14][4]);

    RdataIteratorPtr it(result->rrset->getRdataIterator());
    std::vector<std::string> rdata;
    while (!it->isLast()) {
        rdata.push_back(it->getCurrent().toText());
        it->next();
    }
    std::sort(rdata.begin(), rdata.end());
    std::sort(expected_rdata.begin(), expected_rdata.end());
    ASSERT_EQ(expected_rdata.size(), rdata.size());
    for (size_t i(0); i < expected_rdata.size(); ++ i) {
        EXPECT_EQ(expected_rdata[i], rdata[i]);
    }
}

// Test the findAll method.
TEST_P(DatabaseClientTest, getAll) {
    // The domain doesn't exist, so we must get the right NSEC
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    // It should act the same on the "failures"
    std::vector<ConstRRsetPtr> target;
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              finder->findAll(isc::dns::Name("nothere.example.org."),
                              target)->code);
    EXPECT_TRUE(target.empty());
    EXPECT_EQ(ZoneFinder::NXRRSET,
              finder->findAll(isc::dns::Name("here.wild.example.org."),
                              target)->code);
    expected_rdatas_.push_back("ns.delegation.example.org.");
    expected_rdatas_.push_back("ns.example.com.");
    doFindAllTestResult(*finder, isc::dns::Name("xx.delegation.example.org."),
                        ZoneFinder::DELEGATION, RRType::NS(), expected_rdatas_,
                        isc::dns::Name("delegation.example.org."));
    expected_rdatas_.clear();
    expected_rdatas_.push_back("www.example.org.");
    doFindAllTestResult(*finder, isc::dns::Name("cname.example.org"),
                        ZoneFinder::CNAME, RRType::CNAME(), expected_rdatas_);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("dname.example.com.");
    doFindAllTestResult(*finder, isc::dns::Name("a.dname.example.org"),
                        ZoneFinder::DNAME, RRType::DNAME(), expected_rdatas_,
                        isc::dns::Name("dname.example.org."));
    // It should get the data on success
    EXPECT_EQ(ZoneFinder::SUCCESS,
              finder->findAll(isc::dns::Name("www2.example.org."),
                              target)->code);
    ASSERT_EQ(2, target.size());
    size_t a_idx(target[1]->getType() == RRType::A());
    EXPECT_EQ(RRType::A(), target[a_idx]->getType());
    std::string previous;
    size_t count(0);
    for (RdataIteratorPtr it(target[a_idx]->getRdataIterator());
         !it->isLast(); it->next()) {
        ++count;
        EXPECT_NE(previous, it->getCurrent().toText());
        EXPECT_TRUE(it->getCurrent().toText() == "192.0.2.1" ||
                    it->getCurrent().toText() == "192.0.2.2");
        previous = it->getCurrent().toText();
    }
    EXPECT_EQ(2, count);
    EXPECT_EQ(RRType::AAAA(), target[1 - a_idx]->getType());
    RdataIteratorPtr it(target[1 - a_idx]->getRdataIterator());
    ASSERT_FALSE(it->isLast());
    EXPECT_EQ("2001:db8::1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    // And on wildcard. Check the signatures as well.
    target.clear();
    ConstZoneFinderContextPtr result =
        finder->findAll(Name("a.wild.example.org"), target,
                        ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::SUCCESS, result->code);
    EXPECT_TRUE(result->isWildcard());
    EXPECT_TRUE(result->isNSECSigned());
    EXPECT_FALSE(result->isNSEC3Signed());
    ASSERT_EQ(2, target.size());
    a_idx = target[1]->getType() == RRType::A();
    EXPECT_EQ(RRType::A(), target[a_idx]->getType());
    it = target[a_idx]->getRdataIterator();
    ASSERT_FALSE(it->isLast());
    EXPECT_EQ("192.0.2.5", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
    ConstRRsetPtr sig(target[a_idx]->getRRsig());
    ASSERT_TRUE(sig);
    EXPECT_EQ(RRType::RRSIG(), sig->getType());
    EXPECT_EQ("A 5 3 3600 20000101000000 20000201000000 12345 example.org. "
              "FAKEFAKEFAKE", sig->getRdataIterator()->getCurrent().toText());
    EXPECT_EQ(RRType::NSEC(), target[1 - a_idx]->getType());
    it = target[1 - a_idx]->getRdataIterator();
    ASSERT_FALSE(it->isLast());
    EXPECT_EQ("cancel.here.wild.example.org. A RRSIG NSEC",
              it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
    sig = target[1 - a_idx]->getRRsig();
    ASSERT_TRUE(sig);
    EXPECT_EQ(RRType::RRSIG(), sig->getType());
    EXPECT_EQ("NSEC 5 3 3600 20000101000000 20000201000000 12345 example.org. "
              "FAKEFAKEFAKE", sig->getRdataIterator()->getCurrent().toText());
}

TEST_P(DatabaseClientTest, getOrigin) {
    const DataSourceClient::FindResult result =
        client_->findZone(Name("example.org"));
    ASSERT_EQ(result::SUCCESS, result.code);
    boost::shared_ptr<DatabaseClient::Finder> finder(
        dynamic_pointer_cast<DatabaseClient::Finder>(result.zone_finder));
    if (is_mock_) {
        EXPECT_EQ(READONLY_ZONE_ID, finder->zone_id());
    }
    EXPECT_EQ(zname_, finder->getOrigin());
}

TEST_P(DatabaseClientTest, updaterFinder) {
    updater_ = client_->getUpdater(zname_, false);
    ASSERT_TRUE(updater_);

    // If this update isn't replacing the zone, the finder should work
    // just like the normal find() case.
    if (is_mock_) {
        DatabaseClient::Finder& finder = dynamic_cast<DatabaseClient::Finder&>(
            updater_->getFinder());
        EXPECT_EQ(WRITABLE_ZONE_ID, finder.zone_id());
    }
    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
               ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);

    // When replacing the zone, the updater's finder shouldn't see anything
    // in the zone until something is added.
    updater_.reset();
    updater_ = client_->getUpdater(zname_, true);
    ASSERT_TRUE(updater_);
    if (is_mock_) {
        DatabaseClient::Finder& finder = dynamic_cast<DatabaseClient::Finder&>(
            updater_->getFinder());
        EXPECT_EQ(WRITABLE_ZONE_ID, finder.zone_id());
    }
    doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
               ZoneFinder::NXDOMAIN, empty_rdatas_, empty_rdatas_);
}

TEST_P(DatabaseClientTest, flushZone) {
    // A simple update case: flush the entire zone
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    // Before update, the name exists.
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(qname_, qtype_)->code);

    // start update in the replace mode.  the normal finder should still
    // be able to see the record, but the updater's finder shouldn't.
    updater_ = client_->getUpdater(zname_, true);
    setUpdateAccessor();
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(qname_, qtype_)->code);
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              updater_->getFinder().find(qname_, qtype_)->code);

    // commit the update.  now the normal finder shouldn't see it.
    updater_->commit();
    EXPECT_EQ(ZoneFinder::NXDOMAIN, finder->find(qname_, qtype_)->code);

    // Check rollback wasn't accidentally performed.
    EXPECT_FALSE(isRollbacked());
}

TEST_P(DatabaseClientTest, updateCancel) {
    // similar to the previous test, but destruct the updater before commit.

    ZoneFinderPtr finder = client_->findZone(zname_).zone_finder;
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(qname_, qtype_)->code);

    updater_ = client_->getUpdater(zname_, true);
    setUpdateAccessor();
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              updater_->getFinder().find(qname_, qtype_)->code);
    // DB should not have been rolled back yet.
    EXPECT_FALSE(isRollbacked());
    updater_.reset();            // destruct without commit

    // reset() should have triggered rollback (although it doesn't affect
    // anything to the mock accessor implementation except for the result of
    // isRollbacked())
    EXPECT_TRUE(isRollbacked(true));
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(qname_, qtype_)->code);
}

TEST_P(DatabaseClientTest, exceptionFromRollback) {
    updater_ = client_->getUpdater(zname_, true);

    rrset_.reset(new RRset(Name("throw.example.org"), qclass_,
                                 qtype_, rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "192.0.2.1"));
    updater_->addRRset(*rrset_);
    // destruct without commit.  The added name will result in an exception
    // in the MockAccessor's rollback method.  It shouldn't be propagated.
    EXPECT_NO_THROW(updater_.reset());
}

TEST_P(DatabaseClientTest, duplicateCommit) {
    // duplicate commit.  should result in exception.
    updater_ = client_->getUpdater(zname_, true);
    updater_->commit();
    EXPECT_THROW(updater_->commit(), DataSourceError);
}

TEST_P(DatabaseClientTest, addRRsetToNewZone) {
    // Add a single RRset to a fresh empty zone
    updater_ = client_->getUpdater(zname_, true);
    updater_->addRRset(*rrset_);

    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);
    }

    // Similar to the previous case, but with RRSIG
    updater_.reset();
    updater_ = client_->getUpdater(zname_, true);
    updater_->addRRset(*rrset_);
    updater_->addRRset(*rrsigset_);

    // confirm the expected columns were passed to the accessor (if checkable).
    const char* const rrsig_added[] = {
        "www.example.org.", "org.example.www.", "3600", "RRSIG", "A",
        "A 5 3 0 20000101000000 20000201000000 0 example.org. FAKEFAKEFAKE"
    };
    checkLastAdded(rrsig_added);

    expected_sig_rdatas_.clear();
    expected_sig_rdatas_.push_back(rrsig_added[DatabaseAccessor::ADD_RDATA]);
    {
        SCOPED_TRACE("add RRset with RRSIG");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_,
                   expected_sig_rdatas_);
    }

    // Add the non RRSIG RRset again, to see the attempt of adding RRSIG
    // causes any unexpected effect, in particular, whether the SIGTYPE
    // field might remain.
    updater_->addRRset(*rrset_);
    const char* const rrset_added[] = {
        "www.example.org.", "org.example.www.", "3600", "A", "", "192.0.2.2"
    };
    checkLastAdded(rrset_added);
}

//
// Below we define a set of NSEC3 update tests.
//
// Commonly used data for NSEC3 update tests below.
const char* const nsec3_hash = "1BB7SO0452U1QHL98UISNDD9218GELR5";
const char* const nsec3_rdata = "1 1 12 AABBCCDD "
    "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR NS SOA RRSIG NSEC3PARAM";
const char* const nsec3_rdata2 = "1 1 12 AABBCCDD "
    "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR NS SOA RRSIG"; // differ in bitmaps
const char* const nsec3_sig_rdata = "NSEC3 5 3 3600 20000101000000 "
    "20000201000000 12345 example.org. FAKEFAKEFAKE";
const char* const nsec3_sig_rdata2 = "NSEC3 5 3 3600 20000101000000 "
    "20000201000000 12345 example.org. FAKEFAKE"; // differ in the signature

// Commonly used subroutine that checks if we can get the expected record.
// According to the API, implementations can skip filling in columns other
// than those explicitly checked below, so we don't check them.
void
nsec3Check(const vector<ConstRRsetPtr>& expected_rrsets,
           const Name& zone_name, const string& expected_hash,
           DatabaseAccessor& accessor)
{
    const int zone_id = accessor.getZone(zone_name.toText()).second;
    DatabaseAccessor::IteratorContextPtr itctx =
        accessor.getNSEC3Records(expected_hash, zone_id);
    ASSERT_TRUE(itctx);

    // Build a list of matched RRsets and compare the both expected and built
    // ones as sets.
    string columns[DatabaseAccessor::COLUMN_COUNT];
    vector<ConstRRsetPtr> actual_rrsets;
    while (itctx->getNext(columns)) {
        actual_rrsets.push_back(
            textToRRset(expected_hash + "." + zone_name.toText() + " " +
                        columns[DatabaseAccessor::TTL_COLUMN] + " IN " +
                        columns[DatabaseAccessor::TYPE_COLUMN] + " " +
                        columns[DatabaseAccessor::RDATA_COLUMN]));
    }
    rrsetsCheck(expected_rrsets.begin(), expected_rrsets.end(),
                actual_rrsets.begin(), actual_rrsets.end());
}

TEST_P(DatabaseClientTest, addDeleteNSEC3InZone) {
    // Add one NSEC3 RR to the zone, delete it, and add another one.
    updater_ = client_->getUpdater(zname_, true);
    const ConstRRsetPtr nsec3_rrset =
        textToRRset(string(nsec3_hash) + ".example.org. 3600 IN NSEC3 " +
                    string(nsec3_rdata));
    const ConstRRsetPtr nsec3_rrset2 =
        textToRRset(string(nsec3_hash) + ".example.org. 3600 IN NSEC3 " +
                    string(nsec3_rdata2));
    updater_->addRRset(*nsec3_rrset);
    updater_->deleteRRset(*nsec3_rrset);
    updater_->addRRset(*nsec3_rrset2);
    updater_->commit();

    // Check if we can get the expected record.
    vector<ConstRRsetPtr> expected_rrsets;
    expected_rrsets.push_back(nsec3_rrset2);
    nsec3Check(expected_rrsets, zname_, nsec3_hash, *current_accessor_);
}

TEST_P(DatabaseClientTest, addDeleteNSEC3AndRRSIGToZone) {
    // Add one NSEC3 RR and its RRSIG to the zone, delete the RRSIG and add
    // a new one.
    updater_ = client_->getUpdater(zname_, true);
    const ConstRRsetPtr nsec3_rrset =
        textToRRset(string(nsec3_hash) + ".example.org. 3600 IN NSEC3 " +
                    string(nsec3_rdata));
    const ConstRRsetPtr nsec3_sig_rrset =
        textToRRset(string(nsec3_hash) + ".example.org. 3600 IN RRSIG " +
                    string(nsec3_sig_rdata));
    const ConstRRsetPtr nsec3_sig_rrset2 =
        textToRRset(string(nsec3_hash) + ".example.org. 3600 IN RRSIG " +
                    string(nsec3_sig_rdata2));
    updater_->addRRset(*nsec3_rrset);
    updater_->addRRset(*nsec3_sig_rrset);
    updater_->deleteRRset(*nsec3_sig_rrset);
    updater_->addRRset(*nsec3_sig_rrset2);
    updater_->commit();

    // Check if we can get the expected record.
    vector<ConstRRsetPtr> expected_rrsets;
    expected_rrsets.push_back(nsec3_rrset);
    expected_rrsets.push_back(nsec3_sig_rrset2);
    nsec3Check(expected_rrsets, zname_, nsec3_hash, *current_accessor_);
}

TEST_P(DatabaseClientTest, addRRsetToCurrentZone) {
    // Similar to the previous test, but not replacing the existing data.
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    updater_ = client_->getUpdater(zname_, false);
    updater_->addRRset(*rrset_);

    // We should see both old and new data.
    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_rdatas_.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);
    }
    updater_->commit();
    {
        SCOPED_TRACE("add RRset after commit");
        doFindTest(*finder, qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, addMultipleRRs) {
    // Similar to the previous case, but the added RRset contains multiple
    // RRs.
    updater_ = client_->getUpdater(zname_, false);
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "192.0.2.3"));
    updater_->addRRset(*rrset_);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_rdatas_.push_back("192.0.2.2");
    expected_rdatas_.push_back("192.0.2.3");
    {
        SCOPED_TRACE("add multiple RRs");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, addRRsetOfLargerTTL) {
    // Similar to the previous one, but the TTL of the added RRset is larger
    // than that of the existing record.  The finder should use the smaller
    // one.
    updater_ = client_->getUpdater(zname_, false);
    rrset_->setTTL(RRTTL(7200));
    updater_->addRRset(*rrset_);

    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_rdatas_.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset of larger TTL");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, addRRsetOfSmallerTTL) {
    // Similar to the previous one, but the added RRset has a smaller TTL.
    // The added TTL should be used by the finder.
    updater_ = client_->getUpdater(zname_, false);
    rrset_->setTTL(RRTTL(1800));
    updater_->addRRset(*rrset_);

    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_rdatas_.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset of smaller TTL");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, RRTTL(1800),
                   ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, addSameRR) {
    // Add the same RR as that is already in the data source.
    // Currently the add interface doesn't try to suppress the duplicate,
    // neither does the finder.  We may want to revisit it in future versions.

    updater_ = client_->getUpdater(zname_, false);
    rrset_.reset(new RRset(qname_, qclass_, qtype_, rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "192.0.2.1"));
    updater_->addRRset(*rrset_);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_rdatas_.push_back("192.0.2.1");
    {
        SCOPED_TRACE("add same RR");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, addDeviantRR) {
    updater_ = client_->getUpdater(zname_, false);

    // RR class mismatch.  This should be detected and rejected.
    rrset_.reset(new RRset(qname_, RRClass::CH(), RRType::TXT(), rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "test text"));
    EXPECT_THROW(updater_->addRRset(*rrset_), DataSourceError);

    // Out-of-zone owner name.  At a higher level this should be rejected,
    // but it doesn't happen in this interface.
    rrset_.reset(new RRset(Name("example.com"), qclass_, qtype_, rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "192.0.2.100"));
    updater_->addRRset(*rrset_);

    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.100");
    {
        // Note: find() rejects out-of-zone query name with an exception
        // regardless of whether adding the RR succeeded, so this check
        // actually doesn't confirm it.
        SCOPED_TRACE("add out-of-zone RR");
        EXPECT_THROW(updater_->getFinder().find(Name("example.com"), qtype_),
                     OutOfZone);
    }
}

TEST_P(DatabaseClientTest, addEmptyRRset) {
    updater_ = client_->getUpdater(zname_, false);
    rrset_.reset(new RRset(qname_, qclass_, qtype_, rrttl_));
    EXPECT_THROW(updater_->addRRset(*rrset_), DataSourceError);
}

TEST_P(DatabaseClientTest, addAfterCommit) {
   updater_ = client_->getUpdater(zname_, false);
   updater_->commit();
   EXPECT_THROW(updater_->addRRset(*rrset_), DataSourceError);
}

TEST_P(DatabaseClientTest, addRRsetWithRRSIG) {
    updater_ = client_->getUpdater(zname_, false);
    rrset_->addRRsig(*rrsigset_);
    EXPECT_THROW(updater_->addRRset(*rrset_), DataSourceError);
}

TEST_P(DatabaseClientTest, deleteRRset) {
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    rrset_.reset(new RRset(qname_, qclass_, qtype_, rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "192.0.2.1"));

    // Delete one RR from an RRset
    updater_ = client_->getUpdater(zname_, false);
    updater_->deleteRRset(*rrset_);

    // Delete the only RR of a name
    rrset_.reset(new RRset(Name("cname.example.org"), qclass_,
                           RRType::CNAME(), rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "www.example.org."));
    updater_->deleteRRset(*rrset_);

    // The updater_ finder should immediately see the deleted results.
    {
        SCOPED_TRACE("delete RRset");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::NXRRSET, empty_rdatas_, empty_rdatas_);
        doFindTest(updater_->getFinder(), Name("cname.example.org"),
                   qtype_, qtype_, rrttl_, ZoneFinder::NXDOMAIN, empty_rdatas_,
                   empty_rdatas_);
    }

    // before committing the change, the original finder should see the
    // original record.
    {
        SCOPED_TRACE("delete RRset before commit");
        expected_rdatas_.push_back("192.0.2.1");
        doFindTest(*finder, qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);

        expected_rdatas_.clear();
        expected_rdatas_.push_back("www.example.org.");
        doFindTest(*finder, Name("cname.example.org"), qtype_, RRType::CNAME(),
                   rrttl_, ZoneFinder::CNAME, expected_rdatas_, empty_rdatas_);
    }

    // once committed, the record should be removed from the original finder's
    // view, too.
    updater_->commit();
    {
        SCOPED_TRACE("delete RRset after commit");
        doFindTest(*finder, qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::NXRRSET, empty_rdatas_, empty_rdatas_);
        doFindTest(*finder, Name("cname.example.org"), qtype_, qtype_, rrttl_,
                   ZoneFinder::NXDOMAIN, empty_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, deleteRRsetToNXDOMAIN) {
    // similar to the previous case, but it removes the only record of the
    // given name.  a subsequent find() should result in NXDOMAIN.
    rrset_.reset(new RRset(Name("cname.example.org"), qclass_,
                           RRType::CNAME(), rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "www.example.org."));

    updater_ = client_->getUpdater(zname_, false);
    updater_->deleteRRset(*rrset_);
    {
        SCOPED_TRACE("delete RRset to NXDOMAIN");
        doFindTest(updater_->getFinder(), Name("cname.example.org"),
                   qtype_, qtype_, rrttl_, ZoneFinder::NXDOMAIN, empty_rdatas_,
                   empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, deleteMultipleRRs) {
    rrset_.reset(new RRset(qname_, qclass_, RRType::AAAA(), rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "2001:db8::1"));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "2001:db8::2"));

    updater_ = client_->getUpdater(zname_, false);
    updater_->deleteRRset(*rrset_);

    {
        SCOPED_TRACE("delete multiple RRs");
        doFindTest(updater_->getFinder(), qname_, RRType::AAAA(),
                   qtype_, rrttl_, ZoneFinder::NXRRSET,
                   empty_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, partialDelete) {
    rrset_.reset(new RRset(qname_, qclass_, RRType::AAAA(), rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "2001:db8::1"));
    // This does not exist in the test data source:
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "2001:db8::3"));

    // deleteRRset should succeed "silently", and subsequent find() should
    // find the remaining RR.
    updater_ = client_->getUpdater(zname_, false);
    updater_->deleteRRset(*rrset_);
    {
        SCOPED_TRACE("partial delete");
        expected_rdatas_.push_back("2001:db8::2");
        doFindTest(updater_->getFinder(), qname_, RRType::AAAA(),
                   RRType::AAAA(), rrttl_, ZoneFinder::SUCCESS,
                   expected_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, deleteNoMatch) {
    // similar to the previous test, but there's not even a match in the
    // specified RRset.  Essentially there's no difference in the result.
    updater_ = client_->getUpdater(zname_, false);
    updater_->deleteRRset(*rrset_);
    {
        SCOPED_TRACE("delete no match");
        expected_rdatas_.push_back("192.0.2.1");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, deleteWithDifferentTTL) {
    // Our delete interface simply ignores TTL (may change in a future version)
    rrset_.reset(new RRset(qname_, qclass_, qtype_, RRTTL(1800)));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "192.0.2.1"));
    updater_ = client_->getUpdater(zname_, false);
    updater_->deleteRRset(*rrset_);
    {
        SCOPED_TRACE("delete RRset with a different TTL");
        doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
                   ZoneFinder::NXRRSET, empty_rdatas_, empty_rdatas_);
    }
}

TEST_P(DatabaseClientTest, deleteDeviantRR) {
    updater_ = client_->getUpdater(zname_, false);

    // RR class mismatch.  This should be detected and rejected.
    rrset_.reset(new RRset(qname_, RRClass::CH(), RRType::TXT(), rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "test text"));
    EXPECT_THROW(updater_->deleteRRset(*rrset_), DataSourceError);

    // Out-of-zone owner name.  At a higher level this should be rejected,
    // but it doesn't happen in this interface.
    rrset_.reset(new RRset(Name("example.com"), qclass_, qtype_, rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "192.0.2.100"));
    EXPECT_NO_THROW(updater_->deleteRRset(*rrset_));
}

TEST_P(DatabaseClientTest, deleteAfterCommit) {
   updater_ = client_->getUpdater(zname_, false);
   updater_->commit();
   EXPECT_THROW(updater_->deleteRRset(*rrset_), DataSourceError);
}

TEST_P(DatabaseClientTest, deleteEmptyRRset) {
    updater_ = client_->getUpdater(zname_, false);
    rrset_.reset(new RRset(qname_, qclass_, qtype_, rrttl_));
    EXPECT_THROW(updater_->deleteRRset(*rrset_), DataSourceError);
}

TEST_P(DatabaseClientTest, deleteRRsetWithRRSIG) {
    updater_ = client_->getUpdater(zname_, false);
    rrset_->addRRsig(*rrsigset_);
    EXPECT_THROW(updater_->deleteRRset(*rrset_), DataSourceError);
}

TEST_P(DatabaseClientTest, compoundUpdate) {
    // This test case performs an arbitrary chosen add/delete operations
    // in a single update transaction.  Essentially there is nothing new to
    // test here, but there may be some bugs that was overlooked and can
    // only happen in the compound update scenario, so we test it.

    updater_ = client_->getUpdater(zname_, false);

    // add a new RR to an existing RRset
    updater_->addRRset(*rrset_);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.1");
    expected_rdatas_.push_back("192.0.2.2");
    doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
               ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);

    // delete an existing RR
    rrset_.reset(new RRset(Name("www.example.org"), qclass_, qtype_, rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "192.0.2.1"));
    updater_->deleteRRset(*rrset_);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.2");
    doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
               ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);

    // re-add it
    updater_->addRRset(*rrset_);
    expected_rdatas_.push_back("192.0.2.1");
    doFindTest(updater_->getFinder(), qname_, qtype_, qtype_, rrttl_,
               ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);

    // add a new RR with a new name
    const Name newname("newname.example.org");
    const RRType newtype(RRType::AAAA());
    doFindTest(updater_->getFinder(), newname, newtype, newtype, rrttl_,
               ZoneFinder::NXDOMAIN, empty_rdatas_, empty_rdatas_);
    rrset_.reset(new RRset(newname, qclass_, newtype, rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "2001:db8::10"));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "2001:db8::11"));
    updater_->addRRset(*rrset_);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("2001:db8::10");
    expected_rdatas_.push_back("2001:db8::11");
    doFindTest(updater_->getFinder(), newname, newtype, newtype, rrttl_,
               ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);

    // delete one RR from the previous set
    rrset_.reset(new RRset(newname, qclass_, newtype, rrttl_));
    rrset_->addRdata(rdata::createRdata(rrset_->getType(), rrset_->getClass(),
                                        "2001:db8::11"));
    updater_->deleteRRset(*rrset_);
    expected_rdatas_.clear();
    expected_rdatas_.push_back("2001:db8::10");
    doFindTest(updater_->getFinder(), newname, newtype, newtype, rrttl_,
               ZoneFinder::SUCCESS, expected_rdatas_, empty_rdatas_);

    // Commit the changes, confirm the entire changes applied.
    updater_->commit();
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());
    expected_rdatas_.clear();
    expected_rdatas_.push_back("192.0.2.2");
    expected_rdatas_.push_back("192.0.2.1");
    doFindTest(*finder, qname_, qtype_, qtype_, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, empty_rdatas_);

    expected_rdatas_.clear();
    expected_rdatas_.push_back("2001:db8::10");
    doFindTest(*finder, newname, newtype, newtype, rrttl_, ZoneFinder::SUCCESS,
               expected_rdatas_, empty_rdatas_);
}

TEST_P(DatabaseClientTest, invalidRdata) {
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    EXPECT_THROW(finder->find(Name("invalidrdata.example.org."), RRType::A()),
                 DataSourceError);
    EXPECT_THROW(finder->find(Name("invalidrdata2.example.org."),
                              RRType::A(), ZoneFinder::FIND_DNSSEC),
                 DataSourceError);
}

TEST_F(MockDatabaseClientTest, missingNSEC) {
    boost::shared_ptr<DatabaseClient::Finder> finder(getFinder());

    /*
     * FIXME: For now, we can't really distinguish this bogus input
     * from not-signed zone so we can't throw. But once we can,
     * enable the original test.
     */
#if 0
    EXPECT_THROW(finder->find(Name("badnsec2.example.org."), RRType::A(), NULL,
                              ZoneFinder::FIND_DNSSEC),
                 DataSourceError);
#endif
    doFindTest(*finder, Name("badnsec2.example.org."), RRType::A(),
               RRType::A(), rrttl_, ZoneFinder::NXDOMAIN,
               expected_rdatas_, expected_sig_rdatas_);
}

/*
 * Test correct use of the updater with a journal.
 */
TEST_P(DatabaseClientTest, journal) {
    updater_ = client_->getUpdater(zname_, false, true);
    updater_->deleteRRset(*soa_);
    updater_->deleteRRset(*rrset_);
    soa_.reset(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
    soa_->addRdata(rdata::createRdata(soa_->getType(), soa_->getClass(),
                                      "ns1.example.org. admin.example.org. "
                                      "1235 3600 1800 2419200 7200"));
    updater_->addRRset(*soa_);
    updater_->addRRset(*rrset_);
    ASSERT_NO_THROW(updater_->commit());
    std::vector<JournalEntry> expected;
    expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1234,
                                    DatabaseAccessor::DIFF_DELETE,
                                    "example.org.", "SOA", "3600",
                                    "ns1.example.org. admin.example.org. "
                                    "1234 3600 1800 2419200 7200"));
    expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1234,
                                    DatabaseAccessor::DIFF_DELETE,
                                    "www.example.org.", "A", "3600",
                                    "192.0.2.2"));
    expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1235,
                                    DatabaseAccessor::DIFF_ADD,
                                    "example.org.", "SOA", "3600",
                                    "ns1.example.org. admin.example.org. "
                                    "1235 3600 1800 2419200 7200"));
    expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1235,
                                    DatabaseAccessor::DIFF_ADD,
                                    "www.example.org.", "A", "3600",
                                    "192.0.2.2"));
    checkJournal(expected);
}

TEST_P(DatabaseClientTest, journalForNSEC3) {
    // Similar to the previous test, but adding/deleting NSEC3 RRs, just to
    // confirm that NSEC3 is not special for managing diffs.
    const ConstRRsetPtr nsec3_rrset =
        textToRRset(string(nsec3_hash) + ".example.org. 3600 IN NSEC3 " +
                    string(nsec3_rdata));

    updater_ = client_->getUpdater(zname_, false, true);
    updater_->deleteRRset(*soa_);
    updater_->deleteRRset(*nsec3_rrset);

    soa_.reset(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
    soa_->addRdata(rdata::createRdata(soa_->getType(), soa_->getClass(),
                                      "ns1.example.org. admin.example.org. "
                                      "1235 3600 1800 2419200 7200"));
    updater_->addRRset(*soa_);
    updater_->addRRset(*nsec3_rrset);
    updater_->commit();
    std::vector<JournalEntry> expected;
    expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1234,
                                    DatabaseAccessor::DIFF_DELETE,
                                    "example.org.", "SOA", "3600",
                                    "ns1.example.org. admin.example.org. "
                                    "1234 3600 1800 2419200 7200"));
    expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1234,
                                    DatabaseAccessor::DIFF_DELETE,
                                    string(nsec3_hash) + ".example.org.",
                                    "NSEC3", "3600", nsec3_rdata));
    expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1235,
                                    DatabaseAccessor::DIFF_ADD,
                                    "example.org.", "SOA", "3600",
                                    "ns1.example.org. admin.example.org. "
                                    "1235 3600 1800 2419200 7200"));
    expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1235,
                                    DatabaseAccessor::DIFF_ADD,
                                    string(nsec3_hash) + ".example.org.",
                                    "NSEC3", "3600", nsec3_rdata));
    checkJournal(expected);
}

/*
 * Push multiple delete-add sequences. Checks it is allowed and all is
 * saved.
 */
TEST_P(DatabaseClientTest, journalMultiple) {
    std::vector<JournalEntry> expected;
    updater_ = client_->getUpdater(zname_, false, true);
    std::string soa_rdata = "ns1.example.org. admin.example.org. "
        "1234 3600 1800 2419200 7200";
    for (size_t i = 1; i < 100; ++ i) {
        // Remove the old SOA
        updater_->deleteRRset(*soa_);
        expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1234 + i - 1,
                                        DatabaseAccessor::DIFF_DELETE,
                                        "example.org.", "SOA", "3600",
                                        soa_rdata));
        // Create a new SOA
        soa_rdata = "ns1.example.org. admin.example.org. " +
            lexical_cast<std::string>(1234 + i) + " 3600 1800 2419200 7200";
        soa_.reset(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
        soa_->addRdata(rdata::createRdata(soa_->getType(), soa_->getClass(),
                                          soa_rdata));
        // Add the new SOA
        updater_->addRRset(*soa_);
        expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1234 + i,
                                        DatabaseAccessor::DIFF_ADD,
                                        "example.org.", "SOA", "3600",
                                        soa_rdata));
    }
    ASSERT_NO_THROW(updater_->commit());
    // Check the journal contains everything.
    checkJournal(expected);
}

/*
 * Test passing a forbidden sequence to it and expect it to throw.
 *
 * Note that we implicitly test in different testcases (these for add and
 * delete) that if the journaling is false, it doesn't expect the order.
 *
 * In this test we don't check with the real databases as this case shouldn't
 * contain backend specific behavior.
 */
TEST_F(MockDatabaseClientTest, journalBadSequence) {
    std::vector<JournalEntry> expected;
    {
        SCOPED_TRACE("Delete A before SOA");
        updater_ = client_->getUpdater(zname_, false, true);
        EXPECT_THROW(updater_->deleteRRset(*rrset_), isc::BadValue);
        // Make sure the journal is empty now
        checkJournal(expected);
    }

    {
        SCOPED_TRACE("Add before delete");
        updater_ = client_->getUpdater(zname_, false, true);
        EXPECT_THROW(updater_->addRRset(*soa_), isc::BadValue);
        // Make sure the journal is empty now
        checkJournal(expected);
    }

    {
        SCOPED_TRACE("Add A before SOA");
        updater_ = client_->getUpdater(zname_, false, true);
        // So far OK
        EXPECT_NO_THROW(updater_->deleteRRset(*soa_));
        // But we miss the add SOA here
        EXPECT_THROW(updater_->addRRset(*rrset_), isc::BadValue);
        // Make sure the journal contains only the first one
        expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1234,
                                        DatabaseAccessor::DIFF_DELETE,
                                        "example.org.", "SOA", "3600",
                                        "ns1.example.org. admin.example.org. "
                                        "1234 3600 1800 2419200 7200"));
        checkJournal(expected);
    }

    {
        SCOPED_TRACE("Commit before add");
        updater_ = client_->getUpdater(zname_, false, true);
        // So far OK
        EXPECT_NO_THROW(updater_->deleteRRset(*soa_));
        // Commit at the wrong time
        EXPECT_THROW(updater_->commit(), isc::BadValue);
        checkJournal(expected);
    }

    {
        SCOPED_TRACE("Delete two SOAs");
        updater_ = client_->getUpdater(zname_, false, true);
        // So far OK
        EXPECT_NO_THROW(updater_->deleteRRset(*soa_));
        // Delete the SOA again
        EXPECT_THROW(updater_->deleteRRset(*soa_), isc::BadValue);
        checkJournal(expected);
    }

    {
        SCOPED_TRACE("Add two SOAs");
        updater_ = client_->getUpdater(zname_, false, true);
        // So far OK
        EXPECT_NO_THROW(updater_->deleteRRset(*soa_));
        // Still OK
        EXPECT_NO_THROW(updater_->addRRset(*soa_));
        // But this one is added again
        EXPECT_THROW(updater_->addRRset(*soa_), isc::BadValue);
        expected.push_back(JournalEntry(WRITABLE_ZONE_ID, 1234,
                                        DatabaseAccessor::DIFF_ADD,
                                        "example.org.", "SOA", "3600",
                                        "ns1.example.org. admin.example.org. "
                                        "1234 3600 1800 2419200 7200"));
        checkJournal(expected);
    }
}

/*
 * Test it rejects to store journals when we request it together with
 * erasing the whole zone.
 */
TEST_P(DatabaseClientTest, journalOnErase) {
    EXPECT_THROW(client_->getUpdater(zname_, true, true), isc::BadValue);
}

/*
 * Check that exception is propagated when the journal is not implemented.
 */
TEST_F(MockDatabaseClientTest, journalNotImplemented) {
    updater_ = client_->getUpdater(Name("null.example.org"), false, true);
    EXPECT_THROW(updater_->deleteRRset(*soa_), isc::NotImplemented);
    soa_.reset(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
    soa_->addRdata(rdata::createRdata(soa_->getType(), soa_->getClass(),
                                      "ns1.example.org. admin.example.org. "
                                      "1234 3600 1800 2419201 7200"));
    EXPECT_THROW(updater_->addRRset(*soa_), isc::NotImplemented);
}

/*
 * Test that different exceptions are propagated.
 */
TEST_F(MockDatabaseClientTest, journalException) {
    updater_ = client_->getUpdater(Name("bad.example.org"), false, true);
    EXPECT_THROW(updater_->deleteRRset(*soa_), DataSourceError);
}

//
// Tests for the ZoneJournalReader
//

// Install a simple, commonly used diff sequence: making an update from one
// SOA to another.  Return the end SOA RRset for the convenience of the caller.
ConstRRsetPtr
makeSimpleDiff(DataSourceClient& client, const Name& zname,
               const RRClass& rrclass, ConstRRsetPtr begin_soa)
{
    ZoneUpdaterPtr updater = client.getUpdater(zname, false, true);
    updater->deleteRRset(*begin_soa);
    RRsetPtr soa_end(new RRset(zname, rrclass, RRType::SOA(), RRTTL(3600)));
    soa_end->addRdata(rdata::createRdata(RRType::SOA(), rrclass,
                                         "ns1.example.org. admin.example.org. "
                                         "1235 3600 1800 2419200 7200"));
    updater->addRRset(*soa_end);
    updater->commit();

    return (soa_end);
}

TEST_P(DatabaseClientTest, journalReader) {
    // Check the simple case made by makeSimpleDiff.
    ConstRRsetPtr soa_end = makeSimpleDiff(*client_, zname_, qclass_, soa_);
    pair<ZoneJournalReader::Result, ZoneJournalReaderPtr> result =
        client_->getJournalReader(zname_, 1234, 1235);
    EXPECT_EQ(ZoneJournalReader::SUCCESS, result.first);
    ZoneJournalReaderPtr jnl_reader = result.second;
    ASSERT_TRUE(jnl_reader);
    ConstRRsetPtr rrset = jnl_reader->getNextDiff();
    ASSERT_TRUE(rrset);
    rrsetCheck(soa_, rrset);
    rrset = jnl_reader->getNextDiff();
    ASSERT_TRUE(rrset);
    rrsetCheck(soa_end, rrset);
    rrset = jnl_reader->getNextDiff();
    ASSERT_FALSE(rrset);

    // Once it reaches the end of the sequence, further read attempt will
    // result in exception.
    EXPECT_THROW(jnl_reader->getNextDiff(), isc::InvalidOperation);
}

TEST_P(DatabaseClientTest, readLargeJournal) {
    // Similar to journalMultiple, but check that at a higher level.

    updater_ = client_->getUpdater(zname_, false, true);

    vector<ConstRRsetPtr> expected;
    for (size_t i = 0; i < 100; ++i) {
        // Create the old SOA and remove it, and record it in the expected list
        RRsetPtr rrset1(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
        string soa_rdata = "ns1.example.org. admin.example.org. " +
            lexical_cast<std::string>(1234 + i) + " 3600 1800 2419200 7200";
        rrset1->addRdata(rdata::createRdata(RRType::SOA(), qclass_,
                                            soa_rdata));
        updater_->deleteRRset(*rrset1);
        expected.push_back(rrset1);

        // Create a new SOA, add it, and record it.
        RRsetPtr rrset2(new RRset(zname_, qclass_, RRType::SOA(), rrttl_));
        soa_rdata = "ns1.example.org. admin.example.org. " +
            lexical_cast<std::string>(1234 + i + 1) +
            " 3600 1800 2419200 7200";
        rrset2->addRdata(rdata::createRdata(RRType::SOA(), qclass_,
                                            soa_rdata));
        updater_->addRRset(*rrset2);
        expected.push_back(rrset2);
    }
    updater_->commit();

    ZoneJournalReaderPtr jnl_reader(client_->getJournalReader(
                                        zname_, 1234, 1334).second);
    ConstRRsetPtr actual;
    int i = 0;
    while ((actual = jnl_reader->getNextDiff()) != NULL) {
        rrsetCheck(expected.at(i++), actual);
    }
    EXPECT_EQ(expected.size(), i); // we should have eaten all expected data
}

TEST_P(DatabaseClientTest, readJournalForNoRange) {
    makeSimpleDiff(*client_, zname_, qclass_, soa_);

    // The specified range does not exist in the diff storage.  The factory
    // method should result in NO_SUCH_VERSION
    pair<ZoneJournalReader::Result, ZoneJournalReaderPtr> result =
        client_->getJournalReader(zname_, 1200, 1235);
    EXPECT_EQ(ZoneJournalReader::NO_SUCH_VERSION, result.first);
    EXPECT_FALSE(result.second);
}

TEST_P(DatabaseClientTest, journalReaderForNXZone) {
    const pair<ZoneJournalReader::Result, ZoneJournalReaderPtr> result =
        client_->getJournalReader(Name("nosuchzone"), 0, 1);
    EXPECT_EQ(ZoneJournalReader::NO_SUCH_ZONE, result.first);
    EXPECT_FALSE(result.second);
}

// A helper function for journalWithBadData.  It installs a simple diff
// from one serial (of 'begin') to another ('begin' + 1), tweaking a specified
// field of data with some invalid value.
void
installBadDiff(MockAccessor& accessor, uint32_t begin,
               DatabaseAccessor::DiffRecordParams modify_param,
               const char* const data)
{
    string data1[] = {"example.org.", "SOA", "3600", "ns. root. 1 1 1 1 1"};
    string data2[] = {"example.org.", "SOA", "3600", "ns. root. 2 1 1 1 1"};
    data1[modify_param] = data;
    accessor.addRecordDiff(READONLY_ZONE_ID, begin,
                           DatabaseAccessor::DIFF_DELETE, data1);
    accessor.addRecordDiff(READONLY_ZONE_ID, begin + 1,
                           DatabaseAccessor::DIFF_ADD, data2);
}

TEST_F(MockDatabaseClientTest, journalWithBadData) {
    MockAccessor& mock_accessor =
        dynamic_cast<MockAccessor&>(*current_accessor_);

    // One of the fields from the data source is broken as an RR parameter.
    // The journal reader should still be constructed, but getNextDiff()
    // should result in exception.
    installBadDiff(mock_accessor, 1, DatabaseAccessor::DIFF_NAME,
                   "example..org");
    installBadDiff(mock_accessor, 3, DatabaseAccessor::DIFF_TYPE,
                   "bad-rrtype");
    installBadDiff(mock_accessor, 5, DatabaseAccessor::DIFF_TTL,
                   "bad-ttl");
    installBadDiff(mock_accessor, 7, DatabaseAccessor::DIFF_RDATA,
                   "bad rdata");
    EXPECT_THROW(client_->getJournalReader(zname_, 1, 2).
                 second->getNextDiff(), DataSourceError);
    EXPECT_THROW(client_->getJournalReader(zname_, 3, 4).
                 second->getNextDiff(), DataSourceError);
    EXPECT_THROW(client_->getJournalReader(zname_, 5, 6).
                 second->getNextDiff(), DataSourceError);
    EXPECT_THROW(client_->getJournalReader(zname_, 7, 8).
                 second->getNextDiff(), DataSourceError);
}

/// Let us test a little bit of NSEC3.
TEST_P(DatabaseClientTest, findNSEC3) {
    // Set up the faked hash calculator.
    setNSEC3HashCreator(&test_nsec3_hash_creator_);

    const DataSourceClient::FindResult
        zone(client_->findZone(Name("example.org")));
    ASSERT_EQ(result::SUCCESS, zone.code);
    boost::shared_ptr<DatabaseClient::Finder> finder(
        dynamic_pointer_cast<DatabaseClient::Finder>(zone.zone_finder));

    // It'll complain if there is no NSEC3PARAM yet
    EXPECT_THROW(finder->findNSEC3(Name("example.org"), false),
                 DataSourceError);
    // And enable NSEC3 in the zone.
    (GetParam()->enable_nsec3_fn)(*current_accessor_);

    // The rest is in the function, it is shared with in-memory tests
    performNSEC3Test(*finder, true);
}

TEST_P(DatabaseClientTest, createZone) {
    const Name new_name("example.com");
    const DataSourceClient::FindResult result(client_->findZone(new_name));
    ASSERT_EQ(result::NOTFOUND, result.code);

    // Adding a new zone; it should work and return true
    ASSERT_TRUE(client_->createZone(new_name));
    const DataSourceClient::FindResult result2(client_->findZone(new_name));
    ASSERT_EQ(result::SUCCESS, result2.code);
    // And the second call should return false since
    // it already exists
    allowMoreTransaction(true);
    ASSERT_FALSE(client_->createZone(new_name));
}

TEST_P(DatabaseClientTest, createZoneRollbackOnLocked) {
    const Name new_name("example.com");
    isc::datasrc::ZoneUpdaterPtr updater = client_->getUpdater(zname_, true);
    allowMoreTransaction(false);
    ASSERT_THROW(client_->createZone(new_name), DataSourceError);
    // createZone started a transaction as well, but since it failed,
    // it should have been rolled back. Roll back the other one as
    // well, and the next attempt should succeed
    updater.reset();
    allowMoreTransaction(true);
    ASSERT_TRUE(client_->createZone(new_name));
}

TEST_P(DatabaseClientTest, createZoneRollbackOnExists) {
    const Name new_name("example.com");
    ASSERT_FALSE(client_->createZone(zname_));

    // deleteZone started a transaction, but since the zone didn't even exist
    // the transaction was not committed but should have been rolled back.
    // The first transaction shouldn't leave any state, lock, etc, that
    // would hinder the second attempt.
    allowMoreTransaction(true);
    ASSERT_TRUE(client_->createZone(new_name));
}

TEST_P(DatabaseClientTest, deleteZone) {
    // Check the zone currently exists.
    EXPECT_EQ(result::SUCCESS, client_->findZone(zname_).code);

    // Deleting an existing zone; it should work and return true (previously
    // existed and is now deleted)
    EXPECT_TRUE(client_->deleteZone(zname_));

    // Now it's not found by findZone
    EXPECT_EQ(result::NOTFOUND, client_->findZone(zname_).code);

    // And the second call should return false since it doesn't exist any more
    allowMoreTransaction(true);
    EXPECT_FALSE(client_->deleteZone(zname_));
}

TEST_P(DatabaseClientTest, deleteZoneRollbackOnLocked) {
    isc::datasrc::ZoneUpdaterPtr updater = client_->getUpdater(zname_, true);

    // updater locks the DB so deleteZone() will fail.
    allowMoreTransaction(false);
    EXPECT_THROW(client_->deleteZone(zname_), DataSourceError);

    // deleteZone started a transaction as well, but since it failed,
    // it should have been rolled back. Roll back the other one as
    // well, and the next attempt should succeed
    updater.reset();
    allowMoreTransaction(true);
    EXPECT_TRUE(client_->deleteZone(zname_));
}

TEST_P(DatabaseClientTest, deleteZoneRollbackOnNotFind) {
    // attempt of deleting non-existent zone.  result in false
    const Name new_name("example.com");
    EXPECT_FALSE(client_->deleteZone(new_name));

    // deleteZone started a transaction, but since the zone didn't even exist
    // the transaction was not committed but should have been rolled back.
    // The first transaction shouldn't leave any state, lock, etc, that
    // would hinder the second attempt.
    allowMoreTransaction(true);
    EXPECT_TRUE(client_->deleteZone(zname_));
}

INSTANTIATE_TEST_CASE_P(, RRsetCollectionTest, ::testing::Values(&mock_param));

TEST_P(RRsetCollectionTest, find) {
    isc::dns::RRsetCollectionBase& collection = updater->getRRsetCollection();

    // Test the find() that returns ConstRRsetPtr
    ConstRRsetPtr rrset = collection.find(Name("www.example.org."),
                                          RRClass::IN(), RRType::A());
    ASSERT_TRUE(rrset);
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRTTL(3600), rrset->getTTL());
    EXPECT_EQ(RRClass("IN"), rrset->getClass());
    EXPECT_EQ(Name("www.example.org"), rrset->getName());

    // foo.example.org doesn't exist
    rrset = collection.find(Name("foo.example.org"), qclass_, RRType::A());
    EXPECT_FALSE(rrset);

    // www.example.org exists, but not with MX
    rrset = collection.find(Name("www.example.org"), qclass_, RRType::MX());
    EXPECT_FALSE(rrset);

    // www.example.org exists, with AAAA
    rrset = collection.find(Name("www.example.org"), qclass_, RRType::AAAA());
    EXPECT_TRUE(rrset);

    // www.example.org with AAAA does not exist in RRClass::CH()
    rrset = collection.find(Name("www.example.org"), RRClass::CH(),
                            RRType::AAAA());
    EXPECT_FALSE(rrset);

    // Out-of-zone find()s must not throw.
    rrset = collection.find(Name("www.example.com"), qclass_, RRType::A());
    EXPECT_FALSE(rrset);

    // "cname.example.org." with type CNAME should return the CNAME RRset
    rrset = collection.find(Name("cname.example.org"), qclass_,
                            RRType::CNAME());
    ASSERT_TRUE(rrset);
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(Name("cname.example.org"), rrset->getName());

    // "cname.example.org." with type A should return nothing
    rrset = collection.find(Name("cname.example.org"), qclass_, RRType::A());
    EXPECT_FALSE(rrset);

    // "dname.example.org." with type DNAME should return the DNAME RRset
    rrset = collection.find(Name("dname.example.org"), qclass_,
                            RRType::DNAME());
    ASSERT_TRUE(rrset);
    EXPECT_EQ(RRType::DNAME(), rrset->getType());
    EXPECT_EQ(Name("dname.example.org"), rrset->getName());

    // "below.dname.example.org." with type AAAA should return nothing
    rrset = collection.find(Name("below.dname.example.org"),
                            qclass_, RRType::AAAA());
    EXPECT_FALSE(rrset);

    // "below.dname.example.org." with type A does not return the record
    // (see top of file). See \c isc::datasrc::RRsetCollectionBase::find()
    // documentation for details.
    rrset = collection.find(Name("below.dname.example.org"), qclass_,
                            RRType::A());
    EXPECT_FALSE(rrset);

    // With the FIND_GLUE_OK option passed to ZoneFinder's find(),
    // searching for "delegation.example.org." with type NS should
    // return the NS record. Without FIND_GLUE_OK, ZoneFinder's find()
    // would return DELEGATION and the find() below would return
    // nothing.
    rrset = collection.find(Name("delegation.example.org"), qclass_,
                            RRType::NS());
    ASSERT_TRUE(rrset);
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(Name("delegation.example.org"), rrset->getName());

    // With the NO_WILDCARD option passed to ZoneFinder's find(),
    // searching for some "foo.wildcard.example.org." would make
    // ZoneFinder's find() return NXDOMAIN, and the find() below should
    // return nothing.
    rrset = collection.find(Name("foo.wild.example.org"), qclass_,
                            RRType::A());
    EXPECT_FALSE(rrset);

    // Searching directly for "*.wild.example.org." should return the
    // record.
    rrset = collection.find(Name("*.wild.example.org"), qclass_,
                            RRType::A());
    ASSERT_TRUE(rrset);
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(Name("*.wild.example.org"), rrset->getName());
}

TEST_P(RRsetCollectionTest, iteratorTest) {
    isc::dns::RRsetCollectionBase& collection = updater->getRRsetCollection();

    // Iterators are currently not implemented.
    EXPECT_THROW(collection.begin(), isc::NotImplemented);
    EXPECT_THROW(collection.end(), isc::NotImplemented);
}

// This inherit the RRsetCollectionTest cases except for the parameterized
// setup; it's intended to be used selected test cases that only work for mock
// data sources.
class MockRRsetCollectionTest : public RRsetCollectionTest {
protected:
    virtual void SetUp() {
        createClient(&mock_param);
        updater = client_->getUpdater(zname_, false);
    }
};

TEST_F(MockRRsetCollectionTest, findError) {
    // A test using the MockAccessor for checking that FindError is
    // thrown properly if a find attempt using ZoneFinder results in a
    // DataSourceError.
    //
    // The "dsexception.example.org." name is rigged by the MockAccessor
    // to throw a DataSourceError.
    EXPECT_THROW({
            updater->getRRsetCollection().find(
                Name("dsexception.example.org"), qclass_, RRType::A());
        }, RRsetCollectionError);
}

// Test that using addRRset() or deleteRRset() on the ZoneUpdater throws
// after an RRsetCollection is created.
TEST_P(RRsetCollectionTest, updateThrows) {
    // 1. Addition test

    // addRRset() must not throw.
    updater->addRRset(*rrset_);

    // Now setup a new updater and call getRRsetCollection() on it.
    updater.reset();
    updater = client_->getUpdater(zname_, false);

    // Just call getRRsetCollection() here. The test using .find() is
    // unnecessary for the purpose of this test case, but we have it to
    // use the result of getRRsetCollection() and silence some compiler
    // complaining about ignoring the return value of
    // getRRsetCollection().
    EXPECT_FALSE(updater->getRRsetCollection().
                 find(Name("www.example.org"), RRClass::IN(), RRType::MX()));

    // addRRset() must throw isc::InvalidOperation here.
    EXPECT_THROW(updater->addRRset(*rrset_), isc::InvalidOperation);

    // 2. Deletion test

    // deleteRRset() must not throw.
    updater.reset();
    updater = client_->getUpdater(zname_, false);
    updater->addRRset(*rrset_);
    updater->deleteRRset(*rrset_);

    // Now setup a new updater and call getRRsetCollection() on it.
    updater.reset();
    updater = client_->getUpdater(zname_, false);
    updater->addRRset(*rrset_);

    // Just call getRRsetCollection() here. The .find() is unnecessary,
    // but we have it to use the result of getRRsetCollection().
    updater->getRRsetCollection().find(Name("www.example.org"),
                                       RRClass::IN(), RRType::MX());

    // deleteRRset() must throw isc::InvalidOperation here.
    EXPECT_THROW(updater->deleteRRset(*rrset_), isc::InvalidOperation);
}

// Test that using an RRsetCollection after calling commit() on the
// ZoneUpdater throws, as the RRsetCollection is disabled.
TEST_P(RRsetCollectionTest, useAfterCommitThrows) {
     isc::dns::RRsetCollectionBase& collection =
         updater->getRRsetCollection();

     // find() must not throw here.
     collection.find(Name("foo.wild.example.org"), qclass_, RRType::A());

     updater->commit();

     // find() must throw RRsetCollectionError here, as the
     // RRsetCollection is disabled.
     EXPECT_THROW(collection.find(Name("foo.wild.example.org"), qclass_,
                                  RRType::A()), RRsetCollectionError);
}

}
