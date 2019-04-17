// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <database/audit_entry.h>
#include <exceptions/exceptions.h>
#include <boost/make_shared.hpp>

namespace isc {
namespace db {

AuditEntry::AuditEntry(const std::string& object_type,
                       const uint64_t object_id,
                       const ModificationType& modification_type,
                       const boost::posix_time::ptime& modification_time,
                       const std::string& log_message)
    : object_type_(object_type),
      object_id_(object_id),
      modification_type_(modification_type),
      modification_time_(modification_time),
      log_message_(log_message) {
    // Check if the provided values are sane.
    validate();
}

AuditEntry::AuditEntry(const std::string& object_type,
                       const uint64_t object_id,
                       const ModificationType& modification_type,
                       const std::string& log_message)
    : object_type_(object_type),
      object_id_(object_id),
      modification_type_(modification_type),
      modification_time_(boost::posix_time::microsec_clock::local_time()),
      log_message_(log_message) {
    // Check if the provided values are sane.
    validate();
}

AuditEntryPtr
AuditEntry::create(const std::string& object_type,
                   const uint64_t object_id,
                   const ModificationType& modification_type,
                   const boost::posix_time::ptime& modification_time,
                   const std::string& log_message) {
    return (boost::make_shared<AuditEntry>(object_type, object_id,
                                           modification_type,
                                           modification_time,
                                           log_message));
}

AuditEntryPtr
AuditEntry::create(const std::string& object_type,
                   const uint64_t object_id,
                   const ModificationType& modification_type,
                   const std::string& log_message) {
    return (boost::make_shared<AuditEntry>(object_type, object_id,
                                           modification_type,
                                           log_message));
}

void
AuditEntry::validate() const {
    // object type can't be empty
    if (object_type_.empty()) {
        isc_throw(BadValue, "object type can't be empty in the database "
                  "audit entry");

    // modification time must be a valid date time value
    } else if (modification_time_.is_not_a_date_time()) {
        isc_throw(BadValue, "modification time value is not a valid time "
                  "object in the database audit entry");
    }
}

} // end of namespace isc::db
} // end of namespace isc
