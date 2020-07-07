// Copyright (C) 2019-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef AUDIT_ENTRY_H
#define AUDIT_ENTRY_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <string>

namespace isc {
namespace db {

class AuditEntry;

/// @brief Pointer to the @c AuditEntry object.
typedef boost::shared_ptr<AuditEntry> AuditEntryPtr;

/// @brief Represents a single entry in the audit table.
///
/// The audit tables are used in the databases to track incremental
/// changes, e.g. configuration changes applied via the configuration
/// backend. The backend can query for the entries in the audit table
/// to identify the SQL table in which the records were modified, the
/// identifiers of the modified objects, type of the modifications,
/// time of the modifications and optional log messages associated
/// with the modifications.
///
/// The server should remember the most recent modification time out of
/// all audit entries it has fetched. During the next attempt to fetch
/// the most recent modifications in the database it will query for all
/// entries with later modification time than stored. That way the
/// server queries only for the audit entries it hasn't fetched yet.
/// In the case two (or more) successive audit entries have the same
/// modification time the strictly increasing modification id is used.
///
/// When the modification type of the entry is set to
/// @c AuditEntry::ModificationType::DELETE, the corresponding
/// configuration entry is already gone from the database. For example:
/// when a subnet with ID of 123 is deleted from the dhcp4_subnet
/// table, the audit entry similar to this will be stored in the audit
/// table:
///
/// - object_type: "dhcp4_subnet"
/// - object_id: 123
/// - modification_type: 3 (DELETE)
/// - modification_time: "2019-01-15 15:45:23"
/// - revision id: 234
/// - log_message: "DHCPv4 subnet 123 deleted"
///
/// The subnet is instantly removed from the dhcp4_subnet table. When
/// the server finds such entry in the audit table, it removes the
/// subnet 123 from its (in-memory) configuration. There is no need
/// make additional queries to fetch updated data from the dhcp4_subnet
/// table, unless there are also audit entries indicating that some
/// new subnets have been added or some subnets have been updated.
class AuditEntry {
public:

    /// @brief Types of the modifications.
    ///
    /// The numbers representing those modification types correspond
    /// to the values representing them in the database.
    enum class ModificationType : uint8_t {
        CREATE = 0,
        UPDATE = 1,
        DELETE = 2
    };

    /// @brief Constructor using explicit modification time and id.
    ///
    /// @param object_type name of the table where data was modified.
    /// @param object_id identifier of the modified record in this table.
    /// @param modification_type type of the modification, e.g. DELETE.
    /// @param modification_time time of modification for that record.
    /// @param revision_id identifier of the revision.
    /// @param log_message optional log message associated with the
    /// modification.
    AuditEntry(const std::string& object_type,
               const uint64_t object_id,
               const ModificationType& modification_type,
               const boost::posix_time::ptime& modification_time,
               const uint64_t revision_id,
               const std::string& log_message);

    /// @brief Constructor using default modification time.
    ///
    /// @param object_type name of the table where data was modified.
    /// @param object_id identifier of the modified record in this table.
    /// @param modification_type type of the modification, e.g. DELETE.
    /// @param revision_id identifier of the revision.
    /// @param log_message optional log message associated with the
    /// modification.
    AuditEntry(const std::string& object_type,
               const uint64_t object_id,
               const ModificationType& modification_type,
               const uint64_t revision_id,
               const std::string& log_message);

    /// @brief Factory function creating an instance of @c AuditEntry.
    ///
    /// This function should be used to create an instance of the audit
    /// entry within a hooks library in cases when the library may be
    /// unloaded before the object is destroyed. This ensures that the
    /// ownership of the object by the Kea process is retained.
    ///
    /// @param object_type name of the table where data was modified.
    /// @param object_id identifier of the modified record in this table.
    /// @param modification_type type of the modification, e.g. DELETE.
    /// @param modification_time time of modification for that record.
    /// @param revision_id identifier of the revision.
    /// @param log_message optional log message associated with the
    /// modification.
    ///
    /// @return Pointer to the @c AuditEntry instance.
    static AuditEntryPtr create(const std::string& object_type,
                                const uint64_t object_id,
                                const ModificationType& modification_type,
                                const boost::posix_time::ptime& modification_time,
                                const uint64_t revision_id,
                                const std::string& log_message);

    /// @brief Factory function creating an instance of @c AuditEntry.
    ///
    /// This function should be used to create an instance of the audit
    /// entry within a hooks library in cases when the library may be
    /// unloaded before the object is destroyed. This ensures that the
    /// ownership of the object by the Kea process is retained.
    ///
    /// @param object_type name of the table where data was modified.
    /// @param object_id identifier of the modified record in this table.
    /// @param modification_type type of the modification, e.g. DELETE.
    /// @param revision_id identifier of the revision.
    /// @param log_message optional log message associated with the
    /// modification.
    ///
    /// @return Pointer to the @c AuditEntry instance.
    static AuditEntryPtr create(const std::string& object_type,
                                const uint64_t object_id,
                                const ModificationType& modification_type,
                                const uint64_t revision_id,
                                const std::string& log_message);

    /// @brief Returns object type.
    ///
    /// @return Name of the table in which the modification is present.
    std::string getObjectType() const {
        return (object_type_);
    }

    /// @brief Returns object id.
    ///
    /// @return Identifier of the added, updated or deleted object.
    uint64_t getObjectId() const {
        return (object_id_);
    }

    /// @brief Returns modification type.
    ///
    /// @return Type of the modification, e.g. DELETE.
    ModificationType getModificationType() const {
        return (modification_type_);
    }

    /// @brief Returns modification time.
    ///
    /// @return Modification time of the corresponding record.
    boost::posix_time::ptime getModificationTime() const {
        return (modification_time_);
    }

    /// @brief Returns revision id.
    ///
    /// The revision id is used when two audit entries have the same
    /// modification time.
    ///
    /// @return Identifier of the revision.
    uint64_t getRevisionId() const {
        return (revision_id_);
    }

    /// @brief Returns log message.
    ///
    /// @return Optional log message corresponding to the changes.
    std::string getLogMessage() const {
        return (log_message_);
    }

private:

    /// @brief Validates the values specified for the audit entry.
    ///
    /// @throw BadValue if the object type is empty or if the
    /// modification time is not a date time value.
    void validate() const;

    /// @brief Object type.
    std::string object_type_;

    /// @brief Object id.
    uint64_t object_id_;

    /// @brief Modification type.
    ModificationType modification_type_;

    /// @brief Modification time.
    boost::posix_time::ptime modification_time_;

    /// @brief Revision id.
    ///
    /// The revision id is used when two audit entries have the same
    /// modification time.
    uint64_t revision_id_;

    /// @brief Log message.
    std::string log_message_;
};

/// @brief Tag used to access index by object type.
struct AuditEntryObjectTypeTag { };

/// @brief Tag used to access index by modification time.
struct AuditEntryModificationTimeIdTag { };

/// @brief Tag used to access index by object id.
struct AuditEntryObjectIdTag { };

/// @brief Multi index container holding @c AuditEntry instances.
///
/// This container provides indexes to access the audit entries
/// by object type and modification time.
typedef boost::multi_index_container<
    // The container holds pointers to @c AuditEntry objects.
    AuditEntryPtr,
    // First index allows for accessing by the object type.
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<AuditEntryObjectTypeTag>,
            boost::multi_index::composite_key<
                AuditEntry,
                boost::multi_index::const_mem_fun<
                    AuditEntry,
                    std::string,
                    &AuditEntry::getObjectType
                >,
                boost::multi_index::const_mem_fun<
                    AuditEntry,
                    AuditEntry::ModificationType,
                    &AuditEntry::getModificationType
                >
            >
        >,

        // Second index allows for accessing by the modification time and id.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<AuditEntryModificationTimeIdTag>,
            boost::multi_index::composite_key<
                AuditEntry,
                boost::multi_index::const_mem_fun<
                    AuditEntry,
                    boost::posix_time::ptime,
                    &AuditEntry::getModificationTime
                >,
                boost::multi_index::const_mem_fun<
                    AuditEntry,
                    uint64_t,
                    &AuditEntry::getRevisionId
                >
            >
        >,

        // Third index allows for accessing by the object id.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<AuditEntryObjectIdTag>,
            boost::multi_index::const_mem_fun<
                AuditEntry,
                uint64_t,
                &AuditEntry::getObjectId
            >
        >
    >
> AuditEntryCollection;

//// @brief Pointer to the @c AuditEntryCollection object.
typedef boost::shared_ptr<AuditEntryCollection> AuditEntryCollectionPtr;

} // end of namespace isc::db
} // end of namespace isc

#endif
